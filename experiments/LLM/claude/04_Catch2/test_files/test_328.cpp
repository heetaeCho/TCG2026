#include <gtest/gtest.h>
#include <cstdint>
#include <set>
#include <vector>

#include "catch2/internal/catch_random_number_generator.hpp"

class SimplePcg32Test_328 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor creates a valid generator
TEST_F(SimplePcg32Test_328, DefaultConstructor_328) {
    Catch::SimplePcg32 rng;
    // Should be able to generate a value without crashing
    auto val = rng();
    (void)val;
}

// Test explicit seed constructor
TEST_F(SimplePcg32Test_328, SeedConstructor_328) {
    Catch::SimplePcg32 rng(42);
    auto val = rng();
    (void)val;
}

// Test that min() returns 0
TEST_F(SimplePcg32Test_328, MinReturnsZero_328) {
    constexpr auto minVal = (Catch::SimplePcg32::min)();
    EXPECT_EQ(minVal, 0u);
}

// Test that max() returns the maximum uint32 value
TEST_F(SimplePcg32Test_328, MaxReturnsMaxUint32_328) {
    constexpr auto maxVal = (Catch::SimplePcg32::max)();
    EXPECT_EQ(maxVal, std::numeric_limits<std::uint32_t>::max());
}

// Test that same seed produces same sequence
TEST_F(SimplePcg32Test_328, SameSeedProducesSameSequence_328) {
    Catch::SimplePcg32 rng1(12345);
    Catch::SimplePcg32 rng2(12345);

    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

// Test that different seeds produce different sequences
TEST_F(SimplePcg32Test_328, DifferentSeedsProduceDifferentSequences_328) {
    Catch::SimplePcg32 rng1(1);
    Catch::SimplePcg32 rng2(2);

    bool allSame = true;
    for (int i = 0; i < 100; ++i) {
        if (rng1() != rng2()) {
            allSame = false;
            break;
        }
    }
    EXPECT_FALSE(allSame);
}

// Test equality operator for same seed
TEST_F(SimplePcg32Test_328, EqualityOperatorSameSeed_328) {
    Catch::SimplePcg32 rng1(100);
    Catch::SimplePcg32 rng2(100);
    EXPECT_TRUE(rng1 == rng2);
    EXPECT_FALSE(rng1 != rng2);
}

// Test inequality operator for different seeds
TEST_F(SimplePcg32Test_328, InequalityOperatorDifferentSeeds_328) {
    Catch::SimplePcg32 rng1(100);
    Catch::SimplePcg32 rng2(200);
    EXPECT_TRUE(rng1 != rng2);
    EXPECT_FALSE(rng1 == rng2);
}

// Test that generating a value changes state (inequality after one call)
TEST_F(SimplePcg32Test_328, GeneratingValueChangesState_328) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);

    rng1(); // advance rng1

    EXPECT_NE(rng1, rng2);
}

// Test seed method resets state
TEST_F(SimplePcg32Test_328, SeedMethodResetsState_328) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);

    // Advance rng1
    rng1();
    rng1();
    rng1();

    // Re-seed rng1
    rng1.seed(42);

    EXPECT_EQ(rng1, rng2);

    // Verify sequences match after reseed
    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

// Test discard advances the state correctly
TEST_F(SimplePcg32Test_328, DiscardAdvancesState_328) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);

    // Manually advance rng1 by 10
    for (int i = 0; i < 10; ++i) {
        rng1();
    }

    // Use discard on rng2
    rng2.discard(10);

    // They should now be in the same state
    EXPECT_EQ(rng1, rng2);

    // Verify subsequent values match
    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

// Test discard with zero does not change state
TEST_F(SimplePcg32Test_328, DiscardZeroNoChange_328) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);

    rng1.discard(0);

    EXPECT_EQ(rng1, rng2);
}

// Test discard with one is equivalent to one call
TEST_F(SimplePcg32Test_328, DiscardOneEquivalentToOneCall_328) {
    Catch::SimplePcg32 rng1(99);
    Catch::SimplePcg32 rng2(99);

    rng1();
    rng2.discard(1);

    EXPECT_EQ(rng1, rng2);
}

// Test that generated values are within [min, max] range
TEST_F(SimplePcg32Test_328, GeneratedValuesWithinRange_328) {
    Catch::SimplePcg32 rng(77);
    constexpr auto minVal = (Catch::SimplePcg32::min)();
    constexpr auto maxVal = (Catch::SimplePcg32::max)();

    for (int i = 0; i < 1000; ++i) {
        auto val = rng();
        EXPECT_GE(val, minVal);
        EXPECT_LE(val, maxVal);
    }
}

// Test that the generator produces varied output (not all same values)
TEST_F(SimplePcg32Test_328, ProducesVariedOutput_328) {
    Catch::SimplePcg32 rng(123);
    std::set<std::uint32_t> values;

    for (int i = 0; i < 100; ++i) {
        values.insert(rng());
    }

    // With a good PRNG, 100 calls should produce many distinct values
    EXPECT_GT(values.size(), 90u);
}

// Test seed with zero
TEST_F(SimplePcg32Test_328, SeedWithZero_328) {
    Catch::SimplePcg32 rng1(0);
    Catch::SimplePcg32 rng2;
    rng2.seed(0);

    EXPECT_EQ(rng1, rng2);
}

// Test default constructor uses expected default seed
TEST_F(SimplePcg32Test_328, DefaultConstructorMatchesDefaultSeed_328) {
    Catch::SimplePcg32 rng1;
    Catch::SimplePcg32 rng2(0xed743cc4U);

    // According to the interface, default ctor uses 0xed743cc4U
    EXPECT_EQ(rng1, rng2);
}

// Test large discard value
TEST_F(SimplePcg32Test_328, LargeDiscard_328) {
    Catch::SimplePcg32 rng1(55);
    Catch::SimplePcg32 rng2(55);

    uint64_t skipCount = 10000;
    for (uint64_t i = 0; i < skipCount; ++i) {
        rng1();
    }
    rng2.discard(skipCount);

    EXPECT_EQ(rng1, rng2);
}

// Test re-seeding with different value
TEST_F(SimplePcg32Test_328, ReseedWithDifferentValue_328) {
    Catch::SimplePcg32 rng(42);
    rng(); rng(); rng();

    rng.seed(100);

    Catch::SimplePcg32 fresh(100);
    EXPECT_EQ(rng, fresh);
}

// Test equality after generating same number of values
TEST_F(SimplePcg32Test_328, EqualityAfterSameNumberOfGenerations_328) {
    Catch::SimplePcg32 rng1(500);
    Catch::SimplePcg32 rng2(500);

    for (int i = 0; i < 50; ++i) {
        rng1();
        rng2();
    }

    EXPECT_EQ(rng1, rng2);
}

// Test inequality after different number of generations
TEST_F(SimplePcg32Test_328, InequalityAfterDifferentGenerations_328) {
    Catch::SimplePcg32 rng1(500);
    Catch::SimplePcg32 rng2(500);

    rng1();
    // rng2 not advanced

    EXPECT_NE(rng1, rng2);
}

// Test seed with max uint32 value
TEST_F(SimplePcg32Test_328, SeedWithMaxValue_328) {
    Catch::SimplePcg32 rng(std::numeric_limits<std::uint32_t>::max());
    auto val = rng();
    EXPECT_GE(val, (Catch::SimplePcg32::min)());
    EXPECT_LE(val, (Catch::SimplePcg32::max)());
}
