#include <gtest/gtest.h>

#include "SplashMath.h"



class SplashMathTest_1564 : public ::testing::Test {

protected:

    static constexpr double epsilon = 1e-5;

};



TEST_F(SplashMathTest_1564, NormalOperation_DetGreaterEqualEpsilon_1564) {

    EXPECT_TRUE(splashCheckDet(2.0, 1.0, 1.0, 2.0, epsilon));

}



TEST_F(SplashMathTest_1564, NormalOperation_DetLessThanEpsilon_1564) {

    EXPECT_FALSE(splashCheckDet(1.0, 1.0, 1.0, 1.0, epsilon));

}



TEST_F(SplashMathTest_1564, BoundaryCondition_ZeroEpsilon_1564) {

    EXPECT_TRUE(splashCheckDet(1.0, 0.0, 0.0, 1.0, 0.0));

}



TEST_F(SplashMathTest_1564, BoundaryCondition_NegativeEpsilon_1564) {

    EXPECT_TRUE(splashCheckDet(1.0, 0.0, 0.0, 1.0, -epsilon));

}



TEST_F(SplashMathTest_1564, BoundaryCondition_LargeValues_1564) {

    EXPECT_TRUE(splashCheckDet(1e10, 1e9, 1e9, 1e10, epsilon));

}



TEST_F(SplashMathTest_1564, BoundaryCondition_SmallValues_1564) {

    EXPECT_FALSE(splashCheckDet(1e-10, 1e-11, 1e-11, 1e-10, epsilon));

}
