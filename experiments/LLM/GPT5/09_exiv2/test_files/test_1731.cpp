#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/tiffimage.hpp"
#include "exiv2/exif.hpp"
#include "exiv2/metadatum.hpp"
#include "exiv2/image.hpp"

// Mock dependencies
class MockExifData : public Exiv2::ExifData {
public:
    MOCK_METHOD(Exiv2::Exifdatum&, operator[], (const std::string& key), (override));
    MOCK_METHOD(void, add, (const Exiv2::ExifKey& key, const Exiv2::Value* pValue), (override));
    MOCK_METHOD(void, clear, (), (override));
    MOCK_METHOD(Exiv2::ExifData::iterator, findKey, (const Exiv2::ExifKey& key), (const, override));
    MOCK_METHOD(Exiv2::ExifData::const_iterator, findKey, (const Exiv2::ExifKey& key), (const, override));
};

// Test fixture class for TiffImage
class TiffImageTest_1731 : public ::testing::Test {
protected:
    std::unique_ptr<Exiv2::BasicIo> io_;
    std::unique_ptr<Exiv2::TiffImage> tiffImage_;

    TiffImageTest_1731() : io_(nullptr) {}

    void SetUp() override {
        io_ = std::make_unique<Exiv2::BasicIo>();
        tiffImage_ = std::make_unique<Exiv2::TiffImage>(std::move(io_), true);
    }
};

// Test case: Test pixelHeight for normal operation
TEST_F(TiffImageTest_1731, PixelHeightReturnsValue_1731) {
    MockExifData mockExifData;
    Exiv2::ExifKey key("Exif.TestGroup.ImageLength");
    EXPECT_CALL(mockExifData, findKey(key)).WillOnce(testing::Return(mockExifData.end()));
    EXPECT_CALL(mockExifData, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(mockExifData, toUint32()).WillOnce(testing::Return(300));

    // Set mock exifData to tiffImage
    tiffImage_->exifData() = mockExifData;

    uint32_t pixelHeight = tiffImage_->pixelHeight();
    EXPECT_EQ(pixelHeight, 300);  // The expected pixel height
}

// Test case: Test pixelHeight when primary height is non-zero
TEST_F(TiffImageTest_1731, PixelHeightReturnsPrimaryValue_1732) {
    tiffImage_->pixelHeightPrimary_ = 500;  // Set a non-zero primary height

    uint32_t pixelHeight = tiffImage_->pixelHeight();
    EXPECT_EQ(pixelHeight, 500);  // It should return the primary pixel height value
}

// Test case: Test boundary condition where image height is 0
TEST_F(TiffImageTest_1731, PixelHeightReturnsZeroIfNotSet_1733) {
    MockExifData mockExifData;
    Exiv2::ExifKey key("Exif.TestGroup.ImageLength");
    EXPECT_CALL(mockExifData, findKey(key)).WillOnce(testing::Return(mockExifData.end()));
    EXPECT_CALL(mockExifData, count()).WillOnce(testing::Return(0));

    // Set mock exifData to tiffImage
    tiffImage_->exifData() = mockExifData;

    uint32_t pixelHeight = tiffImage_->pixelHeight();
    EXPECT_EQ(pixelHeight, 0);  // Since no valid value is found, it should return 0
}

// Test case: Test error handling when an invalid Exif key is returned
TEST_F(TiffImageTest_1731, PixelHeightHandlesErrorGracefully_1734) {
    MockExifData mockExifData;
    Exiv2::ExifKey key("Exif.InvalidGroup.ImageLength");
    EXPECT_CALL(mockExifData, findKey(key)).WillOnce(testing::Return(mockExifData.end()));
    EXPECT_CALL(mockExifData, count()).WillOnce(testing::Return(0));

    // Set mock exifData to tiffImage
    tiffImage_->exifData() = mockExifData;

    uint32_t pixelHeight = tiffImage_->pixelHeight();
    EXPECT_EQ(pixelHeight, 0);  // Invalid key handling should return 0
}

// Test case: Test pixelHeight when Exif key has no data
TEST_F(TiffImageTest_1731, PixelHeightReturnsZeroIfNoData_1735) {
    MockExifData mockExifData;
    Exiv2::ExifKey key("Exif.TestGroup.ImageLength");
    EXPECT_CALL(mockExifData, findKey(key)).WillOnce(testing::Return(mockExifData.end()));
    EXPECT_CALL(mockExifData, count()).WillOnce(testing::Return(0));  // No data available for the key

    // Set mock exifData to tiffImage
    tiffImage_->exifData() = mockExifData;

    uint32_t pixelHeight = tiffImage_->pixelHeight();
    EXPECT_EQ(pixelHeight, 0);  // It should return 0 due to no data
}