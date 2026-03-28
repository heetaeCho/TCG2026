#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/rafimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>
#include <exiv2/image.hpp>
#include <memory>
#include <cstring>
#include <vector>
#include <fstream>

using namespace Exiv2;

// Helper to create a minimal RAF file header
// RAF files start with "FUJIFILMCCD-RAW " (16 bytes magic)
static std::vector<byte> createMinimalRafHeader() {
    // RAF magic: "FUJIFILMCCD-RAW " (16 bytes)
    // Then various header fields up to at least offset 108
    // Offset 84: jpg_img_offset (4 bytes, big-endian)
    // Offset 88: jpg_img_length (4 bytes, big-endian)
    // Offset 100: tiff_offset (4 bytes, big-endian)
    // Offset 104: tiff_length (4 bytes, big-endian)
    
    const size_t headerSize = 256;
    const size_t jpgDataOffset = 200;
    
    // Minimal JPEG: need at least 12 bytes
    // Create a minimal JPEG with SOI and EOI markers
    std::vector<byte> jpgData = {
        0xFF, 0xD8, // SOI
        0xFF, 0xE1, // APP1 marker
        0x00, 0x02, // length 2 (just the length field)
        0xFF, 0xD9, // EOI
        0x00, 0x00, 0x00, 0x00 // padding to make >= 12
    };
    
    size_t totalSize = jpgDataOffset + jpgData.size() + 16; // extra for safety
    std::vector<byte> data(totalSize, 0);
    
    // Write RAF magic
    const char* magic = "FUJIFILMCCD-RAW ";
    std::memcpy(data.data(), magic, 16);
    
    // Fill rest of header with zeros (format version, etc.)
    // Offset 84: jpg_img_offset (big-endian)
    uint32_t jpgOffset = static_cast<uint32_t>(jpgDataOffset);
    data[84] = (jpgOffset >> 24) & 0xFF;
    data[85] = (jpgOffset >> 16) & 0xFF;
    data[86] = (jpgOffset >> 8) & 0xFF;
    data[87] = jpgOffset & 0xFF;
    
    // Offset 88: jpg_img_length (big-endian)
    uint32_t jpgLen = static_cast<uint32_t>(jpgData.size());
    data[88] = (jpgLen >> 24) & 0xFF;
    data[89] = (jpgLen >> 16) & 0xFF;
    data[90] = (jpgLen >> 8) & 0xFF;
    data[91] = jpgLen & 0xFF;
    
    // Offset 100: tiff_offset (big-endian) - point to end area with no valid TIFF
    uint32_t tiffOffset = static_cast<uint32_t>(jpgDataOffset + jpgData.size());
    data[100] = (tiffOffset >> 24) & 0xFF;
    data[101] = (tiffOffset >> 16) & 0xFF;
    data[102] = (tiffOffset >> 8) & 0xFF;
    data[103] = tiffOffset & 0xFF;
    
    // Offset 104: tiff_length (big-endian) - 8 bytes
    uint32_t tiffLen = 8;
    data[104] = (tiffLen >> 24) & 0xFF;
    data[105] = (tiffLen >> 16) & 0xFF;
    data[106] = (tiffLen >> 8) & 0xFF;
    data[107] = tiffLen & 0xFF;
    
    // Write jpg data
    std::memcpy(data.data() + jpgDataOffset, jpgData.data(), jpgData.size());
    
    // Make sure total size is enough
    data.resize(tiffOffset + tiffLen, 0);
    
    return data;
}

class RafImageTest_221 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    void TearDown() override {
    }
    
    std::unique_ptr<RafImage> createRafImageFromData(const std::vector<byte>& data) {
        auto io = std::make_unique<MemIo>(data.data(), data.size());
        return std::make_unique<RafImage>(std::move(io), false);
    }
    
    std::unique_ptr<RafImage> createRafImageFromEmptyMemIo() {
        auto io = std::make_unique<MemIo>();
        return std::make_unique<RafImage>(std::move(io), false);
    }
};

// Test that reading metadata from an empty buffer throws
TEST_F(RafImageTest_221, ReadMetadataEmptyBuffer_221) {
    auto img = createRafImageFromEmptyMemIo();
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test that reading metadata from non-RAF data throws kerNotAnImage
TEST_F(RafImageTest_221, ReadMetadataNotRafFile_221) {
    std::vector<byte> notRaf(200, 0x00);
    auto img = createRafImageFromData(notRaf);
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test that reading metadata from data with only the RAF magic but truncated throws
TEST_F(RafImageTest_221, ReadMetadataTruncatedAfterMagic_221) {
    const char* magic = "FUJIFILMCCD-RAW ";
    std::vector<byte> data(magic, magic + 16);
    auto img = createRafImageFromData(data);
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test that a minimal valid RAF header with too short jpg length throws
TEST_F(RafImageTest_221, ReadMetadataJpgLengthTooShort_221) {
    // Create a RAF with jpg_img_length < 12
    std::vector<byte> data(256, 0);
    const char* magic = "FUJIFILMCCD-RAW ";
    std::memcpy(data.data(), magic, 16);
    
    // jpg offset at 84, pointing to 200
    uint32_t jpgOffset = 200;
    data[84] = (jpgOffset >> 24) & 0xFF;
    data[85] = (jpgOffset >> 16) & 0xFF;
    data[86] = (jpgOffset >> 8) & 0xFF;
    data[87] = jpgOffset & 0xFF;
    
    // jpg length = 8 (< 12, should fail)
    uint32_t jpgLen = 8;
    data[88] = (jpgLen >> 24) & 0xFF;
    data[89] = (jpgLen >> 16) & 0xFF;
    data[90] = (jpgLen >> 8) & 0xFF;
    data[91] = jpgLen & 0xFF;
    
    auto img = createRafImageFromData(data);
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test that jpg offset + length exceeding file size throws
TEST_F(RafImageTest_221, ReadMetadataJpgOffsetLengthExceedsSize_221) {
    std::vector<byte> data(128, 0);
    const char* magic = "FUJIFILMCCD-RAW ";
    std::memcpy(data.data(), magic, 16);
    
    // jpg offset pointing beyond file
    uint32_t jpgOffset = 1000;
    data[84] = (jpgOffset >> 24) & 0xFF;
    data[85] = (jpgOffset >> 16) & 0xFF;
    data[86] = (jpgOffset >> 8) & 0xFF;
    data[87] = jpgOffset & 0xFF;
    
    uint32_t jpgLen = 100;
    data[88] = (jpgLen >> 24) & 0xFF;
    data[89] = (jpgLen >> 16) & 0xFF;
    data[90] = (jpgLen >> 8) & 0xFF;
    data[91] = jpgLen & 0xFF;
    
    auto img = createRafImageFromData(data);
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test that RAF header truncated at offset 84 (can't read jpg_img_offset) throws
TEST_F(RafImageTest_221, ReadMetadataTruncatedAtJpgOffset_221) {
    std::vector<byte> data(86, 0);  // Not enough for full 4-byte read at offset 84
    const char* magic = "FUJIFILMCCD-RAW ";
    std::memcpy(data.data(), magic, 16);
    
    auto img = createRafImageFromData(data);
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test mimeType returns "image/x-fuji-raf"
TEST_F(RafImageTest_221, MimeTypeReturnsCorrectValue_221) {
    auto img = createRafImageFromEmptyMemIo();
    EXPECT_EQ(img->mimeType(), "image/x-fuji-raf");
}

// Test that setExifData does not throw (but may be no-op)
TEST_F(RafImageTest_221, SetExifDataNoThrow_221) {
    auto img = createRafImageFromEmptyMemIo();
    ExifData exifData;
    EXPECT_NO_THROW(img->setExifData(exifData));
}

// Test that setIptcData does not throw (but may be no-op)
TEST_F(RafImageTest_221, SetIptcDataNoThrow_221) {
    auto img = createRafImageFromEmptyMemIo();
    IptcData iptcData;
    EXPECT_NO_THROW(img->setIptcData(iptcData));
}

// Test that setComment does not throw (but may be no-op)
TEST_F(RafImageTest_221, SetCommentNoThrow_221) {
    auto img = createRafImageFromEmptyMemIo();
    EXPECT_NO_THROW(img->setComment("test comment"));
}

// Test pixelWidth returns 0 before metadata is read
TEST_F(RafImageTest_221, PixelWidthDefaultZero_221) {
    auto img = createRafImageFromEmptyMemIo();
    EXPECT_EQ(img->pixelWidth(), 0u);
}

// Test pixelHeight returns 0 before metadata is read
TEST_F(RafImageTest_221, PixelHeightDefaultZero_221) {
    auto img = createRafImageFromEmptyMemIo();
    EXPECT_EQ(img->pixelHeight(), 0u);
}

// Test construction with create=true
TEST_F(RafImageTest_221, ConstructionWithCreateTrue_221) {
    auto io = std::make_unique<MemIo>();
    EXPECT_NO_THROW(RafImage(std::move(io), true));
}

// Test construction with create=false
TEST_F(RafImageTest_221, ConstructionWithCreateFalse_221) {
    auto io = std::make_unique<MemIo>();
    EXPECT_NO_THROW(RafImage(std::move(io), false));
}

// Test that good() returns true for a valid MemIo
TEST_F(RafImageTest_221, GoodReturnsTrueForMemIo_221) {
    auto img = createRafImageFromEmptyMemIo();
    EXPECT_TRUE(img->good());
}

// Test readMetadata with data that has RAF header but truncated before tiff offset fields
TEST_F(RafImageTest_221, ReadMetadataTruncatedBeforeTiffOffset_221) {
    // Build a RAF with valid jpg section but truncated at offset 100
    std::vector<byte> data(104, 0);
    const char* magic = "FUJIFILMCCD-RAW ";
    std::memcpy(data.data(), magic, 16);
    
    // jpg offset = 92, length = 12 (minimum)
    uint32_t jpgOffset = 92;
    data[84] = (jpgOffset >> 24) & 0xFF;
    data[85] = (jpgOffset >> 16) & 0xFF;
    data[86] = (jpgOffset >> 8) & 0xFF;
    data[87] = jpgOffset & 0xFF;
    
    uint32_t jpgLen = 12;
    data[88] = (jpgLen >> 24) & 0xFF;
    data[89] = (jpgLen >> 16) & 0xFF;
    data[90] = (jpgLen >> 8) & 0xFF;
    data[91] = jpgLen & 0xFF;
    
    auto img = createRafImageFromData(data);
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test that data with random bytes after magic fails
TEST_F(RafImageTest_221, ReadMetadataRandomDataAfterMagic_221) {
    std::vector<byte> data(32, 0xFF);
    const char* magic = "FUJIFILMCCD-RAW ";
    std::memcpy(data.data(), magic, 16);
    
    auto img = createRafImageFromData(data);
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test writeMetadata on an empty MemIo throws
TEST_F(RafImageTest_221, WriteMetadataEmptyThrows_221) {
    auto img = createRafImageFromEmptyMemIo();
    EXPECT_THROW(img->writeMetadata(), Exiv2::Error);
}

// Test that exifData() returns empty data before readMetadata
TEST_F(RafImageTest_221, ExifDataEmptyBeforeRead_221) {
    auto img = createRafImageFromEmptyMemIo();
    EXPECT_TRUE(img->exifData().empty());
}

// Test that iptcData() returns empty data before readMetadata
TEST_F(RafImageTest_221, IptcDataEmptyBeforeRead_221) {
    auto img = createRafImageFromEmptyMemIo();
    EXPECT_TRUE(img->iptcData().empty());
}

// Test that xmpData() returns empty data before readMetadata
TEST_F(RafImageTest_221, XmpDataEmptyBeforeRead_221) {
    auto img = createRafImageFromEmptyMemIo();
    EXPECT_TRUE(img->xmpData().empty());
}

// Test that tiff offset + length exceeding file size throws corrupted metadata
TEST_F(RafImageTest_221, ReadMetadataTiffOffsetExceedsSize_221) {
    // Build valid RAF header with valid jpg, but tiff offset+length > size
    size_t jpgDataOffset = 200;
    size_t jpgDataLen = 12;
    
    std::vector<byte> data(jpgDataOffset + jpgDataLen + 8, 0);
    const char* magic = "FUJIFILMCCD-RAW ";
    std::memcpy(data.data(), magic, 16);
    
    // jpg offset
    data[84] = (jpgDataOffset >> 24) & 0xFF;
    data[85] = (jpgDataOffset >> 16) & 0xFF;
    data[86] = (jpgDataOffset >> 8) & 0xFF;
    data[87] = jpgDataOffset & 0xFF;
    
    // jpg length
    data[88] = (jpgDataLen >> 24) & 0xFF;
    data[89] = (jpgDataLen >> 16) & 0xFF;
    data[90] = (jpgDataLen >> 8) & 0xFF;
    data[91] = jpgDataLen & 0xFF;
    
    // tiff offset = 9999 (way beyond file size)
    uint32_t tiffOff = 9999;
    data[100] = (tiffOff >> 24) & 0xFF;
    data[101] = (tiffOff >> 16) & 0xFF;
    data[102] = (tiffOff >> 8) & 0xFF;
    data[103] = tiffOff & 0xFF;
    
    // tiff length = 100
    uint32_t tiffLen = 100;
    data[104] = (tiffLen >> 24) & 0xFF;
    data[105] = (tiffLen >> 16) & 0xFF;
    data[106] = (tiffLen >> 8) & 0xFF;
    data[107] = tiffLen & 0xFF;
    
    auto img = createRafImageFromData(data);
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test that comment is empty before readMetadata
TEST_F(RafImageTest_221, CommentEmptyBeforeRead_221) {
    auto img = createRafImageFromEmptyMemIo();
    EXPECT_TRUE(img->comment().empty());
}

// Test clearMetadata works without crashing
TEST_F(RafImageTest_221, ClearMetadataNoThrow_221) {
    auto img = createRafImageFromEmptyMemIo();
    EXPECT_NO_THROW(img->clearMetadata());
}
