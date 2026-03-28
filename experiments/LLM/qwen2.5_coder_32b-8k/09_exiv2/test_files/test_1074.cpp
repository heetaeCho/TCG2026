#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = BasicIo::autoPtr();

    Image* image = nullptr;



    void SetUp() override {

        io = BasicIo::createMemIo();

        image = new Image(imagePng, 0x1F, std::move(io));

    }



    void TearDown() override {

        delete image;

    }

};



TEST_F(ImageTest_1074, SetExifDataWithNonEmptyExifData_1074) {

    ExifData exifData;

    exifData.add(ExifKey("Exif.Image.Artist"), new AsciiValue("John Doe"));

    image->setExifData(exifData);

    EXPECT_EQ(image->exifData().count(), 1u);

}



TEST_F(ImageTest_1074, SetExifDataWithEmptyExifData_1074) {

    ExifData exifData;

    image->setExifData(exifData);

    EXPECT_EQ(image->exifData().empty(), true);

}



TEST_F(ImageTest_1074, SetExifDataTwice_1074) {

    ExifData firstExifData;

    firstExifData.add(ExifKey("Exif.Image.Artist"), new AsciiValue("John Doe"));

    image->setExifData(firstExifData);



    ExifData secondExifData;

    secondExifData.add(ExifKey("Exif.Image.Copyright"), new AsciiValue("2023 John Doe"));

    image->setExifData(secondExifData);

    EXPECT_EQ(image->exifData().count(), 1u);

}



TEST_F(ImageTest_1074, SetExifDataWithMultipleEntries_1074) {

    ExifData exifData;

    exifData.add(ExifKey("Exif.Image.Artist"), new AsciiValue("John Doe"));

    exifData.add(ExifKey("Exif.Image.Copyright"), new AsciiValue("2023 John Doe"));

    image->setExifData(exifData);

    EXPECT_EQ(image->exifData().count(), 2u);

}



TEST_F(ImageTest_1074, SetExifDataWithInvalidKey_1074) {

    ExifData exifData;

    exifData.add(ExifKey("Invalid.Key"), new AsciiValue("John Doe"));

    image->setExifData(exifData);

    EXPECT_EQ(image->exifData().count(), 1u); // Assuming invalid keys are added

}
