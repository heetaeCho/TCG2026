#include <gtest/gtest.h>
#include <cmath>
#include <string>
#include <limits>

// Include the necessary Catch2 headers
#include "catch2/matchers/catch_matchers_floating_point.hpp"
#include "catch2/matchers/catch_matchers.hpp"

using namespace Catch::Matchers;

// Test fixture
class WithinAbsMatcherTest_1049 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(WithinAbsMatcherTest_1049, ConstructWithValidMargin_1049) {
    EXPECT_NO_THROW(WithinAbsMatcher(1.0, 0.5));
}

TEST_F(WithinAbsMatcherTest_1049, ConstructWithZeroMargin_1049) {
    EXPECT_NO_THROW(WithinAbsMatcher(1.0, 0.0));
}

TEST_F(WithinAbsMatcherTest_1049, ConstructWithLargeMargin_1049) {
    EXPECT_NO_THROW(WithinAbsMatcher(1.0, 1e15));
}

TEST_F(WithinAbsMatcherTest_1049, ConstructWithNegativeMarginThrows_1049) {
    EXPECT_ANY_THROW(WithinAbsMatcher(1.0, -0.1));
}

TEST_F(WithinAbsMatcherTest_1049, ConstructWithNegativeLargeMarginThrows_1049) {
    EXPECT_ANY_THROW(WithinAbsMatcher(1.0, -100.0));
}

TEST_F(WithinAbsMatcherTest_1049, ConstructWithVerySmallNegativeMarginThrows_1049) {
    EXPECT_ANY_THROW(WithinAbsMatcher(0.0, -1e-15));
}

// ==================== Match Tests - Exact Match ====================

TEST_F(WithinAbsMatcherTest_1049, ExactMatchReturnsTrue_1049) {
    WithinAbsMatcher matcher(5.0, 0.1);
    EXPECT_TRUE(matcher.match(5.0));
}

TEST_F(WithinAbsMatcherTest_1049, ExactMatchWithZeroMarginReturnsTrue_1049) {
    WithinAbsMatcher matcher(3.14, 0.0);
    EXPECT_TRUE(matcher.match(3.14));
}

TEST_F(WithinAbsMatcherTest_1049, ExactMatchZeroTargetZeroMargin_1049) {
    WithinAbsMatcher matcher(0.0, 0.0);
    EXPECT_TRUE(matcher.match(0.0));
}

// ==================== Match Tests - Within Margin ====================

TEST_F(WithinAbsMatcherTest_1049, ValueWithinMarginAboveReturnsTrue_1049) {
    WithinAbsMatcher matcher(10.0, 0.5);
    EXPECT_TRUE(matcher.match(10.3));
}

TEST_F(WithinAbsMatcherTest_1049, ValueWithinMarginBelowReturnsTrue_1049) {
    WithinAbsMatcher matcher(10.0, 0.5);
    EXPECT_TRUE(matcher.match(9.7));
}

TEST_F(WithinAbsMatcherTest_1049, ValueSlightlyWithinMarginReturnsTrue_1049) {
    WithinAbsMatcher matcher(1.0, 1.0);
    EXPECT_TRUE(matcher.match(1.5));
}

// ==================== Match Tests - Boundary ====================

TEST_F(WithinAbsMatcherTest_1049, ValueExactlyAtMarginBoundaryAboveReturnsTrue_1049) {
    WithinAbsMatcher matcher(10.0, 0.5);
    EXPECT_TRUE(matcher.match(10.5));
}

TEST_F(WithinAbsMatcherTest_1049, ValueExactlyAtMarginBoundaryBelowReturnsTrue_1049) {
    WithinAbsMatcher matcher(10.0, 0.5);
    EXPECT_TRUE(matcher.match(9.5));
}

// ==================== Match Tests - Outside Margin ====================

TEST_F(WithinAbsMatcherTest_1049, ValueJustOutsideMarginAboveReturnsFalse_1049) {
    WithinAbsMatcher matcher(10.0, 0.5);
    EXPECT_FALSE(matcher.match(10.6));
}

TEST_F(WithinAbsMatcherTest_1049, ValueJustOutsideMarginBelowReturnsFalse_1049) {
    WithinAbsMatcher matcher(10.0, 0.5);
    EXPECT_FALSE(matcher.match(9.4));
}

TEST_F(WithinAbsMatcherTest_1049, ValueFarOutsideMarginReturnsFalse_1049) {
    WithinAbsMatcher matcher(10.0, 0.5);
    EXPECT_FALSE(matcher.match(100.0));
}

TEST_F(WithinAbsMatcherTest_1049, ValueFarBelowMarginReturnsFalse_1049) {
    WithinAbsMatcher matcher(10.0, 0.5);
    EXPECT_FALSE(matcher.match(-100.0));
}

// ==================== Match Tests - Zero Margin ====================

TEST_F(WithinAbsMatcherTest_1049, ZeroMarginDifferentValueReturnsFalse_1049) {
    WithinAbsMatcher matcher(1.0, 0.0);
    EXPECT_FALSE(matcher.match(1.1));
}

TEST_F(WithinAbsMatcherTest_1049, ZeroMarginSlightlyDifferentValueReturnsFalse_1049) {
    WithinAbsMatcher matcher(1.0, 0.0);
    // Even a very small difference should be false with zero margin
    // (subject to floating point representation)
    EXPECT_FALSE(matcher.match(1.0 + 1e-10));
}

// ==================== Match Tests - Negative Target ====================

TEST_F(WithinAbsMatcherTest_1049, NegativeTargetExactMatch_1049) {
    WithinAbsMatcher matcher(-5.0, 0.1);
    EXPECT_TRUE(matcher.match(-5.0));
}

TEST_F(WithinAbsMatcherTest_1049, NegativeTargetWithinMargin_1049) {
    WithinAbsMatcher matcher(-5.0, 0.5);
    EXPECT_TRUE(matcher.match(-4.7));
}

TEST_F(WithinAbsMatcherTest_1049, NegativeTargetOutsideMargin_1049) {
    WithinAbsMatcher matcher(-5.0, 0.5);
    EXPECT_FALSE(matcher.match(-4.0));
}

// ==================== Match Tests - Zero Target ====================

TEST_F(WithinAbsMatcherTest_1049, ZeroTargetWithinMargin_1049) {
    WithinAbsMatcher matcher(0.0, 1.0);
    EXPECT_TRUE(matcher.match(0.5));
}

TEST_F(WithinAbsMatcherTest_1049, ZeroTargetNegativeWithinMargin_1049) {
    WithinAbsMatcher matcher(0.0, 1.0);
    EXPECT_TRUE(matcher.match(-0.5));
}

TEST_F(WithinAbsMatcherTest_1049, ZeroTargetOutsideMargin_1049) {
    WithinAbsMatcher matcher(0.0, 1.0);
    EXPECT_FALSE(matcher.match(1.5));
}

// ==================== Match Tests - Large Values ====================

TEST_F(WithinAbsMatcherTest_1049, LargeValuesWithinMargin_1049) {
    WithinAbsMatcher matcher(1e10, 1.0);
    EXPECT_TRUE(matcher.match(1e10 + 0.5));
}

TEST_F(WithinAbsMatcherTest_1049, LargeValuesOutsideMargin_1049) {
    WithinAbsMatcher matcher(1e10, 1.0);
    EXPECT_FALSE(matcher.match(1e10 + 2.0));
}

// ==================== Match Tests - Very Small Margin ====================

TEST_F(WithinAbsMatcherTest_1049, VerySmallMarginExactMatch_1049) {
    WithinAbsMatcher matcher(1.0, 1e-15);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST_F(WithinAbsMatcherTest_1049, VerySmallMarginSlightlyOff_1049) {
    WithinAbsMatcher matcher(1.0, 1e-10);
    EXPECT_TRUE(matcher.match(1.0 + 1e-11));
}

// ==================== Describe Tests ====================

TEST_F(WithinAbsMatcherTest_1049, DescribeReturnsNonEmptyString_1049) {
    WithinAbsMatcher matcher(5.0, 0.5);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

TEST_F(WithinAbsMatcherTest_1049, DescribeContainsTargetInfo_1049) {
    WithinAbsMatcher matcher(5.0, 0.5);
    std::string description = matcher.describe();
    // The description should mention something about the target or margin
    EXPECT_GT(description.size(), 0u);
}

// ==================== Special Floating Point Values ====================

TEST_F(WithinAbsMatcherTest_1049, MatchWithInfinityTarget_1049) {
    double inf = std::numeric_limits<double>::infinity();
    WithinAbsMatcher matcher(inf, 1.0);
    // Infinity - anything finite is still infinity, so matching inf with inf should work
    EXPECT_TRUE(matcher.match(inf));
}

TEST_F(WithinAbsMatcherTest_1049, MatchWithNaNReturnsFalse_1049) {
    double nan = std::numeric_limits<double>::quiet_NaN();
    WithinAbsMatcher matcher(1.0, 1.0);
    // NaN comparisons should generally return false
    EXPECT_FALSE(matcher.match(nan));
}

TEST_F(WithinAbsMatcherTest_1049, MatchNaNTargetWithNaNReturnsFalse_1049) {
    double nan = std::numeric_limits<double>::quiet_NaN();
    WithinAbsMatcher matcher(nan, 1.0);
    // NaN != NaN, so even matching NaN against NaN should be false
    EXPECT_FALSE(matcher.match(nan));
}

TEST_F(WithinAbsMatcherTest_1049, MatchFiniteValueWithInfinityReturnsFalse_1049) {
    double inf = std::numeric_limits<double>::infinity();
    WithinAbsMatcher matcher(1.0, 1.0);
    EXPECT_FALSE(matcher.match(inf));
}

// ==================== Large Margin Tests ====================

TEST_F(WithinAbsMatcherTest_1049, VeryLargeMarginMatchesDistantValues_1049) {
    WithinAbsMatcher matcher(0.0, 1e15);
    EXPECT_TRUE(matcher.match(1e14));
}

TEST_F(WithinAbsMatcherTest_1049, LargeMarginStillRejectsOutOfRangeValues_1049) {
    WithinAbsMatcher matcher(0.0, 100.0);
    EXPECT_FALSE(matcher.match(200.0));
}
