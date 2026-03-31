#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

class ChompTest_152 : public ::testing::Test {
 protected:
  const RegEx& chomp = Exp::Chomp();
};

// Test that Chomp regex matches a valid chomp indicator '-'
TEST_F(ChompTest_152, MatchesMinusChompIndicator_152) {
  EXPECT_TRUE(chomp.Matches(std::string("-")));
}

// Test that Chomp regex matches a valid chomp indicator '+'
TEST_F(ChompTest_152, MatchesPlusChompIndicator_152) {
  EXPECT_TRUE(chomp.Matches(std::string("+")));
}

// Test that Chomp regex matches a single digit
TEST_F(ChompTest_152, MatchesSingleDigit_152) {
  EXPECT_TRUE(chomp.Matches(std::string("1")));
}

// Test that Chomp regex matches digit 9
TEST_F(ChompTest_152, MatchesDigitNine_152) {
  EXPECT_TRUE(chomp.Matches(std::string("9")));
}

// Test that Chomp regex matches chomp indicator followed by digit
TEST_F(ChompTest_152, MatchesChompThenDigit_152) {
  int result = chomp.Match(std::string("-1"));
  EXPECT_EQ(result, 2);
}

// Test that Chomp regex matches digit followed by chomp indicator
TEST_F(ChompTest_152, MatchesDigitThenChomp_152) {
  int result = chomp.Match(std::string("1-"));
  EXPECT_EQ(result, 2);
}

// Test that Chomp regex matches plus chomp followed by digit
TEST_F(ChompTest_152, MatchesPlusChompThenDigit_152) {
  int result = chomp.Match(std::string("+3"));
  EXPECT_EQ(result, 2);
}

// Test that Chomp regex matches digit followed by plus chomp
TEST_F(ChompTest_152, MatchesDigitThenPlusChomp_152) {
  int result = chomp.Match(std::string("3+")));
  EXPECT_EQ(result, 2);
}

// Test that Chomp regex does not match an empty string
TEST_F(ChompTest_152, DoesNotMatchEmptyString_152) {
  EXPECT_FALSE(chomp.Matches(std::string("")));
}

// Test that Chomp regex does not match an arbitrary letter
TEST_F(ChompTest_152, DoesNotMatchArbitraryLetter_152) {
  EXPECT_FALSE(chomp.Matches(std::string("a")));
}

// Test that Chomp regex does not match a space
TEST_F(ChompTest_152, DoesNotMatchSpace_152) {
  EXPECT_FALSE(chomp.Matches(std::string(" ")));
}

// Test that Chomp regex does not match zero (digit 0 is typically not valid in YAML indentation digit)
TEST_F(ChompTest_152, MatchOrNotMatchDigitZero_152) {
  // Digit in YAML block scalar headers is [1-9], not 0
  // We test observable behavior
  int result = chomp.Match(std::string("0"));
  // If 0 is not a valid digit, result should be -1 or 0
  // If 0 is a valid digit, result should be 1
  // We just record the behavior
  if (result > 0) {
    EXPECT_EQ(result, 1);
  } else {
    EXPECT_LE(result, 0);
  }
}

// Test that Chomp returns the same object on repeated calls (singleton)
TEST_F(ChompTest_152, ReturnsSameReference_152) {
  const RegEx& chomp1 = Exp::Chomp();
  const RegEx& chomp2 = Exp::Chomp();
  EXPECT_EQ(&chomp1, &chomp2);
}

// Test Match returns correct length for single chomp indicator '-'
TEST_F(ChompTest_152, MatchLengthForMinus_152) {
  int result = chomp.Match(std::string("-"));
  EXPECT_EQ(result, 1);
}

// Test Match returns correct length for single chomp indicator '+'
TEST_F(ChompTest_152, MatchLengthForPlus_152) {
  int result = chomp.Match(std::string("+"));
  EXPECT_EQ(result, 1);
}

// Test Match returns correct length for single digit
TEST_F(ChompTest_152, MatchLengthForDigit_152) {
  int result = chomp.Match(std::string("5"));
  EXPECT_EQ(result, 1);
}

// Test that Chomp with chomp+digit on longer string only matches first 2 chars
TEST_F(ChompTest_152, MatchLengthForChompDigitWithTrailing_152) {
  int result = chomp.Match(std::string("-1abc"));
  EXPECT_EQ(result, 2);
}

// Test that Chomp does not match two digits
TEST_F(ChompTest_152, DoesNotMatchTwoDigits_152) {
  // Two digits would not be a valid chomp expression
  // The match should return 1 (only first digit matched) not 2
  int result = chomp.Match(std::string("12"));
  EXPECT_EQ(result, 1);
}

// Test all digits 1-9
TEST_F(ChompTest_152, MatchesAllDigitsOneToNine_152) {
  for (char c = '1'; c <= '9'; ++c) {
    std::string s(1, c);
    EXPECT_TRUE(chomp.Matches(s)) << "Failed for digit: " << c;
  }
}

// Test Matches with char overload for '-'
TEST_F(ChompTest_152, MatchesCharMinus_152) {
  EXPECT_TRUE(chomp.Matches('-'));
}

// Test Matches with char overload for '+'
TEST_F(ChompTest_152, MatchesCharPlus_152) {
  EXPECT_TRUE(chomp.Matches('+'));
}

// Test Matches with char overload for digit
TEST_F(ChompTest_152, MatchesCharDigit_152) {
  EXPECT_TRUE(chomp.Matches('5'));
}

// Test Matches with char overload for non-matching char
TEST_F(ChompTest_152, DoesNotMatchCharLetter_152) {
  EXPECT_FALSE(chomp.Matches('a'));
}

// Test that special characters don't match
TEST_F(ChompTest_152, DoesNotMatchSpecialChars_152) {
  EXPECT_FALSE(chomp.Matches('*'));
  EXPECT_FALSE(chomp.Matches('#'));
  EXPECT_FALSE(chomp.Matches('\n'));
  EXPECT_FALSE(chomp.Matches('\t'));
}

}  // namespace
}  // namespace YAML
#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

class ChompTest_152 : public ::testing::Test {
 protected:
  const RegEx& chomp = Exp::Chomp();
};

// Test that Chomp regex matches a valid chomp indicator '-'
TEST_F(ChompTest_152, MatchesMinusChompIndicator_152) {
  EXPECT_TRUE(chomp.Matches(std::string("-")));
}

// Test that Chomp regex matches a valid chomp indicator '+'
TEST_F(ChompTest_152, MatchesPlusChompIndicator_152) {
  EXPECT_TRUE(chomp.Matches(std::string("+")));
}

// Test that Chomp regex matches a single digit
TEST_F(ChompTest_152, MatchesSingleDigit_152) {
  EXPECT_TRUE(chomp.Matches(std::string("1")));
}

// Test that Chomp regex matches digit 9
TEST_F(ChompTest_152, MatchesDigitNine_152) {
  EXPECT_TRUE(chomp.Matches(std::string("9")));
}

// Test that Chomp regex matches chomp indicator followed by digit
TEST_F(ChompTest_152, MatchesChompThenDigit_152) {
  int result = chomp.Match(std::string("-1"));
  EXPECT_EQ(result, 2);
}

// Test that Chomp regex matches digit followed by chomp indicator
TEST_F(ChompTest_152, MatchesDigitThenChomp_152) {
  int result = chomp.Match(std::string("1-"));
  EXPECT_EQ(result, 2);
}

// Test that Chomp regex matches plus chomp followed by digit
TEST_F(ChompTest_152, MatchesPlusChompThenDigit_152) {
  int result = chomp.Match(std::string("+3"));
  EXPECT_EQ(result, 2);
}

// Test that Chomp regex matches digit followed by plus chomp
TEST_F(ChompTest_152, MatchesDigitThenPlusChomp_152) {
  int result = chomp.Match(std::string("3+"));
  EXPECT_EQ(result, 2);
}

// Test that Chomp regex does not match an empty string
TEST_F(ChompTest_152, DoesNotMatchEmptyString_152) {
  EXPECT_FALSE(chomp.Matches(std::string("")));
}

// Test that Chomp regex does not match an arbitrary letter
TEST_F(ChompTest_152, DoesNotMatchArbitraryLetter_152) {
  EXPECT_FALSE(chomp.Matches(std::string("a")));
}

// Test that Chomp regex does not match a space
TEST_F(ChompTest_152, DoesNotMatchSpace_152) {
  EXPECT_FALSE(chomp.Matches(std::string(" ")));
}

// Test that Chomp returns the same object on repeated calls (singleton)
TEST_F(ChompTest_152, ReturnsSameReference_152) {
  const RegEx& chomp1 = Exp::Chomp();
  const RegEx& chomp2 = Exp::Chomp();
  EXPECT_EQ(&chomp1, &chomp2);
}

// Test Match returns correct length for single chomp indicator '-'
TEST_F(ChompTest_152, MatchLengthForMinus_152) {
  int result = chomp.Match(std::string("-"));
  EXPECT_EQ(result, 1);
}

// Test Match returns correct length for single chomp indicator '+'
TEST_F(ChompTest_152, MatchLengthForPlus_152) {
  int result = chomp.Match(std::string("+"));
  EXPECT_EQ(result, 1);
}

// Test Match returns correct length for single digit
TEST_F(ChompTest_152, MatchLengthForDigit_152) {
  int result = chomp.Match(std::string("5"));
  EXPECT_EQ(result, 1);
}

// Test that Chomp with chomp+digit on longer string only matches first 2 chars
TEST_F(ChompTest_152, MatchLengthForChompDigitWithTrailing_152) {
  int result = chomp.Match(std::string("-1abc"));
  EXPECT_EQ(result, 2);
}

// Test that Chomp does not match two digits as length 2
TEST_F(ChompTest_152, TwoDigitsMatchesOnlyFirst_152) {
  int result = chomp.Match(std::string("12"));
  EXPECT_EQ(result, 1);
}

// Test all digits 1-9
TEST_F(ChompTest_152, MatchesAllDigitsOneToNine_152) {
  for (char c = '1'; c <= '9'; ++c) {
    std::string s(1, c);
    EXPECT_TRUE(chomp.Matches(s)) << "Failed for digit: " << c;
  }
}

// Test Matches with char overload for '-'
TEST_F(ChompTest_152, MatchesCharMinus_152) {
  EXPECT_TRUE(chomp.Matches('-'));
}

// Test Matches with char overload for '+'
TEST_F(ChompTest_152, MatchesCharPlus_152) {
  EXPECT_TRUE(chomp.Matches('+'));
}

// Test Matches with char overload for digit
TEST_F(ChompTest_152, MatchesCharDigit_152) {
  EXPECT_TRUE(chomp.Matches('5'));
}

// Test Matches with char overload for non-matching char
TEST_F(ChompTest_152, DoesNotMatchCharLetter_152) {
  EXPECT_FALSE(chomp.Matches('a'));
}

// Test that special characters don't match
TEST_F(ChompTest_152, DoesNotMatchSpecialChars_152) {
  EXPECT_FALSE(chomp.Matches('*'));
  EXPECT_FALSE(chomp.Matches('#'));
  EXPECT_FALSE(chomp.Matches('\n'));
  EXPECT_FALSE(chomp.Matches('\t'));
}

// Test that match on non-matching string returns -1
TEST_F(ChompTest_152, MatchReturnsNegativeForNonMatch_152) {
  int result = chomp.Match(std::string("abc"));
  EXPECT_EQ(result, -1);
}

// Test two chomp indicators without digit
TEST_F(ChompTest_152, TwoChompIndicatorsMatchesOnlyFirst_152) {
  int result = chomp.Match(std::string("+-"));
  EXPECT_EQ(result, 1);
}

}  // namespace
}  // namespace YAML
