#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Matchers;

// ============================================================
// Tests for ContainsMatcher
// ============================================================

// Helper: create a ContainsMatcher and call match
// Since ContainsMatcher takes a reference, we need to keep the comparator alive.

// --- Normal Operation Tests ---

TEST(ContainsMatcherTest_966, MatchReturnsTrueWhenAllElementsPresent_966) {
    std::vector<int> comparator = {1, 2, 3};
    std::vector<int> v = {1, 2, 3, 4, 5};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_TRUE(matcher.match(v));
}

TEST(ContainsMatcherTest_966, MatchReturnsTrueWhenExactMatch_966) {
    std::vector<int> comparator = {1, 2, 3};
    std::vector<int> v = {1, 2, 3};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_TRUE(matcher.match(v));
}

TEST(ContainsMatcherTest_966, MatchReturnsFalseWhenElementMissing_966) {
    std::vector<int> comparator = {1, 2, 6};
    std::vector<int> v = {1, 2, 3, 4, 5};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_FALSE(matcher.match(v));
}

TEST(ContainsMatcherTest_966, MatchReturnsTrueWhenSingleElementPresent_966) {
    std::vector<int> comparator = {3};
    std::vector<int> v = {1, 2, 3, 4, 5};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_TRUE(matcher.match(v));
}

TEST(ContainsMatcherTest_966, MatchReturnsFalseWhenSingleElementMissing_966) {
    std::vector<int> comparator = {99};
    std::vector<int> v = {1, 2, 3, 4, 5};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_FALSE(matcher.match(v));
}

// --- Boundary Condition Tests ---

TEST(ContainsMatcherTest_966, EmptyComparatorMatchesAnyVector_966) {
    std::vector<int> comparator = {};
    std::vector<int> v = {1, 2, 3};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_TRUE(matcher.match(v));
}

TEST(ContainsMatcherTest_966, EmptyComparatorMatchesEmptyVector_966) {
    std::vector<int> comparator = {};
    std::vector<int> v = {};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_TRUE(matcher.match(v));
}

TEST(ContainsMatcherTest_966, NonEmptyComparatorFailsOnEmptyVector_966) {
    std::vector<int> comparator = {1};
    std::vector<int> v = {};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_FALSE(matcher.match(v));
}

TEST(ContainsMatcherTest_966, ComparatorLargerThanVectorReturnsFalse_966) {
    std::vector<int> comparator = {1, 2, 3, 4, 5, 6};
    std::vector<int> v = {1, 2, 3};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_FALSE(matcher.match(v));
}

// --- Order Independence Tests ---

TEST(ContainsMatcherTest_966, MatchIsOrderIndependent_966) {
    std::vector<int> comparator = {3, 1, 2};
    std::vector<int> v = {1, 2, 3, 4, 5};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_TRUE(matcher.match(v));
}

TEST(ContainsMatcherTest_966, MatchWithReversedOrder_966) {
    std::vector<int> comparator = {5, 4, 3, 2, 1};
    std::vector<int> v = {1, 2, 3, 4, 5};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_TRUE(matcher.match(v));
}

// --- Duplicate Element Tests ---

TEST(ContainsMatcherTest_966, DuplicateInComparatorMatchesIfPresentOnce_966) {
    // The comparator has duplicate 1s, but the match logic checks presence (not count)
    // Each comparator element is checked for presence in v independently.
    // Since 1 is present in v, both comparator entries for 1 will find it.
    std::vector<int> comparator = {1, 1};
    std::vector<int> v = {1, 2, 3};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_TRUE(matcher.match(v));
}

TEST(ContainsMatcherTest_966, DuplicatesInVectorStillMatch_966) {
    std::vector<int> comparator = {1, 2};
    std::vector<int> v = {1, 1, 2, 2, 3, 3};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_TRUE(matcher.match(v));
}

// --- String Type Tests ---

TEST(ContainsMatcherTest_966, MatchWorksWithStrings_966) {
    std::vector<std::string> comparator = {"hello", "world"};
    std::vector<std::string> v = {"hello", "beautiful", "world"};
    ContainsMatcher<std::string, std::allocator<std::string>, std::allocator<std::string>> matcher(comparator);
    EXPECT_TRUE(matcher.match(v));
}

TEST(ContainsMatcherTest_966, MatchFailsWithMissingString_966) {
    std::vector<std::string> comparator = {"hello", "missing"};
    std::vector<std::string> v = {"hello", "beautiful", "world"};
    ContainsMatcher<std::string, std::allocator<std::string>, std::allocator<std::string>> matcher(comparator);
    EXPECT_FALSE(matcher.match(v));
}

// --- Describe Tests ---

TEST(ContainsMatcherTest_966, DescribeReturnsNonEmptyString_966) {
    std::vector<int> comparator = {1, 2, 3};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// --- Edge case: comparator same size as vector but different elements ---

TEST(ContainsMatcherTest_966, SameSizeDifferentElementsReturnsFalse_966) {
    std::vector<int> comparator = {4, 5, 6};
    std::vector<int> v = {1, 2, 3};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_FALSE(matcher.match(v));
}

// --- Edge case: comparator has one more element than vector ---

TEST(ContainsMatcherTest_966, ComparatorOneElementLargerReturnsFalse_966) {
    std::vector<int> comparator = {1, 2, 3, 4};
    std::vector<int> v = {1, 2, 3};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_FALSE(matcher.match(v));
}

// --- Negative/Zero value tests ---

TEST(ContainsMatcherTest_966, MatchWithNegativeValues_966) {
    std::vector<int> comparator = {-1, -2};
    std::vector<int> v = {-3, -2, -1, 0, 1};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_TRUE(matcher.match(v));
}

TEST(ContainsMatcherTest_966, MatchWithZeroValue_966) {
    std::vector<int> comparator = {0};
    std::vector<int> v = {-1, 0, 1};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_TRUE(matcher.match(v));
}

// --- Large vector test ---

TEST(ContainsMatcherTest_966, MatchWithLargeVectors_966) {
    std::vector<int> comparator;
    std::vector<int> v;
    for (int i = 0; i < 1000; ++i) {
        v.push_back(i);
    }
    for (int i = 0; i < 500; ++i) {
        comparator.push_back(i * 2); // even numbers 0..998
    }
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_TRUE(matcher.match(v));
}

TEST(ContainsMatcherTest_966, MatchFailsWithLargeVectorsMissingElement_966) {
    std::vector<int> comparator;
    std::vector<int> v;
    for (int i = 0; i < 1000; ++i) {
        v.push_back(i);
    }
    comparator.push_back(1000); // not in v
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_FALSE(matcher.match(v));
}
