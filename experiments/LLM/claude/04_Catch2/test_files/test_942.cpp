#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <string>
#include <array>
#include <set>
#include <deque>

// Include Catch2 amalgamated header for the generators
#define CATCH_CONFIG_MAIN
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

class FromRangeTest_942 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper to extract all values from a generator
template <typename T>
std::vector<T> extractAll(Catch::Generators::GeneratorWrapper<T>& gen) {
    std::vector<T> result;
    result.push_back(gen.get());
    while (gen.next()) {
        result.push_back(gen.get());
    }
    return result;
}

// Test: from_range with a vector of integers produces all elements in order
TEST_F(FromRangeTest_942, VectorOfIntsProducesAllElements_942) {
    std::vector<int> input = {1, 2, 3, 4, 5};
    auto gen = Catch::Generators::from_range(input);
    auto results = extractAll(gen);
    ASSERT_EQ(results.size(), input.size());
    for (size_t i = 0; i < input.size(); ++i) {
        EXPECT_EQ(results[i], input[i]);
    }
}

// Test: from_range with a single element container
TEST_F(FromRangeTest_942, SingleElementContainer_942) {
    std::vector<int> input = {42};
    auto gen = Catch::Generators::from_range(input);
    auto results = extractAll(gen);
    ASSERT_EQ(results.size(), 1u);
    EXPECT_EQ(results[0], 42);
}

// Test: from_range with a list container
TEST_F(FromRangeTest_942, ListContainer_942) {
    std::list<int> input = {10, 20, 30};
    auto gen = Catch::Generators::from_range(input);
    auto results = extractAll(gen);
    ASSERT_EQ(results.size(), 3u);
    EXPECT_EQ(results[0], 10);
    EXPECT_EQ(results[1], 20);
    EXPECT_EQ(results[2], 30);
}

// Test: from_range with a vector of strings
TEST_F(FromRangeTest_942, VectorOfStrings_942) {
    std::vector<std::string> input = {"hello", "world", "test"};
    auto gen = Catch::Generators::from_range(input);
    auto results = extractAll(gen);
    ASSERT_EQ(results.size(), 3u);
    EXPECT_EQ(results[0], "hello");
    EXPECT_EQ(results[1], "world");
    EXPECT_EQ(results[2], "test");
}

// Test: from_range with std::array
TEST_F(FromRangeTest_942, StdArrayContainer_942) {
    std::array<int, 4> input = {100, 200, 300, 400};
    auto gen = Catch::Generators::from_range(input);
    auto results = extractAll(gen);
    ASSERT_EQ(results.size(), 4u);
    EXPECT_EQ(results[0], 100);
    EXPECT_EQ(results[3], 400);
}

// Test: from_range with a set (sorted order)
TEST_F(FromRangeTest_942, SetContainer_942) {
    std::set<int> input = {3, 1, 2};
    auto gen = Catch::Generators::from_range(input);
    auto results = extractAll(gen);
    ASSERT_EQ(results.size(), 3u);
    // set is sorted
    EXPECT_EQ(results[0], 1);
    EXPECT_EQ(results[1], 2);
    EXPECT_EQ(results[2], 3);
}

// Test: from_range with deque
TEST_F(FromRangeTest_942, DequeContainer_942) {
    std::deque<double> input = {1.1, 2.2, 3.3};
    auto gen = Catch::Generators::from_range(input);
    auto results = extractAll(gen);
    ASSERT_EQ(results.size(), 3u);
    EXPECT_DOUBLE_EQ(results[0], 1.1);
    EXPECT_DOUBLE_EQ(results[1], 2.2);
    EXPECT_DOUBLE_EQ(results[2], 3.3);
}

// Test: from_range - next() returns false after last element
TEST_F(FromRangeTest_942, NextReturnsFalseAfterLastElement_942) {
    std::vector<int> input = {1, 2};
    auto gen = Catch::Generators::from_range(input);
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_FALSE(gen.next());
}

// Test: from_range with large container
TEST_F(FromRangeTest_942, LargeContainer_942) {
    std::vector<int> input(1000);
    for (int i = 0; i < 1000; ++i) {
        input[i] = i;
    }
    auto gen = Catch::Generators::from_range(input);
    auto results = extractAll(gen);
    ASSERT_EQ(results.size(), 1000u);
    EXPECT_EQ(results[0], 0);
    EXPECT_EQ(results[999], 999);
}

// Test: first get() returns first element without calling next()
TEST_F(FromRangeTest_942, FirstGetReturnsFirstElement_942) {
    std::vector<int> input = {7, 8, 9};
    auto gen = Catch::Generators::from_range(input);
    EXPECT_EQ(gen.get(), 7);
}

// Test: from_range with const container
TEST_F(FromRangeTest_942, ConstContainer_942) {
    const std::vector<int> input = {11, 22, 33};
    auto gen = Catch::Generators::from_range(input);
    auto results = extractAll(gen);
    ASSERT_EQ(results.size(), 3u);
    EXPECT_EQ(results[0], 11);
    EXPECT_EQ(results[1], 22);
    EXPECT_EQ(results[2], 33);
}

// Test: from_range with vector of booleans
TEST_F(FromRangeTest_942, VectorOfBools_942) {
    std::vector<int> input = {0, 1, 0, 1}; // using int since vector<bool> is special
    auto gen = Catch::Generators::from_range(input);
    auto results = extractAll(gen);
    ASSERT_EQ(results.size(), 4u);
    EXPECT_EQ(results[0], 0);
    EXPECT_EQ(results[1], 1);
}

// Test: from_range preserves order of elements
TEST_F(FromRangeTest_942, PreservesOrder_942) {
    std::vector<int> input = {5, 3, 1, 4, 2};
    auto gen = Catch::Generators::from_range(input);
    auto results = extractAll(gen);
    ASSERT_EQ(results.size(), 5u);
    for (size_t i = 0; i < input.size(); ++i) {
        EXPECT_EQ(results[i], input[i]);
    }
}

// Test: Multiple calls to get() without next() return same value
TEST_F(FromRangeTest_942, MultipleGetWithoutNextReturnsSameValue_942) {
    std::vector<int> input = {42, 43};
    auto gen = Catch::Generators::from_range(input);
    EXPECT_EQ(gen.get(), 42);
    EXPECT_EQ(gen.get(), 42);
    EXPECT_EQ(gen.get(), 42);
}
