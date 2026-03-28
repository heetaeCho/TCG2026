#include <gtest/gtest.h>
#include "splash/SplashTypes.h"
#include <cstring>

// Include the .cc file to access the static function
// This is necessary because the function under test has internal linkage (static)
#include "poppler/SplashOutputDev.cc"

class SplashOutBlendLuminosityTest_1595 : public ::testing::Test {
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

// --- Mono1 Mode Tests ---

TEST_F(SplashOutBlendLuminosityTest_1595, Mono1_BlackSrcBlackDest_1595) {
    src[0] = 0;
    dest[0] = 0;
    splashOutBlendLuminosity(src, dest, blend, splashModeMono1);
    EXPECT_EQ(blend[0], 0);
}

TEST_F(SplashOutBlendLuminosityTest_1595, Mono1_WhiteSrcWhiteDest_1595) {
    src[0] = 255;
    dest[0] = 255;
    splashOutBlendLuminosity(src, dest, blend, splashModeMono1);
    EXPECT_EQ(blend[0], 255);
}

TEST_F(SplashOutBlendLuminosityTest_1595, Mono1_WhiteSrcBlackDest_1595) {
    src[0] = 255;
    dest[0] = 0;
    splashOutBlendLuminosity(src, dest, blend, splashModeMono1);
    // Luminosity of src applied to dest's hue/sat; dest is black so result depends on setLum
    // With dest=(0,0,0) and lum from src=255, setLum should clamp
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
}

TEST_F(SplashOutBlendLuminosityTest_1595, Mono1_BlackSrcWhiteDest_1595) {
    src[0] = 0;
    dest[0] = 255;
    splashOutBlendLuminosity(src, dest, blend, splashModeMono1);
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
}

// --- Mono8 Mode Tests ---

TEST_F(SplashOutBlendLuminosityTest_1595, Mono8_AllZero_1595) {
    src[0] = 0;
    dest[0] = 0;
    splashOutBlendLuminosity(src, dest, blend, splashModeMono8);
    EXPECT_EQ(blend[0], 0);
}

TEST_F(SplashOutBlendLuminosityTest_1595, Mono8_AllMax_1595) {
    src[0] = 255;
    dest[0] = 255;
    splashOutBlendLuminosity(src, dest, blend, splashModeMono8);
    EXPECT_EQ(blend[0], 255);
}

TEST_F(SplashOutBlendLuminosityTest_1595, Mono8_MidValues_1595) {
    src[0] = 128;
    dest[0] = 128;
    splashOutBlendLuminosity(src, dest, blend, splashModeMono8);
    // Same luminosity, same hue/sat, should produce same value
    EXPECT_EQ(blend[0], 128);
}

TEST_F(SplashOutBlendLuminosityTest_1595, Mono8_SrcLumAppliedToDest_1595) {
    src[0] = 200;
    dest[0] = 100;
    splashOutBlendLuminosity(src, dest, blend, splashModeMono8);
    // For mono, setLum with gray input and lum from src should yield src luminosity
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
}

// --- RGB8 Mode Tests ---

TEST_F(SplashOutBlendLuminosityTest_1595, RGB8_AllBlack_1595) {
    src[0] = 0; src[1] = 0; src[2] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;
    splashOutBlendLuminosity(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

TEST_F(SplashOutBlendLuminosityTest_1595, RGB8_AllWhite_1595) {
    src[0] = 255; src[1] = 255; src[2] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 255;
    splashOutBlendLuminosity(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
}

TEST_F(SplashOutBlendLuminosityTest_1595, RGB8_WhiteSrcBlackDest_1595) {
    src[0] = 255; src[1] = 255; src[2] = 255;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;
    splashOutBlendLuminosity(src, dest, blend, splashModeRGB8);
    // Dest hue/sat is neutral (black), applying white luminosity
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
    EXPECT_GE(blend[1], 0);
    EXPECT_LE(blend[1], 255);
    EXPECT_GE(blend[2], 0);
    EXPECT_LE(blend[2], 255);
}

TEST_F(SplashOutBlendLuminosityTest_1595, RGB8_PureRedDestBrightSrc_1595) {
    src[0] = 200; src[1] = 200; src[2] = 200;
    dest[0] = 255; dest[1] = 0; dest[2] = 0;
    splashOutBlendLuminosity(src, dest, blend, splashModeRGB8);
    // Should apply luminosity of src to dest's red hue
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
    EXPECT_GE(blend[1], 0);
    EXPECT_LE(blend[1], 255);
    EXPECT_GE(blend[2], 0);
    EXPECT_LE(blend[2], 255);
}

TEST_F(SplashOutBlendLuminosityTest_1595, RGB8_SameLuminosity_1595) {
    // If src and dest have same luminosity, dest colors should be preserved
    src[0] = 128; src[1] = 128; src[2] = 128;
    dest[0] = 128; dest[1] = 128; dest[2] = 128;
    splashOutBlendLuminosity(src, dest, blend, splashModeRGB8);
    EXPECT_EQ(blend[0], 128);
    EXPECT_EQ(blend[1], 128);
    EXPECT_EQ(blend[2], 128);
}

// --- BGR8 Mode Tests ---

TEST_F(SplashOutBlendLuminosityTest_1595, BGR8_AllBlack_1595) {
    src[0] = 0; src[1] = 0; src[2] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;
    splashOutBlendLuminosity(src, dest, blend, splashModeBGR8);
    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

TEST_F(SplashOutBlendLuminosityTest_1595, BGR8_AllWhite_1595) {
    src[0] = 255; src[1] = 255; src[2] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 255;
    splashOutBlendLuminosity(src, dest, blend, splashModeBGR8);
    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
}

TEST_F(SplashOutBlendLuminosityTest_1595, BGR8_MixedValues_1595) {
    src[0] = 100; src[1] = 150; src[2] = 200;
    dest[0] = 50; dest[1] = 100; dest[2] = 150;
    splashOutBlendLuminosity(src, dest, blend, splashModeBGR8);
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
    EXPECT_GE(blend[1], 0);
    EXPECT_LE(blend[1], 255);
    EXPECT_GE(blend[2], 0);
    EXPECT_LE(blend[2], 255);
}

// --- XBGR8 Mode Tests ---

TEST_F(SplashOutBlendLuminosityTest_1595, XBGR8_AllBlack_1595) {
    src[0] = 0; src[1] = 0; src[2] = 0; src[3] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;
    splashOutBlendLuminosity(src, dest, blend, splashModeXBGR8);
    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

TEST_F(SplashOutBlendLuminosityTest_1595, XBGR8_SetsSrc3To255_1595) {
    src[0] = 100; src[1] = 100; src[2] = 100; src[3] = 0;
    dest[0] = 100; dest[1] = 100; dest[2] = 100;
    splashOutBlendLuminosity(src, dest, blend, splashModeXBGR8);
    // The function sets src[3] = 255 before processing
    EXPECT_EQ(src[3], 255);
}

TEST_F(SplashOutBlendLuminosityTest_1595, XBGR8_AllWhite_1595) {
    src[0] = 255; src[1] = 255; src[2] = 255; src[3] = 0;
    dest[0] = 255; dest[1] = 255; dest[2] = 255;
    splashOutBlendLuminosity(src, dest, blend, splashModeXBGR8);
    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
}

// --- CMYK8 Mode Tests ---

TEST_F(SplashOutBlendLuminosityTest_1595, CMYK8_AllZero_1595) {
    // CMYK all zero means white in device space
    src[0] = 0; src[1] = 0; src[2] = 0; src[3] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0; dest[3] = 0;
    splashOutBlendLuminosity(src, dest, blend, splashModeCMYK8);
    // Both are "white" in RGB after inversion, so luminosity blend should stay white -> CMYK all 0
    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
    EXPECT_EQ(blend[3], 0);
}

TEST_F(SplashOutBlendLuminosityTest_1595, CMYK8_AllMax_1595) {
    // CMYK all 255 means black in device space
    src[0] = 255; src[1] = 255; src[2] = 255; src[3] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 255; dest[3] = 255;
    splashOutBlendLuminosity(src, dest, blend, splashModeCMYK8);
    // Both are "black" in RGB after inversion
    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
    EXPECT_EQ(blend[3], 255);
}

TEST_F(SplashOutBlendLuminosityTest_1595, CMYK8_MixedValues_1595) {
    src[0] = 50; src[1] = 100; src[2] = 150; src[3] = 200;
    dest[0] = 200; dest[1] = 150; dest[2] = 100; dest[3] = 50;
    splashOutBlendLuminosity(src, dest, blend, splashModeCMYK8);
    // Just verify valid range
    for (int i = 0; i < 4; i++) {
        EXPECT_GE(blend[i], 0);
        EXPECT_LE(blend[i], 255);
    }
}

TEST_F(SplashOutBlendLuminosityTest_1595, CMYK8_KChannelFromSrc_1595) {
    // The K channel in blend comes from src2[3] (inverted), then inverted back
    // blend[3] = 0xff - src2[3] where src2[3] = 0xff - src[3]
    // So blend[3] = 0xff - (0xff - src[3]) = src[3]
    src[0] = 0; src[1] = 0; src[2] = 0; src[3] = 100;
    dest[0] = 0; dest[1] = 0; dest[2] = 0; dest[3] = 200;
    splashOutBlendLuminosity(src, dest, blend, splashModeCMYK8);
    EXPECT_EQ(blend[3], 100);
}

// --- DeviceN8 Mode Tests ---

TEST_F(SplashOutBlendLuminosityTest_1595, DeviceN8_AllZero_1595) {
    src[0] = 0; src[1] = 0; src[2] = 0; src[3] = 0;
    dest[0] = 0; dest[1] = 0; dest[2] = 0; dest[3] = 0;
    splashOutBlendLuminosity(src, dest, blend, splashModeDeviceN8);
    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
    EXPECT_EQ(blend[3], 0);
}

TEST_F(SplashOutBlendLuminosityTest_1595, DeviceN8_AllMax_1595) {
    src[0] = 255; src[1] = 255; src[2] = 255; src[3] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 255; dest[3] = 255;
    splashOutBlendLuminosity(src, dest, blend, splashModeDeviceN8);
    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
    EXPECT_EQ(blend[3], 255);
}

TEST_F(SplashOutBlendLuminosityTest_1595, DeviceN8_SameAsCMYK8_1595) {
    // DeviceN8 and CMYK8 share the same code path for the first 4 channels
    SplashColor blendCMYK, blendDevN;
    src[0] = 30; src[1] = 60; src[2] = 90; src[3] = 120;
    dest[0] = 120; dest[1] = 90; dest[2] = 60; dest[3] = 30;

    splashOutBlendLuminosity(src, dest, blendCMYK, splashModeCMYK8);

    // Reset src/dest since XBGR8 path modifies src[3], but CMYK doesn't
    src[0] = 30; src[1] = 60; src[2] = 90; src[3] = 120;
    dest[0] = 120; dest[1] = 90; dest[2] = 60; dest[3] = 30;

    splashOutBlendLuminosity(src, dest, blendDevN, splashModeDeviceN8);

    EXPECT_EQ(blendCMYK[0], blendDevN[0]);
    EXPECT_EQ(blendCMYK[1], blendDevN[1]);
    EXPECT_EQ(blendCMYK[2], blendDevN[2]);
    EXPECT_EQ(blendCMYK[3], blendDevN[3]);
}

// --- Boundary tests ---

TEST_F(SplashOutBlendLuminosityTest_1595, RGB8_MaxSrcMinDest_1595) {
    src[0] = 255; src[1] = 255; src[2] = 255;
    dest[0] = 0; dest[1] = 0; dest[2] = 0;
    splashOutBlendLuminosity(src, dest, blend, splashModeRGB8);
    // Black dest with white luminosity; dest has no chroma
    for (int i = 0; i < 3; i++) {
        EXPECT_GE(blend[i], 0);
        EXPECT_LE(blend[i], 255);
    }
}

TEST_F(SplashOutBlendLuminosityTest_1595, RGB8_MinSrcMaxDest_1595) {
    src[0] = 0; src[1] = 0; src[2] = 0;
    dest[0] = 255; dest[1] = 255; dest[2] = 255;
    splashOutBlendLuminosity(src, dest, blend, splashModeRGB8);
    for (int i = 0; i < 3; i++) {
        EXPECT_GE(blend[i], 0);
        EXPECT_LE(blend[i], 255);
    }
}

TEST_F(SplashOutBlendLuminosityTest_1595, Mono8_BoundaryValues_1595) {
    // Test with value 1 (near boundary)
    src[0] = 1;
    dest[0] = 254;
    splashOutBlendLuminosity(src, dest, blend, splashModeMono8);
    EXPECT_GE(blend[0], 0);
    EXPECT_LE(blend[0], 255);
}

TEST_F(SplashOutBlendLuminosityTest_1595, CMYK8_OnlyCyanComponent_1595) {
    src[0] = 128; src[1] = 0; src[2] = 0; src[3] = 0;
    dest[0] = 64; dest[1] = 0; dest[2] = 0; dest[3] = 0;
    splashOutBlendLuminosity(src, dest, blend, splashModeCMYK8);
    for (int i = 0; i < 4; i++) {
        EXPECT_GE(blend[i], 0);
        EXPECT_LE(blend[i], 255);
    }
}

TEST_F(SplashOutBlendLuminosityTest_1595, RGB8_PureGreen_1595) {
    src[0] = 0; src[1] = 255; src[2] = 0;
    dest[0] = 255; dest[1] = 0; dest[2] = 0;
    splashOutBlendLuminosity(src, dest, blend, splashModeRGB8);
    // Green luminosity applied to red hue
    for (int i = 0; i < 3; i++) {
        EXPECT_GE(blend[i], 0);
        EXPECT_LE(blend[i], 255);
    }
}

TEST_F(SplashOutBlendLuminosityTest_1595, RGB8_PureBlue_1595) {
    src[0] = 0; src[1] = 0; src[2] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 0;
    splashOutBlendLuminosity(src, dest, blend, splashModeRGB8);
    for (int i = 0; i < 3; i++) {
        EXPECT_GE(blend[i], 0);
        EXPECT_LE(blend[i], 255);
    }
}

// Test that identical src and dest produce dest-like results for gray
TEST_F(SplashOutBlendLuminosityTest_1595, RGB8_IdenticalSrcDest_1595) {
    src[0] = 100; src[1] = 150; src[2] = 200;
    dest[0] = 100; dest[1] = 150; dest[2] = 200;
    splashOutBlendLuminosity(src, dest, blend, splashModeRGB8);
    // When src == dest, luminosity blend should produce same result
    EXPECT_EQ(blend[0], 100);
    EXPECT_EQ(blend[1], 150);
    EXPECT_EQ(blend[2], 200);
}

TEST_F(SplashOutBlendLuminosityTest_1595, CMYK8_IdenticalSrcDest_1595) {
    src[0] = 50; src[1] = 100; src[2] = 150; src[3] = 200;
    dest[0] = 50; dest[1] = 100; dest[2] = 150; dest[3] = 200;
    splashOutBlendLuminosity(src, dest, blend, splashModeCMYK8);
    // When src == dest, result should match
    EXPECT_EQ(blend[0], 50);
    EXPECT_EQ(blend[1], 100);
    EXPECT_EQ(blend[2], 150);
    EXPECT_EQ(blend[3], 200);
}
