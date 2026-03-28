#include <gtest/gtest.h>
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

class ChompIndicatorTest_151 : public ::testing::Test {
 protected:
  const RegEx& chomp_ = Exp::ChompIndicator();
};

// Test that ChompIndicator matches '+' character
TEST_F(ChompIndicatorTest_151, MatchesPlus_151) {
  EXPECT_TRUE(chomp_.Matches('+'));
}

// Test that ChompIndicator matches '-' character
TEST_F(ChompIndicatorTest_151, MatchesMinus_151) {
  EXPECT_TRUE(chomp_.Matches('-'));
}

// Test that ChompIndicator does not match other characters
TEST_F(ChompIndicatorTest_151, DoesNotMatchOtherChar_151) {
  EXPECT_FALSE(chomp_.Matches('a'));
}

TEST_F(ChompIndicatorTest_151, DoesNotMatchDigit_151) {
  EXPECT_FALSE(chomp_.Matches('0'));
}

TEST_F(ChompIndicatorTest_151, DoesNotMatchSpace_151) {
  EXPECT_FALSE(chomp_.Matches(' '));
}

TEST_F(ChompIndicatorTest_151, DoesNotMatchNewline_151) {
  EXPECT_FALSE(chomp_.Matches('\n'));
}

TEST_F(ChompIndicatorTest_151, DoesNotMatchNull_151) {
  EXPECT_FALSE(chomp_.Matches('\0'));
}

// Test that ChompIndicator matches string "+"
TEST_F(ChompIndicatorTest_151, MatchesPlusString_151) {
  EXPECT_TRUE(chomp_.Matches(std::string("+")));
}

// Test that ChompIndicator matches string "-"
TEST_F(ChompIndicatorTest_151, MatchesMinusString_151) {
  EXPECT_TRUE(chomp_.Matches(std::string("-")));
}

// Test that ChompIndicator does not match empty string
TEST_F(ChompIndicatorTest_151, DoesNotMatchEmptyString_151) {
  EXPECT_FALSE(chomp_.Matches(std::string("")));
}

// Test that ChompIndicator does not match a non-chomp string
TEST_F(ChompIndicatorTest_151, DoesNotMatchArbitraryString_151) {
  EXPECT_FALSE(chomp_.Matches(std::string("x")));
}

// Test Match returns 1 for "+"
TEST_F(ChompIndicatorTest_151, MatchReturnOneForPlus_151) {
  EXPECT_EQ(1, chomp_.Match(std::string("+")));
}

// Test Match returns 1 for "-"
TEST_F(ChompIndicatorTest_151, MatchReturnOneForMinus_151) {
  EXPECT_EQ(1, chomp_.Match(std::string("-")));
}

// Test Match returns -1 for non-matching string
TEST_F(ChompIndicatorTest_151, MatchReturnNegativeForNonMatch_151) {
  EXPECT_EQ(-1, chomp_.Match(std::string("x")));
}

// Test Match returns -1 for empty string
TEST_F(ChompIndicatorTest_151, MatchReturnNegativeForEmptyString_151) {
  EXPECT_EQ(-1, chomp_.Match(std::string("")));
}

// Test that ChompIndicator returns the same reference on repeated calls (singleton)
TEST_F(ChompIndicatorTest_151, ReturnsSameReference_151) {
  const RegEx& first = Exp::ChompIndicator();
  const RegEx& second = Exp::ChompIndicator();
  EXPECT_EQ(&first, &second);
}

// Test Match with string starting with '+' followed by more characters
TEST_F(ChompIndicatorTest_151, MatchReturnOneForPlusPrefix_151) {
  // OR regex should match just the first character
  EXPECT_EQ(1, chomp_.Match(std::string("+abc")));
}

// Test Match with string starting with '-' followed by more characters
TEST_F(ChompIndicatorTest_151, MatchReturnOneForMinusPrefix_151) {
  EXPECT_EQ(1, chomp_.Match(std::string("-abc")));
}

// Test that various special characters don't match
TEST_F(ChompIndicatorTest_151, DoesNotMatchExclamation_151) {
  EXPECT_FALSE(chomp_.Matches('!'));
}

TEST_F(ChompIndicatorTest_151, DoesNotMatchEquals_151) {
  EXPECT_FALSE(chomp_.Matches('='));
}

TEST_F(ChompIndicatorTest_151, DoesNotMatchAsterisk_151) {
  EXPECT_FALSE(chomp_.Matches('*'));
}

TEST_F(ChompIndicatorTest_151, DoesNotMatchSlash_151) {
  EXPECT_FALSE(chomp_.Matches('/'));
}

// Boundary: characters adjacent to '+' and '-' in ASCII
TEST_F(ChompIndicatorTest_151, DoesNotMatchComma_151) {
  // ',' is ASCII 44, '-' is 45
  EXPECT_FALSE(chomp_.Matches(','));
}

TEST_F(ChompIndicatorTest_151, DoesNotMatchPeriod_151) {
  // '.' is ASCII 46, '-' is 45
  EXPECT_FALSE(chomp_.Matches('.'));
}

TEST_F(ChompIndicatorTest_151, DoesNotMatchAsteriskBeforePlus_151) {
  // '*' is ASCII 42, '+' is 43
  EXPECT_FALSE(chomp_.Matches('*'));
}

}  // namespace
}  // namespace YAML
