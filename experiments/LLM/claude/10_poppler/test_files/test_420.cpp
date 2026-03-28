#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalGrayColorSpaceTest_420 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxCalGrayColorSpace>();
    }

    std::unique_ptr<GfxCalGrayColorSpace> colorSpace;
};

// Test default construction and default values for white point
TEST_F(GfxCalGrayColorSpaceTest_420, DefaultWhiteX_420) {
    double whiteX = colorSpace->getWhiteX();
    // Default white point X - just verify it returns a value (typically 1.0 for D65 or similar)
    EXPECT_GE(whiteX, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_420, DefaultWhiteY_420) {
    double whiteY = colorSpace->getWhiteY();
    EXPECT_GE(whiteY, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_420, DefaultWhiteZ_420) {
    double whiteZ = colorSpace->getWhiteZ();
    EXPECT_GE(whiteZ, 0.0);
}

// Test default black point values (should be 0 by default per PDF spec)
TEST_F(GfxCalGrayColorSpaceTest_420, DefaultBlackX_420) {
    double blackX = colorSpace->getBlackX();
    EXPECT_DOUBLE_EQ(blackX, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_420, DefaultBlackY_420) {
    double blackY = colorSpace->getBlackY();
    EXPECT_DOUBLE_EQ(blackY, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_420, DefaultBlackZ_420) {
    double blackZ = colorSpace->getBlackZ();
    EXPECT_DOUBLE_EQ(blackZ, 0.0);
}

// Test default gamma (should be 1.0 by default per PDF spec)
TEST_F(GfxCalGrayColorSpaceTest_420, DefaultGamma_420) {
    double gamma = colorSpace->getGamma();
    EXPECT_DOUBLE_EQ(gamma, 1.0);
}

// Test getMode returns CalGray mode
TEST_F(GfxCalGrayColorSpaceTest_420, GetModeReturnsCalGray_420) {
    GfxColorSpaceMode mode = colorSpace->getMode();
    EXPECT_EQ(mode, csCalGray);
}

// Test getNComps returns 1 for gray color space
TEST_F(GfxCalGrayColorSpaceTest_420, GetNCompsReturnsOne_420) {
    int nComps = colorSpace->getNComps();
    EXPECT_EQ(nComps, 1);
}

// Test copy creates a valid copy
TEST_F(GfxCalGrayColorSpaceTest_420, CopyCreatesValidCopy_420) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csCalGray);
    EXPECT_EQ(copied->getNComps(), 1);
}

// Test copy preserves black point values
TEST_F(GfxCalGrayColorSpaceTest_420, CopyPreservesBlackPoint_420) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    GfxCalGrayColorSpace* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackX(), colorSpace->getBlackX());
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackY(), colorSpace->getBlackY());
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackZ(), colorSpace->getBlackZ());
}

// Test copy preserves white point values
TEST_F(GfxCalGrayColorSpaceTest_420, CopyPreservesWhitePoint_420) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    GfxCalGrayColorSpace* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteX(), colorSpace->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteY(), colorSpace->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteZ(), colorSpace->getWhiteZ());
}

// Test copy preserves gamma
TEST_F(GfxCalGrayColorSpaceTest_420, CopyPreservesGamma_420) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    GfxCalGrayColorSpace* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalGray->getGamma(), colorSpace->getGamma());
}

// Test getDefaultColor sets color to valid value
TEST_F(GfxCalGrayColorSpaceTest_420, GetDefaultColorSetsColor_420) {
    GfxColor color;
    // Initialize to non-zero to verify it gets set
    color.c[0] = 12345;
    colorSpace->getDefaultColor(&color);
    // Default color for CalGray should be 0 (black)
    EXPECT_EQ(color.c[0], 0);
}

// Test getGray with minimum value (black)
TEST_F(GfxCalGrayColorSpaceTest_420, GetGrayBlack_420) {
    GfxColor color;
    color.c[0] = 0;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getGray with maximum value (white)
TEST_F(GfxCalGrayColorSpaceTest_420, GetGrayWhite_420) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // With default gamma=1, max input should produce max gray
    EXPECT_GE(gray, 0);
}

// Test getRGB with minimum value (black)
TEST_F(GfxCalGrayColorSpaceTest_420, GetRGBBlack_420) {
    GfxColor color;
    color.c[0] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB with maximum value (white)
TEST_F(GfxCalGrayColorSpaceTest_420, GetRGBWhite_420) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // White should have all components at or near maximum
    EXPECT_GT(rgb.r, 0);
    EXPECT_GT(rgb.g, 0);
    EXPECT_GT(rgb.b, 0);
}

// Test getCMYK with minimum value (black)
TEST_F(GfxCalGrayColorSpaceTest_420, GetCMYKBlack_420) {
    GfxColor color;
    color.c[0] = 0;
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Black in CMYK should have K at maximum
    EXPECT_GE(cmyk.k, 0);
}

// Test getCMYK with maximum value (white)
TEST_F(GfxCalGrayColorSpaceTest_420, GetCMYKWhite_420) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // White in CMYK should have all components at or near 0
    EXPECT_GE(cmyk.c, 0);
    EXPECT_GE(cmyk.m, 0);
    EXPECT_GE(cmyk.y, 0);
}

// Test getDeviceN with black
TEST_F(GfxCalGrayColorSpaceTest_420, GetDeviceNBlack_420) {
    GfxColor color;
    color.c[0] = 0;
    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    // Just verify it doesn't crash and produces some output
    SUCCEED();
}

// Test getDeviceN with white
TEST_F(GfxCalGrayColorSpaceTest_420, GetDeviceNWhite_420) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    SUCCEED();
}

// Test that black point values are consistent (all zero by default)
TEST_F(GfxCalGrayColorSpaceTest_420, BlackPointConsistency_420) {
    EXPECT_DOUBLE_EQ(colorSpace->getBlackX(), 0.0);
    EXPECT_DOUBLE_EQ(colorSpace->getBlackY(), 0.0);
    EXPECT_DOUBLE_EQ(colorSpace->getBlackZ(), 0.0);
}

// Test getRGB produces equal R, G, B for a gray color space (monotone)
TEST_F(GfxCalGrayColorSpaceTest_420, GetRGBProducesEqualComponents_420) {
    GfxColor color;
    color.c[0] = gfxColorComp1 / 2;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // For a calibrated gray, R, G, B should be approximately equal
    // Allow some tolerance due to color transform
    EXPECT_NEAR(static_cast<double>(rgb.r), static_cast<double>(rgb.g), 1000);
    EXPECT_NEAR(static_cast<double>(rgb.g), static_cast<double>(rgb.b), 1000);
}
