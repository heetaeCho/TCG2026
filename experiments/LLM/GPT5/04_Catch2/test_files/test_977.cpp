// File: test_contains_matcher_977.cpp
#include <gtest/gtest.h>
#include <vector>

// Only public interface from the amalgamated header:
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Matchers::Contains;

// A tiny allocator to exercise AllocComp vs AllocMatch being different.
template <typename T>
struct TestAlloc {
    using value_type = T;
    TestAlloc() noexcept = default;
    template <class U> TestAlloc(const TestAlloc<U>&) noexcept {}

    T* allocate(std::size_t n) { return std::allocator<T>{}.allocate(n); }
    void deallocate(T* p, std::size_t n) { std::allocator<T>{}.deallocate(p, n); }

    template <class U>
    bool operator==(const TestAlloc<U>&) const noexcept { return true; }
    template <class U>
    bool operator!=(const TestAlloc<U>&) const noexcept { return false; }
};

//
// Normal operation
//
TEST(ContainsMatcher_977, MatchesWhenAllElementsPresent_977) {
    const std::vector<int> comparator{2, 4};
    const auto matcher = Contains(comparator);

    std::vector<int> actual{1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(actual));
}

TEST(ContainsMatcher_977, DoesNotRequireOrder_977) {
    const std::vector<int> comparator{3, 1};
    const auto matcher = Contains(comparator);

    std::vector<int> actual{1, 2, 3};
    EXPECT_TRUE(matcher.match(actual)); // order in 'actual' is different
}

//
// Boundary conditions
//
TEST(ContainsMatcher_977, EmptyComparatorAlwaysMatches_977) {
    const std::vector<int> comparator{}; // vacuously contained
    const auto matcher = Contains(comparator);

    std::vector<int> actual{};                  // empty actual
    EXPECT_TRUE(matcher.match(actual));

    std::vector<int> actual2{10, 20, 30};      // non-empty actual
    EXPECT_TRUE(matcher.match(actual2));
}

TEST(ContainsMatcher_977, EmptyActualMatchesOnlyIfComparatorEmpty_977) {
    const std::vector<int> comparator{1};
    const auto matcher = Contains(comparator);

    std::vector<int> actual{};
    EXPECT_FALSE(matcher.match(actual));
}

//
// Error/negative observable cases
//
TEST(ContainsMatcher_977, FailsWhenAnyComparatorElementMissing_977) {
    const std::vector<int> comparator{2, 99};
    const auto matcher = Contains(comparator);

    std::vector<int> actual{1, 2, 3, 4};
    EXPECT_FALSE(matcher.match(actual)); // 99 not present
}

//
// Allocator interplay (AllocComp vs AllocMatch)
// Verifies the matcher can check a vector with a different allocator type.
//
TEST(ContainsMatcher_977, WorksWithDifferentAllocatorTypes_977) {
    using CompAlloc = std::allocator<int>;
    using MatchAlloc = TestAlloc<int>;

    const std::vector<int, CompAlloc> comparator{7, 8};
    // Explicit template args ensure AllocMatch != AllocComp is exercised.
    const auto matcher =
        Catch::Matchers::Contains<int, CompAlloc, MatchAlloc>(comparator);

    std::vector<int, MatchAlloc> actual{0, 7, 1, 8, 2};
    EXPECT_TRUE(matcher.match(actual));

    std::vector<int, MatchAlloc> actual_missing{0, 7, 1};
    EXPECT_FALSE(matcher.match(actual_missing));
}

//
// Description text (human-readable)
// We don't depend on exact full formatting; we assert recognizable parts.
//
TEST(ContainsMatcher_977, DescribeMentionsContainsAndValues_977) {
    const std::vector<int> comparator{42, 5};
    const auto matcher = Contains(comparator);

    const std::string desc = matcher.describe();
    // Observable expectations without relying on exact full formatting.
    EXPECT_NE(std::string::npos, desc.find("Contains"))
        << "Description should mention 'Contains'";
    EXPECT_NE(std::string::npos, desc.find("42"))
        << "Description should mention a comparator element";
    EXPECT_NE(std::string::npos, desc.find("5"))
        << "Description should mention another comparator element";
}
