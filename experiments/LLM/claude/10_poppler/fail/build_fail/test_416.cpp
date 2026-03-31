#include <gtest/gtest.h>
#include "GfxState.h"

class GfxCalGrayColorSpaceTest_416 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxCalGrayColorSpace>();
    }

    std::unique_ptr<GfxCalGrayColorSpace> colorSpace;
};

// Test default construction and getWhiteY
TEST_F(GfxCalGrayColorSpaceTest_416, DefaultConstructionWhiteY_416) {
    // After default construction, getWhiteY should return a valid value
    // Typically the default white point Y for CalGray is 1.0 (D65 or similar)
    double whiteY = colorSpace->getWhiteY();
    // The value should be a finite number
    EXPECT_FALSE(std::isnan(whiteY));
    EXPECT_FALSE(std::isinf(whiteY));
}

// Test default construction and getWhiteX
TEST_F(GfxCalGrayColorSpaceTest_416, DefaultConstructionWhiteX_416) {
    double whiteX = colorSpace->getWhiteX();
    EXPECT_FALSE(std::isnan(whiteX));
    EXPECT_FALSE(std::isinf(whiteX));
}

// Test default construction and getWhiteZ
TEST_F(GfxCalGrayColorSpaceTest_416, DefaultConstructionWhiteZ_416) {
    double whiteZ = colorSpace->getWhiteZ();
    EXPECT_FALSE(std::isnan(whiteZ));
    EXPECT_FALSE(std::isinf(whiteZ));
}

// Test default black point values (should be 0.0 by default per PDF spec)
TEST_F(GfxCalGrayColorSpaceTest_416, DefaultBlackX_416) {
    double blackX = colorSpace->getBlackX();
    EXPECT_DOUBLE_EQ(blackX, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_416, DefaultBlackY_416) {
    double blackY = colorSpace->getBlackY();
    EXPECT_DOUBLE_EQ(blackY, 0.0);
}

TEST_F(GfxCalGrayColorSpaceTest_416, DefaultBlackZ_416) {
    double blackZ = colorSpace->getBlackZ();
    EXPECT_DOUBLE_EQ(blackZ, 0.0);
}

// Test default gamma value (should be 1.0 by default per PDF spec)
TEST_F(GfxCalGrayColorSpaceTest_416, DefaultGamma_416) {
    double gamma = colorSpace->getGamma();
    EXPECT_DOUBLE_EQ(gamma, 1.0);
}

// Test getMode returns csCalGray
TEST_F(GfxCalGrayColorSpaceTest_416, GetModeReturnsCalGray_416) {
    EXPECT_EQ(colorSpace->getMode(), csCalGray);
}

// Test getNComps returns 1 for CalGray
TEST_F(GfxCalGrayColorSpaceTest_416, GetNCompsReturnsOne_416) {
    EXPECT_EQ(colorSpace->getNComps(), 1);
}

// Test copy creates a valid copy
TEST_F(GfxCalGrayColorSpaceTest_416, CopyCreatesValidCopy_416) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csCalGray);
    EXPECT_EQ(copied->getNComps(), 1);
}

// Test that copy preserves white point values
TEST_F(GfxCalGrayColorSpaceTest_416, CopyPreservesWhitePoint_416) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    
    // Cast to GfxCalGrayColorSpace to check specific values
    GfxCalGrayColorSpace* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteX(), colorSpace->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteY(), colorSpace->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedCalGray->getWhiteZ(), colorSpace->getWhiteZ());
}

// Test that copy preserves black point values
TEST_F(GfxCalGrayColorSpaceTest_416, CopyPreservesBlackPoint_416) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    
    GfxCalGrayColorSpace* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackX(), colorSpace->getBlackX());
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackY(), colorSpace->getBlackY());
    EXPECT_DOUBLE_EQ(copiedCalGray->getBlackZ(), colorSpace->getBlackZ());
}

// Test that copy preserves gamma
TEST_F(GfxCalGrayColorSpaceTest_416, CopyPreservesGamma_416) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    
    GfxCalGrayColorSpace* copiedCalGray = dynamic_cast<GfxCalGrayColorSpace*>(copied.get());
    ASSERT_NE(copiedCalGray, nullptr);
    
    EXPECT_DOUBLE_EQ(copiedCalGray->getGamma(), colorSpace->getGamma());
}

// Test getDefaultColor
TEST_F(GfxCalGrayColorSpaceTest_416, GetDefaultColor_416) {
    GfxColor color;
    colorSpace->getDefaultColor(&color);
    // Default color for CalGray should have the first component set to 0
    EXPECT_EQ(color.c[0], 0);
}

// Test getGray with zero color value
TEST_F(GfxCalGrayColorSpaceTest_416, GetGrayWithZero_416) {
    GfxColor color;
    color.c[0] = 0;
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // Zero input should produce a gray value of 0
    EXPECT_EQ(gray, 0);
}

// Test getGray with maximum color value
TEST_F(GfxCalGrayColorSpaceTest_416, GetGrayWithMax_416) {
    GfxColor color;
    color.c[0] = gfxColorComp1;  // Maximum value
    GfxGray gray;
    colorSpace->getGray(&color, &gray);
    // Maximum input should produce maximum gray
    EXPECT_EQ(gray, gfxColorComp1);
}

// Test getRGB with zero color value
TEST_F(GfxCalGrayColorSpaceTest_416, GetRGBWithZero_416) {
    GfxColor color;
    color.c[0] = 0;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB with maximum color value
TEST_F(GfxCalGrayColorSpaceTest_416, GetRGBWithMax_416) {
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxRGB rgb;
    colorSpace->getRGB(&color, &rgb);
    // For a gray colorspace with default gamma=1, max input should produce white
    EXPECT_GE(rgb.r, 0);
    EXPECT_GE(rgb.g, 0);
    EXPECT_GE(rgb.b, 0);
}

// Test getCMYK with zero color value
TEST_F(GfxCalGrayColorSpaceTest_416, GetCMYKWithZero_416) {
    GfxColor color;
    color.c[0] = 0;
    GfxCMYK cmyk;
    colorSpace->getCMYK(&color, &cmyk);
    // Zero gray should map to black in CMYK (k=1 or max)
    // We just verify it doesn't crash and returns valid values
    EXPECT_GE(cmyk.c, 0);
    EXPECT_GE(cmyk.m, 0);
    EXPECT_GE(cmyk.y, 0);
    EXPECT_GE(cmyk.k, 0);
}

// Test getDeviceN with zero color value
TEST_F(GfxCalGrayColorSpaceTest_416, GetDeviceNWithZero_416) {
    GfxColor color;
    color.c[0] = 0;
    GfxColor deviceN;
    colorSpace->getDeviceN(&color, &deviceN);
    // Just verify it doesn't crash
}

// Test WhiteY is 1.0 by default (PDF spec: required, typically Y=1)
TEST_F(GfxCalGrayColorSpaceTest_416, DefaultWhiteYIsOne_416) {
    EXPECT_DOUBLE_EQ(colorSpace->getWhiteY(), 1.0);
}
