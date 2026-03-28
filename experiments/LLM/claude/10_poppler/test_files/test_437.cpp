#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalRGBColorSpaceTest_437 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxCalRGBColorSpace>();
    }

    std::unique_ptr<GfxCalRGBColorSpace> colorSpace;
};

// Test default construction and getBlackZ returns expected default value
TEST_F(GfxCalRGBColorSpaceTest_437, DefaultConstructionBlackZ_437) {
    double blackZ = colorSpace->getBlackZ();
    // Default black point Z should be 0
    EXPECT_DOUBLE_EQ(blackZ, 0.0);
}

// Test that getBlackX returns expected default value
TEST_F(GfxCalRGBColorSpaceTest_437, DefaultConstructionBlackX_437) {
    double blackX = colorSpace->getBlackX();
    EXPECT_DOUBLE_EQ(blackX, 0.0);
}

// Test that getBlackY returns expected default value
TEST_F(GfxCalRGBColorSpaceTest_437, DefaultConstructionBlackY_437) {
    double blackY = colorSpace->getBlackY();
    EXPECT_DOUBLE_EQ(blackY, 0.0);
}

// Test default white point values
TEST_F(GfxCalRGBColorSpaceTest_437, DefaultWhiteX_437) {
    double whiteX = colorSpace->getWhiteX();
    // White point X should have a default value (typically 1.0)
    EXPECT_DOUBLE_EQ(whiteX, 1.0);
}

TEST_F(GfxCalRGBColorSpaceTest_437, DefaultWhiteY_437) {
    double whiteY = colorSpace->getWhiteY();
    EXPECT_DOUBLE_EQ(whiteY, 1.0);
}

TEST_F(GfxCalRGBColorSpaceTest_437, DefaultWhiteZ_437) {
    double whiteZ = colorSpace->getWhiteZ();
    EXPECT_DOUBLE_EQ(whiteZ, 1.0);
}

// Test default gamma values
TEST_F(GfxCalRGBColorSpaceTest_437, DefaultGammaR_437) {
    double gammaR = colorSpace->getGammaR();
    EXPECT_DOUBLE_EQ(gammaR, 1.0);
}

TEST_F(GfxCalRGBColorSpaceTest_437, DefaultGammaG_437) {
    double gammaG = colorSpace->getGammaG();
    EXPECT_DOUBLE_EQ(gammaG, 1.0);
}

TEST_F(GfxCalRGBColorSpaceTest_437, DefaultGammaB_437) {
    double gammaB = colorSpace->getGammaB();
    EXPECT_DOUBLE_EQ(gammaB, 1.0);
}

// Test color space mode
TEST_F(GfxCalRGBColorSpaceTest_437, GetMode_437) {
    GfxColorSpaceMode mode = colorSpace->getMode();
    EXPECT_EQ(mode, csCalRGB);
}

// Test number of components
TEST_F(GfxCalRGBColorSpaceTest_437, GetNComps_437) {
    int nComps = colorSpace->getNComps();
    EXPECT_EQ(nComps, 3);
}

// Test getMatrix returns a 9-element array
TEST_F(GfxCalRGBColorSpaceTest_437, GetMatrixSize_437) {
    const std::array<double, 9> &mat = colorSpace->getMatrix();
    EXPECT_EQ(mat.size(), 9u);
}

// Test default matrix values (identity-like for CalRGB)
TEST_F(GfxCalRGBColorSpaceTest_437, DefaultMatrixValues_437) {
    const std::array<double, 9> &mat = colorSpace->getMatrix();
    // Default matrix should be identity matrix for CalRGB
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

// Test copy produces a valid object with same properties
TEST_F(GfxCalRGBColorSpaceTest_437, CopyPreservesProperties_437) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);

    GfxCalRGBColorSpace *copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace *>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);

    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackX(), colorSpace->getBlackX());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackY(), colorSpace->getBlackY());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackZ(), colorSpace->getBlackZ());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteX(), colorSpace->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteY(), colorSpace->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteZ(), colorSpace->getWhiteZ());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaR(), colorSpace->getGammaR());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaG(), colorSpace->getGammaG());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaB(), colorSpace->getGammaB());
    EXPECT_EQ(copiedCalRGB->getMode(), colorSpace->getMode());
    EXPECT_EQ(copiedCalRGB->getNComps(), colorSpace->getNComps());
}

// Test copy preserves matrix
TEST_F(GfxCalRGBColorSpaceTest_437, CopyPreservesMatrix_437) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    GfxCalRGBColorSpace *copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace *>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);

    const auto &origMat = colorSpace->getMatrix();
    const auto &copyMat = copiedCalRGB->getMatrix();
    for (size_t i = 0; i < 9; ++i) {
        EXPECT_DOUBLE_EQ(origMat[i], copyMat[i]) << "Matrix element " << i << " differs";
    }
}

// Test getDefaultColor
TEST_F(GfxCalRGBColorSpaceTest_437, GetDefaultColor_437) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    // Default color for CalRGB should be black (0, 0, 0)
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
}

// Test getGray with default/black color
TEST_F(GfxCalRGBColorSpaceTest_437, GetGrayBlackColor_437) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // Black should map to gray value of 0
    EXPECT_EQ(gray, 0);
}

// Test getRGB with default/black color
TEST_F(GfxCalRGBColorSpaceTest_437, GetRGBBlackColor_437) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getCMYK with default/black color
TEST_F(GfxCalRGBColorSpaceTest_437, GetCMYKBlackColor_437) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Black in CMYK should have K=max (or close to it)
    // c, m, y should be 0, k should be max
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
    EXPECT_NE(cmyk.k, 0);
}

// Test getRGB with white color (all components at max)
TEST_F(GfxCalRGBColorSpaceTest_437, GetRGBWhiteColor_437) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // White color should map to RGB (1, 1, 1) approximately
    EXPECT_NEAR(colToDbl(rgb.r), 1.0, 0.01);
    EXPECT_NEAR(colToDbl(rgb.g), 1.0, 0.01);
    EXPECT_NEAR(colToDbl(rgb.b), 1.0, 0.01);
}

// Test getGray with white color
TEST_F(GfxCalRGBColorSpaceTest_437, GetGrayWhiteColor_437) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    EXPECT_NEAR(colToDbl(gray), 1.0, 0.01);
}

// Test getDeviceN with default color
TEST_F(GfxCalRGBColorSpaceTest_437, GetDeviceNBlackColor_437) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    // DeviceN for black should have specific values
    // At minimum, this should not crash
    SUCCEED();
}

// Test that black point values are consistent and non-negative
TEST_F(GfxCalRGBColorSpaceTest_437, BlackPointNonNegative_437) {
    EXPECT_GE(colorSpace->getBlackX(), 0.0);
    EXPECT_GE(colorSpace->getBlackY(), 0.0);
    EXPECT_GE(colorSpace->getBlackZ(), 0.0);
}

// Test that white point values are positive
TEST_F(GfxCalRGBColorSpaceTest_437, WhitePointPositive_437) {
    EXPECT_GT(colorSpace->getWhiteX(), 0.0);
    EXPECT_GT(colorSpace->getWhiteY(), 0.0);
    EXPECT_GT(colorSpace->getWhiteZ(), 0.0);
}

// Test that gamma values are positive
TEST_F(GfxCalRGBColorSpaceTest_437, GammaPositive_437) {
    EXPECT_GT(colorSpace->getGammaR(), 0.0);
    EXPECT_GT(colorSpace->getGammaG(), 0.0);
    EXPECT_GT(colorSpace->getGammaB(), 0.0);
}
