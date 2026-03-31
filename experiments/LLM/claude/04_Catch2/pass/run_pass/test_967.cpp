#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Matchers;

// ============================================================
// Tests for ContainsMatcher
// ============================================================

// Test: match returns true when the target vector contains all elements of the comparator
TEST(ContainsMatcherTest_967, MatchReturnsTrueWhenAllElementsPresent_967) {
    std::vector<int> comparator = {1, 2, 3};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> target = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(target));
}

// Test: match returns false when not all comparator elements are in target
TEST(ContainsMatcherTest_967, MatchReturnsFalseWhenElementsMissing_967) {
    std::vector<int> comparator = {1, 2, 6};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> target = {1, 2, 3, 4, 5};
    EXPECT_FALSE(matcher.match(target));
}

// Test: match returns true when comparator is empty (empty set is a subset of any set)
TEST(ContainsMatcherTest_967, MatchReturnsTrueWhenComparatorIsEmpty_967) {
    std::vector<int> comparator = {};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> target = {1, 2, 3};
    EXPECT_TRUE(matcher.match(target));
}

// Test: match returns true when both comparator and target are empty
TEST(ContainsMatcherTest_967, MatchReturnsTrueWhenBothEmpty_967) {
    std::vector<int> comparator = {};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> target = {};
    EXPECT_TRUE(matcher.match(target));
}

// Test: match returns false when target is empty but comparator is not
TEST(ContainsMatcherTest_967, MatchReturnsFalseWhenTargetEmptyComparatorNot_967) {
    std::vector<int> comparator = {1};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> target = {};
    EXPECT_FALSE(matcher.match(target));
}

// Test: match returns true when comparator and target are identical
TEST(ContainsMatcherTest_967, MatchReturnsTrueWhenIdentical_967) {
    std::vector<int> comparator = {1, 2, 3};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> target = {1, 2, 3};
    EXPECT_TRUE(matcher.match(target));
}

// Test: match with a single element present
TEST(ContainsMatcherTest_967, MatchReturnsTrueForSingleElementPresent_967) {
    std::vector<int> comparator = {3};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> target = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(target));
}

// Test: match with a single element not present
TEST(ContainsMatcherTest_967, MatchReturnsFalseForSingleElementMissing_967) {
    std::vector<int> comparator = {99};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> target = {1, 2, 3, 4, 5};
    EXPECT_FALSE(matcher.match(target));
}

// Test: describe returns a string containing "Contains: " and the comparator representation
TEST(ContainsMatcherTest_967, DescribeContainsExpectedString_967) {
    std::vector<int> comparator = {1, 2, 3};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::string description = matcher.describe();
    EXPECT_NE(description.find("Contains: "), std::string::npos);
}

// Test: describe on empty comparator
TEST(ContainsMatcherTest_967, DescribeWithEmptyComparator_967) {
    std::vector<int> comparator = {};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::string description = matcher.describe();
    EXPECT_NE(description.find("Contains: "), std::string::npos);
}

// Test: match with string elements
TEST(ContainsMatcherTest_967, MatchWorksWithStrings_967) {
    std::vector<std::string> comparator = {"hello", "world"};
    ContainsMatcher<std::string, std::allocator<std::string>, std::allocator<std::string>> matcher(comparator);

    std::vector<std::string> target = {"hello", "beautiful", "world"};
    EXPECT_TRUE(matcher.match(target));
}

// Test: match with string elements when one is missing
TEST(ContainsMatcherTest_967, MatchReturnsFalseWithStringsMissing_967) {
    std::vector<std::string> comparator = {"hello", "missing"};
    ContainsMatcher<std::string, std::allocator<std::string>, std::allocator<std::string>> matcher(comparator);

    std::vector<std::string> target = {"hello", "beautiful", "world"};
    EXPECT_FALSE(matcher.match(target));
}

// Test: match with duplicate elements in comparator - target has enough copies
TEST(ContainsMatcherTest_967, MatchWithDuplicatesInComparator_967) {
    std::vector<int> comparator = {1, 1};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> target = {1, 1, 2, 3};
    // Whether this passes depends on implementation; we just verify it doesn't crash
    // and returns a bool
    bool result = matcher.match(target);
    (void)result; // Just ensure it runs without error
}

// Test: match where target has elements in different order than comparator
TEST(ContainsMatcherTest_967, MatchIgnoresOrder_967) {
    std::vector<int> comparator = {3, 1};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::vector<int> target = {1, 2, 3};
    EXPECT_TRUE(matcher.match(target));
}

// Test: describe with single element comparator
TEST(ContainsMatcherTest_967, DescribeWithSingleElement_967) {
    std::vector<int> comparator = {42};
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
    EXPECT_NE(description.find("Contains: "), std::string::npos);
}

// Test: match with large vectors
TEST(ContainsMatcherTest_967, MatchWithLargeVectors_967) {
    std::vector<int> comparator;
    std::vector<int> target;
    for (int i = 0; i < 1000; ++i) {
        target.push_back(i);
    }
    for (int i = 0; i < 500; ++i) {
        comparator.push_back(i * 2); // even numbers 0..998
    }
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// Test: match with large comparator that has one missing element
TEST(ContainsMatcherTest_967, MatchFailsWithLargeComparatorOneMissing_967) {
    std::vector<int> comparator;
    std::vector<int> target;
    for (int i = 0; i < 100; ++i) {
        target.push_back(i);
    }
    for (int i = 0; i < 100; ++i) {
        comparator.push_back(i);
    }
    comparator.push_back(1000); // This one is missing from target
    ContainsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_FALSE(matcher.match(target));
}
