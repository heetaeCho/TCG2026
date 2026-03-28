#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/bmffimage.hpp"

#include "exiv2/exif.hpp"



namespace {



using namespace Exiv2;

using ::testing::Eq;



class BmffImageTest : public ::testing::Test {

protected:

    BmffImageTest() : io_(nullptr, [](BasicIo*){}), bmffImage_(std::make_unique<BasicIo>(), false, 10) {}



    void SetUp() override {

        // Reset the ExifData for each test

        bmffImage_.exifData_.clear();

        bmffImage_.pixelHeight_ = 42; // Default pixel height

    }



    std::unique_ptr<BasicIo> io_;

    BmffImage bmffImage_;

};



TEST_F(BmffImageTest, PixelHeightDefault_1195) {

    EXPECT_EQ(bmffImage_.pixelHeight(), 42U);

}



TEST_F(BmffImageTest, PixelHeightFromExifData_1195) {

    Exifdatum pixelYDimension(ExifKey("Exif.Photo.PixelYDimension"), new Value);

    pixelYDimension.setValue(1080);

    bmffImage_.exifData_.add(pixelYDimension);



    EXPECT_EQ(bmffImage_.pixelHeight(), 1080U);

}



TEST_F(BmffImageTest, PixelHeightMissingExifKey_1195) {

    bmffImage_.exifData_.erase(bmffImage_.exifData_.findKey(ExifKey("Exif.Photo.PixelYDimension")));



    EXPECT_EQ(bmffImage_.pixelHeight(), 42U);

}



TEST_F(BmffImageTest, PixelHeightEmptyExifData_1195) {

    bmffImage_.exifData_.clear();



    EXPECT_EQ(bmffImage_.pixelHeight(), 42U);

}



TEST_F(BmffImageTest, PixelHeightZeroCountExifKey_1195) {

    Exifdatum pixelYDimension(ExifKey("Exif.Photo.PixelYDimension"), new Value);

    bmffImage_.exifData_.add(pixelYDimension);



    EXPECT_EQ(bmffImage_.pixelHeight(), 42U);

}



TEST_F(BmffImageTest, PixelHeightInvalidExifValue_1195) {

    Exifdatum pixelYDimension(ExifKey("Exif.Photo.PixelYDimension"), new Value);

    pixelYDimension.setValue("invalid");

    bmffImage_.exifData_.add(pixelYDimension);



    EXPECT_EQ(bmffImage_.pixelHeight(), 42U);

}



} // namespace
