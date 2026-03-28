#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <string>
#include <initializer_list>
#include <functional>

// Include the Catch2 amalgamated header for the matcher
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

class RangeEqualsMatcherTest_961 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that RangeEquals matches identical integer vectors
TEST_F(RangeEqualsMatcherTest_961, MatchesIdenticalIntVectors_961) {
    auto matcher = Catch::Matchers::RangeEquals({1, 2, 3});
    std::vector<int> vec = {1, 2, 3};
    EXPECT_TRUE(matcher.match(vec));
}

// Test that RangeEquals does not match different vectors
TEST_F(RangeEqualsMatcherTest_961, DoesNotMatchDifferentVectors_961) {
    auto matcher = Catch::Matchers::RangeEquals({1, 2, 3});
    std::vector<int> vec = {1, 2, 4};
    EXPECT_FALSE(matcher.match(vec));
}

// Test that RangeEquals does not match vectors of different sizes
TEST_F(RangeEqualsMatcherTest_961, DoesNotMatchDifferentSizedVectors_961) {
    auto matcher = Catch::Matchers::RangeEquals({1, 2, 3});
    std::vector<int> vec = {1, 2};
    EXPECT_FALSE(matcher.match(vec));
}

// Test that RangeEquals does not match when target is longer
TEST_F(RangeEqualsMatcherTest_961, DoesNotMatchLongerVector_961) {
    auto matcher = Catch::Matchers::RangeEquals({1, 2, 3});
    std::vector<int> vec = {1, 2, 3, 4};
    EXPECT_FALSE(matcher.match(vec));
}

// Test matching with empty ranges
TEST_F(RangeEqualsMatcherTest_961, MatchesEmptyRanges_961) {
    auto matcher = Catch::Matchers::RangeEquals<int>({});
    std::vector<int> vec = {};
    EXPECT_TRUE(matcher.match(vec));
}

// Test empty matcher does not match non-empty vector
TEST_F(RangeEqualsMatcherTest_961, EmptyMatcherDoesNotMatchNonEmpty_961) {
    auto matcher = Catch::Matchers::RangeEquals<int>({});
    std::vector<int> vec = {1};
    EXPECT_FALSE(matcher.match(vec));
}

// Test matching with a custom predicate
TEST_F(RangeEqualsMatcherTest_961, MatchesWithCustomPredicate_961) {
    auto matcher = Catch::Matchers::RangeEquals(
        {10, 20, 30},
        [](int a, int b) { return a / 10 == b / 10; }
    );
    std::vector<int> vec = {11, 22, 33};
    EXPECT_TRUE(matcher.match(vec));
}

// Test custom predicate that fails
TEST_F(RangeEqualsMatcherTest_961, CustomPredicateFailsCorrectly_961) {
    auto matcher = Catch::Matchers::RangeEquals(
        {10, 20, 30},
        [](int a, int b) { return a / 10 == b / 10; }
    );
    std::vector<int> vec = {11, 55, 33};
    EXPECT_FALSE(matcher.match(vec));
}

// Test matching with a single element
TEST_F(RangeEqualsMatcherTest_961, MatchesSingleElement_961) {
    auto matcher = Catch::Matchers::RangeEquals({42});
    std::vector<int> vec = {42};
    EXPECT_TRUE(matcher.match(vec));
}

// Test matching against a list (different container type)
TEST_F(RangeEqualsMatcherTest_961, MatchesAgainstList_961) {
    auto matcher = Catch::Matchers::RangeEquals({1, 2, 3});
    std::list<int> lst = {1, 2, 3};
    EXPECT_TRUE(matcher.match(lst));
}

// Test with negative numbers
TEST_F(RangeEqualsMatcherTest_961, MatchesNegativeNumbers_961) {
    auto matcher = Catch::Matchers::RangeEquals({-1, -2, -3});
    std::vector<int> vec = {-1, -2, -3};
    EXPECT_TRUE(matcher.match(vec));
}

// Test that order matters
TEST_F(RangeEqualsMatcherTest_961, OrderMatters_961) {
    auto matcher = Catch::Matchers::RangeEquals({1, 2, 3});
    std::vector<int> vec = {3, 2, 1};
    EXPECT_FALSE(matcher.match(vec));
}

// Test with string types
TEST_F(RangeEqualsMatcherTest_961, MatchesStringTypes_961) {
    auto matcher = Catch::Matchers::RangeEquals({std::string("a"), std::string("b"), std::string("c")});
    std::vector<std::string> vec = {"a", "b", "c"};
    EXPECT_TRUE(matcher.match(vec));
}

// Test with double values
TEST_F(RangeEqualsMatcherTest_961, MatchesDoubleValues_961) {
    auto matcher = Catch::Matchers::RangeEquals({1.0, 2.0, 3.0});
    std::vector<double> vec = {1.0, 2.0, 3.0};
    EXPECT_TRUE(matcher.match(vec));
}

// Test describe method returns non-empty string
TEST_F(RangeEqualsMatcherTest_961, DescribeReturnsNonEmpty_961) {
    auto matcher = Catch::Matchers::RangeEquals({1, 2, 3});
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}
