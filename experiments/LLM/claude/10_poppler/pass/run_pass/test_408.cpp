#include <gtest/gtest.h>
#include "poppler/GfxState.h"

class GfxDeviceGrayColorSpaceTest_408 : public ::testing::Test {
protected:
    GfxDeviceGrayColorSpace colorSpace;
};

// Test that getMode returns the correct color space mode for DeviceGray
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetModeReturnsDeviceGray_408) {
    EXPECT_EQ(colorSpace.getMode(), csDeviceGray);
}

// Test that getNComps returns 1 for a grayscale color space
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetNCompsReturnsOne_408) {
    EXPECT_EQ(colorSpace.getNComps(), 1);
}

// Test that useGetRGBLine returns true
TEST_F(GfxDeviceGrayColorSpaceTest_408, UseGetRGBLineReturnsTrue_408) {
    EXPECT_TRUE(colorSpace.useGetRGBLine());
}

// Test that useGetGrayLine returns true
TEST_F(GfxDeviceGrayColorSpaceTest_408, UseGetGrayLineReturnsTrue_408) {
    EXPECT_TRUE(colorSpace.useGetGrayLine());
}

// Test that useGetCMYKLine returns true
TEST_F(GfxDeviceGrayColorSpaceTest_408, UseGetCMYKLineReturnsTrue_408) {
    EXPECT_TRUE(colorSpace.useGetCMYKLine());
}

// Test that useGetDeviceNLine returns true
TEST_F(GfxDeviceGrayColorSpaceTest_408, UseGetDeviceNLineReturnsTrue_408) {
    EXPECT_TRUE(colorSpace.useGetDeviceNLine());
}

// Test getGray with a fully black color (component = 0)
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetGrayBlack_408) {
    GfxColor color;
    color.c[0] = 0;
    GfxGray gray;
    colorSpace.getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getGray with a fully white color (component = max)
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetGrayWhite_408) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxGray gray;
    colorSpace.getGray(&color, &gray);
    EXPECT_EQ(gray, gfxColorComp1);
}

// Test getRGB with black - should produce black RGB
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetRGBBlack_408) {
    GfxColor color;
    color.c[0] = 0;
    GfxRGB rgb;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB with white - should produce white RGB
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetRGBWhite_408) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxRGB rgb;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, gfxColorComp1);
    EXPECT_EQ(rgb.g, gfxColorComp1);
    EXPECT_EQ(rgb.b, gfxColorComp1);
}

// Test getCMYK with black (gray=0 means black in CMYK)
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetCMYKBlack_408) {
    GfxColor color;
    color.c[0] = 0;
    GfxCMYK cmyk;
    colorSpace.getCMYK(&color, &cmyk);
    // Black in gray -> K=1, C=M=Y=0
    EXPECT_EQ(cmyk.k, gfxColorComp1);
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
}

// Test getCMYK with white (gray=1 means no ink in CMYK)
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetCMYKWhite_408) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxCMYK cmyk;
    colorSpace.getCMYK(&color, &cmyk);
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
    EXPECT_EQ(cmyk.k, 0);
}

// Test getDefaultColor sets the color to default (should be 0 for gray)
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetDefaultColor_408) {
    GfxColor color;
    color.c[0] = gfxColorComp1; // Set to non-default
    colorSpace.getDefaultColor(&color);
    EXPECT_EQ(color.c[0], 0);
}

// Test copy creates a valid copy
TEST_F(GfxDeviceGrayColorSpaceTest_408, CopyReturnsValidObject_408) {
    auto copy = colorSpace.copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getMode(), csDeviceGray);
    EXPECT_EQ(copy->getNComps(), 1);
}

// Test getRGBLine with unsigned int output
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetRGBLineUintBlack_408) {
    unsigned char in[3] = {0, 0, 0};
    unsigned int out[3] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    colorSpace.getRGBLine(in, out, 3);
    for (int i = 0; i < 3; i++) {
        // Each pixel should be black: alpha=0xFF, R=0, G=0, B=0
        unsigned int expected = (255u << 24); // 0xFF000000
        EXPECT_EQ(out[i], expected);
    }
}

// Test getRGBLine with unsigned int output for white
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetRGBLineUintWhite_408) {
    unsigned char in[3] = {255, 255, 255};
    unsigned int out[3] = {0, 0, 0};
    colorSpace.getRGBLine(in, out, 3);
    for (int i = 0; i < 3; i++) {
        unsigned int expected = (255u << 24) | (255u << 16) | (255u << 8) | 255u;
        EXPECT_EQ(out[i], expected);
    }
}

// Test getRGBLine with unsigned char output
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetRGBLineUcharBlack_408) {
    unsigned char in[2] = {0, 0};
    unsigned char out[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    colorSpace.getRGBLine(in, out, 2);
    for (int i = 0; i < 6; i++) {
        EXPECT_EQ(out[i], 0);
    }
}

// Test getRGBLine with unsigned char output for white
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetRGBLineUcharWhite_408) {
    unsigned char in[2] = {255, 255};
    unsigned char out[6] = {0, 0, 0, 0, 0, 0};
    colorSpace.getRGBLine(in, out, 2);
    for (int i = 0; i < 6; i++) {
        EXPECT_EQ(out[i], 255);
    }
}

// Test getGrayLine
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetGrayLineIdentity_408) {
    unsigned char in[4] = {0, 64, 128, 255};
    unsigned char out[4] = {0, 0, 0, 0};
    colorSpace.getGrayLine(in, out, 4);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(out[i], in[i]);
    }
}

// Test getRGBXLine
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetRGBXLineBlack_408) {
    unsigned char in[2] = {0, 255};
    unsigned char out[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    colorSpace.getRGBXLine(in, out, 2);
    // First pixel: R=0, G=0, B=0, X=255
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    EXPECT_EQ(out[3], 255);
    // Second pixel: R=255, G=255, B=255, X=255
    EXPECT_EQ(out[4], 255);
    EXPECT_EQ(out[5], 255);
    EXPECT_EQ(out[6], 255);
    EXPECT_EQ(out[7], 255);
}

// Test getCMYKLine
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetCMYKLineBlack_408) {
    unsigned char in[1] = {0};
    unsigned char out[4] = {0, 0, 0, 0};
    colorSpace.getCMYKLine(in, out, 1);
    // Black should be C=0, M=0, Y=0, K=255
    EXPECT_EQ(out[0], 0);   // C
    EXPECT_EQ(out[1], 0);   // M
    EXPECT_EQ(out[2], 0);   // Y
    EXPECT_EQ(out[3], 255); // K
}

// Test getCMYKLine white
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetCMYKLineWhite_408) {
    unsigned char in[1] = {255};
    unsigned char out[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    colorSpace.getCMYKLine(in, out, 1);
    // White should be C=0, M=0, Y=0, K=0
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    EXPECT_EQ(out[3], 0);
}

// Test with zero-length line operations (boundary)
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetRGBLineZeroLength_408) {
    unsigned char in[1] = {0};
    unsigned int out[1] = {0xDEADBEEF};
    colorSpace.getRGBLine(in, out, 0);
    // Output should remain unchanged
    EXPECT_EQ(out[0], 0xDEADBEEFu);
}

// Test getGray with mid-range value
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetGrayMidRange_408) {
    GfxColor color;
    color.c[0] = gfxColorComp1 / 2;
    GfxGray gray;
    colorSpace.getGray(&color, &gray);
    EXPECT_EQ(gray, gfxColorComp1 / 2);
}

// Test getRGB with mid-range gray
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetRGBMidGray_408) {
    GfxColor color;
    color.c[0] = gfxColorComp1 / 2;
    GfxRGB rgb;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, gfxColorComp1 / 2);
    EXPECT_EQ(rgb.g, gfxColorComp1 / 2);
    EXPECT_EQ(rgb.b, gfxColorComp1 / 2);
}

// Test single-pixel getRGBLine with mid-range value
TEST_F(GfxDeviceGrayColorSpaceTest_408, GetRGBLineSinglePixelMidRange_408) {
    unsigned char in[1] = {128};
    unsigned char out[3] = {0, 0, 0};
    colorSpace.getRGBLine(in, out, 1);
    EXPECT_EQ(out[0], 128);
    EXPECT_EQ(out[1], 128);
    EXPECT_EQ(out[2], 128);
}
