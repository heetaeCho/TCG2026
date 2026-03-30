#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/easyaccess.cpp"



using namespace Exiv2;



class FocalLengthTest_538 : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(FocalLengthTest_538, NormalOperationWithValidKey_538) {

    exifData.add(ExifKey("Exif.Photo.FocalLength"), new RationalValue(Rational(100, 2)));

    auto it = focalLength(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Photo.FocalLength");

}



TEST_F(FocalLengthTest_538, BoundaryConditionEmptyExifData_538) {

    auto it = focalLength(exifData);

    EXPECT_EQ(it, exifData.end());

}



TEST_F(FocalLengthTest_538, BoundaryConditionKeyNotPresent_538) {

    exifData.add(ExifKey("Exif.Photo.ApertureValue"), new RationalValue(Rational(100, 2)));

    auto it = focalLength(exifData);

    EXPECT_EQ(it, exifData.end());

}



TEST_F(FocalLengthTest_538, NormalOperationWithMultipleValidKeys_538) {

    exifData.add(ExifKey("Exif.Image.FocalLength"), new RationalValue(Rational(100, 2)));

    exifData.add(ExifKey("Exif.Photo.FocalLength"), new RationalValue(Rational(150, 2)));

    auto it = focalLength(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Image.FocalLength");

}



TEST_F(FocalLengthTest_538, NormalOperationWithDifferentValidKeys_538) {

    exifData.add(ExifKey("Exif.Canon.FocalLength"), new RationalValue(Rational(200, 2)));

    auto it = focalLength(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Canon.FocalLength");

}



TEST_F(FocalLengthTest_538, ExceptionalCaseWithInvalidKey_538) {

    exifData.add(ExifKey("Invalid.Key"), new RationalValue(Rational(100, 2)));

    auto it = focalLength(exifData);

    EXPECT_EQ(it, exifData.end());

}
