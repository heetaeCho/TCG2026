#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Matchers;

// =============================================================================
// Tests for UnorderedEqualsMatcher
// =============================================================================

class UnorderedEqualsMatcherTest_976 : public ::testing::Test {
protected:
    // Helper to create matcher and test match
    template<typename T>
    bool testMatch(const std::vector<T>& target, const std::vector<T>& candidate) {
        UnorderedEqualsMatcher<T, std::allocator<T>, std::allocator<T>> matcher(target);
        return matcher.match(candidate);
    }

    template<typename T>
    std::string testDescribe(const std::vector<T>& target) {
        UnorderedEqualsMatcher<T, std::allocator<T>, std::allocator<T>> matcher(target);
        return matcher.describe();
    }
};

// --- Normal operation tests ---

TEST_F(UnorderedEqualsMatcherTest_976, IdenticalVectorsMatch_976) {
    std::vector<int> target = {1, 2, 3, 4, 5};
    std::vector<int> candidate = {1, 2, 3, 4, 5};
    EXPECT_TRUE(testMatch(target, candidate));
}

TEST_F(UnorderedEqualsMatcherTest_976, ReorderedVectorsMatch_976) {
    std::vector<int> target = {1, 2, 3, 4, 5};
    std::vector<int> candidate = {5, 4, 3, 2, 1};
    EXPECT_TRUE(testMatch(target, candidate));
}

TEST_F(UnorderedEqualsMatcherTest_976, ShuffledVectorsMatch_976) {
    std::vector<int> target = {1, 2, 3, 4, 5};
    std::vector<int> candidate = {3, 1, 5, 2, 4};
    EXPECT_TRUE(testMatch(target, candidate));
}

TEST_F(UnorderedEqualsMatcherTest_976, EmptyVectorsMatch_976) {
    std::vector<int> target = {};
    std::vector<int> candidate = {};
    EXPECT_TRUE(testMatch(target, candidate));
}

TEST_F(UnorderedEqualsMatcherTest_976, SingleElementMatch_976) {
    std::vector<int> target = {42};
    std::vector<int> candidate = {42};
    EXPECT_TRUE(testMatch(target, candidate));
}

TEST_F(UnorderedEqualsMatcherTest_976, StringVectorsMatch_976) {
    std::vector<std::string> target = {"hello", "world", "foo"};
    std::vector<std::string> candidate = {"foo", "hello", "world"};
    EXPECT_TRUE(testMatch(target, candidate));
}

TEST_F(UnorderedEqualsMatcherTest_976, DuplicateElementsMatch_976) {
    std::vector<int> target = {1, 1, 2, 2, 3};
    std::vector<int> candidate = {2, 1, 3, 1, 2};
    EXPECT_TRUE(testMatch(target, candidate));
}

// --- Mismatch / Error cases ---

TEST_F(UnorderedEqualsMatcherTest_976, DifferentSizesDoNotMatch_976) {
    std::vector<int> target = {1, 2, 3};
    std::vector<int> candidate = {1, 2};
    EXPECT_FALSE(testMatch(target, candidate));
}

TEST_F(UnorderedEqualsMatcherTest_976, DifferentSizesLargerCandidateDoNotMatch_976) {
    std::vector<int> target = {1, 2};
    std::vector<int> candidate = {1, 2, 3};
    EXPECT_FALSE(testMatch(target, candidate));
}

TEST_F(UnorderedEqualsMatcherTest_976, DifferentElementsDoNotMatch_976) {
    std::vector<int> target = {1, 2, 3};
    std::vector<int> candidate = {4, 5, 6};
    EXPECT_FALSE(testMatch(target, candidate));
}

TEST_F(UnorderedEqualsMatcherTest_976, SameSizeDifferentValuesDoNotMatch_976) {
    std::vector<int> target = {1, 2, 3};
    std::vector<int> candidate = {1, 2, 4};
    EXPECT_FALSE(testMatch(target, candidate));
}

TEST_F(UnorderedEqualsMatcherTest_976, DifferentDuplicateCountsDoNotMatch_976) {
    std::vector<int> target = {1, 1, 2};
    std::vector<int> candidate = {1, 2, 2};
    EXPECT_FALSE(testMatch(target, candidate));
}

TEST_F(UnorderedEqualsMatcherTest_976, EmptyTargetNonEmptyCandidateDoNotMatch_976) {
    std::vector<int> target = {};
    std::vector<int> candidate = {1};
    EXPECT_FALSE(testMatch(target, candidate));
}

TEST_F(UnorderedEqualsMatcherTest_976, NonEmptyTargetEmptyCandidateDoNotMatch_976) {
    std::vector<int> target = {1};
    std::vector<int> candidate = {};
    EXPECT_FALSE(testMatch(target, candidate));
}

TEST_F(UnorderedEqualsMatcherTest_976, SingleElementMismatch_976) {
    std::vector<int> target = {1};
    std::vector<int> candidate = {2};
    EXPECT_FALSE(testMatch(target, candidate));
}

// --- Describe tests ---

TEST_F(UnorderedEqualsMatcherTest_976, DescribeContainsUnorderedEquals_976) {
    std::vector<int> target = {1, 2, 3};
    std::string description = testDescribe(target);
    EXPECT_NE(description.find("UnorderedEquals:"), std::string::npos);
}

TEST_F(UnorderedEqualsMatcherTest_976, DescribeContainsTargetElements_976) {
    std::vector<int> target = {1, 2, 3};
    std::string description = testDescribe(target);
    // The description should contain the stringified form of the target
    EXPECT_NE(description.find("1"), std::string::npos);
    EXPECT_NE(description.find("2"), std::string::npos);
    EXPECT_NE(description.find("3"), std::string::npos);
}

TEST_F(UnorderedEqualsMatcherTest_976, DescribeEmptyTarget_976) {
    std::vector<int> target = {};
    std::string description = testDescribe(target);
    EXPECT_NE(description.find("UnorderedEquals:"), std::string::npos);
}

TEST_F(UnorderedEqualsMatcherTest_976, DescribeStringVector_976) {
    std::vector<std::string> target = {"hello", "world"};
    std::string description = testDescribe(target);
    EXPECT_NE(description.find("UnorderedEquals:"), std::string::npos);
    EXPECT_NE(description.find("hello"), std::string::npos);
    EXPECT_NE(description.find("world"), std::string::npos);
}

// --- Boundary condition tests ---

TEST_F(UnorderedEqualsMatcherTest_976, LargeVectorsMatch_976) {
    std::vector<int> target(1000);
    std::iota(target.begin(), target.end(), 0);
    std::vector<int> candidate(target.rbegin(), target.rend());
    EXPECT_TRUE(testMatch(target, candidate));
}

TEST_F(UnorderedEqualsMatcherTest_976, LargeVectorsOneElementDifference_976) {
    std::vector<int> target(100);
    std::iota(target.begin(), target.end(), 0);
    std::vector<int> candidate(target);
    candidate.back() = -1;  // Change one element
    EXPECT_FALSE(testMatch(target, candidate));
}

TEST_F(UnorderedEqualsMatcherTest_976, AllSameElementsMatch_976) {
    std::vector<int> target(10, 5);
    std::vector<int> candidate(10, 5);
    EXPECT_TRUE(testMatch(target, candidate));
}

TEST_F(UnorderedEqualsMatcherTest_976, AllSameElementsDifferentCountDoNotMatch_976) {
    std::vector<int> target(10, 5);
    std::vector<int> candidate(11, 5);
    EXPECT_FALSE(testMatch(target, candidate));
}

TEST_F(UnorderedEqualsMatcherTest_976, NegativeNumbersMatch_976) {
    std::vector<int> target = {-3, -2, -1, 0, 1, 2, 3};
    std::vector<int> candidate = {3, -1, 0, 2, -3, 1, -2};
    EXPECT_TRUE(testMatch(target, candidate));
}

TEST_F(UnorderedEqualsMatcherTest_976, TwoElementsSwapped_976) {
    std::vector<int> target = {1, 2};
    std::vector<int> candidate = {2, 1};
    EXPECT_TRUE(testMatch(target, candidate));
}
