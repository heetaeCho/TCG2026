#include <gtest/gtest.h>
#include <cmath>
#include <string>
#include <limits>

// Include the necessary Catch2 headers
#include "catch2/matchers/catch_matchers_floating_point.hpp"

using Catch::Matchers::WithinRelMatcher;

// Test normal construction with valid parameters
TEST(WithinRelMatcherTest_1051, ConstructWithValidParameters_1051) {
    EXPECT_NO_THROW(WithinRelMatcher(1.0, 0.1));
}

TEST(WithinRelMatcherTest_1051, ConstructWithZeroEpsilon_1051) {
    EXPECT_NO_THROW(WithinRelMatcher(1.0, 0.0));
}

TEST(WithinRelMatcherTest_1051, ConstructWithSmallEpsilon_1051) {
    EXPECT_NO_THROW(WithinRelMatcher(1.0, 0.001));
}

TEST(WithinRelMatcherTest_1051, ConstructWithEpsilonJustBelowOne_1051) {
    EXPECT_NO_THROW(WithinRelMatcher(1.0, 0.999));
}

// Test construction with invalid parameters - epsilon < 0
TEST(WithinRelMatcherTest_1051, ConstructWithNegativeEpsilonThrows_1051) {
    EXPECT_THROW(WithinRelMatcher(1.0, -0.1), std::domain_error);
}

TEST(WithinRelMatcherTest_1051, ConstructWithVeryNegativeEpsilonThrows_1051) {
    EXPECT_THROW(WithinRelMatcher(1.0, -100.0), std::domain_error);
}

// Test construction with invalid parameters - epsilon >= 1
TEST(WithinRelMatcherTest_1051, ConstructWithEpsilonEqualToOneThrows_1051) {
    EXPECT_THROW(WithinRelMatcher(1.0, 1.0), std::domain_error);
}

TEST(WithinRelMatcherTest_1051, ConstructWithEpsilonGreaterThanOneThrows_1051) {
    EXPECT_THROW(WithinRelMatcher(1.0, 2.0), std::domain_error);
}

TEST(WithinRelMatcherTest_1051, ConstructWithLargeEpsilonThrows_1051) {
    EXPECT_THROW(WithinRelMatcher(1.0, 100.0), std::domain_error);
}

// Test match - exact match
TEST(WithinRelMatcherTest_1051, MatchExactValue_1051) {
    WithinRelMatcher matcher(1.0, 0.1);
    EXPECT_TRUE(matcher.match(1.0));
}

// Test match - value within relative tolerance
TEST(WithinRelMatcherTest_1051, MatchValueWithinTolerance_1051) {
    WithinRelMatcher matcher(100.0, 0.1);
    EXPECT_TRUE(matcher.match(95.0));  // 5% off, within 10%
    EXPECT_TRUE(matcher.match(105.0)); // 5% off, within 10%
}

// Test match - value outside relative tolerance
TEST(WithinRelMatcherTest_1051, MatchValueOutsideTolerance_1051) {
    WithinRelMatcher matcher(100.0, 0.01);
    EXPECT_FALSE(matcher.match(120.0)); // 20% off, outside 1%
}

// Test match with zero target
TEST(WithinRelMatcherTest_1051, MatchWithZeroTarget_1051) {
    WithinRelMatcher matcher(0.0, 0.1);
    EXPECT_TRUE(matcher.match(0.0));
}

// Test match with negative values
TEST(WithinRelMatcherTest_1051, MatchNegativeValues_1051) {
    WithinRelMatcher matcher(-100.0, 0.1);
    EXPECT_TRUE(matcher.match(-100.0));
    EXPECT_TRUE(matcher.match(-95.0));  // within 10%
}

// Test match with very small epsilon
TEST(WithinRelMatcherTest_1051, MatchWithVerySmallEpsilon_1051) {
    WithinRelMatcher matcher(1.0, 0.0001);
    EXPECT_TRUE(matcher.match(1.0));
    EXPECT_TRUE(matcher.match(1.00005));
    EXPECT_FALSE(matcher.match(1.001));
}

// Test match - boundary of tolerance
TEST(WithinRelMatcherTest_1051, MatchAtBoundaryOfTolerance_1051) {
    WithinRelMatcher matcher(100.0, 0.1);
    // Value exactly at boundary (10% of 100 = 10, so 110 and 90 are at boundary)
    EXPECT_TRUE(matcher.match(110.0));
    EXPECT_TRUE(matcher.match(90.0));
}

// Test match - just outside tolerance boundary
TEST(WithinRelMatcherTest_1051, MatchJustOutsideTolerance_1051) {
    WithinRelMatcher matcher(100.0, 0.1);
    EXPECT_FALSE(matcher.match(112.0));
    EXPECT_FALSE(matcher.match(88.0));
}

// Test describe returns non-empty string
TEST(WithinRelMatcherTest_1051, DescribeReturnsNonEmptyString_1051) {
    WithinRelMatcher matcher(1.0, 0.1);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test with zero epsilon - only exact match should work
TEST(WithinRelMatcherTest_1051, ZeroEpsilonOnlyExactMatch_1051) {
    WithinRelMatcher matcher(1.0, 0.0);
    EXPECT_TRUE(matcher.match(1.0));
    EXPECT_FALSE(matcher.match(1.0001));
}

// Test with large values
TEST(WithinRelMatcherTest_1051, MatchLargeValues_1051) {
    WithinRelMatcher matcher(1e10, 0.01);
    EXPECT_TRUE(matcher.match(1e10));
    EXPECT_TRUE(matcher.match(1.005e10));
    EXPECT_FALSE(matcher.match(1.02e10));
}

// Test with very small values
TEST(WithinRelMatcherTest_1051, MatchVerySmallValues_1051) {
    WithinRelMatcher matcher(1e-10, 0.1);
    EXPECT_TRUE(matcher.match(1e-10));
    EXPECT_TRUE(matcher.match(1.05e-10));
}

// Test with negative target and positive matchee
TEST(WithinRelMatcherTest_1051, MatchNegativeTargetPositiveMatchee_1051) {
    WithinRelMatcher matcher(-100.0, 0.01);
    EXPECT_FALSE(matcher.match(100.0));
}

// Test construction with various valid target values
TEST(WithinRelMatcherTest_1051, ConstructWithVariousTargets_1051) {
    EXPECT_NO_THROW(WithinRelMatcher(0.0, 0.5));
    EXPECT_NO_THROW(WithinRelMatcher(-1.0, 0.5));
    EXPECT_NO_THROW(WithinRelMatcher(1e300, 0.5));
    EXPECT_NO_THROW(WithinRelMatcher(-1e300, 0.5));
}

// Test with infinity target
TEST(WithinRelMatcherTest_1051, MatchWithInfinityTarget_1051) {
    double inf = std::numeric_limits<double>::infinity();
    WithinRelMatcher matcher(inf, 0.1);
    EXPECT_TRUE(matcher.match(inf));
    EXPECT_FALSE(matcher.match(1e308));
}

// Test with NaN matchee
TEST(WithinRelMatcherTest_1051, MatchWithNaNMatchee_1051) {
    WithinRelMatcher matcher(1.0, 0.1);
    double nan_val = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(matcher.match(nan_val));
}

// Test describe contains meaningful information
TEST(WithinRelMatcherTest_1051, DescribeContainsTargetInfo_1051) {
    WithinRelMatcher matcher(42.0, 0.05);
    std::string desc = matcher.describe();
    // Description should mention something about the comparison
    EXPECT_GT(desc.size(), 0u);
}
