#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <array>

// Include the necessary Catch2 headers for the matchers
#include "catch2/matchers/catch_matchers_container_properties.hpp"
#include "catch2/matchers/catch_matchers.hpp"

using namespace Catch::Matchers;

// Test fixture
class IsEmptyMatcherTest_238 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Normal Operation Tests ====================

TEST_F(IsEmptyMatcherTest_238, EmptyVectorMatches_238) {
    std::vector<int> v;
    auto matcher = IsEmpty();
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(IsEmptyMatcherTest_238, NonEmptyVectorDoesNotMatch_238) {
    std::vector<int> v = {1, 2, 3};
    auto matcher = IsEmpty();
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(IsEmptyMatcherTest_238, EmptyStringMatches_238) {
    std::string s;
    auto matcher = IsEmpty();
    EXPECT_TRUE(matcher.match(s));
}

TEST_F(IsEmptyMatcherTest_238, NonEmptyStringDoesNotMatch_238) {
    std::string s = "hello";
    auto matcher = IsEmpty();
    EXPECT_FALSE(matcher.match(s));
}

TEST_F(IsEmptyMatcherTest_238, EmptyListMatches_238) {
    std::list<double> l;
    auto matcher = IsEmpty();
    EXPECT_TRUE(matcher.match(l));
}

TEST_F(IsEmptyMatcherTest_238, NonEmptyListDoesNotMatch_238) {
    std::list<double> l = {1.0, 2.0};
    auto matcher = IsEmpty();
    EXPECT_FALSE(matcher.match(l));
}

TEST_F(IsEmptyMatcherTest_238, EmptyMapMatches_238) {
    std::map<int, int> m;
    auto matcher = IsEmpty();
    EXPECT_TRUE(matcher.match(m));
}

TEST_F(IsEmptyMatcherTest_238, NonEmptyMapDoesNotMatch_238) {
    std::map<int, int> m = {{1, 2}};
    auto matcher = IsEmpty();
    EXPECT_FALSE(matcher.match(m));
}

TEST_F(IsEmptyMatcherTest_238, EmptySetMatches_238) {
    std::set<int> s;
    auto matcher = IsEmpty();
    EXPECT_TRUE(matcher.match(s));
}

TEST_F(IsEmptyMatcherTest_238, NonEmptySetDoesNotMatch_238) {
    std::set<int> s = {1, 2, 3};
    auto matcher = IsEmpty();
    EXPECT_FALSE(matcher.match(s));
}

TEST_F(IsEmptyMatcherTest_238, EmptyDequeMatches_238) {
    std::deque<int> d;
    auto matcher = IsEmpty();
    EXPECT_TRUE(matcher.match(d));
}

TEST_F(IsEmptyMatcherTest_238, NonEmptyDequeDoesNotMatch_238) {
    std::deque<int> d = {1};
    auto matcher = IsEmpty();
    EXPECT_FALSE(matcher.match(d));
}

// ==================== Boundary Condition Tests ====================

TEST_F(IsEmptyMatcherTest_238, SingleElementVectorDoesNotMatch_238) {
    std::vector<int> v = {42};
    auto matcher = IsEmpty();
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(IsEmptyMatcherTest_238, SingleCharStringDoesNotMatch_238) {
    std::string s = "a";
    auto matcher = IsEmpty();
    EXPECT_FALSE(matcher.match(s));
}

TEST_F(IsEmptyMatcherTest_238, VectorClearedBecomesEmpty_238) {
    std::vector<int> v = {1, 2, 3};
    auto matcher = IsEmpty();
    EXPECT_FALSE(matcher.match(v));
    v.clear();
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(IsEmptyMatcherTest_238, VectorWithElementAddedBecomesNonEmpty_238) {
    std::vector<int> v;
    auto matcher = IsEmpty();
    EXPECT_TRUE(matcher.match(v));
    v.push_back(1);
    EXPECT_FALSE(matcher.match(v));
}

// ==================== Description Test ====================

TEST_F(IsEmptyMatcherTest_238, DescribeReturnsNonEmptyString_238) {
    auto matcher = IsEmpty();
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// ==================== Factory Function Tests ====================

TEST_F(IsEmptyMatcherTest_238, IsEmptyFactoryFunctionReturnsValidMatcher_238) {
    auto matcher = IsEmpty();
    std::vector<int> empty_vec;
    std::vector<int> non_empty_vec = {1};
    EXPECT_TRUE(matcher.match(empty_vec));
    EXPECT_FALSE(matcher.match(non_empty_vec));
}

// ==================== HasSize Matcher Tests (if available) ====================

TEST_F(IsEmptyMatcherTest_238, EmptyVectorOfStringsMatches_238) {
    std::vector<std::string> v;
    auto matcher = IsEmpty();
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(IsEmptyMatcherTest_238, NonEmptyVectorOfStringsDoesNotMatch_238) {
    std::vector<std::string> v = {"hello", "world"};
    auto matcher = IsEmpty();
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(IsEmptyMatcherTest_238, EmptyMultimapMatches_238) {
    std::multimap<int, int> mm;
    auto matcher = IsEmpty();
    EXPECT_TRUE(matcher.match(mm));
}

TEST_F(IsEmptyMatcherTest_238, NonEmptyMultimapDoesNotMatch_238) {
    std::multimap<int, int> mm = {{1, 2}, {1, 3}};
    auto matcher = IsEmpty();
    EXPECT_FALSE(matcher.match(mm));
}

// Test reusability of the matcher instance
TEST_F(IsEmptyMatcherTest_238, MatcherCanBeReused_238) {
    auto matcher = IsEmpty();
    
    std::vector<int> v1;
    EXPECT_TRUE(matcher.match(v1));
    
    std::vector<int> v2 = {1, 2};
    EXPECT_FALSE(matcher.match(v2));
    
    std::string s1;
    EXPECT_TRUE(matcher.match(s1));
    
    std::string s2 = "test";
    EXPECT_FALSE(matcher.match(s2));
}

// Test with large container
TEST_F(IsEmptyMatcherTest_238, LargeNonEmptyContainerDoesNotMatch_238) {
    std::vector<int> v(10000, 0);
    auto matcher = IsEmpty();
    EXPECT_FALSE(matcher.match(v));
}
