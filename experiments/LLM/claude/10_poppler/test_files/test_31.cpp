#include <gtest/gtest.h>
#include <cmath>
#include <cstring>
#include <cerrno>
#include <climits>

// Declaration of the function under test
extern double gstrtod(const char *nptr, char **endptr);

class GstrtodTest_31 : public ::testing::Test {
protected:
    void SetUp() override {
        errno = 0;
    }
};

// Normal operation: parse a simple integer
TEST_F(GstrtodTest_31, ParseSimpleInteger_31) {
    char *endptr = nullptr;
    double val = gstrtod("123", &endptr);
    EXPECT_DOUBLE_EQ(val, 123.0);
    EXPECT_NE(endptr, nullptr);
    EXPECT_EQ(*endptr, '\0');
}

// Normal operation: parse a simple floating point number
TEST_F(GstrtodTest_31, ParseSimpleFloat_31) {
    char *endptr = nullptr;
    double val = gstrtod("3.14", &endptr);
    EXPECT_DOUBLE_EQ(val, 3.14);
    EXPECT_NE(endptr, nullptr);
    EXPECT_EQ(*endptr, '\0');
}

// Normal operation: parse negative number
TEST_F(GstrtodTest_31, ParseNegativeNumber_31) {
    char *endptr = nullptr;
    double val = gstrtod("-2.5", &endptr);
    EXPECT_DOUBLE_EQ(val, -2.5);
    EXPECT_EQ(*endptr, '\0');
}

// Normal operation: parse positive sign
TEST_F(GstrtodTest_31, ParsePositiveSign_31) {
    char *endptr = nullptr;
    double val = gstrtod("+7.25", &endptr);
    EXPECT_DOUBLE_EQ(val, 7.25);
    EXPECT_EQ(*endptr, '\0');
}

// Normal operation: parse number with exponent
TEST_F(GstrtodTest_31, ParseScientificNotation_31) {
    char *endptr = nullptr;
    double val = gstrtod("1.5e2", &endptr);
    EXPECT_DOUBLE_EQ(val, 150.0);
    EXPECT_EQ(*endptr, '\0');
}

// Normal operation: parse number with uppercase E exponent
TEST_F(GstrtodTest_31, ParseScientificNotationUpperE_31) {
    char *endptr = nullptr;
    double val = gstrtod("2.0E3", &endptr);
    EXPECT_DOUBLE_EQ(val, 2000.0);
    EXPECT_EQ(*endptr, '\0');
}

// Normal operation: parse number with negative exponent
TEST_F(GstrtodTest_31, ParseNegativeExponent_31) {
    char *endptr = nullptr;
    double val = gstrtod("5.0e-2", &endptr);
    EXPECT_DOUBLE_EQ(val, 0.05);
    EXPECT_EQ(*endptr, '\0');
}

// Normal operation: parse number with positive exponent sign
TEST_F(GstrtodTest_31, ParsePositiveExponent_31) {
    char *endptr = nullptr;
    double val = gstrtod("1.0e+3", &endptr);
    EXPECT_DOUBLE_EQ(val, 1000.0);
    EXPECT_EQ(*endptr, '\0');
}

// Leading whitespace
TEST_F(GstrtodTest_31, ParseWithLeadingWhitespace_31) {
    char *endptr = nullptr;
    double val = gstrtod("   42.0", &endptr);
    EXPECT_DOUBLE_EQ(val, 42.0);
    EXPECT_EQ(*endptr, '\0');
}

// Trailing non-numeric characters
TEST_F(GstrtodTest_31, ParseWithTrailingChars_31) {
    char *endptr = nullptr;
    double val = gstrtod("3.14abc", &endptr);
    EXPECT_DOUBLE_EQ(val, 3.14);
    EXPECT_NE(endptr, nullptr);
    EXPECT_STREQ(endptr, "abc");
}

// Number starting with decimal point
TEST_F(GstrtodTest_31, ParseStartingWithDecimalPoint_31) {
    char *endptr = nullptr;
    double val = gstrtod(".5", &endptr);
    EXPECT_DOUBLE_EQ(val, 0.5);
    EXPECT_EQ(*endptr, '\0');
}

// Number ending with decimal point
TEST_F(GstrtodTest_31, ParseEndingWithDecimalPoint_31) {
    char *endptr = nullptr;
    double val = gstrtod("5.", &endptr);
    EXPECT_DOUBLE_EQ(val, 5.0);
    EXPECT_EQ(*endptr, '\0');
}

// Zero value
TEST_F(GstrtodTest_31, ParseZero_31) {
    char *endptr = nullptr;
    double val = gstrtod("0", &endptr);
    EXPECT_DOUBLE_EQ(val, 0.0);
    EXPECT_EQ(*endptr, '\0');
}

// Zero with decimal
TEST_F(GstrtodTest_31, ParseZeroWithDecimal_31) {
    char *endptr = nullptr;
    double val = gstrtod("0.0", &endptr);
    EXPECT_DOUBLE_EQ(val, 0.0);
    EXPECT_EQ(*endptr, '\0');
}

// Empty string
TEST_F(GstrtodTest_31, ParseEmptyString_31) {
    char *endptr = nullptr;
    const char *input = "";
    double val = gstrtod(input, &endptr);
    EXPECT_DOUBLE_EQ(val, 0.0);
    EXPECT_EQ(endptr, input);
}

// Non-numeric string
TEST_F(GstrtodTest_31, ParseNonNumericString_31) {
    char *endptr = nullptr;
    const char *input = "abc";
    double val = gstrtod(input, &endptr);
    EXPECT_DOUBLE_EQ(val, 0.0);
    EXPECT_EQ(endptr, input);
}

// Null endptr (should not crash)
TEST_F(GstrtodTest_31, NullEndPtr_31) {
    double val = gstrtod("123.456", nullptr);
    EXPECT_DOUBLE_EQ(val, 123.456);
}

// Very large number
TEST_F(GstrtodTest_31, ParseVeryLargeNumber_31) {
    char *endptr = nullptr;
    double val = gstrtod("1e308", &endptr);
    EXPECT_DOUBLE_EQ(val, 1e308);
    EXPECT_EQ(*endptr, '\0');
}

// Very small number
TEST_F(GstrtodTest_31, ParseVerySmallNumber_31) {
    char *endptr = nullptr;
    double val = gstrtod("1e-308", &endptr);
    EXPECT_DOUBLE_EQ(val, 1e-308);
    EXPECT_EQ(*endptr, '\0');
}

// Overflow should set errno to ERANGE
TEST_F(GstrtodTest_31, OverflowSetsErrno_31) {
    char *endptr = nullptr;
    double val = gstrtod("1e99999", &endptr);
    EXPECT_TRUE(std::isinf(val));
    EXPECT_EQ(errno, ERANGE);
}

// Underflow to zero
TEST_F(GstrtodTest_31, UnderflowToZero_31) {
    char *endptr = nullptr;
    double val = gstrtod("1e-99999", &endptr);
    EXPECT_DOUBLE_EQ(val, 0.0);
    // errno may or may not be ERANGE depending on implementation
}

// Multiple decimal points - should stop at second one
TEST_F(GstrtodTest_31, MultipleDecimalPoints_31) {
    char *endptr = nullptr;
    double val = gstrtod("1.2.3", &endptr);
    EXPECT_DOUBLE_EQ(val, 1.2);
    EXPECT_STREQ(endptr, ".3");
}

// Whitespace only
TEST_F(GstrtodTest_31, WhitespaceOnly_31) {
    char *endptr = nullptr;
    const char *input = "   ";
    double val = gstrtod(input, &endptr);
    EXPECT_DOUBLE_EQ(val, 0.0);
    // endptr should point to the beginning (no valid conversion)
    EXPECT_EQ(endptr, input);
}

// Negative zero
TEST_F(GstrtodTest_31, ParseNegativeZero_31) {
    char *endptr = nullptr;
    double val = gstrtod("-0.0", &endptr);
    EXPECT_DOUBLE_EQ(val, 0.0);
    // Check if it's negative zero
    EXPECT_TRUE(std::signbit(val));
    EXPECT_EQ(*endptr, '\0');
}

// Number followed by space
TEST_F(GstrtodTest_31, NumberFollowedBySpace_31) {
    char *endptr = nullptr;
    double val = gstrtod("1.5 ", &endptr);
    EXPECT_DOUBLE_EQ(val, 1.5);
    EXPECT_STREQ(endptr, " ");
}

// Just a decimal point
TEST_F(GstrtodTest_31, JustDecimalPoint_31) {
    char *endptr = nullptr;
    const char *input = ".";
    double val = gstrtod(input, &endptr);
    // A lone decimal point is not a valid number for standard strtod
    EXPECT_DOUBLE_EQ(val, 0.0);
}

// Sign followed by non-digit
TEST_F(GstrtodTest_31, SignFollowedByNonDigit_31) {
    char *endptr = nullptr;
    const char *input = "+abc";
    double val = gstrtod(input, &endptr);
    EXPECT_DOUBLE_EQ(val, 0.0);
    EXPECT_EQ(endptr, input);
}

// Exponent without digits after it
TEST_F(GstrtodTest_31, ExponentWithoutDigits_31) {
    char *endptr = nullptr;
    double val = gstrtod("1.5e", &endptr);
    // Standard strtod behavior: parse "1.5", leave "e" unconsumed
    EXPECT_DOUBLE_EQ(val, 1.5);
    EXPECT_STREQ(endptr, "e");
}

// Complex scientific notation
TEST_F(GstrtodTest_31, ComplexScientificNotation_31) {
    char *endptr = nullptr;
    double val = gstrtod("  -1.23456e+10xyz", &endptr);
    EXPECT_DOUBLE_EQ(val, -1.23456e+10);
    EXPECT_STREQ(endptr, "xyz");
}

// Integer with exponent
TEST_F(GstrtodTest_31, IntegerWithExponent_31) {
    char *endptr = nullptr;
    double val = gstrtod("5e3", &endptr);
    EXPECT_DOUBLE_EQ(val, 5000.0);
    EXPECT_EQ(*endptr, '\0');
}

// Leading zeros
TEST_F(GstrtodTest_31, LeadingZeros_31) {
    char *endptr = nullptr;
    double val = gstrtod("007.5", &endptr);
    EXPECT_DOUBLE_EQ(val, 7.5);
    EXPECT_EQ(*endptr, '\0');
}

// Negative scientific notation
TEST_F(GstrtodTest_31, NegativeScientific_31) {
    char *endptr = nullptr;
    double val = gstrtod("-3.0e-1", &endptr);
    EXPECT_DOUBLE_EQ(val, -0.3);
    EXPECT_EQ(*endptr, '\0');
}

// Decimal point with only trailing digits
TEST_F(GstrtodTest_31, DecimalPointOnlyTrailingDigits_31) {
    char *endptr = nullptr;
    double val = gstrtod(".001", &endptr);
    EXPECT_DOUBLE_EQ(val, 0.001);
    EXPECT_EQ(*endptr, '\0');
}

// Tab as leading whitespace
TEST_F(GstrtodTest_31, TabAsLeadingWhitespace_31) {
    char *endptr = nullptr;
    double val = gstrtod("\t10.0", &endptr);
    EXPECT_DOUBLE_EQ(val, 10.0);
    EXPECT_EQ(*endptr, '\0');
}

// Newline as leading whitespace
TEST_F(GstrtodTest_31, NewlineAsLeadingWhitespace_31) {
    char *endptr = nullptr;
    double val = gstrtod("\n10.0", &endptr);
    EXPECT_DOUBLE_EQ(val, 10.0);
    EXPECT_EQ(*endptr, '\0');
}

// Large precision number
TEST_F(GstrtodTest_31, LargePrecision_31) {
    char *endptr = nullptr;
    double val = gstrtod("3.141592653589793", &endptr);
    EXPECT_NEAR(val, 3.141592653589793, 1e-15);
    EXPECT_EQ(*endptr, '\0');
}

// Single digit
TEST_F(GstrtodTest_31, SingleDigit_31) {
    char *endptr = nullptr;
    double val = gstrtod("7", &endptr);
    EXPECT_DOUBLE_EQ(val, 7.0);
    EXPECT_EQ(*endptr, '\0');
}

// Negative integer
TEST_F(GstrtodTest_31, NegativeInteger_31) {
    char *endptr = nullptr;
    double val = gstrtod("-42", &endptr);
    EXPECT_DOUBLE_EQ(val, -42.0);
    EXPECT_EQ(*endptr, '\0');
}
