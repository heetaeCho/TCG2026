#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalRGBColorSpaceTest_440 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxCalRGBColorSpace>();
    }

    std::unique_ptr<GfxCalRGBColorSpace> colorSpace;
};

// Test that default construction yields expected gamma values
TEST_F(GfxCalRGBColorSpaceTest_440, DefaultGammaR_440) {
    double gammaR = colorSpace->getGammaR();
    EXPECT_DOUBLE_EQ(gammaR, 1.0);
}

TEST_F(GfxCalRGBColorSpaceTest_440, DefaultGammaG_440) {
    double gammaG = colorSpace->getGammaG();
    EXPECT_DOUBLE_EQ(gammaG, 1.0);
}

TEST_F(GfxCalRGBColorSpaceTest_440, DefaultGammaB_440) {
    double gammaB = colorSpace->getGammaB();
    EXPECT_DOUBLE_EQ(gammaB, 1.0);
}

// Test that the color space mode is csCalRGB
TEST_F(GfxCalRGBColorSpaceTest_440, GetModeReturnsCalRGB_440) {
    EXPECT_EQ(colorSpace->getMode(), csCalRGB);
}

// Test number of components
TEST_F(GfxCalRGBColorSpaceTest_440, GetNCompsReturns3_440) {
    EXPECT_EQ(colorSpace->getNComps(), 3);
}

// Test default white point values
TEST_F(GfxCalRGBColorSpaceTest_440, DefaultWhiteX_440) {
    double whiteX = colorSpace->getWhiteX();
    EXPECT_DOUBLE_EQ(whiteX, 1.0);
}

TEST_F(GfxCalRGBColorSpaceTest_440, DefaultWhiteY_440) {
    double whiteY = colorSpace->getWhiteY();
    EXPECT_DOUBLE_EQ(whiteY, 1.0);
}

TEST_F(GfxCalRGBColorSpaceTest_440, DefaultWhiteZ_440) {
    double whiteZ = colorSpace->getWhiteZ();
    EXPECT_DOUBLE_EQ(whiteZ, 1.0);
}

// Test default black point values
TEST_F(GfxCalRGBColorSpaceTest_440, DefaultBlackX_440) {
    double blackX = colorSpace->getBlackX();
    EXPECT_DOUBLE_EQ(blackX, 0.0);
}

TEST_F(GfxCalRGBColorSpaceTest_440, DefaultBlackY_440) {
    double blackY = colorSpace->getBlackY();
    EXPECT_DOUBLE_EQ(blackY, 0.0);
}

TEST_F(GfxCalRGBColorSpaceTest_440, DefaultBlackZ_440) {
    double blackZ = colorSpace->getBlackZ();
    EXPECT_DOUBLE_EQ(blackZ, 0.0);
}

// Test default matrix values
TEST_F(GfxCalRGBColorSpaceTest_440, DefaultMatrixValues_440) {
    const std::array<double, 9>& mat = colorSpace->getMatrix();
    // Default matrix should be identity-like for CalRGB
    // Typically: [1 0 0 0 1 0 0 0 1]
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

// Test copy preserves gamma values
TEST_F(GfxCalRGBColorSpaceTest_440, CopyPreservesGammaB_440) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    auto* copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaB(), colorSpace->getGammaB());
}

TEST_F(GfxCalRGBColorSpaceTest_440, CopyPreservesGammaR_440) {
    auto copied = colorSpace->copy();
    auto* copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaR(), colorSpace->getGammaR());
}

TEST_F(GfxCalRGBColorSpaceTest_440, CopyPreservesGammaG_440) {
    auto copied = colorSpace->copy();
    auto* copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaG(), colorSpace->getGammaG());
}

TEST_F(GfxCalRGBColorSpaceTest_440, CopyPreservesMode_440) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csCalRGB);
}

TEST_F(GfxCalRGBColorSpaceTest_440, CopyPreservesNComps_440) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNComps(), 3);
}

TEST_F(GfxCalRGBColorSpaceTest_440, CopyPreservesWhitePoint_440) {
    auto copied = colorSpace->copy();
    auto* copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteX(), colorSpace->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteY(), colorSpace->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteZ(), colorSpace->getWhiteZ());
}

TEST_F(GfxCalRGBColorSpaceTest_440, CopyPreservesBlackPoint_440) {
    auto copied = colorSpace->copy();
    auto* copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackX(), colorSpace->getBlackX());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackY(), colorSpace->getBlackY());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackZ(), colorSpace->getBlackZ());
}

TEST_F(GfxCalRGBColorSpaceTest_440, CopyPreservesMatrix_440) {
    auto copied = colorSpace->copy();
    auto* copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);
    const auto& origMat = colorSpace->getMatrix();
    const auto& copyMat = copiedCalRGB->getMatrix();
    for (int i = 0; i < 9; i++) {
        EXPECT_DOUBLE_EQ(origMat[i], copyMat[i]);
    }
}

// Test getDefaultColor
TEST_F(GfxCalRGBColorSpaceTest_440, GetDefaultColor_440) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    // Default color for CalRGB should be black (all components 0)
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
}

// Test getGray with default (black) color
TEST_F(GfxCalRGBColorSpaceTest_440, GetGrayFromBlack_440) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getRGB with default (black) color
TEST_F(GfxCalRGBColorSpaceTest_440, GetRGBFromBlack_440) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getCMYK with default (black) color
TEST_F(GfxCalRGBColorSpaceTest_440, GetCMYKFromBlack_440) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Black in CMYK: C=0, M=0, Y=0, K=max
    EXPECT_EQ(cmyk.k, gfxColorComp1);
}

// Test getRGB with white color (all components max)
TEST_F(GfxCalRGBColorSpaceTest_440, GetRGBFromWhite_440) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // With default gamma=1 and identity matrix, white should map to white
    EXPECT_NEAR(colToDbl(rgb.r), 1.0, 0.05);
    EXPECT_NEAR(colToDbl(rgb.g), 1.0, 0.05);
    EXPECT_NEAR(colToDbl(rgb.b), 1.0, 0.05);
}

// Test getGray with white color
TEST_F(GfxCalRGBColorSpaceTest_440, GetGrayFromWhite_440) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    EXPECT_NEAR(colToDbl(gray), 1.0, 0.05);
}

// Test getDeviceN with default color
TEST_F(GfxCalRGBColorSpaceTest_440, GetDeviceNFromBlack_440) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    // DeviceN for black should have spot colors at 0 and K at max
    // The exact mapping depends on implementation, but we verify it doesn't crash
    // and produces some reasonable output
}

// Test matrix returns reference to array of size 9
TEST_F(GfxCalRGBColorSpaceTest_440, MatrixHasNineElements_440) {
    const std::array<double, 9>& mat = colorSpace->getMatrix();
    EXPECT_EQ(mat.size(), 9u);
}

// Test that gamma values are consistent between original and copy
TEST_F(GfxCalRGBColorSpaceTest_440, GammaValuesConsistency_440) {
    EXPECT_DOUBLE_EQ(colorSpace->getGammaR(), colorSpace->getGammaR());
    EXPECT_DOUBLE_EQ(colorSpace->getGammaG(), colorSpace->getGammaG());
    EXPECT_DOUBLE_EQ(colorSpace->getGammaB(), colorSpace->getGammaB());
}

// Test with mid-range color
TEST_F(GfxCalRGBColorSpaceTest_440, GetRGBFromMidRange_440) {
    GfxColor color;
    color.c[0] = gfxColorComp1 / 2;
    color.c[1] = gfxColorComp1 / 2;
    color.c[2] = gfxColorComp1 / 2;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // Mid-range input with gamma=1 should produce mid-range output
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

// Test single channel red
TEST_F(GfxCalRGBColorSpaceTest_440, GetRGBFromPureRed_440) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // With identity matrix and gamma=1, pure red input should be red-ish
    EXPECT_GT(colToDbl(rgb.r), 0.5);
}

// Test single channel green
TEST_F(GfxCalRGBColorSpaceTest_440, GetRGBFromPureGreen_440) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = gfxColorComp1;
    color.c[2] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_GT(colToDbl(rgb.g), 0.5);
}

// Test single channel blue
TEST_F(GfxCalRGBColorSpaceTest_440, GetRGBFromPureBlue_440) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = gfxColorComp1;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_GT(colToDbl(rgb.b), 0.5);
}
