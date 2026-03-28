#include <gtest/gtest.h>
#include "GfxState.h"

class GfxLabColorSpaceTest_448 : public ::testing::Test {
protected:
    void SetUp() override {
        labCS = std::make_unique<GfxLabColorSpace>();
    }

    std::unique_ptr<GfxLabColorSpace> labCS;
};

// Test that getNComps returns 3 for Lab color space
TEST_F(GfxLabColorSpaceTest_448, GetNCompsReturnsThree_448) {
    EXPECT_EQ(labCS->getNComps(), 3);
}

// Test that getMode returns the correct mode for Lab color space
TEST_F(GfxLabColorSpaceTest_448, GetModeReturnsLabMode_448) {
    EXPECT_EQ(labCS->getMode(), csLab);
}

// Test default constructor initializes white point values
TEST_F(GfxLabColorSpaceTest_448, DefaultConstructorWhitePoint_448) {
    // Default white point should be reasonable values (D65 or similar)
    double whiteX = labCS->getWhiteX();
    double whiteY = labCS->getWhiteY();
    double whiteZ = labCS->getWhiteZ();
    // White Y is typically 1.0 for normalized white point
    EXPECT_GE(whiteX, 0.0);
    EXPECT_GE(whiteY, 0.0);
    EXPECT_GE(whiteZ, 0.0);
}

// Test default constructor initializes black point values
TEST_F(GfxLabColorSpaceTest_448, DefaultConstructorBlackPoint_448) {
    double blackX = labCS->getBlackX();
    double blackY = labCS->getBlackY();
    double blackZ = labCS->getBlackZ();
    // Black point defaults are typically 0
    EXPECT_GE(blackX, 0.0);
    EXPECT_GE(blackY, 0.0);
    EXPECT_GE(blackZ, 0.0);
}

// Test default constructor initializes a/b range values
TEST_F(GfxLabColorSpaceTest_448, DefaultConstructorRanges_448) {
    double aMin = labCS->getAMin();
    double aMax = labCS->getAMax();
    double bMin = labCS->getBMin();
    double bMax = labCS->getBMax();
    // aMin should be <= aMax, bMin should be <= bMax
    EXPECT_LE(aMin, aMax);
    EXPECT_LE(bMin, bMax);
}

// Test copy creates a valid copy
TEST_F(GfxLabColorSpaceTest_448, CopyProducesValidCopy_448) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csLab);
    EXPECT_EQ(copied->getNComps(), 3);

    // Cast to GfxLabColorSpace to check specific properties
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_EQ(copiedLab->getWhiteX(), labCS->getWhiteX());
    EXPECT_EQ(copiedLab->getWhiteY(), labCS->getWhiteY());
    EXPECT_EQ(copiedLab->getWhiteZ(), labCS->getWhiteZ());
    EXPECT_EQ(copiedLab->getBlackX(), labCS->getBlackX());
    EXPECT_EQ(copiedLab->getBlackY(), labCS->getBlackY());
    EXPECT_EQ(copiedLab->getBlackZ(), labCS->getBlackZ());
    EXPECT_EQ(copiedLab->getAMin(), labCS->getAMin());
    EXPECT_EQ(copiedLab->getAMax(), labCS->getAMax());
    EXPECT_EQ(copiedLab->getBMin(), labCS->getBMin());
    EXPECT_EQ(copiedLab->getBMax(), labCS->getBMax());
}

// Test getDefaultColor produces a valid color
TEST_F(GfxLabColorSpaceTest_448, GetDefaultColorProducesValidColor_448) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    // Default color for Lab: L*=0, a*=0, b*=0 or within valid ranges
    // We just verify it doesn't crash and values are set
    // L* component should be between 0 and 1 (normalized)
    EXPECT_GE(colToDbl(color.c[0]), 0.0);
    EXPECT_LE(colToDbl(color.c[0]), 1.0);
}

// Test getGray with default color
TEST_F(GfxLabColorSpaceTest_448, GetGrayWithDefaultColor_448) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxGray gray;
    labCS->getGray(&color, &gray);
    // Gray value should be in valid range [0, 1]
    double grayVal = colToDbl(gray);
    EXPECT_GE(grayVal, 0.0);
    EXPECT_LE(grayVal, 1.0);
}

// Test getRGB with default color
TEST_F(GfxLabColorSpaceTest_448, GetRGBWithDefaultColor_448) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    // RGB values should be in valid range [0, 1]
    EXPECT_GE(colToDbl(rgb.r), 0.0);
    EXPECT_LE(colToDbl(rgb.r), 1.0);
    EXPECT_GE(colToDbl(rgb.g), 0.0);
    EXPECT_LE(colToDbl(rgb.g), 1.0);
    EXPECT_GE(colToDbl(rgb.b), 0.0);
    EXPECT_LE(colToDbl(rgb.b), 1.0);
}

// Test getCMYK with default color
TEST_F(GfxLabColorSpaceTest_448, GetCMYKWithDefaultColor_448) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxCMYK cmyk;
    labCS->getCMYK(&color, &cmyk);
    // CMYK values should be in valid range [0, 1]
    EXPECT_GE(colToDbl(cmyk.c), 0.0);
    EXPECT_LE(colToDbl(cmyk.c), 1.0);
    EXPECT_GE(colToDbl(cmyk.m), 0.0);
    EXPECT_LE(colToDbl(cmyk.m), 1.0);
    EXPECT_GE(colToDbl(cmyk.y), 0.0);
    EXPECT_LE(colToDbl(cmyk.y), 1.0);
    EXPECT_GE(colToDbl(cmyk.k), 0.0);
    EXPECT_LE(colToDbl(cmyk.k), 1.0);
}

// Test getDeviceN with default color
TEST_F(GfxLabColorSpaceTest_448, GetDeviceNWithDefaultColor_448) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxColor deviceN;
    labCS->getDeviceN(&color, &deviceN);
    // DeviceN output should have valid component values
    for (int i = 0; i < gfxColorMaxComps; i++) {
        EXPECT_GE(colToDbl(deviceN.c[i]), 0.0);
        EXPECT_LE(colToDbl(deviceN.c[i]), 1.0);
    }
}

// Test getDefaultRanges
TEST_F(GfxLabColorSpaceTest_448, GetDefaultRanges_448) {
    double decodeLow[3];
    double decodeRange[3];
    int maxImgPixel = 255;
    labCS->getDefaultRanges(decodeLow, decodeRange, maxImgPixel);
    // L* component: decode low should be 0, range should be 100
    EXPECT_DOUBLE_EQ(decodeLow[0], 0.0);
    EXPECT_DOUBLE_EQ(decodeRange[0], 100.0);
    // a* and b* components should use the aMin/aMax and bMin/bMax ranges
    double aMin = labCS->getAMin();
    double aMax = labCS->getAMax();
    double bMin = labCS->getBMin();
    double bMax = labCS->getBMax();
    EXPECT_DOUBLE_EQ(decodeLow[1], aMin);
    EXPECT_DOUBLE_EQ(decodeRange[1], aMax - aMin);
    EXPECT_DOUBLE_EQ(decodeLow[2], bMin);
    EXPECT_DOUBLE_EQ(decodeRange[2], bMax - bMin);
}

// Test with a color having maximum L* value
TEST_F(GfxLabColorSpaceTest_448, GetRGBWithMaxLightness_448) {
    GfxColor color;
    // Set L* to maximum (100 normalized to 1.0 in GfxColor)
    color.c[0] = dblToCol(1.0);  // L* = 100
    color.c[1] = dblToCol(0.5);  // a* midpoint
    color.c[2] = dblToCol(0.5);  // b* midpoint
    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    // Should produce valid RGB values
    EXPECT_GE(colToDbl(rgb.r), 0.0);
    EXPECT_LE(colToDbl(rgb.r), 1.0);
    EXPECT_GE(colToDbl(rgb.g), 0.0);
    EXPECT_LE(colToDbl(rgb.g), 1.0);
    EXPECT_GE(colToDbl(rgb.b), 0.0);
    EXPECT_LE(colToDbl(rgb.b), 1.0);
}

// Test with a color having minimum L* value (black)
TEST_F(GfxLabColorSpaceTest_448, GetRGBWithMinLightness_448) {
    GfxColor color;
    color.c[0] = dblToCol(0.0);  // L* = 0
    color.c[1] = dblToCol(0.5);  // a* midpoint
    color.c[2] = dblToCol(0.5);  // b* midpoint
    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    // With L*=0, the color should be very dark
    EXPECT_GE(colToDbl(rgb.r), 0.0);
    EXPECT_LE(colToDbl(rgb.r), 1.0);
    EXPECT_GE(colToDbl(rgb.g), 0.0);
    EXPECT_LE(colToDbl(rgb.g), 1.0);
    EXPECT_GE(colToDbl(rgb.b), 0.0);
    EXPECT_LE(colToDbl(rgb.b), 1.0);
}

// Test that copy is independent of the original
TEST_F(GfxLabColorSpaceTest_448, CopyIsIndependent_448) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    // Destroying original should not affect copy
    labCS.reset();
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_EQ(copiedLab->getNComps(), 3);
    EXPECT_EQ(copiedLab->getMode(), csLab);
}

// Test getGray with zero color (all components 0)
TEST_F(GfxLabColorSpaceTest_448, GetGrayWithZeroColor_448) {
    GfxColor color;
    color.c[0] = dblToCol(0.0);
    color.c[1] = dblToCol(0.0);
    color.c[2] = dblToCol(0.0);
    GfxGray gray;
    labCS->getGray(&color, &gray);
    double grayVal = colToDbl(gray);
    EXPECT_GE(grayVal, 0.0);
    EXPECT_LE(grayVal, 1.0);
}

// Test getGray with maximum color (all components 1)
TEST_F(GfxLabColorSpaceTest_448, GetGrayWithMaxColor_448) {
    GfxColor color;
    color.c[0] = dblToCol(1.0);
    color.c[1] = dblToCol(1.0);
    color.c[2] = dblToCol(1.0);
    GfxGray gray;
    labCS->getGray(&color, &gray);
    double grayVal = colToDbl(gray);
    EXPECT_GE(grayVal, 0.0);
    EXPECT_LE(grayVal, 1.0);
}
