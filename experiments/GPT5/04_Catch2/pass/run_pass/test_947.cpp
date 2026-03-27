// File: check_element_counts_947_tests.cpp

#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <string>
#include <cctype>
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Detail::check_element_counts;

namespace {

// Simple case-insensitive comparator for std::string
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

// Comparator that treats numbers as equal if their absolute values match
struct AbsEq {
    bool operator()(int a, int b) const {
        return (a < 0 ? -a : a) == (b < 0 ? -b : b);
    }
};

} // namespace

// Normal operation: identical multisets → true
TEST(CheckElementCountsTest_947, IdenticalMultisetsReturnTrue_947) {
    std::vector<int> a{1, 2, 2, 3};
    std::vector<int> b{1, 2, 2, 3};
    EXPECT_TRUE(check_element_counts(a.begin(), a.end(), b.begin(), b.end(), std::equal_to<int>{}));
}

// Normal operation: same counts, different order → true
TEST(CheckElementCountsTest_947, PermutedOrderStillTrue_947) {
    std::list<int> a{4, 5, 5, 6};
    std::vector<int> b{6, 5, 4, 5};
    EXPECT_TRUE(check_element_counts(a.begin(), a.end(), b.begin(), b.end(), std::equal_to<int>{}));
}

// Boundary: both ranges empty → true
TEST(CheckElementCountsTest_947, BothEmptyRangesReturnTrue_947) {
    std::vector<int> a;
    std::vector<int> b;
    EXPECT_TRUE(check_element_counts(a.begin(), a.end(), b.begin(), b.end(), std::equal_to<int>{}));
}

// Boundary/Asymmetry: first empty, second non-empty → true
// (Function only verifies counts of elements present in the first range.)
TEST(CheckElementCountsTest_947, FirstEmptySecondNonEmptyReturnsTrue_947) {
    std::vector<int> a;
    std::vector<int> b{10, 20, 20};
    EXPECT_TRUE(check_element_counts(a.begin(), a.end(), b.begin(), b.end(), std::equal_to<int>{}));
}

// Error case: element missing in second range → false
TEST(CheckElementCountsTest_947, MissingElementInSecondReturnsFalse_947) {
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{1, 2}; // 3 is missing
    EXPECT_FALSE(check_element_counts(a.begin(), a.end(), b.begin(), b.end(), std::equal_to<int>{}));
}

// Error case: duplicate count mismatch → false
TEST(CheckElementCountsTest_947, DuplicateCountMismatchReturnsFalse_947) {
    std::vector<int> a{7, 7, 8};
    std::vector<int> b{7, 8}; // '7' count differs
    EXPECT_FALSE(check_element_counts(a.begin(), a.end(), b.begin(), b.end(), std::equal_to<int>{}));
}

// Custom comparator: case-insensitive string equality
TEST(CheckElementCountsTest_947, CaseInsensitiveComparator_947) {
    std::vector<std::string> a{"Alpha", "beta", "Beta"};
    std::vector<std::string> b{"ALPHA", "BETA", "beta"};
    EXPECT_TRUE(check_element_counts(a.begin(), a.end(), b.begin(), b.end(), CaseInsensitiveEq{}));
}

// Custom comparator: absolute-value equality
TEST(CheckElementCountsTest_947, AbsoluteValueComparator_947) {
    std::vector<int> a{1, -1, 2, -2, -2};
    std::vector<int> b{-1, 1, -2, 2, 2};
    EXPECT_TRUE(check_element_counts(a.begin(), a.end(), b.begin(), b.end(), AbsEq{}));
}

// Error-ish edge: first has element not matched by abs comparator counts in second → false
TEST(CheckElementCountsTest_947, AbsoluteValueCountsMismatchReturnsFalse_947) {
    std::vector<int> a{3, -3, 3}; // |3| appears 3 times
    std::vector<int> b{-3, 3};    // |3| appears 2 times
    EXPECT_FALSE(check_element_counts(a.begin(), a.end(), b.begin(), b.end(), AbsEq{}));
}

// Asymmetry check: second has extra distinct elements → still true
TEST(CheckElementCountsTest_947, SecondHasExtraElementsStillTrue_947) {
    std::vector<int> a{9, 9};
    std::vector<int> b{9, 9, 10, 11}; // extras present only in second
    EXPECT_TRUE(check_element_counts(a.begin(), a.end(), b.begin(), b.end(), std::equal_to<int>{}));
}
