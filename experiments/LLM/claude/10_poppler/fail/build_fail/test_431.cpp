#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalRGBColorSpaceTest_431 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxCalRGBColorSpace>();
    }

    std::unique_ptr<GfxCalRGBColorSpace> colorSpace;
};

// Test that getNComps returns 3 for CalRGB color space
TEST_F(GfxCalRGBColorSpaceTest_431, GetNCompsReturnsThree_431) {
    EXPECT_EQ(colorSpace->getNComps(), 3);
}

// Test that getMode returns the correct mode for CalRGB
TEST_F(GfxCalRGBColorSpaceTest_431, GetModeReturnsCalRGB_431) {
    EXPECT_EQ(colorSpace->getMode(), csCalRGB);
}

// Test default white point values
TEST_F(GfxCalRGBColorSpaceTest_431, DefaultWhitePointValues_431) {
    // Default white point should be D65 or some default
    double whiteX = colorSpace->getWhiteX();
    double whiteY = colorSpace->getWhiteY();
    double whiteZ = colorSpace->getWhiteZ();
    // White point Y should be 1.0 by convention
    EXPECT_DOUBLE_EQ(whiteY, 1.0);
}

// Test default black point values (should be 0,0,0)
TEST_F(GfxCalRGBColorSpaceTest_431, DefaultBlackPointValues_431) {
    EXPECT_DOUBLE_EQ(colorSpace->getBlackX(), 0.0);
    EXPECT_DOUBLE_EQ(colorSpace->getBlackY(), 0.0);
    EXPECT_DOUBLE_EQ(colorSpace->getBlackZ(), 0.0);
}

// Test default gamma values (should be 1.0 for each channel)
TEST_F(GfxCalRGBColorSpaceTest_431, DefaultGammaValues_431) {
    EXPECT_DOUBLE_EQ(colorSpace->getGammaR(), 1.0);
    EXPECT_DOUBLE_EQ(colorSpace->getGammaG(), 1.0);
    EXPECT_DOUBLE_EQ(colorSpace->getGammaB(), 1.0);
}

// Test default matrix values
TEST_F(GfxCalRGBColorSpaceTest_431, DefaultMatrixValues_431) {
    const std::array<double, 9> &mat = colorSpace->getMatrix();
    // Default matrix should be identity-like (1 0 0 0 1 0 0 0 1)
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

// Test getDefaultColor
TEST_F(GfxCalRGBColorSpaceTest_431, GetDefaultColor_431) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    // Default color for CalRGB should be black (0, 0, 0)
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
}

// Test getGray with black color
TEST_F(GfxCalRGBColorSpaceTest_431, GetGrayWithBlack_431) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getGray with white color
TEST_F(GfxCalRGBColorSpaceTest_431, GetGrayWithWhite_431) {
    GfxColor color;
    color.c[0] = dblToCol(1.0);
    color.c[1] = dblToCol(1.0);
    color.c[2] = dblToCol(1.0);
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    EXPECT_GE(gray, dblToCol(0.9));
    EXPECT_LE(gray, dblToCol(1.0));
}

// Test getRGB with black color
TEST_F(GfxCalRGBColorSpaceTest_431, GetRGBWithBlack_431) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB with white color
TEST_F(GfxCalRGBColorSpaceTest_431, GetRGBWithWhite_431) {
    GfxColor color;
    color.c[0] = dblToCol(1.0);
    color.c[1] = dblToCol(1.0);
    color.c[2] = dblToCol(1.0);
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // Should be close to white
    EXPECT_GE(colToDbl(rgb.r), 0.9);
    EXPECT_GE(colToDbl(rgb.g), 0.9);
    EXPECT_GE(colToDbl(rgb.b), 0.9);
}

// Test getCMYK with black color
TEST_F(GfxCalRGBColorSpaceTest_431, GetCMYKWithBlack_431) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Black in CMYK should have K close to max
    EXPECT_GE(cmyk.k, dblToCol(0.9));
}

// Test getCMYK with white color
TEST_F(GfxCalRGBColorSpaceTest_431, GetCMYKWithWhite_431) {
    GfxColor color;
    color.c[0] = dblToCol(1.0);
    color.c[1] = dblToCol(1.0);
    color.c[2] = dblToCol(1.0);
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // White in CMYK should be (0, 0, 0, 0) approximately
    EXPECT_LE(colToDbl(cmyk.c), 0.1);
    EXPECT_LE(colToDbl(cmyk.m), 0.1);
    EXPECT_LE(colToDbl(cmyk.y), 0.1);
    EXPECT_LE(colToDbl(cmyk.k), 0.1);
}

// Test getDeviceN with black color
TEST_F(GfxCalRGBColorSpaceTest_431, GetDeviceNWithBlack_431) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    // DeviceN for black should have K component high
    // The exact mapping depends on implementation
    EXPECT_GE(colToDbl(deviceN.c[3]), 0.9);
}

// Test copy creates a valid copy
TEST_F(GfxCalRGBColorSpaceTest_431, CopyCreatesValidCopy_431) {
    auto copy = colorSpace->copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getMode(), csCalRGB);
    EXPECT_EQ(copy->getNComps(), 3);
}

// Test copy preserves properties
TEST_F(GfxCalRGBColorSpaceTest_431, CopyPreservesProperties_431) {
    auto copy = colorSpace->copy();
    ASSERT_NE(copy, nullptr);

    // Cast to GfxCalRGBColorSpace to check specific properties
    auto *calRGBCopy = dynamic_cast<GfxCalRGBColorSpace *>(copy.get());
    ASSERT_NE(calRGBCopy, nullptr);

    EXPECT_DOUBLE_EQ(calRGBCopy->getGammaR(), colorSpace->getGammaR());
    EXPECT_DOUBLE_EQ(calRGBCopy->getGammaG(), colorSpace->getGammaG());
    EXPECT_DOUBLE_EQ(calRGBCopy->getGammaB(), colorSpace->getGammaB());
    EXPECT_DOUBLE_EQ(calRGBCopy->getWhiteX(), colorSpace->getWhiteX());
    EXPECT_DOUBLE_EQ(calRGBCopy->getWhiteY(), colorSpace->getWhiteY());
    EXPECT_DOUBLE_EQ(calRGBCopy->getWhiteZ(), colorSpace->getWhiteZ());
    EXPECT_DOUBLE_EQ(calRGBCopy->getBlackX(), colorSpace->getBlackX());
    EXPECT_DOUBLE_EQ(calRGBCopy->getBlackY(), colorSpace->getBlackY());
    EXPECT_DOUBLE_EQ(calRGBCopy->getBlackZ(), colorSpace->getBlackZ());

    const auto &origMat = colorSpace->getMatrix();
    const auto &copyMat = calRGBCopy->getMatrix();
    for (int i = 0; i < 9; i++) {
        EXPECT_DOUBLE_EQ(copyMat[i], origMat[i]);
    }
}

// Test getRGB with a pure red input
TEST_F(GfxCalRGBColorSpaceTest_431, GetRGBWithPureRed_431) {
    GfxColor color;
    color.c[0] = dblToCol(1.0);
    color.c[1] = 0;
    color.c[2] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // Red component should be significant
    EXPECT_GT(colToDbl(rgb.r), 0.5);
}

// Test getRGB with a pure green input
TEST_F(GfxCalRGBColorSpaceTest_431, GetRGBWithPureGreen_431) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = dblToCol(1.0);
    color.c[2] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // Green component should be significant
    EXPECT_GT(colToDbl(rgb.g), 0.5);
}

// Test getRGB with a pure blue input
TEST_F(GfxCalRGBColorSpaceTest_431, GetRGBWithPureBlue_431) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = dblToCol(1.0);
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // Blue component should be significant
    EXPECT_GT(colToDbl(rgb.b), 0.5);
}

// Test matrix has exactly 9 elements
TEST_F(GfxCalRGBColorSpaceTest_431, MatrixHasNineElements_431) {
    const std::array<double, 9> &mat = colorSpace->getMatrix();
    EXPECT_EQ(mat.size(), 9u);
}

// Test getRGB with mid-gray
TEST_F(GfxCalRGBColorSpaceTest_431, GetRGBWithMidGray_431) {
    GfxColor color;
    color.c[0] = dblToCol(0.5);
    color.c[1] = dblToCol(0.5);
    color.c[2] = dblToCol(0.5);
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // All components should be similar for gray
    double r = colToDbl(rgb.r);
    double g = colToDbl(rgb.g);
    double b = colToDbl(rgb.b);
    EXPECT_NEAR(r, g, 0.15);
    EXPECT_NEAR(g, b, 0.15);
    EXPECT_GT(r, 0.0);
    EXPECT_LT(r, 1.0);
}

// Test getGray with mid value
TEST_F(GfxCalRGBColorSpaceTest_431, GetGrayWithMidValue_431) {
    GfxColor color;
    color.c[0] = dblToCol(0.5);
    color.c[1] = dblToCol(0.5);
    color.c[2] = dblToCol(0.5);
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    double grayVal = colToDbl(gray);
    EXPECT_GT(grayVal, 0.0);
    EXPECT_LT(grayVal, 1.0);
}
