#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "TestProjects/exiv2/src/easyaccess.cpp"



namespace Exiv2 {



class BrightnessValueTest_531 : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(BrightnessValueTest_531, NormalOperation_531) {

    // Arrange

    Exifdatum datum("Exif.Photo.BrightnessValue", "1.0");

    exifData.add(datum);



    // Act

    auto it = brightnessValue(exifData);



    // Assert

    EXPECT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Photo.BrightnessValue");

}



TEST_F(BrightnessValueTest_531, BoundaryConditions_EmptyExifData_531) {

    // Arrange: Empty ExifData



    // Act

    auto it = brightnessValue(exifData);



    // Assert

    EXPECT_EQ(it, exifData.end());

}



TEST_F(BrightnessValueTest_531, BoundaryConditions_NoBrightnessTags_531) {

    // Arrange: Add a different tag

    Exifdatum datum("Exif.Photo.SomeOtherTag", "SomeValue");

    exifData.add(datum);



    // Act

    auto it = brightnessValue(exifData);



    // Assert

    EXPECT_EQ(it, exifData.end());

}



TEST_F(BrightnessValueTest_531, MultipleBrightnessTags_ReturnsFirstMatch_531) {

    // Arrange: Add multiple brightness tags

    Exifdatum datum1("Exif.Photo.BrightnessValue", "1.0");

    Exifdatum datum2("Exif.Image.BrightnessValue", "2.0");

    exifData.add(datum1);

    exifData.add(datum2);



    // Act

    auto it = brightnessValue(exifData);



    // Assert: Should return the first match

    EXPECT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Photo.BrightnessValue");

}



TEST_F(BrightnessValueTest_531, CaseInsensitiveKeyMatching_531) {

    // Arrange: Add a brightness tag with mixed case key

    Exifdatum datum("exIf.PhoTo.brIgHtNeSsVaLuE", "1.0");

    exifData.add(datum);



    // Act

    auto it = brightnessValue(exifData);



    // Assert: Should still match the key correctly

    EXPECT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "exIf.PhoTo.brIgHtNeSsVaLuE");

}



}  // namespace Exiv2
