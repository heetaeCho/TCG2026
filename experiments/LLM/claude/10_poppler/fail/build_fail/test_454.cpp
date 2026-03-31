#include <gtest/gtest.h>
#include "GfxState.h"

class GfxLabColorSpaceTest_454 : public ::testing::Test {
protected:
    void SetUp() override {
        labCS = std::make_unique<GfxLabColorSpace>();
    }

    void TearDown() override {
        labCS.reset();
    }

    std::unique_ptr<GfxLabColorSpace> labCS;
};

// Test that default construction yields expected default values for blackZ
TEST_F(GfxLabColorSpaceTest_454, DefaultBlackZ_454) {
    // According to the Lab color space spec, default black point is (0,0,0)
    EXPECT_DOUBLE_EQ(labCS->getBlackZ(), 0.0);
}

// Test that default construction yields expected default values for blackX
TEST_F(GfxLabColorSpaceTest_454, DefaultBlackX_454) {
    EXPECT_DOUBLE_EQ(labCS->getBlackX(), 0.0);
}

// Test that default construction yields expected default values for blackY
TEST_F(GfxLabColorSpaceTest_454, DefaultBlackY_454) {
    EXPECT_DOUBLE_EQ(labCS->getBlackY(), 0.0);
}

// Test default white point values
TEST_F(GfxLabColorSpaceTest_454, DefaultWhiteX_454) {
    // WhiteX should have a default value (typically 1.0 for D65 or similar)
    double whiteX = labCS->getWhiteX();
    // Just verify it's retrievable; default constructed value
    EXPECT_GE(whiteX, 0.0);
}

TEST_F(GfxLabColorSpaceTest_454, DefaultWhiteY_454) {
    double whiteY = labCS->getWhiteY();
    EXPECT_GE(whiteY, 0.0);
}

TEST_F(GfxLabColorSpaceTest_454, DefaultWhiteZ_454) {
    double whiteZ = labCS->getWhiteZ();
    EXPECT_GE(whiteZ, 0.0);
}

// Test default a range
TEST_F(GfxLabColorSpaceTest_454, DefaultAMin_454) {
    double aMin = labCS->getAMin();
    // Default range for a is typically [-100, 100]
    EXPECT_LE(aMin, 0.0);
}

TEST_F(GfxLabColorSpaceTest_454, DefaultAMax_454) {
    double aMax = labCS->getAMax();
    EXPECT_GE(aMax, 0.0);
}

// Test default b range
TEST_F(GfxLabColorSpaceTest_454, DefaultBMin_454) {
    double bMin = labCS->getBMin();
    EXPECT_LE(bMin, 0.0);
}

TEST_F(GfxLabColorSpaceTest_454, DefaultBMax_454) {
    double bMax = labCS->getBMax();
    EXPECT_GE(bMax, 0.0);
}

// Test the color space mode
TEST_F(GfxLabColorSpaceTest_454, ModeIsLab_454) {
    EXPECT_EQ(labCS->getMode(), csLab);
}

// Test the number of components
TEST_F(GfxLabColorSpaceTest_454, NCompsIsThree_454) {
    EXPECT_EQ(labCS->getNComps(), 3);
}

// Test copy produces a valid copy with same blackZ
TEST_F(GfxLabColorSpaceTest_454, CopyPreservesBlackZ_454) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_DOUBLE_EQ(copiedLab->getBlackZ(), labCS->getBlackZ());
}

// Test copy preserves all properties
TEST_F(GfxLabColorSpaceTest_454, CopyPreservesAllProperties_454) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
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
    EXPECT_EQ(copiedLab->getMode(), labCS->getMode());
    EXPECT_EQ(copiedLab->getNComps(), labCS->getNComps());
}

// Test copy returns independent object
TEST_F(GfxLabColorSpaceTest_454, CopyReturnsIndependentObject_454) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(copied.get(), labCS.get());
}

// Test getDefaultColor
TEST_F(GfxLabColorSpaceTest_454, GetDefaultColor_454) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    // Default color should be set; at minimum L* should be 0 (black)
    // The first component represents L*
    // Just verify it doesn't crash and produces some value
    SUCCEED();
}

// Test getGray with default color
TEST_F(GfxLabColorSpaceTest_454, GetGrayFromDefaultColor_454) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxGray gray;
    labCS->getGray(&color, &gray);
    // Gray should be in valid range [0, 65535]
    EXPECT_GE(gray, 0);
    EXPECT_LE(gray, 65535);
}

// Test getRGB with default color
TEST_F(GfxLabColorSpaceTest_454, GetRGBFromDefaultColor_454) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    // RGB values should be in valid range [0, 65535]
    EXPECT_GE(rgb.r, 0);
    EXPECT_LE(rgb.r, 65535);
    EXPECT_GE(rgb.g, 0);
    EXPECT_LE(rgb.g, 65535);
    EXPECT_GE(rgb.b, 0);
    EXPECT_LE(rgb.b, 65535);
}

// Test getCMYK with default color
TEST_F(GfxLabColorSpaceTest_454, GetCMYKFromDefaultColor_454) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxCMYK cmyk;
    labCS->getCMYK(&color, &cmyk);
    // CMYK values should be in valid range [0, 65535]
    EXPECT_GE(cmyk.c, 0);
    EXPECT_LE(cmyk.c, 65535);
    EXPECT_GE(cmyk.m, 0);
    EXPECT_LE(cmyk.m, 65535);
    EXPECT_GE(cmyk.y, 0);
    EXPECT_LE(cmyk.y, 65535);
    EXPECT_GE(cmyk.k, 0);
    EXPECT_LE(cmyk.k, 65535);
}

// Test getDeviceN with default color
TEST_F(GfxLabColorSpaceTest_454, GetDeviceNFromDefaultColor_454) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxColor deviceN;
    labCS->getDeviceN(&color, &deviceN);
    // Should not crash
    SUCCEED();
}

// Test getDefaultRanges
TEST_F(GfxLabColorSpaceTest_454, GetDefaultRanges_454) {
    double decodeLow[3];
    double decodeRange[3];
    labCS->getDefaultRanges(decodeLow, decodeRange, 255);
    // L* range should be [0, 100], so decodeLow[0] = 0, decodeRange[0] = 100
    EXPECT_DOUBLE_EQ(decodeLow[0], 0.0);
    EXPECT_DOUBLE_EQ(decodeRange[0], 100.0);
    // a and b ranges should correspond to aMin/aMax and bMin/bMax
    EXPECT_DOUBLE_EQ(decodeLow[1], labCS->getAMin());
    EXPECT_DOUBLE_EQ(decodeRange[1], labCS->getAMax() - labCS->getAMin());
    EXPECT_DOUBLE_EQ(decodeLow[2], labCS->getBMin());
    EXPECT_DOUBLE_EQ(decodeRange[2], labCS->getBMax() - labCS->getBMin());
}

// Test that aMin <= aMax
TEST_F(GfxLabColorSpaceTest_454, AMinLessOrEqualAMax_454) {
    EXPECT_LE(labCS->getAMin(), labCS->getAMax());
}

// Test that bMin <= bMax
TEST_F(GfxLabColorSpaceTest_454, BMinLessOrEqualBMax_454) {
    EXPECT_LE(labCS->getBMin(), labCS->getBMax());
}

// Boundary test: maxImgPixel = 0 for getDefaultRanges
TEST_F(GfxLabColorSpaceTest_454, GetDefaultRangesZeroMaxImgPixel_454) {
    double decodeLow[3];
    double decodeRange[3];
    // Should not crash even with 0
    labCS->getDefaultRanges(decodeLow, decodeRange, 0);
    SUCCEED();
}

// Boundary test: maxImgPixel = 1 for getDefaultRanges
TEST_F(GfxLabColorSpaceTest_454, GetDefaultRangesOneMaxImgPixel_454) {
    double decodeLow[3];
    double decodeRange[3];
    labCS->getDefaultRanges(decodeLow, decodeRange, 1);
    SUCCEED();
}

// Test multiple copies are independent
TEST_F(GfxLabColorSpaceTest_454, MultipleCopiesAreIndependent_454) {
    auto copy1 = labCS->copy();
    auto copy2 = labCS->copy();
    ASSERT_NE(copy1, nullptr);
    ASSERT_NE(copy2, nullptr);
    EXPECT_NE(copy1.get(), copy2.get());
    
    GfxLabColorSpace* lab1 = dynamic_cast<GfxLabColorSpace*>(copy1.get());
    GfxLabColorSpace* lab2 = dynamic_cast<GfxLabColorSpace*>(copy2.get());
    ASSERT_NE(lab1, nullptr);
    ASSERT_NE(lab2, nullptr);
    EXPECT_DOUBLE_EQ(lab1->getBlackZ(), lab2->getBlackZ());
}
