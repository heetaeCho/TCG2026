// File: ./TestProjects/ninja/tests/pool_is_valid_test_74.cc

#include "gtest/gtest.h"
#include "state.h"

class PoolTest_74 : public ::testing::Test {
protected:
  // Helper to create a Pool with given depth.
  Pool MakePool(const std::string& name, int depth) {
    return Pool(name, depth);
  }
};

// Normal operation: positive depth should be considered valid.
TEST_F(PoolTest_74, IsValidReturnsTrueWhenDepthIsPositive_74) {
  Pool pool = MakePool("link_pool", 5);

  EXPECT_TRUE(pool.is_valid());
}

// Boundary condition: depth == 0.
TEST_F(PoolTest_74, IsValidReturnsTrueWhenDepthIsZero_74) {
  Pool pool = MakePool("zero_pool", 0);

  EXPECT_TRUE(pool.is_valid());
}

// Boundary / error-like condition: negative depth.
TEST_F(PoolTest_74, IsValidReturnsFalseWhenDepthIsNegative_74) {
  Pool pool = MakePool("negative_pool", -1);

  EXPECT_FALSE(pool.is_valid());
}
