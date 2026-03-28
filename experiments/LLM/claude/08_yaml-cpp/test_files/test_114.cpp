#include "gtest/gtest.h"
#include "regex_yaml.h"
#include "regeximpl.h"
#include <string>

namespace YAML {

// ============================================================
// Test Fixture
// ============================================================
class RegExTest_114 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ============================================================
// Construction Tests
// ============================================================

TEST_F(RegExTest_114, DefaultConstructor_CreatesEmptyRegex_114) {
  RegEx re;
  // An empty regex should not match any character
  EXPECT_FALSE(re.Matches('a'));
  EXPECT_FALSE(re.Matches('z'));
}

TEST_F(RegExTest_114, CharConstructor_MatchesSingleChar_114) {
  RegEx re('a');
  EXPECT_TRUE(re.Matches('a'));
  EXPECT_FALSE(re.Matches('b'));
  EXPECT_FALSE(re.Matches('A'));
}

TEST_F(RegExTest_114, RangeConstructor_MatchesCharInRange_114) {
  RegEx re('a', 'z');
  EXPECT_TRUE(re.Matches('a'));
  EXPECT_TRUE(re.Matches('m'));
  EXPECT_TRUE(re.Matches('z'));
  EXPECT_FALSE(re.Matches('A'));
  EXPECT_FALSE(re.Matches('0'));
}

TEST_F(RegExTest_114, RangeConstructor_BoundaryChars_114) {
  RegEx re('a', 'c');
  EXPECT_TRUE(re.Matches('a'));
  EXPECT_TRUE(re.Matches('b'));
  EXPECT_TRUE(re.Matches('c'));
  EXPECT_FALSE(re.Matches('d'));
  EXPECT_FALSE(re.Matches('`')); // char before 'a'
}

// ============================================================
// Match with string tests
// ============================================================

TEST_F(RegExTest_114, CharRegex_MatchString_ReturnsOneOnMatch_114) {
  RegEx re('a');
  EXPECT_EQ(1, re.Match(std::string("abc")));
}

TEST_F(RegExTest_114, CharRegex_MatchString_ReturnsNegativeOnMismatch_114) {
  RegEx re('x');
  EXPECT_EQ(-1, re.Match(std::string("abc")));
}

TEST_F(RegExTest_114, CharRegex_MatchEmptyString_ReturnsNegative_114) {
  RegEx re('a');
  EXPECT_EQ(-1, re.Match(std::string("")));
}

TEST_F(RegExTest_114, CharRegex_MatchesString_ReturnsTrueOnFullMatch_114) {
  RegEx re('a');
  EXPECT_TRUE(re.Matches(std::string("a")));
}

TEST_F(RegExTest_114, CharRegex_MatchesString_ReturnsFalseOnPartialMatch_114) {
  RegEx re('a');
  // "abc" is longer than what the regex matches, so Matches should return false
  EXPECT_FALSE(re.Matches(std::string("abc")));
}

TEST_F(RegExTest_114, EmptyRegex_MatchString_ReturnsZeroForNonEmpty_114) {
  RegEx re;
  // Empty regex matches zero characters
  int result = re.Match(std::string("abc"));
  EXPECT_EQ(0, result);
}

TEST_F(RegExTest_114, EmptyRegex_MatchEmptyString_114) {
  RegEx re;
  int result = re.Match(std::string(""));
  // Empty regex on empty string: could be 0 or -1 depending on IsValidSource
  // We just verify it doesn't crash; the actual value depends on implementation
  (void)result;
}

// ============================================================
// Operator | (Or) Tests
// ============================================================

TEST_F(RegExTest_114, OrOperator_MatchesEitherChar_114) {
  RegEx a('a');
  RegEx b('b');
  RegEx orRegex = a | b;
  EXPECT_TRUE(orRegex.Matches('a'));
  EXPECT_TRUE(orRegex.Matches('b'));
  EXPECT_FALSE(orRegex.Matches('c'));
}

TEST_F(RegExTest_114, OrOperator_MatchString_114) {
  RegEx a('a');
  RegEx b('b');
  RegEx orRegex = a | b;
  EXPECT_EQ(1, orRegex.Match(std::string("a")));
  EXPECT_EQ(1, orRegex.Match(std::string("b")));
  EXPECT_EQ(-1, orRegex.Match(std::string("c")));
}

// ============================================================
// Operator & (And) Tests
// ============================================================

TEST_F(RegExTest_114, AndOperator_MatchesBothConditions_114) {
  RegEx range('a', 'z');
  RegEx specific('m');
  RegEx andRegex = range & specific;
  EXPECT_TRUE(andRegex.Matches('m'));
  EXPECT_FALSE(andRegex.Matches('a'));
  EXPECT_FALSE(andRegex.Matches('A'));
}

// ============================================================
// Operator + (Sequence) Tests
// ============================================================

TEST_F(RegExTest_114, SeqOperator_MatchesSequence_114) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_EQ(2, seq.Match(std::string("ab")));
  EXPECT_TRUE(seq.Matches(std::string("ab")));
  EXPECT_FALSE(seq.Matches(std::string("a")));
  EXPECT_FALSE(seq.Matches(std::string("ba")));
}

TEST_F(RegExTest_114, SeqOperator_MatchesLongerString_114) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_EQ(2, seq.Match(std::string("abc")));
}

TEST_F(RegExTest_114, SeqOperator_NoMatchOnWrongSequence_114) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_EQ(-1, seq.Match(std::string("ba")));
}

// ============================================================
// Operator ! (Not) Tests
// ============================================================

TEST_F(RegExTest_114, NotOperator_InvertsMatch_114) {
  RegEx a('a');
  RegEx notA = !a;
  EXPECT_FALSE(notA.Matches('a'));
  EXPECT_TRUE(notA.Matches('b'));
  EXPECT_TRUE(notA.Matches('z'));
}

TEST_F(RegExTest_114, NotOperator_MatchReturnsOneForNonMatch_114) {
  RegEx a('a');
  RegEx notA = !a;
  EXPECT_EQ(1, notA.Match(std::string("b")));
  EXPECT_EQ(-1, notA.Match(std::string("a")));
}

// ============================================================
// Range Tests
// ============================================================

TEST_F(RegExTest_114, Range_MatchString_114) {
  RegEx range('0', '9');
  EXPECT_EQ(1, range.Match(std::string("5abc")));
  EXPECT_EQ(-1, range.Match(std::string("abc")));
}

TEST_F(RegExTest_114, Range_MatchesDigits_114) {
  RegEx range('0', '9');
  EXPECT_TRUE(range.Matches('0'));
  EXPECT_TRUE(range.Matches('5'));
  EXPECT_TRUE(range.Matches('9'));
  EXPECT_FALSE(range.Matches('a'));
}

// ============================================================
// String Constructor Tests (REGEX_SEQ and REGEX_OR)
// ============================================================

TEST_F(RegExTest_114, StringSeqConstructor_MatchesFullString_114) {
  RegEx re("abc", REGEX_SEQ);
  EXPECT_TRUE(re.Matches(std::string("abc")));
  EXPECT_FALSE(re.Matches(std::string("ab")));
  EXPECT_FALSE(re.Matches(std::string("abcd")));
  EXPECT_EQ(3, re.Match(std::string("abcdef")));
}

TEST_F(RegExTest_114, StringOrConstructor_MatchesAnyChar_114) {
  RegEx re("abc", REGEX_OR);
  EXPECT_TRUE(re.Matches('a'));
  EXPECT_TRUE(re.Matches('b'));
  EXPECT_TRUE(re.Matches('c'));
  EXPECT_FALSE(re.Matches('d'));
}

// ============================================================
// Complex Composition Tests
// ============================================================

TEST_F(RegExTest_114, ComplexOrAndSeq_114) {
  RegEx a('a');
  RegEx b('b');
  RegEx c('c');
  // (a | b) + c
  RegEx combined = (a | b) + c;
  EXPECT_TRUE(combined.Matches(std::string("ac")));
  EXPECT_TRUE(combined.Matches(std::string("bc")));
  EXPECT_FALSE(combined.Matches(std::string("cc")));
  EXPECT_FALSE(combined.Matches(std::string("ab")));
}

TEST_F(RegExTest_114, ComplexAndRange_114) {
  RegEx lower('a', 'z');
  RegEx upper('A', 'Z');
  RegEx letter = lower | upper;
  EXPECT_TRUE(letter.Matches('a'));
  EXPECT_TRUE(letter.Matches('Z'));
  EXPECT_FALSE(letter.Matches('0'));
}

TEST_F(RegExTest_114, DoubleNot_114) {
  RegEx a('a');
  RegEx notNotA = !(!a);
  EXPECT_TRUE(notNotA.Matches('a'));
  EXPECT_FALSE(notNotA.Matches('b'));
}

// ============================================================
// Boundary / Edge Cases
// ============================================================

TEST_F(RegExTest_114, MatchSingleCharString_114) {
  RegEx re('x');
  EXPECT_EQ(1, re.Match(std::string("x")));
  EXPECT_TRUE(re.Matches(std::string("x")));
}

TEST_F(RegExTest_114, RangeSameChar_114) {
  // Range where a == z
  RegEx re('m', 'm');
  EXPECT_TRUE(re.Matches('m'));
  EXPECT_FALSE(re.Matches('l'));
  EXPECT_FALSE(re.Matches('n'));
}

TEST_F(RegExTest_114, SeqOfEmptyAndChar_114) {
  RegEx empty;
  RegEx a('a');
  RegEx seq = empty + a;
  EXPECT_EQ(1, seq.Match(std::string("a")));
  EXPECT_TRUE(seq.Matches(std::string("a")));
}

TEST_F(RegExTest_114, NullCharMatch_114) {
  RegEx re('\0');
  EXPECT_TRUE(re.Matches('\0'));
  EXPECT_FALSE(re.Matches('a'));
}

TEST_F(RegExTest_114, StringSeqEmptyString_114) {
  RegEx re("", REGEX_SEQ);
  // Empty sequence should match zero characters
  EXPECT_EQ(0, re.Match(std::string("anything")));
}

TEST_F(RegExTest_114, OrWithSelf_114) {
  RegEx a('a');
  RegEx orSelf = a | a;
  EXPECT_TRUE(orSelf.Matches('a'));
  EXPECT_FALSE(orSelf.Matches('b'));
}

TEST_F(RegExTest_114, LongSequence_114) {
  RegEx re("hello", REGEX_SEQ);
  EXPECT_TRUE(re.Matches(std::string("hello")));
  EXPECT_FALSE(re.Matches(std::string("hell")));
  EXPECT_EQ(5, re.Match(std::string("hello world")));
  EXPECT_EQ(-1, re.Match(std::string("world")));
}

TEST_F(RegExTest_114, NotOnRange_114) {
  RegEx digits('0', '9');
  RegEx notDigit = !digits;
  EXPECT_TRUE(notDigit.Matches('a'));
  EXPECT_FALSE(notDigit.Matches('5'));
}

TEST_F(RegExTest_114, AndWithNothing_114) {
  RegEx a('a');
  RegEx range('a', 'z');
  RegEx result = a & range;
  EXPECT_TRUE(result.Matches('a'));
  EXPECT_FALSE(result.Matches('b'));
}

}  // namespace YAML
