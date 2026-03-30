// File: uniform_floating_point_distribution_tests_343.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_uniform_floating_point_distribution.hpp"
#include <random>
#include <cmath>
#include <limits>

using ::testing::AtLeast;
using ::testing::Return;

namespace {

template <typename T>
inline T min2(T a, T b) { return a < b ? a : b; }

template <typename T>
inline T max2(T a, T b) { return a > b ? a : b; }

// A mockable generator that conforms to UniformRandomBitGenerator.
// We verify that the distribution calls into the supplied generator.
struct MockGenerator {
    using result_type = uint32_t;
    static constexpr result_type min() { return std::numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }

    MOCK_METHOD(result_type, generate, ());
    result_type operator()() { return generate(); }
};

} // namespace

// 1) Accessors return constructor arguments.
TEST(UniformFloatingPointDistribution_343, AccessorsReturnCtorArgs_343) {
    Catch::uniform_floating_point_distribution<double> dist(-1.5, 3.0);
    EXPECT_DOUBLE_EQ(dist.a(), -1.5);
    EXPECT_DOUBLE_EQ(dist.b(), 3.0);
}

// 2) Values are within [min(a,b), max(a,b)] for many samples (normal operation).
TEST(UniformFloatingPointDistribution_343, GeneratesWithinClosedInterval_343) {
    const double a = -2.0;
    const double b = 5.0;
    Catch::uniform_floating_point_distribution<double> dist(a, b);

    std::mt19937 rng(12345u); // deterministic engine for repeatability

    const double lo = min2(a, b);
    const double hi = max2(a, b);

    for (int i = 0; i < 1000; ++i) {
        double x = dist(rng);
        ASSERT_TRUE(std::isfinite(x));
        EXPECT_LE(lo, x);
        EXPECT_LE(x, hi);
    }
}

// 3) Degenerate range a == b always returns that value (boundary condition).
TEST(UniformFloatingPointDistribution_343, DegenerateRangeAlwaysReturnsEndpoint_343) {
    const double v = 0.0;
    Catch::uniform_floating_point_distribution<double> dist(v, v);

    std::mt19937 rng(7u);
    for (int i = 0; i < 50; ++i) {
        double x = dist(rng);
        EXPECT_DOUBLE_EQ(x, v);
    }
}

// 4) Works with negative-only ranges (normal/boundary mix).
TEST(UniformFloatingPointDistribution_343, NegativeOnlyRangeWithinBounds_343) {
    const double a = -5.0;
    const double b = -1.0;
    Catch::uniform_floating_point_distribution<double> dist(a, b);

    std::mt19937 rng(4242u);

    const double lo = min2(a, b);
    const double hi = max2(a, b);

    for (int i = 0; i < 200; ++i) {
        double x = dist(rng);
        ASSERT_TRUE(std::isfinite(x));
        EXPECT_LE(lo, x);
        EXPECT_LE(x, hi);
    }
}

// 5) Large-magnitude endpoints still yield results within bounds (stress/edge).
TEST(UniformFloatingPointDistribution_343, LargeMagnitudeRangeWithinBounds_343) {
    const double a = -1e6;
    const double b = 1e6;
    Catch::uniform_floating_point_distribution<double> dist(a, b);

    std::mt19937_64 rng(999u);

    const double lo = min2(a, b);
    const double hi = max2(a, b);

    for (int i = 0; i < 500; ++i) {
        double x = dist(rng);
        ASSERT_TRUE(std::isfinite(x));
        EXPECT_LE(lo, x);
        EXPECT_LE(x, hi);
    }
}

// 6) Verifies external interaction: the provided generator is invoked
//    when operator()(Generator&) is called (without assuming any count).
TEST(UniformFloatingPointDistribution_343, InvokesProvidedGenerator_AtLeastOnce_343) {
    Catch::uniform_floating_point_distribution<double> dist(0.0, 1.0);

    MockGenerator mockGen;
    // Provide a stable value for underlying RNG calls; we do not assume
    // how many times it is called internally.
    EXPECT_CALL(mockGen, generate())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(123456789u));

    // Exercise once; expectation ensures external collaborator is used.
    (void)dist(mockGen);
}

