#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"
#include <string>

namespace YAML {
namespace {

class AnchorTest_139 : public ::testing::Test {
 protected:
  const RegEx& anchor = Exp::Anchor();
};

// Test that Anchor returns the same instance each time (it's static)
TEST_F(AnchorTest_139, ReturnsSameInstance_139) {
  const RegEx& anchor1 = Exp::Anchor();
  const RegEx& anchor2 = Exp::Anchor();
  EXPECT_EQ(&anchor1, &anchor2);
}

// Test that normal alphanumeric characters match the anchor regex
TEST_F(AnchorTest_139, MatchesAlphabeticCharacters_139) {
  EXPECT_TRUE(anchor.Matches('a'));
  EXPECT_TRUE(anchor.Matches('z'));
  EXPECT_TRUE(anchor.Matches('A'));
  EXPECT_TRUE(anchor.Matches('Z'));
}

TEST_F(AnchorTest_139, MatchesDigitCharacters_139) {
  EXPECT_TRUE(anchor.Matches('0'));
  EXPECT_TRUE(anchor.Matches('9'));
  EXPECT_TRUE(anchor.Matches('5'));
}

// Test that special characters like underscore, dash, dot match
TEST_F(AnchorTest_139, MatchesUnderscoreAndDash_139) {
  EXPECT_TRUE(anchor.Matches('_'));
  EXPECT_TRUE(anchor.Matches('-'));
  EXPECT_TRUE(anchor.Matches('.'));
}

// Test that bracket characters do NOT match (they're in the exclusion set "[]{}")
TEST_F(AnchorTest_139, DoesNotMatchOpenSquareBracket_139) {
  EXPECT_FALSE(anchor.Matches('['));
}

TEST_F(AnchorTest_139, DoesNotMatchCloseSquareBracket_139) {
  EXPECT_FALSE(anchor.Matches(']'));
}

TEST_F(AnchorTest_139, DoesNotMatchOpenCurlyBrace_139) {
  EXPECT_FALSE(anchor.Matches('{'));
}

TEST_F(AnchorTest_139, DoesNotMatchCloseCurlyBrace_139) {
  EXPECT_FALSE(anchor.Matches('}'));
}

// Test that comma does NOT match
TEST_F(AnchorTest_139, DoesNotMatchComma_139) {
  EXPECT_FALSE(anchor.Matches(','));
}

// Test that blank characters (space) do NOT match (BlankOrBreak exclusion)
TEST_F(AnchorTest_139, DoesNotMatchSpace_139) {
  EXPECT_FALSE(anchor.Matches(' '));
}

// Test that tab does NOT match (BlankOrBreak exclusion)
TEST_F(AnchorTest_139, DoesNotMatchTab_139) {
  EXPECT_FALSE(anchor.Matches('\t'));
}

// Test that newline does NOT match (BlankOrBreak exclusion)
TEST_F(AnchorTest_139, DoesNotMatchNewline_139) {
  EXPECT_FALSE(anchor.Matches('\n'));
}

// Test that carriage return does NOT match (BlankOrBreak exclusion)
TEST_F(AnchorTest_139, DoesNotMatchCarriageReturn_139) {
  EXPECT_FALSE(anchor.Matches('\r'));
}

// Test string matching for a valid anchor string
TEST_F(AnchorTest_139, MatchesValidAnchorString_139) {
  // Match returns the number of characters matched from the start
  int result = anchor.Match(std::string("abc"));
  EXPECT_GE(result, 1);
}

// Test string matching for an invalid anchor string starting with excluded char
TEST_F(AnchorTest_139, DoesNotMatchStringStartingWithComma_139) {
  EXPECT_FALSE(anchor.Matches(std::string(",")));
}

TEST_F(AnchorTest_139, DoesNotMatchStringStartingWithBracket_139) {
  EXPECT_FALSE(anchor.Matches(std::string("[")));
}

// Test various printable characters that should be valid in anchors
TEST_F(AnchorTest_139, MatchesExclamationMark_139) {
  EXPECT_TRUE(anchor.Matches('!'));
}

TEST_F(AnchorTest_139, MatchesAtSign_139) {
  EXPECT_TRUE(anchor.Matches('@'));
}

TEST_F(AnchorTest_139, MatchesHashSign_139) {
  EXPECT_TRUE(anchor.Matches('#'));
}

TEST_F(AnchorTest_139, MatchesDollarSign_139) {
  EXPECT_TRUE(anchor.Matches('$'));
}

TEST_F(AnchorTest_139, MatchesPercentSign_139) {
  EXPECT_TRUE(anchor.Matches('%'));
}

TEST_F(AnchorTest_139, MatchesAmpersand_139) {
  EXPECT_TRUE(anchor.Matches('&'));
}

TEST_F(AnchorTest_139, MatchesAsterisk_139) {
  EXPECT_TRUE(anchor.Matches('*'));
}

TEST_F(AnchorTest_139, MatchesPlus_139) {
  EXPECT_TRUE(anchor.Matches('+'));
}

TEST_F(AnchorTest_139, MatchesSlash_139) {
  EXPECT_TRUE(anchor.Matches('/'));
}

// Test that null character doesn't match
TEST_F(AnchorTest_139, DoesNotMatchNullChar_139) {
  EXPECT_FALSE(anchor.Matches('\0'));
}

// Test Match on empty string
TEST_F(AnchorTest_139, MatchOnEmptyString_139) {
  int result = anchor.Match(std::string(""));
  // Empty string should not match an anchor character
  EXPECT_LE(result, 0);
}

// Test Match returns at least 1 for a valid single character string
TEST_F(AnchorTest_139, MatchReturnsSingleCharForValidChar_139) {
  int result = anchor.Match(std::string("a"));
  EXPECT_EQ(result, 1);
}

// Test Matches on a string with a single excluded character
TEST_F(AnchorTest_139, MatchesStringWithSingleSpace_139) {
  EXPECT_FALSE(anchor.Matches(std::string(" ")));
}

}  // namespace
}  // namespace YAML
