#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/easyaccess.cpp"



using namespace Exiv2;



class SensingMethodTest_542 : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(SensingMethodTest_542, FindExifPhotoSensingMethod_542) {

    ExifKey key("Exif.Photo.SensingMethod");

    Value* value = new UShortValue(1);

    Exifdatum datum(key, value);

    exifData.add(datum);



    auto it = sensingMethod(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), key);

}



TEST_F(SensingMethodTest_542, FindExifImageSensingMethod_542) {

    ExifKey key("Exif.Image.SensingMethod");

    Value* value = new UShortValue(1);

    Exifdatum datum(key, value);

    exifData.add(datum);



    auto it = sensingMethod(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), key);

}



TEST_F(SensingMethodTest_542, NoSensingMethodFound_542) {

    ExifKey key("Exif.Image.Artist");

    Value* value = new AsciiValue("Artist Name");

    Exifdatum datum(key, value);

    exifData.add(datum);



    auto it = sensingMethod(exifData);

    EXPECT_EQ(it, exifData.end());

}



TEST_F(SensingMethodTest_542, BothSensingMethodsPresent_542) {

    ExifKey key1("Exif.Photo.SensingMethod");

    Value* value1 = new UShortValue(1);

    Exifdatum datum1(key1, value1);



    ExifKey key2("Exif.Image.SensingMethod");

    Value* value2 = new UShortValue(2);

    Exifdatum datum2(key2, value2);



    exifData.add(datum1);

    exifData.add(datum2);



    auto it = sensingMethod(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), key1); // Should find the first one in the list

}



TEST_F(SensingMethodTest_542, EmptyExifData_542) {

    auto it = sensingMethod(exifData);

    EXPECT_EQ(it, exifData.end());

}
