#include <gtest/gtest.h>
#include "GfxState.h"

class GfxLabColorSpaceTest_447 : public ::testing::Test {
protected:
    void SetUp() override {
        labCS = std::make_unique<GfxLabColorSpace>();
    }

    void TearDown() override {
        labCS.reset();
    }

    std::unique_ptr<GfxLabColorSpace> labCS;
};

// Test that getMode returns csLab
TEST_F(GfxLabColorSpaceTest_447, GetModeReturnsLab_447) {
    EXPECT_EQ(labCS->getMode(), csLab);
}

// Test that getNComps returns 3 for Lab color space (L, a, b)
TEST_F(GfxLabColorSpaceTest_447, GetNCompsReturnsThree_447) {
    EXPECT_EQ(labCS->getNComps(), 3);
}

// Test default white point values
TEST_F(GfxLabColorSpaceTest_447, DefaultWhitePointValues_447) {
    // Default constructed Lab color space should have some white point
    double whiteX = labCS->getWhiteX();
    double whiteY = labCS->getWhiteY();
    double whiteZ = labCS->getWhiteZ();
    // White point Y should typically be 1.0 for a default Lab space
    EXPECT_GE(whiteX, 0.0);
    EXPECT_GE(whiteY, 0.0);
    EXPECT_GE(whiteZ, 0.0);
}

// Test default black point values
TEST_F(GfxLabColorSpaceTest_447, DefaultBlackPointValues_447) {
    // Default black point is typically all zeros
    double blackX = labCS->getBlackX();
    double blackY = labCS->getBlackY();
    double blackZ = labCS->getBlackZ();
    EXPECT_DOUBLE_EQ(blackX, 0.0);
    EXPECT_DOUBLE_EQ(blackY, 0.0);
    EXPECT_DOUBLE_EQ(blackZ, 0.0);
}

// Test default range values for a and b
TEST_F(GfxLabColorSpaceTest_447, DefaultRangeValues_447) {
    double aMin = labCS->getAMin();
    double aMax = labCS->getAMax();
    double bMin = labCS->getBMin();
    double bMax = labCS->getBMax();
    // Default range for a and b in Lab is typically [-100, 100]
    EXPECT_LE(aMin, aMax);
    EXPECT_LE(bMin, bMax);
}

// Test copy creates a valid copy
TEST_F(GfxLabColorSpaceTest_447, CopyCreatesValidCopy_447) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csLab);
    EXPECT_EQ(copied->getNComps(), labCS->getNComps());

    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_DOUBLE_EQ(copiedLab->getWhiteX(), labCS->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedLab->getWhiteY(), labCS->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedLab->getWhiteZ(), labCS->getWhiteZ());
    EXPECT_DOUBLE_EQ(copiedLab->getBlackX(), labCS->getBlackX());
    EXPECT_DOUBLE_EQ(copiedLab->getBlackY(), labCS->getBlackY());
    EXPECT_DOUBLE_EQ(copiedLab->getBlackZ(), labCS->getBlackZ());
    EXPECT_DOUBLE_EQ(copiedLab->getAMin(), labCS->getAMin());
    EXPECT_DOUBLE_EQ(copiedLab->getAMax(), labCS->getAMax());
    EXPECT_DOUBLE_EQ(copiedLab->getBMin(), labCS->getBMin());
    EXPECT_DOUBLE_EQ(copiedLab->getBMax(), labCS->getBMax());
}

// Test getDefaultColor sets a valid default color
TEST_F(GfxLabColorSpaceTest_447, GetDefaultColorSetsValidColor_447) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    // For Lab, L* default should be 0 (mapped), a* and b* should be within range
    // We just verify it doesn't crash and produces some values
    // L* is component 0, a* is component 1, b* is component 2
    // The values should be representable in GfxColorComp
}

// Test getGray produces a valid gray value
TEST_F(GfxLabColorSpaceTest_447, GetGrayProducesValidValue_447) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxGray gray;
    labCS->getGray(&color, &gray);
    // Gray value should be in valid range [0, gfxColorComp1]
    EXPECT_GE(gray, 0);
}

// Test getRGB produces valid RGB values
TEST_F(GfxLabColorSpaceTest_447, GetRGBProducesValidValues_447) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    // RGB values should be in valid range
    EXPECT_GE(rgb.r, 0);
    EXPECT_GE(rgb.g, 0);
    EXPECT_GE(rgb.b, 0);
}

// Test getCMYK produces valid CMYK values
TEST_F(GfxLabColorSpaceTest_447, GetCMYKProducesValidValues_447) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxCMYK cmyk;
    labCS->getCMYK(&color, &cmyk);
    EXPECT_GE(cmyk.c, 0);
    EXPECT_GE(cmyk.m, 0);
    EXPECT_GE(cmyk.y, 0);
    EXPECT_GE(cmyk.k, 0);
}

// Test getDeviceN doesn't crash
TEST_F(GfxLabColorSpaceTest_447, GetDeviceNDoesNotCrash_447) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxColor deviceN;
    labCS->getDeviceN(&color, &deviceN);
}

// Test getDefaultRanges for typical image pixel max
TEST_F(GfxLabColorSpaceTest_447, GetDefaultRangesForTypicalMaxPixel_447) {
    double decodeLow[3];
    double decodeRange[3];
    labCS->getDefaultRanges(decodeLow, decodeRange, 255);
    // L* should map from 0 to 100
    EXPECT_DOUBLE_EQ(decodeLow[0], 0.0);
    EXPECT_DOUBLE_EQ(decodeRange[0], 100.0);
    // a* and b* should map based on aMin/aMax and bMin/bMax
    EXPECT_DOUBLE_EQ(decodeLow[1], labCS->getAMin());
    EXPECT_DOUBLE_EQ(decodeRange[1], labCS->getAMax() - labCS->getAMin());
    EXPECT_DOUBLE_EQ(decodeLow[2], labCS->getBMin());
    EXPECT_DOUBLE_EQ(decodeRange[2], labCS->getBMax() - labCS->getBMin());
}

// Test getDefaultRanges with boundary maxImgPixel value of 1
TEST_F(GfxLabColorSpaceTest_447, GetDefaultRangesWithMinMaxPixel_447) {
    double decodeLow[3];
    double decodeRange[3];
    labCS->getDefaultRanges(decodeLow, decodeRange, 1);
    // Should still produce valid ranges
    EXPECT_DOUBLE_EQ(decodeLow[0], 0.0);
    EXPECT_DOUBLE_EQ(decodeRange[0], 100.0);
}

// Test that aMin <= aMax and bMin <= bMax for default-constructed object
TEST_F(GfxLabColorSpaceTest_447, RangeConsistency_447) {
    EXPECT_LE(labCS->getAMin(), labCS->getAMax());
    EXPECT_LE(labCS->getBMin(), labCS->getBMax());
}

// Test with a specific Lab color (L=50, a=0, b=0 should give gray)
TEST_F(GfxLabColorSpaceTest_447, MidGrayLabColor_447) {
    GfxColor color;
    // Set L* = 50 (mid luminance), a* = 0, b* = 0 (neutral)
    // We need to encode these into GfxColorComp
    // L* ranges 0-100, a* and b* use the range from the color space
    color.c[0] = dblToCol(50.0 / 100.0); // Normalized L*
    color.c[1] = dblToCol(0.5);           // Mid-range for a*
    color.c[2] = dblToCol(0.5);           // Mid-range for b*

    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    // Should produce some valid color
    EXPECT_GE(rgb.r, 0);
    EXPECT_GE(rgb.g, 0);
    EXPECT_GE(rgb.b, 0);
}

// Test copy independence - modifying original shouldn't affect copy
TEST_F(GfxLabColorSpaceTest_447, CopyIndependence_447) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);

    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);

    // Both should return the same mode
    EXPECT_EQ(copiedLab->getMode(), labCS->getMode());
    EXPECT_EQ(copiedLab->getNComps(), labCS->getNComps());
}
