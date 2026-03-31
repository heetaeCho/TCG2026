#include "re2/re2.h"
#include "re2/prog.h"
#include "gtest/gtest.h"
#include <string>
#include <vector>

namespace re2 {

// Test DFA through RE2's public interface, which is the observable behavior
// of the DFA implementation.

class DFATest_436 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test basic matching through DFA (normal operation)
TEST_F(DFATest_436, BasicMatch_436) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test partial match through DFA
TEST_F(DFATest_436, PartialMatch_436) {
  RE2 re("ell");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("hello", re));
  EXPECT_FALSE(RE2::PartialMatch("world", re));
}

// Test empty string matching
TEST_F(DFATest_436, EmptyStringMatch_436) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::PartialMatch("hello", re));
}

// Test empty pattern with empty string
TEST_F(DFATest_436, EmptyPatternEmptyString_436) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
}

// Test alternation patterns that exercise DFA state transitions
TEST_F(DFATest_436, AlternationMatch_436) {
  RE2 re("(abc|def|ghi)");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_TRUE(RE2::FullMatch("def", re));
  EXPECT_TRUE(RE2::FullMatch("ghi", re));
  EXPECT_FALSE(RE2::FullMatch("xyz", re));
}

// Test repetition patterns
TEST_F(DFATest_436, RepetitionMatch_436) {
  RE2 re("a*b+c?");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("b", re));
  EXPECT_TRUE(RE2::FullMatch("aaabbc", re));
  EXPECT_TRUE(RE2::FullMatch("bb", re));
  EXPECT_FALSE(RE2::FullMatch("ac", re));
}

// Test character class patterns
TEST_F(DFATest_436, CharClassMatch_436) {
  RE2 re("[a-z]+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("Hello", re));
  EXPECT_FALSE(RE2::FullMatch("123", re));
}

// Test that DFA handles long strings correctly
TEST_F(DFATest_436, LongStringMatch_436) {
  RE2 re("a+");
  ASSERT_TRUE(re.ok());
  std::string long_string(10000, 'a');
  EXPECT_TRUE(RE2::FullMatch(long_string, re));
  long_string += 'b';
  EXPECT_FALSE(RE2::FullMatch(long_string, re));
}

// Test anchored vs unanchored matching
TEST_F(DFATest_436, AnchoredMatch_436) {
  RE2 re("^abc$");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_FALSE(RE2::FullMatch("xabc", re));
  EXPECT_FALSE(RE2::FullMatch("abcx", re));
}

// Test DFA with no match possible (dead state scenario)
TEST_F(DFATest_436, NoMatchDeadState_436) {
  RE2 re("xyz");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("abc", re));
  EXPECT_FALSE(RE2::PartialMatch("abc", re));
}

// Test dot-star pattern (full match state scenario)
TEST_F(DFATest_436, DotStarFullMatch_436) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("anything at all!", re));
  EXPECT_TRUE(RE2::FullMatch("", re));
}

// Test complex pattern with multiple DFA states
TEST_F(DFATest_436, ComplexPattern_436) {
  RE2 re("(a[bc]d|e[fg]h)+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abd", re));
  EXPECT_TRUE(RE2::FullMatch("acd", re));
  EXPECT_TRUE(RE2::FullMatch("efh", re));
  EXPECT_TRUE(RE2::FullMatch("egh", re));
  EXPECT_TRUE(RE2::FullMatch("abdefh", re));
  EXPECT_FALSE(RE2::FullMatch("aed", re));
}

// Test boundary: single character match
TEST_F(DFATest_436, SingleCharMatch_436) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_FALSE(RE2::FullMatch("b", re));
  EXPECT_FALSE(RE2::FullMatch("aa", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
}

// Test with special characters that might map to MatchSep or Mark values
TEST_F(DFATest_436, SpecialByteValues_436) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  std::string s;
  s.push_back('\x00');
  s.push_back('\x01');
  s.push_back('\xff');
  EXPECT_TRUE(RE2::FullMatch(s, re));
}

// Test word boundary patterns
TEST_F(DFATest_436, WordBoundary_436) {
  RE2 re("\\bhello\\b");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("say hello world", re));
  EXPECT_FALSE(RE2::PartialMatch("sayhelloworld", re));
}

// Test that DFA works with case-insensitive flag
TEST_F(DFATest_436, CaseInsensitive_436) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("HeLLo", re));
}

// Test multiple consecutive matches (exercises state caching)
TEST_F(DFATest_436, RepeatedMatching_436) {
  RE2 re("[0-9]+");
  ASSERT_TRUE(re.ok());
  for (int i = 0; i < 100; i++) {
    std::string s = std::to_string(i);
    EXPECT_TRUE(RE2::FullMatch(s, re));
  }
}

// Test pattern that results in many DFA states
TEST_F(DFATest_436, ManyStatesPattern_436) {
  RE2 re("(a|b)(c|d)(e|f)(g|h)(i|j)");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("acegi", re));
  EXPECT_TRUE(RE2::FullMatch("bdfhj", re));
  EXPECT_FALSE(RE2::FullMatch("abcde", re));
}

// Test invalid regex
TEST_F(DFATest_436, InvalidRegex_436) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
}

}  // namespace re2
