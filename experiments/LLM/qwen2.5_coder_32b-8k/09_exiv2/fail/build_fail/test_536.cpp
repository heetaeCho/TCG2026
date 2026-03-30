#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class FlashFunctionTest : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(FlashFunctionTest_536, NormalOperationWithExistingKey_536) {

    Exifdatum exifDatum("Exif.Photo.Flash", 0);

    exifData.add(exifDatum);



    auto it = flash(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Photo.Flash");

}



TEST_F(FlashFunctionTest_536, NormalOperationWithDifferentKeyOrder_536) {

    Exifdatum exifDatum("Exif.Sony2.FlashAction", 0);

    exifData.add(exifDatum);



    auto it = flash(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Sony2.FlashAction");

}



TEST_F(FlashFunctionTest_536, BoundaryConditionWithEmptyExifData_536) {

    auto it = flash(exifData);

    EXPECT_EQ(it, exifData.end());

}



TEST_F(FlashFunctionTest_536, BoundaryConditionWithNonFlashKeys_536) {

    Exifdatum exifDatum("Exif.Photo.DateTime", 0);

    exifData.add(exifDatum);



    auto it = flash(exifData);

    EXPECT_EQ(it, exifData.end());

}



TEST_F(FlashFunctionTest_536, BoundaryConditionWithMultipleFlashKeys_536) {

    Exifdatum exifDatum1("Exif.Photo.Flash", 0);

    Exifdatum exifDatum2("Exif.Image.Flash", 0);

    exifData.add(exifDatum1);

    exifData.add(exifDatum2);



    auto it = flash(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Photo.Flash");

}
