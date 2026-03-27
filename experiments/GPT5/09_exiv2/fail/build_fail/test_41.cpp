#include <gtest/gtest.h>
#include "exiv2/exif.hpp"

namespace Exiv2 {

class ExifDataTest : public ::testing::Test {
protected:
    ExifData exifData;
};

TEST_F(ExifDataTest, EmptyReturnsTrueWhenMetadataIsEmpty_41) {
    // Test case for when the ExifData is empty
    EXPECT_TRUE(exifData.empty());
}

TEST_F(ExifDataTest, EmptyReturnsFalseWhenMetadataIsNotEmpty_42) {
    // Test case for when the ExifData has data
    ExifKey key("key");
    Value* value = nullptr; // assuming a Value* type
    exifData.add(key, value);
    EXPECT_FALSE(exifData.empty());
}

TEST_F(ExifDataTest, CountReturnsZeroWhenEmpty_43) {
    // Test case for the count method when the ExifData is empty
    EXPECT_EQ(exifData.count(), 0);
}

TEST_F(ExifDataTest, CountReturnsNonZeroWhenNotEmpty_44) {
    // Test case for the count method when ExifData has items
    ExifKey key("key");
    Value* value = nullptr; // assuming a Value* type
    exifData.add(key, value);
    EXPECT_GT(exifData.count(), 0);
}

TEST_F(ExifDataTest, FindKeyReturnsEndIfKeyNotFound_45) {
    // Test case for the findKey method when key is not found
    ExifKey key("nonexistent_key");
    EXPECT_EQ(exifData.findKey(key), exifData.end());
}

TEST_F(ExifDataTest, FindKeyReturnsValidIteratorIfKeyFound_46) {
    // Test case for the findKey method when key is found
    ExifKey key("existing_key");
    Value* value = nullptr; // assuming a Value* type
    exifData.add(key, value);
    auto it = exifData.findKey(key);
    EXPECT_NE(it, exifData.end());
}

TEST_F(ExifDataTest, ClearEmptiesExifData_47) {
    // Test case for the clear method
    ExifKey key("key");
    Value* value = nullptr; // assuming a Value* type
    exifData.add(key, value);
    exifData.clear();
    EXPECT_TRUE(exifData.empty());
}

TEST_F(ExifDataTest, SortByKeyDoesNotCrash_48) {
    // Test case for the sortByKey method
    EXPECT_NO_THROW(exifData.sortByKey());
}

TEST_F(ExifDataTest, SortByTagDoesNotCrash_49) {
    // Test case for the sortByTag method
    EXPECT_NO_THROW(exifData.sortByTag());
}

TEST_F(ExifDataTest, EraseRemovesElement_50) {
    // Test case for the erase method
    ExifKey key("key");
    Value* value = nullptr; // assuming a Value* type
    exifData.add(key, value);
    auto it = exifData.begin();
    exifData.erase(it);
    EXPECT_EQ(exifData.count(), 0);
}

TEST_F(ExifDataTest, EraseRangeRemovesElements_51) {
    // Test case for the erase method with range
    ExifKey key1("key1"), key2("key2");
    Value* value1 = nullptr, *value2 = nullptr; // assuming Value* type
    exifData.add(key1, value1);
    exifData.add(key2, value2);
    auto it1 = exifData.begin();
    auto it2 = std::next(it1);
    exifData.erase(it1, it2);
    EXPECT_EQ(exifData.count(), 1);
}

}  // namespace Exiv2