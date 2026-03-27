#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class ShutterSpeedValueTest_529 : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(ShutterSpeedValueTest_529, NormalOperation_ExifPhotoShutterSpeedValuePresent_529) {

    Exifdatum datum("Exif.Photo.ShutterSpeedValue", 0x1324, undefined, "value");

    exifData.add(datum);

    auto result = shutterSpeedValue(exifData);

    ASSERT_NE(result, exifData.end());

    EXPECT_EQ(result->key(), "Exif.Photo.ShutterSpeedValue");

}



TEST_F(ShutterSpeedValueTest_529, NormalOperation_ExifImageShutterSpeedValuePresent_529) {

    Exifdatum datum("Exif.Image.ShutterSpeedValue", 0x1324, undefined, "value");

    exifData.add(datum);

    auto result = shutterSpeedValue(exifData);

    ASSERT_NE(result, exifData.end());

    EXPECT_EQ(result->key(), "Exif.Image.ShutterSpeedValue");

}



TEST_F(ShutterSpeedValueTest_529, BoundaryConditions_NoKeysPresent_529) {

    auto result = shutterSpeedValue(exifData);

    EXPECT_EQ(result, exifData.end());

}



TEST_F(ShutterSpeedValueTest_529, BoundaryConditions_EmptyExifData_529) {

    exifData.clear();

    auto result = shutterSpeedValue(exifData);

    EXPECT_EQ(result, exifData.end());

}



TEST_F(ShutterSpeedValueTest_529, ExceptionalCases_ExifPhotoKeyPresentButEmpty_529) {

    Exifdatum datum("Exif.Photo.ShutterSpeedValue", 0x1324, undefined, "");

    exifData.add(datum);

    auto result = shutterSpeedValue(exifData);

    ASSERT_NE(result, exifData.end());

    EXPECT_EQ(result->key(), "Exif.Photo.ShutterSpeedValue");

}



TEST_F(ShutterSpeedValueTest_529, ExceptionalCases_ExifImageKeyPresentButEmpty_529) {

    Exifdatum datum("Exif.Image.ShutterSpeedValue", 0x1324, undefined, "");

    exifData.add(datum);

    auto result = shutterSpeedValue(exifData);

    ASSERT_NE(result, exifData.end());

    EXPECT_EQ(result->key(), "Exif.Image.ShutterSpeedValue");

}
