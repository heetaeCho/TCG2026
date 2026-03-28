#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/webpimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>
#include <fstream>
#include <cstring>
#include <sstream>

namespace {

// Helper function to create a minimal valid WebP file in memory
std::vector<Exiv2::byte> createMinimalWebP(uint32_t fileSize = 20, const char* format = "VP8 ") {
    std::vector<Exiv2::byte> data;
    
    // RIFF header
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    
    // File size (little-endian, total size minus 8)
    uint32_t riffSize = fileSize - 8;
    data.push_back(static_cast<Exiv2::byte>(riffSize & 0xFF));
    data.push_back(static_cast<Exiv2::byte>((riffSize >> 8) & 0xFF));
    data.push_back(static_cast<Exiv2::byte>((riffSize >> 16) & 0xFF));
    data.push_back(static_cast<Exiv2::byte>((riffSize >> 24) & 0xFF));
    
    // WEBP signature
    data.push_back('W'); data.push_back('E'); data.push_back('B'); data.push_back('P');
    
    // VP8 chunk header
    data.push_back(format[0]); data.push_back(format[1]); data.push_back(format[2]); data.push_back(format[3]);
    
    // Chunk size (little-endian) - minimal
    uint32_t chunkSize = 10;
    data.push_back(static_cast<Exiv2::byte>(chunkSize & 0xFF));
    data.push_back(static_cast<Exiv2::byte>((chunkSize >> 8) & 0xFF));
    data.push_back(static_cast<Exiv2::byte>((chunkSize >> 16) & 0xFF));
    data.push_back(static_cast<Exiv2::byte>((chunkSize >> 24) & 0xFF));
    
    // VP8 bitstream header (minimal)
    // Frame tag: keyframe
    data.push_back(0x9D); data.push_back(0x01); data.push_back(0x2A);
    // Width and height (little-endian)
    uint16_t width = 1;
    uint16_t height = 1;
    data.push_back(static_cast<Exiv2::byte>(width & 0xFF));
    data.push_back(static_cast<Exiv2::byte>((width >> 8) & 0xFF));
    data.push_back(static_cast<Exiv2::byte>(height & 0xFF));
    data.push_back(static_cast<Exiv2::byte>((height >> 8) & 0xFF));
    
    // Pad to match sizes
    while (data.size() < fileSize) {
        data.push_back(0);
    }
    
    // Fix the RIFF size
    riffSize = static_cast<uint32_t>(data.size()) - 8;
    data[4] = static_cast<Exiv2::byte>(riffSize & 0xFF);
    data[5] = static_cast<Exiv2::byte>((riffSize >> 8) & 0xFF);
    data[6] = static_cast<Exiv2::byte>((riffSize >> 16) & 0xFF);
    data[7] = static_cast<Exiv2::byte>((riffSize >> 24) & 0xFF);
    
    // Fix chunk size
    chunkSize = static_cast<uint32_t>(data.size()) - 20;
    data[16] = static_cast<Exiv2::byte>(chunkSize & 0xFF);
    data[17] = static_cast<Exiv2::byte>((chunkSize >> 8) & 0xFF);
    data[18] = static_cast<Exiv2::byte>((chunkSize >> 16) & 0xFF);
    data[19] = static_cast<Exiv2::byte>((chunkSize >> 24) & 0xFF);
    
    return data;
}

// Helper to create a valid VP8L WebP
std::vector<Exiv2::byte> createMinimalWebPLossless() {
    std::vector<Exiv2::byte> data;
    
    // RIFF header
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    // placeholder for size
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    
    // WEBP
    data.push_back('W'); data.push_back('E'); data.push_back('B'); data.push_back('P');
    
    // VP8L chunk
    data.push_back('V'); data.push_back('P'); data.push_back('8'); data.push_back('L');
    
    // chunk size placeholder
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    
    // VP8L signature byte
    data.push_back(0x2F);
    
    // Encoded width-1 (14 bits) and height-1 (14 bits) and alpha (1 bit) and version (3 bits)
    // width=1 (0), height=1 (0), no alpha, version 0
    uint32_t bits = 0; // width-1=0, height-1=0, alpha=0, version=0
    data.push_back(static_cast<Exiv2::byte>(bits & 0xFF));
    data.push_back(static_cast<Exiv2::byte>((bits >> 8) & 0xFF));
    data.push_back(static_cast<Exiv2::byte>((bits >> 16) & 0xFF));
    data.push_back(static_cast<Exiv2::byte>((bits >> 24) & 0xFF));
    
    // Pad
    for (int i = 0; i < 5; i++) data.push_back(0);
    
    // Fix sizes
    uint32_t riffSize = static_cast<uint32_t>(data.size()) - 8;
    data[4] = static_cast<Exiv2::byte>(riffSize & 0xFF);
    data[5] = static_cast<Exiv2::byte>((riffSize >> 8) & 0xFF);
    data[6] = static_cast<Exiv2::byte>((riffSize >> 16) & 0xFF);
    data[7] = static_cast<Exiv2::byte>((riffSize >> 24) & 0xFF);
    
    uint32_t chunkSize = static_cast<uint32_t>(data.size()) - 20;
    data[16] = static_cast<Exiv2::byte>(chunkSize & 0xFF);
    data[17] = static_cast<Exiv2::byte>((chunkSize >> 8) & 0xFF);
    data[18] = static_cast<Exiv2::byte>((chunkSize >> 16) & 0xFF);
    data[19] = static_cast<Exiv2::byte>((chunkSize >> 24) & 0xFF);
    
    return data;
}

// Helper to create WebP with VP8X extended format
std::vector<Exiv2::byte> createWebPWithVP8X(bool hasExif = false, bool hasXmp = false, bool hasIcc = false) {
    std::vector<Exiv2::byte> data;
    
    // RIFF header
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    
    // WEBP
    data.push_back('W'); data.push_back('E'); data.push_back('B'); data.push_back('P');
    
    // VP8X chunk
    data.push_back('V'); data.push_back('P'); data.push_back('8'); data.push_back('X');
    
    // VP8X payload size = 10
    uint32_t vp8xSize = 10;
    data.push_back(static_cast<Exiv2::byte>(vp8xSize & 0xFF));
    data.push_back(static_cast<Exiv2::byte>((vp8xSize >> 8) & 0xFF));
    data.push_back(static_cast<Exiv2::byte>((vp8xSize >> 16) & 0xFF));
    data.push_back(static_cast<Exiv2::byte>((vp8xSize >> 24) & 0xFF));
    
    // Flags byte
    Exiv2::byte flags = 0;
    if (hasIcc) flags |= 0x20;
    if (hasExif) flags |= 0x08;
    if (hasXmp) flags |= 0x04;
    data.push_back(flags);
    
    // Reserved 3 bytes
    data.push_back(0); data.push_back(0); data.push_back(0);
    
    // Canvas width - 1 (24 bits, little-endian)
    data.push_back(0); data.push_back(0); data.push_back(0);
    
    // Canvas height - 1 (24 bits, little-endian)
    data.push_back(0); data.push_back(0); data.push_back(0);
    
    // VP8 chunk (minimal image data)
    data.push_back('V'); data.push_back('P'); data.push_back('8'); data.push_back(' ');
    uint32_t vp8Size = 10;
    data.push_back(static_cast<Exiv2::byte>(vp8Size & 0xFF));
    data.push_back(static_cast<Exiv2::byte>((vp8Size >> 8) & 0xFF));
    data.push_back(static_cast<Exiv2::byte>((vp8Size >> 16) & 0xFF));
    data.push_back(static_cast<Exiv2::byte>((vp8Size >> 24) & 0xFF));
    
    data.push_back(0x9D); data.push_back(0x01); data.push_back(0x2A);
    data.push_back(0x01); data.push_back(0x00);
    data.push_back(0x01); data.push_back(0x00);
    data.push_back(0); data.push_back(0); data.push_back(0);
    
    // Fix RIFF size
    uint32_t riffSize = static_cast<uint32_t>(data.size()) - 8;
    data[4] = static_cast<Exiv2::byte>(riffSize & 0xFF);
    data[5] = static_cast<Exiv2::byte>((riffSize >> 8) & 0xFF);
    data[6] = static_cast<Exiv2::byte>((riffSize >> 16) & 0xFF);
    data[7] = static_cast<Exiv2::byte>((riffSize >> 24) & 0xFF);
    
    return data;
}

class WebPImageTest_68 : public ::testing::Test {
protected:
    std::unique_ptr<Exiv2::WebPImage> createWebPImageFromData(const std::vector<Exiv2::byte>& data) {
        auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
        return std::make_unique<Exiv2::WebPImage>(std::move(io));
    }
};

// Test: mimeType returns correct MIME type for WebP
TEST_F(WebPImageTest_68, MimeTypeReturnsImageWebP_68) {
    auto data = createMinimalWebP(30);
    auto image = createWebPImageFromData(data);
    EXPECT_EQ("image/webp", image->mimeType());
}

// Test: Constructor with valid WebP data does not throw
TEST_F(WebPImageTest_68, ConstructorWithValidDataDoesNotThrow_68) {
    auto data = createMinimalWebP(30);
    EXPECT_NO_THROW({
        auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
        Exiv2::WebPImage image(std::move(io));
    });
}

// Test: Constructor with invalid data (not a RIFF/WEBP file) throws
TEST_F(WebPImageTest_68, ConstructorWithInvalidDataThrows_68) {
    std::vector<Exiv2::byte> invalidData(30, 0);
    EXPECT_THROW({
        auto io = std::make_unique<Exiv2::MemIo>(invalidData.data(), invalidData.size());
        Exiv2::WebPImage image(std::move(io));
    }, Exiv2::Error);
}

// Test: Constructor with empty data throws
TEST_F(WebPImageTest_68, ConstructorWithEmptyDataThrows_68) {
    EXPECT_THROW({
        auto io = std::make_unique<Exiv2::MemIo>();
        Exiv2::WebPImage image(std::move(io));
    }, Exiv2::Error);
}

// Test: Constructor with too-short data throws
TEST_F(WebPImageTest_68, ConstructorWithTooShortDataThrows_68) {
    std::vector<Exiv2::byte> shortData = {'R', 'I', 'F', 'F'};
    EXPECT_THROW({
        auto io = std::make_unique<Exiv2::MemIo>(shortData.data(), shortData.size());
        Exiv2::WebPImage image(std::move(io));
    }, Exiv2::Error);
}

// Test: Constructor with RIFF header but wrong format (not WEBP) throws
TEST_F(WebPImageTest_68, ConstructorWithRiffButNotWebPThrows_68) {
    std::vector<Exiv2::byte> data = {
        'R', 'I', 'F', 'F',
        0x14, 0x00, 0x00, 0x00,  // size
        'A', 'V', 'I', ' ',      // Not WEBP
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0
    };
    EXPECT_THROW({
        auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
        Exiv2::WebPImage image(std::move(io));
    }, Exiv2::Error);
}

// Test: readMetadata on a minimal VP8 WebP file
TEST_F(WebPImageTest_68, ReadMetadataOnMinimalVP8_68) {
    auto data = createMinimalWebP(30);
    auto image = createWebPImageFromData(data);
    EXPECT_NO_THROW(image->readMetadata());
}

// Test: setComment is a no-op (does not throw)
TEST_F(WebPImageTest_68, SetCommentDoesNotThrow_68) {
    auto data = createMinimalWebP(30);
    auto image = createWebPImageFromData(data);
    EXPECT_NO_THROW(image->setComment("test comment"));
}

// Test: setIptcData is a no-op (does not throw or may throw)
TEST_F(WebPImageTest_68, SetIptcDataBehavior_68) {
    auto data = createMinimalWebP(30);
    auto image = createWebPImageFromData(data);
    Exiv2::IptcData iptcData;
    // setIptcData for WebP may throw since IPTC is not supported
    // We just verify it doesn't crash unexpectedly
    try {
        image->setIptcData(iptcData);
    } catch (const Exiv2::Error&) {
        // Expected - WebP doesn't support IPTC
    }
}

// Test: writeMetadata on minimal file
TEST_F(WebPImageTest_68, WriteMetadataOnMinimalFile_68) {
    auto data = createMinimalWebP(30);
    auto image = createWebPImageFromData(data);
    image->readMetadata();
    // writeMetadata should work on a valid file
    EXPECT_NO_THROW(image->writeMetadata());
}

// Test: mimeType is consistent across multiple calls
TEST_F(WebPImageTest_68, MimeTypeConsistentAcrossMultipleCalls_68) {
    auto data = createMinimalWebP(30);
    auto image = createWebPImageFromData(data);
    EXPECT_EQ(image->mimeType(), image->mimeType());
    EXPECT_EQ("image/webp", image->mimeType());
}

// Test: printStructure with kpsNone option
TEST_F(WebPImageTest_68, PrintStructureKpsNone_68) {
    auto data = createMinimalWebP(30);
    auto image = createWebPImageFromData(data);
    std::ostringstream oss;
    EXPECT_NO_THROW(image->printStructure(oss, Exiv2::kpsNone, 0));
}

// Test: readMetadata with VP8X extended format
TEST_F(WebPImageTest_68, ReadMetadataWithVP8X_68) {
    auto data = createWebPWithVP8X(false, false, false);
    auto image = createWebPImageFromData(data);
    EXPECT_NO_THROW(image->readMetadata());
}

// Test: After readMetadata, exifData and xmpData are accessible
TEST_F(WebPImageTest_68, MetadataAccessibleAfterRead_68) {
    auto data = createMinimalWebP(30);
    auto image = createWebPImageFromData(data);
    image->readMetadata();
    
    // For a minimal WebP without metadata, these should be empty
    EXPECT_TRUE(image->exifData().empty());
    EXPECT_TRUE(image->xmpData().empty());
}

// Test: WebP image with VP8X format - no EXIF
TEST_F(WebPImageTest_68, VP8XNoExifMetadata_68) {
    auto data = createWebPWithVP8X(false, false, false);
    auto image = createWebPImageFromData(data);
    image->readMetadata();
    EXPECT_TRUE(image->exifData().empty());
}

// Test: printStructure with kpsBasic option
TEST_F(WebPImageTest_68, PrintStructureKpsBasic_68) {
    auto data = createMinimalWebP(30);
    auto image = createWebPImageFromData(data);
    std::ostringstream oss;
    // kpsBasic may or may not produce output, but should not crash
    try {
        image->printStructure(oss, Exiv2::kpsBasic, 0);
    } catch (const Exiv2::Error&) {
        // Some options might not be supported
    }
}

// Test: Multiple readMetadata calls on same image
TEST_F(WebPImageTest_68, MultipleReadMetadataCalls_68) {
    auto data = createMinimalWebP(30);
    auto image = createWebPImageFromData(data);
    EXPECT_NO_THROW(image->readMetadata());
    EXPECT_NO_THROW(image->readMetadata());
}

// Test: setComment with empty string
TEST_F(WebPImageTest_68, SetCommentEmptyString_68) {
    auto data = createMinimalWebP(30);
    auto image = createWebPImageFromData(data);
    EXPECT_NO_THROW(image->setComment(""));
}

// Test: setComment with very long string
TEST_F(WebPImageTest_68, SetCommentLongString_68) {
    auto data = createMinimalWebP(30);
    auto image = createWebPImageFromData(data);
    std::string longComment(10000, 'A');
    EXPECT_NO_THROW(image->setComment(longComment));
}

// Test: VP8L (lossless) format
TEST_F(WebPImageTest_68, ReadMetadataVP8LFormat_68) {
    auto data = createMinimalWebPLossless();
    auto image = createWebPImageFromData(data);
    EXPECT_NO_THROW(image->readMetadata());
}

// Test: writeMetadata after setting comment
TEST_F(WebPImageTest_68, WriteMetadataAfterSetComment_68) {
    auto data = createMinimalWebP(30);
    auto image = createWebPImageFromData(data);
    image->readMetadata();
    image->setComment("test");
    EXPECT_NO_THROW(image->writeMetadata());
}

} // namespace
