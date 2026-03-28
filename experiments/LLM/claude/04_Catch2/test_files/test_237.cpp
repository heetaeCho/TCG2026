#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <list>
#include <array>
#include <set>
#include <map>
#include <deque>

#include "catch2/matchers/catch_matchers_container_properties.hpp"

using Catch::Matchers::HasSizeMatcher;

// Test that describe() returns the correct string for size 0
TEST(HasSizeMatcherTest_237, DescribeReturnsCorrectStringForSizeZero_237) {
    HasSizeMatcher matcher(0);
    std::string description = matcher.describe();
    EXPECT_EQ(description, "has size == 0");
}

// Test that describe() returns the correct string for a positive size
TEST(HasSizeMatcherTest_237, DescribeReturnsCorrectStringForPositiveSize_237) {
    HasSizeMatcher matcher(42);
    std::string description = matcher.describe();
    EXPECT_EQ(description, "has size == 42");
}

// Test that describe() returns the correct string for a large size
TEST(HasSizeMatcherTest_237, DescribeReturnsCorrectStringForLargeSize_237) {
    HasSizeMatcher matcher(1000000);
    std::string description = matcher.describe();
    EXPECT_EQ(description, "has size == 1000000");
}

// Test that describe() returns the correct string for size 1
TEST(HasSizeMatcherTest_237, DescribeReturnsCorrectStringForSizeOne_237) {
    HasSizeMatcher matcher(1);
    std::string description = matcher.describe();
    EXPECT_EQ(description, "has size == 1");
}

// Test match with a vector that matches the target size
TEST(HasSizeMatcherTest_237, MatchReturnsTrueForVectorWithMatchingSize_237) {
    HasSizeMatcher matcher(3);
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

// Test match with a vector that does not match the target size
TEST(HasSizeMatcherTest_237, MatchReturnsFalseForVectorWithNonMatchingSize_237) {
    HasSizeMatcher matcher(5);
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

// Test match with an empty vector and target size 0
TEST(HasSizeMatcherTest_237, MatchReturnsTrueForEmptyVectorWithSizeZero_237) {
    HasSizeMatcher matcher(0);
    std::vector<int> v;
    EXPECT_TRUE(matcher.match(v));
}

// Test match with an empty vector and target size non-zero
TEST(HasSizeMatcherTest_237, MatchReturnsFalseForEmptyVectorWithNonZeroSize_237) {
    HasSizeMatcher matcher(1);
    std::vector<int> v;
    EXPECT_FALSE(matcher.match(v));
}

// Test match with a string container
TEST(HasSizeMatcherTest_237, MatchWorksWithString_237) {
    HasSizeMatcher matcher(5);
    std::string s = "hello";
    EXPECT_TRUE(matcher.match(s));
}

// Test match with a string that does not match
TEST(HasSizeMatcherTest_237, MatchReturnsFalseForStringWithNonMatchingSize_237) {
    HasSizeMatcher matcher(3);
    std::string s = "hello";
    EXPECT_FALSE(matcher.match(s));
}

// Test match with a list container
TEST(HasSizeMatcherTest_237, MatchWorksWithList_237) {
    HasSizeMatcher matcher(2);
    std::list<double> l = {1.0, 2.0};
    EXPECT_TRUE(matcher.match(l));
}

// Test match with a set container
TEST(HasSizeMatcherTest_237, MatchWorksWithSet_237) {
    HasSizeMatcher matcher(3);
    std::set<int> s = {10, 20, 30};
    EXPECT_TRUE(matcher.match(s));
}

// Test match with a map container
TEST(HasSizeMatcherTest_237, MatchWorksWithMap_237) {
    HasSizeMatcher matcher(2);
    std::map<int, std::string> m = {{1, "a"}, {2, "b"}};
    EXPECT_TRUE(matcher.match(m));
}

// Test match with a deque container
TEST(HasSizeMatcherTest_237, MatchWorksWithDeque_237) {
    HasSizeMatcher matcher(4);
    std::deque<int> d = {1, 2, 3, 4};
    EXPECT_TRUE(matcher.match(d));
}

// Test match with std::array
TEST(HasSizeMatcherTest_237, MatchWorksWithArray_237) {
    HasSizeMatcher matcher(3);
    std::array<int, 3> a = {1, 2, 3};
    EXPECT_TRUE(matcher.match(a));
}

// Test match with std::array that doesn't match
TEST(HasSizeMatcherTest_237, MatchReturnsFalseForArrayWithNonMatchingSize_237) {
    HasSizeMatcher matcher(5);
    std::array<int, 3> a = {1, 2, 3};
    EXPECT_FALSE(matcher.match(a));
}

// Test that describe is consistent across multiple calls
TEST(HasSizeMatcherTest_237, DescribeIsConsistentAcrossMultipleCalls_237) {
    HasSizeMatcher matcher(10);
    std::string first = matcher.describe();
    std::string second = matcher.describe();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, "has size == 10");
}

// Test with max size_t boundary value
TEST(HasSizeMatcherTest_237, DescribeWorksWithMaxSizeT_237) {
    std::size_t maxVal = std::numeric_limits<std::size_t>::max();
    HasSizeMatcher matcher(maxVal);
    std::string description = matcher.describe();
    EXPECT_EQ(description, "has size == " + std::to_string(maxVal));
}

// Test match with const container reference
TEST(HasSizeMatcherTest_237, MatchWorksWithConstContainerReference_237) {
    HasSizeMatcher matcher(3);
    const std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

// Test match with rvalue container
TEST(HasSizeMatcherTest_237, MatchWorksWithRvalueContainer_237) {
    HasSizeMatcher matcher(2);
    EXPECT_TRUE(matcher.match(std::vector<int>{10, 20}));
}

// Test match returns false for off-by-one size (boundary)
TEST(HasSizeMatcherTest_237, MatchReturnsFalseForOffByOneSize_237) {
    HasSizeMatcher matcher(3);
    std::vector<int> v2 = {1, 2};
    std::vector<int> v4 = {1, 2, 3, 4};
    EXPECT_FALSE(matcher.match(v2));
    EXPECT_FALSE(matcher.match(v4));
}
