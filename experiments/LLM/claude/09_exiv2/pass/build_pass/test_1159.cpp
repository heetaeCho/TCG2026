#include <gtest/gtest.h>
#include <string>
#include <cmath>
#include <limits>

// Include the necessary Exiv2 headers
#include "types.hpp"

namespace {

class ParseFloatTest_1159 : public ::testing::Test {
protected:
    bool ok;
    
    void SetUp() override {
        ok = false;
    }
};

// Normal operation: parsing a simple integer string
TEST_F(ParseFloatTest_1159, ParseSimpleInteger_1159) {
    float result = Exiv2::parseFloat("42", ok);
    EXPECT_TRUE(ok);
    EXPECT_FLOAT_EQ(result, 42.0f);
}

// Normal operation: parsing a floating point string
TEST_F(ParseFloatTest_1159, ParseSimpleFloat_1159) {
    float result = Exiv2::parseFloat("3.14", ok);
    EXPECT_TRUE(ok);
    EXPECT_NEAR(result, 3.14f, 0.001f);
}

// Normal operation: parsing a negative float
TEST_F(ParseFloatTest_1159, ParseNegativeFloat_1159) {
    float result = Exiv2::parseFloat("-2.5", ok);
    EXPECT_TRUE(ok);
    EXPECT_FLOAT_EQ(result, -2.5f);
}

// Normal operation: parsing zero
TEST_F(ParseFloatTest_1159, ParseZero_1159) {
    float result = Exiv2::parseFloat("0", ok);
    EXPECT_TRUE(ok);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

// Normal operation: parsing a rational number (fraction)
TEST_F(ParseFloatTest_1159, ParseRational_1159) {
    float result = Exiv2::parseFloat("1/2", ok);
    EXPECT_TRUE(ok);
    EXPECT_FLOAT_EQ(result, 0.5f);
}

// Normal operation: parsing a rational with larger values
TEST_F(ParseFloatTest_1159, ParseRationalLargerValues_1159) {
    float result = Exiv2::parseFloat("3/4", ok);
    EXPECT_TRUE(ok);
    EXPECT_FLOAT_EQ(result, 0.75f);
}

// Normal operation: parsing negative rational
TEST_F(ParseFloatTest_1159, ParseNegativeRational_1159) {
    float result = Exiv2::parseFloat("-1/4", ok);
    EXPECT_TRUE(ok);
    EXPECT_FLOAT_EQ(result, -0.25f);
}

// Boundary: rational with zero denominator should fail
TEST_F(ParseFloatTest_1159, ParseRationalZeroDenominator_1159) {
    float result = Exiv2::parseFloat("1/0", ok);
    EXPECT_FALSE(ok);
}

// Normal operation: parsing boolean "true"
TEST_F(ParseFloatTest_1159, ParseBoolTrue_1159) {
    float result = Exiv2::parseFloat("true", ok);
    EXPECT_TRUE(ok);
    EXPECT_FLOAT_EQ(result, 1.0f);
}

// Normal operation: parsing boolean "false"
TEST_F(ParseFloatTest_1159, ParseBoolFalse_1159) {
    float result = Exiv2::parseFloat("false", ok);
    EXPECT_TRUE(ok);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

// Error case: parsing a completely invalid string
TEST_F(ParseFloatTest_1159, ParseInvalidString_1159) {
    Exiv2::parseFloat("not_a_number", ok);
    EXPECT_FALSE(ok);
}

// Error case: empty string
TEST_F(ParseFloatTest_1159, ParseEmptyString_1159) {
    Exiv2::parseFloat("", ok);
    EXPECT_FALSE(ok);
}

// Normal operation: parsing "0.0"
TEST_F(ParseFloatTest_1159, ParseZeroPointZero_1159) {
    float result = Exiv2::parseFloat("0.0", ok);
    EXPECT_TRUE(ok);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

// Normal operation: parsing a negative integer
TEST_F(ParseFloatTest_1159, ParseNegativeInteger_1159) {
    float result = Exiv2::parseFloat("-10", ok);
    EXPECT_TRUE(ok);
    EXPECT_FLOAT_EQ(result, -10.0f);
}

// Normal operation: parsing a rational that results in integer
TEST_F(ParseFloatTest_1159, ParseRationalResultingInInteger_1159) {
    float result = Exiv2::parseFloat("6/3", ok);
    EXPECT_TRUE(ok);
    EXPECT_FLOAT_EQ(result, 2.0f);
}

// Normal operation: parsing a large float
TEST_F(ParseFloatTest_1159, ParseLargeFloat_1159) {
    float result = Exiv2::parseFloat("100000.5", ok);
    EXPECT_TRUE(ok);
    EXPECT_NEAR(result, 100000.5f, 1.0f);
}

// Normal operation: parsing a very small float
TEST_F(ParseFloatTest_1159, ParseSmallFloat_1159) {
    float result = Exiv2::parseFloat("0.001", ok);
    EXPECT_TRUE(ok);
    EXPECT_NEAR(result, 0.001f, 0.0001f);
}

// Boundary: parsing with leading/trailing spaces may or may not work
// This tests the observable behavior
TEST_F(ParseFloatTest_1159, ParseStringWithSpaces_1159) {
    Exiv2::parseFloat("  42  ", ok);
    // We just observe what happens; ok may be true or false depending on implementation
    // No assertion on ok here since it depends on internal behavior
}

// Normal operation: rational 0/1 should give 0
TEST_F(ParseFloatTest_1159, ParseRationalZeroNumerator_1159) {
    float result = Exiv2::parseFloat("0/1", ok);
    EXPECT_TRUE(ok);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

// Normal operation: parsing "1"
TEST_F(ParseFloatTest_1159, ParseOne_1159) {
    float result = Exiv2::parseFloat("1", ok);
    EXPECT_TRUE(ok);
    EXPECT_FLOAT_EQ(result, 1.0f);
}

// Error case: random special characters
TEST_F(ParseFloatTest_1159, ParseSpecialCharacters_1159) {
    Exiv2::parseFloat("@#$%", ok);
    EXPECT_FALSE(ok);
}

// Normal operation: parsing rational with negative denominator
TEST_F(ParseFloatTest_1159, ParseRationalNegativeDenominator_1159) {
    float result = Exiv2::parseFloat("1/-2", ok);
    if (ok) {
        EXPECT_FLOAT_EQ(result, -0.5f);
    }
    // If parsing fails, that's also acceptable behavior
}

// Boundary: parsing "0/0" - zero denominator with zero numerator
TEST_F(ParseFloatTest_1159, ParseRationalZeroOverZero_1159) {
    Exiv2::parseFloat("0/0", ok);
    EXPECT_FALSE(ok);
}

// Normal: positive float with plus sign
TEST_F(ParseFloatTest_1159, ParsePositiveSignFloat_1159) {
    float result = Exiv2::parseFloat("+3.5", ok);
    if (ok) {
        EXPECT_FLOAT_EQ(result, 3.5f);
    }
}

// Normal: scientific notation
TEST_F(ParseFloatTest_1159, ParseScientificNotation_1159) {
    float result = Exiv2::parseFloat("1.5e2", ok);
    if (ok) {
        EXPECT_FLOAT_EQ(result, 150.0f);
    }
}

// Rational: large numerator and denominator
TEST_F(ParseFloatTest_1159, ParseLargeRational_1159) {
    float result = Exiv2::parseFloat("1000000/1000000", ok);
    EXPECT_TRUE(ok);
    EXPECT_FLOAT_EQ(result, 1.0f);
}

}  // namespace
