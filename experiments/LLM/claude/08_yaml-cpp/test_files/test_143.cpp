#include <gtest/gtest.h>
#include <string>

// Include the necessary headers
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

class PlainScalarTest_143 : public ::testing::Test {
 protected:
  const RegEx& plainScalar() { return Exp::PlainScalar(); }
};

// Test that PlainScalar returns a consistent reference (singleton pattern)
TEST_F(PlainScalarTest_143, ReturnsSameReference_143) {
  const RegEx& ref1 = plainScalar();
  const RegEx& ref2 = plainScalar();
  EXPECT_EQ(&ref1, &ref2);
}

// Test that a simple alphanumeric string matches PlainScalar
TEST_F(PlainScalarTest_143, MatchesSimpleAlphanumericString_143) {
  const RegEx& ps = plainScalar();
  EXPECT_TRUE(ps.Matches(std::string("a")));
  EXPECT_TRUE(ps.Matches(std::string("z")));
  EXPECT_TRUE(ps.Matches(std::string("A")));
  EXPECT_TRUE(ps.Matches(std::string("Z")));
  EXPECT_TRUE(ps.Matches(std::string("0")));
  EXPECT_TRUE(ps.Matches(std::string("9")));
}

// Test that a simple alphabetic character matches
TEST_F(PlainScalarTest_143, MatchesSingleAlphaChar_143) {
  const RegEx& ps = plainScalar();
  EXPECT_TRUE(ps.Matches('a'));
  EXPECT_TRUE(ps.Matches('Z'));
  EXPECT_TRUE(ps.Matches('5'));
}

// Test that blank characters (space, tab) do NOT match PlainScalar
TEST_F(PlainScalarTest_143, DoesNotMatchBlankCharacters_143) {
  const RegEx& ps = plainScalar();
  EXPECT_FALSE(ps.Matches(' '));
  EXPECT_FALSE(ps.Matches('\t'));
}

// Test that line break characters do NOT match PlainScalar
TEST_F(PlainScalarTest_143, DoesNotMatchLineBreaks_143) {
  const RegEx& ps = plainScalar();
  EXPECT_FALSE(ps.Matches('\n'));
  EXPECT_FALSE(ps.Matches('\r'));
}

// Test that comma does NOT match PlainScalar
TEST_F(PlainScalarTest_143, DoesNotMatchComma_143) {
  const RegEx& ps = plainScalar();
  EXPECT_FALSE(ps.Matches(','));
}

// Test that flow indicators [ ] { } do NOT match PlainScalar
TEST_F(PlainScalarTest_143, DoesNotMatchFlowIndicators_143) {
  const RegEx& ps = plainScalar();
  EXPECT_FALSE(ps.Matches('['));
  EXPECT_FALSE(ps.Matches(']'));
  EXPECT_FALSE(ps.Matches('{'));
  EXPECT_FALSE(ps.Matches('}'));
}

// Test that '#' does NOT match PlainScalar
TEST_F(PlainScalarTest_143, DoesNotMatchHash_143) {
  const RegEx& ps = plainScalar();
  EXPECT_FALSE(ps.Matches('#'));
}

// Test that '&' does NOT match PlainScalar
TEST_F(PlainScalarTest_143, DoesNotMatchAmpersand_143) {
  const RegEx& ps = plainScalar();
  EXPECT_FALSE(ps.Matches('&'));
}

// Test that '*' does NOT match PlainScalar
TEST_F(PlainScalarTest_143, DoesNotMatchAsterisk_143) {
  const RegEx& ps = plainScalar();
  EXPECT_FALSE(ps.Matches('*'));
}

// Test that '!' does NOT match PlainScalar
TEST_F(PlainScalarTest_143, DoesNotMatchExclamation_143) {
  const RegEx& ps = plainScalar();
  EXPECT_FALSE(ps.Matches('!'));
}

// Test that '|' does NOT match PlainScalar
TEST_F(PlainScalarTest_143, DoesNotMatchPipe_143) {
  const RegEx& ps = plainScalar();
  EXPECT_FALSE(ps.Matches('|'));
}

// Test that '>' does NOT match PlainScalar
TEST_F(PlainScalarTest_143, DoesNotMatchGreaterThan_143) {
  const RegEx& ps = plainScalar();
  EXPECT_FALSE(ps.Matches('>'));
}

// Test that single quote does NOT match PlainScalar
TEST_F(PlainScalarTest_143, DoesNotMatchSingleQuote_143) {
  const RegEx& ps = plainScalar();
  EXPECT_FALSE(ps.Matches('\''));
}

// Test that double quote does NOT match PlainScalar
TEST_F(PlainScalarTest_143, DoesNotMatchDoubleQuote_143) {
  const RegEx& ps = plainScalar();
  EXPECT_FALSE(ps.Matches('"'));
}

// Test that '%' does NOT match PlainScalar
TEST_F(PlainScalarTest_143, DoesNotMatchPercent_143) {
  const RegEx& ps = plainScalar();
  EXPECT_FALSE(ps.Matches('%'));
}

// Test that '@' does NOT match PlainScalar
TEST_F(PlainScalarTest_143, DoesNotMatchAtSign_143) {
  const RegEx& ps = plainScalar();
  EXPECT_FALSE(ps.Matches('@'));
}

// Test that backtick does NOT match PlainScalar
TEST_F(PlainScalarTest_143, DoesNotMatchBacktick_143) {
  const RegEx& ps = plainScalar();
  EXPECT_FALSE(ps.Matches('`'));
}

// Test that '-' followed by a non-blank character should match
// (The regex excludes '-' only when followed by blank/break or end)
// '-' by itself at end of string might not match since it's "-" + (BlankOrBreak | RegEx())
TEST_F(PlainScalarTest_143, HyphenBehavior_143) {
  const RegEx& ps = plainScalar();
  // A hyphen by itself - this tests the boundary condition
  // '-' is in the special set "-?:" that are excluded when followed by blank or nothing
  EXPECT_FALSE(ps.Matches('-'));
}

// Test that '?' followed by blank does not match
TEST_F(PlainScalarTest_143, QuestionMarkBehavior_143) {
  const RegEx& ps = plainScalar();
  EXPECT_FALSE(ps.Matches('?'));
}

// Test that ':' followed by blank does not match
TEST_F(PlainScalarTest_143, ColonBehavior_143) {
  const RegEx& ps = plainScalar();
  EXPECT_FALSE(ps.Matches(':'));
}

// Test that regular printable characters match
TEST_F(PlainScalarTest_143, MatchesRegularPrintableChars_143) {
  const RegEx& ps = plainScalar();
  EXPECT_TRUE(ps.Matches('.'));
  EXPECT_TRUE(ps.Matches('/'));
  EXPECT_TRUE(ps.Matches('('));
  EXPECT_TRUE(ps.Matches(')'));
  EXPECT_TRUE(ps.Matches('+'));
  EXPECT_TRUE(ps.Matches('='));
  EXPECT_TRUE(ps.Matches('_'));
  EXPECT_TRUE(ps.Matches('~'));
}

// Test that underscore matches
TEST_F(PlainScalarTest_143, MatchesUnderscore_143) {
  const RegEx& ps = plainScalar();
  EXPECT_TRUE(ps.Matches('_'));
}

// Test Match function returns appropriate length for matching strings
TEST_F(PlainScalarTest_143, MatchReturnsLengthForMatchingString_143) {
  const RegEx& ps = plainScalar();
  int result = ps.Match(std::string("a"));
  EXPECT_GE(result, 1);
}

// Test Match function returns -1 or 0 for non-matching strings
TEST_F(PlainScalarTest_143, MatchReturnsNegativeForNonMatching_143) {
  const RegEx& ps = plainScalar();
  int result = ps.Match(std::string(","));
  EXPECT_LT(result, 1);
}

// Test with an empty string
TEST_F(PlainScalarTest_143, EmptyStringBehavior_143) {
  const RegEx& ps = plainScalar();
  EXPECT_FALSE(ps.Matches(std::string("")));
}

// Test Match with empty string
TEST_F(PlainScalarTest_143, MatchEmptyString_143) {
  const RegEx& ps = plainScalar();
  int result = ps.Match(std::string(""));
  // Empty string should not match a PlainScalar start
  EXPECT_LE(result, 0);
}

// Test that semicolon matches (not a forbidden character)
TEST_F(PlainScalarTest_143, MatchesSemicolon_143) {
  const RegEx& ps = plainScalar();
  EXPECT_TRUE(ps.Matches(';'));
}

// Test that backslash matches (not a forbidden character)
TEST_F(PlainScalarTest_143, MatchesBackslash_143) {
  const RegEx& ps = plainScalar();
  EXPECT_TRUE(ps.Matches('\\'));
}

// Test that dollar sign matches
TEST_F(PlainScalarTest_143, MatchesDollarSign_143) {
  const RegEx& ps = plainScalar();
  EXPECT_TRUE(ps.Matches('$'));
}

// Test that caret matches
TEST_F(PlainScalarTest_143, MatchesCaret_143) {
  const RegEx& ps = plainScalar();
  EXPECT_TRUE(ps.Matches('^'));
}

}  // namespace
}  // namespace YAML
