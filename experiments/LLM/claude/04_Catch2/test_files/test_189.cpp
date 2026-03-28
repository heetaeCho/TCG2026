#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <array>
#include <list>

// Include Catch2 matcher headers
#include "catch2/matchers/catch_matchers_quantifiers.hpp"
#include "catch2/matchers/catch_matchers.hpp"

using namespace Catch::Matchers;

// Test fixture
class AllTrueMatcherTest_189 : public ::testing::Test {
protected:
    AllTrueMatcher matcher = AllTrue();
};

// Normal operation tests

TEST_F(AllTrueMatcherTest_189, AllElementsTrue_ReturnsTrue_189) {
    std::vector<bool> v = {true, true, true, true};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_189, AllElementsTrueInts_ReturnsTrue_189) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_189, SingleTrueElement_ReturnsTrue_189) {
    std::vector<bool> v = {true};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_189, SingleNonZeroInt_ReturnsTrue_189) {
    std::vector<int> v = {42};
    EXPECT_TRUE(matcher.match(v));
}

// Boundary conditions

TEST_F(AllTrueMatcherTest_189, EmptyContainer_ReturnsTrue_189) {
    std::vector<bool> v = {};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_189, EmptyIntContainer_ReturnsTrue_189) {
    std::vector<int> v = {};
    EXPECT_TRUE(matcher.match(v));
}

// Failure cases

TEST_F(AllTrueMatcherTest_189, OneElementFalse_ReturnsFalse_189) {
    std::vector<bool> v = {true, true, false, true};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_189, AllElementsFalse_ReturnsFalse_189) {
    std::vector<bool> v = {false, false, false};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_189, SingleFalseElement_ReturnsFalse_189) {
    std::vector<bool> v = {false};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_189, ContainsZeroInt_ReturnsFalse_189) {
    std::vector<int> v = {1, 2, 0, 3};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_189, AllZeroInts_ReturnsFalse_189) {
    std::vector<int> v = {0, 0, 0};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_189, FirstElementFalse_ReturnsFalse_189) {
    std::vector<bool> v = {false, true, true};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_189, LastElementFalse_ReturnsFalse_189) {
    std::vector<bool> v = {true, true, false};
    EXPECT_FALSE(matcher.match(v));
}

// Different container types

TEST_F(AllTrueMatcherTest_189, ArrayAllTrue_ReturnsTrue_189) {
    std::array<bool, 3> a = {true, true, true};
    EXPECT_TRUE(matcher.match(a));
}

TEST_F(AllTrueMatcherTest_189, ListAllTrue_ReturnsTrue_189) {
    std::list<bool> l = {true, true, true};
    EXPECT_TRUE(matcher.match(l));
}

TEST_F(AllTrueMatcherTest_189, ListWithFalse_ReturnsFalse_189) {
    std::list<bool> l = {true, false, true};
    EXPECT_FALSE(matcher.match(l));
}

// Factory function test

TEST_F(AllTrueMatcherTest_189, FactoryFunctionReturnsValidMatcher_189) {
    auto m = AllTrue();
    std::vector<bool> v = {true, true};
    EXPECT_TRUE(m.match(v));
}

// Describe method test

TEST_F(AllTrueMatcherTest_189, DescribeReturnsNonEmptyString_189) {
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}
