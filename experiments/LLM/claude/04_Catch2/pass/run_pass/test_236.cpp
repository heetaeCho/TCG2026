#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <array>
#include <deque>

// Include the header for IsEmptyMatcher
#include "catch2/matchers/catch_matchers_container_properties.hpp"

using namespace Catch::Matchers;

// Test that describe() returns the expected string
TEST(IsEmptyMatcherTest_236, DescribeReturnsCorrectString_236) {
    IsEmptyMatcher matcher;
    EXPECT_EQ(matcher.describe(), "is empty");
}

// Test match with an empty vector
TEST(IsEmptyMatcherTest_236, MatchEmptyVector_236) {
    IsEmptyMatcher matcher;
    std::vector<int> emptyVec;
    EXPECT_TRUE(matcher.match(emptyVec));
}

// Test match with a non-empty vector
TEST(IsEmptyMatcherTest_236, MatchNonEmptyVector_236) {
    IsEmptyMatcher matcher;
    std::vector<int> nonEmptyVec = {1, 2, 3};
    EXPECT_FALSE(matcher.match(nonEmptyVec));
}

// Test match with an empty string
TEST(IsEmptyMatcherTest_236, MatchEmptyString_236) {
    IsEmptyMatcher matcher;
    std::string emptyStr;
    EXPECT_TRUE(matcher.match(emptyStr));
}

// Test match with a non-empty string
TEST(IsEmptyMatcherTest_236, MatchNonEmptyString_236) {
    IsEmptyMatcher matcher;
    std::string nonEmptyStr = "hello";
    EXPECT_FALSE(matcher.match(nonEmptyStr));
}

// Test match with an empty list
TEST(IsEmptyMatcherTest_236, MatchEmptyList_236) {
    IsEmptyMatcher matcher;
    std::list<double> emptyList;
    EXPECT_TRUE(matcher.match(emptyList));
}

// Test match with a non-empty list
TEST(IsEmptyMatcherTest_236, MatchNonEmptyList_236) {
    IsEmptyMatcher matcher;
    std::list<double> nonEmptyList = {1.0, 2.0};
    EXPECT_FALSE(matcher.match(nonEmptyList));
}

// Test match with an empty set
TEST(IsEmptyMatcherTest_236, MatchEmptySet_236) {
    IsEmptyMatcher matcher;
    std::set<int> emptySet;
    EXPECT_TRUE(matcher.match(emptySet));
}

// Test match with a non-empty set
TEST(IsEmptyMatcherTest_236, MatchNonEmptySet_236) {
    IsEmptyMatcher matcher;
    std::set<int> nonEmptySet = {1, 2, 3};
    EXPECT_FALSE(matcher.match(nonEmptySet));
}

// Test match with an empty map
TEST(IsEmptyMatcherTest_236, MatchEmptyMap_236) {
    IsEmptyMatcher matcher;
    std::map<int, int> emptyMap;
    EXPECT_TRUE(matcher.match(emptyMap));
}

// Test match with a non-empty map
TEST(IsEmptyMatcherTest_236, MatchNonEmptyMap_236) {
    IsEmptyMatcher matcher;
    std::map<int, int> nonEmptyMap = {{1, 2}, {3, 4}};
    EXPECT_FALSE(matcher.match(nonEmptyMap));
}

// Test match with an empty deque
TEST(IsEmptyMatcherTest_236, MatchEmptyDeque_236) {
    IsEmptyMatcher matcher;
    std::deque<int> emptyDeque;
    EXPECT_TRUE(matcher.match(emptyDeque));
}

// Test match with a non-empty deque
TEST(IsEmptyMatcherTest_236, MatchNonEmptyDeque_236) {
    IsEmptyMatcher matcher;
    std::deque<int> nonEmptyDeque = {1};
    EXPECT_FALSE(matcher.match(nonEmptyDeque));
}

// Test match with a vector containing a single element (boundary)
TEST(IsEmptyMatcherTest_236, MatchSingleElementVector_236) {
    IsEmptyMatcher matcher;
    std::vector<int> singleElem = {42};
    EXPECT_FALSE(matcher.match(singleElem));
}

// Test match with an empty array (zero-size std::array)
TEST(IsEmptyMatcherTest_236, MatchEmptyArray_236) {
    IsEmptyMatcher matcher;
    std::array<int, 0> emptyArr;
    EXPECT_TRUE(matcher.match(emptyArr));
}

// Test match with a non-empty array
TEST(IsEmptyMatcherTest_236, MatchNonEmptyArray_236) {
    IsEmptyMatcher matcher;
    std::array<int, 3> nonEmptyArr = {1, 2, 3};
    EXPECT_FALSE(matcher.match(nonEmptyArr));
}

// Test match with const reference to empty container
TEST(IsEmptyMatcherTest_236, MatchConstEmptyVector_236) {
    IsEmptyMatcher matcher;
    const std::vector<int> emptyVec;
    EXPECT_TRUE(matcher.match(emptyVec));
}

// Test match with const reference to non-empty container
TEST(IsEmptyMatcherTest_236, MatchConstNonEmptyVector_236) {
    IsEmptyMatcher matcher;
    const std::vector<int> nonEmptyVec = {1, 2};
    EXPECT_FALSE(matcher.match(nonEmptyVec));
}

// Test that describe is consistent across multiple calls
TEST(IsEmptyMatcherTest_236, DescribeIsConsistent_236) {
    IsEmptyMatcher matcher;
    std::string first = matcher.describe();
    std::string second = matcher.describe();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, "is empty");
}

// Test that match can be called multiple times on same matcher
TEST(IsEmptyMatcherTest_236, MatchCanBeCalledMultipleTimes_236) {
    IsEmptyMatcher matcher;
    std::vector<int> emptyVec;
    std::vector<int> nonEmptyVec = {1};
    
    EXPECT_TRUE(matcher.match(emptyVec));
    EXPECT_FALSE(matcher.match(nonEmptyVec));
    EXPECT_TRUE(matcher.match(emptyVec));
}

// Test match with a vector that was cleared
TEST(IsEmptyMatcherTest_236, MatchClearedVector_236) {
    IsEmptyMatcher matcher;
    std::vector<int> vec = {1, 2, 3};
    vec.clear();
    EXPECT_TRUE(matcher.match(vec));
}

// Test with empty multiset
TEST(IsEmptyMatcherTest_236, MatchEmptyMultiset_236) {
    IsEmptyMatcher matcher;
    std::multiset<int> emptyMultiset;
    EXPECT_TRUE(matcher.match(emptyMultiset));
}
