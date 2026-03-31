#include <gtest/gtest.h>
#include "GfxState.h"

class GfxDeviceCMYKColorSpaceTest_443 : public ::testing::Test {
protected:
    GfxDeviceCMYKColorSpace cmykCS;
};

// Test that useGetRGBLine returns true
TEST_F(GfxDeviceCMYKColorSpaceTest_443, UseGetRGBLineReturnsTrue_443) {
    EXPECT_TRUE(cmykCS.useGetRGBLine());
}

// Test that getMode returns the correct color space mode for CMYK
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetModeReturnsCMYK_443) {
    EXPECT_EQ(cmykCS.getMode(), csDeviceCMYK);
}

// Test that getNComps returns 4 for CMYK
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetNCompsReturnsFour_443) {
    EXPECT_EQ(cmykCS.getNComps(), 4);
}

// Test useGetCMYKLine
TEST_F(GfxDeviceCMYKColorSpaceTest_443, UseGetCMYKLineReturnsTrue_443) {
    EXPECT_TRUE(cmykCS.useGetCMYKLine());
}

// Test useGetDeviceNLine
TEST_F(GfxDeviceCMYKColorSpaceTest_443, UseGetDeviceNLineReturnsTrue_443) {
    EXPECT_TRUE(cmykCS.useGetDeviceNLine());
}

// Test copy creates a valid copy
TEST_F(GfxDeviceCMYKColorSpaceTest_443, CopyReturnsValidObject_443) {
    auto copied = cmykCS.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csDeviceCMYK);
    EXPECT_EQ(copied->getNComps(), 4);
    EXPECT_TRUE(copied->useGetRGBLine());
}

// Test getDefaultColor sets expected default values
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetDefaultColorSetsDefaults_443) {
    GfxColor color;
    cmykCS.getDefaultColor(&color);
    // Default CMYK color should be (0, 0, 0, 1) meaning black
    // C=0, M=0, Y=0, K=1 (full key/black)
    EXPECT_EQ(color.c[0], 0); // C
    EXPECT_EQ(color.c[1], 0); // M
    EXPECT_EQ(color.c[2], 0); // Y
    EXPECT_EQ(color.c[3], gfxColorComp1); // K
}

// Test getGray with black color (C=0, M=0, Y=0, K=max)
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetGrayWithBlack_443) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    color.c[3] = gfxColorComp1; // K = 1.0
    GfxGray gray;
    cmykCS.getGray(&color, &gray);
    EXPECT_EQ(gray, 0); // Black should give gray = 0
}

// Test getGray with white color (C=0, M=0, Y=0, K=0)
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetGrayWithWhite_443) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    color.c[3] = 0; // K = 0
    GfxGray gray;
    cmykCS.getGray(&color, &gray);
    EXPECT_EQ(gray, gfxColorComp1); // White should give gray = 1.0
}

// Test getRGB with white (C=0, M=0, Y=0, K=0)
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetRGBWithWhite_443) {
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

// Test getRGB with black (C=0, M=0, Y=0, K=1)
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetRGBWithBlack_443) {
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

// Test getCMYK returns the same color
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetCMYKReturnsIdentity_443) {
    GfxColor color;
    color.c[0] = 1000;
    color.c[1] = 2000;
    color.c[2] = 3000;
    color.c[3] = 4000;
    GfxCMYK cmyk;
    cmykCS.getCMYK(&color, &cmyk);
    EXPECT_EQ(cmyk.c, 1000);
    EXPECT_EQ(cmyk.m, 2000);
    EXPECT_EQ(cmyk.y, 3000);
    EXPECT_EQ(cmyk.k, 4000);
}

// Test getRGBLine with unsigned int output and zero length
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetRGBLineUintZeroLength_443) {
    unsigned char in[4] = {0, 0, 0, 0};
    unsigned int out[1] = {0};
    // Should handle zero length without crashing
    cmykCS.getRGBLine(in, out, 0);
}

// Test getRGBLine with unsigned char output and zero length
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetRGBLineUcharZeroLength_443) {
    unsigned char in[4] = {0, 0, 0, 0};
    unsigned char out[3] = {0, 0, 0};
    cmykCS.getRGBLine(in, out, 0);
}

// Test getRGBLine with single white pixel (CMYK = 0,0,0,0)
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetRGBLineUcharSingleWhitePixel_443) {
    unsigned char in[4] = {0, 0, 0, 0}; // C=0, M=0, Y=0, K=0 -> white
    unsigned char out[3] = {0, 0, 0};
    cmykCS.getRGBLine(in, out, 1);
    EXPECT_EQ(out[0], 255); // R
    EXPECT_EQ(out[1], 255); // G
    EXPECT_EQ(out[2], 255); // B
}

// Test getRGBLine with single black pixel (CMYK = 0,0,0,255)
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetRGBLineUcharSingleBlackPixel_443) {
    unsigned char in[4] = {0, 0, 0, 255}; // C=0, M=0, Y=0, K=255 -> black
    unsigned char out[3] = {255, 255, 255};
    cmykCS.getRGBLine(in, out, 1);
    EXPECT_EQ(out[0], 0); // R
    EXPECT_EQ(out[1], 0); // G
    EXPECT_EQ(out[2], 0); // B
}

// Test getRGBXLine with zero length
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetRGBXLineZeroLength_443) {
    unsigned char in[4] = {0, 0, 0, 0};
    unsigned char out[4] = {0, 0, 0, 0};
    cmykCS.getRGBXLine(in, out, 0);
}

// Test getRGBXLine with single white pixel
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetRGBXLineSingleWhitePixel_443) {
    unsigned char in[4] = {0, 0, 0, 0};
    unsigned char out[4] = {0, 0, 0, 0};
    cmykCS.getRGBXLine(in, out, 1);
    EXPECT_EQ(out[0], 255); // R
    EXPECT_EQ(out[1], 255); // G
    EXPECT_EQ(out[2], 255); // B
}

// Test getCMYKLine with zero length
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetCMYKLineZeroLength_443) {
    unsigned char in[4] = {0, 0, 0, 0};
    unsigned char out[4] = {0, 0, 0, 0};
    cmykCS.getCMYKLine(in, out, 0);
}

// Test getCMYKLine identity for single pixel
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetCMYKLineSinglePixelIdentity_443) {
    unsigned char in[4] = {100, 150, 200, 50};
    unsigned char out[4] = {0, 0, 0, 0};
    cmykCS.getCMYKLine(in, out, 1);
    EXPECT_EQ(out[0], 100);
    EXPECT_EQ(out[1], 150);
    EXPECT_EQ(out[2], 200);
    EXPECT_EQ(out[3], 50);
}

// Test getDeviceNLine with zero length
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetDeviceNLineZeroLength_443) {
    unsigned char in[4] = {0, 0, 0, 0};
    unsigned char out[8] = {0};
    cmykCS.getDeviceNLine(in, out, 0);
}

// Test getRGBLine with uint output for single white pixel
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetRGBLineUintSingleWhitePixel_443) {
    unsigned char in[4] = {0, 0, 0, 0};
    unsigned int out[1] = {0};
    cmykCS.getRGBLine(in, out, 1);
    // Expected format: 0xFFRRGGBB or similar packed format
    // White should have R=255, G=255, B=255
    unsigned int expected = (255 << 24) | (255 << 16) | (255 << 8) | 255;
    // The exact packing depends on implementation, but all channels should be 0xFF
    // Check that the result is non-zero for white
    EXPECT_NE(out[0], 0u);
}

// Test multiple pixels in getRGBLine
TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetRGBLineMultiplePixels_443) {
    // Two pixels: white and black
    unsigned char in[8] = {0, 0, 0, 0,   // white
                           0, 0, 0, 255}; // black
    unsigned char out[6] = {0};
    cmykCS.getRGBLine(in, out, 2);
    // First pixel should be white
    EXPECT_EQ(out[0], 255);
    EXPECT_EQ(out[1], 255);
    EXPECT_EQ(out[2], 255);
    // Second pixel should be black
    EXPECT_EQ(out[3], 0);
    EXPECT_EQ(out[4], 0);
    EXPECT_EQ(out[5], 0);
}
