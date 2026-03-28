#include <gtest/gtest.h>
#include "catch2/internal/catch_random_number_generator.hpp"
#include <cstdint>
#include <set>
#include <limits>

class SimplePcg32Test_639 : public ::testing::Test {
protected:
    Catch::SimplePcg32 rng;
};

// Test default constructor creates a valid RNG
TEST_F(SimplePcg32Test_639, DefaultConstructor_639) {
    Catch::SimplePcg32 defaultRng;
    // Should be able to generate a number without crashing
    auto val = defaultRng();
    (void)val;
}

// Test explicit seed constructor
TEST_F(SimplePcg32Test_639, ExplicitSeedConstructor_639) {
    Catch::SimplePcg32 seededRng(42u);
    auto val = seededRng();
    (void)val;
}

// Test that same seed produces same sequence
TEST_F(SimplePcg32Test_639, SameSeedSameSequence_639) {
    Catch::SimplePcg32 rng1(12345u);
    Catch::SimplePcg32 rng2(12345u);
    
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

// Test that different seeds produce different sequences
TEST_F(SimplePcg32Test_639, DifferentSeedsDifferentSequence_639) {
    Catch::SimplePcg32 rng1(1u);
    Catch::SimplePcg32 rng2(2u);
    
    bool allSame = true;
    for (int i = 0; i < 10; ++i) {
        if (rng1() != rng2()) {
            allSame = false;
            break;
        }
    }
    EXPECT_FALSE(allSame);
}

// Test seed method resets state deterministically
TEST_F(SimplePcg32Test_639, SeedResetsState_639) {
    Catch::SimplePcg32 rng1;
    rng1.seed(42u);
    auto val1 = rng1();
    
    Catch::SimplePcg32 rng2;
    // Generate some values to change state
    rng2();
    rng2();
    rng2();
    rng2.seed(42u);
    auto val2 = rng2();
    
    EXPECT_EQ(val1, val2);
}

// Test seed with zero
TEST_F(SimplePcg32Test_639, SeedWithZero_639) {
    Catch::SimplePcg32 rng1(0u);
    Catch::SimplePcg32 rng2;
    rng2.seed(0u);
    
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

// Test seed with max value
TEST_F(SimplePcg32Test_639, SeedWithMaxValue_639) {
    Catch::SimplePcg32 rng1(std::numeric_limits<Catch::SimplePcg32::result_type>::max());
    auto val = rng1();
    (void)val;
}

// Test operator() produces output
TEST_F(SimplePcg32Test_639, OperatorCallProducesValues_639) {
    Catch::SimplePcg32 rng1(42u);
    std::set<Catch::SimplePcg32::result_type> values;
    for (int i = 0; i < 100; ++i) {
        values.insert(rng1());
    }
    // Should produce many distinct values
    EXPECT_GT(values.size(), 90u);
}

// Test equality operator - same seed, same state
TEST_F(SimplePcg32Test_639, EqualityOperatorSameState_639) {
    Catch::SimplePcg32 rng1(42u);
    Catch::SimplePcg32 rng2(42u);
    
    EXPECT_TRUE(rng1 == rng2);
    EXPECT_FALSE(rng1 != rng2);
}

// Test equality operator - different state after generation
TEST_F(SimplePcg32Test_639, EqualityOperatorDifferentState_639) {
    Catch::SimplePcg32 rng1(42u);
    Catch::SimplePcg32 rng2(42u);
    
    rng1(); // Advance rng1 by one step
    
    EXPECT_FALSE(rng1 == rng2);
    EXPECT_TRUE(rng1 != rng2);
}

// Test equality operator - different seeds
TEST_F(SimplePcg32Test_639, EqualityOperatorDifferentSeeds_639) {
    Catch::SimplePcg32 rng1(1u);
    Catch::SimplePcg32 rng2(2u);
    
    EXPECT_FALSE(rng1 == rng2);
    EXPECT_TRUE(rng1 != rng2);
}

// Test discard advances state correctly
TEST_F(SimplePcg32Test_639, DiscardAdvancesState_639) {
    Catch::SimplePcg32 rng1(42u);
    Catch::SimplePcg32 rng2(42u);
    
    // Manually advance rng1 by 5 steps
    for (int i = 0; i < 5; ++i) {
        rng1();
    }
    
    // Use discard to advance rng2 by 5 steps
    rng2.discard(5);
    
    // Both should now be in the same state
    EXPECT_EQ(rng1, rng2);
    EXPECT_EQ(rng1(), rng2());
}

// Test discard with zero does nothing
TEST_F(SimplePcg32Test_639, DiscardZero_639) {
    Catch::SimplePcg32 rng1(42u);
    Catch::SimplePcg32 rng2(42u);
    
    rng1.discard(0);
    
    EXPECT_EQ(rng1, rng2);
}

// Test discard with one
TEST_F(SimplePcg32Test_639, DiscardOne_639) {
    Catch::SimplePcg32 rng1(42u);
    Catch::SimplePcg32 rng2(42u);
    
    rng1();
    rng2.discard(1);
    
    EXPECT_EQ(rng1, rng2);
}

// Test min() returns 0
TEST_F(SimplePcg32Test_639, MinReturnsZero_639) {
    EXPECT_EQ(Catch::SimplePcg32::min(), 0u);
}

// Test max() returns max uint32
TEST_F(SimplePcg32Test_639, MaxReturnsMaxUint32_639) {
    EXPECT_EQ(Catch::SimplePcg32::max(), std::numeric_limits<std::uint32_t>::max());
}

// Test that generated values are within [min, max] range
TEST_F(SimplePcg32Test_639, GeneratedValuesInRange_639) {
    Catch::SimplePcg32 rng1(99u);
    for (int i = 0; i < 1000; ++i) {
        auto val = rng1();
        EXPECT_GE(val, Catch::SimplePcg32::min());
        EXPECT_LE(val, Catch::SimplePcg32::max());
    }
}

// Test discard with large value doesn't crash
TEST_F(SimplePcg32Test_639, DiscardLargeValue_639) {
    Catch::SimplePcg32 rng1(42u);
    rng1.discard(10000);
    auto val = rng1();
    (void)val;
}

// Test repeated seeding
TEST_F(SimplePcg32Test_639, RepeatedSeeding_639) {
    Catch::SimplePcg32 rng1;
    
    rng1.seed(100u);
    auto val1 = rng1();
    
    rng1.seed(100u);
    auto val2 = rng1();
    
    EXPECT_EQ(val1, val2);
}

// Test that sequential calls produce different values
TEST_F(SimplePcg32Test_639, SequentialCallsDifferent_639) {
    Catch::SimplePcg32 rng1(42u);
    auto val1 = rng1();
    auto val2 = rng1();
    auto val3 = rng1();
    
    // It's extremely unlikely (but theoretically possible) for consecutive values to be equal
    // Check that at least two of three are different
    EXPECT_TRUE(val1 != val2 || val2 != val3);
}

// Test equality after discard and manual advance synchronize
TEST_F(SimplePcg32Test_639, EqualityAfterSynchronization_639) {
    Catch::SimplePcg32 rng1(42u);
    Catch::SimplePcg32 rng2(42u);
    
    // Advance both by different means to same point
    rng1.discard(10);
    for (int i = 0; i < 10; ++i) {
        rng2();
    }
    
    EXPECT_TRUE(rng1 == rng2);
    
    // And subsequent values should match
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

// Test copy behavior (if default copy works)
TEST_F(SimplePcg32Test_639, CopyProducesSameState_639) {
    Catch::SimplePcg32 rng1(42u);
    rng1(); // advance a bit
    rng1();
    
    Catch::SimplePcg32 rng2 = rng1; // copy
    
    EXPECT_EQ(rng1, rng2);
    EXPECT_EQ(rng1(), rng2());
}

// Test default constructed RNGs are equal
TEST_F(SimplePcg32Test_639, DefaultConstructedAreEqual_639) {
    Catch::SimplePcg32 rng1;
    Catch::SimplePcg32 rng2;
    
    EXPECT_EQ(rng1, rng2);
}

// Test that the default seed value produces consistent results
TEST_F(SimplePcg32Test_639, DefaultSeedConsistency_639) {
    Catch::SimplePcg32 rng1;
    Catch::SimplePcg32 rng2;
    
    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}
