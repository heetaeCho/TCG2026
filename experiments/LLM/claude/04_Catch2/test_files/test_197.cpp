#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Include the header for the class under test
#include "catch2/matchers/catch_matchers_floating_point.hpp"

using Catch::Matchers::WithinAbsMatcher;

class WithinAbsMatcherTest_197 : public ::testing::Test {
protected:
};

// Normal operation tests

TEST_F(WithinAbsMatcherTest_197, ExactMatch_197) {
    WithinAbsMatcher matcher(5.0, 0.1);
    EXPECT_TRUE(matcher.match(5.0));
}

TEST_F(WithinAbsMatcherTest_197, WithinMarginAbove_197) {
    WithinAbsMatcher matcher(5.0, 0.5);
    EXPECT_TRUE(matcher.match(5.3));
}

TEST_F(WithinAbsMatcherTest_197, WithinMarginBelow_197) {
    WithinAbsMatcher matcher(5.0, 0.5);
    EXPECT_TRUE(matcher.match(4.7));
}

TEST_F(WithinAbsMatcherTest_197, AtUpperBoundary_197) {
    WithinAbsMatcher matcher(5.0, 0.5);
    EXPECT_TRUE(matcher.match(5.5));
}

TEST_F(WithinAbsMatcherTest_197, AtLowerBoundary_197) {
    WithinAbsMatcher matcher(5.0, 0.5);
    EXPECT_TRUE(matcher.match(4.5));
}

TEST_F(WithinAbsMatcherTest_197, JustOutsideUpperBoundary_197) {
    WithinAbsMatcher matcher(5.0, 0.5);
    EXPECT_FALSE(matcher.match(5.5 + 1e-10));
}

TEST_F(WithinAbsMatcherTest_197, JustOutsideLowerBoundary_197) {
    WithinAbsMatcher matcher(5.0, 0.5);
    EXPECT_FALSE(matcher.match(4.5 - 1e-10));
}

TEST_F(WithinAbsMatcherTest_197, FarAboveTarget_197) {
    WithinAbsMatcher matcher(5.0, 0.1);
    EXPECT_FALSE(matcher.match(10.0));
}

TEST_F(WithinAbsMatcherTest_197, FarBelowTarget_197) {
    WithinAbsMatcher matcher(5.0, 0.1);
    EXPECT_FALSE(matcher.match(0.0));
}

// Zero target tests

TEST_F(WithinAbsMatcherTest_197, ZeroTargetExactMatch_197) {
    WithinAbsMatcher matcher(0.0, 0.01);
    EXPECT_TRUE(matcher.match(0.0));
}

TEST_F(WithinAbsMatcherTest_197, ZeroTargetWithinMargin_197) {
    WithinAbsMatcher matcher(0.0, 0.01);
    EXPECT_TRUE(matcher.match(0.005));
}

TEST_F(WithinAbsMatcherTest_197, ZeroTargetNegativeWithinMargin_197) {
    WithinAbsMatcher matcher(0.0, 0.01);
    EXPECT_TRUE(matcher.match(-0.005));
}

TEST_F(WithinAbsMatcherTest_197, ZeroTargetOutsideMargin_197) {
    WithinAbsMatcher matcher(0.0, 0.01);
    EXPECT_FALSE(matcher.match(0.02));
}

// Zero margin tests

TEST_F(WithinAbsMatcherTest_197, ZeroMarginExactMatch_197) {
    WithinAbsMatcher matcher(3.14, 0.0);
    EXPECT_TRUE(matcher.match(3.14));
}

TEST_F(WithinAbsMatcherTest_197, ZeroMarginSlightlyOff_197) {
    WithinAbsMatcher matcher(3.14, 0.0);
    EXPECT_FALSE(matcher.match(3.15));
}

// Negative target tests

TEST_F(WithinAbsMatcherTest_197, NegativeTargetExactMatch_197) {
    WithinAbsMatcher matcher(-5.0, 0.5);
    EXPECT_TRUE(matcher.match(-5.0));
}

TEST_F(WithinAbsMatcherTest_197, NegativeTargetWithinMargin_197) {
    WithinAbsMatcher matcher(-5.0, 0.5);
    EXPECT_TRUE(matcher.match(-4.7));
}

TEST_F(WithinAbsMatcherTest_197, NegativeTargetAtUpperBoundary_197) {
    WithinAbsMatcher matcher(-5.0, 0.5);
    EXPECT_TRUE(matcher.match(-4.5));
}

TEST_F(WithinAbsMatcherTest_197, NegativeTargetAtLowerBoundary_197) {
    WithinAbsMatcher matcher(-5.0, 0.5);
    EXPECT_TRUE(matcher.match(-5.5));
}

TEST_F(WithinAbsMatcherTest_197, NegativeTargetOutsideMargin_197) {
    WithinAbsMatcher matcher(-5.0, 0.5);
    EXPECT_FALSE(matcher.match(-6.0));
}

// Large values

TEST_F(WithinAbsMatcherTest_197, LargeValuesWithinMargin_197) {
    WithinAbsMatcher matcher(1e15, 1.0);
    EXPECT_TRUE(matcher.match(1e15 + 0.5));
}

TEST_F(WithinAbsMatcherTest_197, LargeValuesOutsideMargin_197) {
    WithinAbsMatcher matcher(1e15, 1.0);
    EXPECT_FALSE(matcher.match(1e15 + 2.0));
}

// Very small margin

TEST_F(WithinAbsMatcherTest_197, VerySmallMarginExactMatch_197) {
    WithinAbsMatcher matcher(1.0, 1e-15);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST_F(WithinAbsMatcherTest_197, VerySmallMarginSlightlyOff_197) {
    WithinAbsMatcher matcher(1.0, 1e-15);
    EXPECT_TRUE(matcher.match(1.0 + 5e-16));
}

// Large margin

TEST_F(WithinAbsMatcherTest_197, LargeMarginCoversWideRange_197) {
    WithinAbsMatcher matcher(0.0, 1000.0);
    EXPECT_TRUE(matcher.match(999.0));
    EXPECT_TRUE(matcher.match(-999.0));
    EXPECT_TRUE(matcher.match(1000.0));
    EXPECT_FALSE(matcher.match(1001.0));
}

// Symmetry test

TEST_F(WithinAbsMatcherTest_197, SymmetricBehavior_197) {
    WithinAbsMatcher matcher(10.0, 2.0);
    EXPECT_TRUE(matcher.match(8.0));  // lower boundary
    EXPECT_TRUE(matcher.match(12.0)); // upper boundary
    EXPECT_FALSE(matcher.match(7.9));
    EXPECT_FALSE(matcher.match(12.1));
}

// Describe method test

TEST_F(WithinAbsMatcherTest_197, DescribeReturnsNonEmptyString_197) {
    WithinAbsMatcher matcher(5.0, 0.1);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

TEST_F(WithinAbsMatcherTest_197, DescribeContainsMarginInfo_197) {
    WithinAbsMatcher matcher(5.0, 0.1);
    std::string description = matcher.describe();
    // The description should mention the target or margin in some form
    EXPECT_GT(description.size(), 0u);
}

// Special floating point values

TEST_F(WithinAbsMatcherTest_197, MatcheeIsNegativeZero_197) {
    WithinAbsMatcher matcher(0.0, 0.01);
    EXPECT_TRUE(matcher.match(-0.0));
}

TEST_F(WithinAbsMatcherTest_197, TargetAndMatcheeBothNegativeZero_197) {
    WithinAbsMatcher matcher(-0.0, 0.0);
    EXPECT_TRUE(matcher.match(0.0));
}
