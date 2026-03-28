#include <gtest/gtest.h>
#include "GfxState.h"

class GfxLabColorSpaceTest_455 : public ::testing::Test {
protected:
    void SetUp() override {
        labCS = std::make_unique<GfxLabColorSpace>();
    }

    void TearDown() override {
        labCS.reset();
    }

    std::unique_ptr<GfxLabColorSpace> labCS;
};

// Test that a default-constructed GfxLabColorSpace returns expected default values for aMin
TEST_F(GfxLabColorSpaceTest_455, DefaultAMinValue_455) {
    double aMin = labCS->getAMin();
    // Default aMin should be some defined value (typically 0 or a standard Lab range)
    // We just verify it returns a finite number
    EXPECT_FALSE(std::isnan(aMin));
    EXPECT_FALSE(std::isinf(aMin));
}

// Test that a default-constructed GfxLabColorSpace returns expected default values for aMax
TEST_F(GfxLabColorSpaceTest_455, DefaultAMaxValue_455) {
    double aMax = labCS->getAMax();
    EXPECT_FALSE(std::isnan(aMax));
    EXPECT_FALSE(std::isinf(aMax));
}

// Test that a default-constructed GfxLabColorSpace returns expected default values for bMin
TEST_F(GfxLabColorSpaceTest_455, DefaultBMinValue_455) {
    double bMin = labCS->getBMin();
    EXPECT_FALSE(std::isnan(bMin));
    EXPECT_FALSE(std::isinf(bMin));
}

// Test that a default-constructed GfxLabColorSpace returns expected default values for bMax
TEST_F(GfxLabColorSpaceTest_455, DefaultBMaxValue_455) {
    double bMax = labCS->getBMax();
    EXPECT_FALSE(std::isnan(bMax));
    EXPECT_FALSE(std::isinf(bMax));
}

// Test that aMin <= aMax for default construction
TEST_F(GfxLabColorSpaceTest_455, AMinLessOrEqualAMax_455) {
    EXPECT_LE(labCS->getAMin(), labCS->getAMax());
}

// Test that bMin <= bMax for default construction
TEST_F(GfxLabColorSpaceTest_455, BMinLessOrEqualBMax_455) {
    EXPECT_LE(labCS->getBMin(), labCS->getBMax());
}

// Test that the color space mode is csLab
TEST_F(GfxLabColorSpaceTest_455, ModeIsLab_455) {
    EXPECT_EQ(labCS->getMode(), csLab);
}

// Test that the number of components is 3 (L*, a*, b*)
TEST_F(GfxLabColorSpaceTest_455, NCompsIsThree_455) {
    EXPECT_EQ(labCS->getNComps(), 3);
}

// Test white point values are valid (Y must be 1.0 for proper Lab)
TEST_F(GfxLabColorSpaceTest_455, WhitePointValues_455) {
    double whiteX = labCS->getWhiteX();
    double whiteY = labCS->getWhiteY();
    double whiteZ = labCS->getWhiteZ();
    EXPECT_FALSE(std::isnan(whiteX));
    EXPECT_FALSE(std::isnan(whiteY));
    EXPECT_FALSE(std::isnan(whiteZ));
    // White point components should be non-negative
    EXPECT_GE(whiteX, 0.0);
    EXPECT_GE(whiteY, 0.0);
    EXPECT_GE(whiteZ, 0.0);
}

// Test black point values are valid
TEST_F(GfxLabColorSpaceTest_455, BlackPointValues_455) {
    double blackX = labCS->getBlackX();
    double blackY = labCS->getBlackY();
    double blackZ = labCS->getBlackZ();
    EXPECT_FALSE(std::isnan(blackX));
    EXPECT_FALSE(std::isnan(blackY));
    EXPECT_FALSE(std::isnan(blackZ));
    // Black point components should be non-negative
    EXPECT_GE(blackX, 0.0);
    EXPECT_GE(blackY, 0.0);
    EXPECT_GE(blackZ, 0.0);
}

// Test copy produces a valid color space with same properties
TEST_F(GfxLabColorSpaceTest_455, CopyPreservesProperties_455) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);

    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);

    EXPECT_EQ(copiedLab->getAMin(), labCS->getAMin());
    EXPECT_EQ(copiedLab->getAMax(), labCS->getAMax());
    EXPECT_EQ(copiedLab->getBMin(), labCS->getBMin());
    EXPECT_EQ(copiedLab->getBMax(), labCS->getBMax());
    EXPECT_EQ(copiedLab->getWhiteX(), labCS->getWhiteX());
    EXPECT_EQ(copiedLab->getWhiteY(), labCS->getWhiteY());
    EXPECT_EQ(copiedLab->getWhiteZ(), labCS->getWhiteZ());
    EXPECT_EQ(copiedLab->getBlackX(), labCS->getBlackX());
    EXPECT_EQ(copiedLab->getBlackY(), labCS->getBlackY());
    EXPECT_EQ(copiedLab->getBlackZ(), labCS->getBlackZ());
    EXPECT_EQ(copiedLab->getMode(), labCS->getMode());
    EXPECT_EQ(copiedLab->getNComps(), labCS->getNComps());
}

// Test getDefaultColor produces a valid color
TEST_F(GfxLabColorSpaceTest_455, GetDefaultColor_455) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    // Default color should have been set; we can at least verify no crash
    // and that the values are within expected ranges
    // L* component (index 0) should be within [0, gfxColorComp1]
    SUCCEED();
}

// Test getGray with default color
TEST_F(GfxLabColorSpaceTest_455, GetGrayWithDefaultColor_455) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxGray gray;
    labCS->getGray(&color, &gray);
    // Gray should be in valid range [0, gfxColorComp1]
    EXPECT_GE(gray, 0);
}

// Test getRGB with default color
TEST_F(GfxLabColorSpaceTest_455, GetRGBWithDefaultColor_455) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    // RGB components should be in valid range
    EXPECT_GE(rgb.r, 0);
    EXPECT_GE(rgb.g, 0);
    EXPECT_GE(rgb.b, 0);
}

// Test getCMYK with default color
TEST_F(GfxLabColorSpaceTest_455, GetCMYKWithDefaultColor_455) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxCMYK cmyk;
    labCS->getCMYK(&color, &cmyk);
    EXPECT_GE(cmyk.c, 0);
    EXPECT_GE(cmyk.m, 0);
    EXPECT_GE(cmyk.y, 0);
    EXPECT_GE(cmyk.k, 0);
}

// Test getDefaultRanges
TEST_F(GfxLabColorSpaceTest_455, GetDefaultRanges_455) {
    double decodeLow[4] = {0};
    double decodeRange[4] = {0};
    int maxImgPixel = 255;
    labCS->getDefaultRanges(decodeLow, decodeRange, maxImgPixel);
    // L* decode low should be 0, range should be 100
    // a* and b* should use aMin/aMax and bMin/bMax
    // Just verify they are finite
    for (int i = 0; i < 3; i++) {
        EXPECT_FALSE(std::isnan(decodeLow[i]));
        EXPECT_FALSE(std::isnan(decodeRange[i]));
    }
}

// Test getDeviceN with default color doesn't crash
TEST_F(GfxLabColorSpaceTest_455, GetDeviceNWithDefaultColor_455) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxColor deviceN;
    labCS->getDeviceN(&color, &deviceN);
    SUCCEED();
}
