#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalRGBColorSpaceTest_433 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxCalRGBColorSpace>();
    }

    std::unique_ptr<GfxCalRGBColorSpace> colorSpace;
};

// Test default construction and getWhiteY
TEST_F(GfxCalRGBColorSpaceTest_433, DefaultConstructionWhiteY_433) {
    double whiteY = colorSpace->getWhiteY();
    // Default white point Y should be 1.0 (D65 or standard)
    EXPECT_DOUBLE_EQ(whiteY, 1.0);
}

// Test default construction and getWhiteX
TEST_F(GfxCalRGBColorSpaceTest_433, DefaultConstructionWhiteX_433) {
    double whiteX = colorSpace->getWhiteX();
    EXPECT_GE(whiteX, 0.0);
}

// Test default construction and getWhiteZ
TEST_F(GfxCalRGBColorSpaceTest_433, DefaultConstructionWhiteZ_433) {
    double whiteZ = colorSpace->getWhiteZ();
    EXPECT_GE(whiteZ, 0.0);
}

// Test default construction and getBlackX
TEST_F(GfxCalRGBColorSpaceTest_433, DefaultConstructionBlackX_433) {
    double blackX = colorSpace->getBlackX();
    EXPECT_DOUBLE_EQ(blackX, 0.0);
}

// Test default construction and getBlackY
TEST_F(GfxCalRGBColorSpaceTest_433, DefaultConstructionBlackY_433) {
    double blackY = colorSpace->getBlackY();
    EXPECT_DOUBLE_EQ(blackY, 0.0);
}

// Test default construction and getBlackZ
TEST_F(GfxCalRGBColorSpaceTest_433, DefaultConstructionBlackZ_433) {
    double blackZ = colorSpace->getBlackZ();
    EXPECT_DOUBLE_EQ(blackZ, 0.0);
}

// Test default gamma values
TEST_F(GfxCalRGBColorSpaceTest_433, DefaultGammaR_433) {
    double gammaR = colorSpace->getGammaR();
    EXPECT_DOUBLE_EQ(gammaR, 1.0);
}

TEST_F(GfxCalRGBColorSpaceTest_433, DefaultGammaG_433) {
    double gammaG = colorSpace->getGammaG();
    EXPECT_DOUBLE_EQ(gammaG, 1.0);
}

TEST_F(GfxCalRGBColorSpaceTest_433, DefaultGammaB_433) {
    double gammaB = colorSpace->getGammaB();
    EXPECT_DOUBLE_EQ(gammaB, 1.0);
}

// Test getMode returns CalRGB
TEST_F(GfxCalRGBColorSpaceTest_433, GetModeReturnsCalRGB_433) {
    GfxColorSpaceMode mode = colorSpace->getMode();
    EXPECT_EQ(mode, csCalRGB);
}

// Test getNComps returns 3 for RGB
TEST_F(GfxCalRGBColorSpaceTest_433, GetNCompsReturns3_433) {
    int nComps = colorSpace->getNComps();
    EXPECT_EQ(nComps, 3);
}

// Test getMatrix returns a 9-element array
TEST_F(GfxCalRGBColorSpaceTest_433, GetMatrixSize_433) {
    const std::array<double, 9>& matrix = colorSpace->getMatrix();
    EXPECT_EQ(matrix.size(), 9u);
}

// Test default matrix values (identity-like for CalRGB)
TEST_F(GfxCalRGBColorSpaceTest_433, DefaultMatrixValues_433) {
    const std::array<double, 9>& matrix = colorSpace->getMatrix();
    // Default matrix should be identity-like: 
    // [1, 0, 0, 0, 1, 0, 0, 0, 1]
    EXPECT_DOUBLE_EQ(matrix[0], 1.0);
    EXPECT_DOUBLE_EQ(matrix[1], 0.0);
    EXPECT_DOUBLE_EQ(matrix[2], 0.0);
    EXPECT_DOUBLE_EQ(matrix[3], 0.0);
    EXPECT_DOUBLE_EQ(matrix[4], 1.0);
    EXPECT_DOUBLE_EQ(matrix[5], 0.0);
    EXPECT_DOUBLE_EQ(matrix[6], 0.0);
    EXPECT_DOUBLE_EQ(matrix[7], 0.0);
    EXPECT_DOUBLE_EQ(matrix[8], 1.0);
}

// Test copy returns a valid copy
TEST_F(GfxCalRGBColorSpaceTest_433, CopyReturnsValidObject_433) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csCalRGB);
    EXPECT_EQ(copied->getNComps(), 3);
}

// Test that copy preserves white point
TEST_F(GfxCalRGBColorSpaceTest_433, CopyPreservesWhitePoint_433) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    
    // Cast to GfxCalRGBColorSpace to check specific properties
    auto* copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);
    
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteX(), colorSpace->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteY(), colorSpace->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteZ(), colorSpace->getWhiteZ());
}

// Test that copy preserves black point
TEST_F(GfxCalRGBColorSpaceTest_433, CopyPreservesBlackPoint_433) {
    auto copied = colorSpace->copy();
    auto* copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);
    
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackX(), colorSpace->getBlackX());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackY(), colorSpace->getBlackY());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackZ(), colorSpace->getBlackZ());
}

// Test that copy preserves gamma
TEST_F(GfxCalRGBColorSpaceTest_433, CopyPreservesGamma_433) {
    auto copied = colorSpace->copy();
    auto* copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);
    
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaR(), colorSpace->getGammaR());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaG(), colorSpace->getGammaG());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaB(), colorSpace->getGammaB());
}

// Test that copy preserves matrix
TEST_F(GfxCalRGBColorSpaceTest_433, CopyPreservesMatrix_433) {
    auto copied = colorSpace->copy();
    auto* copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace*>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);
    
    const auto& origMatrix = colorSpace->getMatrix();
    const auto& copiedMatrix = copiedCalRGB->getMatrix();
    for (size_t i = 0; i < 9; ++i) {
        EXPECT_DOUBLE_EQ(origMatrix[i], copiedMatrix[i]);
    }
}

// Test getDefaultColor
TEST_F(GfxCalRGBColorSpaceTest_433, GetDefaultColor_433) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    // Default color for CalRGB should be (0, 0, 0)
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
}

// Test getGray with default (black) color
TEST_F(GfxCalRGBColorSpaceTest_433, GetGrayBlackColor_433) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getGray with white color
TEST_F(GfxCalRGBColorSpaceTest_433, GetGrayWhiteColor_433) {
    GfxColor color;
    color.c[0] = GfxColorComp1;
    color.c[1] = GfxColorComp1;
    color.c[2] = GfxColorComp1;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // White should map to maximum gray
    EXPECT_GT(gray, 0);
}

// Test getRGB with default (black) color
TEST_F(GfxCalRGBColorSpaceTest_433, GetRGBBlackColor_433) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB with white color
TEST_F(GfxCalRGBColorSpaceTest_433, GetRGBWhiteColor_433) {
    GfxColor color;
    color.c[0] = GfxColorComp1;
    color.c[1] = GfxColorComp1;
    color.c[2] = GfxColorComp1;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // White should produce high RGB values
    EXPECT_GT(rgb.r, 0);
    EXPECT_GT(rgb.g, 0);
    EXPECT_GT(rgb.b, 0);
}

// Test getCMYK with default (black) color
TEST_F(GfxCalRGBColorSpaceTest_433, GetCMYKBlackColor_433) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Black in CMYK should have K=max
    EXPECT_GT(cmyk.k, 0);
}

// Test getDeviceN with default (black) color
TEST_F(GfxCalRGBColorSpaceTest_433, GetDeviceNBlackColor_433) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    // Should produce some output without crashing
}

// Test WhiteY is positive (physical constraint)
TEST_F(GfxCalRGBColorSpaceTest_433, WhiteYIsPositive_433) {
    EXPECT_GT(colorSpace->getWhiteY(), 0.0);
}

// Test that copied object is independent
TEST_F(GfxCalRGBColorSpaceTest_433, CopyIsIndependent_433) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    // The copy should be a different object
    EXPECT_NE(copied.get(), static_cast<GfxColorSpace*>(colorSpace.get()));
}
