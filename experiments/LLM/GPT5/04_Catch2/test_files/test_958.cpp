// File: tests/UnorderedRangeEqualsMatcher_958.tests.cpp

#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <string>
#include <functional>
#include <cctype>

#include "Catch2/extras/catch_amalgamated.hpp"

namespace {
using Catch::Matchers::UnorderedRangeEqualsMatcher;

// Helper: case-insensitive equality for std::string
struct CaseInsensitiveEq {
    bool operator()(const std::string& a, const std::string& b) const {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i) {
            if (std::tolower(static_cast<unsigned char>(a[i])) !=
                std::tolower(static_cast<unsigned char>(b[i]))) return false;
        }
        return true;
    }
};

} // namespace

// ---------- Normal operation ----------

TEST(UnorderedRangeEqualsMatcherTest_958, EqualElementsDifferentOrder_958) {
    std::vector<int> desired{3, 1, 2, 1};
    auto eq = [](int a, int b){ return a == b; };

    UnorderedRangeEqualsMatcher<std::vector<int>, decltype(eq)> matcher(desired, eq);

    std::list<int> actual{1, 2, 1, 3}; // same multiset, different order & container type
    EXPECT_TRUE(matcher.match(actual));
}

TEST(UnorderedRangeEqualsMatcherTest_958, DifferentSizesReturnFalse_958) {
    std::vector<int> desired{1, 2, 3};
    auto eq = [](int a, int b){ return a == b; };

    UnorderedRangeEqualsMatcher<std::vector<int>, decltype(eq)> matcher(desired, eq);

    std::vector<int> fewer{1, 2};
    std::vector<int> more{1, 2, 3, 4};

    EXPECT_FALSE(matcher.match(fewer));
    EXPECT_FALSE(matcher.match(more));
}

// ---------- Boundary conditions ----------

TEST(UnorderedRangeEqualsMatcherTest_958, EmptyRangesAreEqual_958) {
    std::vector<int> desired{};
    auto eq = [](int a, int b){ return a == b; };

    UnorderedRangeEqualsMatcher<std::vector<int>, decltype(eq)> matcher(desired, eq);

    std::list<int> actual{}; // empty vs empty
    EXPECT_TRUE(matcher.match(actual));
}

TEST(UnorderedRangeEqualsMatcherTest_958, SingleElementEqualAndNotEqual_958) {
    std::vector<int> desired{42};
    auto eq = [](int a, int b){ return a == b; };

    UnorderedRangeEqualsMatcher<std::vector<int>, decltype(eq)> matcher(desired, eq);

    EXPECT_TRUE(matcher.match(std::vector<int>{42}));
    EXPECT_FALSE(matcher.match(std::vector<int>{41}));
}

// ---------- Duplicates / multiplicities ----------

TEST(UnorderedRangeEqualsMatcherTest_958, MultiplicityMustMatch_958) {
    std::vector<int> desired{5, 5, 7};
    auto eq = [](int a, int b){ return a == b; };

    UnorderedRangeEqualsMatcher<std::vector<int>, decltype(eq)> matcher(desired, eq);

    // Same set of values but different counts (two 5s vs one 5)
    std::vector<int> actual{5, 7, 7};
    EXPECT_FALSE(matcher.match(actual));
}

// ---------- Custom predicate (verifies external interaction through predicate use) ----------

TEST(UnorderedRangeEqualsMatcherTest_958, UsesCustomPredicateCaseInsensitive_958) {
    std::vector<std::string> desired{"Alpha", "Bravo", "alpha"};
    CaseInsensitiveEq ci;

    UnorderedRangeEqualsMatcher<std::vector<std::string>, CaseInsensitiveEq> matcher(desired, ci);

    // These differ by case and order; should still match under the custom predicate
    std::list<std::string> actual{"ALPHA", "bravo", "AlPhA"};
    EXPECT_TRUE(matcher.match(actual));

    // Changing multiplicity under same predicate should fail
    std::vector<std::string> bad{"alpha", "bravo", "charlie"};
    EXPECT_FALSE(matcher.match(bad));
}

// ---------- Exceptional / error case (observable) ----------

TEST(UnorderedRangeEqualsMatcherTest_958, PredicateExceptionPropagates_958) {
    std::vector<int> desired{1, 2};
    struct ThrowingEq {
        bool operator()(int, int) const {
            throw std::runtime_error("predicate failure");
        }
    } throwing_eq;

    UnorderedRangeEqualsMatcher<std::vector<int>, ThrowingEq> matcher(desired, throwing_eq);

    // Same size to encourage predicate evaluation during comparison
    std::vector<int> actual{2, 1};
    EXPECT_THROW(static_cast<void>(matcher.match(actual)), std::runtime_error);
}
