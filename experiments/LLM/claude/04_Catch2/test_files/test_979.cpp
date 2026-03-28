#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <memory>

// Include the Catch2 amalgamated header for the Equals matcher
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

class EqualsMatcherTest_979 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper to check if a matcher matches a given vector
template<typename T, typename AllocComp = std::allocator<T>, typename AllocMatch = std::allocator<T>>
bool matcherMatches(const std::vector<T, AllocMatch>& target, const std::vector<T, AllocComp>& comparator) {
    auto matcher = Catch::Matchers::Equals(comparator);
    return matcher.match(target);
}

// Normal operation tests

TEST_F(EqualsMatcherTest_979, EmptyVectorsMatch_979) {
    std::vector<int> empty1;
    std::vector<int> empty2;
    EXPECT_TRUE(matcherMatches(empty1, empty2));
}

TEST_F(EqualsMatcherTest_979, IdenticalIntVectorsMatch_979) {
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcherMatches(v1, v2));
}

TEST_F(EqualsMatcherTest_979, IdenticalStringVectorsMatch_979) {
    std::vector<std::string> v1 = {"hello", "world"};
    std::vector<std::string> v2 = {"hello", "world"};
    EXPECT_TRUE(matcherMatches(v1, v2));
}

TEST_F(EqualsMatcherTest_979, SingleElementVectorsMatch_979) {
    std::vector<int> v1 = {42};
    std::vector<int> v2 = {42};
    EXPECT_TRUE(matcherMatches(v1, v2));
}

TEST_F(EqualsMatcherTest_979, IdenticalDoubleVectorsMatch_979) {
    std::vector<double> v1 = {1.1, 2.2, 3.3};
    std::vector<double> v2 = {1.1, 2.2, 3.3};
    EXPECT_TRUE(matcherMatches(v1, v2));
}

// Mismatch tests - different content

TEST_F(EqualsMatcherTest_979, DifferentElementsDoNotMatch_979) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, 4};
    EXPECT_FALSE(matcherMatches(v1, v2));
}

TEST_F(EqualsMatcherTest_979, DifferentOrderDoesNotMatch_979) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {3, 2, 1};
    EXPECT_FALSE(matcherMatches(v1, v2));
}

TEST_F(EqualsMatcherTest_979, DifferentStringElementsDoNotMatch_979) {
    std::vector<std::string> v1 = {"hello", "world"};
    std::vector<std::string> v2 = {"hello", "earth"};
    EXPECT_FALSE(matcherMatches(v1, v2));
}

// Boundary conditions - different sizes

TEST_F(EqualsMatcherTest_979, DifferentSizesDoNotMatch_979) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2};
    EXPECT_FALSE(matcherMatches(v1, v2));
}

TEST_F(EqualsMatcherTest_979, EmptyVsNonEmptyDoNotMatch_979) {
    std::vector<int> v1 = {};
    std::vector<int> v2 = {1};
    EXPECT_FALSE(matcherMatches(v1, v2));
}

TEST_F(EqualsMatcherTest_979, NonEmptyVsEmptyDoNotMatch_979) {
    std::vector<int> v1 = {1};
    std::vector<int> v2 = {};
    EXPECT_FALSE(matcherMatches(v1, v2));
}

TEST_F(EqualsMatcherTest_979, LongerTargetDoesNotMatch_979) {
    std::vector<int> v1 = {1, 2, 3, 4};
    std::vector<int> v2 = {1, 2, 3};
    EXPECT_FALSE(matcherMatches(v1, v2));
}

TEST_F(EqualsMatcherTest_979, LongerComparatorDoesNotMatch_979) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, 3, 4};
    EXPECT_FALSE(matcherMatches(v1, v2));
}

// Test with various types

TEST_F(EqualsMatcherTest_979, CharVectorsMatch_979) {
    std::vector<char> v1 = {'a', 'b', 'c'};
    std::vector<char> v2 = {'a', 'b', 'c'};
    EXPECT_TRUE(matcherMatches(v1, v2));
}

TEST_F(EqualsMatcherTest_979, BoolVectorsMatch_979) {
    std::vector<bool> v1 = {true, false, true};
    std::vector<bool> v2 = {true, false, true};
    auto matcher = Catch::Matchers::Equals(v2);
    EXPECT_TRUE(matcher.match(v1));
}

TEST_F(EqualsMatcherTest_979, BoolVectorsDoNotMatch_979) {
    std::vector<bool> v1 = {true, false, true};
    std::vector<bool> v2 = {true, true, true};
    auto matcher = Catch::Matchers::Equals(v2);
    EXPECT_FALSE(matcher.match(v1));
}

// Test matcher description

TEST_F(EqualsMatcherTest_979, MatcherHasDescription_979) {
    std::vector<int> v = {1, 2, 3};
    auto matcher = Catch::Matchers::Equals(v);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test that the matcher can be created and used multiple times

TEST_F(EqualsMatcherTest_979, MatcherCanBeReused_979) {
    std::vector<int> comparator = {1, 2, 3};
    auto matcher = Catch::Matchers::Equals(comparator);
    
    std::vector<int> match1 = {1, 2, 3};
    std::vector<int> match2 = {1, 2, 4};
    std::vector<int> match3 = {1, 2, 3};
    
    EXPECT_TRUE(matcher.match(match1));
    EXPECT_FALSE(matcher.match(match2));
    EXPECT_TRUE(matcher.match(match3));
}

// Test with large vectors

TEST_F(EqualsMatcherTest_979, LargeIdenticalVectorsMatch_979) {
    std::vector<int> v1(1000);
    std::vector<int> v2(1000);
    for (int i = 0; i < 1000; ++i) {
        v1[i] = i;
        v2[i] = i;
    }
    EXPECT_TRUE(matcherMatches(v1, v2));
}

TEST_F(EqualsMatcherTest_979, LargeVectorsWithOneDifferenceDoNotMatch_979) {
    std::vector<int> v1(1000);
    std::vector<int> v2(1000);
    for (int i = 0; i < 1000; ++i) {
        v1[i] = i;
        v2[i] = i;
    }
    v2[999] = -1;
    EXPECT_FALSE(matcherMatches(v1, v2));
}

// Test with negative numbers

TEST_F(EqualsMatcherTest_979, NegativeNumbersMatch_979) {
    std::vector<int> v1 = {-1, -2, -3};
    std::vector<int> v2 = {-1, -2, -3};
    EXPECT_TRUE(matcherMatches(v1, v2));
}

TEST_F(EqualsMatcherTest_979, MixedSignNumbersDoNotMatchWhenDifferent_979) {
    std::vector<int> v1 = {-1, 2, -3};
    std::vector<int> v2 = {1, -2, 3};
    EXPECT_FALSE(matcherMatches(v1, v2));
}

// Test with duplicate elements

TEST_F(EqualsMatcherTest_979, VectorsWithDuplicatesMatch_979) {
    std::vector<int> v1 = {1, 1, 2, 2, 3, 3};
    std::vector<int> v2 = {1, 1, 2, 2, 3, 3};
    EXPECT_TRUE(matcherMatches(v1, v2));
}

TEST_F(EqualsMatcherTest_979, VectorsWithDifferentDuplicateCountsDoNotMatch_979) {
    std::vector<int> v1 = {1, 1, 2};
    std::vector<int> v2 = {1, 2, 2};
    EXPECT_FALSE(matcherMatches(v1, v2));
}

// Test with zero-valued elements

TEST_F(EqualsMatcherTest_979, ZeroValuedElementsMatch_979) {
    std::vector<int> v1 = {0, 0, 0};
    std::vector<int> v2 = {0, 0, 0};
    EXPECT_TRUE(matcherMatches(v1, v2));
}

TEST_F(EqualsMatcherTest_979, ZeroVsNonZeroDoNotMatch_979) {
    std::vector<int> v1 = {0, 0, 0};
    std::vector<int> v2 = {0, 0, 1};
    EXPECT_FALSE(matcherMatches(v1, v2));
}
