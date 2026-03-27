#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashTypes.h"



class SplashTypesTest_1042 : public ::testing::Test {

protected:

    // No additional setup needed for these tests as they are standalone function tests.

};



TEST_F(SplashTypesTest_1042, NormalOperation_1042) {

    unsigned char cmyk8[4] = {255, 128, 64, 32};

    EXPECT_EQ(splashCMYK8K(cmyk8), 32);

}



TEST_F(SplashTypesTest_1042, BoundaryCondition_MaxValue_1042) {

    unsigned char cmyk8[4] = {255, 255, 255, 255};

    EXPECT_EQ(splashCMYK8K(cmyk8), 255);

}



TEST_F(SplashTypesTest_1042, BoundaryCondition_MinValue_1042) {

    unsigned char cmyk8[4] = {0, 0, 0, 0};

    EXPECT_EQ(splashCMYK8K(cmyk8), 0);

}



TEST_F(SplashTypesTest_1042, BoundaryCondition_ZeroExceptLast_1042) {

    unsigned char cmyk8[4] = {0, 0, 0, 1};

    EXPECT_EQ(splashCMYK8K(cmyk8), 1);

}



TEST_F(SplashTypesTest_1042, BoundaryCondition_MaxExceptLast_1042) {

    unsigned char cmyk8[4] = {255, 255, 255, 0};

    EXPECT_EQ(splashCMYK8K(cmyk8), 0);

}
