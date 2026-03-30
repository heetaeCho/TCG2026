// File: dfa_state_is_match_test_435.cc

#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

// Bring in the interface under test (inline method + sentinels/constants).
// We intentionally include the provided .cc because the method is inline
// in the snippet you shared.
#include "TestProjects/re2/re2/dfa.cc"

namespace {

using re2::DFA;

// ---------------------------
// DFA::State::IsMatch() tests
// ---------------------------

TEST(DFAStateTest_435, IsMatch_FalseWhenNoFlags_435) {
  // Arrange
  DFA::State s{};
  s.flag_ = 0u;

  // Act / Assert
  EXPECT_FALSE(s.IsMatch());
}

TEST(DFAStateTest_435, IsMatch_TrueWhenAllBitsSet_435) {
  // Arrange
  DFA::State s{};
  s.flag_ = std::numeric_limits<uint32_t>::max();  // Ensures any nonzero kFlagMatch bit is set

  // Act / Assert
  EXPECT_TRUE(s.IsMatch());
}

TEST(DFAStateTest_435, IsMatch_ConstCorrectness_435) {
  // Arrange
  DFA::State s{};
  s.flag_ = std::numeric_limits<uint32_t>::max();

  // Act
  const DFA::State& cs = s;

  // Assert
  EXPECT_TRUE(cs.IsMatch());
}

// -----------------------------------------
// Sentinel and constant sanity/identity tests
// -----------------------------------------

TEST(DFAStateTest_435, Sentinels_AreNonNullAndDistinct_435) {
  // DeadState and FullMatchState are special sentinel pointers.
  // These properties are observable without touching internal state.
  EXPECT_NE(DeadState, static_cast<DFA::State*>(nullptr));
  EXPECT_NE(FullMatchState, static_cast<DFA::State*>(nullptr));
  EXPECT_NE(DeadState, FullMatchState);
}

TEST(DFAStateTest_435, MatchSepAndMark_HaveExpectedValues_435) {
  // These are integer constants exposed in the same unit.
  EXPECT_EQ(MatchSep, -2);
  EXPECT_EQ(Mark, -1);
}

}  // namespace
