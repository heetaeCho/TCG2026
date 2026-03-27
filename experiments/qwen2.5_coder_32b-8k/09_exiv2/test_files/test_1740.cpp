#include <gtest/gtest.h>

#include "exiv2/cr2image.hpp"

#include "exiv2/exif.hpp"



namespace {



class Cr2ImageTest : public ::testing::Test {

protected:

    void SetUp() override {

        io = Exiv2::BasicIo::createMemIo();

        cr2Image = std::make_unique<Exiv2::Cr2Image>(std::move(io), false);

    }



    void TearDown() override {

        // No specific teardown needed for this test suite

    }



    Exiv2::BasicIo::UniquePtr io;

    std::unique_ptr<Exiv2::Cr2Image> cr2Image;

};



TEST_F(Cr2ImageTest_PixelWidth_ReturnsDefaultValue_1740, DefaultValueWhenKeyNotFound_1740) {

    EXPECT_EQ(cr2Image->pixelWidth(), 0u);

}



TEST_F(Cr2ImageTest_PixelWidth_ReturnsCorrectValue_1740, ValueFromExifData_1740) {

    Exiv2::ExifKey key("Exif.Photo.PixelXDimension");

    Exiv2::Value::AutoPtr value = Exiv2::Value::create(Exiv2::unsignedLong);

    value->read(800u); // Example width

    cr2Image->exifData().add(key, value.get());

    EXPECT_EQ(cr2Image->pixelWidth(), 800u);

}



TEST_F(Cr2ImageTest_PixelWidth_BoundaryCondition_1740, ZeroValueFromExifData_1740) {

    Exiv2::ExifKey key("Exif.Photo.PixelXDimension");

    Exiv2::Value::AutoPtr value = Exiv2::Value::create(Exiv2::unsignedLong);

    value->read(0u); // Zero width

    cr2Image->exifData().add(key, value.get());

    EXPECT_EQ(cr2Image->pixelWidth(), 0u);

}



TEST_F(Cr2ImageTest_PixelWidth_ExceptionalCase_1740, InvalidValueTypeInExifData_1740) {

    Exiv2::ExifKey key("Exif.Photo.PixelXDimension");

    Exiv2::Value::AutoPtr value = Exiv2::Value::create(Exiv2::asciiString);

    value->read("Invalid"); // Invalid width

    cr2Image->exifData().add(key, value.get());

    EXPECT_EQ(cr2Image->pixelWidth(), 0u); // Expecting default due to invalid conversion

}



}  // namespace
