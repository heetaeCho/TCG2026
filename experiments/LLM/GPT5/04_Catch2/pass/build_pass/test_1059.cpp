// File: tests/random_floating_generator_tests_1059.cpp

#include <gtest/gtest.h>

// Include the header under test (adjust include path if your build differs)
#include "Catch2/src/catch2/generators/catch_generators_random.hpp"

using Catch::Generators::RandomFloatingGenerator;

// Helper to check value within [lo, hi] (inclusive on both ends for safety as a black box)
template <typename T>
static void ExpectWithinInclusiveRange(T value, T lo, T hi) {
    if (lo > hi) std::swap(lo, hi);
    EXPECT_LE(lo, value);
    EXPECT_LE(value, hi);
}

// --- Tests for float/double/long double are separate to keep types explicit ---

// Normal operation: constructor advances once; get() is immediately usable and in range
TEST(RandomFloatingGeneratorTest_1059, ConstructsAdvancesOnce_InRange_Float_1059) {
    const float a = 0.0f, b = 1.0f;
    const std::uint32_t seed = 123u;

    RandomFloatingGenerator<float> gen(a, b, seed);
    float first = gen.get();

    ExpectWithinInclusiveRange<float>(first, a, b);
}

// Determinism with same seed (float)
TEST(RandomFloatingGeneratorTest_1059, DeterministicWithSameSeed_Float_1059) {
    const float a = -2.0f, b = 3.5f;
    const std::uint32_t seed = 42u;

    RandomFloatingGenerator<float> g1(a, b, seed);
    RandomFloatingGenerator<float> g2(a, b, seed);

    // Compare first N values
    constexpr int N = 10;
    for (int i = 0; i < N; ++i) {
        // Use EXPECT_FLOAT_EQ for deterministic bitwise-identical sequences
        EXPECT_FLOAT_EQ(g1.get(), g2.get());
        // Advance both; next() should succeed per observable behavior contract
        EXPECT_TRUE(g1.next());
        EXPECT_TRUE(g2.next());
    }
}

// Different seeds should produce different sequence at some point (float)
TEST(RandomFloatingGeneratorTest_1059, DifferentSeedsYieldDifferentSequence_Float_1059) {
    const float a = -10.0f, b = 10.0f;

    RandomFloatingGenerator<float> g1(a, b, 1u);
    RandomFloatingGenerator<float> g2(a, b, 2u);

    // Check first K values; extremely unlikely all K are equal
    constexpr int K = 20;
    bool differs = false;
    for (int i = 0; i < K; ++i) {
        if (g1.get() != g2.get()) { // direct compare is fine for inequality
            differs = true;
            break;
        }
        ASSERT_TRUE(g1.next());
        ASSERT_TRUE(g2.next());
    }
    EXPECT_TRUE(differs) << "Sequences with different seeds matched for first " << K << " draws";
}

// Range respected for negative-only interval (double)
TEST(RandomFloatingGeneratorTest_1059, RangeRespected_NegativeInterval_Double_1059) {
    const double a = -5.0, b = -2.0;
    const std::uint32_t seed = 777u;

    RandomFloatingGenerator<double> gen(a, b, seed);
    // Sample a few values to be safe
    constexpr int N = 8;
    for (int i = 0; i < N; ++i) {
        ExpectWithinInclusiveRange<double>(gen.get(), a, b);
        EXPECT_TRUE(gen.next());
    }
}

// Degenerate interval a == b should always yield that value (double)
TEST(RandomFloatingGeneratorTest_1059, DegenerateIntervalAlwaysSame_Double_1059) {
    const double a = 3.14159265358979323846;
    const std::uint32_t seed = 2025u;

    RandomFloatingGenerator<double> gen(a, a, seed);
    constexpr int N = 6;
    for (int i = 0; i < N; ++i) {
        EXPECT_DOUBLE_EQ(gen.get(), a);
        EXPECT_TRUE(gen.next());
    }
}

// next() continues to return true across many iterations (float)
TEST(RandomFloatingGeneratorTest_1059, NextAlwaysReturnsTrue_ForManySteps_Float_1059) {
    const float a = 1.0f, b = 2.0f;
    RandomFloatingGenerator<float> gen(a, b, 999u);

    constexpr int STEPS = 1000;
    for (int i = 0; i < STEPS; ++i) {
        // Just ensure it stays within range and next keeps succeeding
        ExpectWithinInclusiveRange<float>(gen.get(), a, b);
        EXPECT_TRUE(gen.next());
    }
}

// Long double specialization: determinism + range checks
TEST(RandomFloatingGeneratorTest_1059, LongDouble_DeterminismAndRange_1059) {
    const long double a = -0.25L, b = 0.75L;
    const std::uint32_t seed = 13579u;

    RandomFloatingGenerator<long double> g1(a, b, seed);
    RandomFloatingGenerator<long double> g2(a, b, seed);

    constexpr int N = 12;
    for (int i = 0; i < N; ++i) {
        long double v1 = g1.get();
        long double v2 = g2.get();

        // Range check
        ExpectWithinInclusiveRange<long double>(v1, a, b);
        ExpectWithinInclusiveRange<long double>(v2, a, b);

        // Determinism check — use EXPECT_EQ for exact long double equality where supported,
        // fall back to EXPECT_NEAR-style tolerance if your toolchain needs it.
        EXPECT_EQ(v1, v2);

        EXPECT_TRUE(g1.next());
        EXPECT_TRUE(g2.next());
    }
}
