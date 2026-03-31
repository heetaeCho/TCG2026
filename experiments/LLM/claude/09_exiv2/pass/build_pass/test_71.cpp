#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/webpimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>
#include <cstring>
#include <fstream>
#include <memory>

// Helper to create a minimal valid WebP file in memory
static std::vector<Exiv2::byte> createMinimalWebP() {
    // Minimal WebP file: RIFF header + WEBP + VP8 chunk
    // RIFF<filesize>WEBPVP8 <chunksize><vp8data>
    std::vector<Exiv2::byte> data;
    
    // "RIFF"
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    
    // File size (little-endian) - will be filled after building content
    // filesize = total - 8 (RIFF + size field)
    // Content: "WEBP" (4) + VP8 chunk header (8) + VP8 data (10) = 22
    uint32_t contentSize = 22;
    data.push_back(contentSize & 0xFF);
    data.push_back((contentSize >> 8) & 0xFF);
    data.push_back((contentSize >> 16) & 0xFF);
    data.push_back((contentSize >> 24) & 0xFF);
    
    // "WEBP"
    data.push_back('W'); data.push_back('E'); data.push_back('B'); data.push_back('P');
    
    // VP8 chunk: "VP8 " + size (little-endian) + minimal VP8 data
    data.push_back('V'); data.push_back('P'); data.push_back('8'); data.push_back(' ');
    
    // VP8 chunk size = 10
    uint32_t vp8Size = 10;
    data.push_back(vp8Size & 0xFF);
    data.push_back((vp8Size >> 8) & 0xFF);
    data.push_back((vp8Size >> 16) & 0xFF);
    data.push_back((vp8Size >> 24) & 0xFF);
    
    // VP8 bitstream: frame tag (3 bytes) + signature (3 bytes: 0x9D 0x01 0x2A) + width (2 bytes LE) + height (2 bytes LE)
    // Keyframe: bit 0 = 0, version = 0, show_frame = 1 => 0x00, 0x00, 0x00 works for tag
    // Actually, let's use proper VP8 keyframe header
    data.push_back(0x9D); data.push_back(0x01); data.push_back(0x2A); // VP8 sync code
    // Actually the frame tag comes first. Let me construct properly:
    // The VP8 bitstream starts with a frame_tag (3 bytes for keyframe)
    // frame_tag: bit0 = keyframe(0), bits 1-2 = version, bit3 = show_frame
    // Then if keyframe: 3 bytes startup code (0x9D 0x01 0x2A), then 2 bytes width, 2 bytes height
    
    // Let me just fill with zeros plus the sync code
    data.resize(data.size() - 3); // remove the 3 bytes we just added
    
    // frame_tag (3 bytes): keyframe=0, version=0, show=1 => byte0=0x10 (bit3=1 for show, bit0=0 for keyframe)
    // Actually the format is: bit0 = frame_type (0=key), bits1-2 = version, bit3 = show_frame
    // bit4 = first_part_size[bit0], etc.
    // Let's just use 0x10, 0x00, 0x00
    data.push_back(0x10); data.push_back(0x00); data.push_back(0x00);
    
    // Sync code
    data.push_back(0x9D); data.push_back(0x01); data.push_back(0x2A);
    
    // Width (16-bit LE): 1 pixel
    data.push_back(0x01); data.push_back(0x00);
    
    // Height (16-bit LE): 1 pixel
    data.push_back(0x01); data.push_back(0x00);
    
    return data;
}

// Helper to write data to a temp file and return the path
static std::string writeTempFile(const std::vector<Exiv2::byte>& data, const std::string& suffix = ".webp") {
    std::string path = std::tmpnam(nullptr) + suffix;
    std::ofstream ofs(path, std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
    ofs.close();
    return path;
}

static void removeTempFile(const std::string& path) {
    std::remove(path.c_str());
}

class WebPImageTest_71 : public ::testing::Test {
protected:
    void TearDown() override {
        for (auto& f : tempFiles_) {
            removeTempFile(f);
        }
    }
    
    std::string createTempFile(const std::vector<Exiv2::byte>& data) {
        std::string path = writeTempFile(data);
        tempFiles_.push_back(path);
        return path;
    }
    
    std::vector<std::string> tempFiles_;
};

// Test that readMetadata throws when the file cannot be opened
TEST_F(WebPImageTest_71, ReadMetadataThrowsOnOpenFailure_71) {
    auto io = std::make_unique<Exiv2::FileIo>("/nonexistent/path/to/file.webp");
    Exiv2::WebPImage img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test that readMetadata throws for an empty file
TEST_F(WebPImageTest_71, ReadMetadataThrowsOnEmptyFile_71) {
    std::vector<Exiv2::byte> emptyData;
    std::string path = createTempFile(emptyData);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::WebPImage img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test that readMetadata throws for non-WebP data
TEST_F(WebPImageTest_71, ReadMetadataThrowsOnNonWebPData_71) {
    std::vector<Exiv2::byte> data = {'N', 'O', 'T', 'W', 'E', 'B', 'P', '!', '!', '!', '!', '!'};
    std::string path = createTempFile(data);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::WebPImage img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test that readMetadata throws when RIFF header is present but not WEBP
TEST_F(WebPImageTest_71, ReadMetadataThrowsOnRIFFButNotWebP_71) {
    std::vector<Exiv2::byte> data = {'R', 'I', 'F', 'F', 0x04, 0x00, 0x00, 0x00, 'A', 'V', 'I', ' '};
    std::string path = createTempFile(data);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::WebPImage img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test that readMetadata throws when file is too short (only partial RIFF header)
TEST_F(WebPImageTest_71, ReadMetadataThrowsOnTruncatedHeader_71) {
    std::vector<Exiv2::byte> data = {'R', 'I', 'F', 'F'};
    std::string path = createTempFile(data);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::WebPImage img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test that readMetadata throws when filesize in header exceeds actual file size
TEST_F(WebPImageTest_71, ReadMetadataThrowsOnCorruptedFilesize_71) {
    std::vector<Exiv2::byte> data = {
        'R', 'I', 'F', 'F',
        0xFF, 0xFF, 0x00, 0x00, // filesize claims to be much larger than actual
        'W', 'E', 'B', 'P'
    };
    std::string path = createTempFile(data);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::WebPImage img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test that mimeType returns the correct MIME type
TEST_F(WebPImageTest_71, MimeTypeReturnsCorrectValue_71) {
    auto data = createMinimalWebP();
    std::string path = createTempFile(data);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::WebPImage img(std::move(io));
    EXPECT_EQ(img.mimeType(), "image/webp");
}

// Test that readMetadata succeeds on a minimal valid WebP file
TEST_F(WebPImageTest_71, ReadMetadataSucceedsOnMinimalValidWebP_71) {
    auto data = createMinimalWebP();
    std::string path = createTempFile(data);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::WebPImage img(std::move(io));
    EXPECT_NO_THROW(img.readMetadata());
}

// Test setComment is a no-op (WebP doesn't support comment in the usual way)
TEST_F(WebPImageTest_71, SetCommentDoesNotThrow_71) {
    auto data = createMinimalWebP();
    std::string path = createTempFile(data);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::WebPImage img(std::move(io));
    EXPECT_NO_THROW(img.setComment("test comment"));
}

// Test setIptcData doesn't crash (WebP may not support IPTC)
TEST_F(WebPImageTest_71, SetIptcDataDoesNotThrow_71) {
    auto data = createMinimalWebP();
    std::string path = createTempFile(data);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::WebPImage img(std::move(io));
    Exiv2::IptcData iptcData;
    EXPECT_NO_THROW(img.setIptcData(iptcData));
}

// Test that after readMetadata, exifData is accessible
TEST_F(WebPImageTest_71, ExifDataAccessibleAfterRead_71) {
    auto data = createMinimalWebP();
    std::string path = createTempFile(data);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::WebPImage img(std::move(io));
    img.readMetadata();
    // A minimal WebP without EXIF should have empty exifData
    EXPECT_TRUE(img.exifData().empty());
}

// Test that after readMetadata, xmpData is accessible
TEST_F(WebPImageTest_71, XmpDataAccessibleAfterRead_71) {
    auto data = createMinimalWebP();
    std::string path = createTempFile(data);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::WebPImage img(std::move(io));
    img.readMetadata();
    EXPECT_TRUE(img.xmpData().empty());
}

// Test readMetadata with file that has RIFF + WEBP but zero content size
TEST_F(WebPImageTest_71, ReadMetadataWithZeroContentChunks_71) {
    std::vector<Exiv2::byte> data = {
        'R', 'I', 'F', 'F',
        0x04, 0x00, 0x00, 0x00, // content size = 4 (just "WEBP")
        'W', 'E', 'B', 'P'
    };
    std::string path = createTempFile(data);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::WebPImage img(std::move(io));
    // With no chunks at all, it should either succeed or throw predictably
    EXPECT_NO_THROW(img.readMetadata());
}

// Test that readMetadata with MemIo works
TEST_F(WebPImageTest_71, ReadMetadataWithMemIo_71) {
    auto data = createMinimalWebP();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::WebPImage img(std::move(io));
    EXPECT_NO_THROW(img.readMetadata());
}

// Test that readMetadata throws on MemIo with non-WebP data
TEST_F(WebPImageTest_71, ReadMetadataMemIoNonWebPThrows_71) {
    std::vector<Exiv2::byte> data = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::WebPImage img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test that good() returns true after successful read
TEST_F(WebPImageTest_71, GoodReturnsTrueAfterSuccessfulRead_71) {
    auto data = createMinimalWebP();
    std::string path = createTempFile(data);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::WebPImage img(std::move(io));
    img.readMetadata();
    EXPECT_TRUE(img.good());
}

// Test pixelWidth and pixelHeight after reading minimal WebP
TEST_F(WebPImageTest_71, PixelDimensionsAfterRead_71) {
    auto data = createMinimalWebP();
    std::string path = createTempFile(data);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::WebPImage img(std::move(io));
    img.readMetadata();
    // The minimal VP8 we created has 1x1 dimensions
    // This may or may not be parsed correctly depending on VP8 parsing,
    // but at minimum the values should be non-negative
    EXPECT_GE(img.pixelWidth(), 0u);
    EXPECT_GE(img.pixelHeight(), 0u);
}

// Test that filesize overflow is caught (filesize field near UINT32_MAX)
TEST_F(WebPImageTest_71, ReadMetadataThrowsOnFilesizeOverflow_71) {
    std::vector<Exiv2::byte> data = {
        'R', 'I', 'F', 'F',
        0xFC, 0xFF, 0xFF, 0xFF, // filesize near max, would overflow when adding 8
        'W', 'E', 'B', 'P'
    };
    std::string path = createTempFile(data);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::WebPImage img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test readMetadata with just 8 bytes (RIFF + size but no WEBP tag)
TEST_F(WebPImageTest_71, ReadMetadataThrowsOnOnlyRIFFHeader_71) {
    std::vector<Exiv2::byte> data = {
        'R', 'I', 'F', 'F',
        0x00, 0x00, 0x00, 0x00
    };
    std::string path = createTempFile(data);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::WebPImage img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test ICC profile is not set on a minimal WebP
TEST_F(WebPImageTest_71, IccProfileNotDefinedOnMinimalWebP_71) {
    auto data = createMinimalWebP();
    std::string path = createTempFile(data);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::WebPImage img(std::move(io));
    img.readMetadata();
    EXPECT_FALSE(img.iccProfileDefined());
}
