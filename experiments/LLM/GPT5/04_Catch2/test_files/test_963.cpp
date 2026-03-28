// File: tests/UnorderedRangeEquals_initlist_963_tests.cpp

#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cctype>

// Include the provided header path from the prompt.
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Matchers::UnorderedRangeEquals;

// Helper to keep assertions concise.
template <typename MatcherT, typename RangeT>
static bool Matches(const MatcherT& m, const RangeT& r) {
    return m.match(r);
}

// ========== Normal operation ==========

TEST(UnorderedRangeEqualsMatcher_963, SameElementsDifferentOrder_963) {
    auto matcher = UnorderedRangeEquals({1, 2, 3});
    std::vector<int> actual{3, 1, 2};
    EXPECT_TRUE(Matches(matcher, actual));
}

TEST(UnorderedRangeEqualsMatcher_963, DuplicatesWithSameMultiplicity_963) {
    auto matcher = UnorderedRangeEquals({1, 1, 2, 3, 3});
    std::list<int> actual{3, 1, 3, 2, 1};
    EXPECT_TRUE(Matches(matcher, actual));
}

// ========== Boundary conditions ==========

TEST(UnorderedRangeEqualsMatcher_963, BothEmpty_963) {
    auto matcher = UnorderedRangeEquals({}); // initializer_list<int> empty
    std::vector<int> actual{};
    EXPECT_TRUE(Matches(matcher, actual));
}

TEST(UnorderedRangeEqualsMatcher_963, OneEmptyOneNonEmpty_963) {
    auto matcher = UnorderedRangeEquals({}); // expected empty
    std::vector<int> actual{42};
    EXPECT_FALSE(Matches(matcher, actual));
}

TEST(UnorderedRangeEqualsMatcher_963, SameSetDifferentCounts_963) {
    auto matcher = UnorderedRangeEquals({1, 1, 2}); // multiplicity matters
    std::vector<int> actual{1, 2, 2};
    EXPECT_FALSE(Matches(matcher, actual));
}

// ========== Exceptional / error-like observable cases ==========
// (There is no throwing/exception behavior in the interface we can observe;
// we validate only boolean match outcomes for edge scenarios.)

TEST(UnorderedRangeEqualsMatcher_963, ExtraElementInActual_963) {
    auto matcher = UnorderedRangeEquals({10, 20});
    std::vector<int> actual{10, 20, 30};
    EXPECT_FALSE(Matches(matcher, actual));
}

TEST(UnorderedRangeEqualsMatcher_963, MissingElementInActual_963) {
    auto matcher = UnorderedRangeEquals({10, 20, 30});
    std::list<int> actual{10, 30};
    EXPECT_FALSE(Matches(matcher, actual));
}

// ========== Custom predicate (verification of external interaction via parameter) ==========

static bool CaseInsensitiveEq(const std::string& a, const std::string& b) {
    auto lower = [](const std::string& s) {
        std::string t; t.reserve(s.size());
        for (unsigned char ch : s) t.push_back(static_cast<char>(std::tolower(ch)));
        return t;
    };
    return lower(a) == lower(b);
}

TEST(UnorderedRangeEqualsMatcher_963, CaseInsensitiveStrings_Match_963) {
    auto matcher = UnorderedRangeEquals<std::string>( { "Alpha", "beta", "Gamma" }, CaseInsensitiveEq );
    std::vector<std::string> actual{ "gamma", "ALPHA", "BETA" };
    EXPECT_TRUE(Matches(matcher, actual));
}

TEST(UnorderedRangeEqualsMatcher_963, CaseInsensitiveStrings_MultiplicityMatters_963) {
    auto matcher = UnorderedRangeEquals<std::string>( { "one", "one", "two" }, CaseInsensitiveEq );
    std::list<std::string> actual{ "ONE", "TWO" }; // missing one "one"
    EXPECT_FALSE(Matches(matcher, actual));
}

// ========== Heterogeneous container types (interface flexibility) ==========

TEST(UnorderedRangeEqualsMatcher_963, VectorVsListContainers_963) {
    auto matcher = UnorderedRangeEquals({4, 5, 6, 6});
    std::list<int> actual{6, 4, 6, 5};
    EXPECT_TRUE(Matches(matcher, actual));
}

