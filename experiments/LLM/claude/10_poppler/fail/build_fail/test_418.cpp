#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalGrayColorSpaceTest_418 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxCalGrayColorSpace>();
    }

    std::unique_ptr<GfxCalGrayColorSpace> colorSpace;
};

// Test default construction and getBlackX
TEST_F(GfxCalGrayColorSpaceTest_418, DefaultBlackX_418) {
    double blackX = colorSpace->getBlackX();
    EXPECT_DOUBLE_EQ(blackX, 0.0);
}

// Test default construction and getBlackY
TEST_F(GfxCalGrayColorSpaceTest_418, DefaultBlackY_418) {
    double blackY = colorSpace->getBlackY();
    EXPECT_DOUBLE_EQ(blackY, 0.0);
}

// Test default construction and getBlackZ
TEST_F(GfxCalGrayColorSpaceTest_418, DefaultBlackZ_418) {
    double blackZ = colorSpace->getBlackZ();
    EXPECT_DOUBLE_EQ(blackZ, 0.0);
}

// Test default construction and getWhiteX
TEST_F(GfxCalGrayColorSpaceTest_418, DefaultWhiteX_418) {
    double whiteX = colorSpace->getWhiteX();
    // White point default is typically 1.0 for X (D65 or similar), but depends on implementation
    // We just verify it returns a value without crashing
    EXPECT_GE(whiteX, 0.0);
}

// Test default construction and getWhiteY
TEST_F(GfxCalGrayColorSpaceTest_418, DefaultWhiteY_418) {
    double whiteY = colorSpace->getWhiteY();
    EXPECT_GE(whiteY, 0.0);
}

// Test default construction and getWhiteZ
TEST_F(GfxCalGrayColorSpaceTest_418, DefaultWhiteZ_418) {
    double whiteZ = colorSpace->getWhiteZ();
    EXPECT_GE(whiteZ, 0.0);
}

// Test default gamma value
TEST_F(GfxCalGrayColorSpaceTest_418, DefaultGamma_418) {
    double gamma = colorSpace->getGamma();
    // Default gamma is typically 1.0
    EXPECT_DOUBLE_EQ(gamma, 1.0);
}

// Test getMode returns csCalGray
TEST_F(GfxCalGrayColorSpaceTest_418, GetModeReturnsCalGray_418) {
    GfxColorSpaceMode mode = colorSpace->getMode();
    EXPECT_EQ(mode, csCalGray);
}

// Test getNComps returns 1 for gray
TEST_F(GfxCalGrayColorSpaceTest_418, GetNCompsReturnsOne_418) {
    int nComps = colorSpace->getNComps();
    EXPECT_EQ(nComps, 1);
}

// Test copy produces a valid copy
TEST_F(GfxCalGrayColorSpaceTest_418, CopyProducesValidCopy_418) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csCalGray);
    EXPECT_EQ(copied->getNComps(), 1);
}

// Test that copy preserves black point values
TEST_F(GfxCalGrayColorSpaceTest_418, CopyPreservesBlackPoint_418) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    GfxCalGrayColorSpace* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackX(), colorSpace->getBlackX());
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackY(), colorSpace->getBlackY());
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackZ(), colorSpace->getBlackZ());
}

// Test that copy preserves white point values
TEST_F(GfxCalGrayColorSpaceTest_418, CopyPreservesWhitePoint_418) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    GfxCalGrayColorSpace* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteX(), colorSpace->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteY(), colorSpace->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteZ(), colorSpace->getWhiteZ());
}

// Test that copy preserves gamma
TEST_F(GfxCalGrayColorSpaceTest_418, CopyPreservesGamma_418) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    GfxCalGrayColorSpace* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalGray->getGamma(), colorSpace->getGamma());
}

// Test getDefaultColor sets color component to 0
TEST_F(GfxCalGrayColorSpaceTest_418, GetDefaultColor_418) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    // Default color for CalGray should be 0 (black)
    EXPECT_EQ(color.c[0], 0);
}

// Test getGray with a zero color
TEST_F(GfxCalGrayColorSpaceTest_418, GetGrayWithZeroColor_418) {
    GfxColor color;
    color.c[0] = 0;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getGray with max color value
TEST_F(GfxCalGrayColorSpaceTest_418, GetGrayWithMaxColor_418) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // Max input should produce max (or near max) gray
    EXPECT_GT(gray, 0);
}

// Test getRGB with zero color
TEST_F(GfxCalGrayColorSpaceTest_418, GetRGBWithZeroColor_418) {
    GfxColor color;
    color.c[0] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB with max color value
TEST_F(GfxCalGrayColorSpaceTest_418, GetRGBWithMaxColor_418) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // For a gray color space, R, G, B should be similar/equal
    EXPECT_GT(rgb.r, 0);
    EXPECT_GT(rgb.g, 0);
    EXPECT_GT(rgb.b, 0);
}

// Test getCMYK with zero color
TEST_F(GfxCalGrayColorSpaceTest_418, GetCMYKWithZeroColor_418) {
    GfxColor color;
    color.c[0] = 0;
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Zero gray should map to some CMYK representation of black
    // Typically K=1 for black, but exact values depend on implementation
    (void)cmyk; // Just verify no crash
}

// Test getDeviceN with zero color
TEST_F(GfxCalGrayColorSpaceTest_418, GetDeviceNWithZeroColor_418) {
    GfxColor color;
    color.c[0] = 0;
    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    // Just verify no crash
    (void)deviceN;
}

// Test getDeviceN with max color
TEST_F(GfxCalGrayColorSpaceTest_418, GetDeviceNWithMaxColor_418) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    // Just verify no crash
    (void)deviceN;
}

// Test that all black point values are consistent as zero by default
TEST_F(GfxCalGrayColorSpaceTest_418, AllBlackPointDefaultsZero_418) {
    EXPECT_DOUBLE_EQ(colorSpace->getBlackX(), 0.0);
    EXPECT_DOUBLE_EQ(colorSpace->getBlackY(), 0.0);
    EXPECT_DOUBLE_EQ(colorSpace->getBlackZ(), 0.0);
}

// Test getRGB with mid-range color
TEST_F(GfxCalGrayColorSpaceTest_418, GetRGBWithMidColor_418) {
    GfxColor color;
    color.c[0] = gfxColorComp1 / 2;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // Mid-range gray: R, G, B should be roughly equal and in mid range
    EXPECT_GT(rgb.r, 0);
    EXPECT_GT(rgb.g, 0);
    EXPECT_GT(rgb.b, 0);
    EXPECT_LT(rgb.r, gfxColorComp1);
    EXPECT_LT(rgb.g, gfxColorComp1);
    EXPECT_LT(rgb.b, gfxColorComp1);
}
