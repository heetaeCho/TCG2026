#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

// We need to declare the function under test since it's static in the .cc file.
// We'll include it or redefine the signature for testing purposes.
// Since the function is static, we need to either include the .cc file or
// use a workaround. We'll include the .cc to get access to the static function.

// Forward declarations of types we need
typedef unsigned char SplashColor[SPLASH_MAX_COLOR > 0 ? SPLASH_MAX_COLOR : 8];
typedef unsigned char *SplashColorPtr;

// Include the source file to get access to the static function
// This is necessary because the function is declared static
#include "poppler/SplashOutputDev.cc"

class SplashOutBlendHardLightTest_1584 : public ::testing::Test {
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

// Test RGB8 mode with src < 0x80 (multiply branch)
TEST_F(SplashOutBlendHardLightTest_1584, RGB8_SrcLessThan0x80_Multiply_1584) {
    src[0] = 64;   // < 0x80
    src[1] = 64;
    src[2] = 64;
    dest[0] = 128;
    dest[1] = 128;
    dest[2] = 128;

    splashOutBlendHardLight(src, dest, blend, splashModeRGB8);

    for (int i = 0; i < 3; ++i) {
        int expected = (dest[i] * 2 * src[i]) / 255;
        EXPECT_EQ(blend[i], (unsigned char)expected) << "Component " << i;
    }
}

// Test RGB8 mode with src >= 0x80 (screen branch)
TEST_F(SplashOutBlendHardLightTest_1584, RGB8_SrcGreaterOrEqual0x80_Screen_1584) {
    src[0] = 200;  // >= 0x80
    src[1] = 200;
    src[2] = 200;
    dest[0] = 100;
    dest[1] = 100;
    dest[2] = 100;

    splashOutBlendHardLight(src, dest, blend, splashModeRGB8);

    for (int i = 0; i < 3; ++i) {
        int expected = 255 - 2 * ((255 - dest[i]) * (255 - src[i])) / 255;
        EXPECT_EQ(blend[i], (unsigned char)expected) << "Component " << i;
    }
}

// Test RGB8 with src exactly at boundary 0x80
TEST_F(SplashOutBlendHardLightTest_1584, RGB8_SrcExactly0x80_1584) {
    src[0] = 0x80;
    src[1] = 0x80;
    src[2] = 0x80;
    dest[0] = 128;
    dest[1] = 128;
    dest[2] = 128;

    splashOutBlendHardLight(src, dest, blend, splashModeRGB8);

    for (int i = 0; i < 3; ++i) {
        // src[i] >= 0x80, so screen branch
        int expected = 255 - 2 * ((255 - 128) * (255 - 128)) / 255;
        EXPECT_EQ(blend[i], (unsigned char)expected) << "Component " << i;
    }
}

// Test RGB8 with all zeros
TEST_F(SplashOutBlendHardLightTest_1584, RGB8_AllZeros_1584) {
    memset(src, 0, sizeof(SplashColor));
    memset(dest, 0, sizeof(SplashColor));

    splashOutBlendHardLight(src, dest, blend, splashModeRGB8);

    for (int i = 0; i < 3; ++i) {
        // src < 0x80, so (0 * 2 * 0) / 255 = 0
        EXPECT_EQ(blend[i], 0) << "Component " << i;
    }
}

// Test RGB8 with all 255
TEST_F(SplashOutBlendHardLightTest_1584, RGB8_AllMax_1584) {
    memset(src, 255, sizeof(SplashColor));
    memset(dest, 255, sizeof(SplashColor));

    splashOutBlendHardLight(src, dest, blend, splashModeRGB8);

    for (int i = 0; i < 3; ++i) {
        // src >= 0x80, so 255 - 2 * (0 * 0) / 255 = 255
        EXPECT_EQ(blend[i], 255) << "Component " << i;
    }
}

// Test RGB8 src=0, dest=255
TEST_F(SplashOutBlendHardLightTest_1584, RGB8_SrcZero_DestMax_1584) {
    memset(src, 0, sizeof(SplashColor));
    memset(dest, 255, sizeof(SplashColor));

    splashOutBlendHardLight(src, dest, blend, splashModeRGB8);

    for (int i = 0; i < 3; ++i) {
        // src < 0x80, (255 * 2 * 0) / 255 = 0
        EXPECT_EQ(blend[i], 0) << "Component " << i;
    }
}

// Test RGB8 src=255, dest=0
TEST_F(SplashOutBlendHardLightTest_1584, RGB8_SrcMax_DestZero_1584) {
    memset(src, 255, sizeof(SplashColor));
    memset(dest, 0, sizeof(SplashColor));

    splashOutBlendHardLight(src, dest, blend, splashModeRGB8);

    for (int i = 0; i < 3; ++i) {
        // src >= 0x80, 255 - 2*(255*0)/255 = 255
        EXPECT_EQ(blend[i], 255) << "Component " << i;
    }
}

// Test Mono8 mode
TEST_F(SplashOutBlendHardLightTest_1584, Mono8_Normal_1584) {
    src[0] = 100;
    dest[0] = 150;

    splashOutBlendHardLight(src, dest, blend, splashModeMono8);

    // src < 0x80: (150 * 2 * 100) / 255
    int expected = (150 * 2 * 100) / 255;
    EXPECT_EQ(blend[0], (unsigned char)expected);
}

// Test CMYK8 mode - involves inversion of src and dest before and after
TEST_F(SplashOutBlendHardLightTest_1584, CMYK8_Normal_1584) {
    src[0] = 50;
    src[1] = 100;
    src[2] = 150;
    src[3] = 200;
    dest[0] = 30;
    dest[1] = 60;
    dest[2] = 90;
    dest[3] = 120;

    // Save original values to verify src and dest are restored
    unsigned char origSrc[4] = {50, 100, 150, 200};
    unsigned char origDest[4] = {30, 60, 90, 120};

    splashOutBlendHardLight(src, dest, blend, splashModeCMYK8);

    // Verify src and dest are restored to original values
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(src[i], origSrc[i]) << "src component " << i << " should be restored";
        EXPECT_EQ(dest[i], origDest[i]) << "dest component " << i << " should be restored";
    }

    // Verify blend computation for CMYK8:
    // Step 1: invert src and dest
    // Step 2: compute blend as normal HardLight
    // Step 3: invert back src, dest, blend
    for (int i = 0; i < 4; ++i) {
        unsigned char invSrc = 255 - origSrc[i];
        unsigned char invDest = 255 - origDest[i];
        int b;
        if (invSrc < 0x80) {
            b = (invDest * 2 * invSrc) / 255;
        } else {
            b = 255 - 2 * ((255 - invDest) * (255 - invSrc)) / 255;
        }
        int expected = 255 - b;
        EXPECT_EQ(blend[i], (unsigned char)expected) << "CMYK8 blend component " << i;
    }
}

// Test BGR8 mode (same number of components as RGB8)
TEST_F(SplashOutBlendHardLightTest_1584, BGR8_Normal_1584) {
    src[0] = 40;
    src[1] = 180;
    src[2] = 127;
    dest[0] = 200;
    dest[1] = 50;
    dest[2] = 100;

    splashOutBlendHardLight(src, dest, blend, splashModeBGR8);

    // Component 0: src < 0x80, multiply
    EXPECT_EQ(blend[0], (unsigned char)((200 * 2 * 40) / 255));
    // Component 1: src >= 0x80, screen
    EXPECT_EQ(blend[1], (unsigned char)(255 - 2 * ((255 - 50) * (255 - 180)) / 255));
    // Component 2: src = 127 < 0x80, multiply
    EXPECT_EQ(blend[2], (unsigned char)((100 * 2 * 127) / 255));
}

// Test XBGR8 mode (4 components)
TEST_F(SplashOutBlendHardLightTest_1584, XBGR8_Normal_1584) {
    src[0] = 10;
    src[1] = 200;
    src[2] = 128;
    src[3] = 50;
    dest[0] = 240;
    dest[1] = 30;
    dest[2] = 100;
    dest[3] = 200;

    splashOutBlendHardLight(src, dest, blend, splashModeXBGR8);

    // 4 components for XBGR8
    // Component 0: src=10 < 0x80
    EXPECT_EQ(blend[0], (unsigned char)((240 * 2 * 10) / 255));
    // Component 1: src=200 >= 0x80
    EXPECT_EQ(blend[1], (unsigned char)(255 - 2 * ((255 - 30) * (255 - 200)) / 255));
    // Component 2: src=128 >= 0x80
    EXPECT_EQ(blend[2], (unsigned char)(255 - 2 * ((255 - 100) * (255 - 128)) / 255));
    // Component 3: src=50 < 0x80
    EXPECT_EQ(blend[3], (unsigned char)((200 * 2 * 50) / 255));
}

// Test mixed components - some < 0x80, some >= 0x80
TEST_F(SplashOutBlendHardLightTest_1584, RGB8_MixedComponents_1584) {
    src[0] = 0x7F;  // < 0x80 (multiply)
    src[1] = 0x80;  // >= 0x80 (screen)
    src[2] = 0x00;  // < 0x80 (multiply)
    dest[0] = 200;
    dest[1] = 200;
    dest[2] = 200;

    splashOutBlendHardLight(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], (unsigned char)((200 * 2 * 0x7F) / 255));
    EXPECT_EQ(blend[1], (unsigned char)(255 - 2 * ((255 - 200) * (255 - 0x80)) / 255));
    EXPECT_EQ(blend[2], (unsigned char)((200 * 2 * 0) / 255));
}

// Test CMYK8 all zeros
TEST_F(SplashOutBlendHardLightTest_1584, CMYK8_AllZeros_1584) {
    memset(src, 0, sizeof(SplashColor));
    memset(dest, 0, sizeof(SplashColor));

    splashOutBlendHardLight(src, dest, blend, splashModeCMYK8);

    // After inversion: src=255, dest=255 for each component
    // 255 >= 0x80, so screen: 255 - 2*(0*0)/255 = 255
    // Then invert blend: 255 - 255 = 0
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(blend[i], 0) << "CMYK8 all-zero component " << i;
    }
}

// Test CMYK8 all 255
TEST_F(SplashOutBlendHardLightTest_1584, CMYK8_AllMax_1584) {
    memset(src, 255, sizeof(SplashColor));
    memset(dest, 255, sizeof(SplashColor));

    splashOutBlendHardLight(src, dest, blend, splashModeCMYK8);

    // After inversion: src=0, dest=0
    // 0 < 0x80, multiply: (0*2*0)/255 = 0
    // Then invert blend: 255 - 0 = 255
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(blend[i], 255) << "CMYK8 all-max component " << i;
    }
}

// Test that src and dest are not modified for RGB8 mode
TEST_F(SplashOutBlendHardLightTest_1584, RGB8_SrcDestUnmodified_1584) {
    src[0] = 100;
    src[1] = 200;
    src[2] = 50;
    dest[0] = 150;
    dest[1] = 75;
    dest[2] = 225;

    unsigned char origSrc[3] = {100, 200, 50};
    unsigned char origDest[3] = {150, 75, 225};

    splashOutBlendHardLight(src, dest, blend, splashModeRGB8);

    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(src[i], origSrc[i]) << "src should not be modified for RGB8, component " << i;
        EXPECT_EQ(dest[i], origDest[i]) << "dest should not be modified for RGB8, component " << i;
    }
}

// Test Mono8 with src exactly 0x7F (just below boundary)
TEST_F(SplashOutBlendHardLightTest_1584, Mono8_SrcJustBelow0x80_1584) {
    src[0] = 0x7F;
    dest[0] = 200;

    splashOutBlendHardLight(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], (unsigned char)((200 * 2 * 0x7F) / 255));
}

// Test Mono8 with src = 1 (very small non-zero)
TEST_F(SplashOutBlendHardLightTest_1584, Mono8_SrcOne_1584) {
    src[0] = 1;
    dest[0] = 255;

    splashOutBlendHardLight(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], (unsigned char)((255 * 2 * 1) / 255));
}

// Test Mono8 with src = 254 (just below max)
TEST_F(SplashOutBlendHardLightTest_1584, Mono8_SrcNearMax_1584) {
    src[0] = 254;
    dest[0] = 254;

    splashOutBlendHardLight(src, dest, blend, splashModeMono8);

    // src >= 0x80: 255 - 2*(1*1)/255 = 255 - 0 = 255
    EXPECT_EQ(blend[0], (unsigned char)(255 - 2 * ((255 - 254) * (255 - 254)) / 255));
}
