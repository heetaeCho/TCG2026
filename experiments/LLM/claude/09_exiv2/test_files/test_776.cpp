#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>
#include <string>

using namespace Exiv2;

class ExifDataTest_776 : public ::testing::Test {
protected:
    ExifData exifData_;
};

// Test that a newly created ExifData is empty
TEST_F(ExifDataTest_776, DefaultConstructedIsEmpty_776) {
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test that begin() == end() for empty ExifData
TEST_F(ExifDataTest_776, EmptyBeginEqualsEnd_776) {
    EXPECT_EQ(exifData_.begin(), exifData_.end());
}

// Test adding an Exifdatum via add(ExifKey, Value*)
TEST_F(ExifDataTest_776, AddWithKeyAndValueIncreasesCount_776) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Canon");
    exifData_.add(key, value.get());
    EXPECT_FALSE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test adding an Exifdatum directly
TEST_F(ExifDataTest_776, AddExifdatumIncreasesCount_776) {
    ExifKey key("Exif.Image.Model");
    auto value = Value::create(asciiString);
    value->read("EOS 5D");
    Exifdatum datum(key, value.get());
    exifData_.add(datum);
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test adding multiple entries
TEST_F(ExifDataTest_776, AddMultipleEntries_776) {
    ExifKey key1("Exif.Image.Make");
    auto val1 = Value::create(asciiString);
    val1->read("Canon");
    exifData_.add(key1, val1.get());

    ExifKey key2("Exif.Image.Model");
    auto val2 = Value::create(asciiString);
    val2->read("EOS 5D");
    exifData_.add(key2, val2.get());

    ExifKey key3("Exif.Image.Orientation");
    auto val3 = Value::create(unsignedShort);
    val3->read("1");
    exifData_.add(key3, val3.get());

    EXPECT_EQ(exifData_.count(), 3u);
}

// Test clear empties the data
TEST_F(ExifDataTest_776, ClearRemovesAllEntries_776) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Nikon");
    exifData_.add(key, value.get());
    EXPECT_EQ(exifData_.count(), 1u);

    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test findKey finds an existing key
TEST_F(ExifDataTest_776, FindKeyFindsExistingEntry_776) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Sony");
    exifData_.add(key, value.get());

    auto it = exifData_.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_NE(it, exifData_.end());
    EXPECT_EQ(it->key(), "Exif.Image.Make");
}

// Test findKey returns end() for non-existing key
TEST_F(ExifDataTest_776, FindKeyReturnsEndForNonExisting_776) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Sony");
    exifData_.add(key, value.get());

    auto it = exifData_.findKey(ExifKey("Exif.Image.Model"));
    EXPECT_EQ(it, exifData_.end());
}

// Test findKey on empty ExifData
TEST_F(ExifDataTest_776, FindKeyOnEmptyReturnsEnd_776) {
    auto it = exifData_.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_EQ(it, exifData_.end());
}

// Test erase single element
TEST_F(ExifDataTest_776, EraseSingleElement_776) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Fuji");
    exifData_.add(key, value.get());
    EXPECT_EQ(exifData_.count(), 1u);

    auto it = exifData_.begin();
    exifData_.erase(it);
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test erase range
TEST_F(ExifDataTest_776, EraseRange_776) {
    ExifKey key1("Exif.Image.Make");
    auto val1 = Value::create(asciiString);
    val1->read("Canon");
    exifData_.add(key1, val1.get());

    ExifKey key2("Exif.Image.Model");
    auto val2 = Value::create(asciiString);
    val2->read("EOS R");
    exifData_.add(key2, val2.get());

    ExifKey key3("Exif.Image.Orientation");
    auto val3 = Value::create(unsignedShort);
    val3->read("1");
    exifData_.add(key3, val3.get());

    EXPECT_EQ(exifData_.count(), 3u);

    exifData_.erase(exifData_.begin(), exifData_.end());
    EXPECT_TRUE(exifData_.empty());
}

// Test operator[] creates entry if not found
TEST_F(ExifDataTest_776, OperatorBracketCreatesEntry_776) {
    Exifdatum& datum = exifData_["Exif.Image.Make"];
    // After accessing with operator[], the key should exist or be created
    // The datum should have the key set
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test operator[] on existing entry returns same datum
TEST_F(ExifDataTest_776, OperatorBracketReturnsExistingEntry_776) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Pentax");
    exifData_.add(key, value.get());

    Exifdatum& datum = exifData_["Exif.Image.Make"];
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.toString(), "Pentax");
}

// Test sortByKey doesn't crash and maintains count
TEST_F(ExifDataTest_776, SortByKeyMaintainsCount_776) {
    ExifKey key1("Exif.Image.Model");
    auto val1 = Value::create(asciiString);
    val1->read("EOS R");
    exifData_.add(key1, val1.get());

    ExifKey key2("Exif.Image.Make");
    auto val2 = Value::create(asciiString);
    val2->read("Canon");
    exifData_.add(key2, val2.get());

    size_t countBefore = exifData_.count();
    exifData_.sortByKey();
    EXPECT_EQ(exifData_.count(), countBefore);
}

// Test sortByTag doesn't crash and maintains count
TEST_F(ExifDataTest_776, SortByTagMaintainsCount_776) {
    ExifKey key1("Exif.Image.Model");
    auto val1 = Value::create(asciiString);
    val1->read("D850");
    exifData_.add(key1, val1.get());

    ExifKey key2("Exif.Image.Make");
    auto val2 = Value::create(asciiString);
    val2->read("Nikon");
    exifData_.add(key2, val2.get());

    size_t countBefore = exifData_.count();
    exifData_.sortByTag();
    EXPECT_EQ(exifData_.count(), countBefore);
}

// Test iteration over entries
TEST_F(ExifDataTest_776, IterationOverEntries_776) {
    ExifKey key1("Exif.Image.Make");
    auto val1 = Value::create(asciiString);
    val1->read("Olympus");
    exifData_.add(key1, val1.get());

    ExifKey key2("Exif.Image.Model");
    auto val2 = Value::create(asciiString);
    val2->read("E-M1");
    exifData_.add(key2, val2.get());

    size_t iterCount = 0;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        ++iterCount;
    }
    EXPECT_EQ(iterCount, 2u);
}

// Test erase single element from middle
TEST_F(ExifDataTest_776, EraseSingleFromMiddle_776) {
    ExifKey key1("Exif.Image.Make");
    auto val1 = Value::create(asciiString);
    val1->read("Canon");
    exifData_.add(key1, val1.get());

    ExifKey key2("Exif.Image.Model");
    auto val2 = Value::create(asciiString);
    val2->read("EOS R5");
    exifData_.add(key2, val2.get());

    ExifKey key3("Exif.Image.Orientation");
    auto val3 = Value::create(unsignedShort);
    val3->read("1");
    exifData_.add(key3, val3.get());

    auto it = exifData_.findKey(ExifKey("Exif.Image.Model"));
    ASSERT_NE(it, exifData_.end());
    exifData_.erase(it);
    EXPECT_EQ(exifData_.count(), 2u);

    // Model should no longer be found
    auto it2 = exifData_.findKey(ExifKey("Exif.Image.Model"));
    EXPECT_EQ(it2, exifData_.end());
}

// Test clear on already empty data
TEST_F(ExifDataTest_776, ClearOnEmptyIsNoOp_776) {
    EXPECT_TRUE(exifData_.empty());
    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test adding entry with null value pointer
TEST_F(ExifDataTest_776, AddWithNullValue_776) {
    ExifKey key("Exif.Image.Make");
    exifData_.add(key, nullptr);
    // The entry should still be added (count increases)
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test const findKey
TEST_F(ExifDataTest_776, ConstFindKey_776) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Leica");
    exifData_.add(key, value.get());

    const ExifData& constData = exifData_;
    auto it = constData.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_NE(it, constData.end());
    EXPECT_EQ(it->key(), "Exif.Image.Make");
}

// Test const findKey returns end for non-existing
TEST_F(ExifDataTest_776, ConstFindKeyNonExisting_776) {
    const ExifData& constData = exifData_;
    auto it = constData.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_EQ(it, constData.end());
}

// Test erase empty range is no-op
TEST_F(ExifDataTest_776, EraseEmptyRange_776) {
    ExifKey key("Exif.Image.Make");
    auto val = Value::create(asciiString);
    val->read("Canon");
    exifData_.add(key, val.get());

    auto it = exifData_.begin();
    exifData_.erase(it, it); // empty range
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test value stored via add is retrievable
TEST_F(ExifDataTest_776, StoredValueIsRetrievable_776) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Hasselblad");
    exifData_.add(key, value.get());

    auto it = exifData_.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "Hasselblad");
}

// Test sortByKey actually sorts
TEST_F(ExifDataTest_776, SortByKeyProducesOrder_776) {
    ExifKey key1("Exif.Photo.DateTimeOriginal");
    auto val1 = Value::create(asciiString);
    val1->read("2023:01:01 12:00:00");
    exifData_.add(key1, val1.get());

    ExifKey key2("Exif.Image.Make");
    auto val2 = Value::create(asciiString);
    val2->read("Canon");
    exifData_.add(key2, val2.get());

    exifData_.sortByKey();

    // After sorting by key, keys should be in lexicographic order
    auto it = exifData_.begin();
    std::string prevKey = it->key();
    ++it;
    while (it != exifData_.end()) {
        EXPECT_LE(prevKey, it->key());
        prevKey = it->key();
        ++it;
    }
}
