#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exiv2.hpp>
#include <memory>
#include <cmath>

using namespace Exiv2;

class ExifdatumTest_761 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that toFloat returns -1 when no value is set
TEST_F(ExifdatumTest_761, ToFloatReturnsNegativeOneWhenNoValue_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    float result = datum.toFloat(0);
    EXPECT_FLOAT_EQ(result, -1.0f);
}

// Test that toFloat returns correct value when a value is set
TEST_F(ExifdatumTest_761, ToFloatReturnsValueWhenSet_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur(72, 1);
    datum = ur;
    float result = datum.toFloat(0);
    EXPECT_FLOAT_EQ(result, 72.0f);
}

// Test toFloat with a rational value
TEST_F(ExifdatumTest_761, ToFloatWithRational_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur(1, 2);
    datum = ur;
    float result = datum.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.5f);
}

// Test toFloat with signed rational
TEST_F(ExifdatumTest_761, ToFloatWithSignedRational_761) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key, nullptr);
    Rational r(-1, 3);
    datum = r;
    float result = datum.toFloat(0);
    EXPECT_NEAR(result, -1.0f / 3.0f, 0.0001f);
}

// Test toFloat with uint16_t value
TEST_F(ExifdatumTest_761, ToFloatWithUint16_761) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 42;
    datum = val;
    float result = datum.toFloat(0);
    EXPECT_FLOAT_EQ(result, 42.0f);
}

// Test toFloat with uint32_t value
TEST_F(ExifdatumTest_761, ToFloatWithUint32_761) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    uint32_t val = 1920;
    datum = val;
    float result = datum.toFloat(0);
    EXPECT_FLOAT_EQ(result, 1920.0f);
}

// Test toFloat with int16_t value
TEST_F(ExifdatumTest_761, ToFloatWithInt16_761) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    int16_t val = -5;
    datum = val;
    float result = datum.toFloat(0);
    EXPECT_FLOAT_EQ(result, -5.0f);
}

// Test toFloat with int32_t value
TEST_F(ExifdatumTest_761, ToFloatWithInt32_761) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key, nullptr);
    int32_t val = -100;
    datum = val;
    float result = datum.toFloat(0);
    EXPECT_FLOAT_EQ(result, -100.0f);
}

// Test copy constructor preserves value for toFloat
TEST_F(ExifdatumTest_761, CopyConstructorPreservesValue_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur(300, 1);
    datum = ur;
    
    Exifdatum copy(datum);
    float result = copy.toFloat(0);
    EXPECT_FLOAT_EQ(result, 300.0f);
}

// Test copy constructor with no value
TEST_F(ExifdatumTest_761, CopyConstructorNoValue_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    Exifdatum copy(datum);
    float result = copy.toFloat(0);
    EXPECT_FLOAT_EQ(result, -1.0f);
}

// Test assignment operator preserves value for toFloat
TEST_F(ExifdatumTest_761, AssignmentOperatorPreservesValue_761) {
    ExifKey key1("Exif.Image.XResolution");
    ExifKey key2("Exif.Image.YResolution");
    Exifdatum datum1(key1, nullptr);
    Exifdatum datum2(key2, nullptr);
    
    URational ur(150, 1);
    datum1 = ur;
    datum2 = datum1;
    
    float result = datum2.toFloat(0);
    EXPECT_FLOAT_EQ(result, 150.0f);
}

// Test toFloat with n=0 for multi-component not applicable (single value)
TEST_F(ExifdatumTest_761, ToFloatIndexZero_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur(96, 1);
    datum = ur;
    float result = datum.toFloat(0);
    EXPECT_FLOAT_EQ(result, 96.0f);
}

// Test key method
TEST_F(ExifdatumTest_761, KeyReturnsCorrectKey_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Exif.Image.XResolution");
}

// Test familyName
TEST_F(ExifdatumTest_761, FamilyNameReturnsExif_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test groupName
TEST_F(ExifdatumTest_761, GroupNameReturnsCorrect_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Image");
}

// Test tagName
TEST_F(ExifdatumTest_761, TagNameReturnsCorrect_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "XResolution");
}

// Test tag number
TEST_F(ExifdatumTest_761, TagReturnsCorrectNumber_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    // XResolution tag number is 0x011a = 282
    EXPECT_EQ(datum.tag(), 0x011a);
}

// Test toString when no value set
TEST_F(ExifdatumTest_761, ToStringNoValue_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    std::string result = datum.toString();
    EXPECT_EQ(result, "");
}

// Test toString with a value set
TEST_F(ExifdatumTest_761, ToStringWithValue_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur(72, 1);
    datum = ur;
    std::string result = datum.toString();
    EXPECT_FALSE(result.empty());
}

// Test count when no value
TEST_F(ExifdatumTest_761, CountNoValue_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test count with value set
TEST_F(ExifdatumTest_761, CountWithValue_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur(72, 1);
    datum = ur;
    EXPECT_EQ(datum.count(), 1u);
}

// Test toInt64 when no value
TEST_F(ExifdatumTest_761, ToInt64NoValue_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    int64_t result = datum.toInt64(0);
    EXPECT_EQ(result, -1);
}

// Test toInt64 with a value
TEST_F(ExifdatumTest_761, ToInt64WithValue_761) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 6;
    datum = val;
    int64_t result = datum.toInt64(0);
    EXPECT_EQ(result, 6);
}

// Test setValue with string
TEST_F(ExifdatumTest_761, SetValueWithString_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    // First set a type via URational assignment, then try string
    URational ur(72, 1);
    datum = ur;
    int ret = datum.setValue("300/1");
    EXPECT_EQ(ret, 0);
    float result = datum.toFloat(0);
    EXPECT_FLOAT_EQ(result, 300.0f);
}

// Test toRational when no value
TEST_F(ExifdatumTest_761, ToRationalNoValue_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 1);
}

// Test toRational with value
TEST_F(ExifdatumTest_761, ToRationalWithValue_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur(72, 1);
    datum = ur;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 72);
    EXPECT_EQ(result.second, 1);
}

// Test getValue returns nullptr when no value
TEST_F(ExifdatumTest_761, GetValueNullWhenNoValue_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    auto val = datum.getValue();
    EXPECT_EQ(val, nullptr);
}

// Test getValue returns non-null when value is set
TEST_F(ExifdatumTest_761, GetValueNonNullWhenValueSet_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur(72, 1);
    datum = ur;
    auto val = datum.getValue();
    EXPECT_NE(val, nullptr);
}

// Test URational with zero denominator
TEST_F(ExifdatumTest_761, ToFloatWithZeroDenominator_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur(1, 0);
    datum = ur;
    float result = datum.toFloat(0);
    // The behavior with zero denominator - could be inf or special value
    EXPECT_TRUE(std::isinf(result) || std::isnan(result) || result == 0.0f);
}

// Test size when no value
TEST_F(ExifdatumTest_761, SizeNoValue_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test size with value
TEST_F(ExifdatumTest_761, SizeWithValue_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur(72, 1);
    datum = ur;
    EXPECT_GT(datum.size(), 0u);
}

// Test typeId when no value
TEST_F(ExifdatumTest_761, TypeIdNoValue_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    TypeId tid = datum.typeId();
    EXPECT_EQ(tid, invalidTypeId);
}

// Test typeId with URational value
TEST_F(ExifdatumTest_761, TypeIdWithURational_761) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    URational ur(72, 1);
    datum = ur;
    TypeId tid = datum.typeId();
    EXPECT_EQ(tid, unsignedRational);
}

// Test toFloat with string value assignment
TEST_F(ExifdatumTest_761, ToFloatWithStringAssignment_761) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    uint16_t val = 1;
    datum = val;
    datum.setValue("3");
    float result = datum.toFloat(0);
    EXPECT_FLOAT_EQ(result, 3.0f);
}
