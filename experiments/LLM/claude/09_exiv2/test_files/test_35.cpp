#include <gtest/gtest.h>
#include <string>
#include <limits>
#include <cmath>

// Include the header under test
#include "exiv2/types.hpp"

// ============================================================================
// Tests for Exiv2::stringTo<int>
// ============================================================================

TEST(StringToInt_35, ValidPositiveInteger_35) {
    bool ok = false;
    int result = Exiv2::stringTo<int>("42", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 42);
}

TEST(StringToInt_35, ValidNegativeInteger_35) {
    bool ok = false;
    int result = Exiv2::stringTo<int>("-100", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, -100);
}

TEST(StringToInt_35, ValidZero_35) {
    bool ok = false;
    int result = Exiv2::stringTo<int>("0", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 0);
}

TEST(StringToInt_35, EmptyString_35) {
    bool ok = true;
    int result = Exiv2::stringTo<int>("", ok);
    EXPECT_FALSE(ok);
    (void)result;
}

TEST(StringToInt_35, NonNumericString_35) {
    bool ok = true;
    int result = Exiv2::stringTo<int>("abc", ok);
    EXPECT_FALSE(ok);
    (void)result;
}

TEST(StringToInt_35, IntegerWithTrailingText_35) {
    bool ok = true;
    int result = Exiv2::stringTo<int>("42abc", ok);
    EXPECT_FALSE(ok);
    (void)result;
}

TEST(StringToInt_35, IntegerWithLeadingWhitespace_35) {
    bool ok = false;
    int result = Exiv2::stringTo<int>("  42", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 42);
}

TEST(StringToInt_35, IntegerWithTrailingWhitespace_35) {
    bool ok = false;
    int result = Exiv2::stringTo<int>("42  ", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 42);
}

TEST(StringToInt_35, IntegerWithTrailingWhitespaceAndText_35) {
    bool ok = true;
    int result = Exiv2::stringTo<int>("42  abc", ok);
    EXPECT_FALSE(ok);
    (void)result;
}

TEST(StringToInt_35, OnlyWhitespace_35) {
    bool ok = true;
    int result = Exiv2::stringTo<int>("   ", ok);
    EXPECT_FALSE(ok);
    (void)result;
}

TEST(StringToInt_35, PlusSign_35) {
    bool ok = false;
    int result = Exiv2::stringTo<int>("+10", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 10);
}

TEST(StringToInt_35, MaxInt_35) {
    bool ok = false;
    std::string maxStr = std::to_string(std::numeric_limits<int>::max());
    int result = Exiv2::stringTo<int>(maxStr, ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, std::numeric_limits<int>::max());
}

TEST(StringToInt_35, MinInt_35) {
    bool ok = false;
    std::string minStr = std::to_string(std::numeric_limits<int>::min());
    int result = Exiv2::stringTo<int>(minStr, ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, std::numeric_limits<int>::min());
}

TEST(StringToInt_35, MultipleNumbers_35) {
    bool ok = true;
    int result = Exiv2::stringTo<int>("12 34", ok);
    EXPECT_FALSE(ok);
    (void)result;
}

// ============================================================================
// Tests for Exiv2::stringTo<double>
// ============================================================================

TEST(StringToDouble_35, ValidPositiveDouble_35) {
    bool ok = false;
    double result = Exiv2::stringTo<double>("3.14", ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, 3.14);
}

TEST(StringToDouble_35, ValidNegativeDouble_35) {
    bool ok = false;
    double result = Exiv2::stringTo<double>("-2.718", ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, -2.718);
}

TEST(StringToDouble_35, ValidZeroDouble_35) {
    bool ok = false;
    double result = Exiv2::stringTo<double>("0.0", ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(StringToDouble_35, ScientificNotation_35) {
    bool ok = false;
    double result = Exiv2::stringTo<double>("1.5e2", ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, 150.0);
}

TEST(StringToDouble_35, NegativeScientificNotation_35) {
    bool ok = false;
    double result = Exiv2::stringTo<double>("1.5e-2", ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, 0.015);
}

TEST(StringToDouble_35, DoubleWithTrailingText_35) {
    bool ok = true;
    double result = Exiv2::stringTo<double>("3.14xyz", ok);
    EXPECT_FALSE(ok);
    (void)result;
}

TEST(StringToDouble_35, EmptyString_35) {
    bool ok = true;
    double result = Exiv2::stringTo<double>("", ok);
    EXPECT_FALSE(ok);
    (void)result;
}

TEST(StringToDouble_35, IntegerAsDouble_35) {
    bool ok = false;
    double result = Exiv2::stringTo<double>("42", ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, 42.0);
}

// ============================================================================
// Tests for Exiv2::stringTo<float>
// ============================================================================

TEST(StringToFloat_35, ValidFloat_35) {
    bool ok = false;
    float result = Exiv2::stringTo<float>("1.5", ok);
    EXPECT_TRUE(ok);
    EXPECT_FLOAT_EQ(result, 1.5f);
}

TEST(StringToFloat_35, InvalidString_35) {
    bool ok = true;
    float result = Exiv2::stringTo<float>("not_a_number", ok);
    EXPECT_FALSE(ok);
    (void)result;
}

// ============================================================================
// Tests for Exiv2::stringTo<long>
// ============================================================================

TEST(StringToLong_35, ValidLong_35) {
    bool ok = false;
    long result = Exiv2::stringTo<long>("123456789", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 123456789L);
}

TEST(StringToLong_35, NegativeLong_35) {
    bool ok = false;
    long result = Exiv2::stringTo<long>("-987654321", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, -987654321L);
}

TEST(StringToLong_35, InvalidLong_35) {
    bool ok = true;
    long result = Exiv2::stringTo<long>("abc", ok);
    EXPECT_FALSE(ok);
    (void)result;
}

// ============================================================================
// Tests for Exiv2::stringTo<unsigned int>
// ============================================================================

TEST(StringToUnsignedInt_35, ValidUnsigned_35) {
    bool ok = false;
    unsigned int result = Exiv2::stringTo<unsigned int>("500", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 500u);
}

TEST(StringToUnsignedInt_35, Zero_35) {
    bool ok = false;
    unsigned int result = Exiv2::stringTo<unsigned int>("0", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 0u);
}

// ============================================================================
// Tests for Exiv2::stringTo<std::string>
// ============================================================================

TEST(StringToString_35, SingleWord_35) {
    bool ok = false;
    std::string result = Exiv2::stringTo<std::string>("hello", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, "hello");
}

TEST(StringToString_35, MultipleWords_35) {
    // stringTo reads until whitespace, then rest is not empty => ok should be false
    bool ok = true;
    std::string result = Exiv2::stringTo<std::string>("hello world", ok);
    EXPECT_FALSE(ok);
    (void)result;
}

TEST(StringToString_35, EmptyString_35) {
    bool ok = true;
    std::string result = Exiv2::stringTo<std::string>("", ok);
    EXPECT_FALSE(ok);
    (void)result;
}

TEST(StringToString_35, SingleWordWithLeadingTrailingWhitespace_35) {
    bool ok = false;
    std::string result = Exiv2::stringTo<std::string>("  hello  ", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, "hello");
}

// ============================================================================
// Tests for Exiv2::stringTo<bool>
// ============================================================================

TEST(StringToBool_35, TrueValue_35) {
    bool ok = false;
    bool result = Exiv2::stringTo<bool>("1", ok);
    EXPECT_TRUE(ok);
    EXPECT_TRUE(result);
}

TEST(StringToBool_35, FalseValue_35) {
    bool ok = false;
    bool result = Exiv2::stringTo<bool>("0", ok);
    EXPECT_TRUE(ok);
    EXPECT_FALSE(result);
}

// ============================================================================
// Tests for Exiv2::stringTo<short>
// ============================================================================

TEST(StringToShort_35, ValidShort_35) {
    bool ok = false;
    short result = Exiv2::stringTo<short>("32000", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 32000);
}

TEST(StringToShort_35, NegativeShort_35) {
    bool ok = false;
    short result = Exiv2::stringTo<short>("-1000", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, -1000);
}

// ============================================================================
// Edge case tests
// ============================================================================

TEST(StringToInt_35, TabAndNewlineWhitespace_35) {
    bool ok = false;
    int result = Exiv2::stringTo<int>("\t42\n", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 42);
}

TEST(StringToInt_35, DecimalPointInteger_35) {
    // "42.5" should fail for int since ".5" remains
    bool ok = true;
    int result = Exiv2::stringTo<int>("42.5", ok);
    EXPECT_FALSE(ok);
    (void)result;
}

TEST(StringToDouble_35, MultipleDecimalPoints_35) {
    bool ok = true;
    double result = Exiv2::stringTo<double>("3.14.15", ok);
    EXPECT_FALSE(ok);
    (void)result;
}

TEST(StringToInt_35, LeadingZeros_35) {
    bool ok = false;
    int result = Exiv2::stringTo<int>("007", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 7);
}

TEST(StringToDouble_35, LeadingDot_35) {
    bool ok = false;
    double result = Exiv2::stringTo<double>(".5", ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, 0.5);
}

TEST(StringToDouble_35, TrailingDot_35) {
    bool ok = false;
    double result = Exiv2::stringTo<double>("5.", ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST(StringToInt_35, HexFormat_35) {
    // Hex format "0x1A" - depends on stream behavior
    // For int, istringstream by default reads decimal
    bool ok = true;
    int result = Exiv2::stringTo<int>("0x1A", ok);
    // "0x1A" - reads "0", rest is "x1A" which is not empty
    EXPECT_FALSE(ok);
    (void)result;
}

TEST(StringToLongLong_35, ValidLongLong_35) {
    bool ok = false;
    long long result = Exiv2::stringTo<long long>("9999999999", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 9999999999LL);
}

TEST(StringToChar_35, SingleChar_35) {
    bool ok = false;
    char result = Exiv2::stringTo<char>("A", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 'A');
}

TEST(StringToChar_35, MultipleChars_35) {
    bool ok = true;
    char result = Exiv2::stringTo<char>("AB", ok);
    // Reads 'A', rest is "B" which is not empty
    EXPECT_FALSE(ok);
    (void)result;
}
