#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test that EscSingleQuote returns a RegEx that matches two consecutive single quotes
TEST(EscSingleQuoteTest_149, MatchesDoubleQuote_149) {
  const RegEx& regex = Exp::EscSingleQuote();
  EXPECT_TRUE(regex.Matches("''"));
}

// Test that EscSingleQuote does not match a single quote alone
TEST(EscSingleQuoteTest_149, DoesNotMatchSingleQuote_149) {
  const RegEx& regex = Exp::EscSingleQuote();
  EXPECT_FALSE(regex.Matches("'"));
}

// Test that EscSingleQuote does not match an empty string
TEST(EscSingleQuoteTest_149, DoesNotMatchEmptyString_149) {
  const RegEx& regex = Exp::EscSingleQuote();
  EXPECT_FALSE(regex.Matches(""));
}

// Test that EscSingleQuote does not match a different character
TEST(EscSingleQuoteTest_149, DoesNotMatchOtherCharacters_149) {
  const RegEx& regex = Exp::EscSingleQuote();
  EXPECT_FALSE(regex.Matches("ab"));
}

// Test that EscSingleQuote does not match a double-quote character pair
TEST(EscSingleQuoteTest_149, DoesNotMatchDoubleQuoteChars_149) {
  const RegEx& regex = Exp::EscSingleQuote();
  EXPECT_FALSE(regex.Matches("\"\""));
}

// Test that EscSingleQuote returns the same instance every time (static)
TEST(EscSingleQuoteTest_149, ReturnsSameInstance_149) {
  const RegEx& regex1 = Exp::EscSingleQuote();
  const RegEx& regex2 = Exp::EscSingleQuote();
  EXPECT_EQ(&regex1, &regex2);
}

// Test Match returns 2 for "''" (the length of the matched sequence)
TEST(EscSingleQuoteTest_149, MatchReturnsCorrectLength_149) {
  const RegEx& regex = Exp::EscSingleQuote();
  int matchLen = regex.Match("''");
  EXPECT_EQ(matchLen, 2);
}

// Test Match returns -1 (or non-positive) for non-matching string
TEST(EscSingleQuoteTest_149, MatchReturnsNegativeForNonMatch_149) {
  const RegEx& regex = Exp::EscSingleQuote();
  int matchLen = regex.Match("ab");
  EXPECT_EQ(matchLen, -1);
}

// Test Match returns -1 for single quote only
TEST(EscSingleQuoteTest_149, MatchReturnsNegativeForSingleQuote_149) {
  const RegEx& regex = Exp::EscSingleQuote();
  int matchLen = regex.Match("'");
  EXPECT_EQ(matchLen, -1);
}

// Test Match returns -1 for empty string
TEST(EscSingleQuoteTest_149, MatchReturnsNegativeForEmpty_149) {
  const RegEx& regex = Exp::EscSingleQuote();
  int matchLen = regex.Match("");
  EXPECT_EQ(matchLen, -1);
}

// Test that Match on a longer string starting with '' still matches the prefix
TEST(EscSingleQuoteTest_149, MatchPrefixOfLongerString_149) {
  const RegEx& regex = Exp::EscSingleQuote();
  int matchLen = regex.Match("''hello");
  EXPECT_EQ(matchLen, 2);
}

// Test that a single quote character does not match via Matches(char)
TEST(EscSingleQuoteTest_149, DoesNotMatchSingleChar_149) {
  const RegEx& regex = Exp::EscSingleQuote();
  EXPECT_FALSE(regex.Matches('\''));
}

// Test that an arbitrary character does not match
TEST(EscSingleQuoteTest_149, DoesNotMatchArbitraryChar_149) {
  const RegEx& regex = Exp::EscSingleQuote();
  EXPECT_FALSE(regex.Matches('a'));
}

// Test with string of three single quotes - should still match prefix of two
TEST(EscSingleQuoteTest_149, MatchThreeSingleQuotes_149) {
  const RegEx& regex = Exp::EscSingleQuote();
  int matchLen = regex.Match("'''");
  EXPECT_EQ(matchLen, 2);
}

// Test that null character doesn't match
TEST(EscSingleQuoteTest_149, DoesNotMatchNullChar_149) {
  const RegEx& regex = Exp::EscSingleQuote();
  EXPECT_FALSE(regex.Matches('\0'));
}

}  // namespace
}  // namespace YAML
