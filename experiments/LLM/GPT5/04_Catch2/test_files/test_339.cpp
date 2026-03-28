// File: catch_random_floating_point_helpers_tests_339.cpp

#include <gtest/gtest.h>
#include <limits>
#include <cmath>

#include "catch2/internal/catch_random_floating_point_helpers.hpp"

// We always qualify with Catch::Detail to avoid clashes with ::gamma/tgamma.
template <typename T>
class GammaHelperTypedTest_339 : public ::testing::Test {};

using FloatTypes_339 = ::testing::Types<float, double, long double>;
TYPED_TEST_SUITE(GammaHelperTypedTest_339, FloatTypes_339);

// [Normal] Degenerate range [v, v] -> largest ULP in the range is ULP at v.
TYPED_TEST(GammaHelperTypedTest_339, DegenerateRangeReturnsUlpAtThatPoint_339) {
    using T = TypeParam;
    const T v = static_cast<T>(1.0);
    const T expected = std::nextafter(v, std::numeric_limits<T>::infinity()) - v;
    const T got = Catch::Detail::gamma<T>(v, v);
    ASSERT_EQ(expected, got);
}

// [Boundary] Exact zero range -> should be the smallest positive subnormal.
TYPED_TEST(GammaHelperTypedTest_339, ZeroRangeReturnsSmallestPositive_339) {
    using T = TypeParam;
    const T zero = static_cast<T>(0);
    const T expected = std::nextafter(zero, std::numeric_limits<T>::infinity());
    const T got = Catch::Detail::gamma<T>(zero, zero);
    ASSERT_EQ(expected, got);
}

// [Property] Non-decreasing with upper bound: expanding [a, b] upward can't decrease result.
TYPED_TEST(GammaHelperTypedTest_339, MonotoneInUpperBound_339) {
    using T = TypeParam;
    const T a  = static_cast<T>(1.0);
    const T b1 = static_cast<T>(2.0);
    const T b2 = static_cast<T>(4.0);

    const T g1 = Catch::Detail::gamma<T>(a, b1);
    const T g2 = Catch::Detail::gamma<T>(a, b2);

    ASSERT_LE(g1, g2);
}

// [Normal] Result is non-negative and finite for finite ordered inputs.
TYPED_TEST(GammaHelperTypedTest_339, NonNegativeForFiniteOrderedInputs_339) {
    using T = TypeParam;
    const T a = static_cast<T>(-123.0);
    const T b = static_cast<T>(456.0);

    const T g = Catch::Detail::gamma<T>(a, b);

    ASSERT_GE(g, static_cast<T>(0));
    ASSERT_TRUE(std::isfinite(static_cast<long double>(g)));
}

// [Boundary/Property] Symmetric interval [-x, x] has the same largest ULP as [0, x].
TYPED_TEST(GammaHelperTypedTest_339, SymmetricAroundZeroHasSameAsPositiveHalf_339) {
    using T = TypeParam;
    const T x = static_cast<T>(8.0);

    const T g_full = Catch::Detail::gamma<T>(-x, x);
    const T g_half = Catch::Detail::gamma<T>(static_cast<T>(0), x);

    ASSERT_EQ(g_full, g_half);
}

// [Boundary] If upper bound is +infinity, result is +infinity (largest ULP in [a, +inf]).
TEST(GammaHelperTest_339, UpperBoundInfinityYieldsInfinity_339) {
    const double a = 1.0;
    const double b = std::numeric_limits<double>::infinity();

    const double g = Catch::Detail::gamma<double>(a, b);

    ASSERT_TRUE(std::isinf(g));
    ASSERT_GT(g, 0.0);
}

// [Boundary] If lower bound is -infinity, result is +infinity (largest ULP in [-inf, b]).
TEST(GammaHelperTest_339, LowerBoundMinusInfinityYieldsInfinity_339) {
    const double a = -std::numeric_limits<double>::infinity();
    const double b = 1.0;

    const double g = Catch::Detail::gamma<double>(a, b);

    ASSERT_TRUE(std::isinf(g));
    ASSERT_GT(g, 0.0);
}

// [Exceptional/Error] Contract violation: a > b triggers assert.
// Guarded so it only runs when asserts are enabled.
#ifndef NDEBUG
# if GTEST_HAS_DEATH_TEST
TEST(GammaHelperDeathTest_339, AssertsWhenAIsGreaterThanB_339) {
    EXPECT_DEATH( (void)Catch::Detail::gamma<double>(2.0, 1.0), ".*" );
}

// [Exceptional/Error] NaN inputs violate a <= b and should assert.
TEST(GammaHelperDeathTest_339, AssertsOnNaNInputs_339) {
    const double nan = std::numeric_limits<double>::quiet_NaN();
    EXPECT_DEATH( (void)Catch::Detail::gamma<double>(nan, 0.0), ".*" );
    EXPECT_DEATH( (void)Catch::Detail::gamma<double>(0.0, nan), ".*" );
}
# endif
#endif
