#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Include Catch2 matchers headers
#include "catch2/matchers/catch_matchers_floating_point.hpp"
#include "catch2/matchers/catch_matchers.hpp"

class FloatingPointMatchersTest_206 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== WithinRel (double) Tests ====================

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleExactMatch_206) {
    auto matcher = Catch::Matchers::WithinRel(1.0, 0.01);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleWithinEpsilon_206) {
    auto matcher = Catch::Matchers::WithinRel(1.0, 0.01);
    EXPECT_TRUE(matcher.match(1.005));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleOutsideEpsilon_206) {
    auto matcher = Catch::Matchers::WithinRel(1.0, 0.01);
    EXPECT_FALSE(matcher.match(1.02));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleNegativeValues_206) {
    auto matcher = Catch::Matchers::WithinRel(-1.0, 0.01);
    EXPECT_TRUE(matcher.match(-1.0));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleNegativeValuesWithinEpsilon_206) {
    auto matcher = Catch::Matchers::WithinRel(-1.0, 0.01);
    EXPECT_TRUE(matcher.match(-1.005));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleNegativeValuesOutsideEpsilon_206) {
    auto matcher = Catch::Matchers::WithinRel(-1.0, 0.01);
    EXPECT_FALSE(matcher.match(-1.02));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleZeroTarget_206) {
    auto matcher = Catch::Matchers::WithinRel(0.0, 0.01);
    EXPECT_TRUE(matcher.match(0.0));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleLargeValues_206) {
    auto matcher = Catch::Matchers::WithinRel(1000000.0, 0.01);
    EXPECT_TRUE(matcher.match(1000000.0));
    EXPECT_TRUE(matcher.match(1005000.0));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleLargeValuesOutside_206) {
    auto matcher = Catch::Matchers::WithinRel(1000000.0, 0.001);
    EXPECT_FALSE(matcher.match(1002000.0));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleVerySmallEpsilon_206) {
    auto matcher = Catch::Matchers::WithinRel(1.0, 1e-10);
    EXPECT_TRUE(matcher.match(1.0));
    EXPECT_FALSE(matcher.match(1.001));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleDefaultEpsilon_206) {
    // WithinRel with default epsilon (should use machine epsilon)
    auto matcher = Catch::Matchers::WithinRel(1.0);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleDefaultEpsilonRejectsDistant_206) {
    auto matcher = Catch::Matchers::WithinRel(1.0);
    EXPECT_FALSE(matcher.match(2.0));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleBothZero_206) {
    auto matcher = Catch::Matchers::WithinRel(0.0, 0.01);
    EXPECT_TRUE(matcher.match(0.0));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleSymmetry_206) {
    // If a is within rel of b, b should be within rel of a (approximately)
    auto matcher1 = Catch::Matchers::WithinRel(100.0, 0.1);
    auto matcher2 = Catch::Matchers::WithinRel(105.0, 0.1);
    EXPECT_TRUE(matcher1.match(105.0));
    EXPECT_TRUE(matcher2.match(100.0));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleEpsilonBoundary_206) {
    // Testing at the boundary of epsilon
    double target = 100.0;
    double eps = 0.01;
    auto matcher = Catch::Matchers::WithinRel(target, eps);
    // Value at exactly 1% should be within
    EXPECT_TRUE(matcher.match(101.0));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleJustOutsideBoundary_206) {
    double target = 100.0;
    double eps = 0.01;
    auto matcher = Catch::Matchers::WithinRel(target, eps);
    // Value clearly beyond 1% should not match
    EXPECT_FALSE(matcher.match(102.0));
}

// ==================== WithinRel (float) Tests ====================

TEST_F(FloatingPointMatchersTest_206, WithinRelFloatExactMatch_206) {
    auto matcher = Catch::Matchers::WithinRel(1.0f, 0.01f);
    EXPECT_TRUE(matcher.match(1.0f));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelFloatWithinEpsilon_206) {
    auto matcher = Catch::Matchers::WithinRel(1.0f, 0.01f);
    EXPECT_TRUE(matcher.match(1.005f));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelFloatOutsideEpsilon_206) {
    auto matcher = Catch::Matchers::WithinRel(1.0f, 0.01f);
    EXPECT_FALSE(matcher.match(1.02f));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelFloatDefaultEpsilon_206) {
    auto matcher = Catch::Matchers::WithinRel(1.0f);
    EXPECT_TRUE(matcher.match(1.0f));
}

// ==================== WithinAbs Tests ====================

TEST_F(FloatingPointMatchersTest_206, WithinAbsDoubleExactMatch_206) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.01);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST_F(FloatingPointMatchersTest_206, WithinAbsDoubleWithinMargin_206) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.1);
    EXPECT_TRUE(matcher.match(1.05));
}

TEST_F(FloatingPointMatchersTest_206, WithinAbsDoubleOutsideMargin_206) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.01);
    EXPECT_FALSE(matcher.match(1.02));
}

TEST_F(FloatingPointMatchersTest_206, WithinAbsDoubleNegativeValues_206) {
    auto matcher = Catch::Matchers::WithinAbs(-1.0, 0.1);
    EXPECT_TRUE(matcher.match(-1.05));
}

TEST_F(FloatingPointMatchersTest_206, WithinAbsDoubleZeroMargin_206) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.0);
    EXPECT_TRUE(matcher.match(1.0));
    EXPECT_FALSE(matcher.match(1.0 + std::numeric_limits<double>::epsilon() * 10));
}

TEST_F(FloatingPointMatchersTest_206, WithinAbsDoubleLargeMargin_206) {
    auto matcher = Catch::Matchers::WithinAbs(0.0, 100.0);
    EXPECT_TRUE(matcher.match(50.0));
    EXPECT_TRUE(matcher.match(-50.0));
    EXPECT_FALSE(matcher.match(200.0));
}

TEST_F(FloatingPointMatchersTest_206, WithinAbsDoubleBoundaryExact_206) {
    auto matcher = Catch::Matchers::WithinAbs(10.0, 1.0);
    EXPECT_TRUE(matcher.match(11.0));
    EXPECT_TRUE(matcher.match(9.0));
}

// ==================== WithinULP Tests ====================

TEST_F(FloatingPointMatchersTest_206, WithinULPDoubleExactMatch_206) {
    auto matcher = Catch::Matchers::WithinULP(1.0, 1);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST_F(FloatingPointMatchersTest_206, WithinULPDoubleOneULP_206) {
    double val = 1.0;
    double next = std::nextafter(val, std::numeric_limits<double>::max());
    auto matcher = Catch::Matchers::WithinULP(val, 1);
    EXPECT_TRUE(matcher.match(next));
}

TEST_F(FloatingPointMatchersTest_206, WithinULPDoubleFarApart_206) {
    auto matcher = Catch::Matchers::WithinULP(1.0, 1);
    EXPECT_FALSE(matcher.match(2.0));
}

TEST_F(FloatingPointMatchersTest_206, WithinULPFloatExactMatch_206) {
    auto matcher = Catch::Matchers::WithinULP(1.0f, 1);
    EXPECT_TRUE(matcher.match(1.0f));
}

TEST_F(FloatingPointMatchersTest_206, WithinULPFloatOneULP_206) {
    float val = 1.0f;
    float next = std::nextafter(val, std::numeric_limits<float>::max());
    auto matcher = Catch::Matchers::WithinULP(val, 1);
    EXPECT_TRUE(matcher.match(next));
}

TEST_F(FloatingPointMatchersTest_206, WithinULPFloatFarApart_206) {
    auto matcher = Catch::Matchers::WithinULP(1.0f, 1);
    EXPECT_FALSE(matcher.match(2.0f));
}

TEST_F(FloatingPointMatchersTest_206, WithinULPDoubleMultipleULPs_206) {
    double val = 1.0;
    double next1 = std::nextafter(val, std::numeric_limits<double>::max());
    double next2 = std::nextafter(next1, std::numeric_limits<double>::max());
    double next3 = std::nextafter(next2, std::numeric_limits<double>::max());
    
    auto matcher = Catch::Matchers::WithinULP(val, 2);
    EXPECT_TRUE(matcher.match(next1));
    EXPECT_TRUE(matcher.match(next2));
    EXPECT_FALSE(matcher.match(next3));
}

// ==================== Description Tests ====================

TEST_F(FloatingPointMatchersTest_206, WithinRelDescribeNotEmpty_206) {
    auto matcher = Catch::Matchers::WithinRel(1.0, 0.01);
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}

TEST_F(FloatingPointMatchersTest_206, WithinAbsDescribeNotEmpty_206) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.01);
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}

TEST_F(FloatingPointMatchersTest_206, WithinULPDoubleDescribeNotEmpty_206) {
    auto matcher = Catch::Matchers::WithinULP(1.0, 1);
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}

TEST_F(FloatingPointMatchersTest_206, WithinULPFloatDescribeNotEmpty_206) {
    auto matcher = Catch::Matchers::WithinULP(1.0f, 1);
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}

TEST_F(FloatingPointMatchersTest_206, WithinRelFloatDescribeNotEmpty_206) {
    auto matcher = Catch::Matchers::WithinRel(1.0f, 0.01f);
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}

// ==================== Special Values Tests ====================

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleInfinityTarget_206) {
    auto matcher = Catch::Matchers::WithinRel(std::numeric_limits<double>::infinity(), 0.01);
    EXPECT_TRUE(matcher.match(std::numeric_limits<double>::infinity()));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleNaNDoesNotMatch_206) {
    auto matcher = Catch::Matchers::WithinRel(1.0, 0.01);
    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::quiet_NaN()));
}

TEST_F(FloatingPointMatchersTest_206, WithinAbsDoubleNaNDoesNotMatch_206) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 100.0);
    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::quiet_NaN()));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleNegInfinity_206) {
    auto matcher = Catch::Matchers::WithinRel(-std::numeric_limits<double>::infinity(), 0.01);
    EXPECT_TRUE(matcher.match(-std::numeric_limits<double>::infinity()));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleMismatchedInfinity_206) {
    auto matcher = Catch::Matchers::WithinRel(std::numeric_limits<double>::infinity(), 0.01);
    EXPECT_FALSE(matcher.match(-std::numeric_limits<double>::infinity()));
}

TEST_F(FloatingPointMatchersTest_206, WithinAbsDoubleZeroTarget_206) {
    auto matcher = Catch::Matchers::WithinAbs(0.0, 0.001);
    EXPECT_TRUE(matcher.match(0.0005));
    EXPECT_TRUE(matcher.match(-0.0005));
    EXPECT_FALSE(matcher.match(0.002));
}

// ==================== Combined / Edge Case Tests ====================

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleVerySmallValues_206) {
    double target = 1e-300;
    auto matcher = Catch::Matchers::WithinRel(target, 0.01);
    EXPECT_TRUE(matcher.match(target));
    EXPECT_TRUE(matcher.match(target * 1.005));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleVeryLargeValues_206) {
    double target = 1e300;
    auto matcher = Catch::Matchers::WithinRel(target, 0.01);
    EXPECT_TRUE(matcher.match(target));
    EXPECT_TRUE(matcher.match(target * 1.005));
}

TEST_F(FloatingPointMatchersTest_206, WithinRelDoubleEpsilonOne_206) {
    // eps = 1.0 means 100% relative tolerance
    auto matcher = Catch::Matchers::WithinRel(1.0, 1.0);
    EXPECT_TRUE(matcher.match(1.0));
    EXPECT_TRUE(matcher.match(0.0));
    EXPECT_TRUE(matcher.match(2.0));
}

TEST_F(FloatingPointMatchersTest_206, WithinULPDoubleZeroULPs_206) {
    auto matcher = Catch::Matchers::WithinULP(1.0, 0);
    EXPECT_TRUE(matcher.match(1.0));
    double next = std::nextafter(1.0, std::numeric_limits<double>::max());
    EXPECT_FALSE(matcher.match(next));
}
