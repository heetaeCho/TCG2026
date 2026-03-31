#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <list>
#include <string>

// Include the necessary Catch2 headers for the matchers
#include "catch2/matchers/catch_matchers_quantifiers.hpp"
#include "catch2/matchers/catch_matchers.hpp"

using namespace Catch::Matchers;

// Test fixture
class NoneTrueMatcherTest_190 : public ::testing::Test {
protected:
    NoneTrueMatcher matcher;
};

// ========== describe() tests ==========

TEST_F(NoneTrueMatcherTest_190, DescribeReturnsExpectedString_190) {
    std::string description = matcher.describe();
    EXPECT_EQ(description, "contains no true");
}

TEST_F(NoneTrueMatcherTest_190, DescribeIsConsistentAcrossCalls_190) {
    std::string desc1 = matcher.describe();
    std::string desc2 = matcher.describe();
    EXPECT_EQ(desc1, desc2);
}

// ========== match() tests with bool containers ==========

TEST_F(NoneTrueMatcherTest_190, MatchEmptyVectorReturnsTrue_190) {
    std::vector<bool> empty;
    EXPECT_TRUE(matcher.match(empty));
}

TEST_F(NoneTrueMatcherTest_190, MatchAllFalseVectorReturnsTrue_190) {
    std::vector<bool> allFalse = {false, false, false};
    EXPECT_TRUE(matcher.match(allFalse));
}

TEST_F(NoneTrueMatcherTest_190, MatchAllTrueVectorReturnsFalse_190) {
    std::vector<bool> allTrue = {true, true, true};
    EXPECT_FALSE(matcher.match(allTrue));
}

TEST_F(NoneTrueMatcherTest_190, MatchMixedVectorReturnsFalse_190) {
    std::vector<bool> mixed = {false, true, false};
    EXPECT_FALSE(matcher.match(mixed));
}

TEST_F(NoneTrueMatcherTest_190, MatchSingleTrueReturnsFalse_190) {
    std::vector<bool> single = {true};
    EXPECT_FALSE(matcher.match(single));
}

TEST_F(NoneTrueMatcherTest_190, MatchSingleFalseReturnsTrue_190) {
    std::vector<bool> single = {false};
    EXPECT_TRUE(matcher.match(single));
}

TEST_F(NoneTrueMatcherTest_190, MatchFirstElementTrueReturnsFalse_190) {
    std::vector<bool> v = {true, false, false, false};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_190, MatchLastElementTrueReturnsFalse_190) {
    std::vector<bool> v = {false, false, false, true};
    EXPECT_FALSE(matcher.match(v));
}

// ========== match() tests with different container types ==========

TEST_F(NoneTrueMatcherTest_190, MatchArrayAllFalseReturnsTrue_190) {
    std::array<bool, 3> arr = {false, false, false};
    EXPECT_TRUE(matcher.match(arr));
}

TEST_F(NoneTrueMatcherTest_190, MatchArrayWithTrueReturnsFalse_190) {
    std::array<bool, 3> arr = {false, true, false};
    EXPECT_FALSE(matcher.match(arr));
}

TEST_F(NoneTrueMatcherTest_190, MatchListAllFalseReturnsTrue_190) {
    std::list<bool> lst = {false, false, false};
    EXPECT_TRUE(matcher.match(lst));
}

TEST_F(NoneTrueMatcherTest_190, MatchListWithTrueReturnsFalse_190) {
    std::list<bool> lst = {false, false, true};
    EXPECT_FALSE(matcher.match(lst));
}

TEST_F(NoneTrueMatcherTest_190, MatchEmptyArrayReturnsTrue_190) {
    std::array<bool, 0> arr = {};
    EXPECT_TRUE(matcher.match(arr));
}

// ========== match() tests with integer-like containers (truthy values) ==========

TEST_F(NoneTrueMatcherTest_190, MatchIntVectorAllZerosReturnsTrue_190) {
    std::vector<int> v = {0, 0, 0};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_190, MatchIntVectorWithNonZeroReturnsFalse_190) {
    std::vector<int> v = {0, 1, 0};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_190, MatchIntVectorWithNegativeReturnsFalse_190) {
    std::vector<int> v = {0, -1, 0};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_190, MatchEmptyIntVectorReturnsTrue_190) {
    std::vector<int> v;
    EXPECT_TRUE(matcher.match(v));
}

// ========== Large container tests ==========

TEST_F(NoneTrueMatcherTest_190, MatchLargeAllFalseVectorReturnsTrue_190) {
    std::vector<bool> v(1000, false);
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_190, MatchLargeVectorWithOneTrueReturnsFalse_190) {
    std::vector<bool> v(1000, false);
    v[999] = true;
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_190, MatchLargeVectorTrueInMiddleReturnsFalse_190) {
    std::vector<bool> v(1000, false);
    v[500] = true;
    EXPECT_FALSE(matcher.match(v));
}
