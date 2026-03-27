// Filename: isnan_matcher_test_210.cpp
#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Include the header that declares Catch::Matchers::IsNaNMatcher.
// If your build already exposes it via include paths, keep this as-is.
// Otherwise, adjust the relative path as needed.
#include "catch2/matchers/catch_matchers_floating_point.hpp"

using Catch::Matchers::IsNaNMatcher;

class IsNaNMatcherTest_210 : public ::testing::Test {
protected:
    IsNaNMatcher matcher_;
};

// Normal operation: quiet NaN should match
TEST_F(IsNaNMatcherTest_210, ReturnsTrueForQuietNaN_210) {
    const double qnan = std::numeric_limits<double>::quiet_NaN();
    EXPECT_TRUE(matcher_.match(qnan));
}

// Normal operation: finite values should not match
TEST_F(IsNaNMatcherTest_210, ReturnsFalseForFiniteNumbers_210) {
    EXPECT_FALSE(matcher_.match(0.0));
    EXPECT_FALSE(matcher_.match(1.0));
    EXPECT_FALSE(matcher_.match(-1.0));
    EXPECT_FALSE(matcher_.match(12345.6789));
}

// Boundary condition: infinities are not NaN
TEST_F(IsNaNMatcherTest_210, ReturnsFalseForInfinities_210) {
    const double pos_inf = std::numeric_limits<double>::infinity();
    const double neg_inf = -std::numeric_limits<double>::infinity();
    EXPECT_FALSE(matcher_.match(pos_inf));
    EXPECT_FALSE(matcher_.match(neg_inf));
}

// Boundary condition: negative zero should not match
TEST_F(IsNaNMatcherTest_210, ReturnsFalseForNegativeZero_210) {
    const double neg_zero = -0.0;
    ASSERT_TRUE(std::signbit(neg_zero)); // ensure it's actually negative zero
    EXPECT_FALSE(matcher_.match(neg_zero));
}

// Exceptional-ish input: signaling NaN (if supported) should match
TEST_F(IsNaNMatcherTest_210, ReturnsTrueForSignalingNaNIfSupported_210) {
    if (std::numeric_limits<double>::has_signaling_NaN) {
        volatile double snan = std::numeric_limits<double>::signaling_NaN();
        // volatile to discourage compiler folding/optimizations around sNaN
        EXPECT_TRUE(matcher_.match(snan));
    } else {
        GTEST_SKIP() << "signaling NaN not supported on this platform";
    }
}

// Idempotence / stability: multiple calls with mixed inputs should be consistent
TEST_F(IsNaNMatcherTest_210, StableAcrossMultipleCalls_210) {
    const double qnan = std::numeric_limits<double>::quiet_NaN();
    EXPECT_TRUE(matcher_.match(qnan));
    EXPECT_FALSE(matcher_.match(42.0));
    EXPECT_FALSE(matcher_.match(std::numeric_limits<double>::infinity()));
    EXPECT_TRUE(matcher_.match(std::numeric_limits<double>::quiet_NaN()));
}

// Oracle-based check (without re-implementing internals):
// For a variety of values, result should match std::isnan's observable behavior.
TEST_F(IsNaNMatcherTest_210, MatchesStdIsNaNBehaviorForRepresentativeValues_210) {
    const double vals[] = {
        0.0,
        -0.0,
        1.0,
        -3.14,
        std::numeric_limits<double>::infinity(),
        -std::numeric_limits<double>::infinity(),
        std::numeric_limits<double>::quiet_NaN()
    };

    for (double v : vals) {
        bool expected = std::isnan(v);
        EXPECT_EQ(expected, matcher_.match(v)) << "value under test: " << v;
    }

    if (std::numeric_limits<double>::has_signaling_NaN) {
        volatile double snan = std::numeric_limits<double>::signaling_NaN();
        EXPECT_EQ(std::isnan(snan), matcher_.match(snan));
    }
}
