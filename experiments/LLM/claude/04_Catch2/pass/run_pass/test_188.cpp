#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <list>
#include <string>

// Include the necessary Catch2 headers
#include "catch2/matchers/catch_matchers_quantifiers.hpp"
#include "catch2/matchers/catch_matchers.hpp"

using namespace Catch::Matchers;

// Test describe() method
TEST(AllTrueMatcherTest_188, DescribeReturnsExpectedString_188) {
    AllTrueMatcher matcher;
    EXPECT_EQ(matcher.describe(), "contains only true");
}

// Test match with all true values in a vector
TEST(AllTrueMatcherTest_188, MatchAllTrueVector_188) {
    AllTrueMatcher matcher;
    std::vector<bool> allTrue = {true, true, true, true};
    EXPECT_TRUE(matcher.match(allTrue));
}

// Test match with some false values in a vector
TEST(AllTrueMatcherTest_188, MatchSomeFalseVector_188) {
    AllTrueMatcher matcher;
    std::vector<bool> someFalse = {true, false, true, true};
    EXPECT_FALSE(matcher.match(someFalse));
}

// Test match with all false values
TEST(AllTrueMatcherTest_188, MatchAllFalseVector_188) {
    AllTrueMatcher matcher;
    std::vector<bool> allFalse = {false, false, false};
    EXPECT_FALSE(matcher.match(allFalse));
}

// Test match with empty container
TEST(AllTrueMatcherTest_188, MatchEmptyVector_188) {
    AllTrueMatcher matcher;
    std::vector<bool> empty;
    // An empty range should vacuously satisfy "all true"
    EXPECT_TRUE(matcher.match(empty));
}

// Test match with single true element
TEST(AllTrueMatcherTest_188, MatchSingleTrueElement_188) {
    AllTrueMatcher matcher;
    std::vector<bool> single = {true};
    EXPECT_TRUE(matcher.match(single));
}

// Test match with single false element
TEST(AllTrueMatcherTest_188, MatchSingleFalseElement_188) {
    AllTrueMatcher matcher;
    std::vector<bool> single = {false};
    EXPECT_FALSE(matcher.match(single));
}

// Test match with std::array
TEST(AllTrueMatcherTest_188, MatchAllTrueArray_188) {
    AllTrueMatcher matcher;
    std::array<bool, 3> arr = {true, true, true};
    EXPECT_TRUE(matcher.match(arr));
}

// Test match with std::array containing false
TEST(AllTrueMatcherTest_188, MatchArrayWithFalse_188) {
    AllTrueMatcher matcher;
    std::array<bool, 3> arr = {true, false, true};
    EXPECT_FALSE(matcher.match(arr));
}

// Test match with std::list
TEST(AllTrueMatcherTest_188, MatchAllTrueList_188) {
    AllTrueMatcher matcher;
    std::list<bool> lst = {true, true, true};
    EXPECT_TRUE(matcher.match(lst));
}

// Test match with std::list containing false
TEST(AllTrueMatcherTest_188, MatchListWithFalse_188) {
    AllTrueMatcher matcher;
    std::list<bool> lst = {true, true, false};
    EXPECT_FALSE(matcher.match(lst));
}

// Test match with integer-like range where non-zero is truthy
TEST(AllTrueMatcherTest_188, MatchIntegerVectorAllNonZero_188) {
    AllTrueMatcher matcher;
    std::vector<int> allNonZero = {1, 2, 3, 42};
    EXPECT_TRUE(matcher.match(allNonZero));
}

// Test match with integer range containing zero
TEST(AllTrueMatcherTest_188, MatchIntegerVectorWithZero_188) {
    AllTrueMatcher matcher;
    std::vector<int> withZero = {1, 0, 3};
    EXPECT_FALSE(matcher.match(withZero));
}

// Test match with only false at the beginning
TEST(AllTrueMatcherTest_188, MatchFalseAtBeginning_188) {
    AllTrueMatcher matcher;
    std::vector<bool> v = {false, true, true, true};
    EXPECT_FALSE(matcher.match(v));
}

// Test match with only false at the end
TEST(AllTrueMatcherTest_188, MatchFalseAtEnd_188) {
    AllTrueMatcher matcher;
    std::vector<bool> v = {true, true, true, false};
    EXPECT_FALSE(matcher.match(v));
}

// Test match with large all-true container
TEST(AllTrueMatcherTest_188, MatchLargeAllTrueVector_188) {
    AllTrueMatcher matcher;
    std::vector<bool> large(1000, true);
    EXPECT_TRUE(matcher.match(large));
}

// Test match with large container with one false in the middle
TEST(AllTrueMatcherTest_188, MatchLargeVectorWithOneFalse_188) {
    AllTrueMatcher matcher;
    std::vector<bool> large(1000, true);
    large[500] = false;
    EXPECT_FALSE(matcher.match(large));
}

// Test with empty array
TEST(AllTrueMatcherTest_188, MatchEmptyArray_188) {
    AllTrueMatcher matcher;
    std::array<bool, 0> emptyArr = {};
    EXPECT_TRUE(matcher.match(emptyArr));
}
