// File: is_nan_matcher_test_211.cpp

#include <gtest/gtest.h>
#include <limits>
#include <cmath>

// Include the matcher under test (as provided by your codebase)
#include "catch2/matchers/catch_matchers_floating_point.hpp"

using Catch::Matchers::IsNaNMatcher;

class IsNaNMatcherTest_211 : public ::testing::Test {
protected:
    IsNaNMatcher matcher; // System Under Test
};

// --- Description behavior ---

// Verifies that describe() reports a stable, user-facing description.
TEST_F(IsNaNMatcherTest_211, DescribeReturnsIsNaN_211) {
    EXPECT_EQ(matcher.describe(), "is NaN");
}

// --- Matching behavior: normal operation ---

// Quiet NaN should be matched as NaN.
TEST_F(IsNaNMatcherTest_211, MatchReturnsTrueForQuietNaN_211) {
    const double qnan = std::numeric_limits<double>::quiet_NaN();
    EXPECT_TRUE(matcher.match(qnan));
}

// If the platform provides signaling NaN, it should also be considered NaN.
TEST_F(IsNaNMatcherTest_211, MatchReturnsTrueForSignalingNaNWhenAvailable_211) {
    if (!std::numeric_limits<double>::has_signaling_NaN) {
        GTEST_SKIP() << "Platform does not provide signaling NaN.";
    }
    const double snan = std::numeric_limits<double>::signaling_NaN();
    EXPECT_TRUE(matcher.match(snan));
}

// Finite numbers should not match.
TEST_F(IsNaNMatcherTest_211, MatchReturnsFalseForFiniteNumbers_211) {
    EXPECT_FALSE(matcher.match(0.0));
    EXPECT_FALSE(matcher.match(-0.0));
    EXPECT_FALSE(matcher.match(1.0));
    EXPECT_FALSE(matcher.match(-42.5));
    EXPECT_FALSE(matcher.match(1e-300));  // subnormal/very small finite
    EXPECT_FALSE(matcher.match(1e300));    // very large finite
}

// Infinities are not NaN and should not match.
TEST_F(IsNaNMatcherTest_211, MatchReturnsFalseForInfinities_211) {
    const double pos_inf = std::numeric_limits<double>::infinity();
    const double neg_inf = -std::numeric_limits<double>::infinity();
    EXPECT_FALSE(matcher.match(pos_inf));
    EXPECT_FALSE(matcher.match(neg_inf));
}

// --- Stability / idempotence (observable through repeated calls) ---

// Repeated calls with identical inputs should yield the same observable result.
TEST_F(IsNaNMatcherTest_211, MatchIsIdempotentForSameInput_211) {
    const double qnan = std::numeric_limits<double>::quiet_NaN();
    const double finite = 3.141592653589793;

    // Call multiple times; results should not change.
    EXPECT_TRUE(matcher.match(qnan));
    EXPECT_TRUE(matcher.match(qnan));

    EXPECT_FALSE(matcher.match(finite));
    EXPECT_FALSE(matcher.match(finite));
}
