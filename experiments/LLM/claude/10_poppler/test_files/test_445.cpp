#include <gtest/gtest.h>
#include "GfxState.h"

class GfxDeviceCMYKColorSpaceTest_445 : public ::testing::Test {
protected:
    GfxDeviceCMYKColorSpace cmykCS;
};

// Test that useGetDeviceNLine returns true
TEST_F(GfxDeviceCMYKColorSpaceTest_445, UseGetDeviceNLineReturnsTrue_445) {
    EXPECT_TRUE(cmykCS.useGetDeviceNLine());
}

// Test that getMode returns the correct color space mode for CMYK
TEST_F(GfxDeviceCMYKColorSpaceTest_445, GetModeReturnsCMYK_445) {
    EXPECT_EQ(cmykCS.getMode(), csDeviceCMYK);
}

// Test that getNComps returns 4 for CMYK
TEST_F(GfxDeviceCMYKColorSpaceTest_445, GetNCompsReturnsFour_445) {
    EXPECT_EQ(cmykCS.getNComps(), 4);
}

// Test that useGetRGBLine returns true
TEST_F(GfxDeviceCMYKColorSpaceTest_445, UseGetRGBLineReturnsTrue_445) {
    EXPECT_TRUE(cmykCS.useGetRGBLine());
}

// Test that useGetCMYKLine returns true
TEST_F(GfxDeviceCMYKColorSpaceTest_445, UseGetCMYKLineReturnsTrue_445) {
    EXPECT_TRUE(cmykCS.useGetCMYKLine());
}

// Test copy produces a valid copy
TEST_F(GfxDeviceCMYKColorSpaceTest_445, CopyProducesValidObject_445) {
    auto copied = cmykCS.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csDeviceCMYK);
    EXPECT_EQ(copied->getNComps(), 4);
    EXPECT_TRUE(copied->useGetDeviceNLine());
    EXPECT_TRUE(copied->useGetRGBLine());
    EXPECT_TRUE(copied->useGetCMYKLine());
}

// Test getDefaultColor sets expected default values
TEST_F(GfxDeviceCMYKColorSpaceTest_445, GetDefaultColorSetsValues_445) {
    GfxColor color;
    cmykCS.getDefaultColor(&color);
    // Default CMYK color should be (0,0,0,1) which represents black
    // c[0]=0, c[1]=0, c[2]=0, c[3]=65535 (GfxColorComp max)
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
    EXPECT_EQ(color.c[3], gfxColorComp1);
}

// Test getGray for black color (C=0, M=0, Y=0, K=max)
TEST_F(GfxDeviceCMYKColorSpaceTest_445, GetGrayBlack_445) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    color.c[3] = gfxColorComp1;  // K=1 -> black
    GfxGray gray;
    cmykCS.getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getGray for white color (C=0, M=0, Y=0, K=0)
TEST_F(GfxDeviceCMYKColorSpaceTest_445, GetGrayWhite_445) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    color.c[3] = 0;  // K=0 -> white
    GfxGray gray;
    cmykCS.getGray(&color, &gray);
    EXPECT_EQ(gray, gfxColorComp1);
}

// Test getRGB for white color (C=0, M=0, Y=0, K=0)
TEST_F(GfxDeviceCMYKColorSpaceTest_445, GetRGBWhite_445) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    color.c[3] = 0;
    GfxRGB rgb;
    cmykCS.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, gfxColorComp1);
    EXPECT_EQ(rgb.g, gfxColorComp1);
    EXPECT_EQ(rgb.b, gfxColorComp1);
}

// Test getRGB for black color (C=0, M=0, Y=0, K=max)
TEST_F(GfxDeviceCMYKColorSpaceTest_445, GetRGBBlack_445) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    color.c[3] = gfxColorComp1;
    GfxRGB rgb;
    cmykCS.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getCMYK returns the same CMYK values passed in
TEST_F(GfxDeviceCMYKColorSpaceTest_445, GetCMYKIdentity_445) {
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

// Test getDeviceN for a CMYK color
TEST_F(GfxDeviceCMYKColorSpaceTest_445, GetDeviceN_445) {
    GfxColor color;
    color.c[0] = 10000;
    color.c[1] = 20000;
    color.c[2] = 30000;
    color.c[3] = 40000;
    GfxColor deviceN;
    // Initialize deviceN to zeros
    for (int i = 0; i < gfxColorMaxComps; i++) {
        deviceN.c[i] = 0;
    }
    cmykCS.getDeviceN(&color, &deviceN);
    // DeviceN should contain the CMYK values in the first 4 components
    EXPECT_EQ(deviceN.c[0], 10000);
    EXPECT_EQ(deviceN.c[1], 20000);
    EXPECT_EQ(deviceN.c[2], 30000);
    EXPECT_EQ(deviceN.c[3], 40000);
}

// Test getRGBLine (unsigned int* out) with a single white pixel
TEST_F(GfxDeviceCMYKColorSpaceTest_445, GetRGBLineUintWhite_445) {
    unsigned char in[4] = {0, 0, 0, 0}; // C=0, M=0, Y=0, K=0 -> white
    unsigned int out[1] = {0};
    cmykCS.getRGBLine(in, out, 1);
    // Expected: white pixel in ARGB or similar packed format
    // White should have R=255, G=255, B=255
    unsigned int r = (out[0] >> 16) & 0xFF;
    unsigned int g = (out[0] >> 8) & 0xFF;
    unsigned int b = out[0] & 0xFF;
    EXPECT_EQ(r, 255);
    EXPECT_EQ(g, 255);
    EXPECT_EQ(b, 255);
}

// Test getRGBLine (unsigned int* out) with a single black pixel
TEST_F(GfxDeviceCMYKColorSpaceTest_445, GetRGBLineUintBlack_445) {
    unsigned char in[4] = {0, 0, 0, 255}; // C=0, M=0, Y=0, K=255 -> black
    unsigned int out[1] = {0};
    cmykCS.getRGBLine(in, out, 1);
    unsigned int r = (out[0] >> 16) & 0xFF;
    unsigned int g = (out[0] >> 8) & 0xFF;
    unsigned int b = out[0] & 0xFF;
    EXPECT_EQ(r, 0);
    EXPECT_EQ(g, 0);
    EXPECT_EQ(b, 0);
}

// Test getRGBLine (unsigned char* out) with white
TEST_F(GfxDeviceCMYKColorSpaceTest_445, GetRGBLineUcharWhite_445) {
    unsigned char in[4] = {0, 0, 0, 0};
    unsigned char out[3] = {0, 0, 0};
    cmykCS.getRGBLine(in, out, 1);
    EXPECT_EQ(out[0], 255);
    EXPECT_EQ(out[1], 255);
    EXPECT_EQ(out[2], 255);
}

// Test getRGBXLine with white pixel
TEST_F(GfxDeviceCMYKColorSpaceTest_445, GetRGBXLineWhite_445) {
    unsigned char in[4] = {0, 0, 0, 0};
    unsigned char out[4] = {0, 0, 0, 0};
    cmykCS.getRGBXLine(in, out, 1);
    EXPECT_EQ(out[0], 255);
    EXPECT_EQ(out[1], 255);
    EXPECT_EQ(out[2], 255);
    // out[3] is the X component, usually 255
    EXPECT_EQ(out[3], 255);
}

// Test getCMYKLine identity
TEST_F(GfxDeviceCMYKColorSpaceTest_445, GetCMYKLineIdentity_445) {
    unsigned char in[4] = {10, 20, 30, 40};
    unsigned char out[4] = {0, 0, 0, 0};
    cmykCS.getCMYKLine(in, out, 1);
    EXPECT_EQ(out[0], 10);
    EXPECT_EQ(out[1], 20);
    EXPECT_EQ(out[2], 30);
    EXPECT_EQ(out[3], 40);
}

// Test getDeviceNLine
TEST_F(GfxDeviceCMYKColorSpaceTest_445, GetDeviceNLine_445) {
    unsigned char in[4] = {10, 20, 30, 40};
    unsigned char out[gfxColorMaxComps] = {};
    cmykCS.getDeviceNLine(in, out, 1);
    EXPECT_EQ(out[0], 10);
    EXPECT_EQ(out[1], 20);
    EXPECT_EQ(out[2], 30);
    EXPECT_EQ(out[3], 40);
}

// Test with zero-length lines (boundary)
TEST_F(GfxDeviceCMYKColorSpaceTest_445, ZeroLengthRGBLine_445) {
    unsigned char in[1] = {0};
    unsigned int out[1] = {0xDEADBEEF};
    cmykCS.getRGBLine(in, out, 0);
    // Output should remain unchanged
    EXPECT_EQ(out[0], 0xDEADBEEF);
}

// Test with multiple pixels
TEST_F(GfxDeviceCMYKColorSpaceTest_445, MultiplePixelsRGBLine_445) {
    // Two pixels: white and black
    unsigned char in[8] = {0, 0, 0, 0, 0, 0, 0, 255};
    unsigned int out[2] = {0, 0};
    cmykCS.getRGBLine(in, out, 2);
    
    // First pixel: white
    unsigned int r1 = (out[0] >> 16) & 0xFF;
    unsigned int g1 = (out[0] >> 8) & 0xFF;
    unsigned int b1 = out[0] & 0xFF;
    EXPECT_EQ(r1, 255);
    EXPECT_EQ(g1, 255);
    EXPECT_EQ(b1, 255);
    
    // Second pixel: black
    unsigned int r2 = (out[1] >> 16) & 0xFF;
    unsigned int g2 = (out[1] >> 8) & 0xFF;
    unsigned int b2 = out[1] & 0xFF;
    EXPECT_EQ(r2, 0);
    EXPECT_EQ(g2, 0);
    EXPECT_EQ(b2, 0);
}
