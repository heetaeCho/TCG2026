#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

class ExifdatumTest_742 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with ExifKey and key() method
TEST_F(ExifdatumTest_742, ConstructWithExifKeyReturnsCorrectKey_742) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Exif.Image.Make", datum.key());
}

// Test familyName returns "Exif"
TEST_F(ExifdatumTest_742, FamilyNameReturnsExif_742) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string family = datum.familyName();
    EXPECT_STREQ("Exif", family.c_str());
}

// Test groupName
TEST_F(ExifdatumTest_742, GroupNameReturnsCorrectGroup_742) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Image", datum.groupName());
}

// Test tagName
TEST_F(ExifdatumTest_742, TagNameReturnsCorrectTag_742) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Make", datum.tagName());
}

// Test tag() returns correct tag number
TEST_F(ExifdatumTest_742, TagReturnsCorrectTagNumber_742) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Make tag is 0x010f
    EXPECT_EQ(0x010f, datum.tag());
}

// Test copy constructor
TEST_F(ExifdatumTest_742, CopyConstructorCopiesKey_742) {
    ExifKey key("Exif.Image.Model");
    Exifdatum datum1(key, nullptr);
    Exifdatum datum2(datum1);
    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ("Exif.Image.Model", datum2.key());
}

// Test copy assignment operator
TEST_F(ExifdatumTest_742, CopyAssignmentCopiesKey_742) {
    ExifKey key1("Exif.Image.Make");
    ExifKey key2("Exif.Image.Model");
    Exifdatum datum1(key1, nullptr);
    Exifdatum datum2(key2, nullptr);
    datum2 = datum1;
    EXPECT_EQ("Exif.Image.Make", datum2.key());
}

// Test setValue with string when no value is set initially
TEST_F(ExifdatumTest_742, SetValueStringOnNullValue_742) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    int result = datum.setValue("Canon");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Canon", datum.toString());
}

// Test assignment operator with string
TEST_F(ExifdatumTest_742, AssignStringValue_742) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("InitialValue");
    datum = std::string("NewValue");
    EXPECT_EQ("NewValue", datum.toString());
}

// Test count when no value is set
TEST_F(ExifdatumTest_742, CountWithNoValueReturnsZero_742) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(0u, datum.count());
}

// Test size when no value is set
TEST_F(ExifdatumTest_742, SizeWithNoValueReturnsZero_742) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(0u, datum.size());
}

// Test typeId when no value set
TEST_F(ExifdatumTest_742, TypeIdWithNoValueReturnsInvalidTypeId_742) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(invalidTypeId, datum.typeId());
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_742, SetValueWithValuePointer_742) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    AsciiValue val("TestValue");
    datum.setValue(&val);
    EXPECT_EQ("TestValue", datum.toString());
    EXPECT_EQ(asciiString, datum.typeId());
}

// Test assignment with uint16_t
TEST_F(ExifdatumTest_742, AssignUint16Value_742) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    // Need to set an initial value with correct type first
    UShortValue val;
    val.read("1");
    datum.setValue(&val);
    datum = static_cast<uint16_t>(6);
    EXPECT_EQ(6, datum.toInt64(0));
}

// Test assignment with int32_t
TEST_F(ExifdatumTest_742, AssignInt32Value_742) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    LongValue val;
    val.read("100");
    datum.setValue(&val);
    datum = static_cast<int32_t>(200);
    EXPECT_EQ(200, datum.toInt64(0));
}

// Test getValue returns valid unique_ptr when value is set
TEST_F(ExifdatumTest_742, GetValueReturnsValidPtr_742) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val("TestMake");
    Exifdatum datum(key, &val);
    auto vp = datum.getValue();
    ASSERT_NE(nullptr, vp.get());
    EXPECT_EQ("TestMake", vp->toString());
}

// Test getValue returns nullptr when no value set
TEST_F(ExifdatumTest_742, GetValueReturnsNullWhenNoValue_742) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    auto vp = datum.getValue();
    EXPECT_EQ(nullptr, vp.get());
}

// Test toString with index when value is set
TEST_F(ExifdatumTest_742, ToStringWithIndex_742) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val("TestBrand");
    Exifdatum datum(key, &val);
    EXPECT_EQ("TestBrand", datum.toString(0));
}

// Test construction with tag number and group name
TEST_F(ExifdatumTest_742, ConstructWithTagNumberAndGroupName_742) {
    ExifKey key(0x010f, "Image");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Exif.Image.Make", datum.key());
    EXPECT_EQ(0x010f, datum.tag());
}

// Test ifdId
TEST_F(ExifdatumTest_742, IfdIdReturnsValidId_742) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    IfdId id = datum.ifdId();
    // ifdId for Image group should be ifd0Id
    EXPECT_EQ(ifd0Id, id);
}

// Test sizeDataArea when no data area is set
TEST_F(ExifdatumTest_742, SizeDataAreaReturnsZeroWhenEmpty_742) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(0u, datum.sizeDataArea());
}

// Test tagLabel returns non-empty string for known tag
TEST_F(ExifdatumTest_742, TagLabelReturnsNonEmptyForKnownTag_742) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test write to ostream
TEST_F(ExifdatumTest_742, WriteToOutputStream_742) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val("Canon");
    Exifdatum datum(key, &val);
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test assignment with URational
TEST_F(ExifdatumTest_742, AssignURationalValue_742) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URationalValue val;
    val.read("72/1");
    datum.setValue(&val);
    datum = URational(300, 1);
    Rational r = datum.toRational(0);
    EXPECT_EQ(300, r.first);
    EXPECT_EQ(1, r.second);
}

// Test assignment with Rational
TEST_F(ExifdatumTest_742, AssignRationalValue_742) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key, nullptr);
    RationalValue val;
    val.read("0/1");
    datum.setValue(&val);
    datum = Rational(1, 3);
    Rational r = datum.toRational(0);
    EXPECT_EQ(1, r.first);
    EXPECT_EQ(3, r.second);
}

// Test typeName when no value is set
TEST_F(ExifdatumTest_742, TypeNameWithNoValueReturnsExpected_742) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // When no value, typeName should return something (possibly nullptr or "(Invalid)")
    const char* tn = datum.typeName();
    // Just verify it doesn't crash; the exact value depends on implementation
    (void)tn;
}

// Test count after setting a value with multiple components
TEST_F(ExifdatumTest_742, CountReflectsMultipleComponents_742) {
    ExifKey key("Exif.Image.BitsPerSample");
    UShortValue val;
    val.read("8 8 8");
    Exifdatum datum(key, &val);
    EXPECT_EQ(3u, datum.count());
}

// Test toFloat
TEST_F(ExifdatumTest_742, ToFloatReturnsCorrectValue_742) {
    ExifKey key("Exif.Image.XResolution");
    URationalValue val;
    val.read("72/1");
    Exifdatum datum(key, &val);
    float f = datum.toFloat(0);
    EXPECT_FLOAT_EQ(72.0f, f);
}

// Test toInt64
TEST_F(ExifdatumTest_742, ToInt64ReturnsCorrectValue_742) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);
    int64_t i = datum.toInt64(0);
    EXPECT_EQ(1, i);
}

// Test different ExifKey constructions yield correct Exifdatum properties
TEST_F(ExifdatumTest_742, ExifdatumWithPhotoGroup_742) {
    ExifKey key("Exif.Photo.DateTimeOriginal");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ("Exif.Photo.DateTimeOriginal", datum.key());
    EXPECT_EQ("Photo", datum.groupName());
    EXPECT_EQ("DateTimeOriginal", datum.tagName());
}

// Test setValue replaces existing value
TEST_F(ExifdatumTest_742, SetValueReplacesExistingValue_742) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val1("Canon");
    Exifdatum datum(key, &val1);
    EXPECT_EQ("Canon", datum.toString());
    
    AsciiValue val2("Nikon");
    datum.setValue(&val2);
    EXPECT_EQ("Nikon", datum.toString());
}

// Test copy preserves value
TEST_F(ExifdatumTest_742, CopyConstructorPreservesValue_742) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val("Canon");
    Exifdatum datum1(key, &val);
    Exifdatum datum2(datum1);
    EXPECT_EQ("Canon", datum2.toString());
    EXPECT_EQ(datum1.typeId(), datum2.typeId());
    EXPECT_EQ(datum1.count(), datum2.count());
}

// Test assignment with uint32_t
TEST_F(ExifdatumTest_742, AssignUint32Value_742) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    ULongValue val;
    val.read("100");
    datum.setValue(&val);
    datum = static_cast<uint32_t>(4000);
    EXPECT_EQ(4000, datum.toInt64(0));
}

// Test assignment with int16_t
TEST_F(ExifdatumTest_742, AssignInt16Value_742) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    ShortValue val;
    val.read("1");
    datum.setValue(&val);
    datum = static_cast<int16_t>(3);
    EXPECT_EQ(3, datum.toInt64(0));
}

// Test idx method
TEST_F(ExifdatumTest_742, IdxReturnsDefaultIndex_742) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Default idx should be 0
    EXPECT_EQ(0, datum.idx());
}

// Test construction with Value pointer in constructor
TEST_F(ExifdatumTest_742, ConstructWithValuePointer_742) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val("Sony");
    Exifdatum datum(key, &val);
    EXPECT_EQ("Sony", datum.toString());
    EXPECT_EQ(asciiString, datum.typeId());
    EXPECT_GT(datum.size(), 0u);
}
