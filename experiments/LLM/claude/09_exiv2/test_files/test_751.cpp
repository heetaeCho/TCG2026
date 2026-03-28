#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

class ExifdatumTest_751 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction with a known ExifKey
TEST_F(ExifdatumTest_751, ConstructWithExifKey_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Exif.Image.Make", datum.key());
    EXPECT_EQ("Exif", std::string(datum.familyName()));
    EXPECT_EQ("Image", datum.groupName());
    EXPECT_EQ("Make", datum.tagName());
}

// Test idx() returns 0 when default
TEST_F(ExifdatumTest_751, IdxDefaultIsZero_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(0, datum.idx());
}

// Test copy constructor
TEST_F(ExifdatumTest_751, CopyConstructor_751) {
    ExifKey key("Exif.Image.Model");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon EOS 5D");

    Exifdatum copy(datum);
    EXPECT_EQ(datum.key(), copy.key());
    EXPECT_EQ(datum.toString(), copy.toString());
    EXPECT_EQ(datum.tag(), copy.tag());
}

// Test assignment operator
TEST_F(ExifdatumTest_751, AssignmentOperator_751) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1, nullptr);
    datum1.setValue("Nikon");

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2, nullptr);
    datum2 = datum1;

    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
}

// Test setValue with string
TEST_F(ExifdatumTest_751, SetValueString_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    int result = datum.setValue("Canon");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Canon", datum.toString());
}

// Test operator= with string
TEST_F(ExifdatumTest_751, OperatorAssignString_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Sony");
    EXPECT_EQ("Sony", datum.toString());
}

// Test tag() returns correct tag number
TEST_F(ExifdatumTest_751, TagReturnsCorrectValue_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Make tag is 0x010f
    EXPECT_EQ(0x010f, datum.tag());
}

// Test familyName returns "Exif"
TEST_F(ExifdatumTest_751, FamilyNameIsExif_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_STREQ("Exif", datum.familyName());
}

// Test groupName
TEST_F(ExifdatumTest_751, GroupName_751) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Photo", datum.groupName());
}

// Test tagName
TEST_F(ExifdatumTest_751, TagName_751) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("ExposureTime", datum.tagName());
}

// Test typeId when no value is set
TEST_F(ExifdatumTest_751, TypeIdWhenNoValue_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // When no value is set, typeId should return unsignedByte or invalidTypeId
    // Based on typical behavior with no value set
    TypeId tid = datum.typeId();
    (void)tid; // Just ensure it doesn't crash
}

// Test count() with no value
TEST_F(ExifdatumTest_751, CountWithNoValue_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(0u, datum.count());
}

// Test size() with no value
TEST_F(ExifdatumTest_751, SizeWithNoValue_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(0u, datum.size());
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_751, SetValueWithValuePtr_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    AsciiValue val("TestValue");
    datum.setValue(&val);
    EXPECT_EQ("TestValue", datum.toString());
    EXPECT_GT(datum.count(), 0u);
}

// Test operator= with uint16_t
TEST_F(ExifdatumTest_751, OperatorAssignUint16_751) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ("1", datum.toString());
}

// Test operator= with uint32_t
TEST_F(ExifdatumTest_751, OperatorAssignUint32_751) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint32_t>(1920);
    EXPECT_EQ("1920", datum.toString());
}

// Test operator= with int16_t
TEST_F(ExifdatumTest_751, OperatorAssignInt16_751) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<int16_t>(-5);
    EXPECT_EQ("-5", datum.toString());
}

// Test operator= with int32_t
TEST_F(ExifdatumTest_751, OperatorAssignInt32_751) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum = static_cast<int32_t>(4000);
    EXPECT_EQ("4000", datum.toString());
}

// Test operator= with Rational
TEST_F(ExifdatumTest_751, OperatorAssignRational_751) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key, nullptr);
    Rational rat(1, 250);
    datum = rat;
    EXPECT_EQ("1/250", datum.toString());
}

// Test operator= with URational
TEST_F(ExifdatumTest_751, OperatorAssignURational_751) {
    ExifKey key("Exif.Photo.FNumber");
    Exifdatum datum(key, nullptr);
    URational urat(28, 10);
    datum = urat;
    EXPECT_EQ("28/10", datum.toString());
}

// Test operator= with Value
TEST_F(ExifdatumTest_751, OperatorAssignValue_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    AsciiValue val("Fujifilm");
    datum = static_cast<const Value&>(val);
    EXPECT_EQ("Fujifilm", datum.toString());
}

// Test getValue returns unique_ptr
TEST_F(ExifdatumTest_751, GetValueReturnsUniquePtr_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestMake");

    auto val = datum.getValue();
    ASSERT_NE(nullptr, val.get());
    EXPECT_EQ("TestMake", val->toString());
}

// Test value() const reference
TEST_F(ExifdatumTest_751, ValueConstRef_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestValue");

    const Value& val = datum.value();
    EXPECT_EQ("TestValue", val.toString());
}

// Test value() throws when no value set
TEST_F(ExifdatumTest_751, ValueThrowsWhenNoValueSet_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_THROW(datum.value(), Error);
}

// Test toInt64
TEST_F(ExifdatumTest_751, ToInt64_751) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(6);
    EXPECT_EQ(6, datum.toInt64(0));
}

// Test toFloat
TEST_F(ExifdatumTest_751, ToFloat_751) {
    ExifKey key("Exif.Photo.FNumber");
    Exifdatum datum(key, nullptr);
    URational urat(56, 10);
    datum = urat;
    EXPECT_FLOAT_EQ(5.6f, datum.toFloat(0));
}

// Test toRational
TEST_F(ExifdatumTest_751, ToRational_751) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key, nullptr);
    Rational rat(1, 125);
    datum = rat;
    Rational result = datum.toRational(0);
    EXPECT_EQ(1, result.first);
    EXPECT_EQ(125, result.second);
}

// Test toString with index
TEST_F(ExifdatumTest_751, ToStringWithIndex_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Hello");
    std::string s = datum.toString(0);
    EXPECT_FALSE(s.empty());
}

// Test ifdId
TEST_F(ExifdatumTest_751, IfdId_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    IfdId id = datum.ifdId();
    // ifdId for Image group should be ifd0Id
    EXPECT_NE(ifdIdNotSet, id);
}

// Test ifdName
TEST_F(ExifdatumTest_751, IfdName_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    const char* name = datum.ifdName();
    EXPECT_NE(nullptr, name);
}

// Test write to ostream
TEST_F(ExifdatumTest_751, WriteToOstream_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestCamera");

    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
    EXPECT_NE(std::string::npos, os.str().find("TestCamera"));
}

// Test sizeDataArea when no data area
TEST_F(ExifdatumTest_751, SizeDataAreaNoData_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Test");
    EXPECT_EQ(0u, datum.sizeDataArea());
}

// Test copy to buffer
TEST_F(ExifdatumTest_751, CopyToBuffer_751) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);

    byte buf[64] = {};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test tagLabel returns non-empty string for known tags
TEST_F(ExifdatumTest_751, TagLabel_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test tagDesc
TEST_F(ExifdatumTest_751, TagDesc_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // tagDesc may or may not be empty, but should not crash
    std::string desc = datum.tagDesc();
    (void)desc;
}

// Test typeName when value is set
TEST_F(ExifdatumTest_751, TypeName_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Test");
    const char* tn = datum.typeName();
    EXPECT_NE(nullptr, tn);
}

// Test typeSize when value is set
TEST_F(ExifdatumTest_751, TypeSize_751) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);
    size_t ts = datum.typeSize();
    EXPECT_EQ(2u, ts); // uint16 = 2 bytes
}

// Test construction with ExifKey using tag number and group name
TEST_F(ExifdatumTest_751, ConstructWithTagAndGroup_751) {
    ExifKey key(0x010f, "Image");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(0x010f, datum.tag());
    EXPECT_EQ("Image", datum.groupName());
}

// Test setting value then overwriting
TEST_F(ExifdatumTest_751, OverwriteValue_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("First");
    EXPECT_EQ("First", datum.toString());
    datum.setValue("Second");
    EXPECT_EQ("Second", datum.toString());
}

// Test that setting nullptr value clears value
TEST_F(ExifdatumTest_751, SetValueNullptr_751) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("SomeValue");
    EXPECT_GT(datum.count(), 0u);

    datum.setValue(static_cast<const Value*>(nullptr));
    EXPECT_EQ(0u, datum.count());
}

// Test construction with Value
TEST_F(ExifdatumTest_751, ConstructWithValue_751) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val("InitialValue");
    Exifdatum datum(key, &val);
    EXPECT_EQ("InitialValue", datum.toString());
}

// Test idx with ExifKey that has idx set
TEST_F(ExifdatumTest_751, IdxReflectsKeyIdx_751) {
    ExifKey key("Exif.Image.Make");
    key.setIdx(42);
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(42, datum.idx());
}
