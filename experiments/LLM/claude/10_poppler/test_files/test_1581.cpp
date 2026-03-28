#include <gtest/gtest.h>
#include "splash/SplashTypes.h"
#include <cstring>
#include <algorithm>

// Declaration of the function under test (it's static in the .cc file, so we need to
// either include it or redeclare it). Since it's a static function in a .cc file,
// we need to include the source or use a workaround. We'll declare it as extern
// and rely on linkage, or include the implementation file.
// For testing purposes, we include the source file to access the static function.

// Forward declare the splashColorModeNComps array
extern int splashColorModeNComps[];

// We need access to the static function. Including the cc file or using a test helper.
// Since the function is static, we'll include the source file to get access.
// Alternatively, if the test framework provides access, we use that.

// For this test, we replicate the static function signature and include it via the .cc file
// or assume the build system makes it accessible.

static void splashOutBlendLighten(SplashColorPtr src, SplashColorPtr dest, SplashColorPtr blend, SplashColorMode cm);

// Include the implementation to get access to the static function
#include "poppler/SplashOutputDev.cc"

class SplashOutBlendLightenTest_1581 : public ::testing::Test {
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

// Test RGB8 mode: blend should be max of src and dest per component
TEST_F(SplashOutBlendLightenTest_1581, RGB8_BasicLighten_1581) {
    src[0] = 100; src[1] = 200; src[2] = 50;
    dest[0] = 150; dest[1] = 100; dest[2] = 250;

    splashOutBlendLighten(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 150); // max(100, 150)
    EXPECT_EQ(blend[1], 200); // max(200, 100)
    EXPECT_EQ(blend[2], 250); // max(50, 250)
}

// Test RGB8 mode: src and dest should remain unchanged
TEST_F(SplashOutBlendLightenTest_1581, RGB8_SrcDestUnchanged_1581) {
    src[0] = 100; src[1] = 200; src[2] = 50;
    dest[0] = 150; dest[1] = 100; dest[2] = 250;

    SplashColor srcCopy, destCopy;
    memcpy(srcCopy, src, sizeof(SplashColor));
    memcpy(destCopy, dest, sizeof(SplashColor));

    splashOutBlendLighten(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(src[0], srcCopy[0]);
    EXPECT_EQ(src[1], srcCopy[1]);
    EXPECT_EQ(src[2], srcCopy[2]);
    EXPECT_EQ(dest[0], destCopy[0]);
    EXPECT_EQ(dest[1], destCopy[1]);
    EXPECT_EQ(dest[2], destCopy[2]);
}

// Test RGB8 mode: identical src and dest
TEST_F(SplashOutBlendLightenTest_1581, RGB8_IdenticalSrcDest_1581) {
    src[0] = 128; src[1] = 128; src[2] = 128;
    dest[0] = 128; dest[1] = 128; dest[2] = 128;

    splashOutBlendLighten(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 128);
    EXPECT_EQ(blend[1], 128);
    EXPECT_EQ(blend[2], 128);
}

// Test RGB8 mode: all zeros
TEST_F(SplashOutBlendLightenTest_1581, RGB8_AllZeros_1581) {
    splashOutBlendLighten(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
}

// Test RGB8 mode: all 255
TEST_F(SplashOutBlendLightenTest_1581, RGB8_AllMax_1581) {
    src[0] = 255; src[1] = 255; src[2] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 255;

    splashOutBlendLighten(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
}

// Test RGB8 mode: src all zeros, dest all 255
TEST_F(SplashOutBlendLightenTest_1581, RGB8_SrcZeroDestMax_1581) {
    dest[0] = 255; dest[1] = 255; dest[2] = 255;

    splashOutBlendLighten(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
}

// Test Mono8 mode: single component lighten
TEST_F(SplashOutBlendLightenTest_1581, Mono8_BasicLighten_1581) {
    src[0] = 100;
    dest[0] = 200;

    splashOutBlendLighten(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], 200); // max(100, 200)
}

// Test Mono8 mode: src greater than dest
TEST_F(SplashOutBlendLightenTest_1581, Mono8_SrcGreater_1581) {
    src[0] = 200;
    dest[0] = 100;

    splashOutBlendLighten(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], 200); // max(200, 100)
}

// Test CMYK8 mode: the inversion logic
// For CMYK8, the function inverts src and dest, computes max, then inverts back
// This effectively computes min of original values
TEST_F(SplashOutBlendLightenTest_1581, CMYK8_BasicLighten_1581) {
    // CMYK has 4 components
    src[0] = 100; src[1] = 200; src[2] = 50; src[3] = 30;
    dest[0] = 150; dest[1] = 100; dest[2] = 250; dest[3] = 60;

    SplashColor srcCopy, destCopy;
    memcpy(srcCopy, src, sizeof(SplashColor));
    memcpy(destCopy, dest, sizeof(SplashColor));

    splashOutBlendLighten(src, dest, blend, splashModeCMYK8);

    // After inversion: src'[i] = 255 - src[i], dest'[i] = 255 - dest[i]
    // blend'[i] = max(dest'[i], src'[i])
    // Final blend[i] = 255 - blend'[i] = 255 - max(255 - dest[i], 255 - src[i]) = min(dest[i], src[i])
    EXPECT_EQ(blend[0], std::min(srcCopy[0], destCopy[0])); // min(100, 150) = 100
    EXPECT_EQ(blend[1], std::min(srcCopy[1], destCopy[1])); // min(200, 100) = 100
    EXPECT_EQ(blend[2], std::min(srcCopy[2], destCopy[2])); // min(50, 250) = 50
    EXPECT_EQ(blend[3], std::min(srcCopy[3], destCopy[3])); // min(30, 60) = 30
}

// Test CMYK8: src and dest unchanged after call
TEST_F(SplashOutBlendLightenTest_1581, CMYK8_SrcDestUnchanged_1581) {
    src[0] = 100; src[1] = 200; src[2] = 50; src[3] = 30;
    dest[0] = 150; dest[1] = 100; dest[2] = 250; dest[3] = 60;

    SplashColor srcCopy, destCopy;
    memcpy(srcCopy, src, sizeof(SplashColor));
    memcpy(destCopy, dest, sizeof(SplashColor));

    splashOutBlendLighten(src, dest, blend, splashModeCMYK8);

    // After the double inversion, src and dest should be restored
    EXPECT_EQ(src[0], srcCopy[0]);
    EXPECT_EQ(src[1], srcCopy[1]);
    EXPECT_EQ(src[2], srcCopy[2]);
    EXPECT_EQ(src[3], srcCopy[3]);
    EXPECT_EQ(dest[0], destCopy[0]);
    EXPECT_EQ(dest[1], destCopy[1]);
    EXPECT_EQ(dest[2], destCopy[2]);
    EXPECT_EQ(dest[3], destCopy[3]);
}

// Test CMYK8 mode: all zeros
TEST_F(SplashOutBlendLightenTest_1581, CMYK8_AllZeros_1581) {
    splashOutBlendLighten(src, dest, blend, splashModeCMYK8);

    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
    EXPECT_EQ(blend[3], 0);
}

// Test CMYK8 mode: all 255
TEST_F(SplashOutBlendLightenTest_1581, CMYK8_AllMax_1581) {
    src[0] = 255; src[1] = 255; src[2] = 255; src[3] = 255;
    dest[0] = 255; dest[1] = 255; dest[2] = 255; dest[3] = 255;

    splashOutBlendLighten(src, dest, blend, splashModeCMYK8);

    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
    EXPECT_EQ(blend[3], 255);
}

// Test BGR8 mode: behaves same as RGB8 (no inversion)
TEST_F(SplashOutBlendLightenTest_1581, BGR8_BasicLighten_1581) {
    src[0] = 10; src[1] = 200; src[2] = 50;
    dest[0] = 150; dest[1] = 100; dest[2] = 250;

    splashOutBlendLighten(src, dest, blend, splashModeBGR8);

    EXPECT_EQ(blend[0], 150); // max(10, 150)
    EXPECT_EQ(blend[1], 200); // max(200, 100)
    EXPECT_EQ(blend[2], 250); // max(50, 250)
}

// Test XBGR8 mode: 4 components, no inversion
TEST_F(SplashOutBlendLightenTest_1581, XBGR8_BasicLighten_1581) {
    src[0] = 10; src[1] = 200; src[2] = 50; src[3] = 80;
    dest[0] = 150; dest[1] = 100; dest[2] = 250; dest[3] = 40;

    splashOutBlendLighten(src, dest, blend, splashModeXBGR8);

    EXPECT_EQ(blend[0], 150); // max(10, 150)
    EXPECT_EQ(blend[1], 200); // max(200, 100)
    EXPECT_EQ(blend[2], 250); // max(50, 250)
    EXPECT_EQ(blend[3], 80);  // max(80, 40)
}

// Test DeviceN8 mode: same inversion logic as CMYK8
TEST_F(SplashOutBlendLightenTest_1581, DeviceN8_BasicLighten_1581) {
    // DeviceN8 has SPOT_NCOMPS+4 components, but we test with what's available
    int nComps = splashColorModeNComps[splashModeDeviceN8];
    for (int i = 0; i < nComps; ++i) {
        src[i] = (unsigned char)(i * 10);
        dest[i] = (unsigned char)(255 - i * 10);
    }

    SplashColor srcCopy, destCopy;
    memcpy(srcCopy, src, sizeof(SplashColor));
    memcpy(destCopy, dest, sizeof(SplashColor));

    splashOutBlendLighten(src, dest, blend, splashModeDeviceN8);

    // For DeviceN8, same logic as CMYK8: effectively min of original values
    for (int i = 0; i < nComps; ++i) {
        EXPECT_EQ(blend[i], std::min(srcCopy[i], destCopy[i]))
            << "Component " << i << " mismatch";
    }
}

// Test DeviceN8: src and dest restored after call
TEST_F(SplashOutBlendLightenTest_1581, DeviceN8_SrcDestUnchanged_1581) {
    int nComps = splashColorModeNComps[splashModeDeviceN8];
    for (int i = 0; i < nComps; ++i) {
        src[i] = (unsigned char)(i * 15);
        dest[i] = (unsigned char)(200 - i * 5);
    }

    SplashColor srcCopy, destCopy;
    memcpy(srcCopy, src, sizeof(SplashColor));
    memcpy(destCopy, dest, sizeof(SplashColor));

    splashOutBlendLighten(src, dest, blend, splashModeDeviceN8);

    for (int i = 0; i < nComps; ++i) {
        EXPECT_EQ(src[i], srcCopy[i]) << "src component " << i << " changed";
        EXPECT_EQ(dest[i], destCopy[i]) << "dest component " << i << " changed";
    }
}

// Test CMYK8: one channel identical
TEST_F(SplashOutBlendLightenTest_1581, CMYK8_OneChannelIdentical_1581) {
    src[0] = 100; src[1] = 100; src[2] = 0; src[3] = 255;
    dest[0] = 100; dest[1] = 50; dest[2] = 255; dest[3] = 0;

    splashOutBlendLighten(src, dest, blend, splashModeCMYK8);

    EXPECT_EQ(blend[0], 100); // min(100, 100)
    EXPECT_EQ(blend[1], 50);  // min(100, 50)
    EXPECT_EQ(blend[2], 0);   // min(0, 255)
    EXPECT_EQ(blend[3], 0);   // min(255, 0)
}

// Test RGB8: boundary values 0 and 255 mixed
TEST_F(SplashOutBlendLightenTest_1581, RGB8_BoundaryMixed_1581) {
    src[0] = 0; src[1] = 255; src[2] = 0;
    dest[0] = 255; dest[1] = 0; dest[2] = 255;

    splashOutBlendLighten(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 255);
    EXPECT_EQ(blend[1], 255);
    EXPECT_EQ(blend[2], 255);
}

// Test Mono8: boundary value 0
TEST_F(SplashOutBlendLightenTest_1581, Mono8_BothZero_1581) {
    src[0] = 0;
    dest[0] = 0;

    splashOutBlendLighten(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], 0);
}

// Test Mono8: boundary value 255
TEST_F(SplashOutBlendLightenTest_1581, Mono8_BothMax_1581) {
    src[0] = 255;
    dest[0] = 255;

    splashOutBlendLighten(src, dest, blend, splashModeMono8);

    EXPECT_EQ(blend[0], 255);
}

// Test CMYK8: src zero, dest max
TEST_F(SplashOutBlendLightenTest_1581, CMYK8_SrcZeroDestMax_1581) {
    dest[0] = 255; dest[1] = 255; dest[2] = 255; dest[3] = 255;

    splashOutBlendLighten(src, dest, blend, splashModeCMYK8);

    // min(0, 255) for each = 0
    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
    EXPECT_EQ(blend[3], 0);
}

// Test CMYK8: src max, dest zero
TEST_F(SplashOutBlendLightenTest_1581, CMYK8_SrcMaxDestZero_1581) {
    src[0] = 255; src[1] = 255; src[2] = 255; src[3] = 255;

    splashOutBlendLighten(src, dest, blend, splashModeCMYK8);

    // min(255, 0) for each = 0
    EXPECT_EQ(blend[0], 0);
    EXPECT_EQ(blend[1], 0);
    EXPECT_EQ(blend[2], 0);
    EXPECT_EQ(blend[3], 0);
}

// Test RGB8: src[i] == dest[i] + 1 (near equal)
TEST_F(SplashOutBlendLightenTest_1581, RGB8_NearEqual_1581) {
    src[0] = 128; src[1] = 127; src[2] = 1;
    dest[0] = 127; dest[1] = 128; dest[2] = 0;

    splashOutBlendLighten(src, dest, blend, splashModeRGB8);

    EXPECT_EQ(blend[0], 128);
    EXPECT_EQ(blend[1], 128);
    EXPECT_EQ(blend[2], 1);
}
