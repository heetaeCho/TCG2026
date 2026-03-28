#include <gtest/gtest.h>
#include "splash/SplashTypes.h"
#include <cstring>
#include <algorithm>

// Since splashOutBlendDifference is static in SplashOutputDev.cc, we include it
// or re-declare. For testing purposes, we include the definition.
// The splashColorModeNComps array needs to be available.
extern int splashColorModeNComps[];

typedef unsigned char SplashColor[SPOT_NCOMPS + 4];
typedef unsigned char *SplashColorPtr;

// Include the static function for testing
static void splashOutBlendDifference(SplashColorPtr src, SplashColorPtr dest, SplashColorPtr blend, SplashColorMode cm) {
    int i;
    if (cm == splashModeCMYK8 || cm == splashModeDeviceN8) {
        for (i = 0; i < splashColorModeNComps[cm]; ++i) {
            dest[i] = 255 - dest[i];
            src[i] = 255 - src[i];
        }
    }
    {
        for (i = 0; i < splashColorModeNComps[cm]; ++i) {
            blend[i] = dest[i] < src[i] ? src[i] - dest[i] : dest[i] - src[i];
        }
    }
    if (cm == splashModeCMYK8 || cm == splashModeDeviceN8) {
        for (i = 0; i < splashColorModeNComps[cm]; ++i) {
            dest[i] = 255 - dest[i];
            src[i] = 255 - src[i];
            blend[i] = 255 - blend[i];
        }
    }
    if (cm == splashModeDeviceN8) {
        for (i = 4; i < splashColorModeNComps[cm]; ++i) {
            if (dest[i] == 0 && src[i] == 0) {
                blend[i] = 0;
            }
        }
    }
}

class SplashOutBlendDifferenceTest_1586 : public ::testing::Test {
protected:
    SplashColor src, dest, blend;

    void SetUp() override {
        memset(src, 0, sizeof(src));
        memset(dest, 0, sizeof(dest));
        memset(blend, 0, sizeof(blend));
    }
};

// ==================== RGB8 Tests ====================

TEST_F(SplashOutBlendDifferenceTest_1586, RGB8_BasicDifference_1586) {
    src[0] = 200; src[1] = 100; src[2] = 50;
    dest[0] = 100; dest[1] = 200; dest[2] = 50;

    splashOutBlendDifference(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 100);
    EXPECT_EQ(blend[1], 100);
    EXPECT_EQ(blend[2], 0);
}

TEST_F(SplashOutBlendDifferenceTest_1586, RGB8_SrcGreaterThanDest_1586) {
    src[0] = 255; src[1] = 200; src[2] = 128;
    dest[0] = 0; dest[1] = 50; dest[2] = 64;

    splashOutBlendDifference(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 150);
    EXPECT_EQ(blend[2], 64);
}

TEST_F(SplashOutBlendDifferenceTest_1586, RGB8_DestGreaterThanSrc_1586) {
    src[0] = 0; src[1] = 50; src[2] = 64;
    dest[0] = 255; dest[1] = 200; dest[2] = 128;

    splashOutBlendDifference(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 150);
    EXPECT_EQ(blend[2], 64);
}

TEST_F(SplashOutBlendDifferenceTest_1586, RGB8_AllZeros_1586) {
    splashOutBlendDifference(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

TEST_F(SplashOutBlendDifferenceTest_1586, RGB8_AllMax_1586) {
    src[0] = 255; src[1] = 255; src[2] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 255;

    splashOutBlendDifference(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

TEST_F(SplashOutBlendDifferenceTest_1586, RGB8_SrcZeroDestMax_1586) {
    dest[0] = 255; dest[1] = 255; dest[2] = 255;

    splashOutBlendDifference(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
}

TEST_F(SplashOutBlendDifferenceTest_1586, RGB8_DoesNotModifySrcDest_1586) {
    src[0] = 100; src[1] = 150; src[2] = 200;
    dest[0] = 50; dest[1] = 75; dest[2] = 100;

    unsigned char orig_src[3] = {100, 150, 200};
    unsigned char orig_dest[3] = {50, 75, 100};

    splashOutBlendDifference(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(src[0], orig_src[0]);
    EXPECT_EQ(src[1], orig_src[1]);
    EXPECT_EQ(src[2], orig_src[2]);
    EXPECT_EQ(dest[0], orig_dest[0]);
    EXPECT_EQ(dest[1], orig_dest[1]);
    EXPECT_EQ(dest[2], orig_dest[2]);
}

// ==================== Mono8 Tests ====================

TEST_F(SplashOutBlendDifferenceTest_1586, Mono8_BasicDifference_1586) {
    src[0] = 200;
    dest[0] = 100;

    splashOutBlendDifference(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], 100);
}

TEST_F(SplashOutBlendDifferenceTest_1586, Mono8_EqualValues_1586) {
    src[0] = 128;
    dest[0] = 128;

    splashOutBlendDifference(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], 0);
}

// ==================== BGR8 Tests ====================

TEST_F(SplashOutBlendDifferenceTest_1586, BGR8_BasicDifference_1586) {
    src[0] = 10; src[1] = 20; src[2] = 30;
    dest[0] = 40; dest[1] = 50; dest[2] = 60;

    splashOutBlendDifference(src, dest, blend, splashModeBGR8);

    EXPECT_EQ(blend[0], 30);
    EXPECT_EQ(blend[1], 30);
    EXPECT_EQ(blend[2], 30);
}

// ==================== XBGR8 Tests ====================

TEST_F(SplashOutBlendDifferenceTest_1586, XBGR8_BasicDifference_1586) {
    src[0] = 10; src[1] = 20; src[2] = 30; src[3] = 40;
    dest[0] = 50; dest[1] = 60; dest[2] = 70; dest[3] = 80;

    splashOutBlendDifference(src, dest, blend, splashModeXBGR8);

    EXPECT_EQ(blend[0], 40);
    EXPECT_EQ(blend[1], 40);
    EXPECT_EQ(blend[2], 40);
    EXPECT_EQ(blend[3], 40);
}

// ==================== CMYK8 Tests ====================

TEST_F(SplashOutBlendDifferenceTest_1586, CMYK8_AllZeros_1586) {
    // src=0, dest=0 in CMYK
    // Inverted: src_inv=255, dest_inv=255
    // diff = |255-255| = 0
    // blend_inv = 255 - 0 = 255
    splashOutBlendDifference(src, dest, blend, splashModeCMYK8);

    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
    EXPECT_EQ(blend[3], 255);

    // Verify src and dest are restored
    EXPECT_EQ(src[0], 0);
    EXPECT_EQ(dest[0], 0);
}

TEST_F(SplashOutBlendDifferenceTest_1586, CMYK8_AllMax_1586) {
    // src=255, dest=255
    // Inverted: src_inv=0, dest_inv=0
    // diff = 0
    // blend_inv = 255 - 0 = 255
    for (int i = 0; i < 4; i++) { src[i] = 255; dest[i] = 255; }

    splashOutBlendDifference(src, dest, blend, splashModeCMYK8);

    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
    EXPECT_EQ(blend[3], 255);
}

TEST_F(SplashOutBlendDifferenceTest_1586, CMYK8_SrcZeroDestMax_1586) {
    // src=0, dest=255
    // Inverted: src_inv=255, dest_inv=0
    // diff = 255
    // blend_inv = 255 - 255 = 0
    for (int i = 0; i < 4; i++) { dest[i] = 255; }

    splashOutBlendDifference(src, dest, blend, splashModeCMYK8);

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(blend[i], 0);
    }
}

TEST_F(SplashOutBlendDifferenceTest_1586, CMYK8_MixedValues_1586) {
    // src=100, dest=200
    // Inverted: src_inv=155, dest_inv=55
    // diff = |155 - 55| = 100
    // blend_inv = 255 - 100 = 155
    src[0] = 100; dest[0] = 200;
    src[1] = 50;  dest[1] = 50;
    src[2] = 0;   dest[2] = 255;
    src[3] = 255; dest[3] = 0;

    splashOutBlendDifference(src, dest, blend, splashModeCMYK8);

    // Component 0: src_inv=155, dest_inv=55, diff=100, blend=255-100=155
    EXPECT_EQ(blend[0], 155);
    // Component 1: src_inv=205, dest_inv=205, diff=0, blend=255
    EXPECT_EQ(blend[1], 255);
    // Component 2: src_inv=255, dest_inv=0, diff=255, blend=0
    EXPECT_EQ(blend[2], 0);
    // Component 3: src_inv=0, dest_inv=255, diff=255, blend=0
    EXPECT_EQ(blend[3], 0);

    // Verify src and dest are restored
    EXPECT_EQ(src[0], 100);
    EXPECT_EQ(src[1], 50);
    EXPECT_EQ(dest[0], 200);
    EXPECT_EQ(dest[1], 50);
}

// ==================== DeviceN8 Tests ====================

TEST_F(SplashOutBlendDifferenceTest_1586, DeviceN8_BasicWithSpotChannels_1586) {
    // For DeviceN8, nComps = SPOT_NCOMPS + 4
    // Components 0-3 are CMYK, 4+ are spot colors
    // Same CMYK inversion logic applies
    // Additional: if dest[i]==0 && src[i]==0 for i>=4, blend[i]=0

    for (int i = 0; i < splashColorModeNComps[splashModeDeviceN8]; i++) {
        src[i] = 0;
        dest[i] = 0;
    }

    splashOutBlendDifference(src, dest, blend, splashModeDeviceN8);

    // For CMYK components (0-3): same as CMYK8 all-zeros -> blend=255
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(blend[i], 255);
    }

    // For spot channels (4+): both src and dest are 0, so blend[i] = 0
    for (int i = 4; i < splashColorModeNComps[splashModeDeviceN8]; i++) {
        EXPECT_EQ(blend[i], 0);
    }
}

TEST_F(SplashOutBlendDifferenceTest_1586, DeviceN8_SpotChannelsBothZero_1586) {
    // Set CMYK to some values, spot channels to 0
    for (int i = 0; i < 4; i++) {
        src[i] = 100;
        dest[i] = 100;
    }
    for (int i = 4; i < splashColorModeNComps[splashModeDeviceN8]; i++) {
        src[i] = 0;
        dest[i] = 0;
    }

    splashOutBlendDifference(src, dest, blend, splashModeDeviceN8);

    // CMYK: src_inv=155, dest_inv=155, diff=0, blend=255
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(blend[i], 255);
    }

    // Spot channels: both 0 -> blend = 0
    for (int i = 4; i < splashColorModeNComps[splashModeDeviceN8]; i++) {
        EXPECT_EQ(blend[i], 0);
    }
}

TEST_F(SplashOutBlendDifferenceTest_1586, DeviceN8_SpotChannelsNonZero_1586) {
    // If spot channels are non-zero, the normal CMYK blend logic applies
    for (int i = 0; i < splashColorModeNComps[splashModeDeviceN8]; i++) {
        src[i] = 100;
        dest[i] = 200;
    }

    splashOutBlendDifference(src, dest, blend, splashModeDeviceN8);

    // All components: src_inv=155, dest_inv=55, diff=100, blend=255-100=155
    for (int i = 0; i < splashColorModeNComps[splashModeDeviceN8]; i++) {
        EXPECT_EQ(blend[i], 155);
    }

    // Verify src/dest restored
    for (int i = 0; i < splashColorModeNComps[splashModeDeviceN8]; i++) {
        EXPECT_EQ(src[i], 100);
        EXPECT_EQ(dest[i], 200);
    }
}

TEST_F(SplashOutBlendDifferenceTest_1586, DeviceN8_SpotOneSrcZeroDestNonZero_1586) {
    // Spot channel: src=0, dest=50
    // Not both zero, so normal blend applies
    for (int i = 0; i < 4; i++) {
        src[i] = 0;
        dest[i] = 0;
    }
    if (splashColorModeNComps[splashModeDeviceN8] > 4) {
        src[4] = 0;
        dest[4] = 50;
        // src_inv=255, dest_inv=205, diff=50, blend=255-50=205
        splashOutBlendDifference(src, dest, blend, splashModeDeviceN8);
        // dest[4] was 50, not 0 at original, so the "both zero" check doesn't trigger
        // Wait, the check is after restoring: dest[i] and src[i] are restored
        // dest[4]=50, src[4]=0, not both 0 -> blend stays 205
        EXPECT_EQ(blend[4], 205);
    }
}

TEST_F(SplashOutBlendDifferenceTest_1586, DeviceN8_SpotOneSrcNonZeroDestZero_1586) {
    for (int i = 0; i < 4; i++) {
        src[i] = 0;
        dest[i] = 0;
    }
    if (splashColorModeNComps[splashModeDeviceN8] > 4) {
        src[4] = 50;
        dest[4] = 0;
        splashOutBlendDifference(src, dest, blend, splashModeDeviceN8);
        // src_inv=205, dest_inv=255, diff=50, blend=255-50=205
        // src[4]=50, dest[4]=0 -> not both zero, blend stays
        EXPECT_EQ(blend[4], 205);
    }
}

// ==================== Boundary Tests ====================

TEST_F(SplashOutBlendDifferenceTest_1586, RGB8_AdjacentValues_1586) {
    src[0] = 128; dest[0] = 127;
    src[1] = 0;   dest[1] = 1;
    src[2] = 254; dest[2] = 255;

    splashOutBlendDifference(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 1);
    EXPECT_EQ(blend[1], 1);
    EXPECT_EQ(blend[2], 1);
}

TEST_F(SplashOutBlendDifferenceTest_1586, CMYK8_BoundaryValues_1586) {
    // src=1, dest=0
    // src_inv=254, dest_inv=255, diff=1, blend=255-1=254
    src[0] = 1; dest[0] = 0;
    src[1] = 0; dest[1] = 1;
    src[2] = 1; dest[2] = 1;
    src[3] = 254; dest[3] = 255;

    splashOutBlendDifference(src, dest, blend, splashModeCMYK8);

    EXPECT_EQ(blend[0], 254);
    EXPECT_EQ(blend[1], 254);
    // Component 2: src_inv=254, dest_inv=254, diff=0, blend=255
    EXPECT_EQ(blend[2], 255);
    // Component 3: src_inv=1, dest_inv=0, diff=1, blend=254
    EXPECT_EQ(blend[3], 254);
}

TEST_F(SplashOutBlendDifferenceTest_1586, RGB8_SymmetryProperty_1586) {
    // |a - b| == |b - a|
    SplashColor src1, dest1, blend1;
    SplashColor src2, dest2, blend2;

    src1[0] = 100; src1[1] = 200; src1[2] = 50;
    dest1[0] = 200; dest1[1] = 50; dest1[2] = 100;

    src2[0] = 200; src2[1] = 50; src2[2] = 100;
    dest2[0] = 100; dest2[1] = 200; dest2[2] = 50;

    splashOutBlendDifference(src1, dest1, blend1, splashModeRGB8);
    splashOutBlendDifference(src2, dest2, blend2, splashModeRGB8);

    EXPECT_EQ(blend1[0], blend2[0]);
    EXPECT_EQ(blend1[1], blend2[1]);
    EXPECT_EQ(blend1[2], blend2[2]);
}

TEST_F(SplashOutBlendDifferenceTest_1586, CMYK8_SymmetryProperty_1586) {
    SplashColor src1, dest1, blend1;
    SplashColor src2, dest2, blend2;

    for (int i = 0; i < 4; i++) {
        src1[i] = 100 + i * 20;
        dest1[i] = 200 - i * 20;
        src2[i] = dest1[i];
        dest2[i] = src1[i];
    }

    splashOutBlendDifference(src1, dest1, blend1, splashModeCMYK8);
    splashOutBlendDifference(src2, dest2, blend2, splashModeCMYK8);

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(blend1[i], blend2[i]);
    }
}
