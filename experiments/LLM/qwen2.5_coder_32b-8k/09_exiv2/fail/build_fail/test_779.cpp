#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class ExifDataTest_779 : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(ExifDataTest_779, ClearRemovesAllEntries_779) {

    // Assuming add method works correctly and we can add entries to test clear functionality

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("TestArtist");

    exifData.add(key, value);



    exifData.clear();



    EXPECT_TRUE(exifData.empty());

}



TEST_F(ExifDataTest_779, EmptyReturnsTrueInitially_779) {

    EXPECT_TRUE(exifData.empty());

}



TEST_F(ExifDataTest_779, CountReturnsZeroInitially_779) {

    EXPECT_EQ(0, exifData.count());

}



TEST_F(ExifDataTest_779, AddIncreasesCount_779) {

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("TestArtist");

    exifData.add(key, value);



    EXPECT_EQ(1, exifData.count());

}



TEST_F(ExifDataTest_779, AddSameKeyDoesNotDuplicateCount_779) {

    ExifKey key("Exif.Image.Artist");

    Value* value1 = new StringValue("TestArtist1");

    Value* value2 = new StringValue("TestArtist2");



    exifData.add(key, value1);

    exifData[key] = *value2; // Overwrite the existing entry



    EXPECT_EQ(1, exifData.count());

}



TEST_F(ExifDataTest_779, EraseSingleElementReducesCount_779) {

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("TestArtist");

    exifData.add(key, value);



    auto it = exifData.findKey(key);

    exifData.erase(it);



    EXPECT_EQ(0, exifData.count());

}



TEST_F(ExifDataTest_779, EraseRangeReducesCount_779) {

    ExifKey key1("Exif.Image.Artist");

    ExifKey key2("Exif.Image.Copyright");

    Value* value1 = new StringValue("TestArtist");

    Value* value2 = new StringValue("TestCopyright");



    exifData.add(key1, value1);

    exifData.add(key2, value2);



    exifData.erase(exifData.begin(), exifData.end());



    EXPECT_EQ(0, exifData.count());

}



TEST_F(ExifDataTest_779, FindKeyReturnsValidIteratorWhenFound_779) {

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("TestArtist");

    exifData.add(key, value);



    auto it = exifData.findKey(key);

    EXPECT_NE(it, exifData.end());

}



TEST_F(ExifDataTest_779, FindKeyReturnsEndWhenNotFound_779) {

    ExifKey key("Non.Existing.Key");



    auto it = exifData.findKey(key);

    EXPECT_EQ(it, exifData.end());

}



TEST_F(ExifDataTest_779, SortByKeyDoesNotAffectCount_779) {

    ExifKey key1("Exif.Image.Artist");

    ExifKey key2("Exif.Image.Copyright");

    Value* value1 = new StringValue("TestArtist");

    Value* value2 = new StringValue("TestCopyright");



    exifData.add(key1, value1);

    exifData.add(key2, value2);



    size_t countBeforeSort = exifData.count();

    exifData.sortByKey();



    EXPECT_EQ(countBeforeSort, exifData.count());

}



TEST_F(ExifDataTest_779, SortByTagDoesNotAffectCount_779) {

    ExifKey key1("Exif.Image.Artist");

    ExifKey key2("Exif.Image.Copyright");

    Value* value1 = new StringValue("TestArtist");

    Value* value2 = new StringValue("TestCopyright");



    exifData.add(key1, value1);

    exifData.add(key2, value2);



    size_t countBeforeSort = exifData.count();

    exifData.sortByTag();



    EXPECT_EQ(countBeforeSort, exifData.count());

}
