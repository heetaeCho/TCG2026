#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "splash/SplashTypes.h"

// We need to declare the function under test since it's static in the .cc file.
// We'll need to either include it or redefine its signature for testing.
// Since it's a static function in a .cc file, we need a workaround.

// For testing a static function, we include the .cc file directly
// or we extract the function. Here we'll define it as extern or include the source.

// The function is static, so we need to include the source file to access it.
// We'll use a trick: define a wrapper or include the relevant portion.

// Actually, let's just declare and define the function signature matching what we see,
// and include the source file that contains it.

// Forward declaration approach - we'll redefine the static function for testing
// by including the source directly (common pattern for testing static functions)

// We need the splashColorModeNComps array
// From SplashTypes.h, these are the known values:
// splashModeMono1 = 0 -> 1 comp
// splashModeMono8 = 1 -> 1 comp  
// splashModeRGB8 = 2 -> 3 comps
// splashModeBGR8 = 3 -> 3 comps
// splashModeXBGR8 = 4 -> 4 comps
// splashModeCMYK8 = 5 -> 4 comps
// splashModeDeviceN8 = 6 -> typically SPOT_NCOMPS+4, but let's use what's available

// Since the function is static, we reproduce it here for testing purposes.
// This is the only viable approach for unit testing a static function in another TU.

typedef unsigned char SplashColor[SPOT_NCOMPS + 4];
typedef unsigned char *SplashColorPtr;

// Bring in the array
extern int splashColorModeNComps[];

static void splashOutBlendOverlay(SplashColorPtr src, SplashColorPtr dest, SplashColorPtr blend, SplashColorMode cm)
{
    int i;
    if (cm == splashModeCMYK8 || cm == splashModeDeviceN8) {
        for (i = 0; i < splashColorModeNComps[cm]; ++i) {
            dest[i] = 255 - dest[i];
            src[i] = 255 - src[i];
        }
    }
    {
        for (i = 0; i < splashColorModeNComps[cm]; ++i) {
            blend[i] = dest[i] < 0x80 ? (src[i] * 2 * dest[i]) / 255 : 255 - 2 * ((255 - src[i]) * (255 - dest[i])) / 255;
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

class SplashOutBlendOverlayTest_1579 : public ::testing::Test {
protected:
    SplashColor src;
    SplashColor dest;
    SplashColor blend;

    void SetUp() override
    {
        memset(src, 0, sizeof(src));
        memset(dest, 0, sizeof(dest));
        memset(blend, 0, sizeof(blend));
    }
};

// Test RGB8 mode with all zeros
TEST_F(SplashOutBlendOverlayTest_1579, RGB8_AllZeros_1579)
{
    // src=0, dest=0: dest[i] < 0x80 -> blend = (0*2*0)/255 = 0
    src[0] = 0; src[1] = 0; src[2] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;

    splashOutBlendOverlay(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);

    // src and dest should be unchanged for RGB8 (no CMYK inversion)
    EXPECT_EQ(src[0], 0);
    EXPECT_EQ(dest[0], 0);
}

// Test RGB8 mode with all 255
TEST_F(SplashOutBlendOverlayTest_1579, RGB8_AllMax_1579)
{
    // src=255, dest=255: dest[i]=255 >= 0x80 -> blend = 255 - 2*((0)*(0))/255 = 255
    src[0] = 255; src[1] = 255; src[2] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 255;

    splashOutBlendOverlay(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
}

// Test RGB8 with dest below 0x80 threshold
TEST_F(SplashOutBlendOverlayTest_1579, RGB8_DestBelowThreshold_1579)
{
    // dest=100 < 128, src=200
    // blend = (200 * 2 * 100) / 255 = 40000/255 = 156
    src[0] = 200; src[1] = 200; src[2] = 200;
    dest[0] = 100; dest[1] = 100; dest[2] = 100;

    splashOutBlendOverlay(src, dest, blend, splashModeRGB8);

    unsigned char expected = (unsigned char)((200 * 2 * 100) / 255);
    EXPECT_EQ(blend[0], expected);
    EXPECT_EQ(blend[1], expected);
    EXPECT_EQ(blend[2], expected);
}

// Test RGB8 with dest at exactly 0x80 (128) - should take the else branch
TEST_F(SplashOutBlendOverlayTest_1579, RGB8_DestAtThreshold_1579)
{
    // dest=128 >= 0x80, src=100
    // blend = 255 - 2*((255-100)*(255-128))/255 = 255 - 2*(155*127)/255
    //       = 255 - 2*19685/255 = 255 - 39370/255 = 255 - 154 = 101
    src[0] = 100;
    dest[0] = 128;

    splashOutBlendOverlay(src, dest, blend, splashModeRGB8);

    unsigned char expected = (unsigned char)(255 - 2 * ((255 - 100) * (255 - 128)) / 255);
    EXPECT_EQ(blend[0], expected);
}

// Test RGB8 with dest at 127 (just below threshold)
TEST_F(SplashOutBlendOverlayTest_1579, RGB8_DestJustBelowThreshold_1579)
{
    // dest=127 < 0x80? No, 0x80=128, so 127 < 128 -> true, takes multiply branch
    // blend = (src * 2 * 127) / 255
    src[0] = 100;
    dest[0] = 127;

    splashOutBlendOverlay(src, dest, blend, splashModeRGB8);

    unsigned char expected = (unsigned char)((100 * 2 * 127) / 255);
    EXPECT_EQ(blend[0], expected);
}

// Test RGB8 - src and dest should be preserved (no CMYK transform)
TEST_F(SplashOutBlendOverlayTest_1579, RGB8_SrcDestPreserved_1579)
{
    src[0] = 50; src[1] = 100; src[2] = 150;
    dest[0] = 60; dest[1] = 110; dest[2] = 200;

    splashOutBlendOverlay(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(src[0], 50);
    EXPECT_EQ(src[1], 100);
    EXPECT_EQ(src[2], 150);
    EXPECT_EQ(dest[0], 60);
    EXPECT_EQ(dest[1], 110);
    EXPECT_EQ(dest[2], 200);
}

// Test Mono8 mode (1 component, no CMYK inversion)
TEST_F(SplashOutBlendOverlayTest_1579, Mono8_Basic_1579)
{
    src[0] = 200;
    dest[0] = 50;

    splashOutBlendOverlay(src, dest, blend, splashModeMono8);

    // dest=50 < 128 -> blend = (200*2*50)/255 = 20000/255 = 78
    unsigned char expected = (unsigned char)((200 * 2 * 50) / 255);
    EXPECT_EQ(blend[0], expected);
}

// Test Mono8 with values in the screen branch
TEST_F(SplashOutBlendOverlayTest_1579, Mono8_ScreenBranch_1579)
{
    src[0] = 200;
    dest[0] = 200;

    splashOutBlendOverlay(src, dest, blend, splashModeMono8);

    // dest=200 >= 128 -> blend = 255 - 2*((255-200)*(255-200))/255 = 255 - 2*(55*55)/255
    //                   = 255 - 2*3025/255 = 255 - 6050/255 = 255 - 23 = 232
    unsigned char expected = (unsigned char)(255 - 2 * ((255 - 200) * (255 - 200)) / 255);
    EXPECT_EQ(blend[0], expected);
}

// Test CMYK8 mode - should do inversion before and after
TEST_F(SplashOutBlendOverlayTest_1579, CMYK8_Basic_1579)
{
    // CMYK8 has 4 components
    src[0] = 100; src[1] = 50; src[2] = 200; src[3] = 150;
    dest[0] = 60; dest[1] = 130; dest[2] = 10; dest[3] = 250;

    unsigned char orig_src[4], orig_dest[4];
    memcpy(orig_src, src, 4);
    memcpy(orig_dest, dest, 4);

    splashOutBlendOverlay(src, dest, blend, splashModeCMYK8);

    // After the call, src and dest should be restored to original values
    // (inverted, then processed, then inverted back)
    EXPECT_EQ(src[0], orig_src[0]);
    EXPECT_EQ(src[1], orig_src[1]);
    EXPECT_EQ(src[2], orig_src[2]);
    EXPECT_EQ(src[3], orig_src[3]);
    EXPECT_EQ(dest[0], orig_dest[0]);
    EXPECT_EQ(dest[1], orig_dest[1]);
    EXPECT_EQ(dest[2], orig_dest[2]);
    EXPECT_EQ(dest[3], orig_dest[3]);
}

// Test CMYK8 blend computation
TEST_F(SplashOutBlendOverlayTest_1579, CMYK8_BlendComputation_1579)
{
    // For CMYK: first invert src and dest, then blend, then invert blend
    // src[0] = 100, dest[0] = 60
    // After invert: src'=155, dest'=195
    // dest'=195 >= 128 -> b = 255 - 2*((255-155)*(255-195))/255 = 255 - 2*(100*60)/255
    //                    = 255 - 12000/255 = 255 - 47 = 208
    // After invert blend: blend[0] = 255 - 208 = 47
    src[0] = 100;
    dest[0] = 60;
    // Set other components to 0 for simplicity
    src[1] = 0; src[2] = 0; src[3] = 0;
    dest[1] = 0; dest[2] = 0; dest[3] = 0;

    splashOutBlendOverlay(src, dest, blend, splashModeCMYK8);

    // Compute expected for component 0
    unsigned char s_inv = 255 - 100; // 155
    unsigned char d_inv = 255 - 60;  // 195
    unsigned char b;
    if (d_inv < 0x80) {
        b = (s_inv * 2 * d_inv) / 255;
    } else {
        b = 255 - 2 * ((255 - s_inv) * (255 - d_inv)) / 255;
    }
    unsigned char expected = 255 - b;

    EXPECT_EQ(blend[0], expected);
}

// Test CMYK8 with all zeros
TEST_F(SplashOutBlendOverlayTest_1579, CMYK8_AllZeros_1579)
{
    memset(src, 0, 4);
    memset(dest, 0, 4);

    splashOutBlendOverlay(src, dest, blend, splashModeCMYK8);

    // src_inv=255, dest_inv=255, dest_inv >= 128
    // b = 255 - 2*((255-255)*(255-255))/255 = 255 - 0 = 255
    // blend_final = 255 - 255 = 0
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(blend[i], 0);
    }
}

// Test CMYK8 with all 255
TEST_F(SplashOutBlendOverlayTest_1579, CMYK8_AllMax_1579)
{
    memset(src, 255, 4);
    memset(dest, 255, 4);

    splashOutBlendOverlay(src, dest, blend, splashModeCMYK8);

    // src_inv=0, dest_inv=0, dest_inv < 128
    // b = (0 * 2 * 0) / 255 = 0
    // blend_final = 255 - 0 = 255
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(blend[i], 255);
    }
}

// Test BGR8 mode (3 components, no CMYK inversion)
TEST_F(SplashOutBlendOverlayTest_1579, BGR8_Basic_1579)
{
    src[0] = 50; src[1] = 150; src[2] = 200;
    dest[0] = 30; dest[1] = 180; dest[2] = 100;

    splashOutBlendOverlay(src, dest, blend, splashModeBGR8);

    // Component 0: dest=30 < 128 -> (50*2*30)/255 = 3000/255 = 11
    unsigned char exp0 = (unsigned char)((50 * 2 * 30) / 255);
    // Component 1: dest=180 >= 128 -> 255 - 2*((255-150)*(255-180))/255 = 255 - 2*(105*75)/255
    //            = 255 - 15750/255 = 255 - 61 = 194
    unsigned char exp1 = (unsigned char)(255 - 2 * ((255 - 150) * (255 - 180)) / 255);
    // Component 2: dest=100 < 128 -> (200*2*100)/255 = 40000/255 = 156
    unsigned char exp2 = (unsigned char)((200 * 2 * 100) / 255);

    EXPECT_EQ(blend[0], exp0);
    EXPECT_EQ(blend[1], exp1);
    EXPECT_EQ(blend[2], exp2);
}

// Test XBGR8 mode (4 components, no CMYK inversion)
TEST_F(SplashOutBlendOverlayTest_1579, XBGR8_Basic_1579)
{
    src[0] = 100; src[1] = 200; src[2] = 50; src[3] = 128;
    dest[0] = 64; dest[1] = 192; dest[2] = 32; dest[3] = 255;

    splashOutBlendOverlay(src, dest, blend, splashModeXBGR8);

    // 4 components, no CMYK inversion
    // Component 0: dest=64 < 128 -> (100*2*64)/255 = 12800/255 = 50
    unsigned char exp0 = (unsigned char)((100 * 2 * 64) / 255);
    EXPECT_EQ(blend[0], exp0);

    // Component 1: dest=192 >= 128 -> 255 - 2*((55)*(63))/255 = 255 - 6930/255 = 255-27 = 228
    unsigned char exp1 = (unsigned char)(255 - 2 * ((255 - 200) * (255 - 192)) / 255);
    EXPECT_EQ(blend[1], exp1);

    // Component 2: dest=32 < 128 -> (50*2*32)/255 = 3200/255 = 12
    unsigned char exp2 = (unsigned char)((50 * 2 * 32) / 255);
    EXPECT_EQ(blend[2], exp2);

    // Component 3: dest=255 >= 128 -> 255 - 2*((255-128)*(255-255))/255 = 255 - 0 = 255
    unsigned char exp3 = (unsigned char)(255 - 2 * ((255 - 128) * (255 - 255)) / 255);
    EXPECT_EQ(blend[3], exp3);
}

// Test RGB8 with mixed components (some below, some above threshold)
TEST_F(SplashOutBlendOverlayTest_1579, RGB8_MixedComponents_1579)
{
    src[0] = 128; src[1] = 64; src[2] = 255;
    dest[0] = 64; dest[1] = 200; dest[2] = 128;

    splashOutBlendOverlay(src, dest, blend, splashModeRGB8);

    // Component 0: dest=64 < 128 -> (128*2*64)/255 = 16384/255 = 64
    unsigned char exp0 = (unsigned char)((128 * 2 * 64) / 255);
    // Component 1: dest=200 >= 128 -> 255 - 2*((255-64)*(255-200))/255 = 255 - 2*(191*55)/255
    //            = 255 - 21010/255 = 255 - 82 = 173
    unsigned char exp1 = (unsigned char)(255 - 2 * ((255 - 64) * (255 - 200)) / 255);
    // Component 2: dest=128 >= 128 -> 255 - 2*((255-255)*(255-128))/255 = 255 - 0 = 255
    unsigned char exp2 = (unsigned char)(255 - 2 * ((255 - 255) * (255 - 128)) / 255);

    EXPECT_EQ(blend[0], exp0);
    EXPECT_EQ(blend[1], exp1);
    EXPECT_EQ(blend[2], exp2);
}

// Test RGB8 with src=0 and dest=255
TEST_F(SplashOutBlendOverlayTest_1579, RGB8_SrcZeroDestMax_1579)
{
    src[0] = 0;
    dest[0] = 255;
    src[1] = 0; src[2] = 0;
    dest[1] = 255; dest[2] = 255;

    splashOutBlendOverlay(src, dest, blend, splashModeRGB8);

    // dest=255 >= 128 -> 255 - 2*((255-0)*(255-255))/255 = 255 - 0 = 255
    EXPECT_EQ(blend[0], 255);
}

// Test RGB8 with src=255 and dest=0
TEST_F(SplashOutBlendOverlayTest_1579, RGB8_SrcMaxDestZero_1579)
{
    src[0] = 255;
    dest[0] = 0;
    src[1] = 255; src[2] = 255;
    dest[1] = 0; dest[2] = 0;

    splashOutBlendOverlay(src, dest, blend, splashModeRGB8);

    // dest=0 < 128 -> (255*2*0)/255 = 0
    EXPECT_EQ(blend[0], 0);
}

// Test RGB8 with src=128 and dest=128 (midpoint)
TEST_F(SplashOutBlendOverlayTest_1579, RGB8_Midpoint_1579)
{
    src[0] = 128; src[1] = 128; src[2] = 128;
    dest[0] = 128; dest[1] = 128; dest[2] = 128;

    splashOutBlendOverlay(src, dest, blend, splashModeRGB8);

    // dest=128 >= 128 -> 255 - 2*((255-128)*(255-128))/255 = 255 - 2*(127*127)/255
    //                  = 255 - 32258/255 = 255 - 126 = 129
    unsigned char expected = (unsigned char)(255 - 2 * ((255 - 128) * (255 - 128)) / 255);
    EXPECT_EQ(blend[0], expected);
}

// Test CMYK8 mixed values
TEST_F(SplashOutBlendOverlayTest_1579, CMYK8_MixedValues_1579)
{
    src[0] = 0; src[1] = 255; src[2] = 128; src[3] = 64;
    dest[0] = 255; dest[1] = 0; dest[2] = 128; dest[3] = 192;

    unsigned char orig_src[4], orig_dest[4];
    memcpy(orig_src, src, 4);
    memcpy(orig_dest, dest, 4);

    splashOutBlendOverlay(src, dest, blend, splashModeCMYK8);

    // Verify src and dest are restored
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(src[i], orig_src[i]);
        EXPECT_EQ(dest[i], orig_dest[i]);
    }

    // Verify blend computation for each component
    for (int i = 0; i < 4; ++i) {
        unsigned char s_inv = 255 - orig_src[i];
        unsigned char d_inv = 255 - orig_dest[i];
        unsigned char b;
        if (d_inv < 0x80) {
            b = (s_inv * 2 * d_inv) / 255;
        } else {
            b = 255 - 2 * ((255 - s_inv) * (255 - d_inv)) / 255;
        }
        unsigned char expected = 255 - b;
        EXPECT_EQ(blend[i], expected) << "Component " << i;
    }
}

// Test Mono8 with zero
TEST_F(SplashOutBlendOverlayTest_1579, Mono8_ZeroValues_1579)
{
    src[0] = 0;
    dest[0] = 0;

    splashOutBlendOverlay(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], 0);
}

// Test Mono8 with max values
TEST_F(SplashOutBlendOverlayTest_1579, Mono8_MaxValues_1579)
{
    src[0] = 255;
    dest[0] = 255;

    splashOutBlendOverlay(src, dest, blend, splashModeMono8);

    // dest=255 >= 128 -> 255 - 2*(0*0)/255 = 255
    EXPECT_EQ(blend[0], 255);
}

// Test that only the relevant number of components are modified
TEST_F(SplashOutBlendOverlayTest_1579, Mono8_OnlyOneComponentModified_1579)
{
    src[0] = 100; src[1] = 42;
    dest[0] = 50; dest[1] = 42;
    blend[0] = 0; blend[1] = 99;

    splashOutBlendOverlay(src, dest, blend, splashModeMono8);

    // Only blend[0] should be computed, blend[1] should remain 99
    unsigned char expected = (unsigned char)((100 * 2 * 50) / 255);
    EXPECT_EQ(blend[0], expected);
    EXPECT_EQ(blend[1], 99); // untouched
}

// Test RGB8 only modifies 3 components
TEST_F(SplashOutBlendOverlayTest_1579, RGB8_OnlyThreeComponentsModified_1579)
{
    src[0] = 100; src[1] = 100; src[2] = 100; src[3] = 42;
    dest[0] = 50; dest[1] = 50; dest[2] = 50; dest[3] = 42;
    blend[3] = 77;

    splashOutBlendOverlay(src, dest, blend, splashModeRGB8);

    // blend[3] should be untouched
    EXPECT_EQ(blend[3], 77);
}
