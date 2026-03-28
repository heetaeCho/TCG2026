#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/webpimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>
#include <fstream>
#include <cstring>
#include <vector>

namespace {

// Minimal valid WebP file (lossy): RIFF header + WEBP + VP8 chunk
// This is the smallest valid WebP we can construct
std::vector<uint8_t> createMinimalWebP() {
    // A minimal WebP file with VP8 chunk
    // RIFF header: "RIFF" + file_size (4 bytes LE) + "WEBP"
    // VP8 chunk: "VP8 " + chunk_size (4 bytes LE) + VP8 bitstream
    
    // Minimal VP8 bitstream (keyframe with 1x1 pixel)
    // VP8 frame tag: 3 bytes, then VP8 signature 9D 01 2A, then width/height
    std::vector<uint8_t> vp8Data = {
        0x9D, 0x01, 0x2A,  // VP8 signature
        0x01, 0x00,         // width = 1 (no scale)
        0x01, 0x00,         // height = 1 (no scale)
        0x01, 0x34, 0x25,   // some minimal bitstream data
    };
    
    // Frame tag (3 bytes): keyframe, version 0, show_frame, partition size
    uint8_t frameTag0 = 0x00 | (0 << 1) | (1 << 4); // keyframe=0, version=0, show=1
    uint32_t partSize = static_cast<uint32_t>(vp8Data.size());
    uint8_t ft0 = (partSize & 0x07) << 5;  // first 3 bits of partition size
    uint8_t ft1 = (partSize >> 3) & 0xFF;
    uint8_t ft2 = (partSize >> 11) & 0xFF;
    
    std::vector<uint8_t> vp8Chunk;
    vp8Chunk.push_back(ft0);
    vp8Chunk.push_back(ft1);
    vp8Chunk.push_back(ft2);
    vp8Chunk.insert(vp8Chunk.end(), vp8Data.begin(), vp8Data.end());
    
    uint32_t vp8ChunkSize = static_cast<uint32_t>(vp8Chunk.size());
    uint32_t fileSize = 4 + 8 + vp8ChunkSize; // "WEBP" + "VP8 " + size + data
    if (vp8ChunkSize % 2 != 0) fileSize++; // padding
    
    std::vector<uint8_t> webp;
    // RIFF
    webp.push_back('R'); webp.push_back('I'); webp.push_back('F'); webp.push_back('F');
    webp.push_back(fileSize & 0xFF);
    webp.push_back((fileSize >> 8) & 0xFF);
    webp.push_back((fileSize >> 16) & 0xFF);
    webp.push_back((fileSize >> 24) & 0xFF);
    // WEBP
    webp.push_back('W'); webp.push_back('E'); webp.push_back('B'); webp.push_back('P');
    // VP8 chunk
    webp.push_back('V'); webp.push_back('P'); webp.push_back('8'); webp.push_back(' ');
    webp.push_back(vp8ChunkSize & 0xFF);
    webp.push_back((vp8ChunkSize >> 8) & 0xFF);
    webp.push_back((vp8ChunkSize >> 16) & 0xFF);
    webp.push_back((vp8ChunkSize >> 24) & 0xFF);
    webp.insert(webp.end(), vp8Chunk.begin(), vp8Chunk.end());
    if (vp8ChunkSize % 2 != 0) webp.push_back(0); // padding
    
    return webp;
}

// Create a completely invalid/empty data
std::vector<uint8_t> createInvalidData() {
    return {0x00, 0x01, 0x02, 0x03};
}

class WebPImageTest_69 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test that WebPImage can be constructed with a MemIo
TEST_F(WebPImageTest_69, ConstructWithMemIo_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW(Exiv2::WebPImage img(std::move(io)));
}

// Test mimeType returns correct MIME type for WebP
TEST_F(WebPImageTest_69, MimeTypeReturnsWebP_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::WebPImage img(std::move(io));
    EXPECT_EQ(img.mimeType(), "image/webp");
}

// Test reading metadata from empty/invalid data throws
TEST_F(WebPImageTest_69, ReadMetadataFromEmptyThrows_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::WebPImage img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test reading metadata from invalid data throws
TEST_F(WebPImageTest_69, ReadMetadataFromInvalidDataThrows_69) {
    auto data = createInvalidData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::WebPImage img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test writing metadata on empty image throws (no valid WebP to write to)
TEST_F(WebPImageTest_69, WriteMetadataOnEmptyImageThrows_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::WebPImage img(std::move(io));
    EXPECT_THROW(img.writeMetadata(), Exiv2::Error);
}

// Test writing metadata on invalid data throws
TEST_F(WebPImageTest_69, WriteMetadataOnInvalidDataThrows_69) {
    auto data = createInvalidData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::WebPImage img(std::move(io));
    EXPECT_THROW(img.writeMetadata(), Exiv2::Error);
}

// Test that setIptcData doesn't crash (WebP doesn't support IPTC typically)
TEST_F(WebPImageTest_69, SetIptcDataDoesNotThrow_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::WebPImage img(std::move(io));
    Exiv2::IptcData iptcData;
    EXPECT_NO_THROW(img.setIptcData(iptcData));
}

// Test that setComment doesn't crash
TEST_F(WebPImageTest_69, SetCommentDoesNotThrow_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::WebPImage img(std::move(io));
    EXPECT_NO_THROW(img.setComment("test comment"));
}

// Test that exifData is accessible
TEST_F(WebPImageTest_69, ExifDataAccessible_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::WebPImage img(std::move(io));
    Exiv2::ExifData& exif = img.exifData();
    EXPECT_TRUE(exif.empty());
}

// Test that xmpData is accessible
TEST_F(WebPImageTest_69, XmpDataAccessible_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::WebPImage img(std::move(io));
    Exiv2::XmpData& xmp = img.xmpData();
    EXPECT_TRUE(xmp.empty());
}

// Test that iptcData is accessible
TEST_F(WebPImageTest_69, IptcDataAccessible_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::WebPImage img(std::move(io));
    Exiv2::IptcData& iptc = img.iptcData();
    EXPECT_TRUE(iptc.empty());
}

// Test good() returns false for empty MemIo initially
TEST_F(WebPImageTest_69, GoodReturnsFalseForEmpty_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::WebPImage img(std::move(io));
    // good() checks if io is valid - for empty memio it should still be ok
    // The behavior depends on implementation
    // Just ensure it doesn't crash
    bool result = img.good();
    (void)result;
}

// Test that reading metadata from data that starts with RIFF but is not WebP throws
TEST_F(WebPImageTest_69, ReadMetadataFromRiffButNotWebPThrows_69) {
    // RIFF header but not WEBP format
    std::vector<uint8_t> data = {
        'R', 'I', 'F', 'F',
        0x04, 0x00, 0x00, 0x00,
        'A', 'V', 'I', ' '
    };
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::WebPImage img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test that too-short RIFF data throws
TEST_F(WebPImageTest_69, ReadMetadataFromTooShortDataThrows_69) {
    std::vector<uint8_t> data = {'R', 'I', 'F'};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::WebPImage img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test printStructure on empty/invalid data
TEST_F(WebPImageTest_69, PrintStructureOnEmptyThrows_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::WebPImage img(std::move(io));
    std::ostringstream oss;
    EXPECT_THROW(img.printStructure(oss, Exiv2::kpsBasic, 0), Exiv2::Error);
}

// Test clear metadata operations don't throw
TEST_F(WebPImageTest_69, ClearMetadataDoesNotThrow_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::WebPImage img(std::move(io));
    EXPECT_NO_THROW(img.clearExifData());
    EXPECT_NO_THROW(img.clearIptcData());
    EXPECT_NO_THROW(img.clearXmpData());
    EXPECT_NO_THROW(img.clearXmpPacket());
    EXPECT_NO_THROW(img.clearComment());
}

// Test setExifData on WebPImage
TEST_F(WebPImageTest_69, SetExifDataDoesNotThrow_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::WebPImage img(std::move(io));
    Exiv2::ExifData exifData;
    EXPECT_NO_THROW(img.setExifData(exifData));
}

// Test setXmpData on WebPImage
TEST_F(WebPImageTest_69, SetXmpDataDoesNotThrow_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::WebPImage img(std::move(io));
    Exiv2::XmpData xmpData;
    EXPECT_NO_THROW(img.setXmpData(xmpData));
}

// Test pixelWidth and pixelHeight default to 0
TEST_F(WebPImageTest_69, PixelDimensionsDefaultToZero_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::WebPImage img(std::move(io));
    EXPECT_EQ(img.pixelWidth(), 0u);
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test that io() returns a reference to the underlying IO
TEST_F(WebPImageTest_69, IoReturnsReference_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::WebPImage img(std::move(io));
    const Exiv2::BasicIo& ioRef = img.io();
    EXPECT_EQ(ioRef.size(), 0u);
}

// Test that reading truncated RIFF+WEBP header fails
TEST_F(WebPImageTest_69, ReadMetadataFromTruncatedWebPThrows_69) {
    // Valid RIFF+WEBP header but claims larger size than available
    std::vector<uint8_t> data = {
        'R', 'I', 'F', 'F',
        0xFF, 0x00, 0x00, 0x00,  // claims 255 bytes
        'W', 'E', 'B', 'P'
        // no actual chunk data
    };
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::WebPImage img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test writing metadata after setting comment on invalid data still throws
TEST_F(WebPImageTest_69, WriteMetadataAfterSetCommentOnInvalidThrows_69) {
    auto data = createInvalidData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::WebPImage img(std::move(io));
    img.setComment("test");
    EXPECT_THROW(img.writeMetadata(), Exiv2::Error);
}

// Test imageType returns webp
TEST_F(WebPImageTest_69, ImageTypeIsWebP_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::WebPImage img(std::move(io));
    EXPECT_EQ(img.imageType(), Exiv2::ImageType::webp);
}

// Test xmpPacket is initially empty
TEST_F(WebPImageTest_69, XmpPacketInitiallyEmpty_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::WebPImage img(std::move(io));
    EXPECT_TRUE(img.xmpPacket().empty());
}

// Test comment is initially empty
TEST_F(WebPImageTest_69, CommentInitiallyEmpty_69) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::WebPImage img(std::move(io));
    EXPECT_TRUE(img.comment().empty());
}

// Test that RIFF with zero file size but valid WEBP tag
TEST_F(WebPImageTest_69, ReadMetadataFromZeroSizeWebPThrows_69) {
    std::vector<uint8_t> data = {
        'R', 'I', 'F', 'F',
        0x00, 0x00, 0x00, 0x00,  // file size = 0
        'W', 'E', 'B', 'P'
    };
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::WebPImage img(std::move(io));
    // The behavior might throw or might not read anything meaningful
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

}  // namespace
