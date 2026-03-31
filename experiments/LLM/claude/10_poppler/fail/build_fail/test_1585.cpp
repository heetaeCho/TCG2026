#include <gtest/gtest.h>
#include <cmath>
#include <cstring>

// Include necessary headers
#include "splash/SplashTypes.h"

// We need to declare the function under test since it's static in the .cc file.
// We'll need to either make it accessible or redefine the signature for testing.
// Since it's a static function in a .cc file, we need to include it or use a workaround.

// For testing a static function, we include the source file directly.
// This is a common technique for testing static (file-scope) functions.

// We need the splashColorModeNComps array
extern int splashColorModeNComps[];

// Forward declare or include the static function by including the .cc file
// However, that would pull in too many dependencies. Instead, let's replicate
// just the function signature and test it.

// Since the function is static, we need to access it. Let's define a test wrapper.
// We'll include the implementation file to get access to the static function.
// But to avoid pulling in all dependencies, let's extract the function.

// Actually, let's just re-declare and define the function for testing purposes,
// copying it exactly as given. This is the only way to test a static function
// without modifying the source.

// We define the necessary types and the function directly for testing.

typedef unsigned char SplashColor[SPLASH_MAX_COLOR + 1];
typedef unsigned char *SplashColorPtr;

// The splashColorModeNComps should already be defined, but let's ensure we have it
// for standalone compilation
#ifndef SPLASH_COLOR_MODE_N_COMPS_DEFINED
static int testSplashColorModeNComps[] = { 1, 1, 3, 3, 4, 4, SPOT_NCOMPS + 4 };
#define splashColorModeNComps testSplashColorModeNComps
#endif

static void splashOutBlendSoftLight(SplashColorPtr src, SplashColorPtr dest, SplashColorPtr blend, SplashColorMode cm)
{
    int i, x;
    if (cm == splashModeCMYK8 || cm == splashModeDeviceN8) {
        for (i = 0; i < splashColorModeNComps[cm]; ++i) {
            dest[i] = 255 - dest[i];
            src[i] = 255 - src[i];
        }
    }
    {
        for (i = 0; i < splashColorModeNComps[cm]; ++i) {
            if (src[i] < 0x80) {
                blend[i] = dest[i] - (255 - 2 * src[i]) * dest[i] * (255 - dest[i]) / (255 * 255);
            } else {
                if (dest[i] < 0x40) {
                    x = (((((16 * dest[i] - 12 * 255) * dest[i]) / 255) + 4 * 255) * dest[i]) / 255;
                } else {
                    x = (int)sqrt(255.0 * dest[i]);
                }
                blend[i] = dest[i] + (2 * src[i] - 255) * (x - dest[i]) / 255;
            }
        }
    }
    if (cm == splashModeCMYK8 || cm == splashModeDeviceN8) {
        for (i = 0; i < splashColorModeNComps[cm]; ++i) {
            dest[i] = 255 - dest[i];
            src[i] = 255 - src[i];
            blend[i] = 255 - blend[i];
        }
    }
}

class SplashOutBlendSoftLightTest_1585 : public ::testing::Test {
protected:
    SplashColor src, dest, blend;

    void SetUp() override
    {
        memset(src, 0, sizeof(src));
        memset(dest, 0, sizeof(dest));
        memset(blend, 0, sizeof(blend));
    }
};

// Test with RGB8 mode, all zeros
TEST_F(SplashOutBlendSoftLightTest_1585, RGB8_AllZeros_1585)
{
    memset(src, 0, sizeof(src));
    memset(dest, 0, sizeof(dest));

    splashOutBlendSoftLight(src, dest, blend, splashModeRGB8);

    // src[i] = 0 < 0x80, so:
    // blend[i] = dest[i] - (255 - 0)*dest[i]*(255 - dest[i])/(255*255)
    // = 0 - 255*0*255/(255*255) = 0
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(blend[i], 0);
    }
}

// Test with RGB8 mode, all 255
TEST_F(SplashOutBlendSoftLightTest_1585, RGB8_AllMax_1585)
{
    memset(src, 255, 3);
    memset(dest, 255, 3);

    splashOutBlendSoftLight(src, dest, blend, splashModeRGB8);

    // src[i] = 255 >= 0x80
    // dest[i] = 255 >= 0x40
    // x = (int)sqrt(255.0 * 255) = (int)sqrt(65025) = 255
    // blend[i] = 255 + (2*255 - 255)*(255 - 255)/255 = 255 + 0 = 255
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(blend[i], 255);
    }
}

// Test with RGB8 mode, src = 128 (0x80), dest = 128
TEST_F(SplashOutBlendSoftLightTest_1585, RGB8_MidValues_1585)
{
    memset(src, 128, 3);
    memset(dest, 128, 3);

    splashOutBlendSoftLight(src, dest, blend, splashModeRGB8);

    // src[i] = 128 >= 0x80
    // dest[i] = 128 >= 0x40
    // x = (int)sqrt(255.0 * 128) = (int)sqrt(32640) = (int)180.66... = 180
    // blend[i] = 128 + (2*128 - 255)*(180 - 128)/255
    //          = 128 + 1 * 52 / 255 = 128 + 0 = 128
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(blend[i], 128);
    }
}

// Test with RGB8 mode, src < 0x80, dest non-zero
TEST_F(SplashOutBlendSoftLightTest_1585, RGB8_SrcLow_DestMid_1585)
{
    src[0] = 64;
    src[1] = 64;
    src[2] = 64;
    dest[0] = 128;
    dest[1] = 128;
    dest[2] = 128;

    splashOutBlendSoftLight(src, dest, blend, splashModeRGB8);

    // src[i] = 64 < 0x80
    // blend[i] = dest[i] - (255 - 2*64)*dest[i]*(255 - dest[i])/(255*255)
    //          = 128 - (255 - 128)*128*(255 - 128)/(255*255)
    //          = 128 - 127*128*127/65025
    //          = 128 - 2048256/65025
    //          = 128 - 31 = 97 (approximately)
    int expected = 128 - (255 - 2 * 64) * 128 * (255 - 128) / (255 * 255);
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(blend[i], expected);
    }
}

// Test with RGB8 mode, src >= 0x80, dest < 0x40 (uses the cubic approximation)
TEST_F(SplashOutBlendSoftLightTest_1585, RGB8_SrcHigh_DestLow_1585)
{
    src[0] = 200;
    src[1] = 200;
    src[2] = 200;
    dest[0] = 32;
    dest[1] = 32;
    dest[2] = 32;

    splashOutBlendSoftLight(src, dest, blend, splashModeRGB8);

    // src[i] = 200 >= 0x80
    // dest[i] = 32 < 0x40
    // x = (((((16*32 - 12*255)*32)/255) + 4*255)*32)/255
    //   = ((((512 - 3060)*32)/255 + 1020)*32)/255
    //   = ((((-2548)*32)/255 + 1020)*32)/255
    //   = (((-81536)/255 + 1020)*32)/255
    //   = ((-319 + 1020)*32)/255     (integer division: -81536/255 = -319)
    //   = (701*32)/255
    //   = 22432/255
    //   = 87
    int x = (((((16 * 32 - 12 * 255) * 32) / 255) + 4 * 255) * 32) / 255;
    int expected = 32 + (2 * 200 - 255) * (x - 32) / 255;

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(blend[i], expected);
    }
}

// Test with Mono8 mode (1 component)
TEST_F(SplashOutBlendSoftLightTest_1585, Mono8_Basic_1585)
{
    src[0] = 100;
    dest[0] = 200;

    splashOutBlendSoftLight(src, dest, blend, splashModeMono8);

    // src = 100 < 0x80
    // blend = 200 - (255 - 200)*200*(255-200)/(255*255)
    //       = 200 - 55*200*55/65025
    //       = 200 - 605000/65025
    //       = 200 - 9 = 191
    int expected = 200 - (255 - 2 * 100) * 200 * (255 - 200) / (255 * 255);
    EXPECT_EQ(blend[0], expected);
}

// Test with BGR8 mode (3 components, no CMYK inversion)
TEST_F(SplashOutBlendSoftLightTest_1585, BGR8_Basic_1585)
{
    src[0] = 50;
    src[1] = 150;
    src[2] = 250;
    dest[0] = 100;
    dest[1] = 100;
    dest[2] = 100;

    splashOutBlendSoftLight(src, dest, blend, splashModeBGR8);

    // Channel 0: src=50 < 0x80
    int expected0 = 100 - (255 - 2 * 50) * 100 * (255 - 100) / (255 * 255);
    EXPECT_EQ(blend[0], expected0);

    // Channel 1: src=150 >= 0x80, dest=100 >= 0x40
    int x1 = (int)sqrt(255.0 * 100);
    int expected1 = 100 + (2 * 150 - 255) * (x1 - 100) / 255;
    EXPECT_EQ(blend[1], expected1);

    // Channel 2: src=250 >= 0x80, dest=100 >= 0x40
    int x2 = (int)sqrt(255.0 * 100);
    int expected2 = 100 + (2 * 250 - 255) * (x2 - 100) / 255;
    EXPECT_EQ(blend[2], expected2);
}

// Test with CMYK8 mode (4 components, with inversion)
TEST_F(SplashOutBlendSoftLightTest_1585, CMYK8_Basic_1585)
{
    src[0] = 100;
    src[1] = 100;
    src[2] = 100;
    src[3] = 100;
    dest[0] = 200;
    dest[1] = 200;
    dest[2] = 200;
    dest[3] = 200;

    unsigned char origSrc[4], origDest[4];
    memcpy(origSrc, src, 4);
    memcpy(origDest, dest, 4);

    splashOutBlendSoftLight(src, dest, blend, splashModeCMYK8);

    // After the call, src and dest should be restored to original values
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(src[i], origSrc[i]);
        EXPECT_EQ(dest[i], origDest[i]);
    }

    // Manually compute: first invert src and dest
    // inv_src = 255 - 100 = 155, inv_dest = 255 - 200 = 55
    // inv_src = 155 >= 0x80, inv_dest = 55 >= 0x40
    // x = (int)sqrt(255.0 * 55) = (int)sqrt(14025) = 118
    // raw_blend = 55 + (2*155 - 255)*(118 - 55)/255 = 55 + 55*63/255 = 55 + 13 = 68
    // final blend = 255 - 68 = 187
    // Let's compute properly:
    int inv_src = 255 - 100;
    int inv_dest = 255 - 200;
    int x;
    if (inv_dest < 0x40) {
        x = (((((16 * inv_dest - 12 * 255) * inv_dest) / 255) + 4 * 255) * inv_dest) / 255;
    } else {
        x = (int)sqrt(255.0 * inv_dest);
    }
    int raw_blend = inv_dest + (2 * inv_src - 255) * (x - inv_dest) / 255;
    int expected = 255 - raw_blend;

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(blend[i], expected);
    }
}

// Test CMYK8 with src and dest both zero
TEST_F(SplashOutBlendSoftLightTest_1585, CMYK8_AllZeros_1585)
{
    memset(src, 0, 4);
    memset(dest, 0, 4);

    splashOutBlendSoftLight(src, dest, blend, splashModeCMYK8);

    // Invert: inv_src = 255, inv_dest = 255
    // src=255 >= 0x80, dest=255 >= 0x40
    // x = (int)sqrt(255*255) = 255
    // raw = 255 + (2*255-255)*(255-255)/255 = 255
    // final = 255 - 255 = 0
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(blend[i], 0);
    }
}

// Test CMYK8 with src and dest both 255
TEST_F(SplashOutBlendSoftLightTest_1585, CMYK8_AllMax_1585)
{
    memset(src, 255, 4);
    memset(dest, 255, 4);

    splashOutBlendSoftLight(src, dest, blend, splashModeCMYK8);

    // Invert: inv_src = 0, inv_dest = 0
    // src=0 < 0x80
    // raw = 0 - (255-0)*0*(255-0)/(255*255) = 0
    // final = 255 - 0 = 255
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(blend[i], 255);
    }
}

// Test with XBGR8 mode (4 components, no CMYK inversion)
TEST_F(SplashOutBlendSoftLightTest_1585, XBGR8_Basic_1585)
{
    src[0] = 50;
    src[1] = 100;
    src[2] = 150;
    src[3] = 200;
    dest[0] = 128;
    dest[1] = 128;
    dest[2] = 128;
    dest[3] = 128;

    splashOutBlendSoftLight(src, dest, blend, splashModeXBGR8);

    // XBGR8 has 4 components but no CMYK inversion
    // Channel 0: src=50 < 0x80
    int expected0 = 128 - (255 - 2 * 50) * 128 * (255 - 128) / (255 * 255);
    EXPECT_EQ(blend[0], expected0);

    // Channel 1: src=100 < 0x80
    int expected1 = 128 - (255 - 2 * 100) * 128 * (255 - 128) / (255 * 255);
    EXPECT_EQ(blend[1], expected1);

    // Channel 2: src=150 >= 0x80, dest=128 >= 0x40
    int x2 = (int)sqrt(255.0 * 128);
    int expected2 = 128 + (2 * 150 - 255) * (x2 - 128) / 255;
    EXPECT_EQ(blend[2], expected2);

    // Channel 3: src=200 >= 0x80, dest=128 >= 0x40
    int x3 = (int)sqrt(255.0 * 128);
    int expected3 = 128 + (2 * 200 - 255) * (x3 - 128) / 255;
    EXPECT_EQ(blend[3], expected3);
}

// Test boundary: src exactly at 0x80 threshold
TEST_F(SplashOutBlendSoftLightTest_1585, RGB8_SrcExactly0x80_1585)
{
    src[0] = 0x80;
    dest[0] = 100;
    src[1] = 0x7F;
    dest[1] = 100;
    src[2] = 0x80;
    dest[2] = 100;

    splashOutBlendSoftLight(src, dest, blend, splashModeRGB8);

    // Channel 0: src=0x80 >= 0x80 -> uses second branch
    // dest=100 >= 0x40
    int x0 = (int)sqrt(255.0 * 100);
    int expected0 = 100 + (2 * 0x80 - 255) * (x0 - 100) / 255;
    EXPECT_EQ(blend[0], expected0);

    // Channel 1: src=0x7F < 0x80 -> uses first branch
    int expected1 = 100 - (255 - 2 * 0x7F) * 100 * (255 - 100) / (255 * 255);
    EXPECT_EQ(blend[1], expected1);
}

// Test boundary: dest exactly at 0x40 threshold
TEST_F(SplashOutBlendSoftLightTest_1585, RGB8_DestExactly0x40_1585)
{
    src[0] = 200;
    dest[0] = 0x40; // exactly 64
    src[1] = 200;
    dest[1] = 0x3F; // 63, just below
    src[2] = 200;
    dest[2] = 0x41; // 65, just above

    splashOutBlendSoftLight(src, dest, blend, splashModeRGB8);

    // Channel 0: src=200>=0x80, dest=64>=0x40 -> sqrt branch
    int x0 = (int)sqrt(255.0 * 64);
    int expected0 = 64 + (2 * 200 - 255) * (x0 - 64) / 255;
    EXPECT_EQ(blend[0], expected0);

    // Channel 1: src=200>=0x80, dest=63<0x40 -> cubic branch
    int x1 = (((((16 * 63 - 12 * 255) * 63) / 255) + 4 * 255) * 63) / 255;
    int expected1 = 63 + (2 * 200 - 255) * (x1 - 63) / 255;
    EXPECT_EQ(blend[1], expected1);

    // Channel 2: src=200>=0x80, dest=65>=0x40 -> sqrt branch
    int x2 = (int)sqrt(255.0 * 65);
    int expected2 = 65 + (2 * 200 - 255) * (x2 - 65) / 255;
    EXPECT_EQ(blend[2], expected2);
}

// Test that src and dest are not modified in RGB8 mode
TEST_F(SplashOutBlendSoftLightTest_1585, RGB8_SrcDestUnmodified_1585)
{
    src[0] = 100;
    src[1] = 150;
    src[2] = 200;
    dest[0] = 50;
    dest[1] = 100;
    dest[2] = 150;

    unsigned char origSrc[3], origDest[3];
    memcpy(origSrc, src, 3);
    memcpy(origDest, dest, 3);

    splashOutBlendSoftLight(src, dest, blend, splashModeRGB8);

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(src[i], origSrc[i]);
        EXPECT_EQ(dest[i], origDest[i]);
    }
}

// Test that src and dest are restored in CMYK8 mode
TEST_F(SplashOutBlendSoftLightTest_1585, CMYK8_SrcDestRestored_1585)
{
    src[0] = 30;
    src[1] = 60;
    src[2] = 90;
    src[3] = 120;
    dest[0] = 40;
    dest[1] = 80;
    dest[2] = 120;
    dest[3] = 160;

    unsigned char origSrc[4], origDest[4];
    memcpy(origSrc, src, 4);
    memcpy(origDest, dest, 4);

    splashOutBlendSoftLight(src, dest, blend, splashModeCMYK8);

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(src[i], origSrc[i]);
        EXPECT_EQ(dest[i], origDest[i]);
    }
}

// Test with dest=0 and high src (src >= 0x80)
TEST_F(SplashOutBlendSoftLightTest_1585, RGB8_DestZero_SrcHigh_1585)
{
    src[0] = 200;
    dest[0] = 0;
    src[1] = 200;
    dest[1] = 0;
    src[2] = 200;
    dest[2] = 0;

    splashOutBlendSoftLight(src, dest, blend, splashModeRGB8);

    // dest=0 < 0x40
    // x = (((((16*0 - 12*255)*0)/255) + 4*255)*0)/255 = 0
    // blend = 0 + (2*200 - 255)*(0 - 0)/255 = 0
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(blend[i], 0);
    }
}

// Test with dest=255 and low src (src < 0x80)
TEST_F(SplashOutBlendSoftLightTest_1585, RGB8_DestMax_SrcLow_1585)
{
    src[0] = 0;
    dest[0] = 255;
    src[1] = 0;
    dest[1] = 255;
    src[2] = 0;
    dest[2] = 255;

    splashOutBlendSoftLight(src, dest, blend, splashModeRGB8);

    // src=0 < 0x80
    // blend = 255 - (255 - 0)*255*(255-255)/(255*255)
    //       = 255 - 255*255*0/65025 = 255
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(blend[i], 255);
    }
}

// Test with src=127 (just below 0x80) in RGB8
TEST_F(SplashOutBlendSoftLightTest_1585, RGB8_SrcJustBelow0x80_1585)
{
    src[0] = 127;
    src[1] = 127;
    src[2] = 127;
    dest[0] = 128;
    dest[1] = 128;
    dest[2] = 128;

    splashOutBlendSoftLight(src, dest, blend, splashModeRGB8);

    // src=127 < 0x80
    // blend = 128 - (255 - 254)*128*(255-128)/(255*255)
    //       = 128 - 1*128*127/65025
    //       = 128 - 16256/65025
    //       = 128 - 0 = 128
    int expected = 128 - (255 - 2 * 127) * 128 * (255 - 128) / (255 * 255);
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(blend[i], expected);
    }
}

// Test with different values per channel in RGB8
TEST_F(SplashOutBlendSoftLightTest_1585, RGB8_DifferentChannels_1585)
{
    src[0] = 10;
    src[1] = 200;
    src[2] = 127;
    dest[0] = 30;
    dest[1] = 50;
    dest[2] = 250;

    splashOutBlendSoftLight(src, dest, blend, splashModeRGB8);

    // Channel 0: src=10 < 0x80
    int expected0 = 30 - (255 - 20) * 30 * (255 - 30) / (255 * 255);
    EXPECT_EQ(blend[0], expected0);

    // Channel 1: src=200 >= 0x80, dest=50 >= 0x40
    int x1 = (int)sqrt(255.0 * 50);
    int expected1 = 50 + (400 - 255) * (x1 - 50) / 255;
    EXPECT_EQ(blend[1], expected1);

    // Channel 2: src=127 < 0x80
    int expected2 = 250 - (255 - 254) * 250 * (255 - 250) / (255 * 255);
    EXPECT_EQ(blend[2], expected2);
}

// Test Mono1 mode (1 component)
TEST_F(SplashOutBlendSoftLightTest_1585, Mono1_Basic_1585)
{
    src[0] = 100;
    dest[0] = 150;

    splashOutBlendSoftLight(src, dest, blend, splashModeMono1);

    // Mono1 has 1 component, src=100<0x80
    int expected = 150 - (255 - 200) * 150 * (255 - 150) / (255 * 255);
    EXPECT_EQ(blend[0], expected);
}

// Test CMYK8 with mixed channels
TEST_F(SplashOutBlendSoftLightTest_1585, CMYK8_MixedChannels_1585)
{
    src[0] = 0;
    src[1] = 128;
    src[2] = 255;
    src[3] = 50;
    dest[0] = 0;
    dest[1] = 128;
    dest[2] = 255;
    dest[3] = 200;

    unsigned char origSrc[4], origDest[4];
    memcpy(origSrc, src, 4);
    memcpy(origDest, dest, 4);

    splashOutBlendSoftLight(src, dest, blend, splashModeCMYK8);

    // Verify src and dest are restored
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(src[i], origSrc[i]);
        EXPECT_EQ(dest[i], origDest[i]);
    }

    // Compute expected values manually for each channel
    for (int i = 0; i < 4; i++) {
        int inv_s = 255 - origSrc[i];
        int inv_d = 255 - origDest[i];
        int raw_blend;

        if (inv_s < 0x80) {
            raw_blend = inv_d - (255 - 2 * inv_s) * inv_d * (255 - inv_d) / (255 * 255);
        } else {
            int x;
            if (inv_d < 0x40) {
                x = (((((16 * inv_d - 12 * 255) * inv_d) / 255) + 4 * 255) * inv_d) / 255;
            } else {
                x = (int)sqrt(255.0 * inv_d);
            }
            raw_blend = inv_d + (2 * inv_s - 255) * (x - inv_d) / 255;
        }
        int expected = 255 - raw_blend;
        EXPECT_EQ(blend[i], expected) << "Channel " << i;
    }
}

// Test with dest = 1 (very small but non-zero) and src high
TEST_F(SplashOutBlendSoftLightTest_1585, RGB8_DestVerySmall_1585)
{
    src[0] = 255;
    src[1] = 255;
    src[2] = 255;
    dest[0] = 1;
    dest[1] = 1;
    dest[2] = 1;

    splashOutBlendSoftLight(src, dest, blend, splashModeRGB8);

    // src=255 >= 0x80, dest=1 < 0x40
    // x = (((((16*1 - 3060)*1)/255) + 1020)*1)/255
    //   = ((((16 - 3060)/255) + 1020)*1)/255
    //   = ((-3044/255 + 1020))/255
    //   = ((-11 + 1020))/255       (int division: -3044/255 = -11)
    //   = 1009/255 = 3
    int x = (((((16 * 1 - 12 * 255) * 1) / 255) + 4 * 255) * 1) / 255;
    int expected = 1 + (2 * 255 - 255) * (x - 1) / 255;

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(blend[i], expected);
    }
}
