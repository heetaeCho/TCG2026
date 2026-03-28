#include "catch2/internal/catch_uniform_integer_distribution.hpp"
#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include <random>

// A simple deterministic generator for testing
class SimpleGenerator {
public:
    using result_type = uint32_t;
    
    explicit SimpleGenerator(uint32_t seed) : state(seed) {}
    
    constexpr result_type operator()() {
        // Simple LCG
        state = state * 1103515245u + 12345u;
        return state;
    }
    
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return std::numeric_limits<uint32_t>::max(); }

private:
    uint32_t state;
};

class SimpleGenerator64 {
public:
    using result_type = uint64_t;
    
    explicit SimpleGenerator64(uint64_t seed) : state(seed) {}
    
    constexpr result_type operator()() {
        state = state * 6364136223846793005ULL + 1442695040888963407ULL;
        return state;
    }
    
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return std::numeric_limits<uint64_t>::max(); }

private:
    uint64_t state;
};

class UniformIntegerDistributionTest_1057 : public ::testing::Test {};

// Test construction with equal bounds (a == b)
TEST_F(UniformIntegerDistributionTest_1057, ConstructionEqualBounds_1057) {
    Catch::uniform_integer_distribution<int> dist(5, 5);
    EXPECT_EQ(dist.a(), 5);
    EXPECT_EQ(dist.b(), 5);
}

// Test construction with different bounds
TEST_F(UniformIntegerDistributionTest_1057, ConstructionDifferentBounds_1057) {
    Catch::uniform_integer_distribution<int> dist(1, 10);
    EXPECT_EQ(dist.a(), 1);
    EXPECT_EQ(dist.b(), 10);
}

// Test that a() returns the lower bound
TEST_F(UniformIntegerDistributionTest_1057, ReturnsCorrectLowerBound_1057) {
    Catch::uniform_integer_distribution<int> dist(-100, 100);
    EXPECT_EQ(dist.a(), -100);
}

// Test that b() returns the upper bound
TEST_F(UniformIntegerDistributionTest_1057, ReturnsCorrectUpperBound_1057) {
    Catch::uniform_integer_distribution<int> dist(-100, 100);
    EXPECT_EQ(dist.b(), 100);
}

// Test generation produces values within range for int
TEST_F(UniformIntegerDistributionTest_1057, GeneratedValuesWithinRangeInt_1057) {
    Catch::uniform_integer_distribution<int> dist(0, 100);
    SimpleGenerator gen(42);
    
    for (int i = 0; i < 1000; ++i) {
        int val = dist(gen);
        EXPECT_GE(val, 0);
        EXPECT_LE(val, 100);
    }
}

// Test generation with negative range
TEST_F(UniformIntegerDistributionTest_1057, GeneratedValuesWithinNegativeRange_1057) {
    Catch::uniform_integer_distribution<int> dist(-50, -10);
    SimpleGenerator gen(123);
    
    for (int i = 0; i < 1000; ++i) {
        int val = dist(gen);
        EXPECT_GE(val, -50);
        EXPECT_LE(val, -10);
    }
}

// Test generation with range crossing zero
TEST_F(UniformIntegerDistributionTest_1057, GeneratedValuesWithinCrossingZeroRange_1057) {
    Catch::uniform_integer_distribution<int> dist(-50, 50);
    SimpleGenerator gen(999);
    
    for (int i = 0; i < 1000; ++i) {
        int val = dist(gen);
        EXPECT_GE(val, -50);
        EXPECT_LE(val, 50);
    }
}

// Test with equal bounds always returns same value
TEST_F(UniformIntegerDistributionTest_1057, EqualBoundsAlwaysReturnsSameValue_1057) {
    Catch::uniform_integer_distribution<int> dist(42, 42);
    SimpleGenerator gen(0);
    
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(dist(gen), 42);
    }
}

// Test with unsigned integer type
TEST_F(UniformIntegerDistributionTest_1057, UnsignedIntegerType_1057) {
    Catch::uniform_integer_distribution<unsigned int> dist(10u, 20u);
    SimpleGenerator gen(7);
    
    for (int i = 0; i < 1000; ++i) {
        unsigned int val = dist(gen);
        EXPECT_GE(val, 10u);
        EXPECT_LE(val, 20u);
    }
}

// Test with int32_t
TEST_F(UniformIntegerDistributionTest_1057, Int32Type_1057) {
    Catch::uniform_integer_distribution<int32_t> dist(-1000, 1000);
    SimpleGenerator gen(55);
    
    for (int i = 0; i < 1000; ++i) {
        int32_t val = dist(gen);
        EXPECT_GE(val, -1000);
        EXPECT_LE(val, 1000);
    }
}

// Test with uint32_t full range
TEST_F(UniformIntegerDistributionTest_1057, Uint32FullRange_1057) {
    Catch::uniform_integer_distribution<uint32_t> dist(0u, std::numeric_limits<uint32_t>::max());
    SimpleGenerator gen(1);
    
    for (int i = 0; i < 100; ++i) {
        uint32_t val = dist(gen);
        EXPECT_GE(val, 0u);
        EXPECT_LE(val, std::numeric_limits<uint32_t>::max());
    }
}

// Test with int range near limits
TEST_F(UniformIntegerDistributionTest_1057, IntNearMinMax_1057) {
    Catch::uniform_integer_distribution<int32_t> dist(
        std::numeric_limits<int32_t>::min(),
        std::numeric_limits<int32_t>::max()
    );
    SimpleGenerator gen(77);
    
    for (int i = 0; i < 100; ++i) {
        int32_t val = dist(gen);
        EXPECT_GE(val, std::numeric_limits<int32_t>::min());
        EXPECT_LE(val, std::numeric_limits<int32_t>::max());
    }
}

// Test a() and b() with zero bounds
TEST_F(UniformIntegerDistributionTest_1057, ZeroBounds_1057) {
    Catch::uniform_integer_distribution<int> dist(0, 0);
    EXPECT_EQ(dist.a(), 0);
    EXPECT_EQ(dist.b(), 0);
    
    SimpleGenerator gen(0);
    EXPECT_EQ(dist(gen), 0);
}

// Test with range of size 1
TEST_F(UniformIntegerDistributionTest_1057, RangeOfSizeOne_1057) {
    Catch::uniform_integer_distribution<int> dist(5, 6);
    SimpleGenerator gen(42);
    
    for (int i = 0; i < 100; ++i) {
        int val = dist(gen);
        EXPECT_GE(val, 5);
        EXPECT_LE(val, 6);
    }
}

// Test with int16_t
TEST_F(UniformIntegerDistributionTest_1057, Int16Type_1057) {
    Catch::uniform_integer_distribution<int16_t> dist(-100, 100);
    SimpleGenerator gen(33);
    
    for (int i = 0; i < 1000; ++i) {
        int16_t val = dist(gen);
        EXPECT_GE(val, -100);
        EXPECT_LE(val, 100);
    }
}

// Test with uint16_t
TEST_F(UniformIntegerDistributionTest_1057, Uint16Type_1057) {
    Catch::uniform_integer_distribution<uint16_t> dist(0, 1000);
    SimpleGenerator gen(44);
    
    for (int i = 0; i < 1000; ++i) {
        uint16_t val = dist(gen);
        EXPECT_GE(val, 0);
        EXPECT_LE(val, 1000);
    }
}

// Test with int64_t
TEST_F(UniformIntegerDistributionTest_1057, Int64Type_1057) {
    Catch::uniform_integer_distribution<int64_t> dist(-1000000LL, 1000000LL);
    SimpleGenerator64 gen(88);
    
    for (int i = 0; i < 1000; ++i) {
        int64_t val = dist(gen);
        EXPECT_GE(val, -1000000LL);
        EXPECT_LE(val, 1000000LL);
    }
}

// Test deterministic output: same seed gives same sequence
TEST_F(UniformIntegerDistributionTest_1057, DeterministicOutput_1057) {
    Catch::uniform_integer_distribution<int> dist(0, 1000);
    
    SimpleGenerator gen1(12345);
    SimpleGenerator gen2(12345);
    
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(dist(gen1), dist(gen2));
    }
}

// Test with large unsigned range
TEST_F(UniformIntegerDistributionTest_1057, LargeUnsignedRange_1057) {
    Catch::uniform_integer_distribution<uint32_t> dist(0, 1000000u);
    SimpleGenerator gen(1);
    
    for (int i = 0; i < 1000; ++i) {
        uint32_t val = dist(gen);
        EXPECT_GE(val, 0u);
        EXPECT_LE(val, 1000000u);
    }
}

// Test a() and b() with negative values
TEST_F(UniformIntegerDistributionTest_1057, NegativeBoundsAccessors_1057) {
    Catch::uniform_integer_distribution<int> dist(-200, -100);
    EXPECT_EQ(dist.a(), -200);
    EXPECT_EQ(dist.b(), -100);
}

// Test a() and b() with max int values
TEST_F(UniformIntegerDistributionTest_1057, MaxIntBoundsAccessors_1057) {
    Catch::uniform_integer_distribution<int32_t> dist(
        std::numeric_limits<int32_t>::min(),
        std::numeric_limits<int32_t>::max()
    );
    EXPECT_EQ(dist.a(), std::numeric_limits<int32_t>::min());
    EXPECT_EQ(dist.b(), std::numeric_limits<int32_t>::max());
}

// Test distribution produces varied values (not all the same) for non-trivial range
TEST_F(UniformIntegerDistributionTest_1057, ProducesVariedValues_1057) {
    Catch::uniform_integer_distribution<int> dist(0, 1000);
    SimpleGenerator gen(42);
    
    int first = dist(gen);
    bool foundDifferent = false;
    for (int i = 0; i < 100; ++i) {
        if (dist(gen) != first) {
            foundDifferent = true;
            break;
        }
    }
    EXPECT_TRUE(foundDifferent);
}
