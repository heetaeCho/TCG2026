#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalRGBColorSpaceTest_439 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxCalRGBColorSpace>();
    }

    std::unique_ptr<GfxCalRGBColorSpace> colorSpace;
};

// Test that the default constructor creates a valid object
TEST_F(GfxCalRGBColorSpaceTest_439, DefaultConstructor_439) {
    ASSERT_NE(colorSpace, nullptr);
}

// Test getMode returns the correct color space mode for CalRGB
TEST_F(GfxCalRGBColorSpaceTest_439, GetModeReturnsCalRGB_439) {
    EXPECT_EQ(colorSpace->getMode(), csCalRGB);
}

// Test getNComps returns 3 for RGB color space
TEST_F(GfxCalRGBColorSpaceTest_439, GetNCompsReturnsThree_439) {
    EXPECT_EQ(colorSpace->getNComps(), 3);
}

// Test default gamma values (typically 1.0 for CalRGB default)
TEST_F(GfxCalRGBColorSpaceTest_439, DefaultGammaR_439) {
    EXPECT_DOUBLE_EQ(colorSpace->getGammaR(), 1.0);
}

TEST_F(GfxCalRGBColorSpaceTest_439, DefaultGammaG_439) {
    EXPECT_DOUBLE_EQ(colorSpace->getGammaG(), 1.0);
}

TEST_F(GfxCalRGBColorSpaceTest_439, DefaultGammaB_439) {
    EXPECT_DOUBLE_EQ(colorSpace->getGammaB(), 1.0);
}

// Test default white point values (D65 or similar defaults)
TEST_F(GfxCalRGBColorSpaceTest_439, DefaultWhiteY_439) {
    EXPECT_DOUBLE_EQ(colorSpace->getWhiteY(), 1.0);
}

// Test default black point values (should be 0.0)
TEST_F(GfxCalRGBColorSpaceTest_439, DefaultBlackX_439) {
    EXPECT_DOUBLE_EQ(colorSpace->getBlackX(), 0.0);
}

TEST_F(GfxCalRGBColorSpaceTest_439, DefaultBlackY_439) {
    EXPECT_DOUBLE_EQ(colorSpace->getBlackY(), 0.0);
}

TEST_F(GfxCalRGBColorSpaceTest_439, DefaultBlackZ_439) {
    EXPECT_DOUBLE_EQ(colorSpace->getBlackZ(), 0.0);
}

// Test that the matrix has 9 elements
TEST_F(GfxCalRGBColorSpaceTest_439, MatrixHasNineElements_439) {
    const auto &matrix = colorSpace->getMatrix();
    EXPECT_EQ(matrix.size(), 9u);
}

// Test copy creates a valid independent copy
TEST_F(GfxCalRGBColorSpaceTest_439, CopyCreatesValidObject_439) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csCalRGB);
    EXPECT_EQ(copied->getNComps(), 3);
}

// Test that copied object preserves gamma values
TEST_F(GfxCalRGBColorSpaceTest_439, CopyPreservesGammaValues_439) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    auto *copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace *>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaR(), colorSpace->getGammaR());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaG(), colorSpace->getGammaG());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaB(), colorSpace->getGammaB());
}

// Test that copied object preserves white/black point values
TEST_F(GfxCalRGBColorSpaceTest_439, CopyPreservesWhiteBlackPoints_439) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    auto *copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace *>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteX(), colorSpace->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteY(), colorSpace->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getWhiteZ(), colorSpace->getWhiteZ());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackX(), colorSpace->getBlackX());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackY(), colorSpace->getBlackY());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getBlackZ(), colorSpace->getBlackZ());
}

// Test that copied object preserves matrix values
TEST_F(GfxCalRGBColorSpaceTest_439, CopyPreservesMatrix_439) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    auto *copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace *>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);
    const auto &origMatrix = colorSpace->getMatrix();
    const auto &copyMatrix = copiedCalRGB->getMatrix();
    for (size_t i = 0; i < 9; ++i) {
        EXPECT_DOUBLE_EQ(origMatrix[i], copyMatrix[i]);
    }
}

// Test getDefaultColor sets color values properly
TEST_F(GfxCalRGBColorSpaceTest_439, GetDefaultColor_439) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    // Default color for CalRGB should have all components set to 0
    for (int i = 0; i < colorSpace->getNComps(); ++i) {
        EXPECT_EQ(color.c[i], 0);
    }
}

// Test getGray with a default (black) color
TEST_F(GfxCalRGBColorSpaceTest_439, GetGrayWithBlackColor_439) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // Black color should produce gray value of 0
    EXPECT_EQ(gray, 0);
}

// Test getRGB with a default (black) color
TEST_F(GfxCalRGBColorSpaceTest_439, GetRGBWithBlackColor_439) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getCMYK with a default (black) color
TEST_F(GfxCalRGBColorSpaceTest_439, GetCMYKWithBlackColor_439) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Black in CMYK should have k = max (or near max)
    // At minimum, we verify the function doesn't crash and produces valid values
    EXPECT_GE(cmyk.k, 0);
}

// Test getDeviceN with a default color
TEST_F(GfxCalRGBColorSpaceTest_439, GetDeviceNWithBlackColor_439) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    // Just verify it doesn't crash and produces some output
}

// Test getRGB with white color (all components at max)
TEST_F(GfxCalRGBColorSpaceTest_439, GetRGBWithWhiteColor_439) {
    GfxColor color;
    color.c[0] = GfxColorComp1;
    color.c[1] = GfxColorComp1;
    color.c[2] = GfxColorComp1;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // White in CalRGB should map to white (or near white) in device RGB
    EXPECT_GT(rgb.r, 0);
    EXPECT_GT(rgb.g, 0);
    EXPECT_GT(rgb.b, 0);
}

// Test getGray with white color
TEST_F(GfxCalRGBColorSpaceTest_439, GetGrayWithWhiteColor_439) {
    GfxColor color;
    color.c[0] = GfxColorComp1;
    color.c[1] = GfxColorComp1;
    color.c[2] = GfxColorComp1;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // White should produce a high gray value
    EXPECT_GT(gray, 0);
}

// Test that getWhiteX returns a valid value
TEST_F(GfxCalRGBColorSpaceTest_439, GetWhiteX_439) {
    double whiteX = colorSpace->getWhiteX();
    EXPECT_GE(whiteX, 0.0);
}

// Test that getWhiteZ returns a valid value
TEST_F(GfxCalRGBColorSpaceTest_439, GetWhiteZ_439) {
    double whiteZ = colorSpace->getWhiteZ();
    EXPECT_GE(whiteZ, 0.0);
}

// Test default matrix values (identity-like matrix for CalRGB)
TEST_F(GfxCalRGBColorSpaceTest_439, DefaultMatrixValues_439) {
    const auto &matrix = colorSpace->getMatrix();
    // Default CalRGB matrix is typically the identity matrix:
    // 1 0 0 / 0 1 0 / 0 0 1
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
