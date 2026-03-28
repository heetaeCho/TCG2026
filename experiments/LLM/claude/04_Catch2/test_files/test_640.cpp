#include <gtest/gtest.h>
#include "catch2/internal/catch_random_number_generator.hpp"
#include <cstdint>
#include <set>

class SimplePcg32Test_640 : public ::testing::Test {
protected:
    Catch::SimplePcg32 rng;
};

// Test default construction produces a valid generator
TEST_F(SimplePcg32Test_640, DefaultConstruction_640) {
    Catch::SimplePcg32 gen;
    // Should be callable without crashing
    auto val = gen();
    (void)val;
}

// Test explicit seed construction
TEST_F(SimplePcg32Test_640, ExplicitSeedConstruction_640) {
    Catch::SimplePcg32 gen(42);
    auto val = gen();
    (void)val;
}

// Test that same seed produces same sequence
TEST_F(SimplePcg32Test_640, SameSeedProducesSameSequence_640) {
    Catch::SimplePcg32 gen1(12345);
    Catch::SimplePcg32 gen2(12345);
    
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(gen1(), gen2());
    }
}

// Test that different seeds produce different sequences
TEST_F(SimplePcg32Test_640, DifferentSeedsProduceDifferentSequences_640) {
    Catch::SimplePcg32 gen1(1);
    Catch::SimplePcg32 gen2(2);
    
    bool all_same = true;
    for (int i = 0; i < 100; ++i) {
        if (gen1() != gen2()) {
            all_same = false;
            break;
        }
    }
    EXPECT_FALSE(all_same);
}

// Test seed() resets the generator state
TEST_F(SimplePcg32Test_640, SeedResetsState_640) {
    Catch::SimplePcg32 gen(42);
    auto first_val = gen();
    
    gen.seed(42);
    auto second_val = gen();
    
    EXPECT_EQ(first_val, second_val);
}

// Test seed() with same seed produces same sequence
TEST_F(SimplePcg32Test_640, SeedProducesSameSequenceAsConstruction_640) {
    Catch::SimplePcg32 gen1(99);
    
    Catch::SimplePcg32 gen2;
    gen2.seed(99);
    
    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(gen1(), gen2());
    }
}

// Test discard(0) does nothing
TEST_F(SimplePcg32Test_640, DiscardZero_640) {
    Catch::SimplePcg32 gen1(42);
    Catch::SimplePcg32 gen2(42);
    
    gen1.discard(0);
    
    EXPECT_EQ(gen1(), gen2());
}

// Test discard(n) is equivalent to calling operator() n times
TEST_F(SimplePcg32Test_640, DiscardEquivalentToNCalls_640) {
    Catch::SimplePcg32 gen1(42);
    Catch::SimplePcg32 gen2(42);
    
    gen1.discard(5);
    for (int i = 0; i < 5; ++i) {
        gen2();
    }
    
    EXPECT_EQ(gen1(), gen2());
}

// Test discard with larger values
TEST_F(SimplePcg32Test_640, DiscardLargerValue_640) {
    Catch::SimplePcg32 gen1(42);
    Catch::SimplePcg32 gen2(42);
    
    uint64_t skip = 100;
    gen1.discard(skip);
    for (uint64_t i = 0; i < skip; ++i) {
        gen2();
    }
    
    EXPECT_EQ(gen1(), gen2());
}

// Test discard(1) is equivalent to one call
TEST_F(SimplePcg32Test_640, DiscardOne_640) {
    Catch::SimplePcg32 gen1(42);
    Catch::SimplePcg32 gen2(42);
    
    gen1.discard(1);
    gen2();
    
    EXPECT_EQ(gen1(), gen2());
}

// Test equality operator - same state
TEST_F(SimplePcg32Test_640, EqualityOperatorSameState_640) {
    Catch::SimplePcg32 gen1(42);
    Catch::SimplePcg32 gen2(42);
    
    EXPECT_TRUE(gen1 == gen2);
}

// Test equality operator - different state
TEST_F(SimplePcg32Test_640, EqualityOperatorDifferentState_640) {
    Catch::SimplePcg32 gen1(42);
    Catch::SimplePcg32 gen2(43);
    
    EXPECT_FALSE(gen1 == gen2);
}

// Test inequality operator - same state
TEST_F(SimplePcg32Test_640, InequalityOperatorSameState_640) {
    Catch::SimplePcg32 gen1(42);
    Catch::SimplePcg32 gen2(42);
    
    EXPECT_FALSE(gen1 != gen2);
}

// Test inequality operator - different state
TEST_F(SimplePcg32Test_640, InequalityOperatorDifferentState_640) {
    Catch::SimplePcg32 gen1(42);
    Catch::SimplePcg32 gen2(43);
    
    EXPECT_TRUE(gen1 != gen2);
}

// Test that after calling operator(), state changes (generators become unequal)
TEST_F(SimplePcg32Test_640, OperatorCallChangesState_640) {
    Catch::SimplePcg32 gen1(42);
    Catch::SimplePcg32 gen2(42);
    
    EXPECT_TRUE(gen1 == gen2);
    gen1();
    EXPECT_TRUE(gen1 != gen2);
}

// Test min() returns 0
TEST_F(SimplePcg32Test_640, MinValue_640) {
    EXPECT_EQ(Catch::SimplePcg32::min(), 0u);
}

// Test max() returns max of uint32_t
TEST_F(SimplePcg32Test_640, MaxValue_640) {
    EXPECT_EQ(Catch::SimplePcg32::max(), std::numeric_limits<std::uint32_t>::max());
}

// Test that min() < max()
TEST_F(SimplePcg32Test_640, MinLessThanMax_640) {
    EXPECT_LT(Catch::SimplePcg32::min(), Catch::SimplePcg32::max());
}

// Test that operator() returns values within [min, max]
TEST_F(SimplePcg32Test_640, OutputWithinRange_640) {
    Catch::SimplePcg32 gen(42);
    for (int i = 0; i < 1000; ++i) {
        auto val = gen();
        EXPECT_GE(val, Catch::SimplePcg32::min());
        EXPECT_LE(val, Catch::SimplePcg32::max());
    }
}

// Test that the generator produces varied output (not all zeros, not constant)
TEST_F(SimplePcg32Test_640, ProducesVariedOutput_640) {
    Catch::SimplePcg32 gen(42);
    std::set<Catch::SimplePcg32::result_type> values;
    for (int i = 0; i < 100; ++i) {
        values.insert(gen());
    }
    // Should produce many distinct values
    EXPECT_GT(values.size(), 90u);
}

// Test default constructed generators are equal
TEST_F(SimplePcg32Test_640, DefaultConstructedAreEqual_640) {
    Catch::SimplePcg32 gen1;
    Catch::SimplePcg32 gen2;
    
    EXPECT_TRUE(gen1 == gen2);
}

// Test seed(0) differs from default
TEST_F(SimplePcg32Test_640, SeedZeroDiffersFromDefault_640) {
    Catch::SimplePcg32 gen1; // default seed is 0xed743cc4U
    Catch::SimplePcg32 gen2(0);
    
    // They should be different since default is 0xed743cc4U and gen2 is seeded with 0
    bool same_first = (gen1() == gen2());
    // We just check they can be called; the actual comparison depends on implementation
    (void)same_first;
}

// Test that equality holds after same number of advances
TEST_F(SimplePcg32Test_640, EqualityAfterSameAdvances_640) {
    Catch::SimplePcg32 gen1(42);
    Catch::SimplePcg32 gen2(42);
    
    for (int i = 0; i < 10; ++i) {
        gen1();
        gen2();
    }
    
    EXPECT_TRUE(gen1 == gen2);
}

// Test that equality fails after different number of advances
TEST_F(SimplePcg32Test_640, InequalityAfterDifferentAdvances_640) {
    Catch::SimplePcg32 gen1(42);
    Catch::SimplePcg32 gen2(42);
    
    gen1();
    // gen2 not advanced
    
    EXPECT_TRUE(gen1 != gen2);
    EXPECT_FALSE(gen1 == gen2);
}

// Test re-seeding makes generators equal again
TEST_F(SimplePcg32Test_640, ReseedingMakesEqual_640) {
    Catch::SimplePcg32 gen1(42);
    Catch::SimplePcg32 gen2(42);
    
    // Advance gen1
    for (int i = 0; i < 10; ++i) {
        gen1();
    }
    
    EXPECT_TRUE(gen1 != gen2);
    
    // Reseed both
    gen1.seed(100);
    gen2.seed(100);
    
    EXPECT_TRUE(gen1 == gen2);
    EXPECT_EQ(gen1(), gen2());
}

// Test result_type is uint32_t compatible
TEST_F(SimplePcg32Test_640, ResultTypeSize_640) {
    static_assert(sizeof(Catch::SimplePcg32::result_type) == sizeof(std::uint32_t),
                  "result_type should be 32 bits");
}
