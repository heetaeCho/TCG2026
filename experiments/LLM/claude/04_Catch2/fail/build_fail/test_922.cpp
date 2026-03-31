#include <gtest/gtest.h>
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"
#include <string>
#include <vector>

using namespace Catch::Generators;

// Helper: create a generator from a fixed set of values
template <typename T>
GeneratorWrapper<T> makeValues(std::initializer_list<T> vals) {
    return values(vals);
}

class TakeGeneratorTest_922 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that take(n, ...) produces exactly n values from the underlying generator
TEST_F(TakeGeneratorTest_922, TakeLessThanAvailable_922) {
    auto gen = take(2, values<int>({10, 20, 30, 40}));
    
    // First value should be accessible
    EXPECT_EQ(gen.get(), 10);
    
    // Advance to second value
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    
    // Should not produce a third value since target is 2
    EXPECT_FALSE(gen.next());
}

// Test that take(n, ...) where n equals the number of available values
TEST_F(TakeGeneratorTest_922, TakeExactlyAvailable_922) {
    auto gen = take(3, values<int>({1, 2, 3}));
    
    EXPECT_EQ(gen.get(), 1);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    
    EXPECT_FALSE(gen.next());
}

// Test take with target = 1 (boundary: minimum meaningful take)
TEST_F(TakeGeneratorTest_922, TakeOne_922) {
    auto gen = take(1, values<int>({100, 200, 300}));
    
    EXPECT_EQ(gen.get(), 100);
    EXPECT_FALSE(gen.next());
}

// Test take with string type
TEST_F(TakeGeneratorTest_922, TakeWithStrings_922) {
    auto gen = take(2, values<std::string>({"hello", "world", "foo"}));
    
    EXPECT_EQ(gen.get(), "hello");
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "world");
    
    EXPECT_FALSE(gen.next());
}

// Test take where target exceeds available values - should stop when underlying generator is exhausted
TEST_F(TakeGeneratorTest_922, TakeMoreThanAvailable_922) {
    auto gen = take(10, values<int>({1, 2}));
    
    EXPECT_EQ(gen.get(), 1);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    
    // Underlying generator only has 2 values, so next should return false
    EXPECT_FALSE(gen.next());
}

// Test take with double type
TEST_F(TakeGeneratorTest_922, TakeWithDoubles_922) {
    auto gen = take(2, values<double>({1.5, 2.5, 3.5}));
    
    EXPECT_DOUBLE_EQ(gen.get(), 1.5);
    
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 2.5);
    
    EXPECT_FALSE(gen.next());
}

// Test take with target = 0 (boundary: take nothing)
TEST_F(TakeGeneratorTest_922, TakeZero_922) {
    auto gen = take(0, values<int>({1, 2, 3}));
    
    // With target 0, next() should immediately return false
    EXPECT_FALSE(gen.next());
}

// Test that get() returns the same value when called multiple times without advancing
TEST_F(TakeGeneratorTest_922, GetIsIdempotent_922) {
    auto gen = take(3, values<int>({42, 43, 44}));
    
    EXPECT_EQ(gen.get(), 42);
    EXPECT_EQ(gen.get(), 42);
    EXPECT_EQ(gen.get(), 42);
}

// Test sequential access pattern - all values are correct
TEST_F(TakeGeneratorTest_922, SequentialValues_922) {
    auto gen = take(4, values<int>({10, 20, 30, 40, 50}));
    
    std::vector<int> collected;
    collected.push_back(gen.get());
    while (gen.next()) {
        collected.push_back(gen.get());
    }
    
    ASSERT_EQ(collected.size(), 4u);
    EXPECT_EQ(collected[0], 10);
    EXPECT_EQ(collected[1], 20);
    EXPECT_EQ(collected[2], 30);
    EXPECT_EQ(collected[3], 40);
}

// Test with a single element source generator and take(1)
TEST_F(TakeGeneratorTest_922, SingleElementTakeOne_922) {
    auto gen = take(1, values<int>({99}));
    
    EXPECT_EQ(gen.get(), 99);
    EXPECT_FALSE(gen.next());
}

// Test with boolean type
TEST_F(TakeGeneratorTest_922, TakeWithBool_922) {
    auto gen = take(1, values<bool>({true, false}));
    
    EXPECT_EQ(gen.get(), true);
    EXPECT_FALSE(gen.next());
}

// Test chaining take with another generator wrapper
TEST_F(TakeGeneratorTest_922, TakeFromMappedGenerator_922) {
    auto gen = take(2, map<int>(
        [](int x) { return x * 2; },
        values<int>({1, 2, 3, 4})
    ));
    
    EXPECT_EQ(gen.get(), 2);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    
    EXPECT_FALSE(gen.next());
}

// Test take from filter generator
TEST_F(TakeGeneratorTest_922, TakeFromFilteredGenerator_922) {
    auto gen = take(2, filter(
        [](int x) { return x % 2 == 0; },
        values<int>({1, 2, 3, 4, 5, 6})
    ));
    
    EXPECT_EQ(gen.get(), 2);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    
    EXPECT_FALSE(gen.next());
}
