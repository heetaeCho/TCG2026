// File: tests/range_equals_matcher_match_956_tests.cpp
#include <gtest/gtest.h>
#include <list>
#include <vector>
#include <array>
#include <string>
#include <functional>
#include <cmath>

#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Matchers::RangeEqualsMatcher;

namespace {

// Helper aliases to reduce verbosity in tests
template <typename TargetRange, typename Pred>
using RangeEq = RangeEqualsMatcher<TargetRange, Pred>;

} // namespace

// --- Normal operation ---

TEST(RangeEqualsMatcherTest_956, ExactMatch_SameValuesDifferentRangeTypes_956) {
    RangeEq<std::vector<int>, std::equal_to<int>> matcher({1, 2, 3}, std::equal_to<int>{});
    std::list<int> actual = {1, 2, 3};

    EXPECT_TRUE(matcher.match(actual));
}

TEST(RangeEqualsMatcherTest_956, ExactMatch_WithRvalueRange_956) {
    RangeEq<std::vector<int>, std::equal_to<int>> matcher({10, 20, 30}, std::equal_to<int>{});

    EXPECT_TRUE(matcher.match(std::vector<int>{10, 20, 30}));
}

TEST(RangeEqualsMatcherTest_956, ExactMatch_WithArray_956) {
    RangeEq<std::array<int, 3>, std::equal_to<int>> matcher(std::array<int, 3>{4, 5, 6}, std::equal_to<int>{});
    std::array<int, 3> actual{4, 5, 6};

    EXPECT_TRUE(matcher.match(actual));
}

// --- Boundary conditions ---

TEST(RangeEqualsMatcherTest_956, EmptyDesiredAndEmptyActual_AreEqual_956) {
    RangeEq<std::vector<int>, std::equal_to<int>> matcher({}, std::equal_to<int>{});
    std::vector<int> actual;

    EXPECT_TRUE(matcher.match(actual));
}

TEST(RangeEqualsMatcherTest_956, EmptyDesiredVsNonEmptyActual_NotEqual_956) {
    RangeEq<std::vector<int>, std::equal_to<int>> matcher({}, std::equal_to<int>{});
    std::vector<int> actual{1};

    EXPECT_FALSE(matcher.match(actual));
}

TEST(RangeEqualsMatcherTest_956, NonEmptyDesiredVsEmptyActual_NotEqual_956) {
    RangeEq<std::vector<int>, std::equal_to<int>> matcher({1}, std::equal_to<int>{});
    std::vector<int> actual;

    EXPECT_FALSE(matcher.match(actual));
}

TEST(RangeEqualsMatcherTest_956, SamePrefixButDifferentLengths_NotEqualWhenActualShorter_956) {
    RangeEq<std::vector<int>, std::equal_to<int>> matcher({1, 2, 3}, std::equal_to<int>{});
    std::vector<int> actual{1, 2};

    EXPECT_FALSE(matcher.match(actual));
}

TEST(RangeEqualsMatcherTest_956, SamePrefixButDifferentLengths_NotEqualWhenActualLonger_956) {
    RangeEq<std::vector<int>, std::equal_to<int>> matcher({1, 2, 3}, std::equal_to<int>{});
    std::vector<int> actual{1, 2, 3, 4};

    EXPECT_FALSE(matcher.match(actual));
}

// --- Mismatch / error-like observable cases ---

TEST(RangeEqualsMatcherTest_956, FirstElementMismatch_NotEqual_956) {
    RangeEq<std::vector<int>, std::equal_to<int>> matcher({9, 2, 3}, std::equal_to<int>{});
    std::vector<int> actual{1, 2, 3};

    EXPECT_FALSE(matcher.match(actual));
}

TEST(RangeEqualsMatcherTest_956, MiddleElementMismatch_NotEqual_956) {
    RangeEq<std::vector<int>, std::equal_to<int>> matcher({1, 99, 3}, std::equal_to<int>{});
    std::vector<int> actual{1, 2, 3};

    EXPECT_FALSE(matcher.match(actual));
}

// --- Custom predicate verification (external interaction with provided predicate) ---

TEST(RangeEqualsMatcherTest_956, CustomPredicate_FloatingPointNearEquality_956) {
    auto near_eq = [](double a, double b) { return std::fabs(a - b) < 1e-6; };

    RangeEq<std::vector<double>, decltype(near_eq)> matcher({1.0, 2.0, 3.0}, near_eq);
    std::vector<double> actual{1.0 + 1e-7, 2.0 - 5e-7, 3.0 + 8e-7};

    EXPECT_TRUE(matcher.match(actual));
}

TEST(RangeEqualsMatcherTest_956, CustomPredicate_CaseInsensitiveChars_956) {
    auto ci_equal = [](char a, char b) {
        auto to_low = [](unsigned char c) { return static_cast<char>(std::tolower(c)); };
        return to_low(a) == to_low(b);
    };

    RangeEq<std::string, decltype(ci_equal)> matcher(std::string{"AbC"}, ci_equal);
    std::string actual = "aBc";

    EXPECT_TRUE(matcher.match(actual));
}

TEST(RangeEqualsMatcherTest_956, CustomPredicate_PartialMismatch_956) {
    auto ci_equal = [](char a, char b) {
        auto to_low = [](unsigned char c) { return static_cast<char>(std::tolower(c)); };
        return to_low(a) == to_low(b);
    };

    RangeEq<std::string, decltype(ci_equal)> matcher(std::string{"TesT"}, ci_equal);
    std::string actual = "TeXt"; // differs at third character (s vs x)

    EXPECT_FALSE(matcher.match(actual));
}

// --- Heterogeneous range types with the same element type ---

TEST(RangeEqualsMatcherTest_956, VectorDesired_ListActual_SameSequence_956) {
    RangeEq<std::vector<int>, std::equal_to<int>> matcher({7, 8, 9}, std::equal_to<int>{});
    std::list<int> actual = {7, 8, 9};

    EXPECT_TRUE(matcher.match(actual));
}

TEST(RangeEqualsMatcherTest_956, VectorDesired_ListActual_DifferentSequence_956) {
    RangeEq<std::vector<int>, std::equal_to<int>> matcher({7, 8, 9}, std::equal_to<int>{});
    std::list<int> actual = {7, 9, 8};

    EXPECT_FALSE(matcher.match(actual));
}

