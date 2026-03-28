#include <gtest/gtest.h>
#include <cmath>
#include <climits>
#include <string>

// Include the necessary RE2 headers
#include "re2/re2.h"

// The Parse function is in re2::re2_internal namespace, but it's typically
// accessed through RE2's public interface (e.g., RE2::FullMatch, RE2::PartialMatch).
// We test through the public API.

class RE2ParseFloat_273 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Normal float parsing via RE2::FullMatch
TEST_F(RE2ParseFloat_273, ParseSimpleFloat_273) {
    float val = 0.0f;
    EXPECT_TRUE(RE2::FullMatch("3.14", "([-+]?[0-9]*\\.?[0-9]+)", &val));
    EXPECT_FLOAT_EQ(3.14f, val);
}

// Test: Parse integer as float
TEST_F(RE2ParseFloat_273, ParseIntegerAsFloat_273) {
    float val = 0.0f;
    EXPECT_TRUE(RE2::FullMatch("42", "([0-9]+)", &val));
    EXPECT_FLOAT_EQ(42.0f, val);
}

// Test: Parse negative float
TEST_F(RE2ParseFloat_273, ParseNegativeFloat_273) {
    float val = 0.0f;
    EXPECT_TRUE(RE2::FullMatch("-2.5", "([-+]?[0-9]*\\.?[0-9]+)", &val));
    EXPECT_FLOAT_EQ(-2.5f, val);
}

// Test: Parse positive float with explicit plus sign
TEST_F(RE2ParseFloat_273, ParsePositiveSignFloat_273) {
    float val = 0.0f;
    EXPECT_TRUE(RE2::FullMatch("+1.5", "([-+]?[0-9]*\\.?[0-9]+)", &val));
    EXPECT_FLOAT_EQ(1.5f, val);
}

// Test: Parse zero
TEST_F(RE2ParseFloat_273, ParseZero_273) {
    float val = -1.0f;
    EXPECT_TRUE(RE2::FullMatch("0", "([0-9]+)", &val));
    EXPECT_FLOAT_EQ(0.0f, val);
}

// Test: Parse float with leading zero
TEST_F(RE2ParseFloat_273, ParseLeadingZeroFloat_273) {
    float val = 0.0f;
    EXPECT_TRUE(RE2::FullMatch("0.001", "([0-9]*\\.?[0-9]+)", &val));
    EXPECT_FLOAT_EQ(0.001f, val);
}

// Test: Parse scientific notation
TEST_F(RE2ParseFloat_273, ParseScientificNotation_273) {
    float val = 0.0f;
    EXPECT_TRUE(RE2::FullMatch("1.5e2", "([-+]?[0-9]*\\.?[0-9]+[eE][-+]?[0-9]+)", &val));
    EXPECT_FLOAT_EQ(150.0f, val);
}

// Test: Parse scientific notation with negative exponent
TEST_F(RE2ParseFloat_273, ParseScientificNotationNegativeExp_273) {
    float val = 0.0f;
    EXPECT_TRUE(RE2::FullMatch("2.5e-1", "([-+]?[0-9]*\\.?[0-9]+[eE][-+]?[0-9]+)", &val));
    EXPECT_FLOAT_EQ(0.25f, val);
}

// Test: Empty string should fail to parse as float
TEST_F(RE2ParseFloat_273, ParseEmptyStringFails_273) {
    float val = 0.0f;
    EXPECT_FALSE(RE2::FullMatch("", "(.*)", &val));
}

// Test: Non-numeric string should fail
TEST_F(RE2ParseFloat_273, ParseNonNumericFails_273) {
    float val = 0.0f;
    EXPECT_FALSE(RE2::FullMatch("abc", "([a-z]+)", &val));
}

// Test: Parse very large float (potential overflow)
TEST_F(RE2ParseFloat_273, ParseVeryLargeFloatFails_273) {
    float val = 0.0f;
    // A number larger than FLT_MAX should fail due to errno being set
    EXPECT_FALSE(RE2::FullMatch("1e39", "([-+]?[0-9]*\\.?[0-9]+[eE][-+]?[0-9]+)", &val));
}

// Test: Parse without destination (NULL dest)
TEST_F(RE2ParseFloat_273, ParseWithNullDest_273) {
    // When no destination pointer is given, Parse should still return true for valid input
    EXPECT_TRUE(RE2::FullMatch("3.14", "([-+]?[0-9]*\\.?[0-9]+)"));
}

// Test: Parse float with trailing non-numeric characters should fail for FullMatch
TEST_F(RE2ParseFloat_273, ParseWithTrailingJunk_273) {
    float val = 0.0f;
    // FullMatch requires matching entire string
    EXPECT_FALSE(RE2::FullMatch("3.14abc", "([0-9]*\\.?[0-9]+)", &val));
}

// Test: Parse small positive float near zero
TEST_F(RE2ParseFloat_273, ParseSmallPositiveFloat_273) {
    float val = 0.0f;
    EXPECT_TRUE(RE2::FullMatch("0.000001", "([0-9]*\\.?[0-9]+)", &val));
    EXPECT_FLOAT_EQ(0.000001f, val);
}

// Test: Parse using PartialMatch extracts float from larger string
TEST_F(RE2ParseFloat_273, PartialMatchFloat_273) {
    float val = 0.0f;
    EXPECT_TRUE(RE2::PartialMatch("value is 9.81 m/s^2", "([0-9]+\\.[0-9]+)", &val));
    EXPECT_FLOAT_EQ(9.81f, val);
}

// Test: Parse float with only decimal part
TEST_F(RE2ParseFloat_273, ParseDecimalOnlyFloat_273) {
    float val = 0.0f;
    EXPECT_TRUE(RE2::FullMatch(".5", "(\\.?[0-9]+)", &val));
    EXPECT_FLOAT_EQ(0.5f, val);
}

// Test: Parse very small scientific notation float
TEST_F(RE2ParseFloat_273, ParseVerySmallScientificNotation_273) {
    float val = 0.0f;
    EXPECT_TRUE(RE2::FullMatch("1e-10", "([-+]?[0-9]*\\.?[0-9]+[eE][-+]?[0-9]+)", &val));
    EXPECT_NEAR(1e-10f, val, 1e-15f);
}

// Test: Multiple floats extracted
TEST_F(RE2ParseFloat_273, ParseMultipleFloats_273) {
    float val1 = 0.0f, val2 = 0.0f;
    EXPECT_TRUE(RE2::FullMatch("1.5,2.5", "([0-9.]+),([0-9.]+)", &val1, &val2));
    EXPECT_FLOAT_EQ(1.5f, val1);
    EXPECT_FLOAT_EQ(2.5f, val2);
}

// Test: Parse string with only whitespace should fail
TEST_F(RE2ParseFloat_273, ParseWhitespaceOnlyFails_273) {
    float val = 0.0f;
    EXPECT_FALSE(RE2::FullMatch("   ", "\\s+", &val));
}

// Test: Parse negative zero
TEST_F(RE2ParseFloat_273, ParseNegativeZero_273) {
    float val = 1.0f;
    EXPECT_TRUE(RE2::FullMatch("-0", "([-+]?[0-9]+)", &val));
    EXPECT_FLOAT_EQ(0.0f, val);
}

// Test: Parse large but valid float
TEST_F(RE2ParseFloat_273, ParseLargeValidFloat_273) {
    float val = 0.0f;
    EXPECT_TRUE(RE2::FullMatch("1e30", "([-+]?[0-9]*\\.?[0-9]+[eE][-+]?[0-9]+)", &val));
    EXPECT_FLOAT_EQ(1e30f, val);
}

// Test: Parse very very large float overflowing float range
TEST_F(RE2ParseFloat_273, ParseOverflowFloat_273) {
    float val = 0.0f;
    // 1e300 overflows float
    EXPECT_FALSE(RE2::FullMatch("1e300", "([-+]?[0-9]*\\.?[0-9]+[eE][-+]?[0-9]+)", &val));
}
