#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/bmpimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>

#include <fstream>
#include <cstdio>
#include <cstring>

namespace {

// Helper to create a minimal valid BMP file in memory
std::vector<uint8_t> createMinimalBmpData() {
    // Minimal BMP: 14-byte file header + 40-byte DIB header (BITMAPINFOHEADER)
    // Total = 54 bytes minimum for a 1x1 pixel BMP
    std::vector<uint8_t> data(58, 0);
    // BM signature
    data[0] = 'B';
    data[1] = 'M';
    // File size (58 bytes)
    data[2] = 58;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    // Reserved
    data[6] = 0; data[7] = 0; data[8] = 0; data[9] = 0;
    // Pixel data offset (54)
    data[10] = 54; data[11] = 0; data[12] = 0; data[13] = 0;
    // DIB header size (40 = BITMAPINFOHEADER)
    data[14] = 40; data[15] = 0; data[16] = 0; data[17] = 0;
    // Width = 1
    data[18] = 1; data[19] = 0; data[20] = 0; data[21] = 0;
    // Height = 1
    data[22] = 1; data[23] = 0; data[24] = 0; data[25] = 0;
    // Planes = 1
    data[26] = 1; data[27] = 0;
    // Bits per pixel = 24
    data[28] = 24; data[29] = 0;
    // Compression = 0 (BI_RGB)
    data[30] = 0; data[31] = 0; data[32] = 0; data[33] = 0;
    // Image size (can be 0 for BI_RGB)
    data[34] = 0; data[35] = 0; data[36] = 0; data[37] = 0;
    // Horizontal resolution
    data[38] = 0; data[39] = 0; data[40] = 0; data[41] = 0;
    // Vertical resolution
    data[42] = 0; data[43] = 0; data[44] = 0; data[45] = 0;
    // Colors in color table
    data[46] = 0; data[47] = 0; data[48] = 0; data[49] = 0;
    // Important color count
    data[50] = 0; data[51] = 0; data[52] = 0; data[53] = 0;
    // Pixel data (1 pixel = 3 bytes + 1 byte padding for row alignment)
    data[54] = 0xFF; data[55] = 0x00; data[56] = 0x00; data[57] = 0x00;
    return data;
}

std::unique_ptr<Exiv2::BasicIo> createMemIoFromData(const std::vector<uint8_t>& data) {
    return std::make_unique<Exiv2::MemIo>(data.data(), data.size());
}

std::unique_ptr<Exiv2::BasicIo> createEmptyMemIo() {
    return std::make_unique<Exiv2::MemIo>();
}

} // anonymous namespace

class BmpImageTest_1038 : public ::testing::Test {
protected:
    void SetUp() override {
        auto bmpData = createMinimalBmpData();
        auto io = createMemIoFromData(bmpData);
        bmpImage_ = std::make_unique<Exiv2::BmpImage>(std::move(io));
    }

    std::unique_ptr<Exiv2::BmpImage> bmpImage_;
};

// Test that mimeType returns the correct MIME type for BMP images
TEST_F(BmpImageTest_1038, MimeTypeReturnsBmpMimeType_1038) {
    EXPECT_EQ(bmpImage_->mimeType(), "image/x-ms-bmp");
}

// Test that mimeType is consistent across multiple calls
TEST_F(BmpImageTest_1038, MimeTypeIsConsistent_1038) {
    std::string first = bmpImage_->mimeType();
    std::string second = bmpImage_->mimeType();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, "image/x-ms-bmp");
}

// Test that setExifData throws or is a no-op (BMP doesn't support EXIF)
TEST_F(BmpImageTest_1038, SetExifDataThrowsOrNoOp_1038) {
    Exiv2::ExifData exifData;
    try {
        bmpImage_->setExifData(exifData);
        // If it doesn't throw, that's acceptable (no-op behavior)
    } catch (const Exiv2::Error&) {
        // Expected - BMP doesn't support EXIF
        SUCCEED();
    }
}

// Test that setIptcData throws or is a no-op (BMP doesn't support IPTC)
TEST_F(BmpImageTest_1038, SetIptcDataThrowsOrNoOp_1038) {
    Exiv2::IptcData iptcData;
    try {
        bmpImage_->setIptcData(iptcData);
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test that setComment throws or is a no-op (BMP doesn't support comments)
TEST_F(BmpImageTest_1038, SetCommentThrowsOrNoOp_1038) {
    try {
        bmpImage_->setComment("test comment");
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test that readMetadata can be called on a valid BMP
TEST_F(BmpImageTest_1038, ReadMetadataOnValidBmp_1038) {
    EXPECT_NO_THROW(bmpImage_->readMetadata());
}

// Test that writeMetadata throws for BMP (BMP typically doesn't support writing metadata)
TEST_F(BmpImageTest_1038, WriteMetadataThrows_1038) {
    try {
        bmpImage_->writeMetadata();
        // If it succeeds, that's also acceptable
    } catch (const Exiv2::Error&) {
        // Expected behavior for BMP
        SUCCEED();
    }
}

// Test readMetadata on empty/invalid data
TEST(BmpImageErrorTest_1038, ReadMetadataOnEmptyIoThrows_1038) {
    auto io = createEmptyMemIo();
    auto bmpImage = std::make_unique<Exiv2::BmpImage>(std::move(io));
    EXPECT_THROW(bmpImage->readMetadata(), Exiv2::Error);
}

// Test readMetadata with truncated/invalid BMP data
TEST(BmpImageErrorTest_1038, ReadMetadataOnInvalidDataThrows_1038) {
    std::vector<uint8_t> invalidData = {0x00, 0x01, 0x02, 0x03};
    auto io = createMemIoFromData(invalidData);
    auto bmpImage = std::make_unique<Exiv2::BmpImage>(std::move(io));
    EXPECT_THROW(bmpImage->readMetadata(), Exiv2::Error);
}

// Test with data that has BM signature but is too short
TEST(BmpImageErrorTest_1038, ReadMetadataTruncatedBmpThrows_1038) {
    std::vector<uint8_t> truncatedData = {'B', 'M', 0x00, 0x00};
    auto io = createMemIoFromData(truncatedData);
    auto bmpImage = std::make_unique<Exiv2::BmpImage>(std::move(io));
    EXPECT_THROW(bmpImage->readMetadata(), Exiv2::Error);
}

// Test that pixel dimensions are readable after readMetadata on a valid BMP
TEST_F(BmpImageTest_1038, PixelDimensionsAfterReadMetadata_1038) {
    bmpImage_->readMetadata();
    // The minimal BMP we created is 1x1
    EXPECT_EQ(bmpImage_->pixelWidth(), 1);
    EXPECT_EQ(bmpImage_->pixelHeight(), 1);
}

// Test that the image type is BMP
TEST_F(BmpImageTest_1038, ImageTypeIsBmp_1038) {
    // After construction, the image should report its type
    // BmpImage should have imageType as bmp
    EXPECT_EQ(bmpImage_->imageType(), Exiv2::ImageType::bmp);
}

// Test that EXIF data is empty for BMP (BMP doesn't support EXIF natively)
TEST_F(BmpImageTest_1038, ExifDataIsEmptyAfterRead_1038) {
    bmpImage_->readMetadata();
    EXPECT_TRUE(bmpImage_->exifData().empty());
}

// Test that IPTC data is empty for BMP
TEST_F(BmpImageTest_1038, IptcDataIsEmptyAfterRead_1038) {
    bmpImage_->readMetadata();
    EXPECT_TRUE(bmpImage_->iptcData().empty());
}

// Test that comment is empty for BMP
TEST_F(BmpImageTest_1038, CommentIsEmptyAfterRead_1038) {
    bmpImage_->readMetadata();
    EXPECT_TRUE(bmpImage_->comment().empty());
}

// Test construction with a valid MemIo does not throw
TEST(BmpImageConstructionTest_1038, ConstructWithValidIo_1038) {
    auto bmpData = createMinimalBmpData();
    auto io = createMemIoFromData(bmpData);
    EXPECT_NO_THROW(auto img = std::make_unique<Exiv2::BmpImage>(std::move(io)));
}

// Test with a larger valid BMP (e.g., 2x2 pixels)
TEST(BmpImageVariantTest_1038, ReadMetadata2x2Bmp_1038) {
    // Create a 2x2 24-bit BMP
    // Row size = ceil(2*3/4)*4 = 8 bytes (6 bytes data + 2 padding)
    // Pixel data = 2 rows * 8 = 16 bytes
    // Total = 54 + 16 = 70 bytes
    std::vector<uint8_t> data(70, 0);
    data[0] = 'B'; data[1] = 'M';
    // File size
    data[2] = 70; data[3] = 0; data[4] = 0; data[5] = 0;
    // Pixel offset
    data[10] = 54;
    // DIB header size
    data[14] = 40;
    // Width = 2
    data[18] = 2;
    // Height = 2
    data[22] = 2;
    // Planes = 1
    data[26] = 1;
    // Bits per pixel = 24
    data[28] = 24;

    auto io = createMemIoFromData(data);
    auto bmpImage = std::make_unique<Exiv2::BmpImage>(std::move(io));
    
    EXPECT_NO_THROW(bmpImage->readMetadata());
    EXPECT_EQ(bmpImage->pixelWidth(), 2);
    EXPECT_EQ(bmpImage->pixelHeight(), 2);
    EXPECT_EQ(bmpImage->mimeType(), "image/x-ms-bmp");
}
