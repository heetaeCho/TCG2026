// TEST_ID: 590
// File: test/node/convert_isinfinity_test.cpp

#include <gtest/gtest.h>

#include <string>

// Include the header under test
#include "yaml-cpp/node/convert.h"

namespace {

class IsInfinityTest_590 : public ::testing::Test {};

TEST_F(IsInfinityTest_590, MatchesDotInfLowercase_590) {
  EXPECT_TRUE(YAML::conversion::IsInfinity(".inf"));
}

TEST_F(IsInfinityTest_590, MatchesDotInfCapitalI_590) {
  EXPECT_TRUE(YAML::conversion::IsInfinity(".Inf"));
}

TEST_F(IsInfinityTest_590, MatchesDotInfUppercase_590) {
  EXPECT_TRUE(YAML::conversion::IsInfinity(".INF"));
}

TEST_F(IsInfinityTest_590, MatchesPlusDotInfLowercase_590) {
  EXPECT_TRUE(YAML::conversion::IsInfinity("+.inf"));
}

TEST_F(IsInfinityTest_590, MatchesPlusDotInfCapitalI_590) {
  EXPECT_TRUE(YAML::conversion::IsInfinity("+.Inf"));
}

TEST_F(IsInfinityTest_590, MatchesPlusDotInfUppercase_590) {
  EXPECT_TRUE(YAML::conversion::IsInfinity("+.INF"));
}

// Boundary / negative cases: strings close to valid tokens but not exact matches.

TEST_F(IsInfinityTest_590, RejectsMinusInfinityToken_590) {
  EXPECT_FALSE(YAML::conversion::IsInfinity("-.inf"));
  EXPECT_FALSE(YAML::conversion::IsInfinity("-.Inf"));
  EXPECT_FALSE(YAML::conversion::IsInfinity("-.INF"));
}

TEST_F(IsInfinityTest_590, RejectsNoLeadingDot_590) {
  EXPECT_FALSE(YAML::conversion::IsInfinity("inf"));
  EXPECT_FALSE(YAML::conversion::IsInfinity("Inf"));
  EXPECT_FALSE(YAML::conversion::IsInfinity("INF"));
}

TEST_F(IsInfinityTest_590, RejectsWrongCasingInSuffix_590) {
  // Only ".inf", ".Inf", ".INF" (and + variants) are accepted by the interface.
  EXPECT_FALSE(YAML::conversion::IsInfinity(".iNf"));
  EXPECT_FALSE(YAML::conversion::IsInfinity("+.iNf"));
}

TEST_F(IsInfinityTest_590, RejectsExtraWhitespace_590) {
  EXPECT_FALSE(YAML::conversion::IsInfinity(" .inf"));
  EXPECT_FALSE(YAML::conversion::IsInfinity(".inf "));
  EXPECT_FALSE(YAML::conversion::IsInfinity("\t.inf"));
  EXPECT_FALSE(YAML::conversion::IsInfinity(".Inf\n"));
}

TEST_F(IsInfinityTest_590, RejectsExtraCharacters_590) {
  EXPECT_FALSE(YAML::conversion::IsInfinity(".infx"));
  EXPECT_FALSE(YAML::conversion::IsInfinity("x.inf"));
  EXPECT_FALSE(YAML::conversion::IsInfinity("+.INFx"));
  EXPECT_FALSE(YAML::conversion::IsInfinity("++.inf"));
}

TEST_F(IsInfinityTest_590, RejectsEmptyString_590) {
  EXPECT_FALSE(YAML::conversion::IsInfinity(std::string()));
}

TEST_F(IsInfinityTest_590, RejectsCommonSpecialFloatSpellings_590) {
  // Ensure no unintended acceptance of other spellings.
  EXPECT_FALSE(YAML::conversion::IsInfinity("Infinity"));
  EXPECT_FALSE(YAML::conversion::IsInfinity("inf"));
  EXPECT_FALSE(YAML::conversion::IsInfinity("INFINITY"));
  EXPECT_FALSE(YAML::conversion::IsInfinity("+inf"));
}

}  // namespace