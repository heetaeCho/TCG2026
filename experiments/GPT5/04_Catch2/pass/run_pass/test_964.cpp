// File: tests/vector_contains_element_matcher_964_test.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Matchers::VectorContainsElementMatcher;

namespace {

// A simple custom type to verify that the matcher relies on operator==
// and not on identity or internal details.
struct Item {
    int id;
    std::string name;

    friend bool operator==(const Item& a, const Item& b) {
        // Equality intentionally defined by `id` only (observable via operator==)
        return a.id == b.id;
    }
};

} // namespace

// ---------- Normal operation ----------

TEST(VectorContainsElementMatcherTest_964, EmptyVector_NoMatch_964) {
    int needle = 42;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(needle);

    const std::vector<int> v; // empty
    EXPECT_FALSE(matcher.match(v));
}

TEST(VectorContainsElementMatcherTest_964, SingleElement_MatchWhenEqual_964) {
    int needle = 7;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(needle);

    const std::vector<int> v{7};
    EXPECT_TRUE(matcher.match(v));
}

TEST(VectorContainsElementMatcherTest_964, SingleElement_NoMatchWhenDifferent_964) {
    int needle = 7;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(needle);

    const std::vector<int> v{8};
    EXPECT_FALSE(matcher.match(v));
}

TEST(VectorContainsElementMatcherTest_964, MultipleElements_TrueIfAnyMatches_964) {
    int needle = 99;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(needle);

    const std::vector<int> v{1, 2, 3, 99, 5, 99};
    EXPECT_TRUE(matcher.match(v));
}

// ---------- Boundary-like cases ----------

TEST(VectorContainsElementMatcherTest_964, WorksWithStrings_964) {
    std::string needle = "target";
    VectorContainsElementMatcher<std::string, std::allocator<std::string>> matcher(needle);

    const std::vector<std::string> v{"alpha", "beta", "target", "gamma"};
    EXPECT_TRUE(matcher.match(v));
}

TEST(VectorContainsElementMatcherTest_964, ConstVector_IsAccepted_964) {
    int needle = -1;
    VectorContainsElementMatcher<int, std::allocator<int>> matcher(needle);

    const std::vector<int> v{0, 1, 2};
    // No mutation expected; just ensure const vector compiles and works
    EXPECT_FALSE(matcher.match(v));
}

// ---------- External interaction via operator== (custom type) ----------

TEST(VectorContainsElementMatcherTest_964, UsesOperatorEquality_ForCustomType_964) {
    Item needle{42, "x"};
    VectorContainsElementMatcher<Item, std::allocator<Item>> matcher(needle);

    // Same id (== true by our operator==), different names
    const std::vector<Item> v{
        {1, "a"},
        {42, "different-name"},
        {3, "c"}
    };
    EXPECT_TRUE(matcher.match(v));
}

TEST(VectorContainsElementMatcherTest_964, CustomType_NoMatchWhenOperatorEqualFalse_964) {
    Item needle{100, "ignored"};
    VectorContainsElementMatcher<Item, std::allocator<Item>> matcher(needle);

    const std::vector<Item> v{
        {1, "a"},
        {2, "b"},
        {3, "c"}
    };
    EXPECT_FALSE(matcher.match(v));
}

