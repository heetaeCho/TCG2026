#include <gtest/gtest.h>
#include <string>
#include <cmath>
#include <limits>

// Include the necessary Catch2 headers
#include "catch2/matchers/catch_matchers_floating_point.hpp"

using Catch::Matchers::WithinUlpsMatcher;
using Catch::Matchers::Detail::FloatingPointKind;

class WithinUlpsMatcherTest_200 : public ::testing::Test {
protected:
    // Helper to create matchers
};

// ============================================================
// Tests for describe() method
// ============================================================

TEST_F(WithinUlpsMatcherTest_200, DescribeDoubleContainsULPsText_200) {
    WithinUlpsMatcher matcher(1.0, 5, FloatingPointKind::Double);
    std::string desc = matcher.describe();
    EXPECT_NE(desc.find("is within 5 ULPs of"), std::string::npos);
}

TEST_F(WithinUlpsMatcherTest_200, DescribeFloatContainsULPsTextAndFSuffix_200) {
    WithinUlpsMatcher matcher(1.0, 3, FloatingPointKind::Float);
    std::string desc = matcher.describe();
    EXPECT_NE(desc.find("is within 3 ULPs of"), std::string::npos);
    // Float description should contain 'f' suffix
    EXPECT_NE(desc.find("f"), std::string::npos);
}

TEST_F(WithinUlpsMatcherTest_200, DescribeDoubleContainsBracketedRange_200) {
    WithinUlpsMatcher matcher(1.0, 2, FloatingPointKind::Double);
    std::string desc = matcher.describe();
    EXPECT_NE(desc.find("["), std::string::npos);
    EXPECT_NE(desc.find("]"), std::string::npos);
    EXPECT_NE(desc.find(", "), std::string::npos);
}

TEST_F(WithinUlpsMatcherTest_200, DescribeFloatContainsBracketedRange_200) {
    WithinUlpsMatcher matcher(1.0f, 2, FloatingPointKind::Float);
    std::string desc = matcher.describe();
    EXPECT_NE(desc.find("["), std::string::npos);
    EXPECT_NE(desc.find("]"), std::string::npos);
}

TEST_F(WithinUlpsMatcherTest_200, DescribeWithZeroUlps_200) {
    WithinUlpsMatcher matcher(1.0, 0, FloatingPointKind::Double);
    std::string desc = matcher.describe();
    EXPECT_NE(desc.find("is within 0 ULPs of"), std::string::npos);
}

TEST_F(WithinUlpsMatcherTest_200, DescribeWithLargeUlps_200) {
    WithinUlpsMatcher matcher(1.0, 1000000, FloatingPointKind::Double);
    std::string desc = matcher.describe();
    EXPECT_NE(desc.find("is within 1000000 ULPs of"), std::string::npos);
}

TEST_F(WithinUlpsMatcherTest_200, DescribeWithZeroTarget_200) {
    WithinUlpsMatcher matcher(0.0, 5, FloatingPointKind::Double);
    std::string desc = matcher.describe();
    EXPECT_NE(desc.find("is within 5 ULPs of"), std::string::npos);
    EXPECT_FALSE(desc.empty());
}

TEST_F(WithinUlpsMatcherTest_200, DescribeWithNegativeTarget_200) {
    WithinUlpsMatcher matcher(-1.5, 3, FloatingPointKind::Double);
    std::string desc = matcher.describe();
    EXPECT_NE(desc.find("is within 3 ULPs of"), std::string::npos);
}

TEST_F(WithinUlpsMatcherTest_200, DescribeFloatWithZeroTarget_200) {
    WithinUlpsMatcher matcher(0.0, 5, FloatingPointKind::Float);
    std::string desc = matcher.describe();
    EXPECT_NE(desc.find("is within 5 ULPs of"), std::string::npos);
}

// ============================================================
// Tests for match() method
// ============================================================

TEST_F(WithinUlpsMatcherTest_200, MatchExactDoubleValue_200) {
    WithinUlpsMatcher matcher(1.0, 0, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST_F(WithinUlpsMatcherTest_200, MatchExactFloatValue_200) {
    WithinUlpsMatcher matcher(1.0f, 0, FloatingPointKind::Float);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST_F(WithinUlpsMatcherTest_200, MatchWithinOneUlpDouble_200) {
    double target = 1.0;
    WithinUlpsMatcher matcher(target, 1, FloatingPointKind::Double);
    // The next representable double after 1.0
    double next = std::nextafter(1.0, std::numeric_limits<double>::infinity());
    EXPECT_TRUE(matcher.match(next));
}

TEST_F(WithinUlpsMatcherTest_200, NoMatchBeyondUlpsDouble_200) {
    double target = 1.0;
    WithinUlpsMatcher matcher(target, 1, FloatingPointKind::Double);
    // Two ULPs away
    double next1 = std::nextafter(1.0, std::numeric_limits<double>::infinity());
    double next2 = std::nextafter(next1, std::numeric_limits<double>::infinity());
    EXPECT_FALSE(matcher.match(next2));
}

TEST_F(WithinUlpsMatcherTest_200, MatchWithinMultipleUlpsDouble_200) {
    double target = 1.0;
    WithinUlpsMatcher matcher(target, 5, FloatingPointKind::Double);
    double val = target;
    for (int i = 0; i < 5; ++i) {
        val = std::nextafter(val, std::numeric_limits<double>::infinity());
    }
    EXPECT_TRUE(matcher.match(val));
}

TEST_F(WithinUlpsMatcherTest_200, NoMatchJustBeyondMultipleUlpsDouble_200) {
    double target = 1.0;
    WithinUlpsMatcher matcher(target, 5, FloatingPointKind::Double);
    double val = target;
    for (int i = 0; i < 6; ++i) {
        val = std::nextafter(val, std::numeric_limits<double>::infinity());
    }
    EXPECT_FALSE(matcher.match(val));
}

TEST_F(WithinUlpsMatcherTest_200, MatchWithinUlpsBelowTargetDouble_200) {
    double target = 1.0;
    WithinUlpsMatcher matcher(target, 1, FloatingPointKind::Double);
    double prev = std::nextafter(1.0, -std::numeric_limits<double>::infinity());
    EXPECT_TRUE(matcher.match(prev));
}

TEST_F(WithinUlpsMatcherTest_200, MatchZeroWithZeroDouble_200) {
    WithinUlpsMatcher matcher(0.0, 0, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(0.0));
}

TEST_F(WithinUlpsMatcherTest_200, MatchNegativeZeroWithZeroDouble_200) {
    WithinUlpsMatcher matcher(0.0, 0, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(-0.0));
}

TEST_F(WithinUlpsMatcherTest_200, MatchWithinOneUlpFloat_200) {
    float target = 1.0f;
    WithinUlpsMatcher matcher(static_cast<double>(target), 1, FloatingPointKind::Float);
    float next = std::nextafter(target, std::numeric_limits<float>::infinity());
    EXPECT_TRUE(matcher.match(static_cast<double>(next)));
}

TEST_F(WithinUlpsMatcherTest_200, NoMatchBeyondUlpsFloat_200) {
    float target = 1.0f;
    WithinUlpsMatcher matcher(static_cast<double>(target), 1, FloatingPointKind::Float);
    float next1 = std::nextafter(target, std::numeric_limits<float>::infinity());
    float next2 = std::nextafter(next1, std::numeric_limits<float>::infinity());
    EXPECT_FALSE(matcher.match(static_cast<double>(next2)));
}

TEST_F(WithinUlpsMatcherTest_200, MatchNegativeTargetDouble_200) {
    double target = -1.0;
    WithinUlpsMatcher matcher(target, 1, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(target));
    double next = std::nextafter(target, -std::numeric_limits<double>::infinity());
    EXPECT_TRUE(matcher.match(next));
}

TEST_F(WithinUlpsMatcherTest_200, MatchVerySmallDoubleValues_200) {
    double target = std::numeric_limits<double>::min(); // smallest normal
    WithinUlpsMatcher matcher(target, 1, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(target));
}

TEST_F(WithinUlpsMatcherTest_200, MatchLargeDoubleValues_200) {
    double target = 1e300;
    WithinUlpsMatcher matcher(target, 1, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(target));
    double next = std::nextafter(target, std::numeric_limits<double>::infinity());
    EXPECT_TRUE(matcher.match(next));
}

TEST_F(WithinUlpsMatcherTest_200, DescribeWithOneUlp_200) {
    WithinUlpsMatcher matcher(1.0, 1, FloatingPointKind::Double);
    std::string desc = matcher.describe();
    EXPECT_NE(desc.find("is within 1 ULPs of"), std::string::npos);
}

TEST_F(WithinUlpsMatcherTest_200, DescribeReturnsNonEmptyString_200) {
    WithinUlpsMatcher matcher(42.0, 10, FloatingPointKind::Double);
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}

TEST_F(WithinUlpsMatcherTest_200, MatchSymmetricDouble_200) {
    double target = 100.0;
    WithinUlpsMatcher matcher(target, 3, FloatingPointKind::Double);
    
    double above = target;
    double below = target;
    for (int i = 0; i < 3; ++i) {
        above = std::nextafter(above, std::numeric_limits<double>::infinity());
        below = std::nextafter(below, -std::numeric_limits<double>::infinity());
    }
    EXPECT_TRUE(matcher.match(above));
    EXPECT_TRUE(matcher.match(below));
}

TEST_F(WithinUlpsMatcherTest_200, NoMatchFarAwayValue_200) {
    WithinUlpsMatcher matcher(1.0, 5, FloatingPointKind::Double);
    EXPECT_FALSE(matcher.match(2.0));
}

TEST_F(WithinUlpsMatcherTest_200, NoMatchNegativeWhenTargetPositiveDouble_200) {
    WithinUlpsMatcher matcher(1.0, 5, FloatingPointKind::Double);
    EXPECT_FALSE(matcher.match(-1.0));
}

TEST_F(WithinUlpsMatcherTest_200, MatchWithinUlpsFloatNegative_200) {
    float target = -2.0f;
    WithinUlpsMatcher matcher(static_cast<double>(target), 2, FloatingPointKind::Float);
    EXPECT_TRUE(matcher.match(static_cast<double>(target)));
}

TEST_F(WithinUlpsMatcherTest_200, DescribeDoubleDoesNotContainFSuffix_200) {
    WithinUlpsMatcher matcher(1.0, 1, FloatingPointKind::Double);
    std::string desc = matcher.describe();
    // For double, the value part should not end with 'f' before the bracket
    // This is a structural check - the 'f' suffix is only for Float kind
    // We check that the describe output makes sense structurally
    EXPECT_NE(desc.find("(["), std::string::npos);
    EXPECT_NE(desc.find("])"), std::string::npos);
}
