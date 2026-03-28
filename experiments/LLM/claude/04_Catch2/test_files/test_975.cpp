#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Matchers;

// Test: Matching two identical vectors should return true
TEST(UnorderedEqualsMatcherTest_975, IdenticalVectors_975) {
    std::vector<int> target = {1, 2, 3, 4, 5};
    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(target);
    std::vector<int> vec = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: Matching two vectors that are permutations of each other should return true
TEST(UnorderedEqualsMatcherTest_975, PermutedVectors_975) {
    std::vector<int> target = {1, 2, 3, 4, 5};
    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(target);
    std::vector<int> vec = {5, 4, 3, 2, 1};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: Vectors with different sizes should return false
TEST(UnorderedEqualsMatcherTest_975, DifferentSizes_975) {
    std::vector<int> target = {1, 2, 3};
    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(target);
    std::vector<int> vec = {1, 2, 3, 4};
    EXPECT_FALSE(matcher.match(vec));
}

// Test: Empty vectors should match
TEST(UnorderedEqualsMatcherTest_975, EmptyVectors_975) {
    std::vector<int> target = {};
    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(target);
    std::vector<int> vec = {};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: Empty target with non-empty vec should not match
TEST(UnorderedEqualsMatcherTest_975, EmptyTargetNonEmptyVec_975) {
    std::vector<int> target = {};
    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(target);
    std::vector<int> vec = {1};
    EXPECT_FALSE(matcher.match(vec));
}

// Test: Non-empty target with empty vec should not match
TEST(UnorderedEqualsMatcherTest_975, NonEmptyTargetEmptyVec_975) {
    std::vector<int> target = {1};
    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(target);
    std::vector<int> vec = {};
    EXPECT_FALSE(matcher.match(vec));
}

// Test: Same size but different elements should not match
TEST(UnorderedEqualsMatcherTest_975, SameSizeDifferentElements_975) {
    std::vector<int> target = {1, 2, 3};
    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(target);
    std::vector<int> vec = {4, 5, 6};
    EXPECT_FALSE(matcher.match(vec));
}

// Test: Duplicate elements matching
TEST(UnorderedEqualsMatcherTest_975, DuplicateElementsMatch_975) {
    std::vector<int> target = {1, 1, 2, 2, 3};
    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(target);
    std::vector<int> vec = {2, 1, 3, 1, 2};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: Duplicate elements with different counts should not match
TEST(UnorderedEqualsMatcherTest_975, DuplicateElementsDifferentCounts_975) {
    std::vector<int> target = {1, 1, 2, 3, 3};
    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(target);
    std::vector<int> vec = {1, 2, 2, 3, 3};
    EXPECT_FALSE(matcher.match(vec));
}

// Test: Single element vectors that match
TEST(UnorderedEqualsMatcherTest_975, SingleElementMatch_975) {
    std::vector<int> target = {42};
    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(target);
    std::vector<int> vec = {42};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: Single element vectors that don't match
TEST(UnorderedEqualsMatcherTest_975, SingleElementNoMatch_975) {
    std::vector<int> target = {42};
    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(target);
    std::vector<int> vec = {99};
    EXPECT_FALSE(matcher.match(vec));
}

// Test: String vectors permuted
TEST(UnorderedEqualsMatcherTest_975, StringVectorsPermuted_975) {
    std::vector<std::string> target = {"hello", "world", "foo"};
    UnorderedEqualsMatcher<std::string, std::allocator<std::string>, std::allocator<std::string>> matcher(target);
    std::vector<std::string> vec = {"foo", "hello", "world"};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: String vectors not matching
TEST(UnorderedEqualsMatcherTest_975, StringVectorsNoMatch_975) {
    std::vector<std::string> target = {"hello", "world"};
    UnorderedEqualsMatcher<std::string, std::allocator<std::string>, std::allocator<std::string>> matcher(target);
    std::vector<std::string> vec = {"hello", "bar"};
    EXPECT_FALSE(matcher.match(vec));
}

// Test: All same elements match
TEST(UnorderedEqualsMatcherTest_975, AllSameElementsMatch_975) {
    std::vector<int> target = {7, 7, 7, 7};
    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(target);
    std::vector<int> vec = {7, 7, 7, 7};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: All same elements different counts
TEST(UnorderedEqualsMatcherTest_975, AllSameElementsDifferentSize_975) {
    std::vector<int> target = {7, 7, 7};
    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(target);
    std::vector<int> vec = {7, 7, 7, 7};
    EXPECT_FALSE(matcher.match(vec));
}

// Test: Large vector permutation
TEST(UnorderedEqualsMatcherTest_975, LargeVectorPermutation_975) {
    std::vector<int> target;
    for (int i = 0; i < 1000; ++i) {
        target.push_back(i);
    }
    std::vector<int> vec(target.rbegin(), target.rend());
    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(target);
    EXPECT_TRUE(matcher.match(vec));
}

// Test: describe() returns a non-empty string
TEST(UnorderedEqualsMatcherTest_975, DescribeReturnsNonEmpty_975) {
    std::vector<int> target = {1, 2, 3};
    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(target);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test: Negative numbers permutation
TEST(UnorderedEqualsMatcherTest_975, NegativeNumbersPermutation_975) {
    std::vector<int> target = {-3, -1, -2, 0};
    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(target);
    std::vector<int> vec = {0, -2, -3, -1};
    EXPECT_TRUE(matcher.match(vec));
}

// Test: Partial overlap should not match
TEST(UnorderedEqualsMatcherTest_975, PartialOverlap_975) {
    std::vector<int> target = {1, 2, 3};
    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(target);
    std::vector<int> vec = {1, 2, 4};
    EXPECT_FALSE(matcher.match(vec));
}

// Test: Matching with double type
TEST(UnorderedEqualsMatcherTest_975, DoubleTypePermutation_975) {
    std::vector<double> target = {1.1, 2.2, 3.3};
    UnorderedEqualsMatcher<double, std::allocator<double>, std::allocator<double>> matcher(target);
    std::vector<double> vec = {3.3, 1.1, 2.2};
    EXPECT_TRUE(matcher.match(vec));
}
