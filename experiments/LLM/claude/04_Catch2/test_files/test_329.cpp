#include <gtest/gtest.h>
#include <cstdint>
#include <set>
#include <vector>

#include "catch2/internal/catch_random_number_generator.hpp"

class SimplePcg32Test_329 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction
TEST_F(SimplePcg32Test_329, DefaultConstruction_329) {
    Catch::SimplePcg32 rng;
    // Should be constructible without errors
    auto val = rng();
    // Just verify it produces a value (no crash)
    (void)val;
}

// Test construction with explicit seed
TEST_F(SimplePcg32Test_329, ExplicitSeedConstruction_329) {
    Catch::SimplePcg32 rng(42);
    auto val = rng();
    (void)val;
}

// Test that same seed produces same sequence
TEST_F(SimplePcg32Test_329, SameSeedProducesSameSequence_329) {
    Catch::SimplePcg32 rng1(12345);
    Catch::SimplePcg32 rng2(12345);

    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

// Test that different seeds produce different sequences
TEST_F(SimplePcg32Test_329, DifferentSeedsProduceDifferentSequences_329) {
    Catch::SimplePcg32 rng1(1);
    Catch::SimplePcg32 rng2(2);

    bool anyDifferent = false;
    for (int i = 0; i < 100; ++i) {
        if (rng1() != rng2()) {
            anyDifferent = true;
            break;
        }
    }
    EXPECT_TRUE(anyDifferent);
}

// Test min() static method
TEST_F(SimplePcg32Test_329, MinValue_329) {
    auto minVal = (Catch::SimplePcg32::min)();
    EXPECT_EQ(minVal, 0u);
}

// Test max() static method
TEST_F(SimplePcg32Test_329, MaxValue_329) {
    auto maxVal = (Catch::SimplePcg32::max)();
    EXPECT_EQ(maxVal, static_cast<Catch::SimplePcg32::result_type>(-1));
    EXPECT_EQ(maxVal, 0xFFFFFFFFu);
}

// Test equality operator - same state
TEST_F(SimplePcg32Test_329, EqualityOperatorSameState_329) {
    Catch::SimplePcg32 rng1(100);
    Catch::SimplePcg32 rng2(100);
    EXPECT_TRUE(rng1 == rng2);
}

// Test equality operator - different state
TEST_F(SimplePcg32Test_329, EqualityOperatorDifferentState_329) {
    Catch::SimplePcg32 rng1(100);
    Catch::SimplePcg32 rng2(200);
    EXPECT_FALSE(rng1 == rng2);
}

// Test inequality operator - same state
TEST_F(SimplePcg32Test_329, InequalityOperatorSameState_329) {
    Catch::SimplePcg32 rng1(100);
    Catch::SimplePcg32 rng2(100);
    EXPECT_FALSE(rng1 != rng2);
}

// Test inequality operator - different state
TEST_F(SimplePcg32Test_329, InequalityOperatorDifferentState_329) {
    Catch::SimplePcg32 rng1(100);
    Catch::SimplePcg32 rng2(200);
    EXPECT_TRUE(rng1 != rng2);
}

// Test that calling operator() advances state (generators become unequal)
TEST_F(SimplePcg32Test_329, OperatorCallAdvancesState_329) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);
    EXPECT_TRUE(rng1 == rng2);

    rng1();
    EXPECT_TRUE(rng1 != rng2);
}

// Test seed() resets to a known state
TEST_F(SimplePcg32Test_329, SeedResetsState_329) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);

    // Advance rng1
    rng1();
    rng1();
    rng1();

    // Re-seed rng1
    rng1.seed(42);
    EXPECT_TRUE(rng1 == rng2);

    // Verify they produce same sequence
    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

// Test seed() with different value
TEST_F(SimplePcg32Test_329, SeedWithDifferentValue_329) {
    Catch::SimplePcg32 rng(42);
    rng.seed(99);

    Catch::SimplePcg32 rng2(99);
    EXPECT_TRUE(rng == rng2);
}

// Test discard(0) doesn't change state
TEST_F(SimplePcg32Test_329, DiscardZero_329) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);

    rng1.discard(0);
    EXPECT_TRUE(rng1 == rng2);
}

// Test discard(n) is equivalent to calling operator() n times
TEST_F(SimplePcg32Test_329, DiscardEquivalentToMultipleCalls_329) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);

    const uint64_t n = 10;
    rng1.discard(n);

    for (uint64_t i = 0; i < n; ++i) {
        rng2();
    }

    EXPECT_TRUE(rng1 == rng2);
}

// Test discard with large value
TEST_F(SimplePcg32Test_329, DiscardLargeValue_329) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);

    const uint64_t n = 1000;
    rng1.discard(n);

    for (uint64_t i = 0; i < n; ++i) {
        rng2();
    }

    EXPECT_TRUE(rng1 == rng2);
}

// Test discard(1) is equivalent to single call
TEST_F(SimplePcg32Test_329, DiscardOneEquivalentToSingleCall_329) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);

    rng1.discard(1);
    rng2();

    EXPECT_TRUE(rng1 == rng2);
}

// Test that generator produces varied output (not all same value)
TEST_F(SimplePcg32Test_329, ProducesVariedOutput_329) {
    Catch::SimplePcg32 rng(42);
    std::set<Catch::SimplePcg32::result_type> values;

    for (int i = 0; i < 100; ++i) {
        values.insert(rng());
    }

    // Should have many distinct values
    EXPECT_GT(values.size(), 90u);
}

// Test construction with seed 0
TEST_F(SimplePcg32Test_329, SeedZero_329) {
    Catch::SimplePcg32 rng(0);
    auto val1 = rng();
    auto val2 = rng();
    // Just ensure it works and produces something
    // Two consecutive values should differ (extremely likely for any reasonable PRNG)
    EXPECT_NE(val1, val2);
}

// Test construction with max seed value
TEST_F(SimplePcg32Test_329, MaxSeedValue_329) {
    Catch::SimplePcg32 rng(static_cast<Catch::SimplePcg32::result_type>(-1));
    auto val = rng();
    (void)val;
    // No crash expected
}

// Test default constructor produces deterministic sequence
TEST_F(SimplePcg32Test_329, DefaultConstructorDeterministic_329) {
    Catch::SimplePcg32 rng1;
    Catch::SimplePcg32 rng2;

    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

// Test that seed after default construction with same default seed gives equal state
TEST_F(SimplePcg32Test_329, SeedToDefaultValue_329) {
    Catch::SimplePcg32 rng1;
    Catch::SimplePcg32 rng2;

    // Advance rng1
    for (int i = 0; i < 10; ++i) {
        rng1();
    }

    // Re-seed with the known default seed
    rng1.seed(0xed743cc4U);
    EXPECT_TRUE(rng1 == rng2);
}

// Test operator() return value is within range
TEST_F(SimplePcg32Test_329, OutputWithinRange_329) {
    Catch::SimplePcg32 rng(42);

    for (int i = 0; i < 1000; ++i) {
        auto val = rng();
        EXPECT_GE(val, (Catch::SimplePcg32::min)());
        EXPECT_LE(val, (Catch::SimplePcg32::max)());
    }
}

// Test equality after advancing both by same amount
TEST_F(SimplePcg32Test_329, EqualityAfterSameAdvancement_329) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);

    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(rng1(), rng2());
        EXPECT_TRUE(rng1 == rng2);
    }
}

// Test inequality after advancing one more than the other
TEST_F(SimplePcg32Test_329, InequalityAfterDifferentAdvancement_329) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);

    rng1();
    rng1();
    rng2();

    EXPECT_TRUE(rng1 != rng2);
}
