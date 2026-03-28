#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test that Alpha() returns a consistent reference (singleton pattern)
TEST(ExpAlphaTest_122, ReturnsSameReference_122) {
  const RegEx& ref1 = Exp::Alpha();
  const RegEx& ref2 = Exp::Alpha();
  EXPECT_EQ(&ref1, &ref2);
}

// Test that Alpha matches lowercase letters
TEST(ExpAlphaTest_122, MatchesLowercaseLetters_122) {
  const RegEx& alpha = Exp::Alpha();
  for (char ch = 'a'; ch <= 'z'; ++ch) {
    EXPECT_TRUE(alpha.Matches(ch)) << "Expected Alpha to match '" << ch << "'";
  }
}

// Test that Alpha matches uppercase letters
TEST(ExpAlphaTest_122, MatchesUppercaseLetters_122) {
  const RegEx& alpha = Exp::Alpha();
  for (char ch = 'A'; ch <= 'Z'; ++ch) {
    EXPECT_TRUE(alpha.Matches(ch)) << "Expected Alpha to match '" << ch << "'";
  }
}

// Test that Alpha does not match digits
TEST(ExpAlphaTest_122, DoesNotMatchDigits_122) {
  const RegEx& alpha = Exp::Alpha();
  for (char ch = '0'; ch <= '9'; ++ch) {
    EXPECT_FALSE(alpha.Matches(ch)) << "Expected Alpha NOT to match '" << ch << "'";
  }
}

// Test that Alpha does not match special characters
TEST(ExpAlphaTest_122, DoesNotMatchSpecialCharacters_122) {
  const RegEx& alpha = Exp::Alpha();
  const std::string specials = "!@#$%^&*()_+-=[]{}|;':\",./<>?`~ \t\n\r";
  for (char ch : specials) {
    EXPECT_FALSE(alpha.Matches(ch)) << "Expected Alpha NOT to match '" << ch << "'";
  }
}

// Test boundary: characters just before and after lowercase range
TEST(ExpAlphaTest_122, BoundaryAroundLowercaseRange_122) {
  const RegEx& alpha = Exp::Alpha();
  // 'a' - 1 = '`', 'z' + 1 = '{'
  EXPECT_FALSE(alpha.Matches('`')) << "Character before 'a' should not match";
  EXPECT_FALSE(alpha.Matches('{')) << "Character after 'z' should not match";
  EXPECT_TRUE(alpha.Matches('a')) << "'a' should match";
  EXPECT_TRUE(alpha.Matches('z')) << "'z' should match";
}

// Test boundary: characters just before and after uppercase range
TEST(ExpAlphaTest_122, BoundaryAroundUppercaseRange_122) {
  const RegEx& alpha = Exp::Alpha();
  // 'A' - 1 = '@', 'Z' + 1 = '['
  EXPECT_FALSE(alpha.Matches('@')) << "Character before 'A' should not match";
  EXPECT_FALSE(alpha.Matches('[')) << "Character after 'Z' should not match";
  EXPECT_TRUE(alpha.Matches('A')) << "'A' should match";
  EXPECT_TRUE(alpha.Matches('Z')) << "'Z' should match";
}

// Test that Alpha does not match null character
TEST(ExpAlphaTest_122, DoesNotMatchNullCharacter_122) {
  const RegEx& alpha = Exp::Alpha();
  EXPECT_FALSE(alpha.Matches('\0'));
}

// Test matching single-character strings
TEST(ExpAlphaTest_122, MatchesSingleCharAlphaString_122) {
  const RegEx& alpha = Exp::Alpha();
  EXPECT_EQ(1, alpha.Match(std::string("a")));
  EXPECT_EQ(1, alpha.Match(std::string("Z")));
}

// Test that Match returns appropriate value for non-alpha single char string
TEST(ExpAlphaTest_122, MatchReturnsNegativeForNonAlphaString_122) {
  const RegEx& alpha = Exp::Alpha();
  int result = alpha.Match(std::string("1"));
  // Non-match should return -1 or 0 depending on implementation
  EXPECT_LE(result, 0) << "Non-alpha string should not match positively";
}

// Test matching with empty string
TEST(ExpAlphaTest_122, MatchWithEmptyString_122) {
  const RegEx& alpha = Exp::Alpha();
  int result = alpha.Match(std::string(""));
  EXPECT_LE(result, 0) << "Empty string should not match Alpha";
}

// Test Matches with single-character strings
TEST(ExpAlphaTest_122, MatchesSingleCharStringTrue_122) {
  const RegEx& alpha = Exp::Alpha();
  EXPECT_TRUE(alpha.Matches(std::string("b")));
  EXPECT_TRUE(alpha.Matches(std::string("M")));
}

// Test Matches with non-alpha single-character strings
TEST(ExpAlphaTest_122, MatchesSingleCharStringFalse_122) {
  const RegEx& alpha = Exp::Alpha();
  EXPECT_FALSE(alpha.Matches(std::string("5")));
  EXPECT_FALSE(alpha.Matches(std::string(" ")));
}

// Test that Match on a multi-character string starting with alpha returns 1
TEST(ExpAlphaTest_122, MatchMultiCharStringStartingWithAlpha_122) {
  const RegEx& alpha = Exp::Alpha();
  int result = alpha.Match(std::string("abc"));
  // Alpha regex matches a single character, so it should match 1 character
  EXPECT_EQ(1, result);
}

// Test all characters in range 0-127 for completeness
TEST(ExpAlphaTest_122, FullASCIIRangeCheck_122) {
  const RegEx& alpha = Exp::Alpha();
  for (int i = 1; i < 128; ++i) {  // skip null
    char ch = static_cast<char>(i);
    bool expected = (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    EXPECT_EQ(expected, alpha.Matches(ch))
        << "Mismatch for character code " << i << " ('" << ch << "')";
  }
}

}  // namespace
}  // namespace YAML
