#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test that Ampersand returns a RegEx that matches '&'
TEST(ExpAmpersandTest_137, MatchesAmpersandChar_137) {
  const RegEx& ampersand = Exp::Ampersand();
  EXPECT_TRUE(ampersand.Matches('&'));
}

// Test that Ampersand does not match other characters
TEST(ExpAmpersandTest_137, DoesNotMatchOtherChars_137) {
  const RegEx& ampersand = Exp::Ampersand();
  EXPECT_FALSE(ampersand.Matches('a'));
  EXPECT_FALSE(ampersand.Matches('!'));
  EXPECT_FALSE(ampersand.Matches(' '));
  EXPECT_FALSE(ampersand.Matches('\0'));
  EXPECT_FALSE(ampersand.Matches('#'));
  EXPECT_FALSE(ampersand.Matches('*'));
  EXPECT_FALSE(ampersand.Matches('\n'));
  EXPECT_FALSE(ampersand.Matches('\t'));
}

// Test that Ampersand matches a string consisting of just '&'
TEST(ExpAmpersandTest_137, MatchesAmpersandString_137) {
  const RegEx& ampersand = Exp::Ampersand();
  EXPECT_TRUE(ampersand.Matches(std::string("&")));
}

// Test that Ampersand does not match a string with different content
TEST(ExpAmpersandTest_137, DoesNotMatchDifferentString_137) {
  const RegEx& ampersand = Exp::Ampersand();
  EXPECT_FALSE(ampersand.Matches(std::string("a")));
  EXPECT_FALSE(ampersand.Matches(std::string("!")));
}

// Test that Ampersand Match returns 1 for a string starting with '&'
TEST(ExpAmpersandTest_137, MatchReturnsOneForAmpersandString_137) {
  const RegEx& ampersand = Exp::Ampersand();
  EXPECT_EQ(1, ampersand.Match(std::string("&")));
}

// Test that Ampersand Match returns 1 for a string starting with '&' followed by other chars
TEST(ExpAmpersandTest_137, MatchReturnsOneForAmpersandPrefix_137) {
  const RegEx& ampersand = Exp::Ampersand();
  EXPECT_EQ(1, ampersand.Match(std::string("&hello")));
}

// Test that Ampersand Match returns -1 for non-matching string
TEST(ExpAmpersandTest_137, MatchReturnsNegativeForNonMatch_137) {
  const RegEx& ampersand = Exp::Ampersand();
  EXPECT_EQ(-1, ampersand.Match(std::string("hello")));
}

// Test that Ampersand Match returns -1 for empty string
TEST(ExpAmpersandTest_137, MatchReturnsNegativeForEmptyString_137) {
  const RegEx& ampersand = Exp::Ampersand();
  EXPECT_EQ(-1, ampersand.Match(std::string("")));
}

// Test that Ampersand does not match empty string
TEST(ExpAmpersandTest_137, DoesNotMatchEmptyString_137) {
  const RegEx& ampersand = Exp::Ampersand();
  EXPECT_FALSE(ampersand.Matches(std::string("")));
}

// Test that Ampersand returns the same instance (static singleton)
TEST(ExpAmpersandTest_137, ReturnsSameInstance_137) {
  const RegEx& first = Exp::Ampersand();
  const RegEx& second = Exp::Ampersand();
  EXPECT_EQ(&first, &second);
}

// Test boundary: Ampersand does not match characters adjacent in ASCII to '&'
TEST(ExpAmpersandTest_137, DoesNotMatchAdjacentAsciiChars_137) {
  const RegEx& ampersand = Exp::Ampersand();
  // '&' is ASCII 38, so test 37 ('%') and 39 ('\'')
  EXPECT_FALSE(ampersand.Matches('%'));
  EXPECT_FALSE(ampersand.Matches('\''));
}

// Test that Ampersand does not match multi-character strings without leading '&'
TEST(ExpAmpersandTest_137, DoesNotMatchMultiCharStringWithoutAmpersand_137) {
  const RegEx& ampersand = Exp::Ampersand();
  EXPECT_FALSE(ampersand.Matches(std::string("ab")));
}

// Test that Ampersand does not match string "&&" (Matches checks exact single-char match for string)
TEST(ExpAmpersandTest_137, DoesNotMatchDoubleAmpersandString_137) {
  const RegEx& ampersand = Exp::Ampersand();
  // Matches for string checks if the entire string matches, which for a single char regex should be length 1
  EXPECT_FALSE(ampersand.Matches(std::string("&&")));
}

}  // namespace
}  // namespace YAML
