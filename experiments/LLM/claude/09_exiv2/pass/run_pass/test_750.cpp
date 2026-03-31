#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <string>
#include <cstring>

using namespace Exiv2;

class ExifdatumTest_750 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction with a known ExifKey
TEST_F(ExifdatumTest_750, ConstructWithExifKey_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test ifdName returns non-empty string for valid key
TEST_F(ExifdatumTest_750, IfdNameReturnsValidName_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    const char* name = datum.ifdName();
    ASSERT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

// Test familyName returns "Exif"
TEST_F(ExifdatumTest_750, FamilyNameIsExif_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    const char* family = datum.familyName();
    ASSERT_NE(family, nullptr);
    EXPECT_STREQ(family, "Exif");
}

// Test groupName matches the key's group
TEST_F(ExifdatumTest_750, GroupNameMatchesKey_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Image");
}

// Test tagName matches the key's tag name
TEST_F(ExifdatumTest_750, TagNameMatchesKey_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test tag() returns expected tag number for Make
TEST_F(ExifdatumTest_750, TagNumberForMake_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Make tag is 0x010f
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test copy constructor
TEST_F(ExifdatumTest_750, CopyConstructor_750) {
    ExifKey key("Exif.Image.Model");
    Exifdatum datum1(key, nullptr);
    datum1.setValue("TestCamera");
    
    Exifdatum datum2(datum1);
    EXPECT_EQ(datum2.key(), "Exif.Image.Model");
    EXPECT_EQ(datum2.toString(), "TestCamera");
}

// Test assignment operator
TEST_F(ExifdatumTest_750, AssignmentOperator_750) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1, nullptr);
    datum1.setValue("Canon");
    
    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2, nullptr);
    datum2 = datum1;
    
    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.toString(), "Canon");
}

// Test setValue with string
TEST_F(ExifdatumTest_750, SetValueString_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    int result = datum.setValue("Nikon");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Nikon");
}

// Test operator= with string
TEST_F(ExifdatumTest_750, AssignString_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Sony");
    EXPECT_EQ(datum.toString(), "Sony");
}

// Test operator= with uint16_t
TEST_F(ExifdatumTest_750, AssignUint16_750) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 1);
}

// Test operator= with uint32_t
TEST_F(ExifdatumTest_750, AssignUint32_750) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    uint32_t val = 1920;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 1920);
}

// Test operator= with int16_t
TEST_F(ExifdatumTest_750, AssignInt16_750) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    int16_t val = 3;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 3);
}

// Test operator= with int32_t
TEST_F(ExifdatumTest_750, AssignInt32_750) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    int32_t val = 4096;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 4096);
}

// Test operator= with Rational
TEST_F(ExifdatumTest_750, AssignRational_750) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    Rational rat = {72, 1};
    datum = rat;
    EXPECT_EQ(datum.toRational(0).first, 72);
    EXPECT_EQ(datum.toRational(0).second, 1);
}

// Test operator= with URational
TEST_F(ExifdatumTest_750, AssignURational_750) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational urat = {300, 1};
    datum = urat;
    EXPECT_EQ(datum.toInt64(0), 300);
}

// Test count() when no value is set
TEST_F(ExifdatumTest_750, CountWithNoValue_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test count() after setting a string value
TEST_F(ExifdatumTest_750, CountAfterSetValue_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestValue");
    EXPECT_GT(datum.count(), 0u);
}

// Test size() when no value is set
TEST_F(ExifdatumTest_750, SizeWithNoValue_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test size() after setting a value
TEST_F(ExifdatumTest_750, SizeAfterSetValue_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Hello");
    EXPECT_GT(datum.size(), 0u);
}

// Test typeId when no value is set
TEST_F(ExifdatumTest_750, TypeIdWithNoValue_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.typeId(), invalidTypeId);
}

// Test typeName when no value is set
TEST_F(ExifdatumTest_750, TypeNameWithNoValue_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // When no value set, typeName should handle gracefully
    const char* tn = datum.typeName();
    // May be nullptr or empty, just shouldn't crash
    (void)tn;
}

// Test getValue when no value is set
TEST_F(ExifdatumTest_750, GetValueWithNoValue_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    auto val = datum.getValue();
    // Should return nullptr when no value is set
    EXPECT_EQ(val.get(), nullptr);
}

// Test getValue when value is set
TEST_F(ExifdatumTest_750, GetValueWithValue_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestMake");
    auto val = datum.getValue();
    EXPECT_NE(val.get(), nullptr);
}

// Test ifdId for Image IFD
TEST_F(ExifdatumTest_750, IfdIdForImageIfd_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    IfdId id = datum.ifdId();
    // Should be ifd0Id for Image group
    EXPECT_EQ(id, IfdId::ifd0Id);
}

// Test ifdId for Photo (Exif) IFD
TEST_F(ExifdatumTest_750, IfdIdForPhotoIfd_750) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key, nullptr);
    IfdId id = datum.ifdId();
    EXPECT_EQ(id, IfdId::exifId);
}

// Test with a different group - GPSInfo
TEST_F(ExifdatumTest_750, GpsGroupDatum_750) {
    ExifKey key("Exif.GPSInfo.GPSLatitude");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "GPSInfo");
    const char* ifdname = datum.ifdName();
    ASSERT_NE(ifdname, nullptr);
    EXPECT_STRNE(ifdname, "");
}

// Test idx() default value
TEST_F(ExifdatumTest_750, IdxDefault_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // idx should have a default value (typically 0)
    int idx = datum.idx();
    EXPECT_GE(idx, 0);
}

// Test tagLabel returns non-empty for known tags
TEST_F(ExifdatumTest_750, TagLabelForKnownTag_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test toString with index parameter
TEST_F(ExifdatumTest_750, ToStringWithIndex_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestMaker");
    std::string s = datum.toString(0);
    EXPECT_EQ(s, "TestMaker");
}

// Test toFloat
TEST_F(ExifdatumTest_750, ToFloat_750) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational urat = {72, 1};
    datum = urat;
    float f = datum.toFloat(0);
    EXPECT_FLOAT_EQ(f, 72.0f);
}

// Test setting value via Value object
TEST_F(ExifdatumTest_750, SetValueViaValueObject_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    AsciiValue val;
    val.read("TestValue");
    datum = val;
    
    EXPECT_EQ(datum.toString(), "TestValue");
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_750, SetValueWithValuePointer_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    
    auto val = std::make_unique<AsciiValue>();
    val->read("PointerValue");
    datum.setValue(val.get());
    
    EXPECT_EQ(datum.toString(), "PointerValue");
}

// Test setValue with nullptr
TEST_F(ExifdatumTest_750, SetValueWithNullptr_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("SomeValue");
    EXPECT_NE(datum.count(), 0u);
    
    datum.setValue(static_cast<const Value*>(nullptr));
    EXPECT_EQ(datum.count(), 0u);
}

// Test sizeDataArea when no data area
TEST_F(ExifdatumTest_750, SizeDataAreaNoData_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Test");
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test copy to buffer
TEST_F(ExifdatumTest_750, CopyToBuffer_750) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    
    byte buf[64] = {};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test write to ostream
TEST_F(ExifdatumTest_750, WriteToStream_750) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("StreamTest");
    
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test construction with tag number and group name
TEST_F(ExifdatumTest_750, ConstructWithTagAndGroup_750) {
    ExifKey key(0x010f, "Image");  // Make tag
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), 0x010f);
    EXPECT_EQ(datum.groupName(), "Image");
}

// Test typeSize when value is set
TEST_F(ExifdatumTest_750, TypeSizeWithValue_750) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    EXPECT_GT(datum.typeSize(), 0u);
}

// Test that key() returns full dotted notation
TEST_F(ExifdatumTest_750, KeyFullDottedNotation_750) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key, nullptr);
    std::string k = datum.key();
    EXPECT_EQ(k, "Exif.Photo.ExposureTime");
    EXPECT_EQ(datum.tagName(), "ExposureTime");
    EXPECT_EQ(datum.groupName(), "Photo");
    EXPECT_STREQ(datum.familyName(), "Exif");
}
