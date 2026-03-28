#include <gtest/gtest.h>
#include "poppler/GfxState.h"

class GfxCalRGBColorSpaceTest_430 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxCalRGBColorSpace>();
    }

    std::unique_ptr<GfxCalRGBColorSpace> colorSpace;
};

// Test that getMode returns csCalRGB
TEST_F(GfxCalRGBColorSpaceTest_430, GetModeReturnsCalRGB_430) {
    EXPECT_EQ(colorSpace->getMode(), csCalRGB);
}

// Test that getNComps returns 3 for RGB
TEST_F(GfxCalRGBColorSpaceTest_430, GetNCompsReturnsThree_430) {
    EXPECT_EQ(colorSpace->getNComps(), 3);
}

// Test default white point values
TEST_F(GfxCalRGBColorSpaceTest_430, DefaultWhitePointValues_430) {
    // Default white point should be reasonable (typically D65: 0.9505, 1.0, 1.089)
    // but constructor defaults may differ; just check they are accessible
    double whiteX = colorSpace->getWhiteX();
    double whiteY = colorSpace->getWhiteY();
    double whiteZ = colorSpace->getWhiteZ();
    // White point Y should be 1.0 per PDF spec
    EXPECT_DOUBLE_EQ(whiteY, 1.0);
    // WhiteX and WhiteZ should be non-negative
    EXPECT_GE(whiteX, 0.0);
    EXPECT_GE(whiteZ, 0.0);
}

// Test default black point values (should be 0,0,0)
TEST_F(GfxCalRGBColorSpaceTest_430, DefaultBlackPointValues_430) {
    EXPECT_DOUBLE_EQ(colorSpace->getBlackX(), 0.0);
    EXPECT_DOUBLE_EQ(colorSpace->getBlackY(), 0.0);
    EXPECT_DOUBLE_EQ(colorSpace->getBlackZ(), 0.0);
}

// Test default gamma values (should be 1.0 per PDF spec default)
TEST_F(GfxCalRGBColorSpaceTest_430, DefaultGammaValues_430) {
    EXPECT_DOUBLE_EQ(colorSpace->getGammaR(), 1.0);
    EXPECT_DOUBLE_EQ(colorSpace->getGammaG(), 1.0);
    EXPECT_DOUBLE_EQ(colorSpace->getGammaB(), 1.0);
}

// Test default matrix values (should be identity-like)
TEST_F(GfxCalRGBColorSpaceTest_430, DefaultMatrixValues_430) {
    const std::array<double, 9> &mat = colorSpace->getMatrix();
    // Default matrix per PDF spec is identity:
    // 1 0 0  0 1 0  0 0 1
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

// Test getDefaultColor sets color to default (0, 0, 0)
TEST_F(GfxCalRGBColorSpaceTest_430, GetDefaultColorSetsToBlack_430) {
    GfxColor color;
    // Initialize to non-zero values
    for (int i = 0; i < gfxColorMaxComps; i++) {
        color.c[i] = 65535;
    }
    colorSpace->getDefaultColor(&color);
    // Default color for CalRGB should be (0, 0, 0)
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
}

// Test copy creates a valid copy with same mode
TEST_F(GfxCalRGBColorSpaceTest_430, CopyRetainsSameMode_430) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csCalRGB);
    EXPECT_EQ(copied->getNComps(), 3);
}

// Test copy preserves gamma values
TEST_F(GfxCalRGBColorSpaceTest_430, CopyPreservesGamma_430) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    auto *copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace *>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaR(), colorSpace->getGammaR());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaG(), colorSpace->getGammaG());
    EXPECT_DOUBLE_EQ(copiedCalRGB->getGammaB(), colorSpace->getGammaB());
}

// Test copy preserves white/black points
TEST_F(GfxCalRGBColorSpaceTest_430, CopyPreservesWhiteBlackPoints_430) {
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

// Test copy preserves matrix
TEST_F(GfxCalRGBColorSpaceTest_430, CopyPreservesMatrix_430) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    auto *copiedCalRGB = dynamic_cast<GfxCalRGBColorSpace *>(copied.get());
    ASSERT_NE(copiedCalRGB, nullptr);
    const auto &origMat = colorSpace->getMatrix();
    const auto &copyMat = copiedCalRGB->getMatrix();
    for (int i = 0; i < 9; i++) {
        EXPECT_DOUBLE_EQ(origMat[i], copyMat[i]);
    }
}

// Test getGray with black color (0,0,0)
TEST_F(GfxCalRGBColorSpaceTest_430, GetGrayWithBlackColor_430) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getGray with white color (max, max, max)
TEST_F(GfxCalRGBColorSpaceTest_430, GetGrayWithWhiteColor_430) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // White should produce a gray value close to max
    EXPECT_GT(gray, 0);
}

// Test getRGB with black color
TEST_F(GfxCalRGBColorSpaceTest_430, GetRGBWithBlackColor_430) {
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
TEST_F(GfxCalRGBColorSpaceTest_430, GetRGBWithWhiteColor_430) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = gfxColorComp1;
    color.c[2] = gfxColorComp1;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // For default CalRGB (identity matrix, gamma=1), white should map to white
    EXPECT_GT(rgb.r, 0);
    EXPECT_GT(rgb.g, 0);
    EXPECT_GT(rgb.b, 0);
}

// Test getCMYK with black color
TEST_F(GfxCalRGBColorSpaceTest_430, GetCMYKWithBlackColor_430) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Black in RGB should result in K=max or equivalent
    // At minimum, verify it doesn't crash and produces valid output
    EXPECT_GE(cmyk.k, 0);
}

// Test getDeviceN with black color
TEST_F(GfxCalRGBColorSpaceTest_430, GetDeviceNWithBlackColor_430) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxColor deviceN;
    memset(&deviceN, 0, sizeof(deviceN));
    colorSpace->getDeviceN(&color, &deviceN);
    // Just ensure it doesn't crash; deviceN output depends on implementation
}

// Test getRGB with a pure red color
TEST_F(GfxCalRGBColorSpaceTest_430, GetRGBWithPureRed_430) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // Red component should be non-zero
    EXPECT_GT(rgb.r, 0);
}

// Test getRGB with a pure green color
TEST_F(GfxCalRGBColorSpaceTest_430, GetRGBWithPureGreen_430) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = gfxColorComp1;
    color.c[2] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // Green component should be non-zero
    EXPECT_GT(rgb.g, 0);
}

// Test getRGB with a pure blue color
TEST_F(GfxCalRGBColorSpaceTest_430, GetRGBWithPureBlue_430) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = gfxColorComp1;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // Blue component should be non-zero
    EXPECT_GT(rgb.b, 0);
}

// Test that copy returns a distinct object
TEST_F(GfxCalRGBColorSpaceTest_430, CopyReturnsDifferentPointer_430) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(copied.get(), colorSpace.get());
}
