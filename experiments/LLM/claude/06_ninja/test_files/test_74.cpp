#include "gtest/gtest.h"
#include "state.h"

// Test fixture for Pool class
class PoolTest_74 : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a pool with positive depth is valid
TEST_F(PoolTest_74, PositiveDepthIsValid_74) {
  Pool pool("test_pool", 5);
  EXPECT_TRUE(pool.is_valid());
}

// Test that a pool with zero depth is valid (depth >= 0)
TEST_F(PoolTest_74, ZeroDepthIsValid_74) {
  Pool pool("zero_pool", 0);
  EXPECT_TRUE(pool.is_valid());
}

// Test that a pool with negative depth is not valid
TEST_F(PoolTest_74, NegativeDepthIsNotValid_74) {
  Pool pool("invalid_pool", -1);
  EXPECT_FALSE(pool.is_valid());
}

// Test that a pool with large positive depth is valid
TEST_F(PoolTest_74, LargePositiveDepthIsValid_74) {
  Pool pool("large_pool", 1000000);
  EXPECT_TRUE(pool.is_valid());
}

// Test that a pool with depth of -100 is not valid
TEST_F(PoolTest_74, LargeNegativeDepthIsNotValid_74) {
  Pool pool("very_invalid_pool", -100);
  EXPECT_FALSE(pool.is_valid());
}

// Test that depth() returns the correct value
TEST_F(PoolTest_74, DepthReturnsCorrectValue_74) {
  Pool pool("depth_pool", 42);
  EXPECT_EQ(42, pool.depth());
}

// Test that name() returns the correct value
TEST_F(PoolTest_74, NameReturnsCorrectValue_74) {
  Pool pool("my_pool", 10);
  EXPECT_EQ("my_pool", pool.name());
}

// Test that current_use starts at zero
TEST_F(PoolTest_74, InitialCurrentUseIsZero_74) {
  Pool pool("use_pool", 5);
  EXPECT_EQ(0, pool.current_use());
}

// Test that a pool with depth 1 is valid (boundary)
TEST_F(PoolTest_74, DepthOneIsValid_74) {
  Pool pool("one_pool", 1);
  EXPECT_TRUE(pool.is_valid());
}

// Test that a pool with depth -1 is invalid (boundary)
TEST_F(PoolTest_74, DepthMinusOneIsInvalid_74) {
  Pool pool("neg_one_pool", -1);
  EXPECT_FALSE(pool.is_valid());
}

// Test that ShouldDelayEdge returns false when pool has capacity
TEST_F(PoolTest_74, ShouldNotDelayEdgeWhenUnderCapacity_74) {
  Pool pool("capacity_pool", 5);
  // With current_use at 0 and depth 5, should not delay
  EXPECT_FALSE(pool.ShouldDelayEdge());
}

// Test that a pool with zero depth should delay edges (no capacity)
TEST_F(PoolTest_74, ZeroDepthShouldDelayEdge_74) {
  Pool pool("zero_cap_pool", 0);
  // With depth 0 and current_use 0, edge should be delayed since there's no capacity
  EXPECT_TRUE(pool.ShouldDelayEdge());
}

// Test empty name pool
TEST_F(PoolTest_74, EmptyNamePool_74) {
  Pool pool("", 3);
  EXPECT_EQ("", pool.name());
  EXPECT_TRUE(pool.is_valid());
}

// Test depth accessor for zero
TEST_F(PoolTest_74, DepthZeroAccessor_74) {
  Pool pool("zero", 0);
  EXPECT_EQ(0, pool.depth());
}

// Test depth accessor for negative
TEST_F(PoolTest_74, DepthNegativeAccessor_74) {
  Pool pool("neg", -5);
  EXPECT_EQ(-5, pool.depth());
  EXPECT_FALSE(pool.is_valid());
}
