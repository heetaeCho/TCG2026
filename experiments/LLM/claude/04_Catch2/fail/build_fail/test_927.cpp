#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>

#include <gtest/gtest.h>
#include <vector>
#include <memory>

// We need to include the amalgamated header for RepeatGenerator
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Generators;

// Helper: create a simple generator that yields values from a fixed list
template <typename T>
class FixedValuesGenerator : public IGenerator<T> {
    std::vector<T> m_values;
    size_t m_index = 0;
public:
    FixedValuesGenerator(std::vector<T> values) : m_values(std::move(values)) {
        assert(!m_values.empty());
    }
    
    T const& get() const override {
        return m_values[m_index];
    }
    
    bool next() override {
        ++m_index;
        return m_index < m_values.size();
    }
};

template <typename T>
GeneratorWrapper<T> fixedValues(std::vector<T> values) {
    return GeneratorWrapper<T>(
        Catch::Detail::make_unique<FixedValuesGenerator<T>>(std::move(values))
    );
}

class RepeatGeneratorTest_927 : public ::testing::Test {
protected:
};

TEST_F(RepeatGeneratorTest_927, SingleValueRepeatedOnce_927) {
    // A generator with a single value, repeated 1 time
    auto gen = RepeatGenerator<int>(1, fixedValues<int>({42}));
    
    // First call to get() should return 42
    EXPECT_EQ(gen.get(), 42);
    
    // next() should return false since we only repeat once and there's only one value
    EXPECT_FALSE(gen.next());
}

TEST_F(RepeatGeneratorTest_927, SingleValueRepeatedMultipleTimes_927) {
    // A single value repeated 3 times
    auto gen = RepeatGenerator<int>(3, fixedValues<int>({42}));
    
    EXPECT_EQ(gen.get(), 42);
    
    // After first value, next should advance to repeat 1
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 42);
    
    // Advance to repeat 2
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 42);
    
    // No more repeats
    EXPECT_FALSE(gen.next());
}

TEST_F(RepeatGeneratorTest_927, MultipleValuesRepeatedOnce_927) {
    // Multiple values, repeated once (just pass through)
    auto gen = RepeatGenerator<int>(1, fixedValues<int>({1, 2, 3}));
    
    EXPECT_EQ(gen.get(), 1);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    
    EXPECT_FALSE(gen.next());
}

TEST_F(RepeatGeneratorTest_927, MultipleValuesRepeatedMultipleTimes_927) {
    // Values {10, 20} repeated 3 times -> should yield 10,20,10,20,10,20
    auto gen = RepeatGenerator<int>(3, fixedValues<int>({10, 20}));
    
    std::vector<int> results;
    results.push_back(gen.get());
    
    while (gen.next()) {
        results.push_back(gen.get());
    }
    
    std::vector<int> expected = {10, 20, 10, 20, 10, 20};
    EXPECT_EQ(results, expected);
}

TEST_F(RepeatGeneratorTest_927, ZeroRepeats_927) {
    // Zero repeats - next() should immediately return false
    auto gen = RepeatGenerator<int>(0, fixedValues<int>({1, 2, 3}));
    
    // With 0 target repeats, the first next() call should return false
    EXPECT_FALSE(gen.next());
}

TEST_F(RepeatGeneratorTest_927, StringValues_927) {
    // Test with string type
    auto gen = RepeatGenerator<std::string>(2, fixedValues<std::string>({"hello", "world"}));
    
    std::vector<std::string> results;
    results.push_back(gen.get());
    
    while (gen.next()) {
        results.push_back(gen.get());
    }
    
    std::vector<std::string> expected = {"hello", "world", "hello", "world"};
    EXPECT_EQ(results, expected);
}

TEST_F(RepeatGeneratorTest_927, LargeRepeatCount_927) {
    // Repeat a single value many times
    auto gen = RepeatGenerator<int>(100, fixedValues<int>({7}));
    
    int count = 1; // already have first value from get()
    while (gen.next()) {
        EXPECT_EQ(gen.get(), 7);
        ++count;
    }
    
    EXPECT_EQ(count, 100);
}

TEST_F(RepeatGeneratorTest_927, GetReturnsConsistentValueWithoutNext_927) {
    // Calling get() multiple times without next() should return the same value
    auto gen = RepeatGenerator<int>(2, fixedValues<int>({5, 10}));
    
    EXPECT_EQ(gen.get(), 5);
    EXPECT_EQ(gen.get(), 5);
    EXPECT_EQ(gen.get(), 5);
}

TEST_F(RepeatGeneratorTest_927, ThreeValuesRepeatedTwice_927) {
    // {1, 2, 3} repeated 2 times
    auto gen = RepeatGenerator<int>(2, fixedValues<int>({1, 2, 3}));
    
    std::vector<int> results;
    results.push_back(gen.get());
    
    while (gen.next()) {
        results.push_back(gen.get());
    }
    
    std::vector<int> expected = {1, 2, 3, 1, 2, 3};
    EXPECT_EQ(results, expected);
}

TEST_F(RepeatGeneratorTest_927, SingleRepeatSingleValue_927) {
    // Minimal case: 1 repeat, 1 value
    auto gen = RepeatGenerator<int>(1, fixedValues<int>({99}));
    
    EXPECT_EQ(gen.get(), 99);
    EXPECT_FALSE(gen.next());
}

TEST_F(RepeatGeneratorTest_927, NextReturnsFalseAfterExhaustion_927) {
    // After generator is exhausted, verify behavior
    auto gen = RepeatGenerator<int>(1, fixedValues<int>({1}));
    
    EXPECT_EQ(gen.get(), 1);
    EXPECT_FALSE(gen.next());
    // Calling next again after exhaustion
    EXPECT_FALSE(gen.next());
}

TEST_F(RepeatGeneratorTest_927, FiveValuesRepeatedFiveTimes_927) {
    auto gen = RepeatGenerator<int>(5, fixedValues<int>({1, 2, 3, 4, 5}));
    
    std::vector<int> results;
    results.push_back(gen.get());
    
    while (gen.next()) {
        results.push_back(gen.get());
    }
    
    EXPECT_EQ(results.size(), 25u);
    
    // Verify pattern repeats
    for (size_t i = 0; i < results.size(); ++i) {
        EXPECT_EQ(results[i], static_cast<int>((i % 5) + 1));
    }
}
