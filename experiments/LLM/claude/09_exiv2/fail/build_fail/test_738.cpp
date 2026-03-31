#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <memory>

using namespace Exiv2;

class ExifdatumTest_738 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a known ExifKey
TEST_F(ExifdatumTest_738, ConstructWithExifKey_738) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Exif.Image.Make", datum.key());
    EXPECT_EQ("Exif", std::string(datum.familyName()));
    EXPECT_EQ("Image", datum.groupName());
    EXPECT_EQ("Make", datum.tagName());
}

// Test construction with a value
TEST_F(ExifdatumTest_738, ConstructWithValue_738) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    EXPECT_EQ("Canon", datum.toString());
    EXPECT_EQ(1u, datum.count());
}

// Test copy constructor
TEST_F(ExifdatumTest_738, CopyConstructor_738) {
    ExifKey key("Exif.Image.Model");
    AsciiValue val;
    val.read("EOS 5D");
    Exifdatum original(key, &val);
    Exifdatum copy(original);
    EXPECT_EQ(original.key(), copy.key());
    EXPECT_EQ(original.toString(), copy.toString());
}

// Test copy assignment operator
TEST_F(ExifdatumTest_738, CopyAssignment_738) {
    ExifKey key1("Exif.Image.Make");
    AsciiValue val1;
    val1.read("Canon");
    Exifdatum datum1(key1, &val1);

    ExifKey key2("Exif.Image.Model");
    AsciiValue val2;
    val2.read("EOS R");
    Exifdatum datum2(key2, &val2);

    datum2 = datum1;
    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
}

// Test assignment from string
TEST_F(ExifdatumTest_738, AssignFromString_738) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Initial");
    Exifdatum datum(key, &val);
    datum = std::string("Nikon");
    EXPECT_EQ("Nikon", datum.toString());
}

// Test assignment from uint16_t
TEST_F(ExifdatumTest_738, AssignFromUint16_738) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);
    uint16_t newVal = 6;
    datum = newVal;
    EXPECT_EQ(6, datum.toInt64(0));
}

// Test assignment from uint32_t
TEST_F(ExifdatumTest_738, AssignFromUint32_738) {
    ExifKey key("Exif.Image.ImageWidth");
    ULongValue val;
    val.read("100");
    Exifdatum datum(key, &val);
    uint32_t newVal = 4000;
    datum = newVal;
    EXPECT_EQ(4000, datum.toInt64(0));
}

// Test assignment from int16_t
TEST_F(ExifdatumTest_738, AssignFromInt16_738) {
    ExifKey key("Exif.Image.Orientation");
    ShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);
    int16_t newVal = -5;
    datum = newVal;
    EXPECT_EQ(-5, datum.toInt64(0));
}

// Test assignment from int32_t
TEST_F(ExifdatumTest_738, AssignFromInt32_738) {
    ExifKey key("Exif.Image.ImageWidth");
    LongValue val;
    val.read("100");
    Exifdatum datum(key, &val);
    int32_t newVal = -1000;
    datum = newVal;
    EXPECT_EQ(-1000, datum.toInt64(0));
}

// Test assignment from URational
TEST_F(ExifdatumTest_738, AssignFromURational_738) {
    ExifKey key("Exif.Image.XResolution");
    URationalValue val;
    val.read("72/1");
    Exifdatum datum(key, &val);
    URational newVal(300, 1);
    datum = newVal;
    EXPECT_EQ(URational(300, 1), datum.toRational(0));
}

// Test assignment from Rational
TEST_F(ExifdatumTest_738, AssignFromRational_738) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    RationalValue val;
    val.read("0/1");
    Exifdatum datum(key, &val);
    Rational newVal(-1, 3);
    datum = newVal;
    Rational result = datum.toRational(0);
    EXPECT_EQ(-1, result.first);
    EXPECT_EQ(3, result.second);
}

// Test assignment from Value
TEST_F(ExifdatumTest_738, AssignFromValue_738) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);

    AsciiValue newVal;
    newVal.read("Nikon");
    datum = static_cast<const Value&>(newVal);
    EXPECT_EQ("Nikon", datum.toString());
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_738, SetValueWithPointer_738) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    AsciiValue val;
    val.read("Sony");
    datum.setValue(&val);
    EXPECT_EQ("Sony", datum.toString());
}

// Test setValue with nullptr
TEST_F(ExifdatumTest_738, SetValueWithNullptr_738) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);

    datum.setValue(nullptr);
    // After setting nullptr, count should be 0
    EXPECT_EQ(0u, datum.count());
}

// Test setValue with string
TEST_F(ExifdatumTest_738, SetValueWithString_738) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);

    int result = datum.setValue("3");
    EXPECT_EQ(0, result);
    EXPECT_EQ(3, datum.toInt64(0));
}

// Test key() returns correct key string
TEST_F(ExifdatumTest_738, KeyReturnsCorrectString_738) {
    ExifKey key("Exif.Photo.DateTimeOriginal");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Exif.Photo.DateTimeOriginal", datum.key());
}

// Test familyName() returns "Exif"
TEST_F(ExifdatumTest_738, FamilyNameReturnsExif_738) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_STREQ("Exif", datum.familyName());
}

// Test groupName()
TEST_F(ExifdatumTest_738, GroupName_738) {
    ExifKey key("Exif.Photo.ISOSpeedRatings");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Photo", datum.groupName());
}

// Test tagName()
TEST_F(ExifdatumTest_738, TagName_738) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Make", datum.tagName());
}

// Test tag() returns correct tag number
TEST_F(ExifdatumTest_738, TagNumber_738) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(0x010f, datum.tag());
}

// Test typeId() with no value set
TEST_F(ExifdatumTest_738, TypeIdNoValue_738) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Without a value, typeId should be undefined
    EXPECT_EQ(unsignedByte, datum.typeId());
}

// Test typeId() with a value set
TEST_F(ExifdatumTest_738, TypeIdWithValue_738) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Test");
    Exifdatum datum(key, &val);
    EXPECT_EQ(asciiString, datum.typeId());
}

// Test count() with value
TEST_F(ExifdatumTest_738, CountWithValue_738) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);
    EXPECT_EQ(1u, datum.count());
}

// Test count() without value
TEST_F(ExifdatumTest_738, CountWithoutValue_738) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(0u, datum.count());
}

// Test size() with value
TEST_F(ExifdatumTest_738, SizeWithValue_738) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    EXPECT_GT(datum.size(), 0u);
}

// Test size() without value
TEST_F(ExifdatumTest_738, SizeWithoutValue_738) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(0u, datum.size());
}

// Test toString()
TEST_F(ExifdatumTest_738, ToString_738) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Fujifilm");
    Exifdatum datum(key, &val);
    EXPECT_EQ("Fujifilm", datum.toString());
}

// Test toString(n)
TEST_F(ExifdatumTest_738, ToStringWithIndex_738) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Pentax");
    Exifdatum datum(key, &val);
    EXPECT_EQ("Pentax", datum.toString(0));
}

// Test toInt64()
TEST_F(ExifdatumTest_738, ToInt64_738) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("8");
    Exifdatum datum(key, &val);
    EXPECT_EQ(8, datum.toInt64(0));
}

// Test toFloat()
TEST_F(ExifdatumTest_738, ToFloat_738) {
    ExifKey key("Exif.Image.XResolution");
    URationalValue val;
    val.read("72/1");
    Exifdatum datum(key, &val);
    EXPECT_FLOAT_EQ(72.0f, datum.toFloat(0));
}

// Test toRational()
TEST_F(ExifdatumTest_738, ToRational_738) {
    ExifKey key("Exif.Image.XResolution");
    URationalValue val;
    val.read("300/1");
    Exifdatum datum(key, &val);
    Rational r = datum.toRational(0);
    EXPECT_EQ(300, r.first);
    EXPECT_EQ(1, r.second);
}

// Test getValue() returns a clone of the value
TEST_F(ExifdatumTest_738, GetValueReturnsClone_738) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Olympus");
    Exifdatum datum(key, &val);
    auto clonedValue = datum.getValue();
    ASSERT_NE(clonedValue, nullptr);
    EXPECT_EQ("Olympus", clonedValue->toString());
}

// Test getValue() when no value is set
TEST_F(ExifdatumTest_738, GetValueWithoutValue_738) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    auto val = datum.getValue();
    // Should return nullptr or throw; test accordingly
    EXPECT_EQ(val, nullptr);
}

// Test idx()
TEST_F(ExifdatumTest_738, IdxDefault_738) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Default idx should be 0
    EXPECT_EQ(0, datum.idx());
}

// Test copy() writes data to buffer
TEST_F(ExifdatumTest_738, CopyToBuffer_738) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);

    byte buf[16] = {};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test write() to ostream
TEST_F(ExifdatumTest_738, WriteToOstream_738) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Leica");
    Exifdatum datum(key, &val);

    std::ostringstream oss;
    datum.write(oss, nullptr);
    EXPECT_FALSE(oss.str().empty());
}

// Test sizeDataArea() with no data area
TEST_F(ExifdatumTest_738, SizeDataAreaEmpty_738) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Test");
    Exifdatum datum(key, &val);
    EXPECT_EQ(0u, datum.sizeDataArea());
}

// Test tagLabel() returns a non-empty string for known tags
TEST_F(ExifdatumTest_738, TagLabelNonEmpty_738) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test typeName() with ASCII value
TEST_F(ExifdatumTest_738, TypeNameAscii_738) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Test");
    Exifdatum datum(key, &val);
    EXPECT_STREQ("Ascii", datum.typeName());
}

// Test typeSize() with UShort value
TEST_F(ExifdatumTest_738, TypeSizeUShort_738) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);
    EXPECT_EQ(2u, datum.typeSize());
}

// Test multiple assignment operations on same datum
TEST_F(ExifdatumTest_738, MultipleAssignments_738) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);

    uint16_t v1 = 3;
    datum = v1;
    EXPECT_EQ(3, datum.toInt64(0));

    uint16_t v2 = 6;
    datum = v2;
    EXPECT_EQ(6, datum.toInt64(0));

    uint16_t v3 = 8;
    datum = v3;
    EXPECT_EQ(8, datum.toInt64(0));
}

// Test self-assignment
TEST_F(ExifdatumTest_738, SelfAssignment_738) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);

    datum = datum;
    EXPECT_EQ("Canon", datum.toString());
    EXPECT_EQ("Exif.Image.Make", datum.key());
}

// Test with ExifData container (basic usage)
TEST_F(ExifdatumTest_738, ExifDataBasicUsage_738) {
    ExifData exifData;
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("TestBrand");
    exifData.add(key, &val);

    auto it = exifData.findKey(key);
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ("TestBrand", it->toString());
}

// Test ExifData empty check
TEST_F(ExifdatumTest_738, ExifDataEmpty_738) {
    ExifData exifData;
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(0u, exifData.count());
}

// Test ExifData add and count
TEST_F(ExifdatumTest_738, ExifDataAddAndCount_738) {
    ExifData exifData;
    ExifKey key1("Exif.Image.Make");
    AsciiValue val1;
    val1.read("Canon");
    exifData.add(key1, &val1);

    ExifKey key2("Exif.Image.Model");
    AsciiValue val2;
    val2.read("EOS 5D");
    exifData.add(key2, &val2);

    EXPECT_FALSE(exifData.empty());
    EXPECT_EQ(2u, exifData.count());
}

// Test ExifData findKey returns end for non-existent key
TEST_F(ExifdatumTest_738, ExifDataFindKeyNotFound_738) {
    ExifData exifData;
    ExifKey key("Exif.Image.Make");
    auto it = exifData.findKey(key);
    EXPECT_EQ(it, exifData.end());
}

// Test ExifData erase
TEST_F(ExifdatumTest_738, ExifDataErase_738) {
    ExifData exifData;
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    exifData.add(key, &val);

    auto it = exifData.findKey(key);
    ASSERT_NE(it, exifData.end());
    exifData.erase(it);
    EXPECT_TRUE(exifData.empty());
}

// Test ExifData clear
TEST_F(ExifdatumTest_738, ExifDataClear_738) {
    ExifData exifData;
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    exifData.add(key, &val);
    exifData.clear();
    EXPECT_TRUE(exifData.empty());
}
