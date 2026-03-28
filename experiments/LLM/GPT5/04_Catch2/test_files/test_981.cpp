// File: tests/UnorderedEqualsMatcherTests_981.cpp

#include <gtest/gtest.h>
#include "Catch2/extras/catch_amalgamated.hpp"

// For brevity
using Catch::Matchers::UnorderedEquals;

class UnorderedEqualsTest_981 : public ::testing::Test {};

TEST_F(UnorderedEqualsTest_981, MatchesWhenSameElementsDifferentOrder_981) {
    std::vector<int> expected{1, 2, 3, 4};
    std::vector<int> actual  {4, 3, 2, 1};

    auto m = UnorderedEquals(expected);
    EXPECT_TRUE(m.match(actual));
}

TEST_F(UnorderedEqualsTest_981, MatchesWithDuplicateElementsSameMultiplicity_981) {
    std::vector<int> expected{1, 1, 2, 3};
    std::vector<int> actual  {3, 1, 2, 1};

    auto m = UnorderedEquals(expected);
    EXPECT_TRUE(m.match(actual));
}

TEST_F(UnorderedEqualsTest_981, MismatchWhenDifferentMultiplicity_981) {
    std::vector<int> expected{1, 1, 2, 3};
    std::vector<int> actual  {1, 2, 3, 3}; // multiplicities differ

    auto m = UnorderedEquals(expected);
    EXPECT_FALSE(m.match(actual));
}

TEST_F(UnorderedEqualsTest_981, MismatchWhenDifferentSizes_981) {
    std::vector<int> expected{10, 20, 30};
    std::vector<int> actual  {10, 20};

    auto m = UnorderedEquals(expected);
    EXPECT_FALSE(m.match(actual));
}

TEST_F(UnorderedEqualsTest_981, MatchesEmptyVectors_981) {
    std::vector<int> expected{};
    std::vector<int> actual{};

    auto m = UnorderedEquals(expected);
    EXPECT_TRUE(m.match(actual));
}

TEST_F(UnorderedEqualsTest_981, MismatchWhenElementsDiffer_981) {
    std::vector<int> expected{5, 6, 7};
    std::vector<int> actual  {5, 6, 8};

    auto m = UnorderedEquals(expected);
    EXPECT_FALSE(m.match(actual));
}

TEST_F(UnorderedEqualsTest_981, WorksWithStrings_981) {
    std::vector<std::string> expected{"alpha", "beta", "gamma"};
    std::vector<std::string> actual  {"gamma", "alpha", "beta"};

    auto m = UnorderedEquals(expected);
    EXPECT_TRUE(m.match(actual));
}

TEST_F(UnorderedEqualsTest_981, DescribeProducesNonEmptyMessage_981) {
    std::vector<int> expected{1, 2, 3};
    auto m = UnorderedEquals(expected);

    // We don't assert the exact contents (black-box). Just that it describes something.
    const std::string desc = m.describe();
    EXPECT_FALSE(desc.empty());
}
