// File: test_uniform_floating_point_distribution_a_344.cpp
#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Include the header under test
#include "catch2/internal/catch_uniform_floating_point_distribution.hpp"

namespace {

using Dist = Catch::uniform_floating_point_distribution<double>;

TEST(UniformFloatingPointDistTest_344, ReturnsConstructorLowerBound_344) {
    Dist dist(1.5, 3.5);
    EXPECT_DOUBLE_EQ(dist.a(), 1.5);
}

TEST(UniformFloatingPointDistTest_344, PreservesNegativeValues_344) {
    Dist dist(-2.0, 5.0);
    EXPECT_DOUBLE_EQ(dist.a(), -2.0);
}

TEST(UniformFloatingPointDistTest_344, HandlesSignedZero_344) {
    // Ensure we pass a negative zero explicitly
    const double neg_zero = -0.0;
    const double pos_zero = 0.0;

    Dist dist(neg_zero, pos_zero);
    const double a = dist.a();

    // Equality alone cannot distinguish -0.0 from +0.0; check signbit.
    EXPECT_EQ(a, 0.0);
    EXPECT_TRUE(std::signbit(a)) << "a() should preserve the sign of -0.0";
}

TEST(UniformFloatingPointDistTest_344, PropagatesInfinity_344) {
    const double inf = std::numeric_limits<double>::infinity();
    Dist dist(inf, 1.0);

    const double a = dist.a();
    EXPECT_TRUE(std::isinf(a));
    EXPECT_FALSE(std::signbit(a)) << "a() should be +inf (not -inf)";
}

TEST(UniformFloatingPointDistTest_344, PropagatesNaN_344) {
    const double nan = std::numeric_limits<double>::quiet_NaN();
    Dist dist(nan, 0.0);

    const double a = dist.a();
    EXPECT_TRUE(std::isnan(a)) << "a() should propagate NaN when constructed with NaN";
}

TEST(UniformFloatingPointDistTest_344, MultipleCallsConsistent_344) {
    Dist dist(-10.25, -9.75);
    const double first = dist.a();
    const double second = dist.a();
    EXPECT_EQ(first, second) << "a() should be const and consistent across calls";
}

} // namespace
