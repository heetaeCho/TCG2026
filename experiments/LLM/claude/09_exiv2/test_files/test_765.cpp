#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exifdatum.hpp>
#include <exiv2/value.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/types.hpp>
#include <cstring>

using namespace Exiv2;

class ExifdatumTest_765 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction with a known ExifKey
TEST_F(ExifdatumTest_765, ConstructWithExifKey_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test copy construction
TEST_F(ExifdatumTest_765, CopyConstruction_765) {
    ExifKey key("Exif.Image.Model");
    Exifdatum datum(key);
    datum.setValue("Canon EOS 5D");
    
    Exifdatum copy(datum);
    EXPECT_EQ(copy.key(), "Exif.Image.Model");
    EXPECT_EQ(copy.toString(), "Canon EOS 5D");
}

// Test copy assignment operator
TEST_F(ExifdatumTest_765, CopyAssignment_765) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1);
    datum1.setValue("Nikon");
    
    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2);
    datum2.setValue("D850");
    
    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "Nikon");
}

// Test setValue with string
TEST_F(ExifdatumTest_765, SetValueString_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    int result = datum.setValue("TestMake");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "TestMake");
}

// Test assignment with string
TEST_F(ExifdatumTest_765, AssignString_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("Hello");
    EXPECT_EQ(datum.toString(), "Hello");
}

// Test assignment with uint16_t
TEST_F(ExifdatumTest_765, AssignUint16_765) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ(datum.toInt64(0), 1);
}

// Test assignment with uint32_t
TEST_F(ExifdatumTest_765, AssignUint32_765) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    datum = static_cast<uint32_t>(1920);
    EXPECT_EQ(datum.toInt64(0), 1920);
}

// Test assignment with int16_t
TEST_F(ExifdatumTest_765, AssignInt16_765) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    datum = static_cast<int16_t>(-5);
    EXPECT_EQ(datum.toInt64(0), -5);
}

// Test assignment with int32_t
TEST_F(ExifdatumTest_765, AssignInt32_765) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    datum = static_cast<int32_t>(-100);
    EXPECT_EQ(datum.toInt64(0), -100);
}

// Test assignment with URational
TEST_F(ExifdatumTest_765, AssignURational_765) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key);
    URational ur = {72, 1};
    datum = ur;
    EXPECT_EQ(datum.toInt64(0), 72);
}

// Test assignment with Rational
TEST_F(ExifdatumTest_765, AssignRational_765) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key);
    Rational r = {-1, 3};
    datum = r;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 3);
}

// Test assignment with Value object
TEST_F(ExifdatumTest_765, AssignValue_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    auto value = Value::create(asciiString);
    value->read("TestValue");
    datum = *value;
    EXPECT_EQ(datum.toString(), "TestValue");
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_765, SetValuePointer_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    auto value = Value::create(asciiString);
    value->read("PointerValue");
    datum.setValue(value.get());
    EXPECT_EQ(datum.toString(), "PointerValue");
}

// Test key() returns correct key string
TEST_F(ExifdatumTest_765, KeyReturnsCorrectString_765) {
    ExifKey key("Exif.Photo.DateTimeOriginal");
    Exifdatum datum(key);
    EXPECT_EQ(datum.key(), "Exif.Photo.DateTimeOriginal");
}

// Test familyName
TEST_F(ExifdatumTest_765, FamilyNameIsExif_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test groupName
TEST_F(ExifdatumTest_765, GroupName_765) {
    ExifKey key("Exif.Photo.FNumber");
    Exifdatum datum(key);
    EXPECT_EQ(datum.groupName(), "Photo");
}

// Test tagName
TEST_F(ExifdatumTest_765, TagName_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test tag() returns correct tag number
TEST_F(ExifdatumTest_765, TagNumber_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    // Make tag is 0x010f
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test typeId after setting a string value
TEST_F(ExifdatumTest_765, TypeIdAscii_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Test");
    EXPECT_EQ(datum.typeId(), asciiString);
}

// Test typeName after setting value
TEST_F(ExifdatumTest_765, TypeName_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Test");
    EXPECT_STREQ(datum.typeName(), "Ascii");
}

// Test count() after setting value
TEST_F(ExifdatumTest_765, Count_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Test");
    EXPECT_GT(datum.count(), static_cast<size_t>(0));
}

// Test size() after setting value
TEST_F(ExifdatumTest_765, Size_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Test");
    EXPECT_GT(datum.size(), static_cast<size_t>(0));
}

// Test toString()
TEST_F(ExifdatumTest_765, ToString_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("CanonMake");
    EXPECT_EQ(datum.toString(), "CanonMake");
}

// Test toString(n)
TEST_F(ExifdatumTest_765, ToStringWithIndex_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("IndexTest");
    EXPECT_EQ(datum.toString(0), "IndexTest");
}

// Test toInt64
TEST_F(ExifdatumTest_765, ToInt64_765) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    datum = static_cast<uint16_t>(6);
    EXPECT_EQ(datum.toInt64(0), 6);
}

// Test toFloat
TEST_F(ExifdatumTest_765, ToFloat_765) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key);
    URational ur = {72, 1};
    datum = ur;
    EXPECT_FLOAT_EQ(datum.toFloat(0), 72.0f);
}

// Test toRational
TEST_F(ExifdatumTest_765, ToRational_765) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key);
    URational ur = {300, 1};
    datum = ur;
    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, 300);
    EXPECT_EQ(r.second, 1);
}

// Test getValue
TEST_F(ExifdatumTest_765, GetValue_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("TestGetValue");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "TestGetValue");
}

// Test value() reference
TEST_F(ExifdatumTest_765, ValueReference_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("RefTest");
    const Value& val = datum.value();
    EXPECT_EQ(val.toString(), "RefTest");
}

// Test dataArea when no data area is set (should return empty)
TEST_F(ExifdatumTest_765, DataAreaEmpty_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("NoDataArea");
    DataBuf buf = datum.dataArea();
    EXPECT_EQ(buf.size(), static_cast<size_t>(0));
}

// Test sizeDataArea when no data area is set
TEST_F(ExifdatumTest_765, SizeDataAreaEmpty_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("NoDataArea");
    EXPECT_EQ(datum.sizeDataArea(), static_cast<size_t>(0));
}

// Test dataArea when value_ is null (no value set)
TEST_F(ExifdatumTest_765, DataAreaNullValue_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    // No setValue called, value_ should be null
    DataBuf buf = datum.dataArea();
    EXPECT_EQ(buf.size(), static_cast<size_t>(0));
}

// Test setDataArea
TEST_F(ExifdatumTest_765, SetDataArea_765) {
    ExifKey key("Exif.Image.StripOffsets");
    Exifdatum datum(key);
    datum = static_cast<uint32_t>(0);
    
    byte testData[] = {0x01, 0x02, 0x03, 0x04};
    // setDataArea might return non-zero if value doesn't support data area
    datum.setDataArea(testData, sizeof(testData));
}

// Test copy to buffer
TEST_F(ExifdatumTest_765, CopyToBuffer_765) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    datum = static_cast<uint16_t>(1);
    
    byte buf[64] = {};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, static_cast<size_t>(0));
}

// Test typeSize
TEST_F(ExifdatumTest_765, TypeSize_765) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ(datum.typeSize(), static_cast<size_t>(2)); // uint16 = 2 bytes
}

// Test idx (default should be 0)
TEST_F(ExifdatumTest_765, IdxDefault_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.idx(), 0);
}

// Test ifdId
TEST_F(ExifdatumTest_765, IfdId_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.ifdId(), IfdId::ifd0Id);
}

// Test tagLabel returns non-empty for known tags
TEST_F(ExifdatumTest_765, TagLabelNonEmpty_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test multiple assignments overwrite correctly
TEST_F(ExifdatumTest_765, MultipleAssignments_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("First");
    EXPECT_EQ(datum.toString(), "First");
    datum.setValue("Second");
    EXPECT_EQ(datum.toString(), "Second");
}

// Test setValue with nullptr Value
TEST_F(ExifdatumTest_765, SetValueNullptr_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Something");
    datum.setValue(static_cast<const Value*>(nullptr));
    // After setting null, getValue should return null
    auto val = datum.getValue();
    EXPECT_EQ(val, nullptr);
}

// Test boundary: very long string value
TEST_F(ExifdatumTest_765, LongStringValue_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    std::string longStr(1000, 'A');
    datum.setValue(longStr);
    EXPECT_EQ(datum.toString(), longStr);
}

// Test boundary: empty string value
TEST_F(ExifdatumTest_765, EmptyStringValue_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("");
    EXPECT_EQ(datum.count(), static_cast<size_t>(0));
}

// Test uint16 boundary values
TEST_F(ExifdatumTest_765, Uint16MaxValue_765) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    datum = static_cast<uint16_t>(65535);
    EXPECT_EQ(datum.toInt64(0), 65535);
}

// Test uint16 zero value
TEST_F(ExifdatumTest_765, Uint16ZeroValue_765) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    datum = static_cast<uint16_t>(0);
    EXPECT_EQ(datum.toInt64(0), 0);
}

// Test construction with ExifKey for Photo group
TEST_F(ExifdatumTest_765, PhotoGroupKey_765) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key);
    EXPECT_EQ(datum.groupName(), "Photo");
    EXPECT_EQ(datum.tagName(), "ExposureTime");
}

// Test write to ostream
TEST_F(ExifdatumTest_765, WriteToStream_765) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("StreamTest");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}
