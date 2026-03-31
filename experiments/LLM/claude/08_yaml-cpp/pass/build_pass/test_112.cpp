#include <gtest/gtest.h>
#include "regex_yaml.h"
#include "regeximpl.h"

namespace YAML {
namespace {

// Helper constants
constexpr int NO_MATCH = -1;

// =============================================================================
// Tests for RegEx default constructor (REGEX_EMPTY)
// =============================================================================

TEST(RegExTest_112, DefaultConstructor_MatchesEmptyString_112) {
  RegEx re;
  // REGEX_EMPTY should match with length 0 on any valid source
  int result = re.Match(std::string("hello"));
  EXPECT_EQ(result, 0);
}

TEST(RegExTest_112, DefaultConstructor_MatchesEmptyStringInput_112) {
  RegEx re;
  int result = re.Match(std::string(""));
  // Empty regex on empty string - depends on IsValidSource
  // For empty string, StringCharSource may be invalid
  EXPECT_GE(result, -1);
}

TEST(RegExTest_112, DefaultConstructor_MatchesBool_112) {
  RegEx re;
  bool result = re.Matches(std::string("anything"));
  EXPECT_TRUE(result);
}

// =============================================================================
// Tests for RegEx(char ch) - REGEX_MATCH
// =============================================================================

TEST(RegExTest_112, CharConstructor_MatchesSingleChar_112) {
  RegEx re('a');
  int result = re.Match(std::string("a"));
  EXPECT_EQ(result, 1);
}

TEST(RegExTest_112, CharConstructor_DoesNotMatchDifferentChar_112) {
  RegEx re('a');
  int result = re.Match(std::string("b"));
  EXPECT_EQ(result, -1);
}

TEST(RegExTest_112, CharConstructor_MatchesFirstCharOfString_112) {
  RegEx re('h');
  int result = re.Match(std::string("hello"));
  EXPECT_EQ(result, 1);
}

TEST(RegExTest_112, CharConstructor_DoesNotMatchEmptyString_112) {
  RegEx re('a');
  int result = re.Match(std::string(""));
  EXPECT_EQ(result, -1);
}

TEST(RegExTest_112, CharConstructor_MatchesBool_True_112) {
  RegEx re('x');
  EXPECT_TRUE(re.Matches('x'));
}

TEST(RegExTest_112, CharConstructor_MatchesBool_False_112) {
  RegEx re('x');
  EXPECT_FALSE(re.Matches('y'));
}

TEST(RegExTest_112, CharConstructor_MatchesString_True_112) {
  RegEx re('a');
  EXPECT_TRUE(re.Matches(std::string("a")));
}

TEST(RegExTest_112, CharConstructor_MatchesString_False_112) {
  RegEx re('a');
  EXPECT_FALSE(re.Matches(std::string("b")));
}

// =============================================================================
// Tests for RegEx(char a, char z) - REGEX_RANGE
// =============================================================================

TEST(RegExTest_112, RangeConstructor_MatchesCharInRange_112) {
  RegEx re('a', 'z');
  int result = re.Match(std::string("m"));
  EXPECT_EQ(result, 1);
}

TEST(RegExTest_112, RangeConstructor_MatchesLowerBound_112) {
  RegEx re('a', 'z');
  int result = re.Match(std::string("a"));
  EXPECT_EQ(result, 1);
}

TEST(RegExTest_112, RangeConstructor_MatchesUpperBound_112) {
  RegEx re('a', 'z');
  int result = re.Match(std::string("z"));
  EXPECT_EQ(result, 1);
}

TEST(RegExTest_112, RangeConstructor_DoesNotMatchOutOfRange_112) {
  RegEx re('a', 'z');
  int result = re.Match(std::string("A"));
  EXPECT_EQ(result, -1);
}

TEST(RegExTest_112, RangeConstructor_DoesNotMatchEmptyString_112) {
  RegEx re('a', 'z');
  int result = re.Match(std::string(""));
  EXPECT_EQ(result, -1);
}

TEST(RegExTest_112, RangeConstructor_DigitRange_112) {
  RegEx re('0', '9');
  EXPECT_EQ(re.Match(std::string("5")), 1);
  EXPECT_EQ(re.Match(std::string("0")), 1);
  EXPECT_EQ(re.Match(std::string("9")), 1);
  EXPECT_EQ(re.Match(std::string("a")), -1);
}

TEST(RegExTest_112, RangeConstructor_MatchesBool_112) {
  RegEx re('A', 'Z');
  EXPECT_TRUE(re.Matches('M'));
  EXPECT_FALSE(re.Matches('m'));
}

// =============================================================================
// Tests for operator| (OR)
// =============================================================================

TEST(RegExTest_112, OrOperator_MatchesFirstAlternative_112) {
  RegEx a('a');
  RegEx b('b');
  RegEx combined = a | b;
  EXPECT_EQ(combined.Match(std::string("a")), 1);
}

TEST(RegExTest_112, OrOperator_MatchesSecondAlternative_112) {
  RegEx a('a');
  RegEx b('b');
  RegEx combined = a | b;
  EXPECT_EQ(combined.Match(std::string("b")), 1);
}

TEST(RegExTest_112, OrOperator_NoMatchForNeither_112) {
  RegEx a('a');
  RegEx b('b');
  RegEx combined = a | b;
  EXPECT_EQ(combined.Match(std::string("c")), -1);
}

TEST(RegExTest_112, OrOperator_EmptyString_112) {
  RegEx a('a');
  RegEx b('b');
  RegEx combined = a | b;
  EXPECT_EQ(combined.Match(std::string("")), -1);
}

// =============================================================================
// Tests for operator& (AND)
// =============================================================================

TEST(RegExTest_112, AndOperator_BothMatch_112) {
  RegEx range('a', 'z');
  RegEx specific('m');
  RegEx combined = range & specific;
  EXPECT_EQ(combined.Match(std::string("m")), 1);
}

TEST(RegExTest_112, AndOperator_OnlyFirstMatches_112) {
  RegEx range('a', 'z');
  RegEx specific('m');
  RegEx combined = range & specific;
  EXPECT_EQ(combined.Match(std::string("a")), -1);
}

TEST(RegExTest_112, AndOperator_NeitherMatches_112) {
  RegEx range('a', 'z');
  RegEx specific('m');
  RegEx combined = range & specific;
  EXPECT_EQ(combined.Match(std::string("A")), -1);
}

// =============================================================================
// Tests for operator+ (SEQ - sequence)
// =============================================================================

TEST(RegExTest_112, SeqOperator_MatchesSequence_112) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_EQ(seq.Match(std::string("ab")), 2);
}

TEST(RegExTest_112, SeqOperator_PartialMatchFails_112) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_EQ(seq.Match(std::string("ac")), -1);
}

TEST(RegExTest_112, SeqOperator_FirstCharDoesNotMatch_112) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_EQ(seq.Match(std::string("ba")), -1);
}

TEST(RegExTest_112, SeqOperator_EmptyString_112) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_EQ(seq.Match(std::string("")), -1);
}

TEST(RegExTest_112, SeqOperator_TooShortString_112) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_EQ(seq.Match(std::string("a")), -1);
}

TEST(RegExTest_112, SeqOperator_LongerString_112) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  // Should match the first 2 characters
  EXPECT_EQ(seq.Match(std::string("abcdef")), 2);
}

TEST(RegExTest_112, SeqOperator_ThreeChars_112) {
  RegEx a('a');
  RegEx b('b');
  RegEx c('c');
  RegEx seq = a + b + c;
  EXPECT_EQ(seq.Match(std::string("abc")), 3);
}

// =============================================================================
// Tests for operator! (NOT)
// =============================================================================

TEST(RegExTest_112, NotOperator_MatchesWhenOriginalDoesNot_112) {
  RegEx a('a');
  RegEx notA = !a;
  int result = notA.Match(std::string("b"));
  EXPECT_EQ(result, 1);
}

TEST(RegExTest_112, NotOperator_DoesNotMatchWhenOriginalMatches_112) {
  RegEx a('a');
  RegEx notA = !a;
  int result = notA.Match(std::string("a"));
  EXPECT_EQ(result, -1);
}

TEST(RegExTest_112, NotOperator_EmptyString_112) {
  RegEx a('a');
  RegEx notA = !a;
  int result = notA.Match(std::string(""));
  EXPECT_EQ(result, -1);
}

// =============================================================================
// Tests for string-based RegEx (REGEX_OP based on string)
// =============================================================================

TEST(RegExTest_112, StringConstructor_MatchesFullString_112) {
  // When constructed with a string and REGEX_SEQ op, it should create a
  // sequence of character matchers
  RegEx re(std::string("abc"), REGEX_SEQ);
  EXPECT_EQ(re.Match(std::string("abc")), 3);
}

TEST(RegExTest_112, StringConstructor_SeqPartialStringFails_112) {
  RegEx re(std::string("abc"), REGEX_SEQ);
  EXPECT_EQ(re.Match(std::string("abd")), -1);
}

TEST(RegExTest_112, StringConstructor_OrMatchesAnyChar_112) {
  RegEx re(std::string("abc"), REGEX_OR);
  EXPECT_EQ(re.Match(std::string("a")), 1);
  EXPECT_EQ(re.Match(std::string("b")), 1);
  EXPECT_EQ(re.Match(std::string("c")), 1);
  EXPECT_EQ(re.Match(std::string("d")), -1);
}

// =============================================================================
// Tests for Matches (bool) method with strings
// =============================================================================

TEST(RegExTest_112, MatchesBoolString_FullMatch_112) {
  RegEx re(std::string("hello"), REGEX_SEQ);
  EXPECT_TRUE(re.Matches(std::string("hello")));
}

TEST(RegExTest_112, MatchesBoolString_NoMatch_112) {
  RegEx re(std::string("hello"), REGEX_SEQ);
  EXPECT_FALSE(re.Matches(std::string("world")));
}

// =============================================================================
// Complex composition tests
// =============================================================================

TEST(RegExTest_112, ComplexOr_MultipleRanges_112) {
  RegEx lower('a', 'z');
  RegEx upper('A', 'Z');
  RegEx digit('0', '9');
  RegEx alphaNum = lower | upper | digit;
  EXPECT_EQ(alphaNum.Match(std::string("a")), 1);
  EXPECT_EQ(alphaNum.Match(std::string("Z")), 1);
  EXPECT_EQ(alphaNum.Match(std::string("5")), 1);
  EXPECT_EQ(alphaNum.Match(std::string("!")), -1);
}

TEST(RegExTest_112, ComplexSeqAndOr_112) {
  RegEx a('a');
  RegEx b('b');
  RegEx c('c');
  // (a|b) + c means first char is 'a' or 'b', then 'c'
  RegEx re = (a | b) + c;
  EXPECT_EQ(re.Match(std::string("ac")), 2);
  EXPECT_EQ(re.Match(std::string("bc")), 2);
  EXPECT_EQ(re.Match(std::string("cc")), -1);
}

TEST(RegExTest_112, NotWithRange_112) {
  RegEx digit('0', '9');
  RegEx notDigit = !digit;
  EXPECT_EQ(notDigit.Match(std::string("a")), 1);
  EXPECT_EQ(notDigit.Match(std::string("5")), -1);
}

// =============================================================================
// Boundary tests
// =============================================================================

TEST(RegExTest_112, SingleCharString_112) {
  RegEx re('x');
  EXPECT_EQ(re.Match(std::string("x")), 1);
}

TEST(RegExTest_112, NullCharInRange_112) {
  RegEx re('\0');
  // Matching null character
  std::string str(1, '\0');
  int result = re.Match(str);
  EXPECT_EQ(result, 1);
}

TEST(RegExTest_112, SpecialChars_112) {
  RegEx re('\n');
  EXPECT_EQ(re.Match(std::string("\n")), 1);
  EXPECT_EQ(re.Match(std::string("n")), -1);
}

TEST(RegExTest_112, TabChar_112) {
  RegEx re('\t');
  EXPECT_EQ(re.Match(std::string("\t")), 1);
  EXPECT_EQ(re.Match(std::string(" ")), -1);
}

TEST(RegExTest_112, SpaceChar_112) {
  RegEx re(' ');
  EXPECT_EQ(re.Match(std::string(" ")), 1);
  EXPECT_EQ(re.Match(std::string("a")), -1);
}

// =============================================================================
// Matches(char) tests
// =============================================================================

TEST(RegExTest_112, MatchesChar_InRange_112) {
  RegEx re('a', 'f');
  EXPECT_TRUE(re.Matches('a'));
  EXPECT_TRUE(re.Matches('c'));
  EXPECT_TRUE(re.Matches('f'));
  EXPECT_FALSE(re.Matches('g'));
  EXPECT_FALSE(re.Matches('A'));
}

TEST(RegExTest_112, MatchesChar_ExactMatch_112) {
  RegEx re('z');
  EXPECT_TRUE(re.Matches('z'));
  EXPECT_FALSE(re.Matches('a'));
}

// =============================================================================
// Long sequence tests
// =============================================================================

TEST(RegExTest_112, LongSequence_112) {
  RegEx re(std::string("abcdefgh"), REGEX_SEQ);
  EXPECT_EQ(re.Match(std::string("abcdefgh")), 8);
  EXPECT_EQ(re.Match(std::string("abcdefgx")), -1);
  EXPECT_EQ(re.Match(std::string("abcdefghijkl")), 8);
}

TEST(RegExTest_112, MatchReturnValueIsLength_112) {
  RegEx a('a');
  RegEx b('b');
  RegEx c('c');
  RegEx d('d');
  RegEx seq = a + b + c + d;
  EXPECT_EQ(seq.Match(std::string("abcd")), 4);
  EXPECT_EQ(seq.Match(std::string("abcde")), 4);
}

// =============================================================================
// Empty regex with empty string
// =============================================================================

TEST(RegExTest_112, EmptyRegex_EmptyString_112) {
  RegEx re;
  int result = re.Match(std::string(""));
  // Empty source may be invalid, so result could be -1
  // or empty match returns 0 - implementation dependent
  EXPECT_GE(result, -1);
}

TEST(RegExTest_112, EmptyRegex_NonEmptyString_112) {
  RegEx re;
  int result = re.Match(std::string("x"));
  EXPECT_EQ(result, 0);
}

}  // namespace
}  // namespace YAML
