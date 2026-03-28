// File: tests/EqualsMatcher_Vector_979_Test.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>

// Use the amalgamated header as provided in the prompt.
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Matchers::Equals;

namespace {

// A simple fixture is provided for naming consistency and future extension.
class EqualsMatcherVectorTest_979 : public ::testing::Test {};

} // namespace

// --- Normal operation: exact match, same order ---
TEST_F(EqualsMatcherVectorTest_979, IntVectors_ExactMatch_979) {
    const std::vector<int> comparator{1, 2, 3};
    const auto matcher = Equals(comparator);

    std::vector<int> candidate{1, 2, 3};
    EXPECT_TRUE(matcher.match(candidate));
}

// --- Normal operation: empty vectors match ---
TEST_F(EqualsMatcherVectorTest_979, EmptyVectors_Match_979) {
    const std::vector<int> comparator{};
    const auto matcher = Equals(comparator);

    const std::vector<int> candidate{};
    EXPECT_TRUE(matcher.match(candidate));
}

// --- Negative case: different order should not match (order-sensitive) ---
TEST_F(EqualsMatcherVectorTest_979, IntVectors_DifferentOrder_NoMatch_979) {
    const std::vector<int> comparator{1, 2, 3};
    const auto matcher = Equals(comparator);

    const std::vector<int> candidate{3, 2, 1};
    EXPECT_FALSE(matcher.match(candidate));
}

// --- Boundary case: size differs (candidate shorter) ---
TEST_F(EqualsMatcherVectorTest_979, IntVectors_CandidateShorter_NoMatch_979) {
    const std::vector<int> comparator{1, 2, 3};
    const auto matcher = Equals(comparator);

    const std::vector<int> candidate{1, 2};
    EXPECT_FALSE(matcher.match(candidate));
}

// --- Boundary case: size differs (candidate longer) ---
TEST_F(EqualsMatcherVectorTest_979, IntVectors_CandidateLonger_NoMatch_979) {
    const std::vector<int> comparator{1, 2, 3};
    const auto matcher = Equals(comparator);

    const std::vector<int> candidate{1, 2, 3, 4};
    EXPECT_FALSE(matcher.match(candidate));
}

// --- Normal operation: strings with duplicates match when identical ---
TEST_F(EqualsMatcherVectorTest_979, StringVectors_WithDuplicates_ExactMatch_979) {
    const std::vector<std::string> comparator{"a", "b", "b"};
    const auto matcher = Equals(comparator);

    const std::vector<std::string> candidate{"a", "b", "b"};
    EXPECT_TRUE(matcher.match(candidate));
}

// --- Negative case: strings with duplicates but different multiplicity/size ---
TEST_F(EqualsMatcherVectorTest_979, StringVectors_WithDuplicates_SizeDiff_NoMatch_979) {
    const std::vector<std::string> comparator{"a", "b", "b"};
    const auto matcher = Equals(comparator);

    const std::vector<std::string> candidate{"a", "b"};
    EXPECT_FALSE(matcher.match(candidate));
}

// --- API surface check: describe() should provide a non-empty explanation ---
// (We do NOT assert the exact text to avoid depending on internal formatting.)
TEST_F(EqualsMatcherVectorTest_979, Describe_NonEmpty_OnMatch_And_Mismatch_979) {
    const std::vector<int> comparator{1, 2, 3};
    const auto matcher = Equals(comparator);

    const std::vector<int> good{1, 2, 3};
    const std::vector<int> bad{1, 3, 2};

    // Just verify describe() returns something non-empty in both situations.
    {
        (void)good; // ensure no unused warnings in certain builds
        const std::string d = matcher.describe();
        EXPECT_FALSE(d.empty());
    }
    {
        (void)bad;
        const std::string d = matcher.describe();
        EXPECT_FALSE(d.empty());
    }
}

// --- Const-correctness / different value category on the candidate side ---
TEST_F(EqualsMatcherVectorTest_979, ConstCandidate_And_RValueCandidate_979) {
    const std::vector<int> comparator{10, 20};
    const auto matcher = Equals(comparator);

    const std::vector<int> const_candidate{10, 20};
    EXPECT_TRUE(matcher.match(const_candidate));

    // rvalue candidate
    EXPECT_TRUE(matcher.match(std::vector<int>{10, 20}));
    EXPECT_FALSE(matcher.match(std::vector<int>{20, 10}));
}
