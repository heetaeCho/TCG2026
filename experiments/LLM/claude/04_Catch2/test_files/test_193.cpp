#include <catch2/matchers/catch_matchers_quantifiers.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <vector>
#include <array>
#include <string>

#include <gtest/gtest.h>

using Catch::Matchers::AnyTrue;
using Catch::Matchers::AllTrue;
using Catch::Matchers::NoneTrue;

class AnyTrueMatcherTest_193 : public ::testing::Test {};
class AllTrueMatcherTest_193 : public ::testing::Test {};
class NoneTrueMatcherTest_193 : public ::testing::Test {};

// ========================
// AnyTrue Tests
// ========================

TEST_F(AnyTrueMatcherTest_193, MatchesWhenSingleElementIsTrue_193) {
    auto matcher = AnyTrue();
    std::vector<bool> v = {true};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_193, MatchesWhenAllElementsAreTrue_193) {
    auto matcher = AnyTrue();
    std::vector<bool> v = {true, true, true};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_193, MatchesWhenAtLeastOneElementIsTrue_193) {
    auto matcher = AnyTrue();
    std::vector<bool> v = {false, false, true, false};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_193, DoesNotMatchWhenAllElementsAreFalse_193) {
    auto matcher = AnyTrue();
    std::vector<bool> v = {false, false, false};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_193, DoesNotMatchEmptyContainer_193) {
    auto matcher = AnyTrue();
    std::vector<bool> v = {};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_193, MatchesWhenFirstElementIsTrue_193) {
    auto matcher = AnyTrue();
    std::vector<bool> v = {true, false, false};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_193, MatchesWhenLastElementIsTrue_193) {
    auto matcher = AnyTrue();
    std::vector<bool> v = {false, false, true};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_193, SingleFalseElementDoesNotMatch_193) {
    auto matcher = AnyTrue();
    std::vector<bool> v = {false};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_193, DescribeReturnsNonEmptyString_193) {
    auto matcher = AnyTrue();
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}

// ========================
// AllTrue Tests
// ========================

TEST_F(AllTrueMatcherTest_193, MatchesWhenAllElementsAreTrue_193) {
    auto matcher = AllTrue();
    std::vector<bool> v = {true, true, true};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_193, DoesNotMatchWhenAnyElementIsFalse_193) {
    auto matcher = AllTrue();
    std::vector<bool> v = {true, false, true};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_193, MatchesEmptyContainer_193) {
    auto matcher = AllTrue();
    std::vector<bool> v = {};
    // Vacuously true for AllTrue on empty
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_193, DoesNotMatchAllFalse_193) {
    auto matcher = AllTrue();
    std::vector<bool> v = {false, false, false};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_193, MatchesSingleTrueElement_193) {
    auto matcher = AllTrue();
    std::vector<bool> v = {true};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_193, DescribeReturnsNonEmptyString_193) {
    auto matcher = AllTrue();
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}

// ========================
// NoneTrue Tests
// ========================

TEST_F(NoneTrueMatcherTest_193, MatchesWhenAllElementsAreFalse_193) {
    auto matcher = NoneTrue();
    std::vector<bool> v = {false, false, false};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_193, DoesNotMatchWhenAnyElementIsTrue_193) {
    auto matcher = NoneTrue();
    std::vector<bool> v = {false, true, false};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_193, MatchesEmptyContainer_193) {
    auto matcher = NoneTrue();
    std::vector<bool> v = {};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_193, DoesNotMatchAllTrue_193) {
    auto matcher = NoneTrue();
    std::vector<bool> v = {true, true, true};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_193, MatchesSingleFalseElement_193) {
    auto matcher = NoneTrue();
    std::vector<bool> v = {false};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_193, DoesNotMatchSingleTrueElement_193) {
    auto matcher = NoneTrue();
    std::vector<bool> v = {true};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_193, DescribeReturnsNonEmptyString_193) {
    auto matcher = NoneTrue();
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}
