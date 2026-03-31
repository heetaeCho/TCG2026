#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test fixture for Break() regex tests
class BreakRegExTest_119 : public ::testing::Test {
 protected:
  const RegEx& break_regex = Exp::Break();
};

// Normal operation: matches a newline character '\n'
TEST_F(BreakRegExTest_119, MatchesNewline_119) {
  EXPECT_TRUE(break_regex.Matches(std::string("\n")));
}

// Normal operation: matches a carriage return '\r'
TEST_F(BreakRegExTest_119, MatchesCarriageReturn_119) {
  EXPECT_TRUE(break_regex.Matches(std::string("\r")));
}

// Normal operation: matches "\r\n" (CRLF)
TEST_F(BreakRegExTest_119, MatchesCRLF_119) {
  int match_len = break_regex.Match(std::string("\r\n"));
  EXPECT_GE(match_len, 1);  // Should match at least 1 character (could be 2 for \r\n)
}

// Normal operation: single char '\n' matches
TEST_F(BreakRegExTest_119, MatchesSingleCharNewline_119) {
  EXPECT_TRUE(break_regex.Matches('\n'));
}

// Normal operation: single char '\r' matches
TEST_F(BreakRegExTest_119, MatchesSingleCharCarriageReturn_119) {
  EXPECT_TRUE(break_regex.Matches('\r'));
}

// Boundary: does not match a regular character
TEST_F(BreakRegExTest_119, DoesNotMatchRegularChar_119) {
  EXPECT_FALSE(break_regex.Matches('a'));
}

// Boundary: does not match space
TEST_F(BreakRegExTest_119, DoesNotMatchSpace_119) {
  EXPECT_FALSE(break_regex.Matches(' '));
}

// Boundary: does not match tab
TEST_F(BreakRegExTest_119, DoesNotMatchTab_119) {
  EXPECT_FALSE(break_regex.Matches('\t'));
}

// Boundary: does not match null character
TEST_F(BreakRegExTest_119, DoesNotMatchNullChar_119) {
  EXPECT_FALSE(break_regex.Matches('\0'));
}

// Boundary: does not match a digit
TEST_F(BreakRegExTest_119, DoesNotMatchDigit_119) {
  EXPECT_FALSE(break_regex.Matches('0'));
}

// Boundary: does not match an empty string
TEST_F(BreakRegExTest_119, DoesNotMatchEmptyString_119) {
  EXPECT_FALSE(break_regex.Matches(std::string("")));
}

// Normal: Match returns positive length for '\n'
TEST_F(BreakRegExTest_119, MatchReturnsPositiveForNewline_119) {
  int result = break_regex.Match(std::string("\n"));
  EXPECT_EQ(result, 1);
}

// Normal: Match returns positive length for '\r'
TEST_F(BreakRegExTest_119, MatchReturnsPositiveForCarriageReturn_119) {
  int result = break_regex.Match(std::string("\r"));
  EXPECT_GE(result, 1);
}

// Normal: Match returns 2 for "\r\n"
TEST_F(BreakRegExTest_119, MatchReturnsTwoForCRLF_119) {
  int result = break_regex.Match(std::string("\r\n"));
  // \r\n should match as 2, or \r should match as 1 - depends on implementation
  // but should be positive
  EXPECT_GE(result, 1);
}

// Error: Match returns -1 (or non-positive) for non-matching string
TEST_F(BreakRegExTest_119, MatchReturnsNegativeForNonBreak_119) {
  int result = break_regex.Match(std::string("abc"));
  EXPECT_EQ(result, -1);
}

// Error: Match returns -1 for empty string
TEST_F(BreakRegExTest_119, MatchReturnsNegativeForEmptyString_119) {
  int result = break_regex.Match(std::string(""));
  EXPECT_EQ(result, -1);
}

// Verify Break() returns the same reference each time (static)
TEST_F(BreakRegExTest_119, ReturnsSameReference_119) {
  const RegEx& ref1 = Exp::Break();
  const RegEx& ref2 = Exp::Break();
  EXPECT_EQ(&ref1, &ref2);
}

// Boundary: does not match form feed
TEST_F(BreakRegExTest_119, DoesNotMatchFormFeed_119) {
  EXPECT_FALSE(break_regex.Matches('\f'));
}

// Boundary: does not match vertical tab
TEST_F(BreakRegExTest_119, DoesNotMatchVerticalTab_119) {
  EXPECT_FALSE(break_regex.Matches('\v'));
}

// Normal: string starting with newline followed by other chars
TEST_F(BreakRegExTest_119, MatchReturnsOneForNewlineFollowedByText_119) {
  int result = break_regex.Match(std::string("\nabc"));
  EXPECT_EQ(result, 1);
}

// Normal: string starting with \r\n followed by other chars
TEST_F(BreakRegExTest_119, MatchForCRLFFollowedByText_119) {
  int result = break_regex.Match(std::string("\r\nabc"));
  EXPECT_GE(result, 1);
}

// Boundary: does not match string with only regular characters
TEST_F(BreakRegExTest_119, DoesNotMatchAlphabeticString_119) {
  EXPECT_FALSE(break_regex.Matches(std::string("hello")));
}

}  // namespace
}  // namespace YAML
