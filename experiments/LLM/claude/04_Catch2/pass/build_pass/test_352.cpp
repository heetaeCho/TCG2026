#include <gtest/gtest.h>
#include <cstdint>
#include <set>

// Include the necessary headers
#include "catch2/generators/catch_generators_random.cpp"
#include "catch2/internal/catch_random_number_generator.hpp"

// If the header for getSeed is separate, include it too
// We need to declare the function if not available through headers
namespace Catch {
namespace Generators {
namespace Detail {
    std::uint32_t getSeed();
}
}
}

class GetSeedTest_352 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getSeed returns a value within the valid uint32_t range
TEST_F(GetSeedTest_352, ReturnsUint32Value_352) {
    std::uint32_t seed = Catch::Generators::Detail::getSeed();
    EXPECT_GE(seed, std::numeric_limits<std::uint32_t>::min());
    EXPECT_LE(seed, std::numeric_limits<std::uint32_t>::max());
}

// Test that getSeed can be called multiple times without crashing
TEST_F(GetSeedTest_352, CanBeCalledMultipleTimes_352) {
    EXPECT_NO_THROW({
        for (int i = 0; i < 100; ++i) {
            Catch::Generators::Detail::getSeed();
        }
    });
}

// Test that successive calls to getSeed produce different values
// (since it advances the RNG state each time)
TEST_F(GetSeedTest_352, SuccessiveCallsProduceDifferentValues_352) {
    std::uint32_t seed1 = Catch::Generators::Detail::getSeed();
    std::uint32_t seed2 = Catch::Generators::Detail::getSeed();
    // While theoretically possible to get the same value, 
    // a properly functioning PCG should produce different values
    // on successive calls
    EXPECT_NE(seed1, seed2);
}

// Test that getSeed produces a variety of values over many calls
TEST_F(GetSeedTest_352, ProducesVarietyOfValues_352) {
    std::set<std::uint32_t> values;
    for (int i = 0; i < 1000; ++i) {
        values.insert(Catch::Generators::Detail::getSeed());
    }
    // With 1000 calls from a good RNG, we should get many distinct values
    EXPECT_GT(values.size(), 900u);
}

// Test that getSeed returns non-zero values (at least most of the time)
TEST_F(GetSeedTest_352, ProducesNonZeroValues_352) {
    int nonZeroCount = 0;
    for (int i = 0; i < 100; ++i) {
        if (Catch::Generators::Detail::getSeed() != 0) {
            nonZeroCount++;
        }
    }
    // Almost all values should be non-zero
    EXPECT_GT(nonZeroCount, 95);
}

// Test SimplePcg32 basic functionality
class SimplePcg32Test_352 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction
TEST_F(SimplePcg32Test_352, DefaultConstruction_352) {
    EXPECT_NO_THROW({
        Catch::SimplePcg32 rng;
    });
}

// Test seeded construction
TEST_F(SimplePcg32Test_352, SeededConstruction_352) {
    EXPECT_NO_THROW({
        Catch::SimplePcg32 rng(42);
    });
}

// Test that operator() returns values
TEST_F(SimplePcg32Test_352, OperatorCallReturnsValue_352) {
    Catch::SimplePcg32 rng(12345);
    std::uint32_t val = rng();
    // Just verify it doesn't crash and returns something
    EXPECT_GE(val, (Catch::SimplePcg32::min)());
    EXPECT_LE(val, (Catch::SimplePcg32::max)());
}

// Test determinism: same seed produces same sequence
TEST_F(SimplePcg32Test_352, DeterministicWithSameSeed_352) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);
    
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

// Test that different seeds produce different sequences
TEST_F(SimplePcg32Test_352, DifferentSeedsDifferentSequences_352) {
    Catch::SimplePcg32 rng1(1);
    Catch::SimplePcg32 rng2(2);
    
    bool allSame = true;
    for (int i = 0; i < 10; ++i) {
        if (rng1() != rng2()) {
            allSame = false;
            break;
        }
    }
    EXPECT_FALSE(allSame);
}

// Test equality operator
TEST_F(SimplePcg32Test_352, EqualityOperator_352) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);
    EXPECT_TRUE(rng1 == rng2);
    
    rng1();
    EXPECT_FALSE(rng1 == rng2);
}

// Test inequality operator
TEST_F(SimplePcg32Test_352, InequalityOperator_352) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(43);
    EXPECT_TRUE(rng1 != rng2);
}

// Test seed method resets state
TEST_F(SimplePcg32Test_352, SeedResetsState_352) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);
    
    // Advance rng1
    rng1();
    rng1();
    rng1();
    
    // Re-seed rng1
    rng1.seed(42);
    
    // Now both should produce the same sequence
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

// Test discard advances state correctly
TEST_F(SimplePcg32Test_352, DiscardAdvancesState_352) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);
    
    // Manually advance rng1
    rng1();
    rng1();
    rng1();
    
    // Use discard on rng2
    rng2.discard(3);
    
    // Both should now be in the same state
    EXPECT_EQ(rng1(), rng2());
}

// Test discard with 0 doesn't change state
TEST_F(SimplePcg32Test_352, DiscardZeroNoChange_352) {
    Catch::SimplePcg32 rng1(42);
    Catch::SimplePcg32 rng2(42);
    
    rng1.discard(0);
    
    EXPECT_TRUE(rng1 == rng2);
}

// Test min and max
TEST_F(SimplePcg32Test_352, MinMaxValues_352) {
    EXPECT_EQ((Catch::SimplePcg32::min)(), 0u);
    EXPECT_EQ((Catch::SimplePcg32::max)(), std::numeric_limits<std::uint32_t>::max());
}

// Test that default constructed generators are equal
TEST_F(SimplePcg32Test_352, DefaultConstructedAreEqual_352) {
    Catch::SimplePcg32 rng1;
    Catch::SimplePcg32 rng2;
    EXPECT_TRUE(rng1 == rng2);
}

// Test large discard value
TEST_F(SimplePcg32Test_352, LargeDiscard_352) {
    Catch::SimplePcg32 rng(42);
    EXPECT_NO_THROW(rng.discard(1000000));
    // Should still produce valid output
    std::uint32_t val = rng();
    EXPECT_GE(val, (Catch::SimplePcg32::min)());
    EXPECT_LE(val, (Catch::SimplePcg32::max)());
}
