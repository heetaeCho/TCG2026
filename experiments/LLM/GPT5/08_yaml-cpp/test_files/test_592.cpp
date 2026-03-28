// File: test/node/convert_isnan_test.cpp

#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/convert.h"

namespace {

class IsNaNTest_592 : public ::testing::Test {};

TEST_F(IsNaNTest_592, ReturnsTrueForDotNanLowercase_592) {
  EXPECT_TRUE(YAML::conversion::IsNaN(std::string(".nan")));
}

TEST_F(IsNaNTest_592, ReturnsTrueForDotNaNMixedCase_592) {
  EXPECT_TRUE(YAML::conversion::IsNaN(std::string(".NaN")));
}

TEST_F(IsNaNTest_592, ReturnsTrueForDotNANUppercase_592) {
  EXPECT_TRUE(YAML::conversion::IsNaN(std::string(".NAN")));
}

TEST_F(IsNaNTest_592, ReturnsFalseForOtherCasingVariants_592) {
  // Boundary-ish: very close strings that differ by case pattern.
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string(".nAn")));
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string(".naN")));
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string(".Nan")));
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string(".nAN")));
}

TEST_F(IsNaNTest_592, ReturnsFalseForMissingDot_592) {
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string("nan")));
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string("NaN")));
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string("NAN")));
}

TEST_F(IsNaNTest_592, ReturnsFalseForWhitespaceOrPadding_592) {
  // Boundary: surrounding whitespace should make the string different.
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string(" .nan")));
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string(".nan ")));
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string("\t.nan")));
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string(".nan\n")));
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string("  .NaN  ")));
}

TEST_F(IsNaNTest_592, ReturnsFalseForAdditionalCharacters_592) {
  // Boundary: prefix/suffix/embedded characters.
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string("..nan")));
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string(".nan.")));
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string(".nan0")));
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string(".0nan")));
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string("x.nan")));
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string(".NaNx")));
}

TEST_F(IsNaNTest_592, ReturnsFalseForEmptyString_592) {
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string("")));
}

TEST_F(IsNaNTest_592, ReturnsFalseForUnrelatedTokens_592) {
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string(".inf")));
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string("-.nan")));
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string("+.nan")));
  EXPECT_FALSE(YAML::conversion::IsNaN(std::string("nan()")));
}

}  // namespace