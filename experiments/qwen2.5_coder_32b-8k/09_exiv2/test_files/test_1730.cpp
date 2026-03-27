#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffimage.hpp"

#include "exif.hpp"



using namespace Exiv2;



class TiffImageTest_1730 : public ::testing::Test {

protected:

    void SetUp() override {

        io = std::make_unique<BasicIo>();

        tiffImage = std::make_unique<TiffImage>(std::move(io), false);

    }



    BasicIo::UniquePtr io;

    std::unique_ptr<TiffImage> tiffImage;

};



TEST_F(TiffImageTest_1730, PixelWidthReturnsPrimaryValueWhenSet_1730) {

    uint32_t expectedWidth = 1920;

    tiffImage->pixelWidthPrimary_ = expectedWidth;

    EXPECT_EQ(tiffImage->pixelWidth(), expectedWidth);

}



TEST_F(TiffImageTest_1730, PixelWidthFallsBackToExifDataWhenPrimaryNotSet_1730) {

    uint32_t expectedWidth = 1920;

    ExifKey key("Exif.PrimaryGroup.ImageWidth");

    tiffImage->exifData_.add(key, new Value);

    auto metadata = tiffImage->exifData_.findKey(key);

    metadata->setValue(expectedWidth);



    EXPECT_EQ(tiffImage->pixelWidth(), expectedWidth);

}



TEST_F(TiffImageTest_1730, PixelWidthReturnsZeroWhenNoDataAvailable_1730) {

    EXPECT_EQ(tiffImage->pixelWidth(), 0);

}



TEST_F(TiffImageTest_1730, PixelWidthCachesPrimaryValueAfterFirstAccess_1730) {

    uint32_t expectedWidth = 1920;

    ExifKey key("Exif.PrimaryGroup.ImageWidth");

    tiffImage->exifData_.add(key, new Value);

    auto metadata = tiffImage->exifData_.findKey(key);

    metadata->setValue(expectedWidth);



    EXPECT_EQ(tiffImage->pixelWidth(), expectedWidth);

    // Modify EXIF data to a different value

    metadata->setValue(1024);

    EXPECT_EQ(tiffImage->pixelWidth(), expectedWidth);  // Should still return cached value

}
