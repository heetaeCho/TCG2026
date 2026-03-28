#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/sparse_set.h"
#include "absl/strings/string_view.h"
#include <string>
#include <memory>

namespace re2 {

class DFATest_605 : public ::testing::Test {
 protected:
  Prog* CompilePattern(const char* pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re == nullptr) return nullptr;
    Prog* prog = re->CompileToProg(0);
    re->Decref();
    return prog;
  }
};

// Test that a simple DFA search works for a basic pattern
TEST_F(DFATest_605, BasicSearchMatch_605) {
  std::unique_ptr<Prog> prog(CompilePattern("hello"));
  ASSERT_NE(prog, nullptr);

  bool failed = false;
  bool matched = prog->SearchDFA("hello world", "hello world",
                                  Prog::kAnchored, Prog::kFirstMatch,
                                  nullptr, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
}

// Test that DFA search returns no match for non-matching text
TEST_F(DFATest_605, BasicSearchNoMatch_605) {
  std::unique_ptr<Prog> prog(CompilePattern("hello"));
  ASSERT_NE(prog, nullptr);

  bool failed = false;
  bool matched = prog->SearchDFA("world", "world",
                                  Prog::kAnchored, Prog::kFirstMatch,
                                  nullptr, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_FALSE(matched);
}

// Test DFA search with unanchored match
TEST_F(DFATest_605, UnanchoredSearch_605) {
  std::unique_ptr<Prog> prog(CompilePattern("llo"));
  ASSERT_NE(prog, nullptr);

  bool failed = false;
  bool matched = prog->SearchDFA("hello", "hello",
                                  Prog::kUnanchored, Prog::kFirstMatch,
                                  nullptr, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
}

// Test DFA search on empty text with pattern that matches empty
TEST_F(DFATest_605, EmptyTextEmptyPattern_605) {
  std::unique_ptr<Prog> prog(CompilePattern(""));
  ASSERT_NE(prog, nullptr);

  bool failed = false;
  bool matched = prog->SearchDFA("", "",
                                  Prog::kAnchored, Prog::kFirstMatch,
                                  nullptr, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
}

// Test DFA search on empty text with non-empty pattern
TEST_F(DFATest_605, EmptyTextNonEmptyPattern_605) {
  std::unique_ptr<Prog> prog(CompilePattern("abc"));
  ASSERT_NE(prog, nullptr);

  bool failed = false;
  bool matched = prog->SearchDFA("", "",
                                  Prog::kAnchored, Prog::kFirstMatch,
                                  nullptr, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_FALSE(matched);
}

// Test PossibleMatchRange
TEST_F(DFATest_605, PossibleMatchRange_605) {
  std::unique_ptr<Prog> prog(CompilePattern("abc"));
  ASSERT_NE(prog, nullptr);

  std::string min_match, max_match;
  bool result = prog->PossibleMatchRange(&min_match, &max_match, 10);
  EXPECT_TRUE(result);
  EXPECT_FALSE(min_match.empty());
  EXPECT_FALSE(max_match.empty());
  EXPECT_LE(min_match, max_match);
}

// Test PossibleMatchRange with maxlen = 0
TEST_F(DFATest_605, PossibleMatchRangeZeroMaxlen_605) {
  std::unique_ptr<Prog> prog(CompilePattern("abc"));
  ASSERT_NE(prog, nullptr);

  std::string min_match, max_match;
  bool result = prog->PossibleMatchRange(&min_match, &max_match, 0);
  // With maxlen 0, behavior depends on implementation but should not crash
  (void)result;
}

// Test BuildAllStates with a simple pattern
TEST_F(DFATest_605, BuildAllStates_605) {
  std::unique_ptr<Prog> prog(CompilePattern("a"));
  ASSERT_NE(prog, nullptr);

  int count = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  // Should build at least some states
  EXPECT_GE(count, 0);
}

// Test DFA with alternation pattern
TEST_F(DFATest_605, AlternationPattern_605) {
  std::unique_ptr<Prog> prog(CompilePattern("abc|def"));
  ASSERT_NE(prog, nullptr);

  bool failed = false;
  bool matched1 = prog->SearchDFA("abc", "abc",
                                   Prog::kAnchored, Prog::kFirstMatch,
                                   nullptr, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched1);

  bool matched2 = prog->SearchDFA("def", "def",
                                   Prog::kAnchored, Prog::kFirstMatch,
                                   nullptr, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched2);

  bool matched3 = prog->SearchDFA("ghi", "ghi",
                                   Prog::kAnchored, Prog::kFirstMatch,
                                   nullptr, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_FALSE(matched3);
}

// Test DFA with repetition
TEST_F(DFATest_605, RepetitionPattern_605) {
  std::unique_ptr<Prog> prog(CompilePattern("a+"));
  ASSERT_NE(prog, nullptr);

  bool failed = false;
  bool matched = prog->SearchDFA("aaa", "aaa",
                                  Prog::kAnchored, Prog::kFirstMatch,
                                  nullptr, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
}

// Test DFA with character class
TEST_F(DFATest_605, CharacterClassPattern_605) {
  std::unique_ptr<Prog> prog(CompilePattern("[a-z]+"));
  ASSERT_NE(prog, nullptr);

  bool failed = false;
  bool matched = prog->SearchDFA("hello", "hello",
                                  Prog::kAnchored, Prog::kFirstMatch,
                                  nullptr, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);

  bool matched2 = prog->SearchDFA("12345", "12345",
                                   Prog::kAnchored, Prog::kFirstMatch,
                                   nullptr, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_FALSE(matched2);
}

// Test DFA with wildcard
TEST_F(DFATest_605, WildcardPattern_605) {
  std::unique_ptr<Prog> prog(CompilePattern("a.c"));
  ASSERT_NE(prog, nullptr);

  bool failed = false;
  bool matched = prog->SearchDFA("abc", "abc",
                                  Prog::kAnchored, Prog::kFirstMatch,
                                  nullptr, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);

  bool matched2 = prog->SearchDFA("aXc", "aXc",
                                   Prog::kAnchored, Prog::kFirstMatch,
                                   nullptr, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched2);
}

// Test DFA search with endpoint output
TEST_F(DFATest_605, SearchWithEndpoint_605) {
  std::unique_ptr<Prog> prog(CompilePattern("hel+o"));
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  const char* ep = nullptr;
  bool failed = false;
  bool matched = prog->SearchDFA(text, text,
                                  Prog::kUnanchored, Prog::kFirstMatch,
                                  &ep, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  if (matched && ep != nullptr) {
    EXPECT_GE(ep, text.data());
    EXPECT_LE(ep, text.data() + text.size());
  }
}

// Test DFA with very small memory budget through RE2 options
TEST_F(DFATest_605, SmallMemoryBudget_605) {
  RE2::Options opts;
  opts.set_max_mem(256);
  RE2 re("a{1,100}", opts);
  // May or may not be ok depending on budget, but should not crash
  if (re.ok()) {
    EXPECT_TRUE(RE2::PartialMatch("aaa", re));
  }
}

// Test PossibleMatchRange with a broader pattern
TEST_F(DFATest_605, PossibleMatchRangeBroad_605) {
  std::unique_ptr<Prog> prog(CompilePattern("[a-z]{3}"));
  ASSERT_NE(prog, nullptr);

  std::string min_match, max_match;
  bool result = prog->PossibleMatchRange(&min_match, &max_match, 10);
  EXPECT_TRUE(result);
  EXPECT_EQ(min_match, "aaa");
  EXPECT_LE(min_match, "zzz");
}

// Test DFA with optional pattern
TEST_F(DFATest_605, OptionalPattern_605) {
  std::unique_ptr<Prog> prog(CompilePattern("ab?c"));
  ASSERT_NE(prog, nullptr);

  bool failed = false;
  bool matched1 = prog->SearchDFA("abc", "abc",
                                   Prog::kAnchored, Prog::kFirstMatch,
                                   nullptr, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched1);

  bool matched2 = prog->SearchDFA("ac", "ac",
                                   Prog::kAnchored, Prog::kFirstMatch,
                                   nullptr, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched2);
}

// Test DFA anchored search that should fail at start
TEST_F(DFATest_605, AnchoredSearchFailsWhenNotAtStart_605) {
  std::unique_ptr<Prog> prog(CompilePattern("world"));
  ASSERT_NE(prog, nullptr);

  bool failed = false;
  bool matched = prog->SearchDFA("hello world", "hello world",
                                  Prog::kAnchored, Prog::kFirstMatch,
                                  nullptr, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_FALSE(matched);
}

// Test DFA with longest match
TEST_F(DFATest_605, LongestMatch_605) {
  std::unique_ptr<Prog> prog(CompilePattern("a+"));
  ASSERT_NE(prog, nullptr);

  absl::string_view text("aaaa");
  const char* ep = nullptr;
  bool failed = false;
  bool matched = prog->SearchDFA(text, text,
                                  Prog::kAnchored, Prog::kLongestMatch,
                                  &ep, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
}

// Test through RE2 which internally uses DFA
TEST_F(DFATest_605, RE2IntegrationSimple_605) {
  RE2 re("\\d{3}-\\d{4}");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("Call 555-1234 now", re));
  EXPECT_FALSE(RE2::PartialMatch("No phone here", re));
}

// Test through RE2 for full match
TEST_F(DFATest_605, RE2IntegrationFullMatch_605) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("hello world", re));
}

// Test with single character
TEST_F(DFATest_605, SingleCharPattern_605) {
  std::unique_ptr<Prog> prog(CompilePattern("x"));
  ASSERT_NE(prog, nullptr);

  bool failed = false;
  EXPECT_TRUE(prog->SearchDFA("x", "x",
                               Prog::kAnchored, Prog::kFirstMatch,
                               nullptr, &failed, nullptr));
  EXPECT_FALSE(failed);

  EXPECT_FALSE(prog->SearchDFA("y", "y",
                                Prog::kAnchored, Prog::kFirstMatch,
                                nullptr, &failed, nullptr));
  EXPECT_FALSE(failed);
}

// Test DFA with long input string
TEST_F(DFATest_605, LongInputString_605) {
  std::unique_ptr<Prog> prog(CompilePattern("needle"));
  ASSERT_NE(prog, nullptr);

  std::string haystack(10000, 'a');
  haystack += "needle";
  haystack += std::string(10000, 'b');

  bool failed = false;
  bool matched = prog->SearchDFA(haystack, haystack,
                                  Prog::kUnanchored, Prog::kFirstMatch,
                                  nullptr, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
}

}  // namespace re2
