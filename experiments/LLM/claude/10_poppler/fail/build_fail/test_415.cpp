#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalGrayColorSpaceTest_415 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxCalGrayColorSpace>();
    }

    std::unique_ptr<GfxCalGrayColorSpace> colorSpace;
};

// Test default construction and white point values
TEST_F(GfxCalGrayColorSpaceTest_415, DefaultWhiteX_415) {
    double whiteX = colorSpace->getWhiteX();
    // Default white point X should be a valid number (typically 1.0 for D65 or similar)
    EXPECT_GE(whiteX, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_415, DefaultWhiteY_415) {
    double whiteY = colorSpace->getWhiteY();
    EXPECT_GE(whiteY, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_415, DefaultWhiteZ_415) {
    double whiteZ = colorSpace->getWhiteZ();
    EXPECT_GE(whiteZ, 0.0);
}

// Test default black point values (should typically be 0.0)
TEST_F(GfxCalGrayColorSpaceTest_415, DefaultBlackX_415) {
    double blackX = colorSpace->getBlackX();
    EXPECT_DOUBLE_EQ(blackX, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_415, DefaultBlackY_415) {
    double blackY = colorSpace->getBlackY();
    EXPECT_DOUBLE_EQ(blackY, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_415, DefaultBlackZ_415) {
    double blackZ = colorSpace->getBlackZ();
    EXPECT_DOUBLE_EQ(blackZ, 0.0);
}

// Test default gamma value (should typically be 1.0)
TEST_F(GfxCalGrayColorSpaceTest_415, DefaultGamma_415) {
    double gamma = colorSpace->getGamma();
    EXPECT_GT(gamma, 0.0);
}

// Test that getNComps returns 1 for CalGray
TEST_F(GfxCalGrayColorSpaceTest_415, NCompsIsOne_415) {
    EXPECT_EQ(colorSpace->getNComps(), 1);
}

// Test the color space mode
TEST_F(GfxCalGrayColorSpaceTest_415, ModeIsCalGray_415) {
    EXPECT_EQ(colorSpace->getMode(), csCalGray);
}

// Test copy functionality
TEST_F(GfxCalGrayColorSpaceTest_415, CopyPreservesWhiteX_415) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    auto* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteX(), colorSpace->getWhiteX());
}

TEST_F(GfxCalGrayColorSpaceTest_415, CopyPreservesWhiteY_415) {
    auto copied = colorSpace->copy();
    auto* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteY(), colorSpace->getWhiteY());
}

TEST_F(GfxCalGrayColorSpaceTest_415, CopyPreservesWhiteZ_415) {
    auto copied = colorSpace->copy();
    auto* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteZ(), colorSpace->getWhiteZ());
}

TEST_F(GfxCalGrayColorSpaceTest_415, CopyPreservesBlackX_415) {
    auto copied = colorSpace->copy();
    auto* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackX(), colorSpace->getBlackX());
}

TEST_F(GfxCalGrayColorSpaceTest_415, CopyPreservesBlackY_415) {
    auto copied = colorSpace->copy();
    auto* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackY(), colorSpace->getBlackY());
}

TEST_F(GfxCalGrayColorSpaceTest_415, CopyPreservesBlackZ_415) {
    auto copied = colorSpace->copy();
    auto* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackZ(), colorSpace->getBlackZ());
}

TEST_F(GfxCalGrayColorSpaceTest_415, CopyPreservesGamma_415) {
    auto copied = colorSpace->copy();
    auto* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalGray->getGamma(), colorSpace->getGamma());
}

TEST_F(GfxCalGrayColorSpaceTest_415, CopyPreservesNComps_415) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNComps(), colorSpace->getNComps());
}

TEST_F(GfxCalGrayColorSpaceTest_415, CopyPreservesMode_415) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), colorSpace->getMode());
}

// Test getDefaultColor
TEST_F(GfxCalGrayColorSpaceTest_415, GetDefaultColor_415) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    // For CalGray, default color component should be 0 (black)
    EXPECT_EQ(color.c[0], 0);
}

// Test getGray with a known color value
TEST_F(GfxCalGrayColorSpaceTest_415, GetGrayWithZeroColor_415) {
    GfxColor color;
    color.c[0] = 0;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // Gray value for 0 input should be 0
    EXPECT_EQ(gray, 0);
}

TEST_F(GfxCalGrayColorSpaceTest_415, GetGrayWithMaxColor_415) {
    GfxColor color;
    color.c[0] = gfxColorComp1;  // Maximum value
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // Gray value for max input should be max
    EXPECT_EQ(gray, gfxColorComp1);
}

// Test getRGB with zero input
TEST_F(GfxCalGrayColorSpaceTest_415, GetRGBWithZeroColor_415) {
    GfxColor color;
    color.c[0] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB with max input
TEST_F(GfxCalGrayColorSpaceTest_415, GetRGBWithMaxColor_415) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // For a gray color space, max input should produce white
    EXPECT_GT(rgb.r, 0);
    EXPECT_GT(rgb.g, 0);
    EXPECT_GT(rgb.b, 0);
}

// Test getCMYK with zero input
TEST_F(GfxCalGrayColorSpaceTest_415, GetCMYKWithZeroColor_415) {
    GfxColor color;
    color.c[0] = 0;
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Zero gray input should result in black in CMYK
    // Typically K=1 (max) for black
    EXPECT_GE(cmyk.k, 0);
}

// Test getDeviceN with zero input
TEST_F(GfxCalGrayColorSpaceTest_415, GetDeviceNWithZeroColor_415) {
    GfxColor color;
    color.c[0] = 0;
    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    // Just verify it doesn't crash; exact values depend on implementation
}

// Test consistency: white point values are non-negative
TEST_F(GfxCalGrayColorSpaceTest_415, WhitePointValuesNonNegative_415) {
    EXPECT_GE(colorSpace->getWhiteX(), 0.0);
    EXPECT_GE(colorSpace->getWhiteY(), 0.0);
    EXPECT_GE(colorSpace->getWhiteZ(), 0.0);
}

// Test consistency: black point values are non-negative
TEST_F(GfxCalGrayColorSpaceTest_415, BlackPointValuesNonNegative_415) {
    EXPECT_GE(colorSpace->getBlackX(), 0.0);
    EXPECT_GE(colorSpace->getBlackY(), 0.0);
    EXPECT_GE(colorSpace->getBlackZ(), 0.0);
}

// Test consistency: gamma is positive
TEST_F(GfxCalGrayColorSpaceTest_415, GammaIsPositive_415) {
    EXPECT_GT(colorSpace->getGamma(), 0.0);
}

// Test that copy creates an independent object
TEST_F(GfxCalGrayColorSpaceTest_415, CopyCreatesIndependentObject_415) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(copied.get(), colorSpace.get());
}

// Test getRGB mid-value
TEST_F(GfxCalGrayColorSpaceTest_415, GetRGBWithMidColor_415) {
    GfxColor color;
    color.c[0] = gfxColorComp1 / 2;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // Mid gray should produce mid-range RGB values
    EXPECT_GT(rgb.r, 0);
    EXPECT_GT(rgb.g, 0);
    EXPECT_GT(rgb.b, 0);
    EXPECT_LE(rgb.r, gfxColorComp1);
    EXPECT_LE(rgb.g, gfxColorComp1);
    EXPECT_LE(rgb.b, gfxColorComp1);
}

// Test getGray monotonicity: higher input should give higher gray
TEST_F(GfxCalGrayColorSpaceTest_415, GetGrayMonotonicity_415) {
    GfxColor colorLow, colorHigh;
    colorLow.c[0] = gfxColorComp1 / 4;
    colorHigh.c[0] = 3 * (gfxColorComp1 / 4);
    GfxGray grayLow, grayHigh;
    colorSpace->getGray(&colorLow, &grayLow);
    colorSpace->getGray(&colorHigh, &grayHigh);
    EXPECT_LE(grayLow, grayHigh);
}
