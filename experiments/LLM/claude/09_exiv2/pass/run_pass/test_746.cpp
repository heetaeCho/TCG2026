#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Test fixture for Exifdatum tests
class ExifdatumTest_746 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction with a known ExifKey
TEST_F(ExifdatumTest_746, ConstructWithExifKey_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_STREQ(datum.familyName(), "Exif");
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test tagLabel returns non-empty for a known tag
TEST_F(ExifdatumTest_746, TagLabelReturnsNonEmpty_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test tagDesc returns a description for a known tag
TEST_F(ExifdatumTest_746, TagDescReturnsDescription_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string desc = datum.tagDesc();
    // Description should be non-empty for well-known tags
    EXPECT_FALSE(desc.empty());
}

// Test tag() returns the correct tag number
TEST_F(ExifdatumTest_746, TagReturnsCorrectNumber_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Make tag is 0x010f
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test copy constructor
TEST_F(ExifdatumTest_746, CopyConstructor_746) {
    ExifKey key("Exif.Image.Model");
    Exifdatum datum1(key, nullptr);
    datum1.setValue("Canon EOS 5D");
    
    Exifdatum datum2(datum1);
    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.toString(), datum1.toString());
    EXPECT_EQ(datum2.tag(), datum1.tag());
}

// Test assignment operator
TEST_F(ExifdatumTest_746, AssignmentOperator_746) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1, nullptr);
    datum1.setValue("Nikon");

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2, nullptr);
    datum2 = datum1;
    
    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.toString(), "Nikon");
}

// Test setValue with string
TEST_F(ExifdatumTest_746, SetValueString_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    int result = datum.setValue("TestManufacturer");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "TestManufacturer");
}

// Test operator= with string
TEST_F(ExifdatumTest_746, OperatorAssignString_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("SomeValue");
    EXPECT_EQ(datum.toString(), "SomeValue");
}

// Test operator= with uint16_t
TEST_F(ExifdatumTest_746, OperatorAssignUint16_746) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 1);
}

// Test operator= with uint32_t
TEST_F(ExifdatumTest_746, OperatorAssignUint32_746) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    uint32_t val = 4000;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 4000);
}

// Test operator= with int16_t
TEST_F(ExifdatumTest_746, OperatorAssignInt16_746) {
    ExifKey key("Exif.Photo.ExposureCompensation");
    Exifdatum datum(key, nullptr);
    // Use a signed rational tag - but we'll test with a short-compatible one
    ExifKey key2("Exif.Image.Orientation");
    Exifdatum datum2(key2, nullptr);
    int16_t val = -5;
    datum2 = val;
    EXPECT_EQ(datum2.toInt64(0), -5);
}

// Test operator= with int32_t
TEST_F(ExifdatumTest_746, OperatorAssignInt32_746) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    int32_t val = 1920;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 1920);
}

// Test operator= with URational
TEST_F(ExifdatumTest_746, OperatorAssignURational_746) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key, nullptr);
    URational val(1, 250);
    datum = val;
    Rational r = datum.toRational(0);
    EXPECT_EQ(static_cast<uint32_t>(r.first), 1u);
    EXPECT_EQ(static_cast<uint32_t>(r.second), 250u);
}

// Test operator= with Rational
TEST_F(ExifdatumTest_746, OperatorAssignRational_746) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key, nullptr);
    Rational val(-1, 3);
    datum = val;
    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, -1);
    EXPECT_EQ(r.second, 3);
}

// Test typeId for ASCII data
TEST_F(ExifdatumTest_746, TypeIdForAscii_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestValue");
    EXPECT_EQ(datum.typeId(), asciiString);
}

// Test typeName for ASCII data
TEST_F(ExifdatumTest_746, TypeNameForAscii_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestValue");
    EXPECT_STREQ(datum.typeName(), "Ascii");
}

// Test count
TEST_F(ExifdatumTest_746, CountAfterSetValue_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Hello");
    // ASCII strings include null terminator in count
    EXPECT_GE(datum.count(), 1u);
}

// Test size
TEST_F(ExifdatumTest_746, SizeAfterSetValue_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Test");
    EXPECT_GT(datum.size(), 0u);
}

// Test getValue returns non-null after setting a value
TEST_F(ExifdatumTest_746, GetValueNonNull_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("SomeValue");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "SomeValue");
}

// Test value() reference
TEST_F(ExifdatumTest_746, ValueReference_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("RefTest");
    const Value& val = datum.value();
    EXPECT_EQ(val.toString(), "RefTest");
}

// Test ifdId
TEST_F(ExifdatumTest_746, IfdIdForImage_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.ifdId(), IfdId::ifd0Id);
}

// Test familyName
TEST_F(ExifdatumTest_746, FamilyNameIsExif_746) {
    ExifKey key("Exif.Photo.DateTimeOriginal");
    Exifdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test groupName for Photo group
TEST_F(ExifdatumTest_746, GroupNamePhoto_746) {
    ExifKey key("Exif.Photo.DateTimeOriginal");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Photo");
}

// Test idx default
TEST_F(ExifdatumTest_746, IdxDefault_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Default idx should be 0
    EXPECT_EQ(datum.idx(), 0);
}

// Test write to ostream
TEST_F(ExifdatumTest_746, WriteToOstream_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test toString with index
TEST_F(ExifdatumTest_746, ToStringWithIndex_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestCam");
    std::string s = datum.toString(0);
    EXPECT_EQ(s, "TestCam");
}

// Test toFloat
TEST_F(ExifdatumTest_746, ToFloat_746) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key, nullptr);
    URational val(1, 100);
    datum = val;
    float f = datum.toFloat(0);
    EXPECT_NEAR(f, 0.01f, 0.001f);
}

// Test setValue with Value pointer (nullptr clears value)
TEST_F(ExifdatumTest_746, SetValueWithNullPtr_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Hello");
    EXPECT_GT(datum.size(), 0u);
    datum.setValue(static_cast<const Value*>(nullptr));
    // After setting nullptr, size should be 0
    EXPECT_EQ(datum.size(), 0u);
}

// Test setValue with a Value object
TEST_F(ExifdatumTest_746, SetValueWithValueObject_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    AsciiValue av("TestBrand");
    datum = static_cast<const Value&>(av);
    EXPECT_EQ(datum.toString(), "TestBrand");
}

// Test copy to buffer
TEST_F(ExifdatumTest_746, CopyToBuffer_746) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 6;
    datum = val;
    byte buf[64] = {0};
    size_t sz = datum.copy(buf, littleEndian);
    EXPECT_GT(sz, 0u);
}

// Test construction with value pointer
TEST_F(ExifdatumTest_746, ConstructWithValuePtr_746) {
    ExifKey key("Exif.Image.Make");
    AsciiValue av("InitValue");
    Exifdatum datum(key, &av);
    EXPECT_EQ(datum.toString(), "InitValue");
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test sizeDataArea for a datum without data area
TEST_F(ExifdatumTest_746, SizeDataAreaZero_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Test");
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test typeSize for short type
TEST_F(ExifdatumTest_746, TypeSizeForShort_746) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.typeSize(), 2u);
}

// Test multiple assignments overwrite correctly
TEST_F(ExifdatumTest_746, MultipleAssignments_746) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("First");
    EXPECT_EQ(datum.toString(), "First");
    datum.setValue("Second");
    EXPECT_EQ(datum.toString(), "Second");
    datum.setValue("Third");
    EXPECT_EQ(datum.toString(), "Third");
}

// Test different ExifKey groups
TEST_F(ExifdatumTest_746, DifferentGroups_746) {
    {
        ExifKey key("Exif.Photo.ISOSpeedRatings");
        Exifdatum datum(key, nullptr);
        EXPECT_EQ(datum.groupName(), "Photo");
    }
    {
        ExifKey key("Exif.GPSInfo.GPSLatitude");
        Exifdatum datum(key, nullptr);
        EXPECT_EQ(datum.groupName(), "GPSInfo");
    }
}

// Test ExifKey constructed by tag number and group name
TEST_F(ExifdatumTest_746, ExifKeyByTagAndGroup_746) {
    // 0x010f is Make tag in Image group
    ExifKey key(0x010f, "Image");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), 0x010f);
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test toInt64
TEST_F(ExifdatumTest_746, ToInt64_746) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    uint32_t val = 12345;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 12345);
}
