#include <gtest/gtest.h>
#include "GfxState.h"

class GfxDeviceRGBColorSpaceTest_425 : public ::testing::Test {
protected:
    GfxDeviceRGBColorSpace colorSpace;
};

// Test that useGetCMYKLine returns true
TEST_F(GfxDeviceRGBColorSpaceTest_425, UseGetCMYKLineReturnsTrue_425) {
    EXPECT_TRUE(colorSpace.useGetCMYKLine());
}

// Test that useGetRGBLine returns true (DeviceRGB typically supports RGB line)
TEST_F(GfxDeviceRGBColorSpaceTest_425, UseGetRGBLineReturnsTrue_425) {
    EXPECT_TRUE(colorSpace.useGetRGBLine());
}

// Test that useGetGrayLine returns true
TEST_F(GfxDeviceRGBColorSpaceTest_425, UseGetGrayLineReturnsTrue_425) {
    EXPECT_TRUE(colorSpace.useGetGrayLine());
}

// Test that useGetDeviceNLine returns true
TEST_F(GfxDeviceRGBColorSpaceTest_425, UseGetDeviceNLineReturnsTrue_425) {
    EXPECT_TRUE(colorSpace.useGetDeviceNLine());
}

// Test that getMode returns csDeviceRGB
TEST_F(GfxDeviceRGBColorSpaceTest_425, GetModeReturnsDeviceRGB_425) {
    EXPECT_EQ(colorSpace.getMode(), csDeviceRGB);
}

// Test that getNComps returns 3 (R, G, B)
TEST_F(GfxDeviceRGBColorSpaceTest_425, GetNCompsReturnsThree_425) {
    EXPECT_EQ(colorSpace.getNComps(), 3);
}

// Test copy returns a valid non-null pointer
TEST_F(GfxDeviceRGBColorSpaceTest_425, CopyReturnsNonNull_425) {
    auto copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csDeviceRGB);
    EXPECT_EQ(copied->getNComps(), 3);
}

// Test getDefaultColor sets expected default values
TEST_F(GfxDeviceRGBColorSpaceTest_425, GetDefaultColorSetsBlack_425) {
    GfxColor color;
    colorSpace.getDefaultColor(&color);
    // Default for DeviceRGB is typically black: (0, 0, 0)
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
}

// Test getGray for a known color
TEST_F(GfxDeviceRGBColorSpaceTest_425, GetGrayForBlack_425) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxGray gray;
    colorSpace.getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getRGB for a known color (black)
TEST_F(GfxDeviceRGBColorSpaceTest_425, GetRGBForBlack_425) {
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
TEST_F(GfxDeviceRGBColorSpaceTest_425, GetRGBForWhite_425) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;
    GfxRGB rgb;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, gfxColorComp1);
    EXPECT_EQ(rgb.g, gfxColorComp1);
    EXPECT_EQ(rgb.b, gfxColorComp1);
}

// Test getCMYK for black (should give full K)
TEST_F(GfxDeviceRGBColorSpaceTest_425, GetCMYKForBlack_425) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxCMYK cmyk;
    colorSpace.getCMYK(&color, &cmyk);
    // Black in CMYK: C=0, M=0, Y=0, K=1
    EXPECT_EQ(cmyk.k, gfxColorComp1);
}

// Test getGrayLine with known input
TEST_F(GfxDeviceRGBColorSpaceTest_425, GetGrayLineBasic_425) {
    const int length = 2;
    unsigned char in[length * 3] = {0, 0, 0, 255, 255, 255};
    unsigned char out[length];
    colorSpace.getGrayLine(in, out, length);
    // Black should map to gray 0, white to gray 255
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 255);
}

// Test getRGBLine (unsigned int* version) with known input
TEST_F(GfxDeviceRGBColorSpaceTest_425, GetRGBLineUintBasic_425) {
    const int length = 1;
    unsigned char in[3] = {255, 0, 0}; // Red
    unsigned int out[length];
    colorSpace.getRGBLine(in, out, length);
    // Output should contain packed RGB for red
    // Exact packing depends on implementation, just ensure it's non-zero for red
    EXPECT_NE(out[0], 0u);
}

// Test getRGBLine (unsigned char* version) with known input
TEST_F(GfxDeviceRGBColorSpaceTest_425, GetRGBLineUcharBasic_425) {
    const int length = 1;
    unsigned char in[3] = {128, 64, 32};
    unsigned char out[3];
    colorSpace.getRGBLine(in, out, length);
    EXPECT_EQ(out[0], 128);
    EXPECT_EQ(out[1], 64);
    EXPECT_EQ(out[2], 32);
}

// Test getRGBXLine with known input
TEST_F(GfxDeviceRGBColorSpaceTest_425, GetRGBXLineBasic_425) {
    const int length = 1;
    unsigned char in[3] = {100, 150, 200};
    unsigned char out[4];
    colorSpace.getRGBXLine(in, out, length);
    EXPECT_EQ(out[0], 100);
    EXPECT_EQ(out[1], 150);
    EXPECT_EQ(out[2], 200);
    EXPECT_EQ(out[3], 255);
}

// Test getCMYKLine with known input
TEST_F(GfxDeviceRGBColorSpaceTest_425, GetCMYKLineBasic_425) {
    const int length = 1;
    unsigned char in[3] = {255, 255, 255}; // White
    unsigned char out[4];
    colorSpace.getCMYKLine(in, out, length);
    // White in CMYK should be (0,0,0,0)
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    EXPECT_EQ(out[3], 0);
}

// Test getDeviceNLine with length 0 (boundary)
TEST_F(GfxDeviceRGBColorSpaceTest_425, GetDeviceNLineZeroLength_425) {
    unsigned char in[1] = {0};
    unsigned char out[1] = {0xFF};
    colorSpace.getDeviceNLine(in, out, 0);
    // Output should remain unchanged
    EXPECT_EQ(out[0], 0xFF);
}

// Test getGrayLine with length 0 (boundary)
TEST_F(GfxDeviceRGBColorSpaceTest_425, GetGrayLineZeroLength_425) {
    unsigned char in[1] = {0};
    unsigned char out[1] = {0xFF};
    colorSpace.getGrayLine(in, out, 0);
    EXPECT_EQ(out[0], 0xFF);
}

// Test that copied color space also reports useGetCMYKLine as true
TEST_F(GfxDeviceRGBColorSpaceTest_425, CopiedUseGetCMYKLineReturnsTrue_425) {
    auto copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->useGetCMYKLine());
}

// Test getDeviceN for black
TEST_F(GfxDeviceRGBColorSpaceTest_425, GetDeviceNForBlack_425) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxColor deviceN;
    memset(&deviceN, 0, sizeof(deviceN));
    colorSpace.getDeviceN(&color, &deviceN);
    // DeviceN for black from RGB: spot colors should reflect black
    // Just verify it doesn't crash and produces some output
    // The K channel (index 3) should be max for black
    EXPECT_EQ(deviceN.c[3], gfxColorComp1);
}
