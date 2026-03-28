#include "catch2/internal/catch_uniform_integer_distribution.hpp"
#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include <type_traits>

// A simple deterministic generator for testing
struct MockGenerator {
    using result_type = uint32_t;
    uint32_t value;
    
    constexpr MockGenerator(uint32_t v) : value(v) {}
    
    constexpr result_type operator()() { return value; }
    
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return std::numeric_limits<uint32_t>::max(); }
};

struct MockGenerator64 {
    using result_type = uint64_t;
    uint64_t value;
    
    constexpr MockGenerator64(uint64_t v) : value(v) {}
    
    constexpr result_type operator()() { return value; }
    
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return std::numeric_limits<uint64_t>::max(); }
};

// Test fixture for int type
class UniformIntegerDistributionIntTest_338 : public ::testing::Test {};

// Test fixture for unsigned type
class UniformIntegerDistributionUnsignedTest_338 : public ::testing::Test {};

// Test fixture for signed types with negative ranges
class UniformIntegerDistributionSignedTest_338 : public ::testing::Test {};

// ========== Tests for a() and b() accessors ==========

TEST_F(UniformIntegerDistributionIntTest_338, ConstructorSetsAAndB_338) {
    Catch::uniform_integer_distribution<int> dist(3, 10);
    EXPECT_EQ(dist.a(), 3);
    EXPECT_EQ(dist.b(), 10);
}

TEST_F(UniformIntegerDistributionIntTest_338, SingleValueRange_338) {
    Catch::uniform_integer_distribution<int> dist(5, 5);
    EXPECT_EQ(dist.a(), 5);
    EXPECT_EQ(dist.b(), 5);
}

TEST_F(UniformIntegerDistributionIntTest_338, ZeroRange_338) {
    Catch::uniform_integer_distribution<int> dist(0, 0);
    EXPECT_EQ(dist.a(), 0);
    EXPECT_EQ(dist.b(), 0);
}

TEST_F(UniformIntegerDistributionIntTest_338, NegativeRange_338) {
    Catch::uniform_integer_distribution<int> dist(-10, -3);
    EXPECT_EQ(dist.a(), -10);
    EXPECT_EQ(dist.b(), -3);
}

TEST_F(UniformIntegerDistributionIntTest_338, NegativeToPositiveRange_338) {
    Catch::uniform_integer_distribution<int> dist(-5, 5);
    EXPECT_EQ(dist.a(), -5);
    EXPECT_EQ(dist.b(), 5);
}

TEST_F(UniformIntegerDistributionIntTest_338, ZeroToPositive_338) {
    Catch::uniform_integer_distribution<int> dist(0, 100);
    EXPECT_EQ(dist.a(), 0);
    EXPECT_EQ(dist.b(), 100);
}

TEST_F(UniformIntegerDistributionIntTest_338, NegativeToZero_338) {
    Catch::uniform_integer_distribution<int> dist(-100, 0);
    EXPECT_EQ(dist.a(), -100);
    EXPECT_EQ(dist.b(), 0);
}

// ========== Tests with unsigned int type ==========

TEST_F(UniformIntegerDistributionUnsignedTest_338, UnsignedBasicRange_338) {
    Catch::uniform_integer_distribution<unsigned int> dist(0, 10);
    EXPECT_EQ(dist.a(), 0u);
    EXPECT_EQ(dist.b(), 10u);
}

TEST_F(UniformIntegerDistributionUnsignedTest_338, UnsignedSingleValue_338) {
    Catch::uniform_integer_distribution<unsigned int> dist(7, 7);
    EXPECT_EQ(dist.a(), 7u);
    EXPECT_EQ(dist.b(), 7u);
}

TEST_F(UniformIntegerDistributionUnsignedTest_338, UnsignedLargeRange_338) {
    Catch::uniform_integer_distribution<unsigned int> dist(0, std::numeric_limits<unsigned int>::max());
    EXPECT_EQ(dist.a(), 0u);
    EXPECT_EQ(dist.b(), std::numeric_limits<unsigned int>::max());
}

// ========== Tests for operator() generating values in range ==========

TEST_F(UniformIntegerDistributionIntTest_338, GeneratedValueInRange_338) {
    Catch::uniform_integer_distribution<int> dist(1, 6);
    MockGenerator gen(42);
    
    int result = dist(gen);
    EXPECT_GE(result, 1);
    EXPECT_LE(result, 6);
}

TEST_F(UniformIntegerDistributionIntTest_338, SingleValueAlwaysReturnsSame_338) {
    Catch::uniform_integer_distribution<int> dist(42, 42);
    MockGenerator gen(0);
    
    int result = dist(gen);
    EXPECT_EQ(result, 42);
}

TEST_F(UniformIntegerDistributionIntTest_338, SingleValueAlwaysReturnsSameWithMaxGen_338) {
    Catch::uniform_integer_distribution<int> dist(42, 42);
    MockGenerator gen(std::numeric_limits<uint32_t>::max());
    
    int result = dist(gen);
    EXPECT_EQ(result, 42);
}

TEST_F(UniformIntegerDistributionIntTest_338, NegativeRangeGeneratedValueInRange_338) {
    Catch::uniform_integer_distribution<int> dist(-10, -1);
    MockGenerator gen(123456789);
    
    int result = dist(gen);
    EXPECT_GE(result, -10);
    EXPECT_LE(result, -1);
}

TEST_F(UniformIntegerDistributionIntTest_338, CrossZeroRangeGeneratedValueInRange_338) {
    Catch::uniform_integer_distribution<int> dist(-5, 5);
    MockGenerator gen(999999);
    
    int result = dist(gen);
    EXPECT_GE(result, -5);
    EXPECT_LE(result, 5);
}

TEST_F(UniformIntegerDistributionUnsignedTest_338, UnsignedGeneratedValueInRange_338) {
    Catch::uniform_integer_distribution<unsigned int> dist(10, 20);
    MockGenerator gen(500);
    
    unsigned int result = dist(gen);
    EXPECT_GE(result, 10u);
    EXPECT_LE(result, 20u);
}

TEST_F(UniformIntegerDistributionUnsignedTest_338, UnsignedZeroSingleValue_338) {
    Catch::uniform_integer_distribution<unsigned int> dist(0, 0);
    MockGenerator gen(12345);
    
    unsigned int result = dist(gen);
    EXPECT_EQ(result, 0u);
}

// ========== Tests with various generator values to check range compliance ==========

TEST_F(UniformIntegerDistributionIntTest_338, GeneratedWithMinGenerator_338) {
    Catch::uniform_integer_distribution<int> dist(0, 100);
    MockGenerator gen(0);
    
    int result = dist(gen);
    EXPECT_GE(result, 0);
    EXPECT_LE(result, 100);
}

TEST_F(UniformIntegerDistributionIntTest_338, GeneratedWithMaxGenerator_338) {
    Catch::uniform_integer_distribution<int> dist(0, 100);
    MockGenerator gen(std::numeric_limits<uint32_t>::max());
    
    int result = dist(gen);
    EXPECT_GE(result, 0);
    EXPECT_LE(result, 100);
}

TEST_F(UniformIntegerDistributionIntTest_338, GeneratedWithMidGenerator_338) {
    Catch::uniform_integer_distribution<int> dist(0, 100);
    MockGenerator gen(std::numeric_limits<uint32_t>::max() / 2);
    
    int result = dist(gen);
    EXPECT_GE(result, 0);
    EXPECT_LE(result, 100);
}

// ========== Boundary tests for integer limits ==========

TEST_F(UniformIntegerDistributionSignedTest_338, IntMinToIntMax_338) {
    Catch::uniform_integer_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    EXPECT_EQ(dist.a(), std::numeric_limits<int>::min());
    EXPECT_EQ(dist.b(), std::numeric_limits<int>::max());
    
    MockGenerator gen(0);
    int result = dist(gen);
    EXPECT_GE(result, std::numeric_limits<int>::min());
    EXPECT_LE(result, std::numeric_limits<int>::max());
}

TEST_F(UniformIntegerDistributionSignedTest_338, IntMinOnly_338) {
    Catch::uniform_integer_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::min());
    EXPECT_EQ(dist.a(), std::numeric_limits<int>::min());
    EXPECT_EQ(dist.b(), std::numeric_limits<int>::min());
    
    MockGenerator gen(12345);
    int result = dist(gen);
    EXPECT_EQ(result, std::numeric_limits<int>::min());
}

TEST_F(UniformIntegerDistributionSignedTest_338, IntMaxOnly_338) {
    Catch::uniform_integer_distribution<int> dist(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
    EXPECT_EQ(dist.a(), std::numeric_limits<int>::max());
    EXPECT_EQ(dist.b(), std::numeric_limits<int>::max());
    
    MockGenerator gen(12345);
    int result = dist(gen);
    EXPECT_EQ(result, std::numeric_limits<int>::max());
}

// ========== Tests with different integer types ==========

TEST_F(UniformIntegerDistributionIntTest_338, ShortType_338) {
    Catch::uniform_integer_distribution<short> dist(-100, 100);
    EXPECT_EQ(dist.a(), static_cast<short>(-100));
    EXPECT_EQ(dist.b(), static_cast<short>(100));
}

TEST_F(UniformIntegerDistributionIntTest_338, Int64Type_338) {
    Catch::uniform_integer_distribution<int64_t> dist(-1000000LL, 1000000LL);
    EXPECT_EQ(dist.a(), -1000000LL);
    EXPECT_EQ(dist.b(), 1000000LL);
}

TEST_F(UniformIntegerDistributionIntTest_338, Uint64Type_338) {
    Catch::uniform_integer_distribution<uint64_t> dist(0, 1000000ULL);
    EXPECT_EQ(dist.a(), 0ULL);
    EXPECT_EQ(dist.b(), 1000000ULL);
}

// ========== Multiple calls should always be in range ==========

TEST_F(UniformIntegerDistributionIntTest_338, MultipleCallsInRange_338) {
    Catch::uniform_integer_distribution<int> dist(1, 10);
    
    // Test with various generator values
    for (uint32_t v = 0; v < 1000; v += 7) {
        MockGenerator gen(v);
        int result = dist(gen);
        EXPECT_GE(result, 1) << "Failed with generator value " << v;
        EXPECT_LE(result, 10) << "Failed with generator value " << v;
    }
}

TEST_F(UniformIntegerDistributionIntTest_338, SmallRangeMultipleCalls_338) {
    Catch::uniform_integer_distribution<int> dist(0, 1);
    
    for (uint32_t v = 0; v < 100; ++v) {
        MockGenerator gen(v);
        int result = dist(gen);
        EXPECT_GE(result, 0);
        EXPECT_LE(result, 1);
    }
}

// ========== Test result_type ==========

TEST_F(UniformIntegerDistributionIntTest_338, ResultTypeMatchesIntegerType_338) {
    using DistType = Catch::uniform_integer_distribution<int>;
    static_assert(std::is_same<DistType::result_type, int>::value, "result_type should match IntegerType");
}

TEST_F(UniformIntegerDistributionUnsignedTest_338, ResultTypeMatchesUnsignedType_338) {
    using DistType = Catch::uniform_integer_distribution<unsigned int>;
    static_assert(std::is_same<DistType::result_type, unsigned int>::value, "result_type should match IntegerType");
}

// ========== Test with int64 and 64-bit generator ==========

TEST_F(UniformIntegerDistributionIntTest_338, Int64WithGen64InRange_338) {
    Catch::uniform_integer_distribution<int64_t> dist(-1000000000LL, 1000000000LL);
    MockGenerator64 gen(999999999ULL);
    
    int64_t result = dist(gen);
    EXPECT_GE(result, -1000000000LL);
    EXPECT_LE(result, 1000000000LL);
}

// ========== Edge case: range of 2 ==========

TEST_F(UniformIntegerDistributionIntTest_338, RangeOfTwo_338) {
    Catch::uniform_integer_distribution<int> dist(0, 1);
    
    MockGenerator gen0(0);
    int r0 = dist(gen0);
    EXPECT_GE(r0, 0);
    EXPECT_LE(r0, 1);
    
    MockGenerator genMax(std::numeric_limits<uint32_t>::max());
    int rMax = dist(genMax);
    EXPECT_GE(rMax, 0);
    EXPECT_LE(rMax, 1);
}

// ========== Power of 2 range ==========

TEST_F(UniformIntegerDistributionIntTest_338, PowerOfTwoRange_338) {
    Catch::uniform_integer_distribution<int> dist(0, 255);
    EXPECT_EQ(dist.a(), 0);
    EXPECT_EQ(dist.b(), 255);
    
    MockGenerator gen(12345);
    int result = dist(gen);
    EXPECT_GE(result, 0);
    EXPECT_LE(result, 255);
}

TEST_F(UniformIntegerDistributionIntTest_338, PowerOfTwoMinusOneRange_338) {
    Catch::uniform_integer_distribution<int> dist(0, 127);
    EXPECT_EQ(dist.a(), 0);
    EXPECT_EQ(dist.b(), 127);
    
    MockGenerator gen(54321);
    int result = dist(gen);
    EXPECT_GE(result, 0);
    EXPECT_LE(result, 127);
}
