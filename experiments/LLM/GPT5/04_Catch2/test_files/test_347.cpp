// File: random_floating_generator_test_347.cpp

#include <gtest/gtest.h>
#include "catch2/generators/catch_generators_random.hpp"

namespace {
using Catch::Generators::RandomFloatingGenerator;

// Helper: check N samples are within [a, b], advancing via next() each time.
template <typename Float>
void ExpectSamplesWithinBounds(RandomFloatingGenerator<Float>& gen,
                               Float a, Float b, int nSamples) {
    for (int i = 0; i < nSamples; ++i) {
        // Advance and verify next() reports success (observable behavior)
        EXPECT_TRUE(gen.next());
        const Float& v = gen.get();
        EXPECT_LE(v, b);
        EXPECT_GE(v, a);
    }
}

} // namespace

// ---- Tests for double ----

TEST(RandomFloatingGeneratorTest_347, NextReturnsTrue_Double_347) {
    RandomFloatingGenerator<double> gen(/*a=*/-5.0, /*b=*/5.0, /*seed=*/123u);
    // We don't assume anything about initial state before first next().
    EXPECT_TRUE(gen.next());
    (void)gen.get(); // Access current value to ensure the interface works.
}

TEST(RandomFloatingGeneratorTest_347, ValuesWithinBounds_Double_347) {
    const double a = -10.0, b = 10.0;
    RandomFloatingGenerator<double> gen(a, b, /*seed=*/42u);
    ExpectSamplesWithinBounds(gen, a, b, /*nSamples=*/100);
}

TEST(RandomFloatingGeneratorTest_347, DeterministicSameSeed_Double_347) {
    const double a = 0.25, b = 0.75;
    constexpr std::uint32_t seed = 20240828u;

    RandomFloatingGenerator<double> g1(a, b, seed);
    RandomFloatingGenerator<double> g2(a, b, seed);

    // Compare a sequence of values; only rely on public next()/get().
    for (int i = 0; i < 50; ++i) {
        ASSERT_TRUE(g1.next());
        ASSERT_TRUE(g2.next());
        const double& v1 = g1.get();
        const double& v2 = g2.get();
        EXPECT_DOUBLE_EQ(v1, v2);
        EXPECT_GE(v1, a);
        EXPECT_LE(v1, b);
    }
}

// ---- Tests for long double specialization ----

TEST(RandomFloatingGeneratorTest_347, ValuesWithinBounds_LongDouble_347) {
    const long double a = -1.0L, b = 3.0L;
    RandomFloatingGenerator<long double> gen(a, b, /*seed=*/777u);
    // Use a modest sample size to validate observable range behavior.
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(gen.next());
        const long double& v = gen.get();
        EXPECT_LE(v, b);
        EXPECT_GE(v, a);
    }
}

TEST(RandomFloatingGeneratorTest_347, DeterministicSameSeed_LongDouble_347) {
    const long double a = 1.0L, b = 2.0L;
    constexpr std::uint32_t seed = 13579u;

    RandomFloatingGenerator<long double> g1(a, b, seed);
    RandomFloatingGenerator<long double> g2(a, b, seed);

    for (int i = 0; i < 50; ++i) {
        ASSERT_TRUE(g1.next());
        ASSERT_TRUE(g2.next());
        const long double& v1 = g1.get();
        const long double& v2 = g2.get();
        // Use EXPECT_EQ for long double (GoogleTest supports it).
        EXPECT_EQ(v1, v2);
        EXPECT_GE(v1, a);
        EXPECT_LE(v1, b);
    }
}
