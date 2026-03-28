#include <gtest/gtest.h>
#include "GfxState.h"

class GfxLabColorSpaceTest_453 : public ::testing::Test {
protected:
    void SetUp() override {
        labCS = std::make_unique<GfxLabColorSpace>();
    }

    void TearDown() override {
        labCS.reset();
    }

    std::unique_ptr<GfxLabColorSpace> labCS;
};

// Test that default construction yields expected default values for black point
TEST_F(GfxLabColorSpaceTest_453, DefaultConstructionBlackY_453) {
    // The default black point Y should be 0 per PDF spec defaults
    EXPECT_DOUBLE_EQ(labCS->getBlackY(), 0.0);
}

TEST_F(GfxLabColorSpaceTest_453, DefaultConstructionBlackX_453) {
    EXPECT_DOUBLE_EQ(labCS->getBlackX(), 0.0);
}

TEST_F(GfxLabColorSpaceTest_453, DefaultConstructionBlackZ_453) {
    EXPECT_DOUBLE_EQ(labCS->getBlackZ(), 0.0);
}

// Test default white point values
TEST_F(GfxLabColorSpaceTest_453, DefaultConstructionWhiteX_453) {
    // White point must be set; default constructor may initialize to 1.0 or similar
    double whiteX = labCS->getWhiteX();
    // White X should be a non-negative value
    EXPECT_GE(whiteX, 0.0);
}

TEST_F(GfxLabColorSpaceTest_453, DefaultConstructionWhiteY_453) {
    double whiteY = labCS->getWhiteY();
    EXPECT_GE(whiteY, 0.0);
}

TEST_F(GfxLabColorSpaceTest_453, DefaultConstructionWhiteZ_453) {
    double whiteZ = labCS->getWhiteZ();
    EXPECT_GE(whiteZ, 0.0);
}

// Test default range values for a* and b*
TEST_F(GfxLabColorSpaceTest_453, DefaultARange_453) {
    double aMin = labCS->getAMin();
    double aMax = labCS->getAMax();
    // Default range for a* is [-100, 100] per PDF spec
    EXPECT_LE(aMin, aMax);
}

TEST_F(GfxLabColorSpaceTest_453, DefaultBRange_453) {
    double bMin = labCS->getBMin();
    double bMax = labCS->getBMax();
    // Default range for b* is [-100, 100] per PDF spec
    EXPECT_LE(bMin, bMax);
}

// Test color space mode
TEST_F(GfxLabColorSpaceTest_453, ModeIsLab_453) {
    EXPECT_EQ(labCS->getMode(), csLab);
}

// Test number of components
TEST_F(GfxLabColorSpaceTest_453, NCompsIsThree_453) {
    EXPECT_EQ(labCS->getNComps(), 3);
}

// Test copy produces a valid object with same properties
TEST_F(GfxLabColorSpaceTest_453, CopyPreservesProperties_453) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);

    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);

    EXPECT_EQ(copiedLab->getMode(), labCS->getMode());
    EXPECT_EQ(copiedLab->getNComps(), labCS->getNComps());
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

// Test getDefaultColor sets a valid color
TEST_F(GfxLabColorSpaceTest_453, GetDefaultColor_453) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    // Default color for Lab: L* = 0 (mapped), a* and b* clamped to range
    // Just verify it doesn't crash and the values are in some reasonable range
    // The L* component should correspond to 0
    // We can at least check it completes without error
    SUCCEED();
}

// Test getGray with a default color
TEST_F(GfxLabColorSpaceTest_453, GetGrayWithDefaultColor_453) {
    GfxColor color;
    labCS->getDefaultColor(&color);

    GfxGray gray;
    labCS->getGray(&color, &gray);
    // Gray value should be between 0 and 65535 (gfxColorComp1)
    EXPECT_GE(gray, 0);
}

// Test getRGB with a default color
TEST_F(GfxLabColorSpaceTest_453, GetRGBWithDefaultColor_453) {
    GfxColor color;
    labCS->getDefaultColor(&color);

    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    // RGB values should be in valid range
    EXPECT_GE(rgb.r, 0);
    EXPECT_GE(rgb.g, 0);
    EXPECT_GE(rgb.b, 0);
}

// Test getCMYK with a default color
TEST_F(GfxLabColorSpaceTest_453, GetCMYKWithDefaultColor_453) {
    GfxColor color;
    labCS->getDefaultColor(&color);

    GfxCMYK cmyk;
    labCS->getCMYK(&color, &cmyk);
    // Should complete without error
    SUCCEED();
}

// Test getDeviceN with a default color
TEST_F(GfxLabColorSpaceTest_453, GetDeviceNWithDefaultColor_453) {
    GfxColor color;
    labCS->getDefaultColor(&color);

    GfxColor deviceN;
    labCS->getDeviceN(&color, &deviceN);
    // Should complete without error
    SUCCEED();
}

// Test getDefaultRanges
TEST_F(GfxLabColorSpaceTest_453, GetDefaultRanges_453) {
    double decodeLow[3];
    double decodeRange[3];
    int maxImgPixel = 255;

    labCS->getDefaultRanges(decodeLow, decodeRange, maxImgPixel);

    // L* range should be [0, 100]
    EXPECT_DOUBLE_EQ(decodeLow[0], 0.0);
    EXPECT_DOUBLE_EQ(decodeRange[0], 100.0);

    // a* range
    EXPECT_DOUBLE_EQ(decodeLow[1], labCS->getAMin());
    EXPECT_DOUBLE_EQ(decodeRange[1], labCS->getAMax() - labCS->getAMin());

    // b* range
    EXPECT_DOUBLE_EQ(decodeLow[2], labCS->getBMin());
    EXPECT_DOUBLE_EQ(decodeRange[2], labCS->getBMax() - labCS->getBMin());
}

// Test that a* range defaults match PDF spec defaults [-100, 100]
TEST_F(GfxLabColorSpaceTest_453, DefaultAMinMax_453) {
    // Per PDF spec, default range for a* and b* is [-100, 100]
    EXPECT_DOUBLE_EQ(labCS->getAMin(), -100.0);
    EXPECT_DOUBLE_EQ(labCS->getAMax(), 100.0);
}

TEST_F(GfxLabColorSpaceTest_453, DefaultBMinMax_453) {
    EXPECT_DOUBLE_EQ(labCS->getBMin(), -100.0);
    EXPECT_DOUBLE_EQ(labCS->getBMax(), 100.0);
}

// Test that BlackY is consistent with BlackX and BlackZ (all should be 0 by default)
TEST_F(GfxLabColorSpaceTest_453, BlackPointConsistency_453) {
    EXPECT_DOUBLE_EQ(labCS->getBlackX(), labCS->getBlackY());
    EXPECT_DOUBLE_EQ(labCS->getBlackY(), labCS->getBlackZ());
}

// Boundary: test with maxImgPixel = 0 in getDefaultRanges
TEST_F(GfxLabColorSpaceTest_453, GetDefaultRangesZeroMaxPixel_453) {
    double decodeLow[3];
    double decodeRange[3];

    labCS->getDefaultRanges(decodeLow, decodeRange, 0);
    // Should not crash
    SUCCEED();
}

// Boundary: test with maxImgPixel = 1 in getDefaultRanges
TEST_F(GfxLabColorSpaceTest_453, GetDefaultRangesOneMaxPixel_453) {
    double decodeLow[3];
    double decodeRange[3];

    labCS->getDefaultRanges(decodeLow, decodeRange, 1);
    SUCCEED();
}
