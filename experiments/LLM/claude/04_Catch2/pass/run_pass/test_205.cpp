#include <gtest/gtest.h>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <cmath>
#include <limits>

class WithinAbsMatcherTest_205 : public ::testing::Test {
protected:
};

// Normal operation tests

TEST_F(WithinAbsMatcherTest_205, ExactMatch_205) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.1);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST_F(WithinAbsMatcherTest_205, WithinMarginAbove_205) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.1);
    EXPECT_TRUE(matcher.match(1.05));
}

TEST_F(WithinAbsMatcherTest_205, WithinMarginBelow_205) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.1);
    EXPECT_TRUE(matcher.match(0.95));
}

TEST_F(WithinAbsMatcherTest_205, OutsideMarginAbove_205) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.1);
    EXPECT_FALSE(matcher.match(1.2));
}

TEST_F(WithinAbsMatcherTest_205, OutsideMarginBelow_205) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.1);
    EXPECT_FALSE(matcher.match(0.8));
}

// Boundary condition tests

TEST_F(WithinAbsMatcherTest_205, ExactlyAtUpperBoundary_205) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.1);
    EXPECT_TRUE(matcher.match(1.1));
}

TEST_F(WithinAbsMatcherTest_205, ExactlyAtLowerBoundary_205) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.1);
    EXPECT_TRUE(matcher.match(0.9));
}

TEST_F(WithinAbsMatcherTest_205, JustOutsideUpperBoundary_205) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.1);
    EXPECT_FALSE(matcher.match(1.1 + 1e-10));
}

TEST_F(WithinAbsMatcherTest_205, JustOutsideLowerBoundary_205) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.1);
    EXPECT_FALSE(matcher.match(0.9 - 1e-10));
}

TEST_F(WithinAbsMatcherTest_205, ZeroMargin_ExactMatch_205) {
    auto matcher = Catch::Matchers::WithinAbs(5.0, 0.0);
    EXPECT_TRUE(matcher.match(5.0));
}

TEST_F(WithinAbsMatcherTest_205, ZeroMargin_NoMatch_205) {
    auto matcher = Catch::Matchers::WithinAbs(5.0, 0.0);
    EXPECT_FALSE(matcher.match(5.0 + 1e-15));
}

TEST_F(WithinAbsMatcherTest_205, ZeroTarget_205) {
    auto matcher = Catch::Matchers::WithinAbs(0.0, 0.001);
    EXPECT_TRUE(matcher.match(0.0005));
}

TEST_F(WithinAbsMatcherTest_205, ZeroTargetOutside_205) {
    auto matcher = Catch::Matchers::WithinAbs(0.0, 0.001);
    EXPECT_FALSE(matcher.match(0.01));
}

TEST_F(WithinAbsMatcherTest_205, NegativeTarget_205) {
    auto matcher = Catch::Matchers::WithinAbs(-3.0, 0.5);
    EXPECT_TRUE(matcher.match(-3.3));
}

TEST_F(WithinAbsMatcherTest_205, NegativeTargetOutside_205) {
    auto matcher = Catch::Matchers::WithinAbs(-3.0, 0.5);
    EXPECT_FALSE(matcher.match(-4.0));
}

TEST_F(WithinAbsMatcherTest_205, LargeMargin_205) {
    auto matcher = Catch::Matchers::WithinAbs(0.0, 1e10);
    EXPECT_TRUE(matcher.match(1e9));
}

TEST_F(WithinAbsMatcherTest_205, VerySmallMargin_205) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 1e-15);
    EXPECT_TRUE(matcher.match(1.0));
    EXPECT_FALSE(matcher.match(1.0 + 1e-14));
}

// Describe test
TEST_F(WithinAbsMatcherTest_205, DescribeReturnsNonEmptyString_205) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.1);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

TEST_F(WithinAbsMatcherTest_205, DescribeContainsTargetInfo_205) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.1);
    std::string description = matcher.describe();
    // The description should mention the margin or target in some form
    EXPECT_NE(description.find("0.1"), std::string::npos);
}

// Special floating point values
TEST_F(WithinAbsMatcherTest_205, InfinityDoesNotMatch_205) {
    auto matcher = Catch::Matchers::WithinAbs(0.0, 1.0);
    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::infinity()));
}

TEST_F(WithinAbsMatcherTest_205, NaNDoesNotMatch_205) {
    auto matcher = Catch::Matchers::WithinAbs(0.0, 1.0);
    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::quiet_NaN()));
}

TEST_F(WithinAbsMatcherTest_205, NegativeInfinityDoesNotMatch_205) {
    auto matcher = Catch::Matchers::WithinAbs(0.0, 1.0);
    EXPECT_FALSE(matcher.match(-std::numeric_limits<double>::infinity()));
}
