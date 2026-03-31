#include <gtest/gtest.h>
#include <cstring>
#include <cmath>
#include <climits>
#include <cfloat>
#include <cerrno>

// We need to access the static function. Since it's defined as static in a .cc file,
// we'll need to either include the .cc file or redeclare it. For testing purposes,
// we include the source file to get access to the static function.
// However, since the function is in namespace re2 and is static, we need to include
// the implementation file directly.

// Forward declare - but since it's static we need to include the cc file
// We'll include the .cc file to access the static function
namespace re2 {
static bool parse_double_float(const char* str, size_t n, bool isfloat, void* dest);
}

// Include the implementation to get access to the static function
#include "./TestProjects/re2/util/pcre.cc"

namespace {

class ParseDoubleFloatTest_203 : public ::testing::Test {
protected:
    // Helper to call the function under test
    bool ParseDoubleFloat(const char* str, size_t n, bool isfloat, void* dest) {
        return re2::parse_double_float(str, n, isfloat, dest);
    }
};

// ==================== Normal Operation Tests ====================

TEST_F(ParseDoubleFloatTest_203, ParseSimpleDouble_203) {
    double result = 0.0;
    EXPECT_TRUE(ParseDoubleFloat("3.14", 4, false, &result));
    EXPECT_DOUBLE_EQ(3.14, result);
}

TEST_F(ParseDoubleFloatTest_203, ParseSimpleFloat_203) {
    float result = 0.0f;
    EXPECT_TRUE(ParseDoubleFloat("3.14", 4, true, &result));
    EXPECT_FLOAT_EQ(3.14f, result);
}

TEST_F(ParseDoubleFloatTest_203, ParseIntegerAsDouble_203) {
    double result = 0.0;
    EXPECT_TRUE(ParseDoubleFloat("42", 2, false, &result));
    EXPECT_DOUBLE_EQ(42.0, result);
}

TEST_F(ParseDoubleFloatTest_203, ParseIntegerAsFloat_203) {
    float result = 0.0f;
    EXPECT_TRUE(ParseDoubleFloat("42", 2, true, &result));
    EXPECT_FLOAT_EQ(42.0f, result);
}

TEST_F(ParseDoubleFloatTest_203, ParseNegativeDouble_203) {
    double result = 0.0;
    EXPECT_TRUE(ParseDoubleFloat("-2.5", 4, false, &result));
    EXPECT_DOUBLE_EQ(-2.5, result);
}

TEST_F(ParseDoubleFloatTest_203, ParseNegativeFloat_203) {
    float result = 0.0f;
    EXPECT_TRUE(ParseDoubleFloat("-2.5", 4, true, &result));
    EXPECT_FLOAT_EQ(-2.5f, result);
}

TEST_F(ParseDoubleFloatTest_203, ParseZeroDouble_203) {
    double result = 1.0;
    EXPECT_TRUE(ParseDoubleFloat("0", 1, false, &result));
    EXPECT_DOUBLE_EQ(0.0, result);
}

TEST_F(ParseDoubleFloatTest_203, ParseZeroFloat_203) {
    float result = 1.0f;
    EXPECT_TRUE(ParseDoubleFloat("0", 1, true, &result));
    EXPECT_FLOAT_EQ(0.0f, result);
}

TEST_F(ParseDoubleFloatTest_203, ParseScientificNotationDouble_203) {
    double result = 0.0;
    EXPECT_TRUE(ParseDoubleFloat("1.5e10", 6, false, &result));
    EXPECT_DOUBLE_EQ(1.5e10, result);
}

TEST_F(ParseDoubleFloatTest_203, ParseScientificNotationFloat_203) {
    float result = 0.0f;
    EXPECT_TRUE(ParseDoubleFloat("1.5e10", 6, true, &result));
    EXPECT_FLOAT_EQ(1.5e10f, result);
}

TEST_F(ParseDoubleFloatTest_203, ParseNegativeExponentDouble_203) {
    double result = 0.0;
    EXPECT_TRUE(ParseDoubleFloat("1.5e-3", 6, false, &result));
    EXPECT_DOUBLE_EQ(1.5e-3, result);
}

TEST_F(ParseDoubleFloatTest_203, ParseZeroPointZeroDouble_203) {
    double result = 1.0;
    EXPECT_TRUE(ParseDoubleFloat("0.0", 3, false, &result));
    EXPECT_DOUBLE_EQ(0.0, result);
}

TEST_F(ParseDoubleFloatTest_203, ParseLeadingDotDouble_203) {
    double result = 0.0;
    EXPECT_TRUE(ParseDoubleFloat(".5", 2, false, &result));
    EXPECT_DOUBLE_EQ(0.5, result);
}

TEST_F(ParseDoubleFloatTest_203, ParseTrailingDotDouble_203) {
    double result = 0.0;
    EXPECT_TRUE(ParseDoubleFloat("5.", 2, false, &result));
    EXPECT_DOUBLE_EQ(5.0, result);
}

TEST_F(ParseDoubleFloatTest_203, ParsePositiveSignDouble_203) {
    double result = 0.0;
    EXPECT_TRUE(ParseDoubleFloat("+3.14", 5, false, &result));
    EXPECT_DOUBLE_EQ(3.14, result);
}

// ==================== Null Destination Tests ====================

TEST_F(ParseDoubleFloatTest_203, NullDestValidDoubleReturnsTrueDouble_203) {
    EXPECT_TRUE(ParseDoubleFloat("3.14", 4, false, nullptr));
}

TEST_F(ParseDoubleFloatTest_203, NullDestValidFloatReturnsTrueFloat_203) {
    EXPECT_TRUE(ParseDoubleFloat("3.14", 4, true, nullptr));
}

TEST_F(ParseDoubleFloatTest_203, NullDestInvalidStringReturnsFalse_203) {
    EXPECT_FALSE(ParseDoubleFloat("abc", 3, false, nullptr));
}

// ==================== Boundary Condition Tests ====================

TEST_F(ParseDoubleFloatTest_203, EmptyStringReturnsFalse_203) {
    double result = 0.0;
    EXPECT_FALSE(ParseDoubleFloat("", 0, false, &result));
}

TEST_F(ParseDoubleFloatTest_203, EmptyStringFloatReturnsFalse_203) {
    float result = 0.0f;
    EXPECT_FALSE(ParseDoubleFloat("", 0, true, &result));
}

TEST_F(ParseDoubleFloatTest_203, SingleDigitDouble_203) {
    double result = 0.0;
    EXPECT_TRUE(ParseDoubleFloat("7", 1, false, &result));
    EXPECT_DOUBLE_EQ(7.0, result);
}

TEST_F(ParseDoubleFloatTest_203, SingleDigitFloat_203) {
    float result = 0.0f;
    EXPECT_TRUE(ParseDoubleFloat("7", 1, true, &result));
    EXPECT_FLOAT_EQ(7.0f, result);
}

TEST_F(ParseDoubleFloatTest_203, StringAtMaxLength199ReturnsFalse_203) {
    // kMaxLength is 200, so n >= 200 should fail
    std::string longStr(200, '1');
    double result = 0.0;
    EXPECT_FALSE(ParseDoubleFloat(longStr.c_str(), 200, false, &result));
}

TEST_F(ParseDoubleFloatTest_203, StringAtLength199Succeeds_203) {
    // kMaxLength is 200, so n = 199 should be the max that works
    // Create a string of length 199 that's a valid number: "0." followed by 197 zeros
    std::string longStr = "0.";
    longStr.append(197, '0');
    ASSERT_EQ(199u, longStr.size());
    double result = 1.0;
    EXPECT_TRUE(ParseDoubleFloat(longStr.c_str(), 199, false, &result));
    EXPECT_DOUBLE_EQ(0.0, result);
}

TEST_F(ParseDoubleFloatTest_203, VeryLongStringReturnsFalse_203) {
    std::string longStr(500, '1');
    double result = 0.0;
    EXPECT_FALSE(ParseDoubleFloat(longStr.c_str(), 500, false, &result));
}

// ==================== Error / Invalid Input Tests ====================

TEST_F(ParseDoubleFloatTest_203, NonNumericStringReturnsFalse_203) {
    double result = 0.0;
    EXPECT_FALSE(ParseDoubleFloat("abc", 3, false, &result));
}

TEST_F(ParseDoubleFloatTest_203, NonNumericStringFloatReturnsFalse_203) {
    float result = 0.0f;
    EXPECT_FALSE(ParseDoubleFloat("abc", 3, true, &result));
}

TEST_F(ParseDoubleFloatTest_203, TrailingJunkReturnsFalse_203) {
    double result = 0.0;
    EXPECT_FALSE(ParseDoubleFloat("3.14abc", 7, false, &result));
}

TEST_F(ParseDoubleFloatTest_203, LeadingJunkReturnsFalse_203) {
    double result = 0.0;
    EXPECT_FALSE(ParseDoubleFloat("abc3.14", 7, false, &result));
}

TEST_F(ParseDoubleFloatTest_203, SpacesOnlyReturnsFalse_203) {
    double result = 0.0;
    // strtod may skip leading whitespace, but there will be leftover or none consumed
    // Actually strtod skips leading whitespace, so "   " would parse as nothing useful
    // and end would not equal buf + n. Let's verify:
    EXPECT_FALSE(ParseDoubleFloat("   ", 3, false, &result));
}

TEST_F(ParseDoubleFloatTest_203, NumberWithTrailingSpaceReturnsFalse_203) {
    double result = 0.0;
    EXPECT_FALSE(ParseDoubleFloat("3.14 ", 5, false, &result));
}

TEST_F(ParseDoubleFloatTest_203, NumberWithLeadingSpaceDouble_203) {
    double result = 0.0;
    // strtod skips leading whitespace, so " 3.14" (length 5) should parse
    // end should point to buf + 5, which is correct
    EXPECT_TRUE(ParseDoubleFloat(" 3.14", 5, false, &result));
    EXPECT_DOUBLE_EQ(3.14, result);
}

TEST_F(ParseDoubleFloatTest_203, OnlyMinusSignReturnsFalse_203) {
    double result = 0.0;
    EXPECT_FALSE(ParseDoubleFloat("-", 1, false, &result));
}

TEST_F(ParseDoubleFloatTest_203, OnlyPlusSignReturnsFalse_203) {
    double result = 0.0;
    EXPECT_FALSE(ParseDoubleFloat("+", 1, false, &result));
}

TEST_F(ParseDoubleFloatTest_203, OnlyDotReturnsFalse_203) {
    double result = 0.0;
    // "." alone - strtod may or may not parse it
    // Most implementations: strtod(".") -> end points to ".", so end != buf + n? 
    // Actually strtod(".") returns 0 and end points to "." (no digits consumed)
    // so end != buf + 1 -> returns false
    EXPECT_FALSE(ParseDoubleFloat(".", 1, false, &result));
}

// ==================== Partial String Tests ====================

TEST_F(ParseDoubleFloatTest_203, ParsePartialStringDouble_203) {
    // Pass only first 4 chars of "3.14159"
    double result = 0.0;
    EXPECT_TRUE(ParseDoubleFloat("3.14159", 4, false, &result));
    EXPECT_DOUBLE_EQ(3.14, result);
}

TEST_F(ParseDoubleFloatTest_203, ParsePartialStringFloat_203) {
    float result = 0.0f;
    EXPECT_TRUE(ParseDoubleFloat("3.14159", 4, true, &result));
    EXPECT_FLOAT_EQ(3.14f, result);
}

// ==================== Special Values Tests ====================

TEST_F(ParseDoubleFloatTest_203, ParseInfDouble_203) {
    double result = 0.0;
    // "inf" is typically recognized by strtod
    bool success = ParseDoubleFloat("inf", 3, false, &result);
    if (success) {
        EXPECT_TRUE(std::isinf(result));
    }
    // If not supported, the function returns false, which is also acceptable
}

TEST_F(ParseDoubleFloatTest_203, ParseNanDouble_203) {
    double result = 0.0;
    bool success = ParseDoubleFloat("nan", 3, false, &result);
    if (success) {
        EXPECT_TRUE(std::isnan(result));
    }
}

// ==================== Overflow Tests ====================

TEST_F(ParseDoubleFloatTest_203, OverflowDoubleReturnsFalse_203) {
    double result = 0.0;
    // A very large number that overflows double
    EXPECT_FALSE(ParseDoubleFloat("1e309", 5, false, &result));
}

TEST_F(ParseDoubleFloatTest_203, OverflowFloatReturnsFalse_203) {
    float result = 0.0f;
    // A number that overflows float but not double
    EXPECT_FALSE(ParseDoubleFloat("1e39", 4, true, &result));
}

// ==================== Float vs Double Precision Tests ====================

TEST_F(ParseDoubleFloatTest_203, DoubleStoresFullPrecision_203) {
    double result = 0.0;
    EXPECT_TRUE(ParseDoubleFloat("1.23456789012345", 16, false, &result));
    EXPECT_DOUBLE_EQ(1.23456789012345, result);
}

TEST_F(ParseDoubleFloatTest_203, FloatStoresReducedPrecision_203) {
    float result = 0.0f;
    EXPECT_TRUE(ParseDoubleFloat("1.234567", 8, true, &result));
    EXPECT_FLOAT_EQ(1.234567f, result);
}

// ==================== Edge Case: Embedded Null-like Scenarios ====================

TEST_F(ParseDoubleFloatTest_203, NLengthSmallerThanActualString_203) {
    double result = 0.0;
    // Only first character '3' is considered
    EXPECT_TRUE(ParseDoubleFloat("3abc", 1, false, &result));
    EXPECT_DOUBLE_EQ(3.0, result);
}

TEST_F(ParseDoubleFloatTest_203, ParseNegativeZeroDouble_203) {
    double result = 1.0;
    EXPECT_TRUE(ParseDoubleFloat("-0", 2, false, &result));
    EXPECT_DOUBLE_EQ(0.0, result);
}

TEST_F(ParseDoubleFloatTest_203, ParseNegativeZeroFloat_203) {
    float result = 1.0f;
    EXPECT_TRUE(ParseDoubleFloat("-0.0", 4, true, &result));
    EXPECT_FLOAT_EQ(0.0f, result);
}

TEST_F(ParseDoubleFloatTest_203, ParseVerySmallDouble_203) {
    double result = 0.0;
    EXPECT_TRUE(ParseDoubleFloat("1e-300", 6, false, &result));
    EXPECT_DOUBLE_EQ(1e-300, result);
}

TEST_F(ParseDoubleFloatTest_203, ParseHexDouble_203) {
    double result = 0.0;
    // "0x1" - strtod supports hex in C99+
    bool success = ParseDoubleFloat("0x1", 3, false, &result);
    if (success) {
        EXPECT_DOUBLE_EQ(1.0, result);
    }
}

}  // namespace
