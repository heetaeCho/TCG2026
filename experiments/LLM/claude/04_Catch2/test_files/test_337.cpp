#include "catch2/internal/catch_uniform_integer_distribution.hpp"
#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include <type_traits>

// A simple deterministic generator for testing
struct SimpleGenerator {
    using result_type = uint32_t;
    uint32_t value;
    
    constexpr SimpleGenerator(uint32_t v) : value(v) {}
    
    constexpr result_type operator()() { return value; }
    
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return std::numeric_limits<uint32_t>::max(); }
};

// A generator that cycles through values
struct CyclingGenerator {
    using result_type = uint32_t;
    uint32_t current;
    uint32_t increment;
    
    CyclingGenerator(uint32_t start, uint32_t inc = 1) : current(start), increment(inc) {}
    
    result_type operator()() {
        uint32_t ret = current;
        current += increment;
        return ret;
    }
    
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return std::numeric_limits<uint32_t>::max(); }
};

// A generator for 64-bit types
struct SimpleGenerator64 {
    using result_type = uint64_t;
    uint64_t value;
    
    constexpr SimpleGenerator64(uint64_t v) : value(v) {}
    
    constexpr result_type operator()() { return value; }
    
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return std::numeric_limits<uint64_t>::max(); }
};

class UniformIntegerDistributionTest_337 : public ::testing::Test {};

// Test that a() returns the lower bound for int type
TEST_F(UniformIntegerDistributionTest_337, AReturnsLowerBound_337) {
    Catch::uniform_integer_distribution<int> dist(3, 10);
    EXPECT_EQ(dist.a(), 3);
}

// Test that b() returns the upper bound for int type
TEST_F(UniformIntegerDistributionTest_337, BReturnsUpperBound_337) {
    Catch::uniform_integer_distribution<int> dist(3, 10);
    EXPECT_EQ(dist.b(), 10);
}

// Test with zero range (a == b)
TEST_F(UniformIntegerDistributionTest_337, SingleValueRange_337) {
    Catch::uniform_integer_distribution<int> dist(5, 5);
    EXPECT_EQ(dist.a(), 5);
    EXPECT_EQ(dist.b(), 5);
}

// Test that single value range always returns that value
TEST_F(UniformIntegerDistributionTest_337, SingleValueRangeAlwaysReturnsSameValue_337) {
    Catch::uniform_integer_distribution<int> dist(42, 42);
    SimpleGenerator gen(0);
    EXPECT_EQ(dist(gen), 42);
    
    SimpleGenerator gen2(std::numeric_limits<uint32_t>::max());
    EXPECT_EQ(dist(gen2), 42);
}

// Test with negative range
TEST_F(UniformIntegerDistributionTest_337, NegativeRange_337) {
    Catch::uniform_integer_distribution<int> dist(-10, -3);
    EXPECT_EQ(dist.a(), -10);
    EXPECT_EQ(dist.b(), -3);
}

// Test with range crossing zero
TEST_F(UniformIntegerDistributionTest_337, RangeCrossingZero_337) {
    Catch::uniform_integer_distribution<int> dist(-5, 5);
    EXPECT_EQ(dist.a(), -5);
    EXPECT_EQ(dist.b(), 5);
}

// Test with unsigned int type
TEST_F(UniformIntegerDistributionTest_337, UnsignedIntType_337) {
    Catch::uniform_integer_distribution<unsigned int> dist(0, 100);
    EXPECT_EQ(dist.a(), 0u);
    EXPECT_EQ(dist.b(), 100u);
}

// Test generated values are within range for int
TEST_F(UniformIntegerDistributionTest_337, GeneratedValueInRange_337) {
    Catch::uniform_integer_distribution<int> dist(1, 6);
    SimpleGenerator gen(0);
    int result = dist(gen);
    EXPECT_GE(result, 1);
    EXPECT_LE(result, 6);
}

// Test generated values are within range for negative range
TEST_F(UniformIntegerDistributionTest_337, GeneratedValueInNegativeRange_337) {
    Catch::uniform_integer_distribution<int> dist(-100, -50);
    SimpleGenerator gen(12345);
    int result = dist(gen);
    EXPECT_GE(result, -100);
    EXPECT_LE(result, -50);
}

// Test generated values are within range with max generator value
TEST_F(UniformIntegerDistributionTest_337, GeneratedValueInRangeMaxGenerator_337) {
    Catch::uniform_integer_distribution<int> dist(0, 10);
    SimpleGenerator gen(std::numeric_limits<uint32_t>::max());
    int result = dist(gen);
    EXPECT_GE(result, 0);
    EXPECT_LE(result, 10);
}

// Test generated values are within range with min generator value
TEST_F(UniformIntegerDistributionTest_337, GeneratedValueInRangeMinGenerator_337) {
    Catch::uniform_integer_distribution<int> dist(0, 10);
    SimpleGenerator gen(0);
    int result = dist(gen);
    EXPECT_GE(result, 0);
    EXPECT_LE(result, 10);
}

// Test with full int range
TEST_F(UniformIntegerDistributionTest_337, FullIntRange_337) {
    Catch::uniform_integer_distribution<int> dist(
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::max()
    );
    EXPECT_EQ(dist.a(), std::numeric_limits<int>::min());
    EXPECT_EQ(dist.b(), std::numeric_limits<int>::max());
}

// Test full int range generates valid values
TEST_F(UniformIntegerDistributionTest_337, FullIntRangeGeneratesValid_337) {
    Catch::uniform_integer_distribution<int> dist(
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::max()
    );
    SimpleGenerator gen(42);
    int result = dist(gen);
    EXPECT_GE(result, std::numeric_limits<int>::min());
    EXPECT_LE(result, std::numeric_limits<int>::max());
}

// Test with int16_t type
TEST_F(UniformIntegerDistributionTest_337, Int16Type_337) {
    Catch::uniform_integer_distribution<int16_t> dist(-100, 100);
    EXPECT_EQ(dist.a(), -100);
    EXPECT_EQ(dist.b(), 100);
}

// Test with uint32_t type
TEST_F(UniformIntegerDistributionTest_337, Uint32Type_337) {
    Catch::uniform_integer_distribution<uint32_t> dist(0, 1000);
    EXPECT_EQ(dist.a(), 0u);
    EXPECT_EQ(dist.b(), 1000u);
}

// Test with int64_t type
TEST_F(UniformIntegerDistributionTest_337, Int64Type_337) {
    Catch::uniform_integer_distribution<int64_t> dist(-1000000LL, 1000000LL);
    EXPECT_EQ(dist.a(), -1000000LL);
    EXPECT_EQ(dist.b(), 1000000LL);
}

// Test multiple calls produce values in range
TEST_F(UniformIntegerDistributionTest_337, MultipleCallsInRange_337) {
    Catch::uniform_integer_distribution<int> dist(1, 100);
    CyclingGenerator gen(0, 7919); // prime increment for variety
    
    for (int i = 0; i < 100; ++i) {
        int result = dist(gen);
        EXPECT_GE(result, 1) << "Failed on iteration " << i;
        EXPECT_LE(result, 100) << "Failed on iteration " << i;
    }
}

// Test range of size 2
TEST_F(UniformIntegerDistributionTest_337, RangeOfTwo_337) {
    Catch::uniform_integer_distribution<int> dist(0, 1);
    EXPECT_EQ(dist.a(), 0);
    EXPECT_EQ(dist.b(), 1);
    
    SimpleGenerator gen(0);
    int result = dist(gen);
    EXPECT_GE(result, 0);
    EXPECT_LE(result, 1);
}

// Test with zero as both bounds
TEST_F(UniformIntegerDistributionTest_337, ZeroBothBounds_337) {
    Catch::uniform_integer_distribution<int> dist(0, 0);
    EXPECT_EQ(dist.a(), 0);
    EXPECT_EQ(dist.b(), 0);
    
    SimpleGenerator gen(999);
    EXPECT_EQ(dist(gen), 0);
}

// Test with large unsigned range
TEST_F(UniformIntegerDistributionTest_337, LargeUnsignedRange_337) {
    Catch::uniform_integer_distribution<uint32_t> dist(0, std::numeric_limits<uint32_t>::max());
    EXPECT_EQ(dist.a(), 0u);
    EXPECT_EQ(dist.b(), std::numeric_limits<uint32_t>::max());
}

// Test int range with min value as lower bound
TEST_F(UniformIntegerDistributionTest_337, IntMinAsLowerBound_337) {
    Catch::uniform_integer_distribution<int> dist(std::numeric_limits<int>::min(), 0);
    EXPECT_EQ(dist.a(), std::numeric_limits<int>::min());
    EXPECT_EQ(dist.b(), 0);
}

// Test int range with max value as upper bound
TEST_F(UniformIntegerDistributionTest_337, IntMaxAsUpperBound_337) {
    Catch::uniform_integer_distribution<int> dist(0, std::numeric_limits<int>::max());
    EXPECT_EQ(dist.a(), 0);
    EXPECT_EQ(dist.b(), std::numeric_limits<int>::max());
}

// Test that values in crossing-zero range are within bounds
TEST_F(UniformIntegerDistributionTest_337, CrossingZeroRangeMultipleCalls_337) {
    Catch::uniform_integer_distribution<int> dist(-50, 50);
    CyclingGenerator gen(100, 1000003);
    
    for (int i = 0; i < 50; ++i) {
        int result = dist(gen);
        EXPECT_GE(result, -50) << "Failed on iteration " << i;
        EXPECT_LE(result, 50) << "Failed on iteration " << i;
    }
}

// Test with int8_t type and small range
TEST_F(UniformIntegerDistributionTest_337, Int8SmallRange_337) {
    Catch::uniform_integer_distribution<int8_t> dist(-1, 1);
    EXPECT_EQ(dist.a(), -1);
    EXPECT_EQ(dist.b(), 1);
}

// Test with int8_t type full range
TEST_F(UniformIntegerDistributionTest_337, Int8FullRange_337) {
    Catch::uniform_integer_distribution<int8_t> dist(
        std::numeric_limits<int8_t>::min(),
        std::numeric_limits<int8_t>::max()
    );
    EXPECT_EQ(dist.a(), std::numeric_limits<int8_t>::min());
    EXPECT_EQ(dist.b(), std::numeric_limits<int8_t>::max());
}

// Test constexpr construction
TEST_F(UniformIntegerDistributionTest_337, ConstexprConstruction_337) {
    constexpr Catch::uniform_integer_distribution<int> dist(1, 10);
    static_assert(dist.a() == 1, "a() should be constexpr");
    static_assert(dist.b() == 10, "b() should be constexpr");
    EXPECT_EQ(dist.a(), 1);
    EXPECT_EQ(dist.b(), 10);
}

// Test adjacent values (range of 1 difference)
TEST_F(UniformIntegerDistributionTest_337, AdjacentValues_337) {
    Catch::uniform_integer_distribution<int> dist(99, 100);
    EXPECT_EQ(dist.a(), 99);
    EXPECT_EQ(dist.b(), 100);
    
    CyclingGenerator gen(0, 1);
    for (int i = 0; i < 20; ++i) {
        int result = dist(gen);
        EXPECT_GE(result, 99);
        EXPECT_LE(result, 100);
    }
}

// Test negative adjacent values
TEST_F(UniformIntegerDistributionTest_337, NegativeAdjacentValues_337) {
    Catch::uniform_integer_distribution<int> dist(-2, -1);
    EXPECT_EQ(dist.a(), -2);
    EXPECT_EQ(dist.b(), -1);
}

// Test power of two range
TEST_F(UniformIntegerDistributionTest_337, PowerOfTwoRange_337) {
    // Range of exactly 256 values (0 to 255)
    Catch::uniform_integer_distribution<int> dist(0, 255);
    EXPECT_EQ(dist.a(), 0);
    EXPECT_EQ(dist.b(), 255);
    
    CyclingGenerator gen(0, 99991);
    for (int i = 0; i < 100; ++i) {
        int result = dist(gen);
        EXPECT_GE(result, 0);
        EXPECT_LE(result, 255);
    }
}

// Test uint16_t type
TEST_F(UniformIntegerDistributionTest_337, Uint16Type_337) {
    Catch::uniform_integer_distribution<uint16_t> dist(0, 65535);
    EXPECT_EQ(dist.a(), 0);
    EXPECT_EQ(dist.b(), 65535);
}
