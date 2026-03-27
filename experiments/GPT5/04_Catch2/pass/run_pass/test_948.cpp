// File: tests/is_permutation_948_tests.cpp

#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <list>
#include <cctype>
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Detail::is_permutation;

namespace {

// Simple equality comparator for ints
struct IntEq {
    constexpr bool operator()(int a, int b) const noexcept { return a == b; }
};

} // namespace

// Normal operation: identical sequences -> true
TEST(IsPermutationTest_948, IdenticalSequences_948) {
    std::vector<int> a{1, 2, 3, 4, 5};
    std::vector<int> b{1, 2, 3, 4, 5};

    EXPECT_TRUE(is_permutation(a.begin(), a.end(), b.begin(), b.end(), IntEq{}));
}

// Normal operation: proper permutation with duplicates -> true
TEST(IsPermutationTest_948, PermutedWithDuplicates_948) {
    std::array<int, 6> a{{1, 2, 2, 3, 4, 4}};
    std::array<int, 6> b{{4, 2, 1, 4, 3, 2}}; // permutation

    EXPECT_TRUE(is_permutation(a.begin(), a.end(), b.begin(), b.end(), IntEq{}));
}

// Boundary: both empty ranges -> true
TEST(IsPermutationTest_948, BothEmpty_948) {
    std::vector<int> a;
    std::vector<int> b;

    EXPECT_TRUE(is_permutation(a.begin(), a.end(), b.begin(), b.end(), IntEq{}));
}

// Boundary: one empty, one non-empty -> false
TEST(IsPermutationTest_948, EmptyVsNonEmpty_948) {
    std::vector<int> a;
    std::vector<int> b{1};

    EXPECT_FALSE(is_permutation(a.begin(), a.end(), b.begin(), b.end(), IntEq{}));
    EXPECT_FALSE(is_permutation(b.begin(), b.end(), a.begin(), a.end(), IntEq{}));
}

// Error/negative observable case: same length but different element counts -> false
TEST(IsPermutationTest_948, SameLengthDifferentCounts_948) {
    std::vector<int> a{1, 2, 2, 3};
    std::vector<int> b{1, 1, 2, 3}; // different multiplicity of '1' and '2'

    EXPECT_FALSE(is_permutation(a.begin(), a.end(), b.begin(), b.end(), IntEq{}));
}

// Boundary: different lengths -> false
TEST(IsPermutationTest_948, DifferentLengths_948) {
    std::list<int> a{1, 2, 3, 4};
    std::list<int> b{1, 2, 3};

    EXPECT_FALSE(is_permutation(a.begin(), a.end(), b.begin(), b.end(), IntEq{}));
    EXPECT_FALSE(is_permutation(b.begin(), b.end(), a.begin(), a.end(), IntEq{}));
}

// Custom comparator: case-insensitive chars (observable via comparator usage) -> true
TEST(IsPermutationTest_948, CustomComparatorCaseInsensitive_948) {
    auto ci_eq = [](char lhs, char rhs) {
        return std::tolower(static_cast<unsigned char>(lhs)) ==
               std::tolower(static_cast<unsigned char>(rhs));
    };

    const char a[] = {'A', 'b', 'C', 'd'};
    const char b[] = {'c', 'D', 'a', 'B'}; // permutation ignoring case

    EXPECT_TRUE(is_permutation(std::begin(a), std::end(a),
                               std::begin(b), std::end(b),
                               ci_eq));
}

// Custom comparator: absolute-value equality on ints -> true
TEST(IsPermutationTest_948, CustomComparatorAbsoluteValue_948) {
    auto abs_eq = [](int x, int y) { return std::abs(x) == std::abs(y); };

    std::vector<int> a{ 1, -2, 3, -4, 5 };
    std::vector<int> b{ -5, 4, -3, 2, -1 }; // permutation by |value|

    EXPECT_TRUE(is_permutation(a.begin(), a.end(), b.begin(), b.end(), abs_eq));
}

// Early prefix-equality path: leading equal prefix, differing tails but still permutation -> true
TEST(IsPermutationTest_948, LeadingEqualPrefixPermutation_948) {
    // First two elements match in order; tails are a permutation
    std::vector<int> a{10, 20, 1, 2, 3, 4};
    std::vector<int> b{10, 20, 4, 3, 2, 1};

    EXPECT_TRUE(is_permutation(a.begin(), a.end(), b.begin(), b.end(), IntEq{}));
}

// Early termination path: leading equal prefix, but different total sizes -> false
TEST(IsPermutationTest_948, LeadingEqualPrefixDifferentSizes_948) {
    // First two elements equal; then one sequence ends earlier
    std::vector<int> a{10, 20, 1, 2};
    std::vector<int> b{10, 20, 1};

    EXPECT_FALSE(is_permutation(a.begin(), a.end(), b.begin(), b.end(), IntEq{}));
}

