#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_all.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include <limits>

class WithinRelMatcherTest_207 : public ::testing::Test {
protected:
};

// Test that a value exactly equal to the target matches
TEST_F(WithinRelMatcherTest_207, ExactMatch_207) {
    auto matcher = Catch::Matchers::WithinRel(1.0);
    EXPECT_TRUE(matcher.match(1.0));
}

// Test that zero matches itself
TEST_F(WithinRelMatcherTest_207, ZeroMatchesZero_207) {
    auto matcher = Catch::Matchers::WithinRel(0.0);
    EXPECT_TRUE(matcher.match(0.0));
}

// Test that a value very close to target matches with default tolerance
TEST_F(WithinRelMatcherTest_207, CloseValueMatches_207) {
    double target = 1.0;
    double eps100 = std::numeric_limits<double>::epsilon() * 100;
    double closeValue = target * (1.0 + eps100 * 0.5);
    auto matcher = Catch::Matchers::WithinRel(target);
    EXPECT_TRUE(matcher.match(closeValue));
}

// Test that a value far from target does not match
TEST_F(WithinRelMatcherTest_207, FarValueDoesNotMatch_207) {
    auto matcher = Catch::Matchers::WithinRel(1.0);
    EXPECT_FALSE(matcher.match(2.0));
}

// Test with negative target, exact match
TEST_F(WithinRelMatcherTest_207, NegativeTargetExactMatch_207) {
    auto matcher = Catch::Matchers::WithinRel(-5.0);
    EXPECT_TRUE(matcher.match(-5.0));
}

// Test with negative target, far value
TEST_F(WithinRelMatcherTest_207, NegativeTargetFarValue_207) {
    auto matcher = Catch::Matchers::WithinRel(-5.0);
    EXPECT_FALSE(matcher.match(5.0));
}

// Test with large values
TEST_F(WithinRelMatcherTest_207, LargeValuesExactMatch_207) {
    double large = 1e15;
    auto matcher = Catch::Matchers::WithinRel(large);
    EXPECT_TRUE(matcher.match(large));
}

// Test with large values, slightly off
TEST_F(WithinRelMatcherTest_207, LargeValuesSlightlyOff_207) {
    double large = 1e15;
    auto matcher = Catch::Matchers::WithinRel(large);
    EXPECT_FALSE(matcher.match(large * 1.1));
}

// Test with very small values
TEST_F(WithinRelMatcherTest_207, SmallValuesExactMatch_207) {
    double small = 1e-15;
    auto matcher = Catch::Matchers::WithinRel(small);
    EXPECT_TRUE(matcher.match(small));
}

// Test that explicit tolerance overload works
TEST_F(WithinRelMatcherTest_207, ExplicitToleranceMatches_207) {
    auto matcher = Catch::Matchers::WithinRel(100.0, 0.1);
    EXPECT_TRUE(matcher.match(105.0)); // within 10%
}

// Test that explicit tolerance overload rejects far values
TEST_F(WithinRelMatcherTest_207, ExplicitToleranceRejectsFarValue_207) {
    auto matcher = Catch::Matchers::WithinRel(100.0, 0.01);
    EXPECT_FALSE(matcher.match(120.0)); // 20% away, tolerance is 1%
}

// Test describe returns non-empty string
TEST_F(WithinRelMatcherTest_207, DescribeReturnsNonEmpty_207) {
    auto matcher = Catch::Matchers::WithinRel(1.0);
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}

// Test default tolerance: value just beyond tolerance does not match
TEST_F(WithinRelMatcherTest_207, BeyondDefaultToleranceDoesNotMatch_207) {
    double target = 1.0;
    double eps100 = std::numeric_limits<double>::epsilon() * 100;
    double beyondValue = target * (1.0 + eps100 * 10.0);
    auto matcher = Catch::Matchers::WithinRel(target);
    EXPECT_FALSE(matcher.match(beyondValue));
}

// Test with infinity target
TEST_F(WithinRelMatcherTest_207, InfinityTarget_207) {
    auto matcher = Catch::Matchers::WithinRel(std::numeric_limits<double>::infinity());
    EXPECT_TRUE(matcher.match(std::numeric_limits<double>::infinity()));
}

// Test NaN does not match NaN
TEST_F(WithinRelMatcherTest_207, NaNDoesNotMatchNaN_207) {
    auto matcher = Catch::Matchers::WithinRel(std::numeric_limits<double>::quiet_NaN());
    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::quiet_NaN()));
}

// Test NaN does not match a regular number
TEST_F(WithinRelMatcherTest_207, NaNDoesNotMatchRegular_207) {
    auto matcher = Catch::Matchers::WithinRel(1.0);
    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::quiet_NaN()));
}

// Test negative infinity matches itself
TEST_F(WithinRelMatcherTest_207, NegativeInfinityMatchesSelf_207) {
    auto matcher = Catch::Matchers::WithinRel(-std::numeric_limits<double>::infinity());
    EXPECT_TRUE(matcher.match(-std::numeric_limits<double>::infinity()));
}

// Test positive infinity does not match negative infinity
TEST_F(WithinRelMatcherTest_207, PosInfDoesNotMatchNegInf_207) {
    auto matcher = Catch::Matchers::WithinRel(std::numeric_limits<double>::infinity());
    EXPECT_FALSE(matcher.match(-std::numeric_limits<double>::infinity()));
}
