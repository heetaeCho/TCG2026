#include <gtest/gtest.h>
#include "GfxState.h"

class GfxDeviceCMYKColorSpaceTest_444 : public ::testing::Test {
protected:
    GfxDeviceCMYKColorSpace cmykCS;
};

// Test that useGetCMYKLine returns true
TEST_F(GfxDeviceCMYKColorSpaceTest_444, UseGetCMYKLineReturnsTrue_444) {
    EXPECT_TRUE(cmykCS.useGetCMYKLine());
}

// Test that getMode returns the correct mode for CMYK
TEST_F(GfxDeviceCMYKColorSpaceTest_444, GetModeReturnsCMYK_444) {
    EXPECT_EQ(cmykCS.getMode(), csDeviceCMYK);
}

// Test that getNComps returns 4 for CMYK
TEST_F(GfxDeviceCMYKColorSpaceTest_444, GetNCompsReturnsFour_444) {
    EXPECT_EQ(cmykCS.getNComps(), 4);
}

// Test that useGetRGBLine returns true
TEST_F(GfxDeviceCMYKColorSpaceTest_444, UseGetRGBLineReturnsTrue_444) {
    EXPECT_TRUE(cmykCS.useGetRGBLine());
}

// Test that useGetDeviceNLine returns true
TEST_F(GfxDeviceCMYKColorSpaceTest_444, UseGetDeviceNLineReturnsTrue_444) {
    EXPECT_TRUE(cmykCS.useGetDeviceNLine());
}

// Test that copy produces a valid non-null copy
TEST_F(GfxDeviceCMYKColorSpaceTest_444, CopyProducesValidObject_444) {
    auto copied = cmykCS.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csDeviceCMYK);
    EXPECT_EQ(copied->getNComps(), 4);
}

// Test that copied object also returns true for useGetCMYKLine
TEST_F(GfxDeviceCMYKColorSpaceTest_444, CopiedObjectUseGetCMYKLine_444) {
    auto copied = cmykCS.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->useGetCMYKLine());
}

// Test getDefaultColor sets expected default values
TEST_F(GfxDeviceCMYKColorSpaceTest_444, GetDefaultColorSetsDefaults_444) {
    GfxColor color;
    cmykCS.getDefaultColor(&color);
    // Default CMYK color should be (0, 0, 0, 1) representing black
    // c[0]=0, c[1]=0, c[2]=0, c[3]=65535 (1.0 in fixed point)
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
    EXPECT_EQ(color.c[3], 65535);
}

// Test getCMYK returns the same color components
TEST_F(GfxDeviceCMYKColorSpaceTest_444, GetCMYKReturnsIdentity_444) {
    GfxColor color;
    color.c[0] = 10000;
    color.c[1] = 20000;
    color.c[2] = 30000;
    color.c[3] = 40000;

    GfxCMYK cmyk;
    cmykCS.getCMYK(&color, &cmyk);
    EXPECT_EQ(cmyk.c, 10000);
    EXPECT_EQ(cmyk.m, 20000);
    EXPECT_EQ(cmyk.y, 30000);
    EXPECT_EQ(cmyk.k, 40000);
}

// Test getGray with a default (black) color
TEST_F(GfxDeviceCMYKColorSpaceTest_444, GetGrayWithBlack_444) {
    GfxColor color;
    cmykCS.getDefaultColor(&color);

    GfxGray gray;
    cmykCS.getGray(&color, &gray);
    // Black color (K=1) should produce gray = 0
    EXPECT_EQ(gray, 0);
}

// Test getGray with white color (all zeros)
TEST_F(GfxDeviceCMYKColorSpaceTest_444, GetGrayWithWhite_444) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    color.c[3] = 0;

    GfxGray gray;
    cmykCS.getGray(&color, &gray);
    // White in CMYK (0,0,0,0) should produce gray = 65535 (1.0)
    EXPECT_EQ(gray, 65535);
}

// Test getRGB with white color
TEST_F(GfxDeviceCMYKColorSpaceTest_444, GetRGBWithWhite_444) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    color.c[3] = 0;

    GfxRGB rgb;
    cmykCS.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 65535);
    EXPECT_EQ(rgb.g, 65535);
    EXPECT_EQ(rgb.b, 65535);
}

// Test getCMYKLine with known input
TEST_F(GfxDeviceCMYKColorSpaceTest_444, GetCMYKLineIdentity_444) {
    unsigned char in[] = { 100, 150, 200, 50 };
    unsigned char out[4] = { 0 };
    cmykCS.getCMYKLine(in, out, 1);
    EXPECT_EQ(out[0], 100);
    EXPECT_EQ(out[1], 150);
    EXPECT_EQ(out[2], 200);
    EXPECT_EQ(out[3], 50);
}

// Test getCMYKLine with multiple pixels
TEST_F(GfxDeviceCMYKColorSpaceTest_444, GetCMYKLineMultiplePixels_444) {
    unsigned char in[] = { 0, 0, 0, 0, 255, 255, 255, 255 };
    unsigned char out[8] = { 0 };
    cmykCS.getCMYKLine(in, out, 2);
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    EXPECT_EQ(out[3], 0);
    EXPECT_EQ(out[4], 255);
    EXPECT_EQ(out[5], 255);
    EXPECT_EQ(out[6], 255);
    EXPECT_EQ(out[7], 255);
}

// Test getRGBLine (unsigned int* version) with zero length
TEST_F(GfxDeviceCMYKColorSpaceTest_444, GetRGBLineZeroLength_444) {
    unsigned char in[4] = { 0 };
    unsigned int out[1] = { 0xDEADBEEF };
    cmykCS.getRGBLine(in, out, 0);
    // With zero length, output should remain unchanged
    EXPECT_EQ(out[0], 0xDEADBEEF);
}

// Test getRGBLine (unsigned char* version) with white CMYK input
TEST_F(GfxDeviceCMYKColorSpaceTest_444, GetRGBLineUcharWhite_444) {
    unsigned char in[] = { 0, 0, 0, 0 };
    unsigned char out[3] = { 0 };
    cmykCS.getRGBLine(in, out, 1);
    EXPECT_EQ(out[0], 255);
    EXPECT_EQ(out[1], 255);
    EXPECT_EQ(out[2], 255);
}

// Test getRGBXLine with white CMYK input
TEST_F(GfxDeviceCMYKColorSpaceTest_444, GetRGBXLineWhite_444) {
    unsigned char in[] = { 0, 0, 0, 0 };
    unsigned char out[4] = { 0 };
    cmykCS.getRGBXLine(in, out, 1);
    EXPECT_EQ(out[0], 255);
    EXPECT_EQ(out[1], 255);
    EXPECT_EQ(out[2], 255);
    EXPECT_EQ(out[3], 255);
}

// Test getDeviceN with a color
TEST_F(GfxDeviceCMYKColorSpaceTest_444, GetDeviceNColor_444) {
    GfxColor color;
    color.c[0] = 10000;
    color.c[1] = 20000;
    color.c[2] = 30000;
    color.c[3] = 40000;

    GfxColor deviceN;
    // Initialize all components to a known value
    for (int i = 0; i < gfxColorMaxComps; i++) {
        deviceN.c[i] = 0;
    }
    cmykCS.getDeviceN(&color, &deviceN);
    // CMYK components should be set in deviceN
    EXPECT_EQ(deviceN.c[0], 10000);
    EXPECT_EQ(deviceN.c[1], 20000);
    EXPECT_EQ(deviceN.c[2], 30000);
    EXPECT_EQ(deviceN.c[3], 40000);
}

// Test getDeviceNLine
TEST_F(GfxDeviceCMYKColorSpaceTest_444, GetDeviceNLine_444) {
    unsigned char in[] = { 100, 150, 200, 50 };
    // DeviceN typically has up to 8 components per pixel (CMYK + spot colors)
    unsigned char out[gfxColorMaxComps + 4] = { 0 };
    cmykCS.getDeviceNLine(in, out, 1);
    EXPECT_EQ(out[0], 100);
    EXPECT_EQ(out[1], 150);
    EXPECT_EQ(out[2], 200);
    EXPECT_EQ(out[3], 50);
}

// Test getRGB with black CMYK color
TEST_F(GfxDeviceCMYKColorSpaceTest_444, GetRGBWithBlack_444) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    color.c[3] = 65535;

    GfxRGB rgb;
    cmykCS.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGBLine (unsigned int* version) with white input
TEST_F(GfxDeviceCMYKColorSpaceTest_444, GetRGBLineUintWhite_444) {
    unsigned char in[] = { 0, 0, 0, 0 };
    unsigned int out[1] = { 0 };
    cmykCS.getRGBLine(in, out, 1);
    // Expected: white pixel packed as 0x00RRGGBB or 0xFFRRGGBB format
    // Check that all RGB components are 255
    unsigned int pixel = out[0];
    unsigned char r = (pixel >> 16) & 0xFF;
    unsigned char g = (pixel >> 8) & 0xFF;
    unsigned char b = pixel & 0xFF;
    EXPECT_EQ(r, 255);
    EXPECT_EQ(g, 255);
    EXPECT_EQ(b, 255);
}
