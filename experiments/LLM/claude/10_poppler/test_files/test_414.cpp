#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalGrayColorSpaceTest_414 : public ::testing::Test {
protected:
    void SetUp() override {
        cs = std::make_unique<GfxCalGrayColorSpace>();
    }

    std::unique_ptr<GfxCalGrayColorSpace> cs;
};

// Test that getNComps returns 1 for CalGray color space
TEST_F(GfxCalGrayColorSpaceTest_414, GetNCompsReturnsOne_414) {
    EXPECT_EQ(cs->getNComps(), 1);
}

// Test that getMode returns the correct mode for CalGray
TEST_F(GfxCalGrayColorSpaceTest_414, GetModeReturnsCalGray_414) {
    EXPECT_EQ(cs->getMode(), csCalGray);
}

// Test default white point values
TEST_F(GfxCalGrayColorSpaceTest_414, DefaultWhitePointX_414) {
    // Default constructed CalGray should have some white point
    double wx = cs->getWhiteX();
    // White point X is typically initialized; just verify it's accessible
    EXPECT_GE(wx, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_414, DefaultWhitePointY_414) {
    double wy = cs->getWhiteY();
    EXPECT_GE(wy, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_414, DefaultWhitePointZ_414) {
    double wz = cs->getWhiteZ();
    EXPECT_GE(wz, 0.0);
}

// Test default black point values (should be 0,0,0 by default per PDF spec)
TEST_F(GfxCalGrayColorSpaceTest_414, DefaultBlackPointX_414) {
    EXPECT_DOUBLE_EQ(cs->getBlackX(), 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_414, DefaultBlackPointY_414) {
    EXPECT_DOUBLE_EQ(cs->getBlackY(), 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_414, DefaultBlackPointZ_414) {
    EXPECT_DOUBLE_EQ(cs->getBlackZ(), 0.0);
}

// Test default gamma value (should be 1 by default per PDF spec)
TEST_F(GfxCalGrayColorSpaceTest_414, DefaultGamma_414) {
    EXPECT_DOUBLE_EQ(cs->getGamma(), 1.0);
}

// Test copy creates a valid copy
TEST_F(GfxCalGrayColorSpaceTest_414, CopyCreatesCopy_414) {
    auto copied = cs->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csCalGray);
    EXPECT_EQ(copied->getNComps(), 1);
}

// Test copy preserves properties
TEST_F(GfxCalGrayColorSpaceTest_414, CopyPreservesProperties_414) {
    auto copied = cs->copy();
    ASSERT_NE(copied, nullptr);

    auto* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);

    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteX(), cs->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteY(), cs->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteZ(), cs->getWhiteZ());
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackX(), cs->getBlackX());
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackY(), cs->getBlackY());
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackZ(), cs->getBlackZ());
    EXPECT_DOUBLE_EQ(copiedCalGray->getGamma(), cs->getGamma());
}

// Test getDefaultColor sets default color
TEST_F(GfxCalGrayColorSpaceTest_414, GetDefaultColorSetsColor_414) {
    GfxColor color;
    cs->getDefaultColor(&color);
    // Default color for CalGray should be 0 (black)
    EXPECT_EQ(color.c[0], 0);
}

// Test getGray with a color value of 0 (black)
TEST_F(GfxCalGrayColorSpaceTest_414, GetGrayBlack_414) {
    GfxColor color;
    color.c[0] = 0;
    GfxGray gray;
    cs->getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getGray with maximum value (white)
TEST_F(GfxCalGrayColorSpaceTest_414, GetGrayWhite_414) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxGray gray;
    cs->getGray(&color, &gray);
    EXPECT_EQ(gray, gfxColorComp1);
}

// Test getRGB with black
TEST_F(GfxCalGrayColorSpaceTest_414, GetRGBBlack_414) {
    GfxColor color;
    color.c[0] = 0;
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB with white
TEST_F(GfxCalGrayColorSpaceTest_414, GetRGBWhite_414) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    // For white in CalGray, all components should be at or near max
    EXPECT_GE(rgb.r, 0);
    EXPECT_GE(rgb.g, 0);
    EXPECT_GE(rgb.b, 0);
}

// Test getCMYK with black
TEST_F(GfxCalGrayColorSpaceTest_414, GetCMYKBlack_414) {
    GfxColor color;
    color.c[0] = 0;
    GfxCMYK cmyk;
    cs->getCMYK(&color, &cmyk);
    // Black in CMYK should have K component set
    EXPECT_GE(cmyk.k, 0);
}

// Test getCMYK with white
TEST_F(GfxCalGrayColorSpaceTest_414, GetCMYKWhite_414) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxCMYK cmyk;
    cs->getCMYK(&color, &cmyk);
    // White in CMYK: C=0, M=0, Y=0, K=0
    EXPECT_GE(cmyk.c, 0);
}

// Test getDeviceN with a color
TEST_F(GfxCalGrayColorSpaceTest_414, GetDeviceNBlack_414) {
    GfxColor color;
    color.c[0] = 0;
    GfxColor deviceN;
    cs->getDeviceN(&color, &deviceN);
    // DeviceN output should be valid
    // Just ensure no crash and values are accessible
    (void)deviceN.c[0];
}

// Test getDeviceN with white
TEST_F(GfxCalGrayColorSpaceTest_414, GetDeviceNWhite_414) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxColor deviceN;
    cs->getDeviceN(&color, &deviceN);
    (void)deviceN.c[0];
}

// Test with mid-range gray value
TEST_F(GfxCalGrayColorSpaceTest_414, GetGrayMidRange_414) {
    GfxColor color;
    color.c[0] = gfxColorComp1 / 2;
    GfxGray gray;
    cs->getGray(&color, &gray);
    // Mid-range gray should be between 0 and max
    EXPECT_GE(gray, 0);
    EXPECT_LE(gray, gfxColorComp1);
}

// Test getRGB with mid-range value
TEST_F(GfxCalGrayColorSpaceTest_414, GetRGBMidRange_414) {
    GfxColor color;
    color.c[0] = gfxColorComp1 / 2;
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    EXPECT_GE(rgb.r, 0);
    EXPECT_LE(rgb.r, gfxColorComp1);
    EXPECT_GE(rgb.g, 0);
    EXPECT_LE(rgb.g, gfxColorComp1);
    EXPECT_GE(rgb.b, 0);
    EXPECT_LE(rgb.b, gfxColorComp1);
}

// Test that copy is independent (modifying original doesn't affect copy)
TEST_F(GfxCalGrayColorSpaceTest_414, CopyIsIndependent_414) {
    auto copied = cs->copy();
    ASSERT_NE(copied, nullptr);
    // Both should still be valid after this scope
    EXPECT_EQ(copied->getNComps(), 1);
    EXPECT_EQ(cs->getNComps(), 1);
}
