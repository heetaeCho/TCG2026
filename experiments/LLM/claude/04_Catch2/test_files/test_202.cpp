#include <gtest/gtest.h>
#include <string>
#include <cmath>
#include <limits>

// Include the necessary headers
#include "catch2/matchers/catch_matchers_floating_point.hpp"

using namespace Catch::Matchers;

// ============================================================
// Tests for WithinRelMatcher::describe()
// ============================================================

TEST(WithinRelMatcherDescribeTest_202, DescribeContainsTargetValue_202) {
    WithinRelMatcher matcher(1.0, 0.01);
    std::string description = matcher.describe();
    // Should contain the target value
    EXPECT_NE(description.find("1.0"), std::string::npos);
}

TEST(WithinRelMatcherDescribeTest_202, DescribeContainsPercentage_202) {
    WithinRelMatcher matcher(1.0, 0.01);
    std::string description = matcher.describe();
    // epsilon * 100 = 1%, so description should contain "1"
    EXPECT_NE(description.find("1"), std::string::npos);
    EXPECT_NE(description.find("%"), std::string::npos);
}

TEST(WithinRelMatcherDescribeTest_202, DescribeContainsWithinText_202) {
    WithinRelMatcher matcher(5.0, 0.1);
    std::string description = matcher.describe();
    EXPECT_NE(description.find("within"), std::string::npos);
}

TEST(WithinRelMatcherDescribeTest_202, DescribeWithZeroEpsilon_202) {
    WithinRelMatcher matcher(3.14, 0.0);
    std::string description = matcher.describe();
    // 0.0 * 100 = 0%
    EXPECT_NE(description.find("0"), std::string::npos);
    EXPECT_NE(description.find("%"), std::string::npos);
}

TEST(WithinRelMatcherDescribeTest_202, DescribeWithLargeEpsilon_202) {
    WithinRelMatcher matcher(42.0, 1.0);
    std::string description = matcher.describe();
    // 1.0 * 100 = 100%
    EXPECT_NE(description.find("100"), std::string::npos);
}

TEST(WithinRelMatcherDescribeTest_202, DescribeWithNegativeTarget_202) {
    WithinRelMatcher matcher(-10.5, 0.05);
    std::string description = matcher.describe();
    EXPECT_NE(description.find("-10.5"), std::string::npos);
}

TEST(WithinRelMatcherDescribeTest_202, DescribeContainsAndPrefix_202) {
    WithinRelMatcher matcher(2.0, 0.5);
    std::string description = matcher.describe();
    EXPECT_NE(description.find("and"), std::string::npos);
}

TEST(WithinRelMatcherDescribeTest_202, DescribeContainsOfEachOther_202) {
    WithinRelMatcher matcher(2.0, 0.5);
    std::string description = matcher.describe();
    EXPECT_NE(description.find("of each other"), std::string::npos);
}

// ============================================================
// Tests for WithinRelMatcher::match()
// ============================================================

TEST(WithinRelMatcherMatchTest_202, ExactMatchReturnsTrue_202) {
    WithinRelMatcher matcher(1.0, 0.01);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST(WithinRelMatcherMatchTest_202, WithinToleranceReturnsTrue_202) {
    WithinRelMatcher matcher(100.0, 0.01);
    // 1% of 100 = 1, so 100.5 should be within
    EXPECT_TRUE(matcher.match(100.5));
}

TEST(WithinRelMatcherMatchTest_202, OutsideToleranceReturnsFalse_202) {
    WithinRelMatcher matcher(100.0, 0.01);
    // 1% of 100 = 1, so 102.0 should be outside
    EXPECT_FALSE(matcher.match(102.0));
}

TEST(WithinRelMatcherMatchTest_202, ZeroTargetExactMatch_202) {
    WithinRelMatcher matcher(0.0, 0.01);
    EXPECT_TRUE(matcher.match(0.0));
}

TEST(WithinRelMatcherMatchTest_202, NegativeValuesWithinTolerance_202) {
    WithinRelMatcher matcher(-100.0, 0.01);
    EXPECT_TRUE(matcher.match(-100.5));
}

TEST(WithinRelMatcherMatchTest_202, NegativeValuesOutsideTolerance_202) {
    WithinRelMatcher matcher(-100.0, 0.01);
    EXPECT_FALSE(matcher.match(-102.0));
}

TEST(WithinRelMatcherMatchTest_202, BoundaryValueExactlyAtTolerance_202) {
    WithinRelMatcher matcher(100.0, 0.01);
    // Exactly at 1% boundary: 101.0
    EXPECT_TRUE(matcher.match(101.0));
}

TEST(WithinRelMatcherMatchTest_202, BoundaryValueJustBeyondTolerance_202) {
    WithinRelMatcher matcher(100.0, 0.01);
    // Just beyond 1% boundary
    EXPECT_FALSE(matcher.match(101.1));
}

TEST(WithinRelMatcherMatchTest_202, ZeroEpsilonRequiresExactMatch_202) {
    WithinRelMatcher matcher(1.0, 0.0);
    EXPECT_TRUE(matcher.match(1.0));
    EXPECT_FALSE(matcher.match(1.0 + 1e-10));
}

TEST(WithinRelMatcherMatchTest_202, LargeEpsilonAcceptsWideRange_202) {
    WithinRelMatcher matcher(100.0, 1.0);
    // 100% tolerance: anything from 0 to 200 relative
    EXPECT_TRUE(matcher.match(200.0));
    EXPECT_TRUE(matcher.match(0.0));
}

TEST(WithinRelMatcherMatchTest_202, VerySmallValues_202) {
    WithinRelMatcher matcher(1e-10, 0.01);
    EXPECT_TRUE(matcher.match(1e-10));
}

TEST(WithinRelMatcherMatchTest_202, VeryLargeValues_202) {
    WithinRelMatcher matcher(1e15, 0.01);
    EXPECT_TRUE(matcher.match(1e15));
    EXPECT_TRUE(matcher.match(1e15 + 1e13 * 0.5));
}

// ============================================================
// Tests for WithinRelMatcher construction
// ============================================================

TEST(WithinRelMatcherConstructionTest_202, ConstructWithPositiveValues_202) {
    EXPECT_NO_THROW(WithinRelMatcher(1.0, 0.01));
}

TEST(WithinRelMatcherConstructionTest_202, ConstructWithZeroTarget_202) {
    EXPECT_NO_THROW(WithinRelMatcher(0.0, 0.01));
}

TEST(WithinRelMatcherConstructionTest_202, ConstructWithZeroEpsilon_202) {
    EXPECT_NO_THROW(WithinRelMatcher(1.0, 0.0));
}

TEST(WithinRelMatcherConstructionTest_202, ConstructWithNegativeTarget_202) {
    EXPECT_NO_THROW(WithinRelMatcher(-5.0, 0.1));
}

// ============================================================
// Combined match + describe tests
// ============================================================

TEST(WithinRelMatcherCombinedTest_202, MatchAndDescribeConsistency_202) {
    WithinRelMatcher matcher(50.0, 0.1);
    // Match should succeed for value within 10%
    EXPECT_TRUE(matcher.match(54.0));
    // Describe should mention the target and percentage
    std::string desc = matcher.describe();
    EXPECT_NE(desc.find("50"), std::string::npos);
    EXPECT_NE(desc.find("10"), std::string::npos);
    EXPECT_NE(desc.find("%"), std::string::npos);
}

TEST(WithinRelMatcherMatchTest_202, SymmetricMatch_202) {
    // If a is within x% of b, then b should be within x% of a (approximately)
    WithinRelMatcher matcher1(100.0, 0.05);
    WithinRelMatcher matcher2(104.0, 0.05);
    
    // 104 is within 5% of 100 (5% of 100 = 5, |104-100| = 4 < 5)
    EXPECT_TRUE(matcher1.match(104.0));
    // 100 is within 5% of 104 (5% of 104 = 5.2, |100-104| = 4 < 5.2)
    EXPECT_TRUE(matcher2.match(100.0));
}
