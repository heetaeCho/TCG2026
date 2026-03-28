#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

class ExpWordTest_124 : public ::testing::Test {
 protected:
  const RegEx& word_ = Exp::Word();
};

// Test that Word() returns a consistent reference (singleton pattern)
TEST_F(ExpWordTest_124, ReturnsSameReference_124) {
  const RegEx& ref1 = Exp::Word();
  const RegEx& ref2 = Exp::Word();
  EXPECT_EQ(&ref1, &ref2);
}

// Test that lowercase alphabetic characters match
TEST_F(ExpWordTest_124, MatchesLowercaseLetters_124) {
  for (char c = 'a'; c <= 'z'; ++c) {
    EXPECT_TRUE(word_.Matches(c)) << "Expected '" << c << "' to match";
  }
}

// Test that uppercase alphabetic characters match
TEST_F(ExpWordTest_124, MatchesUppercaseLetters_124) {
  for (char c = 'A'; c <= 'Z'; ++c) {
    EXPECT_TRUE(word_.Matches(c)) << "Expected '" << c << "' to match";
  }
}

// Test that digit characters match
TEST_F(ExpWordTest_124, MatchesDigits_124) {
  for (char c = '0'; c <= '9'; ++c) {
    EXPECT_TRUE(word_.Matches(c)) << "Expected '" << c << "' to match";
  }
}

// Test that hyphen matches
TEST_F(ExpWordTest_124, MatchesHyphen_124) {
  EXPECT_TRUE(word_.Matches('-'));
}

// Test that space does not match
TEST_F(ExpWordTest_124, DoesNotMatchSpace_124) {
  EXPECT_FALSE(word_.Matches(' '));
}

// Test that tab does not match
TEST_F(ExpWordTest_124, DoesNotMatchTab_124) {
  EXPECT_FALSE(word_.Matches('\t'));
}

// Test that newline does not match
TEST_F(ExpWordTest_124, DoesNotMatchNewline_124) {
  EXPECT_FALSE(word_.Matches('\n'));
}

// Test that various special characters do not match
TEST_F(ExpWordTest_124, DoesNotMatchSpecialCharacters_124) {
  const char specials[] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
                           '+', '=', '[', ']', '{', '}', '|', '\\', '/',
                           '?', '<', '>', ',', '.', ':', ';', '"', '\'',
                           '~', '`'};
  for (char c : specials) {
    EXPECT_FALSE(word_.Matches(c)) << "Expected '" << c << "' NOT to match";
  }
}

// Test that underscore does not match (Word is alphanumeric + hyphen only)
TEST_F(ExpWordTest_124, DoesNotMatchUnderscore_124) {
  EXPECT_FALSE(word_.Matches('_'));
}

// Test matching against a simple alphanumeric string
TEST_F(ExpWordTest_124, MatchesSingleCharString_124) {
  EXPECT_TRUE(word_.Matches(std::string("a")));
  EXPECT_TRUE(word_.Matches(std::string("Z")));
  EXPECT_TRUE(word_.Matches(std::string("5")));
  EXPECT_TRUE(word_.Matches(std::string("-")));
}

// Test that Match returns expected length for a single char string
TEST_F(ExpWordTest_124, MatchReturnsSingleCharLength_124) {
  EXPECT_EQ(1, word_.Match(std::string("a")));
  EXPECT_EQ(1, word_.Match(std::string("Z")));
  EXPECT_EQ(1, word_.Match(std::string("9")));
  EXPECT_EQ(1, word_.Match(std::string("-")));
}

// Test that Match returns -1 or 0 for non-matching strings
TEST_F(ExpWordTest_124, MatchReturnsNonPositiveForNonMatch_124) {
  int result = word_.Match(std::string("!"));
  EXPECT_LE(result, 0);
}

// Test null character does not match
TEST_F(ExpWordTest_124, DoesNotMatchNullChar_124) {
  EXPECT_FALSE(word_.Matches('\0'));
}

// Test that empty string does not match via Matches(string)
TEST_F(ExpWordTest_124, DoesNotMatchEmptyString_124) {
  EXPECT_FALSE(word_.Matches(std::string("")));
}

// Test Match on empty string
TEST_F(ExpWordTest_124, MatchEmptyStringReturnsNonPositive_124) {
  int result = word_.Match(std::string(""));
  EXPECT_LE(result, 0);
}

// Test boundary: character just before '0' (which is '/')
TEST_F(ExpWordTest_124, DoesNotMatchCharBeforeDigitZero_124) {
  EXPECT_FALSE(word_.Matches('/'));
}

// Test boundary: character just after '9' (which is ':')
TEST_F(ExpWordTest_124, DoesNotMatchCharAfterDigitNine_124) {
  EXPECT_FALSE(word_.Matches(':'));
}

// Test boundary: character just before 'A' (which is '@')
TEST_F(ExpWordTest_124, DoesNotMatchCharBeforeUpperA_124) {
  EXPECT_FALSE(word_.Matches('@'));
}

// Test boundary: character just after 'Z' (which is '[')
TEST_F(ExpWordTest_124, DoesNotMatchCharAfterUpperZ_124) {
  EXPECT_FALSE(word_.Matches('['));
}

// Test boundary: character just before 'a' (which is '`')
TEST_F(ExpWordTest_124, DoesNotMatchCharBeforeLowerA_124) {
  EXPECT_FALSE(word_.Matches('`'));
}

// Test boundary: character just after 'z' (which is '{')
TEST_F(ExpWordTest_124, DoesNotMatchCharAfterLowerZ_124) {
  EXPECT_FALSE(word_.Matches('{'));
}

}  // namespace
}  // namespace YAML
