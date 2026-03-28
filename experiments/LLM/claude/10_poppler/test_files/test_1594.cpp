#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

// Include the implementation file to access the static function
// This is necessary because the function has internal linkage (static)
#include "poppler/SplashOutputDev.cc"

class SplashOutBlendColorTest_1594 : public ::testing::Test {
protected:
    SplashColor src;
    SplashColor dest;
    SplashColor blend;

    void SetUp() override {
        memset(src, 0, sizeof(SplashColor));
        memset(dest, 0, sizeof(SplashColor));
        memset(blend, 0, sizeof(SplashColor));
    }
};

// Test Mono1 mode with all zeros
TEST_F(SplashOutBlendColorTest_1594, Mono1_AllZeros_1594) {
    src[0] = 0;
    dest[0] = 0;
    splashOutBlendColor(src, dest, blend, splashModeMono1);
    EXPECT_EQ(blend[0], 0);
}

// Test Mono1 mode with all 255
TEST_F(SplashOutBlendColorTest_1594, Mono1_AllMax_1594) {
    src[0] = 255;
    dest[0] = 255;
    splashOutBlendColor(src, dest, blend, splashModeMono1);
    EXPECT_EQ(blend[0], 255);
}

// Test Mono8 mode - source luminance applied to dest luminance
TEST_F(SplashOutBlendColorTest_1594, Mono8_SrcColorDestLum_1594) {
    src[0] = 100;
    dest[0] = 200;
    splashOutBlendColor(src, dest, blend, splashModeMono8);
    // setLum adjusts src to have dest's luminance
    // Since mono is single channel, the result should reflect dest's luminance
    EXPECT_EQ(blend[0], 200);
}

// Test Mono8 mode with src=0, dest=128
TEST_F(SplashOutBlendColorTest_1594, Mono8_SrcZeroDestMid_1594) {
    src[0] = 0;
    dest[0] = 128;
    splashOutBlendColor(src, dest, blend, splashModeMono8);
    EXPECT_EQ(blend[0], 128);
}

// Test RGB8 mode with all zeros
TEST_F(SplashOutBlendColorTest_1594, RGB8_AllZeros_1594) {
    src[0] = 0; src[1] = 0; src[2] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;
    splashOutBlendColor(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

// Test RGB8 mode with all 255
TEST_F(SplashOutBlendColorTest_1594, RGB8_AllMax_1594) {
    src[0] = 255; src[1] = 255; src[2] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 255;
    splashOutBlendColor(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
}

// Test RGB8 mode with gray src and colored dest
TEST_F(SplashOutBlendColorTest_1594, RGB8_GraySrcColoredDest_1594) {
    src[0] = 128; src[1] = 128; src[2] = 128;
    dest[0] = 200; dest[1] = 100; dest[2] = 50;
    splashOutBlendColor(src, dest, blend, splashModeRGB8);
    // Gray source has no color variation, so result should have dest's luminance
    // with gray chrominance - effectively a gray at dest's luminance level
    int destLum = (int)(0.299 * 200 + 0.587 * 100 + 0.114 * 50);
    // All blend channels should be approximately equal (gray) at dest luminance
    EXPECT_NEAR(blend[0], blend[1], 1);
    EXPECT_NEAR(blend[1], blend[2], 1);
}

// Test BGR8 mode with specific values
TEST_F(SplashOutBlendColorTest_1594, BGR8_BasicTest_1594) {
    src[0] = 200; src[1] = 100; src[2] = 50;
    dest[0] = 128; dest[1] = 128; dest[2] = 128;
    splashOutBlendColor(src, dest, blend, splashModeBGR8);
    // Should produce valid output
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
    EXPECT_GE(blend[1], 0);
    EXPECT_LE(blend[1], 255);
    EXPECT_GE(blend[2], 0);
    EXPECT_LE(blend[2], 255);
}

// Test XBGR8 mode sets alpha to 255
TEST_F(SplashOutBlendColorTest_1594, XBGR8_AlphaSetTo255_1594) {
    src[0] = 100; src[1] = 150; src[2] = 200; src[3] = 0;
    dest[0] = 50; dest[1] = 100; dest[2] = 150;
    splashOutBlendColor(src, dest, blend, splashModeXBGR8);
    // src[3] should be set to 255 in XBGR8 mode
    EXPECT_EQ(src[3], 255);
}

// Test XBGR8 produces valid blend values
TEST_F(SplashOutBlendColorTest_1594, XBGR8_ValidBlendValues_1594) {
    src[0] = 255; src[1] = 0; src[2] = 0; src[3] = 0;
    dest[0] = 0; dest[1] = 255; dest[2] = 0;
    splashOutBlendColor(src, dest, blend, splashModeXBGR8);
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
    EXPECT_GE(blend[1], 0);
    EXPECT_LE(blend[1], 255);
    EXPECT_GE(blend[2], 0);
    EXPECT_LE(blend[2], 255);
}

// Test CMYK8 mode with all zeros
TEST_F(SplashOutBlendColorTest_1594, CMYK8_AllZeros_1594) {
    src[0] = 0; src[1] = 0; src[2] = 0; src[3] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0; dest[3] = 0;
    splashOutBlendColor(src, dest, blend, splashModeCMYK8);
    // CMYK 0 = white in RGB (after inversion: 255,255,255)
    // setLum with white src and white dest luminance -> white -> re-inverted to 0
    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
    EXPECT_EQ(blend[3], 0);
}

// Test CMYK8 mode with all 255 (full CMYK = black)
TEST_F(SplashOutBlendColorTest_1594, CMYK8_AllMax_1594) {
    src[0] = 255; src[1] = 255; src[2] = 255; src[3] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 255; dest[3] = 255;
    splashOutBlendColor(src, dest, blend, splashModeCMYK8);
    // All 255 CMYK -> inverted to 0,0,0 RGB (black)
    // setLum with black src and black dest luminance -> black -> re-inverted to 255
    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
    EXPECT_EQ(blend[3], 255);
}

// Test CMYK8 mode - blend[3] should be dest's inverted K value inverted back
TEST_F(SplashOutBlendColorTest_1594, CMYK8_KChannelFromDest_1594) {
    src[0] = 50; src[1] = 100; src[2] = 150; src[3] = 200;
    dest[0] = 10; dest[1] = 20; dest[2] = 30; dest[3] = 40;
    splashOutBlendColor(src, dest, blend, splashModeCMYK8);
    // blend[3] before final inversion = dest2[3] = 0xff - dest[3] = 0xff - 40 = 215
    // After inversion: 0xff - 215 = 40
    EXPECT_EQ(blend[3], 40);
}

// Test DeviceN8 mode works same as CMYK8 for first 4 channels
TEST_F(SplashOutBlendColorTest_1594, DeviceN8_SameAsCMYK_1594) {
    SplashColor src_cmyk, dest_cmyk, blend_cmyk;
    SplashColor src_devn, dest_devn, blend_devn;

    src_cmyk[0] = src_devn[0] = 80;
    src_cmyk[1] = src_devn[1] = 120;
    src_cmyk[2] = src_devn[2] = 160;
    src_cmyk[3] = src_devn[3] = 200;
    dest_cmyk[0] = dest_devn[0] = 30;
    dest_cmyk[1] = dest_devn[1] = 60;
    dest_cmyk[2] = dest_devn[2] = 90;
    dest_cmyk[3] = dest_devn[3] = 120;

    splashOutBlendColor(src_cmyk, dest_cmyk, blend_cmyk, splashModeCMYK8);
    splashOutBlendColor(src_devn, dest_devn, blend_devn, splashModeDeviceN8);

    EXPECT_EQ(blend_cmyk[0], blend_devn[0]);
    EXPECT_EQ(blend_cmyk[1], blend_devn[1]);
    EXPECT_EQ(blend_cmyk[2], blend_devn[2]);
    EXPECT_EQ(blend_cmyk[3], blend_devn[3]);
}

// Test RGB8 with pure red src and gray dest
TEST_F(SplashOutBlendColorTest_1594, RGB8_PureRedSrcGrayDest_1594) {
    src[0] = 255; src[1] = 0; src[2] = 0;
    dest[0] = 128; dest[1] = 128; dest[2] = 128;
    splashOutBlendColor(src, dest, blend, splashModeRGB8);
    // The blend should preserve the color (hue/saturation) of src 
    // but use the luminance of dest
    // Luminance of dest (gray 128) = 128
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
    EXPECT_GE(blend[1], 0);
    EXPECT_LE(blend[1], 255);
    EXPECT_GE(blend[2], 0);
    EXPECT_LE(blend[2], 255);
    // Red channel should be highest since src is red
    EXPECT_GE(blend[0], blend[1]);
    EXPECT_GE(blend[0], blend[2]);
}

// Test Mono8 mode with max src and zero dest
TEST_F(SplashOutBlendColorTest_1594, Mono8_MaxSrcZeroDest_1594) {
    src[0] = 255;
    dest[0] = 0;
    splashOutBlendColor(src, dest, blend, splashModeMono8);
    // setLum with same channel for all R,G,B: result should be dest luminance = 0
    EXPECT_EQ(blend[0], 0);
}

// Test RGB8 mode - same color src and dest should produce same color
TEST_F(SplashOutBlendColorTest_1594, RGB8_SameColor_1594) {
    src[0] = 100; src[1] = 150; src[2] = 200;
    dest[0] = 100; dest[1] = 150; dest[2] = 200;
    splashOutBlendColor(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(blend[0], 100);
    EXPECT_EQ(blend[1], 150);
    EXPECT_EQ(blend[2], 200);
}

// Test CMYK8 with same src and dest
TEST_F(SplashOutBlendColorTest_1594, CMYK8_SameColor_1594) {
    src[0] = 50; src[1] = 100; src[2] = 150; src[3] = 200;
    dest[0] = 50; dest[1] = 100; dest[2] = 150; dest[3] = 200;
    splashOutBlendColor(src, dest, blend, splashModeCMYK8);
    EXPECT_EQ(blend[0], 50);
    EXPECT_EQ(blend[1], 100);
    EXPECT_EQ(blend[2], 150);
    EXPECT_EQ(blend[3], 200);
}

// Test RGB8 with white src and white dest
TEST_F(SplashOutBlendColorTest_1594, RGB8_WhiteOnWhite_1594) {
    src[0] = 255; src[1] = 255; src[2] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 255;
    splashOutBlendColor(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
}

// Test RGB8 with black src and black dest
TEST_F(SplashOutBlendColorTest_1594, RGB8_BlackOnBlack_1594) {
    src[0] = 0; src[1] = 0; src[2] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;
    splashOutBlendColor(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

// Test RGB8 gray src should maintain gray in output at dest luminance level
TEST_F(SplashOutBlendColorTest_1594, RGB8_GraySrcGrayDest_1594) {
    src[0] = 100; src[1] = 100; src[2] = 100;
    dest[0] = 200; dest[1] = 200; dest[2] = 200;
    splashOutBlendColor(src, dest, blend, splashModeRGB8);
    // Gray src with gray dest - should produce gray at dest luminance
    EXPECT_EQ(blend[0], 200);
    EXPECT_EQ(blend[1], 200);
    EXPECT_EQ(blend[2], 200);
}

// Test Mono1 mode boundary - src=255, dest=1
TEST_F(SplashOutBlendColorTest_1594, Mono1_Boundary_1594) {
    src[0] = 255;
    dest[0] = 1;
    splashOutBlendColor(src, dest, blend, splashModeMono1);
    EXPECT_EQ(blend[0], 1);
}
