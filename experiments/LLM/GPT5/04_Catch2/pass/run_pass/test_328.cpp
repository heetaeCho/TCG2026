// File: simple_pcg32_tests_328.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_random_number_generator.hpp"

using Catch::SimplePcg32;

class SimplePcg32Test_328 : public ::testing::Test {};

// --- Basic range properties ---

TEST_F(SimplePcg32Test_328, MinIsZero_328) {
    // From the provided partial code: min() == 0
    EXPECT_EQ(SimplePcg32::min(), 0);
}

TEST_F(SimplePcg32Test_328, MinLessOrEqualMax_328) {
    EXPECT_LE(SimplePcg32::min(), SimplePcg32::max());
}

TEST_F(SimplePcg32Test_328, ValuesWithinRange_328) {
    SimplePcg32 rng; // default constructible
    // Check a handful of draws lie within [min, max]
    for (int i = 0; i < 10; ++i) {
        auto v = rng();
        EXPECT_GE(v, SimplePcg32::min());
        EXPECT_LE(v, SimplePcg32::max());
    }
}

// --- Determinism & seeding behavior ---

TEST_F(SimplePcg32Test_328, DefaultConstructorsProduceSameSequence_328) {
    SimplePcg32 a;
    SimplePcg32 b;

    // Sequences from two default-constructed generators should match
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(a(), b());
    }
}

TEST_F(SimplePcg32Test_328, SameSeedSameSequence_328) {
    SimplePcg32 a;
    SimplePcg32 b;

    // Seed both with the same value; sequences should match
    a.seed(123456u);
    b.seed(123456u);

    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(a(), b());
    }
}

TEST_F(SimplePcg32Test_328, SeedResetsSequence_328) {
    SimplePcg32 rng;

    // Record first few outputs with a given seed
    rng.seed(42u);
    auto v0 = rng();
    auto v1 = rng();
    auto v2 = rng();

    // Reseed with the same value; sequence should restart
    rng.seed(42u);
    EXPECT_EQ(rng(), v0);
    EXPECT_EQ(rng(), v1);
    EXPECT_EQ(rng(), v2);
}

// --- Equality / inequality reflect state ---

TEST_F(SimplePcg32Test_328, EqualityReflectsSameState_328) {
    SimplePcg32 a;
    SimplePcg32 b;

    // Immediately after construction, states should be equal
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);

    // Advance one of them; states should diverge
    (void)a();
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST_F(SimplePcg32Test_328, EqualityAfterAlignedAdvances_328) {
    SimplePcg32 a;
    SimplePcg32 b;

    // Advance both by the same number of steps; states should remain equal
    for (int i = 0; i < 7; ++i) {
        (void)a();
        (void)b();
    }
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

// --- Discard behavior (observable alignment) ---

TEST_F(SimplePcg32Test_328, DiscardZeroNoChange_328) {
    SimplePcg32 a;
    SimplePcg32 b;

    // Discarding zero should not change the state relative to an untouched copy
    a.discard(0);
    EXPECT_TRUE(a == b);
    EXPECT_EQ(a(), b());
}

TEST_F(SimplePcg32Test_328, DiscardMatchesManualAdvances_328) {
    SimplePcg32 a;
    SimplePcg32 b;

    // Move 'a' forward by discarding N numbers
    constexpr uint64_t N = 10;
    a.discard(N);

    // Manually advance 'b' N times
    for (uint64_t i = 0; i < N; ++i) {
        (void)b();
    }

    // Their next outputs should match
    EXPECT_EQ(a(), b());
    // And their states should now be equal as well
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}
