#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <functional>

// We need to include the header that contains the is_permutation function
// and its dependencies (sentinel_distance, check_element_counts)
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

class IsPermutationTest_948 : public ::testing::Test {
protected:
    // Default comparator using equality
    template <typename T>
    static bool equal_cmp(const T& a, const T& b) {
        return a == b;
    }
};

// Test: Both ranges are empty - should return true
TEST_F(IsPermutationTest_948, BothEmptyRanges_948) {
    std::vector<int> v1;
    std::vector<int> v2;
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_TRUE(result);
}

// Test: Identical single-element ranges
TEST_F(IsPermutationTest_948, IdenticalSingleElement_948) {
    std::vector<int> v1 = {42};
    std::vector<int> v2 = {42};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_TRUE(result);
}

// Test: Different single-element ranges
TEST_F(IsPermutationTest_948, DifferentSingleElement_948) {
    std::vector<int> v1 = {1};
    std::vector<int> v2 = {2};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_FALSE(result);
}

// Test: Identical multi-element ranges (same order)
TEST_F(IsPermutationTest_948, IdenticalMultiElement_948) {
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {1, 2, 3, 4, 5};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_TRUE(result);
}

// Test: Simple permutation of two elements
TEST_F(IsPermutationTest_948, SimplePermutationTwoElements_948) {
    std::vector<int> v1 = {1, 2};
    std::vector<int> v2 = {2, 1};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_TRUE(result);
}

// Test: Permutation of multiple elements
TEST_F(IsPermutationTest_948, PermutationMultipleElements_948) {
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {5, 3, 1, 4, 2};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_TRUE(result);
}

// Test: Different lengths - first longer
TEST_F(IsPermutationTest_948, DifferentLengthsFirstLonger_948) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_FALSE(result);
}

// Test: Different lengths - second longer
TEST_F(IsPermutationTest_948, DifferentLengthsSecondLonger_948) {
    std::vector<int> v1 = {1, 2};
    std::vector<int> v2 = {1, 2, 3};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_FALSE(result);
}

// Test: First range empty, second non-empty
TEST_F(IsPermutationTest_948, FirstEmptySecondNonEmpty_948) {
    std::vector<int> v1;
    std::vector<int> v2 = {1};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_FALSE(result);
}

// Test: First range non-empty, second empty
TEST_F(IsPermutationTest_948, FirstNonEmptySecondEmpty_948) {
    std::vector<int> v1 = {1};
    std::vector<int> v2;
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_FALSE(result);
}

// Test: Duplicate elements - valid permutation
TEST_F(IsPermutationTest_948, DuplicateElementsValidPermutation_948) {
    std::vector<int> v1 = {1, 1, 2, 2, 3};
    std::vector<int> v2 = {2, 1, 3, 1, 2};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_TRUE(result);
}

// Test: Duplicate elements - invalid permutation (different counts)
TEST_F(IsPermutationTest_948, DuplicateElementsDifferentCounts_948) {
    std::vector<int> v1 = {1, 1, 2, 3, 3};
    std::vector<int> v2 = {1, 2, 2, 3, 3};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_FALSE(result);
}

// Test: All elements the same - same length
TEST_F(IsPermutationTest_948, AllSameElementsSameLength_948) {
    std::vector<int> v1 = {5, 5, 5, 5};
    std::vector<int> v2 = {5, 5, 5, 5};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_TRUE(result);
}

// Test: Same elements but different lengths (all same value)
TEST_F(IsPermutationTest_948, AllSameElementsDifferentLength_948) {
    std::vector<int> v1 = {5, 5, 5};
    std::vector<int> v2 = {5, 5, 5, 5};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_FALSE(result);
}

// Test: Common prefix followed by permutation
TEST_F(IsPermutationTest_948, CommonPrefixThenPermutation_948) {
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {1, 2, 5, 3, 4};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_TRUE(result);
}

// Test: Common prefix followed by non-permutation
TEST_F(IsPermutationTest_948, CommonPrefixThenNonPermutation_948) {
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {1, 2, 3, 6, 7};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_FALSE(result);
}

// Test: Using custom comparator (case-insensitive string comparison)
TEST_F(IsPermutationTest_948, CustomComparatorStrings_948) {
    std::vector<std::string> v1 = {"Hello", "World"};
    std::vector<std::string> v2 = {"World", "Hello"};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        [](const std::string& a, const std::string& b) { return a == b; }
    );
    
    EXPECT_TRUE(result);
}

// Test: Using a custom comparator that considers only modulus
TEST_F(IsPermutationTest_948, CustomComparatorModulus_948) {
    std::vector<int> v1 = {1, 12, 23};
    std::vector<int> v2 = {23, 1, 12};
    
    auto mod10_cmp = [](int a, int b) { return (a % 10) == (b % 10); };
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        mod10_cmp
    );
    
    EXPECT_TRUE(result);
}

// Test: Completely reversed range is a permutation
TEST_F(IsPermutationTest_948, ReversedRange_948) {
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {5, 4, 3, 2, 1};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_TRUE(result);
}

// Test: Large identical prefix optimization path
TEST_F(IsPermutationTest_948, LargeCommonPrefix_948) {
    std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 11};
    std::vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_TRUE(result);
}

// Test: Same values but different element present
TEST_F(IsPermutationTest_948, SameSizeDifferentElements_948) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, 4};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_FALSE(result);
}

// Test: Negative numbers
TEST_F(IsPermutationTest_948, NegativeNumbers_948) {
    std::vector<int> v1 = {-3, -1, -2};
    std::vector<int> v2 = {-1, -2, -3};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_TRUE(result);
}

// Test: Mixed positive and negative numbers
TEST_F(IsPermutationTest_948, MixedPositiveNegative_948) {
    std::vector<int> v1 = {-1, 0, 1};
    std::vector<int> v2 = {1, -1, 0};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_TRUE(result);
}

// Test: Single element ranges that are different
TEST_F(IsPermutationTest_948, SingleElementDifferent_948) {
    std::vector<int> v1 = {0};
    std::vector<int> v2 = {1};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_FALSE(result);
}

// Test: Duplicate elements with different distributions but same length
TEST_F(IsPermutationTest_948, DuplicatesWrongDistribution_948) {
    std::vector<int> v1 = {1, 1, 1, 2};
    std::vector<int> v2 = {1, 2, 2, 2};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_FALSE(result);
}

// Test: Using char type
TEST_F(IsPermutationTest_948, CharType_948) {
    std::vector<char> v1 = {'a', 'b', 'c'};
    std::vector<char> v2 = {'c', 'a', 'b'};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<char>{}
    );
    
    EXPECT_TRUE(result);
}

// Test: Using double type
TEST_F(IsPermutationTest_948, DoubleType_948) {
    std::vector<double> v1 = {1.5, 2.5, 3.5};
    std::vector<double> v2 = {3.5, 1.5, 2.5};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        [](double a, double b) { return a == b; }
    );
    
    EXPECT_TRUE(result);
}

// Test: Entire prefix matches, then divergence at the end with same length but not permutation
TEST_F(IsPermutationTest_948, PrefixMatchDivergenceNotPermutation_948) {
    std::vector<int> v1 = {1, 2, 3, 4, 5, 6};
    std::vector<int> v2 = {1, 2, 3, 4, 5, 7};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_FALSE(result);
}

// Test: Three identical elements
TEST_F(IsPermutationTest_948, ThreeIdenticalElements_948) {
    std::vector<int> v1 = {7, 7, 7};
    std::vector<int> v2 = {7, 7, 7};
    
    bool result = Catch::Detail::is_permutation(
        v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::equal_to<int>{}
    );
    
    EXPECT_TRUE(result);
}
