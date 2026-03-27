#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



// Fixture for testing flashEnergy function

class FlashEnergyTest_540 : public ::testing::Test {

protected:

    ExifData ed;

};



TEST_F(FlashEnergyTest_540, FindExifPhotoFlashEnergy_540) {

    // Arrange

    Exifdatum exifDatum("Exif.Photo.FlashEnergy", "123");

    ed.add(exifDatum);



    // Act

    auto result = flashEnergy(ed);



    // Assert

    ASSERT_NE(result, ed.end());

    EXPECT_EQ(result->key(), "Exif.Photo.FlashEnergy");

}



TEST_F(FlashEnergyTest_540, FindExifImageFlashEnergy_540) {

    // Arrange

    Exifdatum exifDatum("Exif.Image.FlashEnergy", "123");

    ed.add(exifDatum);



    // Act

    auto result = flashEnergy(ed);



    // Assert

    ASSERT_NE(result, ed.end());

    EXPECT_EQ(result->key(), "Exif.Image.FlashEnergy");

}



TEST_F(FlashEnergyTest_540, FindFirstMatchingKey_540) {

    // Arrange

    Exifdatum exifDatum1("Exif.Photo.FlashEnergy", "123");

    Exifdatum exifDatum2("Exif.Image.FlashEnergy", "456");

    ed.add(exifDatum1);

    ed.add(exifDatum2);



    // Act

    auto result = flashEnergy(ed);



    // Assert

    ASSERT_NE(result, ed.end());

    EXPECT_EQ(result->key(), "Exif.Photo.FlashEnergy");

}



TEST_F(FlashEnergyTest_540, NoMatchingKey_540) {

    // Arrange (empty ExifData)



    // Act

    auto result = flashEnergy(ed);



    // Assert

    EXPECT_EQ(result, ed.end());

}



TEST_F(FlashEnergyTest_540, MultipleNonMatchingKeys_540) {

    // Arrange

    Exifdatum exifDatum1("Exif.Photo.ExposureTime", "1/250");

    Exifdatum exifDatum2("Exif.Image.DateTime", "2023:01:01 12:00:00");

    ed.add(exifDatum1);

    ed.add(exifDatum2);



    // Act

    auto result = flashEnergy(ed);



    // Assert

    EXPECT_EQ(result, ed.end());

}
