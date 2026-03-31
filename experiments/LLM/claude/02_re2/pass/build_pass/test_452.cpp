#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/sparse_set.h"
#include "absl/strings/string_view.h"

#include <string>
#include <memory>

namespace re2 {

// Helper to compile a pattern into a Prog
class DFATest_452 : public ::testing::Test {
 protected:
  std::unique_ptr<Prog> CompileProg(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re == nullptr) return nullptr;
    std::unique_ptr<Prog> prog(re->CompileToProg(0));
    re->Decref();
    return prog;
  }
};

// Test DFA Search with a simple pattern - normal match
TEST_F(DFATest_452, SearchFindsMatch_452) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("say hello world", re));
}

// Test DFA Search with no match
TEST_F(DFATest_452, SearchNoMatch_452) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::PartialMatch("goodbye world", re));
}

// Test DFA Search with empty text
TEST_F(DFATest_452, SearchEmptyText_452) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::PartialMatch("", re));
}

// Test DFA Search with empty pattern
TEST_F(DFATest_452, SearchEmptyPattern_452) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("anything", re));
}

// Test DFA Search with anchored match
TEST_F(DFATest_452, SearchAnchoredMatch_452) {
  RE2 re("^hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("hello world", re));
  EXPECT_FALSE(RE2::PartialMatch("say hello", re));
}

// Test DFA Search with full match
TEST_F(DFATest_452, SearchFullMatch_452) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("hello world", re));
}

// Test DFA PossibleMatchRange via Prog interface
TEST_F(DFATest_452, PossibleMatchRange_452) {
  auto prog = CompileProg("abc[def]ghi");
  ASSERT_NE(prog, nullptr);
  std::string min_match, max_match;
  bool result = prog->PossibleMatchRange(&min_match, &max_match, 10);
  EXPECT_TRUE(result);
  EXPECT_FALSE(min_match.empty());
  EXPECT_FALSE(max_match.empty());
  EXPECT_LE(min_match, max_match);
}

// Test PossibleMatchRange with maxlen boundary
TEST_F(DFATest_452, PossibleMatchRangeSmallMaxlen_452) {
  auto prog = CompileProg("abcdefghij");
  ASSERT_NE(prog, nullptr);
  std::string min_match, max_match;
  bool result = prog->PossibleMatchRange(&min_match, &max_match, 1);
  EXPECT_TRUE(result);
}

// Test DFA with complex regex patterns
TEST_F(DFATest_452, SearchComplexPattern_452) {
  RE2 re("[a-z]+[0-9]{2,4}");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("abc123", re));
  EXPECT_FALSE(RE2::PartialMatch("ABC", re));
}

// Test DFA BuildAllStates via Prog
TEST_F(DFATest_452, BuildAllStates_452) {
  auto prog = CompileProg("ab");
  ASSERT_NE(prog, nullptr);
  int count = prog->BuildEntireDFA(Prog::kManyMatch, nullptr);
  // count should be a non-negative number of states
  EXPECT_GE(count, 0);
}

// Test DFA with alternation pattern
TEST_F(DFATest_452, SearchAlternation_452) {
  RE2 re("cat|dog");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("I have a cat", re));
  EXPECT_TRUE(RE2::PartialMatch("I have a dog", re));
  EXPECT_FALSE(RE2::PartialMatch("I have a bird", re));
}

// Test DFA with repetition
TEST_F(DFATest_452, SearchRepetition_452) {
  RE2 re("a{3,5}");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("aaa", re));
  EXPECT_TRUE(RE2::PartialMatch("aaaaa", re));
  EXPECT_FALSE(RE2::PartialMatch("aa", re));
}

// Test DFA with dot-star pattern
TEST_F(DFATest_452, SearchDotStar_452) {
  RE2 re("a.*b");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("aXYZb", re));
  EXPECT_TRUE(RE2::PartialMatch("ab", re));
  EXPECT_FALSE(RE2::PartialMatch("ba", re));
}

// Test that a very small memory budget still works or fails gracefully
TEST_F(DFATest_452, SmallMemoryBudget_452) {
  RE2::Options opts;
  opts.set_max_mem(256);
  RE2 re("a{100}", opts);
  // Even with small memory, the regex should be usable or report issues gracefully
  if (re.ok()) {
    // If it compiled, search should not crash
    bool result = RE2::PartialMatch("aaaa", re);
    (void)result;  // We just check it doesn't crash
  }
}

// Test DFA with character class
TEST_F(DFATest_452, SearchCharacterClass_452) {
  RE2 re("[abc]+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("abc", re));
  EXPECT_TRUE(RE2::PartialMatch("xyz abc", re));
  EXPECT_FALSE(RE2::PartialMatch("xyz", re));
}

// Test DFA with unicode-like patterns
TEST_F(DFATest_452, SearchWordBoundary_452) {
  RE2 re("\\bword\\b");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("a word here", re));
  EXPECT_FALSE(RE2::PartialMatch("awordhere", re));
}

// Test PossibleMatchRange with zero maxlen
TEST_F(DFATest_452, PossibleMatchRangeZeroMaxlen_452) {
  auto prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  std::string min_match, max_match;
  // Zero maxlen is a boundary condition
  bool result = prog->PossibleMatchRange(&min_match, &max_match, 0);
  // Result may be false since maxlen=0 is degenerate
  (void)result;
}

// Test DFA search on single character text
TEST_F(DFATest_452, SearchSingleChar_452) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("a", re));
  EXPECT_FALSE(RE2::PartialMatch("b", re));
}

// Test DFA with longest match semantics
TEST_F(DFATest_452, SearchLongestMatch_452) {
  RE2::Options opts;
  opts.set_longest_match(true);
  RE2 re("a+", opts);
  ASSERT_TRUE(re.ok());
  std::string match;
  EXPECT_TRUE(RE2::PartialMatch("aaa", re, &match));
  EXPECT_EQ(match, "aaa");
}

}  // namespace re2
