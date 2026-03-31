#include "re2/re2.h"
#include "re2/prog.h"
#include "gtest/gtest.h"
#include <string>

namespace re2 {

// Since Workq is a private class inside DFA (defined in dfa.cc),
// we test it indirectly through DFA/RE2 matching which exercises
// the Workq insert, mark, clear, and size operations.

class DFAWorkqTest_446 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test basic DFA matching which exercises Workq insert operations
TEST_F(DFAWorkqTest_446, BasicMatch_446) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test DFA with alternation which exercises Workq mark operations
TEST_F(DFAWorkqTest_446, AlternationMatch_446) {
  RE2 re("(abc|def|ghi)");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_TRUE(RE2::FullMatch("def", re));
  EXPECT_TRUE(RE2::FullMatch("ghi", re));
  EXPECT_FALSE(RE2::FullMatch("xyz", re));
}

// Test DFA with repetition which exercises Workq insert_new and mark
TEST_F(DFAWorkqTest_446, RepetitionMatch_446) {
  RE2 re("a*b+c?");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("b", re));
  EXPECT_TRUE(RE2::FullMatch("ab", re));
  EXPECT_TRUE(RE2::FullMatch("aaabbc", re));
  EXPECT_TRUE(RE2::FullMatch("aaabb", re));
  EXPECT_FALSE(RE2::FullMatch("a", re));
}

// Test DFA with complex pattern exercising multiple Workq operations
TEST_F(DFAWorkqTest_446, ComplexPattern_446) {
  RE2 re("(a|b)*abb");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abb", re));
  EXPECT_TRUE(RE2::FullMatch("aabb", re));
  EXPECT_TRUE(RE2::FullMatch("babb", re));
  EXPECT_TRUE(RE2::FullMatch("abababb", re));
  EXPECT_FALSE(RE2::FullMatch("ab", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
}

// Test DFA partial match which exercises different DFA search paths
TEST_F(DFAWorkqTest_446, PartialMatch_446) {
  RE2 re("\\d+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("abc123def", re));
  EXPECT_FALSE(RE2::PartialMatch("abcdef", re));
}

// Test empty pattern - boundary case
TEST_F(DFAWorkqTest_446, EmptyPattern_446) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_FALSE(RE2::FullMatch("a", re));
}

// Test single character - minimal Workq usage
TEST_F(DFAWorkqTest_446, SingleChar_446) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
  EXPECT_FALSE(RE2::FullMatch("aa", re));
}

// Test character class which exercises multiple inserts into Workq
TEST_F(DFAWorkqTest_446, CharacterClass_446) {
  RE2 re("[a-z]+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("HELLO", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
}

// Test nested groups exercising deep Workq mark nesting
TEST_F(DFAWorkqTest_446, NestedGroups_446) {
  RE2 re("((a|b)(c|d))+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("ac", re));
  EXPECT_TRUE(RE2::FullMatch("bd", re));
  EXPECT_TRUE(RE2::FullMatch("acbd", re));
  EXPECT_FALSE(RE2::FullMatch("ab", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
}

// Test long input to exercise DFA state cache and Workq reuse
TEST_F(DFAWorkqTest_446, LongInput_446) {
  RE2 re("(ab)+");
  ASSERT_TRUE(re.ok());
  std::string input;
  for (int i = 0; i < 1000; i++) {
    input += "ab";
  }
  EXPECT_TRUE(RE2::FullMatch(input, re));
  EXPECT_FALSE(RE2::FullMatch(input + "a", re));
}

// Test DFA with dot-star which stresses Workq clear and re-insert
TEST_F(DFAWorkqTest_446, DotStar_446) {
  RE2 re(".*abc.*");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_TRUE(RE2::FullMatch("xyzabcdef", re));
  EXPECT_FALSE(RE2::FullMatch("ab", re));
}

// Test DFA with anchored pattern
TEST_F(DFAWorkqTest_446, AnchoredPattern_446) {
  RE2 re("^abc$");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_FALSE(RE2::FullMatch("xabc", re));
  EXPECT_FALSE(RE2::FullMatch("abcx", re));
}

// Test with many alternatives to stress Workq capacity
TEST_F(DFAWorkqTest_446, ManyAlternatives_446) {
  RE2 re("(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("z", re));
  EXPECT_FALSE(RE2::FullMatch("A", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
}

// Test optional and counted repetition
TEST_F(DFAWorkqTest_446, CountedRepetition_446) {
  RE2 re("a{2,4}b?");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("aa", re));
  EXPECT_TRUE(RE2::FullMatch("aab", re));
  EXPECT_TRUE(RE2::FullMatch("aaaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaab", re));
  EXPECT_FALSE(RE2::FullMatch("a", re));
  EXPECT_FALSE(RE2::FullMatch("aaaaa", re));
}

// Test DeadState path - pattern that can't match
TEST_F(DFAWorkqTest_446, NoMatchPossible_446) {
  RE2 re("[^\\s\\S]");  // matches nothing
  // This pattern matches a character that is neither whitespace nor non-whitespace
  // which is impossible
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("a", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
}

}  // namespace re2
