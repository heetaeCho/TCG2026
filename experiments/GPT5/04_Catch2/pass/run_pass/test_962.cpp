// File: tests/UnorderedRangeEqualsMatcher_962.tests.cpp

#include <gtest/gtest.h>
#include <list>
#include <vector>
#include <array>
#include <string>
#include <cctype>

#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Matchers::UnorderedRangeEquals;

// A simple case-insensitive equality predicate for strings.
// Used only to verify that the matcher honors a custom Equality.
struct CaseInsensitiveEq {
    bool operator()(const std::string& a, const std::string& b) const {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i) {
            if (std::tolower(static_cast<unsigned char>(a[i])) !=
                std::tolower(static_cast<unsigned char>(b[i]))) {
                return false;
            }
        }
        return true;
    }
};

class UnorderedRangeEqualsTest_962 : public ::testing::Test {};

// Normal operation: same elements, different order -> match == true
TEST_F(UnorderedRangeEqualsTest_962, SameElementsDifferentOrder_962) {
    std::vector<int> expected{1, 2, 3, 4};
    std::list<int>   actual  {4, 3, 2, 1};

    auto matcher = UnorderedRangeEquals(expected);
    EXPECT_TRUE(matcher.match(actual));
}

// Boundary: duplicates must be respected (multiset semantics)
TEST_F(UnorderedRangeEqualsTest_962, DuplicateElementsCountMustMatch_962) {
    std::vector<int> expected{1, 2, 2, 3};
    std::vector<int> actualOk{2, 3, 2, 1};
    std::vector<int> actualBad{1, 2, 3, 3};  // counts differ

    auto matcher = UnorderedRangeEquals(expected);
    EXPECT_TRUE(matcher.match(actualOk));
    EXPECT_FALSE(matcher.match(actualBad));
}

// Boundary: empty vs empty -> true; empty vs non-empty -> false
TEST_F(UnorderedRangeEqualsTest_962, EmptyRangeHandling_962) {
    std::vector<int> expected{};
    std::vector<int> actualEmpty{};
    std::vector<int> actualNonEmpty{1};

    auto matcher = UnorderedRangeEquals(expected);
    EXPECT_TRUE(matcher.match(actualEmpty));
    EXPECT_FALSE(matcher.match(actualNonEmpty));
}

// Boundary: size mismatch with overlapping elements -> false
TEST_F(UnorderedRangeEqualsTest_962, SizeMismatchEvenIfElementsOverlap_962) {
    std::vector<int> expected{1, 2, 3};
    std::vector<int> actual{1, 2, 3, 3};

    auto matcher = UnorderedRangeEquals(expected);
    EXPECT_FALSE(matcher.match(actual));
}

// Normal operation: works across heterogeneous range-like types
TEST_F(UnorderedRangeEqualsTest_962, WorksAcrossDifferentContainerTypes_962) {
    std::array<int, 5> expected{{10, 20, 30, 40, 50}};
    std::list<int>     actual  {50, 30, 10, 40, 20};

    auto matcher = UnorderedRangeEquals(expected);
    EXPECT_TRUE(matcher.match(actual));
}

// Custom comparator: case-insensitive equality for strings
TEST_F(UnorderedRangeEqualsTest_962, CustomEqualityPredicate_CaseInsensitive_962) {
    std::vector<std::string> expected{"Alpha", "beta", "Gamma"};
    std::list<std::string>   actual  {"gamma", "ALPHA", "BETA"};

    auto matcher = UnorderedRangeEquals(expected, CaseInsensitiveEq{});
    EXPECT_TRUE(matcher.match(actual));
}

// Custom comparator negative: same spellings but different counts
TEST_F(UnorderedRangeEqualsTest_962, CustomEqualityPredicate_CountsStillMatter_962) {
    std::vector<std::string> expected{"a", "a", "B"};
    std::vector<std::string> actual  {"A", "b"};  // missing one "a" (case-insensitive)

    auto matcher = UnorderedRangeEquals(expected, CaseInsensitiveEq{});
    EXPECT_FALSE(matcher.match(actual));
}

// Normal operation: initializer_list construction of expected
TEST_F(UnorderedRangeEqualsTest_962, InitializerListAsExpectedRange_962) {
    auto matcher = UnorderedRangeEquals({3, 1, 2});
    std::vector<int> actual{2, 3, 1};

    EXPECT_TRUE(matcher.match(actual));
}
