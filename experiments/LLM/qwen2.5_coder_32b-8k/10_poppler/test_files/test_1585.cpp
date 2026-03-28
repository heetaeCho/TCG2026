#include <gtest/gtest.h>

#include <cmath>



// Assuming SplashTypes.h and necessary headers are included



extern "C" {

    void splashOutBlendSoftLight(SplashColorPtr src, SplashColorPtr dest, SplashColorPtr blend, SplashColorMode cm);

}



TEST(splashOutBlendSoftLightTest_1585, NormalOperation_RGB8_1585) {

    const int nComps = 3;

    unsigned char src[nComps] = {128, 64, 192};

    unsigned char dest[nComps] = {64, 128, 192};

    unsigned char blend[nComps];



    splashOutBlendSoftLight(src, dest, blend, splashModeRGB8);



    // Expected values based on the function logic

    unsigned char expected[nComps] = {130, 125, 206};



    for (int i = 0; i < nComps; ++i) {

        EXPECT_EQ(blend[i], expected[i]) << "Mismatch at component index " << i;

    }

}



TEST(splashOutBlendSoftLightTest_1585, NormalOperation_CMYK8_1585) {

    const int nComps = 4;

    unsigned char src[nComps] = {200, 150, 100, 50};

    unsigned char dest[nComps] = {50, 100, 150, 200};

    unsigned char blend[nComps];



    splashOutBlendSoftLight(src, dest, blend, splashModeCMYK8);



    // Expected values based on the function logic

    unsigned char expected[nComps] = {79, 134, 186, 233};



    for (int i = 0; i < nComps; ++i) {

        EXPECT_EQ(blend[i], expected[i]) << "Mismatch at component index " << i;

    }

}



TEST(splashOutBlendSoftLightTest_1585, BoundaryConditions_ExtremeValues_1585) {

    const int nComps = 3;

    unsigned char src[nComps] = {0, 255, 127};

    unsigned char dest[nComps] = {0, 255, 127};

    unsigned char blend[nComps];



    splashOutBlendSoftLight(src, dest, blend, splashModeRGB8);



    // Expected values based on the function logic

    unsigned char expected[nComps] = {0, 255, 127};



    for (int i = 0; i < nComps; ++i) {

        EXPECT_EQ(blend[i], expected[i]) << "Mismatch at component index " << i;

    }

}



TEST(splashOutBlendSoftLightTest_1585, BoundaryConditions_ZeroComponents_1585) {

    const int nComps = 3;

    unsigned char src[nComps] = {0, 0, 0};

    unsigned char dest[nComps] = {0, 0, 0};

    unsigned char blend[nComps];



    splashOutBlendSoftLight(src, dest, blend, splashModeRGB8);



    // Expected values based on the function logic

    unsigned char expected[nComps] = {0, 0, 0};



    for (int i = 0; i < nComps; ++i) {

        EXPECT_EQ(blend[i], expected[i]) << "Mismatch at component index " << i;

    }

}



TEST(splashOutBlendSoftLightTest_1585, BoundaryConditions_MaxComponents_1585) {

    const int nComps = 3;

    unsigned char src[nComps] = {255, 255, 255};

    unsigned char dest[nComps] = {255, 255, 255};

    unsigned char blend[nComps];



    splashOutBlendSoftLight(src, dest, blend, splashModeRGB8);



    // Expected values based on the function logic

    unsigned char expected[nComps] = {255, 255, 255};



    for (int i = 0; i < nComps; ++i) {

        EXPECT_EQ(blend[i], expected[i]) << "Mismatch at component index " << i;

    }

}
