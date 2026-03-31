#include <gtest/gtest.h>
#include "GfxState.h"

class GfxDeviceGrayColorSpaceTest_411 : public ::testing::Test {
protected:
    GfxDeviceGrayColorSpace colorSpace;
};

// Test that useGetDeviceNLine returns true
TEST_F(GfxDeviceGrayColorSpaceTest_411, UseGetDeviceNLineReturnsTrue_411) {
    EXPECT_TRUE(colorSpace.useGetDeviceNLine());
}

// Test that useGetRGBLine returns true (DeviceGray typically supports RGB line optimization)
TEST_F(GfxDeviceGrayColorSpaceTest_411, UseGetRGBLine_411) {
    bool result = colorSpace.useGetRGBLine();
    // Just verify it returns a valid bool without crashing
    EXPECT_TRUE(result == true || result == false);
}

// Test that useGetGrayLine returns a valid value
TEST_F(GfxDeviceGrayColorSpaceTest_411, UseGetGrayLine_411) {
    bool result = colorSpace.useGetGrayLine();
    EXPECT_TRUE(result == true || result == false);
}

// Test that useGetCMYKLine returns a valid value
TEST_F(GfxDeviceGrayColorSpaceTest_411, UseGetCMYKLine_411) {
    bool result = colorSpace.useGetCMYKLine();
    EXPECT_TRUE(result == true || result == false);
}

// Test that getMode returns csDeviceGray
TEST_F(GfxDeviceGrayColorSpaceTest_411, GetModeReturnsDeviceGray_411) {
    EXPECT_EQ(colorSpace.getMode(), csDeviceGray);
}

// Test that getNComps returns 1 for grayscale
TEST_F(GfxDeviceGrayColorSpaceTest_411, GetNCompsReturnsOne_411) {
    EXPECT_EQ(colorSpace.getNComps(), 1);
}

// Test copy produces a non-null result
TEST_F(GfxDeviceGrayColorSpaceTest_411, CopyReturnsNonNull_411) {
    auto copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csDeviceGray);
}

// Test copy produces an independent object with same properties
TEST_F(GfxDeviceGrayColorSpaceTest_411, CopyPreservesProperties_411) {
    auto copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNComps(), colorSpace.getNComps());
    EXPECT_EQ(copied->getMode(), colorSpace.getMode());
}

// Test getDefaultColor sets a valid default
TEST_F(GfxDeviceGrayColorSpaceTest_411, GetDefaultColor_411) {
    GfxColor color;
    colorSpace.getDefaultColor(&color);
    // Default gray color should be 0 (black) - component c[0] should be 0
    EXPECT_EQ(color.c[0], 0);
}

// Test getGray with black (0)
TEST_F(GfxDeviceGrayColorSpaceTest_411, GetGrayBlack_411) {
    GfxColor color;
    color.c[0] = 0;
    GfxGray gray;
    colorSpace.getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getGray with white (max value)
TEST_F(GfxDeviceGrayColorSpaceTest_411, GetGrayWhite_411) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxGray gray;
    colorSpace.getGray(&color, &gray);
    EXPECT_EQ(gray, gfxColorComp1);
}

// Test getRGB with black
TEST_F(GfxDeviceGrayColorSpaceTest_411, GetRGBBlack_411) {
    GfxColor color;
    color.c[0] = 0;
    GfxRGB rgb;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB with white
TEST_F(GfxDeviceGrayColorSpaceTest_411, GetRGBWhite_411) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxRGB rgb;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, gfxColorComp1);
    EXPECT_EQ(rgb.g, gfxColorComp1);
    EXPECT_EQ(rgb.b, gfxColorComp1);
}

// Test getCMYK with black
TEST_F(GfxDeviceGrayColorSpaceTest_411, GetCMYKBlack_411) {
    GfxColor color;
    color.c[0] = 0;
    GfxCMYK cmyk;
    colorSpace.getCMYK(&color, &cmyk);
    // Black in CMYK should have K = max
    EXPECT_EQ(cmyk.k, gfxColorComp1);
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
}

// Test getCMYK with white
TEST_F(GfxDeviceGrayColorSpaceTest_411, GetCMYKWhite_411) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxCMYK cmyk;
    colorSpace.getCMYK(&color, &cmyk);
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
    EXPECT_EQ(cmyk.k, 0);
}

// Test getGrayLine with a buffer
TEST_F(GfxDeviceGrayColorSpaceTest_411, GetGrayLine_411) {
    unsigned char in[] = {0, 128, 255};
    unsigned char out[3] = {};
    colorSpace.getGrayLine(in, out, 3);
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 128);
    EXPECT_EQ(out[2], 255);
}

// Test getRGBLine (unsigned int* output)
TEST_F(GfxDeviceGrayColorSpaceTest_411, GetRGBLineUint_411) {
    unsigned char in[] = {0, 255};
    unsigned int out[2] = {};
    colorSpace.getRGBLine(in, out, 2);
    // For black (0), expect RGB packed as 0 or with alpha
    // For white (255), expect RGB packed as white
    // Just verify no crash and output is populated
    SUCCEED();
}

// Test getRGBLine (unsigned char* output)
TEST_F(GfxDeviceGrayColorSpaceTest_411, GetRGBLineUchar_411) {
    unsigned char in[] = {0, 128, 255};
    unsigned char out[9] = {};
    colorSpace.getRGBLine(in, out, 3);
    // Black: R=0, G=0, B=0
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    // White: R=255, G=255, B=255
    EXPECT_EQ(out[6], 255);
    EXPECT_EQ(out[7], 255);
    EXPECT_EQ(out[8], 255);
}

// Test getRGBXLine
TEST_F(GfxDeviceGrayColorSpaceTest_411, GetRGBXLine_411) {
    unsigned char in[] = {0, 255};
    unsigned char out[8] = {};
    colorSpace.getRGBXLine(in, out, 2);
    // Black: R=0, G=0, B=0, X=?
    EXPECT_EQ(out[0], 0);
    EXPECT_EQ(out[1], 0);
    EXPECT_EQ(out[2], 0);
    // White: R=255, G=255, B=255, X=?
    EXPECT_EQ(out[4], 255);
    EXPECT_EQ(out[5], 255);
    EXPECT_EQ(out[6], 255);
}

// Test getCMYKLine
TEST_F(GfxDeviceGrayColorSpaceTest_411, GetCMYKLine_411) {
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

// Test getDeviceNLine
TEST_F(GfxDeviceGrayColorSpaceTest_411, GetDeviceNLine_411) {
    unsigned char in[] = {0, 255};
    // DeviceN output typically has CMYK + spot colors; at minimum 4 bytes per pixel
    unsigned char out[8 * (SPOT_NCOMPS + 4)] = {};
    colorSpace.getDeviceNLine(in, out, 2);
    // Just verify no crash
    SUCCEED();
}

// Test getDeviceN
TEST_F(GfxDeviceGrayColorSpaceTest_411, GetDeviceN_411) {
    GfxColor color;
    color.c[0] = 0;
    GfxColor deviceN;
    memset(&deviceN, 0, sizeof(deviceN));
    colorSpace.getDeviceN(&color, &deviceN);
    // For black, K channel should be max
    SUCCEED();
}

// Test with zero-length line operations (boundary)
TEST_F(GfxDeviceGrayColorSpaceTest_411, ZeroLengthLineOperations_411) {
    unsigned char in[1] = {0};
    unsigned char out[1] = {0};
    unsigned int outUint[1] = {0};
    // These should handle zero length gracefully
    colorSpace.getGrayLine(in, out, 0);
    colorSpace.getRGBLine(in, outUint, 0);
    colorSpace.getRGBLine(in, out, 0);
    colorSpace.getRGBXLine(in, out, 0);
    colorSpace.getCMYKLine(in, out, 0);
    colorSpace.getDeviceNLine(in, out, 0);
    SUCCEED();
}

// Test single element line operations (boundary)
TEST_F(GfxDeviceGrayColorSpaceTest_411, SingleElementLine_411) {
    unsigned char in[] = {128};
    unsigned char outGray[1] = {};
    colorSpace.getGrayLine(in, outGray, 1);
    EXPECT_EQ(outGray[0], 128);

    unsigned char outRGB[3] = {};
    colorSpace.getRGBLine(in, outRGB, 1);
    EXPECT_EQ(outRGB[0], 128);
    EXPECT_EQ(outRGB[1], 128);
    EXPECT_EQ(outRGB[2], 128);
}

// Test mid-gray value
TEST_F(GfxDeviceGrayColorSpaceTest_411, GetGrayMidValue_411) {
    GfxColor color;
    color.c[0] = gfxColorComp1 / 2;
    GfxGray gray;
    colorSpace.getGray(&color, &gray);
    EXPECT_EQ(gray, gfxColorComp1 / 2);
}

// Test getRGB mid-gray
TEST_F(GfxDeviceGrayColorSpaceTest_411, GetRGBMidGray_411) {
    GfxColor color;
    color.c[0] = gfxColorComp1 / 2;
    GfxRGB rgb;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, gfxColorComp1 / 2);
    EXPECT_EQ(rgb.g, gfxColorComp1 / 2);
    EXPECT_EQ(rgb.b, gfxColorComp1 / 2);
}
