#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

class ExifdatumTest_743 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test familyName returns "Exif" for a valid ExifKey
TEST_F(ExifdatumTest_743, FamilyNameReturnsExif_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test key() returns the full key string
TEST_F(ExifdatumTest_743, KeyReturnsFullKeyString_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test groupName() returns the group name
TEST_F(ExifdatumTest_743, GroupNameReturnsCorrectGroup_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Image");
}

// Test tagName() returns the tag name
TEST_F(ExifdatumTest_743, TagNameReturnsCorrectTag_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test tag() returns the correct tag number
TEST_F(ExifdatumTest_743, TagReturnsCorrectTagNumber_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Make tag is 0x010f
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test count() returns 0 when no value is set
TEST_F(ExifdatumTest_743, CountReturnsZeroWhenNoValue_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test size() returns 0 when no value is set
TEST_F(ExifdatumTest_743, SizeReturnsZeroWhenNoValue_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test setValue with string
TEST_F(ExifdatumTest_743, SetValueWithString_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    int result = datum.setValue("Canon");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Canon");
}

// Test operator= with string
TEST_F(ExifdatumTest_743, OperatorAssignString_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum = std::string("Nikon");
    EXPECT_EQ(datum.toString(), "Nikon");
}

// Test copy constructor
TEST_F(ExifdatumTest_743, CopyConstructor_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestValue");
    Exifdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.familyName(), datum.familyName());
    EXPECT_EQ(copy.toString(), datum.toString());
}

// Test copy assignment operator
TEST_F(ExifdatumTest_743, CopyAssignmentOperator_743) {
    ExifKey key1("Exif.Image.Make");
    ExifKey key2("Exif.Image.Model");
    Exifdatum datum1(key1, nullptr);
    datum1.setValue("Canon");
    Exifdatum datum2(key2, nullptr);
    datum2.setValue("EOS");
    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "Canon");
}

// Test operator= with uint16_t
TEST_F(ExifdatumTest_743, OperatorAssignUint16_743) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ(datum.toInt64(0), 1);
}

// Test operator= with uint32_t
TEST_F(ExifdatumTest_743, OperatorAssignUint32_743) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint32_t>(1920);
    EXPECT_EQ(datum.toInt64(0), 1920);
}

// Test operator= with int16_t
TEST_F(ExifdatumTest_743, OperatorAssignInt16_743) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<int16_t>(3);
    EXPECT_EQ(datum.toInt64(0), 3);
}

// Test operator= with int32_t
TEST_F(ExifdatumTest_743, OperatorAssignInt32_743) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    datum = static_cast<int32_t>(4096);
    EXPECT_EQ(datum.toInt64(0), 4096);
}

// Test operator= with URational
TEST_F(ExifdatumTest_743, OperatorAssignURational_743) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur(72, 1);
    datum = ur;
    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, 72);
    EXPECT_EQ(r.second, 1);
}

// Test operator= with Rational
TEST_F(ExifdatumTest_743, OperatorAssignRational_743) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key, nullptr);
    Rational rat(-1, 3);
    datum = rat;
    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, -1);
    EXPECT_EQ(r.second, 3);
}

// Test typeId when no value set
TEST_F(ExifdatumTest_743, TypeIdWhenNoValue_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // When no value is set, typeId should return invalidTypeId or similar
    TypeId tid = datum.typeId();
    // Just check it doesn't crash; the actual value depends on implementation
    (void)tid;
}

// Test setValue with a Value object
TEST_F(ExifdatumTest_743, SetValueWithValuePtr_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    AsciiValue val;
    val.read("TestCamera");
    datum.setValue(&val);
    EXPECT_EQ(datum.toString(), "TestCamera");
    EXPECT_GT(datum.count(), 0u);
}

// Test getValue returns valid pointer after setting value
TEST_F(ExifdatumTest_743, GetValueReturnsValidPointer_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("SomeValue");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "SomeValue");
}

// Test getValue returns nullptr when no value is set
TEST_F(ExifdatumTest_743, GetValueReturnsNullWhenNoValue_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    auto val = datum.getValue();
    // Depending on implementation, getValue might return nullptr or throw
    // We just test it doesn't crash
    (void)val;
}

// Test toString returns empty-like string when no value set
TEST_F(ExifdatumTest_743, ToStringWhenNoValueSet_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string result = datum.toString();
    EXPECT_TRUE(result.empty());
}

// Test write to ostream
TEST_F(ExifdatumTest_743, WriteToOstream_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("TestWrite");
    std::ostringstream os;
    datum.write(os, nullptr);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test tagLabel returns a non-empty string for known tags
TEST_F(ExifdatumTest_743, TagLabelForKnownTag_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test construction with tag number and group name
TEST_F(ExifdatumTest_743, ConstructWithTagAndGroup_743) {
    ExifKey key(0x010f, "Image");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), 0x010f);
    EXPECT_EQ(datum.tagName(), "Make");
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test ifdId returns a valid IfdId
TEST_F(ExifdatumTest_743, IfdIdReturnsValidValue_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    IfdId id = datum.ifdId();
    EXPECT_NE(id, ifdIdNotSet);
}

// Test idx initial value
TEST_F(ExifdatumTest_743, IdxInitialValue_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    int idx = datum.idx();
    EXPECT_EQ(idx, 0);
}

// Test sizeDataArea returns 0 when no data area
TEST_F(ExifdatumTest_743, SizeDataAreaReturnsZero_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("Test");
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test copy to buffer
TEST_F(ExifdatumTest_743, CopyToBuffer_743) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);
    byte buf[64] = {};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test multiple setValue calls overwrite previous value
TEST_F(ExifdatumTest_743, SetValueOverwritesPrevious_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    datum.setValue("First");
    EXPECT_EQ(datum.toString(), "First");
    datum.setValue("Second");
    EXPECT_EQ(datum.toString(), "Second");
}

// Test operator= with Value reference
TEST_F(ExifdatumTest_743, OperatorAssignValueRef_743) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    AsciiValue val;
    val.read("ValueRef");
    datum = static_cast<const Value&>(val);
    EXPECT_EQ(datum.toString(), "ValueRef");
}

// Test toFloat
TEST_F(ExifdatumTest_743, ToFloatConversion_743) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur(72, 1);
    datum = ur;
    float f = datum.toFloat(0);
    EXPECT_FLOAT_EQ(f, 72.0f);
}

// Test different Exif groups
TEST_F(ExifdatumTest_743, PhotoGroupTag_743) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Photo");
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test typeName for known type
TEST_F(ExifdatumTest_743, TypeNameForSetValue_743) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    EXPECT_STREQ(tn, "Short");
}

// Test typeSize for uint16_t
TEST_F(ExifdatumTest_743, TypeSizeForShort_743) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    datum = static_cast<uint16_t>(1);
    EXPECT_EQ(datum.typeSize(), 2u);
}
