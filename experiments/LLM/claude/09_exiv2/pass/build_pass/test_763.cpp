#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/types.hpp>
#include <memory>
#include <string>
#include <sstream>

using namespace Exiv2;

class ExifdatumTest_763 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with ExifKey and null Value pointer
TEST_F(ExifdatumTest_763, ConstructWithKeyAndNullValue_763) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test construction with ExifKey and a Value
TEST_F(ExifdatumTest_763, ConstructWithKeyAndValue_763) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.toString(), "Canon");
}

// Test copy constructor
TEST_F(ExifdatumTest_763, CopyConstructor_763) {
    ExifKey key("Exif.Image.Model");
    AsciiValue val;
    val.read("EOS 5D");
    Exifdatum original(key, &val);
    Exifdatum copy(original);
    EXPECT_EQ(copy.key(), "Exif.Image.Model");
    EXPECT_EQ(copy.toString(), "EOS 5D");
}

// Test copy assignment operator
TEST_F(ExifdatumTest_763, CopyAssignment_763) {
    ExifKey key1("Exif.Image.Make");
    AsciiValue val1;
    val1.read("Canon");
    Exifdatum datum1(key1, &val1);

    ExifKey key2("Exif.Image.Model");
    AsciiValue val2;
    val2.read("EOS R");
    Exifdatum datum2(key2, &val2);

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Exif.Image.Make");
    EXPECT_EQ(datum2.toString(), "Canon");
}

// Test assignment from string
TEST_F(ExifdatumTest_763, AssignString_763) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    datum = std::string("Nikon");
    EXPECT_EQ(datum.toString(), "Nikon");
}

// Test assignment from uint16_t
TEST_F(ExifdatumTest_763, AssignUint16_763) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);
    datum = static_cast<uint16_t>(3);
    EXPECT_EQ(datum.toInt64(0), 3);
}

// Test assignment from uint32_t
TEST_F(ExifdatumTest_763, AssignUint32_763) {
    ExifKey key("Exif.Image.ImageWidth");
    ULongValue val;
    val.read("100");
    Exifdatum datum(key, &val);
    datum = static_cast<uint32_t>(4000);
    EXPECT_EQ(datum.toInt64(0), 4000);
}

// Test assignment from int16_t
TEST_F(ExifdatumTest_763, AssignInt16_763) {
    ExifKey key("Exif.Image.Orientation");
    ShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);
    datum = static_cast<int16_t>(-5);
    EXPECT_EQ(datum.toInt64(0), -5);
}

// Test assignment from int32_t
TEST_F(ExifdatumTest_763, AssignInt32_763) {
    ExifKey key("Exif.Image.ImageWidth");
    LongValue val;
    val.read("100");
    Exifdatum datum(key, &val);
    datum = static_cast<int32_t>(-1000);
    EXPECT_EQ(datum.toInt64(0), -1000);
}

// Test assignment from URational
TEST_F(ExifdatumTest_763, AssignURational_763) {
    ExifKey key("Exif.Photo.ExposureTime");
    URationalValue val;
    val.read("1/100");
    Exifdatum datum(key, &val);
    URational ur(1, 250);
    datum = ur;
    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 250);
}

// Test assignment from Rational
TEST_F(ExifdatumTest_763, AssignRational_763) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    RationalValue val;
    val.read("-1/3");
    Exifdatum datum(key, &val);
    Rational rat(-2, 3);
    datum = rat;
    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, -2);
    EXPECT_EQ(r.second, 3);
}

// Test assignment from Value
TEST_F(ExifdatumTest_763, AssignValue_763) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);

    AsciiValue newVal;
    newVal.read("Sony");
    datum = static_cast<const Value&>(newVal);
    EXPECT_EQ(datum.toString(), "Sony");
}

// Test setValue with Value pointer
TEST_F(ExifdatumTest_763, SetValueWithPointer_763) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    AsciiValue val;
    val.read("Panasonic");
    datum.setValue(&val);
    EXPECT_EQ(datum.toString(), "Panasonic");
}

// Test setValue with nullptr
TEST_F(ExifdatumTest_763, SetValueWithNullPointer_763) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);

    datum.setValue(nullptr);
    auto v = datum.getValue();
    EXPECT_EQ(v, nullptr);
}

// Test setValue with string
TEST_F(ExifdatumTest_763, SetValueWithString_763) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);

    int result = datum.setValue("Olympus");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Olympus");
}

// Test getValue returns clone (not nullptr when value is set)
TEST_F(ExifdatumTest_763, GetValueReturnsClone_763) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Leica");
    Exifdatum datum(key, &val);

    auto v = datum.getValue();
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->toString(), "Leica");
}

// Test getValue returns nullptr when no value is set
TEST_F(ExifdatumTest_763, GetValueReturnsNullWhenNoValue_763) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);

    auto v = datum.getValue();
    EXPECT_EQ(v, nullptr);
}

// Test key() returns correct key string
TEST_F(ExifdatumTest_763, KeyReturnsCorrectString_763) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
}

// Test familyName() returns "Exif"
TEST_F(ExifdatumTest_763, FamilyNameReturnsExif_763) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test groupName()
TEST_F(ExifdatumTest_763, GroupNameReturnsCorrectGroup_763) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Image");
}

// Test tagName()
TEST_F(ExifdatumTest_763, TagNameReturnsCorrectTag_763) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test tag() returns correct tag number
TEST_F(ExifdatumTest_763, TagReturnsCorrectNumber_763) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // Make tag is 0x010f
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test typeId() for ASCII value
TEST_F(ExifdatumTest_763, TypeIdForAsciiValue_763) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    EXPECT_EQ(datum.typeId(), asciiString);
}

// Test count() for a value
TEST_F(ExifdatumTest_763, CountReturnsCorrectCount_763) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    EXPECT_GT(datum.count(), static_cast<size_t>(0));
}

// Test size() for a value
TEST_F(ExifdatumTest_763, SizeReturnsNonZero_763) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    EXPECT_GT(datum.size(), static_cast<size_t>(0));
}

// Test toString() with index
TEST_F(ExifdatumTest_763, ToStringWithIndex_763) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    EXPECT_EQ(datum.toString(0), "Canon");
}

// Test toInt64 for numeric value
TEST_F(ExifdatumTest_763, ToInt64ForNumericValue_763) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("6");
    Exifdatum datum(key, &val);
    EXPECT_EQ(datum.toInt64(0), 6);
}

// Test toFloat for numeric value
TEST_F(ExifdatumTest_763, ToFloatForNumericValue_763) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("6");
    Exifdatum datum(key, &val);
    EXPECT_FLOAT_EQ(datum.toFloat(0), 6.0f);
}

// Test toRational for rational value
TEST_F(ExifdatumTest_763, ToRationalForRationalValue_763) {
    ExifKey key("Exif.Photo.ExposureTime");
    URationalValue val;
    val.read("1/500");
    Exifdatum datum(key, &val);
    Rational r = datum.toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 500);
}

// Test write to ostream
TEST_F(ExifdatumTest_763, WriteToOstream_763) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test value() reference access
TEST_F(ExifdatumTest_763, ValueReferenceAccess_763) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Fujifilm");
    Exifdatum datum(key, &val);
    const Value& vref = datum.value();
    EXPECT_EQ(vref.toString(), "Fujifilm");
}

// Test sizeDataArea when no data area
TEST_F(ExifdatumTest_763, SizeDataAreaDefault_763) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    EXPECT_EQ(datum.sizeDataArea(), static_cast<size_t>(0));
}

// Test copy to buffer
TEST_F(ExifdatumTest_763, CopyToBuffer_763) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);
    byte buf[64] = {};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, static_cast<size_t>(0));
}

// Test tagLabel returns non-empty string for known tag
TEST_F(ExifdatumTest_763, TagLabelNonEmpty_763) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test idx() default
TEST_F(ExifdatumTest_763, IdxDefault_763) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key, nullptr);
    // idx should have a default value, typically 0
    EXPECT_GE(datum.idx(), 0);
}

// Test typeName for known type
TEST_F(ExifdatumTest_763, TypeNameForAscii_763) {
    ExifKey key("Exif.Image.Make");
    AsciiValue val;
    val.read("Canon");
    Exifdatum datum(key, &val);
    EXPECT_STREQ(datum.typeName(), "Ascii");
}

// Test typeSize for known type
TEST_F(ExifdatumTest_763, TypeSizeForUShort_763) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);
    EXPECT_EQ(datum.typeSize(), static_cast<size_t>(2));
}

// Test multiple values in UShortValue
TEST_F(ExifdatumTest_763, MultipleValuesInUShort_763) {
    ExifKey key("Exif.Image.Orientation");
    UShortValue val;
    val.read("1");
    Exifdatum datum(key, &val);
    EXPECT_EQ(datum.count(), static_cast<size_t>(1));
    EXPECT_EQ(datum.toInt64(0), 1);
}

// Test different Exif group (Photo)
TEST_F(ExifdatumTest_763, PhotoGroupTag_763) {
    ExifKey key("Exif.Photo.ISOSpeedRatings");
    UShortValue val;
    val.read("400");
    Exifdatum datum(key, &val);
    EXPECT_EQ(datum.groupName(), "Photo");
    EXPECT_EQ(datum.toInt64(0), 400);
}
