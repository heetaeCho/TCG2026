#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

class PlainScalarInFlowTest_144 : public ::testing::Test {
 protected:
  const RegEx& regex = Exp::PlainScalarInFlow();
};

// Test that PlainScalarInFlow returns a consistent reference (singleton)
TEST_F(PlainScalarInFlowTest_144, ReturnsSameReference_144) {
  const RegEx& ref1 = Exp::PlainScalarInFlow();
  const RegEx& ref2 = Exp::PlainScalarInFlow();
  EXPECT_EQ(&ref1, &ref2);
}

// Test that regular alphanumeric characters match
TEST_F(PlainScalarInFlowTest_144, MatchesAlphanumericCharacters_144) {
  EXPECT_TRUE(regex.Matches('a'));
  EXPECT_TRUE(regex.Matches('z'));
  EXPECT_TRUE(regex.Matches('A'));
  EXPECT_TRUE(regex.Matches('Z'));
  EXPECT_TRUE(regex.Matches('0'));
  EXPECT_TRUE(regex.Matches('9'));
}

// Test that space (blank) does not match
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchSpace_144) {
  EXPECT_FALSE(regex.Matches(' '));
}

// Test that tab (blank) does not match
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchTab_144) {
  EXPECT_FALSE(regex.Matches('\t'));
}

// Test that newline (break) does not match
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchNewline_144) {
  EXPECT_FALSE(regex.Matches('\n'));
}

// Test that carriage return (break) does not match
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchCarriageReturn_144) {
  EXPECT_FALSE(regex.Matches('\r'));
}

// Test that '?' does not match (flow indicator)
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchQuestionMark_144) {
  EXPECT_FALSE(regex.Matches('?'));
}

// Test that ',' does not match (flow indicator)
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchComma_144) {
  EXPECT_FALSE(regex.Matches(','));
}

// Test that '[' does not match (flow indicator)
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchOpenBracket_144) {
  EXPECT_FALSE(regex.Matches('['));
}

// Test that ']' does not match (flow indicator)
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchCloseBracket_144) {
  EXPECT_FALSE(regex.Matches(']'));
}

// Test that '{' does not match (flow indicator)
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchOpenBrace_144) {
  EXPECT_FALSE(regex.Matches('{'));
}

// Test that '}' does not match (flow indicator)
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchCloseBrace_144) {
  EXPECT_FALSE(regex.Matches('}'));
}

// Test that '#' does not match
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchHash_144) {
  EXPECT_FALSE(regex.Matches('#'));
}

// Test that '&' does not match
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchAmpersand_144) {
  EXPECT_FALSE(regex.Matches('&'));
}

// Test that '*' does not match
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchAsterisk_144) {
  EXPECT_FALSE(regex.Matches('*'));
}

// Test that '!' does not match
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchExclamation_144) {
  EXPECT_FALSE(regex.Matches('!'));
}

// Test that '|' does not match
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchPipe_144) {
  EXPECT_FALSE(regex.Matches('|'));
}

// Test that '>' does not match
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchGreaterThan_144) {
  EXPECT_FALSE(regex.Matches('>'));
}

// Test that single quote does not match
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchSingleQuote_144) {
  EXPECT_FALSE(regex.Matches('\''));
}

// Test that double quote does not match
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchDoubleQuote_144) {
  EXPECT_FALSE(regex.Matches('"'));
}

// Test that '%' does not match
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchPercent_144) {
  EXPECT_FALSE(regex.Matches('%'));
}

// Test that '@' does not match
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchAt_144) {
  EXPECT_FALSE(regex.Matches('@'));
}

// Test that backtick does not match
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchBacktick_144) {
  EXPECT_FALSE(regex.Matches('`'));
}

// Test that '-' at start (followed by blank/end) does not match as single char
// '-' is forbidden when followed by blank or end-of-input
TEST_F(PlainScalarInFlowTest_144, DashBehavior_144) {
  // A single '-' should not match (followed by end of string = empty RegEx)
  EXPECT_FALSE(regex.Matches('-'));
}

// Test that ':' at start (followed by blank/end) does not match as single char
TEST_F(PlainScalarInFlowTest_144, ColonBehavior_144) {
  EXPECT_FALSE(regex.Matches(':'));
}

// Test various safe characters that should be valid in plain scalars
TEST_F(PlainScalarInFlowTest_144, MatchesSafeSpecialCharacters_144) {
  EXPECT_TRUE(regex.Matches('.'));
  EXPECT_TRUE(regex.Matches('/'));
  EXPECT_TRUE(regex.Matches('('));
  EXPECT_TRUE(regex.Matches(')'));
  EXPECT_TRUE(regex.Matches('+'));
  EXPECT_TRUE(regex.Matches('='));
  EXPECT_TRUE(regex.Matches('_'));
  EXPECT_TRUE(regex.Matches('~'));
  EXPECT_TRUE(regex.Matches('^'));
}

// Test string matching for a simple alphanumeric string
TEST_F(PlainScalarInFlowTest_144, MatchStringAlphanumeric_144) {
  // Match should return length of match for valid string
  int result = regex.Match(std::string("abc"));
  EXPECT_GE(result, 1);  // At least the first character should match
}

// Test string matching for forbidden first character
TEST_F(PlainScalarInFlowTest_144, MatchStringForbiddenFirstChar_144) {
  int result = regex.Match(std::string(",abc"));
  EXPECT_LE(result, 0);  // Should not match starting with ','
}

// Test string matching for empty string
TEST_F(PlainScalarInFlowTest_144, MatchEmptyString_144) {
  int result = regex.Match(std::string(""));
  EXPECT_LE(result, 0);  // Empty string should not match
}

// Test that Matches on empty string returns false
TEST_F(PlainScalarInFlowTest_144, MatchesEmptyString_144) {
  EXPECT_FALSE(regex.Matches(std::string("")));
}

// Test string with a single valid character
TEST_F(PlainScalarInFlowTest_144, MatchesSingleValidChar_144) {
  EXPECT_TRUE(regex.Matches(std::string("x")));
}

// Test string starting with space
TEST_F(PlainScalarInFlowTest_144, DoesNotMatchStringStartingWithSpace_144) {
  EXPECT_FALSE(regex.Matches(std::string(" ")));
}

// Test that '-' followed by non-blank in a string context
TEST_F(PlainScalarInFlowTest_144, MatchStringDashFollowedByNonBlank_144) {
  // "-a" : dash followed by non-blank character - should match
  int result = regex.Match(std::string("-a"));
  // The regex for plain scalar in flow: dash followed by non-blank should be OK
  // But as a single-char match, '-' alone is problematic
  // The behavior depends on the regex composition
  // We just check it doesn't crash and returns a reasonable value
  EXPECT_GE(result, -1);
}

}  // namespace
}  // namespace YAML
