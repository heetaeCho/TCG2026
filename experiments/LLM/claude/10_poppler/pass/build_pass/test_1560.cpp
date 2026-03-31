#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Include the header under test
#include "splash/SplashMath.h"

class SplashMathAvgTest_1560 : public ::testing::Test {
protected:
};

// Normal operation tests

TEST_F(SplashMathAvgTest_1560, AvgOfTwoPositiveNumbers_1560) {
    SplashCoord result = splashAvg(2.0, 4.0);
    EXPECT_DOUBLE_EQ(result, 3.0);
}

TEST_F(SplashMathAvgTest_1560, AvgOfTwoNegativeNumbers_1560) {
    SplashCoord result = splashAvg(-2.0, -4.0);
    EXPECT_DOUBLE_EQ(result, -3.0);
}

TEST_F(SplashMathAvgTest_1560, AvgOfPositiveAndNegative_1560) {
    SplashCoord result = splashAvg(-3.0, 5.0);
    EXPECT_DOUBLE_EQ(result, 1.0);
}

TEST_F(SplashMathAvgTest_1560, AvgOfEqualNumbers_1560) {
    SplashCoord result = splashAvg(7.0, 7.0);
    EXPECT_DOUBLE_EQ(result, 7.0);
}

TEST_F(SplashMathAvgTest_1560, AvgOfZeroAndPositive_1560) {
    SplashCoord result = splashAvg(0.0, 10.0);
    EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST_F(SplashMathAvgTest_1560, AvgOfZeroAndNegative_1560) {
    SplashCoord result = splashAvg(0.0, -10.0);
    EXPECT_DOUBLE_EQ(result, -5.0);
}

TEST_F(SplashMathAvgTest_1560, AvgOfTwoZeros_1560) {
    SplashCoord result = splashAvg(0.0, 0.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(SplashMathAvgTest_1560, AvgIsCommutative_1560) {
    SplashCoord result1 = splashAvg(3.0, 7.0);
    SplashCoord result2 = splashAvg(7.0, 3.0);
    EXPECT_DOUBLE_EQ(result1, result2);
}

TEST_F(SplashMathAvgTest_1560, AvgOfOppositeNumbers_1560) {
    SplashCoord result = splashAvg(-5.0, 5.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Boundary condition tests

TEST_F(SplashMathAvgTest_1560, AvgOfVerySmallNumbers_1560) {
    SplashCoord small = 1e-15;
    SplashCoord result = splashAvg(small, small);
    EXPECT_DOUBLE_EQ(result, small);
}

TEST_F(SplashMathAvgTest_1560, AvgOfLargeNumbers_1560) {
    SplashCoord large1 = 1e100;
    SplashCoord large2 = 3e100;
    SplashCoord result = splashAvg(large1, large2);
    EXPECT_DOUBLE_EQ(result, 2e100);
}

TEST_F(SplashMathAvgTest_1560, AvgWithMaxDouble_1560) {
    SplashCoord maxVal = std::numeric_limits<SplashCoord>::max();
    // avg(maxVal, 0) should be maxVal/2
    SplashCoord result = splashAvg(maxVal, 0.0);
    EXPECT_DOUBLE_EQ(result, maxVal * 0.5);
}

TEST_F(SplashMathAvgTest_1560, AvgWithMinDouble_1560) {
    SplashCoord minVal = std::numeric_limits<SplashCoord>::min();
    SplashCoord result = splashAvg(minVal, minVal);
    EXPECT_DOUBLE_EQ(result, minVal);
}

TEST_F(SplashMathAvgTest_1560, AvgOfFractionalNumbers_1560) {
    SplashCoord result = splashAvg(0.1, 0.3);
    EXPECT_NEAR(result, 0.2, 1e-15);
}

TEST_F(SplashMathAvgTest_1560, AvgOfOneAndTwo_1560) {
    SplashCoord result = splashAvg(1.0, 2.0);
    EXPECT_DOUBLE_EQ(result, 1.5);
}

TEST_F(SplashMathAvgTest_1560, AvgResultIsBetweenInputs_1560) {
    SplashCoord x = 10.0;
    SplashCoord y = 20.0;
    SplashCoord result = splashAvg(x, y);
    EXPECT_GE(result, x);
    EXPECT_LE(result, y);
}

TEST_F(SplashMathAvgTest_1560, AvgResultIsBetweenInputsNegative_1560) {
    SplashCoord x = -20.0;
    SplashCoord y = -10.0;
    SplashCoord result = splashAvg(x, y);
    EXPECT_GE(result, x);
    EXPECT_LE(result, y);
}

// Special floating-point cases

TEST_F(SplashMathAvgTest_1560, AvgOfInfinityAndFinite_1560) {
    SplashCoord inf = std::numeric_limits<SplashCoord>::infinity();
    SplashCoord result = splashAvg(inf, 0.0);
    EXPECT_TRUE(std::isinf(result));
    EXPECT_GT(result, 0.0);
}

TEST_F(SplashMathAvgTest_1560, AvgOfPositiveAndNegativeInfinity_1560) {
    SplashCoord posInf = std::numeric_limits<SplashCoord>::infinity();
    SplashCoord negInf = -std::numeric_limits<SplashCoord>::infinity();
    SplashCoord result = splashAvg(posInf, negInf);
    EXPECT_TRUE(std::isnan(result));
}

TEST_F(SplashMathAvgTest_1560, AvgWithNaN_1560) {
    SplashCoord nan = std::numeric_limits<SplashCoord>::quiet_NaN();
    SplashCoord result = splashAvg(nan, 5.0);
    EXPECT_TRUE(std::isnan(result));
}

TEST_F(SplashMathAvgTest_1560, AvgOfIntegerValues_1560) {
    SplashCoord result = splashAvg(100.0, 200.0);
    EXPECT_DOUBLE_EQ(result, 150.0);
}

TEST_F(SplashMathAvgTest_1560, AvgOfNegativeAndZero_1560) {
    SplashCoord result = splashAvg(-8.0, 0.0);
    EXPECT_DOUBLE_EQ(result, -4.0);
}
