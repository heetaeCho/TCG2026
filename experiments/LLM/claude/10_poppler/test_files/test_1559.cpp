#include <gtest/gtest.h>
#include "splash/SplashMath.h"

class SplashRoundTest_1559 : public ::testing::Test {
protected:
};

// Test rounding of positive integers (should return the same integer)
TEST_F(SplashRoundTest_1559, PositiveInteger_1559) {
    EXPECT_EQ(5, splashRound(5.0));
    EXPECT_EQ(10, splashRound(10.0));
    EXPECT_EQ(1, splashRound(1.0));
    EXPECT_EQ(100, splashRound(100.0));
}

// Test rounding of negative integers (should return the same integer)
TEST_F(SplashRoundTest_1559, NegativeInteger_1559) {
    EXPECT_EQ(-5, splashRound(-5.0));
    EXPECT_EQ(-10, splashRound(-10.0));
    EXPECT_EQ(-1, splashRound(-1.0));
}

// Test rounding of zero
TEST_F(SplashRoundTest_1559, Zero_1559) {
    EXPECT_EQ(0, splashRound(0.0));
}

// Test rounding of positive values with fractional part < 0.5 (round down)
TEST_F(SplashRoundTest_1559, PositiveFractionBelowHalf_1559) {
    EXPECT_EQ(3, splashRound(3.2));
    EXPECT_EQ(3, splashRound(3.4));
    EXPECT_EQ(3, splashRound(3.1));
    EXPECT_EQ(0, splashRound(0.3));
}

// Test rounding of positive values with fractional part > 0.5 (round up)
TEST_F(SplashRoundTest_1559, PositiveFractionAboveHalf_1559) {
    EXPECT_EQ(4, splashRound(3.6));
    EXPECT_EQ(4, splashRound(3.7));
    EXPECT_EQ(4, splashRound(3.9));
    EXPECT_EQ(1, splashRound(0.8));
}

// Test rounding of positive values at exactly 0.5 (round up per standard rounding)
TEST_F(SplashRoundTest_1559, PositiveExactlyHalf_1559) {
    EXPECT_EQ(1, splashRound(0.5));
    EXPECT_EQ(4, splashRound(3.5));
    EXPECT_EQ(6, splashRound(5.5));
}

// Test rounding of negative values with fractional part < 0.5 in magnitude
TEST_F(SplashRoundTest_1559, NegativeFractionBelowHalf_1559) {
    EXPECT_EQ(-3, splashRound(-3.2));
    EXPECT_EQ(-3, splashRound(-3.4));
    EXPECT_EQ(0, splashRound(-0.3));
}

// Test rounding of negative values with fractional part > 0.5 in magnitude
TEST_F(SplashRoundTest_1559, NegativeFractionAboveHalf_1559) {
    EXPECT_EQ(-4, splashRound(-3.6));
    EXPECT_EQ(-4, splashRound(-3.7));
    EXPECT_EQ(-4, splashRound(-3.9));
    EXPECT_EQ(-1, splashRound(-0.8));
}

// Test rounding of negative values at exactly -0.5
// splashRound(-0.5) = splashFloor(-0.5 + 0.5) = splashFloor(0.0) = 0
TEST_F(SplashRoundTest_1559, NegativeExactlyHalf_1559) {
    EXPECT_EQ(0, splashRound(-0.5));
    // splashRound(-3.5) = splashFloor(-3.5 + 0.5) = splashFloor(-3.0) = -3
    EXPECT_EQ(-3, splashRound(-3.5));
}

// Test rounding of very small positive values
TEST_F(SplashRoundTest_1559, VerySmallPositive_1559) {
    EXPECT_EQ(0, splashRound(0.001));
    EXPECT_EQ(0, splashRound(0.0001));
    EXPECT_EQ(0, splashRound(0.499));
}

// Test rounding of very small negative values
TEST_F(SplashRoundTest_1559, VerySmallNegative_1559) {
    EXPECT_EQ(0, splashRound(-0.001));
    EXPECT_EQ(0, splashRound(-0.0001));
    EXPECT_EQ(0, splashRound(-0.499));
}

// Test rounding of values just above and below an integer
TEST_F(SplashRoundTest_1559, NearIntegerBoundary_1559) {
    EXPECT_EQ(5, splashRound(4.999999));
    EXPECT_EQ(5, splashRound(5.000001));
    EXPECT_EQ(-5, splashRound(-4.999999));
    EXPECT_EQ(-5, splashRound(-5.000001));
}

// Test rounding of large positive values
TEST_F(SplashRoundTest_1559, LargePositive_1559) {
    EXPECT_EQ(1000000, splashRound(1000000.0));
    EXPECT_EQ(1000001, splashRound(1000000.6));
    EXPECT_EQ(1000000, splashRound(1000000.4));
}

// Test rounding of large negative values
TEST_F(SplashRoundTest_1559, LargeNegative_1559) {
    EXPECT_EQ(-1000000, splashRound(-1000000.0));
    EXPECT_EQ(-1000001, splashRound(-1000000.6));
    EXPECT_EQ(-1000000, splashRound(-1000000.4));
}

// Test value just barely above 0.5
TEST_F(SplashRoundTest_1559, JustAboveHalf_1559) {
    EXPECT_EQ(1, splashRound(0.500001));
    EXPECT_EQ(4, splashRound(3.500001));
}

// Test value just barely below 0.5
TEST_F(SplashRoundTest_1559, JustBelowHalf_1559) {
    EXPECT_EQ(0, splashRound(0.499999));
    EXPECT_EQ(3, splashRound(3.499999));
}

// Test negative zero
TEST_F(SplashRoundTest_1559, NegativeZero_1559) {
    EXPECT_EQ(0, splashRound(-0.0));
}

// Test with value 1.5 (half rounding for positive)
TEST_F(SplashRoundTest_1559, OnePointFive_1559) {
    EXPECT_EQ(2, splashRound(1.5));
}

// Test with value -1.5
// splashRound(-1.5) = splashFloor(-1.5 + 0.5) = splashFloor(-1.0) = -1
TEST_F(SplashRoundTest_1559, NegativeOnePointFive_1559) {
    EXPECT_EQ(-1, splashRound(-1.5));
}

// Test with value 2.5
TEST_F(SplashRoundTest_1559, TwoPointFive_1559) {
    EXPECT_EQ(3, splashRound(2.5));
}

// Test with value -2.5
// splashRound(-2.5) = splashFloor(-2.5 + 0.5) = splashFloor(-2.0) = -2
TEST_F(SplashRoundTest_1559, NegativeTwoPointFive_1559) {
    EXPECT_EQ(-2, splashRound(-2.5));
}
