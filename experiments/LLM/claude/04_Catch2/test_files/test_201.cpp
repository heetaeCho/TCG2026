#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Include the header for WithinRelMatcher
#include "catch2/matchers/catch_matchers_floating_point.hpp"

using namespace Catch::Matchers;

class WithinRelMatcherTest_201 : public ::testing::Test {
protected:
    // Helper to create matchers with various parameters
};

// Test exact match with zero epsilon
TEST_F(WithinRelMatcherTest_201, ExactMatch_ZeroEpsilon_201) {
    WithinRelMatcher matcher(1.0, 0.0);
    EXPECT_TRUE(matcher.match(1.0));
}

// Test exact match with nonzero epsilon
TEST_F(WithinRelMatcherTest_201, ExactMatch_NonZeroEpsilon_201) {
    WithinRelMatcher matcher(5.0, 0.1);
    EXPECT_TRUE(matcher.match(5.0));
}

// Test value within relative tolerance
TEST_F(WithinRelMatcherTest_201, ValueWithinRelativeTolerance_201) {
    WithinRelMatcher matcher(100.0, 0.01); // 1% tolerance
    EXPECT_TRUE(matcher.match(100.5));
    EXPECT_TRUE(matcher.match(99.5));
}

// Test value outside relative tolerance
TEST_F(WithinRelMatcherTest_201, ValueOutsideRelativeTolerance_201) {
    WithinRelMatcher matcher(100.0, 0.01); // 1% tolerance
    EXPECT_FALSE(matcher.match(102.0));
    EXPECT_FALSE(matcher.match(98.0));
}

// Test value at boundary of tolerance
TEST_F(WithinRelMatcherTest_201, ValueAtBoundaryOfTolerance_201) {
    WithinRelMatcher matcher(100.0, 0.01); // 1% tolerance => margin = 0.01 * 100 = 1.0
    // matchee = 101.0, diff = 1.0, margin = 1.0 => should be within
    EXPECT_TRUE(matcher.match(101.0));
    // matchee = 99.0, diff = 1.0, margin = 1.0 => should be within
    EXPECT_TRUE(matcher.match(99.0));
}

// Test value just outside boundary
TEST_F(WithinRelMatcherTest_201, ValueJustOutsideBoundary_201) {
    WithinRelMatcher matcher(100.0, 0.01);
    // Just beyond the margin
    EXPECT_FALSE(matcher.match(101.1));
    EXPECT_FALSE(matcher.match(98.9));
}

// Test with zero target
TEST_F(WithinRelMatcherTest_201, ZeroTarget_201) {
    WithinRelMatcher matcher(0.0, 0.1);
    // margin = 0.1 * max(|matchee|, 0) = 0.1 * |matchee|
    // For matchee = 0.0: margin = 0, diff = 0 => match
    EXPECT_TRUE(matcher.match(0.0));
}

// Test with zero target and small matchee
TEST_F(WithinRelMatcherTest_201, ZeroTargetSmallMatchee_201) {
    WithinRelMatcher matcher(0.0, 0.1);
    // margin = 0.1 * max(|0.05|, |0|) = 0.1 * 0.05 = 0.005
    // diff = 0.05, 0.05 > 0.005 => no match
    EXPECT_FALSE(matcher.match(0.05));
}

// Test with negative values
TEST_F(WithinRelMatcherTest_201, NegativeValues_201) {
    WithinRelMatcher matcher(-100.0, 0.01);
    EXPECT_TRUE(matcher.match(-100.0));
    EXPECT_TRUE(matcher.match(-100.5));
    EXPECT_TRUE(matcher.match(-99.5));
}

// Test with negative target and positive matchee far away
TEST_F(WithinRelMatcherTest_201, NegativeTargetPositiveMatchee_201) {
    WithinRelMatcher matcher(-100.0, 0.01);
    EXPECT_FALSE(matcher.match(100.0));
}

// Test with very small epsilon
TEST_F(WithinRelMatcherTest_201, VerySmallEpsilon_201) {
    WithinRelMatcher matcher(1.0, 1e-15);
    EXPECT_TRUE(matcher.match(1.0));
    EXPECT_FALSE(matcher.match(1.0 + 1e-10));
}

// Test with large epsilon (100%)
TEST_F(WithinRelMatcherTest_201, LargeEpsilon_201) {
    WithinRelMatcher matcher(100.0, 1.0); // 100% tolerance
    // margin = 1.0 * max(|matchee|, 100)
    EXPECT_TRUE(matcher.match(0.0));    // margin = 1.0 * 100 = 100, diff = 100 => match
    EXPECT_TRUE(matcher.match(200.0));  // margin = 1.0 * 200 = 200, diff = 100 => match
}

// Test with infinity target
TEST_F(WithinRelMatcherTest_201, InfinityTarget_201) {
    WithinRelMatcher matcher(std::numeric_limits<double>::infinity(), 0.1);
    // relMargin would be inf, so isinf check makes margin = 0
    // Only exact infinity should match
    EXPECT_TRUE(matcher.match(std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(matcher.match(1e308));
}

// Test with negative infinity target
TEST_F(WithinRelMatcherTest_201, NegativeInfinityTarget_201) {
    WithinRelMatcher matcher(-std::numeric_limits<double>::infinity(), 0.1);
    EXPECT_TRUE(matcher.match(-std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(matcher.match(-1e308));
}

// Test with infinity matchee and finite target
TEST_F(WithinRelMatcherTest_201, InfinityMatcheeFiniteTarget_201) {
    WithinRelMatcher matcher(100.0, 0.1);
    // relMargin = 0.1 * max(inf, 100) = inf => isinf => margin = 0
    // diff = inf - 100 = inf, not <= 0
    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::infinity()));
}

// Test NaN matchee
TEST_F(WithinRelMatcherTest_201, NaNMatchee_201) {
    WithinRelMatcher matcher(1.0, 0.1);
    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::quiet_NaN()));
}

// Test NaN target
TEST_F(WithinRelMatcherTest_201, NaNTarget_201) {
    WithinRelMatcher matcher(std::numeric_limits<double>::quiet_NaN(), 0.1);
    EXPECT_FALSE(matcher.match(1.0));
}

// Test both NaN
TEST_F(WithinRelMatcherTest_201, BothNaN_201) {
    WithinRelMatcher matcher(std::numeric_limits<double>::quiet_NaN(), 0.1);
    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::quiet_NaN()));
}

// Test with very large values
TEST_F(WithinRelMatcherTest_201, VeryLargeValues_201) {
    double large = 1e300;
    WithinRelMatcher matcher(large, 0.01);
    EXPECT_TRUE(matcher.match(large));
    EXPECT_TRUE(matcher.match(large * 1.005));
    EXPECT_FALSE(matcher.match(large * 1.02));
}

// Test with very small values (subnormal range)
TEST_F(WithinRelMatcherTest_201, VerySmallValues_201) {
    double tiny = 1e-300;
    WithinRelMatcher matcher(tiny, 0.01);
    EXPECT_TRUE(matcher.match(tiny));
    EXPECT_TRUE(matcher.match(tiny * 1.005));
}

// Test symmetry - the relative margin uses max of fabs(matchee) and fabs(target)
TEST_F(WithinRelMatcherTest_201, AsymmetricBehavior_201) {
    // margin = epsilon * max(|matchee|, |target|)
    // target=10, matchee=11: margin = 0.1 * max(11, 10) = 1.1, diff = 1 => match
    WithinRelMatcher matcher1(10.0, 0.1);
    EXPECT_TRUE(matcher1.match(11.0));
    
    // target=11, matchee=10: margin = 0.1 * max(10, 11) = 1.1, diff = 1 => match
    WithinRelMatcher matcher2(11.0, 0.1);
    EXPECT_TRUE(matcher2.match(10.0));
}

// Test describe returns a non-empty string
TEST_F(WithinRelMatcherTest_201, DescribeReturnsNonEmpty_201) {
    WithinRelMatcher matcher(1.0, 0.01);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test with epsilon = 0 and different values
TEST_F(WithinRelMatcherTest_201, ZeroEpsilonDifferentValues_201) {
    WithinRelMatcher matcher(1.0, 0.0);
    EXPECT_FALSE(matcher.match(1.0 + std::numeric_limits<double>::epsilon()));
}

// Test mixed sign target and matchee close to zero
TEST_F(WithinRelMatcherTest_201, MixedSignCloseToZero_201) {
    WithinRelMatcher matcher(0.001, 0.1);
    // margin = 0.1 * max(|-0.001|, |0.001|) = 0.1 * 0.001 = 0.0001
    // diff = 0.002
    EXPECT_FALSE(matcher.match(-0.001));
}

// Test both positive infinity
TEST_F(WithinRelMatcherTest_201, BothPositiveInfinity_201) {
    WithinRelMatcher matcher(std::numeric_limits<double>::infinity(), 0.1);
    // relMargin = inf => isinf => margin = 0
    // diff = inf - inf = NaN or 0; marginComparison with 0
    EXPECT_TRUE(matcher.match(std::numeric_limits<double>::infinity()));
}

// Test positive vs negative infinity
TEST_F(WithinRelMatcherTest_201, PositiveVsNegativeInfinity_201) {
    WithinRelMatcher matcher(std::numeric_limits<double>::infinity(), 0.1);
    EXPECT_FALSE(matcher.match(-std::numeric_limits<double>::infinity()));
}
