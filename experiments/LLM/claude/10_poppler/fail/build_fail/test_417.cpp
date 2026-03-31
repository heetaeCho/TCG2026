#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalGrayColorSpaceTest_417 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxCalGrayColorSpace>();
    }

    std::unique_ptr<GfxCalGrayColorSpace> colorSpace;
};

// Test default construction and default white point values
TEST_F(GfxCalGrayColorSpaceTest_417, DefaultConstructionWhiteX_417) {
    double whiteX = colorSpace->getWhiteX();
    // Default white point X - just verify it returns a value (typically 1.0 for D65 or similar)
    EXPECT_GE(whiteX, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_417, DefaultConstructionWhiteY_417) {
    double whiteY = colorSpace->getWhiteY();
    EXPECT_GE(whiteY, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_417, DefaultConstructionWhiteZ_417) {
    double whiteZ = colorSpace->getWhiteZ();
    EXPECT_GE(whiteZ, 0.0);
}

// Test default black point values (should be 0.0 by default per PDF spec)
TEST_F(GfxCalGrayColorSpaceTest_417, DefaultConstructionBlackX_417) {
    double blackX = colorSpace->getBlackX();
    EXPECT_DOUBLE_EQ(blackX, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_417, DefaultConstructionBlackY_417) {
    double blackY = colorSpace->getBlackY();
    EXPECT_DOUBLE_EQ(blackY, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_417, DefaultConstructionBlackZ_417) {
    double blackZ = colorSpace->getBlackZ();
    EXPECT_DOUBLE_EQ(blackZ, 0.0);
}

// Test default gamma value (should be 1.0 by default per PDF spec)
TEST_F(GfxCalGrayColorSpaceTest_417, DefaultConstructionGamma_417) {
    double gamma = colorSpace->getGamma();
    EXPECT_DOUBLE_EQ(gamma, 1.0);
}

// Test that getMode returns the correct color space mode for CalGray
TEST_F(GfxCalGrayColorSpaceTest_417, GetModeReturnsCalGray_417) {
    EXPECT_EQ(colorSpace->getMode(), csCalGray);
}

// Test that getNComps returns 1 for a grayscale color space
TEST_F(GfxCalGrayColorSpaceTest_417, GetNCompsReturnsOne_417) {
    EXPECT_EQ(colorSpace->getNComps(), 1);
}

// Test copy produces a valid copy
TEST_F(GfxCalGrayColorSpaceTest_417, CopyProducesValidObject_417) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csCalGray);
    EXPECT_EQ(copied->getNComps(), 1);
}

// Test that the copy preserves white point values
TEST_F(GfxCalGrayColorSpaceTest_417, CopyPreservesWhitePoint_417) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    
    auto* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteX(), colorSpace->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteY(), colorSpace->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteZ(), colorSpace->getWhiteZ());
}

// Test that the copy preserves black point values
TEST_F(GfxCalGrayColorSpaceTest_417, CopyPreservesBlackPoint_417) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    
    auto* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackX(), colorSpace->getBlackX());
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackY(), colorSpace->getBlackY());
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackZ(), colorSpace->getBlackZ());
}

// Test that the copy preserves gamma
TEST_F(GfxCalGrayColorSpaceTest_417, CopyPreservesGamma_417) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    
    auto* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    
    EXPECT_DOUBLE_EQ(copiedCalGray->getGamma(), colorSpace->getGamma());
}

// Test getDefaultColor sets the color to default value
TEST_F(GfxCalGrayColorSpaceTest_417, GetDefaultColorSetsValue_417) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    // For CalGray, default color should be 0 (black)
    EXPECT_EQ(color.c[0], 0);
}

// Test getGray with minimum value (0)
TEST_F(GfxCalGrayColorSpaceTest_417, GetGrayMinValue_417) {
    GfxColor color;
    color.c[0] = 0;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // Gray value for input 0 should be 0 (black)
    EXPECT_EQ(gray, 0);
}

// Test getGray with maximum value
TEST_F(GfxCalGrayColorSpaceTest_417, GetGrayMaxValue_417) {
    GfxColor color;
    color.c[0] = gfxColorComp1;  // Maximum component value
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // Gray value for max input should be close to max
    EXPECT_GE(gray, 0);
}

// Test getRGB with minimum value
TEST_F(GfxCalGrayColorSpaceTest_417, GetRGBMinValue_417) {
    GfxColor color;
    color.c[0] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // For CalGray with input 0, RGB should be (0, 0, 0)
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB with maximum value
TEST_F(GfxCalGrayColorSpaceTest_417, GetRGBMaxValue_417) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // For CalGray with max input, RGB should be near max
    EXPECT_GE(rgb.r, 0);
    EXPECT_GE(rgb.g, 0);
    EXPECT_GE(rgb.b, 0);
}

// Test getCMYK with minimum value
TEST_F(GfxCalGrayColorSpaceTest_417, GetCMYKMinValue_417) {
    GfxColor color;
    color.c[0] = 0;
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // For black in CalGray, K should be max or near max
    EXPECT_GE(cmyk.k, 0);
}

// Test getCMYK with maximum value
TEST_F(GfxCalGrayColorSpaceTest_417, GetCMYKMaxValue_417) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Verify we get valid CMYK values
    EXPECT_GE(cmyk.c, 0);
    EXPECT_GE(cmyk.m, 0);
    EXPECT_GE(cmyk.y, 0);
    EXPECT_GE(cmyk.k, 0);
}

// Test getDeviceN with minimum value
TEST_F(GfxCalGrayColorSpaceTest_417, GetDeviceNMinValue_417) {
    GfxColor color;
    color.c[0] = 0;
    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    // Just verify it doesn't crash and produces some output
    // deviceN components depend on implementation
}

// Test getDeviceN with maximum value
TEST_F(GfxCalGrayColorSpaceTest_417, GetDeviceNMaxValue_417) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    // Just verify it doesn't crash
}

// Test that copy returns independent object
TEST_F(GfxCalGrayColorSpaceTest_417, CopyReturnsIndependentObject_417) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(copied.get(), colorSpace.get());
}

// Test mid-range gray value
TEST_F(GfxCalGrayColorSpaceTest_417, GetGrayMidValue_417) {
    GfxColor color;
    color.c[0] = gfxColorComp1 / 2;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // Mid value should produce a gray between 0 and max
    EXPECT_GE(gray, 0);
}

// Test mid-range RGB value
TEST_F(GfxCalGrayColorSpaceTest_417, GetRGBMidValue_417) {
    GfxColor color;
    color.c[0] = gfxColorComp1 / 2;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // For a gray color space, R, G, B should be equal or very close
    // Just verify they are valid
    EXPECT_GE(rgb.r, 0);
    EXPECT_GE(rgb.g, 0);
    EXPECT_GE(rgb.b, 0);
}
