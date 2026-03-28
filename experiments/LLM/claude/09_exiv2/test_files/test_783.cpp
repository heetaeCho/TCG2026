#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exiv2.hpp>
#include <string>

class ExifDataTest_783 : public ::testing::Test {
protected:
    Exiv2::ExifData exifData_;

    void SetUp() override {
        exifData_.clear();
    }
};

// Test that a newly created ExifData is empty
TEST_F(ExifDataTest_783, DefaultConstructedIsEmpty_783) {
    Exiv2::ExifData data;
    EXPECT_TRUE(data.empty());
    EXPECT_EQ(data.count(), 0u);
}

// Test that begin() == end() for empty container
TEST_F(ExifDataTest_783, BeginEqualsEndWhenEmpty_783) {
    EXPECT_EQ(exifData_.begin(), exifData_.end());
}

// Test adding an element using operator[]
TEST_F(ExifDataTest_783, OperatorBracketAddsElement_783) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    EXPECT_FALSE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test that operator[] retrieves existing element
TEST_F(ExifDataTest_783, OperatorBracketRetrievesExisting_783) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    std::string val = exifData_["Exif.Image.Make"].toString();
    EXPECT_EQ(val, "TestCamera");
}

// Test adding multiple elements
TEST_F(ExifDataTest_783, AddMultipleElements_783) {
    exifData_["Exif.Image.Make"] = "CameraA";
    exifData_["Exif.Image.Model"] = "ModelB";
    exifData_["Exif.Image.Software"] = "SoftwareC";
    EXPECT_EQ(exifData_.count(), 3u);
}

// Test erase single element by position
TEST_F(ExifDataTest_783, EraseSingleElement_783) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    EXPECT_EQ(exifData_.count(), 2u);

    auto it = exifData_.begin();
    auto result = exifData_.erase(it);
    EXPECT_EQ(exifData_.count(), 1u);
    // Result should be a valid iterator (begin or end)
    EXPECT_EQ(result, exifData_.begin());
}

// Test erase returns end() when erasing the last element
TEST_F(ExifDataTest_783, EraseLastElementReturnsEnd_783) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    EXPECT_EQ(exifData_.count(), 1u);

    auto it = exifData_.begin();
    auto result = exifData_.erase(it);
    EXPECT_EQ(result, exifData_.end());
    EXPECT_TRUE(exifData_.empty());
}

// Test erase range
TEST_F(ExifDataTest_783, EraseRange_783) {
    exifData_["Exif.Image.Make"] = "CameraA";
    exifData_["Exif.Image.Model"] = "ModelB";
    exifData_["Exif.Image.Software"] = "SoftwareC";
    EXPECT_EQ(exifData_.count(), 3u);

    auto result = exifData_.erase(exifData_.begin(), exifData_.end());
    EXPECT_EQ(result, exifData_.end());
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test erase range with partial range
TEST_F(ExifDataTest_783, ErasePartialRange_783) {
    exifData_["Exif.Image.Make"] = "CameraA";
    exifData_["Exif.Image.Model"] = "ModelB";
    exifData_["Exif.Image.Software"] = "SoftwareC";
    EXPECT_EQ(exifData_.count(), 3u);

    auto beg = exifData_.begin();
    auto end = exifData_.begin();
    ++end;
    exifData_.erase(beg, end);
    EXPECT_EQ(exifData_.count(), 2u);
}

// Test erase empty range (beg == end) does nothing
TEST_F(ExifDataTest_783, EraseEmptyRangeDoesNothing_783) {
    exifData_["Exif.Image.Make"] = "CameraA";
    EXPECT_EQ(exifData_.count(), 1u);

    auto result = exifData_.erase(exifData_.begin(), exifData_.begin());
    EXPECT_EQ(exifData_.count(), 1u);
    EXPECT_EQ(result, exifData_.begin());
}

// Test clear
TEST_F(ExifDataTest_783, ClearRemovesAll_783) {
    exifData_["Exif.Image.Make"] = "CameraA";
    exifData_["Exif.Image.Model"] = "ModelB";
    EXPECT_EQ(exifData_.count(), 2u);

    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test clear on empty container
TEST_F(ExifDataTest_783, ClearOnEmptyIsNoOp_783) {
    EXPECT_TRUE(exifData_.empty());
    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
}

// Test findKey for existing key
TEST_F(ExifDataTest_783, FindKeyExisting_783) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    Exiv2::ExifKey key("Exif.Image.Make");
    auto it = exifData_.findKey(key);
    EXPECT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "TestCamera");
}

// Test findKey for non-existing key
TEST_F(ExifDataTest_783, FindKeyNonExisting_783) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    Exiv2::ExifKey key("Exif.Image.Model");
    auto it = exifData_.findKey(key);
    EXPECT_EQ(it, exifData_.end());
}

// Test findKey on empty container
TEST_F(ExifDataTest_783, FindKeyOnEmpty_783) {
    Exiv2::ExifKey key("Exif.Image.Make");
    auto it = exifData_.findKey(key);
    EXPECT_EQ(it, exifData_.end());
}

// Test const findKey
TEST_F(ExifDataTest_783, ConstFindKey_783) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    const Exiv2::ExifData& constRef = exifData_;
    Exiv2::ExifKey key("Exif.Image.Make");
    auto it = constRef.findKey(key);
    EXPECT_NE(it, constRef.end());
}

// Test add with ExifKey and Value
TEST_F(ExifDataTest_783, AddWithKeyAndValue_783) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("TestCamera");
    exifData_.add(key, value.get());
    EXPECT_EQ(exifData_.count(), 1u);
    auto it = exifData_.findKey(key);
    EXPECT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "TestCamera");
}

// Test add with Exifdatum
TEST_F(ExifDataTest_783, AddWithExifdatum_783) {
    exifData_["Exif.Image.Make"] = "OriginalCamera";
    Exiv2::Exifdatum datum = *exifData_.begin();

    Exiv2::ExifData otherData;
    otherData.add(datum);
    EXPECT_EQ(otherData.count(), 1u);
    EXPECT_EQ(otherData.begin()->toString(), "OriginalCamera");
}

// Test sortByKey
TEST_F(ExifDataTest_783, SortByKey_783) {
    exifData_["Exif.Image.Software"] = "SoftwareC";
    exifData_["Exif.Image.Make"] = "CameraA";
    exifData_["Exif.Image.Model"] = "ModelB";

    exifData_.sortByKey();

    // After sort by key, verify ordering
    auto it = exifData_.begin();
    std::string prev = it->key();
    ++it;
    while (it != exifData_.end()) {
        EXPECT_LE(prev, it->key());
        prev = it->key();
        ++it;
    }
}

// Test sortByTag
TEST_F(ExifDataTest_783, SortByTag_783) {
    exifData_["Exif.Image.Software"] = "SoftwareC";
    exifData_["Exif.Image.Make"] = "CameraA";
    exifData_["Exif.Image.Model"] = "ModelB";

    exifData_.sortByTag();

    // After sort by tag, verify ordering by tag number
    auto it = exifData_.begin();
    uint16_t prevTag = it->tag();
    ++it;
    while (it != exifData_.end()) {
        EXPECT_LE(prevTag, it->tag());
        prevTag = it->tag();
        ++it;
    }
}

// Test empty() returns true initially and false after adding
TEST_F(ExifDataTest_783, EmptyReflectsState_783) {
    EXPECT_TRUE(exifData_.empty());
    exifData_["Exif.Image.Make"] = "Camera";
    EXPECT_FALSE(exifData_.empty());
    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
}

// Test count reflects additions and removals
TEST_F(ExifDataTest_783, CountReflectsAdditionsAndRemovals_783) {
    EXPECT_EQ(exifData_.count(), 0u);
    exifData_["Exif.Image.Make"] = "CameraA";
    EXPECT_EQ(exifData_.count(), 1u);
    exifData_["Exif.Image.Model"] = "ModelB";
    EXPECT_EQ(exifData_.count(), 2u);
    exifData_.erase(exifData_.begin());
    EXPECT_EQ(exifData_.count(), 1u);
    exifData_.erase(exifData_.begin());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test iterator traversal
TEST_F(ExifDataTest_783, IteratorTraversal_783) {
    exifData_["Exif.Image.Make"] = "CameraA";
    exifData_["Exif.Image.Model"] = "ModelB";

    size_t count = 0;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 2u);
}

// Test operator[] updates existing value
TEST_F(ExifDataTest_783, OperatorBracketUpdatesExisting_783) {
    exifData_["Exif.Image.Make"] = "OldCamera";
    EXPECT_EQ(exifData_.count(), 1u);
    exifData_["Exif.Image.Make"] = "NewCamera";
    // operator[] should find existing, not add duplicate
    EXPECT_EQ(exifData_.count(), 1u);
    EXPECT_EQ(exifData_["Exif.Image.Make"].toString(), "NewCamera");
}

// Test erase in a loop
TEST_F(ExifDataTest_783, EraseInLoop_783) {
    exifData_["Exif.Image.Make"] = "CameraA";
    exifData_["Exif.Image.Model"] = "ModelB";
    exifData_["Exif.Image.Software"] = "SoftwareC";
    EXPECT_EQ(exifData_.count(), 3u);

    auto it = exifData_.begin();
    while (it != exifData_.end()) {
        it = exifData_.erase(it);
    }
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test findKey after erase
TEST_F(ExifDataTest_783, FindKeyAfterErase_783) {
    exifData_["Exif.Image.Make"] = "CameraA";
    exifData_["Exif.Image.Model"] = "ModelB";

    Exiv2::ExifKey makeKey("Exif.Image.Make");
    auto it = exifData_.findKey(makeKey);
    ASSERT_NE(it, exifData_.end());
    exifData_.erase(it);

    it = exifData_.findKey(makeKey);
    EXPECT_EQ(it, exifData_.end());

    Exiv2::ExifKey modelKey("Exif.Image.Model");
    it = exifData_.findKey(modelKey);
    EXPECT_NE(it, exifData_.end());
}

// Test sort stability: sortByKey on already sorted data
TEST_F(ExifDataTest_783, SortByKeyAlreadySorted_783) {
    exifData_["Exif.Image.Make"] = "CameraA";
    exifData_["Exif.Image.Model"] = "ModelB";
    exifData_["Exif.Image.Software"] = "SoftwareC";

    exifData_.sortByKey();
    size_t countBefore = exifData_.count();
    exifData_.sortByKey();
    EXPECT_EQ(exifData_.count(), countBefore);
}
