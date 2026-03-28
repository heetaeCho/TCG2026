#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/orfimage.hpp"

#include "exiv2/exif.hpp"



using namespace Exiv2;



class OrfImageTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Create a basic IO instance for the image

        BasicIo::UniquePtr io = BasicIo::createMemIo();

        orfImage = std::make_unique<OrfImage>(std::move(io), false);

    }



    std::unique_ptr<OrfImage> orfImage;

};



TEST_F(OrfImageTest_PixelHeight_ReturnsZeroWhenNoExifData_1549) {

    EXPECT_EQ(orfImage->pixelHeight(), 0U);

}



TEST_F(OrfImageTest_PixelHeight_ReturnsCorrectValueWhenExifDataPresent_1549) {

    ExifKey imageLengthKey("Exif.Image.ImageLength");

    Value::UniquePtr value = Value::create(TypeId::unsignedLong, 1);

    value->make(2048); // Set the pixel height to 2048

    orfImage->exifData().add(imageLengthKey, value.release());



    EXPECT_EQ(orfImage->pixelHeight(), 2048U);

}



TEST_F(OrfImageTest_PixelHeight_ReturnsZeroWhenExifDataCountIsZero_1549) {

    ExifKey imageLengthKey("Exif.Image.ImageLength");

    Value::UniquePtr value = Value::create(TypeId::unsignedLong, 0);

    orfImage->exifData().add(imageLengthKey, value.release());



    EXPECT_EQ(orfImage->pixelHeight(), 0U);

}



TEST_F(OrfImageTest_PixelHeight_ReturnsZeroWhenExifDataKeyNotFound_1549) {

    ExifKey nonExistentKey("Exif.NonExistent.Key");

    Value::UniquePtr value = Value::create(TypeId::unsignedLong, 1);

    value->make(2048); // Set the pixel height to 2048

    orfImage->exifData().add(nonExistentKey, value.release());



    EXPECT_EQ(orfImage->pixelHeight(), 0U);

}
