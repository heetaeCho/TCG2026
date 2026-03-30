#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class ExifDataTest_39 : public ::testing::Test {

protected:

    ExifData exif_data;

};



TEST_F(ExifDataTest_39, EmptyInitially_39) {

    EXPECT_TRUE(exif_data.empty());

}



TEST_F(ExifDataTest_39, CountInitiallyZero_39) {

    EXPECT_EQ(exif_data.count(), 0);

}



TEST_F(ExifDataTest_39, AddIncreasesCount_39) {

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("John Doe");

    exif_data.add(key, value);

    EXPECT_EQ(exif_data.count(), 1);

    delete value;

}



TEST_F(ExifDataTest_39, AddExifdatumIncreasesCount_39) {

    Exifdatum datum("Exif.Image.Artist", "John Doe");

    exif_data.add(datum);

    EXPECT_EQ(exif_data.count(), 1);

}



TEST_F(ExifDataTest_39, ClearResetsCount_39) {

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("John Doe");

    exif_data.add(key, value);

    exif_data.clear();

    EXPECT_EQ(exif_data.count(), 0);

    delete value;

}



TEST_F(ExifDataTest_39, FindKeyReturnsEndIfNotFound_39) {

    ExifKey key("Exif.Image.Artist");

    EXPECT_EQ(exif_data.findKey(key), exif_data.end());

}



TEST_F(ExifDataTest_39, FindKeyFindsAddedElement_39) {

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("John Doe");

    exif_data.add(key, value);

    EXPECT_NE(exif_data.findKey(key), exif_data.end());

    delete value;

}



TEST_F(ExifDataTest_39, EraseSingleElementDecreasesCount_39) {

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("John Doe");

    exif_data.add(key, value);

    exif_data.erase(exif_data.begin());

    EXPECT_EQ(exif_data.count(), 0);

    delete value;

}



TEST_F(ExifDataTest_39, EraseRangeDecreasesCount_39) {

    ExifKey key1("Exif.Image.Artist");

    Value* value1 = new StringValue("John Doe");

    exif_data.add(key1, value1);



    ExifKey key2("Exif.Image.Copyright");

    Value* value2 = new StringValue("Copyright 2023");

    exif_data.add(key2, value2);



    exif_data.erase(exif_data.begin(), exif_data.end());

    EXPECT_EQ(exif_data.count(), 0);

    delete value1;

    delete value2;

}



TEST_F(ExifDataTest_39, SortByKeyDoesNotChangeCount_39) {

    ExifKey key1("Exif.Image.Artist");

    Value* value1 = new StringValue("John Doe");

    exif_data.add(key1, value1);



    ExifKey key2("Exif.Image.Copyright");

    Value* value2 = new StringValue("Copyright 2023");

    exif_data.add(key2, value2);



    size_t count_before = exif_data.count();

    exif_data.sortByKey();

    EXPECT_EQ(exif_data.count(), count_before);

    delete value1;

    delete value2;

}



TEST_F(ExifDataTest_39, SortByTagDoesNotChangeCount_39) {

    ExifKey key1("Exif.Image.Artist");

    Value* value1 = new StringValue("John Doe");

    exif_data.add(key1, value1);



    ExifKey key2("Exif.Image.Copyright");

    Value* value2 = new StringValue("Copyright 2023");

    exif_data.add(key2, value2);



    size_t count_before = exif_data.count();

    exif_data.sortByTag();

    EXPECT_EQ(exif_data.count(), count_before);

    delete value1;

    delete value2;

}



TEST_F(ExifDataTest_39, OperatorBracketReturnsAddedElement_39) {

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("John Doe");

    exif_data.add(key, value);

    EXPECT_EQ(exif_data[key].value(), "John Doe");

    delete value;

}



TEST_F(ExifDataTest_39, EmptyAfterClear_39) {

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("John Doe");

    exif_data.add(key, value);

    exif_data.clear();

    EXPECT_TRUE(exif_data.empty());

    delete value;

}
