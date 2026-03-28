#include <gtest/gtest.h>
#include "exiv2/exif.hpp"

using namespace Exiv2;

class ExifDataTest_39 : public ::testing::Test {
protected:
    ExifData exifData;
};

// TEST_ID: 39
TEST_F(ExifDataTest_39, BeginReturnsIterator_39) {
    // Normal operation: Test that the begin() method returns a valid iterator
    auto it = exifData.begin();
    EXPECT_TRUE(it == exifData.exifMetadata_.begin());
}

// TEST_ID: 40
TEST_F(ExifDataTest_39, EmptyReturnsTrueInitially_40) {
    // Boundary condition: Check if the ExifData is initially empty
    EXPECT_TRUE(exifData.empty());
}

// TEST_ID: 41
TEST_F(ExifDataTest_39, AddKeyValueAddsExifdatum_41) {
    // Normal operation: Test that adding an ExifKey-Value pair works
    ExifKey key("SampleKey");
    Value value(42);
    exifData.add(key, &value);
    
    // Verify that the size increases
    EXPECT_EQ(exifData.count(), 1);
}

// TEST_ID: 42
TEST_F(ExifDataTest_39, AddExifdatumAddsToExifData_42) {
    // Normal operation: Test that adding an Exifdatum works
    Exifdatum datum;
    exifData.add(datum);
    
    // Verify the count is increased
    EXPECT_EQ(exifData.count(), 1);
}

// TEST_ID: 43
TEST_F(ExifDataTest_39, FindKeyReturnsCorrectIterator_43) {
    // Normal operation: Test that findKey() returns an iterator for a valid key
    ExifKey key("SampleKey");
    Exifdatum datum;
    exifData.add(key, &datum);
    
    auto it = exifData.findKey(key);
    EXPECT_TRUE(it != exifData.end());
}

// TEST_ID: 44
TEST_F(ExifDataTest_39, EraseRemovesElement_44) {
    // Normal operation: Test that erase() removes an element from the ExifData
    ExifKey key("SampleKey");
    Exifdatum datum;
    exifData.add(key, &datum);
    
    // Erase the element
    auto it = exifData.findKey(key);
    exifData.erase(it);
    
    // Verify that the count is now zero
    EXPECT_EQ(exifData.count(), 0);
}

// TEST_ID: 45
TEST_F(ExifDataTest_39, EraseRangeRemovesElements_45) {
    // Normal operation: Test that erase() with a range removes elements
    Exifdatum datum1, datum2;
    ExifKey key1("SampleKey1"), key2("SampleKey2");
    
    exifData.add(key1, &datum1);
    exifData.add(key2, &datum2);
    
    auto begin = exifData.begin();
    auto end = exifData.end();
    exifData.erase(begin, end);
    
    // Verify that the count is zero
    EXPECT_EQ(exifData.count(), 0);
}

// TEST_ID: 46
TEST_F(ExifDataTest_39, ClearRemovesAllElements_46) {
    // Normal operation: Test that clear() removes all elements
    ExifKey key("SampleKey");
    Exifdatum datum;
    exifData.add(key, &datum);
    
    exifData.clear();
    
    // Verify that the count is zero after clearing
    EXPECT_EQ(exifData.count(), 0);
}

// TEST_ID: 47
TEST_F(ExifDataTest_39, SortByKeySortsElements_47) {
    // Normal operation: Test that sortByKey() works correctly
    ExifKey key1("BKey"), key2("AKey");
    Exifdatum datum1, datum2;
    
    exifData.add(key1, &datum1);
    exifData.add(key2, &datum2);
    
    exifData.sortByKey();
    
    // Verify that the first key is "AKey" after sorting
    auto it = exifData.begin();
    EXPECT_EQ(it->first, "AKey");
}

// TEST_ID: 48
TEST_F(ExifDataTest_39, SortByTagSortsElements_48) {
    // Normal operation: Test that sortByTag() works correctly
    ExifKey key1("BKey"), key2("AKey");
    Exifdatum datum1, datum2;
    
    exifData.add(key1, &datum1);
    exifData.add(key2, &datum2);
    
    exifData.sortByTag();
    
    // Verify the sorted order of tags
    auto it = exifData.begin();
    EXPECT_EQ(it->first, "AKey");
}

// TEST_ID: 49
TEST_F(ExifDataTest_39, CountReturnsCorrectSize_49) {
    // Boundary condition: Test that count() returns the correct size
    EXPECT_EQ(exifData.count(), 0);
    ExifKey key("SampleKey");
    Value value(42);
    exifData.add(key, &value);
    EXPECT_EQ(exifData.count(), 1);
}

// TEST_ID: 50
TEST_F(ExifDataTest_39, EraseInvalidIteratorReturnsEnd_50) {
    // Exceptional case: Test that erase with an invalid iterator does nothing
    auto it = exifData.begin();
    exifData.erase(it);
    
    // Verify that the count is still 0
    EXPECT_EQ(exifData.count(), 0);
}