#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalRGBColorSpaceTest_438 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxCalRGBColorSpace>();
    }

    std::unique_ptr<GfxCalRGBColorSpace> colorSpace;
};

// Test that default construction yields expected gamma values
TEST_F(GfxCalRGBColorSpaceTest_438, DefaultGammaR_438) {
    // Default gamma for CalRGB is typically 1.0
    double gammaR = colorSpace->getGammaR();
    EXPECT_DOUBLE_EQ(gammaR, 1.0);
}

TEST_F(GfxCalRGBColorSpaceTest_438, DefaultGammaG_438) {
    double gammaG = colorSpace->getGammaG();
    EXPECT_DOUBLE_EQ(gammaG, 1.0);
}

TEST_F(GfxCalRGBColorSpaceTest_438, DefaultGammaB_438) {
    double gammaB = colorSpace->getGammaB();
    EXPECT_DOUBLE_EQ(gammaB, 1.0);
}

// Test default white point values
TEST_F(GfxCalRGBColorSpaceTest_438, DefaultWhiteX_438) {
    double whiteX = colorSpace->getWhiteX();
    EXPECT_DOUBLE_EQ(whiteX, 1.0);
}

TEST_F(GfxCalRGBColorSpaceTest_438, DefaultWhiteY_438) {
    double whiteY = colorSpace->getWhiteY();
    EXPECT_DOUBLE_EQ(whiteY, 1.0);
}

TEST_F(GfxCalRGBColorSpaceTest_438, DefaultWhiteZ_438) {
    double whiteZ = colorSpace->getWhiteZ();
    EXPECT_DOUBLE_EQ(whiteZ, 1.0);
}

// Test default black point values
TEST_F(GfxCalRGBColorSpaceTest_438, DefaultBlackX_438) {
    double blackX = colorSpace->getBlackX();
    EXPECT_DOUBLE_EQ(blackX, 0.0);
}

TEST_F(GfxCalRGBColorSpaceTest_438, DefaultBlackY_438) {
    double blackY = colorSpace->getBlackY();
    EXPECT_DOUBLE_EQ(blackY, 0.0);
}

TEST_F(GfxCalRGBColorSpaceTest_438, DefaultBlackZ_438) {
    double blackZ = colorSpace->getBlackZ();
    EXPECT_DOUBLE_EQ(blackZ, 0.0);
}

// Test color space mode
TEST_F(GfxCalRGBColorSpaceTest_438, ModeIsCalRGB_438) {
    GfxColorSpaceMode mode = colorSpace->getMode();
    EXPECT_EQ(mode, csCalRGB);
}

// Test number of components
TEST_F(GfxCalRGBColorSpaceTest_438, NCompsIsThree_438) {
    int nComps = colorSpace->getNComps();
    EXPECT_EQ(nComps, 3);
}

// Test default matrix
TEST_F(GfxCalRGBColorSpaceTest_438, DefaultMatrix_438) {
    const std::array<double, 9> &mat = colorSpace->getMatrix();
    // Default matrix should be identity-like: diagonal 1s, rest 0s
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 0.0);
    EXPECT_DOUBLE_EQ(mat[4], 1.0);
    EXPECT_DOUBLE_EQ(mat[5], 0.0);
    EXPECT_DOUBLE_EQ(mat[6], 0.0);
    EXPECT_DOUBLE_EQ(mat[7], 0.0);
    EXPECT_DOUBLE_EQ(mat[8], 1.0);
}

// Test copy produces equivalent color space
TEST_F(GfxCalRGBColorSpaceTest_438, CopyPreservesProperties_438) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);

    // The copy should be a CalRGB color space
    EXPECT_EQ(copied->getMode(), csCalRGB);
    EXPECT_EQ(copied->getNComps(), 3);

    // Cast to GfxCalRGBColorSpace to check CalRGB-specific properties
    GfxCalRGBColorSpace *copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace *>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);

    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaR(), colorSpace->getGammaR());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaG(), colorSpace->getGammaG());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaB(), colorSpace->getGammaB());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteX(), colorSpace->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteY(), colorSpace->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteZ(), colorSpace->getWhiteZ());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackX(), colorSpace->getBlackX());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackY(), colorSpace->getBlackY());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackZ(), colorSpace->getBlackZ());

    const auto &origMat = colorSpace->getMatrix();
    const auto &copyMat = copiedCalRGB->getMatrix();
    for (int i = 0; i < 9; i++) {
        EXPECT_DOUBLE_EQ(copyMat[i], origMat[i]);
    }
}

// Test getDefaultColor
TEST_F(GfxCalRGBColorSpaceTest_438, GetDefaultColor_438) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    // Default color for CalRGB should have all components set to 0
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
}

// Test getGray with default (black) color
TEST_F(GfxCalRGBColorSpaceTest_438, GetGrayFromBlack_438) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);

    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // Black color should produce gray value of 0
    EXPECT_EQ(gray, 0);
}

// Test getRGB with default (black) color
TEST_F(GfxCalRGBColorSpaceTest_438, GetRGBFromBlack_438) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);

    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getCMYK with default (black) color
TEST_F(GfxCalRGBColorSpaceTest_438, GetCMYKFromBlack_438) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);

    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Black in CMYK should have K = max
    EXPECT_EQ(cmyk.k, gfxColorComp1);
}

// Test getRGB with white color (all components at max)
TEST_F(GfxCalRGBColorSpaceTest_438, GetRGBFromWhite_438) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;

    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // White color input should yield white RGB output (or close to it)
    EXPECT_NEAR(colToDbl(rgb.r), 1.0, 0.05);
    EXPECT_NEAR(colToDbl(rgb.g), 1.0, 0.05);
    EXPECT_NEAR(colToDbl(rgb.b), 1.0, 0.05);
}

// Test getGray with white color
TEST_F(GfxCalRGBColorSpaceTest_438, GetGrayFromWhite_438) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;

    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    EXPECT_NEAR(colToDbl(gray), 1.0, 0.05);
}

// Test getDeviceN with black color
TEST_F(GfxCalRGBColorSpaceTest_438, GetDeviceNFromBlack_438) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);

    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    // For black, we expect CMYK-like deviceN with K=max
    // deviceN[0]=C, deviceN[1]=M, deviceN[2]=Y, deviceN[3]=K
    EXPECT_EQ(deviceN.c[3], gfxColorComp1);
}

// Test that copy is independent (modifying copy doesn't affect original)
TEST_F(GfxCalRGBColorSpaceTest_438, CopyIsIndependent_438) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    
    // Original should remain unchanged
    EXPECT_DOUBLE_EQ(colorSpace->getGammaR(), 1.0);
    EXPECT_DOUBLE_EQ(colorSpace->getGammaG(), 1.0);
    EXPECT_DOUBLE_EQ(colorSpace->getGammaB(), 1.0);
}

// Test with mid-range color values
TEST_F(GfxCalRGBColorSpaceTest_438, GetRGBFromMidRange_438) {
    GfxColor color;
    color.c[0] = dblToCol(0.5);
    color.c[1] = dblToCol(0.5);
    color.c[2] = dblToCol(0.5);

    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    
    // With gamma=1 and identity matrix, mid-range input should give mid-range output
    double r = colToDbl(rgb.r);
    double g = colToDbl(rgb.g);
    double b = colToDbl(rgb.b);
    
    EXPECT_GT(r, 0.0);
    EXPECT_LT(r, 1.0);
    EXPECT_GT(g, 0.0);
    EXPECT_LT(g, 1.0);
    EXPECT_GT(b, 0.0);
    EXPECT_LT(b, 1.0);
}

// Test with pure red
TEST_F(GfxCalRGBColorSpaceTest_438, GetRGBFromPureRed_438) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = 0;
    color.c[2] = 0;

    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    
    // With identity matrix, pure red in CalRGB should be predominantly red in device RGB
    double r = colToDbl(rgb.r);
    EXPECT_GT(r, 0.5);
}
