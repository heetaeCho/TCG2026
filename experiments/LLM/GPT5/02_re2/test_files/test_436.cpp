// File: dfa_state_constants_test_436.cc

#include <cstdint>
#include <gtest/gtest.h>

// Pull in the visible interface elements from the snippet: the sentinel
// pointer-like macros and the StateSet alias type.
#include "re2/dfa.cc"

namespace {

// TEST_ID: 436
TEST(DFAStateConstantsTest_436, DeadAndFullMatchAreDistinctNonNull_436) {
  // The sentinels should be non-null and not equal to each other.
  EXPECT_NE(DeadState, nullptr);
  EXPECT_NE(FullMatchState, nullptr);
  EXPECT_NE(DeadState, FullMatchState);
}

// TEST_ID: 436
TEST(DFAStateConstantsTest_436, SentinelsHaveExpectedIntegralValues_436) {
  // Verify the exact values exposed by the interface (no internal logic assumed).
  uintptr_t dead_val = reinterpret_cast<uintptr_t>(DeadState);
  uintptr_t full_val = reinterpret_cast<uintptr_t>(FullMatchState);

  EXPECT_EQ(dead_val, static_cast<uintptr_t>(1));
  EXPECT_EQ(full_val, static_cast<uintptr_t>(2));

  EXPECT_EQ(MatchSep, -2);
  EXPECT_EQ(Mark, -1);
}

// TEST_ID: 436
TEST(DFAStateSetTest_436, InsertSentinelPointers_ActsLikeASet_436) {
  re2::StateSet set;

  // Insert the two sentinel states; they should both be stored distinctly.
  auto [it1, inserted1] = set.insert(DeadState);
  auto [it2, inserted2] = set.insert(FullMatchState);

  EXPECT_TRUE(inserted1);
  EXPECT_TRUE(inserted2);
  EXPECT_EQ(set.size(), 2u);

  // Reinserting the same pointer should not grow the set.
  auto [it1b, inserted1b] = set.insert(DeadState);
  EXPECT_FALSE(inserted1b);
  EXPECT_EQ(set.size(), 2u);

  // Basic membership checks via find (portable across Abseil versions).
  EXPECT_TRUE(set.find(DeadState) != set.end());
  EXPECT_TRUE(set.find(FullMatchState) != set.end());
}

// TEST_ID: 436
TEST(DFAStateSetTest_436, EraseSentinelPointer_RemovesExactlyOne_436) {
  re2::StateSet set;
  set.insert(DeadState);
  set.insert(FullMatchState);
  ASSERT_EQ(set.size(), 2u);

  // Erase one sentinel and ensure size updates accordingly.
  size_t erased = set.erase(DeadState);
  EXPECT_EQ(erased, 1u);
  EXPECT_EQ(set.size(), 1u);
  EXPECT_TRUE(set.find(DeadState) == set.end());
  EXPECT_TRUE(set.find(FullMatchState) != set.end());
}

}  // namespace
