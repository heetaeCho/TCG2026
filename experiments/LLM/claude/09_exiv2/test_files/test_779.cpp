#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

class ExifDataTest_779 : public ::testing::Test {
protected:
    Exiv2::ExifData exifData;
};

// Test that a newly created ExifData is empty
TEST_F(ExifDataTest_779, NewExifDataIsEmpty_779) {
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);
}

// Test that begin() == end() for empty ExifData
TEST_F(ExifDataTest_779, BeginEqualsEndWhenEmpty_779) {
    EXPECT_EQ(exifData.begin(), exifData.end());
}

// Test clear on empty ExifData does not crash
TEST_F(ExifDataTest_779, ClearOnEmptyData_779) {
    exifData.clear();
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);
}

// Test adding an element via operator[]
TEST_F(ExifDataTest_779, OperatorBracketAddsElement_779) {
    exifData["Exif.Image.Make"] = "TestCamera";
    EXPECT_FALSE(exifData.empty());
    EXPECT_EQ(exifData.count(), 1u);
}

// Test that operator[] returns a reference to the same datum on repeated access
TEST_F(ExifDataTest_779, OperatorBracketReturnsSameDatum_779) {
    exifData["Exif.Image.Make"] = "TestCamera";
    exifData["Exif.Image.Make"] = "UpdatedCamera";
    EXPECT_EQ(exifData.count(), 1u);
    EXPECT_EQ(exifData["Exif.Image.Make"].toString(), "UpdatedCamera");
}

// Test adding via add(ExifKey, Value*)
TEST_F(ExifDataTest_779, AddWithKeyAndValue_779) {
    Exiv2::ExifKey key("Exif.Image.Model");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("TestModel");
    exifData.add(key, value.get());
    EXPECT_FALSE(exifData.empty());
    EXPECT_EQ(exifData.count(), 1u);
}

// Test adding via add(Exifdatum)
TEST_F(ExifDataTest_779, AddExifdatum_779) {
    Exiv2::Exifdatum datum;
    Exiv2::ExifKey key("Exif.Image.Make");
    datum = Exiv2::Exifdatum(key);
    exifData.add(datum);
    EXPECT_EQ(exifData.count(), 1u);
}

// Test adding multiple elements
TEST_F(ExifDataTest_779, AddMultipleElements_779) {
    exifData["Exif.Image.Make"] = "CameraA";
    exifData["Exif.Image.Model"] = "ModelB";
    exifData["Exif.Image.Software"] = "SoftwareC";
    EXPECT_EQ(exifData.count(), 3u);
}

// Test clear removes all elements
TEST_F(ExifDataTest_779, ClearRemovesAllElements_779) {
    exifData["Exif.Image.Make"] = "CameraA";
    exifData["Exif.Image.Model"] = "ModelB";
    EXPECT_EQ(exifData.count(), 2u);
    exifData.clear();
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);
    EXPECT_EQ(exifData.begin(), exifData.end());
}

// Test findKey finds an existing key
TEST_F(ExifDataTest_779, FindKeyExistingElement_779) {
    exifData["Exif.Image.Make"] = "TestCamera";
    Exiv2::ExifKey key("Exif.Image.Make");
    auto it = exifData.findKey(key);
    EXPECT_NE(it, exifData.end());
    EXPECT_EQ(it->toString(), "TestCamera");
}

// Test findKey returns end() for non-existing key
TEST_F(ExifDataTest_779, FindKeyNonExistingElement_779) {
    exifData["Exif.Image.Make"] = "TestCamera";
    Exiv2::ExifKey key("Exif.Image.Model");
    auto it = exifData.findKey(key);
    EXPECT_EQ(it, exifData.end());
}

// Test findKey on empty ExifData
TEST_F(ExifDataTest_779, FindKeyOnEmptyData_779) {
    Exiv2::ExifKey key("Exif.Image.Make");
    auto it = exifData.findKey(key);
    EXPECT_EQ(it, exifData.end());
}

// Test erase single element
TEST_F(ExifDataTest_779, EraseSingleElement_779) {
    exifData["Exif.Image.Make"] = "CameraA";
    exifData["Exif.Image.Model"] = "ModelB";
    EXPECT_EQ(exifData.count(), 2u);

    auto it = exifData.begin();
    exifData.erase(it);
    EXPECT_EQ(exifData.count(), 1u);
}

// Test erase range of elements
TEST_F(ExifDataTest_779, EraseRangeOfElements_779) {
    exifData["Exif.Image.Make"] = "CameraA";
    exifData["Exif.Image.Model"] = "ModelB";
    exifData["Exif.Image.Software"] = "SoftwareC";
    EXPECT_EQ(exifData.count(), 3u);

    exifData.erase(exifData.begin(), exifData.end());
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);
}

// Test erase with empty range does nothing
TEST_F(ExifDataTest_779, EraseEmptyRange_779) {
    exifData["Exif.Image.Make"] = "CameraA";
    EXPECT_EQ(exifData.count(), 1u);

    exifData.erase(exifData.begin(), exifData.begin());
    EXPECT_EQ(exifData.count(), 1u);
}

// Test sortByKey does not change count
TEST_F(ExifDataTest_779, SortByKeyPreservesCount_779) {
    exifData["Exif.Image.Software"] = "SoftwareC";
    exifData["Exif.Image.Make"] = "CameraA";
    exifData["Exif.Image.Model"] = "ModelB";
    EXPECT_EQ(exifData.count(), 3u);

    exifData.sortByKey();
    EXPECT_EQ(exifData.count(), 3u);
}

// Test sortByTag does not change count
TEST_F(ExifDataTest_779, SortByTagPreservesCount_779) {
    exifData["Exif.Image.Software"] = "SoftwareC";
    exifData["Exif.Image.Make"] = "CameraA";
    exifData["Exif.Image.Model"] = "ModelB";
    EXPECT_EQ(exifData.count(), 3u);

    exifData.sortByTag();
    EXPECT_EQ(exifData.count(), 3u);
}

// Test sortByKey on empty data does not crash
TEST_F(ExifDataTest_779, SortByKeyOnEmptyData_779) {
    exifData.sortByKey();
    EXPECT_TRUE(exifData.empty());
}

// Test sortByTag on empty data does not crash
TEST_F(ExifDataTest_779, SortByTagOnEmptyData_779) {
    exifData.sortByTag();
    EXPECT_TRUE(exifData.empty());
}

// Test sortByKey produces sorted order
TEST_F(ExifDataTest_779, SortByKeyProducesSortedOrder_779) {
    exifData["Exif.Image.Software"] = "SoftwareC";
    exifData["Exif.Image.Make"] = "CameraA";
    exifData["Exif.Image.Model"] = "ModelB";

    exifData.sortByKey();

    auto it = exifData.begin();
    std::string prev = it->key();
    ++it;
    while (it != exifData.end()) {
        EXPECT_LE(prev, it->key());
        prev = it->key();
        ++it;
    }
}

// Test iteration over elements
TEST_F(ExifDataTest_779, IterationOverElements_779) {
    exifData["Exif.Image.Make"] = "CameraA";
    exifData["Exif.Image.Model"] = "ModelB";

    size_t count = 0;
    for (auto it = exifData.begin(); it != exifData.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2u);
}

// Test that erasing all elements one by one results in empty
TEST_F(ExifDataTest_779, EraseAllOneByOne_779) {
    exifData["Exif.Image.Make"] = "CameraA";
    exifData["Exif.Image.Model"] = "ModelB";
    exifData["Exif.Image.Software"] = "SoftwareC";

    while (!exifData.empty()) {
        exifData.erase(exifData.begin());
    }
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);
}

// Test adding after clear
TEST_F(ExifDataTest_779, AddAfterClear_779) {
    exifData["Exif.Image.Make"] = "CameraA";
    exifData.clear();
    EXPECT_TRUE(exifData.empty());

    exifData["Exif.Image.Model"] = "ModelB";
    EXPECT_EQ(exifData.count(), 1u);
    EXPECT_FALSE(exifData.empty());
}

// Test findKey after erase
TEST_F(ExifDataTest_779, FindKeyAfterErase_779) {
    exifData["Exif.Image.Make"] = "CameraA";
    exifData["Exif.Image.Model"] = "ModelB";

    Exiv2::ExifKey key("Exif.Image.Make");
    auto it = exifData.findKey(key);
    ASSERT_NE(it, exifData.end());
    exifData.erase(it);

    auto it2 = exifData.findKey(key);
    EXPECT_EQ(it2, exifData.end());
    EXPECT_EQ(exifData.count(), 1u);
}

// Test const findKey
TEST_F(ExifDataTest_779, ConstFindKey_779) {
    exifData["Exif.Image.Make"] = "CameraA";

    const Exiv2::ExifData& constData = exifData;
    Exiv2::ExifKey key("Exif.Image.Make");
    auto it = constData.findKey(key);
    EXPECT_NE(it, constData.end());
    EXPECT_EQ(it->toString(), "CameraA");
}

// Test const empty and count
TEST_F(ExifDataTest_779, ConstEmptyAndCount_779) {
    const Exiv2::ExifData& constData = exifData;
    EXPECT_TRUE(constData.empty());
    EXPECT_EQ(constData.count(), 0u);

    exifData["Exif.Image.Make"] = "CameraA";
    EXPECT_FALSE(constData.empty());
    EXPECT_EQ(constData.count(), 1u);
}
