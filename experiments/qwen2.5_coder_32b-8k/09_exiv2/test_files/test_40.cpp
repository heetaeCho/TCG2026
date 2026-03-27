#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class ExifDataTest_40 : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(ExifDataTest_40, EmptyInitially_40) {

    EXPECT_TRUE(exifData.empty());

}



TEST_F(ExifDataTest_40, CountInitiallyZero_40) {

    EXPECT_EQ(0, exifData.count());

}



TEST_F(ExifDataTest_40, AddIncreasesCount_40) {

    ExifKey key("Exif.Image.Artist");

    Value* pValue = new StringValue("Artist Name");

    exifData.add(key, pValue);

    EXPECT_EQ(1, exifData.count());

}



TEST_F(ExifDataTest_40, AddThenClearCountZero_40) {

    ExifKey key("Exif.Image.Artist");

    Value* pValue = new StringValue("Artist Name");

    exifData.add(key, pValue);

    exifData.clear();

    EXPECT_EQ(0, exifData.count());

}



TEST_F(ExifDataTest_40, FindKeyReturnsEndIfNotFound_40) {

    ExifKey key("Exif.Image.Artist");

    auto it = exifData.findKey(key);

    EXPECT_EQ(exifData.end(), it);

}



TEST_F(ExifDataTest_40, AddThenFindKeyFindsIt_40) {

    ExifKey key("Exif.Image.Artist");

    Value* pValue = new StringValue("Artist Name");

    exifData.add(key, pValue);

    auto it = exifData.findKey(key);

    EXPECT_NE(exifData.end(), it);

}



TEST_F(ExifDataTest_40, EraseSingleElementReducesCount_40) {

    ExifKey key("Exif.Image.Artist");

    Value* pValue = new StringValue("Artist Name");

    exifData.add(key, pValue);

    auto it = exifData.findKey(key);

    exifData.erase(it);

    EXPECT_EQ(0, exifData.count());

}



TEST_F(ExifDataTest_40, EraseRangeReducesCount_40) {

    ExifKey key1("Exif.Image.Artist");

    Value* pValue1 = new StringValue("Artist Name");

    ExifKey key2("Exif.Image.Copyright");

    Value* pValue2 = new StringValue("Copyright Info");

    exifData.add(key1, pValue1);

    exifData.add(key2, pValue2);

    exifData.erase(exifData.begin(), exifData.end());

    EXPECT_EQ(0, exifData.count());

}



TEST_F(ExifDataTest_40, SortByKeyDoesNotChangeCount_40) {

    ExifKey key1("Exif.Image.Artist");

    Value* pValue1 = new StringValue("Artist Name");

    ExifKey key2("Exif.Image.Copyright");

    Value* pValue2 = new StringValue("Copyright Info");

    exifData.add(key1, pValue1);

    exifData.add(key2, pValue2);

    size_t countBeforeSort = exifData.count();

    exifData.sortByKey();

    EXPECT_EQ(countBeforeSort, exifData.count());

}



TEST_F(ExifDataTest_40, SortByTagDoesNotChangeCount_40) {

    ExifKey key1("Exif.Image.Artist");

    Value* pValue1 = new StringValue("Artist Name");

    ExifKey key2("Exif.Image.Copyright");

    Value* pValue2 = new StringValue("Copyright Info");

    exifData.add(key1, pValue1);

    exifData.add(key2, pValue2);

    size_t countBeforeSort = exifData.count();

    exifData.sortByTag();

    EXPECT_EQ(countBeforeSort, exifData.count());

}
