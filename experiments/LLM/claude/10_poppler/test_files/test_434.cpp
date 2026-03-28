#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalRGBColorSpaceTest_434 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxCalRGBColorSpace>();
    }

    std::unique_ptr<GfxCalRGBColorSpace> colorSpace;
};

// Test default construction and getWhiteZ
TEST_F(GfxCalRGBColorSpaceTest_434, DefaultConstructionWhiteZ_434) {
    double whiteZ = colorSpace->getWhiteZ();
    // Default WhiteZ should be 1.0 for CalRGB (D65 illuminant default or spec default)
    EXPECT_DOUBLE_EQ(whiteZ, 1.0);
}

// Test default construction and getWhiteX
TEST_F(GfxCalRGBColorSpaceTest_434, DefaultConstructionWhiteX_434) {
    double whiteX = colorSpace->getWhiteX();
    EXPECT_DOUBLE_EQ(whiteX, 1.0);
}

// Test default construction and getWhiteY
TEST_F(GfxCalRGBColorSpaceTest_434, DefaultConstructionWhiteY_434) {
    double whiteY = colorSpace->getWhiteY();
    EXPECT_DOUBLE_EQ(whiteY, 1.0);
}

// Test default construction and getBlackX
TEST_F(GfxCalRGBColorSpaceTest_434, DefaultConstructionBlackX_434) {
    double blackX = colorSpace->getBlackX();
    EXPECT_DOUBLE_EQ(blackX, 0.0);
}

// Test default construction and getBlackY
TEST_F(GfxCalRGBColorSpaceTest_434, DefaultConstructionBlackY_434) {
    double blackY = colorSpace->getBlackY();
    EXPECT_DOUBLE_EQ(blackY, 0.0);
}

// Test default construction and getBlackZ
TEST_F(GfxCalRGBColorSpaceTest_434, DefaultConstructionBlackZ_434) {
    double blackZ = colorSpace->getBlackZ();
    EXPECT_DOUBLE_EQ(blackZ, 0.0);
}

// Test default construction and getGammaR
TEST_F(GfxCalRGBColorSpaceTest_434, DefaultConstructionGammaR_434) {
    double gammaR = colorSpace->getGammaR();
    EXPECT_DOUBLE_EQ(gammaR, 1.0);
}

// Test default construction and getGammaG
TEST_F(GfxCalRGBColorSpaceTest_434, DefaultConstructionGammaG_434) {
    double gammaG = colorSpace->getGammaG();
    EXPECT_DOUBLE_EQ(gammaG, 1.0);
}

// Test default construction and getGammaB
TEST_F(GfxCalRGBColorSpaceTest_434, DefaultConstructionGammaB_434) {
    double gammaB = colorSpace->getGammaB();
    EXPECT_DOUBLE_EQ(gammaB, 1.0);
}

// Test getMode returns csCalRGB
TEST_F(GfxCalRGBColorSpaceTest_434, GetModeReturnsCalRGB_434) {
    GfxColorSpaceMode mode = colorSpace->getMode();
    EXPECT_EQ(mode, csCalRGB);
}

// Test getNComps returns 3 for CalRGB
TEST_F(GfxCalRGBColorSpaceTest_434, GetNCompsReturnsThree_434) {
    int nComps = colorSpace->getNComps();
    EXPECT_EQ(nComps, 3);
}

// Test getMatrix returns a valid 9-element array
TEST_F(GfxCalRGBColorSpaceTest_434, GetMatrixReturnsNineElements_434) {
    const std::array<double, 9> &mat = colorSpace->getMatrix();
    EXPECT_EQ(mat.size(), 9u);
}

// Test default matrix values (identity-like default)
TEST_F(GfxCalRGBColorSpaceTest_434, DefaultMatrixValues_434) {
    const std::array<double, 9> &mat = colorSpace->getMatrix();
    // Default matrix should be identity: [1 0 0 0 1 0 0 0 1]
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

// Test copy produces a valid copy with same properties
TEST_F(GfxCalRGBColorSpaceTest_434, CopyPreservesProperties_434) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csCalRGB);
    EXPECT_EQ(copied->getNComps(), 3);

    GfxCalRGBColorSpace *copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace *>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteX(), colorSpace->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteY(), colorSpace->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteZ(), colorSpace->getWhiteZ());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackX(), colorSpace->getBlackX());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackY(), colorSpace->getBlackY());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackZ(), colorSpace->getBlackZ());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaR(), colorSpace->getGammaR());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaG(), colorSpace->getGammaG());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaB(), colorSpace->getGammaB());
}

// Test getDefaultColor sets default color values
TEST_F(GfxCalRGBColorSpaceTest_434, GetDefaultColorSetsValues_434) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    // Default color for CalRGB should be [0, 0, 0] (black)
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
}

// Test getGray with default (black) color
TEST_F(GfxCalRGBColorSpaceTest_434, GetGrayFromBlack_434) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // Black should produce gray = 0
    EXPECT_EQ(gray, 0);
}

// Test getRGB with default (black) color
TEST_F(GfxCalRGBColorSpaceTest_434, GetRGBFromBlack_434) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getCMYK with default (black) color
TEST_F(GfxCalRGBColorSpaceTest_434, GetCMYKFromBlack_434) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Black in CMYK should have k=65535 (or close)
    EXPECT_EQ(cmyk.k, 65535);
}

// Test getGray with white color
TEST_F(GfxCalRGBColorSpaceTest_434, GetGrayFromWhite_434) {
    GfxColor color;
    color.c[0] = 65535; // max value
    color.c[1] = 65535;
    color.c[2] = 65535;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // White should produce gray close to max
    EXPECT_GT(gray, 0);
}

// Test getRGB with white color
TEST_F(GfxCalRGBColorSpaceTest_434, GetRGBFromWhite_434) {
    GfxColor color;
    color.c[0] = 65535;
    color.c[1] = 65535;
    color.c[2] = 65535;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // With default gamma=1 and identity matrix, white in CalRGB should map to white in RGB
    EXPECT_GT(rgb.r, 0);
    EXPECT_GT(rgb.g, 0);
    EXPECT_GT(rgb.b, 0);
}

// Test getDeviceN with black color
TEST_F(GfxCalRGBColorSpaceTest_434, GetDeviceNFromBlack_434) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    // DeviceN for black should have meaningful values
    // At minimum, it should not crash
    SUCCEED();
}

// Test that copy is independent of original
TEST_F(GfxCalRGBColorSpaceTest_434, CopyIsIndependent_434) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    // Original and copy should be different pointers
    EXPECT_NE(copied.get(), colorSpace.get());
}

// Test getMatrix reference stability
TEST_F(GfxCalRGBColorSpaceTest_434, GetMatrixReferenceConsistency_434) {
    const std::array<double, 9> &mat1 = colorSpace->getMatrix();
    const std::array<double, 9> &mat2 = colorSpace->getMatrix();
    // Same reference should be returned
    EXPECT_EQ(&mat1, &mat2);
}

// Test WhiteZ consistency through copy
TEST_F(GfxCalRGBColorSpaceTest_434, WhiteZConsistentThroughCopy_434) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    GfxCalRGBColorSpace *copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace *>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteZ(), colorSpace->getWhiteZ());
}
