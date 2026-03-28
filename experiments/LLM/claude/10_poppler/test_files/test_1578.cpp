#include <gtest/gtest.h>
#include "splash/SplashTypes.h"
#include <cstring>

// The function is static in SplashOutputDev.cc, so we include the source
// to get access to it for testing purposes.
// We need to declare it or include the file. Since it's static, we replicate
// the declaration and include the implementation file.

// Forward declare - we include the .cc to get the static function
// This is a common testing pattern for static functions.

// We need the splashColorModeNComps array
extern int splashColorModeNComps[];

// Declare the function signature for testing
static void splashOutBlendScreen(SplashColorPtr src, SplashColorPtr dest, SplashColorPtr blend, SplashColorMode cm);

// Include the implementation to get the static function
#include "poppler/SplashOutputDev.cc"

class SplashOutBlendScreenTest_1578 : public ::testing::Test {
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

// ============ RGB8 Mode Tests ============

TEST_F(SplashOutBlendScreenTest_1578, RGB8_BothZero_BlendIsZero_1578) {
    // Screen blend: blend = src + dest - src*dest/255
    // With both 0: blend = 0 + 0 - 0 = 0
    src[0] = 0; src[1] = 0; src[2] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;
    splashOutBlendScreen(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

TEST_F(SplashOutBlendScreenTest_1578, RGB8_BothMax_BlendIsMax_1578) {
    // Screen blend: 255 + 255 - (255*255)/255 = 255 + 255 - 255 = 255
    src[0] = 255; src[1] = 255; src[2] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 255;
    splashOutBlendScreen(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
}

TEST_F(SplashOutBlendScreenTest_1578, RGB8_SrcMaxDestZero_BlendIsMax_1578) {
    // Screen: 0 + 255 - (0*255)/255 = 255
    src[0] = 255; src[1] = 255; src[2] = 255;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;
    splashOutBlendScreen(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
}

TEST_F(SplashOutBlendScreenTest_1578, RGB8_SrcZeroDestMax_BlendIsMax_1578) {
    src[0] = 0; src[1] = 0; src[2] = 0;
    dest[0] = 255; dest[1] = 255; dest[2] = 255;
    splashOutBlendScreen(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
}

TEST_F(SplashOutBlendScreenTest_1578, RGB8_HalfValues_1578) {
    // Screen: 128 + 128 - (128*128)/255 = 256 - 64 = 192 (approx)
    // 128*128 = 16384, 16384/255 = 64 (integer division)
    // blend = 128 + 128 - 64 = 192
    src[0] = 128; src[1] = 128; src[2] = 128;
    dest[0] = 128; dest[1] = 128; dest[2] = 128;
    splashOutBlendScreen(src, dest, blend, splashModeRGB8);
    int expected = 128 + 128 - (128 * 128) / 255;
    EXPECT_EQ(blend[0], expected);
    EXPECT_EQ(blend[1], expected);
    EXPECT_EQ(blend[2], expected);
}

TEST_F(SplashOutBlendScreenTest_1578, RGB8_DifferentChannels_1578) {
    src[0] = 100; src[1] = 200; src[2] = 50;
    dest[0] = 150; dest[1] = 100; dest[2] = 200;
    splashOutBlendScreen(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(blend[0], 150 + 100 - (150 * 100) / 255);
    EXPECT_EQ(blend[1], 100 + 200 - (100 * 200) / 255);
    EXPECT_EQ(blend[2], 200 + 50 - (200 * 50) / 255);
}

TEST_F(SplashOutBlendScreenTest_1578, RGB8_SrcDoesNotChange_1578) {
    src[0] = 100; src[1] = 150; src[2] = 200;
    dest[0] = 50; dest[1] = 75; dest[2] = 100;
    SplashColor origSrc;
    memcpy(origSrc, src, sizeof(SplashColor));
    splashOutBlendScreen(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(src[0], origSrc[0]);
    EXPECT_EQ(src[1], origSrc[1]);
    EXPECT_EQ(src[2], origSrc[2]);
}

TEST_F(SplashOutBlendScreenTest_1578, RGB8_DestDoesNotChange_1578) {
    src[0] = 100; src[1] = 150; src[2] = 200;
    dest[0] = 50; dest[1] = 75; dest[2] = 100;
    SplashColor origDest;
    memcpy(origDest, dest, sizeof(SplashColor));
    splashOutBlendScreen(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(dest[0], origDest[0]);
    EXPECT_EQ(dest[1], origDest[1]);
    EXPECT_EQ(dest[2], origDest[2]);
}

// ============ Mono8 Mode Tests ============

TEST_F(SplashOutBlendScreenTest_1578, Mono8_BothZero_1578) {
    src[0] = 0;
    dest[0] = 0;
    splashOutBlendScreen(src, dest, blend, splashModeMono8);
    EXPECT_EQ(blend[0], 0);
}

TEST_F(SplashOutBlendScreenTest_1578, Mono8_BothMax_1578) {
    src[0] = 255;
    dest[0] = 255;
    splashOutBlendScreen(src, dest, blend, splashModeMono8);
    EXPECT_EQ(blend[0], 255);
}

TEST_F(SplashOutBlendScreenTest_1578, Mono8_MixedValues_1578) {
    src[0] = 100;
    dest[0] = 200;
    splashOutBlendScreen(src, dest, blend, splashModeMono8);
    EXPECT_EQ(blend[0], 200 + 100 - (200 * 100) / 255);
}

// ============ CMYK8 Mode Tests ============
// For CMYK8, src and dest are inverted before blending, then blend is inverted
// Effective formula for CMYK:
// invSrc = 255 - src, invDest = 255 - dest
// rawBlend = invDest + invSrc - (invDest * invSrc) / 255
// blend = 255 - rawBlend
// This simplifies to: blend = (dest * src) / 255

TEST_F(SplashOutBlendScreenTest_1578, CMYK8_BothZero_1578) {
    for (int i = 0; i < 4; i++) { src[i] = 0; dest[i] = 0; }
    splashOutBlendScreen(src, dest, blend, splashModeCMYK8);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(blend[i], (0 * 0) / 255);
    }
}

TEST_F(SplashOutBlendScreenTest_1578, CMYK8_BothMax_1578) {
    for (int i = 0; i < 4; i++) { src[i] = 255; dest[i] = 255; }
    splashOutBlendScreen(src, dest, blend, splashModeCMYK8);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(blend[i], 255);
    }
}

TEST_F(SplashOutBlendScreenTest_1578, CMYK8_MixedValues_1578) {
    src[0] = 100; src[1] = 200; src[2] = 50; src[3] = 150;
    dest[0] = 150; dest[1] = 100; dest[2] = 200; dest[3] = 50;
    splashOutBlendScreen(src, dest, blend, splashModeCMYK8);
    for (int i = 0; i < 4; i++) {
        int invSrc = 255 - src[i];
        int invDest = 255 - dest[i];
        int rawBlend = invDest + invSrc - (invDest * invSrc) / 255;
        int expected = 255 - rawBlend;
        EXPECT_EQ(blend[i], expected) << "Channel " << i;
    }
}

TEST_F(SplashOutBlendScreenTest_1578, CMYK8_SrcDestPreserved_1578) {
    src[0] = 100; src[1] = 200; src[2] = 50; src[3] = 150;
    dest[0] = 150; dest[1] = 100; dest[2] = 200; dest[3] = 50;
    SplashColor origSrc, origDest;
    memcpy(origSrc, src, sizeof(SplashColor));
    memcpy(origDest, dest, sizeof(SplashColor));
    splashOutBlendScreen(src, dest, blend, splashModeCMYK8);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(src[i], origSrc[i]) << "src channel " << i;
        EXPECT_EQ(dest[i], origDest[i]) << "dest channel " << i;
    }
}

TEST_F(SplashOutBlendScreenTest_1578, CMYK8_SrcZeroDestMax_1578) {
    for (int i = 0; i < 4; i++) { src[i] = 0; dest[i] = 255; }
    splashOutBlendScreen(src, dest, blend, splashModeCMYK8);
    // invSrc=255, invDest=0; rawBlend=0+255-(0*255)/255=255; blend=255-255=0
    // Wait: invSrc=255-0=255, invDest=255-255=0
    // rawBlend = 0 + 255 - (0*255)/255 = 255
    // blend = 255 - 255 = 0
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(blend[i], 0);
    }
}

TEST_F(SplashOutBlendScreenTest_1578, CMYK8_SrcMaxDestZero_1578) {
    for (int i = 0; i < 4; i++) { src[i] = 255; dest[i] = 0; }
    splashOutBlendScreen(src, dest, blend, splashModeCMYK8);
    // invSrc=0, invDest=255; rawBlend = 255+0-0=255; blend=255-255=0
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(blend[i], 0);
    }
}

// ============ BGR8 Mode Tests ============

TEST_F(SplashOutBlendScreenTest_1578, BGR8_MixedValues_1578) {
    src[0] = 50; src[1] = 100; src[2] = 200;
    dest[0] = 200; dest[1] = 150; dest[2] = 50;
    splashOutBlendScreen(src, dest, blend, splashModeBGR8);
    for (int i = 0; i < 3; i++) {
        int expected = dest[i] + src[i] - (dest[i] * src[i]) / 255;
        EXPECT_EQ(blend[i], expected) << "Channel " << i;
    }
}

// ============ XBGR8 Mode Tests ============

TEST_F(SplashOutBlendScreenTest_1578, XBGR8_MixedValues_1578) {
    src[0] = 50; src[1] = 100; src[2] = 200; src[3] = 128;
    dest[0] = 200; dest[1] = 150; dest[2] = 50; dest[3] = 64;
    splashOutBlendScreen(src, dest, blend, splashModeXBGR8);
    for (int i = 0; i < 4; i++) {
        int expected = dest[i] + src[i] - (dest[i] * src[i]) / 255;
        EXPECT_EQ(blend[i], expected) << "Channel " << i;
    }
}

// ============ Mono1 Mode Tests ============

TEST_F(SplashOutBlendScreenTest_1578, Mono1_BothZero_1578) {
    src[0] = 0;
    dest[0] = 0;
    splashOutBlendScreen(src, dest, blend, splashModeMono1);
    EXPECT_EQ(blend[0], 0);
}

TEST_F(SplashOutBlendScreenTest_1578, Mono1_BothOne_1578) {
    // In mono1 mode, values are typically 0 or 1 but treated as byte
    src[0] = 1;
    dest[0] = 1;
    splashOutBlendScreen(src, dest, blend, splashModeMono1);
    // blend = 1 + 1 - (1*1)/255 = 2 - 0 = 2
    EXPECT_EQ(blend[0], 2);
}

TEST_F(SplashOutBlendScreenTest_1578, Mono1_SrcOneDestZero_1578) {
    src[0] = 1;
    dest[0] = 0;
    splashOutBlendScreen(src, dest, blend, splashModeMono1);
    // blend = 0 + 1 - 0 = 1
    EXPECT_EQ(blend[0], 1);
}

// ============ Boundary/Edge Tests ============

TEST_F(SplashOutBlendScreenTest_1578, RGB8_OneChannelMax_OthersZero_1578) {
    src[0] = 255; src[1] = 0; src[2] = 0;
    dest[0] = 0; dest[1] = 255; dest[2] = 0;
    splashOutBlendScreen(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(blend[0], 255); // 0 + 255 - 0 = 255
    EXPECT_EQ(blend[1], 255); // 255 + 0 - 0 = 255
    EXPECT_EQ(blend[2], 0);   // 0 + 0 - 0 = 0
}

TEST_F(SplashOutBlendScreenTest_1578, RGB8_SrcOneDestOne_1578) {
    src[0] = 1; src[1] = 1; src[2] = 1;
    dest[0] = 1; dest[1] = 1; dest[2] = 1;
    splashOutBlendScreen(src, dest, blend, splashModeRGB8);
    // blend = 1 + 1 - (1*1)/255 = 2 - 0 = 2
    EXPECT_EQ(blend[0], 2);
    EXPECT_EQ(blend[1], 2);
    EXPECT_EQ(blend[2], 2);
}

TEST_F(SplashOutBlendScreenTest_1578, RGB8_Src254Dest254_1578) {
    src[0] = 254; src[1] = 254; src[2] = 254;
    dest[0] = 254; dest[1] = 254; dest[2] = 254;
    splashOutBlendScreen(src, dest, blend, splashModeRGB8);
    // blend = 254 + 254 - (254*254)/255 = 508 - 64516/255 = 508 - 252 = 256
    // But blend is stored in unsigned char, so this might overflow.
    // Actually 64516/255 = 252 (integer), so 508-252 = 256
    // As SplashColorPtr is unsigned char, 256 wraps to 0
    // Let's just verify the computation
    int raw = 254 + 254 - (254 * 254) / 255;
    EXPECT_EQ(blend[0], (unsigned char)raw);
}

TEST_F(SplashOutBlendScreenTest_1578, CMYK8_HalfValues_1578) {
    for (int i = 0; i < 4; i++) { src[i] = 128; dest[i] = 128; }
    splashOutBlendScreen(src, dest, blend, splashModeCMYK8);
    int invSrc = 127; // 255 - 128
    int invDest = 127;
    int rawBlend = 127 + 127 - (127 * 127) / 255; // 254 - 63 = 191
    int expected = 255 - rawBlend; // 255 - 191 = 64
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(blend[i], expected) << "Channel " << i;
    }
}
