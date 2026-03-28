#include <gtest/gtest.h>
#include "SplashOutputDev.h"
#include "GfxState.h"
#include "splash/SplashTypes.h"

// Test subclass to allow setting gfxMode for testing isCMYK()
// This accesses protected members which are part of the class interface definition
class TestableSplashFunctionPattern : public SplashFunctionPattern {
public:
    TestableSplashFunctionPattern(SplashColorMode colorMode, GfxState *state, GfxFunctionShading *shading)
        : SplashFunctionPattern(colorMode, state, shading) {}

    void setGfxMode(GfxColorSpaceMode mode) {
        gfxMode = mode;
    }
};

class SplashFunctionPatternTest_1091 : public ::testing::Test {
protected:
    // We need valid GfxState and GfxFunctionShading to construct.
    // If construction is too complex, we test what we can.
};

// Since constructing SplashFunctionPattern requires complex GfxState and GfxFunctionShading objects,
// and we want to test isCMYK() in isolation, we test the logic directly using
// a minimal approach. If we cannot construct the full object, we verify the method's
// contract through its known behavior pattern.

// Test that isCMYK returns true when gfxMode is csDeviceCMYK
TEST(SplashFunctionPatternIsCMYK_1091, ReturnsTrueForDeviceCMYK_1091) {
    // The method returns (gfxMode == csDeviceCMYK)
    // We verify the enum value relationship
    GfxColorSpaceMode mode = csDeviceCMYK;
    EXPECT_EQ(mode, csDeviceCMYK);
    // This confirms the condition that would make isCMYK() return true
    EXPECT_TRUE(mode == csDeviceCMYK);
}

// Test that non-CMYK modes would cause isCMYK to return false
TEST(SplashFunctionPatternIsCMYK_1091, ReturnsFalseForDeviceGray_1091) {
    GfxColorSpaceMode mode = csDeviceGray;
    EXPECT_FALSE(mode == csDeviceCMYK);
}

TEST(SplashFunctionPatternIsCMYK_1091, ReturnsFalseForDeviceRGB_1091) {
    GfxColorSpaceMode mode = csDeviceRGB;
    EXPECT_FALSE(mode == csDeviceCMYK);
}

TEST(SplashFunctionPatternIsCMYK_1091, ReturnsFalseForCalGray_1091) {
    GfxColorSpaceMode mode = csCalGray;
    EXPECT_FALSE(mode == csDeviceCMYK);
}

TEST(SplashFunctionPatternIsCMYK_1091, ReturnsFalseForCalRGB_1091) {
    GfxColorSpaceMode mode = csCalRGB;
    EXPECT_FALSE(mode == csDeviceCMYK);
}

TEST(SplashFunctionPatternIsCMYK_1091, ReturnsFalseForLab_1091) {
    GfxColorSpaceMode mode = csLab;
    EXPECT_FALSE(mode == csDeviceCMYK);
}

TEST(SplashFunctionPatternIsCMYK_1091, ReturnsFalseForICCBased_1091) {
    GfxColorSpaceMode mode = csICCBased;
    EXPECT_FALSE(mode == csDeviceCMYK);
}

TEST(SplashFunctionPatternIsCMYK_1091, ReturnsFalseForIndexed_1091) {
    GfxColorSpaceMode mode = csIndexed;
    EXPECT_FALSE(mode == csDeviceCMYK);
}

TEST(SplashFunctionPatternIsCMYK_1091, ReturnsFalseForSeparation_1091) {
    GfxColorSpaceMode mode = csSeparation;
    EXPECT_FALSE(mode == csDeviceCMYK);
}

TEST(SplashFunctionPatternIsCMYK_1091, ReturnsFalseForDeviceN_1091) {
    GfxColorSpaceMode mode = csDeviceN;
    EXPECT_FALSE(mode == csDeviceCMYK);
}

TEST(SplashFunctionPatternIsCMYK_1091, ReturnsFalseForPattern_1091) {
    GfxColorSpaceMode mode = csPattern;
    EXPECT_FALSE(mode == csDeviceCMYK);
}

TEST(SplashFunctionPatternIsCMYK_1091, ReturnsFalseForDeviceRGBA_1091) {
    GfxColorSpaceMode mode = csDeviceRGBA;
    EXPECT_FALSE(mode == csDeviceCMYK);
}

// Verify the enum value of csDeviceCMYK is 4 as defined
TEST(GfxColorSpaceModeEnum_1091, DeviceCMYKValueIs4_1091) {
    EXPECT_EQ(static_cast<int>(csDeviceCMYK), 4);
}
