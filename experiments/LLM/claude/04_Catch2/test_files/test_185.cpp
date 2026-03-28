#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <list>
#include <array>

#include "catch2/matchers/catch_matchers_quantifiers.hpp"
#include "catch2/matchers/catch_matchers_predicate.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"
#include "catch2/matchers/catch_matchers_contains.hpp"
#include "catch2/matchers/catch_matchers.hpp"

using namespace Catch::Matchers;

class AllMatchTest_185 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(AllMatchTest_185, AllElementsMatchPredicate_185) {
    std::vector<int> v = {2, 4, 6, 8, 10};
    auto matcher = AllMatch(Catch::Matchers::Predicate<int>([](int x) { return x % 2 == 0; }, "is even"));
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllMatchTest_185, NotAllElementsMatchPredicate_185) {
    std::vector<int> v = {2, 4, 5, 8, 10};
    auto matcher = AllMatch(Catch::Matchers::Predicate<int>([](int x) { return x % 2 == 0; }, "is even"));
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllMatchTest_185, EmptyContainerMatchesAll_185) {
    std::vector<int> v = {};
    auto matcher = AllMatch(Catch::Matchers::Predicate<int>([](int x) { return x % 2 == 0; }, "is even"));
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllMatchTest_185, SingleElementMatches_185) {
    std::vector<int> v = {4};
    auto matcher = AllMatch(Catch::Matchers::Predicate<int>([](int x) { return x % 2 == 0; }, "is even"));
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllMatchTest_185, SingleElementDoesNotMatch_185) {
    std::vector<int> v = {3};
    auto matcher = AllMatch(Catch::Matchers::Predicate<int>([](int x) { return x % 2 == 0; }, "is even"));
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllMatchTest_185, FirstElementFails_185) {
    std::vector<int> v = {1, 2, 4, 6};
    auto matcher = AllMatch(Catch::Matchers::Predicate<int>([](int x) { return x % 2 == 0; }, "is even"));
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllMatchTest_185, LastElementFails_185) {
    std::vector<int> v = {2, 4, 6, 7};
    auto matcher = AllMatch(Catch::Matchers::Predicate<int>([](int x) { return x % 2 == 0; }, "is even"));
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllMatchTest_185, AllPositive_185) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto matcher = AllMatch(Catch::Matchers::Predicate<int>([](int x) { return x > 0; }, "is positive"));
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllMatchTest_185, WithListContainer_185) {
    std::list<int> l = {2, 4, 6};
    auto matcher = AllMatch(Catch::Matchers::Predicate<int>([](int x) { return x % 2 == 0; }, "is even"));
    EXPECT_TRUE(matcher.match(l));
}

TEST_F(AllMatchTest_185, DescribeMethodReturnsNonEmpty_185) {
    auto matcher = AllMatch(Catch::Matchers::Predicate<int>([](int x) { return x > 0; }, "is positive"));
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

TEST_F(AllMatchTest_185, LargeContainerAllMatch_185) {
    std::vector<int> v(1000, 2);
    auto matcher = AllMatch(Catch::Matchers::Predicate<int>([](int x) { return x == 2; }, "equals 2"));
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllMatchTest_185, LargeContainerOneFailsAtEnd_185) {
    std::vector<int> v(1000, 2);
    v.back() = 3;
    auto matcher = AllMatch(Catch::Matchers::Predicate<int>([](int x) { return x == 2; }, "equals 2"));
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllMatchTest_185, AllNegativeNumbers_185) {
    std::vector<int> v = {-1, -2, -3, -4};
    auto matcher = AllMatch(Catch::Matchers::Predicate<int>([](int x) { return x < 0; }, "is negative"));
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllMatchTest_185, MixedSignsFail_185) {
    std::vector<int> v = {-1, 2, -3, 4};
    auto matcher = AllMatch(Catch::Matchers::Predicate<int>([](int x) { return x < 0; }, "is negative"));
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllMatchTest_185, AllZeros_185) {
    std::vector<int> v = {0, 0, 0};
    auto matcher = AllMatch(Catch::Matchers::Predicate<int>([](int x) { return x == 0; }, "is zero"));
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllMatchTest_185, StringPredicate_185) {
    std::vector<std::string> v = {"hello", "world", "test!"};
    auto matcher = AllMatch(Catch::Matchers::Predicate<std::string>(
        [](const std::string& s) { return s.length() == 5; }, "has length 5"));
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllMatchTest_185, StringPredicateFails_185) {
    std::vector<std::string> v = {"hello", "hi", "world"};
    auto matcher = AllMatch(Catch::Matchers::Predicate<std::string>(
        [](const std::string& s) { return s.length() == 5; }, "has length 5"));
    EXPECT_FALSE(matcher.match(v));
}
