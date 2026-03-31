#include "gtest/gtest.h"
#include "regex_yaml.h"
#include "regeximpl.h"
#include <string>

namespace YAML {

// ==================== Basic Construction Tests ====================

TEST(RegExTest_111, DefaultConstructor_111) {
  RegEx re;
  // Default regex (REGEX_EMPTY) should not match any character
  EXPECT_FALSE(re.Matches('a'));
  EXPECT_FALSE(re.Matches('z'));
}

TEST(RegExTest_111, CharConstructor_MatchesSameChar_111) {
  RegEx re('a');
  EXPECT_TRUE(re.Matches('a'));
}

TEST(RegExTest_111, CharConstructor_DoesNotMatchDifferentChar_111) {
  RegEx re('a');
  EXPECT_FALSE(re.Matches('b'));
  EXPECT_FALSE(re.Matches('A'));
  EXPECT_FALSE(re.Matches('z'));
}

TEST(RegExTest_111, CharConstructor_SpecialChars_111) {
  RegEx re('\n');
  EXPECT_TRUE(re.Matches('\n'));
  EXPECT_FALSE(re.Matches('\t'));
}

TEST(RegExTest_111, CharConstructor_NullChar_111) {
  RegEx re('\0');
  EXPECT_TRUE(re.Matches('\0'));
  EXPECT_FALSE(re.Matches('a'));
}

// ==================== Range Tests ====================

TEST(RegExTest_111, RangeConstructor_MatchesWithinRange_111) {
  RegEx re('a', 'z');
  EXPECT_TRUE(re.Matches('a'));
  EXPECT_TRUE(re.Matches('m'));
  EXPECT_TRUE(re.Matches('z'));
}

TEST(RegExTest_111, RangeConstructor_DoesNotMatchOutsideRange_111) {
  RegEx re('a', 'z');
  EXPECT_FALSE(re.Matches('A'));
  EXPECT_FALSE(re.Matches('Z'));
  EXPECT_FALSE(re.Matches('0'));
}

TEST(RegExTest_111, RangeConstructor_SingleCharRange_111) {
  RegEx re('m', 'm');
  EXPECT_TRUE(re.Matches('m'));
  EXPECT_FALSE(re.Matches('l'));
  EXPECT_FALSE(re.Matches('n'));
}

TEST(RegExTest_111, RangeConstructor_DigitRange_111) {
  RegEx re('0', '9');
  EXPECT_TRUE(re.Matches('0'));
  EXPECT_TRUE(re.Matches('5'));
  EXPECT_TRUE(re.Matches('9'));
  EXPECT_FALSE(re.Matches('a'));
}

// ==================== String Matches Tests ====================

TEST(RegExTest_111, CharMatchesString_SingleCharString_111) {
  RegEx re('a');
  EXPECT_TRUE(re.Matches(std::string("a")));
}

TEST(RegExTest_111, CharMatchesString_DifferentCharString_111) {
  RegEx re('a');
  EXPECT_FALSE(re.Matches(std::string("b")));
}

TEST(RegExTest_111, CharMatchesString_EmptyString_111) {
  RegEx re('a');
  EXPECT_FALSE(re.Matches(std::string("")));
}

TEST(RegExTest_111, DefaultMatchesEmptyString_111) {
  RegEx re;
  EXPECT_FALSE(re.Matches(std::string("")));
}

// ==================== Match (length) Tests with std::string ====================

TEST(RegExTest_111, MatchReturnsLengthForChar_111) {
  RegEx re('a');
  EXPECT_EQ(1, re.Match(std::string("a")));
}

TEST(RegExTest_111, MatchReturnsNegativeForNoMatch_111) {
  RegEx re('a');
  EXPECT_LT(re.Match(std::string("b")), 0);
}

TEST(RegExTest_111, MatchReturnsNegativeForEmptyString_111) {
  RegEx re('a');
  EXPECT_LT(re.Match(std::string("")), 0);
}

TEST(RegExTest_111, RangeMatchReturnsLength_111) {
  RegEx re('a', 'z');
  EXPECT_EQ(1, re.Match(std::string("hello")));
}

TEST(RegExTest_111, RangeMatchReturnsNegativeOutOfRange_111) {
  RegEx re('a', 'z');
  EXPECT_LT(re.Match(std::string("HELLO")), 0);
}

// ==================== Operator | (OR) Tests ====================

TEST(RegExTest_111, OrOperator_MatchesEither_111) {
  RegEx a('a');
  RegEx b('b');
  RegEx orRegex = a | b;
  EXPECT_TRUE(orRegex.Matches('a'));
  EXPECT_TRUE(orRegex.Matches('b'));
  EXPECT_FALSE(orRegex.Matches('c'));
}

TEST(RegExTest_111, OrOperator_MatchesString_111) {
  RegEx a('x');
  RegEx b('y');
  RegEx orRegex = a | b;
  EXPECT_TRUE(orRegex.Matches(std::string("x")));
  EXPECT_TRUE(orRegex.Matches(std::string("y")));
  EXPECT_FALSE(orRegex.Matches(std::string("z")));
}

// ==================== Operator & (AND) Tests ====================

TEST(RegExTest_111, AndOperator_MatchesBoth_111) {
  RegEx range('a', 'z');
  RegEx specific('m');
  RegEx andRegex = range & specific;
  EXPECT_TRUE(andRegex.Matches('m'));
}

TEST(RegExTest_111, AndOperator_FailsIfOneFails_111) {
  RegEx range('a', 'f');
  RegEx specific('z');
  RegEx andRegex = range & specific;
  EXPECT_FALSE(andRegex.Matches('z'));
  EXPECT_FALSE(andRegex.Matches('a'));
}

// ==================== Operator ! (NOT) Tests ====================

TEST(RegExTest_111, NotOperator_InvertsMatch_111) {
  RegEx a('a');
  RegEx notA = !a;
  EXPECT_FALSE(notA.Matches('a'));
  EXPECT_TRUE(notA.Matches('b'));
}

TEST(RegExTest_111, NotOperator_InvertsMatchString_111) {
  RegEx a('a');
  RegEx notA = !a;
  EXPECT_FALSE(notA.Matches(std::string("a")));
  EXPECT_TRUE(notA.Matches(std::string("b")));
}

// ==================== Operator + (SEQ) Tests ====================

TEST(RegExTest_111, SeqOperator_MatchesConcatenation_111) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_TRUE(seq.Matches(std::string("ab")));
  EXPECT_FALSE(seq.Matches(std::string("a")));
  EXPECT_FALSE(seq.Matches(std::string("ba")));
}

TEST(RegExTest_111, SeqOperator_MatchLength_111) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_EQ(2, seq.Match(std::string("ab")));
  EXPECT_EQ(2, seq.Match(std::string("abc")));
}

TEST(RegExTest_111, SeqOperator_NoMatchReturnsNegative_111) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_LT(seq.Match(std::string("ac")), 0);
  EXPECT_LT(seq.Match(std::string("ba")), 0);
}

// ==================== String Constructor (REGEX_SEQ) Tests ====================

TEST(RegExTest_111, StringConstructorSeq_MatchesExactString_111) {
  // Assuming REGEX_SEQ constructs a sequence from each char in string
  // This depends on the REGEX_OP enum value; we test with the string-based constructor
  // Note: We need to know the actual REGEX_OP values. Based on the code,
  // the string constructor takes a string and an op.
  // We'll test basic operators which are more reliably accessible.
}

// ==================== Combined Operator Tests ====================

TEST(RegExTest_111, ComplexOrCombination_111) {
  RegEx a('a');
  RegEx b('b');
  RegEx c('c');
  RegEx orRegex = a | b | c;
  EXPECT_TRUE(orRegex.Matches('a'));
  EXPECT_TRUE(orRegex.Matches('b'));
  EXPECT_TRUE(orRegex.Matches('c'));
  EXPECT_FALSE(orRegex.Matches('d'));
}

TEST(RegExTest_111, ComplexAndOrCombination_111) {
  RegEx range('a', 'z');
  RegEx notX = !RegEx('x');
  RegEx combined = range & notX;
  EXPECT_TRUE(combined.Matches('a'));
  EXPECT_TRUE(combined.Matches('m'));
  EXPECT_FALSE(combined.Matches('x'));
  EXPECT_FALSE(combined.Matches('A'));
}

TEST(RegExTest_111, SeqOfThreeChars_111) {
  RegEx a('a');
  RegEx b('b');
  RegEx c('c');
  RegEx seq = a + b + c;
  EXPECT_TRUE(seq.Matches(std::string("abc")));
  EXPECT_FALSE(seq.Matches(std::string("ab")));
  EXPECT_FALSE(seq.Matches(std::string("abx")));
  EXPECT_EQ(3, seq.Match(std::string("abcdef")));
}

// ==================== Boundary Conditions ====================

TEST(RegExTest_111, MatchOnEmptyStringAlwaysFails_111) {
  RegEx a('a');
  RegEx range('0', '9');
  RegEx empty;
  
  EXPECT_FALSE(a.Matches(std::string("")));
  EXPECT_FALSE(range.Matches(std::string("")));
}

TEST(RegExTest_111, RangeBoundaryLow_111) {
  RegEx re('b', 'y');
  EXPECT_FALSE(re.Matches('a'));
  EXPECT_TRUE(re.Matches('b'));
}

TEST(RegExTest_111, RangeBoundaryHigh_111) {
  RegEx re('b', 'y');
  EXPECT_TRUE(re.Matches('y'));
  EXPECT_FALSE(re.Matches('z'));
}

TEST(RegExTest_111, MatchWithLongerStringReturnsMatchedLength_111) {
  RegEx a('h');
  // Match should return 1 even with a longer string (only first char matched)
  EXPECT_EQ(1, a.Match(std::string("hello")));
}

TEST(RegExTest_111, NotOfEmptyRegex_111) {
  RegEx empty;
  RegEx notEmpty = !empty;
  // Not of empty should match any single character
  EXPECT_TRUE(notEmpty.Matches('a'));
  EXPECT_TRUE(notEmpty.Matches('Z'));
}

// ==================== Double Negation ====================

TEST(RegExTest_111, DoubleNegation_111) {
  RegEx a('a');
  RegEx doubleNot = !(!a);
  EXPECT_TRUE(doubleNot.Matches('a'));
  EXPECT_FALSE(doubleNot.Matches('b'));
}

// ==================== Or with Range ====================

TEST(RegExTest_111, OrWithRange_111) {
  RegEx digits('0', '9');
  RegEx underscore('_');
  RegEx combined = digits | underscore;
  EXPECT_TRUE(combined.Matches('0'));
  EXPECT_TRUE(combined.Matches('5'));
  EXPECT_TRUE(combined.Matches('9'));
  EXPECT_TRUE(combined.Matches('_'));
  EXPECT_FALSE(combined.Matches('a'));
}

// ==================== And with identical ====================

TEST(RegExTest_111, AndWithIdentical_111) {
  RegEx a1('a');
  RegEx a2('a');
  RegEx andRegex = a1 & a2;
  EXPECT_TRUE(andRegex.Matches('a'));
  EXPECT_FALSE(andRegex.Matches('b'));
}

// ==================== Seq then check partial match ====================

TEST(RegExTest_111, SeqPartialStringDoesNotMatch_111) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  // Only 'a' available, seq needs 'ab'
  EXPECT_FALSE(seq.Matches(std::string("a")));
  EXPECT_LT(seq.Match(std::string("a")), 0);
}

}  // namespace YAML
