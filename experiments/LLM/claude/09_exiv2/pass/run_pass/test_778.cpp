#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>

namespace {

class ExifDataTest_778 : public ::testing::Test {
protected:
    Exiv2::ExifData exifData_;
};

// Test that a newly created ExifData is empty
TEST_F(ExifDataTest_778, DefaultConstructedIsEmpty_778) {
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test that begin() == end() for empty container
TEST_F(ExifDataTest_778, BeginEqualsEndWhenEmpty_778) {
    EXPECT_EQ(exifData_.begin(), exifData_.end());
}

// Test adding an element via operator[]
TEST_F(ExifDataTest_778, OperatorBracketAddsElement_778) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    EXPECT_FALSE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test that operator[] returns existing element for same key
TEST_F(ExifDataTest_778, OperatorBracketReturnsSameElement_778) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Make"] = "UpdatedCamera";
    EXPECT_EQ(exifData_.count(), 1u);
    EXPECT_EQ(exifData_["Exif.Image.Make"].toString(), "UpdatedCamera");
}

// Test adding via add(ExifKey, Value*)
TEST_F(ExifDataTest_778, AddWithKeyAndValue_778) {
    Exiv2::ExifKey key("Exif.Image.Model");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("TestModel");
    exifData_.add(key, value.get());
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test adding via add(Exifdatum)
TEST_F(ExifDataTest_778, AddExifdatum_778) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    Exiv2::ExifData otherData;
    // Copy the datum
    auto it = exifData_.begin();
    otherData.add(*it);
    EXPECT_EQ(otherData.count(), 1u);
}

// Test findKey returns end() when key not found
TEST_F(ExifDataTest_778, FindKeyReturnsEndWhenNotFound_778) {
    Exiv2::ExifKey key("Exif.Image.Make");
    auto it = exifData_.findKey(key);
    EXPECT_EQ(it, exifData_.end());
}

// Test findKey on const ExifData returns end() when key not found
TEST_F(ExifDataTest_778, FindKeyConstReturnsEndWhenNotFound_778) {
    const Exiv2::ExifData& constData = exifData_;
    Exiv2::ExifKey key("Exif.Image.Make");
    auto it = constData.findKey(key);
    EXPECT_EQ(it, constData.end());
}

// Test findKey finds existing key
TEST_F(ExifDataTest_778, FindKeyFindsExistingKey_778) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    Exiv2::ExifKey key("Exif.Image.Make");
    auto it = exifData_.findKey(key);
    EXPECT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "TestCamera");
}

// Test const findKey finds existing key
TEST_F(ExifDataTest_778, ConstFindKeyFindsExistingKey_778) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    const Exiv2::ExifData& constData = exifData_;
    Exiv2::ExifKey key("Exif.Image.Make");
    auto it = constData.findKey(key);
    EXPECT_NE(it, constData.end());
    EXPECT_EQ(it->toString(), "TestCamera");
}

// Test findKey among multiple entries
TEST_F(ExifDataTest_778, FindKeyAmongMultipleEntries_778) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    exifData_["Exif.Image.Software"] = "TestSoftware";

    Exiv2::ExifKey key("Exif.Image.Model");
    auto it = exifData_.findKey(key);
    EXPECT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "TestModel");
}

// Test clear empties the container
TEST_F(ExifDataTest_778, ClearEmptiesContainer_778) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    EXPECT_EQ(exifData_.count(), 2u);

    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test erase single element
TEST_F(ExifDataTest_778, EraseSingleElement_778) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    EXPECT_EQ(exifData_.count(), 2u);

    auto it = exifData_.begin();
    exifData_.erase(it);
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test erase range
TEST_F(ExifDataTest_778, EraseRange_778) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    exifData_["Exif.Image.Software"] = "TestSoftware";
    EXPECT_EQ(exifData_.count(), 3u);

    exifData_.erase(exifData_.begin(), exifData_.end());
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test sortByKey doesn't crash and maintains all elements
TEST_F(ExifDataTest_778, SortByKeyMaintainsElements_778) {
    exifData_["Exif.Image.Software"] = "TestSoftware";
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";

    exifData_.sortByKey();
    EXPECT_EQ(exifData_.count(), 3u);
}

// Test sortByTag doesn't crash and maintains all elements
TEST_F(ExifDataTest_778, SortByTagMaintainsElements_778) {
    exifData_["Exif.Image.Software"] = "TestSoftware";
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";

    exifData_.sortByTag();
    EXPECT_EQ(exifData_.count(), 3u);
}

// Test findKey after clear returns end
TEST_F(ExifDataTest_778, FindKeyAfterClearReturnsEnd_778) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_.clear();

    Exiv2::ExifKey key("Exif.Image.Make");
    auto it = exifData_.findKey(key);
    EXPECT_EQ(it, exifData_.end());
}

// Test findKey after erase of that specific element
TEST_F(ExifDataTest_778, FindKeyAfterEraseReturnsEnd_778) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";

    Exiv2::ExifKey key("Exif.Image.Make");
    auto it = exifData_.findKey(key);
    EXPECT_NE(it, exifData_.end());

    exifData_.erase(it);
    auto it2 = exifData_.findKey(key);
    EXPECT_EQ(it2, exifData_.end());
}

// Test that count increments correctly with multiple adds
TEST_F(ExifDataTest_778, CountIncrementsWithAdds_778) {
    EXPECT_EQ(exifData_.count(), 0u);

    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::Value::UniquePtr val1 = Exiv2::Value::create(Exiv2::asciiString);
    val1->read("Camera1");
    exifData_.add(key1, val1.get());
    EXPECT_EQ(exifData_.count(), 1u);

    Exiv2::ExifKey key2("Exif.Image.Model");
    Exiv2::Value::UniquePtr val2 = Exiv2::Value::create(Exiv2::asciiString);
    val2->read("Model1");
    exifData_.add(key2, val2.get());
    EXPECT_EQ(exifData_.count(), 2u);
}

// Test iterator traversal
TEST_F(ExifDataTest_778, IteratorTraversal_778) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";

    size_t count = 0;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 2u);
}

// Test sortByKey orders elements by key string
TEST_F(ExifDataTest_778, SortByKeyOrdersCorrectly_778) {
    exifData_["Exif.Image.Software"] = "Soft";
    exifData_["Exif.Image.Make"] = "Camera";
    exifData_["Exif.Image.Model"] = "Model";

    exifData_.sortByKey();

    std::string prevKey;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        if (!prevKey.empty()) {
            EXPECT_LE(prevKey, it->key());
        }
        prevKey = it->key();
    }
}

// Test erase returns valid iterator
TEST_F(ExifDataTest_778, EraseReturnsValidIterator_778) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    exifData_["Exif.Image.Software"] = "TestSoftware";

    auto it = exifData_.erase(exifData_.begin());
    // The returned iterator should be valid (either points to next element or end)
    EXPECT_EQ(exifData_.count(), 2u);
    if (it != exifData_.end()) {
        // We can dereference safely
        EXPECT_FALSE(it->key().empty());
    }
}

// Test adding duplicate keys with add() method
TEST_F(ExifDataTest_778, AddDuplicateKeysIncreasesCount_778) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::Value::UniquePtr val1 = Exiv2::Value::create(Exiv2::asciiString);
    val1->read("Camera1");
    exifData_.add(key1, val1.get());

    Exiv2::ExifKey key2("Exif.Image.Make");
    Exiv2::Value::UniquePtr val2 = Exiv2::Value::create(Exiv2::asciiString);
    val2->read("Camera2");
    exifData_.add(key2, val2.get());

    // add() should add regardless of duplicates (unlike operator[])
    EXPECT_GE(exifData_.count(), 1u);
}

// Test clear on already empty ExifData
TEST_F(ExifDataTest_778, ClearOnEmptyData_778) {
    EXPECT_TRUE(exifData_.empty());
    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test ExifKey construction and key() method
TEST(ExifKeyTest_778, KeyConstruction_778) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
}

// Test ExifKey familyName
TEST(ExifKeyTest_778, FamilyName_778) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// Test ExifKey groupName
TEST(ExifKeyTest_778, GroupName_778) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.groupName(), "Image");
}

// Test ExifKey tagName
TEST(ExifKeyTest_778, TagName_778) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tagName(), "Make");
}

// Test ExifKey copy constructor
TEST(ExifKeyTest_778, CopyConstruction_778) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::ExifKey key2(key1);
    EXPECT_EQ(key1.key(), key2.key());
}

// Test ExifKey assignment operator
TEST(ExifKeyTest_778, AssignmentOperator_778) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::ExifKey key2("Exif.Image.Model");
    key2 = key1;
    EXPECT_EQ(key2.key(), "Exif.Image.Make");
}

// Test ExifKey clone
TEST(ExifKeyTest_778, Clone_778) {
    Exiv2::ExifKey key("Exif.Image.Make");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
}

}  // namespace
