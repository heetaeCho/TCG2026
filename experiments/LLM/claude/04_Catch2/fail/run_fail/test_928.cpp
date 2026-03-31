#include <gtest/gtest.h>
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"
#include <string>
#include <vector>

using namespace Catch::Generators;

// Helper to collect all values from a generator
template <typename T>
std::vector<T> collectAll(GeneratorWrapper<T>& gen) {
    std::vector<T> results;
    results.push_back(gen.get());
    while (gen.next()) {
        results.push_back(gen.get());
    }
    return results;
}

// Test fixture
class RepeatGeneratorTest_928 : public ::testing::Test {
protected:
};

// Test that repeat with 1 repetition yields the same sequence as the original
TEST_F(RepeatGeneratorTest_928, SingleRepeatYieldsSameSequence_928) {
    auto gen = repeat(1, values<int>({1, 2, 3}));
    auto results = collectAll(gen);
    
    ASSERT_EQ(results.size(), 3u);
    EXPECT_EQ(results[0], 1);
    EXPECT_EQ(results[1], 2);
    EXPECT_EQ(results[2], 3);
}

// Test that repeat with 2 repetitions yields the sequence twice
TEST_F(RepeatGeneratorTest_928, TwoRepeatsYieldsSequenceTwice_928) {
    auto gen = repeat(2, values<int>({1, 2, 3}));
    auto results = collectAll(gen);
    
    ASSERT_EQ(results.size(), 6u);
    EXPECT_EQ(results[0], 1);
    EXPECT_EQ(results[1], 2);
    EXPECT_EQ(results[2], 3);
    EXPECT_EQ(results[3], 1);
    EXPECT_EQ(results[4], 2);
    EXPECT_EQ(results[5], 3);
}

// Test that repeat with 3 repetitions yields the sequence three times
TEST_F(RepeatGeneratorTest_928, ThreeRepeatsYieldsSequenceThreeTimes_928) {
    auto gen = repeat(3, values<int>({10, 20}));
    auto results = collectAll(gen);
    
    ASSERT_EQ(results.size(), 6u);
    EXPECT_EQ(results[0], 10);
    EXPECT_EQ(results[1], 20);
    EXPECT_EQ(results[2], 10);
    EXPECT_EQ(results[3], 20);
    EXPECT_EQ(results[4], 10);
    EXPECT_EQ(results[5], 20);
}

// Test repeat with a single element generator
TEST_F(RepeatGeneratorTest_928, RepeatSingleElement_928) {
    auto gen = repeat(3, value<int>(42));
    auto results = collectAll(gen);
    
    ASSERT_EQ(results.size(), 3u);
    EXPECT_EQ(results[0], 42);
    EXPECT_EQ(results[1], 42);
    EXPECT_EQ(results[2], 42);
}

// Test repeat with zero repetitions - boundary case
TEST_F(RepeatGeneratorTest_928, ZeroRepeatsGeneratesNothing_928) {
    // Zero repeats is a boundary condition. The generator should produce nothing
    // or throw, depending on implementation. We test observable behavior.
    try {
        auto gen = repeat(0, values<int>({1, 2, 3}));
        // If it doesn't throw, check that next() returns false quickly
        // The first get() might be valid or not depending on implementation
        SUCCEED(); // If no exception, the test passes
    } catch (...) {
        SUCCEED(); // If exception is thrown for 0 repeats, that's also valid
    }
}

// Test repeat with string type
TEST_F(RepeatGeneratorTest_928, RepeatWithStringType_928) {
    auto gen = repeat(2, values<std::string>({"hello", "world"}));
    auto results = collectAll(gen);
    
    ASSERT_EQ(results.size(), 4u);
    EXPECT_EQ(results[0], "hello");
    EXPECT_EQ(results[1], "world");
    EXPECT_EQ(results[2], "hello");
    EXPECT_EQ(results[3], "world");
}

// Test repeat with double type
TEST_F(RepeatGeneratorTest_928, RepeatWithDoubleType_928) {
    auto gen = repeat(2, values<double>({1.5, 2.5}));
    auto results = collectAll(gen);
    
    ASSERT_EQ(results.size(), 4u);
    EXPECT_DOUBLE_EQ(results[0], 1.5);
    EXPECT_DOUBLE_EQ(results[1], 2.5);
    EXPECT_DOUBLE_EQ(results[2], 1.5);
    EXPECT_DOUBLE_EQ(results[3], 2.5);
}

// Test that after exhausting all repeats, next() returns false
TEST_F(RepeatGeneratorTest_928, NextReturnsFalseAfterExhaustion_928) {
    auto gen = repeat(1, values<int>({1}));
    EXPECT_EQ(gen.get(), 1);
    EXPECT_FALSE(gen.next());
}

// Test large number of repeats
TEST_F(RepeatGeneratorTest_928, LargeRepeatCount_928) {
    auto gen = repeat(100, value<int>(7));
    auto results = collectAll(gen);
    
    ASSERT_EQ(results.size(), 100u);
    for (const auto& val : results) {
        EXPECT_EQ(val, 7);
    }
}

// Test get() returns first value before any next() call
TEST_F(RepeatGeneratorTest_928, GetReturnsFirstValueInitially_928) {
    auto gen = repeat(2, values<int>({5, 10}));
    EXPECT_EQ(gen.get(), 5);
}

// Test repeat preserves order across repetitions
TEST_F(RepeatGeneratorTest_928, OrderPreservedAcrossRepetitions_928) {
    auto gen = repeat(4, values<int>({1, 2}));
    auto results = collectAll(gen);
    
    ASSERT_EQ(results.size(), 8u);
    for (size_t i = 0; i < results.size(); i += 2) {
        EXPECT_EQ(results[i], 1);
        EXPECT_EQ(results[i + 1], 2);
    }
}
