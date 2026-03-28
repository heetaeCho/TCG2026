// File: dfa_constructor_test_603.cc
#include <gtest/gtest.h>
#include "re2/prog.h"
// If DFA is exposed via a header, include it:
#include "re2/dfa.h"   // assuming the project provides this

using namespace re2;

class DFATest_603 : public ::testing::Test {};

// Constructs with plenty of memory: should be OK and preserve kind.
TEST_F(DFATest_603, ConstructOkWithSufficientMemory_603) {
  Prog prog;  // Use real dependency; treat as a black box.
  const int64_t kPlenty = 1LL << 30;  // Big budget to avoid bailing.

  DFA dfa_first(&prog, Prog::kFirstMatch, kPlenty);
  EXPECT_TRUE(dfa_first.ok());
  EXPECT_EQ(dfa_first.kind(), Prog::kFirstMatch);

  DFA dfa_longest(&prog, Prog::kLongestMatch, kPlenty);
  EXPECT_TRUE(dfa_longest.ok());
  EXPECT_EQ(dfa_longest.kind(), Prog::kLongestMatch);
}

// Constructs with tiny memory: initializer should report not-ok.
TEST_F(DFATest_603, ConstructFailsWithInsufficientMemory_603) {
  Prog prog;
  const int64_t kTiny = 0;  // Intentionally too small.

  DFA dfa(&prog, Prog::kFirstMatch, kTiny);
  EXPECT_FALSE(dfa.ok());
  // kind() is still a valid observable (the arg was accepted).
  EXPECT_EQ(dfa.kind(), Prog::kFirstMatch);
}

// Sanity across all MatchKind values with ample memory.
// This verifies the constructor accepts every kind without crashing
// and that kind() echoes the input.
TEST_F(DFATest_603, ConstructAllMatchKindsEchoKind_603) {
  Prog prog;
  const int64_t kPlenty = 1LL << 28;

  {
    DFA dfa(&prog, Prog::kFirstMatch, kPlenty);
    EXPECT_TRUE(dfa.ok());
    EXPECT_EQ(dfa.kind(), Prog::kFirstMatch);
  }
  {
    DFA dfa(&prog, Prog::kLongestMatch, kPlenty);
    EXPECT_TRUE(dfa.ok());
    EXPECT_EQ(dfa.kind(), Prog::kLongestMatch);
  }
  {
    DFA dfa(&prog, Prog::kFullMatch, kPlenty);
    EXPECT_TRUE(dfa.ok());
    EXPECT_EQ(dfa.kind(), Prog::kFullMatch);
  }
  {
    DFA dfa(&prog, Prog::kManyMatch, kPlenty);
    EXPECT_TRUE(dfa.ok());
    EXPECT_EQ(dfa.kind(), Prog::kManyMatch);
  }
}

// Smoke test that a 'not ok' DFA (due to low memory) does not crash when
// simply queried via its cheap observers; we DO NOT call any heavy methods.
TEST_F(DFATest_603, NotOkDfaIsQueriableViaObservers_603) {
  Prog prog;
  DFA dfa(&prog, Prog::kLongestMatch, /*max_mem=*/0);
  EXPECT_FALSE(dfa.ok());
  // Only use observable, non-mutating API.
  EXPECT_EQ(dfa.kind(), Prog::kLongestMatch);
}
