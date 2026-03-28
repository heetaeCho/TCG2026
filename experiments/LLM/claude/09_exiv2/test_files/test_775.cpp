#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>
#include <string>

using namespace Exiv2;

class ExifDataTest_775 : public ::testing::Test {
protected:
    ExifData exifData_;
};

// Test that a newly created ExifData is empty
TEST_F(ExifDataTest_775, DefaultConstructedIsEmpty_775) {
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test that begin() == end() for empty ExifData
TEST_F(ExifDataTest_775, BeginEqualsEndWhenEmpty_775) {
    EXPECT_TRUE(exifData_.begin() == exifData_.end());
}

// Test operator[] creates a new entry when key doesn't exist
TEST_F(ExifDataTest_775, OperatorBracketCreatesNewEntry_775) {
    exifData_["Exif.Image.Make"];
    EXPECT_FALSE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test operator[] returns the same entry when called twice with the same key
TEST_F(ExifDataTest_775, OperatorBracketReturnsSameEntryForSameKey_775) {
    Exifdatum& d1 = exifData_["Exif.Image.Make"];
    Exifdatum& d2 = exifData_["Exif.Image.Make"];
    EXPECT_EQ(&d1, &d2);
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test operator[] with different keys creates distinct entries
TEST_F(ExifDataTest_775, OperatorBracketDifferentKeysCreateDistinctEntries_775) {
    exifData_["Exif.Image.Make"];
    exifData_["Exif.Image.Model"];
    EXPECT_EQ(exifData_.count(), 2u);
}

// Test that operator[] returns an Exifdatum with the correct key
TEST_F(ExifDataTest_775, OperatorBracketCorrectKey_775) {
    Exifdatum& datum = exifData_["Exif.Image.Make"];
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test add with ExifKey and Value pointer
TEST_F(ExifDataTest_775, AddWithKeyAndValue_775) {
    ExifKey key("Exif.Image.Make");
    Value::UniquePtr val = Value::create(asciiString);
    val->read("Canon");
    exifData_.add(key, val.get());
    EXPECT_EQ(exifData_.count(), 1u);
    auto it = exifData_.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_TRUE(it != exifData_.end());
    EXPECT_EQ(it->toString(), "Canon");
}

// Test add with Exifdatum
TEST_F(ExifDataTest_775, AddWithExifdatum_775) {
    Exifdatum datum(ExifKey("Exif.Image.Model"));
    exifData_.add(datum);
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test findKey returns end() when key not found
TEST_F(ExifDataTest_775, FindKeyNotFound_775) {
    auto it = exifData_.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_TRUE(it == exifData_.end());
}

// Test findKey returns valid iterator when key is found
TEST_F(ExifDataTest_775, FindKeyFound_775) {
    exifData_["Exif.Image.Make"];
    auto it = exifData_.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_TRUE(it != exifData_.end());
    EXPECT_EQ(it->key(), "Exif.Image.Make");
}

// Test clear empties the data
TEST_F(ExifDataTest_775, ClearRemovesAllEntries_775) {
    exifData_["Exif.Image.Make"];
    exifData_["Exif.Image.Model"];
    EXPECT_EQ(exifData_.count(), 2u);
    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test erase single element
TEST_F(ExifDataTest_775, EraseSingleElement_775) {
    exifData_["Exif.Image.Make"];
    exifData_["Exif.Image.Model"];
    EXPECT_EQ(exifData_.count(), 2u);
    auto it = exifData_.findKey(ExifKey("Exif.Image.Make"));
    exifData_.erase(it);
    EXPECT_EQ(exifData_.count(), 1u);
    EXPECT_TRUE(exifData_.findKey(ExifKey("Exif.Image.Make")) == exifData_.end());
}

// Test erase range
TEST_F(ExifDataTest_775, EraseRange_775) {
    exifData_["Exif.Image.Make"];
    exifData_["Exif.Image.Model"];
    exifData_["Exif.Image.Orientation"];
    EXPECT_EQ(exifData_.count(), 3u);
    exifData_.erase(exifData_.begin(), exifData_.end());
    EXPECT_TRUE(exifData_.empty());
}

// Test sortByKey doesn't crash and maintains data
TEST_F(ExifDataTest_775, SortByKeyMaintainsCount_775) {
    exifData_["Exif.Image.Model"];
    exifData_["Exif.Image.Make"];
    exifData_["Exif.Image.Orientation"];
    size_t countBefore = exifData_.count();
    exifData_.sortByKey();
    EXPECT_EQ(exifData_.count(), countBefore);
}

// Test sortByTag doesn't crash and maintains data
TEST_F(ExifDataTest_775, SortByTagMaintainsCount_775) {
    exifData_["Exif.Image.Model"];
    exifData_["Exif.Image.Make"];
    exifData_["Exif.Image.Orientation"];
    size_t countBefore = exifData_.count();
    exifData_.sortByTag();
    EXPECT_EQ(exifData_.count(), countBefore);
}

// Test sortByKey actually sorts
TEST_F(ExifDataTest_775, SortByKeyOrdersEntries_775) {
    exifData_["Exif.Image.Model"];
    exifData_["Exif.Image.Make"];
    exifData_.sortByKey();
    auto it = exifData_.begin();
    std::string firstKey = it->key();
    ++it;
    std::string secondKey = it->key();
    EXPECT_LE(firstKey, secondKey);
}

// Test operator[] after clear re-creates entries
TEST_F(ExifDataTest_775, OperatorBracketAfterClear_775) {
    exifData_["Exif.Image.Make"];
    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    exifData_["Exif.Image.Make"];
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test const findKey on const ExifData
TEST_F(ExifDataTest_775, ConstFindKey_775) {
    exifData_["Exif.Image.Make"];
    const ExifData& constRef = exifData_;
    auto it = constRef.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_TRUE(it != constRef.end());
    EXPECT_EQ(it->key(), "Exif.Image.Make");
}

// Test const findKey returns end when not found
TEST_F(ExifDataTest_775, ConstFindKeyNotFound_775) {
    const ExifData& constRef = exifData_;
    auto it = constRef.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_TRUE(it == constRef.end());
}

// Test empty on const reference
TEST_F(ExifDataTest_775, ConstEmpty_775) {
    const ExifData& constRef = exifData_;
    EXPECT_TRUE(constRef.empty());
}

// Test count on const reference
TEST_F(ExifDataTest_775, ConstCount_775) {
    exifData_["Exif.Image.Make"];
    const ExifData& constRef = exifData_;
    EXPECT_EQ(constRef.count(), 1u);
}

// Test adding multiple items and iterating
TEST_F(ExifDataTest_775, IterateMultipleEntries_775) {
    exifData_["Exif.Image.Make"];
    exifData_["Exif.Image.Model"];
    exifData_["Exif.Image.Orientation"];
    size_t count = 0;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 3u);
}

// Test erase returns valid iterator
TEST_F(ExifDataTest_775, EraseReturnsValidIterator_775) {
    exifData_["Exif.Image.Make"];
    exifData_["Exif.Image.Model"];
    auto it = exifData_.erase(exifData_.begin());
    // After erasing the first element, iterator should point to the remaining element or end
    EXPECT_EQ(exifData_.count(), 1u);
    if (it != exifData_.end()) {
        EXPECT_FALSE(it->key().empty());
    }
}

// Test erase range returns valid iterator
TEST_F(ExifDataTest_775, EraseRangeReturnsIterator_775) {
    exifData_["Exif.Image.Make"];
    exifData_["Exif.Image.Model"];
    exifData_["Exif.Image.Orientation"];
    auto beg = exifData_.begin();
    auto mid = beg;
    ++mid;
    auto it = exifData_.erase(beg, mid);
    EXPECT_EQ(exifData_.count(), 2u);
}

// Test that adding value via operator[] and then setting it works
TEST_F(ExifDataTest_775, OperatorBracketSetValue_775) {
    Exifdatum& datum = exifData_["Exif.Image.Make"];
    datum.setValue("Nikon");
    auto it = exifData_.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_TRUE(it != exifData_.end());
    EXPECT_EQ(it->toString(), "Nikon");
}

// Test that adding a null value pointer via add doesn't crash
TEST_F(ExifDataTest_775, AddWithNullValue_775) {
    ExifKey key("Exif.Image.Make");
    exifData_.add(key, nullptr);
    EXPECT_EQ(exifData_.count(), 1u);
}
