#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/bmpimage.hpp>
#include <exiv2/error.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>

#include <memory>
#include <fstream>
#include <cstdio>
#include <cstring>

namespace {

// Helper to create a minimal valid BMP file in memory
std::vector<unsigned char> createMinimalBmp() {
    // Minimal BMP: 14-byte file header + 40-byte DIB header (BITMAPINFOHEADER)
    // 1x1 pixel, 24-bit color
    std::vector<unsigned char> bmp(54 + 4, 0); // 54 header + some pixel data padded

    // BM signature
    bmp[0] = 'B';
    bmp[1] = 'M';

    // File size (little-endian)
    uint32_t fileSize = static_cast<uint32_t>(bmp.size());
    std::memcpy(&bmp[2], &fileSize, 4);

    // Reserved
    bmp[6] = 0; bmp[7] = 0; bmp[8] = 0; bmp[9] = 0;

    // Pixel data offset
    uint32_t offset = 54;
    std::memcpy(&bmp[10], &offset, 4);

    // DIB header size (BITMAPINFOHEADER = 40)
    uint32_t dibSize = 40;
    std::memcpy(&bmp[14], &dibSize, 4);

    // Width = 1
    int32_t width = 1;
    std::memcpy(&bmp[18], &width, 4);

    // Height = 1
    int32_t height = 1;
    std::memcpy(&bmp[22], &height, 4);

    // Color planes = 1
    uint16_t planes = 1;
    std::memcpy(&bmp[26], &planes, 2);

    // Bits per pixel = 24
    uint16_t bpp = 24;
    std::memcpy(&bmp[28], &bpp, 2);

    // Compression = 0 (BI_RGB)
    uint32_t compression = 0;
    std::memcpy(&bmp[30], &compression, 4);

    // Image size (can be 0 for BI_RGB)
    uint32_t imgSize = 0;
    std::memcpy(&bmp[34], &imgSize, 4);

    return bmp;
}

// Helper to create a BmpImage from memory
std::unique_ptr<Exiv2::BmpImage> createBmpImageFromMemory(const std::vector<unsigned char>& data) {
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    return std::make_unique<Exiv2::BmpImage>(std::move(io));
}

// Helper to create a BmpImage from an empty/invalid memory block
std::unique_ptr<Exiv2::BmpImage> createBmpImageFromInvalidMemory() {
    std::vector<unsigned char> data = {0x00, 0x00, 0x00, 0x00};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    return std::make_unique<Exiv2::BmpImage>(std::move(io));
}

} // anonymous namespace

class BmpImageTest_1040 : public ::testing::Test {
protected:
    void SetUp() override {
        bmpData_ = createMinimalBmp();
    }

    std::vector<unsigned char> bmpData_;
};

// Test that writeMetadata throws an exception (BMP writing is unsupported)
TEST_F(BmpImageTest_1040, WriteMetadataThrowsUnsupported_1040) {
    auto image = createBmpImageFromMemory(bmpData_);
    ASSERT_NE(image, nullptr);

    try {
        image->writeMetadata();
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerWritingImageFormatUnsupported);
    } catch (...) {
        FAIL() << "Expected Exiv2::Error but got a different exception";
    }
}

// Test that mimeType returns the correct MIME type for BMP
TEST_F(BmpImageTest_1040, MimeTypeIsCorrect_1040) {
    auto image = createBmpImageFromMemory(bmpData_);
    ASSERT_NE(image, nullptr);

    std::string mime = image->mimeType();
    EXPECT_EQ(mime, "image/x-ms-bmp");
}

// Test that readMetadata works on a valid minimal BMP without throwing
TEST_F(BmpImageTest_1040, ReadMetadataOnValidBmp_1040) {
    auto image = createBmpImageFromMemory(bmpData_);
    ASSERT_NE(image, nullptr);

    EXPECT_NO_THROW(image->readMetadata());
}

// Test that setExifData throws (BMP doesn't support EXIF)
TEST_F(BmpImageTest_1040, SetExifDataThrows_1040) {
    auto image = createBmpImageFromMemory(bmpData_);
    ASSERT_NE(image, nullptr);

    Exiv2::ExifData exifData;
    try {
        image->setExifData(exifData);
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerInvalidSettingForImage);
    } catch (...) {
        FAIL() << "Expected Exiv2::Error but got a different exception";
    }
}

// Test that setIptcData throws (BMP doesn't support IPTC)
TEST_F(BmpImageTest_1040, SetIptcDataThrows_1040) {
    auto image = createBmpImageFromMemory(bmpData_);
    ASSERT_NE(image, nullptr);

    Exiv2::IptcData iptcData;
    try {
        image->setIptcData(iptcData);
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerInvalidSettingForImage);
    } catch (...) {
        FAIL() << "Expected Exiv2::Error but got a different exception";
    }
}

// Test that setComment throws (BMP doesn't support comments)
TEST_F(BmpImageTest_1040, SetCommentThrows_1040) {
    auto image = createBmpImageFromMemory(bmpData_);
    ASSERT_NE(image, nullptr);

    try {
        image->setComment("test comment");
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerInvalidSettingForImage);
    } catch (...) {
        FAIL() << "Expected Exiv2::Error but got a different exception";
    }
}

// Test readMetadata on invalid data
TEST_F(BmpImageTest_1040, ReadMetadataOnInvalidDataThrows_1040) {
    auto image = createBmpImageFromInvalidMemory();
    ASSERT_NE(image, nullptr);

    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test readMetadata on empty data
TEST_F(BmpImageTest_1040, ReadMetadataOnEmptyDataThrows_1040) {
    std::vector<unsigned char> emptyData;
    auto io = std::make_unique<Exiv2::MemIo>(emptyData.data(), emptyData.size());
    auto image = std::make_unique<Exiv2::BmpImage>(std::move(io));

    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test that BmpImage can be constructed with a valid IO
TEST_F(BmpImageTest_1040, ConstructionWithValidIo_1040) {
    auto io = std::make_unique<Exiv2::MemIo>(bmpData_.data(), bmpData_.size());
    EXPECT_NO_THROW({
        Exiv2::BmpImage image(std::move(io));
    });
}

// Test that pixelWidth and pixelHeight are set after readMetadata on a valid BMP
TEST_F(BmpImageTest_1040, PixelDimensionsAfterReadMetadata_1040) {
    auto image = createBmpImageFromMemory(bmpData_);
    ASSERT_NE(image, nullptr);

    image->readMetadata();

    EXPECT_EQ(image->pixelWidth(), 1);
    EXPECT_EQ(image->pixelHeight(), 1);
}

// Test writeMetadata multiple times still throws
TEST_F(BmpImageTest_1040, WriteMetadataAlwaysThrows_1040) {
    auto image = createBmpImageFromMemory(bmpData_);
    ASSERT_NE(image, nullptr);

    EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
    EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
}

// Test that reading truncated BMP header throws
TEST_F(BmpImageTest_1040, ReadMetadataOnTruncatedBmpThrows_1040) {
    // Only the "BM" signature, but truncated
    std::vector<unsigned char> truncated = {'B', 'M', 0x00, 0x00};
    auto io = std::make_unique<Exiv2::MemIo>(truncated.data(), truncated.size());
    auto image = std::make_unique<Exiv2::BmpImage>(std::move(io));

    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test with a BMP that has wrong signature
TEST_F(BmpImageTest_1040, ReadMetadataWrongSignatureThrows_1040) {
    auto data = bmpData_;
    data[0] = 'X';  // Corrupt the BM signature
    data[1] = 'Y';

    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto image = std::make_unique<Exiv2::BmpImage>(std::move(io));

    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test that setComment with empty string still throws
TEST_F(BmpImageTest_1040, SetEmptyCommentThrows_1040) {
    auto image = createBmpImageFromMemory(bmpData_);
    ASSERT_NE(image, nullptr);

    try {
        image->setComment("");
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerInvalidSettingForImage);
    } catch (...) {
        FAIL() << "Expected Exiv2::Error but got a different exception";
    }
}
