#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <string>
#include <initializer_list>
#include <functional>
#include <algorithm>

// Include the Catch2 amalgamated header for the matchers
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

class UnorderedRangeEqualsTest_963 : public ::testing::Test {
protected:
    template<typename Range, typename Matcher>
    bool doesMatch(const Range& range, const Matcher& matcher) {
        return matcher.match(range);
    }
};

// Test: Empty ranges should match
TEST_F(UnorderedRangeEqualsTest_963, EmptyRangesMatch_963) {
    auto matcher = Catch::Matchers::UnorderedRangeEquals<int>({});
    std::vector<int> empty_vec{};
    EXPECT_TRUE(doesMatch(empty_vec, matcher));
}

// Test: Identical single-element ranges match
TEST_F(UnorderedRangeEqualsTest_963, SingleElementMatch_963) {
    auto matcher = Catch::Matchers::UnorderedRangeEquals({42});
    std::vector<int> vec{42};
    EXPECT_TRUE(doesMatch(vec, matcher));
}

// Test: Single element mismatch
TEST_F(UnorderedRangeEqualsTest_963, SingleElementMismatch_963) {
    auto matcher = Catch::Matchers::UnorderedRangeEquals({42});
    std::vector<int> vec{43};
    EXPECT_FALSE(doesMatch(vec, matcher));
}

// Test: Same elements in same order should match
TEST_F(UnorderedRangeEqualsTest_963, SameOrderMatch_963) {
    auto matcher = Catch::Matchers::UnorderedRangeEquals({1, 2, 3});
    std::vector<int> vec{1, 2, 3};
    EXPECT_TRUE(doesMatch(vec, matcher));
}

// Test: Same elements in different order should match
TEST_F(UnorderedRangeEqualsTest_963, DifferentOrderMatch_963) {
    auto matcher = Catch::Matchers::UnorderedRangeEquals({1, 2, 3});
    std::vector<int> vec{3, 1, 2};
    EXPECT_TRUE(doesMatch(vec, matcher));
}

// Test: Different sizes should not match - target larger
TEST_F(UnorderedRangeEqualsTest_963, DifferentSizesLargerTarget_963) {
    auto matcher = Catch::Matchers::UnorderedRangeEquals({1, 2, 3});
    std::vector<int> vec{1, 2, 3, 4};
    EXPECT_FALSE(doesMatch(vec, matcher));
}

// Test: Different sizes should not match - target smaller
TEST_F(UnorderedRangeEqualsTest_963, DifferentSizesSmallerTarget_963) {
    auto matcher = Catch::Matchers::UnorderedRangeEquals({1, 2, 3});
    std::vector<int> vec{1, 2};
    EXPECT_FALSE(doesMatch(vec, matcher));
}

// Test: Duplicate elements in matching ranges
TEST_F(UnorderedRangeEqualsTest_963, DuplicateElementsMatch_963) {
    auto matcher = Catch::Matchers::UnorderedRangeEquals({1, 1, 2});
    std::vector<int> vec{1, 2, 1};
    EXPECT_TRUE(doesMatch(vec, matcher));
}

// Test: Duplicate elements with different counts should not match
TEST_F(UnorderedRangeEqualsTest_963, DuplicateElementsDifferentCounts_963) {
    auto matcher = Catch::Matchers::UnorderedRangeEquals({1, 1, 2});
    std::vector<int> vec{1, 2, 2};
    EXPECT_FALSE(doesMatch(vec, matcher));
}

// Test: Empty expected vs non-empty target should not match
TEST_F(UnorderedRangeEqualsTest_963, EmptyExpectedNonEmptyTarget_963) {
    auto matcher = Catch::Matchers::UnorderedRangeEquals<int>({});
    std::vector<int> vec{1};
    EXPECT_FALSE(doesMatch(vec, matcher));
}

// Test: Non-empty expected vs empty target should not match
TEST_F(UnorderedRangeEqualsTest_963, NonEmptyExpectedEmptyTarget_963) {
    auto matcher = Catch::Matchers::UnorderedRangeEquals({1});
    std::vector<int> empty_vec{};
    EXPECT_FALSE(doesMatch(empty_vec, matcher));
}

// Test: Custom predicate - case insensitive comparison using custom equality
TEST_F(UnorderedRangeEqualsTest_963, CustomPredicateMatch_963) {
    auto close_enough = [](int a, int b) { return std::abs(a - b) <= 1; };
    auto matcher = Catch::Matchers::UnorderedRangeEquals({10, 20, 30}, close_enough);
    std::vector<int> vec{31, 11, 21};
    EXPECT_TRUE(doesMatch(vec, matcher));
}

// Test: Custom predicate no match
TEST_F(UnorderedRangeEqualsTest_963, CustomPredicateNoMatch_963) {
    auto close_enough = [](int a, int b) { return std::abs(a - b) <= 1; };
    auto matcher = Catch::Matchers::UnorderedRangeEquals({10, 20, 30}, close_enough);
    std::vector<int> vec{35, 15, 25};
    EXPECT_FALSE(doesMatch(vec, matcher));
}

// Test: Works with different container types (list)
TEST_F(UnorderedRangeEqualsTest_963, WorksWithList_963) {
    auto matcher = Catch::Matchers::UnorderedRangeEquals({3, 2, 1});
    std::list<int> lst{1, 2, 3};
    EXPECT_TRUE(doesMatch(lst, matcher));
}

// Test: Large range with reversed order
TEST_F(UnorderedRangeEqualsTest_963, LargeRangeReversed_963) {
    auto matcher = Catch::Matchers::UnorderedRangeEquals({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    std::vector<int> vec{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    EXPECT_TRUE(doesMatch(vec, matcher));
}

// Test: Completely different elements
TEST_F(UnorderedRangeEqualsTest_963, CompletelyDifferentElements_963) {
    auto matcher = Catch::Matchers::UnorderedRangeEquals({1, 2, 3});
    std::vector<int> vec{4, 5, 6};
    EXPECT_FALSE(doesMatch(vec, matcher));
}

// Test: All same elements match
TEST_F(UnorderedRangeEqualsTest_963, AllSameElementsMatch_963) {
    auto matcher = Catch::Matchers::UnorderedRangeEquals({5, 5, 5});
    std::vector<int> vec{5, 5, 5};
    EXPECT_TRUE(doesMatch(vec, matcher));
}

// Test: Negative numbers
TEST_F(UnorderedRangeEqualsTest_963, NegativeNumbers_963) {
    auto matcher = Catch::Matchers::UnorderedRangeEquals({-3, -1, -2});
    std::vector<int> vec{-1, -2, -3};
    EXPECT_TRUE(doesMatch(vec, matcher));
}

// Test: describe method returns non-empty string
TEST_F(UnorderedRangeEqualsTest_963, DescribeReturnsNonEmpty_963) {
    auto matcher = Catch::Matchers::UnorderedRangeEquals({1, 2, 3});
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}
