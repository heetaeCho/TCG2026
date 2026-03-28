#include <gtest/gtest.h>
#include "GfxState.h"

class GfxDeviceGrayColorSpaceTest_412 : public ::testing::Test {
protected:
    GfxDeviceGrayColorSpace colorSpace;
};

// Test getNComps returns 1 for gray color space
TEST_F(GfxDeviceGrayColorSpaceTest_412, GetNCompsReturnsOne_412) {
    EXPECT_EQ(colorSpace.getNComps(), 1);
}

// Test getMode returns the correct mode for device gray
TEST_F(GfxDeviceGrayColorSpaceTest_412, GetModeReturnsDeviceGray_412) {
    EXPECT_EQ(colorSpace.getMode(), csDeviceGray);
}

// Test getDefaultColor sets appropriate default
TEST_F(GfxDeviceGrayColorSpaceTest_412, GetDefaultColor_412) {
    GfxColor color;
    colorSpace.getDefaultColor(&color);
    // Default gray should be 0 (black)
    EXPECT_EQ(color.c[0], 0);
}

// Test getGray conversion
TEST_F(GfxDeviceGrayColorSpaceTest_412, GetGrayReturnsCorrectValue_412) {
    GfxColor color;
    GfxGray gray;
    color.c[0] = 0;
    colorSpace.getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getGray with max value
TEST_F(GfxDeviceGrayColorSpaceTest_412, GetGrayMaxValue_412) {
    GfxColor color;
    GfxGray gray;
    color.c[0] = gfxColorComp1;
    colorSpace.getGray(&color, &gray);
    EXPECT_EQ(gray, gfxColorComp1);
}

// Test getRGB conversion from gray
TEST_F(GfxDeviceGrayColorSpaceTest_412, GetRGBFromGray_412) {
    GfxColor color;
    GfxRGB rgb;
    color.c[0] = 0;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB with max gray value
TEST_F(GfxDeviceGrayColorSpaceTest_412, GetRGBFromMaxGray_412) {
    GfxColor color;
    GfxRGB rgb;
    color.c[0] = gfxColorComp1;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, gfxColorComp1);
    EXPECT_EQ(rgb.g, gfxColorComp1);
    EXPECT_EQ(rgb.b, gfxColorComp1);
}

// Test getCMYK conversion
TEST_F(GfxDeviceGrayColorSpaceTest_412, GetCMYKFromGray_412) {
    GfxColor color;
    GfxCMYK cmyk;
    color.c[0] = 0;
    colorSpace.getCMYK(&color, &cmyk);
    // Black gray should map to K=1 in CMYK
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
}

// Test getCMYK for white
TEST_F(GfxDeviceGrayColorSpaceTest_412, GetCMYKFromWhiteGray_412) {
    GfxColor color;
    GfxCMYK cmyk;
    color.c[0] = gfxColorComp1;
    colorSpace.getCMYK(&color, &cmyk);
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
    EXPECT_EQ(cmyk.k, 0);
}

// Test copy creates a valid copy
TEST_F(GfxDeviceGrayColorSpaceTest_412, CopyCreatesValidCopy_412) {
    auto copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csDeviceGray);
    EXPECT_EQ(copied->getNComps(), 1);
}

// Test useGetRGBLine
TEST_F(GfxDeviceGrayColorSpaceTest_412, UseGetRGBLine_412) {
    bool result = colorSpace.useGetRGBLine();
    EXPECT_TRUE(result);
}

// Test useGetGrayLine
TEST_F(GfxDeviceGrayColorSpaceTest_412, UseGetGrayLine_412) {
    bool result = colorSpace.useGetGrayLine();
    EXPECT_TRUE(result);
}

// Test useGetCMYKLine
TEST_F(GfxDeviceGrayColorSpaceTest_412, UseGetCMYKLine_412) {
    bool result = colorSpace.useGetCMYKLine();
    EXPECT_TRUE(result);
}

// Test useGetDeviceNLine
TEST_F(GfxDeviceGrayColorSpaceTest_412, UseGetDeviceNLine_412) {
    bool result = colorSpace.useGetDeviceNLine();
    EXPECT_TRUE(result);
}

// Test getGrayLine with zero length
TEST_F(GfxDeviceGrayColorSpaceTest_412, GetGrayLineZeroLength_412) {
    unsigned char in[1] = {0};
    unsigned char out[1] = {0};
    // Should handle zero-length gracefully
    colorSpace.getGrayLine(in, out, 0);
}

// Test getGrayLine with actual data
TEST_F(GfxDeviceGrayColorSpaceTest_412, GetGrayLineWithData_412) {
    unsigned char in[3] = {0, 128, 255};
    unsigned char out[3] = {0, 0, 0};
    colorSpace.getGrayLine(in, out, 3);
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 128);
    EXPECT_EQ(out[2], 255);
}

// Test getRGBLine (unsigned int version) with data
TEST_F(GfxDeviceGrayColorSpaceTest_412, GetRGBLineUintWithData_412) {
    unsigned char in[3] = {0, 128, 255};
    unsigned int out[3] = {0, 0, 0};
    colorSpace.getRGBLine(in, out, 3);
    // Each output should encode the gray value as RGB
    // Check that black maps to black
    EXPECT_NE(out[2], 0u); // 255 gray should produce non-zero RGB
}

// Test getRGBLine (unsigned char version) with data
TEST_F(GfxDeviceGrayColorSpaceTest_412, GetRGBLineUcharWithData_412) {
    unsigned char in[2] = {0, 255};
    unsigned char out[6] = {0};
    colorSpace.getRGBLine(in, out, 2);
    // First pixel (gray=0) should be R=0, G=0, B=0
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    // Second pixel (gray=255) should be R=255, G=255, B=255
    EXPECT_EQ(out[3], 255);
    EXPECT_EQ(out[4], 255);
    EXPECT_EQ(out[5], 255);
}

// Test getRGBXLine with data
TEST_F(GfxDeviceGrayColorSpaceTest_412, GetRGBXLineWithData_412) {
    unsigned char in[2] = {0, 255};
    unsigned char out[8] = {0};
    colorSpace.getRGBXLine(in, out, 2);
    // First pixel (gray=0): R=0, G=0, B=0, X=255
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    // Second pixel (gray=255): R=255, G=255, B=255
    EXPECT_EQ(out[4], 255);
    EXPECT_EQ(out[5], 255);
    EXPECT_EQ(out[6], 255);
}

// Test getCMYKLine with data
TEST_F(GfxDeviceGrayColorSpaceTest_412, GetCMYKLineWithData_412) {
    unsigned char in[2] = {0, 255};
    unsigned char out[8] = {0};
    colorSpace.getCMYKLine(in, out, 2);
    // Gray=0 (black) should map to C=0,M=0,Y=0,K=255
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    EXPECT_EQ(out[3], 255);
    // Gray=255 (white) should map to C=0,M=0,Y=0,K=0
    EXPECT_EQ(out[4], 0);
    EXPECT_EQ(out[5], 0);
    EXPECT_EQ(out[6], 0);
    EXPECT_EQ(out[7], 0);
}

// Test getDeviceN conversion
TEST_F(GfxDeviceGrayColorSpaceTest_412, GetDeviceNFromGray_412) {
    GfxColor color;
    GfxColor deviceN;
    color.c[0] = 0;
    colorSpace.getDeviceN(&color, &deviceN);
    // Just ensure no crash; exact values depend on implementation
}

// Test getDeviceNLine with data
TEST_F(GfxDeviceGrayColorSpaceTest_412, GetDeviceNLineWithData_412) {
    unsigned char in[2] = {0, 255};
    unsigned char out[2 * (SPOT_NCOMPS + 4)] = {0};
    colorSpace.getDeviceNLine(in, out, 2);
    // Just verify it doesn't crash
}

// Test with mid-range gray value
TEST_F(GfxDeviceGrayColorSpaceTest_412, GetGrayMidValue_412) {
    GfxColor color;
    GfxGray gray;
    color.c[0] = gfxColorComp1 / 2;
    colorSpace.getGray(&color, &gray);
    EXPECT_EQ(gray, gfxColorComp1 / 2);
}
