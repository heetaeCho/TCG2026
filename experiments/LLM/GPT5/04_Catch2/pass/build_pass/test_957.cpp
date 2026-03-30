// File: tests/RangeEqualsMatcher_957_Test.cpp

#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <array>
#include <functional>
#include <cmath>

// Include the amalgamated Catch2 header that provides RangeEqualsMatcher
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Matchers::RangeEqualsMatcher;

namespace {

struct RangeEqualsMatcherTest_957 : public ::testing::Test {};

// --- describe() behavior ---

TEST_F(RangeEqualsMatcherTest_957, DescribePrefixesWithElementsAre_957) {
    // Arrange
    std::vector<int> desired{1, 2, 3};
    auto pred = std::equal_to<int>{};
    RangeEqualsMatcher<std::vector<int>, decltype(pred)> matcher(desired, pred);

    // Act
    const std::string desc = matcher.describe();

    // Assert (prefix is observable behavior)
    ASSERT_TRUE(desc.rfind("elements are ", 0) == 0) << "Description should start with 'elements are '";
}

TEST_F(RangeEqualsMatcherTest_957, DescribeUsesCatchStringifyOfDesired_957) {
    // Arrange
    std::list<int> desired{4, 5};
    auto pred = std::equal_to<int>{};
    RangeEqualsMatcher<std::list<int>, decltype(pred)> matcher(desired, pred);

    // Act
    const std::string desc = matcher.describe();

    // Assert (compute expected using the same public stringify facility)
    const std::string expected = std::string("elements are ") + Catch::Detail::stringify(desired);
    EXPECT_EQ(desc, expected);
}

TEST_F(RangeEqualsMatcherTest_957, DescribeOnEmptyRange_957) {
    // Arrange
    std::vector<int> desired; // empty
    auto pred = std::equal_to<int>{};
    RangeEqualsMatcher<std::vector<int>, decltype(pred)> matcher(desired, pred);

    // Act
    const std::string desc = matcher.describe();

    // Assert
    const std::string expected = std::string("elements are ") + Catch::Detail::stringify(desired);
    EXPECT_EQ(desc, expected);
}

// --- match() normal operation ---

TEST_F(RangeEqualsMatcherTest_957, MatchReturnsTrueForIdenticalRanges_957) {
    // Arrange
    std::vector<int> desired{1, 2, 3};
    std::vector<int> actual{1, 2, 3};
    auto pred = std::equal_to<int>{};
    RangeEqualsMatcher<std::vector<int>, decltype(pred)> matcher(desired, pred);

    // Act / Assert
    EXPECT_TRUE(matcher.match(actual));
}

TEST_F(RangeEqualsMatcherTest_957, MatchWorksAcrossDifferentRangeTypes_957) {
    // Arrange
    std::list<int> desired{10, 20, 30};
    std::vector<int> actual{10, 20, 30};
    auto pred = std::equal_to<int>{};
    RangeEqualsMatcher<std::list<int>, decltype(pred)> matcher(desired, pred);

    // Act / Assert
    EXPECT_TRUE(matcher.match(actual));
}

TEST_F(RangeEqualsMatcherTest_957, MatchWithCustomPredicateApproxFloat_957) {
    // Arrange
    std::vector<double> desired{1.0, 2.0, 3.0};
    std::array<double, 3> actual{1.0 + 1e-9, 2.0 - 5e-7, 3.0 + 9e-7};

    auto approx = [](double a, double b) {
        return std::fabs(a - b) < 1e-6;
    };

    RangeEqualsMatcher<std::vector<double>, decltype(approx)> matcher(desired, approx);

    // Act / Assert
    EXPECT_TRUE(matcher.match(actual));
}

// --- boundary conditions ---

TEST_F(RangeEqualsMatcherTest_957, MatchEmptyRangesAreEqual_957) {
    // Arrange
    std::vector<int> desired{};
    std::vector<int> actual{};
    auto pred = std::equal_to<int>{};
    RangeEqualsMatcher<std::vector<int>, decltype(pred)> matcher(desired, pred);

    // Act / Assert
    EXPECT_TRUE(matcher.match(actual));
}

TEST_F(RangeEqualsMatcherTest_957, MatchDifferentSizesAreNotEqual_957) {
    // Arrange
    std::vector<int> desired{1, 2};
    std::vector<int> actual{1, 2, 3};
    auto pred = std::equal_to<int>{};
    RangeEqualsMatcher<std::vector<int>, decltype(pred)> matcher(desired, pred);

    // Act / Assert
    EXPECT_FALSE(matcher.match(actual));
}

TEST_F(RangeEqualsMatcherTest_957, MatchSamePrefixButDifferentTailIsNotEqual_957) {
    // Arrange
    std::vector<int> desired{1, 2, 3};
    std::vector<int> actual{1, 2, 4};
    auto pred = std::equal_to<int>{};
    RangeEqualsMatcher<std::vector<int>, decltype(pred)> matcher(desired, pred);

    // Act / Assert
    EXPECT_FALSE(matcher.match(actual));
}

// --- predicate-related observable behavior ---

TEST_F(RangeEqualsMatcherTest_957, MatchUsesProvidedPredicate_957) {
    // Arrange: predicate that intentionally treats all numbers as equal if they have same parity
    auto sameParity = [](int a, int b) { return (a % 2) == (b % 2); };

    std::vector<int> desired{2, 4, 6};
    std::vector<int> actual{8, 10, 12};
    RangeEqualsMatcher<std::vector<int>, decltype(sameParity)> matcher(desired, sameParity);

    // Act / Assert
    EXPECT_TRUE(matcher.match(actual));

    // Negative case with same predicate
    std::vector<int> actual_mixed{8, 11, 12}; // second element parity differs
    EXPECT_FALSE(matcher.match(actual_mixed));
}

} // namespace
