#include <gtest/gtest.h>
#include "GfxState.h"

class GfxLabColorSpaceTest_451 : public ::testing::Test {
protected:
    void SetUp() override {
        labCS = std::make_unique<GfxLabColorSpace>();
    }

    std::unique_ptr<GfxLabColorSpace> labCS;
};

// Test default construction and white point values
TEST_F(GfxLabColorSpaceTest_451, DefaultConstructionWhiteX_451) {
    double whiteX = labCS->getWhiteX();
    // Default white point X should be a valid value (typically 1.0 for D65 or similar)
    EXPECT_GE(whiteX, 0.0);
}

TEST_F(GfxLabColorSpaceTest_451, DefaultConstructionWhiteY_451) {
    double whiteY = labCS->getWhiteY();
    EXPECT_GE(whiteY, 0.0);
}

TEST_F(GfxLabColorSpaceTest_451, DefaultConstructionWhiteZ_451) {
    double whiteZ = labCS->getWhiteZ();
    EXPECT_GE(whiteZ, 0.0);
}

// Test default construction and black point values
TEST_F(GfxLabColorSpaceTest_451, DefaultConstructionBlackX_451) {
    double blackX = labCS->getBlackX();
    EXPECT_GE(blackX, 0.0);
}

TEST_F(GfxLabColorSpaceTest_451, DefaultConstructionBlackY_451) {
    double blackY = labCS->getBlackY();
    EXPECT_GE(blackY, 0.0);
}

TEST_F(GfxLabColorSpaceTest_451, DefaultConstructionBlackZ_451) {
    double blackZ = labCS->getBlackZ();
    EXPECT_GE(blackZ, 0.0);
}

// Test default range values
TEST_F(GfxLabColorSpaceTest_451, DefaultConstructionAMin_451) {
    double aMin = labCS->getAMin();
    // a* range in Lab is typically -100 to 100, default may vary
    EXPECT_LE(aMin, labCS->getAMax());
}

TEST_F(GfxLabColorSpaceTest_451, DefaultConstructionAMax_451) {
    double aMax = labCS->getAMax();
    EXPECT_GE(aMax, labCS->getAMin());
}

TEST_F(GfxLabColorSpaceTest_451, DefaultConstructionBMin_451) {
    double bMin = labCS->getBMin();
    EXPECT_LE(bMin, labCS->getBMax());
}

TEST_F(GfxLabColorSpaceTest_451, DefaultConstructionBMax_451) {
    double bMax = labCS->getBMax();
    EXPECT_GE(bMax, labCS->getBMin());
}

// Test color space mode
TEST_F(GfxLabColorSpaceTest_451, GetModeReturnsLab_451) {
    GfxColorSpaceMode mode = labCS->getMode();
    EXPECT_EQ(mode, csLab);
}

// Test number of components
TEST_F(GfxLabColorSpaceTest_451, GetNCompsReturnsThree_451) {
    int nComps = labCS->getNComps();
    EXPECT_EQ(nComps, 3);
}

// Test copy functionality
TEST_F(GfxLabColorSpaceTest_451, CopyReturnsSameMode_451) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csLab);
}

TEST_F(GfxLabColorSpaceTest_451, CopyReturnsSameNComps_451) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNComps(), 3);
}

TEST_F(GfxLabColorSpaceTest_451, CopyPreservesWhitePoint_451) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    GfxLabColorSpace *copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_DOUBLE_EQ(copiedLab->getWhiteX(), labCS->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedLab->getWhiteY(), labCS->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedLab->getWhiteZ(), labCS->getWhiteZ());
}

TEST_F(GfxLabColorSpaceTest_451, CopyPreservesBlackPoint_451) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    GfxLabColorSpace *copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_DOUBLE_EQ(copiedLab->getBlackX(), labCS->getBlackX());
    EXPECT_DOUBLE_EQ(copiedLab->getBlackY(), labCS->getBlackY());
    EXPECT_DOUBLE_EQ(copiedLab->getBlackZ(), labCS->getBlackZ());
}

TEST_F(GfxLabColorSpaceTest_451, CopyPreservesRanges_451) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    GfxLabColorSpace *copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_DOUBLE_EQ(copiedLab->getAMin(), labCS->getAMin());
    EXPECT_DOUBLE_EQ(copiedLab->getAMax(), labCS->getAMax());
    EXPECT_DOUBLE_EQ(copiedLab->getBMin(), labCS->getBMin());
    EXPECT_DOUBLE_EQ(copiedLab->getBMax(), labCS->getBMax());
}

// Test getDefaultColor
TEST_F(GfxLabColorSpaceTest_451, GetDefaultColorSetsValidColor_451) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    // Default color should be set; L* component is typically 0 in default
    // Just verify no crash and values are finite
    EXPECT_TRUE(std::isfinite(colToDbl(color.c[0])));
    EXPECT_TRUE(std::isfinite(colToDbl(color.c[1])));
    EXPECT_TRUE(std::isfinite(colToDbl(color.c[2])));
}

// Test getGray with default color
TEST_F(GfxLabColorSpaceTest_451, GetGrayWithDefaultColor_451) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxGray gray;
    labCS->getGray(&color, &gray);
    double grayVal = colToDbl(gray);
    EXPECT_GE(grayVal, 0.0);
    EXPECT_LE(grayVal, 1.0);
}

// Test getRGB with default color
TEST_F(GfxLabColorSpaceTest_451, GetRGBWithDefaultColor_451) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    EXPECT_GE(colToDbl(rgb.r), 0.0);
    EXPECT_LE(colToDbl(rgb.r), 1.0);
    EXPECT_GE(colToDbl(rgb.g), 0.0);
    EXPECT_LE(colToDbl(rgb.g), 1.0);
    EXPECT_GE(colToDbl(rgb.b), 0.0);
    EXPECT_LE(colToDbl(rgb.b), 1.0);
}

// Test getCMYK with default color
TEST_F(GfxLabColorSpaceTest_451, GetCMYKWithDefaultColor_451) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxCMYK cmyk;
    labCS->getCMYK(&color, &cmyk);
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
TEST_F(GfxLabColorSpaceTest_451, GetDeviceNWithDefaultColor_451) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxColor deviceN;
    labCS->getDeviceN(&color, &deviceN);
    // DeviceN should produce valid values
    for (int i = 0; i < gfxColorMaxComps; i++) {
        EXPECT_GE(colToDbl(deviceN.c[i]), 0.0);
        EXPECT_LE(colToDbl(deviceN.c[i]), 1.0);
    }
}

// Test getDefaultRanges
TEST_F(GfxLabColorSpaceTest_451, GetDefaultRanges_451) {
    double decodeLow[3];
    double decodeRange[3];
    labCS->getDefaultRanges(decodeLow, decodeRange, 255);
    // L* component: 0 to 100
    EXPECT_GE(decodeLow[0], 0.0);
    // decodeRange should be positive for component 0 (L*)
    EXPECT_GT(decodeRange[0], 0.0);
}

// Test getRGB with a specific Lab color (white: L*=100, a*=0, b*=0)
TEST_F(GfxLabColorSpaceTest_451, GetRGBWhiteColor_451) {
    GfxColor color;
    // L* = 100 mapped to GfxColorComp range
    color.c[0] = dblToCol(1.0); // L* at max
    color.c[1] = dblToCol(0.5); // a* at midpoint of range (should be 0 if range is symmetric)
    color.c[2] = dblToCol(0.5); // b* at midpoint of range
    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    // Should produce some valid RGB values
    EXPECT_GE(colToDbl(rgb.r), 0.0);
    EXPECT_LE(colToDbl(rgb.r), 1.0);
    EXPECT_GE(colToDbl(rgb.g), 0.0);
    EXPECT_LE(colToDbl(rgb.g), 1.0);
    EXPECT_GE(colToDbl(rgb.b), 0.0);
    EXPECT_LE(colToDbl(rgb.b), 1.0);
}

// Test getRGB with black color (L*=0, a*=0, b*=0)
TEST_F(GfxLabColorSpaceTest_451, GetRGBBlackColor_451) {
    GfxColor color;
    color.c[0] = dblToCol(0.0); // L* = 0
    color.c[1] = dblToCol(0.5); // a* = 0 (midpoint)
    color.c[2] = dblToCol(0.5); // b* = 0 (midpoint)
    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    // Black should produce low RGB values
    EXPECT_GE(colToDbl(rgb.r), 0.0);
    EXPECT_LE(colToDbl(rgb.r), 1.0);
    EXPECT_GE(colToDbl(rgb.g), 0.0);
    EXPECT_LE(colToDbl(rgb.g), 1.0);
    EXPECT_GE(colToDbl(rgb.b), 0.0);
    EXPECT_LE(colToDbl(rgb.b), 1.0);
}

// Test that AMin <= AMax relationship holds
TEST_F(GfxLabColorSpaceTest_451, AMinLessThanOrEqualAMax_451) {
    EXPECT_LE(labCS->getAMin(), labCS->getAMax());
}

// Test that BMin <= BMax relationship holds
TEST_F(GfxLabColorSpaceTest_451, BMinLessThanOrEqualBMax_451) {
    EXPECT_LE(labCS->getBMin(), labCS->getBMax());
}

// Test getDefaultRanges with different maxImgPixel values
TEST_F(GfxLabColorSpaceTest_451, GetDefaultRangesWithMaxPixel1_451) {
    double decodeLow[3];
    double decodeRange[3];
    labCS->getDefaultRanges(decodeLow, decodeRange, 1);
    EXPECT_GT(decodeRange[0], 0.0);
}

TEST_F(GfxLabColorSpaceTest_451, GetDefaultRangesWithMaxPixel65535_451) {
    double decodeLow[3];
    double decodeRange[3];
    labCS->getDefaultRanges(decodeLow, decodeRange, 65535);
    EXPECT_GT(decodeRange[0], 0.0);
}

// Test that copy creates an independent object
TEST_F(GfxLabColorSpaceTest_451, CopyCreatesIndependentObject_451) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(copied.get(), labCS.get());
}
