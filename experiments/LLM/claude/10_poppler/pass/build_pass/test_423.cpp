#include <gtest/gtest.h>
#include "GfxState.h"

class GfxDeviceRGBColorSpaceTest_423 : public ::testing::Test {
protected:
    GfxDeviceRGBColorSpace colorSpace;
};

// Test that useGetRGBLine returns true
TEST_F(GfxDeviceRGBColorSpaceTest_423, UseGetRGBLineReturnsTrue_423) {
    EXPECT_TRUE(colorSpace.useGetRGBLine());
}

// Test that getMode returns the correct mode for DeviceRGB
TEST_F(GfxDeviceRGBColorSpaceTest_423, GetModeReturnsDeviceRGB_423) {
    EXPECT_EQ(colorSpace.getMode(), csDeviceRGB);
}

// Test that getNComps returns 3 for RGB
TEST_F(GfxDeviceRGBColorSpaceTest_423, GetNCompsReturnsThree_423) {
    EXPECT_EQ(colorSpace.getNComps(), 3);
}

// Test useGetGrayLine
TEST_F(GfxDeviceRGBColorSpaceTest_423, UseGetGrayLineReturnsTrue_423) {
    EXPECT_TRUE(colorSpace.useGetGrayLine());
}

// Test useGetCMYKLine
TEST_F(GfxDeviceRGBColorSpaceTest_423, UseGetCMYKLineReturnsTrue_423) {
    EXPECT_TRUE(colorSpace.useGetCMYKLine());
}

// Test useGetDeviceNLine
TEST_F(GfxDeviceRGBColorSpaceTest_423, UseGetDeviceNLineReturnsTrue_423) {
    EXPECT_TRUE(colorSpace.useGetDeviceNLine());
}

// Test getDefaultColor sets expected default values
TEST_F(GfxDeviceRGBColorSpaceTest_423, GetDefaultColorSetsBlack_423) {
    GfxColor color;
    colorSpace.getDefaultColor(&color);
    // Default color for DeviceRGB should be black (0, 0, 0)
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
}

// Test getRGB for a known color (black)
TEST_F(GfxDeviceRGBColorSpaceTest_423, GetRGBBlack_423) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxRGB rgb;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB for white
TEST_F(GfxDeviceRGBColorSpaceTest_423, GetRGBWhite_423) {
    GfxColor color;
    color.c[0] = 65535;  // GfxColorComp max
    color.c[1] = 65535;
    color.c[2] = 65535;
    GfxRGB rgb;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 65535);
    EXPECT_EQ(rgb.g, 65535);
    EXPECT_EQ(rgb.b, 65535);
}

// Test getGray for black
TEST_F(GfxDeviceRGBColorSpaceTest_423, GetGrayBlack_423) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxGray gray;
    colorSpace.getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getGray for white
TEST_F(GfxDeviceRGBColorSpaceTest_423, GetGrayWhite_423) {
    GfxColor color;
    color.c[0] = 65535;
    color.c[1] = 65535;
    color.c[2] = 65535;
    GfxGray gray;
    colorSpace.getGray(&color, &gray);
    EXPECT_NEAR(gray, 65535, 1);
}

// Test copy creates a valid copy
TEST_F(GfxDeviceRGBColorSpaceTest_423, CopyCreatesValidCopy_423) {
    auto copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csDeviceRGB);
    EXPECT_EQ(copied->getNComps(), 3);
    EXPECT_TRUE(copied->useGetRGBLine());
}

// Test getCMYK for black (R=0, G=0, B=0 -> C=0, M=0, Y=0, K=1)
TEST_F(GfxDeviceRGBColorSpaceTest_423, GetCMYKBlack_423) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxCMYK cmyk;
    colorSpace.getCMYK(&color, &cmyk);
    // Black in CMYK: K should be max
    EXPECT_EQ(cmyk.k, 65535);
}

// Test getCMYK for white (R=max, G=max, B=max -> C=0, M=0, Y=0, K=0)
TEST_F(GfxDeviceRGBColorSpaceTest_423, GetCMYKWhite_423) {
    GfxColor color;
    color.c[0] = 65535;
    color.c[1] = 65535;
    color.c[2] = 65535;
    GfxCMYK cmyk;
    colorSpace.getCMYK(&color, &cmyk);
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
    EXPECT_EQ(cmyk.k, 0);
}

// Test getRGBLine with unsigned int output
TEST_F(GfxDeviceRGBColorSpaceTest_423, GetRGBLineUintOutput_423) {
    unsigned char in[] = {255, 0, 0, 0, 255, 0, 0, 0, 255};
    unsigned int out[3] = {0, 0, 0};
    colorSpace.getRGBLine(in, out, 3);
    // Red pixel
    EXPECT_EQ((out[0] >> 16) & 0xFF, 255);
    EXPECT_EQ((out[0] >> 8) & 0xFF, 0);
    EXPECT_EQ(out[0] & 0xFF, 0);
    // Green pixel
    EXPECT_EQ((out[1] >> 16) & 0xFF, 0);
    EXPECT_EQ((out[1] >> 8) & 0xFF, 255);
    EXPECT_EQ(out[1] & 0xFF, 0);
    // Blue pixel
    EXPECT_EQ((out[2] >> 16) & 0xFF, 0);
    EXPECT_EQ((out[2] >> 8) & 0xFF, 0);
    EXPECT_EQ(out[2] & 0xFF, 255);
}

// Test getRGBLine with unsigned char output
TEST_F(GfxDeviceRGBColorSpaceTest_423, GetRGBLineUcharOutput_423) {
    unsigned char in[] = {128, 64, 32};
    unsigned char out[3] = {0, 0, 0};
    colorSpace.getRGBLine(in, out, 1);
    EXPECT_EQ(out[0], 128);
    EXPECT_EQ(out[1], 64);
    EXPECT_EQ(out[2], 32);
}

// Test getGrayLine
TEST_F(GfxDeviceRGBColorSpaceTest_423, GetGrayLine_423) {
    unsigned char in[] = {255, 255, 255, 0, 0, 0};
    unsigned char out[2] = {0, 0};
    colorSpace.getGrayLine(in, out, 2);
    // White should produce gray close to 255
    EXPECT_NEAR(out[0], 255, 1);
    // Black should produce gray 0
    EXPECT_EQ(out[1], 0);
}

// Test getRGBXLine
TEST_F(GfxDeviceRGBColorSpaceTest_423, GetRGBXLine_423) {
    unsigned char in[] = {100, 150, 200};
    unsigned char out[4] = {0, 0, 0, 0};
    colorSpace.getRGBXLine(in, out, 1);
    EXPECT_EQ(out[0], 100);
    EXPECT_EQ(out[1], 150);
    EXPECT_EQ(out[2], 200);
    // 4th byte is padding (alpha or unused), check it's set to 255
    EXPECT_EQ(out[3], 255);
}

// Test with zero-length line operations (boundary)
TEST_F(GfxDeviceRGBColorSpaceTest_423, ZeroLengthRGBLine_423) {
    unsigned char in[1] = {0};
    unsigned int out[1] = {0xDEADBEEF};
    colorSpace.getRGBLine(in, out, 0);
    // Output should remain unchanged for zero-length
    EXPECT_EQ(out[0], 0xDEADBEEF);
}

// Test getCMYKLine
TEST_F(GfxDeviceRGBColorSpaceTest_423, GetCMYKLine_423) {
    unsigned char in[] = {255, 255, 255, 0, 0, 0};
    unsigned char out[8] = {0};
    colorSpace.getCMYKLine(in, out, 2);
    // White: C=0, M=0, Y=0, K=0
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    EXPECT_EQ(out[3], 0);
    // Black: C=0, M=0, Y=0, K=255
    EXPECT_EQ(out[4], 0);
    EXPECT_EQ(out[5], 0);
    EXPECT_EQ(out[6], 0);
    EXPECT_EQ(out[7], 255);
}

// Test getRGB with a mid-range color (pure red)
TEST_F(GfxDeviceRGBColorSpaceTest_423, GetRGBPureRed_423) {
    GfxColor color;
    color.c[0] = 65535;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxRGB rgb;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 65535);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}
