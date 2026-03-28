#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "yaml-cpp/node/convert.h"

// Test fixture for IsInfinity function
class IsInfinityTest_590 : public ::testing::Test {
protected:
};

// ==================== Normal Operation Tests ====================

TEST_F(IsInfinityTest_590, LowercaseDotInf_590) {
    EXPECT_TRUE(YAML::conversion::IsInfinity(".inf"));
}

TEST_F(IsInfinityTest_590, MixedCaseDotInf_590) {
    EXPECT_TRUE(YAML::conversion::IsInfinity(".Inf"));
}

TEST_F(IsInfinityTest_590, UppercaseDotINF_590) {
    EXPECT_TRUE(YAML::conversion::IsInfinity(".INF"));
}

TEST_F(IsInfinityTest_590, PlusLowercaseDotInf_590) {
    EXPECT_TRUE(YAML::conversion::IsInfinity("+.inf"));
}

TEST_F(IsInfinityTest_590, PlusMixedCaseDotInf_590) {
    EXPECT_TRUE(YAML::conversion::IsInfinity("+.Inf"));
}

TEST_F(IsInfinityTest_590, PlusUppercaseDotINF_590) {
    EXPECT_TRUE(YAML::conversion::IsInfinity("+.INF"));
}

// ==================== Negative/Non-Matching Tests ====================

TEST_F(IsInfinityTest_590, EmptyString_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity(""));
}

TEST_F(IsInfinityTest_590, NegativeInfLowercase_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity("-.inf"));
}

TEST_F(IsInfinityTest_590, NegativeInfMixedCase_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity("-.Inf"));
}

TEST_F(IsInfinityTest_590, NegativeInfUppercase_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity("-.INF"));
}

TEST_F(IsInfinityTest_590, PlainWordInfinity_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity("infinity"));
}

TEST_F(IsInfinityTest_590, PlainWordInf_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity("inf"));
}

TEST_F(IsInfinityTest_590, UppercaseINF_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity("INF"));
}

TEST_F(IsInfinityTest_590, JustDot_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity("."));
}

TEST_F(IsInfinityTest_590, JustPlus_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity("+"));
}

TEST_F(IsInfinityTest_590, PlusDot_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity("+."));
}

TEST_F(IsInfinityTest_590, RandomString_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity("hello"));
}

TEST_F(IsInfinityTest_590, NumericString_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity("123"));
}

// ==================== Boundary / Edge Cases ====================

TEST_F(IsInfinityTest_590, LeadingWhitespace_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity(" .inf"));
}

TEST_F(IsInfinityTest_590, TrailingWhitespace_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity(".inf "));
}

TEST_F(IsInfinityTest_590, LeadingAndTrailingWhitespace_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity(" .inf "));
}

TEST_F(IsInfinityTest_590, MixedCaseInfNotMatching_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity(".iNf"));
}

TEST_F(IsInfinityTest_590, MixedCaseInFNotMatching_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity(".InF"));
}

TEST_F(IsInfinityTest_590, MixedCaseINfNotMatching_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity(".INf"));
}

TEST_F(IsInfinityTest_590, DotInfWithExtraChars_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity(".infx"));
}

TEST_F(IsInfinityTest_590, PlusDotInfWithExtraChars_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity("+.infx"));
}

TEST_F(IsInfinityTest_590, NullCharacterInString_590) {
    std::string s(".inf");
    s += '\0';
    // String with null character appended is longer, should not match
    EXPECT_FALSE(YAML::conversion::IsInfinity(s));
}

TEST_F(IsInfinityTest_590, DoublePlusDotInf_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity("++.inf"));
}

TEST_F(IsInfinityTest_590, PlusWithoutDotInf_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity("+inf"));
}

TEST_F(IsInfinityTest_590, DotNan_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity(".nan"));
}

TEST_F(IsInfinityTest_590, DotNaN_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity(".NaN"));
}

TEST_F(IsInfinityTest_590, DotNAN_590) {
    EXPECT_FALSE(YAML::conversion::IsInfinity(".NAN"));
}
