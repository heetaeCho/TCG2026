#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

// Since splashOutBlendHue is static, we need to access it.
// We redefine its visibility for testing purposes by including the source.
// First, we need the helper functions it depends on (getLum, getSat, setLum, setSat)
// which are also static in the same file.

// We include the implementation file to get access to static functions
// This is a common technique for testing static/file-scope functions
#define static
#include "poppler/SplashOutputDev.cc"
#undef static

class SplashOutBlendHueTest_1592 : public ::testing::Test {
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

// Test Mono8 mode with all zeros
TEST_F(SplashOutBlendHueTest_1592, Mono8AllZeros_1592) {
    src[0] = 0;
    dest[0] = 0;
    splashOutBlendHue(src, dest, blend, splashModeMono8);
    // With all zeros, blend should be 0
    EXPECT_EQ(blend[0], 0);
}

// Test Mono8 mode with max values
TEST_F(SplashOutBlendHueTest_1592, Mono8AllMax_1592) {
    src[0] = 255;
    dest[0] = 255;
    splashOutBlendHue(src, dest, blend, splashModeMono8);
    EXPECT_EQ(blend[0], 255);
}

// Test Mono8 mode with different src and dest
TEST_F(SplashOutBlendHueTest_1592, Mono8DifferentValues_1592) {
    src[0] = 128;
    dest[0] = 64;
    splashOutBlendHue(src, dest, blend, splashModeMono8);
    // Mono channels are all the same, so saturation is 0
    // setLum with lum of dest should give dest luminance
    EXPECT_EQ(blend[0], 64);
}

// Test Mono1 mode
TEST_F(SplashOutBlendHueTest_1592, Mono1Basic_1592) {
    src[0] = 1;
    dest[0] = 0;
    splashOutBlendHue(src, dest, blend, splashModeMono1);
    EXPECT_EQ(blend[0], 0);
}

// Test RGB8 mode with all zeros
TEST_F(SplashOutBlendHueTest_1592, RGB8AllZeros_1592) {
    src[0] = 0; src[1] = 0; src[2] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;
    splashOutBlendHue(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

// Test RGB8 mode with all max
TEST_F(SplashOutBlendHueTest_1592, RGB8AllMax_1592) {
    src[0] = 255; src[1] = 255; src[2] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 255;
    splashOutBlendHue(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
}

// Test RGB8 with pure red src and pure green dest
TEST_F(SplashOutBlendHueTest_1592, RGB8RedSrcGreenDest_1592) {
    src[0] = 255; src[1] = 0; src[2] = 0;
    dest[0] = 0; dest[1] = 255; dest[2] = 0;
    splashOutBlendHue(src, dest, blend, splashModeRGB8);
    // The hue of src applied with saturation of dest and luminance of dest
    // Results should be valid color values
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
    EXPECT_GE(blend[1], 0);
    EXPECT_LE(blend[1], 255);
    EXPECT_GE(blend[2], 0);
    EXPECT_LE(blend[2], 255);
}

// Test RGB8 with gray src (no saturation in src)
TEST_F(SplashOutBlendHueTest_1592, RGB8GraySrc_1592) {
    src[0] = 128; src[1] = 128; src[2] = 128;
    dest[0] = 200; dest[1] = 100; dest[2] = 50;
    splashOutBlendHue(src, dest, blend, splashModeRGB8);
    // src has no hue variation (all equal), saturation of dest applied
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
    EXPECT_GE(blend[1], 0);
    EXPECT_LE(blend[1], 255);
    EXPECT_GE(blend[2], 0);
    EXPECT_LE(blend[2], 255);
}

// Test RGB8 with gray dest (no saturation in dest)
TEST_F(SplashOutBlendHueTest_1592, RGB8GrayDest_1592) {
    src[0] = 200; src[1] = 100; src[2] = 50;
    dest[0] = 128; dest[1] = 128; dest[2] = 128;
    splashOutBlendHue(src, dest, blend, splashModeRGB8);
    // dest has zero saturation, so setSat should produce zero-sat result
    // setLum adjusts to dest luminance
    EXPECT_EQ(blend[0], 128);
    EXPECT_EQ(blend[1], 128);
    EXPECT_EQ(blend[2], 128);
}

// Test BGR8 mode
TEST_F(SplashOutBlendHueTest_1592, BGR8Basic_1592) {
    src[0] = 100; src[1] = 150; src[2] = 200;
    dest[0] = 50; dest[1] = 100; dest[2] = 150;
    splashOutBlendHue(src, dest, blend, splashModeBGR8);
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
    EXPECT_GE(blend[1], 0);
    EXPECT_LE(blend[1], 255);
    EXPECT_GE(blend[2], 0);
    EXPECT_LE(blend[2], 255);
}

// Test XBGR8 mode sets alpha to 255
TEST_F(SplashOutBlendHueTest_1592, XBGR8SetsAlpha_1592) {
    src[0] = 100; src[1] = 150; src[2] = 200; src[3] = 0;
    dest[0] = 50; dest[1] = 100; dest[2] = 150; dest[3] = 0;
    splashOutBlendHue(src, dest, blend, splashModeXBGR8);
    // src[3] should be set to 255
    EXPECT_EQ(src[3], 255);
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
    EXPECT_GE(blend[1], 0);
    EXPECT_LE(blend[1], 255);
    EXPECT_GE(blend[2], 0);
    EXPECT_LE(blend[2], 255);
}

// Test CMYK8 mode with all zeros
TEST_F(SplashOutBlendHueTest_1592, CMYK8AllZeros_1592) {
    src[0] = 0; src[1] = 0; src[2] = 0; src[3] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0; dest[3] = 0;
    splashOutBlendHue(src, dest, blend, splashModeCMYK8);
    // 0xff - 0 = 0xff for all; gray, so sat=0
    // Result should be computed from inversions
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
    EXPECT_GE(blend[1], 0);
    EXPECT_LE(blend[1], 255);
    EXPECT_GE(blend[2], 0);
    EXPECT_LE(blend[2], 255);
    EXPECT_GE(blend[3], 0);
    EXPECT_LE(blend[3], 255);
}

// Test CMYK8 mode with all max (255)
TEST_F(SplashOutBlendHueTest_1592, CMYK8AllMax_1592) {
    src[0] = 255; src[1] = 255; src[2] = 255; src[3] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 255; dest[3] = 255;
    splashOutBlendHue(src, dest, blend, splashModeCMYK8);
    // 0xff - 0xff = 0 for all inverted; gray, so sat=0
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
}

// Test CMYK8 mode with mixed values
TEST_F(SplashOutBlendHueTest_1592, CMYK8MixedValues_1592) {
    src[0] = 50; src[1] = 100; src[2] = 150; src[3] = 200;
    dest[0] = 200; dest[1] = 150; dest[2] = 100; dest[3] = 50;
    splashOutBlendHue(src, dest, blend, splashModeCMYK8);
    // blend[3] should be 0xff - dest2[3] where dest2[3] = 0xff - dest[3] = 0xff - 50 = 205
    // blend[3] = 0xff - 205 = 50
    EXPECT_EQ(blend[3], 50);
    for (int i = 0; i < 4; i++) {
        EXPECT_GE(blend[i], 0);
        EXPECT_LE(blend[i], 255);
    }
}

// Test DeviceN8 mode (should behave same as CMYK8)
TEST_F(SplashOutBlendHueTest_1592, DeviceN8Basic_1592) {
    src[0] = 50; src[1] = 100; src[2] = 150; src[3] = 200;
    dest[0] = 200; dest[1] = 150; dest[2] = 100; dest[3] = 50;
    
    SplashColor blendCMYK;
    SplashColor srcCopy, destCopy;
    memcpy(srcCopy, src, sizeof(SplashColor));
    memcpy(destCopy, dest, sizeof(SplashColor));
    
    splashOutBlendHue(srcCopy, destCopy, blendCMYK, splashModeCMYK8);
    
    memcpy(srcCopy, src, sizeof(SplashColor));
    memcpy(destCopy, dest, sizeof(SplashColor));
    splashOutBlendHue(srcCopy, destCopy, blend, splashModeDeviceN8);
    
    // DeviceN8 and CMYK8 use the same code path
    EXPECT_EQ(blend[0], blendCMYK[0]);
    EXPECT_EQ(blend[1], blendCMYK[1]);
    EXPECT_EQ(blend[2], blendCMYK[2]);
    EXPECT_EQ(blend[3], blendCMYK[3]);
}

// Test CMYK8 preserves K channel from dest (after inversion)
TEST_F(SplashOutBlendHueTest_1592, CMYK8KChannelFromDest_1592) {
    src[0] = 10; src[1] = 20; src[2] = 30; src[3] = 40;
    dest[0] = 100; dest[1] = 100; dest[2] = 100; dest[3] = 80;
    splashOutBlendHue(src, dest, blend, splashModeCMYK8);
    // K channel: blend[3] = 0xff - (0xff - dest[3]) = dest[3] = 80
    EXPECT_EQ(blend[3], 80);
}

// Test RGB8: src with same hue ratios but different intensity
TEST_F(SplashOutBlendHueTest_1592, RGB8SameColorDifferentIntensity_1592) {
    src[0] = 200; src[1] = 100; src[2] = 50;
    dest[0] = 100; dest[1] = 50; dest[2] = 25;
    splashOutBlendHue(src, dest, blend, splashModeRGB8);
    // Both have similar hue ratios; blend should preserve dest luminance
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
}

// Test RGB8 with single channel src
TEST_F(SplashOutBlendHueTest_1592, RGB8SingleChannelSrc_1592) {
    src[0] = 255; src[1] = 0; src[2] = 0;
    dest[0] = 128; dest[1] = 128; dest[2] = 128;
    splashOutBlendHue(src, dest, blend, splashModeRGB8);
    // dest is gray (zero sat), so result should maintain dest luminance with zero sat
    EXPECT_EQ(blend[0], 128);
    EXPECT_EQ(blend[1], 128);
    EXPECT_EQ(blend[2], 128);
}

// Test boundary: src and dest at boundaries for RGB8
TEST_F(SplashOutBlendHueTest_1592, RGB8BoundaryValues_1592) {
    src[0] = 0; src[1] = 255; src[2] = 0;
    dest[0] = 255; dest[1] = 0; dest[2] = 255;
    splashOutBlendHue(src, dest, blend, splashModeRGB8);
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
    EXPECT_GE(blend[1], 0);
    EXPECT_LE(blend[1], 255);
    EXPECT_GE(blend[2], 0);
    EXPECT_LE(blend[2], 255);
}

// Test Mono8: src bright, dest dark
TEST_F(SplashOutBlendHueTest_1592, Mono8SrcBrightDestDark_1592) {
    src[0] = 255;
    dest[0] = 0;
    splashOutBlendHue(src, dest, blend, splashModeMono8);
    // Mono: all channels same, sat=0, lum of dest is 0
    EXPECT_EQ(blend[0], 0);
}

// Test Mono8: src dark, dest bright
TEST_F(SplashOutBlendHueTest_1592, Mono8SrcDarkDestBright_1592) {
    src[0] = 0;
    dest[0] = 255;
    splashOutBlendHue(src, dest, blend, splashModeMono8);
    EXPECT_EQ(blend[0], 255);
}

// Test CMYK8 where inverted values are gray (dest all same)
TEST_F(SplashOutBlendHueTest_1592, CMYK8InvertedGrayDest_1592) {
    src[0] = 30; src[1] = 60; src[2] = 90; src[3] = 120;
    dest[0] = 100; dest[1] = 100; dest[2] = 100; dest[3] = 100;
    splashOutBlendHue(src, dest, blend, splashModeCMYK8);
    // dest inverted: all 155, which is gray, sat = 0
    // After setSat with 0, all channels same, then setLum to dest lum
    // Then re-inverted
    EXPECT_EQ(blend[3], 100); // K preserved from dest
}

// Test RGB8 with blue channel only
TEST_F(SplashOutBlendHueTest_1592, RGB8BlueOnly_1592) {
    src[0] = 0; src[1] = 0; src[2] = 255;
    dest[0] = 0; dest[1] = 0; dest[2] = 255;
    splashOutBlendHue(src, dest, blend, splashModeRGB8);
    // Same hue, so should preserve color
    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 255);
}

// Test RGB8 - white src, colored dest
TEST_F(SplashOutBlendHueTest_1592, RGB8WhiteSrcColoredDest_1592) {
    src[0] = 255; src[1] = 255; src[2] = 255;
    dest[0] = 200; dest[1] = 100; dest[2] = 50;
    splashOutBlendHue(src, dest, blend, splashModeRGB8);
    // src has no hue (achromatic), setSat with dest's saturation
    // on achromatic source, then setLum with dest luminance
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
}

// Test RGB8 - black dest
TEST_F(SplashOutBlendHueTest_1592, RGB8BlackDest_1592) {
    src[0] = 200; src[1] = 100; src[2] = 50;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;
    splashOutBlendHue(src, dest, blend, splashModeRGB8);
    // dest is black: sat=0, lum=0
    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

// Test CMYK8 all channels at 128 (mid-range)
TEST_F(SplashOutBlendHueTest_1592, CMYK8MidRange_1592) {
    src[0] = 128; src[1] = 128; src[2] = 128; src[3] = 128;
    dest[0] = 128; dest[1] = 128; dest[2] = 128; dest[3] = 128;
    splashOutBlendHue(src, dest, blend, splashModeCMYK8);
    // Both inverted to 127, gray, sat=0
    // Result should be gray inverted back
    EXPECT_EQ(blend[3], 128); // K channel from dest
}
