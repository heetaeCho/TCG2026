#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

// Since splashOutBlendMultiply is static in the .cc file, we include the declaration
// and provide access. We declare it with the same signature to test it.
// We need to access the static function - include the source or re-declare.
// For testing purposes, we'll include the source file.
#include "poppler/SplashOutputDev.cc"

class SplashOutBlendMultiplyTest_1577 : public ::testing::Test {
protected:
    void SetUp() override {}
};

// Test RGB8 mode: blend = (dest * src) / 255 for 3 components
TEST_F(SplashOutBlendMultiplyTest_1577, RGB8_BasicMultiply_1577) {
    SplashColor src = {100, 200, 50};
    SplashColor dest = {150, 100, 200};
    SplashColor blend = {0, 0, 0};

    splashOutBlendMultiply(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], (150 * 100) / 255);  // 58
    EXPECT_EQ(blend[1], (100 * 200) / 255);  // 78
    EXPECT_EQ(blend[2], (200 * 50) / 255);   // 39
}

// Test RGB8 mode with all zeros
TEST_F(SplashOutBlendMultiplyTest_1577, RGB8_AllZeros_1577) {
    SplashColor src = {0, 0, 0};
    SplashColor dest = {0, 0, 0};
    SplashColor blend = {99, 99, 99};

    splashOutBlendMultiply(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

// Test RGB8 mode with all 255
TEST_F(SplashOutBlendMultiplyTest_1577, RGB8_AllMax_1577) {
    SplashColor src = {255, 255, 255};
    SplashColor dest = {255, 255, 255};
    SplashColor blend = {0, 0, 0};

    splashOutBlendMultiply(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
}

// Test RGB8: src all 255 should return dest
TEST_F(SplashOutBlendMultiplyTest_1577, RGB8_SrcWhiteReturnsDest_1577) {
    SplashColor src = {255, 255, 255};
    SplashColor dest = {100, 150, 200};
    SplashColor blend = {0, 0, 0};

    splashOutBlendMultiply(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], (100 * 255) / 255);
    EXPECT_EQ(blend[1], (150 * 255) / 255);
    EXPECT_EQ(blend[2], (200 * 255) / 255);
}

// Test RGB8: dest all zeros should yield zero
TEST_F(SplashOutBlendMultiplyTest_1577, RGB8_DestZeroYieldsZero_1577) {
    SplashColor src = {128, 200, 50};
    SplashColor dest = {0, 0, 0};
    SplashColor blend = {99, 99, 99};

    splashOutBlendMultiply(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

// Test Mono8 mode: single component
TEST_F(SplashOutBlendMultiplyTest_1577, Mono8_BasicMultiply_1577) {
    SplashColor src = {128};
    SplashColor dest = {200};
    SplashColor blend = {0};

    splashOutBlendMultiply(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], (200 * 128) / 255);  // 100
}

// Test Mono8: zero src
TEST_F(SplashOutBlendMultiplyTest_1577, Mono8_ZeroSrc_1577) {
    SplashColor src = {0};
    SplashColor dest = {255};
    SplashColor blend = {99};

    splashOutBlendMultiply(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], 0);
}

// Test BGR8 mode: 3 components, same as RGB8 logic
TEST_F(SplashOutBlendMultiplyTest_1577, BGR8_BasicMultiply_1577) {
    SplashColor src = {80, 160, 240};
    SplashColor dest = {120, 60, 30};
    SplashColor blend = {0, 0, 0};

    splashOutBlendMultiply(src, dest, blend, splashModeBGR8);

    EXPECT_EQ(blend[0], (120 * 80) / 255);
    EXPECT_EQ(blend[1], (60 * 160) / 255);
    EXPECT_EQ(blend[2], (30 * 240) / 255);
}

// Test XBGR8 mode: 4 components
TEST_F(SplashOutBlendMultiplyTest_1577, XBGR8_BasicMultiply_1577) {
    SplashColor src = {50, 100, 150, 200};
    SplashColor dest = {200, 150, 100, 50};
    SplashColor blend = {0, 0, 0, 0};

    splashOutBlendMultiply(src, dest, blend, splashModeXBGR8);

    EXPECT_EQ(blend[0], (200 * 50) / 255);
    EXPECT_EQ(blend[1], (150 * 100) / 255);
    EXPECT_EQ(blend[2], (100 * 150) / 255);
    EXPECT_EQ(blend[3], (50 * 200) / 255);
}

// Test CMYK8 mode: uses inversion logic
// blend[i] = 255 - ((255-dest[i]) * (255-src[i])) / 255
TEST_F(SplashOutBlendMultiplyTest_1577, CMYK8_BasicMultiply_1577) {
    SplashColor src = {100, 200, 50, 150};
    SplashColor dest = {150, 100, 200, 50};
    SplashColor blend = {0, 0, 0, 0};

    // Save original values
    SplashColor origSrc = {100, 200, 50, 150};
    SplashColor origDest = {150, 100, 200, 50};

    splashOutBlendMultiply(src, dest, blend, splashModeCMYK8);

    for (int i = 0; i < 4; ++i) {
        int expected = 255 - ((255 - origDest[i]) * (255 - origSrc[i])) / 255;
        EXPECT_EQ(blend[i], expected) << "Component " << i;
    }

    // Verify src and dest are restored
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(src[i], origSrc[i]) << "src component " << i << " should be restored";
        EXPECT_EQ(dest[i], origDest[i]) << "dest component " << i << " should be restored";
    }
}

// Test CMYK8 with all zeros
TEST_F(SplashOutBlendMultiplyTest_1577, CMYK8_AllZeros_1577) {
    SplashColor src = {0, 0, 0, 0};
    SplashColor dest = {0, 0, 0, 0};
    SplashColor blend = {99, 99, 99, 99};

    splashOutBlendMultiply(src, dest, blend, splashModeCMYK8);

    for (int i = 0; i < 4; ++i) {
        int expected = 255 - ((255 * 255) / 255);  // 255 - 255 = 0
        EXPECT_EQ(blend[i], expected) << "Component " << i;
    }
}

// Test CMYK8 with all 255
TEST_F(SplashOutBlendMultiplyTest_1577, CMYK8_AllMax_1577) {
    SplashColor src = {255, 255, 255, 255};
    SplashColor dest = {255, 255, 255, 255};
    SplashColor blend = {0, 0, 0, 0};

    splashOutBlendMultiply(src, dest, blend, splashModeCMYK8);

    for (int i = 0; i < 4; ++i) {
        // 255 - ((255-255)*(255-255))/255 = 255 - 0 = 255
        EXPECT_EQ(blend[i], 255) << "Component " << i;
    }
}

// Test CMYK8: src and dest should not be permanently modified
TEST_F(SplashOutBlendMultiplyTest_1577, CMYK8_SrcDestRestored_1577) {
    SplashColor src = {10, 20, 30, 40};
    SplashColor dest = {50, 60, 70, 80};
    SplashColor blend = {0, 0, 0, 0};

    splashOutBlendMultiply(src, dest, blend, splashModeCMYK8);

    EXPECT_EQ(src[0], 10);
    EXPECT_EQ(src[1], 20);
    EXPECT_EQ(src[2], 30);
    EXPECT_EQ(src[3], 40);
    EXPECT_EQ(dest[0], 50);
    EXPECT_EQ(dest[1], 60);
    EXPECT_EQ(dest[2], 70);
    EXPECT_EQ(dest[3], 80);
}

// Test DeviceN8 mode: uses same inversion logic as CMYK8
TEST_F(SplashOutBlendMultiplyTest_1577, DeviceN8_BasicMultiply_1577) {
    SplashColor src = {};
    SplashColor dest = {};
    SplashColor blend = {};

    int nComps = splashColorModeNComps[splashModeDeviceN8];
    for (int i = 0; i < nComps; ++i) {
        src[i] = (i * 30) % 256;
        dest[i] = (i * 50 + 10) % 256;
    }

    SplashColor origSrc, origDest;
    memcpy(origSrc, src, sizeof(SplashColor));
    memcpy(origDest, dest, sizeof(SplashColor));

    splashOutBlendMultiply(src, dest, blend, splashModeDeviceN8);

    for (int i = 0; i < nComps; ++i) {
        int expected = 255 - ((255 - origDest[i]) * (255 - origSrc[i])) / 255;
        EXPECT_EQ(blend[i], expected) << "Component " << i;
    }

    // Verify restoration
    for (int i = 0; i < nComps; ++i) {
        EXPECT_EQ(src[i], origSrc[i]) << "src[" << i << "] should be restored";
        EXPECT_EQ(dest[i], origDest[i]) << "dest[" << i << "] should be restored";
    }
}

// Test Mono1 mode: 1 component, simple multiply
TEST_F(SplashOutBlendMultiplyTest_1577, Mono1_BasicMultiply_1577) {
    SplashColor src = {255};
    SplashColor dest = {255};
    SplashColor blend = {0};

    splashOutBlendMultiply(src, dest, blend, splashModeMono1);

    EXPECT_EQ(blend[0], 255);
}

// Test Mono1 with one zero
TEST_F(SplashOutBlendMultiplyTest_1577, Mono1_OneZero_1577) {
    SplashColor src = {0};
    SplashColor dest = {255};
    SplashColor blend = {99};

    splashOutBlendMultiply(src, dest, blend, splashModeMono1);

    EXPECT_EQ(blend[0], 0);
}

// Test RGB8 symmetry: multiply(src,dest) should equal multiply(dest,src)
TEST_F(SplashOutBlendMultiplyTest_1577, RGB8_Symmetry_1577) {
    SplashColor src1 = {100, 200, 50};
    SplashColor dest1 = {150, 100, 200};
    SplashColor blend1 = {0, 0, 0};

    SplashColor src2 = {150, 100, 200};
    SplashColor dest2 = {100, 200, 50};
    SplashColor blend2 = {0, 0, 0};

    splashOutBlendMultiply(src1, dest1, blend1, splashModeRGB8);
    splashOutBlendMultiply(src2, dest2, blend2, splashModeRGB8);

    EXPECT_EQ(blend1[0], blend2[0]);
    EXPECT_EQ(blend1[1], blend2[1]);
    EXPECT_EQ(blend1[2], blend2[2]);
}

// Test CMYK8 with single component non-zero
TEST_F(SplashOutBlendMultiplyTest_1577, CMYK8_SingleComponentNonZero_1577) {
    SplashColor src = {128, 0, 0, 0};
    SplashColor dest = {64, 0, 0, 0};
    SplashColor blend = {0, 0, 0, 0};

    splashOutBlendMultiply(src, dest, blend, splashModeCMYK8);

    int expected0 = 255 - ((255 - 64) * (255 - 128)) / 255;
    int expectedOther = 255 - ((255 * 255) / 255);  // = 0

    EXPECT_EQ(blend[0], expected0);
    EXPECT_EQ(blend[1], expectedOther);
    EXPECT_EQ(blend[2], expectedOther);
    EXPECT_EQ(blend[3], expectedOther);
}

// Test RGB8 with value 1 (boundary near zero)
TEST_F(SplashOutBlendMultiplyTest_1577, RGB8_SmallValues_1577) {
    SplashColor src = {1, 1, 1};
    SplashColor dest = {1, 1, 1};
    SplashColor blend = {99, 99, 99};

    splashOutBlendMultiply(src, dest, blend, splashModeRGB8);

    // (1*1)/255 = 0
    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

// Test RGB8 with value 254 (boundary near max)
TEST_F(SplashOutBlendMultiplyTest_1577, RGB8_NearMaxValues_1577) {
    SplashColor src = {254, 254, 254};
    SplashColor dest = {254, 254, 254};
    SplashColor blend = {0, 0, 0};

    splashOutBlendMultiply(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], (254 * 254) / 255);  // 253
    EXPECT_EQ(blend[1], (254 * 254) / 255);
    EXPECT_EQ(blend[2], (254 * 254) / 255);
}
