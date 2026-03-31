#include <gtest/gtest.h>
#include <cstdint>
#include <set>
#include <vector>

// Include the header for SimplePcg32
#include "catch2/internal/catch_random_number_generator.hpp"

using namespace Catch;

// Test default constructor creates a valid object
TEST(SimplePcg32Test_643, DefaultConstructor_643) {
    SimplePcg32 rng;
    // Should be able to generate a number without crashing
    auto val = rng();
    (void)val;
}

// Test explicit seed constructor
TEST(SimplePcg32Test_643, SeedConstructor_643) {
    SimplePcg32 rng(42);
    auto val = rng();
    (void)val;
}

// Test that two default-constructed RNGs are equal
TEST(SimplePcg32Test_643, DefaultConstructedAreEqual_643) {
    SimplePcg32 rng1;
    SimplePcg32 rng2;
    EXPECT_TRUE(rng1 == rng2);
    EXPECT_FALSE(rng1 != rng2);
}

// Test that two RNGs with the same seed are equal
TEST(SimplePcg32Test_643, SameSeedAreEqual_643) {
    SimplePcg32 rng1(12345);
    SimplePcg32 rng2(12345);
    EXPECT_TRUE(rng1 == rng2);
    EXPECT_FALSE(rng1 != rng2);
}

// Test that two RNGs with different seeds are not equal
TEST(SimplePcg32Test_643, DifferentSeedsAreNotEqual_643) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(43);
    EXPECT_TRUE(rng1 != rng2);
    EXPECT_FALSE(rng1 == rng2);
}

// Test that same seed produces same sequence
TEST(SimplePcg32Test_643, SameSeedSameSequence_643) {
    SimplePcg32 rng1(100);
    SimplePcg32 rng2(100);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

// Test that different seeds produce different sequences
TEST(SimplePcg32Test_643, DifferentSeedsDifferentSequence_643) {
    SimplePcg32 rng1(100);
    SimplePcg32 rng2(200);
    bool allSame = true;
    for (int i = 0; i < 100; ++i) {
        if (rng1() != rng2()) {
            allSame = false;
            break;
        }
    }
    EXPECT_FALSE(allSame);
}

// Test that calling operator() advances state (RNG becomes different from fresh copy)
TEST(SimplePcg32Test_643, OperatorAdvancesState_643) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);
    rng1();
    EXPECT_TRUE(rng1 != rng2);
}

// Test seed method resets state
TEST(SimplePcg32Test_643, SeedResetsState_643) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);
    // Advance rng1
    rng1();
    rng1();
    rng1();
    // Re-seed rng1 with same seed
    rng1.seed(42);
    EXPECT_TRUE(rng1 == rng2);
}

// Test seed method with different seed changes state
TEST(SimplePcg32Test_643, SeedWithDifferentValue_643) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);
    rng1.seed(99);
    EXPECT_TRUE(rng1 != rng2);
}

// Test discard skips the same number of values as calling operator()
TEST(SimplePcg32Test_643, DiscardEquivalentToMultipleCalls_643) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);
    
    // Advance rng1 by calling operator() 10 times
    for (int i = 0; i < 10; ++i) {
        rng1();
    }
    
    // Advance rng2 by discarding 10
    rng2.discard(10);
    
    EXPECT_TRUE(rng1 == rng2);
}

// Test discard with 0 does nothing
TEST(SimplePcg32Test_643, DiscardZero_643) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);
    rng2.discard(0);
    EXPECT_TRUE(rng1 == rng2);
}

// Test discard with 1 is same as single call
TEST(SimplePcg32Test_643, DiscardOne_643) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);
    rng1();
    rng2.discard(1);
    EXPECT_TRUE(rng1 == rng2);
}

// Test min() returns 0
TEST(SimplePcg32Test_643, MinReturnsZero_643) {
    EXPECT_EQ(SimplePcg32::min(), 0u);
}

// Test max() returns maximum uint32_t
TEST(SimplePcg32Test_643, MaxReturnsMaxUint32_643) {
    EXPECT_EQ(SimplePcg32::max(), std::numeric_limits<std::uint32_t>::max());
}

// Test that generated values are within [min, max] range
TEST(SimplePcg32Test_643, OutputInRange_643) {
    SimplePcg32 rng(42);
    for (int i = 0; i < 1000; ++i) {
        auto val = rng();
        EXPECT_GE(val, SimplePcg32::min());
        EXPECT_LE(val, SimplePcg32::max());
    }
}

// Test that the RNG produces varied output (not all the same value)
TEST(SimplePcg32Test_643, ProducesVariedOutput_643) {
    SimplePcg32 rng(42);
    std::set<SimplePcg32::result_type> values;
    for (int i = 0; i < 100; ++i) {
        values.insert(rng());
    }
    // With 100 calls, we should have many distinct values
    EXPECT_GT(values.size(), 90u);
}

// Test seed with 0
TEST(SimplePcg32Test_643, SeedWithZero_643) {
    SimplePcg32 rng(0);
    auto val = rng();
    (void)val; // Should not crash
}

// Test seed with max uint32
TEST(SimplePcg32Test_643, SeedWithMaxValue_643) {
    SimplePcg32 rng(std::numeric_limits<std::uint32_t>::max());
    auto val = rng();
    (void)val; // Should not crash
}

// Test equality after same number of advances
TEST(SimplePcg32Test_643, EqualityAfterSameAdvances_643) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);
    for (int i = 0; i < 50; ++i) {
        EXPECT_TRUE(rng1 == rng2);
        auto v1 = rng1();
        auto v2 = rng2();
        EXPECT_EQ(v1, v2);
    }
    EXPECT_TRUE(rng1 == rng2);
}

// Test inequality after different number of advances
TEST(SimplePcg32Test_643, InequalityAfterDifferentAdvances_643) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);
    rng1();
    rng1();
    rng2();
    EXPECT_TRUE(rng1 != rng2);
}

// Test large discard
TEST(SimplePcg32Test_643, LargeDiscard_643) {
    SimplePcg32 rng1(42);
    SimplePcg32 rng2(42);
    
    uint64_t skipCount = 10000;
    for (uint64_t i = 0; i < skipCount; ++i) {
        rng1();
    }
    rng2.discard(skipCount);
    
    EXPECT_TRUE(rng1 == rng2);
}

// Test re-seeding produces reproducible sequence
TEST(SimplePcg32Test_643, ReseedProducesReproducibleSequence_643) {
    SimplePcg32 rng(42);
    std::vector<SimplePcg32::result_type> seq1;
    for (int i = 0; i < 10; ++i) {
        seq1.push_back(rng());
    }
    
    rng.seed(42);
    std::vector<SimplePcg32::result_type> seq2;
    for (int i = 0; i < 10; ++i) {
        seq2.push_back(rng());
    }
    
    EXPECT_EQ(seq1, seq2);
}

// Test default constructor uses expected default seed (0xed743cc4U)
TEST(SimplePcg32Test_643, DefaultConstructorMatchesExplicitDefaultSeed_643) {
    SimplePcg32 rng_default;
    SimplePcg32 rng_explicit(0xed743cc4U);
    EXPECT_TRUE(rng_default == rng_explicit);
}
