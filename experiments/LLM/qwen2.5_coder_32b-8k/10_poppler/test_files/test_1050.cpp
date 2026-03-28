#include <gtest/gtest.h>

#include "SplashPattern.h"



class SplashSolidColorTest : public ::testing::Test {

protected:

    SplashSolidColor solidColor;

};



TEST_F(SplashSolidColorTest_1050, TestPosition_ReturnsFalseForAnyCoordinates_1050) {

    EXPECT_FALSE(solidColor.testPosition(0, 0));

    EXPECT_FALSE(solidColor.testPosition(-1, -1));

    EXPECT_FALSE(solidColor.testPosition(100, 200));

}



TEST_F(SplashSolidColorTest_1050, TestPosition_BoundaryConditions_ReturnsFalse_1050) {

    EXPECT_FALSE(solidColor.testPosition(INT_MIN, INT_MIN));

    EXPECT_FALSE(solidColor.testPosition(INT_MAX, INT_MAX));

}
