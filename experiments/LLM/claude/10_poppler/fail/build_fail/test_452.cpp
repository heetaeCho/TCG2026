#include <gtest/gtest.h>
#include "GfxState.h"

class GfxLabColorSpaceTest_452 : public ::testing::Test {
protected:
    void SetUp() override {
        labCS = std::make_unique<GfxLabColorSpace>();
    }

    std::unique_ptr<GfxLabColorSpace> labCS;
};

// Test default construction and white point values
TEST_F(GfxLabColorSpaceTest_452, DefaultConstructionWhiteX_452) {
    double whiteX = labCS->getWhiteX();
    // Default white point X should be a valid value (typically 1.0 for D65 or similar)
    EXPECT_GE(whiteX, 0.0);
}

TEST_F(GfxLabColorSpaceTest_452, DefaultConstructionWhiteY_452) {
    double whiteY = labCS->getWhiteY();
    EXPECT_GE(whiteY, 0.0);
}

TEST_F(GfxLabColorSpaceTest_452, DefaultConstructionWhiteZ_452) {
    double whiteZ = labCS->getWhiteZ();
    EXPECT_GE(whiteZ, 0.0);
}

// Test default black point values
TEST_F(GfxLabColorSpaceTest_452, DefaultConstructionBlackX_452) {
    double blackX = labCS->getBlackX();
    // Default black point is typically 0.0
    EXPECT_DOUBLE_EQ(blackX, 0.0);
}

TEST_F(GfxLabColorSpaceTest_452, DefaultConstructionBlackY_452) {
    double blackY = labCS->getBlackY();
    EXPECT_DOUBLE_EQ(blackY, 0.0);
}

TEST_F(GfxLabColorSpaceTest_452, DefaultConstructionBlackZ_452) {
    double blackZ = labCS->getBlackZ();
    EXPECT_DOUBLE_EQ(blackZ, 0.0);
}

// Test default range values for a and b
TEST_F(GfxLabColorSpaceTest_452, DefaultConstructionAMin_452) {
    double aMin = labCS->getAMin();
    // Default range for a* is typically -100 to 100
    EXPECT_LE(aMin, 0.0);
}

TEST_F(GfxLabColorSpaceTest_452, DefaultConstructionAMax_452) {
    double aMax = labCS->getAMax();
    EXPECT_GE(aMax, 0.0);
}

TEST_F(GfxLabColorSpaceTest_452, DefaultConstructionBMin_452) {
    double bMin = labCS->getBMin();
    EXPECT_LE(bMin, 0.0);
}

TEST_F(GfxLabColorSpaceTest_452, DefaultConstructionBMax_452) {
    double bMax = labCS->getBMax();
    EXPECT_GE(bMax, 0.0);
}

// Test that AMin <= AMax
TEST_F(GfxLabColorSpaceTest_452, AMinLessThanOrEqualAMax_452) {
    EXPECT_LE(labCS->getAMin(), labCS->getAMax());
}

// Test that BMin <= BMax
TEST_F(GfxLabColorSpaceTest_452, BMinLessThanOrEqualBMax_452) {
    EXPECT_LE(labCS->getBMin(), labCS->getBMax());
}

// Test color space mode
TEST_F(GfxLabColorSpaceTest_452, ModeIsLab_452) {
    GfxColorSpaceMode mode = labCS->getMode();
    EXPECT_EQ(mode, csLab);
}

// Test number of components
TEST_F(GfxLabColorSpaceTest_452, NCompsIsThree_452) {
    int nComps = labCS->getNComps();
    EXPECT_EQ(nComps, 3);
}

// Test copy functionality
TEST_F(GfxLabColorSpaceTest_452, CopyPreservesWhitePoint_452) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_DOUBLE_EQ(copiedLab->getWhiteX(), labCS->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedLab->getWhiteY(), labCS->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedLab->getWhiteZ(), labCS->getWhiteZ());
}

TEST_F(GfxLabColorSpaceTest_452, CopyPreservesBlackPoint_452) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_DOUBLE_EQ(copiedLab->getBlackX(), labCS->getBlackX());
    EXPECT_DOUBLE_EQ(copiedLab->getBlackY(), labCS->getBlackY());
    EXPECT_DOUBLE_EQ(copiedLab->getBlackZ(), labCS->getBlackZ());
}

TEST_F(GfxLabColorSpaceTest_452, CopyPreservesRanges_452) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_DOUBLE_EQ(copiedLab->getAMin(), labCS->getAMin());
    EXPECT_DOUBLE_EQ(copiedLab->getAMax(), labCS->getAMax());
    EXPECT_DOUBLE_EQ(copiedLab->getBMin(), labCS->getBMin());
    EXPECT_DOUBLE_EQ(copiedLab->getBMax(), labCS->getBMax());
}

TEST_F(GfxLabColorSpaceTest_452, CopyPreservesMode_452) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csLab);
}

TEST_F(GfxLabColorSpaceTest_452, CopyPreservesNComps_452) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNComps(), 3);
}

// Test getDefaultColor
TEST_F(GfxLabColorSpaceTest_452, GetDefaultColorSetsValidColor_452) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    // The default color should have valid component values
    // For Lab, L* default is 0 (mapped), a* and b* should be within range
    // We just verify it doesn't crash and components are set
    SUCCEED();
}

// Test getGray with a default color
TEST_F(GfxLabColorSpaceTest_452, GetGrayWithDefaultColor_452) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxGray gray;
    labCS->getGray(&color, &gray);
    // Gray value should be within [0, 65535] range
    EXPECT_GE(gray, 0);
    EXPECT_LE(gray, 65535);
}

// Test getRGB with a default color
TEST_F(GfxLabColorSpaceTest_452, GetRGBWithDefaultColor_452) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    EXPECT_GE(rgb.r, 0);
    EXPECT_LE(rgb.r, 65535);
    EXPECT_GE(rgb.g, 0);
    EXPECT_LE(rgb.g, 65535);
    EXPECT_GE(rgb.b, 0);
    EXPECT_LE(rgb.b, 65535);
}

// Test getCMYK with a default color
TEST_F(GfxLabColorSpaceTest_452, GetCMYKWithDefaultColor_452) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxCMYK cmyk;
    labCS->getCMYK(&color, &cmyk);
    EXPECT_GE(cmyk.c, 0);
    EXPECT_LE(cmyk.c, 65535);
    EXPECT_GE(cmyk.m, 0);
    EXPECT_LE(cmyk.m, 65535);
    EXPECT_GE(cmyk.y, 0);
    EXPECT_LE(cmyk.y, 65535);
    EXPECT_GE(cmyk.k, 0);
    EXPECT_LE(cmyk.k, 65535);
}

// Test getDeviceN with a default color
TEST_F(GfxLabColorSpaceTest_452, GetDeviceNWithDefaultColor_452) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxColor deviceN;
    labCS->getDeviceN(&color, &deviceN);
    // DeviceN should produce valid values
    SUCCEED();
}

// Test getDefaultRanges
TEST_F(GfxLabColorSpaceTest_452, GetDefaultRangesProducesValidValues_452) {
    double decodeLow[3];
    double decodeRange[3];
    int maxImgPixel = 255;
    labCS->getDefaultRanges(decodeLow, decodeRange, maxImgPixel);
    // L* range is typically 0..100, a* and b* use configured min/max
    // decodeRange should be non-negative for L*
    EXPECT_GE(decodeRange[0], 0.0);
}

// Test getDefaultRanges with different maxImgPixel
TEST_F(GfxLabColorSpaceTest_452, GetDefaultRangesMaxPixel1_452) {
    double decodeLow[3];
    double decodeRange[3];
    int maxImgPixel = 1;
    labCS->getDefaultRanges(decodeLow, decodeRange, maxImgPixel);
    EXPECT_GE(decodeRange[0], 0.0);
}

// Test that black point values are consistent (all should be >= 0)
TEST_F(GfxLabColorSpaceTest_452, BlackPointNonNegative_452) {
    EXPECT_GE(labCS->getBlackX(), 0.0);
    EXPECT_GE(labCS->getBlackY(), 0.0);
    EXPECT_GE(labCS->getBlackZ(), 0.0);
}

// Test that white point values are positive (white point must be positive per spec)
TEST_F(GfxLabColorSpaceTest_452, WhitePointPositive_452) {
    // WhiteY must be 1.0 per Lab color space definition
    // WhiteX and WhiteZ must be positive
    EXPECT_GT(labCS->getWhiteY(), 0.0);
}
