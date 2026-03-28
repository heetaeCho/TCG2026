#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

class ExifDataTest_40 : public ::testing::Test {
protected:
    Exiv2::ExifData exifData_;
};

// Test that a newly created ExifData is empty
TEST_F(ExifDataTest_40, DefaultConstructedIsEmpty_40) {
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test that begin() == end() for empty ExifData
TEST_F(ExifDataTest_40, BeginEqualsEndWhenEmpty_40) {
    EXPECT_EQ(exifData_.begin(), exifData_.end());
}

// Test adding an element via operator[] increases count
TEST_F(ExifDataTest_40, OperatorBracketAddsElement_40) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    EXPECT_FALSE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test operator[] retrieves the same element when accessed again
TEST_F(ExifDataTest_40, OperatorBracketRetrievesSameElement_40) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    EXPECT_EQ(exifData_["Exif.Image.Make"].toString(), "TestCamera");
}

// Test adding multiple different keys
TEST_F(ExifDataTest_40, AddMultipleDifferentKeys_40) {
    exifData_["Exif.Image.Make"] = "CameraMake";
    exifData_["Exif.Image.Model"] = "CameraModel";
    EXPECT_EQ(exifData_.count(), 2u);
}

// Test operator[] with same key doesn't duplicate
TEST_F(ExifDataTest_40, OperatorBracketSameKeyNoDuplicate_40) {
    exifData_["Exif.Image.Make"] = "First";
    exifData_["Exif.Image.Make"] = "Second";
    EXPECT_EQ(exifData_.count(), 1u);
    EXPECT_EQ(exifData_["Exif.Image.Make"].toString(), "Second");
}

// Test add with ExifKey and Value
TEST_F(ExifDataTest_40, AddWithExifKeyAndValue_40) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("TestMake");
    exifData_.add(key, value.get());
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test add with Exifdatum
TEST_F(ExifDataTest_40, AddWithExifdatum_40) {
    Exiv2::Exifdatum datum(Exiv2::ExifKey("Exif.Image.Model"));
    datum.setValue("TestModel");
    exifData_.add(datum);
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test findKey for existing key
TEST_F(ExifDataTest_40, FindKeyExisting_40) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "TestCamera");
}

// Test findKey for non-existing key
TEST_F(ExifDataTest_40, FindKeyNonExisting_40) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Model"));
    EXPECT_EQ(it, exifData_.end());
}

// Test findKey on empty ExifData
TEST_F(ExifDataTest_40, FindKeyOnEmptyData_40) {
    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_EQ(it, exifData_.end());
}

// Test clear empties the data
TEST_F(ExifDataTest_40, ClearEmptiesData_40) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    EXPECT_EQ(exifData_.count(), 2u);
    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test clear on already empty data
TEST_F(ExifDataTest_40, ClearOnEmptyData_40) {
    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test erase single element
TEST_F(ExifDataTest_40, EraseSingleElement_40) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    EXPECT_EQ(exifData_.count(), 2u);

    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData_.end());
    exifData_.erase(it);
    EXPECT_EQ(exifData_.count(), 1u);

    auto it2 = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_EQ(it2, exifData_.end());
}

// Test erase range
TEST_F(ExifDataTest_40, EraseRange_40) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    exifData_["Exif.Image.Software"] = "TestSoftware";
    EXPECT_EQ(exifData_.count(), 3u);

    exifData_.erase(exifData_.begin(), exifData_.end());
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test erase empty range (begin, begin)
TEST_F(ExifDataTest_40, EraseEmptyRange_40) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    size_t countBefore = exifData_.count();
    exifData_.erase(exifData_.begin(), exifData_.begin());
    EXPECT_EQ(exifData_.count(), countBefore);
}

// Test sortByKey doesn't lose elements
TEST_F(ExifDataTest_40, SortByKeyPreservesCount_40) {
    exifData_["Exif.Image.Software"] = "Software";
    exifData_["Exif.Image.Make"] = "Make";
    exifData_["Exif.Image.Model"] = "Model";
    EXPECT_EQ(exifData_.count(), 3u);

    exifData_.sortByKey();
    EXPECT_EQ(exifData_.count(), 3u);
}

// Test sortByKey produces sorted order
TEST_F(ExifDataTest_40, SortByKeyProducesSortedOrder_40) {
    exifData_["Exif.Image.Software"] = "Software";
    exifData_["Exif.Image.Make"] = "Make";
    exifData_["Exif.Image.Model"] = "Model";

    exifData_.sortByKey();

    auto it = exifData_.begin();
    std::string prevKey;
    while (it != exifData_.end()) {
        std::string currentKey = it->key();
        if (!prevKey.empty()) {
            EXPECT_LE(prevKey, currentKey);
        }
        prevKey = currentKey;
        ++it;
    }
}

// Test sortByTag doesn't lose elements
TEST_F(ExifDataTest_40, SortByTagPreservesCount_40) {
    exifData_["Exif.Image.Software"] = "Software";
    exifData_["Exif.Image.Make"] = "Make";
    exifData_["Exif.Image.Model"] = "Model";
    EXPECT_EQ(exifData_.count(), 3u);

    exifData_.sortByTag();
    EXPECT_EQ(exifData_.count(), 3u);
}

// Test sortByTag produces sorted order by tag
TEST_F(ExifDataTest_40, SortByTagProducesSortedOrder_40) {
    exifData_["Exif.Image.Software"] = "Software";
    exifData_["Exif.Image.Make"] = "Make";
    exifData_["Exif.Image.Model"] = "Model";

    exifData_.sortByTag();

    auto it = exifData_.begin();
    uint16_t prevTag = 0;
    bool first = true;
    while (it != exifData_.end()) {
        uint16_t currentTag = it->tag();
        if (!first) {
            EXPECT_LE(prevTag, currentTag);
        }
        prevTag = currentTag;
        first = false;
        ++it;
    }
}

// Test iterating through all elements
TEST_F(ExifDataTest_40, IterateThroughElements_40) {
    exifData_["Exif.Image.Make"] = "CameraMake";
    exifData_["Exif.Image.Model"] = "CameraModel";
    exifData_["Exif.Image.Software"] = "TestSoftware";

    size_t count = 0;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3u);
    EXPECT_EQ(count, exifData_.count());
}

// Test const findKey on non-empty data
TEST_F(ExifDataTest_40, ConstFindKey_40) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    const Exiv2::ExifData& constData = exifData_;
    auto it = constData.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_NE(it, constData.end());
    EXPECT_EQ(it->toString(), "TestCamera");
}

// Test const findKey returns end for non-existing key
TEST_F(ExifDataTest_40, ConstFindKeyNonExisting_40) {
    const Exiv2::ExifData& constData = exifData_;
    auto it = constData.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_EQ(it, constData.end());
}

// Test empty and count consistency
TEST_F(ExifDataTest_40, EmptyAndCountConsistency_40) {
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);

    exifData_["Exif.Image.Make"] = "Test";
    EXPECT_FALSE(exifData_.empty());
    EXPECT_GT(exifData_.count(), 0u);

    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test erase returns valid iterator
TEST_F(ExifDataTest_40, EraseReturnsValidIterator_40) {
    exifData_["Exif.Image.Make"] = "CameraMake";
    exifData_["Exif.Image.Model"] = "CameraModel";

    auto it = exifData_.begin();
    auto nextIt = exifData_.erase(it);
    // After erasing, nextIt should be a valid iterator
    EXPECT_EQ(exifData_.count(), 1u);
    if (nextIt != exifData_.end()) {
        // Should still be able to access the remaining element
        EXPECT_FALSE(nextIt->key().empty());
    }
}

// Test adding via add method with key and value, then finding it
TEST_F(ExifDataTest_40, AddAndFind_40) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("2023:01:01 12:00:00");
    exifData_.add(key, value.get());

    auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.DateTimeOriginal"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "2023:01:01 12:00:00");
}

// Test adding duplicate key via add (should add another entry or throw)
TEST_F(ExifDataTest_40, AddDuplicateKey_40) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::Value::UniquePtr value1 = Exiv2::Value::create(Exiv2::asciiString);
    value1->read("Make1");
    exifData_.add(key1, value1.get());

    Exiv2::ExifKey key2("Exif.Image.Make");
    Exiv2::Value::UniquePtr value2 = Exiv2::Value::create(Exiv2::asciiString);
    value2->read("Make2");

    // add may add a duplicate or throw; we just verify no crash and data is consistent
    try {
        exifData_.add(key2, value2.get());
        // If no exception, count should be >= 1
        EXPECT_GE(exifData_.count(), 1u);
    } catch (...) {
        // If it throws, the original entry should still exist
        EXPECT_EQ(exifData_.count(), 1u);
    }
}

// Test sort operations on empty data (should not crash)
TEST_F(ExifDataTest_40, SortEmptyDataByKey_40) {
    EXPECT_NO_THROW(exifData_.sortByKey());
    EXPECT_TRUE(exifData_.empty());
}

TEST_F(ExifDataTest_40, SortEmptyDataByTag_40) {
    EXPECT_NO_THROW(exifData_.sortByTag());
    EXPECT_TRUE(exifData_.empty());
}

// Test single element operations
TEST_F(ExifDataTest_40, SingleElementOperations_40) {
    exifData_["Exif.Image.Make"] = "OnlyOne";
    EXPECT_EQ(exifData_.count(), 1u);
    EXPECT_FALSE(exifData_.empty());

    auto it = exifData_.begin();
    EXPECT_NE(it, exifData_.end());
    ++it;
    EXPECT_EQ(it, exifData_.end());
}

// Test erasing all elements one by one
TEST_F(ExifDataTest_40, EraseAllOneByOne_40) {
    exifData_["Exif.Image.Make"] = "Make";
    exifData_["Exif.Image.Model"] = "Model";
    exifData_["Exif.Image.Software"] = "Software";

    while (!exifData_.empty()) {
        exifData_.erase(exifData_.begin());
    }
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
    EXPECT_EQ(exifData_.begin(), exifData_.end());
}
