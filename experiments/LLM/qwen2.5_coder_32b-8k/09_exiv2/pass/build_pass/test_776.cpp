#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/tags.hpp"

#include "exiv2/value.hpp"



namespace {



using namespace Exiv2;



class ExifDataTest_776 : public ::testing::Test {

protected:

    ExifData exifData;

    ExifKey key1{"Exif.Image.Artist"};

    ExifKey key2{"Exif.Image.Copyright"};

    Value* value1 = new StringValue("John Doe");

    Value* value2 = new StringValue("Sample Copyright");

};



TEST_F(ExifDataTest_776, AddSingleEntry_776) {

    exifData.add(key1, value1);

    EXPECT_EQ(exifData.count(), 1u);

}



TEST_F(ExifDataTest_776, AddMultipleEntries_776) {

    exifData.add(key1, value1);

    exifData.add(key2, value2);

    EXPECT_EQ(exifData.count(), 2u);

}



TEST_F(ExifDataTest_776, ClearEntries_776) {

    exifData.add(key1, value1);

    exifData.clear();

    EXPECT_EQ(exifData.count(), 0u);

}



TEST_F(ExifDataTest_776, FindKeyPresent_776) {

    exifData.add(key1, value1);

    auto it = exifData.findKey(key1);

    EXPECT_NE(it, exifData.end());

}



TEST_F(ExifDataTest_776, FindKeyNotPresent_776) {

    auto it = exifData.findKey(key1);

    EXPECT_EQ(it, exifData.end());

}



TEST_F(ExifDataTest_776, BoundaryConditionEmpty_776) {

    EXPECT_TRUE(exifData.empty());

}



TEST_F(ExifDataTest_776, BoundaryConditionNotEmpty_776) {

    exifData.add(key1, value1);

    EXPECT_FALSE(exifData.empty());

}



TEST_F(ExifDataTest_776, EraseSingleEntry_776) {

    exifData.add(key1, value1);

    auto it = exifData.findKey(key1);

    exifData.erase(it);

    EXPECT_EQ(exifData.count(), 0u);

}



TEST_F(ExifDataTest_776, EraseMultipleEntries_776) {

    exifData.add(key1, value1);

    exifData.add(key2, value2);

    auto it1 = exifData.findKey(key1);

    auto it2 = exifData.findKey(key2);

    exifData.erase(it1);

    exifData.erase(it2);

    EXPECT_EQ(exifData.count(), 0u);

}



TEST_F(ExifDataTest_776, SortByKey_776) {

    exifData.add(key2, value2);

    exifData.add(key1, value1);

    exifData.sortByKey();

    auto it = exifData.begin();

    EXPECT_EQ((*it).key(), key1.key());

}



TEST_F(ExifDataTest_776, SortByTag_776) {

    exifData.add(key2, value2);

    exifData.add(key1, value1);

    exifData.sortByTag();

    auto it = exifData.begin();

    EXPECT_EQ((*it).key(), key1.key());

}



}  // namespace
