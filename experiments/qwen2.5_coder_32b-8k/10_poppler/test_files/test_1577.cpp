#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashTypes.h"



// Assuming splashColorModeNComps is defined in a way that we can access it.

extern int splashColorModeNComps[];



namespace {



void splashOutBlendMultiply(SplashColorPtr src, SplashColorPtr dest, SplashColorPtr blend, SplashColorMode cm);



class BlendMultiplyTest : public ::testing::Test {

protected:

    static const int kMaxComponents = 8; // Assuming max components for any color mode

    unsigned char src_[kMaxComponents];

    unsigned char dest_[kMaxComponents];

    unsigned char blend_[kMaxComponents];



    void SetUp() override {

        memset(src_, 0, sizeof(src_));

        memset(dest_, 0, sizeof(dest_));

        memset(blend_, 0, sizeof(blend_));

    }

};



TEST_F(BlendMultiplyTest_NormalOperation_RGB8_1577, CorrectBlendingForRGB8_1577) {

    SplashColorMode cm = splashModeRGB8;

    int numComps = splashColorModeNComps[cm];



    src_[0] = 128; src_[1] = 64; src_[2] = 32;

    dest_[0] = 255; dest_[1] = 192; dest_[2] = 128;



    splashOutBlendMultiply(src_, dest_, blend_, cm);



    EXPECT_EQ(blend_[0], 64);   // (128 * 255) / 255

    EXPECT_EQ(blend_[1], 48);   // (64 * 192) / 255

    EXPECT_EQ(blend_[2], 16);   // (32 * 128) / 255

}



TEST_F(BlendMultiplyTest_NormalOperation_CMYK8_1577, CorrectBlendingForCMYK8_1577) {

    SplashColorMode cm = splashModeCMYK8;

    int numComps = splashColorModeNComps[cm];



    src_[0] = 200; src_[1] = 150; src_[2] = 100; src_[3] = 50;

    dest_[0] = 255; dest_[1] = 200; dest_[2] = 150; dest_[3] = 100;



    splashOutBlendMultiply(src_, dest_, blend_, cm);



    EXPECT_EQ(blend_[0], 55);   // (55 * 55) / 255

    EXPECT_EQ(blend_[1], 69);   // (50 * 50) / 255

    EXPECT_EQ(blend_[2], 83);   // (45 * 45) / 255

    EXPECT_EQ(blend_[3], 97);   // (40 * 40) / 255

}



TEST_F(BlendMultiplyTest_BoundaryConditions_AllZeros_1577, AllZerosInput_1577) {

    SplashColorMode cm = splashModeRGB8;

    int numComps = splashColorModeNComps[cm];



    src_[0] = 0; src_[1] = 0; src_[2] = 0;

    dest_[0] = 0; dest_[1] = 0; dest_[2] = 0;



    splashOutBlendMultiply(src_, dest_, blend_, cm);



    EXPECT_EQ(blend_[0], 0);

    EXPECT_EQ(blend_[1], 0);

    EXPECT_EQ(blend_[2], 0);

}



TEST_F(BlendMultiplyTest_BoundaryConditions_AllMax_1577, AllMaxInput_1577) {

    SplashColorMode cm = splashModeRGB8;

    int numComps = splashColorModeNComps[cm];



    src_[0] = 255; src_[1] = 255; src_[2] = 255;

    dest_[0] = 255; dest_[1] = 255; dest_[2] = 255;



    splashOutBlendMultiply(src_, dest_, blend_, cm);



    EXPECT_EQ(blend_[0], 255);

    EXPECT_EQ(blend_[1], 255);

    EXPECT_EQ(blend_[2], 255);

}



TEST_F(BlendMultiplyTest_ExceptionalCase_InvalidColorMode_1577, InvalidColorMode_1577) {

    SplashColorMode cm = static_cast<SplashColorMode>(-1); // Assuming -1 is invalid

    int numComps = splashColorModeNComps[cm];



    src_[0] = 128; src_[1] = 64; src_[2] = 32;

    dest_[0] = 255; dest_[1] = 192; dest_[2] = 128;



    // Assuming this function does not throw exceptions, we check for no crash and correct behavior

    splashOutBlendMultiply(src_, dest_, blend_, cm);



    // Since the color mode is invalid, the output should be zeroed out or unchanged.

    EXPECT_EQ(blend_[0], 0);

    EXPECT_EQ(blend_[1], 0);

    EXPECT_EQ(blend_[2], 0);

}



}  // namespace
