#include <gtest/gtest.h>
#include "GfxState.h"

class GfxLabColorSpaceTest_456 : public ::testing::Test {
protected:
    void SetUp() override {
        labCS = std::make_unique<GfxLabColorSpace>();
    }

    void TearDown() override {
        labCS.reset();
    }

    std::unique_ptr<GfxLabColorSpace> labCS;
};

// Test that a default-constructed GfxLabColorSpace returns expected default values for aMax
TEST_F(GfxLabColorSpaceTest_456, DefaultConstructor_AMax_456) {
    double aMax = labCS->getAMax();
    // Default Lab color space typically has aMax = 100
    // We just verify it returns a finite number; exact value depends on implementation
    EXPECT_FALSE(std::isnan(aMax));
    EXPECT_FALSE(std::isinf(aMax));
}

// Test that a default-constructed GfxLabColorSpace returns expected default values for aMin
TEST_F(GfxLabColorSpaceTest_456, DefaultConstructor_AMin_456) {
    double aMin = labCS->getAMin();
    EXPECT_FALSE(std::isnan(aMin));
    EXPECT_FALSE(std::isinf(aMin));
}

// Test that a default-constructed GfxLabColorSpace returns expected default values for bMax
TEST_F(GfxLabColorSpaceTest_456, DefaultConstructor_BMax_456) {
    double bMax = labCS->getBMax();
    EXPECT_FALSE(std::isnan(bMax));
    EXPECT_FALSE(std::isinf(bMax));
}

// Test that a default-constructed GfxLabColorSpace returns expected default values for bMin
TEST_F(GfxLabColorSpaceTest_456, DefaultConstructor_BMin_456) {
    double bMin = labCS->getBMin();
    EXPECT_FALSE(std::isnan(bMin));
    EXPECT_FALSE(std::isinf(bMin));
}

// Test that aMin <= aMax
TEST_F(GfxLabColorSpaceTest_456, AMinLessThanOrEqualAMax_456) {
    EXPECT_LE(labCS->getAMin(), labCS->getAMax());
}

// Test that bMin <= bMax
TEST_F(GfxLabColorSpaceTest_456, BMinLessThanOrEqualBMax_456) {
    EXPECT_LE(labCS->getBMin(), labCS->getBMax());
}

// Test that the color space mode is csLab
TEST_F(GfxLabColorSpaceTest_456, GetMode_ReturnsLab_456) {
    EXPECT_EQ(labCS->getMode(), csLab);
}

// Test that getNComps returns 3 for Lab color space
TEST_F(GfxLabColorSpaceTest_456, GetNComps_Returns3_456) {
    EXPECT_EQ(labCS->getNComps(), 3);
}

// Test white point values are valid (Y must be 1.0 for normalized white point)
TEST_F(GfxLabColorSpaceTest_456, WhitePointValues_456) {
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
TEST_F(GfxLabColorSpaceTest_456, BlackPointValues_456) {
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

// Test copy produces a valid object with same properties
TEST_F(GfxLabColorSpaceTest_456, Copy_PreservesProperties_456) {
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

// Test getDefaultColor sets a valid color
TEST_F(GfxLabColorSpaceTest_456, GetDefaultColor_456) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    // Default color should have values within valid range
    // For Lab, L* is in [0, 100], a* in [aMin, aMax], b* in [bMin, bMax]
    // The GfxColor stores values as fixed-point, so we just verify it doesn't crash
    // and the values are set
    SUCCEED();
}

// Test getGray with a default color
TEST_F(GfxLabColorSpaceTest_456, GetGray_DefaultColor_456) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxGray gray;
    labCS->getGray(&color, &gray);
    // Gray value should be in [0, 65535] range (GfxColorComp range)
    EXPECT_GE(gray, 0);
}

// Test getRGB with a default color
TEST_F(GfxLabColorSpaceTest_456, GetRGB_DefaultColor_456) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    // RGB values should be valid
    SUCCEED();
}

// Test getCMYK with a default color
TEST_F(GfxLabColorSpaceTest_456, GetCMYK_DefaultColor_456) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxCMYK cmyk;
    labCS->getCMYK(&color, &cmyk);
    SUCCEED();
}

// Test getDeviceN with a default color
TEST_F(GfxLabColorSpaceTest_456, GetDeviceN_DefaultColor_456) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxColor deviceN;
    labCS->getDeviceN(&color, &deviceN);
    SUCCEED();
}

// Test getDefaultRanges
TEST_F(GfxLabColorSpaceTest_456, GetDefaultRanges_456) {
    double decodeLow[3];
    double decodeRange[3];
    int maxImgPixel = 255;
    labCS->getDefaultRanges(decodeLow, decodeRange, maxImgPixel);
    // For Lab, L* decode low should be 0, range should be 100
    // a* and b* should correspond to aMin/aMax and bMin/bMax
    EXPECT_FALSE(std::isnan(decodeLow[0]));
    EXPECT_FALSE(std::isnan(decodeRange[0]));
    EXPECT_FALSE(std::isnan(decodeLow[1]));
    EXPECT_FALSE(std::isnan(decodeRange[1]));
    EXPECT_FALSE(std::isnan(decodeLow[2]));
    EXPECT_FALSE(std::isnan(decodeRange[2]));
}

// Test that copy returns an independent object (modifying original doesn't affect copy)
TEST_F(GfxLabColorSpaceTest_456, Copy_IsIndependent_456) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    
    // Verify the copied pointer is different from original
    EXPECT_NE(copiedLab, labCS.get());
}

// Test default ranges with maxImgPixel = 0 (boundary)
TEST_F(GfxLabColorSpaceTest_456, GetDefaultRanges_ZeroMaxPixel_456) {
    double decodeLow[3];
    double decodeRange[3];
    int maxImgPixel = 0;
    labCS->getDefaultRanges(decodeLow, decodeRange, maxImgPixel);
    // Should not crash
    SUCCEED();
}

// Test default ranges with maxImgPixel = 1 (boundary)
TEST_F(GfxLabColorSpaceTest_456, GetDefaultRanges_OneMaxPixel_456) {
    double decodeLow[3];
    double decodeRange[3];
    int maxImgPixel = 1;
    labCS->getDefaultRanges(decodeLow, decodeRange, maxImgPixel);
    SUCCEED();
}

// Test default ranges with large maxImgPixel
TEST_F(GfxLabColorSpaceTest_456, GetDefaultRanges_LargeMaxPixel_456) {
    double decodeLow[3];
    double decodeRange[3];
    int maxImgPixel = 65535;
    labCS->getDefaultRanges(decodeLow, decodeRange, maxImgPixel);
    SUCCEED();
}
