#include <gtest/gtest.h>
#include <string>
#include <cmath>
#include <limits>

// Include the header for WithinAbsMatcher
#include "catch2/matchers/catch_matchers_floating_point.hpp"

using namespace Catch::Matchers;

// Test fixture
class WithinAbsMatcherTest_198 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== describe() tests ====================

TEST_F(WithinAbsMatcherTest_198, DescribeContainsMarginAndTarget_198) {
    WithinAbsMatcher matcher(5.0, 0.1);
    std::string description = matcher.describe();
    // The description should mention the margin and target
    EXPECT_NE(description.find("0.1"), std::string::npos);
    EXPECT_NE(description.find("5.0"), std::string::npos);
}

TEST_F(WithinAbsMatcherTest_198, DescribeContainsWithinKeyword_198) {
    WithinAbsMatcher matcher(10.0, 0.5);
    std::string description = matcher.describe();
    EXPECT_NE(description.find("is within"), std::string::npos);
}

TEST_F(WithinAbsMatcherTest_198, DescribeContainsOfKeyword_198) {
    WithinAbsMatcher matcher(3.14, 0.01);
    std::string description = matcher.describe();
    EXPECT_NE(description.find("of"), std::string::npos);
}

TEST_F(WithinAbsMatcherTest_198, DescribeWithZeroMargin_198) {
    WithinAbsMatcher matcher(1.0, 0.0);
    std::string description = matcher.describe();
    EXPECT_NE(description.find("0"), std::string::npos);
    EXPECT_NE(description.find("1"), std::string::npos);
}

TEST_F(WithinAbsMatcherTest_198, DescribeWithNegativeTarget_198) {
    WithinAbsMatcher matcher(-5.0, 1.0);
    std::string description = matcher.describe();
    EXPECT_NE(description.find("-5"), std::string::npos);
}

TEST_F(WithinAbsMatcherTest_198, DescribeWithLargeValues_198) {
    WithinAbsMatcher matcher(1000000.0, 0.001);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// ==================== match() tests ====================

TEST_F(WithinAbsMatcherTest_198, MatchExactValue_198) {
    WithinAbsMatcher matcher(5.0, 0.1);
    EXPECT_TRUE(matcher.match(5.0));
}

TEST_F(WithinAbsMatcherTest_198, MatchWithinMargin_198) {
    WithinAbsMatcher matcher(5.0, 0.1);
    EXPECT_TRUE(matcher.match(5.05));
}

TEST_F(WithinAbsMatcherTest_198, MatchAtExactUpperBoundary_198) {
    WithinAbsMatcher matcher(5.0, 0.1);
    EXPECT_TRUE(matcher.match(5.1));
}

TEST_F(WithinAbsMatcherTest_198, MatchAtExactLowerBoundary_198) {
    WithinAbsMatcher matcher(5.0, 0.1);
    EXPECT_TRUE(matcher.match(4.9));
}

TEST_F(WithinAbsMatcherTest_198, NoMatchOutsideMarginAbove_198) {
    WithinAbsMatcher matcher(5.0, 0.1);
    EXPECT_FALSE(matcher.match(5.2));
}

TEST_F(WithinAbsMatcherTest_198, NoMatchOutsideMarginBelow_198) {
    WithinAbsMatcher matcher(5.0, 0.1);
    EXPECT_FALSE(matcher.match(4.8));
}

TEST_F(WithinAbsMatcherTest_198, MatchWithZeroMargin_198) {
    WithinAbsMatcher matcher(5.0, 0.0);
    EXPECT_TRUE(matcher.match(5.0));
}

TEST_F(WithinAbsMatcherTest_198, NoMatchWithZeroMarginSlightlyOff_198) {
    WithinAbsMatcher matcher(5.0, 0.0);
    EXPECT_FALSE(matcher.match(5.0 + 1e-10));
}

TEST_F(WithinAbsMatcherTest_198, MatchZeroTarget_198) {
    WithinAbsMatcher matcher(0.0, 0.5);
    EXPECT_TRUE(matcher.match(0.3));
}

TEST_F(WithinAbsMatcherTest_198, MatchNegativeTarget_198) {
    WithinAbsMatcher matcher(-3.0, 0.5);
    EXPECT_TRUE(matcher.match(-3.2));
}

TEST_F(WithinAbsMatcherTest_198, NoMatchNegativeTargetOutside_198) {
    WithinAbsMatcher matcher(-3.0, 0.5);
    EXPECT_FALSE(matcher.match(-4.0));
}

TEST_F(WithinAbsMatcherTest_198, MatchNegativeMatcheeWithPositiveTarget_198) {
    WithinAbsMatcher matcher(0.0, 1.0);
    EXPECT_TRUE(matcher.match(-0.5));
}

TEST_F(WithinAbsMatcherTest_198, MatchLargeMargin_198) {
    WithinAbsMatcher matcher(0.0, 1000.0);
    EXPECT_TRUE(matcher.match(999.0));
}

TEST_F(WithinAbsMatcherTest_198, NoMatchLargeMarginExceeded_198) {
    WithinAbsMatcher matcher(0.0, 1000.0);
    EXPECT_FALSE(matcher.match(1001.0));
}

TEST_F(WithinAbsMatcherTest_198, MatchVerySmallMargin_198) {
    WithinAbsMatcher matcher(1.0, 1e-15);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST_F(WithinAbsMatcherTest_198, MatchSymmetricPositive_198) {
    WithinAbsMatcher matcher(10.0, 2.0);
    EXPECT_TRUE(matcher.match(11.0));
    EXPECT_TRUE(matcher.match(9.0));
    EXPECT_TRUE(matcher.match(12.0));
    EXPECT_TRUE(matcher.match(8.0));
}

TEST_F(WithinAbsMatcherTest_198, NoMatchSymmetricOutside_198) {
    WithinAbsMatcher matcher(10.0, 2.0);
    EXPECT_FALSE(matcher.match(12.1));
    EXPECT_FALSE(matcher.match(7.9));
}

TEST_F(WithinAbsMatcherTest_198, MatchWithNaNMatchee_198) {
    WithinAbsMatcher matcher(5.0, 1.0);
    double nan_val = std::numeric_limits<double>::quiet_NaN();
    // NaN should not match anything
    EXPECT_FALSE(matcher.match(nan_val));
}

TEST_F(WithinAbsMatcherTest_198, MatchWithInfinityMatchee_198) {
    WithinAbsMatcher matcher(5.0, 1.0);
    double inf_val = std::numeric_limits<double>::infinity();
    EXPECT_FALSE(matcher.match(inf_val));
}

TEST_F(WithinAbsMatcherTest_198, MatchWithNegativeInfinityMatchee_198) {
    WithinAbsMatcher matcher(5.0, 1.0);
    double neg_inf_val = -std::numeric_limits<double>::infinity();
    EXPECT_FALSE(matcher.match(neg_inf_val));
}

TEST_F(WithinAbsMatcherTest_198, MatchBothNegativeValues_198) {
    WithinAbsMatcher matcher(-100.0, 5.0);
    EXPECT_TRUE(matcher.match(-102.0));
    EXPECT_TRUE(matcher.match(-98.0));
    EXPECT_FALSE(matcher.match(-106.0));
    EXPECT_FALSE(matcher.match(-94.0));
}

TEST_F(WithinAbsMatcherTest_198, MatchWithVeryLargeTarget_198) {
    WithinAbsMatcher matcher(1e300, 1e290);
    EXPECT_TRUE(matcher.match(1e300));
}

TEST_F(WithinAbsMatcherTest_198, ConstructorAndMatchIntegration_198) {
    // Test that creating multiple matchers with different parameters works
    WithinAbsMatcher matcher1(0.0, 0.1);
    WithinAbsMatcher matcher2(0.0, 1.0);

    EXPECT_FALSE(matcher1.match(0.5));
    EXPECT_TRUE(matcher2.match(0.5));
}
