#include <gtest/gtest.h>
#include <string>
#include "yaml-cpp/node/convert.h"

// Test normal negative infinity representations
TEST(IsNegativeInfinityTest_591, LowercaseInf_591) {
    EXPECT_TRUE(YAML::conversion::IsNegativeInfinity("-.inf"));
}

TEST(IsNegativeInfinityTest_591, MixedCaseInf_591) {
    EXPECT_TRUE(YAML::conversion::IsNegativeInfinity("-.Inf"));
}

TEST(IsNegativeInfinityTest_591, UppercaseInf_591) {
    EXPECT_TRUE(YAML::conversion::IsNegativeInfinity("-.INF"));
}

// Test that positive infinity representations return false
TEST(IsNegativeInfinityTest_591, PositiveInfLowercase_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity(".inf"));
}

TEST(IsNegativeInfinityTest_591, PositiveInfMixedCase_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity(".Inf"));
}

TEST(IsNegativeInfinityTest_591, PositiveInfUppercase_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity(".INF"));
}

// Test empty string
TEST(IsNegativeInfinityTest_591, EmptyString_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity(""));
}

// Test unrelated strings
TEST(IsNegativeInfinityTest_591, ArbitraryString_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity("hello"));
}

TEST(IsNegativeInfinityTest_591, NumericString_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity("-123.456"));
}

// Test close but not exact matches
TEST(IsNegativeInfinityTest_591, MissingDash_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity(".inf"));
}

TEST(IsNegativeInfinityTest_591, MissingDot_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity("-inf"));
}

TEST(IsNegativeInfinityTest_591, ExtraSpace_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity(" -.inf"));
}

TEST(IsNegativeInfinityTest_591, TrailingSpace_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity("-.inf "));
}

TEST(IsNegativeInfinityTest_591, WrongCaseMix_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity("-.iNf"));
}

TEST(IsNegativeInfinityTest_591, WrongCaseMix2_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity("-.INf"));
}

TEST(IsNegativeInfinityTest_591, WrongCaseMix3_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity("-.inF"));
}

// Test with "infinity" spelled out
TEST(IsNegativeInfinityTest_591, FullWordInfinity_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity("-infinity"));
}

TEST(IsNegativeInfinityTest_591, NaN_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity(".nan"));
}

// Test with just a dash
TEST(IsNegativeInfinityTest_591, JustDash_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity("-"));
}

// Test with just dash and dot
TEST(IsNegativeInfinityTest_591, DashDot_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity("-."));
}

// Test prefix of valid input
TEST(IsNegativeInfinityTest_591, PartialMatch_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity("-.in"));
}

// Test with null character in string
TEST(IsNegativeInfinityTest_591, NullCharInString_591) {
    std::string withNull("-.inf\0extra", 11);
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity(withNull));
}

// Test positive explicit sign
TEST(IsNegativeInfinityTest_591, PositiveExplicitSign_591) {
    EXPECT_FALSE(YAML::conversion::IsNegativeInfinity("+.inf"));
}
