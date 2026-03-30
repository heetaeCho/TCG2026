// File: within_rel_matcher_test_207.cpp
#include <gtest/gtest.h>
#include <limits>
#include <cmath>

// Catch2 matcher declaration header (public API)
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using Catch::Matchers::WithinRel;

class WithinRelTest_207 : public ::testing::Test {
protected:
    // Default relative margin used by WithinRel(double)
    static double DefaultRelEps() {
        return std::numeric_limits<double>::epsilon() * 100.0;
    }
};

// [Normal] Exact target should match itself
TEST_F(WithinRelTest_207, MatchesExactTarget_207) {
    const double target = 1.0;
    auto matcher = WithinRel(target);
    EXPECT_TRUE(matcher.match(target));
}

// [Boundary] Value just inside default relative margin should match
TEST_F(WithinRelTest_207, MatchesWithinDefaultEpsilon_207) {
    const double target = 1.0;
    const double rel = DefaultRelEps() * 0.9; // strictly inside
    const double actual_high = target * (1.0 + rel);
    const double actual_low  = target * (1.0 - rel);

    auto matcher = WithinRel(target);
    EXPECT_TRUE(matcher.match(actual_high));
    EXPECT_TRUE(matcher.match(actual_low));
}

// [Boundary] Value just outside default relative margin should NOT match
TEST_F(WithinRelTest_207, FailsOutsideDefaultEpsilon_207) {
    const double target = 1.0;
    const double rel = DefaultRelEps() * 1.1; // strictly outside
    const double actual_high = target * (1.0 + rel);
    const double actual_low  = target * (1.0 - rel);

    auto matcher = WithinRel(target);
    EXPECT_FALSE(matcher.match(actual_high));
    EXPECT_FALSE(matcher.match(actual_low));
}

// [Normal] Negative targets behave the same by relative distance
TEST_F(WithinRelTest_207, HandlesNegativeValues_207) {
    const double target = -2.5;
    const double rel_inside  = DefaultRelEps() * 0.5;
    const double rel_outside = DefaultRelEps() * 2.0;

    const double actual_in  = target * (1.0 + rel_inside);
    const double actual_out = target * (1.0 + rel_outside);

    auto matcher = WithinRel(target);
    EXPECT_TRUE(matcher.match(actual_in));
    EXPECT_FALSE(matcher.match(actual_out));
}

// [Edge] Zero should match zero; typical tiny non-zero should not match with purely relative tolerance
TEST_F(WithinRelTest_207, ZeroOnlyMatchesZero_207) {
    const double target = 0.0;
    auto matcher = WithinRel(target);

    EXPECT_TRUE(matcher.match(0.0)) << "Zero should match itself";

    // A small non-zero value should be outside purely-relative tolerance
    // (observable behavior via public match()).
    const double tiny = std::numeric_limits<double>::epsilon();
    EXPECT_FALSE(matcher.match(tiny));
}

// [Edge] NaN should not match any target
TEST_F(WithinRelTest_207, NaNDoesNotMatch_207) {
    const double target = 1.23;
    auto matcher = WithinRel(target);

    const double nan_val = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(matcher.match(nan_val));
    EXPECT_FALSE(WithinRel(nan_val).match(target)); // also when target is NaN
}
