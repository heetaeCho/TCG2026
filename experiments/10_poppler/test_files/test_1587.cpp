#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the function splashOutBlendExclusion is declared in a header file

extern void splashOutBlendExclusion(SplashColorPtr src, SplashColorPtr dest, SplashColorPtr blend, SplashColorMode cm);



TEST(splashOutBlendExclusionTest_1587, NormalOperation_RGB8_1587) {

    SplashColor src = {255, 0, 0}; // Red

    SplashColor dest = {0, 255, 0}; // Green

    SplashColor blend = {0};



    splashOutBlendExclusion(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 0);

}



TEST(splashOutBlendExclusionTest_1587, NormalOperation_CMYK8_1587) {

    SplashColor src = {255, 0, 0, 0}; // Cyan

    SplashColor dest = {0, 255, 0, 0}; // Magenta

    SplashColor blend = {0};



    splashOutBlendExclusion(src, dest, blend, splashModeCMYK8);



    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 0);

    EXPECT_EQ(blend[3], 0);

}



TEST(splashOutBlendExclusionTest_1587, BoundaryCondition_Black_RGB8_1587) {

    SplashColor src = {0, 0, 0}; // Black

    SplashColor dest = {0, 0, 0}; // Black

    SplashColor blend = {0};



    splashOutBlendExclusion(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 0);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 0);

}



TEST(splashOutBlendExclusionTest_1587, BoundaryCondition_White_RGB8_1587) {

    SplashColor src = {255, 255, 255}; // White

    SplashColor dest = {255, 255, 255}; // White

    SplashColor blend = {0};



    splashOutBlendExclusion(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255);

}



TEST(splashOutBlendExclusionTest_1587, DeviceN8_AdditionalComponentZero_1587) {

    SplashColor src = {0, 0, 0, 0, 0}; // Black with additional component

    SplashColor dest = {255, 255, 255, 255, 0}; // White with additional component set to zero

    SplashColor blend = {0};



    splashOutBlendExclusion(src, dest, blend, splashModeDeviceN8);



    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255);

    EXPECT_EQ(blend[3], 255);

    EXPECT_EQ(blend[4], 0); // Additional component should remain zero

}
