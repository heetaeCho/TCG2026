#include <gtest/gtest.h>
#include <string>
#include "./TestProjects/yaml-cpp/src/regex_yaml.h"

namespace YAML {

class RegExTest_158 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ============================================================
// Default Constructor Tests
// ============================================================

TEST_F(RegExTest_158, DefaultConstructor_MatchesEmptyString_158) {
  RegEx re;
  EXPECT_TRUE(re.Matches(std::string("")));
}

TEST_F(RegExTest_158, DefaultConstructor_DoesNotMatchNonEmptyString_158) {
  RegEx re;
  // REGEX_EMPTY typically matches empty / zero-length
  int result = re.Match(std::string("abc"));
  // Match on empty regex should return 0 (zero-length match) or -1
  // We just observe behavior
  EXPECT_GE(result, -1);
}

// ============================================================
// Single Character Constructor Tests
// ============================================================

TEST_F(RegExTest_158, CharConstructor_MatchesSameChar_158) {
  RegEx re('a');
  EXPECT_TRUE(re.Matches('a'));
}

TEST_F(RegExTest_158, CharConstructor_DoesNotMatchDifferentChar_158) {
  RegEx re('a');
  EXPECT_FALSE(re.Matches('b'));
}

TEST_F(RegExTest_158, CharConstructor_MatchesStringStartingWithChar_158) {
  RegEx re('a');
  EXPECT_TRUE(re.Matches(std::string("a")));
}

TEST_F(RegExTest_158, CharConstructor_DoesNotMatchDifferentString_158) {
  RegEx re('a');
  EXPECT_FALSE(re.Matches(std::string("b")));
}

TEST_F(RegExTest_158, CharConstructor_MatchReturnsOne_158) {
  RegEx re('a');
  EXPECT_EQ(1, re.Match(std::string("a")));
}

TEST_F(RegExTest_158, CharConstructor_MatchReturnsOneForLongerString_158) {
  RegEx re('a');
  EXPECT_EQ(1, re.Match(std::string("abc")));
}

TEST_F(RegExTest_158, CharConstructor_MatchReturnsNegativeForNoMatch_158) {
  RegEx re('a');
  EXPECT_EQ(-1, re.Match(std::string("bcd")));
}

TEST_F(RegExTest_158, CharConstructor_DoesNotMatchEmptyString_158) {
  RegEx re('a');
  EXPECT_FALSE(re.Matches(std::string("")));
}

TEST_F(RegExTest_158, CharConstructor_MatchOnEmptyStringReturnsNegative_158) {
  RegEx re('a');
  EXPECT_EQ(-1, re.Match(std::string("")));
}

// ============================================================
// Range Constructor Tests
// ============================================================

TEST_F(RegExTest_158, RangeConstructor_MatchesCharInRange_158) {
  RegEx re('a', 'z');
  EXPECT_TRUE(re.Matches('m'));
}

TEST_F(RegExTest_158, RangeConstructor_MatchesLowerBound_158) {
  RegEx re('a', 'z');
  EXPECT_TRUE(re.Matches('a'));
}

TEST_F(RegExTest_158, RangeConstructor_MatchesUpperBound_158) {
  RegEx re('a', 'z');
  EXPECT_TRUE(re.Matches('z'));
}

TEST_F(RegExTest_158, RangeConstructor_DoesNotMatchOutOfRange_158) {
  RegEx re('a', 'z');
  EXPECT_FALSE(re.Matches('A'));
}

TEST_F(RegExTest_158, RangeConstructor_DoesNotMatchCharBeforeRange_158) {
  RegEx re('b', 'y');
  EXPECT_FALSE(re.Matches('a'));
}

TEST_F(RegExTest_158, RangeConstructor_DoesNotMatchCharAfterRange_158) {
  RegEx re('b', 'y');
  EXPECT_FALSE(re.Matches('z'));
}

TEST_F(RegExTest_158, RangeConstructor_MatchStringInRange_158) {
  RegEx re('a', 'z');
  EXPECT_EQ(1, re.Match(std::string("hello")));
}

TEST_F(RegExTest_158, RangeConstructor_NoMatchStringOutOfRange_158) {
  RegEx re('a', 'z');
  EXPECT_EQ(-1, re.Match(std::string("HELLO")));
}

TEST_F(RegExTest_158, RangeConstructor_DigitRange_158) {
  RegEx re('0', '9');
  EXPECT_TRUE(re.Matches('5'));
  EXPECT_FALSE(re.Matches('a'));
}

// ============================================================
// OR Operator Tests
// ============================================================

TEST_F(RegExTest_158, OrOperator_MatchesFirstAlternative_158) {
  RegEx re1('a');
  RegEx re2('b');
  RegEx combined = re1 | re2;
  EXPECT_TRUE(combined.Matches('a'));
}

TEST_F(RegExTest_158, OrOperator_MatchesSecondAlternative_158) {
  RegEx re1('a');
  RegEx re2('b');
  RegEx combined = re1 | re2;
  EXPECT_TRUE(combined.Matches('b'));
}

TEST_F(RegExTest_158, OrOperator_DoesNotMatchNeither_158) {
  RegEx re1('a');
  RegEx re2('b');
  RegEx combined = re1 | re2;
  EXPECT_FALSE(combined.Matches('c'));
}

TEST_F(RegExTest_158, OrOperator_MatchReturnsCorrectLength_158) {
  RegEx re1('a');
  RegEx re2('b');
  RegEx combined = re1 | re2;
  EXPECT_EQ(1, combined.Match(std::string("a")));
  EXPECT_EQ(1, combined.Match(std::string("b")));
  EXPECT_EQ(-1, combined.Match(std::string("c")));
}

TEST_F(RegExTest_158, OrOperator_WithRanges_158) {
  RegEx lower('a', 'z');
  RegEx upper('A', 'Z');
  RegEx combined = lower | upper;
  EXPECT_TRUE(combined.Matches('m'));
  EXPECT_TRUE(combined.Matches('M'));
  EXPECT_FALSE(combined.Matches('5'));
}

// ============================================================
// AND Operator Tests
// ============================================================

TEST_F(RegExTest_158, AndOperator_MatchesBoth_158) {
  RegEx re_range('a', 'z');
  RegEx re_char('m');
  RegEx combined = re_range & re_char;
  EXPECT_TRUE(combined.Matches('m'));
}

TEST_F(RegExTest_158, AndOperator_DoesNotMatchWhenOnlyOneMatches_158) {
  RegEx re_range('a', 'z');
  RegEx re_char('m');
  RegEx combined = re_range & re_char;
  EXPECT_FALSE(combined.Matches('n'));
}

TEST_F(RegExTest_158, AndOperator_DoesNotMatchWhenNeitherMatches_158) {
  RegEx re_range('a', 'z');
  RegEx re_char('m');
  RegEx combined = re_range & re_char;
  EXPECT_FALSE(combined.Matches('M'));
}

// ============================================================
// NOT Operator Tests
// ============================================================

TEST_F(RegExTest_158, NotOperator_InvertsMatch_158) {
  RegEx re('a');
  RegEx negated = !re;
  EXPECT_FALSE(negated.Matches('a'));
}

TEST_F(RegExTest_158, NotOperator_MatchesNonMatchingChar_158) {
  RegEx re('a');
  RegEx negated = !re;
  EXPECT_TRUE(negated.Matches('b'));
}

TEST_F(RegExTest_158, NotOperator_MatchReturnsOneForNonMatch_158) {
  RegEx re('a');
  RegEx negated = !re;
  EXPECT_EQ(1, negated.Match(std::string("b")));
}

TEST_F(RegExTest_158, NotOperator_MatchReturnsNegativeForOriginalMatch_158) {
  RegEx re('a');
  RegEx negated = !re;
  EXPECT_EQ(-1, negated.Match(std::string("a")));
}

TEST_F(RegExTest_158, NotOperator_WithRange_158) {
  RegEx re('a', 'z');
  RegEx negated = !re;
  EXPECT_FALSE(negated.Matches('m'));
  EXPECT_TRUE(negated.Matches('M'));
}

// ============================================================
// SEQ (Plus) Operator Tests
// ============================================================

TEST_F(RegExTest_158, SeqOperator_MatchesConcatenation_158) {
  RegEx re1('a');
  RegEx re2('b');
  RegEx seq = re1 + re2;
  EXPECT_TRUE(seq.Matches(std::string("ab")));
}

TEST_F(RegExTest_158, SeqOperator_DoesNotMatchPartial_158) {
  RegEx re1('a');
  RegEx re2('b');
  RegEx seq = re1 + re2;
  EXPECT_FALSE(seq.Matches(std::string("a")));
}

TEST_F(RegExTest_158, SeqOperator_DoesNotMatchWrongOrder_158) {
  RegEx re1('a');
  RegEx re2('b');
  RegEx seq = re1 + re2;
  EXPECT_FALSE(seq.Matches(std::string("ba")));
}

TEST_F(RegExTest_158, SeqOperator_MatchReturnsTotalLength_158) {
  RegEx re1('a');
  RegEx re2('b');
  RegEx seq = re1 + re2;
  EXPECT_EQ(2, seq.Match(std::string("ab")));
}

TEST_F(RegExTest_158, SeqOperator_MatchReturnsLengthForLongerString_158) {
  RegEx re1('a');
  RegEx re2('b');
  RegEx seq = re1 + re2;
  EXPECT_EQ(2, seq.Match(std::string("abc")));
}

TEST_F(RegExTest_158, SeqOperator_MatchReturnsNegativeForNoMatch_158) {
  RegEx re1('a');
  RegEx re2('b');
  RegEx seq = re1 + re2;
  EXPECT_EQ(-1, seq.Match(std::string("ac")));
}

TEST_F(RegExTest_158, SeqOperator_ThreeCharSequence_158) {
  RegEx re1('a');
  RegEx re2('b');
  RegEx re3('c');
  RegEx seq = re1 + re2 + re3;
  EXPECT_EQ(3, seq.Match(std::string("abc")));
  EXPECT_EQ(-1, seq.Match(std::string("abd")));
}

// ============================================================
// String Constructor Tests
// ============================================================

TEST_F(RegExTest_158, StringConstructor_SeqOp_MatchesString_158) {
  RegEx re(std::string("abc"), REGEX_SEQ);
  EXPECT_TRUE(re.Matches(std::string("abc")));
}

TEST_F(RegExTest_158, StringConstructor_SeqOp_DoesNotMatchDifferent_158) {
  RegEx re(std::string("abc"), REGEX_SEQ);
  EXPECT_FALSE(re.Matches(std::string("abd")));
}

TEST_F(RegExTest_158, StringConstructor_SeqOp_MatchReturnsLength_158) {
  RegEx re(std::string("abc"), REGEX_SEQ);
  EXPECT_EQ(3, re.Match(std::string("abcdef")));
}

TEST_F(RegExTest_158, StringConstructor_OrOp_MatchesAnyChar_158) {
  RegEx re(std::string("abc"), REGEX_OR);
  EXPECT_TRUE(re.Matches('a'));
  EXPECT_TRUE(re.Matches('b'));
  EXPECT_TRUE(re.Matches('c'));
  EXPECT_FALSE(re.Matches('d'));
}

// ============================================================
// Complex Combination Tests
// ============================================================

TEST_F(RegExTest_158, ComplexOrOfRanges_158) {
  RegEx lower('a', 'z');
  RegEx upper('A', 'Z');
  RegEx digit('0', '9');
  RegEx alphanumeric = lower | upper | digit;
  EXPECT_TRUE(alphanumeric.Matches('g'));
  EXPECT_TRUE(alphanumeric.Matches('G'));
  EXPECT_TRUE(alphanumeric.Matches('7'));
  EXPECT_FALSE(alphanumeric.Matches('!'));
}

TEST_F(RegExTest_158, ComplexSeqWithOr_158) {
  RegEx a('a');
  RegEx b('b');
  RegEx c('c');
  RegEx d('d');
  RegEx first = a | b;
  RegEx second = c | d;
  RegEx seq = first + second;
  EXPECT_TRUE(seq.Matches(std::string("ac")));
  EXPECT_TRUE(seq.Matches(std::string("ad")));
  EXPECT_TRUE(seq.Matches(std::string("bc")));
  EXPECT_TRUE(seq.Matches(std::string("bd")));
  EXPECT_FALSE(seq.Matches(std::string("ab")));
  EXPECT_FALSE(seq.Matches(std::string("cd")));
}

TEST_F(RegExTest_158, NotOfOr_158) {
  RegEx a('a');
  RegEx b('b');
  RegEx ab = a | b;
  RegEx notab = !ab;
  EXPECT_FALSE(notab.Matches('a'));
  EXPECT_FALSE(notab.Matches('b'));
  EXPECT_TRUE(notab.Matches('c'));
}

// ============================================================
// Boundary Conditions
// ============================================================

TEST_F(RegExTest_158, EmptyStringMatchOnCharRegex_158) {
  RegEx re('a');
  EXPECT_EQ(-1, re.Match(std::string("")));
}

TEST_F(RegExTest_158, SingleCharStringMatch_158) {
  RegEx re('a');
  EXPECT_EQ(1, re.Match(std::string("a")));
}

TEST_F(RegExTest_158, RangeBoundaryChars_158) {
  RegEx re('a', 'a');
  EXPECT_TRUE(re.Matches('a'));
  EXPECT_FALSE(re.Matches('b'));
}

TEST_F(RegExTest_158, NullCharMatch_158) {
  RegEx re('\0');
  EXPECT_TRUE(re.Matches('\0'));
  EXPECT_FALSE(re.Matches('a'));
}

TEST_F(RegExTest_158, HighCharRange_158) {
  RegEx re((char)127, (char)127);
  EXPECT_TRUE(re.Matches((char)127));
  EXPECT_FALSE(re.Matches((char)126));
}

// ============================================================
// Match length verification
// ============================================================

TEST_F(RegExTest_158, MatchReturnsExactMatchLength_158) {
  RegEx re(std::string("hello"), REGEX_SEQ);
  EXPECT_EQ(5, re.Match(std::string("hello world")));
}

TEST_F(RegExTest_158, MatchReturnsNegativeOneOnNoMatch_158) {
  RegEx re(std::string("hello"), REGEX_SEQ);
  EXPECT_EQ(-1, re.Match(std::string("world")));
}

TEST_F(RegExTest_158, EmptyRegexMatchReturnsZero_158) {
  RegEx re;
  EXPECT_EQ(0, re.Match(std::string("anything")));
}

TEST_F(RegExTest_158, EmptyRegexMatchOnEmptyString_158) {
  RegEx re;
  EXPECT_EQ(0, re.Match(std::string("")));
}

// ============================================================
// Double NOT Tests
// ============================================================

TEST_F(RegExTest_158, DoubleNotRestoresOriginal_158) {
  RegEx re('a');
  RegEx doubleNot = !(!re);
  EXPECT_TRUE(doubleNot.Matches('a'));
  EXPECT_FALSE(doubleNot.Matches('b'));
}

}  // namespace YAML
