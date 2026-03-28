#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/sparse_array.h"
#include "re2/sparse_set.h"
#include "absl/strings/string_view.h"

#include <string>
#include <vector>

namespace re2 {

// Helper to compile a Regexp into a Prog for testing
class DFATest_432 : public ::testing::Test {
 protected:
  Prog* CompileRegexp(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re == nullptr) return nullptr;
    Prog* prog = re->CompileToProg(0);
    re->Decref();
    return prog;
  }
};

// Test that TESTING_ONLY_set_dfa_should_bail_when_slow can be set to false
TEST_F(DFATest_432, SetDFAShouldBailWhenSlowFalse_432) {
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
  // No crash; restore default
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
}

// Test that TESTING_ONLY_set_dfa_should_bail_when_slow can be set to true
TEST_F(DFATest_432, SetDFAShouldBailWhenSlowTrue_432) {
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  // No crash expected
}

// Test basic SearchDFA with a simple pattern - anchored match
TEST_F(DFATest_432, SearchDFASimpleAnchoredMatch_432) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello");
  absl::string_view context = text;
  absl::string_view match;
  bool failed = false;

  bool result = prog->SearchDFA(text, context, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);

  delete prog;
}

// Test SearchDFA with no match
TEST_F(DFATest_432, SearchDFANoMatch_432) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("world");
  absl::string_view context = text;
  absl::string_view match;
  bool failed = false;

  bool result = prog->SearchDFA(text, context, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_FALSE(result);

  delete prog;
}

// Test SearchDFA unanchored match
TEST_F(DFATest_432, SearchDFAUnanchoredMatch_432) {
  Prog* prog = CompileRegexp("llo");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello");
  absl::string_view context = text;
  absl::string_view match;
  bool failed = false;

  bool result = prog->SearchDFA(text, context, Prog::kUnanchored,
                                 Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);

  delete prog;
}

// Test SearchDFA with empty text
TEST_F(DFATest_432, SearchDFAEmptyText_432) {
  Prog* prog = CompileRegexp(".*");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("");
  absl::string_view context = text;
  absl::string_view match;
  bool failed = false;

  bool result = prog->SearchDFA(text, context, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);

  delete prog;
}

// Test SearchDFA with empty pattern on empty text
TEST_F(DFATest_432, SearchDFAEmptyPatternEmptyText_432) {
  Prog* prog = CompileRegexp("");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("");
  absl::string_view context = text;
  absl::string_view match;
  bool failed = false;

  bool result = prog->SearchDFA(text, context, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);

  delete prog;
}

// Test SearchDFA kLongestMatch mode
TEST_F(DFATest_432, SearchDFALongestMatch_432) {
  Prog* prog = CompileRegexp("a+");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("aaaa");
  absl::string_view context = text;
  absl::string_view match;
  bool failed = false;

  bool result = prog->SearchDFA(text, context, Prog::kAnchored,
                                 Prog::kLongestMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "aaaa");

  delete prog;
}

// Test BuildEntireDFA with a simple pattern
TEST_F(DFATest_432, BuildEntireDFASimple_432) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);

  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(num_states, 0);

  delete prog;
}

// Test BuildEntireDFA with longest match kind
TEST_F(DFATest_432, BuildEntireDFALongestMatch_432) {
  Prog* prog = CompileRegexp("a*");
  ASSERT_NE(prog, nullptr);

  int num_states = prog->BuildEntireDFA(Prog::kLongestMatch, nullptr);
  EXPECT_GT(num_states, 0);

  delete prog;
}

// Test BuildEntireDFA with callback
TEST_F(DFATest_432, BuildEntireDFAWithCallback_432) {
  Prog* prog = CompileRegexp("[ab]");
  ASSERT_NE(prog, nullptr);

  int callback_count = 0;
  auto cb = [&callback_count](const int* next, bool match) {
    callback_count++;
  };

  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, cb);
  EXPECT_GT(num_states, 0);
  EXPECT_GT(callback_count, 0);

  delete prog;
}

// Test PossibleMatchRange
TEST_F(DFATest_432, PossibleMatchRangeSimple_432) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);

  std::string min_match, max_match;
  bool result = prog->PossibleMatchRange(&min_match, &max_match, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min_match, "hello");
  EXPECT_GE(max_match, "hello");

  delete prog;
}

// Test PossibleMatchRange with maxlen boundary
TEST_F(DFATest_432, PossibleMatchRangeMaxLen_432) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);

  std::string min_match, max_match;
  bool result = prog->PossibleMatchRange(&min_match, &max_match, 3);
  EXPECT_TRUE(result);

  delete prog;
}

// Test PossibleMatchRange with very short maxlen
TEST_F(DFATest_432, PossibleMatchRangeShortMaxLen_432) {
  Prog* prog = CompileRegexp("abcdef");
  ASSERT_NE(prog, nullptr);

  std::string min_match, max_match;
  bool result = prog->PossibleMatchRange(&min_match, &max_match, 1);
  // Result depends on the pattern, just ensure no crash
  (void)result;

  delete prog;
}

// Test SearchDFA with character class
TEST_F(DFATest_432, SearchDFACharacterClass_432) {
  Prog* prog = CompileRegexp("[a-z]+");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello");
  absl::string_view context = text;
  absl::string_view match;
  bool failed = false;

  bool result = prog->SearchDFA(text, context, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);

  delete prog;
}

// Test SearchDFA with alternation
TEST_F(DFATest_432, SearchDFAAlternation_432) {
  Prog* prog = CompileRegexp("abc|def");
  ASSERT_NE(prog, nullptr);

  {
    absl::string_view text("abc");
    absl::string_view context = text;
    absl::string_view match;
    bool failed = false;
    bool result = prog->SearchDFA(text, context, Prog::kAnchored,
                                   Prog::kFirstMatch, &match, &failed, nullptr);
    EXPECT_FALSE(failed);
    EXPECT_TRUE(result);
  }

  {
    absl::string_view text("def");
    absl::string_view context = text;
    absl::string_view match;
    bool failed = false;
    bool result = prog->SearchDFA(text, context, Prog::kAnchored,
                                   Prog::kFirstMatch, &match, &failed, nullptr);
    EXPECT_FALSE(failed);
    EXPECT_TRUE(result);
  }

  {
    absl::string_view text("ghi");
    absl::string_view context = text;
    absl::string_view match;
    bool failed = false;
    bool result = prog->SearchDFA(text, context, Prog::kAnchored,
                                   Prog::kFirstMatch, &match, &failed, nullptr);
    EXPECT_FALSE(failed);
    EXPECT_FALSE(result);
  }

  delete prog;
}

// Test SearchDFA with repetition
TEST_F(DFATest_432, SearchDFARepetition_432) {
  Prog* prog = CompileRegexp("a{3}");
  ASSERT_NE(prog, nullptr);

  {
    absl::string_view text("aaa");
    absl::string_view context = text;
    absl::string_view match;
    bool failed = false;
    bool result = prog->SearchDFA(text, context, Prog::kAnchored,
                                   Prog::kFirstMatch, &match, &failed, nullptr);
    EXPECT_FALSE(failed);
    EXPECT_TRUE(result);
  }

  {
    absl::string_view text("aa");
    absl::string_view context = text;
    absl::string_view match;
    bool failed = false;
    bool result = prog->SearchDFA(text, context, Prog::kAnchored,
                                   Prog::kFirstMatch, &match, &failed, nullptr);
    EXPECT_FALSE(failed);
    EXPECT_FALSE(result);
  }

  delete prog;
}

// Test that DFA bail-when-slow setting affects behavior with complex patterns
TEST_F(DFATest_432, SearchDFABailWhenSlowEnabled_432) {
  // With bail enabled (default), complex patterns might cause failure
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);

  Prog* prog = CompileRegexp("a");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("a");
  absl::string_view context = text;
  absl::string_view match;
  bool failed = false;

  bool result = prog->SearchDFA(text, context, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, &failed, nullptr);
  // Simple pattern should not fail
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);

  delete prog;
}

// Test SearchDFA with bail when slow disabled
TEST_F(DFATest_432, SearchDFABailWhenSlowDisabled_432) {
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);

  Prog* prog = CompileRegexp("a");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("a");
  absl::string_view context = text;
  absl::string_view match;
  bool failed = false;

  bool result = prog->SearchDFA(text, context, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);

  delete prog;
  // Restore
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
}

// Test SearchDFA with limited DFA memory
TEST_F(DFATest_432, SearchDFALimitedMemory_432) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a.*b.*c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Compile with very small memory limit
  Prog* prog = re->CompileToProg(256);
  re->Decref();
  if (prog == nullptr) return;  // Compilation might fail with too little memory

  absl::string_view text("axbxc");
  absl::string_view context = text;
  absl::string_view match;
  bool failed = false;

  prog->SearchDFA(text, context, Prog::kUnanchored,
                   Prog::kFirstMatch, &match, &failed, nullptr);
  // Just verify no crash; failed might be true due to memory limit

  delete prog;
}

// Test SearchDFA with null match pointer
TEST_F(DFATest_432, SearchDFANullMatchPointer_432) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello");
  absl::string_view context = text;
  bool failed = false;

  bool result = prog->SearchDFA(text, context, Prog::kAnchored,
                                 Prog::kFirstMatch, nullptr, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);

  delete prog;
}

// Test SearchDFA with dot-star pattern
TEST_F(DFATest_432, SearchDFADotStar_432) {
  Prog* prog = CompileRegexp(".*");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("anything goes here");
  absl::string_view context = text;
  absl::string_view match;
  bool failed = false;

  bool result = prog->SearchDFA(text, context, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);

  delete prog;
}

// Test dfa_mem getter/setter
TEST_F(DFATest_432, DFAMemGetterSetter_432) {
  Prog prog;
  EXPECT_EQ(prog.dfa_mem(), 0);
  prog.set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog.dfa_mem(), 1024 * 1024);
}

// Test BuildEntireDFA with single character
TEST_F(DFATest_432, BuildEntireDFASingleChar_432) {
  Prog* prog = CompileRegexp("a");
  ASSERT_NE(prog, nullptr);

  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(num_states, 0);

  delete prog;
}

// Test repeated SearchDFA calls on same Prog (DFA caching)
TEST_F(DFATest_432, SearchDFARepeatedCalls_432) {
  Prog* prog = CompileRegexp("test");
  ASSERT_NE(prog, nullptr);

  for (int i = 0; i < 5; i++) {
    absl::string_view text("test");
    absl::string_view context = text;
    absl::string_view match;
    bool failed = false;

    bool result = prog->SearchDFA(text, context, Prog::kAnchored,
                                   Prog::kFirstMatch, &match, &failed, nullptr);
    EXPECT_FALSE(failed);
    EXPECT_TRUE(result);
  }

  delete prog;
}

// Test SearchDFA with text longer than pattern
TEST_F(DFATest_432, SearchDFAUnanchoredInLongerText_432) {
  Prog* prog = CompileRegexp("needle");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("this is a haystack with a needle in it");
  absl::string_view context = text;
  absl::string_view match;
  bool failed = false;

  bool result = prog->SearchDFA(text, context, Prog::kUnanchored,
                                 Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(result);

  delete prog;
}

// Test SearchDFA anchored match fails when pattern not at start
TEST_F(DFATest_432, SearchDFAAnchoredMatchNotAtStart_432) {
  Prog* prog = CompileRegexp("needle");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("haystackneedle");
  absl::string_view context = text;
  absl::string_view match;
  bool failed = false;

  bool result = prog->SearchDFA(text, context, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_FALSE(result);

  delete prog;
}

// Test via RE2 integration that DFA works correctly
TEST_F(DFATest_432, RE2IntegrationSimpleMatch_432) {
  RE2 re("\\d+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("abc123def", re));
  EXPECT_FALSE(RE2::PartialMatch("abcdef", re));
}

// Test via RE2 that full match uses DFA
TEST_F(DFATest_432, RE2IntegrationFullMatch_432) {
  RE2 re("hello world");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello world", re));
  EXPECT_FALSE(RE2::FullMatch("hello world!", re));
  EXPECT_FALSE(RE2::FullMatch("hello", re));
}

// Test toggle bail when slow multiple times
TEST_F(DFATest_432, ToggleBailWhenSlowMultipleTimes_432) {
  for (int i = 0; i < 10; i++) {
    Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(i % 2 == 0);
  }
  // Restore default
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
}

}  // namespace re2
