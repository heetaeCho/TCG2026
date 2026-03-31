#include <gtest/gtest.h>
#include "GfxState.h"

class GfxLabColorSpaceTest_450 : public ::testing::Test {
protected:
    void SetUp() override {
        labCS = std::make_unique<GfxLabColorSpace>();
    }

    std::unique_ptr<GfxLabColorSpace> labCS;
};

// Test that default constructor creates a valid object
TEST_F(GfxLabColorSpaceTest_450, DefaultConstructor_450) {
    ASSERT_NE(labCS, nullptr);
}

// Test getWhiteY returns a value (default should be 1.0 for D65 or similar standard illuminant)
TEST_F(GfxLabColorSpaceTest_450, GetWhiteY_DefaultValue_450) {
    double whiteY = labCS->getWhiteY();
    // WhiteY for Lab color space is typically 1.0 by default
    EXPECT_DOUBLE_EQ(whiteY, 1.0);
}

// Test getWhiteX returns a value
TEST_F(GfxLabColorSpaceTest_450, GetWhiteX_DefaultValue_450) {
    double whiteX = labCS->getWhiteX();
    EXPECT_DOUBLE_EQ(whiteX, 1.0);
}

// Test getWhiteZ returns a value
TEST_F(GfxLabColorSpaceTest_450, GetWhiteZ_DefaultValue_450) {
    double whiteZ = labCS->getWhiteZ();
    EXPECT_DOUBLE_EQ(whiteZ, 1.0);
}

// Test getBlackX returns default value (typically 0)
TEST_F(GfxLabColorSpaceTest_450, GetBlackX_DefaultValue_450) {
    double blackX = labCS->getBlackX();
    EXPECT_DOUBLE_EQ(blackX, 0.0);
}

// Test getBlackY returns default value (typically 0)
TEST_F(GfxLabColorSpaceTest_450, GetBlackY_DefaultValue_450) {
    double blackY = labCS->getBlackY();
    EXPECT_DOUBLE_EQ(blackY, 0.0);
}

// Test getBlackZ returns default value (typically 0)
TEST_F(GfxLabColorSpaceTest_450, GetBlackZ_DefaultValue_450) {
    double blackZ = labCS->getBlackZ();
    EXPECT_DOUBLE_EQ(blackZ, 0.0);
}

// Test getAMin returns default value
TEST_F(GfxLabColorSpaceTest_450, GetAMin_DefaultValue_450) {
    double aMin = labCS->getAMin();
    EXPECT_DOUBLE_EQ(aMin, -100.0);
}

// Test getAMax returns default value
TEST_F(GfxLabColorSpaceTest_450, GetAMax_DefaultValue_450) {
    double aMax = labCS->getAMax();
    EXPECT_DOUBLE_EQ(aMax, 100.0);
}

// Test getBMin returns default value
TEST_F(GfxLabColorSpaceTest_450, GetBMin_DefaultValue_450) {
    double bMin = labCS->getBMin();
    EXPECT_DOUBLE_EQ(bMin, -100.0);
}

// Test getBMax returns default value
TEST_F(GfxLabColorSpaceTest_450, GetBMax_DefaultValue_450) {
    double bMax = labCS->getBMax();
    EXPECT_DOUBLE_EQ(bMax, 100.0);
}

// Test getMode returns csLab
TEST_F(GfxLabColorSpaceTest_450, GetMode_ReturnsLab_450) {
    GfxColorSpaceMode mode = labCS->getMode();
    EXPECT_EQ(mode, csLab);
}

// Test getNComps returns 3 (L, a, b)
TEST_F(GfxLabColorSpaceTest_450, GetNComps_ReturnsThree_450) {
    int nComps = labCS->getNComps();
    EXPECT_EQ(nComps, 3);
}

// Test copy creates a valid copy
TEST_F(GfxLabColorSpaceTest_450, Copy_CreatesValidCopy_450) {
    std::unique_ptr<GfxColorSpace> copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csLab);
    EXPECT_EQ(copied->getNComps(), 3);
}

// Test copy preserves white point values
TEST_F(GfxLabColorSpaceTest_450, Copy_PreservesWhitePoint_450) {
    std::unique_ptr<GfxColorSpace> copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_DOUBLE_EQ(copiedLab->getWhiteX(), labCS->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedLab->getWhiteY(), labCS->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedLab->getWhiteZ(), labCS->getWhiteZ());
}

// Test copy preserves black point values
TEST_F(GfxLabColorSpaceTest_450, Copy_PreservesBlackPoint_450) {
    std::unique_ptr<GfxColorSpace> copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_DOUBLE_EQ(copiedLab->getBlackX(), labCS->getBlackX());
    EXPECT_DOUBLE_EQ(copiedLab->getBlackY(), labCS->getBlackY());
    EXPECT_DOUBLE_EQ(copiedLab->getBlackZ(), labCS->getBlackZ());
}

// Test copy preserves range values
TEST_F(GfxLabColorSpaceTest_450, Copy_PreservesRange_450) {
    std::unique_ptr<GfxColorSpace> copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_DOUBLE_EQ(copiedLab->getAMin(), labCS->getAMin());
    EXPECT_DOUBLE_EQ(copiedLab->getAMax(), labCS->getAMax());
    EXPECT_DOUBLE_EQ(copiedLab->getBMin(), labCS->getBMin());
    EXPECT_DOUBLE_EQ(copiedLab->getBMax(), labCS->getBMax());
}

// Test getDefaultColor sets color to default L*=0, a*=0, b*=0
TEST_F(GfxLabColorSpaceTest_450, GetDefaultColor_SetsDefault_450) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    // Default color for Lab should have L*=0 mapped to component range
    // The first component (L*) should be 0
    EXPECT_EQ(color.c[0], 0);
}

// Test getGray with a known color value
TEST_F(GfxLabColorSpaceTest_450, GetGray_WithDefaultColor_450) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxGray gray;
    labCS->getGray(&color, &gray);
    // Default color (L*=0) should map to black (gray=0)
    EXPECT_EQ(gray, 0);
}

// Test getRGB with default color
TEST_F(GfxLabColorSpaceTest_450, GetRGB_WithDefaultColor_450) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    // Default color (L*=0, a*=0, b*=0) should be black
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getCMYK with default color
TEST_F(GfxLabColorSpaceTest_450, GetCMYK_WithDefaultColor_450) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxCMYK cmyk;
    labCS->getCMYK(&color, &cmyk);
    // Black in CMYK should have k=1 (or max value)
    // At least verify it doesn't crash and produces some output
    SUCCEED();
}

// Test getDeviceN with default color
TEST_F(GfxLabColorSpaceTest_450, GetDeviceN_WithDefaultColor_450) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxColor deviceN;
    labCS->getDeviceN(&color, &deviceN);
    // Verify it doesn't crash
    SUCCEED();
}

// Test getDefaultRanges
TEST_F(GfxLabColorSpaceTest_450, GetDefaultRanges_450) {
    double decodeLow[3];
    double decodeRange[3];
    int maxImgPixel = 255;
    labCS->getDefaultRanges(decodeLow, decodeRange, maxImgPixel);
    // L* range is 0 to 100
    EXPECT_DOUBLE_EQ(decodeLow[0], 0.0);
    EXPECT_DOUBLE_EQ(decodeRange[0], 100.0);
    // a* range
    EXPECT_DOUBLE_EQ(decodeLow[1], labCS->getAMin());
    EXPECT_DOUBLE_EQ(decodeRange[1], labCS->getAMax() - labCS->getAMin());
    // b* range
    EXPECT_DOUBLE_EQ(decodeLow[2], labCS->getBMin());
    EXPECT_DOUBLE_EQ(decodeRange[2], labCS->getBMax() - labCS->getBMin());
}

// Test getRGB with a white color (L*=100, a*=0, b*=0)
TEST_F(GfxLabColorSpaceTest_450, GetRGB_WithWhiteColor_450) {
    GfxColor color;
    // L* = 100 -> mapped to GfxColorComp max
    color.c[0] = dblToCol(1.0); // Assuming L* is normalized to [0,1] internally
    color.c[1] = dblToCol(0.5); // a* = 0 when normalized to middle of range
    color.c[2] = dblToCol(0.5); // b* = 0 when normalized to middle of range
    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    // White should have high RGB values
    // Just verify it doesn't crash - exact values depend on implementation
    SUCCEED();
}

// Test that aMin <= aMax and bMin <= bMax
TEST_F(GfxLabColorSpaceTest_450, RangeConsistency_450) {
    EXPECT_LE(labCS->getAMin(), labCS->getAMax());
    EXPECT_LE(labCS->getBMin(), labCS->getBMax());
}

// Test that whiteY is positive (physical constraint)
TEST_F(GfxLabColorSpaceTest_450, WhiteYPositive_450) {
    EXPECT_GT(labCS->getWhiteY(), 0.0);
}
