#include <gtest/gtest.h>
#include "splash/SplashTypes.h"
#include <cstring>
#include <algorithm>

// The function is static in the .cc file, so we include it to access it
// We need to make it accessible for testing
typedef unsigned char SplashColor[SPLASH_MAX_COLOR + 1];

// Declare the function signature matching the static function
// We'll include the source to get access
static void splashOutBlendDarken(SplashColorPtr src, SplashColorPtr dest, SplashColorPtr blend, SplashColorMode cm);

// Include the implementation to access the static function
// Since we can't do that cleanly, we replicate the function for testing.
// In a real scenario, the function would be made testable.
#include "poppler/SplashOutputDev.cc"

class SplashOutBlendDarkenTest_1580 : public ::testing::Test {
protected:
    SplashColor src;
    SplashColor dest;
    SplashColor blend;

    void SetUp() override {
        memset(src, 0, sizeof(src));
        memset(dest, 0, sizeof(dest));
        memset(blend, 0, sizeof(blend));
    }
};

// ============ RGB8 Mode Tests ============

TEST_F(SplashOutBlendDarkenTest_1580, RGB8_SrcLessThanDest_BlendEqualsSrc_1580) {
    src[0] = 50;  src[1] = 60;  src[2] = 70;
    dest[0] = 100; dest[1] = 120; dest[2] = 140;

    splashOutBlendDarken(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 50);
    EXPECT_EQ(blend[1], 60);
    EXPECT_EQ(blend[2], 70);
}

TEST_F(SplashOutBlendDarkenTest_1580, RGB8_DestLessThanSrc_BlendEqualsDest_1580) {
    src[0] = 200; src[1] = 180; src[2] = 220;
    dest[0] = 100; dest[1] = 90;  dest[2] = 110;

    splashOutBlendDarken(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 100);
    EXPECT_EQ(blend[1], 90);
    EXPECT_EQ(blend[2], 110);
}

TEST_F(SplashOutBlendDarkenTest_1580, RGB8_EqualValues_BlendEqualsEither_1580) {
    src[0] = 128; src[1] = 128; src[2] = 128;
    dest[0] = 128; dest[1] = 128; dest[2] = 128;

    splashOutBlendDarken(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 128);
    EXPECT_EQ(blend[1], 128);
    EXPECT_EQ(blend[2], 128);
}

TEST_F(SplashOutBlendDarkenTest_1580, RGB8_AllZeros_1580) {
    memset(src, 0, sizeof(src));
    memset(dest, 0, sizeof(dest));

    splashOutBlendDarken(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

TEST_F(SplashOutBlendDarkenTest_1580, RGB8_AllMax_1580) {
    memset(src, 255, 3);
    memset(dest, 255, 3);

    splashOutBlendDarken(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
}

TEST_F(SplashOutBlendDarkenTest_1580, RGB8_MixedComparison_1580) {
    src[0] = 50;  src[1] = 200; src[2] = 100;
    dest[0] = 200; dest[1] = 50;  dest[2] = 100;

    splashOutBlendDarken(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 50);
    EXPECT_EQ(blend[1], 50);
    EXPECT_EQ(blend[2], 100);
}

TEST_F(SplashOutBlendDarkenTest_1580, RGB8_SrcUnchanged_1580) {
    src[0] = 50; src[1] = 200; src[2] = 100;
    dest[0] = 200; dest[1] = 50; dest[2] = 100;
    SplashColor origSrc;
    memcpy(origSrc, src, sizeof(SplashColor));

    splashOutBlendDarken(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(src[0], origSrc[0]);
    EXPECT_EQ(src[1], origSrc[1]);
    EXPECT_EQ(src[2], origSrc[2]);
}

TEST_F(SplashOutBlendDarkenTest_1580, RGB8_DestUnchanged_1580) {
    src[0] = 50; src[1] = 200; src[2] = 100;
    dest[0] = 200; dest[1] = 50; dest[2] = 100;
    SplashColor origDest;
    memcpy(origDest, dest, sizeof(SplashColor));

    splashOutBlendDarken(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(dest[0], origDest[0]);
    EXPECT_EQ(dest[1], origDest[1]);
    EXPECT_EQ(dest[2], origDest[2]);
}

// ============ Mono8 Mode Tests ============

TEST_F(SplashOutBlendDarkenTest_1580, Mono8_SrcSmaller_1580) {
    src[0] = 30;
    dest[0] = 200;

    splashOutBlendDarken(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], 30);
}

TEST_F(SplashOutBlendDarkenTest_1580, Mono8_DestSmaller_1580) {
    src[0] = 200;
    dest[0] = 30;

    splashOutBlendDarken(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], 30);
}

TEST_F(SplashOutBlendDarkenTest_1580, Mono8_Equal_1580) {
    src[0] = 128;
    dest[0] = 128;

    splashOutBlendDarken(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], 128);
}

// ============ BGR8 Mode Tests ============

TEST_F(SplashOutBlendDarkenTest_1580, BGR8_MinOfEach_1580) {
    src[0] = 10; src[1] = 250; src[2] = 100;
    dest[0] = 240; dest[1] = 20; dest[2] = 100;

    splashOutBlendDarken(src, dest, blend, splashModeBGR8);

    EXPECT_EQ(blend[0], 10);
    EXPECT_EQ(blend[1], 20);
    EXPECT_EQ(blend[2], 100);
}

// ============ XBGR8 Mode Tests ============

TEST_F(SplashOutBlendDarkenTest_1580, XBGR8_FourComponents_1580) {
    src[0] = 10; src[1] = 250; src[2] = 100; src[3] = 50;
    dest[0] = 240; dest[1] = 20; dest[2] = 200; dest[3] = 60;

    splashOutBlendDarken(src, dest, blend, splashModeXBGR8);

    EXPECT_EQ(blend[0], 10);
    EXPECT_EQ(blend[1], 20);
    EXPECT_EQ(blend[2], 100);
    EXPECT_EQ(blend[3], 50);
}

// ============ CMYK8 Mode Tests ============
// For CMYK8: blend[i] = max(dest[i], src[i]) due to the inversion logic

TEST_F(SplashOutBlendDarkenTest_1580, CMYK8_MaxOfEach_1580) {
    src[0] = 50;  src[1] = 200; src[2] = 100; src[3] = 150;
    dest[0] = 200; dest[1] = 50;  dest[2] = 100; dest[3] = 80;

    SplashColor origSrc, origDest;
    memcpy(origSrc, src, sizeof(SplashColor));
    memcpy(origDest, dest, sizeof(SplashColor));

    splashOutBlendDarken(src, dest, blend, splashModeCMYK8);

    // For CMYK, the effective result is max(dest, src) for each component
    EXPECT_EQ(blend[0], 200);
    EXPECT_EQ(blend[1], 200);
    EXPECT_EQ(blend[2], 100);
    EXPECT_EQ(blend[3], 150);

    // Verify src and dest are restored
    EXPECT_EQ(src[0], origSrc[0]);
    EXPECT_EQ(src[1], origSrc[1]);
    EXPECT_EQ(src[2], origSrc[2]);
    EXPECT_EQ(src[3], origSrc[3]);
    EXPECT_EQ(dest[0], origDest[0]);
    EXPECT_EQ(dest[1], origDest[1]);
    EXPECT_EQ(dest[2], origDest[2]);
    EXPECT_EQ(dest[3], origDest[3]);
}

TEST_F(SplashOutBlendDarkenTest_1580, CMYK8_AllZeros_1580) {
    memset(src, 0, 4);
    memset(dest, 0, 4);

    splashOutBlendDarken(src, dest, blend, splashModeCMYK8);

    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
    EXPECT_EQ(blend[3], 0);
}

TEST_F(SplashOutBlendDarkenTest_1580, CMYK8_AllMax_1580) {
    memset(src, 255, 4);
    memset(dest, 255, 4);

    splashOutBlendDarken(src, dest, blend, splashModeCMYK8);

    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
    EXPECT_EQ(blend[3], 255);
}

TEST_F(SplashOutBlendDarkenTest_1580, CMYK8_SrcAllZeroDestAllMax_1580) {
    memset(src, 0, 4);
    memset(dest, 255, 4);

    splashOutBlendDarken(src, dest, blend, splashModeCMYK8);

    // max(0, 255) = 255
    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
    EXPECT_EQ(blend[3], 255);
}

TEST_F(SplashOutBlendDarkenTest_1580, CMYK8_SrcAllMaxDestAllZero_1580) {
    memset(src, 255, 4);
    memset(dest, 0, 4);

    splashOutBlendDarken(src, dest, blend, splashModeCMYK8);

    // max(255, 0) = 255
    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
    EXPECT_EQ(blend[3], 255);
}

TEST_F(SplashOutBlendDarkenTest_1580, CMYK8_EqualValues_1580) {
    src[0] = 100; src[1] = 100; src[2] = 100; src[3] = 100;
    dest[0] = 100; dest[1] = 100; dest[2] = 100; dest[3] = 100;

    splashOutBlendDarken(src, dest, blend, splashModeCMYK8);

    EXPECT_EQ(blend[0], 100);
    EXPECT_EQ(blend[1], 100);
    EXPECT_EQ(blend[2], 100);
    EXPECT_EQ(blend[3], 100);
}

// ============ Mono1 Mode Tests ============

TEST_F(SplashOutBlendDarkenTest_1580, Mono1_BothZero_1580) {
    src[0] = 0;
    dest[0] = 0;

    splashOutBlendDarken(src, dest, blend, splashModeMono1);

    EXPECT_EQ(blend[0], 0);
}

TEST_F(SplashOutBlendDarkenTest_1580, Mono1_BothOne_1580) {
    src[0] = 1;
    dest[0] = 1;

    splashOutBlendDarken(src, dest, blend, splashModeMono1);

    EXPECT_EQ(blend[0], 1);
}

TEST_F(SplashOutBlendDarkenTest_1580, Mono1_SrcZeroDestOne_1580) {
    src[0] = 0;
    dest[0] = 1;

    splashOutBlendDarken(src, dest, blend, splashModeMono1);

    EXPECT_EQ(blend[0], 0);
}

TEST_F(SplashOutBlendDarkenTest_1580, Mono1_SrcOneDestZero_1580) {
    src[0] = 1;
    dest[0] = 0;

    splashOutBlendDarken(src, dest, blend, splashModeMono1);

    EXPECT_EQ(blend[0], 0);
}

// ============ Boundary value tests for RGB8 ============

TEST_F(SplashOutBlendDarkenTest_1580, RGB8_BoundaryZeroAndMax_1580) {
    src[0] = 0;   src[1] = 255; src[2] = 0;
    dest[0] = 255; dest[1] = 0;   dest[2] = 255;

    splashOutBlendDarken(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

TEST_F(SplashOutBlendDarkenTest_1580, RGB8_AdjacentValues_1580) {
    src[0] = 127; src[1] = 128; src[2] = 1;
    dest[0] = 128; dest[1] = 127; dest[2] = 0;

    splashOutBlendDarken(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 127);
    EXPECT_EQ(blend[1], 127);
    EXPECT_EQ(blend[2], 0);
}

// ============ CMYK8 boundary adjacent values ============

TEST_F(SplashOutBlendDarkenTest_1580, CMYK8_AdjacentValues_1580) {
    src[0] = 127; src[1] = 128; src[2] = 254; src[3] = 1;
    dest[0] = 128; dest[1] = 127; dest[2] = 255; dest[3] = 0;

    splashOutBlendDarken(src, dest, blend, splashModeCMYK8);

    // max for each: 128, 128, 255, 1
    EXPECT_EQ(blend[0], 128);
    EXPECT_EQ(blend[1], 128);
    EXPECT_EQ(blend[2], 255);
    EXPECT_EQ(blend[3], 1);
}
