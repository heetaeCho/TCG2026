#include <gtest/gtest.h>
#include "GfxState.h"

class GfxDeviceRGBColorSpaceTest_424 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = new GfxDeviceRGBColorSpace();
    }

    void TearDown() override {
        delete colorSpace;
    }

    GfxDeviceRGBColorSpace* colorSpace;
};

TEST_F(GfxDeviceRGBColorSpaceTest_424, UseGetGrayLineReturnsTrue_424) {
    EXPECT_TRUE(colorSpace->useGetGrayLine());
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, UseGetRGBLineReturnsTrue_424) {
    EXPECT_TRUE(colorSpace->useGetRGBLine());
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, UseGetCMYKLineReturnsTrue_424) {
    EXPECT_TRUE(colorSpace->useGetCMYKLine());
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, UseGetDeviceNLineReturnsTrue_424) {
    EXPECT_TRUE(colorSpace->useGetDeviceNLine());
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetModeReturnsDeviceRGB_424) {
    EXPECT_EQ(colorSpace->getMode(), csDeviceRGB);
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetNCompsReturns3_424) {
    EXPECT_EQ(colorSpace->getNComps(), 3);
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, CopyReturnsValidObject_424) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csDeviceRGB);
    EXPECT_EQ(copied->getNComps(), 3);
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetDefaultColor_424) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    // Default color for RGB is typically black (0,0,0)
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetGrayFromBlack_424) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetGrayFromWhite_424) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    EXPECT_EQ(gray, gfxColorComp1);
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetRGBFromColor_424) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, gfxColorComp1);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetRGBWhite_424) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, gfxColorComp1);
    EXPECT_EQ(rgb.g, gfxColorComp1);
    EXPECT_EQ(rgb.b, gfxColorComp1);
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetCMYKFromBlack_424) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Black in RGB -> K=1 in CMYK
    EXPECT_EQ(cmyk.k, gfxColorComp1);
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetCMYKFromWhite_424) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
    EXPECT_EQ(cmyk.k, 0);
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetGrayLineBlack_424) {
    const int length = 3;
    unsigned char in[length * 3] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned char out[length];
    colorSpace->getGrayLine(in, out, length);
    for (int i = 0; i < length; i++) {
        EXPECT_EQ(out[i], 0);
    }
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetGrayLineWhite_424) {
    const int length = 3;
    unsigned char in[length * 3] = {255, 255, 255, 255, 255, 255, 255, 255, 255};
    unsigned char out[length];
    colorSpace->getGrayLine(in, out, length);
    for (int i = 0; i < length; i++) {
        EXPECT_EQ(out[i], 255);
    }
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetRGBLineUintBlack_424) {
    const int length = 2;
    unsigned char in[length * 3] = {0, 0, 0, 0, 0, 0};
    unsigned int out[length];
    colorSpace->getRGBLine(in, out, length);
    for (int i = 0; i < length; i++) {
        // Expect alpha=0xFF in high byte, rest 0
        unsigned int expected = 0xFF000000u;
        EXPECT_EQ(out[i] & 0xFF000000u, 0xFF000000u);
    }
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetRGBLineUcharWhite_424) {
    const int length = 2;
    unsigned char in[length * 3] = {255, 255, 255, 255, 255, 255};
    unsigned char out[length * 3];
    colorSpace->getRGBLine(in, out, length);
    for (int i = 0; i < length * 3; i++) {
        EXPECT_EQ(out[i], 255);
    }
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetRGBXLineWhite_424) {
    const int length = 2;
    unsigned char in[length * 3] = {255, 255, 255, 255, 255, 255};
    unsigned char out[length * 4];
    colorSpace->getRGBXLine(in, out, length);
    for (int i = 0; i < length; i++) {
        EXPECT_EQ(out[i * 4 + 0], 255);
        EXPECT_EQ(out[i * 4 + 1], 255);
        EXPECT_EQ(out[i * 4 + 2], 255);
        EXPECT_EQ(out[i * 4 + 3], 255);
    }
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetCMYKLineBlack_424) {
    const int length = 2;
    unsigned char in[length * 3] = {0, 0, 0, 0, 0, 0};
    unsigned char out[length * 4];
    colorSpace->getCMYKLine(in, out, length);
    for (int i = 0; i < length; i++) {
        // Black: C=0, M=0, Y=0, K=255
        EXPECT_EQ(out[i * 4 + 0], 0);
        EXPECT_EQ(out[i * 4 + 1], 0);
        EXPECT_EQ(out[i * 4 + 2], 0);
        EXPECT_EQ(out[i * 4 + 3], 255);
    }
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetCMYKLineWhite_424) {
    const int length = 2;
    unsigned char in[length * 3] = {255, 255, 255, 255, 255, 255};
    unsigned char out[length * 4];
    colorSpace->getCMYKLine(in, out, length);
    for (int i = 0; i < length; i++) {
        EXPECT_EQ(out[i * 4 + 0], 0);
        EXPECT_EQ(out[i * 4 + 1], 0);
        EXPECT_EQ(out[i * 4 + 2], 0);
        EXPECT_EQ(out[i * 4 + 3], 0);
    }
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetGrayLineSinglePixel_424) {
    const int length = 1;
    unsigned char in[3] = {128, 128, 128};
    unsigned char out[1];
    colorSpace->getGrayLine(in, out, length);
    // Gray should be approximately 128 for a mid-gray
    EXPECT_GE(out[0], 120);
    EXPECT_LE(out[0], 136);
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetGrayLineZeroLength_424) {
    unsigned char in[1] = {0};
    unsigned char out[1] = {0xFF};
    colorSpace->getGrayLine(in, out, 0);
    // out should remain unchanged
    EXPECT_EQ(out[0], 0xFF);
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetDeviceNFromColor_424) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxColor deviceN;
    memset(&deviceN, 0, sizeof(deviceN));
    colorSpace->getDeviceN(&color, &deviceN);
    // deviceN should have some valid output, at minimum not crash
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, CopyPreservesMode_424) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), colorSpace->getMode());
    EXPECT_EQ(copied->getNComps(), colorSpace->getNComps());
    EXPECT_TRUE(copied->useGetGrayLine());
    EXPECT_TRUE(copied->useGetRGBLine());
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetRGBPureGreen_424) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = gfxColorComp1;
    color.c[2] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, gfxColorComp1);
    EXPECT_EQ(rgb.b, 0);
}

TEST_F(GfxDeviceRGBColorSpaceTest_424, GetRGBPureBlue_424) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = gfxColorComp1;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, gfxColorComp1);
}
