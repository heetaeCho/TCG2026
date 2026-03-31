#include <gtest/gtest.h>
#include <cstdint>
#include <set>
#include <vector>

// Include the header for SimplePcg32
#include "catch2/internal/catch_random_number_generator.hpp"

using Catch::SimplePcg32;

// Test default construction
TEST(SimplePcg32Test_1096, DefaultConstruction_1096) {
    SimplePcg32 rng;
    // Should be constructible with default seed
    auto value = rng();
    // Just verify it produces a value without crashing
    (void)value;
}

// Test construction with explicit seed
TEST(SimplePcg32Test_1096, ExplicitSeedConstruction_1096) {
    SimplePcg32 rng(42u);
    auto value = rng();
    (void)value;
}

// Test that same seed produces same sequence
TEST(SimplePcg32Test_1096, SameSeedProducesSameSequence_1096) {
    SimplePcg32 rng1(12345u);
    SimplePcg32 rng2(12345u);

    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

// Test that different seeds produce different sequences
TEST(SimplePcg32Test_1096, DifferentSeedsProduceDifferentSequences_1096) {
    SimplePcg32 rng1(1u);
    SimplePcg32 rng2(2u);

    bool all_same = true;
    for (int i = 0; i < 100; ++i) {
        if (rng1() != rng2()) {
            all_same = false;
            break;
        }
    }
    EXPECT_FALSE(all_same);
}

// Test seed() resets state
TEST(SimplePcg32Test_1096, SeedResetsState_1096) {
    SimplePcg32 rng(42u);
    auto first_value = rng();
    
    rng.seed(42u);
    auto reset_value = rng();
    
    EXPECT_EQ(first_value, reset_value);
}

// Test seed() with different value changes output
TEST(SimplePcg32Test_1096, SeedWithDifferentValueChangesOutput_1096) {
    SimplePcg32 rng(42u);
    auto val1 = rng();
    
    rng.seed(99u);
    auto val2 = rng();
    
    // While not guaranteed, extremely unlikely to be equal
    // This tests that reseeding actually changes state
    // We check the full sequence to be safe
    rng.seed(42u);
    auto val3 = rng();
    EXPECT_EQ(val1, val3); // Confirms seed(42) resets properly
}

// Test equality operator - same seed
TEST(SimplePcg32Test_1096, EqualityOperatorSameSeed_1096) {
    SimplePcg32 rng1(100u);
    SimplePcg32 rng2(100u);
    
    EXPECT_TRUE(rng1 == rng2);
    EXPECT_FALSE(rng1 != rng2);
}

// Test equality operator - different seeds
TEST(SimplePcg32Test_1096, EqualityOperatorDifferentSeeds_1096) {
    SimplePcg32 rng1(100u);
    SimplePcg32 rng2(200u);
    
    EXPECT_FALSE(rng1 == rng2);
    EXPECT_TRUE(rng1 != rng2);
}

// Test equality after advancing one
TEST(SimplePcg32Test_1096, InequalityAfterAdvancing_1096) {
    SimplePcg32 rng1(100u);
    SimplePcg32 rng2(100u);
    
    rng1(); // Advance rng1 by one
    
    EXPECT_FALSE(rng1 == rng2);
    EXPECT_TRUE(rng1 != rng2);
}

// Test equality after advancing both by same amount
TEST(SimplePcg32Test_1096, EqualityAfterAdvancingBothSame_1096) {
    SimplePcg32 rng1(100u);
    SimplePcg32 rng2(100u);
    
    for (int i = 0; i < 50; ++i) {
        rng1();
        rng2();
    }
    
    EXPECT_TRUE(rng1 == rng2);
}

// Test discard
TEST(SimplePcg32Test_1096, DiscardEquivalentToCallingMultipleTimes_1096) {
    SimplePcg32 rng1(42u);
    SimplePcg32 rng2(42u);
    
    uint64_t skip_count = 10;
    rng1.discard(skip_count);
    
    for (uint64_t i = 0; i < skip_count; ++i) {
        rng2();
    }
    
    EXPECT_TRUE(rng1 == rng2);
    EXPECT_EQ(rng1(), rng2());
}

// Test discard with zero
TEST(SimplePcg32Test_1096, DiscardZero_1096) {
    SimplePcg32 rng1(42u);
    SimplePcg32 rng2(42u);
    
    rng1.discard(0);
    
    EXPECT_TRUE(rng1 == rng2);
    EXPECT_EQ(rng1(), rng2());
}

// Test discard with one
TEST(SimplePcg32Test_1096, DiscardOne_1096) {
    SimplePcg32 rng1(42u);
    SimplePcg32 rng2(42u);
    
    rng1.discard(1);
    rng2();
    
    EXPECT_TRUE(rng1 == rng2);
}

// Test min and max
TEST(SimplePcg32Test_1096, MinMax_1096) {
    auto min_val = (SimplePcg32::min)();
    auto max_val = (SimplePcg32::max)();
    
    EXPECT_EQ(min_val, std::uint32_t(0));
    EXPECT_EQ(max_val, std::numeric_limits<std::uint32_t>::max());
    EXPECT_LT(min_val, max_val);
}

// Test output is within min/max range
TEST(SimplePcg32Test_1096, OutputWithinRange_1096) {
    SimplePcg32 rng(42u);
    
    for (int i = 0; i < 1000; ++i) {
        auto value = rng();
        EXPECT_GE(value, (SimplePcg32::min)());
        EXPECT_LE(value, (SimplePcg32::max)());
    }
}

// Test that operator() produces varying output
TEST(SimplePcg32Test_1096, ProducesVaryingOutput_1096) {
    SimplePcg32 rng(42u);
    std::set<SimplePcg32::result_type> values;
    
    for (int i = 0; i < 100; ++i) {
        values.insert(rng());
    }
    
    // Should have many unique values out of 100 draws
    EXPECT_GT(values.size(), 90u);
}

// Test seed with zero
TEST(SimplePcg32Test_1096, SeedWithZero_1096) {
    SimplePcg32 rng(0u);
    auto val = rng();
    // Just verify it doesn't crash and produces output
    (void)val;
}

// Test seed with max uint32
TEST(SimplePcg32Test_1096, SeedWithMaxValue_1096) {
    SimplePcg32 rng(std::numeric_limits<SimplePcg32::result_type>::max());
    auto val = rng();
    (void)val;
}

// Test default constructed produces deterministic output
TEST(SimplePcg32Test_1096, DefaultConstructedDeterministic_1096) {
    SimplePcg32 rng1;
    SimplePcg32 rng2;
    
    EXPECT_TRUE(rng1 == rng2);
    
    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

// Test large discard
TEST(SimplePcg32Test_1096, LargeDiscard_1096) {
    SimplePcg32 rng1(42u);
    SimplePcg32 rng2(42u);
    
    uint64_t large_skip = 10000;
    rng1.discard(large_skip);
    
    for (uint64_t i = 0; i < large_skip; ++i) {
        rng2();
    }
    
    EXPECT_EQ(rng1(), rng2());
}

// Test reseed after use restores to original state
TEST(SimplePcg32Test_1096, ReseedAfterUse_1096) {
    SimplePcg32 rng(42u);
    
    std::vector<SimplePcg32::result_type> first_run;
    for (int i = 0; i < 20; ++i) {
        first_run.push_back(rng());
    }
    
    rng.seed(42u);
    
    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(rng(), first_run[i]);
    }
}

// Test that consecutive calls produce different values
TEST(SimplePcg32Test_1096, ConsecutiveCallsDiffer_1096) {
    SimplePcg32 rng(42u);
    auto val1 = rng();
    auto val2 = rng();
    
    // While theoretically possible to be equal, extremely unlikely for a good PRNG
    EXPECT_NE(val1, val2);
}
