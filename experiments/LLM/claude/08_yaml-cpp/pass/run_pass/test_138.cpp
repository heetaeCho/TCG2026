#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test that Comment() returns a RegEx that matches '#'
TEST(ExpCommentTest_138, MatchesHashCharacter_138) {
  RegEx comment = Exp::Comment();
  EXPECT_TRUE(comment.Matches('#'));
}

// Test that Comment() does not match other characters
TEST(ExpCommentTest_138, DoesNotMatchNonHashCharacter_138) {
  RegEx comment = Exp::Comment();
  EXPECT_FALSE(comment.Matches('a'));
  EXPECT_FALSE(comment.Matches(' '));
  EXPECT_FALSE(comment.Matches('\0'));
  EXPECT_FALSE(comment.Matches('\n'));
  EXPECT_FALSE(comment.Matches('!'));
  EXPECT_FALSE(comment.Matches('/'));
}

// Test that Comment() matches a string starting with '#'
TEST(ExpCommentTest_138, MatchesStringStartingWithHash_138) {
  RegEx comment = Exp::Comment();
  EXPECT_TRUE(comment.Matches(std::string("#")));
}

// Test that Comment() matches string with '#' followed by other chars
TEST(ExpCommentTest_138, MatchesStringWithHashAndMore_138) {
  RegEx comment = Exp::Comment();
  // Match should return 1 for a single character match on '#...'
  int result = comment.Match(std::string("# this is a comment"));
  EXPECT_EQ(1, result);
}

// Test that Comment() does not match a string not starting with '#'
TEST(ExpCommentTest_138, DoesNotMatchStringNotStartingWithHash_138) {
  RegEx comment = Exp::Comment();
  EXPECT_FALSE(comment.Matches(std::string("abc")));
}

// Test that Comment() does not match an empty string
TEST(ExpCommentTest_138, DoesNotMatchEmptyString_138) {
  RegEx comment = Exp::Comment();
  EXPECT_FALSE(comment.Matches(std::string("")));
}

// Test Match returns -1 for non-matching string
TEST(ExpCommentTest_138, MatchReturnsNegativeForNonMatch_138) {
  RegEx comment = Exp::Comment();
  int result = comment.Match(std::string("not a comment"));
  EXPECT_EQ(-1, result);
}

// Test Match returns -1 for empty string
TEST(ExpCommentTest_138, MatchReturnsNegativeForEmptyString_138) {
  RegEx comment = Exp::Comment();
  int result = comment.Match(std::string(""));
  EXPECT_EQ(-1, result);
}

// Test Match returns 1 for exactly '#'
TEST(ExpCommentTest_138, MatchReturnsOneForExactHash_138) {
  RegEx comment = Exp::Comment();
  int result = comment.Match(std::string("#"));
  EXPECT_EQ(1, result);
}

// Test that Comment() returns a consistent RegEx across multiple calls
TEST(ExpCommentTest_138, ReturnsConsistentRegEx_138) {
  RegEx comment1 = Exp::Comment();
  RegEx comment2 = Exp::Comment();
  // Both should behave the same way
  EXPECT_TRUE(comment1.Matches('#'));
  EXPECT_TRUE(comment2.Matches('#'));
  EXPECT_FALSE(comment1.Matches('x'));
  EXPECT_FALSE(comment2.Matches('x'));
}

// Test boundary: character just before '#' in ASCII ('"')
TEST(ExpCommentTest_138, DoesNotMatchCharBeforeHash_138) {
  RegEx comment = Exp::Comment();
  EXPECT_FALSE(comment.Matches('"'));  // ASCII 34, '#' is 35
}

// Test boundary: character just after '#' in ASCII ('$')
TEST(ExpCommentTest_138, DoesNotMatchCharAfterHash_138) {
  RegEx comment = Exp::Comment();
  EXPECT_FALSE(comment.Matches('$'));  // ASCII 36, '#' is 35
}

}  // namespace
}  // namespace YAML
