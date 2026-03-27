#include <gtest/gtest.h>

#include "splash/SplashMath.h"



class SplashMathTest_1561 : public ::testing::Test {

protected:

    // You can add any setup or teardown code here if needed.

};



TEST_F(SplashMathTest_1561, SqrtOfZero_1561) {

    EXPECT_EQ(splashSqrt(0), 0);

}



TEST_F(SplashMathTest_1561, SqrtOfOne_1561) {

    EXPECT_EQ(splashSqrt(1), 1);

}



TEST_F(SplashMathTest_1561, SqrtOfFour_1561) {

    EXPECT_EQ(splashSqrt(4), 2);

}



TEST_F(SplashMathTest_1561, SqrtOfNine_1561) {

    EXPECT_FLOAT_EQ(splashSqrt(9), 3.0);

}



TEST_F(SplashMathTest_1561, SqrtOfNonPerfectSquare_1561) {

    EXPECT_FLOAT_EQ(splashSqrt(2), sqrt(2));

}



TEST_F(SplashMathTest_1561, SqrtOfLargeNumber_1561) {

    SplashCoord largeNumber = 1000000;

    EXPECT_FLOAT_EQ(splashSqrt(largeNumber), sqrt(largeNumber));

}



TEST_F(SplashMathTest_1561, SqrtOfNegativeNumber_1561) {

    // Assuming splashSqrt is expected to handle negative numbers gracefully.

    // If the implementation returns NaN or throws an exception, this test should reflect that behavior.

    EXPECT_TRUE(isnan(splashSqrt(-1)));

}



TEST_F(SplashMathTest_1561, SqrtOfBoundaryCondition_1561) {

    SplashCoord boundary = std::numeric_limits<SplashCoord>::max();

    EXPECT_FLOAT_EQ(splashSqrt(boundary), sqrt(boundary));

}
