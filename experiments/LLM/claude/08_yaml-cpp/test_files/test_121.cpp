#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test fixture for Exp::Digit tests
class ExpDigitTest_121 : public ::testing::Test {
 protected:
  const RegEx& digit = Exp::Digit();
};

// Normal operation: Digit matches '0'
TEST_F(ExpDigitTest_121, MatchesZero_121) {
  EXPECT_TRUE(digit.Matches('0'));
}

// Normal operation: Digit matches '9'
TEST_F(ExpDigitTest_121, MatchesNine_121) {
  EXPECT_TRUE(digit.Matches('9'));
}

// Normal operation: Digit matches '5' (middle of range)
TEST_F(ExpDigitTest_121, MatchesFive_121) {
  EXPECT_TRUE(digit.Matches('5'));
}

// Normal operation: Digit matches '1'
TEST_F(ExpDigitTest_121, MatchesOne_121) {
  EXPECT_TRUE(digit.Matches('1'));
}

// Normal operation: Digit matches all digits 0-9
TEST_F(ExpDigitTest_121, MatchesAllDigits_121) {
  for (char ch = '0'; ch <= '9'; ++ch) {
    EXPECT_TRUE(digit.Matches(ch)) << "Failed for character: " << ch;
  }
}

// Boundary: Character just before '0' should not match
TEST_F(ExpDigitTest_121, DoesNotMatchCharBeforeZero_121) {
  EXPECT_FALSE(digit.Matches(static_cast<char>('0' - 1)));
}

// Boundary: Character just after '9' should not match
TEST_F(ExpDigitTest_121, DoesNotMatchCharAfterNine_121) {
  EXPECT_FALSE(digit.Matches(static_cast<char>('9' + 1)));
}

// Error/exceptional: Digit does not match 'a'
TEST_F(ExpDigitTest_121, DoesNotMatchLowercaseA_121) {
  EXPECT_FALSE(digit.Matches('a'));
}

// Error/exceptional: Digit does not match 'Z'
TEST_F(ExpDigitTest_121, DoesNotMatchUppercaseZ_121) {
  EXPECT_FALSE(digit.Matches('Z'));
}

// Error/exceptional: Digit does not match space
TEST_F(ExpDigitTest_121, DoesNotMatchSpace_121) {
  EXPECT_FALSE(digit.Matches(' '));
}

// Error/exceptional: Digit does not match null character
TEST_F(ExpDigitTest_121, DoesNotMatchNullChar_121) {
  EXPECT_FALSE(digit.Matches('\0'));
}

// Error/exceptional: Digit does not match newline
TEST_F(ExpDigitTest_121, DoesNotMatchNewline_121) {
  EXPECT_FALSE(digit.Matches('\n'));
}

// Error/exceptional: Digit does not match '-'
TEST_F(ExpDigitTest_121, DoesNotMatchDash_121) {
  EXPECT_FALSE(digit.Matches('-'));
}

// Error/exceptional: Digit does not match '.'
TEST_F(ExpDigitTest_121, DoesNotMatchDot_121) {
  EXPECT_FALSE(digit.Matches('.'));
}

// Normal operation: String match with single digit
TEST_F(ExpDigitTest_121, MatchesSingleDigitString_121) {
  EXPECT_TRUE(digit.Matches(std::string("5")));
}

// Normal operation: String match returns correct length for single digit
TEST_F(ExpDigitTest_121, MatchSingleDigitStringReturnsOne_121) {
  EXPECT_EQ(1, digit.Match(std::string("5")));
}

// Boundary: String match with digit followed by other chars
TEST_F(ExpDigitTest_121, MatchDigitStringWithTrailingChars_121) {
  // Match should return 1 (matches only the first character for a range regex)
  EXPECT_EQ(1, digit.Match(std::string("5abc")));
}

// Error/exceptional: String match with non-digit returns -1 (no match)
TEST_F(ExpDigitTest_121, MatchNonDigitStringReturnsNegative_121) {
  EXPECT_EQ(-1, digit.Match(std::string("abc")));
}

// Error/exceptional: Empty string match
TEST_F(ExpDigitTest_121, MatchEmptyStringReturnsNegative_121) {
  EXPECT_EQ(-1, digit.Match(std::string("")));
}

// Verify Digit() returns the same instance (singleton)
TEST_F(ExpDigitTest_121, ReturnsSameInstance_121) {
  const RegEx& digit1 = Exp::Digit();
  const RegEx& digit2 = Exp::Digit();
  EXPECT_EQ(&digit1, &digit2);
}

// Normal operation: Matches does not match non-digit characters comprehensively
TEST_F(ExpDigitTest_121, DoesNotMatchAlphabeticChars_121) {
  for (char ch = 'a'; ch <= 'z'; ++ch) {
    EXPECT_FALSE(digit.Matches(ch)) << "Should not match: " << ch;
  }
  for (char ch = 'A'; ch <= 'Z'; ++ch) {
    EXPECT_FALSE(digit.Matches(ch)) << "Should not match: " << ch;
  }
}

// Boundary: Does not match special characters
TEST_F(ExpDigitTest_121, DoesNotMatchSpecialChars_121) {
  const char specials[] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
                           '+', '=', '{', '}', '[', ']', '|', '\\', '/',
                           '?', '<', '>', ',', ';', ':', '\'', '"', '`', '~'};
  for (char ch : specials) {
    EXPECT_FALSE(digit.Matches(ch)) << "Should not match: " << ch;
  }
}

// Normal: Matches string "0"
TEST_F(ExpDigitTest_121, MatchesStringZero_121) {
  EXPECT_TRUE(digit.Matches(std::string("0")));
}

// Normal: Matches string "9"
TEST_F(ExpDigitTest_121, MatchesStringNine_121) {
  EXPECT_TRUE(digit.Matches(std::string("9")));
}

// Error: Does not match multi-char non-digit string
TEST_F(ExpDigitTest_121, DoesNotMatchNonDigitString_121) {
  EXPECT_FALSE(digit.Matches(std::string("a")));
}

}  // namespace
}  // namespace YAML
