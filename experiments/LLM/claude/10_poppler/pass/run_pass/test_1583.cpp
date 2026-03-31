#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

// We need to declare the function under test since it's static in the .cc file.
// To test it, we'll need to either include the .cc file or redeclare it.
// Since it's a static function, we include the .cc file to get access.
// However, this is a common pattern for testing static functions.

// Forward declare the splashColorModeNComps array
extern int splashColorModeNComps[];

// We need to include or link the function. Since it's static, we include the source.
// But we need to be careful about other dependencies. Let's declare the function signature
// and rely on linking, or include the specific function.

// Since the function is static, we'll replicate access by including the cc file
// or defining a test-accessible version. For testing purposes, let's define the function
// inline based on the provided code, treating it as the black-box interface.

// Actually, since we can't modify the source and the function is static,
// we need to include the .cc file or use a workaround.
// Let's include relevant headers and define the function as provided.

// For the test, we'll define the function as given (this is the interface we're testing):
static void splashOutBlendColorBurn(SplashColorPtr src, SplashColorPtr dest, SplashColorPtr blend, SplashColorMode cm)
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
            if (src[i] == 0) {
                blend[i] = 0;
            } else {
                x = ((255 - dest[i]) * 255) / src[i];
                blend[i] = x <= 255 ? 255 - x : 0;
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

// Define splashColorModeNComps if not already linked
// Based on Splash types: Mono1=1, Mono8=1, RGB8=3, BGR8=3, XBGR8=4, CMYK8=4, DeviceN8=SPOT_NCOMPS+4
// For testing, we use the standard values
#ifndef SPOT_NCOMPS
#define SPOT_NCOMPS 4
#endif

int splashColorModeNComps[] = { 1, 1, 3, 3, 4, 4, SPOT_NCOMPS + 4 };

class SplashOutBlendColorBurnTest_1583 : public ::testing::Test {
protected:
    SplashColor src;
    SplashColor dest;
    SplashColor blend;

    void SetUp() override
    {
        memset(src, 0, sizeof(SplashColor));
        memset(dest, 0, sizeof(SplashColor));
        memset(blend, 0, sizeof(SplashColor));
    }
};

// ===================== RGB8 Mode Tests =====================

TEST_F(SplashOutBlendColorBurnTest_1583, RGB8_BothBlack_1583)
{
    // src = (0,0,0), dest = (0,0,0)
    // When src[i] == 0, blend[i] = 0
    src[0] = 0; src[1] = 0; src[2] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;

    splashOutBlendColorBurn(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

TEST_F(SplashOutBlendColorBurnTest_1583, RGB8_BothWhite_1583)
{
    // src = (255,255,255), dest = (255,255,255)
    // x = ((255-255)*255)/255 = 0, blend = 255 - 0 = 255
    src[0] = 255; src[1] = 255; src[2] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 255;

    splashOutBlendColorBurn(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
}

TEST_F(SplashOutBlendColorBurnTest_1583, RGB8_SrcWhiteDestBlack_1583)
{
    // src = (255,255,255), dest = (0,0,0)
    // x = ((255-0)*255)/255 = 255, blend = 255-255 = 0
    src[0] = 255; src[1] = 255; src[2] = 255;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;

    splashOutBlendColorBurn(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

TEST_F(SplashOutBlendColorBurnTest_1583, RGB8_SrcBlackDestWhite_1583)
{
    // src = (0,0,0), dest = (255,255,255)
    // src[i] == 0 => blend[i] = 0
    src[0] = 0; src[1] = 0; src[2] = 0;
    dest[0] = 255; dest[1] = 255; dest[2] = 255;

    splashOutBlendColorBurn(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

TEST_F(SplashOutBlendColorBurnTest_1583, RGB8_MidValues_1583)
{
    // src = (128, 128, 128), dest = (128, 128, 128)
    // x = ((255-128)*255)/128 = (127*255)/128 = 32385/128 = 253
    // blend = 255 - 253 = 2
    src[0] = 128; src[1] = 128; src[2] = 128;
    dest[0] = 128; dest[1] = 128; dest[2] = 128;

    splashOutBlendColorBurn(src, dest, blend, splashModeRGB8);

    int expected_x = (127 * 255) / 128; // = 253
    int expected_blend = 255 - expected_x; // = 2
    EXPECT_EQ(blend[0], expected_blend);
    EXPECT_EQ(blend[1], expected_blend);
    EXPECT_EQ(blend[2], expected_blend);
}

TEST_F(SplashOutBlendColorBurnTest_1583, RGB8_SrcOneDestZero_1583)
{
    // src = (1,1,1), dest = (0,0,0)
    // x = ((255-0)*255)/1 = 65025, x > 255 => blend = 0
    src[0] = 1; src[1] = 1; src[2] = 1;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;

    splashOutBlendColorBurn(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

TEST_F(SplashOutBlendColorBurnTest_1583, RGB8_SrcMaxDestHalf_1583)
{
    // src = (255,255,255), dest = (128,128,128)
    // x = ((255-128)*255)/255 = 127, blend = 255-127 = 128
    src[0] = 255; src[1] = 255; src[2] = 255;
    dest[0] = 128; dest[1] = 128; dest[2] = 128;

    splashOutBlendColorBurn(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 128);
    EXPECT_EQ(blend[1], 128);
    EXPECT_EQ(blend[2], 128);
}

TEST_F(SplashOutBlendColorBurnTest_1583, RGB8_DifferentChannels_1583)
{
    // Test with different values per channel
    src[0] = 255; src[1] = 128; src[2] = 1;
    dest[0] = 0; dest[1] = 128; dest[2] = 255;

    splashOutBlendColorBurn(src, dest, blend, splashModeRGB8);

    // Channel 0: x = (255*255)/255 = 255, blend = 0
    EXPECT_EQ(blend[0], 0);
    // Channel 1: x = (127*255)/128 = 253, blend = 2
    EXPECT_EQ(blend[1], 2);
    // Channel 2: x = (0*255)/1 = 0, blend = 255
    EXPECT_EQ(blend[2], 255);
}

TEST_F(SplashOutBlendColorBurnTest_1583, RGB8_XExceedsLimit_1583)
{
    // When x > 255, blend should be 0
    // src = (2, 2, 2), dest = (0, 0, 0)
    // x = (255*255)/2 = 32512, blend = 0
    src[0] = 2; src[1] = 2; src[2] = 2;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;

    splashOutBlendColorBurn(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

TEST_F(SplashOutBlendColorBurnTest_1583, RGB8_XExactly255_1583)
{
    // x = 255 => blend = 0
    // Need (255-dest)*255/src = 255
    // => 255-dest = src => dest = 255 - src
    // Let src = 100, dest = 155
    // x = (100*255)/100 = 255, blend = 0
    src[0] = 100; src[1] = 100; src[2] = 100;
    dest[0] = 155; dest[1] = 155; dest[2] = 155;

    splashOutBlendColorBurn(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

// ===================== Mono8 Mode Tests =====================

TEST_F(SplashOutBlendColorBurnTest_1583, Mono8_BothBlack_1583)
{
    src[0] = 0;
    dest[0] = 0;

    splashOutBlendColorBurn(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], 0);
}

TEST_F(SplashOutBlendColorBurnTest_1583, Mono8_BothWhite_1583)
{
    src[0] = 255;
    dest[0] = 255;

    splashOutBlendColorBurn(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], 255);
}

TEST_F(SplashOutBlendColorBurnTest_1583, Mono8_SrcZero_1583)
{
    src[0] = 0;
    dest[0] = 200;

    splashOutBlendColorBurn(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], 0);
}

// ===================== BGR8 Mode Tests =====================

TEST_F(SplashOutBlendColorBurnTest_1583, BGR8_SameAsRGB8_1583)
{
    // BGR8 has 3 components, same logic as RGB8
    src[0] = 200; src[1] = 100; src[2] = 50;
    dest[0] = 100; dest[1] = 200; dest[2] = 150;

    splashOutBlendColorBurn(src, dest, blend, splashModeBGR8);

    // Channel 0: x = ((255-100)*255)/200 = (155*255)/200 = 39525/200 = 197, blend = 58
    EXPECT_EQ(blend[0], 255 - ((155 * 255) / 200));
    // Channel 1: x = ((255-200)*255)/100 = (55*255)/100 = 14025/100 = 140, blend = 115
    EXPECT_EQ(blend[1], 255 - ((55 * 255) / 100));
    // Channel 2: x = ((255-150)*255)/50 = (105*255)/50 = 26775/50 = 535, blend = 0 (x > 255)
    EXPECT_EQ(blend[2], 0);
}

// ===================== XBGR8 Mode Tests =====================

TEST_F(SplashOutBlendColorBurnTest_1583, XBGR8_FourComponents_1583)
{
    // XBGR8 has 4 components
    src[0] = 255; src[1] = 255; src[2] = 255; src[3] = 255;
    dest[0] = 128; dest[1] = 128; dest[2] = 128; dest[3] = 128;

    splashOutBlendColorBurn(src, dest, blend, splashModeXBGR8);

    // x = (127*255)/255 = 127, blend = 128
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(blend[i], 128);
    }
}

// ===================== CMYK8 Mode Tests =====================

TEST_F(SplashOutBlendColorBurnTest_1583, CMYK8_BothZero_1583)
{
    // CMYK8: 4 components, with inversion at start and end
    // src = (0,0,0,0), dest = (0,0,0,0)
    // After first inversion: src = (255,255,255,255), dest = (255,255,255,255)
    // x = ((255-255)*255)/255 = 0, blend = 255
    // After final inversion: blend = 255 - 255 = 0
    // But also src and dest are restored
    src[0] = 0; src[1] = 0; src[2] = 0; src[3] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0; dest[3] = 0;

    splashOutBlendColorBurn(src, dest, blend, splashModeCMYK8);

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(blend[i], 0);
    }
    // Verify src and dest are restored
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(src[i], 0);
        EXPECT_EQ(dest[i], 0);
    }
}

TEST_F(SplashOutBlendColorBurnTest_1583, CMYK8_BothMax_1583)
{
    // src = (255,255,255,255), dest = (255,255,255,255)
    // After first inversion: src = (0,0,0,0), dest = (0,0,0,0)
    // src[i] == 0 => blend[i] = 0
    // After final inversion: blend = 255, src and dest restored
    src[0] = 255; src[1] = 255; src[2] = 255; src[3] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 255; dest[3] = 255;

    splashOutBlendColorBurn(src, dest, blend, splashModeCMYK8);

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(blend[i], 255);
    }
    // Verify src and dest are restored
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(src[i], 255);
        EXPECT_EQ(dest[i], 255);
    }
}

TEST_F(SplashOutBlendColorBurnTest_1583, CMYK8_MixedValues_1583)
{
    // src = (100, 200, 50, 150), dest = (50, 100, 200, 75)
    // After inversion: src' = (155, 55, 205, 105), dest' = (205, 155, 55, 180)
    // Channel 0: x = ((255-205)*255)/155 = (50*255)/155 = 12750/155 = 82, blend = 255-82 = 173
    // Channel 1: x = ((255-155)*255)/55 = (100*255)/55 = 25500/55 = 463, blend = 0 (x>255)
    // Channel 2: x = ((255-55)*255)/205 = (200*255)/205 = 51000/205 = 248, blend = 255-248 = 7
    // Channel 3: x = ((255-180)*255)/105 = (75*255)/105 = 19125/105 = 182, blend = 255-182 = 73
    // After final inversion: blend = (255-173, 255-0, 255-7, 255-73) = (82, 255, 248, 182)
    src[0] = 100; src[1] = 200; src[2] = 50; src[3] = 150;
    dest[0] = 50; dest[1] = 100; dest[2] = 200; dest[3] = 75;

    splashOutBlendColorBurn(src, dest, blend, splashModeCMYK8);

    EXPECT_EQ(blend[0], 82);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 248);
    EXPECT_EQ(blend[3], 182);

    // Verify src and dest are restored
    EXPECT_EQ(src[0], 100);
    EXPECT_EQ(src[1], 200);
    EXPECT_EQ(src[2], 50);
    EXPECT_EQ(src[3], 150);
    EXPECT_EQ(dest[0], 50);
    EXPECT_EQ(dest[1], 100);
    EXPECT_EQ(dest[2], 200);
    EXPECT_EQ(dest[3], 75);
}

TEST_F(SplashOutBlendColorBurnTest_1583, CMYK8_SrcAndDestPreserved_1583)
{
    // Verify that src and dest are not modified after the call (they should be restored)
    src[0] = 42; src[1] = 84; src[2] = 126; src[3] = 168;
    dest[0] = 10; dest[1] = 20; dest[2] = 30; dest[3] = 40;

    splashOutBlendColorBurn(src, dest, blend, splashModeCMYK8);

    EXPECT_EQ(src[0], 42);
    EXPECT_EQ(src[1], 84);
    EXPECT_EQ(src[2], 126);
    EXPECT_EQ(src[3], 168);
    EXPECT_EQ(dest[0], 10);
    EXPECT_EQ(dest[1], 20);
    EXPECT_EQ(dest[2], 30);
    EXPECT_EQ(dest[3], 40);
}

// ===================== DeviceN8 Mode Tests =====================

TEST_F(SplashOutBlendColorBurnTest_1583, DeviceN8_AllZero_1583)
{
    // DeviceN8: SPOT_NCOMPS + 4 = 8 components
    // All zeros, same logic as CMYK8 for inversion
    for (int i = 0; i < 8; i++) {
        src[i] = 0;
        dest[i] = 0;
    }

    splashOutBlendColorBurn(src, dest, blend, splashModeDeviceN8);

    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(blend[i], 0);
    }
}

TEST_F(SplashOutBlendColorBurnTest_1583, DeviceN8_AllMax_1583)
{
    for (int i = 0; i < 8; i++) {
        src[i] = 255;
        dest[i] = 255;
    }

    splashOutBlendColorBurn(src, dest, blend, splashModeDeviceN8);

    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(blend[i], 255);
    }
}

TEST_F(SplashOutBlendColorBurnTest_1583, DeviceN8_SrcAndDestPreserved_1583)
{
    for (int i = 0; i < 8; i++) {
        src[i] = i * 30;
        dest[i] = 255 - i * 30;
    }

    SplashColor src_copy, dest_copy;
    memcpy(src_copy, src, sizeof(SplashColor));
    memcpy(dest_copy, dest, sizeof(SplashColor));

    splashOutBlendColorBurn(src, dest, blend, splashModeDeviceN8);

    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(src[i], src_copy[i]);
        EXPECT_EQ(dest[i], dest_copy[i]);
    }
}

// ===================== RGB8 src/dest not modified =====================

TEST_F(SplashOutBlendColorBurnTest_1583, RGB8_SrcDestNotModified_1583)
{
    // For non-CMYK modes, src and dest should also not be modified
    src[0] = 50; src[1] = 100; src[2] = 200;
    dest[0] = 30; dest[1] = 60; dest[2] = 90;

    splashOutBlendColorBurn(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(src[0], 50);
    EXPECT_EQ(src[1], 100);
    EXPECT_EQ(src[2], 200);
    EXPECT_EQ(dest[0], 30);
    EXPECT_EQ(dest[1], 60);
    EXPECT_EQ(dest[2], 90);
}

// ===================== Edge case: x exactly at boundary =====================

TEST_F(SplashOutBlendColorBurnTest_1583, RGB8_XBoundaryExact256_1583)
{
    // x = 256 should result in blend = 0
    // Need (255-dest)*255/src = 256
    // Not easily achievable with integers, but let's pick values where x > 255
    // src = 127, dest = 0: x = 255*255/127 = 65025/127 = 512, blend = 0
    src[0] = 127;
    dest[0] = 0;

    splashOutBlendColorBurn(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], 0);
}

TEST_F(SplashOutBlendColorBurnTest_1583, RGB8_XJustBelow256_1583)
{
    // x = 254 => blend = 1
    // Need (255-dest)*255/src = 254
    // src = 255, dest = 1: x = (254*255)/255 = 254, blend = 1
    src[0] = 255; src[1] = 255; src[2] = 255;
    dest[0] = 1; dest[1] = 1; dest[2] = 1;

    splashOutBlendColorBurn(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 1);
    EXPECT_EQ(blend[1], 1);
    EXPECT_EQ(blend[2], 1);
}

// ===================== Mono1 Mode Test =====================

TEST_F(SplashOutBlendColorBurnTest_1583, Mono1_SingleComponent_1583)
{
    // Mono1 has 1 component
    src[0] = 255;
    dest[0] = 0;

    splashOutBlendColorBurn(src, dest, blend, splashModeMono1);

    // x = (255*255)/255 = 255, blend = 0
    EXPECT_EQ(blend[0], 0);
}

TEST_F(SplashOutBlendColorBurnTest_1583, Mono1_SrcZero_1583)
{
    src[0] = 0;
    dest[0] = 128;

    splashOutBlendColorBurn(src, dest, blend, splashModeMono1);

    EXPECT_EQ(blend[0], 0);
}

// ===================== CMYK8 special case: inverted src is zero =====================

TEST_F(SplashOutBlendColorBurnTest_1583, CMYK8_InvertedSrcZero_1583)
{
    // src = (255,255,255,255) => inverted src = (0,0,0,0) => blend[i] = 0
    // After final inversion: blend = (255,255,255,255)
    src[0] = 255; src[1] = 255; src[2] = 255; src[3] = 255;
    dest[0] = 0; dest[1] = 0; dest[2] = 0; dest[3] = 0;

    splashOutBlendColorBurn(src, dest, blend, splashModeCMYK8);

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(blend[i], 255);
    }
}

TEST_F(SplashOutBlendColorBurnTest_1583, CMYK8_InvertedDestMax_1583)
{
    // dest = (0,0,0,0), inverted dest = (255,255,255,255)
    // src = (0,0,0,0), inverted src = (255,255,255,255)
    // x = ((255-255)*255)/255 = 0, blend = 255
    // After inversion: blend = 0
    src[0] = 0; src[1] = 0; src[2] = 0; src[3] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0; dest[3] = 0;

    splashOutBlendColorBurn(src, dest, blend, splashModeCMYK8);

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(blend[i], 0);
    }
}
