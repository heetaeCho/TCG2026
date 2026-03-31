#include <gtest/gtest.h>
#include "GfxState.h"
#include <cstring>
#include <cmath>
#include <vector>

class GfxDeviceCMYKColorSpaceTest_1887 : public ::testing::Test {
protected:
    void SetUp() override {
        cs = new GfxDeviceCMYKColorSpace();
    }

    void TearDown() override {
        delete cs;
    }

    GfxDeviceCMYKColorSpace *cs;
};

// Test that the color space reports correct number of components
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, GetNComps_1887) {
    EXPECT_EQ(cs->getNComps(), 4);
}

// Test that the color space mode is csDeviceCMYK
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, GetMode_1887) {
    EXPECT_EQ(cs->getMode(), csDeviceCMYK);
}

// Test getRGB with all zeros (no ink) -> should produce white (1,1,1)
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, GetRGB_NoInk_White_1887) {
    GfxColor color;
    color.c[0] = 0; // C
    color.c[1] = 0; // M
    color.c[2] = 0; // Y
    color.c[3] = 0; // K
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    EXPECT_NEAR(colToDbl(rgb.r), 1.0, 0.02);
    EXPECT_NEAR(colToDbl(rgb.g), 1.0, 0.02);
    EXPECT_NEAR(colToDbl(rgb.b), 1.0, 0.02);
}

// Test getRGB with full black (K=1) -> should produce black (0,0,0)
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, GetRGB_FullBlack_1887) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    color.c[3] = dblToCol(1.0); // K = 1
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    EXPECT_NEAR(colToDbl(rgb.r), 0.0, 0.02);
    EXPECT_NEAR(colToDbl(rgb.g), 0.0, 0.02);
    EXPECT_NEAR(colToDbl(rgb.b), 0.0, 0.02);
}

// Test getRGB with full cyan -> should have low red, high green and blue components
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, GetRGB_FullCyan_1887) {
    GfxColor color;
    color.c[0] = dblToCol(1.0); // C = 1
    color.c[1] = 0;
    color.c[2] = 0;
    color.c[3] = 0;
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    // Cyan should reduce red
    EXPECT_LT(colToDbl(rgb.r), 0.5);
    EXPECT_GT(colToDbl(rgb.g), 0.5);
    EXPECT_GT(colToDbl(rgb.b), 0.5);
}

// Test getRGB with full magenta -> should have high red, low green, high blue
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, GetRGB_FullMagenta_1887) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = dblToCol(1.0); // M = 1
    color.c[2] = 0;
    color.c[3] = 0;
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    EXPECT_GT(colToDbl(rgb.r), 0.5);
    EXPECT_LT(colToDbl(rgb.g), 0.5);
    EXPECT_GT(colToDbl(rgb.b), 0.5);
}

// Test getRGB with full yellow -> should have high red, high green, low blue
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, GetRGB_FullYellow_1887) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = dblToCol(1.0); // Y = 1
    color.c[3] = 0;
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    EXPECT_GT(colToDbl(rgb.r), 0.5);
    EXPECT_GT(colToDbl(rgb.g), 0.5);
    EXPECT_LT(colToDbl(rgb.b), 0.5);
}

// Test getRGBLine with unsigned char input (byte version)
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, GetRGBLine_ByteInput_NoInk_1887) {
    // All zeros = no ink = white
    unsigned char in[] = {0, 0, 0, 0};
    unsigned char out[3] = {0, 0, 0};
    cs->getRGBLine(in, out, 1);
    EXPECT_NEAR(out[0], 255, 2); // R
    EXPECT_NEAR(out[1], 255, 2); // G
    EXPECT_NEAR(out[2], 255, 2); // B
}

// Test getRGBLine with full black
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, GetRGBLine_ByteInput_FullBlack_1887) {
    unsigned char in[] = {0, 0, 0, 255}; // K=255
    unsigned char out[3] = {255, 255, 255};
    cs->getRGBLine(in, out, 1);
    EXPECT_NEAR(out[0], 0, 2);
    EXPECT_NEAR(out[1], 0, 2);
    EXPECT_NEAR(out[2], 0, 2);
}

// Test getRGBLine with multiple pixels
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, GetRGBLine_MultiplePixels_1887) {
    // Two pixels: white and black
    unsigned char in[] = {0, 0, 0, 0, 0, 0, 0, 255};
    unsigned char out[6] = {0};
    cs->getRGBLine(in, out, 2);
    // First pixel: white
    EXPECT_NEAR(out[0], 255, 2);
    EXPECT_NEAR(out[1], 255, 2);
    EXPECT_NEAR(out[2], 255, 2);
    // Second pixel: black
    EXPECT_NEAR(out[3], 0, 2);
    EXPECT_NEAR(out[4], 0, 2);
    EXPECT_NEAR(out[5], 0, 2);
}

// Test getRGBLine with unsigned int output
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, GetRGBLine_UintOutput_NoInk_1887) {
    unsigned char in[] = {0, 0, 0, 0};
    unsigned int out[1] = {0};
    cs->getRGBLine(in, out, 1);
    // Extract RGB from unsigned int (format is typically 0x00RRGGBB or similar)
    unsigned char r = (out[0] >> 16) & 0xFF;
    unsigned char g = (out[0] >> 8) & 0xFF;
    unsigned char b = out[0] & 0xFF;
    EXPECT_NEAR(r, 255, 2);
    EXPECT_NEAR(g, 255, 2);
    EXPECT_NEAR(b, 255, 2);
}

// Test getRGBLine with zero length
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, GetRGBLine_ZeroLength_1887) {
    unsigned char in[] = {0, 0, 0, 0};
    unsigned char out[3] = {42, 42, 42};
    cs->getRGBLine(in, out, 0);
    // Output should be unchanged
    EXPECT_EQ(out[0], 42);
    EXPECT_EQ(out[1], 42);
    EXPECT_EQ(out[2], 42);
}

// Test copy
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, Copy_1887) {
    GfxColorSpace *copy = cs->copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getMode(), csDeviceCMYK);
    EXPECT_EQ(copy->getNComps(), 4);

    // Verify the copy produces same RGB results
    GfxColor color;
    color.c[0] = dblToCol(0.5);
    color.c[1] = dblToCol(0.3);
    color.c[2] = dblToCol(0.2);
    color.c[3] = dblToCol(0.1);
    GfxRGB rgb1, rgb2;
    cs->getRGB(&color, &rgb1);
    copy->getRGB(&color, &rgb2);
    EXPECT_EQ(colToDbl(rgb1.r), colToDbl(rgb2.r));
    EXPECT_EQ(colToDbl(rgb1.g), colToDbl(rgb2.g));
    EXPECT_EQ(colToDbl(rgb1.b), colToDbl(rgb2.b));

    delete copy;
}

// Test getRGBLine with full CMYK values
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, GetRGBLine_FullCMYK_Black_1887) {
    // Full CMYK should produce very dark / black
    unsigned char in[] = {255, 255, 255, 255};
    unsigned char out[3] = {255, 255, 255};
    cs->getRGBLine(in, out, 1);
    EXPECT_NEAR(out[0], 0, 5);
    EXPECT_NEAR(out[1], 0, 5);
    EXPECT_NEAR(out[2], 0, 5);
}

// Test getRGBLine byte input with mid-range values
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, GetRGBLine_MidRange_1887) {
    unsigned char in[] = {128, 0, 0, 0}; // ~50% cyan
    unsigned char out[3] = {0};
    cs->getRGBLine(in, out, 1);
    // With 50% cyan, red should be reduced, green and blue should be higher
    EXPECT_LT(out[0], 200); // R reduced
    EXPECT_GT(out[1], 100); // G still visible
    EXPECT_GT(out[2], 100); // B still visible
}

// Test getDefaultColor
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, GetDefaultColor_1887) {
    GfxColor color;
    cs->getDefaultColor(&color);
    // Default CMYK should be all zeros (white)
    EXPECT_EQ(colToDbl(color.c[0]), 0.0);
    EXPECT_EQ(colToDbl(color.c[1]), 0.0);
    EXPECT_EQ(colToDbl(color.c[2]), 0.0);
    EXPECT_EQ(colToDbl(color.c[3]), 0.0);
}

// Test getCMYK - should return the same CMYK values
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, GetCMYK_1887) {
    GfxColor color;
    color.c[0] = dblToCol(0.1);
    color.c[1] = dblToCol(0.2);
    color.c[2] = dblToCol(0.3);
    color.c[3] = dblToCol(0.4);
    GfxCMYK cmyk;
    cs->getCMYK(&color, &cmyk);
    EXPECT_NEAR(colToDbl(cmyk.c), 0.1, 0.01);
    EXPECT_NEAR(colToDbl(cmyk.m), 0.2, 0.01);
    EXPECT_NEAR(colToDbl(cmyk.y), 0.3, 0.01);
    EXPECT_NEAR(colToDbl(cmyk.k), 0.4, 0.01);
}

// Test consistency between getRGB and getRGBLine
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, Consistency_getRGB_getRGBLine_1887) {
    unsigned char in[] = {64, 128, 192, 32};
    unsigned char out[3] = {0};
    cs->getRGBLine(in, out, 1);

    GfxColor color;
    color.c[0] = dblToCol(64.0 / 255.0);
    color.c[1] = dblToCol(128.0 / 255.0);
    color.c[2] = dblToCol(192.0 / 255.0);
    color.c[3] = dblToCol(32.0 / 255.0);
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);

    // Both methods should produce similar results
    EXPECT_NEAR(out[0], colToByte(rgb.r), 3);
    EXPECT_NEAR(out[1], colToByte(rgb.g), 3);
    EXPECT_NEAR(out[2], colToByte(rgb.b), 3);
}

// Test getGray with full black
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, GetGray_FullBlack_1887) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    color.c[3] = dblToCol(1.0);
    GfxGray gray;
    cs->getGray(&color, &gray);
    EXPECT_NEAR(colToDbl(gray), 0.0, 0.05);
}

// Test getGray with no ink (white)
TEST_F(GfxDeviceCMYKColorSpaceTest_1887, GetGray_NoInk_White_1887) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    color.c[3] = 0;
    GfxGray gray;
    cs->getGray(&color, &gray);
    EXPECT_NEAR(colToDbl(gray), 1.0, 0.05);
}
