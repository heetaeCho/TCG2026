#include <gtest/gtest.h>
#include <cstdint>
#include "catch2/internal/catch_random_number_generator.hpp"

using Catch::SimplePcg32;

// Test default construction - two default-constructed generators should be equal
TEST(SimplePcg32Test_642, DefaultConstructedAreEqual_642) {
    SimplePcg32 rng1;
    SimplePcg32 rng2;
    EXPECT_EQ(rng1, rng2);
}

// Test explicit seed construction - same seed should produce equal generators
TEST(SimplePcg32Test_642, SameSeedProducesEqualGenerators_642) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);
    EXPECT_EQ(rng1, rng2);
}

// Test explicit seed construction - different seeds should produce unequal generators
TEST(SimplePcg32Test_642, DifferentSeedsProduceUnequalGenerators_642) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(43);
    EXPECT_NE(rng1, rng2);
}

// Test that operator() returns a value and advances state
TEST(SimplePcg32Test_642, OperatorCallAdvancesState_642) {
    SimplePcg32 rng1(100);
    SimplePcg32 rng2(100);
    EXPECT_EQ(rng1, rng2);
    rng1();
    EXPECT_NE(rng1, rng2);
}

// Test that operator() produces same sequence for same seed
TEST(SimplePcg32Test_642, SameSeedSameSequence_642) {
    SimplePcg32 rng1(12345);
    SimplePcg32 rng2(12345);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

// Test that different seeds produce different sequences
TEST(SimplePcg32Test_642, DifferentSeedDifferentSequence_642) {
    SimplePcg32 rng1(12345);
    SimplePcg32 rng2(54321);
    // It's statistically extremely unlikely all 100 values match
    bool any_different = false;
    for (int i = 0; i < 100; ++i) {
        if (rng1() != rng2()) {
            any_different = true;
            break;
        }
    }
    EXPECT_TRUE(any_different);
}

// Test seed() method resets the generator state
TEST(SimplePcg32Test_642, SeedResetsState_642) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);
    // Advance rng1
    rng1();
    rng1();
    EXPECT_NE(rng1, rng2);
    // Re-seed rng1 with original seed
    rng1.seed(42);
    EXPECT_EQ(rng1, rng2);
}

// Test seed() with a different seed
TEST(SimplePcg32Test_642, SeedWithDifferentValue_642) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(99);
    rng1.seed(99);
    EXPECT_EQ(rng1, rng2);
}

// Test discard(1) is equivalent to calling operator() once
TEST(SimplePcg32Test_642, DiscardOneEqualsOneCall_642) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);
    rng1();
    rng2.discard(1);
    EXPECT_EQ(rng1, rng2);
}

// Test discard(n) is equivalent to calling operator() n times
TEST(SimplePcg32Test_642, DiscardNEqualsNCalls_642) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);
    const uint64_t n = 50;
    for (uint64_t i = 0; i < n; ++i) {
        rng1();
    }
    rng2.discard(n);
    EXPECT_EQ(rng1, rng2);
}

// Test discard(0) does not change state
TEST(SimplePcg32Test_642, DiscardZeroNoChange_642) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);
    rng1.discard(0);
    EXPECT_EQ(rng1, rng2);
}

// Test min() returns 0
TEST(SimplePcg32Test_642, MinReturnsZero_642) {
    EXPECT_EQ((SimplePcg32::min)(), 0u);
}

// Test max() returns max uint32_t
TEST(SimplePcg32Test_642, MaxReturnsMaxUint32_642) {
    EXPECT_EQ((SimplePcg32::max)(), std::numeric_limits<std::uint32_t>::max());
}

// Test that operator() returns values within [min(), max()]
TEST(SimplePcg32Test_642, OutputInRange_642) {
    SimplePcg32 rng(777);
    for (int i = 0; i < 1000; ++i) {
        auto val = rng();
        EXPECT_GE(val, (SimplePcg32::min)());
        EXPECT_LE(val, (SimplePcg32::max)());
    }
}

// Test inequality operator
TEST(SimplePcg32Test_642, InequalityOperator_642) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);
    EXPECT_FALSE(rng1 != rng2);
    rng1();
    EXPECT_TRUE(rng1 != rng2);
}

// Test construction with seed 0
TEST(SimplePcg32Test_642, SeedZero_642) {
    SimplePcg32 rng1(0);
    SimplePcg32 rng2(0);
    EXPECT_EQ(rng1, rng2);
    // Should still produce output
    auto val = rng1();
    (void)val;  // Just ensure it doesn't crash
}

// Test construction with max seed value
TEST(SimplePcg32Test_642, MaxSeedValue_642) {
    SimplePcg32 rng1(std::numeric_limits<SimplePcg32::result_type>::max());
    SimplePcg32 rng2(std::numeric_limits<SimplePcg32::result_type>::max());
    EXPECT_EQ(rng1, rng2);
    EXPECT_EQ(rng1(), rng2());
}

// Test default constructor vs explicit default seed
TEST(SimplePcg32Test_642, DefaultConstructorUsesExpectedSeed_642) {
    SimplePcg32 rng_default;
    SimplePcg32 rng_explicit(0xed743cc4U);
    EXPECT_EQ(rng_default, rng_explicit);
}

// Test large discard
TEST(SimplePcg32Test_642, LargeDiscard_642) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);
    const uint64_t n = 10000;
    for (uint64_t i = 0; i < n; ++i) {
        rng1();
    }
    rng2.discard(n);
    EXPECT_EQ(rng1, rng2);
}

// Test that repeated seeding works correctly
TEST(SimplePcg32Test_642, RepeatedSeeding_642) {
    SimplePcg32 rng(1);
    rng.seed(2);
    rng.seed(3);
    SimplePcg32 rng_fresh(3);
    EXPECT_EQ(rng, rng_fresh);
}

// Test that operator() produces non-constant output
TEST(SimplePcg32Test_642, OutputIsNotConstant_642) {
    SimplePcg32 rng(42);
    auto first = rng();
    bool found_different = false;
    for (int i = 0; i < 100; ++i) {
        if (rng() != first) {
            found_different = true;
            break;
        }
    }
    EXPECT_TRUE(found_different);
}
