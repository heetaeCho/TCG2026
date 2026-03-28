#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class ExifDataTest_783 : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(ExifDataTest_783, EraseSingleElementNormalOperation_783) {

    // Add an element to the ExifData

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("John Doe");

    exifData.add(key, value);



    // Get iterator to the added element

    auto it = exifData.findKey(key);

    EXPECT_NE(it, exifData.end());



    // Erase the element

    exifData.erase(it);



    // Verify that the element is removed

    EXPECT_EQ(exifData.empty(), true);

}



TEST_F(ExifDataTest_783, EraseSingleElementBoundaryConditionEmptyList_783) {

    // Try to erase from an empty list

    auto it = exifData.begin();

    EXPECT_EQ(it, exifData.end());



    // Attempting to erase should not cause any issues

    exifData.erase(it);



    // Verify that the list remains empty

    EXPECT_EQ(exifData.empty(), true);

}



TEST_F(ExifDataTest_783, EraseSingleElementBoundaryConditionLastElement_783) {

    // Add an element to the ExifData

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("John Doe");

    exifData.add(key, value);



    // Get iterator to the last element

    auto it = std::prev(exifData.end());



    // Erase the element

    exifData.erase(it);



    // Verify that the element is removed and list is empty

    EXPECT_EQ(exifData.empty(), true);

}



TEST_F(ExifDataTest_783, EraseSingleElementBoundaryConditionFirstElement_783) {

    // Add multiple elements to the ExifData

    ExifKey key1("Exif.Image.Artist");

    Value* value1 = new StringValue("John Doe");

    exifData.add(key1, value1);



    ExifKey key2("Exif.Image.Copyright");

    Value* value2 = new StringValue("Copyright 2023");

    exifData.add(key2, value2);



    // Get iterator to the first element

    auto it = exifData.begin();



    // Erase the element

    exifData.erase(it);



    // Verify that the first element is removed and only one element remains

    EXPECT_EQ(exifData.count(), 1);

}



TEST_F(ExifDataTest_783, EraseSingleElementBoundaryConditionMiddleElement_783) {

    // Add multiple elements to the ExifData

    ExifKey key1("Exif.Image.Artist");

    Value* value1 = new StringValue("John Doe");

    exifData.add(key1, value1);



    ExifKey key2("Exif.Image.Copyright");

    Value* value2 = new StringValue("Copyright 2023");

    exifData.add(key2, value2);



    ExifKey key3("Exif.Image.Model");

    Value* value3 = new StringValue("Camera Model X");

    exifData.add(key3, value3);



    // Get iterator to the middle element

    auto it = std::next(exifData.begin());



    // Erase the element

    exifData.erase(it);



    // Verify that the middle element is removed and two elements remain

    EXPECT_EQ(exifData.count(), 2);

}



TEST_F(ExifDataTest_783, EraseSingleElementBoundaryConditionInvalidIterator_783) {

    // Add an element to the ExifData

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("John Doe");

    exifData.add(key, value);



    // Get invalid iterator (end())

    auto it = exifData.end();



    // Erase the element using an invalid iterator

    EXPECT_THROW(exifData.erase(it), std::out_of_range);  // Assuming erase with end() throws out_of_range



    // Verify that the list remains unchanged

    EXPECT_EQ(exifData.count(), 1);

}
