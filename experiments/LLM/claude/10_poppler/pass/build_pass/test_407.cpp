#include <gtest/gtest.h>
#include "poppler/GfxState.h"

class GfxDeviceGrayColorSpaceTest_407 : public ::testing::Test {
protected:
    GfxDeviceGrayColorSpace colorSpace;
};

// Test that getMode returns csDeviceGray
TEST_F(GfxDeviceGrayColorSpaceTest_407, GetModeReturnsDeviceGray_407) {
    EXPECT_EQ(colorSpace.getMode(), csDeviceGray);
}

// Test that getNComps returns 1 for gray color space
TEST_F(GfxDeviceGrayColorSpaceTest_407, GetNCompsReturnsOne_407) {
    EXPECT_EQ(colorSpace.getNComps(), 1);
}

// Test that copy returns a non-null unique_ptr
TEST_F(GfxDeviceGrayColorSpaceTest_407, CopyReturnsNonNull_407) {
    auto copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
}

// Test that copy returns an object with the same mode
TEST_F(GfxDeviceGrayColorSpaceTest_407, CopyPreservesMode_407) {
    auto copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csDeviceGray);
}

// Test that copy returns an object with the same number of components
TEST_F(GfxDeviceGrayColorSpaceTest_407, CopyPreservesNComps_407) {
    auto copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNComps(), 1);
}

// Test getGray with a gray value of 0 (black)
TEST_F(GfxDeviceGrayColorSpaceTest_407, GetGrayBlack_407) {
    GfxColor color;
    color.c[0] = 0;
    GfxGray gray;
    colorSpace.getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getGray with a gray value of 65535 (white)
TEST_F(GfxDeviceGrayColorSpaceTest_407, GetGrayWhite_407) {
    GfxColor color;
    color.c[0] = 65535;
    GfxGray gray;
    colorSpace.getGray(&color, &gray);
    EXPECT_EQ(gray, 65535);
}

// Test getRGB with black (gray=0)
TEST_F(GfxDeviceGrayColorSpaceTest_407, GetRGBBlack_407) {
    GfxColor color;
    color.c[0] = 0;
    GfxRGB rgb;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB with white (gray=65535)
TEST_F(GfxDeviceGrayColorSpaceTest_407, GetRGBWhite_407) {
    GfxColor color;
    color.c[0] = 65535;
    GfxRGB rgb;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 65535);
    EXPECT_EQ(rgb.g, 65535);
    EXPECT_EQ(rgb.b, 65535);
}

// Test getCMYK with black (gray=0)
TEST_F(GfxDeviceGrayColorSpaceTest_407, GetCMYKBlack_407) {
    GfxColor color;
    color.c[0] = 0;
    GfxCMYK cmyk;
    colorSpace.getCMYK(&color, &cmyk);
    // Black in CMYK should have K=65535
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
    EXPECT_EQ(cmyk.k, 65535);
}

// Test getCMYK with white (gray=65535)
TEST_F(GfxDeviceGrayColorSpaceTest_407, GetCMYKWhite_407) {
    GfxColor color;
    color.c[0] = 65535;
    GfxCMYK cmyk;
    colorSpace.getCMYK(&color, &cmyk);
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
    EXPECT_EQ(cmyk.k, 0);
}

// Test getDefaultColor
TEST_F(GfxDeviceGrayColorSpaceTest_407, GetDefaultColor_407) {
    GfxColor color;
    colorSpace.getDefaultColor(&color);
    // Default for DeviceGray is typically 0 (black)
    EXPECT_EQ(color.c[0], 0);
}

// Test useGetRGBLine
TEST_F(GfxDeviceGrayColorSpaceTest_407, UseGetRGBLine_407) {
    EXPECT_TRUE(colorSpace.useGetRGBLine());
}

// Test useGetGrayLine
TEST_F(GfxDeviceGrayColorSpaceTest_407, UseGetGrayLine_407) {
    EXPECT_TRUE(colorSpace.useGetGrayLine());
}

// Test useGetCMYKLine
TEST_F(GfxDeviceGrayColorSpaceTest_407, UseGetCMYKLine_407) {
    EXPECT_TRUE(colorSpace.useGetCMYKLine());
}

// Test useGetDeviceNLine
TEST_F(GfxDeviceGrayColorSpaceTest_407, UseGetDeviceNLine_407) {
    EXPECT_TRUE(colorSpace.useGetDeviceNLine());
}

// Test getGrayLine with multiple values
TEST_F(GfxDeviceGrayColorSpaceTest_407, GetGrayLine_407) {
    unsigned char in[] = {0, 128, 255};
    unsigned char out[3] = {};
    colorSpace.getGrayLine(in, out, 3);
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 128);
    EXPECT_EQ(out[2], 255);
}

// Test getRGBLine with unsigned int output
TEST_F(GfxDeviceGrayColorSpaceTest_407, GetRGBLineUint_407) {
    unsigned char in[] = {0, 255};
    unsigned int out[2] = {};
    colorSpace.getRGBLine(in, out, 2);
    // For black: expect RGB packed as 0xFF000000 (alpha=255, R=0, G=0, B=0) or similar
    // We check that they are different for different inputs
    EXPECT_NE(out[0], out[1]);
}

// Test getRGBLine with unsigned char output
TEST_F(GfxDeviceGrayColorSpaceTest_407, GetRGBLineUchar_407) {
    unsigned char in[] = {0, 255};
    unsigned char out[6] = {};
    colorSpace.getRGBLine(in, out, 2);
    // Black pixel
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    // White pixel
    EXPECT_EQ(out[3], 255);
    EXPECT_EQ(out[4], 255);
    EXPECT_EQ(out[5], 255);
}

// Test getCMYKLine
TEST_F(GfxDeviceGrayColorSpaceTest_407, GetCMYKLine_407) {
    unsigned char in[] = {0, 255};
    unsigned char out[8] = {};
    colorSpace.getCMYKLine(in, out, 2);
    // Black: C=0, M=0, Y=0, K=255
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    EXPECT_EQ(out[3], 255);
    // White: C=0, M=0, Y=0, K=0
    EXPECT_EQ(out[4], 0);
    EXPECT_EQ(out[5], 0);
    EXPECT_EQ(out[6], 0);
    EXPECT_EQ(out[7], 0);
}

// Test getRGBXLine
TEST_F(GfxDeviceGrayColorSpaceTest_407, GetRGBXLine_407) {
    unsigned char in[] = {0, 255};
    unsigned char out[8] = {};
    colorSpace.getRGBXLine(in, out, 2);
    // Black pixel: R=0, G=0, B=0, X=255
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    EXPECT_EQ(out[3], 255);
    // White pixel: R=255, G=255, B=255, X=255
    EXPECT_EQ(out[4], 255);
    EXPECT_EQ(out[5], 255);
    EXPECT_EQ(out[6], 255);
    EXPECT_EQ(out[7], 255);
}

// Test getGrayLine with zero length
TEST_F(GfxDeviceGrayColorSpaceTest_407, GetGrayLineZeroLength_407) {
    unsigned char in[] = {128};
    unsigned char out[] = {42};
    colorSpace.getGrayLine(in, out, 0);
    // Output should remain unchanged
    EXPECT_EQ(out[0], 42);
}

// Test getRGB with mid-gray
TEST_F(GfxDeviceGrayColorSpaceTest_407, GetRGBMidGray_407) {
    GfxColor color;
    color.c[0] = 32768; // approximately mid-gray
    GfxRGB rgb;
    colorSpace.getRGB(&color, &rgb);
    // All components should be equal for gray
    EXPECT_EQ(rgb.r, rgb.g);
    EXPECT_EQ(rgb.g, rgb.b);
}

// Test getGray with mid-gray
TEST_F(GfxDeviceGrayColorSpaceTest_407, GetGrayMidValue_407) {
    GfxColor color;
    color.c[0] = 32768;
    GfxGray gray;
    colorSpace.getGray(&color, &gray);
    EXPECT_EQ(gray, 32768);
}

// Test that getMode value equals the enum constant 0
TEST_F(GfxDeviceGrayColorSpaceTest_407, GetModeEnumValue_407) {
    EXPECT_EQ(static_cast<int>(colorSpace.getMode()), 0);
}
