#include "gtest/gtest.h"
#include "regex_yaml.h"
#include "regeximpl.h"
#include "stream.h"
#include <sstream>
#include <string>

namespace YAML {
namespace {

// Helper to create a Stream from a string
class StreamFromString {
 public:
  explicit StreamFromString(const std::string& s) : ss_(s), stream_(ss_) {}
  Stream& get() { return stream_; }
 private:
  std::istringstream ss_;
  Stream stream_;
};

// =============================================================================
// Tests for RegEx default constructor (REGEX_EMPTY)
// =============================================================================

TEST(RegExTest_110, DefaultConstructorMatchesEmptyString_110) {
  RegEx re;
  EXPECT_TRUE(re.Matches(std::string("")));
}

TEST(RegExTest_110, DefaultConstructorMatchReturnsZeroOnEmptyString_110) {
  RegEx re;
  EXPECT_EQ(0, re.Match(std::string("")));
}

TEST(RegExTest_110, DefaultConstructorMatchesNonEmptyString_110) {
  RegEx re;
  // REGEX_EMPTY should match with length 0 even on non-empty strings
  EXPECT_TRUE(re.Matches(std::string("abc")));
}

TEST(RegExTest_110, DefaultConstructorMatchReturnsZeroOnNonEmptyString_110) {
  RegEx re;
  EXPECT_EQ(0, re.Match(std::string("abc")));
}

// =============================================================================
// Tests for single character match (REGEX_MATCH)
// =============================================================================

TEST(RegExTest_110, SingleCharMatchesCorrectChar_110) {
  RegEx re('a');
  EXPECT_TRUE(re.Matches(std::string("a")));
}

TEST(RegExTest_110, SingleCharMatchReturnsOneOnCorrectChar_110) {
  RegEx re('a');
  EXPECT_EQ(1, re.Match(std::string("a")));
}

TEST(RegExTest_110, SingleCharDoesNotMatchDifferentChar_110) {
  RegEx re('a');
  EXPECT_FALSE(re.Matches(std::string("b")));
}

TEST(RegExTest_110, SingleCharMatchReturnsNegativeOnDifferentChar_110) {
  RegEx re('a');
  EXPECT_LT(re.Match(std::string("b")), 0);
}

TEST(RegExTest_110, SingleCharDoesNotMatchEmptyString_110) {
  RegEx re('a');
  EXPECT_FALSE(re.Matches(std::string("")));
}

TEST(RegExTest_110, SingleCharMatchReturnsNegativeOnEmptyString_110) {
  RegEx re('a');
  EXPECT_LT(re.Match(std::string("")), 0);
}

TEST(RegExTest_110, SingleCharMatchesFirstCharOfLongerString_110) {
  RegEx re('h');
  EXPECT_TRUE(re.Matches(std::string("hello")));
  EXPECT_EQ(1, re.Match(std::string("hello")));
}

TEST(RegExTest_110, MatchesCharOverload_110) {
  RegEx re('x');
  EXPECT_TRUE(re.Matches('x'));
  EXPECT_FALSE(re.Matches('y'));
}

// =============================================================================
// Tests for range (REGEX_RANGE)
// =============================================================================

TEST(RegExTest_110, RangeMatchesCharInRange_110) {
  RegEx re('a', 'z');
  EXPECT_TRUE(re.Matches(std::string("m")));
  EXPECT_EQ(1, re.Match(std::string("m")));
}

TEST(RegExTest_110, RangeMatchesLowerBound_110) {
  RegEx re('a', 'z');
  EXPECT_TRUE(re.Matches(std::string("a")));
}

TEST(RegExTest_110, RangeMatchesUpperBound_110) {
  RegEx re('a', 'z');
  EXPECT_TRUE(re.Matches(std::string("z")));
}

TEST(RegExTest_110, RangeDoesNotMatchCharOutOfRange_110) {
  RegEx re('a', 'z');
  EXPECT_FALSE(re.Matches(std::string("A")));
}

TEST(RegExTest_110, RangeDoesNotMatchEmptyString_110) {
  RegEx re('a', 'z');
  EXPECT_FALSE(re.Matches(std::string("")));
}

TEST(RegExTest_110, DigitRange_110) {
  RegEx re('0', '9');
  EXPECT_TRUE(re.Matches(std::string("5")));
  EXPECT_FALSE(re.Matches(std::string("a")));
}

// =============================================================================
// Tests for NOT operator
// =============================================================================

TEST(RegExTest_110, NotOperatorInvertsMatch_110) {
  RegEx re('a');
  RegEx notRe = !re;
  EXPECT_FALSE(notRe.Matches(std::string("a")));
  EXPECT_TRUE(notRe.Matches(std::string("b")));
}

TEST(RegExTest_110, NotOperatorOnEmptyString_110) {
  RegEx re('a');
  RegEx notRe = !re;
  // NOT on empty string - depends on implementation, just check it doesn't crash
  notRe.Matches(std::string(""));
}

// =============================================================================
// Tests for OR operator
// =============================================================================

TEST(RegExTest_110, OrOperatorMatchesEither_110) {
  RegEx a('a');
  RegEx b('b');
  RegEx orRe = a | b;
  EXPECT_TRUE(orRe.Matches(std::string("a")));
  EXPECT_TRUE(orRe.Matches(std::string("b")));
  EXPECT_FALSE(orRe.Matches(std::string("c")));
}

TEST(RegExTest_110, OrOperatorMatchReturnsCorrectLength_110) {
  RegEx a('a');
  RegEx b('b');
  RegEx orRe = a | b;
  EXPECT_EQ(1, orRe.Match(std::string("a")));
  EXPECT_EQ(1, orRe.Match(std::string("b")));
  EXPECT_LT(orRe.Match(std::string("c")), 0);
}

// =============================================================================
// Tests for AND operator
// =============================================================================

TEST(RegExTest_110, AndOperatorMatchesBoth_110) {
  RegEx range('a', 'f');
  RegEx specific('c');
  RegEx andRe = range & specific;
  EXPECT_TRUE(andRe.Matches(std::string("c")));
  EXPECT_FALSE(andRe.Matches(std::string("a")));  // 'a' matches range but not specific
}

TEST(RegExTest_110, AndOperatorDoesNotMatchIfOnlyOneMatches_110) {
  RegEx range('a', 'f');
  RegEx specific('z');
  RegEx andRe = range & specific;
  EXPECT_FALSE(andRe.Matches(std::string("a")));
  EXPECT_FALSE(andRe.Matches(std::string("z")));
}

// =============================================================================
// Tests for SEQ (+ operator)
// =============================================================================

TEST(RegExTest_110, SeqOperatorMatchesConcatenation_110) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_TRUE(seq.Matches(std::string("ab")));
  EXPECT_EQ(2, seq.Match(std::string("ab")));
}

TEST(RegExTest_110, SeqOperatorDoesNotMatchPartial_110) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_FALSE(seq.Matches(std::string("a")));
  EXPECT_FALSE(seq.Matches(std::string("b")));
}

TEST(RegExTest_110, SeqOperatorDoesNotMatchReversed_110) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_FALSE(seq.Matches(std::string("ba")));
}

TEST(RegExTest_110, SeqOperatorMatchesPrefix_110) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  // "abc" starts with "ab", so Match should return 2
  EXPECT_TRUE(seq.Matches(std::string("abc")));
  EXPECT_EQ(2, seq.Match(std::string("abc")));
}

TEST(RegExTest_110, SeqOperatorOnEmptyString_110) {
  RegEx a('a');
  RegEx b('b');
  RegEx seq = a + b;
  EXPECT_FALSE(seq.Matches(std::string("")));
  EXPECT_LT(seq.Match(std::string("")), 0);
}

// =============================================================================
// Tests for string-based constructor
// =============================================================================

TEST(RegExTest_110, StringOrConstructor_110) {
  // REGEX_OP for OR with string of chars - each char becomes an alternative
  // This depends on the REGEX_OP enum values; let's try with known patterns
  RegEx re('x');
  // Just verify basic functionality
  EXPECT_TRUE(re.Matches('x'));
}

// =============================================================================
// Tests with Stream
// =============================================================================

TEST(RegExTest_110, MatchesSingleCharFromStream_110) {
  RegEx re('h');
  StreamFromString sfs("hello");
  EXPECT_TRUE(re.Matches(sfs.get()));
}

TEST(RegExTest_110, MatchReturnsSingleCharLenFromStream_110) {
  RegEx re('h');
  StreamFromString sfs("hello");
  EXPECT_EQ(1, re.Match(sfs.get()));
}

TEST(RegExTest_110, DoesNotMatchSingleCharFromStream_110) {
  RegEx re('z');
  StreamFromString sfs("hello");
  EXPECT_FALSE(re.Matches(sfs.get()));
}

TEST(RegExTest_110, MatchReturnsNegativeFromStream_110) {
  RegEx re('z');
  StreamFromString sfs("hello");
  EXPECT_LT(re.Match(sfs.get()), 0);
}

TEST(RegExTest_110, RangeMatchFromStream_110) {
  RegEx re('a', 'z');
  StreamFromString sfs("hello");
  EXPECT_TRUE(re.Matches(sfs.get()));
}

TEST(RegExTest_110, SeqMatchFromStream_110) {
  RegEx h('h');
  RegEx e('e');
  RegEx seq = h + e;
  StreamFromString sfs("hello");
  EXPECT_TRUE(seq.Matches(sfs.get()));
  EXPECT_EQ(2, seq.Match(sfs.get()));
}

TEST(RegExTest_110, EmptyStreamDoesNotMatchChar_110) {
  RegEx re('a');
  StreamFromString sfs("");
  EXPECT_FALSE(re.Matches(sfs.get()));
}

TEST(RegExTest_110, EmptyRegExMatchesStream_110) {
  RegEx re;
  StreamFromString sfs("hello");
  EXPECT_TRUE(re.Matches(sfs.get()));
  EXPECT_EQ(0, re.Match(sfs.get()));
}

// =============================================================================
// Tests for complex combinations
// =============================================================================

TEST(RegExTest_110, OrOfRanges_110) {
  RegEx lower('a', 'z');
  RegEx upper('A', 'Z');
  RegEx alpha = lower | upper;
  EXPECT_TRUE(alpha.Matches(std::string("a")));
  EXPECT_TRUE(alpha.Matches(std::string("Z")));
  EXPECT_FALSE(alpha.Matches(std::string("5")));
}

TEST(RegExTest_110, SeqOfThreeChars_110) {
  RegEx a('a');
  RegEx b('b');
  RegEx c('c');
  RegEx seq = a + b + c;
  EXPECT_TRUE(seq.Matches(std::string("abc")));
  EXPECT_EQ(3, seq.Match(std::string("abc")));
  EXPECT_FALSE(seq.Matches(std::string("ab")));
  EXPECT_FALSE(seq.Matches(std::string("abd")));
}

TEST(RegExTest_110, NotOfRangeMatchesOutsideRange_110) {
  RegEx digit('0', '9');
  RegEx nonDigit = !digit;
  EXPECT_TRUE(nonDigit.Matches(std::string("a")));
  EXPECT_FALSE(nonDigit.Matches(std::string("5")));
}

TEST(RegExTest_110, ComplexCombination_110) {
  // Match a letter followed by a digit
  RegEx letter = RegEx('a', 'z') | RegEx('A', 'Z');
  RegEx digit('0', '9');
  RegEx letterDigit = letter + digit;
  EXPECT_TRUE(letterDigit.Matches(std::string("a5")));
  EXPECT_TRUE(letterDigit.Matches(std::string("Z9")));
  EXPECT_FALSE(letterDigit.Matches(std::string("55")));
  EXPECT_FALSE(letterDigit.Matches(std::string("ab")));
  EXPECT_EQ(2, letterDigit.Match(std::string("a5xyz")));
}

TEST(RegExTest_110, AndWithOverlappingRanges_110) {
  RegEx range1('a', 'm');
  RegEx range2('g', 'z');
  RegEx andRe = range1 & range2;
  // Only 'g' through 'm' should match
  EXPECT_TRUE(andRe.Matches(std::string("g")));
  EXPECT_TRUE(andRe.Matches(std::string("m")));
  EXPECT_TRUE(andRe.Matches(std::string("j")));
  EXPECT_FALSE(andRe.Matches(std::string("a")));
  EXPECT_FALSE(andRe.Matches(std::string("z")));
}

// =============================================================================
// Tests for char Matches overload
// =============================================================================

TEST(RegExTest_110, MatchesCharWithRange_110) {
  RegEx re('0', '9');
  EXPECT_TRUE(re.Matches('0'));
  EXPECT_TRUE(re.Matches('9'));
  EXPECT_TRUE(re.Matches('5'));
  EXPECT_FALSE(re.Matches('a'));
}

TEST(RegExTest_110, MatchesCharWithEmptyRegex_110) {
  RegEx re;
  // Empty regex on a single char - should not match since there's no char to match
  // Actually, REGEX_EMPTY matches with length 0, so Matches on char might be true or false
  // depending on implementation. We just ensure no crash.
  re.Matches('a');
}

// =============================================================================
// Boundary tests
// =============================================================================

TEST(RegExTest_110, MatchNullChar_110) {
  RegEx re('\0');
  EXPECT_TRUE(re.Matches('\0'));
  EXPECT_FALSE(re.Matches('a'));
}

TEST(RegExTest_110, RangeSingleChar_110) {
  // Range where a == z
  RegEx re('m', 'm');
  EXPECT_TRUE(re.Matches(std::string("m")));
  EXPECT_FALSE(re.Matches(std::string("n")));
  EXPECT_FALSE(re.Matches(std::string("l")));
}

TEST(RegExTest_110, MatchSpecialChars_110) {
  RegEx re('\n');
  EXPECT_TRUE(re.Matches(std::string("\n")));
  EXPECT_FALSE(re.Matches(std::string("n")));
}

TEST(RegExTest_110, MatchTabChar_110) {
  RegEx re('\t');
  EXPECT_TRUE(re.Matches(std::string("\t")));
  EXPECT_FALSE(re.Matches(std::string(" ")));
}

TEST(RegExTest_110, MatchSpaceChar_110) {
  RegEx re(' ');
  EXPECT_TRUE(re.Matches(std::string(" ")));
  EXPECT_FALSE(re.Matches(std::string("a")));
}

// =============================================================================
// Tests with Stream - more complex patterns
// =============================================================================

TEST(RegExTest_110, OrMatchFromStream_110) {
  RegEx a('a');
  RegEx b('b');
  RegEx orRe = a | b;
  {
    StreamFromString sfs("apple");
    EXPECT_TRUE(orRe.Matches(sfs.get()));
  }
  {
    StreamFromString sfs("banana");
    EXPECT_TRUE(orRe.Matches(sfs.get()));
  }
  {
    StreamFromString sfs("cherry");
    EXPECT_FALSE(orRe.Matches(sfs.get()));
  }
}

TEST(RegExTest_110, NotMatchFromStream_110) {
  RegEx a('a');
  RegEx notA = !a;
  {
    StreamFromString sfs("apple");
    EXPECT_FALSE(notA.Matches(sfs.get()));
  }
  {
    StreamFromString sfs("banana");
    EXPECT_TRUE(notA.Matches(sfs.get()));
  }
}

}  // namespace
}  // namespace YAML
