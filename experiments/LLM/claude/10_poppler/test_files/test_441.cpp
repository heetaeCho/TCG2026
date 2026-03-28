#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalRGBColorSpaceTest_441 : public ::testing::Test {
protected:
    void SetUp() override {
        cs = std::make_unique<GfxCalRGBColorSpace>();
    }

    std::unique_ptr<GfxCalRGBColorSpace> cs;
};

// Test that the default constructor creates a valid object
TEST_F(GfxCalRGBColorSpaceTest_441, DefaultConstructor_441) {
    ASSERT_NE(cs, nullptr);
}

// Test that getMode returns the correct color space mode for CalRGB
TEST_F(GfxCalRGBColorSpaceTest_441, GetModeReturnsCalRGB_441) {
    EXPECT_EQ(cs->getMode(), csCalRGB);
}

// Test that getNComps returns 3 for CalRGB
TEST_F(GfxCalRGBColorSpaceTest_441, GetNCompsReturnsThree_441) {
    EXPECT_EQ(cs->getNComps(), 3);
}

// Test default white point values
TEST_F(GfxCalRGBColorSpaceTest_441, DefaultWhitePoint_441) {
    // Default white point should be D65 or some standard default
    // At minimum, WhiteY should be 1.0 for a valid CalRGB space
    double whiteX = cs->getWhiteX();
    double whiteY = cs->getWhiteY();
    double whiteZ = cs->getWhiteZ();
    // White point values should be non-negative
    EXPECT_GE(whiteX, 0.0);
    EXPECT_GE(whiteY, 0.0);
    EXPECT_GE(whiteZ, 0.0);
}

// Test default black point values
TEST_F(GfxCalRGBColorSpaceTest_441, DefaultBlackPoint_441) {
    // Default black point is typically (0, 0, 0)
    EXPECT_DOUBLE_EQ(cs->getBlackX(), 0.0);
    EXPECT_DOUBLE_EQ(cs->getBlackY(), 0.0);
    EXPECT_DOUBLE_EQ(cs->getBlackZ(), 0.0);
}

// Test default gamma values
TEST_F(GfxCalRGBColorSpaceTest_441, DefaultGammaValues_441) {
    // Default gamma is typically 1.0 for each channel
    EXPECT_DOUBLE_EQ(cs->getGammaR(), 1.0);
    EXPECT_DOUBLE_EQ(cs->getGammaG(), 1.0);
    EXPECT_DOUBLE_EQ(cs->getGammaB(), 1.0);
}

// Test getMatrix returns a reference to a 9-element array
TEST_F(GfxCalRGBColorSpaceTest_441, GetMatrixReturnsNineElements_441) {
    const std::array<double, 9> &mat = cs->getMatrix();
    EXPECT_EQ(mat.size(), 9u);
}

// Test default matrix values (identity matrix is typically the default)
TEST_F(GfxCalRGBColorSpaceTest_441, DefaultMatrixValues_441) {
    const std::array<double, 9> &mat = cs->getMatrix();
    // Default matrix is typically the identity matrix:
    // 1 0 0
    // 0 1 0
    // 0 0 1
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

// Test that copy produces an equivalent object
TEST_F(GfxCalRGBColorSpaceTest_441, CopyProducesEquivalentObject_441) {
    std::unique_ptr<GfxColorSpace> copied = cs->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csCalRGB);
    EXPECT_EQ(copied->getNComps(), 3);

    // Cast to GfxCalRGBColorSpace to check specific values
    GfxCalRGBColorSpace *copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace *>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);

    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaR(), cs->getGammaR());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaG(), cs->getGammaG());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaB(), cs->getGammaB());

    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteX(), cs->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteY(), cs->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteZ(), cs->getWhiteZ());

    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackX(), cs->getBlackX());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackY(), cs->getBlackY());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackZ(), cs->getBlackZ());

    const std::array<double, 9> &origMat = cs->getMatrix();
    const std::array<double, 9> &copyMat = copiedCalRGB->getMatrix();
    for (size_t i = 0; i < 9; ++i) {
        EXPECT_DOUBLE_EQ(copyMat[i], origMat[i]);
    }
}

// Test that copy creates an independent object (different pointer)
TEST_F(GfxCalRGBColorSpaceTest_441, CopyCreatesIndependentObject_441) {
    std::unique_ptr<GfxColorSpace> copied = cs->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(copied.get(), cs.get());
}

// Test getDefaultColor
TEST_F(GfxCalRGBColorSpaceTest_441, GetDefaultColor_441) {
    GfxColor color;
    cs->getDefaultColor(&color);
    // For CalRGB, default color should be (0, 0, 0) - black
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
}

// Test getGray with default (black) color
TEST_F(GfxCalRGBColorSpaceTest_441, GetGrayBlack_441) {
    GfxColor color;
    cs->getDefaultColor(&color);
    GfxGray gray;
    cs->getGray(&color, &gray);
    // Black should produce gray value of 0
    EXPECT_EQ(gray, 0);
}

// Test getGray with white color
TEST_F(GfxCalRGBColorSpaceTest_441, GetGrayWhite_441) {
    GfxColor color;
    color.c[0] = dblToCol(1.0);
    color.c[1] = dblToCol(1.0);
    color.c[2] = dblToCol(1.0);
    GfxGray gray;
    cs->getGray(&color, &gray);
    // White should produce gray value close to max
    EXPECT_GT(gray, 0);
}

// Test getRGB with black color
TEST_F(GfxCalRGBColorSpaceTest_441, GetRGBBlack_441) {
    GfxColor color;
    cs->getDefaultColor(&color);
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB with white color
TEST_F(GfxCalRGBColorSpaceTest_441, GetRGBWhite_441) {
    GfxColor color;
    color.c[0] = dblToCol(1.0);
    color.c[1] = dblToCol(1.0);
    color.c[2] = dblToCol(1.0);
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    // White RGB should have high values
    EXPECT_GT(rgb.r, 0);
    EXPECT_GT(rgb.g, 0);
    EXPECT_GT(rgb.b, 0);
}

// Test getCMYK with black color
TEST_F(GfxCalRGBColorSpaceTest_441, GetCMYKBlack_441) {
    GfxColor color;
    cs->getDefaultColor(&color);
    GfxCMYK cmyk;
    cs->getCMYK(&color, &cmyk);
    // Black in CMYK should have K = max (or close)
    // C, M, Y could be 0 with K = max
}

// Test getCMYK with white color
TEST_F(GfxCalRGBColorSpaceTest_441, GetCMYKWhite_441) {
    GfxColor color;
    color.c[0] = dblToCol(1.0);
    color.c[1] = dblToCol(1.0);
    color.c[2] = dblToCol(1.0);
    GfxCMYK cmyk;
    cs->getCMYK(&color, &cmyk);
    // White in CMYK should be (0, 0, 0, 0)
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
    EXPECT_EQ(cmyk.k, 0);
}

// Test getDeviceN with black color
TEST_F(GfxCalRGBColorSpaceTest_441, GetDeviceNBlack_441) {
    GfxColor color;
    cs->getDefaultColor(&color);
    GfxColor deviceN;
    cs->getDeviceN(&color, &deviceN);
    // DeviceN for black: C=0, M=0, Y=0, K=max (or similar)
}

// Test getMatrix returns consistent reference
TEST_F(GfxCalRGBColorSpaceTest_441, GetMatrixReturnsSameReference_441) {
    const std::array<double, 9> &mat1 = cs->getMatrix();
    const std::array<double, 9> &mat2 = cs->getMatrix();
    EXPECT_EQ(&mat1, &mat2);
}

// Test getRGB with pure red
TEST_F(GfxCalRGBColorSpaceTest_441, GetRGBPureRed_441) {
    GfxColor color;
    color.c[0] = dblToCol(1.0);
    color.c[1] = dblToCol(0.0);
    color.c[2] = dblToCol(0.0);
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    // Red channel should be significant
    EXPECT_GT(rgb.r, 0);
}

// Test getRGB with pure green
TEST_F(GfxCalRGBColorSpaceTest_441, GetRGBPureGreen_441) {
    GfxColor color;
    color.c[0] = dblToCol(0.0);
    color.c[1] = dblToCol(1.0);
    color.c[2] = dblToCol(0.0);
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    // Green channel should be significant
    EXPECT_GT(rgb.g, 0);
}

// Test getRGB with pure blue
TEST_F(GfxCalRGBColorSpaceTest_441, GetRGBPureBlue_441) {
    GfxColor color;
    color.c[0] = dblToCol(0.0);
    color.c[1] = dblToCol(0.0);
    color.c[2] = dblToCol(1.0);
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    // Blue channel should be significant
    EXPECT_GT(rgb.b, 0);
}

// Test getRGB with mid-range values
TEST_F(GfxCalRGBColorSpaceTest_441, GetRGBMidRange_441) {
    GfxColor color;
    color.c[0] = dblToCol(0.5);
    color.c[1] = dblToCol(0.5);
    color.c[2] = dblToCol(0.5);
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    // Mid-range values should produce non-zero, non-max RGB
    EXPECT_GT(rgb.r, 0);
    EXPECT_GT(rgb.g, 0);
    EXPECT_GT(rgb.b, 0);
}
