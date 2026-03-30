#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashTypes.h"



extern int splashColorModeNComps[];



namespace {



// Test fixture for testing the splashOutBlendDarken function.

class SplashOutBlendDarkenTest_1580 : public ::testing::Test {

protected:

    // Initialize test data

    void SetUp() override {

        src = new unsigned char[8];

        dest = new unsigned char[8];

        blend = new unsigned char[8];



        for (int i = 0; i < 8; ++i) {

            src[i] = 0;

            dest[i] = 0;

            blend[i] = 0;

        }

    }



    // Clean up test data

    void TearDown() override {

        delete[] src;

        delete[] dest;

        delete[] blend;

    }



    unsigned char* src;

    unsigned char* dest;

    unsigned char* blend;

};



// Test normal operation with RGB8 mode.

TEST_F(SplashOutBlendDarkenTest_1580, NormalOperation_RGB8_1580) {

    splashColorModeNComps[splashModeRGB8] = 3;



    src[0] = 100; src[1] = 150; src[2] = 200;

    dest[0] = 50; dest[1] = 200; dest[2] = 100;



    splashOutBlendDarken(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 50);

    EXPECT_EQ(blend[1], 150);

    EXPECT_EQ(blend[2], 100);

}



// Test normal operation with CMYK8 mode.

TEST_F(SplashOutBlendDarkenTest_1580, NormalOperation_CMYK8_1580) {

    splashColorModeNComps[splashModeCMYK8] = 4;



    src[0] = 100; src[1] = 150; src[2] = 200; src[3] = 250;

    dest[0] = 50; dest[1] = 200; dest[2] = 100; dest[3] = 50;



    splashOutBlendDarken(src, dest, blend, splashModeCMYK8);



    EXPECT_EQ(blend[0], 50);

    EXPECT_EQ(blend[1], 150);

    EXPECT_EQ(blend[2], 100);

    EXPECT_EQ(blend[3], 50);

}



// Test boundary conditions with all zeros.

TEST_F(SplashOutBlendDarkenTest_1580, BoundaryAllZeros_RGB8_1580) {

    splashColorModeNComps[splashModeRGB8] = 3;



    src[0] = 0; src[1] = 0; src[2] = 0;

    dest[0] = 0; dest[1] = 0; dest[2] = 0;



    splashOutBlendDarken(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 0);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 0);

}



// Test boundary conditions with all maximum values.

TEST_F(SplashOutBlendDarkenTest_1580, BoundaryAllMax_RGB8_1580) {

    splashColorModeNComps[splashModeRGB8] = 3;



    src[0] = 255; src[1] = 255; src[2] = 255;

    dest[0] = 255; dest[1] = 255; dest[2] = 255;



    splashOutBlendDarken(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255);

}



// Test boundary conditions with src values greater than dest.

TEST_F(SplashOutBlendDarkenTest_1580, BoundarySrcGreater_RGB8_1580) {

    splashColorModeNComps[splashModeRGB8] = 3;



    src[0] = 200; src[1] = 150; src[2] = 100;

    dest[0] = 100; dest[1] = 100; dest[2] = 100;



    splashOutBlendDarken(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 100);

    EXPECT_EQ(blend[1], 100);

    EXPECT_EQ(blend[2], 100);

}



// Test boundary conditions with src values less than dest.

TEST_F(SplashOutBlendDarkenTest_1580, BoundarySrcLess_RGB8_1580) {

    splashColorModeNComps[splashModeRGB8] = 3;



    src[0] = 50; src[1] = 100; src[2] = 150;

    dest[0] = 100; dest[1] = 150; dest[2] = 200;



    splashOutBlendDarken(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 50);

    EXPECT_EQ(blend[1], 100);

    EXPECT_EQ(blend[2], 150);

}



// Test exceptional case with invalid color mode.

TEST_F(SplashOutBlendDarkenTest_1580, ExceptionalInvalidColorMode_1580) {

    splashColorModeNComps[splashModeMono1] = 1;



    src[0] = 255;

    dest[0] = 255;



    // This should not crash and ideally return some expected behavior.

    // Since the function does not specify any error handling, we assume it processes based on available components.

    splashOutBlendDarken(src, dest, blend, splashModeMono1);



    EXPECT_EQ(blend[0], 255);

}



}  // namespace
