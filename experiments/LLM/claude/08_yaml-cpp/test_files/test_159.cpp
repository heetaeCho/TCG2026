#include <gtest/gtest.h>
#include "regex_yaml.h"
#include <string>

namespace YAML {

// Test fixture
class RegExTest_159 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(RegExTest_159, DefaultConstructor_159) {
  RegEx re;
  // Default regex should be REGEX_EMPTY, which typically matches empty/anything
  // We can only observe through Matches/Match
  std::string empty_str = "";
  // An empty regex behavior - test that it doesn't crash
  re.Match(empty_str);
}

TEST_F(RegExTest_159, CharConstructor_MatchesSameChar_159) {
  RegEx re('a');
  EXPECT_TRUE(re.Matches('a'));
}

TEST_F(RegExTest_159, CharConstructor_DoesNotMatchDifferentChar_159) {
  RegEx re('a');
  EXPECT_FALSE(re.Matches('b'));
}

TEST_F(RegExTest_159, RangeConstructor_MatchesCharInRange_159) {
  RegEx re('a', 'z');
  EXPECT_TRUE(re.Matches('m'));
}

TEST_F(RegExTest_159, RangeConstructor_MatchesLowerBound_159) {
  RegEx re('a', 'z');
  EXPECT_TRUE(re.Matches('a'));
}

TEST_F(RegExTest_159, RangeConstructor_MatchesUpperBound_159) {
  RegEx re('a', 'z');
  EXPECT_TRUE(re.Matches('z'));
}

TEST_F(RegExTest_159, RangeConstructor_DoesNotMatchCharOutOfRange_159) {
  RegEx re('a', 'z');
  EXPECT_FALSE(re.Matches('A'));
}

TEST_F(RegExTest_159, StringConstructor_MatchesString_159) {
  RegEx re("hello", REGEX_SEQ);
  EXPECT_TRUE(re.Matches(std::string("hello")));
}

TEST_F(RegExTest_159, StringConstructor_DoesNotMatchDifferentString_159) {
  RegEx re("hello", REGEX_SEQ);
  EXPECT_FALSE(re.Matches(std::string("world")));
}

// ==================== Operator& Tests ====================

TEST_F(RegExTest_159, AndOperator_BothMatch_159) {
  RegEx re1('a', 'z');  // matches lowercase
  RegEx re2('a', 'm');  // matches a-m
  RegEx combined = re1 & re2;
  EXPECT_TRUE(combined.Matches('f'));  // in both ranges
}

TEST_F(RegExTest_159, AndOperator_OnlyFirstMatches_159) {
  RegEx re1('a', 'z');  // matches lowercase
  RegEx re2('a', 'm');  // matches a-m
  RegEx combined = re1 & re2;
  EXPECT_FALSE(combined.Matches('n'));  // only in first range (n > m depends on impl)
  // Actually 'n' > 'm', so re2 won't match
}

TEST_F(RegExTest_159, AndOperator_NeitherMatches_159) {
  RegEx re1('a', 'f');
  RegEx re2('g', 'z');
  RegEx combined = re1 & re2;
  EXPECT_FALSE(combined.Matches('A'));  // not in either range
}

TEST_F(RegExTest_159, AndOperator_DisjointRanges_159) {
  RegEx re1('a', 'f');
  RegEx re2('g', 'z');
  RegEx combined = re1 & re2;
  // No character can be in both ranges
  EXPECT_FALSE(combined.Matches('c'));
  EXPECT_FALSE(combined.Matches('h'));
}

// ==================== Operator| Tests ====================

TEST_F(RegExTest_159, OrOperator_FirstMatches_159) {
  RegEx re1('a');
  RegEx re2('b');
  RegEx combined = re1 | re2;
  EXPECT_TRUE(combined.Matches('a'));
}

TEST_F(RegExTest_159, OrOperator_SecondMatches_159) {
  RegEx re1('a');
  RegEx re2('b');
  RegEx combined = re1 | re2;
  EXPECT_TRUE(combined.Matches('b'));
}

TEST_F(RegExTest_159, OrOperator_NeitherMatches_159) {
  RegEx re1('a');
  RegEx re2('b');
  RegEx combined = re1 | re2;
  EXPECT_FALSE(combined.Matches('c'));
}

TEST_F(RegExTest_159, OrOperator_BothMatch_159) {
  RegEx re1('a', 'z');
  RegEx re2('a', 'm');
  RegEx combined = re1 | re2;
  EXPECT_TRUE(combined.Matches('f'));
}

// ==================== Operator! Tests ====================

TEST_F(RegExTest_159, NotOperator_InvertsMatch_159) {
  RegEx re('a');
  RegEx negated = !re;
  EXPECT_FALSE(negated.Matches('a'));
  EXPECT_TRUE(negated.Matches('b'));
}

TEST_F(RegExTest_159, NotOperator_InvertsRange_159) {
  RegEx re('a', 'z');
  RegEx negated = !re;
  EXPECT_FALSE(negated.Matches('m'));
  EXPECT_TRUE(negated.Matches('A'));
}

// ==================== Operator+ Tests (Sequence) ====================

TEST_F(RegExTest_159, SeqOperator_MatchesConcatenation_159) {
  RegEx re1('a');
  RegEx re2('b');
  RegEx combined = re1 + re2;
  EXPECT_TRUE(combined.Matches(std::string("ab")));
}

TEST_F(RegExTest_159, SeqOperator_DoesNotMatchPartial_159) {
  RegEx re1('a');
  RegEx re2('b');
  RegEx combined = re1 + re2;
  EXPECT_FALSE(combined.Matches(std::string("a")));
}

TEST_F(RegExTest_159, SeqOperator_DoesNotMatchReversed_159) {
  RegEx re1('a');
  RegEx re2('b');
  RegEx combined = re1 + re2;
  EXPECT_FALSE(combined.Matches(std::string("ba")));
}

// ==================== Match (string) Tests ====================

TEST_F(RegExTest_159, Match_ReturnsLengthOnMatch_159) {
  RegEx re('a');
  int result = re.Match(std::string("abc"));
  EXPECT_EQ(1, result);
}

TEST_F(RegExTest_159, Match_ReturnsNegativeOnNoMatch_159) {
  RegEx re('a');
  int result = re.Match(std::string("xyz"));
  EXPECT_EQ(-1, result);
}

TEST_F(RegExTest_159, Match_EmptyString_159) {
  RegEx re('a');
  int result = re.Match(std::string(""));
  EXPECT_EQ(-1, result);
}

TEST_F(RegExTest_159, Match_SequenceReturnsLength_159) {
  RegEx re("abc", REGEX_SEQ);
  int result = re.Match(std::string("abcdef"));
  EXPECT_EQ(3, result);
}

TEST_F(RegExTest_159, Match_SequencePartialStringNoMatch_159) {
  RegEx re("abc", REGEX_SEQ);
  int result = re.Match(std::string("ab"));
  EXPECT_EQ(-1, result);
}

TEST_F(RegExTest_159, Match_RangeReturnsOne_159) {
  RegEx re('0', '9');
  int result = re.Match(std::string("5abc"));
  EXPECT_EQ(1, result);
}

TEST_F(RegExTest_159, Match_RangeNoMatch_159) {
  RegEx re('0', '9');
  int result = re.Match(std::string("abc"));
  EXPECT_EQ(-1, result);
}

// ==================== Matches (string) Tests ====================

TEST_F(RegExTest_159, Matches_String_ExactMatch_159) {
  RegEx re("test", REGEX_SEQ);
  EXPECT_TRUE(re.Matches(std::string("test")));
}

TEST_F(RegExTest_159, Matches_String_PrefixMatch_159) {
  RegEx re("test", REGEX_SEQ);
  // Matches checks if the regex matches the beginning
  EXPECT_TRUE(re.Matches(std::string("testing")));
}

TEST_F(RegExTest_159, Matches_String_NoMatch_159) {
  RegEx re("test", REGEX_SEQ);
  EXPECT_FALSE(re.Matches(std::string("best")));
}

// ==================== Complex Combinations ====================

TEST_F(RegExTest_159, ComplexAndOr_159) {
  RegEx lower('a', 'z');
  RegEx upper('A', 'Z');
  RegEx alpha = lower | upper;
  EXPECT_TRUE(alpha.Matches('a'));
  EXPECT_TRUE(alpha.Matches('Z'));
  EXPECT_FALSE(alpha.Matches('5'));
}

TEST_F(RegExTest_159, ComplexSequenceWithRange_159) {
  RegEx letter('a', 'z');
  RegEx digit('0', '9');
  RegEx seq = letter + digit;
  EXPECT_TRUE(seq.Matches(std::string("a1")));
  EXPECT_FALSE(seq.Matches(std::string("1a")));
}

TEST_F(RegExTest_159, ComplexNotOr_159) {
  RegEx re('a');
  RegEx notA = !re;
  RegEx reB('b');
  RegEx notAorB = notA | reB;
  EXPECT_TRUE(notAorB.Matches('b'));  // matches second
  EXPECT_TRUE(notAorB.Matches('c'));  // matches !a
  EXPECT_FALSE(notAorB.Matches('a')); // doesn't match !a, doesn't match b
}

TEST_F(RegExTest_159, DoubleNegation_159) {
  RegEx re('a');
  RegEx doubleNeg = !(!re);
  EXPECT_TRUE(doubleNeg.Matches('a'));
  EXPECT_FALSE(doubleNeg.Matches('b'));
}

// ==================== Boundary Tests ====================

TEST_F(RegExTest_159, CharBoundary_NullChar_159) {
  RegEx re('\0');
  EXPECT_TRUE(re.Matches('\0'));
  EXPECT_FALSE(re.Matches('a'));
}

TEST_F(RegExTest_159, CharBoundary_MaxChar_159) {
  RegEx re('\x7F');
  EXPECT_TRUE(re.Matches('\x7F'));
  EXPECT_FALSE(re.Matches('a'));
}

TEST_F(RegExTest_159, RangeBoundary_SingleCharRange_159) {
  RegEx re('a', 'a');
  EXPECT_TRUE(re.Matches('a'));
  EXPECT_FALSE(re.Matches('b'));
}

TEST_F(RegExTest_159, StringConstructor_SingleChar_159) {
  RegEx re("x", REGEX_SEQ);
  EXPECT_TRUE(re.Matches(std::string("x")));
  EXPECT_FALSE(re.Matches(std::string("y")));
}

TEST_F(RegExTest_159, StringConstructor_EmptyString_159) {
  RegEx re("", REGEX_SEQ);
  // Empty sequence should match anything (0-length match)
  int result = re.Match(std::string("anything"));
  EXPECT_GE(result, 0);
}

TEST_F(RegExTest_159, Match_AndOperatorReturnsMinimumMatchLength_159) {
  // AND of two single-char matchers
  RegEx re1('a', 'z');
  RegEx re2('a', 'f');
  RegEx combined = re1 & re2;
  int result = combined.Match(std::string("c"));
  EXPECT_EQ(1, result);
}

TEST_F(RegExTest_159, Match_OrOperatorReturnsMaxMatchLength_159) {
  RegEx re1("ab", REGEX_SEQ);
  RegEx re2("abc", REGEX_SEQ);
  RegEx combined = re1 | re2;
  int result = combined.Match(std::string("abcdef"));
  // Or should return the longer match
  EXPECT_GE(result, 2);
}

TEST_F(RegExTest_159, Matches_Char_ExactSingleChar_159) {
  RegEx re('x');
  EXPECT_TRUE(re.Matches('x'));
  EXPECT_FALSE(re.Matches('X'));
}

TEST_F(RegExTest_159, CopySemantics_159) {
  RegEx re1('a');
  RegEx re2 = re1;
  EXPECT_TRUE(re2.Matches('a'));
  EXPECT_FALSE(re2.Matches('b'));
}

TEST_F(RegExTest_159, AndOperator_WithStringMatch_159) {
  RegEx re1("abc", REGEX_SEQ);
  RegEx re2("abc", REGEX_SEQ);
  RegEx combined = re1 & re2;
  EXPECT_TRUE(combined.Matches(std::string("abc")));
  EXPECT_FALSE(combined.Matches(std::string("abd")));
}

TEST_F(RegExTest_159, OrOperator_WithStringMatch_159) {
  RegEx re1("abc", REGEX_SEQ);
  RegEx re2("xyz", REGEX_SEQ);
  RegEx combined = re1 | re2;
  EXPECT_TRUE(combined.Matches(std::string("abc")));
  EXPECT_TRUE(combined.Matches(std::string("xyz")));
  EXPECT_FALSE(combined.Matches(std::string("def")));
}

TEST_F(RegExTest_159, NotOperator_WithStringMatch_159) {
  RegEx re('a');
  RegEx negated = !re;
  int result = negated.Match(std::string("bcd"));
  EXPECT_EQ(1, result);  // matches one non-'a' character
}

}  // namespace YAML
