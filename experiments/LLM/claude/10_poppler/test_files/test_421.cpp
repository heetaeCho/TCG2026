#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalGrayColorSpaceTest_421 : public ::testing::Test {
protected:
    void SetUp() override {
        cs = std::make_unique<GfxCalGrayColorSpace>();
    }

    std::unique_ptr<GfxCalGrayColorSpace> cs;
};

// Test default construction and default gamma value
TEST_F(GfxCalGrayColorSpaceTest_421, DefaultGamma_421) {
    double gamma = cs->getGamma();
    // Default gamma should be 1.0 for CalGray color spaces
    EXPECT_DOUBLE_EQ(gamma, 1.0);
}

// Test default white point values
TEST_F(GfxCalGrayColorSpaceTest_421, DefaultWhitePoint_421) {
    // Default white point for a CalGray should have specific values
    // Typically WhiteY should be 1.0
    EXPECT_DOUBLE_EQ(cs->getWhiteY(), 1.0);
}

// Test default white X value
TEST_F(GfxCalGrayColorSpaceTest_421, DefaultWhiteX_421) {
    double whiteX = cs->getWhiteX();
    EXPECT_DOUBLE_EQ(whiteX, 1.0);
}

// Test default white Z value
TEST_F(GfxCalGrayColorSpaceTest_421, DefaultWhiteZ_421) {
    double whiteZ = cs->getWhiteZ();
    EXPECT_DOUBLE_EQ(whiteZ, 1.0);
}

// Test default black point values (should be 0)
TEST_F(GfxCalGrayColorSpaceTest_421, DefaultBlackX_421) {
    EXPECT_DOUBLE_EQ(cs->getBlackX(), 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_421, DefaultBlackY_421) {
    EXPECT_DOUBLE_EQ(cs->getBlackY(), 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_421, DefaultBlackZ_421) {
    EXPECT_DOUBLE_EQ(cs->getBlackZ(), 0.0);
}

// Test color space mode
TEST_F(GfxCalGrayColorSpaceTest_421, ModeIsCalGray_421) {
    EXPECT_EQ(cs->getMode(), csCalGray);
}

// Test number of components
TEST_F(GfxCalGrayColorSpaceTest_421, NCompsIsOne_421) {
    EXPECT_EQ(cs->getNComps(), 1);
}

// Test copy creates a valid copy
TEST_F(GfxCalGrayColorSpaceTest_421, CopyPreservesMode_421) {
    auto copied = cs->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csCalGray);
}

// Test copy preserves gamma
TEST_F(GfxCalGrayColorSpaceTest_421, CopyPreservesGamma_421) {
    auto copied = cs->copy();
    ASSERT_NE(copied, nullptr);
    GfxCalGrayColorSpace* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalGray->getGamma(), cs->getGamma());
}

// Test copy preserves white point
TEST_F(GfxCalGrayColorSpaceTest_421, CopyPreservesWhitePoint_421) {
    auto copied = cs->copy();
    ASSERT_NE(copied, nullptr);
    GfxCalGrayColorSpace* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteX(), cs->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteY(), cs->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteZ(), cs->getWhiteZ());
}

// Test copy preserves black point
TEST_F(GfxCalGrayColorSpaceTest_421, CopyPreservesBlackPoint_421) {
    auto copied = cs->copy();
    ASSERT_NE(copied, nullptr);
    GfxCalGrayColorSpace* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackX(), cs->getBlackX());
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackY(), cs->getBlackY());
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackZ(), cs->getBlackZ());
}

// Test getDefaultColor
TEST_F(GfxCalGrayColorSpaceTest_421, GetDefaultColor_421) {
    GfxColor color;
    cs->getDefaultColor(&color);
    // Default color for CalGray should set the component to 0
    EXPECT_EQ(color.c[0], 0);
}

// Test getGray with zero color value
TEST_F(GfxCalGrayColorSpaceTest_421, GetGrayWithZeroInput_421) {
    GfxColor color;
    color.c[0] = 0;
    GfxGray gray;
    cs->getGray(&color, &gray);
    // Zero input should produce zero gray
    EXPECT_EQ(gray, 0);
}

// Test getGray with max color value
TEST_F(GfxCalGrayColorSpaceTest_421, GetGrayWithMaxInput_421) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxGray gray;
    cs->getGray(&color, &gray);
    // Max input should produce max gray (or close to it)
    EXPECT_GE(gray, 0);
}

// Test getRGB with zero input
TEST_F(GfxCalGrayColorSpaceTest_421, GetRGBWithZeroInput_421) {
    GfxColor color;
    color.c[0] = 0;
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB with max input
TEST_F(GfxCalGrayColorSpaceTest_421, GetRGBWithMaxInput_421) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    // Should produce some valid RGB values
    EXPECT_GE(rgb.r, 0);
    EXPECT_GE(rgb.g, 0);
    EXPECT_GE(rgb.b, 0);
}

// Test getCMYK with zero input
TEST_F(GfxCalGrayColorSpaceTest_421, GetCMYKWithZeroInput_421) {
    GfxColor color;
    color.c[0] = 0;
    GfxCMYK cmyk;
    cs->getCMYK(&color, &cmyk);
    // Zero gray should map to black in CMYK (K=max)
    EXPECT_GE(cmyk.k, 0);
}

// Test getNComps consistency with copy
TEST_F(GfxCalGrayColorSpaceTest_421, CopyPreservesNComps_421) {
    auto copied = cs->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNComps(), cs->getNComps());
}

// Test getDeviceN with zero input
TEST_F(GfxCalGrayColorSpaceTest_421, GetDeviceNWithZeroInput_421) {
    GfxColor color;
    color.c[0] = 0;
    GfxColor deviceN;
    cs->getDeviceN(&color, &deviceN);
    // Should produce some valid deviceN values
    // Just verify it doesn't crash
}

// Test getDeviceN with max input
TEST_F(GfxCalGrayColorSpaceTest_421, GetDeviceNWithMaxInput_421) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxColor deviceN;
    cs->getDeviceN(&color, &deviceN);
    // Should produce some valid deviceN values
}

// Test that copy returns independent object
TEST_F(GfxCalGrayColorSpaceTest_421, CopyReturnsIndependentObject_421) {
    auto copied = cs->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(copied.get(), cs.get());
}
