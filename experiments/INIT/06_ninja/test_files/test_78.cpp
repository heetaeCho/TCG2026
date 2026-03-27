// File: ./TestProjects/ninja/tests/pool_should_delay_edge_test_78.cc

#include <gtest/gtest.h>
#include "state.h"

// Tests for Pool::ShouldDelayEdge().
// We treat Pool as a black box and only use its public constructor and methods.

// Normal operation & boundary: depth == 0 → should *not* delay edges.
TEST(PoolTest_78, ShouldDelayEdge_DepthZero_NoDelay_78) {
  Pool pool("zero-depth-pool", 0);

  // When depth is 0, ShouldDelayEdge is expected to report that
  // edges should not be delayed.
  EXPECT_FALSE(pool.ShouldDelayEdge());
}

// Normal operation: minimal positive depth (boundary between 0 and >0).
TEST(PoolTest_78, ShouldDelayEdge_DepthOne_Delays_78) {
  Pool pool("depth-one-pool", 1);

  // When depth is a positive value (here: 1), ShouldDelayEdge
  // is expected to report that edges should be delayed.
  EXPECT_TRUE(pool.ShouldDelayEdge());
}

// Normal operation: larger positive depth still indicates delaying.
TEST(PoolTest_78, ShouldDelayEdge_LargePositiveDepth_Delays_78) {
  const int kLargeDepth = 10;
  Pool pool("large-depth-pool", kLargeDepth);

  // For a larger positive depth, edges are still expected to be delayed.
  EXPECT_TRUE(pool.ShouldDelayEdge());
}
