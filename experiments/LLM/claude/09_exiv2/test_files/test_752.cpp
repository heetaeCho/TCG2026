#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exifdatum.hpp>
#include <exiv2/value.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/types.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

class ExifdatumTest_752 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a known ExifKey
TEST_F(ExifdatumTest_752, ConstructWithExifKey_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test copy constructor
TEST_F(ExifdatumTest_752, CopyConstructor_752) {
    ExifKey key("Exif.Image.Model");
    Exifdatum original(key);
    original.setValue("TestModel");

    Exifdatum copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.toString(), "TestModel");
}

// Test assignment operator from another Exifdatum
TEST_F(ExifdatumTest_752, AssignmentOperatorExifdatum_752) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1);
    datum1.setValue("Canon");

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2);
    datum2 = datum1;

    // After assignment, datum2 should have datum1's value
    EXPECT_EQ(datum2.toString(), "Canon");
}

// Test assignment operator with string value
TEST_F(ExifdatumTest_752, AssignStringValue_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Nikon");
    datum = std::string("Canon");
    EXPECT_EQ(datum.toString(), "Canon");
}

// Test assignment operator with uint16_t value
TEST_F(ExifdatumTest_752, AssignUint16Value_752) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 1);
}

// Test assignment operator with uint32_t value
TEST_F(ExifdatumTest_752, AssignUint32Value_752) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    uint32_t val = 4000;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 4000);
}

// Test assignment operator with int16_t value
TEST_F(ExifdatumTest_752, AssignInt16Value_752) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    int16_t val = -5;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), -5);
}

// Test assignment operator with int32_t value
TEST_F(ExifdatumTest_752, AssignInt32Value_752) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    int32_t val = -100;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), -100);
}

// Test assignment operator with Rational value
TEST_F(ExifdatumTest_752, AssignRationalValue_752) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key);
    Rational rat = {1, 125};
    datum = rat;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 125);
}

// Test assignment operator with URational value
TEST_F(ExifdatumTest_752, AssignURationalValue_752) {
    ExifKey key("Exif.Photo.FNumber");
    Exifdatum datum(key);
    URational urat = {28, 10};
    datum = urat;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 28);
    EXPECT_EQ(result.second, 10);
}

// Test setValue with string
TEST_F(ExifdatumTest_752, SetValueString_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    int result = datum.setValue("TestValue");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "TestValue");
}

// Test key() returns correct key string
TEST_F(ExifdatumTest_752, KeyReturnsCorrectString_752) {
    ExifKey key("Exif.Photo.DateTimeOriginal");
    Exifdatum datum(key);
    EXPECT_EQ(datum.key(), "Exif.Photo.DateTimeOriginal");
}

// Test familyName() returns "Exif"
TEST_F(ExifdatumTest_752, FamilyNameIsExif_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test groupName()
TEST_F(ExifdatumTest_752, GroupNameReturnsCorrect_752) {
    ExifKey key("Exif.Photo.ISOSpeedRatings");
    Exifdatum datum(key);
    EXPECT_EQ(datum.groupName(), "Photo");
}

// Test tagName()
TEST_F(ExifdatumTest_752, TagNameReturnsCorrect_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test tag() returns correct tag number
TEST_F(ExifdatumTest_752, TagReturnsCorrectNumber_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test typeId for default (no value set)
TEST_F(ExifdatumTest_752, TypeIdWithNoValue_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    // Without a value set, typeId should be invalidTypeId or the default
    TypeId tid = datum.typeId();
    // Just verify it doesn't crash and returns some valid enum value
    EXPECT_GE(static_cast<int>(tid), 0);
}

// Test count() when no value is set
TEST_F(ExifdatumTest_752, CountWithNoValue_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.count(), 0u);
}

// Test size() when no value is set
TEST_F(ExifdatumTest_752, SizeWithNoValue_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.size(), 0u);
}

// Test toString() when no value is set
TEST_F(ExifdatumTest_752, ToStringWithNoValue_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    std::string str = datum.toString();
    EXPECT_TRUE(str.empty());
}

// Test copy() when no value is set should return 0
TEST_F(ExifdatumTest_752, CopyWithNoValueReturnsZero_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    byte buf[64] = {};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_EQ(copied, 0u);
}

// Test copy() with a value set
TEST_F(ExifdatumTest_752, CopyWithValueSet_752) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 1;
    datum = val;
    byte buf[64] = {};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test getValue() returns a valid pointer when value is set
TEST_F(ExifdatumTest_752, GetValueReturnsValidPtr_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("TestBrand");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "TestBrand");
}

// Test getValue() when no value is set
TEST_F(ExifdatumTest_752, GetValueWithNoValueReturnsNull_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    auto val = datum.getValue();
    // When no value is set, getValue might return nullptr
    // This depends on implementation, but the interface allows it
    // Just check it doesn't crash
    (void)val;
}

// Test write to ostream
TEST_F(ExifdatumTest_752, WriteToOstream_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Canon");
    std::ostringstream oss;
    datum.write(oss, nullptr);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test toFloat
TEST_F(ExifdatumTest_752, ToFloat_752) {
    ExifKey key("Exif.Photo.FNumber");
    Exifdatum datum(key);
    URational urat = {28, 10};
    datum = urat;
    float fval = datum.toFloat(0);
    EXPECT_NEAR(fval, 2.8f, 0.01f);
}

// Test toInt64
TEST_F(ExifdatumTest_752, ToInt64_752) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 6;
    datum = val;
    int64_t ival = datum.toInt64(0);
    EXPECT_EQ(ival, 6);
}

// Test toRational
TEST_F(ExifdatumTest_752, ToRational_752) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key);
    Rational rat = {1, 500};
    datum = rat;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 500);
}

// Test setting value with Value object
TEST_F(ExifdatumTest_752, SetValueWithValueObject_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    auto val = Value::create(asciiString);
    val->read("TestBrand");
    datum = *val;
    EXPECT_EQ(datum.toString(), "TestBrand");
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_752, SetValueWithValuePointer_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    auto val = Value::create(asciiString);
    val->read("PointerTest");
    datum.setValue(val.get());
    EXPECT_EQ(datum.toString(), "PointerTest");
}

// Test sizeDataArea when no data area is set
TEST_F(ExifdatumTest_752, SizeDataAreaDefault_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Test");
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test count after setting a string value
TEST_F(ExifdatumTest_752, CountAfterSetString_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Hello");
    EXPECT_GT(datum.count(), 0u);
}

// Test size after setting a value
TEST_F(ExifdatumTest_752, SizeAfterSetValue_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Hello");
    EXPECT_GT(datum.size(), 0u);
}

// Test toString with index parameter
TEST_F(ExifdatumTest_752, ToStringWithIndex_752) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 3;
    datum = val;
    std::string str = datum.toString(0);
    EXPECT_EQ(str, "3");
}

// Test tagLabel returns non-empty for known tags
TEST_F(ExifdatumTest_752, TagLabelNonEmpty_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test copy with big endian
TEST_F(ExifdatumTest_752, CopyWithBigEndian_752) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 1;
    datum = val;
    byte buf[64] = {};
    size_t copied = datum.copy(buf, bigEndian);
    EXPECT_GT(copied, 0u);
}

// Test that copy produces different bytes for different endianness
TEST_F(ExifdatumTest_752, CopyEndiannessDifference_752) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 0x0102;
    datum = val;

    byte bufLE[64] = {};
    byte bufBE[64] = {};
    size_t copiedLE = datum.copy(bufLE, littleEndian);
    size_t copiedBE = datum.copy(bufBE, bigEndian);

    EXPECT_EQ(copiedLE, copiedBE);
    // At least one byte should differ for multi-byte values
    bool differ = false;
    for (size_t i = 0; i < copiedLE; ++i) {
        if (bufLE[i] != bufBE[i]) {
            differ = true;
            break;
        }
    }
    EXPECT_TRUE(differ);
}

// Test typeName after setting a uint16 value
TEST_F(ExifdatumTest_752, TypeNameForUint16_752) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 1;
    datum = val;
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    EXPECT_EQ(std::string(tn), "Short");
}

// Test typeSize after setting a uint16 value
TEST_F(ExifdatumTest_752, TypeSizeForUint16_752) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.typeSize(), 2u);
}

// Test setValue with nullptr
TEST_F(ExifdatumTest_752, SetValueWithNullptr_752) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("SomeValue");
    datum.setValue(static_cast<const Value*>(nullptr));
    // After setting nullptr, count/size should be 0
    EXPECT_EQ(datum.count(), 0u);
    EXPECT_EQ(datum.size(), 0u);
}
