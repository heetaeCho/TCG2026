// File: ./TestProjects/ninja/src/hash_collision_bench_test.cc

#include <gtest/gtest.h>

// Function under test (implemented in hash_collision_bench.cc).
// We only declare it here; we do NOT re-implement it.
int random(int low, int high);

//
// Test suite for random(int low, int high)
// TEST_ID = 119
//

// Normal operation: values within a positive range
TEST(RandomFunctionTest_119, ReturnsValueWithinPositiveRange_119) {
  const int low = 0;
  const int high = 10;

  // Call multiple times to increase confidence.
  for (int i = 0; i < 1000; ++i) {
    int value = ::random(low, high);
    EXPECT_GE(value, low);
    EXPECT_LE(value, high);
  }
}

// Normal operation with negative-only range
TEST(RandomFunctionTest_119, ReturnsValueWithinNegativeRange_119) {
  const int low = -20;
  const int high = -5;

  for (int i = 0; i < 1000; ++i) {
    int value = ::random(low, high);
    EXPECT_GE(value, low);
    EXPECT_LE(value, high);
  }
}

// Normal operation with range spanning negative to positive (mixed sign)
TEST(RandomFunctionTest_119, ReturnsValueWithinMixedSignRange_119) {
  const int low = -5;
  const int high = 5;

  for (int i = 0; i < 1000; ++i) {
    int value = ::random(low, high);
    EXPECT_GE(value, low);
    EXPECT_LE(value, high);
  }
}

// Boundary condition: low == high should always return that exact value
TEST(RandomFunctionTest_119, SingleValueRangeReturnsThatValue_119) {
  const int fixed_value = 42;

  for (int i = 0; i < 1000; ++i) {
    int value = ::random(fixed_value, fixed_value);
    EXPECT_EQ(fixed_value, value);
  }
}
