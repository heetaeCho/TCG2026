#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/bmpimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>

#include <cstring>
#include <memory>
#include <sstream>

using namespace Exiv2;

// Helper to create a valid BMP header in memory
static std::vector<byte> createValidBmpData(uint32_t width, uint32_t height) {
    // Minimal BMP: 26 bytes needed for readMetadata to read width/height
    // Actually we need a full valid BMP header
    std::vector<byte> data(54, 0);
    
    // Signature: 'BM'
    data[0] = 'B';
    data[1] = 'M';
    
    // File size (little-endian) - minimal
    uint32_t fileSize = 54;
    std::memcpy(&data[2], &fileSize, 4);
    
    // Reserved
    data[6] = 0; data[7] = 0; data[8] = 0; data[9] = 0;
    
    // Bitmap offset
    uint32_t offset = 54;
    std::memcpy(&data[10], &offset, 4);
    
    // Header size (DIB header size = 40 for BITMAPINFOHEADER)
    uint32_t headerSize = 40;
    std::memcpy(&data[14], &headerSize, 4);
    
    // Width (little-endian)
    std::memcpy(&data[18], &width, 4);
    
    // Height (little-endian)
    std::memcpy(&data[22], &height, 4);
    
    // Planes
    uint16_t planes = 1;
    std::memcpy(&data[26], &planes, 2);
    
    // Bit depth
    uint16_t depth = 24;
    std::memcpy(&data[28], &depth, 2);
    
    // Compression = 0 (none)
    uint32_t compression = 0;
    std::memcpy(&data[30], &compression, 4);
    
    // Image size
    uint32_t imageSize = 0;
    std::memcpy(&data[34], &imageSize, 4);
    
    // Horizontal resolution
    uint32_t hRes = 2835;
    std::memcpy(&data[38], &hRes, 4);
    
    // Vertical resolution
    uint32_t vRes = 2835;
    std::memcpy(&data[42], &vRes, 4);
    
    // Color count
    uint32_t colorCount = 0;
    std::memcpy(&data[46], &colorCount, 4);
    
    // Important colors
    uint32_t importantColors = 0;
    std::memcpy(&data[50], &importantColors, 4);
    
    return data;
}

class BmpImageTest_1039 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    void TearDown() override {
    }
    
    std::unique_ptr<BmpImage> createBmpImageFromData(const std::vector<byte>& data) {
        auto io = std::make_unique<MemIo>(data.data(), data.size());
        return std::make_unique<BmpImage>(std::move(io));
    }
};

// Test: Valid BMP with specific dimensions reads correctly
TEST_F(BmpImageTest_1039, ReadMetadata_ValidBmp_ReadsWidthAndHeight_1039) {
    uint32_t expectedWidth = 640;
    uint32_t expectedHeight = 480;
    auto data = createValidBmpData(expectedWidth, expectedHeight);
    auto bmp = createBmpImageFromData(data);
    
    ASSERT_NO_THROW(bmp->readMetadata());
    EXPECT_EQ(bmp->pixelWidth(), expectedWidth);
    EXPECT_EQ(bmp->pixelHeight(), expectedHeight);
}

// Test: Valid BMP with zero dimensions
TEST_F(BmpImageTest_1039, ReadMetadata_ZeroDimensions_1039) {
    auto data = createValidBmpData(0, 0);
    auto bmp = createBmpImageFromData(data);
    
    ASSERT_NO_THROW(bmp->readMetadata());
    EXPECT_EQ(bmp->pixelWidth(), 0u);
    EXPECT_EQ(bmp->pixelHeight(), 0u);
}

// Test: Valid BMP with large dimensions
TEST_F(BmpImageTest_1039, ReadMetadata_LargeDimensions_1039) {
    uint32_t expectedWidth = 4096;
    uint32_t expectedHeight = 2160;
    auto data = createValidBmpData(expectedWidth, expectedHeight);
    auto bmp = createBmpImageFromData(data);
    
    ASSERT_NO_THROW(bmp->readMetadata());
    EXPECT_EQ(bmp->pixelWidth(), expectedWidth);
    EXPECT_EQ(bmp->pixelHeight(), expectedHeight);
}

// Test: Valid BMP with width = 1, height = 1
TEST_F(BmpImageTest_1039, ReadMetadata_MinimalDimensions_1039) {
    auto data = createValidBmpData(1, 1);
    auto bmp = createBmpImageFromData(data);
    
    ASSERT_NO_THROW(bmp->readMetadata());
    EXPECT_EQ(bmp->pixelWidth(), 1u);
    EXPECT_EQ(bmp->pixelHeight(), 1u);
}

// Test: Invalid BMP signature throws exception
TEST_F(BmpImageTest_1039, ReadMetadata_InvalidSignature_ThrowsError_1039) {
    auto data = createValidBmpData(100, 100);
    // Corrupt the signature
    data[0] = 'X';
    data[1] = 'Y';
    auto bmp = createBmpImageFromData(data);
    
    EXPECT_THROW(bmp->readMetadata(), Error);
}

// Test: Empty data throws exception
TEST_F(BmpImageTest_1039, ReadMetadata_EmptyData_ThrowsError_1039) {
    std::vector<byte> emptyData;
    auto io = std::make_unique<MemIo>();
    auto bmp = std::make_unique<BmpImage>(std::move(io));
    
    EXPECT_THROW(bmp->readMetadata(), Error);
}

// Test: Data too short (less than 26 bytes but valid signature)
TEST_F(BmpImageTest_1039, ReadMetadata_TruncatedHeader_1039) {
    // Only 2 bytes - just signature BM but nothing else meaningful
    // The isBmpType check needs at least the signature, but we also need enough
    // for the header check
    auto data = createValidBmpData(200, 300);
    // Truncate to just beyond the signature check but less than 26 bytes for read
    data.resize(20);
    auto bmp = createBmpImageFromData(data);
    
    // This should either throw or result in dimensions not being set
    // Depending on how isBmpType works, it may or may not throw
    try {
        bmp->readMetadata();
        // If it doesn't throw, width/height should be 0 since read didn't get enough bytes
        EXPECT_EQ(bmp->pixelWidth(), 0u);
        EXPECT_EQ(bmp->pixelHeight(), 0u);
    } catch (const Error&) {
        // Also acceptable
    }
}

// Test: MIME type returns correct value
TEST_F(BmpImageTest_1039, MimeType_ReturnsCorrectType_1039) {
    auto data = createValidBmpData(100, 100);
    auto bmp = createBmpImageFromData(data);
    
    EXPECT_EQ(bmp->mimeType(), "image/x-ms-bmp");
}

// Test: setExifData throws or is a no-op (BMP doesn't support EXIF)
TEST_F(BmpImageTest_1039, SetExifData_ThrowsOrNoOp_1039) {
    auto data = createValidBmpData(100, 100);
    auto bmp = createBmpImageFromData(data);
    
    ExifData exifData;
    // BMP doesn't support exif - setExifData should throw
    EXPECT_THROW(bmp->setExifData(exifData), Error);
}

// Test: setIptcData throws or is a no-op (BMP doesn't support IPTC)
TEST_F(BmpImageTest_1039, SetIptcData_ThrowsOrNoOp_1039) {
    auto data = createValidBmpData(100, 100);
    auto bmp = createBmpImageFromData(data);
    
    IptcData iptcData;
    EXPECT_THROW(bmp->setIptcData(iptcData), Error);
}

// Test: setComment throws or is a no-op (BMP doesn't support comments)
TEST_F(BmpImageTest_1039, SetComment_ThrowsOrNoOp_1039) {
    auto data = createValidBmpData(100, 100);
    auto bmp = createBmpImageFromData(data);
    
    EXPECT_THROW(bmp->setComment("test comment"), Error);
}

// Test: writeMetadata throws (BMP writing is not supported)
TEST_F(BmpImageTest_1039, WriteMetadata_ThrowsError_1039) {
    auto data = createValidBmpData(100, 100);
    auto bmp = createBmpImageFromData(data);
    
    EXPECT_THROW(bmp->writeMetadata(), Error);
}

// Test: Reading metadata clears previous metadata
TEST_F(BmpImageTest_1039, ReadMetadata_ClearsExistingMetadata_1039) {
    auto data = createValidBmpData(320, 240);
    auto bmp = createBmpImageFromData(data);
    
    ASSERT_NO_THROW(bmp->readMetadata());
    EXPECT_EQ(bmp->pixelWidth(), 320u);
    EXPECT_EQ(bmp->pixelHeight(), 240u);
    
    // Read again - should still work and give same results
    // Need to recreate because MemIo might be at end
    auto data2 = createValidBmpData(320, 240);
    auto bmp2 = createBmpImageFromData(data2);
    ASSERT_NO_THROW(bmp2->readMetadata());
    EXPECT_EQ(bmp2->pixelWidth(), 320u);
    EXPECT_EQ(bmp2->pixelHeight(), 240u);
}

// Test: BMP with max uint32 dimensions
TEST_F(BmpImageTest_1039, ReadMetadata_MaxDimensions_1039) {
    uint32_t maxVal = 0xFFFFFFFF;
    auto data = createValidBmpData(maxVal, maxVal);
    auto bmp = createBmpImageFromData(data);
    
    ASSERT_NO_THROW(bmp->readMetadata());
    EXPECT_EQ(bmp->pixelWidth(), maxVal);
    EXPECT_EQ(bmp->pixelHeight(), maxVal);
}

// Test: Verify good() after construction
TEST_F(BmpImageTest_1039, Good_AfterConstruction_1039) {
    auto data = createValidBmpData(100, 100);
    auto bmp = createBmpImageFromData(data);
    
    EXPECT_TRUE(bmp->good());
}

// Test: Single byte data (not valid BMP)
TEST_F(BmpImageTest_1039, ReadMetadata_SingleByte_ThrowsError_1039) {
    std::vector<byte> data = {0x42}; // Just 'B'
    auto bmp = createBmpImageFromData(data);
    
    EXPECT_THROW(bmp->readMetadata(), Error);
}

// Test: Two bytes 'BM' but nothing else
TEST_F(BmpImageTest_1039, ReadMetadata_OnlySignature_ThrowsOrHandles_1039) {
    std::vector<byte> data = {0x42, 0x4D}; // 'BM'
    auto bmp = createBmpImageFromData(data);
    
    // May throw or may just not set dimensions
    try {
        bmp->readMetadata();
        // If doesn't throw, dimensions should remain 0
        EXPECT_EQ(bmp->pixelWidth(), 0u);
        EXPECT_EQ(bmp->pixelHeight(), 0u);
    } catch (const Error&) {
        // Also acceptable - might fail isBmpType or read
    }
}

// Test: BMP with asymmetric dimensions
TEST_F(BmpImageTest_1039, ReadMetadata_AsymmetricDimensions_1039) {
    auto data = createValidBmpData(1920, 1);
    auto bmp = createBmpImageFromData(data);
    
    ASSERT_NO_THROW(bmp->readMetadata());
    EXPECT_EQ(bmp->pixelWidth(), 1920u);
    EXPECT_EQ(bmp->pixelHeight(), 1u);
}

// Test: Verify initial pixel dimensions are zero before readMetadata
TEST_F(BmpImageTest_1039, PixelDimensions_BeforeRead_AreZero_1039) {
    auto data = createValidBmpData(100, 200);
    auto bmp = createBmpImageFromData(data);
    
    EXPECT_EQ(bmp->pixelWidth(), 0u);
    EXPECT_EQ(bmp->pixelHeight(), 0u);
}

// Test: Corrupted data after valid signature
TEST_F(BmpImageTest_1039, ReadMetadata_CorruptedDataAfterSignature_1039) {
    auto data = createValidBmpData(100, 200);
    // Keep the signature but corrupt the rest - set header size to something weird
    // but keep enough bytes for the read to succeed
    data[14] = 0xFF;
    data[15] = 0xFF;
    data[16] = 0xFF;
    data[17] = 0xFF;
    
    auto bmp = createBmpImageFromData(data);
    
    // Should still read - the readMetadata doesn't validate header size,
    // it just reads width/height from fixed offsets
    try {
        bmp->readMetadata();
        // Width and height should still be read from offsets 18 and 22
        EXPECT_EQ(bmp->pixelWidth(), 100u);
        EXPECT_EQ(bmp->pixelHeight(), 200u);
    } catch (const Error&) {
        // Also acceptable if isBmpType validates more
    }
}
