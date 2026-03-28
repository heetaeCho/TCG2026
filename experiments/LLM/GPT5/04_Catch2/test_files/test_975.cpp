// File: tests/UnorderedEqualsMatcher_tests_975.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include "Catch2/extras/catch_amalgamated.hpp"

// Simple custom allocator to exercise AllocComp/AllocMatch difference without
// peeking into any internal state.
template <typename T>
struct TestAllocator {
    using value_type = T;
    TestAllocator() noexcept = default;
    template <typename U>
    TestAllocator(const TestAllocator<U>&) noexcept {}

    T* allocate(std::size_t n) {
        return std::allocator<T>{}.allocate(n);
    }
    void deallocate(T* p, std::size_t n) noexcept {
        std::allocator<T>{}.deallocate(p, n);
    }
    template <typename U>
    bool operator==(const TestAllocator<U>&) const noexcept { return true; }
    template <typename U>
    bool operator!=(const TestAllocator<U>&) const noexcept { return false; }
};

using Catch::Matchers::UnorderedEqualsMatcher;

class UnorderedEqualsMatcherTest_975 : public ::testing::Test {};

// Normal operation: same elements, same order => match is true
TEST_F(UnorderedEqualsMatcherTest_975, SameOrderReturnsTrue_975) {
    std::vector<int> target{1, 2, 3, 4};
    std::vector<int> input {1, 2, 3, 4};

    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> m(target);
    EXPECT_TRUE(m.match(input));
}

// Normal operation: same elements, different order => match is true
TEST_F(UnorderedEqualsMatcherTest_975, DifferentOrderReturnsTrue_975) {
    std::vector<int> target{1, 2, 3, 4};
    std::vector<int> input {4, 3, 2, 1};

    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> m(target);
    EXPECT_TRUE(m.match(input));
}

// Boundary: both empty vectors => match is true
TEST_F(UnorderedEqualsMatcherTest_975, EmptyVectorsReturnTrue_975) {
    std::vector<int> target{};
    std::vector<int> input {};

    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> m(target);
    EXPECT_TRUE(m.match(input));
}

// Boundary: different sizes => match is false
TEST_F(UnorderedEqualsMatcherTest_975, DifferentSizesReturnFalse_975) {
    std::vector<int> target{1, 2, 3};
    std::vector<int> input {1, 2, 3, 4};

    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> m(target);
    EXPECT_FALSE(m.match(input));
}

// Error/negative case: same size but different elements => match is false
TEST_F(UnorderedEqualsMatcherTest_975, SameSizeDifferentElementsReturnFalse_975) {
    std::vector<int> target{1, 2, 3, 4};
    std::vector<int> input {1, 2, 3, 5};

    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> m(target);
    EXPECT_FALSE(m.match(input));
}

// Duplicate handling: element counts differ => match is false
TEST_F(UnorderedEqualsMatcherTest_975, DuplicateCountsMismatchReturnFalse_975) {
    std::vector<int> target{1, 1, 2, 3};
    std::vector<int> input {1, 2, 2, 3};

    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> m(target);
    EXPECT_FALSE(m.match(input));
}

// Works with non-integer types (e.g., std::string)
TEST_F(UnorderedEqualsMatcherTest_975, WorksWithStrings_975) {
    std::vector<std::string> target{"alpha", "beta", "gamma"};
    std::vector<std::string> input {"beta", "gamma", "alpha"};

    UnorderedEqualsMatcher<std::string, std::allocator<std::string>, std::allocator<std::string>> m(target);
    EXPECT_TRUE(m.match(input));
}

// Cross-allocator compatibility: target and input use different allocators
TEST_F(UnorderedEqualsMatcherTest_975, CrossAllocatorMatchTrue_975) {
    std::vector<int, TestAllocator<int>> target{10, 20, 30};
    std::vector<int, std::allocator<int>> input {30, 20, 10};

    UnorderedEqualsMatcher<int, TestAllocator<int>, std::allocator<int>> m(target);
    EXPECT_TRUE(m.match(input));
}

// describe(): we don't assert specific wording—only that it provides some description
TEST_F(UnorderedEqualsMatcherTest_975, DescribeIsNonEmpty_975) {
    std::vector<int> target{1, 2, 3};
    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> m(target);

    std::string d = m.describe();
    // Only observable expectation: it returns a non-empty description string.
    EXPECT_FALSE(d.empty());
}
