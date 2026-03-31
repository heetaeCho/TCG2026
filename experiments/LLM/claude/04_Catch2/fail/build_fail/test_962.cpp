#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <string>
#include <array>
#include <set>
#include <functional>
#include <algorithm>

// Include the Catch2 amalgamated header for the matcher
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using Catch::Matchers::UnorderedRangeEquals;

class UnorderedRangeEqualsTest_962 : public ::testing::Test {
protected:
};

// Normal operation: identical vectors should match
TEST_F(UnorderedRangeEqualsTest_962, IdenticalVectorsMatch_962) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, 3};
    auto matcher = UnorderedRangeEquals(v2);
    EXPECT_TRUE(matcher.match(v1));
}

// Normal operation: same elements in different order should match
TEST_F(UnorderedRangeEqualsTest_962, SameElementsDifferentOrderMatch_962) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {3, 1, 2};
    auto matcher = UnorderedRangeEquals(v2);
    EXPECT_TRUE(matcher.match(v1));
}

// Normal operation: different elements should not match
TEST_F(UnorderedRangeEqualsTest_962, DifferentElementsDoNotMatch_962) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};
    auto matcher = UnorderedRangeEquals(v2);
    EXPECT_FALSE(matcher.match(v1));
}

// Boundary: empty ranges should match
TEST_F(UnorderedRangeEqualsTest_962, EmptyRangesMatch_962) {
    std::vector<int> v1 = {};
    std::vector<int> v2 = {};
    auto matcher = UnorderedRangeEquals(v2);
    EXPECT_TRUE(matcher.match(v1));
}

// Boundary: empty vs non-empty should not match
TEST_F(UnorderedRangeEqualsTest_962, EmptyVsNonEmptyDoNotMatch_962) {
    std::vector<int> v1 = {};
    std::vector<int> v2 = {1};
    auto matcher = UnorderedRangeEquals(v2);
    EXPECT_FALSE(matcher.match(v1));
}

// Boundary: non-empty vs empty should not match
TEST_F(UnorderedRangeEqualsTest_962, NonEmptyVsEmptyDoNotMatch_962) {
    std::vector<int> v1 = {1};
    std::vector<int> v2 = {};
    auto matcher = UnorderedRangeEquals(v2);
    EXPECT_FALSE(matcher.match(v1));
}

// Boundary: different sizes should not match
TEST_F(UnorderedRangeEqualsTest_962, DifferentSizesDoNotMatch_962) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2};
    auto matcher = UnorderedRangeEquals(v2);
    EXPECT_FALSE(matcher.match(v1));
}

// Normal: single element ranges that match
TEST_F(UnorderedRangeEqualsTest_962, SingleElementMatch_962) {
    std::vector<int> v1 = {42};
    std::vector<int> v2 = {42};
    auto matcher = UnorderedRangeEquals(v2);
    EXPECT_TRUE(matcher.match(v1));
}

// Normal: single element ranges that don't match
TEST_F(UnorderedRangeEqualsTest_962, SingleElementNoMatch_962) {
    std::vector<int> v1 = {42};
    std::vector<int> v2 = {99};
    auto matcher = UnorderedRangeEquals(v2);
    EXPECT_FALSE(matcher.match(v1));
}

// Normal: duplicate elements in same quantities match
TEST_F(UnorderedRangeEqualsTest_962, DuplicateElementsSameCountMatch_962) {
    std::vector<int> v1 = {1, 1, 2, 3};
    std::vector<int> v2 = {3, 1, 2, 1};
    auto matcher = UnorderedRangeEquals(v2);
    EXPECT_TRUE(matcher.match(v1));
}

// Error case: duplicate elements in different quantities should not match
TEST_F(UnorderedRangeEqualsTest_962, DuplicateElementsDifferentCountDoNotMatch_962) {
    std::vector<int> v1 = {1, 1, 2};
    std::vector<int> v2 = {1, 2, 2};
    auto matcher = UnorderedRangeEquals(v2);
    EXPECT_FALSE(matcher.match(v1));
}

// Normal: custom predicate - case insensitive string comparison
TEST_F(UnorderedRangeEqualsTest_962, CustomPredicateMatch_962) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {11, 12, 13};
    // Custom predicate: elements are "equal" if they have the same last digit
    auto pred = [](int a, int b) { return (a % 10) == (b % 10); };
    auto matcher = UnorderedRangeEquals(v2, pred);
    EXPECT_TRUE(matcher.match(v1));
}

// Normal: custom predicate that doesn't match
TEST_F(UnorderedRangeEqualsTest_962, CustomPredicateNoMatch_962) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {10, 20, 30};
    auto pred = [](int a, int b) { return a == b; };
    auto matcher = UnorderedRangeEquals(v2, pred);
    EXPECT_FALSE(matcher.match(v1));
}

// Cross-container: vector vs list
TEST_F(UnorderedRangeEqualsTest_962, DifferentContainerTypesMatch_962) {
    std::vector<int> v1 = {3, 1, 2};
    std::list<int> l2 = {1, 2, 3};
    auto matcher = UnorderedRangeEquals(l2);
    EXPECT_TRUE(matcher.match(v1));
}

// Cross-container: vector vs array
TEST_F(UnorderedRangeEqualsTest_962, VectorVsArrayMatch_962) {
    std::vector<int> v1 = {3, 2, 1};
    std::array<int, 3> a2 = {1, 2, 3};
    auto matcher = UnorderedRangeEquals(a2);
    EXPECT_TRUE(matcher.match(v1));
}

// Normal: strings
TEST_F(UnorderedRangeEqualsTest_962, StringVectorsMatch_962) {
    std::vector<std::string> v1 = {"hello", "world", "foo"};
    std::vector<std::string> v2 = {"foo", "hello", "world"};
    auto matcher = UnorderedRangeEquals(v2);
    EXPECT_TRUE(matcher.match(v1));
}

// Normal: strings that don't match
TEST_F(UnorderedRangeEqualsTest_962, StringVectorsDoNotMatch_962) {
    std::vector<std::string> v1 = {"hello", "world"};
    std::vector<std::string> v2 = {"hello", "bar"};
    auto matcher = UnorderedRangeEquals(v2);
    EXPECT_FALSE(matcher.match(v1));
}

// Boundary: large range with shuffled order
TEST_F(UnorderedRangeEqualsTest_962, LargeRangeShuffledMatch_962) {
    std::vector<int> v1(100);
    std::iota(v1.begin(), v1.end(), 0);
    std::vector<int> v2(v1.rbegin(), v1.rend()); // reversed
    auto matcher = UnorderedRangeEquals(v2);
    EXPECT_TRUE(matcher.match(v1));
}

// Error: subset should not match
TEST_F(UnorderedRangeEqualsTest_962, SubsetDoesNotMatch_962) {
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {1, 2, 3};
    auto matcher = UnorderedRangeEquals(v2);
    EXPECT_FALSE(matcher.match(v1));
}

// Normal: all same elements
TEST_F(UnorderedRangeEqualsTest_962, AllSameElementsMatch_962) {
    std::vector<int> v1 = {5, 5, 5};
    std::vector<int> v2 = {5, 5, 5};
    auto matcher = UnorderedRangeEquals(v2);
    EXPECT_TRUE(matcher.match(v1));
}

// Error: same elements different count of duplicates
TEST_F(UnorderedRangeEqualsTest_962, AllSameButDifferentSizeDoNotMatch_962) {
    std::vector<int> v1 = {5, 5, 5};
    std::vector<int> v2 = {5, 5};
    auto matcher = UnorderedRangeEquals(v2);
    EXPECT_FALSE(matcher.match(v1));
}
