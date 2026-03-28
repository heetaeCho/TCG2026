#include <gtest/gtest.h>
#include "GfxState.h"

class GfxLabColorSpaceTest_457 : public ::testing::Test {
protected:
    void SetUp() override {
        labCS = std::make_unique<GfxLabColorSpace>();
    }

    void TearDown() override {
        labCS.reset();
    }

    std::unique_ptr<GfxLabColorSpace> labCS;
};

// Test that default constructor creates a valid object
TEST_F(GfxLabColorSpaceTest_457, DefaultConstruction_457) {
    ASSERT_NE(labCS, nullptr);
}

// Test getMode returns the correct color space mode for Lab
TEST_F(GfxLabColorSpaceTest_457, GetModeReturnsLab_457) {
    EXPECT_EQ(labCS->getMode(), csLab);
}

// Test getNComps returns 3 for Lab color space (L*, a*, b*)
TEST_F(GfxLabColorSpaceTest_457, GetNCompsReturnsThree_457) {
    EXPECT_EQ(labCS->getNComps(), 3);
}

// Test getBMin returns the default bMin value
TEST_F(GfxLabColorSpaceTest_457, GetBMinDefaultValue_457) {
    double bMin = labCS->getBMin();
    // Default Lab color space should have some defined bMin
    // Typically for Lab, default range is -100 to 100
    EXPECT_LE(bMin, labCS->getBMax());
}

// Test getBMax returns a value >= getBMin
TEST_F(GfxLabColorSpaceTest_457, GetBMaxGreaterOrEqualBMin_457) {
    EXPECT_GE(labCS->getBMax(), labCS->getBMin());
}

// Test getAMin returns the default aMin value
TEST_F(GfxLabColorSpaceTest_457, GetAMinDefaultValue_457) {
    double aMin = labCS->getAMin();
    EXPECT_LE(aMin, labCS->getAMax());
}

// Test getAMax returns a value >= getAMin
TEST_F(GfxLabColorSpaceTest_457, GetAMaxGreaterOrEqualAMin_457) {
    EXPECT_GE(labCS->getAMax(), labCS->getAMin());
}

// Test getWhiteX returns a non-negative value
TEST_F(GfxLabColorSpaceTest_457, GetWhiteXNonNegative_457) {
    EXPECT_GE(labCS->getWhiteX(), 0.0);
}

// Test getWhiteY returns a non-negative value
TEST_F(GfxLabColorSpaceTest_457, GetWhiteYNonNegative_457) {
    EXPECT_GE(labCS->getWhiteY(), 0.0);
}

// Test getWhiteZ returns a non-negative value
TEST_F(GfxLabColorSpaceTest_457, GetWhiteZNonNegative_457) {
    EXPECT_GE(labCS->getWhiteZ(), 0.0);
}

// Test getBlackX returns a non-negative value (black point values are >= 0)
TEST_F(GfxLabColorSpaceTest_457, GetBlackXNonNegative_457) {
    EXPECT_GE(labCS->getBlackX(), 0.0);
}

// Test getBlackY returns a non-negative value
TEST_F(GfxLabColorSpaceTest_457, GetBlackYNonNegative_457) {
    EXPECT_GE(labCS->getBlackY(), 0.0);
}

// Test getBlackZ returns a non-negative value
TEST_F(GfxLabColorSpaceTest_457, GetBlackZNonNegative_457) {
    EXPECT_GE(labCS->getBlackZ(), 0.0);
}

// Test copy creates a valid copy
TEST_F(GfxLabColorSpaceTest_457, CopyCreatesValidObject_457) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csLab);
    EXPECT_EQ(copied->getNComps(), 3);
}

// Test that copy preserves bMin
TEST_F(GfxLabColorSpaceTest_457, CopyPreservesBMin_457) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_DOUBLE_EQ(copiedLab->getBMin(), labCS->getBMin());
}

// Test that copy preserves bMax
TEST_F(GfxLabColorSpaceTest_457, CopyPreservesBMax_457) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_DOUBLE_EQ(copiedLab->getBMax(), labCS->getBMax());
}

// Test that copy preserves aMin
TEST_F(GfxLabColorSpaceTest_457, CopyPreservesAMin_457) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_DOUBLE_EQ(copiedLab->getAMin(), labCS->getAMin());
}

// Test that copy preserves aMax
TEST_F(GfxLabColorSpaceTest_457, CopyPreservesAMax_457) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_DOUBLE_EQ(copiedLab->getAMax(), labCS->getAMax());
}

// Test that copy preserves white point
TEST_F(GfxLabColorSpaceTest_457, CopyPreservesWhitePoint_457) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_DOUBLE_EQ(copiedLab->getWhiteX(), labCS->getWhiteX());
    EXPECT_DOUBLE_EQ(copiedLab->getWhiteY(), labCS->getWhiteY());
    EXPECT_DOUBLE_EQ(copiedLab->getWhiteZ(), labCS->getWhiteZ());
}

// Test that copy preserves black point
TEST_F(GfxLabColorSpaceTest_457, CopyPreservesBlackPoint_457) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    EXPECT_DOUBLE_EQ(copiedLab->getBlackX(), labCS->getBlackX());
    EXPECT_DOUBLE_EQ(copiedLab->getBlackY(), labCS->getBlackY());
    EXPECT_DOUBLE_EQ(copiedLab->getBlackZ(), labCS->getBlackZ());
}

// Test getDefaultColor produces a valid color
TEST_F(GfxLabColorSpaceTest_457, GetDefaultColorProducesValidColor_457) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    // Default color should be set; for Lab, L* component should be valid
    // No crash expected
    SUCCEED();
}

// Test getGray with default color doesn't crash
TEST_F(GfxLabColorSpaceTest_457, GetGrayWithDefaultColor_457) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxGray gray;
    labCS->getGray(&color, &gray);
    // Gray value should be in valid range [0, 65535] (GfxColorComp range)
    SUCCEED();
}

// Test getRGB with default color doesn't crash
TEST_F(GfxLabColorSpaceTest_457, GetRGBWithDefaultColor_457) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxRGB rgb;
    labCS->getRGB(&color, &rgb);
    SUCCEED();
}

// Test getCMYK with default color doesn't crash
TEST_F(GfxLabColorSpaceTest_457, GetCMYKWithDefaultColor_457) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxCMYK cmyk;
    labCS->getCMYK(&color, &cmyk);
    SUCCEED();
}

// Test getDeviceN with default color doesn't crash
TEST_F(GfxLabColorSpaceTest_457, GetDeviceNWithDefaultColor_457) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    GfxColor deviceN;
    labCS->getDeviceN(&color, &deviceN);
    SUCCEED();
}

// Test getDefaultRanges doesn't crash
TEST_F(GfxLabColorSpaceTest_457, GetDefaultRangesDoesNotCrash_457) {
    double decodeLow[3];
    double decodeRange[3];
    labCS->getDefaultRanges(decodeLow, decodeRange, 255);
    // Should populate arrays without crashing
    SUCCEED();
}

// Test getDefaultRanges with maxImgPixel of 1
TEST_F(GfxLabColorSpaceTest_457, GetDefaultRangesBoundaryMaxPixelOne_457) {
    double decodeLow[3];
    double decodeRange[3];
    labCS->getDefaultRanges(decodeLow, decodeRange, 1);
    SUCCEED();
}

// Test getDefaultRanges with large maxImgPixel
TEST_F(GfxLabColorSpaceTest_457, GetDefaultRangesLargeMaxPixel_457) {
    double decodeLow[3];
    double decodeRange[3];
    labCS->getDefaultRanges(decodeLow, decodeRange, 65535);
    SUCCEED();
}

// Test that bMin and bMax define a valid range for the default ranges
TEST_F(GfxLabColorSpaceTest_457, BMinBMaxDefineValidRange_457) {
    double bMin = labCS->getBMin();
    double bMax = labCS->getBMax();
    EXPECT_LT(bMin, bMax);
}

// Test that aMin and aMax define a valid range
TEST_F(GfxLabColorSpaceTest_457, AMinAMaxDefineValidRange_457) {
    double aMin = labCS->getAMin();
    double aMax = labCS->getAMax();
    EXPECT_LT(aMin, aMax);
}
