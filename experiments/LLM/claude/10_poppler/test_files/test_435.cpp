#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalRGBColorSpaceTest_435 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxCalRGBColorSpace>();
    }

    std::unique_ptr<GfxCalRGBColorSpace> colorSpace;
};

// Test default construction and default black point values
TEST_F(GfxCalRGBColorSpaceTest_435, DefaultBlackX_435) {
    EXPECT_DOUBLE_EQ(colorSpace->getBlackX(), 0.0);
}

TEST_F(GfxCalRGBColorSpaceTest_435, DefaultBlackY_435) {
    EXPECT_DOUBLE_EQ(colorSpace->getBlackY(), 0.0);
}

TEST_F(GfxCalRGBColorSpaceTest_435, DefaultBlackZ_435) {
    EXPECT_DOUBLE_EQ(colorSpace->getBlackZ(), 0.0);
}

// Test default white point values
TEST_F(GfxCalRGBColorSpaceTest_435, DefaultWhiteX_435) {
    double whiteX = colorSpace->getWhiteX();
    // White point should have some default value (typically 1.0 for D65 or similar)
    EXPECT_GE(whiteX, 0.0);
}

TEST_F(GfxCalRGBColorSpaceTest_435, DefaultWhiteY_435) {
    double whiteY = colorSpace->getWhiteY();
    EXPECT_GE(whiteY, 0.0);
}

TEST_F(GfxCalRGBColorSpaceTest_435, DefaultWhiteZ_435) {
    double whiteZ = colorSpace->getWhiteZ();
    EXPECT_GE(whiteZ, 0.0);
}

// Test default gamma values
TEST_F(GfxCalRGBColorSpaceTest_435, DefaultGammaR_435) {
    double gammaR = colorSpace->getGammaR();
    EXPECT_DOUBLE_EQ(gammaR, 1.0);
}

TEST_F(GfxCalRGBColorSpaceTest_435, DefaultGammaG_435) {
    double gammaG = colorSpace->getGammaG();
    EXPECT_DOUBLE_EQ(gammaG, 1.0);
}

TEST_F(GfxCalRGBColorSpaceTest_435, DefaultGammaB_435) {
    double gammaB = colorSpace->getGammaB();
    EXPECT_DOUBLE_EQ(gammaB, 1.0);
}

// Test color space mode
TEST_F(GfxCalRGBColorSpaceTest_435, GetMode_435) {
    EXPECT_EQ(colorSpace->getMode(), csCalRGB);
}

// Test number of components
TEST_F(GfxCalRGBColorSpaceTest_435, GetNComps_435) {
    EXPECT_EQ(colorSpace->getNComps(), 3);
}

// Test matrix accessor
TEST_F(GfxCalRGBColorSpaceTest_435, GetMatrixReturnsNineElements_435) {
    const std::array<double, 9>& mat = colorSpace->getMatrix();
    EXPECT_EQ(mat.size(), 9u);
}

// Test default matrix values (identity-like for CalRGB default)
TEST_F(GfxCalRGBColorSpaceTest_435, DefaultMatrixValues_435) {
    const std::array<double, 9>& mat = colorSpace->getMatrix();
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

// Test copy
TEST_F(GfxCalRGBColorSpaceTest_435, CopyPreservesMode_435) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csCalRGB);
}

TEST_F(GfxCalRGBColorSpaceTest_435, CopyPreservesNComps_435) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNComps(), 3);
}

TEST_F(GfxCalRGBColorSpaceTest_435, CopyPreservesBlackPoint_435) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    auto* calRGBCopy = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(calRGBCopy, nullptr);
    EXPECT_DOUBLE_EQ(calRGBCopy->getBlackX(), colorSpace->getBlackX());
    EXPECT_DOUBLE_EQ(calRGBCopy->getBlackY(), colorSpace->getBlackY());
    EXPECT_DOUBLE_EQ(calRGBCopy->getBlackZ(), colorSpace->getBlackZ());
}

TEST_F(GfxCalRGBColorSpaceTest_435, CopyPreservesWhitePoint_435) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    auto* calRGBCopy = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(calRGBCopy, nullptr);
    EXPECT_DOUBLE_EQ(calRGBCopy->getWhiteX(), colorSpace->getWhiteX());
    EXPECT_DOUBLE_EQ(calRGBCopy->getWhiteY(), colorSpace->getWhiteY());
    EXPECT_DOUBLE_EQ(calRGBCopy->getWhiteZ(), colorSpace->getWhiteZ());
}

TEST_F(GfxCalRGBColorSpaceTest_435, CopyPreservesGamma_435) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    auto* calRGBCopy = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(calRGBCopy, nullptr);
    EXPECT_DOUBLE_EQ(calRGBCopy->getGammaR(), colorSpace->getGammaR());
    EXPECT_DOUBLE_EQ(calRGBCopy->getGammaG(), colorSpace->getGammaG());
    EXPECT_DOUBLE_EQ(calRGBCopy->getGammaB(), colorSpace->getGammaB());
}

TEST_F(GfxCalRGBColorSpaceTest_435, CopyPreservesMatrix_435) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    auto* calRGBCopy = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(calRGBCopy, nullptr);
    const auto& origMat = colorSpace->getMatrix();
    const auto& copyMat = calRGBCopy->getMatrix();
    for (size_t i = 0; i < 9; ++i) {
        EXPECT_DOUBLE_EQ(copyMat[i], origMat[i]);
    }
}

// Test getDefaultColor
TEST_F(GfxCalRGBColorSpaceTest_435, GetDefaultColor_435) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    // Default color for CalRGB should be black (all components 0)
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
}

// Test getGray with black color
TEST_F(GfxCalRGBColorSpaceTest_435, GetGrayBlackColor_435) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getGray with white color
TEST_F(GfxCalRGBColorSpaceTest_435, GetGrayWhiteColor_435) {
    GfxColor color;
    color.c[0] = dblToCol(1.0);
    color.c[1] = dblToCol(1.0);
    color.c[2] = dblToCol(1.0);
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    EXPECT_GT(gray, 0);
}

// Test getRGB with black color
TEST_F(GfxCalRGBColorSpaceTest_435, GetRGBBlackColor_435) {
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
TEST_F(GfxCalRGBColorSpaceTest_435, GetRGBWhiteColor_435) {
    GfxColor color;
    color.c[0] = dblToCol(1.0);
    color.c[1] = dblToCol(1.0);
    color.c[2] = dblToCol(1.0);
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // With default identity matrix and gamma=1, white input should yield high RGB values
    EXPECT_GT(rgb.r, 0);
    EXPECT_GT(rgb.g, 0);
    EXPECT_GT(rgb.b, 0);
}

// Test getCMYK with black color
TEST_F(GfxCalRGBColorSpaceTest_435, GetCMYKBlackColor_435) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Black in RGB should map to K=max in CMYK
    EXPECT_GT(cmyk.k, 0);
}

// Test getDeviceN with black color
TEST_F(GfxCalRGBColorSpaceTest_435, GetDeviceNBlackColor_435) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    // Should produce some valid output without crashing
}

// Test getRGB with pure red
TEST_F(GfxCalRGBColorSpaceTest_435, GetRGBPureRed_435) {
    GfxColor color;
    color.c[0] = dblToCol(1.0);
    color.c[1] = 0;
    color.c[2] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_GT(rgb.r, 0);
}

// Test getRGB with pure green
TEST_F(GfxCalRGBColorSpaceTest_435, GetRGBPureGreen_435) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = dblToCol(1.0);
    color.c[2] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_GT(rgb.g, 0);
}

// Test getRGB with pure blue
TEST_F(GfxCalRGBColorSpaceTest_435, GetRGBPureBlue_435) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = dblToCol(1.0);
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_GT(rgb.b, 0);
}

// Test that copy creates a distinct object
TEST_F(GfxCalRGBColorSpaceTest_435, CopyCreatesDifferentPointer_435) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(copied.get(), colorSpace.get());
}

// Test getRGB with mid-range color
TEST_F(GfxCalRGBColorSpaceTest_435, GetRGBMidRange_435) {
    GfxColor color;
    color.c[0] = dblToCol(0.5);
    color.c[1] = dblToCol(0.5);
    color.c[2] = dblToCol(0.5);
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_GT(rgb.r, 0);
    EXPECT_GT(rgb.g, 0);
    EXPECT_GT(rgb.b, 0);
}
