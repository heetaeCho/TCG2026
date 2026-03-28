#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <cmath>
#include <limits>

// Forward declare the function under test
namespace Exiv2 {
namespace Internal {
float string_to_float(std::string_view str);
}

// We need access to the Error class for catching exceptions
// Include the error header
}

#include "exiv2/error.hpp"

namespace {

using Exiv2::Internal::string_to_float;

// Normal operation tests

TEST(StringToFloatTest_948, ParsesPositiveInteger_948) {
    float result = string_to_float("42");
    EXPECT_FLOAT_EQ(result, 42.0f);
}

TEST(StringToFloatTest_948, ParsesNegativeInteger_948) {
    float result = string_to_float("-42");
    EXPECT_FLOAT_EQ(result, -42.0f);
}

TEST(StringToFloatTest_948, ParsesPositiveFloat_948) {
    float result = string_to_float("3.14");
    EXPECT_NEAR(result, 3.14f, 0.001f);
}

TEST(StringToFloatTest_948, ParsesNegativeFloat_948) {
    float result = string_to_float("-3.14");
    EXPECT_NEAR(result, -3.14f, 0.001f);
}

TEST(StringToFloatTest_948, ParsesZero_948) {
    float result = string_to_float("0");
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST(StringToFloatTest_948, ParsesZeroPointZero_948) {
    float result = string_to_float("0.0");
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST(StringToFloatTest_948, ParsesSmallPositiveFloat_948) {
    float result = string_to_float("0.001");
    EXPECT_NEAR(result, 0.001f, 0.0001f);
}

TEST(StringToFloatTest_948, ParsesLargePositiveFloat_948) {
    float result = string_to_float("1000000.0");
    EXPECT_FLOAT_EQ(result, 1000000.0f);
}

TEST(StringToFloatTest_948, ParsesScientificNotation_948) {
    float result = string_to_float("1.5e2");
    EXPECT_FLOAT_EQ(result, 150.0f);
}

TEST(StringToFloatTest_948, ParsesNegativeScientificNotation_948) {
    float result = string_to_float("-1.5e2");
    EXPECT_FLOAT_EQ(result, -150.0f);
}

TEST(StringToFloatTest_948, ParsesScientificNotationSmallExponent_948) {
    float result = string_to_float("1.5e-2");
    EXPECT_NEAR(result, 0.015f, 0.001f);
}

TEST(StringToFloatTest_948, ParsesLeadingWhitespace_948) {
    float result = string_to_float("  42.5");
    EXPECT_FLOAT_EQ(result, 42.5f);
}

TEST(StringToFloatTest_948, ParsesOne_948) {
    float result = string_to_float("1");
    EXPECT_FLOAT_EQ(result, 1.0f);
}

TEST(StringToFloatTest_948, ParsesNegativeOne_948) {
    float result = string_to_float("-1");
    EXPECT_FLOAT_EQ(result, -1.0f);
}

TEST(StringToFloatTest_948, ParsesFloatWithNoLeadingDigit_948) {
    float result = string_to_float(".5");
    EXPECT_FLOAT_EQ(result, 0.5f);
}

TEST(StringToFloatTest_948, ParsesPositiveSign_948) {
    float result = string_to_float("+3.14");
    EXPECT_NEAR(result, 3.14f, 0.001f);
}

// Boundary condition tests

TEST(StringToFloatTest_948, ParsesVerySmallFloat_948) {
    float result = string_to_float("1.17549e-38");
    EXPECT_GT(result, 0.0f);
}

TEST(StringToFloatTest_948, ParsesVeryLargeFloat_948) {
    float result = string_to_float("3.40282e+38");
    EXPECT_GT(result, 0.0f);
}

// Error / exceptional cases

TEST(StringToFloatTest_948, ThrowsOnEmptyString_948) {
    EXPECT_THROW(string_to_float(""), Exiv2::Error);
}

TEST(StringToFloatTest_948, ThrowsOnNonNumericString_948) {
    EXPECT_THROW(string_to_float("abc"), Exiv2::Error);
}

TEST(StringToFloatTest_948, ThrowsOnPureWhitespace_948) {
    EXPECT_THROW(string_to_float("   "), Exiv2::Error);
}

TEST(StringToFloatTest_948, ThrowsOnSpecialCharacters_948) {
    EXPECT_THROW(string_to_float("@#$"), Exiv2::Error);
}

TEST(StringToFloatTest_948, ThrowsOnLettersOnly_948) {
    EXPECT_THROW(string_to_float("hello"), Exiv2::Error);
}

// C locale tests - ensure period is used as decimal separator regardless of locale

TEST(StringToFloatTest_948, UsesCLocaleDecimalPoint_948) {
    // In C locale, period is the decimal separator
    float result = string_to_float("1.5");
    EXPECT_FLOAT_EQ(result, 1.5f);
}

TEST(StringToFloatTest_948, CommaNotTreatedAsDecimalSeparator_948) {
    // With C locale, comma should not be a valid decimal separator
    // "1,5" should parse as 1.0 (stopping at comma) - not throw,
    // or it might throw depending on implementation. 
    // Since we don't know the exact behavior, we just check it doesn't return 1.5
    try {
        float result = string_to_float("1,5");
        // If it doesn't throw, it should not be 1.5
        EXPECT_NE(result, 1.5f);
    } catch (const Exiv2::Error&) {
        // It's also acceptable to throw
        SUCCEED();
    }
}

TEST(StringToFloatTest_948, ParsesNegativeZero_948) {
    float result = string_to_float("-0.0");
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST(StringToFloatTest_948, ParsesTrailingZeros_948) {
    float result = string_to_float("1.500000");
    EXPECT_FLOAT_EQ(result, 1.5f);
}

TEST(StringToFloatTest_948, ParsesIntegerAsFloat_948) {
    float result = string_to_float("100");
    EXPECT_FLOAT_EQ(result, 100.0f);
}

TEST(StringToFloatTest_948, ParsesUppercaseScientificNotation_948) {
    float result = string_to_float("1.5E2");
    EXPECT_FLOAT_EQ(result, 150.0f);
}

}  // namespace
