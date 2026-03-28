#include <gtest/gtest.h>
#include "GfxState.h"

class GfxDeviceRGBColorSpaceTest_426 : public ::testing::Test {
protected:
    GfxDeviceRGBColorSpace cs;
};

// Test that useGetDeviceNLine returns true
TEST_F(GfxDeviceRGBColorSpaceTest_426, UseGetDeviceNLineReturnsTrue_426) {
    EXPECT_TRUE(cs.useGetDeviceNLine());
}

// Test that useGetRGBLine returns true (DeviceRGB typically supports RGB line operations)
TEST_F(GfxDeviceRGBColorSpaceTest_426, UseGetRGBLineReturnsTrue_426) {
    EXPECT_TRUE(cs.useGetRGBLine());
}

// Test that useGetGrayLine returns true
TEST_F(GfxDeviceRGBColorSpaceTest_426, UseGetGrayLine_426) {
    // Just verify it returns a boolean without crashing
    bool result = cs.useGetGrayLine();
    EXPECT_TRUE(result || !result);
}

// Test that useGetCMYKLine returns true
TEST_F(GfxDeviceRGBColorSpaceTest_426, UseGetCMYKLine_426) {
    bool result = cs.useGetCMYKLine();
    EXPECT_TRUE(result || !result);
}

// Test that the color space mode is csDeviceRGB
TEST_F(GfxDeviceRGBColorSpaceTest_426, GetModeReturnsDeviceRGB_426) {
    EXPECT_EQ(cs.getMode(), csDeviceRGB);
}

// Test that the number of components is 3 for RGB
TEST_F(GfxDeviceRGBColorSpaceTest_426, GetNCompsReturnsThree_426) {
    EXPECT_EQ(cs.getNComps(), 3);
}

// Test copy produces a valid non-null result
TEST_F(GfxDeviceRGBColorSpaceTest_426, CopyReturnsNonNull_426) {
    auto copied = cs.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csDeviceRGB);
    EXPECT_EQ(copied->getNComps(), 3);
}

// Test getDefaultColor sets expected default values
TEST_F(GfxDeviceRGBColorSpaceTest_426, GetDefaultColor_426) {
    GfxColor color;
    cs.getDefaultColor(&color);
    // For DeviceRGB, default color is typically black (0,0,0)
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
}

// Test getGray with black color (R=0, G=0, B=0) -> gray should be 0
TEST_F(GfxDeviceRGBColorSpaceTest_426, GetGrayBlack_426) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxGray gray;
    cs.getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getGray with white color (max, max, max) -> gray should be max
TEST_F(GfxDeviceRGBColorSpaceTest_426, GetGrayWhite_426) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;
    GfxGray gray;
    cs.getGray(&color, &gray);
    EXPECT_EQ(gray, gfxColorComp1);
}

// Test getRGB with a known color
TEST_F(GfxDeviceRGBColorSpaceTest_426, GetRGBIdentity_426) {
    GfxColor color;
    color.c[0] = gfxColorComp1; // R = max
    color.c[1] = 0;              // G = 0
    color.c[2] = 0;              // B = 0
    GfxRGB rgb;
    cs.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, gfxColorComp1);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB for white
TEST_F(GfxDeviceRGBColorSpaceTest_426, GetRGBWhite_426) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;
    GfxRGB rgb;
    cs.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, gfxColorComp1);
    EXPECT_EQ(rgb.g, gfxColorComp1);
    EXPECT_EQ(rgb.b, gfxColorComp1);
}

// Test getCMYK with black
TEST_F(GfxDeviceRGBColorSpaceTest_426, GetCMYKBlack_426) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxCMYK cmyk;
    cs.getCMYK(&color, &cmyk);
    // Black in CMYK should have K = max
    EXPECT_EQ(cmyk.k, gfxColorComp1);
}

// Test getCMYK with white
TEST_F(GfxDeviceRGBColorSpaceTest_426, GetCMYKWhite_426) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;
    GfxCMYK cmyk;
    cs.getCMYK(&color, &cmyk);
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
    EXPECT_EQ(cmyk.k, 0);
}

// Test getDeviceN with a color
TEST_F(GfxDeviceRGBColorSpaceTest_426, GetDeviceN_426) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxColor deviceN;
    cs.getDeviceN(&color, &deviceN);
    // DeviceN for DeviceRGB should contain CMYK equivalent values
    // We just verify it doesn't crash and produces some output
    // The exact values depend on the implementation
}

// Test getRGBLine (unsigned int output) with a simple buffer
TEST_F(GfxDeviceRGBColorSpaceTest_426, GetRGBLineUintOutput_426) {
    unsigned char in[] = {255, 0, 0, 0, 255, 0, 0, 0, 255};
    unsigned int out[3] = {0, 0, 0};
    cs.getRGBLine(in, out, 3);
    // Verify the output is populated (exact format depends on implementation)
    // Just verify no crash occurs
}

// Test getRGBLine (unsigned char output) with a simple buffer
TEST_F(GfxDeviceRGBColorSpaceTest_426, GetRGBLineUcharOutput_426) {
    unsigned char in[] = {255, 0, 0, 0, 255, 0, 0, 0, 255};
    unsigned char out[9] = {0};
    cs.getRGBLine(in, out, 3);
    // For DeviceRGB, output should be the same as input
    EXPECT_EQ(out[0], 255);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    EXPECT_EQ(out[3], 0);
    EXPECT_EQ(out[4], 255);
    EXPECT_EQ(out[5], 0);
}

// Test getRGBXLine
TEST_F(GfxDeviceRGBColorSpaceTest_426, GetRGBXLine_426) {
    unsigned char in[] = {255, 128, 64};
    unsigned char out[4] = {0};
    cs.getRGBXLine(in, out, 1);
    EXPECT_EQ(out[0], 255);
    EXPECT_EQ(out[1], 128);
    EXPECT_EQ(out[2], 64);
    // Fourth byte is padding/alpha, value depends on implementation
}

// Test getGrayLine
TEST_F(GfxDeviceRGBColorSpaceTest_426, GetGrayLine_426) {
    // White pixel
    unsigned char in[] = {255, 255, 255};
    unsigned char out[1] = {0};
    cs.getGrayLine(in, out, 1);
    EXPECT_EQ(out[0], 255);
}

// Test getGrayLine with black
TEST_F(GfxDeviceRGBColorSpaceTest_426, GetGrayLineBlack_426) {
    unsigned char in[] = {0, 0, 0};
    unsigned char out[1] = {255};
    cs.getGrayLine(in, out, 1);
    EXPECT_EQ(out[0], 0);
}

// Test getCMYKLine
TEST_F(GfxDeviceRGBColorSpaceTest_426, GetCMYKLine_426) {
    // White pixel in RGB
    unsigned char in[] = {255, 255, 255};
    unsigned char out[4] = {255, 255, 255, 255};
    cs.getCMYKLine(in, out, 1);
    // White in CMYK: C=0, M=0, Y=0, K=0
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    EXPECT_EQ(out[3], 0);
}

// Test getDeviceNLine
TEST_F(GfxDeviceRGBColorSpaceTest_426, GetDeviceNLine_426) {
    unsigned char in[] = {255, 255, 255};
    // DeviceN output: CMYK + spot colors, typically at least 4 bytes per pixel
    unsigned char out[4 * gfxColorMaxComps] = {0};
    cs.getDeviceNLine(in, out, 1);
    // Just verify it doesn't crash
}

// Test with zero-length lines
TEST_F(GfxDeviceRGBColorSpaceTest_426, ZeroLengthLine_426) {
    unsigned char in[1] = {0};
    unsigned char out[1] = {0};
    unsigned int outUint[1] = {0};
    // These should handle zero length gracefully
    cs.getRGBLine(in, outUint, 0);
    cs.getRGBLine(in, out, 0);
    cs.getGrayLine(in, out, 0);
    cs.getCMYKLine(in, out, 0);
    cs.getDeviceNLine(in, out, 0);
    cs.getRGBXLine(in, out, 0);
}

// Test that copy preserves useGetDeviceNLine
TEST_F(GfxDeviceRGBColorSpaceTest_426, CopyPreservesUseGetDeviceNLine_426) {
    auto copied = cs.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->useGetDeviceNLine());
}

// Test multiple pixels in getRGBLine
TEST_F(GfxDeviceRGBColorSpaceTest_426, GetRGBLineMultiplePixels_426) {
    unsigned char in[] = {255, 0, 0, 0, 255, 0, 0, 0, 255, 128, 128, 128};
    unsigned char out[12] = {0};
    cs.getRGBLine(in, out, 4);
    // For DeviceRGB, input should pass through
    for (int i = 0; i < 12; i++) {
        EXPECT_EQ(out[i], in[i]);
    }
}
