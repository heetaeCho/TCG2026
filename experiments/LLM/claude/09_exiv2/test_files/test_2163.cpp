#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Test fixture for Exifdatum tests
class ExifdatumTest_2163 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction with key and null value
TEST_F(ExifdatumTest_2163, ConstructWithKeyAndNullValue_2163) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test construction with key and a value
TEST_F(ExifdatumTest_2163, ConstructWithKeyAndValue_2163) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Canon");
    
    Exifdatum datum(key, value.get());
    
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.toString(), "Canon");
    EXPECT_EQ(datum.typeId(), asciiString);
}

// Test copy constructor
TEST_F(ExifdatumTest_2163, CopyConstructor_2163) {
    ExifKey key("Exif.Image.Model");
    auto value = Value::create(asciiString);
    value->read("EOS 5D");
    
    Exifdatum original(key, value.get());
    Exifdatum copy(original);
    
    EXPECT_EQ(copy.key(), "Exif.Image.Model");
    EXPECT_EQ(copy.toString(), "EOS 5D");
    EXPECT_EQ(copy.typeId(), asciiString);
}

// Test copy assignment operator
TEST_F(ExifdatumTest_2163, CopyAssignmentOperator_2163) {
    ExifKey key1("Exif.Image.Make");
    auto value1 = Value::create(asciiString);
    value1->read("Canon");
    Exifdatum datum1(key1, value1.get());
    
    ExifKey key2("Exif.Image.Model");
    auto value2 = Value::create(asciiString);
    value2->read("EOS R");
    Exifdatum datum2(key2, value2.get());
    
    datum2 = datum1;
    
    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "Canon");
}

// Test operator= with string
TEST_F(ExifdatumTest_2163, AssignString_2163) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    datum = std::string("Nikon");
    
    EXPECT_EQ(datum.toString(), "Nikon");
}

// Test operator= with uint16_t
TEST_F(ExifdatumTest_2163, AssignUint16_2163) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    
    datum = static_cast<uint16_t>(1);
    
    EXPECT_EQ(datum.toInt64(0), 1);
}

// Test operator= with uint32_t
TEST_F(ExifdatumTest_2163, AssignUint32_2163) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    
    datum = static_cast<uint32_t>(4000);
    
    EXPECT_EQ(datum.toInt64(0), 4000);
}

// Test operator= with int16_t
TEST_F(ExifdatumTest_2163, AssignInt16_2163) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    
    datum = static_cast<int16_t>(-5);
    
    EXPECT_EQ(datum.toInt64(0), -5);
}

// Test operator= with int32_t
TEST_F(ExifdatumTest_2163, AssignInt32_2163) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    
    datum = static_cast<int32_t>(-100);
    
    EXPECT_EQ(datum.toInt64(0), -100);
}

// Test operator= with Rational
TEST_F(ExifdatumTest_2163, AssignRational_2163) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    Rational rat = {72, 1};
    datum = rat;
    
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 72);
    EXPECT_EQ(result.second, 1);
}

// Test operator= with URational
TEST_F(ExifdatumTest_2163, AssignURational_2163) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    URational urat = {300, 1};
    datum = urat;
    
    EXPECT_EQ(datum.toInt64(0), 300);
}

// Test operator= with Value
TEST_F(ExifdatumTest_2163, AssignValue_2163) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    auto value = Value::create(asciiString);
    value->read("Sony");
    datum = *value;
    
    EXPECT_EQ(datum.toString(), "Sony");
    EXPECT_EQ(datum.typeId(), asciiString);
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_2163, SetValueWithPointer_2163) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    auto value = Value::create(asciiString);
    value->read("Fujifilm");
    datum.setValue(value.get());
    
    EXPECT_EQ(datum.toString(), "Fujifilm");
}

// Test setValue with nullptr
TEST_F(ExifdatumTest_2163, SetValueWithNullptr_2163) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Canon");
    Exifdatum datum(key, value.get());
    
    datum.setValue(nullptr);
    
    // After setting nullptr, count should be 0
    EXPECT_EQ(datum.count(), 0u);
}

// Test setValue with string
TEST_F(ExifdatumTest_2163, SetValueWithString_2163) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    int result = datum.setValue("Panasonic");
    
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Panasonic");
}

// Test key-related accessors
TEST_F(ExifdatumTest_2163, KeyAccessors_2163) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Exif.Photo.ExposureTime");
    EXPECT_EQ(std::string(datum.familyName()), "Exif");
    EXPECT_EQ(datum.groupName(), "Photo");
    EXPECT_EQ(datum.tagName(), "ExposureTime");
}

// Test tag() returns correct tag number
TEST_F(ExifdatumTest_2163, TagNumber_2163) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    
    // ImageWidth tag is 0x0100 = 256
    EXPECT_EQ(datum.tag(), 0x0100);
}

// Test ifdId
TEST_F(ExifdatumTest_2163, IfdId_2163) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    IfdId id = datum.ifdId();
    // Should return some valid IfdId for Image group
    EXPECT_NE(id, ifdIdNotSet);
}

// Test typeId when no value is set
TEST_F(ExifdatumTest_2163, TypeIdNoValue_2163) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    // When no value is set, typeId may return the default type
    TypeId tid = datum.typeId();
    // Just ensure it doesn't crash; the specific value depends on implementation
    (void)tid;
}

// Test typeId when value is set
TEST_F(ExifdatumTest_2163, TypeIdWithValue_2163) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Test");
    Exifdatum datum(key, value.get());
    
    EXPECT_EQ(datum.typeId(), asciiString);
}

// Test count with no value
TEST_F(ExifdatumTest_2163, CountNoValue_2163) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.count(), 0u);
}

// Test count with value
TEST_F(ExifdatumTest_2163, CountWithValue_2163) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Canon");
    Exifdatum datum(key, value.get());
    
    EXPECT_GT(datum.count(), 0u);
}

// Test size with no value
TEST_F(ExifdatumTest_2163, SizeNoValue_2163) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.size(), 0u);
}

// Test size with value
TEST_F(ExifdatumTest_2163, SizeWithValue_2163) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Canon");
    Exifdatum datum(key, value.get());
    
    EXPECT_GT(datum.size(), 0u);
}

// Test toString
TEST_F(ExifdatumTest_2163, ToString_2163) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Olympus");
    Exifdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toString(), "Olympus");
}

// Test toString with index
TEST_F(ExifdatumTest_2163, ToStringWithIndex_2163) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Leica");
    Exifdatum datum(key, value.get());
    
    std::string str = datum.toString(0);
    EXPECT_FALSE(str.empty());
}

// Test toInt64
TEST_F(ExifdatumTest_2163, ToInt64_2163) {
    ExifKey key("Exif.Image.Orientation");
    auto value = Value::create(unsignedShort);
    value->read("6");
    Exifdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toInt64(0), 6);
}

// Test toFloat
TEST_F(ExifdatumTest_2163, ToFloat_2163) {
    ExifKey key("Exif.Image.XResolution");
    auto value = Value::create(unsignedRational);
    value->read("72/1");
    Exifdatum datum(key, value.get());
    
    EXPECT_FLOAT_EQ(datum.toFloat(0), 72.0f);
}

// Test toRational
TEST_F(ExifdatumTest_2163, ToRational_2163) {
    ExifKey key("Exif.Image.XResolution");
    auto value = Value::create(unsignedRational);
    value->read("300/1");
    Exifdatum datum(key, value.get());
    
    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, 300);
    EXPECT_EQ(r.second, 1);
}

// Test getValue
TEST_F(ExifdatumTest_2163, GetValue_2163) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Pentax");
    Exifdatum datum(key, value.get());
    
    auto retrieved = datum.getValue();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toString(), "Pentax");
}

// Test getValue when no value is set
TEST_F(ExifdatumTest_2163, GetValueNoValue_2163) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    auto retrieved = datum.getValue();
    // When no value set, getValue should return nullptr or similar
    EXPECT_EQ(retrieved, nullptr);
}

// Test value() reference
TEST_F(ExifdatumTest_2163, ValueReference_2163) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Sigma");
    Exifdatum datum(key, value.get());
    
    const Value& ref = datum.value();
    EXPECT_EQ(ref.toString(), "Sigma");
}

// Test write to ostream
TEST_F(ExifdatumTest_2163, WriteToStream_2163) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Hasselblad");
    Exifdatum datum(key, value.get());
    
    std::ostringstream os;
    datum.write(os, nullptr);
    
    EXPECT_FALSE(os.str().empty());
}

// Test copy to buffer
TEST_F(ExifdatumTest_2163, CopyToBuffer_2163) {
    ExifKey key("Exif.Image.Orientation");
    auto value = Value::create(unsignedShort);
    value->read("1");
    Exifdatum datum(key, value.get());
    
    byte buf[64] = {0};
    size_t copied = datum.copy(buf, littleEndian);
    
    EXPECT_GT(copied, 0u);
}

// Test tagLabel
TEST_F(ExifdatumTest_2163, TagLabel_2163) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test tagDesc
TEST_F(ExifdatumTest_2163, TagDesc_2163) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    // tagDesc may return empty or a description
    std::string desc = datum.tagDesc();
    // Just ensure no crash
    (void)desc;
}

// Test typeName when value is set
TEST_F(ExifdatumTest_2163, TypeName_2163) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Test");
    Exifdatum datum(key, value.get());
    
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    EXPECT_EQ(std::string(tn), "Ascii");
}

// Test typeSize
TEST_F(ExifdatumTest_2163, TypeSize_2163) {
    ExifKey key("Exif.Image.Orientation");
    auto value = Value::create(unsignedShort);
    value->read("1");
    Exifdatum datum(key, value.get());
    
    EXPECT_EQ(datum.typeSize(), 2u);
}

// Test sizeDataArea with no data area
TEST_F(ExifdatumTest_2163, SizeDataAreaNoData_2163) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Test");
    Exifdatum datum(key, value.get());
    
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test construction with tag number and group name
TEST_F(ExifdatumTest_2163, ConstructWithTagAndGroup_2163) {
    ExifKey key(0x010f, "Image");  // 0x010f = Make
    Exifdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.tag(), 0x010f);
    EXPECT_EQ(datum.groupName(), "Image");
}

// Test idx
TEST_F(ExifdatumTest_2163, Idx_2163) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    int index = datum.idx();
    // Default idx, just ensure it doesn't crash
    (void)index;
}

// Test ifdName
TEST_F(ExifdatumTest_2163, IfdName_2163) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    const char* name = datum.ifdName();
    ASSERT_NE(name, nullptr);
}

// Test self-assignment
TEST_F(ExifdatumTest_2163, SelfAssignment_2163) {
    ExifKey key("Exif.Image.Make");
    auto value = Value::create(asciiString);
    value->read("Canon");
    Exifdatum datum(key, value.get());
    
    datum = datum;  // self-assignment
    
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.toString(), "Canon");
}

// Test setting value multiple times
TEST_F(ExifdatumTest_2163, SetValueMultipleTimes_2163) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    datum = std::string("Canon");
    EXPECT_EQ(datum.toString(), "Canon");
    
    datum = std::string("Nikon");
    EXPECT_EQ(datum.toString(), "Nikon");
    
    datum = std::string("Sony");
    EXPECT_EQ(datum.toString(), "Sony");
}

// Test with unsigned long value
TEST_F(ExifdatumTest_2163, UnsignedLongValue_2163) {
    ExifKey key("Exif.Image.ImageWidth");
    auto value = Value::create(unsignedLong);
    value->read("6000");
    Exifdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toInt64(0), 6000);
    EXPECT_EQ(datum.typeId(), unsignedLong);
}

// Test with signed rational
TEST_F(ExifdatumTest_2163, SignedRationalValue_2163) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    auto value = Value::create(signedRational);
    value->read("-1/3");
    Exifdatum datum(key, value.get());
    
    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, -1);
    EXPECT_EQ(r.second, 3);
}

// Test dataArea with no data
TEST_F(ExifdatumTest_2163, DataAreaEmpty_2163) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    DataBuf da = datum.dataArea();
    EXPECT_EQ(da.size(), 0u);
}
