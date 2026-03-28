#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exiv2.hpp>
#include <string>
#include <vector>

using namespace Exiv2;

class ExifDataTest_777 : public ::testing::Test {
protected:
    ExifData exifData_;
};

// Test that a newly created ExifData is empty
TEST_F(ExifDataTest_777, DefaultConstructorCreatesEmptyData_777) {
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test adding an Exifdatum via add(const Exifdatum&)
TEST_F(ExifDataTest_777, AddExifdatumIncreasesCount_777) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    exifData_.add(datum);
    EXPECT_FALSE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test adding via add(const ExifKey&, const Value*)
TEST_F(ExifDataTest_777, AddKeyValueIncreasesCount_777) {
    ExifKey key("Exif.Image.Model");
    Value::UniquePtr val = Value::create(asciiString);
    val->read("TestCamera");
    exifData_.add(key, val.get());
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test adding multiple entries
TEST_F(ExifDataTest_777, AddMultipleEntries_777) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1);
    exifData_.add(datum1);

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2);
    exifData_.add(datum2);

    ExifKey key3("Exif.Image.Orientation");
    Exifdatum datum3(key3);
    exifData_.add(datum3);

    EXPECT_EQ(exifData_.count(), 3u);
}

// Test operator[] creates entry if not found
TEST_F(ExifDataTest_777, OperatorBracketCreatesEntry_777) {
    EXPECT_TRUE(exifData_.empty());
    Exifdatum& datum = exifData_["Exif.Image.Make"];
    EXPECT_FALSE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 1u);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test operator[] returns existing entry
TEST_F(ExifDataTest_777, OperatorBracketReturnsExistingEntry_777) {
    exifData_["Exif.Image.Make"] = "Canon";
    Exifdatum& datum = exifData_["Exif.Image.Make"];
    EXPECT_EQ(datum.toString(), "Canon");
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test findKey for existing key
TEST_F(ExifDataTest_777, FindKeyExistingReturnsIterator_777) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Nikon");
    exifData_.add(datum);

    ExifKey searchKey("Exif.Image.Make");
    auto it = exifData_.findKey(searchKey);
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->key(), "Exif.Image.Make");
}

// Test findKey for non-existing key returns end
TEST_F(ExifDataTest_777, FindKeyNonExistingReturnsEnd_777) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    exifData_.add(datum);

    ExifKey searchKey("Exif.Image.Model");
    auto it = exifData_.findKey(searchKey);
    EXPECT_EQ(it, exifData_.end());
}

// Test erase single element
TEST_F(ExifDataTest_777, EraseSingleElement_777) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1);
    exifData_.add(datum1);

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2);
    exifData_.add(datum2);

    EXPECT_EQ(exifData_.count(), 2u);
    auto it = exifData_.begin();
    exifData_.erase(it);
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test erase range
TEST_F(ExifDataTest_777, EraseRange_777) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1);
    exifData_.add(datum1);

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2);
    exifData_.add(datum2);

    ExifKey key3("Exif.Image.Orientation");
    Exifdatum datum3(key3);
    exifData_.add(datum3);

    EXPECT_EQ(exifData_.count(), 3u);
    exifData_.erase(exifData_.begin(), exifData_.end());
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test clear
TEST_F(ExifDataTest_777, ClearRemovesAllEntries_777) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1);
    exifData_.add(datum1);

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2);
    exifData_.add(datum2);

    EXPECT_EQ(exifData_.count(), 2u);
    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test clear on already empty data
TEST_F(ExifDataTest_777, ClearOnEmptyData_777) {
    EXPECT_TRUE(exifData_.empty());
    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test begin == end for empty data
TEST_F(ExifDataTest_777, BeginEqualsEndWhenEmpty_777) {
    EXPECT_EQ(exifData_.begin(), exifData_.end());
}

// Test iteration over elements
TEST_F(ExifDataTest_777, IterationOverElements_777) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1);
    datum1.setValue("Canon");
    exifData_.add(datum1);

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2);
    datum2.setValue("EOS 5D");
    exifData_.add(datum2);

    size_t count = 0;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 2u);
}

// Test sortByKey
TEST_F(ExifDataTest_777, SortByKeyOrdersEntries_777) {
    ExifKey key1("Exif.Image.Model");
    Exifdatum datum1(key1);
    exifData_.add(datum1);

    ExifKey key2("Exif.Image.Make");
    Exifdatum datum2(key2);
    exifData_.add(datum2);

    exifData_.sortByKey();

    auto it = exifData_.begin();
    std::string firstKey = it->key();
    ++it;
    std::string secondKey = it->key();
    EXPECT_LE(firstKey, secondKey);
}

// Test sortByTag
TEST_F(ExifDataTest_777, SortByTagOrdersEntries_777) {
    ExifKey key1("Exif.Image.Model");
    Exifdatum datum1(key1);
    exifData_.add(datum1);

    ExifKey key2("Exif.Image.Make");
    Exifdatum datum2(key2);
    exifData_.add(datum2);

    exifData_.sortByTag();

    auto it = exifData_.begin();
    uint16_t firstTag = it->tag();
    ++it;
    uint16_t secondTag = it->tag();
    EXPECT_LE(firstTag, secondTag);
}

// Test Exifdatum key properties
TEST_F(ExifDataTest_777, ExifdatumKeyProperties_777) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);

    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_STREQ(datum.familyName(), "Exif");
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test Exifdatum setValue with string
TEST_F(ExifDataTest_777, ExifdatumSetValueString_777) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    int result = datum.setValue("TestValue");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "TestValue");
}

// Test Exifdatum assignment operator with string
TEST_F(ExifDataTest_777, ExifdatumAssignString_777) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("AssignedValue");
    EXPECT_EQ(datum.toString(), "AssignedValue");
}

// Test Exifdatum assignment with uint16_t
TEST_F(ExifDataTest_777, ExifdatumAssignUint16_777) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ(datum.toInt64(0), 1);
}

// Test Exifdatum assignment with uint32_t
TEST_F(ExifDataTest_777, ExifdatumAssignUint32_777) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    datum = static_cast<uint32_t>(1920);
    EXPECT_EQ(datum.toInt64(0), 1920);
}

// Test Exifdatum assignment with int16_t
TEST_F(ExifDataTest_777, ExifdatumAssignInt16_777) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    datum = static_cast<int16_t>(-5);
    EXPECT_EQ(datum.toInt64(0), -5);
}

// Test Exifdatum assignment with int32_t
TEST_F(ExifDataTest_777, ExifdatumAssignInt32_777) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    datum = static_cast<int32_t>(-100);
    EXPECT_EQ(datum.toInt64(0), -100);
}

// Test Exifdatum assignment with URational
TEST_F(ExifDataTest_777, ExifdatumAssignURational_777) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key);
    URational ur(72, 1);
    datum = ur;
    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, 72);
    EXPECT_EQ(r.second, 1);
}

// Test Exifdatum assignment with Rational
TEST_F(ExifDataTest_777, ExifdatumAssignRational_777) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key);
    Rational rat(-1, 3);
    datum = rat;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 3);
}

// Test Exifdatum copy constructor
TEST_F(ExifDataTest_777, ExifdatumCopyConstructor_777) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum1(key);
    datum1.setValue("CopyTest");

    Exifdatum datum2(datum1);
    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "CopyTest");
}

// Test Exifdatum copy assignment
TEST_F(ExifDataTest_777, ExifdatumCopyAssignment_777) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1);
    datum1.setValue("Original");

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2);
    datum2.setValue("OtherValue");

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "Original");
}

// Test Exifdatum count after setting value
TEST_F(ExifDataTest_777, ExifdatumCountAfterSetValue_777) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("TestCount");
    EXPECT_GE(datum.count(), 1u);
    EXPECT_GT(datum.size(), 0u);
}

// Test Exifdatum typeId after uint16_t assignment
TEST_F(ExifDataTest_777, ExifdatumTypeIdUnsignedShort_777) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    datum = static_cast<uint16_t>(3);
    EXPECT_EQ(datum.typeId(), unsignedShort);
}

// Test Exifdatum getValue returns non-null after setting
TEST_F(ExifDataTest_777, ExifdatumGetValueNonNull_777) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("GetValueTest");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "GetValueTest");
}

// Test Exifdatum toFloat
TEST_F(ExifDataTest_777, ExifdatumToFloat_777) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key);
    URational ur(72, 1);
    datum = ur;
    float f = datum.toFloat(0);
    EXPECT_FLOAT_EQ(f, 72.0f);
}

// Test findKey on const ExifData
TEST_F(ExifDataTest_777, FindKeyConst_777) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("ConstTest");
    exifData_.add(datum);

    const ExifData& constData = exifData_;
    ExifKey searchKey("Exif.Image.Make");
    auto it = constData.findKey(searchKey);
    ASSERT_NE(it, constData.end());
    EXPECT_EQ(it->toString(), "ConstTest");
}

// Test erase returns valid iterator
TEST_F(ExifDataTest_777, EraseReturnsValidIterator_777) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1);
    datum1.setValue("First");
    exifData_.add(datum1);

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2);
    datum2.setValue("Second");
    exifData_.add(datum2);

    auto it = exifData_.erase(exifData_.begin());
    EXPECT_EQ(exifData_.count(), 1u);
    if (it != exifData_.end()) {
        EXPECT_FALSE(it->key().empty());
    }
}

// Test adding null value via add(key, nullptr)
TEST_F(ExifDataTest_777, AddKeyWithNullValue_777) {
    ExifKey key("Exif.Image.Make");
    exifData_.add(key, nullptr);
    EXPECT_EQ(exifData_.count(), 1u);
}

// Test tag() returns correct tag number
TEST_F(ExifDataTest_777, ExifdatumTagNumber_777) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    // Make tag is 0x010f
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test that adding the same key twice results in two entries
TEST_F(ExifDataTest_777, AddDuplicateKeys_777) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum1(key);
    datum1.setValue("First");
    exifData_.add(datum1);

    Exifdatum datum2(key);
    datum2.setValue("Second");
    exifData_.add(datum2);

    EXPECT_EQ(exifData_.count(), 2u);
}

// Test operator[] with the same key doesn't add duplicate
TEST_F(ExifDataTest_777, OperatorBracketNoDuplicate_777) {
    exifData_["Exif.Image.Make"] = "First";
    exifData_["Exif.Image.Make"] = "Second";
    EXPECT_EQ(exifData_.count(), 1u);
    EXPECT_EQ(exifData_["Exif.Image.Make"].toString(), "Second");
}
