// File: test_uniform_integer_distribution_336.cpp
#include <gtest/gtest.h>
#include <random>
#include <limits>

// Adjust the include path to match your project layout.
#include "catch2/internal/catch_uniform_integer_distribution.hpp"

using Catch::uniform_integer_distribution;

// A small helper to generate many samples and check they are all in [lo, hi].
template <typename Int, typename Gen>
static void ExpectAllInRange(uniform_integer_distribution<Int>& dist,
                             Gen& gen, Int lo, Int hi, int iters = 20000) {
    for (int i = 0; i < iters; ++i) {
        Int v = dist(gen);
        ASSERT_LE(lo, v);
        ASSERT_LE(v, hi);
    }
}

class UniformIntDistTest_336 : public ::testing::Test {};

TEST_F(UniformIntDistTest_336, EqualBoundsAlwaysReturnsA_336) {
    std::mt19937 gen(123u);
    uniform_integer_distribution<int> dist(5, 5);

    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(5, dist(gen));
    }
}

TEST_F(UniformIntDistTest_336, RangeIsInclusive_PositiveBounds_336) {
    std::mt19937 gen(42u);
    const int a = 2, b = 5;
    uniform_integer_distribution<int> dist(a, b);

    bool seen_lo = false, seen_hi = false;
    for (int i = 0; i < 20000; ++i) {
        int v = dist(gen);
        ASSERT_LE(a, v);
        ASSERT_LE(v, b);
        if (v == a) seen_lo = true;
        if (v == b) seen_hi = true;
        if (seen_lo && seen_hi) break;
    }
    EXPECT_TRUE(seen_lo);
    EXPECT_TRUE(seen_hi);
}

TEST_F(UniformIntDistTest_336, RangeIsInclusive_NegativeToPositive_336) {
    std::mt19937 gen(7u);
    const int a = -3, b = 2;
    uniform_integer_distribution<int> dist(a, b);

    bool seen_lo = false, seen_hi = false;
    for (int i = 0; i < 25000; ++i) {
        int v = dist(gen);
        ASSERT_LE(a, v);
        ASSERT_LE(v, b);
        if (v == a) seen_lo = true;
        if (v == b) seen_hi = true;
        if (seen_lo && seen_hi) break;
    }
    EXPECT_TRUE(seen_lo);
    EXPECT_TRUE(seen_hi);
}

TEST_F(UniformIntDistTest_336, DeterminismGivenSameSeed_336) {
    std::mt19937 g1(123456u), g2(123456u);
    uniform_integer_distribution<int> d1(0, 100);
    uniform_integer_distribution<int> d2(0, 100);

    // Same generator state + same distribution ⇒ identical sequence
    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(d1(g1), d2(g2));
    }
}

TEST_F(UniformIntDistTest_336, WorksWithDifferentStandardGenerators_336) {
    std::minstd_rand gen1(98765u);
    std::mt19937_64 gen2(555u);

    uniform_integer_distribution<int> d1(-10, 10);
    uniform_integer_distribution<int> d2(-10, 10);

    ExpectAllInRange(d1, gen1, -10, 10, 5000);
    ExpectAllInRange(d2, gen2, -10, 10, 5000);
}

TEST_F(UniformIntDistTest_336, LargeFullIntRangeStaysInBounds_336) {
    std::mt19937 gen(314159u);
    using I = int;
    uniform_integer_distribution<I> dist(std::numeric_limits<I>::min(),
                                         std::numeric_limits<I>::max());

    // Just sanity: results are within the declared (very large) bounds
    for (int i = 0; i < 5000; ++i) {
        I v = dist(gen);
        ASSERT_LE(std::numeric_limits<I>::min(), v);
        ASSERT_LE(v, std::numeric_limits<I>::max());
    }
}

TEST_F(UniformIntDistTest_336, AccessorsReturnOriginalBounds_336) {
    // If the interface exposes a() and b(), they should reflect construction bounds.
    std::mt19937 gen(1u);
    (void)gen; // not used here, but keeps symmetry with other tests

    const int a = -100, b = 123;
    uniform_integer_distribution<int> dist(a, b);

    // These accessors are declared in the provided interface.
    EXPECT_EQ(a, dist.a());
    EXPECT_EQ(b, dist.b());
}

TEST_F(UniformIntDistTest_336, ZeroWidthRangeWithOtherGen_336) {
    std::minstd_rand gen(2024u);
    uniform_integer_distribution<long long> dist(777LL, 777LL);

    for (int i = 0; i < 128; ++i) {
        EXPECT_EQ(777LL, dist(gen));
    }
}
