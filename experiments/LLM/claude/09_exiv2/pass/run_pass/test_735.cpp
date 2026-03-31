#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/exif.hpp>
#include <string>
#include <cstdint>

class ExifdatumTest_735 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a known ExifKey
TEST_F(ExifdatumTest_735, ConstructWithExifKey_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test copy constructor
TEST_F(ExifdatumTest_735, CopyConstructor_735) {
    Exiv2::ExifKey key("Exif.Image.Model");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("TestModel");

    Exiv2::Exifdatum copy(datum);
    EXPECT_EQ(copy.key(), "Exif.Image.Model");
    EXPECT_EQ(copy.toString(), "TestModel");
}

// Test copy assignment operator
TEST_F(ExifdatumTest_735, CopyAssignmentOperator_735) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::Exifdatum datum1(key1, nullptr);
    datum1 = std::string("Canon");

    Exiv2::ExifKey key2("Exif.Image.Model");
    Exiv2::Exifdatum datum2(key2, nullptr);
    datum2 = datum1;

    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "Canon");
}

// Test assignment of string value
TEST_F(ExifdatumTest_735, AssignStringValue_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Nikon");
    EXPECT_EQ(datum.toString(), "Nikon");
    EXPECT_EQ(datum.count(), 1u);
}

// Test assignment of uint16_t value
TEST_F(ExifdatumTest_735, AssignUint16Value_735) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 1);
    EXPECT_EQ(datum.typeId(), Exiv2::unsignedShort);
}

// Test assignment of uint32_t value
TEST_F(ExifdatumTest_735, AssignUint32Value_735) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    uint32_t val = 1920;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 1920);
    EXPECT_EQ(datum.typeId(), Exiv2::unsignedLong);
}

// Test assignment of int16_t value
TEST_F(ExifdatumTest_735, AssignInt16Value_735) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    int16_t val = -5;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), -5);
    EXPECT_EQ(datum.typeId(), Exiv2::signedShort);
}

// Test assignment of int32_t value
TEST_F(ExifdatumTest_735, AssignInt32Value_735) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    int32_t val = -100;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), -100);
    EXPECT_EQ(datum.typeId(), Exiv2::signedLong);
}

// Test assignment of URational value
TEST_F(ExifdatumTest_735, AssignURationalValue_735) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::URational val(1, 100);
    datum = val;
    EXPECT_EQ(datum.toRational(0), Exiv2::Rational(1, 100));
}

// Test assignment of Rational value
TEST_F(ExifdatumTest_735, AssignRationalValue_735) {
    Exiv2::ExifKey key("Exif.Photo.ExposureBiasValue");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::Rational val(-1, 3);
    datum = val;
    EXPECT_EQ(datum.toRational(0).first, -1);
    EXPECT_EQ(datum.toRational(0).second, 3);
    EXPECT_EQ(datum.typeId(), Exiv2::signedRational);
}

// Test key() method
TEST_F(ExifdatumTest_735, KeyMethod_735) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Photo.DateTimeOriginal");
}

// Test familyName() method
TEST_F(ExifdatumTest_735, FamilyNameMethod_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test groupName() method
TEST_F(ExifdatumTest_735, GroupNameMethod_735) {
    Exiv2::ExifKey key("Exif.Photo.ISOSpeedRatings");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Photo");
}

// Test tagName() method
TEST_F(ExifdatumTest_735, TagNameMethod_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test tag() method
TEST_F(ExifdatumTest_735, TagMethod_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    // Make tag is 0x010f
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test typeId when no value is set
TEST_F(ExifdatumTest_735, TypeIdNoValue_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    // With no value set, typeId should be unsignedByte or some default
    EXPECT_EQ(datum.typeId(), Exiv2::invalidTypeId);
}

// Test count when no value is set
TEST_F(ExifdatumTest_735, CountNoValue_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test size when no value is set
TEST_F(ExifdatumTest_735, SizeNoValue_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test setValue with string
TEST_F(ExifdatumTest_735, SetValueString_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    int result = datum.setValue("TestValue");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "TestValue");
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_735, SetValueWithValuePtr_735) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::UShortValue val;
    val.value_.push_back(3);
    datum.setValue(&val);
    EXPECT_EQ(datum.toInt64(0), 3);
    EXPECT_EQ(datum.typeId(), Exiv2::unsignedShort);
}

// Test setValue with nullptr clears value
TEST_F(ExifdatumTest_735, SetValueNullptr_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Test");
    EXPECT_EQ(datum.count(), 1u);
    datum.setValue(nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test getValue returns a unique_ptr to a copy of the value
TEST_F(ExifdatumTest_735, GetValue_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Canon");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "Canon");
}

// Test getValue when no value set
TEST_F(ExifdatumTest_735, GetValueNoValueSet_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    auto val = datum.getValue();
    EXPECT_EQ(val, nullptr);
}

// Test toFloat
TEST_F(ExifdatumTest_735, ToFloat_735) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = 42;
    datum = val;
    EXPECT_FLOAT_EQ(datum.toFloat(0), 42.0f);
}

// Test toInt64
TEST_F(ExifdatumTest_735, ToInt64_735) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    int32_t val = -999;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), -999);
}

// Test toString with index
TEST_F(ExifdatumTest_735, ToStringWithIndex_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("TestMake");
    std::string result = datum.toString(0);
    EXPECT_EQ(result, "TestMake");
}

// Test sizeDataArea when no data area
TEST_F(ExifdatumTest_735, SizeDataAreaEmpty_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Test");
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test assignment with Value object
TEST_F(ExifdatumTest_735, AssignValueObject_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::AsciiValue asciiVal;
    asciiVal.read("HelloWorld");
    datum = static_cast<const Exiv2::Value&>(asciiVal);
    EXPECT_EQ(datum.toString(), "HelloWorld");
}

// Test constructing with a Value pointer
TEST_F(ExifdatumTest_735, ConstructWithValue_735) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::UShortValue val;
    val.value_.push_back(6);
    Exiv2::Exifdatum datum(key, &val);
    EXPECT_EQ(datum.toInt64(0), 6);
    EXPECT_EQ(datum.count(), 1u);
}

// Test idx method
TEST_F(ExifdatumTest_735, IdxMethod_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    // idx should have a default value (likely 0)
    EXPECT_GE(datum.idx(), 0);
}

// Test typeName when value is set
TEST_F(ExifdatumTest_735, TypeNameWithValue_735) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    EXPECT_STREQ(datum.typeName(), "SHORT");
}

// Test typeSize when value is set
TEST_F(ExifdatumTest_735, TypeSizeWithValue_735) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.typeSize(), 2u);
}

// Test tagLabel returns non-empty string for known tags
TEST_F(ExifdatumTest_735, TagLabel_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test ExifData container operations
TEST_F(ExifdatumTest_735, ExifDataAddAndFind_735) {
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("TestCamera");
    exifData.add(datum);

    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ(it->toString(), "TestCamera");
}

// Test ExifData with multiple entries
TEST_F(ExifdatumTest_735, ExifDataMultipleEntries_735) {
    Exiv2::ExifData exifData;

    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::Exifdatum datum1(key1, nullptr);
    datum1 = std::string("Canon");
    exifData.add(datum1);

    Exiv2::ExifKey key2("Exif.Image.Model");
    Exiv2::Exifdatum datum2(key2, nullptr);
    datum2 = std::string("EOS R5");
    exifData.add(datum2);

    EXPECT_EQ(exifData.count(), 2u);

    auto it1 = exifData.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    ASSERT_NE(it1, exifData.end());
    EXPECT_EQ(it1->toString(), "Canon");

    auto it2 = exifData.findKey(Exiv2::ExifKey("Exif.Image.Model"));
    ASSERT_NE(it2, exifData.end());
    EXPECT_EQ(it2->toString(), "EOS R5");
}

// Test overwriting value via assignment
TEST_F(ExifdatumTest_735, OverwriteValue_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("First");
    EXPECT_EQ(datum.toString(), "First");
    datum = std::string("Second");
    EXPECT_EQ(datum.toString(), "Second");
}

// Test assigning different types sequentially
TEST_F(ExifdatumTest_735, AssignDifferentTypes_735) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);

    uint16_t uval = 5;
    datum = uval;
    EXPECT_EQ(datum.toInt64(0), 5);
    EXPECT_EQ(datum.typeId(), Exiv2::unsignedShort);

    int32_t ival = -10;
    datum = ival;
    EXPECT_EQ(datum.toInt64(0), -10);
    EXPECT_EQ(datum.typeId(), Exiv2::signedLong);
}

// Test boundary: uint16_t max value
TEST_F(ExifdatumTest_735, Uint16MaxValue_735) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = UINT16_MAX;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), UINT16_MAX);
}

// Test boundary: int16_t min value
TEST_F(ExifdatumTest_735, Int16MinValue_735) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    int16_t val = INT16_MIN;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), INT16_MIN);
}

// Test boundary: uint32_t max value
TEST_F(ExifdatumTest_735, Uint32MaxValue_735) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    uint32_t val = UINT32_MAX;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), UINT32_MAX);
}

// Test boundary: int32_t min value
TEST_F(ExifdatumTest_735, Int32MinValue_735) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    int32_t val = INT32_MIN;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), INT32_MIN);
}

// Test boundary: zero values
TEST_F(ExifdatumTest_735, ZeroValues_735) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = 0;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 0);
}

// Test boundary: empty string
TEST_F(ExifdatumTest_735, EmptyString_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("");
    EXPECT_EQ(datum.toString(), "");
}

// Test Rational with zero denominator
TEST_F(ExifdatumTest_735, RationalZeroDenominator_735) {
    Exiv2::ExifKey key("Exif.Photo.ExposureBiasValue");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::Rational val(1, 0);
    datum = val;
    Exiv2::Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 0);
}

// Test copy method
TEST_F(ExifdatumTest_735, CopyToBuffer_735) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;

    Exiv2::byte buf[16] = {};
    size_t copied = datum.copy(buf, Exiv2::bigEndian);
    EXPECT_GT(copied, 0u);
}

// Test ifdName
TEST_F(ExifdatumTest_735, IfdName_735) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    const char* name = datum.ifdName();
    EXPECT_NE(name, nullptr);
}
