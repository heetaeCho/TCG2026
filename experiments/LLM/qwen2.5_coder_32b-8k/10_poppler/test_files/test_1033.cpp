#include <gtest/gtest.h>



// Assuming SplashColorPtr is defined as an unsigned char pointer

typedef unsigned char* SplashColorPtr;



unsigned char splashRGB8R(SplashColorPtr rgb8) { return rgb8[0]; }



TEST(splashRGB8RTest_1033, NormalOperation_1033) {

    unsigned char color[] = {255, 128, 64};

    EXPECT_EQ(255, splashRGB8R(color));

}



TEST(splashRGB8RTest_1033, BoundaryCondition_Zero_1033) {

    unsigned char color[] = {0, 128, 64};

    EXPECT_EQ(0, splashRGB8R(color));

}



TEST(splashRGB8RTest_1033, BoundaryCondition_MaxValue_1033) {

    unsigned char color[] = {255, 128, 64};

    EXPECT_EQ(255, splashRGB8R(color));

}



TEST(splashRGB8RTest_1033, SingleElementArray_1033) {

    unsigned char color[] = {255};

    EXPECT_EQ(255, splashRGB8R(color));

}
