#include <gtest/gtest.h>
#include "GfxState.h"

class GfxLabColorSpaceTest_449 : public ::testing::Test {
protected:
    void SetUp() override {
        labCS = std::make_unique<GfxLabColorSpace>();
    }

    void TearDown() override {
        labCS.reset();
    }

    std::unique_ptr<GfxLabColorSpace> labCS;
};

// Test that the default constructor creates a valid object
TEST_F(GfxLabColorSpaceTest_449, DefaultConstructor_449) {
    ASSERT_NE(labCS, nullptr);
}

// Test getMode returns the correct color space mode for Lab
TEST_F(GfxLabColorSpaceTest_449, GetModeReturnsLab_449) {
    EXPECT_EQ(labCS->getMode(), csLab);
}

// Test getNComps returns 3 for Lab color space (L, a, b)
TEST_F(GfxLabColorSpaceTest_449, GetNCompsReturnsThree_449) {
    EXPECT_EQ(labCS->getNComps(), 3);
}

// Test default white point values
TEST_F(GfxLabColorSpaceTest_449, DefaultWhiteX_449) {
    double whiteX = labCS->getWhiteX();
    // Default white point X should be a valid value (typically 1.0 for D65 or similar)
    EXPECT_GE(whiteX, 0.0);
}

TEST_F(GfxLabColorSpaceTest_449, DefaultWhiteY_449) {
    double whiteY = labCS->getWhiteY();
    EXPECT_GE(whiteY, 0.0);
}

TEST_F(GfxLabColorSpaceTest_449, DefaultWhiteZ_449) {
    double whiteZ = labCS->getWhiteZ();
    EXPECT_GE(whiteZ, 0.0);
}

// Test default black point values
TEST_F(GfxLabColorSpaceTest_449, DefaultBlackX_449) {
    double blackX = labCS->getBlackX();
    EXPECT_GE(blackX, 0.0);
}

TEST_F(GfxLabColorSpaceTest_449, DefaultBlackY_449) {
    double blackY = labCS->getBlackY();
    EXPECT_GE(blackY, 0.0);
}

TEST_F(GfxLabColorSpaceTest_449, DefaultBlackZ_449) {
    double blackZ = labCS->getBlackZ();
    EXPECT_GE(blackZ, 0.0);
}

// Test default a range values
TEST_F(GfxLabColorSpaceTest_449, DefaultAMin_449) {
    double aMin = labCS->getAMin();
    // Default aMin should be a finite number
    EXPECT_TRUE(std::isfinite(aMin));
}

TEST_F(GfxLabColorSpaceTest_449, DefaultAMax_449) {
    double aMax = labCS->getAMax();
    EXPECT_TRUE(std::isfinite(aMax));
}

TEST_F(GfxLabColorSpaceTest_449, AMinLessThanOrEqualAMax_449) {
    EXPECT_LE(labCS->getAMin(), labCS->getAMax());
}

// Test default b range values
TEST_F(GfxLabColorSpaceTest_449, DefaultBMin_449) {
    double bMin = labCS->getBMin();
    EXPECT_TRUE(std::isfinite(bMin));
}

TEST_F(GfxLabColorSpaceTest_449, DefaultBMax_449) {
    double bMax = labCS->getBMax();
    EXPECT_TRUE(std::isfinite(bMax));
}

TEST_F(GfxLabColorSpaceTest_449, BMinLessThanOrEqualBMax_449) {
    EXPECT_LE(labCS->getBMin(), labCS->getBMax());
}

// Test copy produces a valid copy with same properties
TEST_F(GfxLabColorSpaceTest_449, CopyPreservesWhitePoint_449) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    
    EXPECT_DOUBLE_EQ(copiedLab->getWhiteX(), labCS->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedLab->getWhiteY(), labCS->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedLab->getWhiteZ(), labCS->getWhiteZ());
}

TEST_F(GfxLabColorSpaceTest_449, CopyPreservesBlackPoint_449) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    
    EXPECT_DOUBLE_EQ(copiedLab->getBlackX(), labCS->getBlackX());
    EXPECT_DOUBLE_EQ(copiedLab->getBlackY(), labCS->getBlackY());
    EXPECT_DOUBLE_EQ(copiedLab->getBlackZ(), labCS->getBlackZ());
}

TEST_F(GfxLabColorSpaceTest_449, CopyPreservesRanges_449) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    
    EXPECT_DOUBLE_EQ(copiedLab->getAMin(), labCS->getAMin());
    EXPECT_DOUBLE_EQ(copiedLab->getAMax(), labCS->getAMax());
    EXPECT_DOUBLE_EQ(copiedLab->getBMin(), labCS->getBMin());
    EXPECT_DOUBLE_EQ(copiedLab->getBMax(), labCS->getBMax());
}

TEST_F(GfxLabColorSpaceTest_449, CopyPreservesMode_449) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    
    EXPECT_EQ(copied->getMode(), csLab);
}

TEST_F(GfxLabColorSpaceTest_449, CopyPreservesNComps_449) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    
    EXPECT_EQ(copied->getNComps(), 3);
}

// Test getDefaultColor
TEST_F(GfxLabColorSpaceTest_449, GetDefaultColorSetsValidColor_449) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    // The default color should have valid component values
    // For Lab, typically L=0, a=0, b=0 or similar default
    // We just verify it doesn't crash and components are finite
    EXPECT_TRUE(std::isfinite(colToDbl(color.c[0])));
    EXPECT_TRUE(std::isfinite(colToDbl(color.c[1])));
    EXPECT_TRUE(std::isfinite(colToDbl(color.c[2])));
}

// Test getGray with default color
TEST_F(GfxLabColorSpaceTest_449, GetGrayWithDefaultColor_449) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    
    GfxGray gray;
    labCS->getGray(&color, &gray);
    
    double grayVal = colToDbl(gray);
    EXPECT_GE(grayVal, 0.0);
    EXPECT_LE(grayVal, 1.0);
}

// Test getRGB with default color
TEST_F(GfxLabColorSpaceTest_449, GetRGBWithDefaultColor_449) {
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
TEST_F(GfxLabColorSpaceTest_449, GetCMYKWithDefaultColor_449) {
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
TEST_F(GfxLabColorSpaceTest_449, GetDeviceNWithDefaultColor_449) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    
    GfxColor deviceN;
    labCS->getDeviceN(&color, &deviceN);
    
    // DeviceN should produce valid component values
    for (int i = 0; i < gfxColorMaxComps; i++) {
        double val = colToDbl(deviceN.c[i]);
        EXPECT_GE(val, 0.0);
        EXPECT_LE(val, 1.0);
    }
}

// Test getDefaultRanges
TEST_F(GfxLabColorSpaceTest_449, GetDefaultRanges_449) {
    double decodeLow[3];
    double decodeRange[3];
    int maxImgPixel = 255;
    
    labCS->getDefaultRanges(decodeLow, decodeRange, maxImgPixel);
    
    // The decode ranges should be finite values
    for (int i = 0; i < 3; i++) {
        EXPECT_TRUE(std::isfinite(decodeLow[i]));
        EXPECT_TRUE(std::isfinite(decodeRange[i]));
    }
}

// Test getDefaultRanges with different maxImgPixel values
TEST_F(GfxLabColorSpaceTest_449, GetDefaultRangesWithMaxPixel1_449) {
    double decodeLow[3];
    double decodeRange[3];
    int maxImgPixel = 1;
    
    labCS->getDefaultRanges(decodeLow, decodeRange, maxImgPixel);
    
    for (int i = 0; i < 3; i++) {
        EXPECT_TRUE(std::isfinite(decodeLow[i]));
        EXPECT_TRUE(std::isfinite(decodeRange[i]));
    }
}

TEST_F(GfxLabColorSpaceTest_449, GetDefaultRangesWithLargeMaxPixel_449) {
    double decodeLow[3];
    double decodeRange[3];
    int maxImgPixel = 65535;
    
    labCS->getDefaultRanges(decodeLow, decodeRange, maxImgPixel);
    
    for (int i = 0; i < 3; i++) {
        EXPECT_TRUE(std::isfinite(decodeLow[i]));
        EXPECT_TRUE(std::isfinite(decodeRange[i]));
    }
}

// Test with specific Lab color values
TEST_F(GfxLabColorSpaceTest_449, GetRGBWithWhiteColor_449) {
    GfxColor color;
    // L=100 (max lightness), a=0, b=0 should give white or near-white
    color.c[0] = dblToCol(1.0); // L mapped to [0,1] range
    color.c[1] = dblToCol(0.5); // a at midpoint
    color.c[2] = dblToCol(0.5); // b at midpoint
    
    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    
    // Result should be valid RGB values
    EXPECT_GE(colToDbl(rgb.r), 0.0);
    EXPECT_LE(colToDbl(rgb.r), 1.0);
    EXPECT_GE(colToDbl(rgb.g), 0.0);
    EXPECT_LE(colToDbl(rgb.g), 1.0);
    EXPECT_GE(colToDbl(rgb.b), 0.0);
    EXPECT_LE(colToDbl(rgb.b), 1.0);
}

TEST_F(GfxLabColorSpaceTest_449, GetRGBWithBlackColor_449) {
    GfxColor color;
    // L=0 (min lightness), a=0, b=0 should give black or near-black
    color.c[0] = dblToCol(0.0);
    color.c[1] = dblToCol(0.5);
    color.c[2] = dblToCol(0.5);
    
    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    
    EXPECT_GE(colToDbl(rgb.r), 0.0);
    EXPECT_LE(colToDbl(rgb.r), 1.0);
    EXPECT_GE(colToDbl(rgb.g), 0.0);
    EXPECT_LE(colToDbl(rgb.g), 1.0);
    EXPECT_GE(colToDbl(rgb.b), 0.0);
    EXPECT_LE(colToDbl(rgb.b), 1.0);
}

// Test boundary color values
TEST_F(GfxLabColorSpaceTest_449, GetRGBWithMinComponentValues_449) {
    GfxColor color;
    color.c[0] = dblToCol(0.0);
    color.c[1] = dblToCol(0.0);
    color.c[2] = dblToCol(0.0);
    
    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    
    EXPECT_GE(colToDbl(rgb.r), 0.0);
    EXPECT_LE(colToDbl(rgb.r), 1.0);
    EXPECT_GE(colToDbl(rgb.g), 0.0);
    EXPECT_LE(colToDbl(rgb.g), 1.0);
    EXPECT_GE(colToDbl(rgb.b), 0.0);
    EXPECT_LE(colToDbl(rgb.b), 1.0);
}

TEST_F(GfxLabColorSpaceTest_449, GetRGBWithMaxComponentValues_449) {
    GfxColor color;
    color.c[0] = dblToCol(1.0);
    color.c[1] = dblToCol(1.0);
    color.c[2] = dblToCol(1.0);
    
    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    
    EXPECT_GE(colToDbl(rgb.r), 0.0);
    EXPECT_LE(colToDbl(rgb.r), 1.0);
    EXPECT_GE(colToDbl(rgb.g), 0.0);
    EXPECT_LE(colToDbl(rgb.g), 1.0);
    EXPECT_GE(colToDbl(rgb.b), 0.0);
    EXPECT_LE(colToDbl(rgb.b), 1.0);
}

// Test that WhiteY is 1.0 (required by PDF spec for Lab)
TEST_F(GfxLabColorSpaceTest_449, DefaultWhiteYIsOne_449) {
    // Per PDF spec, whiteY must be 1.0
    EXPECT_DOUBLE_EQ(labCS->getWhiteY(), 1.0);
}
