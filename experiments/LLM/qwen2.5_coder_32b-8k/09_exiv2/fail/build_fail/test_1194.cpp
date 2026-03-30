#include <gtest/gtest.h>

#include "exiv2/bmffimage.hpp"



using namespace Exiv2;



class BmffImageTest_1194 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io;

    BmffImage* bmffImage;



    void SetUp() override {

        io = BasicIo::createMemIo();

        bmffImage = new BmffImage(std::move(io), false, 10);

    }



    void TearDown() override {

        delete bmffImage;

    }

};



TEST_F(BmffImageTest_1194, PixelWidth_Default_1194) {

    EXPECT_EQ(bmffImage->pixelWidth(), 0U);

}



TEST_F(BmffImageTest_1194, PixelWidth_ExifData_Present_1194) {

    Exifdatum pixelXDimension(ExifKey("Exif.Photo.PixelXDimension"), nullptr);

    pixelXDimension.setValue(static_cast<uint32_t>(800));

    bmffImage->exifData_.add(pixelXDimension);



    EXPECT_EQ(bmffImage->pixelWidth(), 800U);

}



TEST_F(BmffImageTest_1194, PixelWidth_ExifData_EmptyCount_1194) {

    Exifdatum pixelXDimension(ExifKey("Exif.Photo.PixelXDimension"), nullptr);

    bmffImage->exifData_.add(pixelXDimension);



    EXPECT_EQ(bmffImage->pixelWidth(), 0U);

}



TEST_F(BmffImageTest_1194, PixelWidth_ExifData_NotPresent_1194) {

    EXPECT_EQ(bmffImage->pixelWidth(), 0U);

}
