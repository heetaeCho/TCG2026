#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalRGBColorSpaceTest_432 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxCalRGBColorSpace>();
    }

    std::unique_ptr<GfxCalRGBColorSpace> colorSpace;
};

// Test default construction and getter for WhiteX
TEST_F(GfxCalRGBColorSpaceTest_432, DefaultWhiteX_432) {
    double whiteX = colorSpace->getWhiteX();
    // Default white point X should be 1.0 (D65 or default)
    EXPECT_GE(whiteX, 0.0);
}

// Test default construction and getter for WhiteY
TEST_F(GfxCalRGBColorSpaceTest_432, DefaultWhiteY_432) {
    double whiteY = colorSpace->getWhiteY();
    EXPECT_GE(whiteY, 0.0);
}

// Test default construction and getter for WhiteZ
TEST_F(GfxCalRGBColorSpaceTest_432, DefaultWhiteZ_432) {
    double whiteZ = colorSpace->getWhiteZ();
    EXPECT_GE(whiteZ, 0.0);
}

// Test default construction and getter for BlackX
TEST_F(GfxCalRGBColorSpaceTest_432, DefaultBlackX_432) {
    double blackX = colorSpace->getBlackX();
    // Default black point should be 0.0
    EXPECT_DOUBLE_EQ(blackX, 0.0);
}

// Test default construction and getter for BlackY
TEST_F(GfxCalRGBColorSpaceTest_432, DefaultBlackY_432) {
    double blackY = colorSpace->getBlackY();
    EXPECT_DOUBLE_EQ(blackY, 0.0);
}

// Test default construction and getter for BlackZ
TEST_F(GfxCalRGBColorSpaceTest_432, DefaultBlackZ_432) {
    double blackZ = colorSpace->getBlackZ();
    EXPECT_DOUBLE_EQ(blackZ, 0.0);
}

// Test default construction and getter for GammaR
TEST_F(GfxCalRGBColorSpaceTest_432, DefaultGammaR_432) {
    double gammaR = colorSpace->getGammaR();
    // Default gamma should be 1.0
    EXPECT_DOUBLE_EQ(gammaR, 1.0);
}

// Test default construction and getter for GammaG
TEST_F(GfxCalRGBColorSpaceTest_432, DefaultGammaG_432) {
    double gammaG = colorSpace->getGammaG();
    EXPECT_DOUBLE_EQ(gammaG, 1.0);
}

// Test default construction and getter for GammaB
TEST_F(GfxCalRGBColorSpaceTest_432, DefaultGammaB_432) {
    double gammaB = colorSpace->getGammaB();
    EXPECT_DOUBLE_EQ(gammaB, 1.0);
}

// Test that getMatrix returns an array of 9 elements
TEST_F(GfxCalRGBColorSpaceTest_432, MatrixSize_432) {
    const std::array<double, 9>& mat = colorSpace->getMatrix();
    EXPECT_EQ(mat.size(), 9u);
}

// Test default matrix values - identity-like matrix
TEST_F(GfxCalRGBColorSpaceTest_432, DefaultMatrixValues_432) {
    const std::array<double, 9>& mat = colorSpace->getMatrix();
    // Default matrix should be identity: 1 0 0 0 1 0 0 0 1
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

// Test that getMode returns the correct color space mode
TEST_F(GfxCalRGBColorSpaceTest_432, GetMode_432) {
    GfxColorSpaceMode mode = colorSpace->getMode();
    EXPECT_EQ(mode, csCalRGB);
}

// Test that getNComps returns 3 for CalRGB
TEST_F(GfxCalRGBColorSpaceTest_432, GetNComps_432) {
    int nComps = colorSpace->getNComps();
    EXPECT_EQ(nComps, 3);
}

// Test copy() produces a valid copy
TEST_F(GfxCalRGBColorSpaceTest_432, CopyProducesValidObject_432) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csCalRGB);
    EXPECT_EQ(copied->getNComps(), 3);
}

// Test that copy preserves white point values
TEST_F(GfxCalRGBColorSpaceTest_432, CopyPreservesWhitePoint_432) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);

    GfxCalRGBColorSpace* copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);

    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteX(), colorSpace->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteY(), colorSpace->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteZ(), colorSpace->getWhiteZ());
}

// Test that copy preserves black point values
TEST_F(GfxCalRGBColorSpaceTest_432, CopyPreservesBlackPoint_432) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);

    GfxCalRGBColorSpace* copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);

    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackX(), colorSpace->getBlackX());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackY(), colorSpace->getBlackY());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackZ(), colorSpace->getBlackZ());
}

// Test that copy preserves gamma values
TEST_F(GfxCalRGBColorSpaceTest_432, CopyPreservesGamma_432) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);

    GfxCalRGBColorSpace* copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);

    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaR(), colorSpace->getGammaR());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaG(), colorSpace->getGammaG());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaB(), colorSpace->getGammaB());
}

// Test that copy preserves matrix values
TEST_F(GfxCalRGBColorSpaceTest_432, CopyPreservesMatrix_432) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);

    GfxCalRGBColorSpace* copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);

    const std::array<double, 9>& origMat = colorSpace->getMatrix();
    const std::array<double, 9>& copyMat = copiedCalRGB->getMatrix();

    for (int i = 0; i < 9; i++) {
        EXPECT_DOUBLE_EQ(origMat[i], copyMat[i]);
    }
}

// Test getDefaultColor sets default color properly
TEST_F(GfxCalRGBColorSpaceTest_432, GetDefaultColor_432) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    // Default color for CalRGB should have components set to 0
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
}

// Test getGray with a black color
TEST_F(GfxCalRGBColorSpaceTest_432, GetGrayBlack_432) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;

    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getRGB with a black color
TEST_F(GfxCalRGBColorSpaceTest_432, GetRGBBlack_432) {
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

// Test getRGB with a white color (max values)
TEST_F(GfxCalRGBColorSpaceTest_432, GetRGBWhite_432) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;

    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // White should map to approximately max values
    EXPECT_GT(rgb.r, 0);
    EXPECT_GT(rgb.g, 0);
    EXPECT_GT(rgb.b, 0);
}

// Test getCMYK with a black color
TEST_F(GfxCalRGBColorSpaceTest_432, GetCMYKBlack_432) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;

    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Black in CMYK should have K = max
    EXPECT_EQ(cmyk.k, gfxColorComp1);
}

// Test getDeviceN with a black color
TEST_F(GfxCalRGBColorSpaceTest_432, GetDeviceNBlack_432) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;

    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    // DeviceN for black should have spot colors at 0 and K at max
    // At minimum, verify it doesn't crash
    SUCCEED();
}

// Test getGray with a white color
TEST_F(GfxCalRGBColorSpaceTest_432, GetGrayWhite_432) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;

    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // White should produce a high gray value
    EXPECT_GT(gray, 0);
}

// Test that the copy is independent (modifying copy doesn't affect original)
TEST_F(GfxCalRGBColorSpaceTest_432, CopyIsIndependent_432) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);

    // Verify they are separate objects
    EXPECT_NE(copied.get(), colorSpace.get());
}

// Test WhiteY default value (should typically be 1.0 for proper white point)
TEST_F(GfxCalRGBColorSpaceTest_432, DefaultWhiteYIsOne_432) {
    // For CalRGB, the default white Y should be 1.0
    EXPECT_DOUBLE_EQ(colorSpace->getWhiteY(), 1.0);
}
