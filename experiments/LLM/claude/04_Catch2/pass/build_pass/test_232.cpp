#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <array>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include "catch2/matchers/catch_matchers_container_properties.hpp"

using Catch::Matchers::HasSizeMatcher;

class HasSizeMatcherTest_232 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation tests

TEST_F(HasSizeMatcherTest_232, MatchesVectorWithCorrectSize_232) {
    HasSizeMatcher matcher(3);
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(HasSizeMatcherTest_232, DoesNotMatchVectorWithIncorrectSize_232) {
    HasSizeMatcher matcher(5);
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(HasSizeMatcherTest_232, MatchesEmptyVectorWithSizeZero_232) {
    HasSizeMatcher matcher(0);
    std::vector<int> v;
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(HasSizeMatcherTest_232, DoesNotMatchEmptyVectorWithNonZeroSize_232) {
    HasSizeMatcher matcher(1);
    std::vector<int> v;
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(HasSizeMatcherTest_232, MatchesStringWithCorrectSize_232) {
    HasSizeMatcher matcher(5);
    std::string s = "hello";
    EXPECT_TRUE(matcher.match(s));
}

TEST_F(HasSizeMatcherTest_232, DoesNotMatchStringWithIncorrectSize_232) {
    HasSizeMatcher matcher(3);
    std::string s = "hello";
    EXPECT_FALSE(matcher.match(s));
}

TEST_F(HasSizeMatcherTest_232, MatchesEmptyStringWithSizeZero_232) {
    HasSizeMatcher matcher(0);
    std::string s;
    EXPECT_TRUE(matcher.match(s));
}

TEST_F(HasSizeMatcherTest_232, MatchesArrayWithCorrectSize_232) {
    HasSizeMatcher matcher(4);
    std::array<int, 4> a = {1, 2, 3, 4};
    EXPECT_TRUE(matcher.match(a));
}

TEST_F(HasSizeMatcherTest_232, DoesNotMatchArrayWithIncorrectSize_232) {
    HasSizeMatcher matcher(5);
    std::array<int, 4> a = {1, 2, 3, 4};
    EXPECT_FALSE(matcher.match(a));
}

TEST_F(HasSizeMatcherTest_232, MatchesListWithCorrectSize_232) {
    HasSizeMatcher matcher(3);
    std::list<int> l = {10, 20, 30};
    EXPECT_TRUE(matcher.match(l));
}

TEST_F(HasSizeMatcherTest_232, DoesNotMatchListWithIncorrectSize_232) {
    HasSizeMatcher matcher(2);
    std::list<int> l = {10, 20, 30};
    EXPECT_FALSE(matcher.match(l));
}

TEST_F(HasSizeMatcherTest_232, MatchesDequeWithCorrectSize_232) {
    HasSizeMatcher matcher(2);
    std::deque<double> d = {1.0, 2.0};
    EXPECT_TRUE(matcher.match(d));
}

TEST_F(HasSizeMatcherTest_232, MatchesSetWithCorrectSize_232) {
    HasSizeMatcher matcher(3);
    std::set<int> s = {1, 2, 3};
    EXPECT_TRUE(matcher.match(s));
}

TEST_F(HasSizeMatcherTest_232, MatchesMapWithCorrectSize_232) {
    HasSizeMatcher matcher(2);
    std::map<int, std::string> m = {{1, "a"}, {2, "b"}};
    EXPECT_TRUE(matcher.match(m));
}

TEST_F(HasSizeMatcherTest_232, MatchesUnorderedSetWithCorrectSize_232) {
    HasSizeMatcher matcher(3);
    std::unordered_set<int> us = {1, 2, 3};
    EXPECT_TRUE(matcher.match(us));
}

TEST_F(HasSizeMatcherTest_232, MatchesUnorderedMapWithCorrectSize_232) {
    HasSizeMatcher matcher(2);
    std::unordered_map<int, int> um = {{1, 10}, {2, 20}};
    EXPECT_TRUE(matcher.match(um));
}

// Boundary condition tests

TEST_F(HasSizeMatcherTest_232, MatchesSingleElementVector_232) {
    HasSizeMatcher matcher(1);
    std::vector<int> v = {42};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(HasSizeMatcherTest_232, SizeZeroDoesNotMatchNonEmptyContainer_232) {
    HasSizeMatcher matcher(0);
    std::vector<int> v = {1};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(HasSizeMatcherTest_232, MatchesLargeVector_232) {
    HasSizeMatcher matcher(10000);
    std::vector<int> v(10000, 0);
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(HasSizeMatcherTest_232, DoesNotMatchLargeVectorWithWrongSize_232) {
    HasSizeMatcher matcher(9999);
    std::vector<int> v(10000, 0);
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(HasSizeMatcherTest_232, MatchesSizeOneOffTooSmall_232) {
    HasSizeMatcher matcher(4);
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(HasSizeMatcherTest_232, MatchesSizeOneOffTooLarge_232) {
    HasSizeMatcher matcher(6);
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_FALSE(matcher.match(v));
}

// Test with const reference
TEST_F(HasSizeMatcherTest_232, MatchesConstVector_232) {
    HasSizeMatcher matcher(3);
    const std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

// Test with rvalue reference
TEST_F(HasSizeMatcherTest_232, MatchesRvalueVector_232) {
    HasSizeMatcher matcher(3);
    EXPECT_TRUE(matcher.match(std::vector<int>{1, 2, 3}));
}

TEST_F(HasSizeMatcherTest_232, DoesNotMatchRvalueVectorWithWrongSize_232) {
    HasSizeMatcher matcher(2);
    EXPECT_FALSE(matcher.match(std::vector<int>{1, 2, 3}));
}

// Test with empty array
TEST_F(HasSizeMatcherTest_232, MatchesZeroSizeArray_232) {
    HasSizeMatcher matcher(0);
    std::array<int, 0> a = {};
    EXPECT_TRUE(matcher.match(a));
}

// Test describe method
TEST_F(HasSizeMatcherTest_232, DescribeReturnsNonEmptyString_232) {
    HasSizeMatcher matcher(5);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

TEST_F(HasSizeMatcherTest_232, DescribeContainsSizeValue_232) {
    HasSizeMatcher matcher(42);
    std::string description = matcher.describe();
    EXPECT_NE(description.find("42"), std::string::npos);
}

TEST_F(HasSizeMatcherTest_232, DescribeForZeroSize_232) {
    HasSizeMatcher matcher(0);
    std::string description = matcher.describe();
    EXPECT_NE(description.find("0"), std::string::npos);
}

// Test with different container element types
TEST_F(HasSizeMatcherTest_232, MatchesVectorOfStrings_232) {
    HasSizeMatcher matcher(2);
    std::vector<std::string> v = {"hello", "world"};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(HasSizeMatcherTest_232, MatchesVectorOfDoubles_232) {
    HasSizeMatcher matcher(4);
    std::vector<double> v = {1.1, 2.2, 3.3, 4.4};
    EXPECT_TRUE(matcher.match(v));
}

// Test with set that deduplicates
TEST_F(HasSizeMatcherTest_232, SetDeduplicatesAffectsSize_232) {
    HasSizeMatcher matcher(3);
    std::set<int> s = {1, 2, 3, 3, 2, 1};
    EXPECT_TRUE(matcher.match(s));
}

// Test that the same matcher can be reused
TEST_F(HasSizeMatcherTest_232, MatcherCanBeReused_232) {
    HasSizeMatcher matcher(3);
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};
    std::vector<int> v3 = {7, 8};
    EXPECT_TRUE(matcher.match(v1));
    EXPECT_TRUE(matcher.match(v2));
    EXPECT_FALSE(matcher.match(v3));
}
