#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <limits>
#include <vector>

#include "catch2/internal/catch_uniform_integer_distribution.hpp"

// A simple deterministic generator that returns values from a predefined sequence
class MockGenerator {
public:
    using result_type = uint32_t;

    explicit MockGenerator(std::vector<uint32_t> values)
        : m_values(std::move(values)), m_index(0) {}

    MockGenerator(uint32_t fixed_value)
        : m_values({fixed_value}), m_index(0), m_repeat(true) {}

    constexpr result_type operator()() {
        if (m_repeat) {
            return m_values[0];
        }
        if (m_index < m_values.size()) {
            return m_values[m_index++];
        }
        return m_values.back();
    }

    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return std::numeric_limits<uint32_t>::max(); }

private:
    std::vector<uint32_t> m_values;
    size_t m_index;
    bool m_repeat = false;
};

// A generator for 64-bit results
class MockGenerator64 {
public:
    using result_type = uint64_t;

    explicit MockGenerator64(uint64_t fixed_value)
        : m_value(fixed_value) {}

    constexpr result_type operator()() {
        return m_value;
    }

    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return std::numeric_limits<uint64_t>::max(); }

private:
    uint64_t m_value;
};

class UniformIntegerDistributionTest_336 : public ::testing::Test {
protected:
};

// Test that a() and b() return the correct bounds for int distribution
TEST_F(UniformIntegerDistributionTest_336, ConstructorStoresBounds_336) {
    Catch::uniform_integer_distribution<int> dist(3, 10);
    EXPECT_EQ(dist.a(), 3);
    EXPECT_EQ(dist.b(), 10);
}

// Test that a() and b() return the correct bounds when a == b
TEST_F(UniformIntegerDistributionTest_336, SameMinMax_336) {
    Catch::uniform_integer_distribution<int> dist(5, 5);
    EXPECT_EQ(dist.a(), 5);
    EXPECT_EQ(dist.b(), 5);
}

// Test with zero distance (a == b), the result should always be that value
TEST_F(UniformIntegerDistributionTest_336, ZeroDistanceAlwaysReturnsSameValue_336) {
    Catch::uniform_integer_distribution<int> dist(42, 42);
    MockGenerator gen(12345u);
    
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(dist(gen), 42);
    }
}

// Test that generated values are within range [a, b]
TEST_F(UniformIntegerDistributionTest_336, GeneratedValuesWithinRange_336) {
    Catch::uniform_integer_distribution<int> dist(0, 100);
    MockGenerator gen(std::vector<uint32_t>{0u, 1000u, 500000u, 
        std::numeric_limits<uint32_t>::max(), 
        std::numeric_limits<uint32_t>::max() / 2});
    
    for (int i = 0; i < 5; ++i) {
        int val = dist(gen);
        EXPECT_GE(val, 0);
        EXPECT_LE(val, 100);
    }
}

// Test with negative range
TEST_F(UniformIntegerDistributionTest_336, NegativeRange_336) {
    Catch::uniform_integer_distribution<int> dist(-10, -1);
    EXPECT_EQ(dist.a(), -10);
    EXPECT_EQ(dist.b(), -1);
    
    MockGenerator gen(std::numeric_limits<uint32_t>::max() / 2);
    int val = dist(gen);
    EXPECT_GE(val, -10);
    EXPECT_LE(val, -1);
}

// Test with range spanning negative to positive
TEST_F(UniformIntegerDistributionTest_336, NegativeToPositiveRange_336) {
    Catch::uniform_integer_distribution<int> dist(-50, 50);
    EXPECT_EQ(dist.a(), -50);
    EXPECT_EQ(dist.b(), 50);
    
    MockGenerator gen(std::numeric_limits<uint32_t>::max() / 2);
    int val = dist(gen);
    EXPECT_GE(val, -50);
    EXPECT_LE(val, 50);
}

// Test with unsigned integer type
TEST_F(UniformIntegerDistributionTest_336, UnsignedIntegerType_336) {
    Catch::uniform_integer_distribution<unsigned int> dist(0u, 1000u);
    EXPECT_EQ(dist.a(), 0u);
    EXPECT_EQ(dist.b(), 1000u);
    
    MockGenerator gen(42u);
    unsigned int val = dist(gen);
    EXPECT_GE(val, 0u);
    EXPECT_LE(val, 1000u);
}

// Test with generator returning 0
TEST_F(UniformIntegerDistributionTest_336, GeneratorReturnsZero_336) {
    Catch::uniform_integer_distribution<int> dist(0, 100);
    MockGenerator gen(0u);
    int val = dist(gen);
    EXPECT_GE(val, 0);
    EXPECT_LE(val, 100);
}

// Test with generator returning max
TEST_F(UniformIntegerDistributionTest_336, GeneratorReturnsMax_336) {
    Catch::uniform_integer_distribution<int> dist(0, 100);
    MockGenerator gen(std::numeric_limits<uint32_t>::max());
    int val = dist(gen);
    EXPECT_GE(val, 0);
    EXPECT_LE(val, 100);
}

// Test full range of int
TEST_F(UniformIntegerDistributionTest_336, FullIntRange_336) {
    Catch::uniform_integer_distribution<int> dist(
        std::numeric_limits<int>::min(), 
        std::numeric_limits<int>::max());
    EXPECT_EQ(dist.a(), std::numeric_limits<int>::min());
    EXPECT_EQ(dist.b(), std::numeric_limits<int>::max());
    
    MockGenerator gen(12345u);
    // Should not crash and should return a valid int
    int val = dist(gen);
    EXPECT_GE(val, std::numeric_limits<int>::min());
    EXPECT_LE(val, std::numeric_limits<int>::max());
}

// Test with range of size 1 (a == b)
TEST_F(UniformIntegerDistributionTest_336, RangeOfSizeOne_336) {
    Catch::uniform_integer_distribution<int> dist(0, 0);
    MockGenerator gen(999u);
    EXPECT_EQ(dist(gen), 0);
}

// Test with range [0, 1]
TEST_F(UniformIntegerDistributionTest_336, BinaryRange_336) {
    Catch::uniform_integer_distribution<int> dist(0, 1);
    EXPECT_EQ(dist.a(), 0);
    EXPECT_EQ(dist.b(), 1);
    
    MockGenerator gen(0u);
    int val = dist(gen);
    EXPECT_GE(val, 0);
    EXPECT_LE(val, 1);
}

// Test multiple calls produce values in range
TEST_F(UniformIntegerDistributionTest_336, MultipleCallsInRange_336) {
    Catch::uniform_integer_distribution<int> dist(10, 20);
    std::vector<uint32_t> sequence;
    for (uint32_t i = 0; i < 50; ++i) {
        sequence.push_back(i * 100000000u);
    }
    MockGenerator gen(std::move(sequence));
    
    for (int i = 0; i < 50; ++i) {
        int val = dist(gen);
        EXPECT_GE(val, 10);
        EXPECT_LE(val, 20);
    }
}

// Test with int16_t type
TEST_F(UniformIntegerDistributionTest_336, ShortIntegerType_336) {
    Catch::uniform_integer_distribution<int16_t> dist(-100, 100);
    EXPECT_EQ(dist.a(), -100);
    EXPECT_EQ(dist.b(), 100);
    
    MockGenerator gen(std::numeric_limits<uint32_t>::max() / 3);
    int16_t val = dist(gen);
    EXPECT_GE(val, -100);
    EXPECT_LE(val, 100);
}

// Test with int64_t type
TEST_F(UniformIntegerDistributionTest_336, Int64Type_336) {
    Catch::uniform_integer_distribution<int64_t> dist(0, 1000000);
    EXPECT_EQ(dist.a(), 0);
    EXPECT_EQ(dist.b(), 1000000);
    
    MockGenerator64 gen(std::numeric_limits<uint64_t>::max() / 2);
    int64_t val = dist(gen);
    EXPECT_GE(val, 0);
    EXPECT_LE(val, 1000000);
}

// Test boundary: min int to 0
TEST_F(UniformIntegerDistributionTest_336, MinIntToZero_336) {
    Catch::uniform_integer_distribution<int> dist(std::numeric_limits<int>::min(), 0);
    EXPECT_EQ(dist.a(), std::numeric_limits<int>::min());
    EXPECT_EQ(dist.b(), 0);
    
    MockGenerator gen(12345u);
    int val = dist(gen);
    EXPECT_GE(val, std::numeric_limits<int>::min());
    EXPECT_LE(val, 0);
}

// Test boundary: 0 to max int
TEST_F(UniformIntegerDistributionTest_336, ZeroToMaxInt_336) {
    Catch::uniform_integer_distribution<int> dist(0, std::numeric_limits<int>::max());
    EXPECT_EQ(dist.a(), 0);
    EXPECT_EQ(dist.b(), std::numeric_limits<int>::max());
    
    MockGenerator gen(12345u);
    int val = dist(gen);
    EXPECT_GE(val, 0);
    EXPECT_LE(val, std::numeric_limits<int>::max());
}

// Test that the same generator value produces the same result (determinism)
TEST_F(UniformIntegerDistributionTest_336, DeterministicOutput_336) {
    Catch::uniform_integer_distribution<int> dist1(0, 100);
    Catch::uniform_integer_distribution<int> dist2(0, 100);
    
    MockGenerator gen1(42u);
    MockGenerator gen2(42u);
    
    EXPECT_EQ(dist1(gen1), dist2(gen2));
}

// Test with uint8_t
TEST_F(UniformIntegerDistributionTest_336, Uint8Type_336) {
    Catch::uniform_integer_distribution<uint8_t> dist(0, 255);
    EXPECT_EQ(dist.a(), 0);
    EXPECT_EQ(dist.b(), 255);
    
    MockGenerator gen(12345u);
    uint8_t val = dist(gen);
    // Any uint8_t value is valid for full range
    EXPECT_GE(val, 0);
    EXPECT_LE(val, 255);
}

// Test with single value negative
TEST_F(UniformIntegerDistributionTest_336, SingleNegativeValue_336) {
    Catch::uniform_integer_distribution<int> dist(-1, -1);
    MockGenerator gen(99999u);
    EXPECT_EQ(dist(gen), -1);
}

// Test with int8_t full range
TEST_F(UniformIntegerDistributionTest_336, Int8FullRange_336) {
    Catch::uniform_integer_distribution<int8_t> dist(-128, 127);
    EXPECT_EQ(dist.a(), -128);
    EXPECT_EQ(dist.b(), 127);
    
    MockGenerator gen(std::numeric_limits<uint32_t>::max());
    int8_t val = dist(gen);
    EXPECT_GE(val, -128);
    EXPECT_LE(val, 127);
}
