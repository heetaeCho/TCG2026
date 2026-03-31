#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

class ExifDataTest_42 : public ::testing::Test {
protected:
    Exiv2::ExifData exifData_;
};

// Test that a newly created ExifData is empty
TEST_F(ExifDataTest_42, DefaultConstructorCreatesEmptyData_42) {
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test that begin() == end() for empty ExifData
TEST_F(ExifDataTest_42, BeginEqualsEndWhenEmpty_42) {
    EXPECT_EQ(exifData_.begin(), exifData_.end());
}

// Test adding an element via operator[]
TEST_F(ExifDataTest_42, OperatorBracketAddsElement_42) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    EXPECT_FALSE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test that operator[] returns existing element for same key
TEST_F(ExifDataTest_42, OperatorBracketReturnsSameElement_42) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Make"] = "UpdatedCamera";
    EXPECT_EQ(exifData_.count(), 1u);
    EXPECT_EQ(exifData_["Exif.Image.Make"].toString(), "UpdatedCamera");
}

// Test adding multiple different keys
TEST_F(ExifDataTest_42, AddMultipleDifferentKeys_42) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    exifData_["Exif.Image.Software"] = "TestSoftware";
    EXPECT_EQ(exifData_.count(), 3u);
}

// Test add with ExifKey and Value
TEST_F(ExifDataTest_42, AddWithExifKeyAndValue_42) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("TestCamera");
    exifData_.add(key, value.get());
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test add with Exifdatum
TEST_F(ExifDataTest_42, AddWithExifdatum_42) {
    Exiv2::Exifdatum datum;
    exifData_["Exif.Image.Make"] = "TestCamera";
    auto it = exifData_.begin();
    Exiv2::ExifData otherData;
    otherData.add(*it);
    EXPECT_EQ(otherData.count(), 1u);
}

// Test clear removes all elements
TEST_F(ExifDataTest_42, ClearRemovesAllElements_42) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    EXPECT_EQ(exifData_.count(), 2u);
    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test clear on empty data
TEST_F(ExifDataTest_42, ClearOnEmptyData_42) {
    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test findKey finds existing key
TEST_F(ExifDataTest_42, FindKeyFindsExistingKey_42) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    Exiv2::ExifKey key("Exif.Image.Make");
    auto it = exifData_.findKey(key);
    EXPECT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "TestCamera");
}

// Test findKey returns end for non-existing key
TEST_F(ExifDataTest_42, FindKeyReturnsEndForNonExistingKey_42) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    Exiv2::ExifKey key("Exif.Image.Model");
    auto it = exifData_.findKey(key);
    EXPECT_EQ(it, exifData_.end());
}

// Test findKey on empty data
TEST_F(ExifDataTest_42, FindKeyOnEmptyData_42) {
    Exiv2::ExifKey key("Exif.Image.Make");
    auto it = exifData_.findKey(key);
    EXPECT_EQ(it, exifData_.end());
}

// Test erase single element
TEST_F(ExifDataTest_42, EraseSingleElement_42) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    EXPECT_EQ(exifData_.count(), 2u);
    auto it = exifData_.begin();
    exifData_.erase(it);
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test erase range of elements
TEST_F(ExifDataTest_42, EraseRangeOfElements_42) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    exifData_["Exif.Image.Software"] = "TestSoftware";
    EXPECT_EQ(exifData_.count(), 3u);
    exifData_.erase(exifData_.begin(), exifData_.end());
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test erase returns valid iterator
TEST_F(ExifDataTest_42, EraseReturnsValidIterator_42) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    auto it = exifData_.erase(exifData_.begin());
    EXPECT_EQ(exifData_.count(), 1u);
    // The returned iterator should be valid (begin or end)
    EXPECT_TRUE(it == exifData_.begin() || it == exifData_.end());
}

// Test sortByKey does not change count
TEST_F(ExifDataTest_42, SortByKeyDoesNotChangeCount_42) {
    exifData_["Exif.Image.Software"] = "TestSoftware";
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    size_t countBefore = exifData_.count();
    exifData_.sortByKey();
    EXPECT_EQ(exifData_.count(), countBefore);
}

// Test sortByTag does not change count
TEST_F(ExifDataTest_42, SortByTagDoesNotChangeCount_42) {
    exifData_["Exif.Image.Software"] = "TestSoftware";
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    size_t countBefore = exifData_.count();
    exifData_.sortByTag();
    EXPECT_EQ(exifData_.count(), countBefore);
}

// Test sortByKey on empty data does not crash
TEST_F(ExifDataTest_42, SortByKeyOnEmptyData_42) {
    EXPECT_NO_THROW(exifData_.sortByKey());
    EXPECT_TRUE(exifData_.empty());
}

// Test sortByTag on empty data does not crash
TEST_F(ExifDataTest_42, SortByTagOnEmptyData_42) {
    EXPECT_NO_THROW(exifData_.sortByTag());
    EXPECT_TRUE(exifData_.empty());
}

// Test sortByKey actually sorts
TEST_F(ExifDataTest_42, SortByKeyActuallySorts_42) {
    exifData_["Exif.Image.Software"] = "TestSoftware";
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    exifData_.sortByKey();
    
    // After sorting by key, keys should be in alphabetical order
    std::string prevKey;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        if (!prevKey.empty()) {
            EXPECT_LE(prevKey, it->key());
        }
        prevKey = it->key();
    }
}

// Test iterator traversal
TEST_F(ExifDataTest_42, IteratorTraversal_42) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    
    size_t iterCount = 0;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        ++iterCount;
    }
    EXPECT_EQ(iterCount, exifData_.count());
}

// Test const findKey
TEST_F(ExifDataTest_42, ConstFindKey_42) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    const Exiv2::ExifData& constData = exifData_;
    Exiv2::ExifKey key("Exif.Image.Make");
    auto it = constData.findKey(key);
    EXPECT_NE(it, constData.end());
    EXPECT_EQ(it->toString(), "TestCamera");
}

// Test that empty returns false after adding an element
TEST_F(ExifDataTest_42, EmptyReturnsFalseAfterAdd_42) {
    EXPECT_TRUE(exifData_.empty());
    exifData_["Exif.Image.Make"] = "TestCamera";
    EXPECT_FALSE(exifData_.empty());
}

// Test erase with empty range
TEST_F(ExifDataTest_42, EraseEmptyRange_42) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    auto it = exifData_.erase(exifData_.begin(), exifData_.begin());
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test copy semantics
TEST_F(ExifDataTest_42, CopyConstructor_42) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    
    Exiv2::ExifData copiedData(exifData_);
    EXPECT_EQ(copiedData.count(), exifData_.count());
    
    // Modifying copy should not affect original
    copiedData.clear();
    EXPECT_EQ(copiedData.count(), 0u);
    EXPECT_EQ(exifData_.count(), 2u);
}

// Test assignment operator
TEST_F(ExifDataTest_42, AssignmentOperator_42) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    
    Exiv2::ExifData otherData;
    otherData = exifData_;
    EXPECT_EQ(otherData.count(), 1u);
    
    // Modifying assigned data should not affect original
    otherData.clear();
    EXPECT_EQ(otherData.count(), 0u);
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test single element data
TEST_F(ExifDataTest_42, SingleElementBoundary_42) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    EXPECT_EQ(exifData_.count(), 1u);
    EXPECT_FALSE(exifData_.empty());
    
    auto it = exifData_.begin();
    ++it;
    EXPECT_EQ(it, exifData_.end());
}

// Test erase last element makes data empty
TEST_F(ExifDataTest_42, EraseLastElementMakesEmpty_42) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_.erase(exifData_.begin());
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}
