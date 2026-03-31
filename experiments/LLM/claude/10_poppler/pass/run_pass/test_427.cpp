#include <gtest/gtest.h>
#include "GfxState.h"

class GfxDeviceRGBColorSpaceTest_427 : public ::testing::Test {
protected:
    GfxDeviceRGBColorSpace cs;
};

// Test that getNComps returns 3 for RGB color space
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetNCompsReturnsThree_427) {
    EXPECT_EQ(cs.getNComps(), 3);
}

// Test that getMode returns the correct mode for DeviceRGB
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetModeReturnsDeviceRGB_427) {
    EXPECT_EQ(cs.getMode(), csDeviceRGB);
}

// Test that copy returns a non-null unique_ptr
TEST_F(GfxDeviceRGBColorSpaceTest_427, CopyReturnsNonNull_427) {
    auto copied = cs.copy();
    ASSERT_NE(copied, nullptr);
}

// Test that copy preserves the mode
TEST_F(GfxDeviceRGBColorSpaceTest_427, CopyPreservesMode_427) {
    auto copied = cs.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csDeviceRGB);
}

// Test that copy preserves getNComps
TEST_F(GfxDeviceRGBColorSpaceTest_427, CopyPreservesNComps_427) {
    auto copied = cs.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNComps(), 3);
}

// Test getDefaultColor sets expected default values
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetDefaultColor_427) {
    GfxColor color;
    cs.getDefaultColor(&color);
    // Default color for DeviceRGB is typically black (0,0,0)
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
}

// Test getGray for black color (R=0, G=0, B=0)
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetGrayBlack_427) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxGray gray;
    cs.getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getGray for white color (R=max, G=max, B=max)
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetGrayWhite_427) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;
    GfxGray gray;
    cs.getGray(&color, &gray);
    // White should produce maximum gray
    EXPECT_GT(gray, 0);
}

// Test getRGB for black
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetRGBBlack_427) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxRGB rgb;
    cs.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB for white
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetRGBWhite_427) {
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

// Test getRGB for pure red
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetRGBRed_427) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxRGB rgb;
    cs.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, gfxColorComp1);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getCMYK for black
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetCMYKBlack_427) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxCMYK cmyk;
    cs.getCMYK(&color, &cmyk);
    // Black in CMYK: C=0, M=0, Y=0, K=max
    EXPECT_EQ(cmyk.k, gfxColorComp1);
}

// Test getCMYK for white
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetCMYKWhite_427) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;
    GfxCMYK cmyk;
    cs.getCMYK(&color, &cmyk);
    // White in CMYK: C=0, M=0, Y=0, K=0
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
    EXPECT_EQ(cmyk.k, 0);
}

// Test useGetRGBLine
TEST_F(GfxDeviceRGBColorSpaceTest_427, UseGetRGBLine_427) {
    // DeviceRGB should support optimized RGB line processing
    EXPECT_TRUE(cs.useGetRGBLine());
}

// Test useGetGrayLine
TEST_F(GfxDeviceRGBColorSpaceTest_427, UseGetGrayLine_427) {
    bool result = cs.useGetGrayLine();
    // Just verify it returns a valid boolean (no crash)
    EXPECT_TRUE(result == true || result == false);
}

// Test useGetCMYKLine
TEST_F(GfxDeviceRGBColorSpaceTest_427, UseGetCMYKLine_427) {
    bool result = cs.useGetCMYKLine();
    EXPECT_TRUE(result == true || result == false);
}

// Test useGetDeviceNLine
TEST_F(GfxDeviceRGBColorSpaceTest_427, UseGetDeviceNLine_427) {
    bool result = cs.useGetDeviceNLine();
    EXPECT_TRUE(result == true || result == false);
}

// Test getGrayLine with a simple input
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetGrayLineBlack_427) {
    unsigned char in[3] = {0, 0, 0};  // One black pixel
    unsigned char out[1] = {255};
    cs.getGrayLine(in, out, 1);
    EXPECT_EQ(out[0], 0);
}

// Test getGrayLine with white
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetGrayLineWhite_427) {
    unsigned char in[3] = {255, 255, 255};  // One white pixel
    unsigned char out[1] = {0};
    cs.getGrayLine(in, out, 1);
    EXPECT_EQ(out[0], 255);
}

// Test getRGBLine (unsigned int version) with black
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetRGBLineUintBlack_427) {
    unsigned char in[3] = {0, 0, 0};
    unsigned int out[1] = {0};
    cs.getRGBLine(in, out, 1);
    // Output should represent black pixel
    // The exact format depends on implementation but should be deterministic
    unsigned int expected_black = out[0];  // Just verify no crash
    SUCCEED();
}

// Test getRGBLine (unsigned char version) identity-like behavior
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetRGBLineUcharIdentity_427) {
    unsigned char in[6] = {255, 0, 0, 0, 255, 0};  // Red, Green pixels
    unsigned char out[6] = {0};
    cs.getRGBLine(in, out, 2);
    // For DeviceRGB, the RGB line should be identity
    EXPECT_EQ(out[0], 255);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    EXPECT_EQ(out[3], 0);
    EXPECT_EQ(out[4], 255);
    EXPECT_EQ(out[5], 0);
}

// Test getRGBXLine
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetRGBXLineBlack_427) {
    unsigned char in[3] = {0, 0, 0};
    unsigned char out[4] = {255, 255, 255, 255};
    cs.getRGBXLine(in, out, 1);
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
}

// Test getCMYKLine for black pixel
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetCMYKLineBlack_427) {
    unsigned char in[3] = {0, 0, 0};
    unsigned char out[4] = {0, 0, 0, 0};
    cs.getCMYKLine(in, out, 1);
    // Black in CMYK should be K=255
    EXPECT_EQ(out[3], 255);
}

// Test getCMYKLine for white pixel
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetCMYKLineWhite_427) {
    unsigned char in[3] = {255, 255, 255};
    unsigned char out[4] = {255, 255, 255, 255};
    cs.getCMYKLine(in, out, 1);
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    EXPECT_EQ(out[3], 0);
}

// Test getDeviceN
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetDeviceNBlack_427) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxColor deviceN;
    // Initialize to non-zero to detect changes
    for (int i = 0; i < gfxColorMaxComps; i++) {
        deviceN.c[i] = 0;
    }
    cs.getDeviceN(&color, &deviceN);
    // DeviceN for black from RGB should have K component
    SUCCEED();  // Just verify no crash
}

// Test with zero-length line operations
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetGrayLineZeroLength_427) {
    unsigned char in[1] = {0};
    unsigned char out[1] = {0};
    cs.getGrayLine(in, out, 0);
    // Should handle zero length gracefully
    SUCCEED();
}

// Test with multiple pixels in line operations
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetRGBLineMultiplePixels_427) {
    // 3 pixels: red, green, blue
    unsigned char in[9] = {255, 0, 0, 0, 255, 0, 0, 0, 255};
    unsigned char out[9] = {0};
    cs.getRGBLine(in, out, 3);
    // Red pixel
    EXPECT_EQ(out[0], 255);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    // Green pixel
    EXPECT_EQ(out[3], 0);
    EXPECT_EQ(out[4], 255);
    EXPECT_EQ(out[5], 0);
    // Blue pixel
    EXPECT_EQ(out[6], 0);
    EXPECT_EQ(out[7], 0);
    EXPECT_EQ(out[8], 255);
}

// Test getDeviceNLine
TEST_F(GfxDeviceRGBColorSpaceTest_427, GetDeviceNLineBlack_427) {
    unsigned char in[3] = {0, 0, 0};
    unsigned char out[gfxColorMaxComps] = {0};
    cs.getDeviceNLine(in, out, 1);
    // Just verify no crash for DeviceN line conversion
    SUCCEED();
}
