#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

using namespace Exiv2;

class ExifdatumTest_762 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that toRational returns Rational(-1, 1) when no value is set
TEST_F(ExifdatumTest_762, ToRationalReturnsDefaultWhenNoValue_762) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 1);
}

// Test that toRational returns correct value when a Rational value is set
TEST_F(ExifdatumTest_762, ToRationalReturnsCorrectValueWhenSet_762) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    Rational r(72, 1);
    datum = r;
    
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 72);
    EXPECT_EQ(result.second, 1);
}

// Test toRational with index 0
TEST_F(ExifdatumTest_762, ToRationalWithIndexZero_762) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    Rational r(300, 1);
    datum = r;
    
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 300);
    EXPECT_EQ(result.second, 1);
}

// Test toRational with a non-trivial rational value
TEST_F(ExifdatumTest_762, ToRationalWithNonTrivialFraction_762) {
    ExifKey key("Exif.Photo.ExposureTime");
    Exifdatum datum(key, nullptr);
    
    Rational r(1, 250);
    datum = r;
    
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 250);
}

// Test toRational with negative rational values
TEST_F(ExifdatumTest_762, ToRationalWithNegativeValues_762) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key, nullptr);
    
    Rational r(-3, 2);
    datum = r;
    
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -3);
    EXPECT_EQ(result.second, 2);
}

// Test toRational returns default for out-of-range index when value is set
TEST_F(ExifdatumTest_762, ToRationalOutOfRangeIndex_762) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    Rational r(72, 1);
    datum = r;
    
    // For a single-element value, accessing index 1 should give some result
    // (we just observe what happens -- the behavior depends on Value implementation)
    Rational result = datum.toRational(1);
    // We don't assert specific values here since behavior for out-of-range
    // depends on Value implementation, but we verify it doesn't crash
    (void)result;
}

// Test copy constructor preserves toRational behavior with value
TEST_F(ExifdatumTest_762, CopyConstructorPreservesRationalValue_762) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    Rational r(150, 1);
    datum = r;
    
    Exifdatum copy(datum);
    
    Rational result = copy.toRational(0);
    EXPECT_EQ(result.first, 150);
    EXPECT_EQ(result.second, 1);
}

// Test copy constructor preserves default behavior when no value
TEST_F(ExifdatumTest_762, CopyConstructorNoValueReturnsDefault_762) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    Exifdatum copy(datum);
    
    Rational result = copy.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 1);
}

// Test assignment operator preserves rational value
TEST_F(ExifdatumTest_762, AssignmentOperatorPreservesRationalValue_762) {
    ExifKey key1("Exif.Image.XResolution");
    Exifdatum datum1(key1, nullptr);
    Rational r(200, 1);
    datum1 = r;
    
    ExifKey key2("Exif.Image.YResolution");
    Exifdatum datum2(key2, nullptr);
    datum2 = datum1;
    
    Rational result = datum2.toRational(0);
    EXPECT_EQ(result.first, 200);
    EXPECT_EQ(result.second, 1);
}

// Test toRational with zero rational
TEST_F(ExifdatumTest_762, ToRationalWithZeroValue_762) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key, nullptr);
    
    Rational r(0, 1);
    datum = r;
    
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 1);
}

// Test toRational after setting value via URational assignment
TEST_F(ExifdatumTest_762, ToRationalFromURational_762) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    URational ur(72, 1);
    datum = ur;
    
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 72);
    EXPECT_EQ(result.second, 1);
}

// Test toRational after setting value via integer assignment
TEST_F(ExifdatumTest_762, ToRationalFromUint16_762) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key, nullptr);
    
    uint16_t val = 6;
    datum = val;
    
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, 6);
    EXPECT_EQ(result.second, 1);
}

// Test that key() returns correct key string
TEST_F(ExifdatumTest_762, KeyReturnsCorrectString_762) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Exif.Image.XResolution");
}

// Test familyName returns "Exif"
TEST_F(ExifdatumTest_762, FamilyNameReturnsExif_762) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    EXPECT_STREQ(datum.familyName(), "Exif");
}

// Test count() is 0 when no value is set
TEST_F(ExifdatumTest_762, CountIsZeroWhenNoValue_762) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.count(), 0u);
}

// Test count() after setting a value
TEST_F(ExifdatumTest_762, CountAfterSettingValue_762) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    Rational r(72, 1);
    datum = r;
    
    EXPECT_EQ(datum.count(), 1u);
}

// Test setValue with string
TEST_F(ExifdatumTest_762, SetValueWithString_762) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    // First set a value type so setValue(string) can parse
    Rational r(72, 1);
    datum = r;
    
    int result = datum.setValue("300/1");
    EXPECT_EQ(result, 0);
    
    Rational rat = datum.toRational(0);
    EXPECT_EQ(rat.first, 300);
    EXPECT_EQ(rat.second, 1);
}

// Test tag() returns correct tag number
TEST_F(ExifdatumTest_762, TagReturnsCorrectValue_762) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    // XResolution tag is 0x011a = 282
    EXPECT_EQ(datum.tag(), 0x011a);
}

// Test toString when no value set
TEST_F(ExifdatumTest_762, ToStringWhenNoValue_762) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    std::string result = datum.toString();
    EXPECT_TRUE(result.empty());
}

// Test toString when value is set
TEST_F(ExifdatumTest_762, ToStringWhenValueIsSet_762) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    Rational r(72, 1);
    datum = r;
    
    std::string result = datum.toString();
    EXPECT_FALSE(result.empty());
}

// Test getValue returns nullptr when no value set
TEST_F(ExifdatumTest_762, GetValueReturnsNullWhenNoValueSet_762) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    auto val = datum.getValue();
    EXPECT_EQ(val, nullptr);
}

// Test getValue returns valid pointer when value is set
TEST_F(ExifdatumTest_762, GetValueReturnsValidPtrWhenValueSet_762) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    Rational r(72, 1);
    datum = r;
    
    auto val = datum.getValue();
    EXPECT_NE(val, nullptr);
}

// Test large index for toRational with no value
TEST_F(ExifdatumTest_762, ToRationalLargeIndexNoValue_762) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key, nullptr);
    
    Rational result = datum.toRational(999999);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 1);
}
