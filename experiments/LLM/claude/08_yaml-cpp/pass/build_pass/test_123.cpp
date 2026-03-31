#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

class AlphaNumericTest_123 : public ::testing::Test {
 protected:
  const RegEx& alphaNumeric = Exp::AlphaNumeric();
};

// Test that lowercase letters match
TEST_F(AlphaNumericTest_123, MatchesLowercaseLetters_123) {
  for (char ch = 'a'; ch <= 'z'; ++ch) {
    EXPECT_TRUE(alphaNumeric.Matches(ch)) << "Failed for char: " << ch;
  }
}

// Test that uppercase letters match
TEST_F(AlphaNumericTest_123, MatchesUppercaseLetters_123) {
  for (char ch = 'A'; ch <= 'Z'; ++ch) {
    EXPECT_TRUE(alphaNumeric.Matches(ch)) << "Failed for char: " << ch;
  }
}

// Test that digits match
TEST_F(AlphaNumericTest_123, MatchesDigits_123) {
  for (char ch = '0'; ch <= '9'; ++ch) {
    EXPECT_TRUE(alphaNumeric.Matches(ch)) << "Failed for char: " << ch;
  }
}

// Test that special characters do not match
TEST_F(AlphaNumericTest_123, DoesNotMatchSpecialCharacters_123) {
  const std::string specials = "!@#$%^&*()-_=+[]{}|;:',.<>?/`~ \t\n";
  for (char ch : specials) {
    EXPECT_FALSE(alphaNumeric.Matches(ch)) << "Should not match char: " << ch
                                           << " (int: " << static_cast<int>(ch) << ")";
  }
}

// Test boundary: character just before '0'
TEST_F(AlphaNumericTest_123, DoesNotMatchCharBeforeDigitZero_123) {
  char ch = '0' - 1;  // '/'
  EXPECT_FALSE(alphaNumeric.Matches(ch));
}

// Test boundary: character just after '9'
TEST_F(AlphaNumericTest_123, DoesNotMatchCharAfterDigitNine_123) {
  char ch = '9' + 1;  // ':'
  EXPECT_FALSE(alphaNumeric.Matches(ch));
}

// Test boundary: character just before 'A'
TEST_F(AlphaNumericTest_123, DoesNotMatchCharBeforeUpperA_123) {
  char ch = 'A' - 1;  // '@'
  EXPECT_FALSE(alphaNumeric.Matches(ch));
}

// Test boundary: character just after 'Z'
TEST_F(AlphaNumericTest_123, DoesNotMatchCharAfterUpperZ_123) {
  char ch = 'Z' + 1;  // '['
  EXPECT_FALSE(alphaNumeric.Matches(ch));
}

// Test boundary: character just before 'a'
TEST_F(AlphaNumericTest_123, DoesNotMatchCharBeforeLowerA_123) {
  char ch = 'a' - 1;  // '`'
  EXPECT_FALSE(alphaNumeric.Matches(ch));
}

// Test boundary: character just after 'z'
TEST_F(AlphaNumericTest_123, DoesNotMatchCharAfterLowerZ_123) {
  char ch = 'z' + 1;  // '{'
  EXPECT_FALSE(alphaNumeric.Matches(ch));
}

// Test that the returned reference is always the same (singleton pattern)
TEST_F(AlphaNumericTest_123, ReturnsSameReference_123) {
  const RegEx& ref1 = Exp::AlphaNumeric();
  const RegEx& ref2 = Exp::AlphaNumeric();
  EXPECT_EQ(&ref1, &ref2);
}

// Test string matching with a single alphanumeric character
TEST_F(AlphaNumericTest_123, MatchesSingleCharAlphaString_123) {
  EXPECT_TRUE(alphaNumeric.Matches(std::string("a")));
  EXPECT_TRUE(alphaNumeric.Matches(std::string("Z")));
  EXPECT_TRUE(alphaNumeric.Matches(std::string("5")));
}

// Test string matching with a non-alphanumeric single character
TEST_F(AlphaNumericTest_123, DoesNotMatchSingleCharNonAlphaString_123) {
  EXPECT_FALSE(alphaNumeric.Matches(std::string("!")));
  EXPECT_FALSE(alphaNumeric.Matches(std::string(" ")));
}

// Test Match function returns expected length for single alphanumeric character string
TEST_F(AlphaNumericTest_123, MatchReturnOneForAlphanumericString_123) {
  EXPECT_EQ(1, alphaNumeric.Match(std::string("a")));
  EXPECT_EQ(1, alphaNumeric.Match(std::string("Z")));
  EXPECT_EQ(1, alphaNumeric.Match(std::string("7")));
}

// Test Match function for non-matching string
TEST_F(AlphaNumericTest_123, MatchReturnsNegativeForNonAlphanumericString_123) {
  int result = alphaNumeric.Match(std::string("!"));
  EXPECT_EQ(-1, result);
}

// Test empty string does not match
TEST_F(AlphaNumericTest_123, DoesNotMatchEmptyString_123) {
  EXPECT_FALSE(alphaNumeric.Matches(std::string("")));
}

// Test Match returns -1 for empty string
TEST_F(AlphaNumericTest_123, MatchReturnsNegativeForEmptyString_123) {
  int result = alphaNumeric.Match(std::string(""));
  EXPECT_EQ(-1, result);
}

// Test that null character does not match
TEST_F(AlphaNumericTest_123, DoesNotMatchNullChar_123) {
  EXPECT_FALSE(alphaNumeric.Matches('\0'));
}

// Test Match on a multi-character string (only first char should be considered for single regex)
TEST_F(AlphaNumericTest_123, MatchOnMultiCharString_123) {
  int result = alphaNumeric.Match(std::string("abc"));
  // AlphaNumeric matches a single character, so should match 1 character
  EXPECT_EQ(1, result);
}

// Test that the regex matches the first boundary characters of each range
TEST_F(AlphaNumericTest_123, MatchesBoundaryFirstChars_123) {
  EXPECT_TRUE(alphaNumeric.Matches('a'));
  EXPECT_TRUE(alphaNumeric.Matches('z'));
  EXPECT_TRUE(alphaNumeric.Matches('A'));
  EXPECT_TRUE(alphaNumeric.Matches('Z'));
  EXPECT_TRUE(alphaNumeric.Matches('0'));
  EXPECT_TRUE(alphaNumeric.Matches('9'));
}

}  // namespace
}  // namespace YAML
