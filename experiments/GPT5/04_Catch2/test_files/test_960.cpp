// File: tests/range_equals_matcher_960_test.cpp

#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <array>
#include <string>
#include <cctype>

// SUT
#include "Catch2/extras/catch_amalgamated.hpp"

namespace {
using Catch::Matchers::RangeEquals;

// Helper: case-insensitive equality for std::string
struct CaseInsensitiveEqStr {
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
} // namespace

// Normal operation: equal vectors
TEST(RangeEqualsMatcherTest_960, MatchesEqualVectors_960) {
    std::vector<int> actual{1, 2, 3};
    auto m = RangeEquals(std::vector<int>{1, 2, 3});
    EXPECT_TRUE(m.match(actual));
}

// Boundary: both empty ranges
TEST(RangeEqualsMatcherTest_960, EmptyRangesMatch_960) {
    std::vector<int> actual;
    auto m = RangeEquals(std::vector<int>{});
    EXPECT_TRUE(m.match(actual));
}

// Boundary: different sizes
TEST(RangeEqualsMatcherTest_960, MismatchDifferentSizes_960) {
    std::vector<int> actual{1, 2};
    auto m = RangeEquals(std::vector<int>{1, 2, 3});
    EXPECT_FALSE(m.match(actual));
}

// Boundary: different order
TEST(RangeEqualsMatcherTest_960, MismatchDifferentOrder_960) {
    std::vector<int> actual{1, 3, 2};
    auto m = RangeEquals(std::vector<int>{1, 2, 3});
    EXPECT_FALSE(m.match(actual));
}

// Normal operation: works with initializer_list as expected range
TEST(RangeEqualsMatcherTest_960, WorksWithInitializerList_960) {
    std::vector<char> actual{'a', 'b', 'c'};
    auto m = RangeEquals({'a', 'b', 'c'});
    EXPECT_TRUE(m.match(actual));
}

// Normal operation: heterogeneous range types (expected=list, actual=vector)
TEST(RangeEqualsMatcherTest_960, HeterogeneousRangeTypes_960) {
    std::vector<int> actual{10, 20, 30};
    std::list<int> expected{10, 20, 30};
    auto m = RangeEquals(expected);
    EXPECT_TRUE(m.match(actual));
}

// Normal operation: C-style arrays
TEST(RangeEqualsMatcherTest_960, WorksWithCArray_960) {
    int actual[3] = {4, 5, 6};
    int expected[3] = {4, 5, 6};
    auto m = RangeEquals(expected);
    EXPECT_TRUE(m.match(actual));
}

// Normal operation: std::array
TEST(RangeEqualsMatcherTest_960, WorksWithStdArray_960) {
    std::array<int, 4> actual{{7, 8, 9, 10}};
    auto m = RangeEquals(std::array<int, 4>{{7, 8, 9, 10}});
    EXPECT_TRUE(m.match(actual));
}

// Custom predicate: modulo equality
TEST(RangeEqualsMatcherTest_960, CustomPredicateModulo_960) {
    std::vector<int> actual{1, 2, 3};
    std::vector<int> expected{4, 5, 6};
    auto pred = [](int a, int b) { return (a % 3) == (b % 3); };
    auto m = RangeEquals(expected, pred);
    EXPECT_TRUE(m.match(actual));
}

// Custom predicate: case-insensitive strings
TEST(RangeEqualsMatcherTest_960, CustomPredicateCaseInsensitive_960) {
    std::vector<std::string> actual{"Hello", "WORLD"};
    std::vector<std::string> expected{"hello", "world"};
    auto m = RangeEquals(expected, CaseInsensitiveEqStr{});
    EXPECT_TRUE(m.match(actual));
}

// External interaction: verifies the provided predicate is invoked
TEST(RangeEqualsMatcherTest_960, InvokesPredicate_960) {
    std::vector<int> actual{1, 2, 3};
    std::vector<int> expected{1, 2, 3};

    int call_count = 0;
    auto counting_pred = [&](int a, int b) {
        ++call_count;
        return a == b;
    };

    auto m = RangeEquals(expected, counting_pred);
    (void)m.match(actual);

    // We don’t assert an exact count (that would assume internal strategy),
    // only that the predicate was used at least once.
    EXPECT_GT(call_count, 0);
}

// Robustness: matcher created from a temporary expected range remains usable
TEST(RangeEqualsMatcherTest_960, TemporaryExpectedLifetime_960) {
    std::vector<int> actual{42, 43, 44};
    auto m = RangeEquals(std::vector<int>{42, 43, 44}); // temporary passed in
    EXPECT_TRUE(m.match(actual));
}

// Describe() should be non-empty (without relying on specific wording)
TEST(RangeEqualsMatcherTest_960, DescribeIsNonEmpty_960) {
    auto m = RangeEquals(std::vector<int>{1, 2, 3});
    std::string desc = m.describe();
    EXPECT_FALSE(desc.empty());
}
