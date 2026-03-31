#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalRGBColorSpaceTest_436 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxCalRGBColorSpace>();
    }

    std::unique_ptr<GfxCalRGBColorSpace> colorSpace;
};

// Test that default-constructed GfxCalRGBColorSpace returns expected default blackY value
TEST_F(GfxCalRGBColorSpaceTest_436, DefaultBlackYIsZero_436) {
    // Black point defaults are typically 0.0 in PDF spec for CalRGB
    EXPECT_DOUBLE_EQ(0.0, colorSpace->getBlackY());
}

// Test that default blackX is also 0
TEST_F(GfxCalRGBColorSpaceTest_436, DefaultBlackXIsZero_436) {
    EXPECT_DOUBLE_EQ(0.0, colorSpace->getBlackX());
}

// Test that default blackZ is also 0
TEST_F(GfxCalRGBColorSpaceTest_436, DefaultBlackZIsZero_436) {
    EXPECT_DOUBLE_EQ(0.0, colorSpace->getBlackZ());
}

// Test default white point values (PDF spec default WhitePoint for D65-like)
TEST_F(GfxCalRGBColorSpaceTest_436, DefaultWhiteY_436) {
    // WhiteY should be 1.0 by default (required in PDF spec)
    EXPECT_DOUBLE_EQ(1.0, colorSpace->getWhiteY());
}

TEST_F(GfxCalRGBColorSpaceTest_436, DefaultWhiteX_436) {
    EXPECT_DOUBLE_EQ(1.0, colorSpace->getWhiteX());
}

TEST_F(GfxCalRGBColorSpaceTest_436, DefaultWhiteZ_436) {
    EXPECT_DOUBLE_EQ(1.0, colorSpace->getWhiteZ());
}

// Test default gamma values (should be 1.0 by PDF spec default)
TEST_F(GfxCalRGBColorSpaceTest_436, DefaultGammaR_436) {
    EXPECT_DOUBLE_EQ(1.0, colorSpace->getGammaR());
}

TEST_F(GfxCalRGBColorSpaceTest_436, DefaultGammaG_436) {
    EXPECT_DOUBLE_EQ(1.0, colorSpace->getGammaG());
}

TEST_F(GfxCalRGBColorSpaceTest_436, DefaultGammaB_436) {
    EXPECT_DOUBLE_EQ(1.0, colorSpace->getGammaB());
}

// Test that getMode returns the correct color space mode
TEST_F(GfxCalRGBColorSpaceTest_436, ModeIsCalRGB_436) {
    EXPECT_EQ(csCalRGB, colorSpace->getMode());
}

// Test that getNComps returns 3 for RGB
TEST_F(GfxCalRGBColorSpaceTest_436, NCompsIsThree_436) {
    EXPECT_EQ(3, colorSpace->getNComps());
}

// Test the matrix accessor returns a 9-element array
TEST_F(GfxCalRGBColorSpaceTest_436, MatrixHasNineElements_436) {
    const std::array<double, 9>& mat = colorSpace->getMatrix();
    EXPECT_EQ(9u, mat.size());
}

// Test default matrix values (identity-like matrix by default)
TEST_F(GfxCalRGBColorSpaceTest_436, DefaultMatrixValues_436) {
    const std::array<double, 9>& mat = colorSpace->getMatrix();
    // Default CalRGB matrix is typically identity: 
    // 1 0 0 / 0 1 0 / 0 0 1
    EXPECT_DOUBLE_EQ(1.0, mat[0]);
    EXPECT_DOUBLE_EQ(0.0, mat[1]);
    EXPECT_DOUBLE_EQ(0.0, mat[2]);
    EXPECT_DOUBLE_EQ(0.0, mat[3]);
    EXPECT_DOUBLE_EQ(1.0, mat[4]);
    EXPECT_DOUBLE_EQ(0.0, mat[5]);
    EXPECT_DOUBLE_EQ(0.0, mat[6]);
    EXPECT_DOUBLE_EQ(0.0, mat[7]);
    EXPECT_DOUBLE_EQ(1.0, mat[8]);
}

// Test copy creates independent object with same blackY
TEST_F(GfxCalRGBColorSpaceTest_436, CopyPreservesBlackY_436) {
    auto copied = colorSpace->copy();
    ASSERT_NE(nullptr, copied.get());
    auto* copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(nullptr, copiedCalRGB);
    EXPECT_DOUBLE_EQ(colorSpace->getBlackY(), copiedCalRGB->getBlackY());
}

// Test copy preserves all properties
TEST_F(GfxCalRGBColorSpaceTest_436, CopyPreservesAllProperties_436) {
    auto copied = colorSpace->copy();
    auto* copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(nullptr, copiedCalRGB);
    
    EXPECT_DOUBLE_EQ(colorSpace->getWhiteX(), copiedCalRGB->getWhiteX());
    EXPECT_DOUBLE_EQ(colorSpace->getWhiteY(), copiedCalRGB->getWhiteY());
    EXPECT_DOUBLE_EQ(colorSpace->getWhiteZ(), copiedCalRGB->getWhiteZ());
    EXPECT_DOUBLE_EQ(colorSpace->getBlackX(), copiedCalRGB->getBlackX());
    EXPECT_DOUBLE_EQ(colorSpace->getBlackY(), copiedCalRGB->getBlackY());
    EXPECT_DOUBLE_EQ(colorSpace->getBlackZ(), copiedCalRGB->getBlackZ());
    EXPECT_DOUBLE_EQ(colorSpace->getGammaR(), copiedCalRGB->getGammaR());
    EXPECT_DOUBLE_EQ(colorSpace->getGammaG(), copiedCalRGB->getGammaG());
    EXPECT_DOUBLE_EQ(colorSpace->getGammaB(), copiedCalRGB->getGammaB());
    EXPECT_EQ(colorSpace->getNComps(), copiedCalRGB->getNComps());
    EXPECT_EQ(colorSpace->getMode(), copiedCalRGB->getMode());
}

// Test getDefaultColor sets color to default (all zeros for CalRGB typically)
TEST_F(GfxCalRGBColorSpaceTest_436, GetDefaultColor_436) {
    GfxColor color;
    // Initialize to non-zero values
    for (int i = 0; i < gfxColorMaxComps; i++) {
        color.c[i] = 65535;
    }
    colorSpace->getDefaultColor(&color);
    // Default color for CalRGB is typically all components at 0
    EXPECT_EQ(0, color.c[0]);
    EXPECT_EQ(0, color.c[1]);
    EXPECT_EQ(0, color.c[2]);
}

// Test getGray with a black color (all zeros)
TEST_F(GfxCalRGBColorSpaceTest_436, GetGrayBlack_436) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    EXPECT_EQ(0, gray);
}

// Test getGray with a white color (all max)
TEST_F(GfxCalRGBColorSpaceTest_436, GetGrayWhite_436) {
    GfxColor color;
    color.c[0] = 65535;
    color.c[1] = 65535;
    color.c[2] = 65535;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // White should produce a high gray value
    EXPECT_GT(gray, 0);
}

// Test getRGB with black color
TEST_F(GfxCalRGBColorSpaceTest_436, GetRGBBlack_436) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_EQ(0, rgb.r);
    EXPECT_EQ(0, rgb.g);
    EXPECT_EQ(0, rgb.b);
}

// Test getRGB with white color
TEST_F(GfxCalRGBColorSpaceTest_436, GetRGBWhite_436) {
    GfxColor color;
    color.c[0] = 65535;
    color.c[1] = 65535;
    color.c[2] = 65535;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // Should produce values close to max
    EXPECT_GT(rgb.r, 0);
    EXPECT_GT(rgb.g, 0);
    EXPECT_GT(rgb.b, 0);
}

// Test getCMYK with black color
TEST_F(GfxCalRGBColorSpaceTest_436, GetCMYKBlack_436) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Black in CMYK should have K component set
    EXPECT_GT(cmyk.k, 0);
}

// Test getDeviceN with black color
TEST_F(GfxCalRGBColorSpaceTest_436, GetDeviceNBlack_436) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    // DeviceN for black should have some defined behavior
    // Just verify it doesn't crash
}

// Test that BlackY is consistent with BlackX and BlackZ for default construction
TEST_F(GfxCalRGBColorSpaceTest_436, BlackPointConsistency_436) {
    EXPECT_DOUBLE_EQ(colorSpace->getBlackX(), colorSpace->getBlackY());
    EXPECT_DOUBLE_EQ(colorSpace->getBlackY(), colorSpace->getBlackZ());
}

// Test that copied mode matches original
TEST_F(GfxCalRGBColorSpaceTest_436, CopyModeMatch_436) {
    auto copied = colorSpace->copy();
    EXPECT_EQ(csCalRGB, copied->getMode());
}

// Test with a pure red color
TEST_F(GfxCalRGBColorSpaceTest_436, GetRGBPureRed_436) {
    GfxColor color;
    color.c[0] = 65535;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // Red component should be non-zero
    EXPECT_GT(rgb.r, 0);
}
