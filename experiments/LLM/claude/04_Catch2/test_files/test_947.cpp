#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <functional>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// Helper comparator - standard equality via less-than
struct DefaultComparator {
    template <typename T>
    constexpr bool operator()(const T& a, const T& b) const {
        return a == b;
    }
};

// Test fixture
class CheckElementCountsTest_947 : public ::testing::Test {
protected:
    DefaultComparator cmp;
};

// Both ranges empty - should return true
TEST_F(CheckElementCountsTest_947, BothRangesEmpty_947) {
    std::vector<int> range1;
    std::vector<int> range2;
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_TRUE(result);
}

// First range empty, second range non-empty - should return true
// (there are no elements in range1 to check against range2)
TEST_F(CheckElementCountsTest_947, FirstRangeEmptySecondNonEmpty_947) {
    std::vector<int> range1;
    std::vector<int> range2 = {1, 2, 3};
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_TRUE(result);
}

// First range non-empty, second range empty - should return false
TEST_F(CheckElementCountsTest_947, FirstNonEmptySecondEmpty_947) {
    std::vector<int> range1 = {1, 2, 3};
    std::vector<int> range2;
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_FALSE(result);
}

// Identical single element ranges
TEST_F(CheckElementCountsTest_947, SingleElementIdentical_947) {
    std::vector<int> range1 = {42};
    std::vector<int> range2 = {42};
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_TRUE(result);
}

// Single element ranges with different values
TEST_F(CheckElementCountsTest_947, SingleElementDifferent_947) {
    std::vector<int> range1 = {1};
    std::vector<int> range2 = {2};
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_FALSE(result);
}

// Same elements, same counts, same order
TEST_F(CheckElementCountsTest_947, SameElementsSameOrder_947) {
    std::vector<int> range1 = {1, 2, 3, 4, 5};
    std::vector<int> range2 = {1, 2, 3, 4, 5};
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_TRUE(result);
}

// Same elements, same counts, different order (permutation)
TEST_F(CheckElementCountsTest_947, SameElementsDifferentOrder_947) {
    std::vector<int> range1 = {3, 1, 4, 1, 5};
    std::vector<int> range2 = {1, 1, 3, 5, 4};
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_TRUE(result);
}

// Same elements but different counts
TEST_F(CheckElementCountsTest_947, SameElementsDifferentCounts_947) {
    std::vector<int> range1 = {1, 1, 2};
    std::vector<int> range2 = {1, 2, 2};
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_FALSE(result);
}

// Element in range1 not present in range2
TEST_F(CheckElementCountsTest_947, ElementMissingInSecondRange_947) {
    std::vector<int> range1 = {1, 2, 3};
    std::vector<int> range2 = {1, 2, 4};
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_FALSE(result);
}

// Duplicates in both ranges with matching counts
TEST_F(CheckElementCountsTest_947, DuplicatesMatchingCounts_947) {
    std::vector<int> range1 = {5, 5, 5, 3, 3};
    std::vector<int> range2 = {3, 5, 3, 5, 5};
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_TRUE(result);
}

// Duplicates in both ranges with non-matching counts
TEST_F(CheckElementCountsTest_947, DuplicatesNonMatchingCounts_947) {
    std::vector<int> range1 = {5, 5, 5, 3, 3};
    std::vector<int> range2 = {3, 5, 3, 3, 5};
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_FALSE(result);
}

// All same elements, matching counts
TEST_F(CheckElementCountsTest_947, AllSameElementsMatchingCounts_947) {
    std::vector<int> range1 = {7, 7, 7};
    std::vector<int> range2 = {7, 7, 7};
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_TRUE(result);
}

// All same elements, different counts
TEST_F(CheckElementCountsTest_947, AllSameElementsDifferentCounts_947) {
    std::vector<int> range1 = {7, 7, 7};
    std::vector<int> range2 = {7, 7};
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_FALSE(result);
}

// Range1 is subset of range2 (range2 has extra elements)
// check_element_counts checks from range1's perspective only
TEST_F(CheckElementCountsTest_947, Range1SubsetOfRange2_947) {
    std::vector<int> range1 = {1, 2};
    std::vector<int> range2 = {1, 2, 3};
    
    // range1 has 1x1 and 1x2; range2 has 1x1 and 1x2
    // counts match for elements in range1, so should return true
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_TRUE(result);
}

// Range2 is subset of range1 (range1 has extra elements)
TEST_F(CheckElementCountsTest_947, Range2SubsetOfRange1_947) {
    std::vector<int> range1 = {1, 2, 3};
    std::vector<int> range2 = {1, 2};
    
    // Element 3 has count 0 in range2, should return false
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_FALSE(result);
}

// Test with strings
TEST_F(CheckElementCountsTest_947, WorksWithStrings_947) {
    std::vector<std::string> range1 = {"hello", "world", "hello"};
    std::vector<std::string> range2 = {"hello", "hello", "world"};
    
    auto str_cmp = [](const std::string& a, const std::string& b) { return a == b; };
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        str_cmp
    );
    
    EXPECT_TRUE(result);
}

// Test with strings - different counts
TEST_F(CheckElementCountsTest_947, WorksWithStringsDifferentCounts_947) {
    std::vector<std::string> range1 = {"hello", "world", "hello"};
    std::vector<std::string> range2 = {"hello", "world", "world"};
    
    auto str_cmp = [](const std::string& a, const std::string& b) { return a == b; };
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        str_cmp
    );
    
    EXPECT_FALSE(result);
}

// Negative numbers
TEST_F(CheckElementCountsTest_947, NegativeNumbers_947) {
    std::vector<int> range1 = {-1, -2, -3};
    std::vector<int> range2 = {-3, -1, -2};
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_TRUE(result);
}

// Large range with same permutation
TEST_F(CheckElementCountsTest_947, LargeRangePermutation_947) {
    std::vector<int> range1;
    std::vector<int> range2;
    for (int i = 0; i < 100; ++i) {
        range1.push_back(i % 10);
        range2.push_back(i % 10);
    }
    // Reverse range2 to make it a different permutation
    std::reverse(range2.begin(), range2.end());
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_TRUE(result);
}

// Custom comparator that considers elements equal modulo some value
TEST_F(CheckElementCountsTest_947, CustomComparatorModulo_947) {
    std::vector<int> range1 = {1, 2, 3};
    std::vector<int> range2 = {11, 12, 13};
    
    // Comparator that considers values equal if they have the same remainder mod 10
    auto mod_cmp = [](int a, int b) { return (a % 10) == (b % 10); };
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        mod_cmp
    );
    
    EXPECT_TRUE(result);
}

// Custom comparator - non-matching
TEST_F(CheckElementCountsTest_947, CustomComparatorNonMatching_947) {
    std::vector<int> range1 = {1, 1, 2};
    std::vector<int> range2 = {11, 22, 12};
    
    auto mod_cmp = [](int a, int b) { return (a % 10) == (b % 10); };
    
    // range1: 1 appears 2 times (mod 10), 2 appears 1 time
    // range2: mod 10 -> 1 appears 1 time (11), 2 appears 2 times (22, 12)
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        mod_cmp
    );
    
    EXPECT_FALSE(result);
}

// Zero elements
TEST_F(CheckElementCountsTest_947, ZeroValueElements_947) {
    std::vector<int> range1 = {0, 0, 0};
    std::vector<int> range2 = {0, 0, 0};
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_TRUE(result);
}

// First element missing from range2
TEST_F(CheckElementCountsTest_947, FirstElementMissingFromRange2_947) {
    std::vector<int> range1 = {99, 1, 2};
    std::vector<int> range2 = {1, 2, 3};
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_FALSE(result);
}

// Last element missing from range2
TEST_F(CheckElementCountsTest_947, LastElementMissingFromRange2_947) {
    std::vector<int> range1 = {1, 2, 99};
    std::vector<int> range2 = {1, 2, 3};
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_FALSE(result);
}

// Two elements, swapped
TEST_F(CheckElementCountsTest_947, TwoElementsSwapped_947) {
    std::vector<int> range1 = {1, 2};
    std::vector<int> range2 = {2, 1};
    
    bool result = Catch::Detail::check_element_counts(
        range1.begin(), range1.end(),
        range2.begin(), range2.end(),
        cmp
    );
    
    EXPECT_TRUE(result);
}
