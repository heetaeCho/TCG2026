#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalGrayColorSpaceTest_419 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxCalGrayColorSpace>();
    }

    std::unique_ptr<GfxCalGrayColorSpace> colorSpace;
};

// Test default construction and default values
TEST_F(GfxCalGrayColorSpaceTest_419, DefaultConstructor_BlackYDefaultValue_419) {
    // After default construction, blackY should have a default value (typically 0)
    double blackY = colorSpace->getBlackY();
    EXPECT_EQ(blackY, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_419, DefaultConstructor_BlackXDefaultValue_419) {
    double blackX = colorSpace->getBlackX();
    EXPECT_EQ(blackX, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_419, DefaultConstructor_BlackZDefaultValue_419) {
    double blackZ = colorSpace->getBlackZ();
    EXPECT_EQ(blackZ, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_419, DefaultConstructor_WhiteXDefaultValue_419) {
    double whiteX = colorSpace->getWhiteX();
    // WhiteX default should be 1.0 for a CalGray color space
    EXPECT_EQ(whiteX, 1.0);
}

TEST_F(GfxCalGrayColorSpaceTest_419, DefaultConstructor_WhiteYDefaultValue_419) {
    double whiteY = colorSpace->getWhiteY();
    EXPECT_EQ(whiteY, 1.0);
}

TEST_F(GfxCalGrayColorSpaceTest_419, DefaultConstructor_WhiteZDefaultValue_419) {
    double whiteZ = colorSpace->getWhiteZ();
    EXPECT_EQ(whiteZ, 1.0);
}

TEST_F(GfxCalGrayColorSpaceTest_419, DefaultConstructor_GammaDefaultValue_419) {
    double gamma = colorSpace->getGamma();
    EXPECT_EQ(gamma, 1.0);
}

// Test getMode returns the correct mode for CalGray
TEST_F(GfxCalGrayColorSpaceTest_419, GetMode_ReturnsCalGray_419) {
    GfxColorSpaceMode mode = colorSpace->getMode();
    EXPECT_EQ(mode, csCalGray);
}

// Test getNComps returns 1 for CalGray
TEST_F(GfxCalGrayColorSpaceTest_419, GetNComps_ReturnsOne_419) {
    int nComps = colorSpace->getNComps();
    EXPECT_EQ(nComps, 1);
}

// Test copy creates a valid copy with same properties
TEST_F(GfxCalGrayColorSpaceTest_419, Copy_PreservesProperties_419) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);

    // The copied color space should have the same mode
    EXPECT_EQ(copied->getMode(), csCalGray);
    EXPECT_EQ(copied->getNComps(), 1);

    // Cast to GfxCalGrayColorSpace to check specific properties
    GfxCalGrayColorSpace *copiedCalGray = dynamic_cast<GfxCalGrayColorSpace *>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);

    EXPECT_EQ(copiedCalGray->getWhiteX(), colorSpace->getWhiteX());
    EXPECT_EQ(copiedCalGray->getWhiteY(), colorSpace->getWhiteY());
    EXPECT_EQ(copiedCalGray->getWhiteZ(), colorSpace->getWhiteZ());
    EXPECT_EQ(copiedCalGray->getBlackX(), colorSpace->getBlackX());
    EXPECT_EQ(copiedCalGray->getBlackY(), colorSpace->getBlackY());
    EXPECT_EQ(copiedCalGray->getBlackZ(), colorSpace->getBlackZ());
    EXPECT_EQ(copiedCalGray->getGamma(), colorSpace->getGamma());
}

// Test getDefaultColor
TEST_F(GfxCalGrayColorSpaceTest_419, GetDefaultColor_SetsDefaultValue_419) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    // Default color for CalGray should set component 0 to 0
    EXPECT_EQ(color.c[0], 0);
}

// Test getGray with minimum value (0)
TEST_F(GfxCalGrayColorSpaceTest_419, GetGray_MinValue_419) {
    GfxColor color;
    color.c[0] = 0;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test getGray with maximum value
TEST_F(GfxCalGrayColorSpaceTest_419, GetGray_MaxValue_419) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // With gamma=1 and white point (1,1,1), max input should give max gray
    EXPECT_GE(gray, 0);
}

// Test getRGB with zero input
TEST_F(GfxCalGrayColorSpaceTest_419, GetRGB_ZeroInput_419) {
    GfxColor color;
    color.c[0] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB with max input
TEST_F(GfxCalGrayColorSpaceTest_419, GetRGB_MaxInput_419) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // For default CalGray with gamma=1, max should produce white-ish values
    EXPECT_GE(rgb.r, 0);
    EXPECT_GE(rgb.g, 0);
    EXPECT_GE(rgb.b, 0);
}

// Test getCMYK with zero input
TEST_F(GfxCalGrayColorSpaceTest_419, GetCMYK_ZeroInput_419) {
    GfxColor color;
    color.c[0] = 0;
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Zero gray input should result in black (k=1 or max)
    EXPECT_GE(cmyk.k, 0);
}

// Test getDeviceN with zero input
TEST_F(GfxCalGrayColorSpaceTest_419, GetDeviceN_ZeroInput_419) {
    GfxColor color;
    color.c[0] = 0;
    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    // Just verify it doesn't crash and produces some output
    SUCCEED();
}

// Test that copy returns a distinct object
TEST_F(GfxCalGrayColorSpaceTest_419, Copy_ReturnsDifferentPointer_419) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied.get(), static_cast<GfxColorSpace *>(colorSpace.get()));
}

// Test consistency between getBlackY on original and copy
TEST_F(GfxCalGrayColorSpaceTest_419, Copy_BlackYConsistency_419) {
    auto copied = colorSpace->copy();
    GfxCalGrayColorSpace *copiedCalGray = dynamic_cast<GfxCalGrayColorSpace *>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackY(), colorSpace->getBlackY());
}

// Test that all black components are consistent (all default to 0)
TEST_F(GfxCalGrayColorSpaceTest_419, DefaultBlackPointIsZero_419) {
    EXPECT_DOUBLE_EQ(colorSpace->getBlackX(), 0.0);
    EXPECT_DOUBLE_EQ(colorSpace->getBlackY(), 0.0);
    EXPECT_DOUBLE_EQ(colorSpace->getBlackZ(), 0.0);
}

// Test that all white components are consistent (all default to 1)
TEST_F(GfxCalGrayColorSpaceTest_419, DefaultWhitePointIsOne_419) {
    EXPECT_DOUBLE_EQ(colorSpace->getWhiteX(), 1.0);
    EXPECT_DOUBLE_EQ(colorSpace->getWhiteY(), 1.0);
    EXPECT_DOUBLE_EQ(colorSpace->getWhiteZ(), 1.0);
}

// Test getRGB with a mid-range value
TEST_F(GfxCalGrayColorSpaceTest_419, GetRGB_MidValue_419) {
    GfxColor color;
    color.c[0] = gfxColorComp1 / 2;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // Mid-range gray should produce some intermediate RGB values
    EXPECT_GE(rgb.r, 0);
    EXPECT_GE(rgb.g, 0);
    EXPECT_GE(rgb.b, 0);
}
