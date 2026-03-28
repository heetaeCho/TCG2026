#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/exif.hpp>
#include <cstdint>
#include <string>
#include <sstream>

class ExifdatumTest_736 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a known ExifKey
TEST_F(ExifdatumTest_736, ConstructWithExifKey_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test copy constructor
TEST_F(ExifdatumTest_736, CopyConstructor_736) {
    Exiv2::ExifKey key("Exif.Image.Model");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("TestCamera");

    Exiv2::Exifdatum copy(datum);
    EXPECT_EQ(copy.key(), "Exif.Image.Model");
    EXPECT_EQ(copy.toString(), "TestCamera");
}

// Test copy assignment operator
TEST_F(ExifdatumTest_736, CopyAssignment_736) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::Exifdatum datum1(key1, nullptr);
    datum1 = std::string("Nikon");

    Exiv2::ExifKey key2("Exif.Image.Model");
    Exiv2::Exifdatum datum2(key2, nullptr);
    datum2 = datum1;

    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "Nikon");
}

// Test operator= with string value
TEST_F(ExifdatumTest_736, AssignString_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Canon");

    EXPECT_EQ(datum.toString(), "Canon");
    EXPECT_EQ(datum.count(), 1u);
}

// Test operator= with uint16_t
TEST_F(ExifdatumTest_736, AssignUint16_736) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;

    EXPECT_EQ(datum.toInt64(0), 1);
    EXPECT_EQ(datum.count(), 1u);
}

// Test operator= with uint32_t
TEST_F(ExifdatumTest_736, AssignUint32_736) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    uint32_t val = 4000;
    datum = val;

    EXPECT_EQ(datum.toInt64(0), 4000);
}

// Test operator= with int16_t
TEST_F(ExifdatumTest_736, AssignInt16_736) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    int16_t val = -5;
    datum = val;

    EXPECT_EQ(datum.toInt64(0), -5);
}

// Test operator= with int32_t
TEST_F(ExifdatumTest_736, AssignInt32_736) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    int32_t val = 3000;
    datum = val;

    EXPECT_EQ(datum.toInt64(0), 3000);
}

// Test operator= with negative int32_t
TEST_F(ExifdatumTest_736, AssignNegativeInt32_736) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    int32_t val = -100;
    datum = val;

    EXPECT_EQ(datum.toInt64(0), -100);
}

// Test operator= with URational
TEST_F(ExifdatumTest_736, AssignURational_736) {
    Exiv2::ExifKey key("Exif.Image.XResolution");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::URational val(72, 1);
    datum = val;

    EXPECT_EQ(datum.toInt64(0), 72);
    Exiv2::Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, 72);
    EXPECT_EQ(r.second, 1);
}

// Test operator= with Rational
TEST_F(ExifdatumTest_736, AssignRational_736) {
    Exiv2::ExifKey key("Exif.Image.XResolution");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::Rational val(-1, 3);
    datum = val;

    Exiv2::Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, -1);
    EXPECT_EQ(r.second, 3);
}

// Test tag() returns expected tag number
TEST_F(ExifdatumTest_736, TagNumber_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    // Make tag is 0x010f
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test key() returns full key string
TEST_F(ExifdatumTest_736, KeyString_736) {
    Exiv2::ExifKey key("Exif.Image.Model");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Model");
}

// Test familyName() returns "Exif"
TEST_F(ExifdatumTest_736, FamilyName_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test groupName()
TEST_F(ExifdatumTest_736, GroupName_736) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Photo");
}

// Test tagLabel() is non-empty for known tags
TEST_F(ExifdatumTest_736, TagLabel_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test setValue with string
TEST_F(ExifdatumTest_736, SetValueString_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    int result = datum.setValue("TestValue");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "TestValue");
}

// Test count after setting a value
TEST_F(ExifdatumTest_736, CountAfterSetValue_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("SomeValue");
    EXPECT_GE(datum.count(), 1u);
}

// Test size after setting a value
TEST_F(ExifdatumTest_736, SizeAfterSetValue_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("SomeValue");
    EXPECT_GT(datum.size(), 0u);
}

// Test typeId after assigning uint16_t
TEST_F(ExifdatumTest_736, TypeIdUint16_736) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.typeId(), Exiv2::unsignedShort);
}

// Test typeId after assigning int32_t
TEST_F(ExifdatumTest_736, TypeIdInt32_736) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    int32_t val = 100;
    datum = val;
    EXPECT_EQ(datum.typeId(), Exiv2::signedLong);
}

// Test toFloat conversion
TEST_F(ExifdatumTest_736, ToFloat_736) {
    Exiv2::ExifKey key("Exif.Image.XResolution");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::URational val(72, 1);
    datum = val;
    EXPECT_FLOAT_EQ(datum.toFloat(0), 72.0f);
}

// Test getValue returns non-null after assignment
TEST_F(ExifdatumTest_736, GetValueNotNull_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("TestMake");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "TestMake");
}

// Test datum with no value set - getValue should return nullptr or throw
TEST_F(ExifdatumTest_736, NoValueSet_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    auto val = datum.getValue();
    // When no value is set, getValue should return nullptr
    EXPECT_EQ(val, nullptr);
}

// Test count when no value is set
TEST_F(ExifdatumTest_736, CountNoValue_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test size when no value is set
TEST_F(ExifdatumTest_736, SizeNoValue_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test setting value with a Value object
TEST_F(ExifdatumTest_736, AssignValueObject_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    Exiv2::AsciiValue asciiVal("TestBrand");
    datum = static_cast<const Exiv2::Value&>(asciiVal);

    EXPECT_EQ(datum.toString(), "TestBrand");
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_736, SetValuePointer_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);

    Exiv2::AsciiValue asciiVal("PointerTest");
    datum.setValue(&asciiVal);

    EXPECT_EQ(datum.toString(), "PointerTest");
}

// Test ifdId for known tag
TEST_F(ExifdatumTest_736, IfdId_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.ifdId(), Exiv2::IfdId::ifd0Id);
}

// Test idx initially
TEST_F(ExifdatumTest_736, IdxInitial_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    // idx should be 0 by default
    EXPECT_EQ(datum.idx(), 0);
}

// Test write to ostream
TEST_F(ExifdatumTest_736, WriteToStream_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("StreamTest");

    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test sizeDataArea when no data area is set
TEST_F(ExifdatumTest_736, SizeDataAreaEmpty_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("Test");
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test typeName for string assignment
TEST_F(ExifdatumTest_736, TypeNameAscii_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("TestValue");
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    EXPECT_EQ(std::string(tn), "Ascii");
}

// Test typeSize for uint16_t
TEST_F(ExifdatumTest_736, TypeSizeUint16_736) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.typeSize(), 2u);
}

// Test typeSize for int32_t
TEST_F(ExifdatumTest_736, TypeSizeInt32_736) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    int32_t val = 100;
    datum = val;
    EXPECT_EQ(datum.typeSize(), 4u);
}

// Test boundary: zero value for uint32_t
TEST_F(ExifdatumTest_736, ZeroUint32_736) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);
    uint32_t val = 0;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 0);
}

// Test boundary: max uint16_t
TEST_F(ExifdatumTest_736, MaxUint16_736) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = 65535;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 65535);
}

// Test URational with zero denominator
TEST_F(ExifdatumTest_736, URationalZeroDenominator_736) {
    Exiv2::ExifKey key("Exif.Image.XResolution");
    Exiv2::Exifdatum datum(key, nullptr);
    Exiv2::URational val(1, 0);
    datum = val;

    Exiv2::Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 0);
}

// Test toString(n) with index 0
TEST_F(ExifdatumTest_736, ToStringWithIndex_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("IndexTest");
    std::string result = datum.toString(0);
    EXPECT_EQ(result, "IndexTest");
}

// Test construction with a Value pointer
TEST_F(ExifdatumTest_736, ConstructWithValue_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::AsciiValue val("ConstructValue");
    Exiv2::Exifdatum datum(key, &val);

    EXPECT_EQ(datum.toString(), "ConstructValue");
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test copy to buffer
TEST_F(ExifdatumTest_736, CopyToBuffer_736) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;

    Exiv2::byte buf[16] = {};
    size_t copied = datum.copy(buf, Exiv2::littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test ExifData container basic usage
TEST_F(ExifdatumTest_736, ExifDataAddAndFind_736) {
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key("Exif.Image.Make");

    exifData["Exif.Image.Make"] = "TestManufacturer";

    auto it = exifData.findKey(key);
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ(it->toString(), "TestManufacturer");
}

// Test multiple assignments overwrite value
TEST_F(ExifdatumTest_736, MultipleAssignments_736) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    Exiv2::Exifdatum datum(key, nullptr);

    uint16_t val1 = 1;
    datum = val1;
    EXPECT_EQ(datum.toInt64(0), 1);

    uint16_t val2 = 6;
    datum = val2;
    EXPECT_EQ(datum.toInt64(0), 6);
}

// Test assigning different types sequentially
TEST_F(ExifdatumTest_736, ReassignDifferentType_736) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key, nullptr);

    uint32_t uval = 100;
    datum = uval;
    EXPECT_EQ(datum.toInt64(0), 100);
    EXPECT_EQ(datum.typeId(), Exiv2::unsignedLong);

    int32_t sval = -50;
    datum = sval;
    EXPECT_EQ(datum.toInt64(0), -50);
    EXPECT_EQ(datum.typeId(), Exiv2::signedLong);
}

// Test setting nullptr as value
TEST_F(ExifdatumTest_736, SetValueNullptr_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("SomeValue");
    EXPECT_GT(datum.count(), 0u);

    datum.setValue(nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test empty string assignment
TEST_F(ExifdatumTest_736, EmptyStringAssignment_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    datum = std::string("");
    // Empty ASCII string should still be valid
    EXPECT_EQ(datum.toString(), "");
}

// Test tagDesc returns something (could be empty for some tags)
TEST_F(ExifdatumTest_736, TagDesc_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    // Just verify it doesn't crash
    std::string desc = datum.tagDesc();
    // desc may or may not be empty depending on tag
    (void)desc;
}

// Test ifdName
TEST_F(ExifdatumTest_736, IfdName_736) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum datum(key, nullptr);
    const char* name = datum.ifdName();
    ASSERT_NE(name, nullptr);
}
