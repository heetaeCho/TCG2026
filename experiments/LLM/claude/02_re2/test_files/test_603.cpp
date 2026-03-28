#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "absl/strings/string_view.h"

namespace re2 {

// Helper function to compile a Prog from a regex pattern
static Prog* CompileProg(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = re->CompileToProg(0);
  re->Decref();
  return prog;
}

class DFATest_603 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Clean up any allocated progs
  }
};

// Test: SearchDFA with a simple pattern matches correctly
TEST_F(DFATest_603, SimpleMatch_603) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("say hello world", re));
}

// Test: SearchDFA with anchored pattern
TEST_F(DFATest_603, AnchoredMatch_603) {
  RE2 re("^hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("hello world", re));
  EXPECT_FALSE(RE2::PartialMatch("say hello", re));
}

// Test: SearchDFA with no match
TEST_F(DFATest_603, NoMatch_603) {
  RE2 re("xyz");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::PartialMatch("hello world", re));
}

// Test: SearchDFA with empty text
TEST_F(DFATest_603, EmptyText_603) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::PartialMatch("", re));
}

// Test: SearchDFA with empty pattern matches empty string
TEST_F(DFATest_603, EmptyPattern_603) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("anything", re));
  EXPECT_TRUE(RE2::PartialMatch("", re));
}

// Test: DFA with very small memory budget causes init failure
TEST_F(DFATest_603, VerySmallMemBudget_603) {
  // Using RE2 options to set very small DFA memory
  RE2::Options opts;
  opts.set_max_mem(1);  // extremely small
  RE2 re("a{100}", opts);
  // The regex might still be ok (RE2 falls back to NFA), but DFA may fail internally
  // We just test that we don't crash
  RE2::PartialMatch("aaaa", re);
}

// Test: SearchDFA with alternation
TEST_F(DFATest_603, AlternationMatch_603) {
  RE2 re("cat|dog");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("I have a cat", re));
  EXPECT_TRUE(RE2::PartialMatch("I have a dog", re));
  EXPECT_FALSE(RE2::PartialMatch("I have a bird", re));
}

// Test: SearchDFA with character class
TEST_F(DFATest_603, CharClassMatch_603) {
  RE2 re("[a-z]+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("hello", re));
  EXPECT_FALSE(RE2::PartialMatch("12345", re));
}

// Test: SearchDFA with repetition
TEST_F(DFATest_603, RepetitionMatch_603) {
  RE2 re("a{3,5}");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("aaa", re));
  EXPECT_TRUE(RE2::PartialMatch("aaaa", re));
  EXPECT_TRUE(RE2::PartialMatch("aaaaa", re));
  EXPECT_FALSE(RE2::PartialMatch("aa", re));
}

// Test: SearchDFA FullMatch
TEST_F(DFATest_603, FullMatch_603) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("hello world", re));
}

// Test: SearchDFA with longest match kind via Prog directly
TEST_F(DFATest_603, LongestMatchKind_603) {
  Prog* prog = CompileProg("a+");
  ASSERT_NE(prog, nullptr);
  
  // Use SearchDFA with longest match kind
  bool failed = false;
  absl::string_view text("aaaa");
  absl::string_view match;
  bool result = prog->SearchDFA(text, text, Prog::kAnchored,
                                 Prog::kLongestMatch, &match, &failed, nullptr);
  EXPECT_TRUE(result || failed);  // Either it succeeds or reports failure
  
  delete prog;
}

// Test: SearchDFA with first match kind
TEST_F(DFATest_603, FirstMatchKind_603) {
  Prog* prog = CompileProg("a+");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("aaaa");
  absl::string_view match;
  bool result = prog->SearchDFA(text, text, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_TRUE(result || failed);
  
  delete prog;
}

// Test: BuildEntireDFA
TEST_F(DFATest_603, BuildEntireDFA_603) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);  // 1MB
  
  int count = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(count, 0);
  
  delete prog;
}

// Test: PossibleMatchRange
TEST_F(DFATest_603, PossibleMatchRange_603) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min_str, max_str);
  
  delete prog;
}

// Test: PossibleMatchRange with maxlen of 0
TEST_F(DFATest_603, PossibleMatchRangeZeroMaxlen_603) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 0);
  // Should still return some result without crashing
  (void)result;
  
  delete prog;
}

// Test: DFA search with dot-star pattern
TEST_F(DFATest_603, DotStarPattern_603) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("anything at all", re));
  EXPECT_TRUE(RE2::FullMatch("", re));
}

// Test: DFA with complex pattern
TEST_F(DFATest_603, ComplexPattern_603) {
  RE2 re("(foo|bar)baz[0-9]+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("foobaz123", re));
  EXPECT_TRUE(RE2::PartialMatch("barbaz99", re));
  EXPECT_FALSE(RE2::PartialMatch("qazbaz123", re));
  EXPECT_FALSE(RE2::PartialMatch("foobaz", re));
}

// Test: DFA search on large text
TEST_F(DFATest_603, LargeText_603) {
  RE2 re("needle");
  ASSERT_TRUE(re.ok());
  
  std::string large_text(100000, 'a');
  large_text += "needle";
  EXPECT_TRUE(RE2::PartialMatch(large_text, re));
}

// Test: DFA search with word boundary-like patterns
TEST_F(DFATest_603, WordBoundaryLike_603) {
  RE2 re("\\bhello\\b");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("say hello world", re));
  EXPECT_FALSE(RE2::PartialMatch("sayhelloworld", re));
}

// Test: SearchDFA unanchored
TEST_F(DFATest_603, UnanchoredSearch_603) {
  Prog* prog = CompileProg("test");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  
  bool failed = false;
  absl::string_view text("this is a test string");
  absl::string_view match;
  bool result = prog->SearchDFA(text, text, Prog::kUnanchored,
                                 Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_TRUE(result);
  }
  
  delete prog;
}

// Test: SearchDFA anchored with non-matching input
TEST_F(DFATest_603, AnchoredNoMatch_603) {
  Prog* prog = CompileProg("test");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  
  bool failed = false;
  absl::string_view text("no match here");
  absl::string_view match;
  bool result = prog->SearchDFA(text, text, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_FALSE(result);
  }
  
  delete prog;
}

// Test: Multiple searches reuse DFA cache
TEST_F(DFATest_603, MultiplSearchesReuseDFA_603) {
  RE2 re("pattern");
  ASSERT_TRUE(re.ok());
  
  for (int i = 0; i < 100; i++) {
    EXPECT_TRUE(RE2::PartialMatch("find the pattern here", re));
    EXPECT_FALSE(RE2::PartialMatch("nothing here", re));
  }
}

// Test: DFA with single character pattern
TEST_F(DFATest_603, SingleCharPattern_603) {
  RE2 re("x");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("x", re));
  EXPECT_TRUE(RE2::PartialMatch("abcxdef", re));
  EXPECT_FALSE(RE2::PartialMatch("abcdef", re));
}

// Test: DFA with special regex characters
TEST_F(DFATest_603, SpecialCharsPattern_603) {
  RE2 re("\\.");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("hello.world", re));
  EXPECT_FALSE(RE2::PartialMatch("helloworld", re));
}

// Test: BuildEntireDFA with longest match
TEST_F(DFATest_603, BuildEntireDFALongestMatch_603) {
  Prog* prog = CompileProg("a+");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  
  int count = prog->BuildEntireDFA(Prog::kLongestMatch, nullptr);
  EXPECT_GT(count, 0);
  
  delete prog;
}

// Test: DFA bail when slow flag
TEST_F(DFATest_603, BailWhenSlow_603) {
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  
  RE2 re("a{0,100}b");
  ASSERT_TRUE(re.ok());
  // This should still work, DFA may bail but RE2 falls back
  bool result = RE2::PartialMatch("b", re);
  EXPECT_TRUE(result);
  
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

}  // namespace re2
