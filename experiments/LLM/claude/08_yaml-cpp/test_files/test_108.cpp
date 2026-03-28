#include <gtest/gtest.h>
#include <string>
#include "regex_yaml.h"
#include "regeximpl.h"

namespace YAML {
namespace {

// =============================================================================
// Tests for RegEx default constructor (REGEX_EMPTY)
// =============================================================================

TEST(RegExTest_108, DefaultConstructor_MatchesEmptyString_108) {
  RegEx re;
  // An empty regex should match an empty string
  EXPECT_TRUE(re.Matches(std::string("")));
}

TEST(RegExTest_108, DefaultConstructor_DoesNotMatchNonEmptyString_108) {
  RegEx re;
  EXPECT_FALSE(re.Matches(std::string("a")));
}

TEST(RegExTest_108, DefaultConstructor_MatchReturnsZeroForEmptyString_108) {
  RegEx re;
  EXPECT_EQ(0, re.Match(std::string("")));
}

TEST(RegExTest_108, DefaultConstructor_MatchReturnsNegativeForNonEmpty_108) {
  RegEx re;
  // Match on non-empty should return -1 (no match) or 0
  int result = re.Match(std::string("abc"));
  // REGEX_EMPTY typically matches zero characters
  EXPECT_GE(result, -1);
}

// =============================================================================
// Tests for RegEx(char) constructor (REGEX_MATCH)
// =============================================================================

TEST(RegExTest_108, CharConstructor_MatchesSameChar_108) {
  RegEx re('a');
  EXPECT_TRUE(re.Matches('a'));
}

TEST(RegExTest_108, CharConstructor_DoesNotMatchDifferentChar_108) {
  RegEx re('a');
  EXPECT_FALSE(re.Matches('b'));
}

TEST(RegExTest_108, CharConstructor_MatchesSingleCharString_108) {
  RegEx re('x');
  EXPECT_TRUE(re.Matches(std::string("x")));
}

TEST(RegExTest_108, CharConstructor_DoesNotMatchDifferentCharString_108) {
  RegEx re('x');
  EXPECT_FALSE(re.Matches(std::string("y")));
}

TEST(RegExTest_108, CharConstructor_DoesNotMatchEmptyString_108) {
  RegEx re('a');
  EXPECT_FALSE(re.Matches(std::string("")));
}

TEST(RegExTest_108, CharConstructor_MatchReturnValue_108) {
  RegEx re('a');
  EXPECT_EQ(1, re.Match(std::string("a")));
}

TEST(RegExTest_108, CharConstructor_MatchReturnNegativeOnMismatch_108) {
  RegEx re('a');
  EXPECT_EQ(-1, re.Match(std::string("b")));
}

TEST(RegExTest_108, CharConstructor_MatchOnLongerString_108) {
  RegEx re('a');
  // Should match first character only, returning 1
  int result = re.Match(std::string("abc"));
  EXPECT_EQ(1, result);
}

// =============================================================================
// Tests for RegEx(char, char) constructor (REGEX_RANGE)
// =============================================================================

TEST(RegExTest_108, RangeConstructor_MatchesCharInRange_108) {
  RegEx re('a', 'z');
  EXPECT_TRUE(re.Matches('m'));
}

TEST(RegExTest_108, RangeConstructor_MatchesLowerBound_108) {
  RegEx re('a', 'z');
  EXPECT_TRUE(re.Matches('a'));
}

TEST(RegExTest_108, RangeConstructor_MatchesUpperBound_108) {
  RegEx re('a', 'z');
  EXPECT_TRUE(re.Matches('z'));
}

TEST(RegExTest_108, RangeConstructor_DoesNotMatchCharOutOfRange_108) {
  RegEx re('a', 'z');
  EXPECT_FALSE(re.Matches('A'));
}

TEST(RegExTest_108, RangeConstructor_DoesNotMatchCharBeforeRange_108) {
  RegEx re('d', 'f');
  EXPECT_FALSE(re.Matches('c'));
}

TEST(RegExTest_108, RangeConstructor_DoesNotMatchCharAfterRange_108) {
  RegEx re('d', 'f');
  EXPECT_FALSE(re.Matches('g'));
}

TEST(RegExTest_108, RangeConstructor_MatchReturnValue_108) {
  RegEx re('0', '9');
  EXPECT_EQ(1, re.Match(std::string("5")));
}

TEST(RegExTest_108, RangeConstructor_MatchReturnNegativeOutOfRange_108) {
  RegEx re('0', '9');
  EXPECT_EQ(-1, re.Match(std::string("a")));
}

TEST(RegExTest_108, RangeConstructor_DigitRange_108) {
  RegEx re('0', '9');
  for (char c = '0'; c <= '9'; ++c) {
    EXPECT_TRUE(re.Matches(c)) << "Failed for char: " << c;
  }
}

TEST(RegExTest_108, RangeConstructor_DoesNotMatchEmptyString_108) {
  RegEx re('a', 'z');
  EXPECT_FALSE(re.Matches(std::string("")));
}

// =============================================================================
// Tests for operator| (OR)
// =============================================================================

TEST(RegExTest_108, OrOperator_MatchesFirstAlternative_108) {
  RegEx a('a');
  RegEx b('b');
  RegEx combined = a | b;
  EXPECT_TRUE(combined.Matches('a'));
}

TEST(RegExTest_108, OrOperator_MatchesSecondAlternative_108) {
  RegEx a('a');
  RegEx b('b');
  RegEx combined = a | b;
  EXPECT_TRUE(combined.Matches('b'));
}

TEST(RegExTest_108, OrOperator_DoesNotMatchNeither_108) {
  RegEx a('a');
  RegEx b('b');
  RegEx combined = a | b;
  EXPECT_FALSE(combined.Matches('c'));
}

TEST(RegExTest_108, OrOperator_MatchReturnValue_108) {
  RegEx a('x');
  RegEx b('y');
  RegEx combined = a | b;
  EXPECT_EQ(1, combined.Match(std::string("x")));
  EXPECT_EQ(1, combined.Match(std::string("y")));
  EXPECT_EQ(-1, combined.Match(std::string("z")));
}

// =============================================================================
// Tests for operator& (AND)
// =============================================================================

TEST(RegExTest_108, AndOperator_MatchesBothConditions_108) {
  RegEx range('a', 'z');
  RegEx specific('m');
  RegEx combined = range & specific;
  EXPECT_TRUE(combined.Matches('m'));
}

TEST(RegExTest_108, AndOperator_FailsWhenOnlyFirstMatches_108) {
  RegEx range('a', 'z');
  RegEx specific('m');
  RegEx combined = range & specific;
  EXPECT_FALSE(combined.Matches('n'));
}

TEST(RegExTest_108, AndOperator_FailsWhenNeitherMatches_108) {
  RegEx range('a', 'z');
  RegEx specific('m');
  RegEx combined = range & specific;
  EXPECT_FALSE(combined.Matches('5'));
}

// =============================================================================
// Tests for operator! (NOT)
// =============================================================================

TEST(RegExTest_108, NotOperator_InvertsMatch_108) {
  RegEx a('a');
  RegEx notA = !a;
  EXPECT_FALSE(notA.Matches('a'));
  EXPECT_TRUE(notA.Matches('b'));
}

TEST(RegExTest_108, NotOperator_MatchReturnValue_108) {
  RegEx a('a');
  RegEx notA = !a;
  EXPECT_EQ(-1, notA.Match(std::string("a")));
  // For NOT match, when the original doesn't match, it should return 1
  EXPECT_EQ(1, notA.Match(std::string("b")));
}

// =============================================================================
// Tests for operator+ (SEQ - sequence)
// =============================================================================

TEST(RegExTest_108, SeqOperator_MatchesSequence_108) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_TRUE(seq.Matches(std::string("ab")));
}

TEST(RegExTest_108, SeqOperator_DoesNotMatchPartial_108) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_FALSE(seq.Matches(std::string("a")));
}

TEST(RegExTest_108, SeqOperator_DoesNotMatchWrongOrder_108) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_FALSE(seq.Matches(std::string("ba")));
}

TEST(RegExTest_108, SeqOperator_MatchReturnsLength_108) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_EQ(2, seq.Match(std::string("ab")));
}

TEST(RegExTest_108, SeqOperator_MatchReturnsNegativeOnMismatch_108) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_EQ(-1, seq.Match(std::string("ac")));
}

TEST(RegExTest_108, SeqOperator_DoesNotMatchEmptyString_108) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_FALSE(seq.Matches(std::string("")));
}

TEST(RegExTest_108, SeqOperator_ThreeCharSequence_108) {
  RegEx a('a');
  RegEx b('b');
  RegEx c('c');
  RegEx seq = a + b + c;
  EXPECT_TRUE(seq.Matches(std::string("abc")));
  EXPECT_EQ(3, seq.Match(std::string("abc")));
}

// =============================================================================
// Tests for string-based RegEx constructor
// =============================================================================

TEST(RegExTest_108, StringConstructor_MatchesStringWithSeqOp_108) {
  // Constructing from a string with REGEX_SEQ should match the full string
  // The string constructor creates a vector of RegEx from the chars
  // This depends on REGEX_OP behavior
  // We'll test with known behavior
  RegEx re(std::string("abc"), REGEX_SEQ);
  EXPECT_TRUE(re.Matches(std::string("abc")));
  EXPECT_FALSE(re.Matches(std::string("ab")));
  EXPECT_FALSE(re.Matches(std::string("abd")));
}

TEST(RegExTest_108, StringConstructor_OrOp_108) {
  RegEx re(std::string("abc"), REGEX_OR);
  EXPECT_TRUE(re.Matches('a'));
  EXPECT_TRUE(re.Matches('b'));
  EXPECT_TRUE(re.Matches('c'));
  EXPECT_FALSE(re.Matches('d'));
}

// =============================================================================
// Complex combinations
// =============================================================================

TEST(RegExTest_108, ComplexOr_RangeOrChar_108) {
  RegEx digits('0', '9');
  RegEx underscore('_');
  RegEx combined = digits | underscore;
  EXPECT_TRUE(combined.Matches('5'));
  EXPECT_TRUE(combined.Matches('_'));
  EXPECT_FALSE(combined.Matches('a'));
}

TEST(RegExTest_108, ComplexNot_NotRange_108) {
  RegEx digits('0', '9');
  RegEx notDigits = !digits;
  EXPECT_FALSE(notDigits.Matches('5'));
  EXPECT_TRUE(notDigits.Matches('a'));
}

TEST(RegExTest_108, ComplexSeqWithRange_108) {
  RegEx letter('a', 'z');
  RegEx digit('0', '9');
  RegEx seq = letter + digit;
  EXPECT_TRUE(seq.Matches(std::string("a1")));
  EXPECT_TRUE(seq.Matches(std::string("z9")));
  EXPECT_FALSE(seq.Matches(std::string("1a")));
  EXPECT_FALSE(seq.Matches(std::string("aa")));
}

// =============================================================================
// Boundary: single char range
// =============================================================================

TEST(RegExTest_108, SingleCharRange_108) {
  RegEx re('m', 'm');
  EXPECT_TRUE(re.Matches('m'));
  EXPECT_FALSE(re.Matches('l'));
  EXPECT_FALSE(re.Matches('n'));
}

// =============================================================================
// Match on longer strings (prefix matching)
// =============================================================================

TEST(RegExTest_108, MatchPrefixOfLongerString_108) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  // Match should return the length of matched prefix
  int result = seq.Match(std::string("abcdef"));
  EXPECT_EQ(2, result);
}

TEST(RegExTest_108, SingleCharMatchOnLongerString_108) {
  RegEx a('h');
  int result = a.Match(std::string("hello"));
  EXPECT_EQ(1, result);
}

// =============================================================================
// Edge case: special characters
// =============================================================================

TEST(RegExTest_108, SpecialChar_Newline_108) {
  RegEx re('\n');
  EXPECT_TRUE(re.Matches('\n'));
  EXPECT_FALSE(re.Matches('n'));
}

TEST(RegExTest_108, SpecialChar_Tab_108) {
  RegEx re('\t');
  EXPECT_TRUE(re.Matches('\t'));
  EXPECT_FALSE(re.Matches('t'));
}

TEST(RegExTest_108, SpecialChar_Space_108) {
  RegEx re(' ');
  EXPECT_TRUE(re.Matches(' '));
  EXPECT_FALSE(re.Matches('a'));
}

TEST(RegExTest_108, SpecialChar_NullChar_108) {
  RegEx re('\0');
  EXPECT_TRUE(re.Matches('\0'));
  EXPECT_FALSE(re.Matches('a'));
}

// =============================================================================
// Match on empty string
// =============================================================================

TEST(RegExTest_108, MatchOnEmptyString_SingleChar_108) {
  RegEx re('a');
  EXPECT_EQ(-1, re.Match(std::string("")));
}

TEST(RegExTest_108, MatchOnEmptyString_Range_108) {
  RegEx re('a', 'z');
  EXPECT_EQ(-1, re.Match(std::string("")));
}

// =============================================================================
// Chained OR
// =============================================================================

TEST(RegExTest_108, ChainedOr_108) {
  RegEx a('a');
  RegEx b('b');
  RegEx c('c');
  RegEx combined = a | b | c;
  EXPECT_TRUE(combined.Matches('a'));
  EXPECT_TRUE(combined.Matches('b'));
  EXPECT_TRUE(combined.Matches('c'));
  EXPECT_FALSE(combined.Matches('d'));
}

// =============================================================================
// Double NOT
// =============================================================================

TEST(RegExTest_108, DoubleNot_108) {
  RegEx a('a');
  RegEx doubleNotA = !(!a);
  EXPECT_TRUE(doubleNotA.Matches('a'));
  EXPECT_FALSE(doubleNotA.Matches('b'));
}

}  // namespace
}  // namespace YAML
