#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exifkey.hpp>
#include <exiv2/value.hpp>
#include <string>
#include <algorithm>

using namespace Exiv2;

class ExifDataTest_781 : public ::testing::Test {
protected:
    ExifData exifData_;
};

// Test that a newly created ExifData is empty
TEST_F(ExifDataTest_781, DefaultConstructorCreatesEmptyData_781) {
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test that begin() == end() for empty data
TEST_F(ExifDataTest_781, BeginEqualsEndWhenEmpty_781) {
    EXPECT_EQ(exifData_.begin(), exifData_.end());
}

// Test adding an element via operator[]
TEST_F(ExifDataTest_781, OperatorBracketAddsElement_781) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    EXPECT_FALSE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test operator[] returns the same datum for the same key
TEST_F(ExifDataTest_781, OperatorBracketReturnsSameDatumForSameKey_781) {
    exifData_["Exif.Image.Make"] = "Camera1";
    exifData_["Exif.Image.Make"] = "Camera2";
    // Should still be 1 entry since same key
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test adding via add(ExifKey, Value*)
TEST_F(ExifDataTest_781, AddWithKeyAndValue_781) {
    ExifKey key("Exif.Image.Make");
    Value::UniquePtr val = Value::create(asciiString);
    val->read("TestValue");
    exifData_.add(key, val.get());
    EXPECT_EQ(exifData_.count(), 1u);
    EXPECT_FALSE(exifData_.empty());
}

// Test adding via add(Exifdatum)
TEST_F(ExifDataTest_781, AddExifdatum_781) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    Exifdatum datum = *exifData_.begin();

    ExifData otherData;
    otherData.add(datum);
    EXPECT_EQ(otherData.count(), 1u);
}

// Test adding multiple elements increases count
TEST_F(ExifDataTest_781, MultipleAddsIncreaseCount_781) {
    exifData_["Exif.Image.Make"] = "Camera";
    exifData_["Exif.Image.Model"] = "Model";
    exifData_["Exif.Image.Software"] = "Software";
    EXPECT_EQ(exifData_.count(), 3u);
}

// Test clear removes all elements
TEST_F(ExifDataTest_781, ClearRemovesAllElements_781) {
    exifData_["Exif.Image.Make"] = "Camera";
    exifData_["Exif.Image.Model"] = "Model";
    EXPECT_EQ(exifData_.count(), 2u);

    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
    EXPECT_EQ(exifData_.begin(), exifData_.end());
}

// Test clear on already empty data
TEST_F(ExifDataTest_781, ClearOnEmptyData_781) {
    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test findKey finds existing key
TEST_F(ExifDataTest_781, FindKeyFindsExistingKey_781) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    ExifKey key("Exif.Image.Make");
    auto it = exifData_.findKey(key);
    EXPECT_NE(it, exifData_.end());
    EXPECT_EQ(it->key(), "Exif.Image.Make");
}

// Test findKey returns end() for non-existing key
TEST_F(ExifDataTest_781, FindKeyReturnsEndForNonExistingKey_781) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    ExifKey key("Exif.Image.Model");
    auto it = exifData_.findKey(key);
    EXPECT_EQ(it, exifData_.end());
}

// Test findKey on empty data returns end()
TEST_F(ExifDataTest_781, FindKeyOnEmptyDataReturnsEnd_781) {
    ExifKey key("Exif.Image.Make");
    auto it = exifData_.findKey(key);
    EXPECT_EQ(it, exifData_.end());
}

// Test erase single element
TEST_F(ExifDataTest_781, EraseSingleElement_781) {
    exifData_["Exif.Image.Make"] = "Camera";
    exifData_["Exif.Image.Model"] = "Model";
    EXPECT_EQ(exifData_.count(), 2u);

    auto it = exifData_.begin();
    exifData_.erase(it);
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test erase range
TEST_F(ExifDataTest_781, EraseRange_781) {
    exifData_["Exif.Image.Make"] = "Camera";
    exifData_["Exif.Image.Model"] = "Model";
    exifData_["Exif.Image.Software"] = "Software";
    EXPECT_EQ(exifData_.count(), 3u);

    exifData_.erase(exifData_.begin(), exifData_.end());
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test erase range with equal iterators does nothing
TEST_F(ExifDataTest_781, EraseEmptyRange_781) {
    exifData_["Exif.Image.Make"] = "Camera";
    EXPECT_EQ(exifData_.count(), 1u);

    exifData_.erase(exifData_.begin(), exifData_.begin());
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test sortByTag
TEST_F(ExifDataTest_781, SortByTagDoesNotChangeCount_781) {
    exifData_["Exif.Image.Make"] = "Camera";
    exifData_["Exif.Image.Model"] = "Model";
    exifData_["Exif.Image.Software"] = "Software";

    size_t countBefore = exifData_.count();
    exifData_.sortByTag();
    EXPECT_EQ(exifData_.count(), countBefore);
}

// Test sortByTag on empty data doesn't crash
TEST_F(ExifDataTest_781, SortByTagOnEmptyData_781) {
    EXPECT_NO_THROW(exifData_.sortByTag());
    EXPECT_TRUE(exifData_.empty());
}

// Test sortByTag on single element
TEST_F(ExifDataTest_781, SortByTagOnSingleElement_781) {
    exifData_["Exif.Image.Make"] = "Camera";
    EXPECT_NO_THROW(exifData_.sortByTag());
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test sortByTag produces sorted order by tag
TEST_F(ExifDataTest_781, SortByTagProducesSortedOrder_781) {
    exifData_["Exif.Image.Software"] = "Software";
    exifData_["Exif.Image.Make"] = "Camera";
    exifData_["Exif.Image.Model"] = "Model";

    exifData_.sortByTag();

    // Verify they are sorted by tag number
    uint16_t prevTag = 0;
    bool sorted = true;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        if (it->tag() < prevTag) {
            sorted = false;
            break;
        }
        prevTag = it->tag();
    }
    EXPECT_TRUE(sorted);
}

// Test sortByKey
TEST_F(ExifDataTest_781, SortByKeyDoesNotChangeCount_781) {
    exifData_["Exif.Image.Make"] = "Camera";
    exifData_["Exif.Image.Model"] = "Model";
    exifData_["Exif.Image.Software"] = "Software";

    size_t countBefore = exifData_.count();
    exifData_.sortByKey();
    EXPECT_EQ(exifData_.count(), countBefore);
}

// Test sortByKey on empty data
TEST_F(ExifDataTest_781, SortByKeyOnEmptyData_781) {
    EXPECT_NO_THROW(exifData_.sortByKey());
    EXPECT_TRUE(exifData_.empty());
}

// Test sortByKey produces sorted order by key
TEST_F(ExifDataTest_781, SortByKeyProducesSortedOrder_781) {
    exifData_["Exif.Image.Software"] = "Software";
    exifData_["Exif.Image.Make"] = "Camera";
    exifData_["Exif.Image.Model"] = "Model";

    exifData_.sortByKey();

    std::string prevKey;
    bool sorted = true;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        if (it->key() < prevKey) {
            sorted = false;
            break;
        }
        prevKey = it->key();
    }
    EXPECT_TRUE(sorted);
}

// Test erase returns valid iterator
TEST_F(ExifDataTest_781, EraseReturnsValidIterator_781) {
    exifData_["Exif.Image.Make"] = "Camera";
    exifData_["Exif.Image.Model"] = "Model";

    auto it = exifData_.erase(exifData_.begin());
    // The returned iterator should be valid
    EXPECT_EQ(exifData_.count(), 1u);
    if (exifData_.count() > 0) {
        EXPECT_EQ(it, exifData_.begin());
    }
}

// Test erasing all elements one by one
TEST_F(ExifDataTest_781, EraseAllOneByOne_781) {
    exifData_["Exif.Image.Make"] = "Camera";
    exifData_["Exif.Image.Model"] = "Model";
    exifData_["Exif.Image.Software"] = "Software";

    while (!exifData_.empty()) {
        exifData_.erase(exifData_.begin());
    }
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test iterator traversal
TEST_F(ExifDataTest_781, IteratorTraversal_781) {
    exifData_["Exif.Image.Make"] = "Camera";
    exifData_["Exif.Image.Model"] = "Model";

    size_t count = 0;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 2u);
}

// Test that value set via operator[] is retrievable
TEST_F(ExifDataTest_781, ValueIsRetrievableAfterSet_781) {
    exifData_["Exif.Image.Make"] = "TestCameraValue";
    ExifKey key("Exif.Image.Make");
    auto it = exifData_.findKey(key);
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "TestCameraValue");
}

// Test adding duplicate keys via add
TEST_F(ExifDataTest_781, AddDuplicateKey_781) {
    ExifKey key1("Exif.Image.Make");
    Value::UniquePtr val1 = Value::create(asciiString);
    val1->read("Value1");
    exifData_.add(key1, val1.get());

    ExifKey key2("Exif.Image.Make");
    Value::UniquePtr val2 = Value::create(asciiString);
    val2->read("Value2");
    exifData_.add(key2, val2.get());

    // add() may allow duplicates (unlike operator[])
    EXPECT_GE(exifData_.count(), 1u);
}
