#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exifsupport.hpp>
#include <exiv2/value.hpp>
#include <string>
#include <algorithm>

using namespace Exiv2;

class ExifDataTest_780 : public ::testing::Test {
protected:
    ExifData exifData;
};

// Test that a newly created ExifData is empty
TEST_F(ExifDataTest_780, DefaultConstructedIsEmpty_780) {
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);
}

// Test that begin() == end() for empty container
TEST_F(ExifDataTest_780, BeginEqualsEndWhenEmpty_780) {
    EXPECT_EQ(exifData.begin(), exifData.end());
}

// Test adding an element via operator[]
TEST_F(ExifDataTest_780, OperatorBracketAddsElement_780) {
    exifData["Exif.Image.Make"] = "TestCamera";
    EXPECT_FALSE(exifData.empty());
    EXPECT_EQ(exifData.count(), 1u);
}

// Test that operator[] returns same element on repeated access
TEST_F(ExifDataTest_780, OperatorBracketReturnsSameElement_780) {
    exifData["Exif.Image.Make"] = "TestCamera";
    exifData["Exif.Image.Make"] = "UpdatedCamera";
    EXPECT_EQ(exifData.count(), 1u);
    EXPECT_EQ(exifData["Exif.Image.Make"].toString(), "UpdatedCamera");
}

// Test adding via add(ExifKey, Value*)
TEST_F(ExifDataTest_780, AddWithKeyAndValue_780) {
    ExifKey key("Exif.Image.Model");
    Value::UniquePtr val = Value::create(asciiString);
    val->read("TestModel");
    exifData.add(key, val.get());
    EXPECT_EQ(exifData.count(), 1u);
    auto it = exifData.findKey(ExifKey("Exif.Image.Model"));
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ(it->toString(), "TestModel");
}

// Test adding via add(Exifdatum)
TEST_F(ExifDataTest_780, AddExifdatum_780) {
    exifData["Exif.Image.Make"] = "TestCamera";
    Exifdatum datum = *exifData.begin();

    ExifData otherData;
    otherData.add(datum);
    EXPECT_EQ(otherData.count(), 1u);
}

// Test findKey returns end() for non-existent key
TEST_F(ExifDataTest_780, FindKeyReturnsEndForNonExistent_780) {
    auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_EQ(it, exifData.end());
}

// Test findKey finds an existing key
TEST_F(ExifDataTest_780, FindKeyFindsExistingKey_780) {
    exifData["Exif.Image.Make"] = "TestCamera";
    auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ(it->toString(), "TestCamera");
}

// Test clear empties the container
TEST_F(ExifDataTest_780, ClearRemovesAllElements_780) {
    exifData["Exif.Image.Make"] = "TestCamera";
    exifData["Exif.Image.Model"] = "TestModel";
    EXPECT_EQ(exifData.count(), 2u);

    exifData.clear();
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);
}

// Test clear on already empty container
TEST_F(ExifDataTest_780, ClearOnEmptyIsNoOp_780) {
    exifData.clear();
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);
}

// Test erase single element
TEST_F(ExifDataTest_780, EraseSingleElement_780) {
    exifData["Exif.Image.Make"] = "TestCamera";
    exifData["Exif.Image.Model"] = "TestModel";
    EXPECT_EQ(exifData.count(), 2u);

    auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData.end());
    exifData.erase(it);
    EXPECT_EQ(exifData.count(), 1u);

    it = exifData.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_EQ(it, exifData.end());
}

// Test erase range
TEST_F(ExifDataTest_780, EraseRange_780) {
    exifData["Exif.Image.Make"] = "TestCamera";
    exifData["Exif.Image.Model"] = "TestModel";
    exifData["Exif.Image.Software"] = "TestSoftware";
    EXPECT_EQ(exifData.count(), 3u);

    exifData.erase(exifData.begin(), exifData.end());
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);
}

// Test erase empty range is no-op
TEST_F(ExifDataTest_780, EraseEmptyRangeIsNoOp_780) {
    exifData["Exif.Image.Make"] = "TestCamera";
    EXPECT_EQ(exifData.count(), 1u);

    exifData.erase(exifData.begin(), exifData.begin());
    EXPECT_EQ(exifData.count(), 1u);
}

// Test sortByKey
TEST_F(ExifDataTest_780, SortByKeySortsElements_780) {
    exifData["Exif.Image.Software"] = "TestSoftware";
    exifData["Exif.Image.Make"] = "TestCamera";
    exifData["Exif.Image.Model"] = "TestModel";

    exifData.sortByKey();

    // After sorting by key, elements should be in lexicographic order of their keys
    std::string prevKey;
    for (auto it = exifData.begin(); it != exifData.end(); ++it) {
        std::string currentKey = it->key();
        if (!prevKey.empty()) {
            EXPECT_LE(prevKey, currentKey) << "Keys not sorted: " << prevKey << " > " << currentKey;
        }
        prevKey = currentKey;
    }
}

// Test sortByTag
TEST_F(ExifDataTest_780, SortByTagSortsElements_780) {
    exifData["Exif.Image.Software"] = "TestSoftware";
    exifData["Exif.Image.Make"] = "TestCamera";
    exifData["Exif.Image.Model"] = "TestModel";

    exifData.sortByTag();

    // After sorting by tag, elements should be in order of their tag numbers
    uint16_t prevTag = 0;
    bool first = true;
    for (auto it = exifData.begin(); it != exifData.end(); ++it) {
        uint16_t currentTag = it->tag();
        if (!first) {
            EXPECT_LE(prevTag, currentTag) << "Tags not sorted: " << prevTag << " > " << currentTag;
        }
        prevTag = currentTag;
        first = false;
    }
}

// Test sortByKey on empty data
TEST_F(ExifDataTest_780, SortByKeyOnEmptyIsNoOp_780) {
    EXPECT_NO_THROW(exifData.sortByKey());
    EXPECT_TRUE(exifData.empty());
}

// Test sortByTag on empty data
TEST_F(ExifDataTest_780, SortByTagOnEmptyIsNoOp_780) {
    EXPECT_NO_THROW(exifData.sortByTag());
    EXPECT_TRUE(exifData.empty());
}

// Test sortByKey with single element
TEST_F(ExifDataTest_780, SortByKeyWithSingleElement_780) {
    exifData["Exif.Image.Make"] = "TestCamera";
    EXPECT_NO_THROW(exifData.sortByKey());
    EXPECT_EQ(exifData.count(), 1u);
}

// Test count increases with each addition
TEST_F(ExifDataTest_780, CountIncreasesWithAdditions_780) {
    EXPECT_EQ(exifData.count(), 0u);

    exifData["Exif.Image.Make"] = "TestCamera";
    EXPECT_EQ(exifData.count(), 1u);

    exifData["Exif.Image.Model"] = "TestModel";
    EXPECT_EQ(exifData.count(), 2u);

    exifData["Exif.Image.Software"] = "TestSoftware";
    EXPECT_EQ(exifData.count(), 3u);
}

// Test multiple operations in sequence
TEST_F(ExifDataTest_780, MultipleOperationsSequence_780) {
    exifData["Exif.Image.Make"] = "Camera1";
    exifData["Exif.Image.Model"] = "Model1";
    EXPECT_EQ(exifData.count(), 2u);

    exifData.sortByKey();
    EXPECT_EQ(exifData.count(), 2u);

    auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData.end());
    exifData.erase(it);
    EXPECT_EQ(exifData.count(), 1u);

    exifData.clear();
    EXPECT_TRUE(exifData.empty());

    exifData["Exif.Image.Software"] = "Software1";
    EXPECT_EQ(exifData.count(), 1u);
    EXPECT_FALSE(exifData.empty());
}

// Test iterator traversal
TEST_F(ExifDataTest_780, IteratorTraversal_780) {
    exifData["Exif.Image.Make"] = "Camera";
    exifData["Exif.Image.Model"] = "Model";
    exifData["Exif.Image.Software"] = "Software";

    size_t count = 0;
    for (auto it = exifData.begin(); it != exifData.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3u);
    EXPECT_EQ(count, exifData.count());
}

// Test erase returns valid iterator
TEST_F(ExifDataTest_780, EraseReturnsValidIterator_780) {
    exifData["Exif.Image.Make"] = "Camera";
    exifData["Exif.Image.Model"] = "Model";

    auto it = exifData.erase(exifData.begin());
    EXPECT_EQ(exifData.count(), 1u);
    // The returned iterator should be valid - either pointing to next element or end
    if (exifData.count() > 0) {
        EXPECT_EQ(it, exifData.begin());
    }
}

// Test findKey with const ExifData
TEST_F(ExifDataTest_780, FindKeyConst_780) {
    exifData["Exif.Image.Make"] = "Camera";

    const ExifData& constData = exifData;
    auto it = constData.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, constData.end());
    EXPECT_EQ(it->toString(), "Camera");
}

// Test findKey const returns end for non-existent
TEST_F(ExifDataTest_780, FindKeyConstReturnsEndForNonExistent_780) {
    const ExifData& constData = exifData;
    auto it = constData.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_EQ(it, constData.end());
}
