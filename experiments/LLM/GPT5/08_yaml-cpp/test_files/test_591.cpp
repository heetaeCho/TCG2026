// File: test/yaml_cpp_node_convert_IsNegativeInfinity_591_test.cpp

#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/convert.h"

namespace {

using YAML::conversion::IsNegativeInfinity;

class IsNegativeInfinityTest_591 : public ::testing::Test {};

TEST_F(IsNegativeInfinityTest_591, ReturnsTrueForLowercaseDotInf_591) {
  EXPECT_TRUE(IsNegativeInfinity("-.inf"));
}

TEST_F(IsNegativeInfinityTest_591, ReturnsTrueForCapitalIOnlyDotInf_591) {
  EXPECT_TRUE(IsNegativeInfinity("-.Inf"));
}

TEST_F(IsNegativeInfinityTest_591, ReturnsTrueForUppercaseDotInf_591) {
  EXPECT_TRUE(IsNegativeInfinity("-.INF"));
}

TEST_F(IsNegativeInfinityTest_591, ReturnsFalseForEmptyString_591) {
  EXPECT_FALSE(IsNegativeInfinity(""));
}

TEST_F(IsNegativeInfinityTest_591, ReturnsFalseForDotInfWithoutMinus_591) {
  EXPECT_FALSE(IsNegativeInfinity(".inf"));
  EXPECT_FALSE(IsNegativeInfinity(".Inf"));
  EXPECT_FALSE(IsNegativeInfinity(".INF"));
}

TEST_F(IsNegativeInfinityTest_591, ReturnsFalseForMinusInfWithoutDot_591) {
  EXPECT_FALSE(IsNegativeInfinity("-inf"));
  EXPECT_FALSE(IsNegativeInfinity("-Inf"));
  EXPECT_FALSE(IsNegativeInfinity("-INF"));
}

TEST_F(IsNegativeInfinityTest_591, ReturnsFalseForPlusDotInf_591) {
  EXPECT_FALSE(IsNegativeInfinity("+.inf"));
  EXPECT_FALSE(IsNegativeInfinity("+.Inf"));
  EXPECT_FALSE(IsNegativeInfinity("+.INF"));
}

TEST_F(IsNegativeInfinityTest_591, ReturnsFalseForDifferentSpellingOrCase_591) {
  EXPECT_FALSE(IsNegativeInfinity("-.inF"));
  EXPECT_FALSE(IsNegativeInfinity("-.iNF"));
  EXPECT_FALSE(IsNegativeInfinity("-.InF"));
  EXPECT_FALSE(IsNegativeInfinity("-.iNf"));
}

TEST_F(IsNegativeInfinityTest_591, ReturnsFalseWhenWhitespaceIsPresent_591) {
  EXPECT_FALSE(IsNegativeInfinity(" -.inf"));
  EXPECT_FALSE(IsNegativeInfinity("-.inf "));
  EXPECT_FALSE(IsNegativeInfinity("\t-.Inf"));
  EXPECT_FALSE(IsNegativeInfinity("-.INF\n"));
}

TEST_F(IsNegativeInfinityTest_591, ReturnsFalseForEmbeddedInLargerString_591) {
  EXPECT_FALSE(IsNegativeInfinity("x-.inf"));
  EXPECT_FALSE(IsNegativeInfinity("-.infy"));
  EXPECT_FALSE(IsNegativeInfinity("value: -.INF"));
}

TEST_F(IsNegativeInfinityTest_591, ReturnsFalseForOtherYamlInfinityMarkers_591) {
  EXPECT_FALSE(IsNegativeInfinity(".inf"));
  EXPECT_FALSE(IsNegativeInfinity(".Inf"));
  EXPECT_FALSE(IsNegativeInfinity(".INF"));
  EXPECT_FALSE(IsNegativeInfinity("-.infinity"));
  EXPECT_FALSE(IsNegativeInfinity("-.Infinity"));
  EXPECT_FALSE(IsNegativeInfinity("-.INFINITY"));
}

}  // namespace