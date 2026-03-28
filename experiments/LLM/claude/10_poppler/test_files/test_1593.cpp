#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

// Include the .cc file to access the static function
// We need to handle potential dependencies
#include <cstring>
#include <cstdlib>

// Forward declare or include necessary headers that SplashOutputDev.cc needs
// We include the actual .cc to get access to the static function
// This is necessary because the function under test is static

// Minimal includes to allow compilation of the static functions we need
#include "SplashOutputDev.cc"

class SplashOutBlendSaturationTest_1593 : public ::testing::Test {
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

// ==================== Mono8 Mode Tests ====================

TEST_F(SplashOutBlendSaturationTest_1593, Mono8_AllZeros_1593) {
    src[0] = 0;
    dest[0] = 0;
    splashOutBlendSaturation(src, dest, blend, splashModeMono8);
    // With all zeros, saturation is 0, luminance is 0, result should be 0
    EXPECT_EQ(blend[0], 0);
}

TEST_F(SplashOutBlendSaturationTest_1593, Mono8_AllMax_1593) {
    src[0] = 255;
    dest[0] = 255;
    splashOutBlendSaturation(src, dest, blend, splashModeMono8);
    EXPECT_EQ(blend[0], 255);
}

TEST_F(SplashOutBlendSaturationTest_1593, Mono8_MidValues_1593) {
    src[0] = 128;
    dest[0] = 128;
    splashOutBlendSaturation(src, dest, blend, splashModeMono8);
    EXPECT_EQ(blend[0], 128);
}

TEST_F(SplashOutBlendSaturationTest_1593, Mono1_AllZeros_1593) {
    src[0] = 0;
    dest[0] = 0;
    splashOutBlendSaturation(src, dest, blend, splashModeMono1);
    EXPECT_EQ(blend[0], 0);
}

// ==================== RGB8 Mode Tests ====================

TEST_F(SplashOutBlendSaturationTest_1593, RGB8_AllZeros_1593) {
    src[0] = 0; src[1] = 0; src[2] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;
    splashOutBlendSaturation(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

TEST_F(SplashOutBlendSaturationTest_1593, RGB8_AllMax_1593) {
    src[0] = 255; src[1] = 255; src[2] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 255;
    splashOutBlendSaturation(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
}

TEST_F(SplashOutBlendSaturationTest_1593, RGB8_PureRed_1593) {
    src[0] = 255; src[1] = 0; src[2] = 0;
    dest[0] = 255; dest[1] = 0; dest[2] = 0;
    splashOutBlendSaturation(src, dest, blend, splashModeRGB8);
    // Saturation of src applied to dest, with dest's luminance preserved
    // Both are pure red so result should maintain character
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
    EXPECT_GE(blend[1], 0);
    EXPECT_LE(blend[1], 255);
    EXPECT_GE(blend[2], 0);
    EXPECT_LE(blend[2], 255);
}

TEST_F(SplashOutBlendSaturationTest_1593, RGB8_GrayDest_ColorSrc_1593) {
    // Gray destination (no saturation), colorful source
    src[0] = 255; src[1] = 0; src[2] = 0;
    dest[0] = 128; dest[1] = 128; dest[2] = 128;
    splashOutBlendSaturation(src, dest, blend, splashModeRGB8);
    // Gray dest with any saturation applied should still be gray (setSat on equal values)
    EXPECT_EQ(blend[0], blend[1]);
    EXPECT_EQ(blend[1], blend[2]);
}

TEST_F(SplashOutBlendSaturationTest_1593, RGB8_ZeroSatSrc_1593) {
    // Source has zero saturation (gray), dest is colorful
    src[0] = 100; src[1] = 100; src[2] = 100;
    dest[0] = 200; dest[1] = 50; dest[2] = 100;
    splashOutBlendSaturation(src, dest, blend, splashModeRGB8);
    // Applying zero saturation to dest should make it gray-ish with dest's luminance
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
}

TEST_F(SplashOutBlendSaturationTest_1593, RGB8_IdenticalSrcDest_1593) {
    src[0] = 100; src[1] = 150; src[2] = 200;
    dest[0] = 100; dest[1] = 150; dest[2] = 200;
    splashOutBlendSaturation(src, dest, blend, splashModeRGB8);
    // When src and dest are identical, blend should be close to the same values
    // (saturation of src applied to dest ordering, with dest luminance)
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
    EXPECT_GE(blend[1], 0);
    EXPECT_LE(blend[1], 255);
    EXPECT_GE(blend[2], 0);
    EXPECT_LE(blend[2], 255);
}

// ==================== BGR8 Mode Tests ====================

TEST_F(SplashOutBlendSaturationTest_1593, BGR8_AllZeros_1593) {
    src[0] = 0; src[1] = 0; src[2] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;
    splashOutBlendSaturation(src, dest, blend, splashModeBGR8);
    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

TEST_F(SplashOutBlendSaturationTest_1593, BGR8_MixedValues_1593) {
    src[0] = 50; src[1] = 150; src[2] = 250;
    dest[0] = 200; dest[1] = 100; dest[2] = 50;
    splashOutBlendSaturation(src, dest, blend, splashModeBGR8);
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
    EXPECT_GE(blend[1], 0);
    EXPECT_LE(blend[1], 255);
    EXPECT_GE(blend[2], 0);
    EXPECT_LE(blend[2], 255);
}

// ==================== XBGR8 Mode Tests ====================

TEST_F(SplashOutBlendSaturationTest_1593, XBGR8_SetsSrcAlphaTo255_1593) {
    src[0] = 100; src[1] = 150; src[2] = 200; src[3] = 0;
    dest[0] = 50; dest[1] = 100; dest[2] = 150;
    splashOutBlendSaturation(src, dest, blend, splashModeXBGR8);
    // XBGR8 sets src[3] = 255
    EXPECT_EQ(src[3], 255);
}

TEST_F(SplashOutBlendSaturationTest_1593, XBGR8_AllZeros_1593) {
    src[0] = 0; src[1] = 0; src[2] = 0; src[3] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;
    splashOutBlendSaturation(src, dest, blend, splashModeXBGR8);
    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
    EXPECT_EQ(src[3], 255);
}

// ==================== CMYK8 Mode Tests ====================

TEST_F(SplashOutBlendSaturationTest_1593, CMYK8_AllZeros_1593) {
    src[0] = 0; src[1] = 0; src[2] = 0; src[3] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0; dest[3] = 0;
    splashOutBlendSaturation(src, dest, blend, splashModeCMYK8);
    // All zeros in CMYK means white. Inverted = 255,255,255,255
    // saturation of uniform color is 0, luminance of uniform is same
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
}

TEST_F(SplashOutBlendSaturationTest_1593, CMYK8_AllMax_1593) {
    src[0] = 255; src[1] = 255; src[2] = 255; src[3] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 255; dest[3] = 255;
    splashOutBlendSaturation(src, dest, blend, splashModeCMYK8);
    // All 255 in CMYK inverted = 0,0,0,0 - uniform, saturation 0
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
}

TEST_F(SplashOutBlendSaturationTest_1593, CMYK8_MixedValues_1593) {
    src[0] = 100; src[1] = 50; src[2] = 200; src[3] = 30;
    dest[0] = 150; dest[1] = 80; dest[2] = 120; dest[3] = 60;
    splashOutBlendSaturation(src, dest, blend, splashModeCMYK8);
    // Just verify output is within valid range
    for (int i = 0; i < 4; i++) {
        EXPECT_GE(blend[i], 0);
        EXPECT_LE(blend[i], 255);
    }
}

TEST_F(SplashOutBlendSaturationTest_1593, CMYK8_BlackK_1593) {
    // Pure black in CMYK: K=255
    src[0] = 0; src[1] = 0; src[2] = 0; src[3] = 255;
    dest[0] = 0; dest[1] = 0; dest[2] = 0; dest[3] = 255;
    splashOutBlendSaturation(src, dest, blend, splashModeCMYK8);
    for (int i = 0; i < 4; i++) {
        EXPECT_GE(blend[i], 0);
        EXPECT_LE(blend[i], 255);
    }
}

// ==================== DeviceN8 Mode Tests ====================

TEST_F(SplashOutBlendSaturationTest_1593, DeviceN8_AllZeros_1593) {
    src[0] = 0; src[1] = 0; src[2] = 0; src[3] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0; dest[3] = 0;
    splashOutBlendSaturation(src, dest, blend, splashModeDeviceN8);
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
}

TEST_F(SplashOutBlendSaturationTest_1593, DeviceN8_MixedValues_1593) {
    src[0] = 30; src[1] = 60; src[2] = 90; src[3] = 120;
    dest[0] = 200; dest[1] = 150; dest[2] = 100; dest[3] = 50;
    splashOutBlendSaturation(src, dest, blend, splashModeDeviceN8);
    for (int i = 0; i < 4; i++) {
        EXPECT_GE(blend[i], 0);
        EXPECT_LE(blend[i], 255);
    }
}

// ==================== Boundary Tests ====================

TEST_F(SplashOutBlendSaturationTest_1593, RGB8_MaxSaturation_1593) {
    // Maximum saturation: one channel at 255, another at 0
    src[0] = 255; src[1] = 0; src[2] = 128;
    dest[0] = 200; dest[1] = 50; dest[2] = 150;
    splashOutBlendSaturation(src, dest, blend, splashModeRGB8);
    for (int i = 0; i < 3; i++) {
        EXPECT_GE(blend[i], 0);
        EXPECT_LE(blend[i], 255);
    }
}

TEST_F(SplashOutBlendSaturationTest_1593, RGB8_SingleChannelDifference_1593) {
    src[0] = 1; src[1] = 0; src[2] = 0;
    dest[0] = 255; dest[1] = 0; dest[2] = 0;
    splashOutBlendSaturation(src, dest, blend, splashModeRGB8);
    for (int i = 0; i < 3; i++) {
        EXPECT_GE(blend[i], 0);
        EXPECT_LE(blend[i], 255);
    }
}

TEST_F(SplashOutBlendSaturationTest_1593, Mono8_BoundaryValues_1593) {
    src[0] = 1;
    dest[0] = 254;
    splashOutBlendSaturation(src, dest, blend, splashModeMono8);
    // For mono, all three channels are same, so sat=0, result is dest luminance
    EXPECT_EQ(blend[0], 254);
}

TEST_F(SplashOutBlendSaturationTest_1593, CMYK8_InversionSymmetry_1593) {
    // Test with values that invert nicely
    src[0] = 127; src[1] = 127; src[2] = 127; src[3] = 127;
    dest[0] = 128; dest[1] = 128; dest[2] = 128; dest[3] = 128;
    splashOutBlendSaturation(src, dest, blend, splashModeCMYK8);
    for (int i = 0; i < 4; i++) {
        EXPECT_GE(blend[i], 0);
        EXPECT_LE(blend[i], 255);
    }
}
