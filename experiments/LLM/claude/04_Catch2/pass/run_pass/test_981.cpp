#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>

// Include the Catch2 amalgamated header for the matchers
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using Catch::Matchers::UnorderedEquals;

class UnorderedEqualsMatcherTest_981 : public ::testing::Test {
protected:
    // Helper to check if a matcher matches a given vector
    template<typename T>
    bool matches(const std::vector<T>& actual, const std::vector<T>& expected) {
        auto matcher = UnorderedEquals(expected);
        return matcher.match(actual);
    }
};

// Normal operation tests

TEST_F(UnorderedEqualsMatcherTest_981, IdenticalVectorsMatch_981) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, 3};
    EXPECT_TRUE(matches(v1, v2));
}

TEST_F(UnorderedEqualsMatcherTest_981, ReorderedVectorsMatch_981) {
    std::vector<int> v1 = {3, 1, 2};
    std::vector<int> v2 = {1, 2, 3};
    EXPECT_TRUE(matches(v1, v2));
}

TEST_F(UnorderedEqualsMatcherTest_981, ReverseOrderMatch_981) {
    std::vector<int> v1 = {3, 2, 1};
    std::vector<int> v2 = {1, 2, 3};
    EXPECT_TRUE(matches(v1, v2));
}

TEST_F(UnorderedEqualsMatcherTest_981, SingleElementMatch_981) {
    std::vector<int> v1 = {42};
    std::vector<int> v2 = {42};
    EXPECT_TRUE(matches(v1, v2));
}

TEST_F(UnorderedEqualsMatcherTest_981, EmptyVectorsMatch_981) {
    std::vector<int> v1 = {};
    std::vector<int> v2 = {};
    EXPECT_TRUE(matches(v1, v2));
}

TEST_F(UnorderedEqualsMatcherTest_981, DuplicateElementsSameCountMatch_981) {
    std::vector<int> v1 = {1, 1, 2, 3};
    std::vector<int> v2 = {1, 2, 1, 3};
    EXPECT_TRUE(matches(v1, v2));
}

// Mismatch tests

TEST_F(UnorderedEqualsMatcherTest_981, DifferentSizesDoNotMatch_981) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2};
    EXPECT_FALSE(matches(v1, v2));
}

TEST_F(UnorderedEqualsMatcherTest_981, DifferentElementsDoNotMatch_981) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};
    EXPECT_FALSE(matches(v1, v2));
}

TEST_F(UnorderedEqualsMatcherTest_981, SubsetDoesNotMatch_981) {
    std::vector<int> v1 = {1, 2};
    std::vector<int> v2 = {1, 2, 3};
    EXPECT_FALSE(matches(v1, v2));
}

TEST_F(UnorderedEqualsMatcherTest_981, SupersetDoesNotMatch_981) {
    std::vector<int> v1 = {1, 2, 3, 4};
    std::vector<int> v2 = {1, 2, 3};
    EXPECT_FALSE(matches(v1, v2));
}

TEST_F(UnorderedEqualsMatcherTest_981, DuplicateCountMismatchDoesNotMatch_981) {
    std::vector<int> v1 = {1, 1, 2};
    std::vector<int> v2 = {1, 2, 2};
    EXPECT_FALSE(matches(v1, v2));
}

TEST_F(UnorderedEqualsMatcherTest_981, EmptyVsNonEmptyDoesNotMatch_981) {
    std::vector<int> v1 = {};
    std::vector<int> v2 = {1};
    EXPECT_FALSE(matches(v1, v2));
}

TEST_F(UnorderedEqualsMatcherTest_981, NonEmptyVsEmptyDoesNotMatch_981) {
    std::vector<int> v1 = {1};
    std::vector<int> v2 = {};
    EXPECT_FALSE(matches(v1, v2));
}

// String type tests

TEST_F(UnorderedEqualsMatcherTest_981, StringVectorsMatch_981) {
    std::vector<std::string> v1 = {"hello", "world"};
    std::vector<std::string> v2 = {"world", "hello"};
    EXPECT_TRUE(matches(v1, v2));
}

TEST_F(UnorderedEqualsMatcherTest_981, StringVectorsDoNotMatch_981) {
    std::vector<std::string> v1 = {"hello", "world"};
    std::vector<std::string> v2 = {"hello", "earth"};
    EXPECT_FALSE(matches(v1, v2));
}

// Double type tests

TEST_F(UnorderedEqualsMatcherTest_981, DoubleVectorsReorderedMatch_981) {
    std::vector<double> v1 = {1.1, 2.2, 3.3};
    std::vector<double> v2 = {3.3, 1.1, 2.2};
    EXPECT_TRUE(matches(v1, v2));
}

// Large vector test

TEST_F(UnorderedEqualsMatcherTest_981, LargeVectorsShuffledMatch_981) {
    std::vector<int> v1;
    for (int i = 0; i < 1000; ++i) {
        v1.push_back(i);
    }
    std::vector<int> v2(v1.rbegin(), v1.rend());
    EXPECT_TRUE(matches(v1, v2));
}

TEST_F(UnorderedEqualsMatcherTest_981, LargeVectorsOneDifferentDoNotMatch_981) {
    std::vector<int> v1;
    std::vector<int> v2;
    for (int i = 0; i < 1000; ++i) {
        v1.push_back(i);
        v2.push_back(i);
    }
    v2[999] = 9999;
    EXPECT_FALSE(matches(v1, v2));
}

// Duplicate heavy tests

TEST_F(UnorderedEqualsMatcherTest_981, AllDuplicatesMatch_981) {
    std::vector<int> v1 = {5, 5, 5, 5};
    std::vector<int> v2 = {5, 5, 5, 5};
    EXPECT_TRUE(matches(v1, v2));
}

TEST_F(UnorderedEqualsMatcherTest_981, AllDuplicatesDifferentCountDoNotMatch_981) {
    std::vector<int> v1 = {5, 5, 5};
    std::vector<int> v2 = {5, 5, 5, 5};
    EXPECT_FALSE(matches(v1, v2));
}

// Test that the matcher has a describe method (basic existence check through compilation)
TEST_F(UnorderedEqualsMatcherTest_981, MatcherDescribeDoesNotThrow_981) {
    std::vector<int> target = {1, 2, 3};
    auto matcher = UnorderedEquals(target);
    EXPECT_NO_THROW({
        std::string desc = matcher.describe();
        EXPECT_FALSE(desc.empty());
    });
}

// Negative values
TEST_F(UnorderedEqualsMatcherTest_981, NegativeValuesReorderedMatch_981) {
    std::vector<int> v1 = {-3, -1, -2};
    std::vector<int> v2 = {-1, -2, -3};
    EXPECT_TRUE(matches(v1, v2));
}

// Mixed positive and negative
TEST_F(UnorderedEqualsMatcherTest_981, MixedSignValuesMatch_981) {
    std::vector<int> v1 = {-1, 0, 1};
    std::vector<int> v2 = {1, -1, 0};
    EXPECT_TRUE(matches(v1, v2));
}

// Single element mismatch
TEST_F(UnorderedEqualsMatcherTest_981, SingleElementMismatch_981) {
    std::vector<int> v1 = {1};
    std::vector<int> v2 = {2};
    EXPECT_FALSE(matches(v1, v2));
}
