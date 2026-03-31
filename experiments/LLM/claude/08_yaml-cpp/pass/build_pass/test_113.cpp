#include "gtest/gtest.h"
#include <sstream>
#include <string>

#include "yaml-cpp/yaml.h"
#include "regex_yaml.h"
#include "regeximpl.h"
#include "stream.h"
#include "streamcharsource.h"

namespace YAML {
namespace {

// Helper to create a Stream from a string
class RegExTest_113 : public ::testing::Test {
 protected:
  std::unique_ptr<Stream> MakeStream(const std::string& input) {
    streams_.emplace_back(std::make_unique<std::istringstream>(input));
    return std::make_unique<Stream>(*streams_.back());
  }

  std::vector<std::unique_ptr<std::istringstream>> streams_;
};

// =============================================================================
// Tests for RegEx default constructor (REGEX_EMPTY)
// =============================================================================

TEST_F(RegExTest_113, DefaultConstructor_MatchesEmptyString_113) {
  RegEx re;
  EXPECT_EQ(0, re.Match(std::string("")));
}

TEST_F(RegExTest_113, DefaultConstructor_MatchesNonEmptyString_113) {
  RegEx re;
  // Empty regex should match with length 0 on non-empty string
  EXPECT_EQ(0, re.Match(std::string("abc")));
}

TEST_F(RegExTest_113, DefaultConstructor_MatchesBool_EmptyString_113) {
  RegEx re;
  EXPECT_TRUE(re.Matches(std::string("")));
}

// =============================================================================
// Tests for single character match (REGEX_MATCH)
// =============================================================================

TEST_F(RegExTest_113, SingleCharMatch_MatchesSameChar_113) {
  RegEx re('a');
  EXPECT_EQ(1, re.Match(std::string("a")));
}

TEST_F(RegExTest_113, SingleCharMatch_DoesNotMatchDifferentChar_113) {
  RegEx re('a');
  EXPECT_EQ(-1, re.Match(std::string("b")));
}

TEST_F(RegExTest_113, SingleCharMatch_MatchesFirstCharOfString_113) {
  RegEx re('a');
  EXPECT_EQ(1, re.Match(std::string("abc")));
}

TEST_F(RegExTest_113, SingleCharMatch_EmptyStringNoMatch_113) {
  RegEx re('a');
  EXPECT_EQ(-1, re.Match(std::string("")));
}

TEST_F(RegExTest_113, SingleCharMatch_MatchesBoolTrue_113) {
  RegEx re('x');
  EXPECT_TRUE(re.Matches('x'));
}

TEST_F(RegExTest_113, SingleCharMatch_MatchesBoolFalse_113) {
  RegEx re('x');
  EXPECT_FALSE(re.Matches('y'));
}

TEST_F(RegExTest_113, SingleCharMatch_MatchesBoolString_113) {
  RegEx re('h');
  EXPECT_TRUE(re.Matches(std::string("h")));
}

TEST_F(RegExTest_113, SingleCharMatch_DoesNotMatchBoolStringMismatch_113) {
  RegEx re('h');
  EXPECT_FALSE(re.Matches(std::string("x")));
}

// =============================================================================
// Tests for range (REGEX_RANGE)
// =============================================================================

TEST_F(RegExTest_113, RangeMatch_MatchesCharInRange_113) {
  RegEx re('a', 'z');
  EXPECT_EQ(1, re.Match(std::string("m")));
}

TEST_F(RegExTest_113, RangeMatch_MatchesLowerBound_113) {
  RegEx re('a', 'z');
  EXPECT_EQ(1, re.Match(std::string("a")));
}

TEST_F(RegExTest_113, RangeMatch_MatchesUpperBound_113) {
  RegEx re('a', 'z');
  EXPECT_EQ(1, re.Match(std::string("z")));
}

TEST_F(RegExTest_113, RangeMatch_DoesNotMatchOutOfRange_113) {
  RegEx re('a', 'z');
  EXPECT_EQ(-1, re.Match(std::string("A")));
}

TEST_F(RegExTest_113, RangeMatch_EmptyStringNoMatch_113) {
  RegEx re('a', 'z');
  EXPECT_EQ(-1, re.Match(std::string("")));
}

TEST_F(RegExTest_113, RangeMatch_MatchesBoolTrue_113) {
  RegEx re('0', '9');
  EXPECT_TRUE(re.Matches('5'));
}

TEST_F(RegExTest_113, RangeMatch_MatchesBoolFalse_113) {
  RegEx re('0', '9');
  EXPECT_FALSE(re.Matches('a'));
}

// =============================================================================
// Tests for OR operator (|)
// =============================================================================

TEST_F(RegExTest_113, OrOperator_MatchesFirst_113) {
  RegEx a('a');
  RegEx b('b');
  RegEx re = a | b;
  EXPECT_EQ(1, re.Match(std::string("a")));
}

TEST_F(RegExTest_113, OrOperator_MatchesSecond_113) {
  RegEx a('a');
  RegEx b('b');
  RegEx re = a | b;
  EXPECT_EQ(1, re.Match(std::string("b")));
}

TEST_F(RegExTest_113, OrOperator_NoMatch_113) {
  RegEx a('a');
  RegEx b('b');
  RegEx re = a | b;
  EXPECT_EQ(-1, re.Match(std::string("c")));
}

// =============================================================================
// Tests for AND operator (&)
// =============================================================================

TEST_F(RegExTest_113, AndOperator_BothMatch_113) {
  RegEx range('a', 'z');
  RegEx specific('m');
  RegEx re = range & specific;
  EXPECT_EQ(1, re.Match(std::string("m")));
}

TEST_F(RegExTest_113, AndOperator_OnlyOneMatches_113) {
  RegEx range('a', 'f');
  RegEx specific('z');
  RegEx re = range & specific;
  EXPECT_EQ(-1, re.Match(std::string("z")));
}

// =============================================================================
// Tests for NOT operator (!)
// =============================================================================

TEST_F(RegExTest_113, NotOperator_InvertsMatch_113) {
  RegEx a('a');
  RegEx re = !a;
  // 'a' matches the original, so NOT should not match
  EXPECT_EQ(-1, re.Match(std::string("a")));
}

TEST_F(RegExTest_113, NotOperator_InvertsNoMatch_113) {
  RegEx a('a');
  RegEx re = !a;
  // 'b' does not match original, so NOT should match with length 1
  EXPECT_EQ(1, re.Match(std::string("b")));
}

TEST_F(RegExTest_113, NotOperator_EmptyString_113) {
  RegEx a('a');
  RegEx re = !a;
  EXPECT_EQ(-1, re.Match(std::string("")));
}

// =============================================================================
// Tests for sequence operator (+)
// =============================================================================

TEST_F(RegExTest_113, SeqOperator_MatchesConcatenation_113) {
  RegEx a('a');
  RegEx b('b');
  RegEx re = a + b;
  EXPECT_EQ(2, re.Match(std::string("ab")));
}

TEST_F(RegExTest_113, SeqOperator_PartialMatchFails_113) {
  RegEx a('a');
  RegEx b('b');
  RegEx re = a + b;
  EXPECT_EQ(-1, re.Match(std::string("ac")));
}

TEST_F(RegExTest_113, SeqOperator_FirstCharMismatch_113) {
  RegEx a('a');
  RegEx b('b');
  RegEx re = a + b;
  EXPECT_EQ(-1, re.Match(std::string("bb")));
}

TEST_F(RegExTest_113, SeqOperator_MatchesLongerString_113) {
  RegEx a('a');
  RegEx b('b');
  RegEx re = a + b;
  EXPECT_EQ(2, re.Match(std::string("abcdef")));
}

TEST_F(RegExTest_113, SeqOperator_EmptyString_113) {
  RegEx a('a');
  RegEx b('b');
  RegEx re = a + b;
  EXPECT_EQ(-1, re.Match(std::string("")));
}

// =============================================================================
// Tests for string-based RegEx (REGEX_OP)
// =============================================================================

// String constructor with SEQ-like op
// Note: The exact behavior depends on REGEX_OP values; testing with common patterns

// =============================================================================
// Tests with Stream input
// =============================================================================

TEST_F(RegExTest_113, StreamMatch_SingleChar_113) {
  RegEx re('h');
  auto stream = MakeStream("hello");
  EXPECT_EQ(1, re.Match(*stream));
}

TEST_F(RegExTest_113, StreamMatch_SingleCharNoMatch_113) {
  RegEx re('x');
  auto stream = MakeStream("hello");
  EXPECT_EQ(-1, re.Match(*stream));
}

TEST_F(RegExTest_113, StreamMatch_Range_113) {
  RegEx re('a', 'z');
  auto stream = MakeStream("hello");
  EXPECT_EQ(1, re.Match(*stream));
}

TEST_F(RegExTest_113, StreamMatch_RangeNoMatch_113) {
  RegEx re('A', 'Z');
  auto stream = MakeStream("hello");
  EXPECT_EQ(-1, re.Match(*stream));
}

TEST_F(RegExTest_113, StreamMatch_Sequence_113) {
  RegEx h('h');
  RegEx e('e');
  RegEx re = h + e;
  auto stream = MakeStream("hello");
  EXPECT_EQ(2, re.Match(*stream));
}

TEST_F(RegExTest_113, StreamMatch_EmptyStream_113) {
  RegEx re('a');
  auto stream = MakeStream("");
  EXPECT_EQ(-1, re.Match(*stream));
}

TEST_F(RegExTest_113, StreamMatches_BoolTrue_113) {
  RegEx re('h');
  auto stream = MakeStream("hello");
  EXPECT_TRUE(re.Matches(*stream));
}

TEST_F(RegExTest_113, StreamMatches_BoolFalse_113) {
  RegEx re('x');
  auto stream = MakeStream("hello");
  EXPECT_FALSE(re.Matches(*stream));
}

// =============================================================================
// Tests for complex compositions
// =============================================================================

TEST_F(RegExTest_113, ComplexOr_ThreeOptions_113) {
  RegEx a('a');
  RegEx b('b');
  RegEx c('c');
  RegEx re = a | b | c;
  EXPECT_EQ(1, re.Match(std::string("a")));
  EXPECT_EQ(1, re.Match(std::string("b")));
  EXPECT_EQ(1, re.Match(std::string("c")));
  EXPECT_EQ(-1, re.Match(std::string("d")));
}

TEST_F(RegExTest_113, ComplexSeq_ThreeChars_113) {
  RegEx a('a');
  RegEx b('b');
  RegEx c('c');
  RegEx re = a + b + c;
  EXPECT_EQ(3, re.Match(std::string("abc")));
  EXPECT_EQ(3, re.Match(std::string("abcdef")));
  EXPECT_EQ(-1, re.Match(std::string("abd")));
}

TEST_F(RegExTest_113, ComplexOrAndSeq_113) {
  RegEx a('a');
  RegEx b('b');
  RegEx c('c');
  // (a|b) + c
  RegEx re = (a | b) + c;
  EXPECT_EQ(2, re.Match(std::string("ac")));
  EXPECT_EQ(2, re.Match(std::string("bc")));
  EXPECT_EQ(-1, re.Match(std::string("cc")));
}

TEST_F(RegExTest_113, NotWithRange_113) {
  RegEx range('a', 'z');
  RegEx re = !range;
  EXPECT_EQ(-1, re.Match(std::string("m")));
  EXPECT_EQ(1, re.Match(std::string("M")));
  EXPECT_EQ(1, re.Match(std::string("5")));
}

TEST_F(RegExTest_113, EmptyRegex_MatchesBoolEmptyString_113) {
  RegEx re;
  EXPECT_TRUE(re.Matches(std::string("")));
}

TEST_F(RegExTest_113, EmptyRegex_MatchesBoolNonEmptyString_113) {
  RegEx re;
  // An empty regex matches with 0 length; Matches checks if Match >= 0
  EXPECT_TRUE(re.Matches(std::string("anything")));
}

// =============================================================================
// Tests for special characters
// =============================================================================

TEST_F(RegExTest_113, MatchNullChar_113) {
  RegEx re('\0');
  std::string s(1, '\0');
  // Matching null character
  int result = re.Match(s);
  // The behavior depends on implementation; just verify it doesn't crash
  (void)result;
}

TEST_F(RegExTest_113, MatchSpaceChar_113) {
  RegEx re(' ');
  EXPECT_EQ(1, re.Match(std::string(" ")));
  EXPECT_EQ(-1, re.Match(std::string("a")));
}

TEST_F(RegExTest_113, MatchNewlineChar_113) {
  RegEx re('\n');
  EXPECT_EQ(1, re.Match(std::string("\n")));
  EXPECT_EQ(-1, re.Match(std::string("a")));
}

TEST_F(RegExTest_113, MatchTabChar_113) {
  RegEx re('\t');
  EXPECT_EQ(1, re.Match(std::string("\t")));
  EXPECT_EQ(-1, re.Match(std::string(" ")));
}

// =============================================================================
// Tests for digit range
// =============================================================================

TEST_F(RegExTest_113, DigitRange_MatchesDigits_113) {
  RegEx re('0', '9');
  for (char c = '0'; c <= '9'; ++c) {
    EXPECT_EQ(1, re.Match(std::string(1, c))) << "Failed for char: " << c;
  }
}

TEST_F(RegExTest_113, DigitRange_DoesNotMatchLetters_113) {
  RegEx re('0', '9');
  EXPECT_EQ(-1, re.Match(std::string("a")));
  EXPECT_EQ(-1, re.Match(std::string("Z")));
}

// =============================================================================
// Stream with sequence match
// =============================================================================

TEST_F(RegExTest_113, StreamMatch_OrOperator_113) {
  RegEx a('h');
  RegEx b('w');
  RegEx re = a | b;
  
  auto stream1 = MakeStream("hello");
  EXPECT_EQ(1, re.Match(*stream1));
  
  auto stream2 = MakeStream("world");
  EXPECT_EQ(1, re.Match(*stream2));
  
  auto stream3 = MakeStream("xyz");
  EXPECT_EQ(-1, re.Match(*stream3));
}

TEST_F(RegExTest_113, StreamMatch_NotOperator_113) {
  RegEx a('x');
  RegEx re = !a;
  
  auto stream1 = MakeStream("hello");
  EXPECT_EQ(1, re.Match(*stream1));
  
  auto stream2 = MakeStream("xyz");
  EXPECT_EQ(-1, re.Match(*stream2));
}

TEST_F(RegExTest_113, AndOperator_RangeAndRange_113) {
  RegEx lower('a', 'f');
  RegEx hex('a', 'z');
  RegEx re = lower & hex;
  EXPECT_EQ(1, re.Match(std::string("c")));
  EXPECT_EQ(-1, re.Match(std::string("g")));
}

}  // namespace
}  // namespace YAML
