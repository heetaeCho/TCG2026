#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test that Key() returns a valid RegEx reference
TEST(ExpKeyTest_132, ReturnsNonNullReference_132) {
  const RegEx& key = Exp::Key();
  // Just verify we can obtain the reference without crashing
  (void)key;
}

// Test that Key() returns the same object on repeated calls (static)
TEST(ExpKeyTest_132, ReturnsSameStaticInstance_132) {
  const RegEx& key1 = Exp::Key();
  const RegEx& key2 = Exp::Key();
  EXPECT_EQ(&key1, &key2);
}

// Test that Key() matches '?' followed by a space (blank)
TEST(ExpKeyTest_132, MatchesQuestionMarkFollowedBySpace_132) {
  const RegEx& key = Exp::Key();
  std::string input = "? ";
  int result = key.Match(input);
  EXPECT_EQ(result, 2);
}

// Test that Key() matches '?' followed by a tab (blank)
TEST(ExpKeyTest_132, MatchesQuestionMarkFollowedByTab_132) {
  const RegEx& key = Exp::Key();
  std::string input = "?\t";
  int result = key.Match(input);
  EXPECT_EQ(result, 2);
}

// Test that Key() matches '?' followed by a newline (break)
TEST(ExpKeyTest_132, MatchesQuestionMarkFollowedByNewline_132) {
  const RegEx& key = Exp::Key();
  std::string input = "?\n";
  int result = key.Match(input);
  EXPECT_EQ(result, 2);
}

// Test that Key() matches '?' followed by carriage return (break)
TEST(ExpKeyTest_132, MatchesQuestionMarkFollowedByCarriageReturn_132) {
  const RegEx& key = Exp::Key();
  std::string input = "?\r";
  int result = key.Match(input);
  EXPECT_EQ(result, 2);
}

// Test that Key() does not match '?' followed by a regular character
TEST(ExpKeyTest_132, DoesNotMatchQuestionMarkFollowedByLetter_132) {
  const RegEx& key = Exp::Key();
  std::string input = "?a";
  int result = key.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that Key() does not match a string starting with a different character
TEST(ExpKeyTest_132, DoesNotMatchNonQuestionMark_132) {
  const RegEx& key = Exp::Key();
  std::string input = "a ";
  int result = key.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that Key() does not match an empty string
TEST(ExpKeyTest_132, DoesNotMatchEmptyString_132) {
  const RegEx& key = Exp::Key();
  std::string input = "";
  int result = key.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that Key() does not match just '?' alone (no following blank/break)
TEST(ExpKeyTest_132, DoesNotMatchLoneQuestionMark_132) {
  const RegEx& key = Exp::Key();
  std::string input = "?";
  int result = key.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that Key() does not match '?' followed by a digit
TEST(ExpKeyTest_132, DoesNotMatchQuestionMarkFollowedByDigit_132) {
  const RegEx& key = Exp::Key();
  std::string input = "?1";
  int result = key.Match(input);
  EXPECT_EQ(result, -1);
}

// Test Matches(string) for a matching string
TEST(ExpKeyTest_132, MatchesMethodReturnsTrueForValidInput_132) {
  const RegEx& key = Exp::Key();
  std::string input = "? ";
  bool result = key.Matches(input);
  EXPECT_TRUE(result);
}

// Test Matches(string) for a non-matching string
TEST(ExpKeyTest_132, MatchesMethodReturnsFalseForInvalidInput_132) {
  const RegEx& key = Exp::Key();
  std::string input = "?x";
  bool result = key.Matches(input);
  EXPECT_FALSE(result);
}

// Test that Key() matches '?' followed by space and more content (only first 2 chars matter)
TEST(ExpKeyTest_132, MatchesQuestionMarkSpaceWithTrailingContent_132) {
  const RegEx& key = Exp::Key();
  std::string input = "? key";
  int result = key.Match(input);
  EXPECT_EQ(result, 2);
}

// Test that Key() does not match '?' followed by punctuation
TEST(ExpKeyTest_132, DoesNotMatchQuestionMarkFollowedByPunctuation_132) {
  const RegEx& key = Exp::Key();
  std::string input = "?:";
  int result = key.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that Key() does not match just spaces
TEST(ExpKeyTest_132, DoesNotMatchJustSpaces_132) {
  const RegEx& key = Exp::Key();
  std::string input = "  ";
  int result = key.Match(input);
  EXPECT_EQ(result, -1);
}

}  // namespace
}  // namespace YAML
