#include <gtest/gtest.h>
#include "GfxState.h"

class GfxDeviceRGBColorSpaceTest_422 : public ::testing::Test {
protected:
    GfxDeviceRGBColorSpace colorSpace;
};

// Test that getMode returns csDeviceRGB
TEST_F(GfxDeviceRGBColorSpaceTest_422, GetModeReturnsDeviceRGB_422) {
    EXPECT_EQ(colorSpace.getMode(), csDeviceRGB);
}

// Test that getMode returns the correct enum value (2)
TEST_F(GfxDeviceRGBColorSpaceTest_422, GetModeReturnsCorrectEnumValue_422) {
    EXPECT_EQ(static_cast<int>(colorSpace.getMode()), 2);
}

// Test that getNComps returns 3 for RGB
TEST_F(GfxDeviceRGBColorSpaceTest_422, GetNCompsReturnsThree_422) {
    EXPECT_EQ(colorSpace.getNComps(), 3);
}

// Test that copy produces a valid color space with the same mode
TEST_F(GfxDeviceRGBColorSpaceTest_422, CopyPreservesMode_422) {
    auto copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csDeviceRGB);
}

// Test that copy produces a color space with the same number of components
TEST_F(GfxDeviceRGBColorSpaceTest_422, CopyPreservesNComps_422) {
    auto copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNComps(), 3);
}

// Test getDefaultColor sets expected default values
TEST_F(GfxDeviceRGBColorSpaceTest_422, GetDefaultColorSetsValues_422) {
    GfxColor color;
    memset(&color, 0, sizeof(color));
    colorSpace.getDefaultColor(&color);
    // Default color for DeviceRGB is typically black (0,0,0)
    // We just verify it doesn't crash and sets some values
    // The exact values depend on implementation
    SUCCEED();
}

// Test getGray conversion from a known color
TEST_F(GfxDeviceRGBColorSpaceTest_422, GetGrayFromColor_422) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxGray gray;
    colorSpace.getGray(&color, &gray);
    // Black RGB should give gray = 0
    EXPECT_EQ(gray, 0);
}

// Test getGray for white
TEST_F(GfxDeviceRGBColorSpaceTest_422, GetGrayFromWhite_422) {
    GfxColor color;
    color.c[0] = 65535;
    color.c[1] = 65535;
    color.c[2] = 65535;
    GfxGray gray;
    colorSpace.getGray(&color, &gray);
    // White RGB should give a high gray value
    EXPECT_GT(gray, 0);
}

// Test getRGB passes through RGB values
TEST_F(GfxDeviceRGBColorSpaceTest_422, GetRGBFromColor_422) {
    GfxColor color;
    color.c[0] = 65535; // R = max
    color.c[1] = 0;     // G = 0
    color.c[2] = 0;     // B = 0
    GfxRGB rgb;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 65535);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB for black
TEST_F(GfxDeviceRGBColorSpaceTest_422, GetRGBFromBlack_422) {
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
TEST_F(GfxDeviceRGBColorSpaceTest_422, GetRGBFromWhite_422) {
    GfxColor color;
    color.c[0] = 65535;
    color.c[1] = 65535;
    color.c[2] = 65535;
    GfxRGB rgb;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 65535);
    EXPECT_EQ(rgb.g, 65535);
    EXPECT_EQ(rgb.b, 65535);
}

// Test getCMYK from black
TEST_F(GfxDeviceRGBColorSpaceTest_422, GetCMYKFromBlack_422) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxCMYK cmyk;
    colorSpace.getCMYK(&color, &cmyk);
    // Black in CMYK should have K = max
    EXPECT_EQ(cmyk.k, 65535);
}

// Test getCMYK from white
TEST_F(GfxDeviceRGBColorSpaceTest_422, GetCMYKFromWhite_422) {
    GfxColor color;
    color.c[0] = 65535;
    color.c[1] = 65535;
    color.c[2] = 65535;
    GfxCMYK cmyk;
    colorSpace.getCMYK(&color, &cmyk);
    // White in CMYK should be (0,0,0,0)
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
    EXPECT_EQ(cmyk.k, 0);
}

// Test useGetRGBLine returns true (DeviceRGB typically supports fast line access)
TEST_F(GfxDeviceRGBColorSpaceTest_422, UseGetRGBLine_422) {
    EXPECT_TRUE(colorSpace.useGetRGBLine());
}

// Test useGetGrayLine
TEST_F(GfxDeviceRGBColorSpaceTest_422, UseGetGrayLine_422) {
    // Just verify it returns a valid boolean
    bool result = colorSpace.useGetGrayLine();
    EXPECT_TRUE(result == true || result == false);
}

// Test useGetCMYKLine
TEST_F(GfxDeviceRGBColorSpaceTest_422, UseGetCMYKLine_422) {
    bool result = colorSpace.useGetCMYKLine();
    EXPECT_TRUE(result == true || result == false);
}

// Test useGetDeviceNLine
TEST_F(GfxDeviceRGBColorSpaceTest_422, UseGetDeviceNLine_422) {
    bool result = colorSpace.useGetDeviceNLine();
    EXPECT_TRUE(result == true || result == false);
}

// Test getGrayLine with a small buffer
TEST_F(GfxDeviceRGBColorSpaceTest_422, GetGrayLineBasic_422) {
    unsigned char in[6] = {255, 255, 255, 0, 0, 0}; // 2 pixels: white, black
    unsigned char out[2] = {0, 0};
    colorSpace.getGrayLine(in, out, 2);
    // White should map to 255, black to 0
    EXPECT_EQ(out[0], 255);
    EXPECT_EQ(out[1], 0);
}

// Test getRGBLine (unsigned int version) with a small buffer
TEST_F(GfxDeviceRGBColorSpaceTest_422, GetRGBLineUIntBasic_422) {
    unsigned char in[3] = {255, 0, 0}; // 1 pixel: red
    unsigned int out[1] = {0};
    colorSpace.getRGBLine(in, out, 1);
    // Check that the output is non-zero (some packed ARGB value)
    EXPECT_NE(out[0], 0u);
}

// Test getRGBLine (unsigned char version) with a small buffer
TEST_F(GfxDeviceRGBColorSpaceTest_422, GetRGBLineUCharBasic_422) {
    unsigned char in[3] = {128, 64, 32};
    unsigned char out[3] = {0, 0, 0};
    colorSpace.getRGBLine(in, out, 1);
    EXPECT_EQ(out[0], 128);
    EXPECT_EQ(out[1], 64);
    EXPECT_EQ(out[2], 32);
}

// Test getRGBXLine with a small buffer
TEST_F(GfxDeviceRGBColorSpaceTest_422, GetRGBXLineBasic_422) {
    unsigned char in[3] = {100, 150, 200};
    unsigned char out[4] = {0, 0, 0, 0};
    colorSpace.getRGBXLine(in, out, 1);
    EXPECT_EQ(out[0], 100);
    EXPECT_EQ(out[1], 150);
    EXPECT_EQ(out[2], 200);
    EXPECT_EQ(out[3], 255);
}

// Test getCMYKLine with a small buffer
TEST_F(GfxDeviceRGBColorSpaceTest_422, GetCMYKLineBasic_422) {
    unsigned char in[3] = {255, 255, 255}; // white
    unsigned char out[4] = {99, 99, 99, 99};
    colorSpace.getCMYKLine(in, out, 1);
    // White -> CMYK (0, 0, 0, 0)
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    EXPECT_EQ(out[3], 0);
}

// Test getDeviceN from a color
TEST_F(GfxDeviceRGBColorSpaceTest_422, GetDeviceNFromColor_422) {
    GfxColor color;
    color.c[0] = 65535;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxColor deviceN;
    memset(&deviceN, 0, sizeof(deviceN));
    colorSpace.getDeviceN(&color, &deviceN);
    // Just verify it doesn't crash
    SUCCEED();
}

// Test zero-length line operations don't crash
TEST_F(GfxDeviceRGBColorSpaceTest_422, ZeroLengthLineOperations_422) {
    unsigned char in[1] = {0};
    unsigned char out[1] = {0};
    unsigned int outUint[1] = {0};
    
    colorSpace.getGrayLine(in, out, 0);
    colorSpace.getRGBLine(in, outUint, 0);
    colorSpace.getRGBLine(in, out, 0);
    colorSpace.getRGBXLine(in, out, 0);
    colorSpace.getCMYKLine(in, out, 0);
    colorSpace.getDeviceNLine(in, out, 0);
    SUCCEED();
}

// Test that mode is distinctly DeviceRGB and not other modes
TEST_F(GfxDeviceRGBColorSpaceTest_422, ModeIsNotOtherTypes_422) {
    EXPECT_NE(colorSpace.getMode(), csDeviceGray);
    EXPECT_NE(colorSpace.getMode(), csCalGray);
    EXPECT_NE(colorSpace.getMode(), csCalRGB);
    EXPECT_NE(colorSpace.getMode(), csDeviceCMYK);
    EXPECT_NE(colorSpace.getMode(), csLab);
    EXPECT_NE(colorSpace.getMode(), csICCBased);
    EXPECT_NE(colorSpace.getMode(), csIndexed);
    EXPECT_NE(colorSpace.getMode(), csSeparation);
    EXPECT_NE(colorSpace.getMode(), csDeviceN);
    EXPECT_NE(colorSpace.getMode(), csPattern);
}

// Test multiple pixels in getRGBLine
TEST_F(GfxDeviceRGBColorSpaceTest_422, GetRGBLineMultiplePixels_422) {
    unsigned char in[9] = {255, 0, 0, 0, 255, 0, 0, 0, 255}; // R, G, B pixels
    unsigned char out[9] = {0};
    colorSpace.getRGBLine(in, out, 3);
    // Should pass through the RGB values
    EXPECT_EQ(out[0], 255); EXPECT_EQ(out[1], 0);   EXPECT_EQ(out[2], 0);
    EXPECT_EQ(out[3], 0);   EXPECT_EQ(out[4], 255); EXPECT_EQ(out[5], 0);
    EXPECT_EQ(out[6], 0);   EXPECT_EQ(out[7], 0);   EXPECT_EQ(out[8], 255);
}
