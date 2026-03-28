#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <exiv2/tags.hpp>
#include <string>

using namespace Exiv2;

class ExifDataTest_782 : public ::testing::Test {
protected:
    ExifData exifData_;

    void SetUp() override {
        exifData_.clear();
    }
};

// Test that a newly created ExifData is empty
TEST_F(ExifDataTest_782, DefaultConstructorCreatesEmptyData_782) {
    ExifData data;
    EXPECT_TRUE(data.empty());
    EXPECT_EQ(data.count(), 0u);
}

// Test that clear() removes all entries
TEST_F(ExifDataTest_782, ClearRemovesAllEntries_782) {
    exifData_["Exif.Image.Make"] = "TestMake";
    exifData_["Exif.Image.Model"] = "TestModel";
    ASSERT_FALSE(exifData_.empty());

    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test operator[] adds new entry
TEST_F(ExifDataTest_782, OperatorBracketAddsEntry_782) {
    exifData_["Exif.Image.Make"] = "Canon";
    EXPECT_FALSE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test operator[] retrieves existing entry
TEST_F(ExifDataTest_782, OperatorBracketRetrievesExistingEntry_782) {
    exifData_["Exif.Image.Make"] = "Canon";
    std::string val = exifData_["Exif.Image.Make"].toString();
    EXPECT_EQ(val, "Canon");
}

// Test adding multiple entries increases count
TEST_F(ExifDataTest_782, AddMultipleEntriesIncreasesCount_782) {
    exifData_["Exif.Image.Make"] = "Canon";
    exifData_["Exif.Image.Model"] = "EOS 5D";
    exifData_["Exif.Image.Orientation"] = uint16_t(1);
    EXPECT_EQ(exifData_.count(), 3u);
}

// Test add with ExifKey and Value
TEST_F(ExifDataTest_782, AddWithKeyAndValue_782) {
    ExifKey key("Exif.Image.Make");
    Value::UniquePtr value = Value::create(asciiString);
    value->read("Nikon");
    exifData_.add(key, value.get());
    EXPECT_EQ(exifData_.count(), 1u);

    auto it = exifData_.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "Nikon");
}

// Test add with Exifdatum
TEST_F(ExifDataTest_782, AddWithExifdatum_782) {
    exifData_["Exif.Image.Make"] = "Sony";
    Exifdatum datum = *exifData_.begin();

    ExifData other;
    other.add(datum);
    EXPECT_EQ(other.count(), 1u);
    EXPECT_EQ(other.begin()->toString(), "Sony");
}

// Test findKey returns end when key not found
TEST_F(ExifDataTest_782, FindKeyReturnsEndWhenNotFound_782) {
    exifData_["Exif.Image.Make"] = "Canon";
    auto it = exifData_.findKey(ExifKey("Exif.Image.Model"));
    EXPECT_EQ(it, exifData_.end());
}

// Test findKey returns correct iterator when key found
TEST_F(ExifDataTest_782, FindKeyReturnsCorrectIterator_782) {
    exifData_["Exif.Image.Make"] = "Canon";
    exifData_["Exif.Image.Model"] = "EOS R5";

    auto it = exifData_.findKey(ExifKey("Exif.Image.Model"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "EOS R5");
}

// Test erase single element
TEST_F(ExifDataTest_782, EraseSingleElement_782) {
    exifData_["Exif.Image.Make"] = "Canon";
    exifData_["Exif.Image.Model"] = "EOS R5";
    ASSERT_EQ(exifData_.count(), 2u);

    auto it = exifData_.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData_.end());
    exifData_.erase(it);
    EXPECT_EQ(exifData_.count(), 1u);

    auto result = exifData_.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_EQ(result, exifData_.end());
}

// Test erase range
TEST_F(ExifDataTest_782, EraseRangeRemovesElements_782) {
    exifData_["Exif.Image.Make"] = "Canon";
    exifData_["Exif.Image.Model"] = "EOS R5";
    exifData_["Exif.Image.Orientation"] = uint16_t(1);
    ASSERT_EQ(exifData_.count(), 3u);

    auto result = exifData_.erase(exifData_.begin(), exifData_.end());
    EXPECT_EQ(result, exifData_.end());
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test erase empty range does nothing
TEST_F(ExifDataTest_782, EraseEmptyRangeDoesNothing_782) {
    exifData_["Exif.Image.Make"] = "Canon";
    ASSERT_EQ(exifData_.count(), 1u);

    auto it = exifData_.begin();
    auto result = exifData_.erase(it, it);
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test erase partial range
TEST_F(ExifDataTest_782, ErasePartialRange_782) {
    exifData_["Exif.Image.Make"] = "Canon";
    exifData_["Exif.Image.Model"] = "EOS R5";
    exifData_["Exif.Image.Orientation"] = uint16_t(1);
    ASSERT_EQ(exifData_.count(), 3u);

    auto beg = exifData_.begin();
    auto end = beg;
    ++end;
    ++end; // erase first two

    exifData_.erase(beg, end);
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test begin and end iterators on empty container
TEST_F(ExifDataTest_782, BeginEqualsEndOnEmptyData_782) {
    EXPECT_EQ(exifData_.begin(), exifData_.end());
}

// Test begin and end iterators on non-empty container
TEST_F(ExifDataTest_782, BeginNotEqualsEndOnNonEmptyData_782) {
    exifData_["Exif.Image.Make"] = "Canon";
    EXPECT_NE(exifData_.begin(), exifData_.end());
}

// Test empty returns true for empty data
TEST_F(ExifDataTest_782, EmptyReturnsTrueForEmptyData_782) {
    EXPECT_TRUE(exifData_.empty());
}

// Test empty returns false for non-empty data
TEST_F(ExifDataTest_782, EmptyReturnsFalseForNonEmptyData_782) {
    exifData_["Exif.Image.Make"] = "Canon";
    EXPECT_FALSE(exifData_.empty());
}

// Test count reflects number of entries
TEST_F(ExifDataTest_782, CountReflectsNumberOfEntries_782) {
    EXPECT_EQ(exifData_.count(), 0u);
    exifData_["Exif.Image.Make"] = "Canon";
    EXPECT_EQ(exifData_.count(), 1u);
    exifData_["Exif.Image.Model"] = "EOS R5";
    EXPECT_EQ(exifData_.count(), 2u);
}

// Test sortByKey does not change count
TEST_F(ExifDataTest_782, SortByKeyPreservesCount_782) {
    exifData_["Exif.Image.Model"] = "EOS R5";
    exifData_["Exif.Image.Make"] = "Canon";
    exifData_["Exif.Image.Orientation"] = uint16_t(1);

    size_t countBefore = exifData_.count();
    exifData_.sortByKey();
    EXPECT_EQ(exifData_.count(), countBefore);
}

// Test sortByTag does not change count
TEST_F(ExifDataTest_782, SortByTagPreservesCount_782) {
    exifData_["Exif.Image.Model"] = "EOS R5";
    exifData_["Exif.Image.Make"] = "Canon";
    exifData_["Exif.Image.Orientation"] = uint16_t(1);

    size_t countBefore = exifData_.count();
    exifData_.sortByTag();
    EXPECT_EQ(exifData_.count(), countBefore);
}

// Test sortByKey on empty data does not crash
TEST_F(ExifDataTest_782, SortByKeyOnEmptyDataDoesNotCrash_782) {
    EXPECT_NO_THROW(exifData_.sortByKey());
}

// Test sortByTag on empty data does not crash
TEST_F(ExifDataTest_782, SortByTagOnEmptyDataDoesNotCrash_782) {
    EXPECT_NO_THROW(exifData_.sortByTag());
}

// Test clear on already empty data
TEST_F(ExifDataTest_782, ClearOnEmptyDataDoesNotCrash_782) {
    EXPECT_NO_THROW(exifData_.clear());
    EXPECT_TRUE(exifData_.empty());
}

// Test erase returns valid iterator pointing to next element
TEST_F(ExifDataTest_782, EraseSingleReturnsNextIterator_782) {
    exifData_["Exif.Image.Make"] = "Canon";
    exifData_["Exif.Image.Model"] = "EOS R5";

    auto it = exifData_.begin();
    auto next = exifData_.erase(it);
    // After erasing first element, next should point to the remaining element or end
    EXPECT_EQ(exifData_.count(), 1u);
    if (next != exifData_.end()) {
        EXPECT_NE(next->toString().size(), 0u);
    }
}

// Test erasing last element makes data empty
TEST_F(ExifDataTest_782, EraseLastElementMakesEmpty_782) {
    exifData_["Exif.Image.Make"] = "Canon";
    ASSERT_EQ(exifData_.count(), 1u);

    auto it = exifData_.begin();
    auto result = exifData_.erase(it);
    EXPECT_EQ(result, exifData_.end());
    EXPECT_TRUE(exifData_.empty());
}

// Test const findKey on non-empty data
TEST_F(ExifDataTest_782, ConstFindKey_782) {
    exifData_["Exif.Image.Make"] = "Canon";
    const ExifData& constRef = exifData_;

    auto it = constRef.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, constRef.end());
    EXPECT_EQ(it->toString(), "Canon");
}

// Test const findKey returns end when not found
TEST_F(ExifDataTest_782, ConstFindKeyNotFound_782) {
    const ExifData& constRef = exifData_;
    auto it = constRef.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_EQ(it, constRef.end());
}

// Test operator[] with same key updates value rather than adding duplicate
TEST_F(ExifDataTest_782, OperatorBracketSameKeyUpdatesValue_782) {
    exifData_["Exif.Image.Make"] = "Canon";
    exifData_["Exif.Image.Make"] = "Nikon";

    // operator[] should find the existing entry and update it
    auto it = exifData_.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "Nikon");
}

// Test erase range where beg equals end (no-op)
TEST_F(ExifDataTest_782, EraseRangeBeginEqualsEnd_782) {
    exifData_["Exif.Image.Make"] = "Canon";
    exifData_["Exif.Image.Model"] = "EOS R5";

    auto beg = exifData_.begin();
    ++beg;
    auto result = exifData_.erase(beg, beg);
    EXPECT_EQ(exifData_.count(), 2u);
}

// Test iteration through all elements
TEST_F(ExifDataTest_782, IterateThroughAllElements_782) {
    exifData_["Exif.Image.Make"] = "Canon";
    exifData_["Exif.Image.Model"] = "EOS R5";
    exifData_["Exif.Image.Orientation"] = uint16_t(1);

    size_t count = 0;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 3u);
}
