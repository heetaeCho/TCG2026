#include <string>
#include <memory>
#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/sparse_set.h"
#include "absl/strings/string_view.h"

namespace re2 {

// We test the DFA::Search functionality indirectly through Prog::SearchDFA,
// since DFA is an internal class created by Prog::GetDFA (which is private).
// Prog::SearchDFA is the public interface that exercises DFA::Search.

class DFASearchTest_453 : public ::testing::Test {
 protected:
  // Helper to compile a pattern into a Prog
  struct ProgHolder {
    Regexp* re;
    Prog* prog;
    ProgHolder(const std::string& pattern) {
      RegexpStatus status;
      re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
      EXPECT_TRUE(re != nullptr) << status.Text();
      prog = re->CompileToProg(0);
      EXPECT_TRUE(prog != nullptr);
    }
    ~ProgHolder() {
      delete prog;
      re->Decref();
    }
  };
};

// Test basic match with a simple pattern
TEST_F(DFASearchTest_453, SimpleMatch_453) {
  ProgHolder ph("hello");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("hello world");
  bool result = ph.prog->SearchDFA(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);
}

// Test no match
TEST_F(DFASearchTest_453, NoMatch_453) {
  ProgHolder ph("hello");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("world");
  bool result = ph.prog->SearchDFA(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_FALSE(result);
}

// Test unanchored search
TEST_F(DFASearchTest_453, UnanchoredMatch_453) {
  ProgHolder ph("world");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("hello world");
  bool result = ph.prog->SearchDFA(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);
}

// Test anchored search fails when pattern not at start
TEST_F(DFASearchTest_453, AnchoredNoMatchMiddle_453) {
  ProgHolder ph("world");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("hello world");
  bool result = ph.prog->SearchDFA(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_FALSE(result);
}

// Test empty text with empty pattern
TEST_F(DFASearchTest_453, EmptyTextEmptyPattern_453) {
  ProgHolder ph("");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("");
  bool result = ph.prog->SearchDFA(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);
}

// Test empty text with non-empty pattern
TEST_F(DFASearchTest_453, EmptyTextNonEmptyPattern_453) {
  ProgHolder ph("abc");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("");
  bool result = ph.prog->SearchDFA(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_FALSE(result);
}

// Test longest match kind
TEST_F(DFASearchTest_453, LongestMatch_453) {
  ProgHolder ph("a+");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("aaaa");
  bool result = ph.prog->SearchDFA(text, text, Prog::kAnchored,
                                     Prog::kLongestMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);
}

// Test with character class
TEST_F(DFASearchTest_453, CharacterClassMatch_453) {
  ProgHolder ph("[a-z]+");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("hello");
  bool result = ph.prog->SearchDFA(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);
}

// Test with alternation
TEST_F(DFASearchTest_453, AlternationMatch_453) {
  ProgHolder ph("cat|dog");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("dog");
  bool result = ph.prog->SearchDFA(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);
}

// Test with optional
TEST_F(DFASearchTest_453, OptionalMatch_453) {
  ProgHolder ph("ab?c");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("ac");
  bool result = ph.prog->SearchDFA(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);
}

// Test with repetition
TEST_F(DFASearchTest_453, RepetitionMatch_453) {
  ProgHolder ph("a{3}");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("aaa");
  bool result = ph.prog->SearchDFA(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);
}

// Test repetition no match (too few)
TEST_F(DFASearchTest_453, RepetitionNoMatch_453) {
  ProgHolder ph("a{3}");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("aa");
  bool result = ph.prog->SearchDFA(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_FALSE(result);
}

// Test dot match
TEST_F(DFASearchTest_453, DotMatch_453) {
  ProgHolder ph("h.llo");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("hello");
  bool result = ph.prog->SearchDFA(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);
}

// Test with a larger text
TEST_F(DFASearchTest_453, LargeTextMatch_453) {
  ProgHolder ph("needle");
  bool failed = false;
  absl::string_view match;
  std::string large_text(10000, 'x');
  large_text += "needle";
  large_text += std::string(10000, 'y');
  absl::string_view text(large_text);
  bool result = ph.prog->SearchDFA(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);
}

// Test BuildEntireDFA
TEST_F(DFASearchTest_453, BuildEntireDFA_453) {
  ProgHolder ph("abc");
  int num_states = ph.prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  // Should build at least some states
  EXPECT_GT(num_states, 0);
}

// Test PossibleMatchRange
TEST_F(DFASearchTest_453, PossibleMatchRange_453) {
  ProgHolder ph("hello");
  std::string min_str, max_str;
  bool result = ph.prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min_str, "hello");
  EXPECT_GE(max_str, "hello");
}

// Test PossibleMatchRange with wildcard
TEST_F(DFASearchTest_453, PossibleMatchRangeWildcard_453) {
  ProgHolder ph("[a-z]+");
  std::string min_str, max_str;
  bool result = ph.prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  // min should start with 'a'
  EXPECT_FALSE(min_str.empty());
}

// Test via RE2 interface for higher-level DFA search validation
TEST_F(DFASearchTest_453, RE2FullMatch_453) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
  EXPECT_FALSE(RE2::FullMatch("hello", "world"));
}

TEST_F(DFASearchTest_453, RE2PartialMatch_453) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "world"));
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

// Test with single character text and pattern
TEST_F(DFASearchTest_453, SingleCharMatch_453) {
  ProgHolder ph("a");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("a");
  bool result = ph.prog->SearchDFA(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);
}

// Test single char no match
TEST_F(DFASearchTest_453, SingleCharNoMatch_453) {
  ProgHolder ph("a");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("b");
  bool result = ph.prog->SearchDFA(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_FALSE(result);
}

// Test with context different from text
TEST_F(DFASearchTest_453, DifferentContext_453) {
  ProgHolder ph("\\bworld\\b");
  bool failed = false;
  absl::string_view match;
  std::string full = "hello world foo";
  absl::string_view context(full);
  // Search only in the "world" portion
  absl::string_view text(full.data() + 6, 5);  // "world"
  bool result = ph.prog->SearchDFA(text, context, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);
}

// Test that DFA search with very low memory budget might set failed
TEST_F(DFASearchTest_453, LowMemoryBudget_453) {
  // This tests that the DFA handles memory constraints.
  // With a complex pattern and tiny memory, it may fail gracefully.
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]{1,100}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  // Use a very small memory limit
  Prog* prog = re->CompileToProg(256);
  if (prog != nullptr) {
    bool failed = false;
    absl::string_view match;
    std::string large(1000, 'a');
    absl::string_view text(large);
    prog->SearchDFA(text, text, Prog::kUnanchored,
                    Prog::kFirstMatch, &match, &failed, nullptr);
    // We just check it doesn't crash. failed might be true or false.
    delete prog;
  }
  re->Decref();
}

// Test star pattern
TEST_F(DFASearchTest_453, StarPattern_453) {
  ProgHolder ph("a*");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("");
  bool result = ph.prog->SearchDFA(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);
}

// Test plus pattern with no match on empty
TEST_F(DFASearchTest_453, PlusPatternEmpty_453) {
  ProgHolder ph("a+");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("");
  bool result = ph.prog->SearchDFA(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_FALSE(result);
}

// Test full match kind
TEST_F(DFASearchTest_453, FullMatchKind_453) {
  ProgHolder ph("hello");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("hello");
  bool result = ph.prog->SearchDFA(text, text, Prog::kAnchored,
                                     Prog::kFullMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);
}

// Test full match kind partial text should fail
TEST_F(DFASearchTest_453, FullMatchKindPartialFails_453) {
  ProgHolder ph("hel");
  bool failed = false;
  absl::string_view match;
  absl::string_view text("hello");
  bool result = ph.prog->SearchDFA(text, text, Prog::kAnchored,
                                     Prog::kFullMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_FALSE(result);
}

}  // namespace re2
