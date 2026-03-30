// File: tests/test_uniform_floating_point_distribution_1058.cpp

#include <gtest/gtest.h>
#include <random>
#include <limits>
#include <type_traits>

// Include the class under test
#include "Catch2/src/catch2/internal/catch_uniform_floating_point_distribution.hpp"

using Catch::uniform_floating_point_distribution;

// A simple helper to run multiple samples and check bounds without inferring internals.
template <typename Dist, typename URBG>
static void sampleAndAssertInRange(Dist& dist, URBG& g, typename Dist::result_type a, typename Dist::result_type b, int samples = 10000) {
    for (int i = 0; i < samples; ++i) {
        auto v = dist(g);
        EXPECT_GE(v, a);
        EXPECT_LE(v, b);
    }
}

// Type-parameterized tests for float and double
template <typename T>
class UniformFPDistTyped_1058 : public ::testing::Test {
public:
    using Float = T;
    using Dist  = uniform_floating_point_distribution<Float>;
    using URBG  = std::mt19937; // external generator we control (not mocked)
};

using TestedFloatTypes_1058 = ::testing::Types<float, double>;
TYPED_TEST_SUITE(UniformFPDistTyped_1058, TestedFloatTypes_1058);

// --- Normal operation: accessors reflect constructor inputs
TYPED_TEST(UniformFPDistTyped_1058, AccessorsReturnCtorValues_1058) {
    using Float = typename TestFixture::Float;
    using Dist  = typename TestFixture::Dist;

    const Float a = static_cast<Float>(-3.5);
    const Float b = static_cast<Float>(7.25);

    Dist d(a, b);
    EXPECT_EQ(d.a(), a);
    EXPECT_EQ(d.b(), b);
}

// --- Normal operation: generated values are within [a, b]
TYPED_TEST(UniformFPDistTyped_1058, SamplesAreWithinClosedInterval_1058) {
    using Float = typename TestFixture::Float;
    using Dist  = typename TestFixture::Dist;
    using URBG  = typename TestFixture::URBG;

    const Float a = static_cast<Float>(-10);
    const Float b = static_cast<Float>(10);
    Dist d(a, b);

    URBG rng(12345); // fixed seed for repeatability of the *test* (not asserting distribution shape)
    sampleAndAssertInRange(d, rng, a, b);
}

// --- Boundary: degenerate interval a == b should always produce that value
TYPED_TEST(UniformFPDistTyped_1058, DegenerateIntervalAlwaysReturnsAkaB_1058) {
    using Float = typename TestFixture::Float;
    using Dist  = typename TestFixture::Dist;
    using URBG  = typename TestFixture::URBG;

    const Float c = static_cast<Float>(1.0);
    Dist d(c, c);

    URBG rng(999u);
    for (int i = 0; i < 100; ++i) {
        auto v = d(rng);
        EXPECT_EQ(v, c);
    }
}

// --- Boundary: very small positive interval near zero
TYPED_TEST(UniformFPDistTyped_1058, TinyPositiveRangeNearZero_1058) {
    using Float = typename TestFixture::Float;
    using Dist  = typename TestFixture::Dist;
    using URBG  = typename TestFixture::URBG;

    const Float a = static_cast<Float>(0);
    const Float b = std::numeric_limits<Float>::epsilon(); // smallest step above 1 scaled for type
    Dist d(a, b);

    URBG rng(2024u);
    sampleAndAssertInRange(d, rng, a, b, /*samples=*/1000);
}

// --- Boundary: negative-only interval
TYPED_TEST(UniformFPDistTyped_1058, NegativeOnlyInterval_1058) {
    using Float = typename TestFixture::Float;
    using Dist  = typename TestFixture::Dist;
    using URBG  = typename TestFixture::URBG;

    const Float a = static_cast<Float>(-7.0);
    const Float b = static_cast<Float>(-2.0);
    Dist d(a, b);

    URBG rng(4242u);
    sampleAndAssertInRange(d, rng, a, b);
}

// --- Boundary: interval crossing zero
TYPED_TEST(UniformFPDistTyped_1058, IntervalCrossingZero_1058) {
    using Float = typename TestFixture::Float;
    using Dist  = typename TestFixture::Dist;
    using URBG  = typename TestFixture::URBG;

    const Float a = static_cast<Float>(-0.25);
    const Float b = static_cast<Float>(0.75);
    Dist d(a, b);

    URBG rng(7u);
    sampleAndAssertInRange(d, rng, a, b);
}

// --- Exceptional (observable): constructing with a > b should trigger the assert in debug builds
#if !defined(NDEBUG) && GTEST_HAS_DEATH_TEST
TEST(UniformFPDist_Death_1058, AssertsWhenAIsGreaterThanB_1058) {
    using Float = double;
    using Dist  = uniform_floating_point_distribution<Float>;

    // The code asserts(a <= b). In a debug build, this should terminate.
    EXPECT_DEATH({ Dist d(static_cast<Float>(2.0), static_cast<Float>(1.0)); (void)d; }, "");
}
#endif
