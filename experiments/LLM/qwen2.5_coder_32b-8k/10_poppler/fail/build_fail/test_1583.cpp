#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/splash/SplashTypes.h"



// Assuming the function splashOutBlendColorBurn is in a namespace or header file

extern "C" void splashOutBlendColorBurn(SplashColorPtr src, SplashColorPtr dest, SplashColorPtr blend, SplashColorMode cm);



TEST(splashOutBlendColorBurnTest_1583, NormalOperation_RGB8_1583) {

    unsigned char src[] = {255, 0, 0};

    unsigned char dest[] = {0, 255, 0};

    unsigned char blend[3];

    splashOutBlendColorBurn(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 0);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 255);

}



TEST(splashOutBlendColorBurnTest_1583, NormalOperation_CMYK8_1583) {

    unsigned char src[] = {255, 0, 0, 0};

    unsigned char dest[] = {0, 255, 0, 0};

    unsigned char blend[4];

    splashOutBlendColorBurn(src, dest, blend, splashModeCMYK8);

    EXPECT_EQ(blend[0], 0);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 255);

    EXPECT_EQ(blend[3], 0);

}



TEST(splashOutBlendColorBurnTest_1583, BoundaryCondition_ZeroSrc_1583) {

    unsigned char src[] = {0, 0, 0};

    unsigned char dest[] = {255, 255, 255};

    unsigned char blend[3];

    splashOutBlendColorBurn(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 0);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 0);

}



TEST(splashOutBlendColorBurnTest_1583, BoundaryCondition_FullSrcAndDest_1583) {

    unsigned char src[] = {255, 255, 255};

    unsigned char dest[] = {255, 255, 255};

    unsigned char blend[3];

    splashOutBlendColorBurn(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255);

}



TEST(splashOutBlendColorBurnTest_1583, BoundaryCondition_ZeroDest_1583) {

    unsigned char src[] = {255, 255, 255};

    unsigned char dest[] = {0, 0, 0};

    unsigned char blend[3];

    splashOutBlendColorBurn(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255);

}



TEST(splashOutBlendColorBurnTest_1583, ExceptionalCase_InvalidColorMode_1583) {

    unsigned char src[] = {255, 0, 0};

    unsigned char dest[] = {0, 255, 0};

    unsigned char blend[3];

    splashOutBlendColorBurn(src, dest, blend, static_cast<SplashColorMode>(10)); // Invalid color mode

    // Assuming no exception is thrown and behavior is defined, verify some default or expected output

    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255); // Example expectation based on possible implementation behavior

}
