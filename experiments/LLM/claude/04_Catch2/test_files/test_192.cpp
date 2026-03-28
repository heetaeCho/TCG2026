#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <list>
#include <string>

// Include the necessary Catch2 headers
#include "catch2/matchers/catch_matchers_quantifiers.hpp"
#include "catch2/matchers/catch_matchers.hpp"

using namespace Catch::Matchers;

// ==================== AnyTrueMatcher Tests ====================

// Test describe() returns expected string
TEST(AnyTrueMatcherTest_192, DescribeReturnsExpectedString_192) {
    AnyTrueMatcher matcher;
    std::string description = matcher.describe();
    EXPECT_EQ(description, "contains at least one true");
}

// Test match with vector containing at least one true
TEST(AnyTrueMatcherTest_192, MatchReturnsTrueWhenVectorContainsTrue_192) {
    AnyTrueMatcher matcher;
    std::vector<bool> v = {false, false, true, false};
    EXPECT_TRUE(matcher.match(v));
}

// Test match with vector containing all true
TEST(AnyTrueMatcherTest_192, MatchReturnsTrueWhenAllTrue_192) {
    AnyTrueMatcher matcher;
    std::vector<bool> v = {true, true, true};
    EXPECT_TRUE(matcher.match(v));
}

// Test match with vector containing all false
TEST(AnyTrueMatcherTest_192, MatchReturnsFalseWhenAllFalse_192) {
    AnyTrueMatcher matcher;
    std::vector<bool> v = {false, false, false};
    EXPECT_FALSE(matcher.match(v));
}

// Test match with empty vector
TEST(AnyTrueMatcherTest_192, MatchReturnsFalseWhenEmpty_192) {
    AnyTrueMatcher matcher;
    std::vector<bool> v = {};
    EXPECT_FALSE(matcher.match(v));
}

// Test match with single true element
TEST(AnyTrueMatcherTest_192, MatchReturnsTrueWithSingleTrue_192) {
    AnyTrueMatcher matcher;
    std::vector<bool> v = {true};
    EXPECT_TRUE(matcher.match(v));
}

// Test match with single false element
TEST(AnyTrueMatcherTest_192, MatchReturnsFalseWithSingleFalse_192) {
    AnyTrueMatcher matcher;
    std::vector<bool> v = {false};
    EXPECT_FALSE(matcher.match(v));
}

// Test match with std::array
TEST(AnyTrueMatcherTest_192, MatchWorksWithStdArray_192) {
    AnyTrueMatcher matcher;
    std::array<bool, 3> arr = {false, true, false};
    EXPECT_TRUE(matcher.match(arr));
}

// Test match with std::array all false
TEST(AnyTrueMatcherTest_192, MatchReturnsFalseWithStdArrayAllFalse_192) {
    AnyTrueMatcher matcher;
    std::array<bool, 3> arr = {false, false, false};
    EXPECT_FALSE(matcher.match(arr));
}

// Test match with std::list
TEST(AnyTrueMatcherTest_192, MatchWorksWithStdList_192) {
    AnyTrueMatcher matcher;
    std::list<bool> lst = {false, false, true};
    EXPECT_TRUE(matcher.match(lst));
}

// Test match with std::list all false
TEST(AnyTrueMatcherTest_192, MatchReturnsFalseWithStdListAllFalse_192) {
    AnyTrueMatcher matcher;
    std::list<bool> lst = {false, false, false};
    EXPECT_FALSE(matcher.match(lst));
}

// Test match with vector of int (truthy/falsy values)
TEST(AnyTrueMatcherTest_192, MatchWorksWithIntVectorContainingNonZero_192) {
    AnyTrueMatcher matcher;
    std::vector<int> v = {0, 0, 1, 0};
    EXPECT_TRUE(matcher.match(v));
}

// Test match with vector of int all zero
TEST(AnyTrueMatcherTest_192, MatchReturnsFalseWithIntVectorAllZero_192) {
    AnyTrueMatcher matcher;
    std::vector<int> v = {0, 0, 0};
    EXPECT_FALSE(matcher.match(v));
}

// Test match with empty int vector
TEST(AnyTrueMatcherTest_192, MatchReturnsFalseWithEmptyIntVector_192) {
    AnyTrueMatcher matcher;
    std::vector<int> v = {};
    EXPECT_FALSE(matcher.match(v));
}

// Test that first element being true is detected
TEST(AnyTrueMatcherTest_192, MatchReturnsTrueWhenFirstElementIsTrue_192) {
    AnyTrueMatcher matcher;
    std::vector<bool> v = {true, false, false, false};
    EXPECT_TRUE(matcher.match(v));
}

// Test that last element being true is detected
TEST(AnyTrueMatcherTest_192, MatchReturnsTrueWhenLastElementIsTrue_192) {
    AnyTrueMatcher matcher;
    std::vector<bool> v = {false, false, false, true};
    EXPECT_TRUE(matcher.match(v));
}

// Test describe is const and can be called multiple times
TEST(AnyTrueMatcherTest_192, DescribeIsConsistentAcrossMultipleCalls_192) {
    AnyTrueMatcher matcher;
    std::string desc1 = matcher.describe();
    std::string desc2 = matcher.describe();
    EXPECT_EQ(desc1, desc2);
    EXPECT_EQ(desc1, "contains at least one true");
}

// Test with large vector all false
TEST(AnyTrueMatcherTest_192, MatchReturnsFalseWithLargeVectorAllFalse_192) {
    AnyTrueMatcher matcher;
    std::vector<bool> v(10000, false);
    EXPECT_FALSE(matcher.match(v));
}

// Test with large vector with one true at end
TEST(AnyTrueMatcherTest_192, MatchReturnsTrueWithLargeVectorOneTrueAtEnd_192) {
    AnyTrueMatcher matcher;
    std::vector<bool> v(10000, false);
    v.back() = true;
    EXPECT_TRUE(matcher.match(v));
}
