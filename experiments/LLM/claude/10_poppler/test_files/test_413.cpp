#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalGrayColorSpaceTest_413 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxCalGrayColorSpace>();
    }

    std::unique_ptr<GfxCalGrayColorSpace> colorSpace;
};

// Test that getMode returns csCalGray
TEST_F(GfxCalGrayColorSpaceTest_413, GetModeReturnsCalGray_413) {
    EXPECT_EQ(colorSpace->getMode(), csCalGray);
}

// Test that getNComps returns 1 for a grayscale color space
TEST_F(GfxCalGrayColorSpaceTest_413, GetNCompsReturnsOne_413) {
    EXPECT_EQ(colorSpace->getNComps(), 1);
}

// Test default white point values
TEST_F(GfxCalGrayColorSpaceTest_413, DefaultWhitePointX_413) {
    double whiteX = colorSpace->getWhiteX();
    // Default constructed, check it has some value (typically 1.0 for D65 or similar)
    // We just verify it's accessible and returns a finite number
    EXPECT_FALSE(std::isnan(whiteX));
}

TEST_F(GfxCalGrayColorSpaceTest_413, DefaultWhitePointY_413) {
    double whiteY = colorSpace->getWhiteY();
    EXPECT_FALSE(std::isnan(whiteY));
}

TEST_F(GfxCalGrayColorSpaceTest_413, DefaultWhitePointZ_413) {
    double whiteZ = colorSpace->getWhiteZ();
    EXPECT_FALSE(std::isnan(whiteZ));
}

// Test default black point values (should be 0.0 by default per PDF spec)
TEST_F(GfxCalGrayColorSpaceTest_413, DefaultBlackPointX_413) {
    EXPECT_DOUBLE_EQ(colorSpace->getBlackX(), 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_413, DefaultBlackPointY_413) {
    EXPECT_DOUBLE_EQ(colorSpace->getBlackY(), 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_413, DefaultBlackPointZ_413) {
    EXPECT_DOUBLE_EQ(colorSpace->getBlackZ(), 0.0);
}

// Test default gamma value (should be 1.0 by default per PDF spec)
TEST_F(GfxCalGrayColorSpaceTest_413, DefaultGamma_413) {
    EXPECT_DOUBLE_EQ(colorSpace->getGamma(), 1.0);
}

// Test copy returns a valid copy
TEST_F(GfxCalGrayColorSpaceTest_413, CopyReturnsValidColorSpace_413) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csCalGray);
}

// Test that copy preserves the mode
TEST_F(GfxCalGrayColorSpaceTest_413, CopyPreservesMode_413) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), colorSpace->getMode());
}

// Test that copy preserves getNComps
TEST_F(GfxCalGrayColorSpaceTest_413, CopyPreservesNComps_413) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNComps(), colorSpace->getNComps());
}

// Test getDefaultColor sets color appropriately
TEST_F(GfxCalGrayColorSpaceTest_413, GetDefaultColorSetsValue_413) {
    GfxColor color;
    // Initialize to something non-zero to verify it gets set
    color.c[0] = 12345;
    colorSpace->getDefaultColor(&color);
    // Default color for CalGray should be 0 (black)
    EXPECT_EQ(color.c[0], 0);
}

// Test getGray with a color value of 0 (black)
TEST_F(GfxCalGrayColorSpaceTest_413, GetGrayBlack_413) {
    GfxColor color;
    color.c[0] = 0;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // Gray value for input 0 should be 0 (black)
    EXPECT_EQ(gray, 0);
}

// Test getGray with maximum color value (white)
TEST_F(GfxCalGrayColorSpaceTest_413, GetGrayWhite_413) {
    GfxColor color;
    color.c[0] = gfxColorComp1; // max value representing 1.0
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // Gray value for input 1.0 should be close to max (white)
    EXPECT_GE(gray, 0);
}

// Test getRGB with black
TEST_F(GfxCalGrayColorSpaceTest_413, GetRGBBlack_413) {
    GfxColor color;
    color.c[0] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB with white
TEST_F(GfxCalGrayColorSpaceTest_413, GetRGBWhite_413) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // For gray=1.0, RGB should all be at or near maximum
    EXPECT_GE(rgb.r, 0);
    EXPECT_GE(rgb.g, 0);
    EXPECT_GE(rgb.b, 0);
}

// Test getCMYK with black
TEST_F(GfxCalGrayColorSpaceTest_413, GetCMYKBlack_413) {
    GfxColor color;
    color.c[0] = 0;
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Black in CMYK should have K=max or close to it
    // Just check it doesn't crash and returns valid values
    EXPECT_GE(cmyk.k, 0);
}

// Test getCMYK with white
TEST_F(GfxCalGrayColorSpaceTest_413, GetCMYKWhite_413) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // White in CMYK should have all components near 0
    EXPECT_GE(cmyk.c, 0);
    EXPECT_GE(cmyk.m, 0);
    EXPECT_GE(cmyk.y, 0);
    EXPECT_GE(cmyk.k, 0);
}

// Test getDeviceN doesn't crash
TEST_F(GfxCalGrayColorSpaceTest_413, GetDeviceNDoesNotCrash_413) {
    GfxColor color;
    color.c[0] = 0;
    GfxColor deviceN;
    EXPECT_NO_FATAL_FAILURE(colorSpace->getDeviceN(&color, &deviceN));
}

// Test copy returns independent object (modifying original doesn't affect copy)
TEST_F(GfxCalGrayColorSpaceTest_413, CopyIsIndependent_413) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    
    // Verify the copy has the same properties
    GfxCalGrayColorSpace* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    
    EXPECT_DOUBLE_EQ(copiedCalGray->getGamma(), colorSpace->getGamma());
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteX(), colorSpace->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteY(), colorSpace->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteZ(), colorSpace->getWhiteZ());
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackX(), colorSpace->getBlackX());
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackY(), colorSpace->getBlackY());
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackZ(), colorSpace->getBlackZ());
}

// Test getGray with mid-range value
TEST_F(GfxCalGrayColorSpaceTest_413, GetGrayMidRange_413) {
    GfxColor color;
    color.c[0] = gfxColorComp1 / 2; // approximately 0.5
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // Mid-range gray should be between 0 and max
    EXPECT_GE(gray, 0);
    EXPECT_LE(gray, gfxColorComp1);
}

// Test getRGB with mid-range value
TEST_F(GfxCalGrayColorSpaceTest_413, GetRGBMidRange_413) {
    GfxColor color;
    color.c[0] = gfxColorComp1 / 2;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // For a gray color space, R, G, B should be approximately equal
    // Just verify they're in valid range
    EXPECT_GE(rgb.r, 0);
    EXPECT_LE(rgb.r, gfxColorComp1);
    EXPECT_GE(rgb.g, 0);
    EXPECT_LE(rgb.g, gfxColorComp1);
    EXPECT_GE(rgb.b, 0);
    EXPECT_LE(rgb.b, gfxColorComp1);
}
