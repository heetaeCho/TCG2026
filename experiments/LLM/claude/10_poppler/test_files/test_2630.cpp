#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Include the header under test
#include "HtmlUtils.h"

// Test normal operation: values within threshold
TEST(IsWithinTest_2630, ValuesWithinThreshold_2630) {
    EXPECT_TRUE(is_within(5.0, 1.0, 5.5));
    EXPECT_TRUE(is_within(10.0, 0.5, 10.3));
    EXPECT_TRUE(is_within(0.0, 1.0, 0.5));
}

// Test normal operation: values outside threshold
TEST(IsWithinTest_2630, ValuesOutsideThreshold_2630) {
    EXPECT_FALSE(is_within(5.0, 1.0, 6.5));
    EXPECT_FALSE(is_within(10.0, 0.5, 11.0));
    EXPECT_FALSE(is_within(0.0, 0.1, 0.5));
}

// Test boundary: difference exactly equal to threshold (should return false since < not <=)
TEST(IsWithinTest_2630, ExactlyAtThreshold_2630) {
    EXPECT_FALSE(is_within(5.0, 1.0, 6.0));
    EXPECT_FALSE(is_within(5.0, 1.0, 4.0));
    EXPECT_FALSE(is_within(0.0, 0.5, 0.5));
    EXPECT_FALSE(is_within(0.0, 0.5, -0.5));
}

// Test boundary: difference just below threshold
TEST(IsWithinTest_2630, JustBelowThreshold_2630) {
    EXPECT_TRUE(is_within(5.0, 1.0, 5.999999));
    EXPECT_TRUE(is_within(5.0, 1.0, 4.000001));
}

// Test boundary: difference just above threshold
TEST(IsWithinTest_2630, JustAboveThreshold_2630) {
    EXPECT_FALSE(is_within(5.0, 1.0, 6.000001));
    EXPECT_FALSE(is_within(5.0, 1.0, 3.999999));
}

// Test with identical values (difference is 0)
TEST(IsWithinTest_2630, IdenticalValues_2630) {
    EXPECT_TRUE(is_within(5.0, 1.0, 5.0));
    EXPECT_TRUE(is_within(0.0, 0.001, 0.0));
    EXPECT_TRUE(is_within(-3.0, 0.1, -3.0));
}

// Test with zero threshold
TEST(IsWithinTest_2630, ZeroThreshold_2630) {
    EXPECT_FALSE(is_within(5.0, 0.0, 5.0));  // fabs(0) < 0 is false
    EXPECT_FALSE(is_within(5.0, 0.0, 5.1));
}

// Test with negative values
TEST(IsWithinTest_2630, NegativeValues_2630) {
    EXPECT_TRUE(is_within(-5.0, 1.0, -5.5));
    EXPECT_TRUE(is_within(-5.0, 1.0, -4.5));
    EXPECT_FALSE(is_within(-5.0, 1.0, -6.5));
    EXPECT_FALSE(is_within(-5.0, 1.0, -3.5));
}

// Test with mixed positive and negative values
TEST(IsWithinTest_2630, MixedPositiveNegative_2630) {
    EXPECT_TRUE(is_within(-0.5, 1.5, 0.5));
    EXPECT_TRUE(is_within(0.5, 1.5, -0.5));
    EXPECT_FALSE(is_within(-5.0, 1.0, 5.0));
}

// Test with very small threshold
TEST(IsWithinTest_2630, VerySmallThreshold_2630) {
    EXPECT_TRUE(is_within(1.0, 1e-10, 1.0 + 1e-11));
    EXPECT_FALSE(is_within(1.0, 1e-10, 1.0 + 1e-9));
}

// Test with very large values
TEST(IsWithinTest_2630, VeryLargeValues_2630) {
    EXPECT_TRUE(is_within(1e15, 1.0, 1e15 + 0.5));
    EXPECT_FALSE(is_within(1e15, 1.0, 1e15 + 1.5));
}

// Test symmetry: is_within(a, thresh, b) should equal is_within(b, thresh, a)
TEST(IsWithinTest_2630, SymmetryProperty_2630) {
    EXPECT_EQ(is_within(3.0, 1.0, 3.5), is_within(3.5, 1.0, 3.0));
    EXPECT_EQ(is_within(3.0, 1.0, 5.0), is_within(5.0, 1.0, 3.0));
    EXPECT_EQ(is_within(-2.0, 0.5, -1.8), is_within(-1.8, 0.5, -2.0));
}

// Test with a very large threshold
TEST(IsWithinTest_2630, LargeThreshold_2630) {
    EXPECT_TRUE(is_within(0.0, 1e15, 1e14));
    EXPECT_TRUE(is_within(-1e10, 1e15, 1e10));
}

// Test with positive zero and negative zero
TEST(IsWithinTest_2630, PositiveAndNegativeZero_2630) {
    EXPECT_TRUE(is_within(0.0, 0.1, -0.0));
    // fabs(0.0 - (-0.0)) should be 0.0, which is < 0.1
}
