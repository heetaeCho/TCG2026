// File: tests/simplepcg32_tests_1096.cpp
#include <gtest/gtest.h>
#include <cstdint>
#include <vector>

// Include the RNG's public interface
#include "catch2/internal/catch_random_number_generator.hpp"

using Catch::SimplePcg32;

class SimplePcg32Test_1096 : public ::testing::Test {};

// [Normal operation] Seeding determinism: same seed -> identical sequence
TEST_F(SimplePcg32Test_1096, SameSeed_ProducesSameSequence_1096) {
    const SimplePcg32::result_type seed = static_cast<SimplePcg32::result_type>(12345u);
    SimplePcg32 a(seed);
    SimplePcg32 b(seed);

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(a(), b()) << "Sequences diverged at step " << i;
    }
}

// [Normal operation + boundary] Default ctor delegates to fixed seed -> must match explicit seed
TEST_F(SimplePcg32Test_1096, DefaultCtor_EqualsKnownSeedCtor_1096) {
    // Based on interface comment: default constructs with 0xed743cc4U
    const SimplePcg32::result_type defaultSeed = static_cast<SimplePcg32::result_type>(0xed743cc4U);

    SimplePcg32 def;          // default-constructed
    SimplePcg32 explicitSeed(defaultSeed);

    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(def(), explicitSeed()) << "Mismatch at draw " << i;
    }
}

// [Normal operation] discard(n) should skip ahead by n draws
TEST_F(SimplePcg32Test_1096, Discard_SkipsSameAsCalling_1096) {
    const SimplePcg32::result_type seed = static_cast<SimplePcg32::result_type>(987654321u);
    SimplePcg32 x(seed);
    SimplePcg32 y(seed);

    const std::uint64_t n = 7;
    // Advance y by calling operator() n times
    for (std::uint64_t i = 0; i < n; ++i) (void)y();

    // Discard n draws on x, then next values should match step-for-step
    x.discard(n);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(x(), y()) << "Mismatch after discard alignment at step " << i;
    }
}

// [Boundary] discard(0) should be a no-op
TEST_F(SimplePcg32Test_1096, DiscardZero_NoEffect_1096) {
    const SimplePcg32::result_type seed = static_cast<SimplePcg32::result_type>(42u);
    SimplePcg32 a(seed);
    SimplePcg32 b(seed);

    a.discard(0);
    for (int i = 0; i < 6; ++i) {
        EXPECT_EQ(a(), b());
    }
}

// [Boundary] Large discard still behaves as skip-ahead (observable alignment)
TEST_F(SimplePcg32Test_1096, DiscardLarge_SkipsAhead_1096) {
    const SimplePcg32::result_type seed = static_cast<SimplePcg32::result_type>(2024u);
    SimplePcg32 x(seed);
    SimplePcg32 y(seed);

    const std::uint64_t n = 1000;
    for (std::uint64_t i = 0; i < n; ++i) (void)y();
    x.discard(n);

    // After aligning, next few draws should match
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(x(), y());
    }
}

// [Normal operation] min/max properties and output range
TEST_F(SimplePcg32Test_1096, MinMax_RangeAndOrdering_1096) {
    EXPECT_LT(SimplePcg32::min(), SimplePcg32::max());

    SimplePcg32 rng; // default seed
    for (int i = 0; i < 20; ++i) {
        auto v = rng();
        EXPECT_LE(SimplePcg32::min(), v);
        EXPECT_LE(v, SimplePcg32::max());
    }
}

// [External interaction via public comparison ops] Equality/inequality reflect state advancement
TEST_F(SimplePcg32Test_1096, EqualityReflectsState_1096) {
    const SimplePcg32::result_type seed = static_cast<SimplePcg32::result_type>(13579u);
    SimplePcg32 a(seed);
    SimplePcg32 b(seed);

    // Initially equal
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);

    // Advance one -> not equal
    (void)a();
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);

    // Advance the other by one -> equal again
    (void)b();
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

// [Exceptional / edge (observable)] Different seeds should (very likely) yield different first draw
// Note: We only check first draw to avoid making assumptions beyond interface.
TEST_F(SimplePcg32Test_1096, DifferentSeeds_YieldDifferentFirstValue_1096) {
    SimplePcg32 a(static_cast<SimplePcg32::result_type>(1u));
    SimplePcg32 b(static_cast<SimplePcg32::result_type>(2u));

    auto v1 = a();
    auto v2 = b();
    // It is extremely unlikely they'd be equal; if equal, test will highlight a surprising behavior.
    EXPECT_NE(v1, v2);
}
