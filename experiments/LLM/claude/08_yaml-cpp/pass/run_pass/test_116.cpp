#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test that Space() returns a RegEx that matches the space character
TEST(ExpSpaceTest_116, MatchesSpaceCharacter_116) {
  const RegEx& spaceRegex = Exp::Space();
  EXPECT_TRUE(spaceRegex.Matches(' '));
}

// Test that Space() does not match a non-space character
TEST(ExpSpaceTest_116, DoesNotMatchNonSpaceCharacter_116) {
  const RegEx& spaceRegex = Exp::Space();
  EXPECT_FALSE(spaceRegex.Matches('a'));
}

// Test that Space() does not match tab character
TEST(ExpSpaceTest_116, DoesNotMatchTab_116) {
  const RegEx& spaceRegex = Exp::Space();
  EXPECT_FALSE(spaceRegex.Matches('\t'));
}

// Test that Space() does not match newline character
TEST(ExpSpaceTest_116, DoesNotMatchNewline_116) {
  const RegEx& spaceRegex = Exp::Space();
  EXPECT_FALSE(spaceRegex.Matches('\n'));
}

// Test that Space() does not match null character
TEST(ExpSpaceTest_116, DoesNotMatchNullChar_116) {
  const RegEx& spaceRegex = Exp::Space();
  EXPECT_FALSE(spaceRegex.Matches('\0'));
}

// Test that Space() returns the same static instance on multiple calls
TEST(ExpSpaceTest_116, ReturnsSameInstance_116) {
  const RegEx& first = Exp::Space();
  const RegEx& second = Exp::Space();
  EXPECT_EQ(&first, &second);
}

// Test that Space() matches a string consisting of just a space
TEST(ExpSpaceTest_116, MatchesSpaceString_116) {
  const RegEx& spaceRegex = Exp::Space();
  EXPECT_TRUE(spaceRegex.Matches(std::string(" ")));
}

// Test that Space() does not match an empty string
TEST(ExpSpaceTest_116, DoesNotMatchEmptyString_116) {
  const RegEx& spaceRegex = Exp::Space();
  EXPECT_FALSE(spaceRegex.Matches(std::string("")));
}

// Test that Space() does not match a string with non-space character
TEST(ExpSpaceTest_116, DoesNotMatchNonSpaceString_116) {
  const RegEx& spaceRegex = Exp::Space();
  EXPECT_FALSE(spaceRegex.Matches(std::string("a")));
}

// Test Match() with a string that starts with space
TEST(ExpSpaceTest_116, MatchReturnsOneForSpaceString_116) {
  const RegEx& spaceRegex = Exp::Space();
  int result = spaceRegex.Match(std::string(" "));
  EXPECT_EQ(1, result);
}

// Test Match() with a string that starts with space followed by other chars
TEST(ExpSpaceTest_116, MatchReturnsOneForSpacePrefix_116) {
  const RegEx& spaceRegex = Exp::Space();
  int result = spaceRegex.Match(std::string(" hello"));
  EXPECT_EQ(1, result);
}

// Test Match() with a non-space string returns -1
TEST(ExpSpaceTest_116, MatchReturnsNegativeForNonSpace_116) {
  const RegEx& spaceRegex = Exp::Space();
  int result = spaceRegex.Match(std::string("hello"));
  EXPECT_EQ(-1, result);
}

// Test Match() with empty string returns -1
TEST(ExpSpaceTest_116, MatchReturnsNegativeForEmptyString_116) {
  const RegEx& spaceRegex = Exp::Space();
  int result = spaceRegex.Match(std::string(""));
  EXPECT_EQ(-1, result);
}

// Test that Space() does not match various whitespace-like characters
TEST(ExpSpaceTest_116, DoesNotMatchCarriageReturn_116) {
  const RegEx& spaceRegex = Exp::Space();
  EXPECT_FALSE(spaceRegex.Matches('\r'));
}

TEST(ExpSpaceTest_116, DoesNotMatchFormFeed_116) {
  const RegEx& spaceRegex = Exp::Space();
  EXPECT_FALSE(spaceRegex.Matches('\f'));
}

TEST(ExpSpaceTest_116, DoesNotMatchVerticalTab_116) {
  const RegEx& spaceRegex = Exp::Space();
  EXPECT_FALSE(spaceRegex.Matches('\v'));
}

// Test various printable characters don't match
TEST(ExpSpaceTest_116, DoesNotMatchDigit_116) {
  const RegEx& spaceRegex = Exp::Space();
  EXPECT_FALSE(spaceRegex.Matches('0'));
}

TEST(ExpSpaceTest_116, DoesNotMatchSpecialChar_116) {
  const RegEx& spaceRegex = Exp::Space();
  EXPECT_FALSE(spaceRegex.Matches('!'));
}

}  // namespace
}  // namespace YAML
