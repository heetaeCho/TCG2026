#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <map>
#include <array>
#include <deque>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>

// Include the header under test
#include "catch2/matchers/catch_matchers_container_properties.hpp"

using Catch::Matchers::IsEmptyMatcher;

// Normal operation tests

TEST(IsEmptyMatcherTest_231, EmptyVectorReturnsTrue_231) {
    IsEmptyMatcher matcher;
    std::vector<int> v;
    EXPECT_TRUE(matcher.match(v));
}

TEST(IsEmptyMatcherTest_231, NonEmptyVectorReturnsFalse_231) {
    IsEmptyMatcher matcher;
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

TEST(IsEmptyMatcherTest_231, EmptyStringReturnsTrue_231) {
    IsEmptyMatcher matcher;
    std::string s;
    EXPECT_TRUE(matcher.match(s));
}

TEST(IsEmptyMatcherTest_231, NonEmptyStringReturnsFalse_231) {
    IsEmptyMatcher matcher;
    std::string s = "hello";
    EXPECT_FALSE(matcher.match(s));
}

TEST(IsEmptyMatcherTest_231, EmptyListReturnsTrue_231) {
    IsEmptyMatcher matcher;
    std::list<int> l;
    EXPECT_TRUE(matcher.match(l));
}

TEST(IsEmptyMatcherTest_231, NonEmptyListReturnsFalse_231) {
    IsEmptyMatcher matcher;
    std::list<int> l = {1};
    EXPECT_FALSE(matcher.match(l));
}

TEST(IsEmptyMatcherTest_231, EmptySetReturnsTrue_231) {
    IsEmptyMatcher matcher;
    std::set<int> s;
    EXPECT_TRUE(matcher.match(s));
}

TEST(IsEmptyMatcherTest_231, NonEmptySetReturnsFalse_231) {
    IsEmptyMatcher matcher;
    std::set<int> s = {42};
    EXPECT_FALSE(matcher.match(s));
}

TEST(IsEmptyMatcherTest_231, EmptyMapReturnsTrue_231) {
    IsEmptyMatcher matcher;
    std::map<int, int> m;
    EXPECT_TRUE(matcher.match(m));
}

TEST(IsEmptyMatcherTest_231, NonEmptyMapReturnsFalse_231) {
    IsEmptyMatcher matcher;
    std::map<int, int> m = {{1, 2}};
    EXPECT_FALSE(matcher.match(m));
}

TEST(IsEmptyMatcherTest_231, EmptyDequeReturnsTrue_231) {
    IsEmptyMatcher matcher;
    std::deque<double> d;
    EXPECT_TRUE(matcher.match(d));
}

TEST(IsEmptyMatcherTest_231, NonEmptyDequeReturnsFalse_231) {
    IsEmptyMatcher matcher;
    std::deque<double> d = {3.14};
    EXPECT_FALSE(matcher.match(d));
}

TEST(IsEmptyMatcherTest_231, EmptyUnorderedSetReturnsTrue_231) {
    IsEmptyMatcher matcher;
    std::unordered_set<int> us;
    EXPECT_TRUE(matcher.match(us));
}

TEST(IsEmptyMatcherTest_231, NonEmptyUnorderedSetReturnsFalse_231) {
    IsEmptyMatcher matcher;
    std::unordered_set<int> us = {1, 2, 3};
    EXPECT_FALSE(matcher.match(us));
}

TEST(IsEmptyMatcherTest_231, EmptyUnorderedMapReturnsTrue_231) {
    IsEmptyMatcher matcher;
    std::unordered_map<std::string, int> um;
    EXPECT_TRUE(matcher.match(um));
}

TEST(IsEmptyMatcherTest_231, NonEmptyUnorderedMapReturnsFalse_231) {
    IsEmptyMatcher matcher;
    std::unordered_map<std::string, int> um = {{"key", 1}};
    EXPECT_FALSE(matcher.match(um));
}

// Boundary conditions

TEST(IsEmptyMatcherTest_231, VectorWithSingleElementReturnsFalse_231) {
    IsEmptyMatcher matcher;
    std::vector<int> v = {0};
    EXPECT_FALSE(matcher.match(v));
}

TEST(IsEmptyMatcherTest_231, StringWithSingleCharReturnsFalse_231) {
    IsEmptyMatcher matcher;
    std::string s = "a";
    EXPECT_FALSE(matcher.match(s));
}

TEST(IsEmptyMatcherTest_231, VectorAfterClearReturnsTrue_231) {
    IsEmptyMatcher matcher;
    std::vector<int> v = {1, 2, 3};
    v.clear();
    EXPECT_TRUE(matcher.match(v));
}

TEST(IsEmptyMatcherTest_231, VectorAfterEraseAllReturnsTrue_231) {
    IsEmptyMatcher matcher;
    std::vector<int> v = {1, 2, 3};
    v.erase(v.begin(), v.end());
    EXPECT_TRUE(matcher.match(v));
}

TEST(IsEmptyMatcherTest_231, VectorAfterAddingElementReturnsFalse_231) {
    IsEmptyMatcher matcher;
    std::vector<int> v;
    EXPECT_TRUE(matcher.match(v));
    v.push_back(1);
    EXPECT_FALSE(matcher.match(v));
}

TEST(IsEmptyMatcherTest_231, EmptyArrayOfSizeZero_231) {
    IsEmptyMatcher matcher;
    std::array<int, 0> a;
    EXPECT_TRUE(matcher.match(a));
}

TEST(IsEmptyMatcherTest_231, NonEmptyArrayReturnsFalse_231) {
    IsEmptyMatcher matcher;
    std::array<int, 3> a = {1, 2, 3};
    EXPECT_FALSE(matcher.match(a));
}

// Test with const reference
TEST(IsEmptyMatcherTest_231, ConstEmptyVectorReturnsTrue_231) {
    IsEmptyMatcher matcher;
    const std::vector<int> v;
    EXPECT_TRUE(matcher.match(v));
}

TEST(IsEmptyMatcherTest_231, ConstNonEmptyVectorReturnsFalse_231) {
    IsEmptyMatcher matcher;
    const std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(matcher.match(v));
}

// Test with rvalue reference
TEST(IsEmptyMatcherTest_231, RvalueEmptyVectorReturnsTrue_231) {
    IsEmptyMatcher matcher;
    EXPECT_TRUE(matcher.match(std::vector<int>{}));
}

TEST(IsEmptyMatcherTest_231, RvalueNonEmptyVectorReturnsFalse_231) {
    IsEmptyMatcher matcher;
    EXPECT_FALSE(matcher.match(std::vector<int>{1, 2, 3}));
}

// Test with large container
TEST(IsEmptyMatcherTest_231, LargeNonEmptyVectorReturnsFalse_231) {
    IsEmptyMatcher matcher;
    std::vector<int> v(10000, 0);
    EXPECT_FALSE(matcher.match(v));
}

// Test with vector of strings
TEST(IsEmptyMatcherTest_231, EmptyVectorOfStringsReturnsTrue_231) {
    IsEmptyMatcher matcher;
    std::vector<std::string> v;
    EXPECT_TRUE(matcher.match(v));
}

TEST(IsEmptyMatcherTest_231, NonEmptyVectorOfStringsReturnsFalse_231) {
    IsEmptyMatcher matcher;
    std::vector<std::string> v = {"hello", "world"};
    EXPECT_FALSE(matcher.match(v));
}

// Test with multiset
TEST(IsEmptyMatcherTest_231, EmptyMultisetReturnsTrue_231) {
    IsEmptyMatcher matcher;
    std::multiset<int> ms;
    EXPECT_TRUE(matcher.match(ms));
}

TEST(IsEmptyMatcherTest_231, NonEmptyMultisetReturnsFalse_231) {
    IsEmptyMatcher matcher;
    std::multiset<int> ms = {1, 1, 2};
    EXPECT_FALSE(matcher.match(ms));
}

// Test matcher can be reused multiple times
TEST(IsEmptyMatcherTest_231, MatcherCanBeReusedMultipleTimes_231) {
    IsEmptyMatcher matcher;
    
    std::vector<int> empty_v;
    std::vector<int> non_empty_v = {1};
    std::string empty_s;
    std::string non_empty_s = "test";
    
    EXPECT_TRUE(matcher.match(empty_v));
    EXPECT_FALSE(matcher.match(non_empty_v));
    EXPECT_TRUE(matcher.match(empty_s));
    EXPECT_FALSE(matcher.match(non_empty_s));
}

// Test with nested containers
TEST(IsEmptyMatcherTest_231, EmptyVectorOfVectorsReturnsTrue_231) {
    IsEmptyMatcher matcher;
    std::vector<std::vector<int>> v;
    EXPECT_TRUE(matcher.match(v));
}

TEST(IsEmptyMatcherTest_231, NonEmptyVectorOfVectorsReturnsFalse_231) {
    IsEmptyMatcher matcher;
    std::vector<std::vector<int>> v = {{}};
    EXPECT_FALSE(matcher.match(v));
}

// Test with C-style arrays via initializer list
TEST(IsEmptyMatcherTest_231, InitializerListEmptyReturnsTrue_231) {
    IsEmptyMatcher matcher;
    auto il = std::initializer_list<int>{};
    EXPECT_TRUE(matcher.match(il));
}

TEST(IsEmptyMatcherTest_231, InitializerListNonEmptyReturnsFalse_231) {
    IsEmptyMatcher matcher;
    auto il = std::initializer_list<int>{1, 2, 3};
    EXPECT_FALSE(matcher.match(il));
}
