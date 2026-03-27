#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class ExifDataTest_780 : public ::testing::Test {

protected:

    ExifData exif_data;

};



TEST_F(ExifDataTest_780, SortByKeyOnEmptyData_780) {

    // Arrange & Act

    exif_data.sortByKey();



    // Assert

    EXPECT_TRUE(exif_data.empty());

}



TEST_F(ExifDataTest_780, SortByKeyWithSingleEntry_780) {

    // Arrange

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("John Doe");

    exif_data.add(key, value);



    // Act

    exif_data.sortByKey();



    // Assert

    EXPECT_EQ(exif_data.count(), 1);

}



TEST_F(ExifDataTest_780, SortByKeyWithMultipleEntries_780) {

    // Arrange

    ExifKey key1("Exif.Image.Artist");

    Value* value1 = new StringValue("John Doe");

    exif_data.add(key1, value1);



    ExifKey key2("Exif.Image.Make");

    Value* value2 = new StringValue("Canon");

    exif_data.add(key2, value2);



    // Act

    exif_data.sortByKey();



    // Assert

    auto it = exif_data.begin();

    EXPECT_EQ((*it).key(), "Exif.Image.Artist");

    ++it;

    EXPECT_EQ((*it).key(), "Exif.Image.Make");

}



TEST_F(ExifDataTest_780, SortByKeyPreservesCount_780) {

    // Arrange

    ExifKey key1("Exif.Image.Artist");

    Value* value1 = new StringValue("John Doe");

    exif_data.add(key1, value1);



    ExifKey key2("Exif.Image.Make");

    Value* value2 = new StringValue("Canon");

    exif_data.add(key2, value2);



    size_t initial_count = exif_data.count();



    // Act

    exif_data.sortByKey();



    // Assert

    EXPECT_EQ(exif_data.count(), initial_count);

}



TEST_F(ExifDataTest_780, SortByKeyDoesNotChangeValues_780) {

    // Arrange

    ExifKey key1("Exif.Image.Artist");

    Value* value1 = new StringValue("John Doe");

    exif_data.add(key1, value1);



    ExifKey key2("Exif.Image.Make");

    Value* value2 = new StringValue("Canon");

    exif_data.add(key2, value2);



    // Act

    exif_data.sortByKey();



    // Assert

    EXPECT_EQ((*exif_data.findKey(key1)).value().toString(), "John Doe");

    EXPECT_EQ((*exif_data.findKey(key2)).value().toString(), "Canon");

}
