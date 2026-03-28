// File: dfa_state_equal_constants_test_439.cc

#include <gtest/gtest.h>
#include <cstdint>

// Include the partial implementation to access the visible interface/macros.
// (We purposefully avoid constructing or dereferencing DFA::State.)
#include "re2/dfa.cc"

using ::testing::Test;

namespace {

class DFAConstantsTest_439 : public ::testing::Test {};

TEST_F(DFAConstantsTest_439, MatchSeparatorsHaveExpectedValues_439) {
  // Verifies integer sentinels exposed by the interface.
  EXPECT_EQ(MatchSep, -2);
  EXPECT_EQ(Mark, -1);
}

TEST_F(DFAConstantsTest_439, SentinelPointersAreNonNullAndDistinct_439) {
  // We only check address identity; no dereferencing.
  ASSERT_NE(DeadState, nullptr);
  ASSERT_NE(FullMatchState, nullptr);
  EXPECT_NE(DeadState, FullMatchState);
}

TEST_F(DFAConstantsTest_439, SentinelPointerExactValues_439) {
  // The interface defines exact reinterpret_cast values; validate them.
  // Checking by value avoids any dereference of invalid pointers.
  EXPECT_EQ(reinterpret_cast<std::uintptr_t>(DeadState), static_cast<std::uintptr_t>(1));
  EXPECT_EQ(reinterpret_cast<std::uintptr_t>(FullMatchState), static_cast<std::uintptr_t>(2));
}

class DFAStateEqualShapeTest_439 : public ::testing::Test {};

TEST_F(DFAStateEqualShapeTest_439, StateEqualIsDefaultConstructible_439) {
  // We only validate the functor is present and default-constructible.
  // We do NOT call operator() because we cannot safely produce valid State objects.
  re2::DFA::StateEqual eq;  // Should compile and construct.
  (void)eq;
  SUCCEED();
}

}  // namespace
