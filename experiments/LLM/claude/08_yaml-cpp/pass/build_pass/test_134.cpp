#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test that Value() returns a valid RegEx object (doesn't crash)
TEST(ExpValueTest_134, ReturnsValidRegEx_134) {
  const RegEx& value = Exp::Value();
  // Just verifying it doesn't crash and returns a reference
  (void)value;
}

// Test that Value() returns the same object each time (static)
TEST(ExpValueTest_134, ReturnsSameStaticInstance_134) {
  const RegEx& value1 = Exp::Value();
  const RegEx& value2 = Exp::Value();
  EXPECT_EQ(&value1, &value2);
}

// Test that Value() matches a colon followed by a space
TEST(ExpValueTest_134, MatchesColonFollowedBySpace_134) {
  const RegEx& value = Exp::Value();
  std::string input = ": ";
  int matchLen = value.Match(input);
  EXPECT_GT(matchLen, 0);
}

// Test that Value() matches a colon followed by a newline
TEST(ExpValueTest_134, MatchesColonFollowedByNewline_134) {
  const RegEx& value = Exp::Value();
  std::string input = ":\n";
  int matchLen = value.Match(input);
  EXPECT_GT(matchLen, 0);
}

// Test that Value() matches a colon followed by a tab
TEST(ExpValueTest_134, MatchesColonFollowedByTab_134) {
  const RegEx& value = Exp::Value();
  std::string input = ":\t";
  int matchLen = value.Match(input);
  EXPECT_GT(matchLen, 0);
}

// Test that Value() matches a colon at end of string (empty after colon)
TEST(ExpValueTest_134, MatchesColonAtEndOfString_134) {
  const RegEx& value = Exp::Value();
  std::string input = ":";
  int matchLen = value.Match(input);
  // The regex is ':' + (BlankOrBreak() | RegEx())
  // RegEx() is REGEX_EMPTY which matches empty, so colon alone should match
  EXPECT_GT(matchLen, 0);
}

// Test that Value() does not match a string not starting with colon
TEST(ExpValueTest_134, DoesNotMatchNonColon_134) {
  const RegEx& value = Exp::Value();
  std::string input = "abc";
  int matchLen = value.Match(input);
  EXPECT_LE(matchLen, 0);
}

// Test that Value() does not match an empty string
TEST(ExpValueTest_134, DoesNotMatchEmptyString_134) {
  const RegEx& value = Exp::Value();
  std::string input = "";
  int matchLen = value.Match(input);
  EXPECT_LE(matchLen, 0);
}

// Test that Value() does not match a space alone
TEST(ExpValueTest_134, DoesNotMatchSpaceAlone_134) {
  const RegEx& value = Exp::Value();
  std::string input = " ";
  int matchLen = value.Match(input);
  EXPECT_LE(matchLen, 0);
}

// Test that Value() matches colon followed by carriage return
TEST(ExpValueTest_134, MatchesColonFollowedByCR_134) {
  const RegEx& value = Exp::Value();
  std::string input = ":\r";
  int matchLen = value.Match(input);
  // Carriage return is typically a break character
  EXPECT_GT(matchLen, 0);
}

// Test that Value() with colon followed by a letter (not blank or break)
TEST(ExpValueTest_134, ColonFollowedByLetter_134) {
  const RegEx& value = Exp::Value();
  std::string input = ":a";
  int matchLen = value.Match(input);
  // The regex is ':' + (BlankOrBreak() | RegEx())
  // 'a' is not blank or break, and RegEx() is empty match
  // This depends on how the OR and sequence work
  // With the empty regex alternative, it should still match just the colon
  // The match length would be 1 (just the colon with empty second part)
  EXPECT_GE(matchLen, 1);
}

// Test Matches(char) - colon should not fully match since Value is a sequence
TEST(ExpValueTest_134, MatchesCharColon_134) {
  const RegEx& value = Exp::Value();
  // Matches(char) checks if a single char matches
  // The Value regex is a sequence of colon + something, so single char behavior may vary
  bool result = value.Matches(':');
  // This tests the single-character match behavior
  (void)result; // We just verify it doesn't crash
}

// Test Matches(string) with ": "
TEST(ExpValueTest_134, MatchesStringColonSpace_134) {
  const RegEx& value = Exp::Value();
  bool result = value.Matches(": ");
  EXPECT_TRUE(result);
}

// Test Matches(string) with "abc"
TEST(ExpValueTest_134, DoesNotMatchStringAbc_134) {
  const RegEx& value = Exp::Value();
  bool result = value.Matches("abc");
  EXPECT_FALSE(result);
}

// Test that colon followed by multiple spaces - match length should be 2
TEST(ExpValueTest_134, MatchLengthColonMultipleSpaces_134) {
  const RegEx& value = Exp::Value();
  std::string input = ":   ";
  int matchLen = value.Match(input);
  // Should match ':' + one blank = 2
  EXPECT_EQ(matchLen, 2);
}

// Test match on just colon returns length 1 (colon + empty)
TEST(ExpValueTest_134, MatchLengthJustColon_134) {
  const RegEx& value = Exp::Value();
  std::string input = ":";
  int matchLen = value.Match(input);
  // colon(1) + empty(0) = 1
  EXPECT_EQ(matchLen, 1);
}

}  // namespace
}  // namespace YAML
