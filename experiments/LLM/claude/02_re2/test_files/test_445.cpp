#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"

// Since DFA::Workq is an internal class defined in dfa.cc, we need to test
// observable behavior through the RE2/DFA public interface.
// We test DFA behavior indirectly through RE2 matching which exercises DFA
// and its internal Workq.

namespace re2 {

class DFAWorkqIndirectTest_445 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that basic DFA matching works (exercises Workq internally)
TEST_F(DFAWorkqIndirectTest_445, BasicMatch_445) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test with alternation (exercises mark/insert in Workq)
TEST_F(DFAWorkqIndirectTest_445, AlternationMatch_445) {
  RE2 re("(abc|def|ghi)");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_TRUE(RE2::FullMatch("def", re));
  EXPECT_TRUE(RE2::FullMatch("ghi", re));
  EXPECT_FALSE(RE2::FullMatch("xyz", re));
}

// Test with repetition (exercises Workq size/insert behavior)
TEST_F(DFAWorkqIndirectTest_445, RepetitionMatch_445) {
  RE2 re("a*b+c?");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("b", re));
  EXPECT_TRUE(RE2::FullMatch("aaab", re));
  EXPECT_TRUE(RE2::FullMatch("aaabbc", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
}

// Test empty pattern
TEST_F(DFAWorkqIndirectTest_445, EmptyPattern_445) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_FALSE(RE2::FullMatch("a", re));
}

// Test complex pattern that exercises DFA state creation heavily
TEST_F(DFAWorkqIndirectTest_445, ComplexPattern_445) {
  RE2 re("(a|b)(c|d)(e|f)(g|h)");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("aceg", re));
  EXPECT_TRUE(RE2::FullMatch("bdfh", re));
  EXPECT_FALSE(RE2::FullMatch("abcd", re));
}

// Test partial match (exercises DFA differently than full match)
TEST_F(DFAWorkqIndirectTest_445, PartialMatch_445) {
  RE2 re("world");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("hello world", re));
  EXPECT_FALSE(RE2::PartialMatch("hello earth", re));
}

// Test with character classes
TEST_F(DFAWorkqIndirectTest_445, CharClassMatch_445) {
  RE2 re("[a-z]+[0-9]+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc123", re));
  EXPECT_FALSE(RE2::FullMatch("123abc", re));
}

// Test boundary: single character
TEST_F(DFAWorkqIndirectTest_445, SingleCharMatch_445) {
  RE2 re("x");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("x", re));
  EXPECT_FALSE(RE2::FullMatch("y", re));
  EXPECT_FALSE(RE2::FullMatch("xx", re));
}

// Test with nested groups exercising Workq mark behavior
TEST_F(DFAWorkqIndirectTest_445, NestedGroups_445) {
  RE2 re("((a+)(b+))+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("aabb", re));
  EXPECT_TRUE(RE2::FullMatch("ababaabb", re));
  EXPECT_FALSE(RE2::FullMatch("ba", re));
}

// Test long input string
TEST_F(DFAWorkqIndirectTest_445, LongInput_445) {
  RE2 re("a*");
  ASSERT_TRUE(re.ok());
  std::string long_input(10000, 'a');
  EXPECT_TRUE(RE2::FullMatch(long_input, re));
}

}  // namespace re2
