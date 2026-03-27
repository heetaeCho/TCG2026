#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class ExifDataTest : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(ExifDataTest_42, CountInitiallyZero_42) {

    EXPECT_EQ(exifData.count(), 0);

}



TEST_F(ExifDataTest_42, AddIncreasesCount_42) {

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("Artist Name");

    exifData.add(key, value);

    EXPECT_EQ(exifData.count(), 1);

    delete value;

}



TEST_F(ExifDataTest_42, AddMultipleIncreasesCount_42) {

    ExifKey key1("Exif.Image.Artist");

    Value* value1 = new StringValue("Artist Name");

    exifData.add(key1, value1);



    ExifKey key2("Exif.Image.Copyright");

    Value* value2 = new StringValue("Copyright Info");

    exifData.add(key2, value2);



    EXPECT_EQ(exifData.count(), 2);

    delete value1;

    delete value2;

}



TEST_F(ExifDataTest_42, ClearResetsCount_42) {

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("Artist Name");

    exifData.add(key, value);



    exifData.clear();

    EXPECT_EQ(exifData.count(), 0);

    delete value;

}



TEST_F(ExifDataTest_42, FindKeyReturnsValidIterator_42) {

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("Artist Name");

    exifData.add(key, value);



    auto it = exifData.findKey(key);

    EXPECT_NE(it, exifData.end());

    delete value;

}



TEST_F(ExifDataTest_42, FindNonExistingKeyReturnsEndIterator_42) {

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("Artist Name");

    exifData.add(key, value);



    ExifKey nonExistingKey("Exif.Non.Existing");

    auto it = exifData.findKey(nonExistingKey);

    EXPECT_EQ(it, exifData.end());

    delete value;

}



TEST_F(ExifDataTest_42, EmptyInitiallyTrue_42) {

    EXPECT_TRUE(exifData.empty());

}



TEST_F(ExifDataTest_42, AddMakesEmptyFalse_42) {

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("Artist Name");

    exifData.add(key, value);



    EXPECT_FALSE(exifData.empty());

    delete value;

}



TEST_F(ExifDataTest_42, ClearMakesEmptyTrue_42) {

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("Artist Name");

    exifData.add(key, value);

    exifData.clear();



    EXPECT_TRUE(exifData.empty());

    delete value;

}



TEST_F(ExifDataTest_42, EraseSingleElementReducesCount_42) {

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("Artist Name");

    exifData.add(key, value);



    auto it = exifData.findKey(key);

    exifData.erase(it);

    EXPECT_EQ(exifData.count(), 0);

    delete value;

}



TEST_F(ExifDataTest_42, EraseRangeReducesCount_42) {

    ExifKey key1("Exif.Image.Artist");

    Value* value1 = new StringValue("Artist Name");

    exifData.add(key1, value1);



    ExifKey key2("Exif.Image.Copyright");

    Value* value2 = new StringValue("Copyright Info");

    exifData.add(key2, value2);



    exifData.erase(exifData.begin(), exifData.end());

    EXPECT_EQ(exifData.count(), 0);

    delete value1;

    delete value2;

}



TEST_F(ExifDataTest_42, AccessOperatorAddsNewElement_42) {

    ExifKey key("Exif.Image.Artist");

    exifData[key] = Exifdatum(key, new StringValue("Artist Name"));



    EXPECT_EQ(exifData.count(), 1);

}
