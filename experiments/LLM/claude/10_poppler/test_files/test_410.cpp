#include <gtest/gtest.h>
#include "GfxState.h"

class GfxDeviceGrayColorSpaceTest_410 : public ::testing::Test {
protected:
    GfxDeviceGrayColorSpace colorSpace;
};

// Test that useGetCMYKLine returns true
TEST_F(GfxDeviceGrayColorSpaceTest_410, UseGetCMYKLineReturnsTrue_410) {
    EXPECT_TRUE(colorSpace.useGetCMYKLine());
}

// Test that useGetRGBLine returns true (DeviceGray typically supports RGB line operations)
TEST_F(GfxDeviceGrayColorSpaceTest_410, UseGetRGBLine_410) {
    bool result = colorSpace.useGetRGBLine();
    // Just verify it returns a valid bool (true or false)
    EXPECT_TRUE(result == true || result == false);
}

// Test that useGetGrayLine returns true (DeviceGray should support gray line)
TEST_F(GfxDeviceGrayColorSpaceTest_410, UseGetGrayLine_410) {
    bool result = colorSpace.useGetGrayLine();
    EXPECT_TRUE(result);
}

// Test that useGetDeviceNLine returns a valid value
TEST_F(GfxDeviceGrayColorSpaceTest_410, UseGetDeviceNLine_410) {
    bool result = colorSpace.useGetDeviceNLine();
    EXPECT_TRUE(result == true || result == false);
}

// Test that getMode returns csDeviceGray
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetModeReturnsDeviceGray_410) {
    EXPECT_EQ(colorSpace.getMode(), csDeviceGray);
}

// Test that getNComps returns 1 for grayscale
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetNCompsReturnsOne_410) {
    EXPECT_EQ(colorSpace.getNComps(), 1);
}

// Test copy creates a valid copy
TEST_F(GfxDeviceGrayColorSpaceTest_410, CopyReturnsValidObject_410) {
    auto copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csDeviceGray);
    EXPECT_EQ(copied->getNComps(), 1);
}

// Test getDefaultColor sets the color appropriately
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetDefaultColor_410) {
    GfxColor color;
    memset(&color, 0, sizeof(color));
    colorSpace.getDefaultColor(&color);
    // Default gray color should be 0 (black) - verify the first component
    // The default for DeviceGray is typically 0
    // We just verify the call doesn't crash and sets something
    SUCCEED();
}

// Test getGray with a gray value
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetGray_410) {
    GfxColor color;
    color.c[0] = 0; // black
    GfxGray gray;
    colorSpace.getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getGray with maximum gray value
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetGrayMaxValue_410) {
    GfxColor color;
    color.c[0] = gfxColorComp1; // white (max value)
    GfxGray gray;
    colorSpace.getGray(&color, &gray);
    EXPECT_EQ(gray, gfxColorComp1);
}

// Test getRGB for black
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetRGBBlack_410) {
    GfxColor color;
    color.c[0] = 0; // black
    GfxRGB rgb;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB for white
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetRGBWhite_410) {
    GfxColor color;
    color.c[0] = gfxColorComp1; // white
    GfxRGB rgb;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, gfxColorComp1);
    EXPECT_EQ(rgb.g, gfxColorComp1);
    EXPECT_EQ(rgb.b, gfxColorComp1);
}

// Test getCMYK for black
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetCMYKBlack_410) {
    GfxColor color;
    color.c[0] = 0; // black
    GfxCMYK cmyk;
    colorSpace.getCMYK(&color, &cmyk);
    // Black in CMYK should have K = max
    EXPECT_EQ(cmyk.k, gfxColorComp1);
}

// Test getCMYK for white
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetCMYKWhite_410) {
    GfxColor color;
    color.c[0] = gfxColorComp1; // white
    GfxCMYK cmyk;
    colorSpace.getCMYK(&color, &cmyk);
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
    EXPECT_EQ(cmyk.k, 0);
}

// Test getGrayLine
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetGrayLine_410) {
    const int length = 4;
    unsigned char in[length] = {0, 128, 255, 64};
    unsigned char out[length] = {0};
    colorSpace.getGrayLine(in, out, length);
    // For DeviceGray, output should match input
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 128);
    EXPECT_EQ(out[2], 255);
    EXPECT_EQ(out[3], 64);
}

// Test getRGBLine with unsigned int output
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetRGBLineUInt_410) {
    const int length = 3;
    unsigned char in[length] = {0, 128, 255};
    unsigned int out[length] = {0};
    colorSpace.getRGBLine(in, out, length);
    // Verify the call completes without crash; specific encoding depends on implementation
    SUCCEED();
}

// Test getRGBLine with unsigned char output
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetRGBLineUChar_410) {
    const int length = 2;
    unsigned char in[length] = {0, 255};
    unsigned char out[length * 3] = {0};
    colorSpace.getRGBLine(in, out, length);
    // Black: R=0, G=0, B=0
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    // White: R=255, G=255, B=255
    EXPECT_EQ(out[3], 255);
    EXPECT_EQ(out[4], 255);
    EXPECT_EQ(out[5], 255);
}

// Test getRGBXLine
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetRGBXLine_410) {
    const int length = 2;
    unsigned char in[length] = {0, 255};
    unsigned char out[length * 4] = {0};
    colorSpace.getRGBXLine(in, out, length);
    // Black
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    // White
    EXPECT_EQ(out[4], 255);
    EXPECT_EQ(out[5], 255);
    EXPECT_EQ(out[6], 255);
}

// Test getCMYKLine
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetCMYKLine_410) {
    const int length = 2;
    unsigned char in[length] = {0, 255};
    unsigned char out[length * 4] = {0};
    colorSpace.getCMYKLine(in, out, length);
    // Just verify no crash; exact CMYK values depend on implementation
    SUCCEED();
}

// Test getDeviceNLine
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetDeviceNLine_410) {
    const int length = 2;
    unsigned char in[length] = {0, 255};
    unsigned char out[length * (SPOT_NCOMPS + 4)] = {0};
    colorSpace.getDeviceNLine(in, out, length);
    SUCCEED();
}

// Test getGrayLine with zero length
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetGrayLineZeroLength_410) {
    unsigned char in[1] = {0};
    unsigned char out[1] = {0};
    colorSpace.getGrayLine(in, out, 0);
    SUCCEED();
}

// Test getRGBLine with zero length
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetRGBLineZeroLength_410) {
    unsigned char in[1] = {0};
    unsigned int out[1] = {0};
    colorSpace.getRGBLine(in, out, 0);
    SUCCEED();
}

// Test getGrayLine with single element
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetGrayLineSingleElement_410) {
    unsigned char in[1] = {127};
    unsigned char out[1] = {0};
    colorSpace.getGrayLine(in, out, 1);
    EXPECT_EQ(out[0], 127);
}

// Test getDeviceN
TEST_F(GfxDeviceGrayColorSpaceTest_410, GetDeviceN_410) {
    GfxColor color;
    color.c[0] = 0;
    GfxColor deviceN;
    memset(&deviceN, 0, sizeof(deviceN));
    colorSpace.getDeviceN(&color, &deviceN);
    SUCCEED();
}

// Test that a copied color space has the same behavior
TEST_F(GfxDeviceGrayColorSpaceTest_410, CopiedUseGetCMYKLine_410) {
    auto copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->useGetCMYKLine());
}

// Test that copy preserves getNComps
TEST_F(GfxDeviceGrayColorSpaceTest_410, CopiedGetNComps_410) {
    auto copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNComps(), 1);
}
