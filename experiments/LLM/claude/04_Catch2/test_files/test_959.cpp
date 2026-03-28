#include <string>
#include <vector>
#include <list>
#include <array>
#include <functional>

// Include Catch2 amalgamated header
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

#include <gtest/gtest.h>

using namespace Catch::Matchers;

class UnorderedRangeEqualsMatcherTest_959 : public ::testing::Test {
protected:
};

// Test that identical vectors match
TEST_F(UnorderedRangeEqualsMatcherTest_959, IdenticalVectorsMatch_959) {
    std::vector<int> desired = {1, 2, 3};
    std::vector<int> input = {1, 2, 3};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, std::equal_to<>>(
        desired, std::equal_to<>{});
    EXPECT_TRUE(matcher.match(input));
}

// Test that vectors with same elements in different order match
TEST_F(UnorderedRangeEqualsMatcherTest_959, SameElementsDifferentOrderMatch_959) {
    std::vector<int> desired = {1, 2, 3};
    std::vector<int> input = {3, 1, 2};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, std::equal_to<>>(
        desired, std::equal_to<>{});
    EXPECT_TRUE(matcher.match(input));
}

// Test that vectors with different elements do not match
TEST_F(UnorderedRangeEqualsMatcherTest_959, DifferentElementsDoNotMatch_959) {
    std::vector<int> desired = {1, 2, 3};
    std::vector<int> input = {4, 5, 6};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, std::equal_to<>>(
        desired, std::equal_to<>{});
    EXPECT_FALSE(matcher.match(input));
}

// Test that vectors with different sizes do not match
TEST_F(UnorderedRangeEqualsMatcherTest_959, DifferentSizesDoNotMatch_959) {
    std::vector<int> desired = {1, 2, 3};
    std::vector<int> input = {1, 2};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, std::equal_to<>>(
        desired, std::equal_to<>{});
    EXPECT_FALSE(matcher.match(input));
}

// Test with empty ranges
TEST_F(UnorderedRangeEqualsMatcherTest_959, EmptyRangesMatch_959) {
    std::vector<int> desired = {};
    std::vector<int> input = {};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, std::equal_to<>>(
        desired, std::equal_to<>{});
    EXPECT_TRUE(matcher.match(input));
}

// Test empty desired vs non-empty input
TEST_F(UnorderedRangeEqualsMatcherTest_959, EmptyDesiredNonEmptyInputDoNotMatch_959) {
    std::vector<int> desired = {};
    std::vector<int> input = {1};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, std::equal_to<>>(
        desired, std::equal_to<>{});
    EXPECT_FALSE(matcher.match(input));
}

// Test non-empty desired vs empty input
TEST_F(UnorderedRangeEqualsMatcherTest_959, NonEmptyDesiredEmptyInputDoNotMatch_959) {
    std::vector<int> desired = {1};
    std::vector<int> input = {};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, std::equal_to<>>(
        desired, std::equal_to<>{});
    EXPECT_FALSE(matcher.match(input));
}

// Test with duplicate elements that match
TEST_F(UnorderedRangeEqualsMatcherTest_959, DuplicateElementsMatch_959) {
    std::vector<int> desired = {1, 1, 2};
    std::vector<int> input = {2, 1, 1};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, std::equal_to<>>(
        desired, std::equal_to<>{});
    EXPECT_TRUE(matcher.match(input));
}

// Test with duplicate elements that do not match (different counts)
TEST_F(UnorderedRangeEqualsMatcherTest_959, DuplicateElementsDifferentCountsDoNotMatch_959) {
    std::vector<int> desired = {1, 1, 2};
    std::vector<int> input = {1, 2, 2};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, std::equal_to<>>(
        desired, std::equal_to<>{});
    EXPECT_FALSE(matcher.match(input));
}

// Test describe returns meaningful string
TEST_F(UnorderedRangeEqualsMatcherTest_959, DescribeContainsElements_959) {
    std::vector<int> desired = {1, 2, 3};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, std::equal_to<>>(
        desired, std::equal_to<>{});
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
    EXPECT_NE(description.find("unordered"), std::string::npos);
}

// Test with custom predicate
TEST_F(UnorderedRangeEqualsMatcherTest_959, CustomPredicateMatch_959) {
    std::vector<int> desired = {10, 20, 30};
    std::vector<int> input = {31, 11, 21};
    // Custom predicate: match if same tens digit
    auto predicate = [](int a, int b) { return (a / 10) == (b / 10); };
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, decltype(predicate)>(
        desired, predicate);
    EXPECT_TRUE(matcher.match(input));
}

// Test with custom predicate that does not match
TEST_F(UnorderedRangeEqualsMatcherTest_959, CustomPredicateNoMatch_959) {
    std::vector<int> desired = {10, 20, 30};
    std::vector<int> input = {41, 51, 61};
    auto predicate = [](int a, int b) { return (a / 10) == (b / 10); };
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, decltype(predicate)>(
        desired, predicate);
    EXPECT_FALSE(matcher.match(input));
}

// Test with different range types (list vs vector)
TEST_F(UnorderedRangeEqualsMatcherTest_959, DifferentRangeTypesMatch_959) {
    std::vector<int> desired = {3, 2, 1};
    std::list<int> input = {1, 2, 3};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, std::equal_to<>>(
        desired, std::equal_to<>{});
    EXPECT_TRUE(matcher.match(input));
}

// Test single element match
TEST_F(UnorderedRangeEqualsMatcherTest_959, SingleElementMatch_959) {
    std::vector<int> desired = {42};
    std::vector<int> input = {42};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, std::equal_to<>>(
        desired, std::equal_to<>{});
    EXPECT_TRUE(matcher.match(input));
}

// Test single element no match
TEST_F(UnorderedRangeEqualsMatcherTest_959, SingleElementNoMatch_959) {
    std::vector<int> desired = {42};
    std::vector<int> input = {43};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, std::equal_to<>>(
        desired, std::equal_to<>{});
    EXPECT_FALSE(matcher.match(input));
}

// Test with string elements
TEST_F(UnorderedRangeEqualsMatcherTest_959, StringElementsMatch_959) {
    std::vector<std::string> desired = {"hello", "world", "foo"};
    std::vector<std::string> input = {"foo", "hello", "world"};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<std::string>, std::equal_to<>>(
        desired, std::equal_to<>{});
    EXPECT_TRUE(matcher.match(input));
}

// Test with string elements that don't match
TEST_F(UnorderedRangeEqualsMatcherTest_959, StringElementsDoNotMatch_959) {
    std::vector<std::string> desired = {"hello", "world"};
    std::vector<std::string> input = {"hello", "bar"};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<std::string>, std::equal_to<>>(
        desired, std::equal_to<>{});
    EXPECT_FALSE(matcher.match(input));
}

// Test describe with empty desired
TEST_F(UnorderedRangeEqualsMatcherTest_959, DescribeEmptyDesired_959) {
    std::vector<int> desired = {};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, std::equal_to<>>(
        desired, std::equal_to<>{});
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
    EXPECT_NE(description.find("unordered"), std::string::npos);
}

// Test with all same elements
TEST_F(UnorderedRangeEqualsMatcherTest_959, AllSameElementsMatch_959) {
    std::vector<int> desired = {5, 5, 5};
    std::vector<int> input = {5, 5, 5};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, std::equal_to<>>(
        desired, std::equal_to<>{});
    EXPECT_TRUE(matcher.match(input));
}

// Test partial overlap does not match
TEST_F(UnorderedRangeEqualsMatcherTest_959, PartialOverlapDoesNotMatch_959) {
    std::vector<int> desired = {1, 2, 3};
    std::vector<int> input = {1, 2, 4};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, std::equal_to<>>(
        desired, std::equal_to<>{});
    EXPECT_FALSE(matcher.match(input));
}

// Test input longer than desired
TEST_F(UnorderedRangeEqualsMatcherTest_959, InputLongerThanDesiredDoesNotMatch_959) {
    std::vector<int> desired = {1, 2};
    std::vector<int> input = {1, 2, 3};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, std::equal_to<>>(
        desired, std::equal_to<>{});
    EXPECT_FALSE(matcher.match(input));
}

// Test with array type as input
TEST_F(UnorderedRangeEqualsMatcherTest_959, ArrayInputMatch_959) {
    std::vector<int> desired = {3, 1, 2};
    std::array<int, 3> input = {1, 2, 3};
    auto matcher = UnorderedRangeEqualsMatcher<std::vector<int>, std::equal_to<>>(
        desired, std::equal_to<>{});
    EXPECT_TRUE(matcher.match(input));
}
