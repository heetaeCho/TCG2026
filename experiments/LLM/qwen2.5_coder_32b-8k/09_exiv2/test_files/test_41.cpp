#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include <string>



namespace {



class ExifDataTest : public ::testing::Test {

protected:

    Exiv2::ExifData exifData;

};



TEST_F(ExifDataTest_41, EmptyInitially_41) {

    EXPECT_TRUE(exifData.empty());

}



TEST_F(ExifDataTest_41, NotEmptyAfterAdd_41) {

    Exiv2::ExifKey key("Exif.Image.Artist");

    Exiv2::Value* value = Exiv2::Value::create(Exiv2::asciiString);

    exifData.add(key, value);

    EXPECT_FALSE(exifData.empty());

}



TEST_F(ExifDataTest_41, ClearEmptiesData_41) {

    Exiv2::ExifKey key("Exif.Image.Artist");

    Exiv2::Value* value = Exiv2::Value::create(Exiv2::asciiString);

    exifData.add(key, value);

    exifData.clear();

    EXPECT_TRUE(exifData.empty());

}



TEST_F(ExifDataTest_41, FindKeyReturnsIterator_41) {

    Exiv2::ExifKey key("Exif.Image.Artist");

    Exiv2::Value* value = Exiv2::Value::create(Exiv2::asciiString);

    exifData.add(key, value);

    auto it = exifData.findKey(key);

    EXPECT_NE(it, exifData.end());

}



TEST_F(ExifDataTest_41, FindNonexistentKeyReturnsEnd_41) {

    Exiv2::ExifKey key("Exif.Image.Artist");

    auto it = exifData.findKey(key);

    EXPECT_EQ(it, exifData.end());

}



TEST_F(ExifDataTest_41, EraseSingleElement_41) {

    Exiv2::ExifKey key("Exif.Image.Artist");

    Exiv2::Value* value = Exiv2::Value::create(Exiv2::asciiString);

    exifData.add(key, value);

    auto it = exifData.findKey(key);

    exifData.erase(it);

    EXPECT_TRUE(exifData.empty());

}



TEST_F(ExifDataTest_41, EraseRange_41) {

    Exiv2::ExifKey key1("Exif.Image.Artist");

    Exiv2::Value* value1 = Exiv2::Value::create(Exiv2::asciiString);

    exifData.add(key1, value1);



    Exiv2::ExifKey key2("Exif.Image.Copyright");

    Exiv2::Value* value2 = Exiv2::Value::create(Exiv2::asciiString);

    exifData.add(key2, value2);



    auto beg = exifData.begin();

    auto end = exifData.end();

    exifData.erase(beg, end);

    EXPECT_TRUE(exifData.empty());

}



TEST_F(ExifDataTest_41, SortByKey_41) {

    Exiv2::ExifKey key1("Exif.Image.Artist");

    Exiv2::Value* value1 = Exiv2::Value::create(Exiv2::asciiString);

    exifData.add(key1, value1);



    Exiv2::ExifKey key2("Exif.Image.Copyright");

    Exiv2::Value* value2 = Exiv2::Value::create(Exiv2::asciiString);

    exifData.add(key2, value2);



    exifData.sortByKey();

    auto it = exifData.begin();

    EXPECT_EQ(it->key(), key1);

    ++it;

    EXPECT_EQ(it->key(), key2);

}



TEST_F(ExifDataTest_41, SortByTag_41) {

    Exiv2::ExifKey key1("Exif.Image.Artist");

    Exiv2::Value* value1 = Exiv2::Value::create(Exiv2::asciiString);

    exifData.add(key1, value1);



    Exiv2::ExifKey key2("Exif.Image.Copyright");

    Exiv2::Value* value2 = Exiv2::Value::create(Exiv2::asciiString);

    exifData.add(key2, value2);



    exifData.sortByTag();

    auto it = exifData.begin();

    EXPECT_EQ(it->key(), key1);

    ++it;

    EXPECT_EQ(it->key(), key2);

}



}  // namespace
