#include <gtest/gtest.h>
#include "splash/SplashMath.h"

class SplashCeilTest_1558 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test ceiling of positive integer - should return the same integer
TEST_F(SplashCeilTest_1558, PositiveInteger_1558) {
    EXPECT_EQ(5, splashCeil((SplashCoord)5.0));
}

// Test ceiling of negative integer - should return the same integer
TEST_F(SplashCeilTest_1558, NegativeInteger_1558) {
    EXPECT_EQ(-5, splashCeil((SplashCoord)-5.0));
}

// Test ceiling of zero
TEST_F(SplashCeilTest_1558, Zero_1558) {
    EXPECT_EQ(0, splashCeil((SplashCoord)0.0));
}

// Test ceiling of positive fractional value - should round up
TEST_F(SplashCeilTest_1558, PositiveFraction_1558) {
    EXPECT_EQ(4, splashCeil((SplashCoord)3.2));
}

// Test ceiling of positive value just above integer
TEST_F(SplashCeilTest_1558, PositiveJustAboveInteger_1558) {
    EXPECT_EQ(4, splashCeil((SplashCoord)3.0001));
}

// Test ceiling of positive value just below integer
TEST_F(SplashCeilTest_1558, PositiveJustBelowInteger_1558) {
    EXPECT_EQ(4, splashCeil((SplashCoord)3.9999));
}

// Test ceiling of negative fractional value - should round toward zero
TEST_F(SplashCeilTest_1558, NegativeFraction_1558) {
    EXPECT_EQ(-3, splashCeil((SplashCoord)-3.2));
}

// Test ceiling of negative value just below integer
TEST_F(SplashCeilTest_1558, NegativeJustBelowInteger_1558) {
    EXPECT_EQ(-3, splashCeil((SplashCoord)-3.9999));
}

// Test ceiling of negative value just above integer
TEST_F(SplashCeilTest_1558, NegativeJustAboveInteger_1558) {
    EXPECT_EQ(-3, splashCeil((SplashCoord)-3.0001));
}

// Test ceiling of 0.5
TEST_F(SplashCeilTest_1558, PositiveHalf_1558) {
    EXPECT_EQ(1, splashCeil((SplashCoord)0.5));
}

// Test ceiling of -0.5
TEST_F(SplashCeilTest_1558, NegativeHalf_1558) {
    EXPECT_EQ(0, splashCeil((SplashCoord)-0.5));
}

// Test ceiling of 1.0
TEST_F(SplashCeilTest_1558, One_1558) {
    EXPECT_EQ(1, splashCeil((SplashCoord)1.0));
}

// Test ceiling of -1.0
TEST_F(SplashCeilTest_1558, NegativeOne_1558) {
    EXPECT_EQ(-1, splashCeil((SplashCoord)-1.0));
}

// Test ceiling of very small positive value
TEST_F(SplashCeilTest_1558, VerySmallPositive_1558) {
    EXPECT_EQ(1, splashCeil((SplashCoord)0.0001));
}

// Test ceiling of very small negative value
TEST_F(SplashCeilTest_1558, VerySmallNegative_1558) {
    EXPECT_EQ(0, splashCeil((SplashCoord)-0.0001));
}

// Test ceiling of large positive fractional value
TEST_F(SplashCeilTest_1558, LargePositiveFraction_1558) {
    EXPECT_EQ(1001, splashCeil((SplashCoord)1000.1));
}

// Test ceiling of large negative fractional value
TEST_F(SplashCeilTest_1558, LargeNegativeFraction_1558) {
    EXPECT_EQ(-1000, splashCeil((SplashCoord)-1000.1));
}

// Test ceiling of positive value with 0.99 fraction
TEST_F(SplashCeilTest_1558, PositiveNearNextInteger_1558) {
    EXPECT_EQ(3, splashCeil((SplashCoord)2.99));
}

// Test ceiling of negative value with 0.01 fraction
TEST_F(SplashCeilTest_1558, NegativeNearInteger_1558) {
    EXPECT_EQ(-2, splashCeil((SplashCoord)-2.01));
}

// Test ceiling of exact positive integer value (e.g., 10.0)
TEST_F(SplashCeilTest_1558, ExactPositiveLargeInteger_1558) {
    EXPECT_EQ(100, splashCeil((SplashCoord)100.0));
}

// Test ceiling of exact negative integer value (e.g., -10.0)
TEST_F(SplashCeilTest_1558, ExactNegativeLargeInteger_1558) {
    EXPECT_EQ(-100, splashCeil((SplashCoord)-100.0));
}

// Test ceiling with value 0.999...
TEST_F(SplashCeilTest_1558, AlmostOne_1558) {
    EXPECT_EQ(1, splashCeil((SplashCoord)0.999));
}

// Test negative zero
TEST_F(SplashCeilTest_1558, NegativeZero_1558) {
    EXPECT_EQ(0, splashCeil((SplashCoord)-0.0));
}
