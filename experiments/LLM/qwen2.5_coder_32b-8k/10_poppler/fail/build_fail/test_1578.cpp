#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/splash/SplashTypes.h"



extern int splashColorModeNComps[];



TEST(splashOutBlendScreenTest_1578, NormalOperation_RGB8_1578) {

    SplashColor src = {255, 0, 0};

    SplashColor dest = {0, 255, 0};

    SplashColor blend;

    

    splashOutBlendScreen(&src[0], &dest[0], &blend[0], splashModeRGB8);

    

    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 0);

}



TEST(splashOutBlendScreenTest_1578, NormalOperation_CMYK8_1578) {

    SplashColor src = {255, 0, 0, 0};

    SplashColor dest = {0, 255, 0, 0};

    SplashColor blend;

    

    splashOutBlendScreen(&src[0], &dest[0], &blend[0], splashModeCMYK8);

    

    EXPECT_EQ(blend[0], 0);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 255);

    EXPECT_EQ(blend[3], 255);

}



TEST(splashOutBlendScreenTest_1578, BoundaryCondition_AllZeroes_RGB8_1578) {

    SplashColor src = {0, 0, 0};

    SplashColor dest = {0, 0, 0};

    SplashColor blend;

    

    splashOutBlendScreen(&src[0], &dest[0], &blend[0], splashModeRGB8);

    

    EXPECT_EQ(blend[0], 0);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 0);

}



TEST(splashOutBlendScreenTest_1578, BoundaryCondition_AllOnes_RGB8_1578) {

    SplashColor src = {255, 255, 255};

    SplashColor dest = {255, 255, 255};

    SplashColor blend;

    

    splashOutBlendScreen(&src[0], &dest[0], &blend[0], splashModeRGB8);

    

    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255);

}



TEST(splashOutBlendScreenTest_1578, BoundaryCondition_AllZeroes_CMYK8_1578) {

    SplashColor src = {0, 0, 0, 0};

    SplashColor dest = {0, 0, 0, 0};

    SplashColor blend;

    

    splashOutBlendScreen(&src[0], &dest[0], &blend[0], splashModeCMYK8);

    

    EXPECT_EQ(blend[0], 0);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 0);

    EXPECT_EQ(blend[3], 0);

}



TEST(splashOutBlendScreenTest_1578, BoundaryCondition_AllOnes_CMYK8_1578) {

    SplashColor src = {255, 255, 255, 255};

    SplashColor dest = {255, 255, 255, 255};

    SplashColor blend;

    

    splashOutBlendScreen(&src[0], &dest[0], &blend[0], splashModeCMYK8);

    

    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255);

    EXPECT_EQ(blend[3], 255);

}
