#include <string>
#include <vector>
#include <functional>

#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"

namespace re2 {

// Helper to compile a regex pattern into a Prog
static Prog* CompileProg(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = re->CompileToProg(0);
  re->Decref();
  return prog;
}

class BuildAllStatesTest_455 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Programs are cleaned up in individual tests
  }
};

// Test that BuildEntireDFA returns a positive number of states for a simple pattern
TEST_F(BuildAllStatesTest_455, SimplePatternReturnsPositiveStates_455) {
  Prog* prog = CompileProg("a");
  ASSERT_NE(prog, nullptr);
  int nstates = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(nstates, 0);
  delete prog;
}

// Test with a more complex pattern
TEST_F(BuildAllStatesTest_455, ComplexPatternReturnsPositiveStates_455) {
  Prog* prog = CompileProg("a(b|c)*d");
  ASSERT_NE(prog, nullptr);
  int nstates = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(nstates, 0);
  delete prog;
}

// Test that the callback is invoked when provided
TEST_F(BuildAllStatesTest_455, CallbackIsInvoked_455) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  int callback_count = 0;
  auto cb = [&callback_count](const int* next, bool is_match) {
    callback_count++;
  };
  int nstates = prog->BuildEntireDFA(Prog::kFirstMatch, cb);
  EXPECT_GT(nstates, 0);
  EXPECT_EQ(callback_count, nstates);
  delete prog;
}

// Test that callback count matches number of states
TEST_F(BuildAllStatesTest_455, CallbackCountMatchesStates_455) {
  Prog* prog = CompileProg("[a-z]+");
  ASSERT_NE(prog, nullptr);
  int callback_count = 0;
  auto cb = [&callback_count](const int* next, bool is_match) {
    callback_count++;
  };
  int nstates = prog->BuildEntireDFA(Prog::kFirstMatch, cb);
  EXPECT_GT(nstates, 0);
  EXPECT_EQ(callback_count, nstates);
  delete prog;
}

// Test that at least one state is a match state for a simple pattern
TEST_F(BuildAllStatesTest_455, AtLeastOneMatchState_455) {
  Prog* prog = CompileProg("a");
  ASSERT_NE(prog, nullptr);
  bool found_match = false;
  auto cb = [&found_match](const int* next, bool is_match) {
    if (is_match) found_match = true;
  };
  int nstates = prog->BuildEntireDFA(Prog::kFirstMatch, cb);
  EXPECT_GT(nstates, 0);
  EXPECT_TRUE(found_match);
  delete prog;
}

// Test with nullptr callback (should still work and return state count)
TEST_F(BuildAllStatesTest_455, NullCallbackStillWorks_455) {
  Prog* prog = CompileProg("hello");
  ASSERT_NE(prog, nullptr);
  int nstates = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(nstates, 0);
  delete prog;
}

// Test with kLongestMatch kind
TEST_F(BuildAllStatesTest_455, LongestMatchKind_455) {
  Prog* prog = CompileProg("a*");
  ASSERT_NE(prog, nullptr);
  int nstates = prog->BuildEntireDFA(Prog::kLongestMatch, nullptr);
  EXPECT_GT(nstates, 0);
  delete prog;
}

// Test with alternation pattern
TEST_F(BuildAllStatesTest_455, AlternationPattern_455) {
  Prog* prog = CompileProg("cat|dog|bird");
  ASSERT_NE(prog, nullptr);
  int nstates = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(nstates, 0);
  delete prog;
}

// Test that the next array in callback contains valid indices or -1
TEST_F(BuildAllStatesTest_455, CallbackNextArrayContainsValidValues_455) {
  Prog* prog = CompileProg("ab");
  ASSERT_NE(prog, nullptr);
  int nstates_result = 0;
  int bytemap_range = prog->bytemap_range();
  int nnext = bytemap_range + 1;
  
  std::vector<std::vector<int>> all_nexts;
  auto cb = [&all_nexts, nnext](const int* next, bool is_match) {
    if (next != nullptr) {
      all_nexts.push_back(std::vector<int>(next, next + nnext));
    }
  };
  nstates_result = prog->BuildEntireDFA(Prog::kFirstMatch, cb);
  EXPECT_GT(nstates_result, 0);
  
  // Verify that all next values are either -1 (dead) or valid state indices
  for (const auto& nexts : all_nexts) {
    for (int val : nexts) {
      EXPECT_TRUE(val == -1 || (val >= 0 && val < nstates_result))
          << "Invalid next state value: " << val;
    }
  }
  delete prog;
}

// Test with dot-star pattern
TEST_F(BuildAllStatesTest_455, DotStarPattern_455) {
  Prog* prog = CompileProg(".*");
  ASSERT_NE(prog, nullptr);
  int nstates = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(nstates, 0);
  delete prog;
}

// Test with character class
TEST_F(BuildAllStatesTest_455, CharacterClassPattern_455) {
  Prog* prog = CompileProg("[0-9]+");
  ASSERT_NE(prog, nullptr);
  int nstates = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(nstates, 0);
  delete prog;
}

// Test with single character produces a small number of states
TEST_F(BuildAllStatesTest_455, SingleCharSmallStateCount_455) {
  Prog* prog = CompileProg("x");
  ASSERT_NE(prog, nullptr);
  int nstates = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(nstates, 0);
  // A single character regex should produce a small DFA
  EXPECT_LE(nstates, 10);
  delete prog;
}

// Test with empty-matching pattern
TEST_F(BuildAllStatesTest_455, EmptyMatchPattern_455) {
  Prog* prog = CompileProg("");
  ASSERT_NE(prog, nullptr);
  int nstates = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  // Even empty pattern should produce some states
  EXPECT_GT(nstates, 0);
  delete prog;
}

// Test that kFirstMatch and kLongestMatch may produce different state counts
TEST_F(BuildAllStatesTest_455, DifferentKindsMayDiffer_455) {
  Prog* prog_first = CompileProg("a+");
  Prog* prog_longest = CompileProg("a+");
  ASSERT_NE(prog_first, nullptr);
  ASSERT_NE(prog_longest, nullptr);
  
  int nstates_first = prog_first->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  int nstates_longest = prog_longest->BuildEntireDFA(Prog::kLongestMatch, nullptr);
  
  EXPECT_GT(nstates_first, 0);
  EXPECT_GT(nstates_longest, 0);
  
  delete prog_first;
  delete prog_longest;
}

// Test with question mark (optional) pattern
TEST_F(BuildAllStatesTest_455, OptionalPattern_455) {
  Prog* prog = CompileProg("ab?c");
  ASSERT_NE(prog, nullptr);
  int nstates = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(nstates, 0);
  delete prog;
}

// Test with very small DFA memory limit - may fail to build
TEST_F(BuildAllStatesTest_455, VerySmallMemoryLimit_455) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)*d", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Compile with very small memory limit
  Prog* prog = re->CompileToProg(256);  // Very small
  re->Decref();
  if (prog != nullptr) {
    // Even if compilation succeeds, building DFA might return 0 or small count
    int nstates = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
    // Just verify it doesn't crash; result may be 0 if memory is too tight
    EXPECT_GE(nstates, 0);
    delete prog;
  }
}

// Test that callback receives non-null next array for non-OOM states
TEST_F(BuildAllStatesTest_455, CallbackReceivesNonNullNext_455) {
  Prog* prog = CompileProg("test");
  ASSERT_NE(prog, nullptr);
  bool received_null = false;
  auto cb = [&received_null](const int* next, bool is_match) {
    if (next == nullptr) received_null = true;
  };
  int nstates = prog->BuildEntireDFA(Prog::kFirstMatch, cb);
  EXPECT_GT(nstates, 0);
  // Under normal conditions (no OOM), next should not be null
  EXPECT_FALSE(received_null);
  delete prog;
}

// Test with anchored pattern (^ and $)
TEST_F(BuildAllStatesTest_455, AnchoredPattern_455) {
  Prog* prog = CompileProg("^abc$");
  ASSERT_NE(prog, nullptr);
  int nstates = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(nstates, 0);
  delete prog;
}

}  // namespace re2
