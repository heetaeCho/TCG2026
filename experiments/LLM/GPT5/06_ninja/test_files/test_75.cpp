// File: ./TestProjects/ninja/tests/pool_depth_test_75.cpp

#include "gtest/gtest.h"
#include "state.h"

#include <string>
#include <climits>

// We only test the public interface (constructor + depth()) of Pool.
// No assumptions are made about internal implementation details.

TEST(PoolTest_75, DepthReturnsConstructorValue_75) {
  // Normal operation: positive depth
  Pool pool("default_pool", 5);
  EXPECT_EQ(5, pool.depth());
}

TEST(PoolTest_75, DepthZeroAllowed_75) {
  // Boundary condition: depth = 0
  Pool pool("zero_pool", 0);
  EXPECT_EQ(0, pool.depth());
}

TEST(PoolTest_75, DepthNegativeValue_75) {
  // Boundary condition: negative depth (interface uses plain int, so this is allowed)
  Pool pool("negative_pool", -3);
  EXPECT_EQ(-3, pool.depth());
}

TEST(PoolTest_75, DepthLargePositiveValue_75) {
  // Boundary condition: very large positive depth
  Pool pool("large_pool", INT_MAX);
  EXPECT_EQ(INT_MAX, pool.depth());
}

TEST(PoolTest_75, DepthConsistentAcrossCallsAndInstances_75) {
  // Verify that depth() is stable and independent per instance
  Pool pool1("pool1", 1);
  Pool pool2("pool2", 10);

  // Multiple calls on the same instance should return the same value
  EXPECT_EQ(1, pool1.depth());
  EXPECT_EQ(1, pool1.depth());

  EXPECT_EQ(10, pool2.depth());
  EXPECT_EQ(10, pool2.depth());

  // Also verify const-correct usage
  const Pool& const_pool1 = pool1;
  const Pool& const_pool2 = pool2;

  EXPECT_EQ(1, const_pool1.depth());
  EXPECT_EQ(10, const_pool2.depth());
}
