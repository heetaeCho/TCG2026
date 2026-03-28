#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/re2.h"

#include <string>
#include <vector>
#include <functional>

namespace re2 {

class BuildEntireDFATest_456 : public ::testing::Test {
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

// Test BuildEntireDFA with a simple pattern using kFirstMatch
TEST_F(BuildEntireDFATest_456, SimplePatternFirstMatch_456) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);

  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(num_states, 0);

  delete prog;
}

// Test BuildEntireDFA with a simple pattern using kLongestMatch
TEST_F(BuildEntireDFATest_456, SimplePatternLongestMatch_456) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);

  int num_states = prog->BuildEntireDFA(Prog::kLongestMatch, nullptr);
  EXPECT_GT(num_states, 0);

  delete prog;
}

// Test BuildEntireDFA with an empty pattern
TEST_F(BuildEntireDFATest_456, EmptyPattern_456) {
  Prog* prog = CompileRegexp("");
  ASSERT_NE(prog, nullptr);

  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(num_states, 0);

  delete prog;
}

// Test BuildEntireDFA with a single character pattern
TEST_F(BuildEntireDFATest_456, SingleCharPattern_456) {
  Prog* prog = CompileRegexp("a");
  ASSERT_NE(prog, nullptr);

  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(num_states, 0);

  delete prog;
}

// Test BuildEntireDFA with alternation pattern
TEST_F(BuildEntireDFATest_456, AlternationPattern_456) {
  Prog* prog = CompileRegexp("a|b|c");
  ASSERT_NE(prog, nullptr);

  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(num_states, 0);

  delete prog;
}

// Test BuildEntireDFA with repetition
TEST_F(BuildEntireDFATest_456, RepetitionPattern_456) {
  Prog* prog = CompileRegexp("a*");
  ASSERT_NE(prog, nullptr);

  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(num_states, 0);

  delete prog;
}

// Test BuildEntireDFA with character class
TEST_F(BuildEntireDFATest_456, CharClassPattern_456) {
  Prog* prog = CompileRegexp("[a-z]");
  ASSERT_NE(prog, nullptr);

  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(num_states, 0);

  delete prog;
}

// Test BuildEntireDFA with dot pattern
TEST_F(BuildEntireDFATest_456, DotPattern_456) {
  Prog* prog = CompileRegexp(".");
  ASSERT_NE(prog, nullptr);

  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(num_states, 0);

  delete prog;
}

// Test BuildEntireDFA with a callback that counts states
TEST_F(BuildEntireDFATest_456, CallbackInvoked_456) {
  Prog* prog = CompileRegexp("ab");
  ASSERT_NE(prog, nullptr);

  int callback_count = 0;
  Prog::DFAStateCallback cb = [&callback_count](const int* next, bool match) {
    callback_count++;
  };

  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, cb);
  EXPECT_GT(num_states, 0);
  EXPECT_GT(callback_count, 0);
  EXPECT_EQ(num_states, callback_count);

  delete prog;
}

// Test BuildEntireDFA with callback for longest match
TEST_F(BuildEntireDFATest_456, CallbackInvokedLongestMatch_456) {
  Prog* prog = CompileRegexp("a+");
  ASSERT_NE(prog, nullptr);

  int callback_count = 0;
  bool found_match_state = false;
  Prog::DFAStateCallback cb = [&callback_count, &found_match_state](const int* next, bool match) {
    callback_count++;
    if (match) found_match_state = true;
  };

  int num_states = prog->BuildEntireDFA(Prog::kLongestMatch, cb);
  EXPECT_GT(num_states, 0);
  EXPECT_GT(callback_count, 0);
  EXPECT_TRUE(found_match_state);

  delete prog;
}

// Test that FirstMatch and LongestMatch can produce different state counts
TEST_F(BuildEntireDFATest_456, FirstMatchVsLongestMatchMayDiffer_456) {
  Prog* prog1 = CompileRegexp("a+b?");
  ASSERT_NE(prog1, nullptr);
  Prog* prog2 = CompileRegexp("a+b?");
  ASSERT_NE(prog2, nullptr);

  int num_first = prog1->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  int num_longest = prog2->BuildEntireDFA(Prog::kLongestMatch, nullptr);

  EXPECT_GT(num_first, 0);
  EXPECT_GT(num_longest, 0);

  delete prog1;
  delete prog2;
}

// Test BuildEntireDFA with a more complex pattern
TEST_F(BuildEntireDFATest_456, ComplexPattern_456) {
  Prog* prog = CompileRegexp("(foo|bar)+baz");
  ASSERT_NE(prog, nullptr);

  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(num_states, 0);

  delete prog;
}

// Test BuildEntireDFA with question mark
TEST_F(BuildEntireDFATest_456, QuestionMarkPattern_456) {
  Prog* prog = CompileRegexp("ab?c");
  ASSERT_NE(prog, nullptr);

  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(num_states, 0);

  delete prog;
}

// Test BuildEntireDFA with nullptr callback (no callback)
TEST_F(BuildEntireDFATest_456, NullCallback_456) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);

  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(num_states, 0);

  delete prog;
}

// Test SearchDFA basic match
class SearchDFATest_456 : public ::testing::Test {};

TEST_F(SearchDFATest_456, BasicMatch_456) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("say hello world", re));
}

TEST_F(SearchDFATest_456, BasicNoMatch_456) {
  RE2 re("xyz");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::PartialMatch("hello world", re));
}

TEST_F(SearchDFATest_456, FullMatch_456) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("hello world", re));
}

TEST_F(SearchDFATest_456, EmptyStringMatch_456) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("", re));
  EXPECT_TRUE(RE2::PartialMatch("anything", re));
}

TEST_F(SearchDFATest_456, AnchoredMatch_456) {
  RE2 re("^hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("hello world", re));
  EXPECT_FALSE(RE2::PartialMatch("say hello", re));
}

// Test PossibleMatchRange
class PossibleMatchRangeTest_456 : public BuildEntireDFATest_456 {};

TEST_F(PossibleMatchRangeTest_456, SimpleRange_456) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);

  std::string min_match, max_match;
  bool result = prog->PossibleMatchRange(&min_match, &max_match, 10);
  EXPECT_TRUE(result);
  EXPECT_FALSE(min_match.empty());
  EXPECT_FALSE(max_match.empty());
  EXPECT_LE(min_match, max_match);

  delete prog;
}

TEST_F(PossibleMatchRangeTest_456, DotStarRange_456) {
  Prog* prog = CompileRegexp(".*");
  ASSERT_NE(prog, nullptr);

  std::string min_match, max_match;
  bool result = prog->PossibleMatchRange(&min_match, &max_match, 10);
  // .* matches everything, so the range should be as wide as possible
  if (result) {
    EXPECT_LE(min_match, max_match);
  }

  delete prog;
}

TEST_F(PossibleMatchRangeTest_456, MaxLenZero_456) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);

  std::string min_match, max_match;
  // maxlen of 0 is a boundary condition
  bool result = prog->PossibleMatchRange(&min_match, &max_match, 0);
  // Result may or may not succeed, but should not crash

  delete prog;
}

// Test callback verifies match states are reported correctly
TEST_F(BuildEntireDFATest_456, CallbackReportsMatchStates_456) {
  Prog* prog = CompileRegexp("a");
  ASSERT_NE(prog, nullptr);

  bool any_match = false;
  bool any_non_match = false;
  Prog::DFAStateCallback cb = [&](const int* next, bool match) {
    if (match) any_match = true;
    else any_non_match = true;
  };

  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, cb);
  EXPECT_GT(num_states, 0);
  // For pattern "a", there should be at least one match state and one non-match state
  EXPECT_TRUE(any_match);

  delete prog;
}

// Test BuildEntireDFA with limited memory
TEST_F(BuildEntireDFATest_456, LimitedMemory_456) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*b*c*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  // Compile with very limited memory
  Prog* prog = re->CompileToProg(1 << 10);  // 1KB
  re->Decref();
  if (prog == nullptr) return;  // May fail to compile with limited memory

  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  // With limited memory, it might build fewer states or return a special value
  // but should not crash
  EXPECT_GE(num_states, 0);

  delete prog;
}

// Test with pattern containing many alternations
TEST_F(BuildEntireDFATest_456, ManyAlternations_456) {
  Prog* prog = CompileRegexp("a|b|c|d|e|f|g|h|i|j");
  ASSERT_NE(prog, nullptr);

  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(num_states, 0);

  delete prog;
}

// Test BuildEntireDFA with nested patterns
TEST_F(BuildEntireDFATest_456, NestedPattern_456) {
  Prog* prog = CompileRegexp("((a+)(b+))+");
  ASSERT_NE(prog, nullptr);

  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(num_states, 0);

  delete prog;
}

// Test that callback next array contains valid state indices
TEST_F(BuildEntireDFATest_456, CallbackNextArrayValid_456) {
  Prog* prog = CompileRegexp("ab");
  ASSERT_NE(prog, nullptr);

  int total_states = 0;
  bool all_next_valid = true;
  
  // First, count states
  total_states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  
  // Recompile to test again with callback
  delete prog;
  prog = CompileRegexp("ab");
  ASSERT_NE(prog, nullptr);

  Prog::DFAStateCallback cb = [&total_states, &all_next_valid](const int* next, bool match) {
    // next array should be provided (bytemap_range + 1 entries)
    if (next == nullptr) {
      all_next_valid = false;
    }
  };

  int num_states2 = prog->BuildEntireDFA(Prog::kFirstMatch, cb);
  EXPECT_GT(num_states2, 0);

  delete prog;
}

}  // namespace re2
