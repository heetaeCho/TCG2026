#include <gtest/gtest.h>
#include <cmath>

// Replicate the macro/function under test exactly as provided
static inline bool IS_CLOSER(double x, double y, double z) { return std::fabs((x) - (y)) < std::fabs((x) - (z)); }

// Normal operation tests

TEST(IsCloserTest_2729, YIsCloserThanZ_2729) {
    // x=5, y=6 (distance 1), z=10 (distance 5) => y is closer
    EXPECT_TRUE(IS_CLOSER(5.0, 6.0, 10.0));
}

TEST(IsCloserTest_2729, ZIsCloserThanY_2729) {
    // x=5, y=10 (distance 5), z=6 (distance 1) => z is closer, so returns false
    EXPECT_FALSE(IS_CLOSER(5.0, 10.0, 6.0));
}

TEST(IsCloserTest_2729, YAndZEquidistant_2729) {
    // x=5, y=3 (distance 2), z=7 (distance 2) => equal distance, not strictly less
    EXPECT_FALSE(IS_CLOSER(5.0, 3.0, 7.0));
}

TEST(IsCloserTest_2729, YEqualsX_2729) {
    // y equals x, distance is 0, z is different => true
    EXPECT_TRUE(IS_CLOSER(5.0, 5.0, 10.0));
}

TEST(IsCloserTest_2729, ZEqualsX_2729) {
    // z equals x, distance to z is 0, y is different => false
    EXPECT_FALSE(IS_CLOSER(5.0, 10.0, 5.0));
}

TEST(IsCloserTest_2729, BothEqualX_2729) {
    // Both y and z equal x => distances are both 0, not strictly less
    EXPECT_FALSE(IS_CLOSER(5.0, 5.0, 5.0));
}

// Negative number tests

TEST(IsCloserTest_2729, NegativeNumbers_YCloser_2729) {
    // x=-5, y=-4 (distance 1), z=0 (distance 5) => y is closer
    EXPECT_TRUE(IS_CLOSER(-5.0, -4.0, 0.0));
}

TEST(IsCloserTest_2729, NegativeNumbers_ZCloser_2729) {
    // x=-5, y=0 (distance 5), z=-4 (distance 1) => z is closer
    EXPECT_FALSE(IS_CLOSER(-5.0, 0.0, -4.0));
}

TEST(IsCloserTest_2729, MixedSigns_YCloser_2729) {
    // x=0, y=-1 (distance 1), z=5 (distance 5)
    EXPECT_TRUE(IS_CLOSER(0.0, -1.0, 5.0));
}

TEST(IsCloserTest_2729, MixedSigns_ZCloser_2729) {
    // x=0, y=5 (distance 5), z=-1 (distance 1)
    EXPECT_FALSE(IS_CLOSER(0.0, 5.0, -1.0));
}

// Boundary / edge case tests with very small differences

TEST(IsCloserTest_2729, VerySmallDifference_2729) {
    // x=1.0, y=1.0000001 (very close), z=2.0 (far)
    EXPECT_TRUE(IS_CLOSER(1.0, 1.0000001, 2.0));
}

TEST(IsCloserTest_2729, VerySmallDifferenceBothClose_2729) {
    // x=0.0, y=1e-10, z=2e-10
    EXPECT_TRUE(IS_CLOSER(0.0, 1e-10, 2e-10));
}

// Large number tests

TEST(IsCloserTest_2729, LargeNumbers_YCloser_2729) {
    EXPECT_TRUE(IS_CLOSER(1e15, 1e15 + 1.0, 1e15 + 1e6));
}

TEST(IsCloserTest_2729, LargeNumbers_ZCloser_2729) {
    EXPECT_FALSE(IS_CLOSER(1e15, 1e15 + 1e6, 1e15 + 1.0));
}

// Zero as x

TEST(IsCloserTest_2729, ZeroAsX_YCloser_2729) {
    EXPECT_TRUE(IS_CLOSER(0.0, 0.1, 1.0));
}

TEST(IsCloserTest_2729, ZeroAsX_ZCloser_2729) {
    EXPECT_FALSE(IS_CLOSER(0.0, 1.0, 0.1));
}

// Symmetry tests: swapping y and z should flip the result (when not equal distance)

TEST(IsCloserTest_2729, SwapYZ_2729) {
    double x = 3.0, y = 2.0, z = 10.0;
    bool result1 = IS_CLOSER(x, y, z);
    bool result2 = IS_CLOSER(x, z, y);
    EXPECT_TRUE(result1);
    EXPECT_FALSE(result2);
}

// Test with infinity

TEST(IsCloserTest_2729, InfinityAsZ_2729) {
    double inf = std::numeric_limits<double>::infinity();
    // y=1.0 is closer to x=0 than z=infinity
    EXPECT_TRUE(IS_CLOSER(0.0, 1.0, inf));
}

TEST(IsCloserTest_2729, InfinityAsY_2729) {
    double inf = std::numeric_limits<double>::infinity();
    // y=infinity is farther from x=0 than z=1.0
    EXPECT_FALSE(IS_CLOSER(0.0, inf, 1.0));
}

// Test with negative infinity

TEST(IsCloserTest_2729, NegativeInfinityAsZ_2729) {
    double neg_inf = -std::numeric_limits<double>::infinity();
    EXPECT_TRUE(IS_CLOSER(0.0, 1.0, neg_inf));
}

// Fractional numbers

TEST(IsCloserTest_2729, Fractions_YCloser_2729) {
    EXPECT_TRUE(IS_CLOSER(0.5, 0.6, 1.5));
}

TEST(IsCloserTest_2729, Fractions_ZCloser_2729) {
    EXPECT_FALSE(IS_CLOSER(0.5, 1.5, 0.6));
}
