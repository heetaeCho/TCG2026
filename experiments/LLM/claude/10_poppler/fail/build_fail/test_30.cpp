#include <gtest/gtest.h>
#include <cmath>
#include <cstring>
#include <climits>
#include <string>

// Forward declarations for the functions we're testing
extern double gstrtod(const char *nptr, char **endptr);
extern double gatof(const char *nptr);

class GstrtodTest_30 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== gatof tests ====================

TEST_F(GstrtodTest_30, GatofSimpleInteger_30) {
    double result = gatof("42");
    EXPECT_DOUBLE_EQ(result, 42.0);
}

TEST_F(GstrtodTest_30, GatofSimpleDecimal_30) {
    double result = gatof("3.14");
    EXPECT_DOUBLE_EQ(result, 3.14);
}

TEST_F(GstrtodTest_30, GatofNegativeNumber_30) {
    double result = gatof("-2.5");
    EXPECT_DOUBLE_EQ(result, -2.5);
}

TEST_F(GstrtodTest_30, GatofZero_30) {
    double result = gatof("0");
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(GstrtodTest_30, GatofNegativeZero_30) {
    double result = gatof("-0.0");
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(GstrtodTest_30, GatofLeadingWhitespace_30) {
    double result = gatof("  123.456");
    EXPECT_DOUBLE_EQ(result, 123.456);
}

TEST_F(GstrtodTest_30, GatofScientificNotation_30) {
    double result = gatof("1.5e2");
    EXPECT_DOUBLE_EQ(result, 150.0);
}

TEST_F(GstrtodTest_30, GatofScientificNotationNegativeExponent_30) {
    double result = gatof("1.5e-2");
    EXPECT_DOUBLE_EQ(result, 0.015);
}

TEST_F(GstrtodTest_30, GatofPositiveSign_30) {
    double result = gatof("+7.5");
    EXPECT_DOUBLE_EQ(result, 7.5);
}

TEST_F(GstrtodTest_30, GatofEmptyString_30) {
    double result = gatof("");
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(GstrtodTest_30, GatofNonNumericString_30) {
    double result = gatof("abc");
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(GstrtodTest_30, GatofVeryLargeNumber_30) {
    double result = gatof("1e308");
    EXPECT_DOUBLE_EQ(result, 1e308);
}

TEST_F(GstrtodTest_30, GatofVerySmallNumber_30) {
    double result = gatof("1e-308");
    EXPECT_DOUBLE_EQ(result, 1e-308);
}

TEST_F(GstrtodTest_30, GatofOnlyDecimalPoint_30) {
    double result = gatof(".");
    // Should return 0 or parse as 0
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(GstrtodTest_30, GatofDecimalWithoutLeadingDigit_30) {
    double result = gatof(".5");
    EXPECT_DOUBLE_EQ(result, 0.5);
}

TEST_F(GstrtodTest_30, GatofDecimalWithoutTrailingDigit_30) {
    double result = gatof("5.");
    EXPECT_DOUBLE_EQ(result, 5.0);
}

// ==================== gstrtod tests ====================

TEST_F(GstrtodTest_30, GstrtodSimpleInteger_30) {
    char *endptr = nullptr;
    double result = gstrtod("42", &endptr);
    EXPECT_DOUBLE_EQ(result, 42.0);
    EXPECT_NE(endptr, nullptr);
}

TEST_F(GstrtodTest_30, GstrtodSimpleDecimal_30) {
    char *endptr = nullptr;
    double result = gstrtod("3.14", &endptr);
    EXPECT_DOUBLE_EQ(result, 3.14);
}

TEST_F(GstrtodTest_30, GstrtodEndptrPointsAfterNumber_30) {
    const char *str = "123abc";
    char *endptr = nullptr;
    double result = gstrtod(str, &endptr);
    EXPECT_DOUBLE_EQ(result, 123.0);
    EXPECT_EQ(endptr, str + 3);
}

TEST_F(GstrtodTest_30, GstrtodNullEndptr_30) {
    double result = gstrtod("99.9", nullptr);
    EXPECT_DOUBLE_EQ(result, 99.9);
}

TEST_F(GstrtodTest_30, GstrtodNegativeNumber_30) {
    char *endptr = nullptr;
    double result = gstrtod("-10.5", &endptr);
    EXPECT_DOUBLE_EQ(result, -10.5);
}

TEST_F(GstrtodTest_30, GstrtodScientificNotation_30) {
    char *endptr = nullptr;
    double result = gstrtod("2.5e3", &endptr);
    EXPECT_DOUBLE_EQ(result, 2500.0);
}

TEST_F(GstrtodTest_30, GstrtodLeadingWhitespace_30) {
    char *endptr = nullptr;
    double result = gstrtod("   45.6", &endptr);
    EXPECT_DOUBLE_EQ(result, 45.6);
}

TEST_F(GstrtodTest_30, GstrtodNoNumberParsed_30) {
    const char *str = "abc";
    char *endptr = nullptr;
    double result = gstrtod(str, &endptr);
    EXPECT_DOUBLE_EQ(result, 0.0);
    EXPECT_EQ(endptr, str);
}

TEST_F(GstrtodTest_30, GstrtodEmptyString_30) {
    const char *str = "";
    char *endptr = nullptr;
    double result = gstrtod(str, &endptr);
    EXPECT_DOUBLE_EQ(result, 0.0);
    EXPECT_EQ(endptr, str);
}

TEST_F(GstrtodTest_30, GstrtodWithTrailingSpaces_30) {
    const char *str = "7.7  ";
    char *endptr = nullptr;
    double result = gstrtod(str, &endptr);
    EXPECT_DOUBLE_EQ(result, 7.7);
    // endptr should point to the space after the number
    EXPECT_EQ(endptr, str + 3);
}

TEST_F(GstrtodTest_30, GstrtodPositiveSign_30) {
    char *endptr = nullptr;
    double result = gstrtod("+100", &endptr);
    EXPECT_DOUBLE_EQ(result, 100.0);
}

TEST_F(GstrtodTest_30, GstrtodScientificUpperE_30) {
    char *endptr = nullptr;
    double result = gstrtod("1.5E2", &endptr);
    EXPECT_DOUBLE_EQ(result, 150.0);
}

TEST_F(GstrtodTest_30, GstrtodMultipleDecimals_30) {
    const char *str = "1.2.3";
    char *endptr = nullptr;
    double result = gstrtod(str, &endptr);
    EXPECT_DOUBLE_EQ(result, 1.2);
    // endptr should point to the second decimal point
    EXPECT_EQ(endptr, str + 3);
}

// Test that gstrtod uses '.' as decimal separator regardless of locale
// (This is the typical reason gstrtod exists - locale-independent parsing)
TEST_F(GstrtodTest_30, GstrtodUsesPointAsDecimalSeparator_30) {
    char *endptr = nullptr;
    double result = gstrtod("1.5", &endptr);
    EXPECT_DOUBLE_EQ(result, 1.5);
}

TEST_F(GstrtodTest_30, GstrtodCommaNotDecimalSeparator_30) {
    const char *str = "1,5";
    char *endptr = nullptr;
    double result = gstrtod(str, &endptr);
    // Expect that comma is NOT treated as decimal separator
    EXPECT_DOUBLE_EQ(result, 1.0);
    EXPECT_EQ(endptr, str + 1);
}

TEST_F(GstrtodTest_30, GstrtodZeroPointZero_30) {
    char *endptr = nullptr;
    double result = gstrtod("0.0", &endptr);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(GstrtodTest_30, GstrtodLargeExponent_30) {
    char *endptr = nullptr;
    double result = gstrtod("1e308", &endptr);
    EXPECT_DOUBLE_EQ(result, 1e308);
}

TEST_F(GstrtodTest_30, GstrtodInfinity_30) {
    // Some implementations may handle "inf"
    char *endptr = nullptr;
    double result = gstrtod("inf", &endptr);
    if (std::isinf(result)) {
        EXPECT_TRUE(std::isinf(result));
    } else {
        // If not parsed as inf, should return 0 with endptr at start
        EXPECT_DOUBLE_EQ(result, 0.0);
    }
}

TEST_F(GstrtodTest_30, GstrtodNegativeScientific_30) {
    char *endptr = nullptr;
    double result = gstrtod("-3.14e1", &endptr);
    EXPECT_DOUBLE_EQ(result, -31.4);
}

TEST_F(GstrtodTest_30, GstrtodConsecutiveParsing_30) {
    const char *str = "1.0 2.0 3.0";
    char *endptr = nullptr;
    
    double r1 = gstrtod(str, &endptr);
    EXPECT_DOUBLE_EQ(r1, 1.0);
    
    double r2 = gstrtod(endptr, &endptr);
    EXPECT_DOUBLE_EQ(r2, 2.0);
    
    double r3 = gstrtod(endptr, &endptr);
    EXPECT_DOUBLE_EQ(r3, 3.0);
}

TEST_F(GstrtodTest_30, GatofWithComma_30) {
    // Verify gatof also treats comma as non-decimal
    double result = gatof("2,5");
    EXPECT_DOUBLE_EQ(result, 2.0);
}

TEST_F(GstrtodTest_30, GstrtodOnlyWhitespace_30) {
    const char *str = "   ";
    char *endptr = nullptr;
    double result = gstrtod(str, &endptr);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(GstrtodTest_30, GatofLargeDecimal_30) {
    double result = gatof("123456789.123456789");
    EXPECT_NEAR(result, 123456789.123456789, 1e-5);
}
