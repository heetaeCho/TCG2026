#include <gtest/gtest.h>
#include <cstdint>
#include <set>
#include <vector>

// Include the header for SimplePcg32
#include "catch2/internal/catch_random_number_generator.hpp"

using Catch::SimplePcg32;

// Test that default constructor creates a valid generator
TEST(SimplePcg32Test_641, DefaultConstructorProducesValues_641) {
    SimplePcg32 rng;
    auto val = rng();
    // Just verify it returns without crashing and produces a value
    (void)val;
}

// Test that seeded constructor creates a valid generator
TEST(SimplePcg32Test_641, SeededConstructorProducesValues_641) {
    SimplePcg32 rng(42);
    auto val = rng();
    (void)val;
}

// Test determinism: same seed produces same sequence
TEST(SimplePcg32Test_641, SameSeedProducesSameSequence_641) {
    SimplePcg32 rng1(12345);
    SimplePcg32 rng2(12345);

    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(rng1(), rng2()) << "Mismatch at iteration " << i;
    }
}

// Test that different seeds produce different sequences
TEST(SimplePcg32Test_641, DifferentSeedsProduceDifferentSequences_641) {
    SimplePcg32 rng1(1);
    SimplePcg32 rng2(2);

    bool all_same = true;
    for (int i = 0; i < 100; ++i) {
        if (rng1() != rng2()) {
            all_same = false;
            break;
        }
    }
    EXPECT_FALSE(all_same);
}

// Test equality operator: same seed means equal state
TEST(SimplePcg32Test_641, EqualityOperatorSameSeed_641) {
    SimplePcg32 rng1(100);
    SimplePcg32 rng2(100);
    EXPECT_TRUE(rng1 == rng2);
    EXPECT_FALSE(rng1 != rng2);
}

// Test equality operator: different seeds means not equal
TEST(SimplePcg32Test_641, EqualityOperatorDifferentSeed_641) {
    SimplePcg32 rng1(100);
    SimplePcg32 rng2(200);
    EXPECT_FALSE(rng1 == rng2);
    EXPECT_TRUE(rng1 != rng2);
}

// Test that calling operator() advances state (generators no longer equal)
TEST(SimplePcg32Test_641, OperatorAdvancesState_641) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);
    EXPECT_TRUE(rng1 == rng2);

    rng1();
    EXPECT_FALSE(rng1 == rng2);
    EXPECT_TRUE(rng1 != rng2);
}

// Test seed method resets state
TEST(SimplePcg32Test_641, SeedResetsState_641) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);

    // Advance rng1
    rng1();
    rng1();
    rng1();

    // Reseed rng1 with same seed
    rng1.seed(42);

    // They should be equal again
    EXPECT_TRUE(rng1 == rng2);

    // And produce the same sequence
    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

// Test discard is equivalent to calling operator() N times
TEST(SimplePcg32Test_641, DiscardEquivalentToCallingN_641) {
    SimplePcg32 rng1(77);
    SimplePcg32 rng2(77);

    uint64_t skip = 10;
    for (uint64_t i = 0; i < skip; ++i) {
        rng1();
    }
    rng2.discard(skip);

    EXPECT_TRUE(rng1 == rng2);
    EXPECT_EQ(rng1(), rng2());
}

// Test discard with zero does nothing
TEST(SimplePcg32Test_641, DiscardZero_641) {
    SimplePcg32 rng1(55);
    SimplePcg32 rng2(55);

    rng2.discard(0);
    EXPECT_TRUE(rng1 == rng2);
}

// Test discard with 1 is equivalent to one call
TEST(SimplePcg32Test_641, DiscardOne_641) {
    SimplePcg32 rng1(55);
    SimplePcg32 rng2(55);

    rng1();
    rng2.discard(1);
    EXPECT_TRUE(rng1 == rng2);
}

// Test min and max static methods
TEST(SimplePcg32Test_641, MinMaxValues_641) {
    auto min_val = (SimplePcg32::min)();
    auto max_val = (SimplePcg32::max)();

    EXPECT_EQ(min_val, std::uint32_t(0));
    EXPECT_EQ(max_val, std::numeric_limits<std::uint32_t>::max());
    EXPECT_LT(min_val, max_val);
}

// Test that output values fall within [min, max] range
TEST(SimplePcg32Test_641, OutputWithinRange_641) {
    SimplePcg32 rng(999);
    auto min_val = (SimplePcg32::min)();
    auto max_val = (SimplePcg32::max)();

    for (int i = 0; i < 1000; ++i) {
        auto val = rng();
        EXPECT_GE(val, min_val);
        EXPECT_LE(val, max_val);
    }
}

// Test that the generator produces varied output (not all the same value)
TEST(SimplePcg32Test_641, ProducesVariedOutput_641) {
    SimplePcg32 rng(0);
    std::set<SimplePcg32::result_type> values;
    for (int i = 0; i < 100; ++i) {
        values.insert(rng());
    }
    // With 100 draws, we should have many distinct values
    EXPECT_GT(values.size(), 90u);
}

// Test default constructor vs explicit default seed constructor
TEST(SimplePcg32Test_641, DefaultConstructorUsesDefaultSeed_641) {
    SimplePcg32 rng_default;
    SimplePcg32 rng_explicit(0xed743cc4U);

    // Both should produce the same sequence since the default seed is 0xed743cc4U
    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(rng_default(), rng_explicit()) << "Mismatch at iteration " << i;
    }
}

// Test seed with zero
TEST(SimplePcg32Test_641, SeedWithZero_641) {
    SimplePcg32 rng1(0);
    SimplePcg32 rng2;
    rng2.seed(0);

    EXPECT_TRUE(rng1 == rng2);
    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

// Test seed with max uint32 value
TEST(SimplePcg32Test_641, SeedWithMaxValue_641) {
    SimplePcg32 rng(std::numeric_limits<SimplePcg32::result_type>::max());
    // Should still produce valid output
    auto val = rng();
    (void)val;
}

// Test large discard
TEST(SimplePcg32Test_641, LargeDiscard_641) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);

    uint64_t skip = 1000;
    for (uint64_t i = 0; i < skip; ++i) {
        rng1();
    }
    rng2.discard(skip);

    EXPECT_TRUE(rng1 == rng2);
}

// Test that re-seeding with a different seed changes behavior
TEST(SimplePcg32Test_641, ReseedWithDifferentSeed_641) {
    SimplePcg32 rng(42);
    auto val1 = rng();

    rng.seed(42);
    auto val2 = rng();

    EXPECT_EQ(val1, val2);

    rng.seed(43);
    auto val3 = rng();

    // Different seed should likely produce different first value
    // (not guaranteed but extremely likely for PCG)
    EXPECT_NE(val1, val3);
}

// Test multiple sequential calls produce a sequence
TEST(SimplePcg32Test_641, SequentialCallsProduceSequence_641) {
    SimplePcg32 rng(7);
    std::vector<SimplePcg32::result_type> sequence;
    for (int i = 0; i < 10; ++i) {
        sequence.push_back(rng());
    }

    // Verify reproducibility
    SimplePcg32 rng2(7);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(sequence[i], rng2());
    }
}

// Test inequality after discard
TEST(SimplePcg32Test_641, InequalityAfterDiscard_641) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);

    rng1.discard(5);
    EXPECT_NE(rng1, rng2);
}
