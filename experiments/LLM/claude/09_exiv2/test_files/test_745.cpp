#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

class ExifdatumTest_745 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction with a known ExifKey and verify tagName
TEST_F(ExifdatumTest_745, ConstructWithExifKey_TagName_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Make", datum.tagName());
}

// Test construction with a known ExifKey and verify key()
TEST_F(ExifdatumTest_745, ConstructWithExifKey_Key_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Exif.Image.Make", datum.key());
}

// Test familyName returns "Exif"
TEST_F(ExifdatumTest_745, FamilyName_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_STREQ("Exif", datum.familyName());
}

// Test groupName
TEST_F(ExifdatumTest_745, GroupName_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Image", datum.groupName());
}

// Test tag() returns the correct tag number
TEST_F(ExifdatumTest_745, Tag_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Make tag is 0x010f
    EXPECT_EQ(0x010f, datum.tag());
}

// Test tagLabel returns a non-empty label for known tags
TEST_F(ExifdatumTest_745, TagLabel_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_FALSE(datum.tagLabel().empty());
}

// Test setValue with string and then toString
TEST_F(ExifdatumTest_745, SetValueString_ToString_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon");
    EXPECT_EQ("Canon", datum.toString());
}

// Test operator= with string
TEST_F(ExifdatumTest_745, AssignString_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Nikon");
    EXPECT_EQ("Nikon", datum.toString());
}

// Test copy constructor
TEST_F(ExifdatumTest_745, CopyConstructor_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Sony");
    Exifdatum copy(datum);
    EXPECT_EQ("Exif.Image.Make", copy.key());
    EXPECT_EQ("Make", copy.tagName());
    EXPECT_EQ("Sony", copy.toString());
}

// Test copy assignment operator
TEST_F(ExifdatumTest_745, CopyAssignment_745) {
    ExifKey key1("Exif.Image.Make");
    ExifKey key2("Exif.Image.Model");
    Exifdatum datum1(key1, nullptr);
    Exifdatum datum2(key2, nullptr);
    datum1.setValue("Canon");
    datum2 = datum1;
    EXPECT_EQ("Exif.Image.Make", datum2.key());
    EXPECT_EQ("Canon", datum2.toString());
}

// Test operator= with uint16_t
TEST_F(ExifdatumTest_745, AssignUint16_745) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ(1, datum.toInt64(0));
}

// Test operator= with uint32_t
TEST_F(ExifdatumTest_745, AssignUint32_745) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint32_t>(1920);
    EXPECT_EQ(1920, datum.toInt64(0));
}

// Test operator= with int16_t
TEST_F(ExifdatumTest_745, AssignInt16_745) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<int16_t>(3);
    EXPECT_EQ(3, datum.toInt64(0));
}

// Test operator= with int32_t
TEST_F(ExifdatumTest_745, AssignInt32_745) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum = static_cast<int32_t>(4096);
    EXPECT_EQ(4096, datum.toInt64(0));
}

// Test operator= with URational
TEST_F(ExifdatumTest_745, AssignURational_745) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur = {72, 1};
    datum = ur;
    EXPECT_EQ(72, datum.toInt64(0));
}

// Test operator= with Rational
TEST_F(ExifdatumTest_745, AssignRational_745) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key, nullptr);
    Rational r = {-1, 3};
    datum = r;
    Rational result = datum.toRational(0);
    EXPECT_EQ(-1, result.first);
    EXPECT_EQ(3, result.second);
}

// Test count() with no value set
TEST_F(ExifdatumTest_745, CountNoValue_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(0u, datum.count());
}

// Test count() after setting a value
TEST_F(ExifdatumTest_745, CountAfterSetValue_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Test");
    EXPECT_GT(datum.count(), 0u);
}

// Test size() with no value
TEST_F(ExifdatumTest_745, SizeNoValue_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(0u, datum.size());
}

// Test size() after setting a value
TEST_F(ExifdatumTest_745, SizeAfterSetValue_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Hello");
    EXPECT_GT(datum.size(), 0u);
}

// Test typeId with no value
TEST_F(ExifdatumTest_745, TypeIdNoValue_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // With no value set, typeId should return invalidTypeId or some default
    TypeId tid = datum.typeId();
    (void)tid; // Just ensure it doesn't crash
}

// Test typeId after setting a string value
TEST_F(ExifdatumTest_745, TypeIdAfterSetString_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon");
    EXPECT_EQ(asciiString, datum.typeId());
}

// Test typeName after setting value
TEST_F(ExifdatumTest_745, TypeName_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Canon");
    EXPECT_STREQ("Ascii", datum.typeName());
}

// Test getValue returns non-null after setValue
TEST_F(ExifdatumTest_745, GetValueNonNull_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestVal");
    auto val = datum.getValue();
    ASSERT_NE(nullptr, val.get());
    EXPECT_EQ("TestVal", val->toString());
}

// Test value() reference after setValue
TEST_F(ExifdatumTest_745, ValueReference_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestRef");
    const Value& v = datum.value();
    EXPECT_EQ("TestRef", v.toString());
}

// Test toString with index
TEST_F(ExifdatumTest_745, ToStringWithIndex_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("IndexTest");
    std::string result = datum.toString(0);
    EXPECT_EQ("IndexTest", result);
}

// Test ifdId
TEST_F(ExifdatumTest_745, IfdId_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    IfdId id = datum.ifdId();
    EXPECT_EQ(IfdId::ifd0Id, id);
}

// Test with Photo group
TEST_F(ExifdatumTest_745, PhotoGroup_745) {
    ExifKey key("Exif.Photo.DateTimeOriginal");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Photo", datum.groupName());
    EXPECT_EQ("DateTimeOriginal", datum.tagName());
    EXPECT_EQ("Exif.Photo.DateTimeOriginal", datum.key());
}

// Test write to stream
TEST_F(ExifdatumTest_745, WriteToStream_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("StreamTest");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test sizeDataArea with no data area
TEST_F(ExifdatumTest_745, SizeDataAreaNoData_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("NoDataArea");
    EXPECT_EQ(0u, datum.sizeDataArea());
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_745, SetValueWithValuePtr_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    AsciiValue av;
    av.read("PtrTest");
    datum.setValue(&av);
    EXPECT_EQ("PtrTest", datum.toString());
}

// Test operator= with Value reference
TEST_F(ExifdatumTest_745, AssignValueRef_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    AsciiValue av;
    av.read("ValueRef");
    datum = static_cast<const Value&>(av);
    EXPECT_EQ("ValueRef", datum.toString());
}

// Test idx() default
TEST_F(ExifdatumTest_745, IdxDefault_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // idx should have a default value, just verify it doesn't crash
    int idx = datum.idx();
    (void)idx;
}

// Test toFloat
TEST_F(ExifdatumTest_745, ToFloat_745) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur = {72, 1};
    datum = ur;
    float f = datum.toFloat(0);
    EXPECT_FLOAT_EQ(72.0f, f);
}

// Test toRational
TEST_F(ExifdatumTest_745, ToRational_745) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur = {300, 1};
    datum = ur;
    Rational r = datum.toRational(0);
    EXPECT_EQ(300, r.first);
    EXPECT_EQ(1, r.second);
}

// Test construction with tag number and group name via ExifKey
TEST_F(ExifdatumTest_745, ConstructWithTagAndGroup_745) {
    ExifKey key(0x010f, "Image");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Exif.Image.Make", datum.key());
    EXPECT_EQ("Make", datum.tagName());
}

// Test setting value to empty string
TEST_F(ExifdatumTest_745, SetEmptyString_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("");
    // Should not crash, size/count may vary
    std::string result = datum.toString();
    // Empty or minimal
    (void)result;
}

// Test copy to buffer
TEST_F(ExifdatumTest_745, CopyToBuffer_745) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(6);
    byte buf[64] = {};
    size_t copied = datum.copy(buf, bigEndian);
    EXPECT_GT(copied, 0u);
}

// Test multiple assignments overwrite previous value
TEST_F(ExifdatumTest_745, MultipleAssignments_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("First");
    EXPECT_EQ("First", datum.toString());
    datum.setValue("Second");
    EXPECT_EQ("Second", datum.toString());
    datum.setValue("Third");
    EXPECT_EQ("Third", datum.toString());
}

// Test tagDesc returns something (may be empty for some tags)
TEST_F(ExifdatumTest_745, TagDesc_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string desc = datum.tagDesc();
    // Just verify it doesn't crash; desc may or may not be empty
    (void)desc;
}

// Test ifdName
TEST_F(ExifdatumTest_745, IfdName_745) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    const char* name = datum.ifdName();
    ASSERT_NE(nullptr, name);
    // Should be related to IFD0
    EXPECT_STRNE("", name);
}

// Test with GPS group
TEST_F(ExifdatumTest_745, GpsGroup_745) {
    ExifKey key("Exif.GPSInfo.GPSLatitude");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("GPSInfo", datum.groupName());
    EXPECT_EQ("GPSLatitude", datum.tagName());
}

// Test typeSize
TEST_F(ExifdatumTest_745, TypeSize_745) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ(2u, datum.typeSize()); // Short type is 2 bytes
}
