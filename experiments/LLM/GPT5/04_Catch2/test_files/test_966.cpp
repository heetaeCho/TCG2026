// File: contains_matcher_match_tests_966.cpp
// Purpose: Black-box tests for Catch::Matchers::ContainsMatcher::match
// Notes:
//  - Tests ONLY observable behavior of `match` based on the provided interface.
//  - No assumptions about internal state or `describe()` output.
//  - No re-implementation or inference of internal logic.

// Includes
#include <gtest/gtest.h>
#include <vector>
#include <string>

// The amalgamated Catch2 header as provided in your tree
#include "Catch2/extras/catch_amalgamated.hpp"

namespace {

using CatchContainsInt =
    Catch::Matchers::ContainsMatcher<int, std::allocator<int>, std::allocator<int>>;

using CatchContainsString =
    Catch::Matchers::ContainsMatcher<std::string, std::allocator<std::string>, std::allocator<std::string>>;

// ---------- Normal operation ----------

TEST(ContainsMatcherTest_966, ReturnsTrueWhenAllComparatorElementsPresent_966) {
    const std::vector<int> comparator{2, 4};
    const std::vector<int> candidate{1, 2, 3, 4, 5};

    CatchContainsInt matcher(comparator);
    EXPECT_TRUE(matcher.match(candidate));
}

TEST(ContainsMatcherTest_966, ReturnsTrueRegardlessOfOrderAndExtrasInCandidate_966) {
    const std::vector<int> comparator{3, 1};
    const std::vector<int> candidate{1, 2, 3, 4}; // order differs; extra elements present

    CatchContainsInt matcher(comparator);
    EXPECT_TRUE(matcher.match(candidate));
}

// ---------- Boundary conditions ----------

TEST(ContainsMatcherTest_966, ReturnsTrueForEmptyComparatorAgainstEmptyCandidate_966) {
    const std::vector<int> comparator{};
    const std::vector<int> candidate{};

    CatchContainsInt matcher(comparator);
    EXPECT_TRUE(matcher.match(candidate));
}

TEST(ContainsMatcherTest_966, ReturnsTrueForEmptyComparatorAgainstNonEmptyCandidate_966) {
    const std::vector<int> comparator{};
    const std::vector<int> candidate{10, 20, 30};

    CatchContainsInt matcher(comparator);
    EXPECT_TRUE(matcher.match(candidate));
}

TEST(ContainsMatcherTest_966, ReturnsFalseWhenComparatorLargerThanCandidate_966) {
    const std::vector<int> comparator{1, 2, 3, 4};
    const std::vector<int> candidate{1, 2};

    CatchContainsInt matcher(comparator);
    EXPECT_FALSE(matcher.match(candidate)); // size pre-check should fail this case
}

// ---------- Exceptional / negative observable cases ----------

TEST(ContainsMatcherTest_966, ReturnsFalseWhenAnyComparatorElementMissing_966) {
    const std::vector<int> comparator{2, 6};   // 6 not in candidate
    const std::vector<int> candidate{1, 2, 3};

    CatchContainsInt matcher(comparator);
    EXPECT_FALSE(matcher.match(candidate));
}

// ---------- Behavior with duplicates (as observable from interface) ----------

TEST(ContainsMatcherTest_966, ComparatorWithDuplicatesDoesNotRequireMultipleOccurrences_966) {
    const std::vector<int> comparator{2, 2}; // duplicate in comparator
    const std::vector<int> candidate{2};     // single occurrence in candidate

    CatchContainsInt matcher(comparator);
    // Based on observable behavior of `match`, each comparator value is checked
    // for presence; duplicates in comparator do not enforce multiplicity.
    EXPECT_TRUE(matcher.match(candidate));
}

TEST(ContainsMatcherTest_966, CandidateWithDuplicatesStillMatchesSingleRequirement_966) {
    const std::vector<int> comparator{5};
    const std::vector<int> candidate{5, 5, 5};

    CatchContainsInt matcher(comparator);
    EXPECT_TRUE(matcher.match(candidate));
}

// ---------- Type coverage (strings) ----------

TEST(ContainsMatcherTest_966, WorksWithNonIntegralTypesUsingEquality_966) {
    const std::vector<std::string> comparator{"cat", "dog"};
    const std::vector<std::string> candidate{"bird", "dog", "cat"};

    CatchContainsString matcher(comparator);
    EXPECT_TRUE(matcher.match(candidate));
}

TEST(ContainsMatcherTest_966, StringMissingElementYieldsFalse_966) {
    const std::vector<std::string> comparator{"alpha", "beta", "gamma"};
    const std::vector<std::string> candidate{"alpha", "gamma"}; // "beta" missing

    CatchContainsString matcher(comparator);
    EXPECT_FALSE(matcher.match(candidate));
}

} // namespace
