#include <gtest/gtest.h>
#include "GfxState.h"

class GfxLabColorSpaceTest_458 : public ::testing::Test {
protected:
    void SetUp() override {
        labCS = std::make_unique<GfxLabColorSpace>();
    }

    void TearDown() override {
        labCS.reset();
    }

    std::unique_ptr<GfxLabColorSpace> labCS;
};

// Test that default-constructed GfxLabColorSpace returns a valid bMax value
TEST_F(GfxLabColorSpaceTest_458, GetBMaxDefaultValue_458) {
    double bMax = labCS->getBMax();
    // Default bMax should be a finite number
    EXPECT_FALSE(std::isnan(bMax));
    EXPECT_FALSE(std::isinf(bMax));
}

// Test that getBMin returns a value less than or equal to getBMax
TEST_F(GfxLabColorSpaceTest_458, GetBMinLessOrEqualBMax_458) {
    double bMin = labCS->getBMin();
    double bMax = labCS->getBMax();
    EXPECT_LE(bMin, bMax);
}

// Test that getAMin and getAMax are consistent
TEST_F(GfxLabColorSpaceTest_458, GetAMinLessOrEqualAMax_458) {
    double aMin = labCS->getAMin();
    double aMax = labCS->getAMax();
    EXPECT_LE(aMin, aMax);
}

// Test that default constructor produces expected default range values
// Lab color space typically has default ranges of [-100, 100] for a and b
TEST_F(GfxLabColorSpaceTest_458, DefaultRangesAreReasonable_458) {
    double aMin = labCS->getAMin();
    double aMax = labCS->getAMax();
    double bMin = labCS->getBMin();
    double bMax = labCS->getBMax();

    // Just verify they are finite and ordered
    EXPECT_TRUE(std::isfinite(aMin));
    EXPECT_TRUE(std::isfinite(aMax));
    EXPECT_TRUE(std::isfinite(bMin));
    EXPECT_TRUE(std::isfinite(bMax));
}

// Test getMode returns the correct mode for Lab color space
TEST_F(GfxLabColorSpaceTest_458, GetModeReturnsLab_458) {
    GfxColorSpaceMode mode = labCS->getMode();
    EXPECT_EQ(mode, csLab);
}

// Test getNComps returns 3 for Lab color space (L*, a*, b*)
TEST_F(GfxLabColorSpaceTest_458, GetNCompsReturnsThree_458) {
    int nComps = labCS->getNComps();
    EXPECT_EQ(nComps, 3);
}

// Test white point accessors return valid values
TEST_F(GfxLabColorSpaceTest_458, WhitePointValues_458) {
    double whiteX = labCS->getWhiteX();
    double whiteY = labCS->getWhiteY();
    double whiteZ = labCS->getWhiteZ();

    EXPECT_TRUE(std::isfinite(whiteX));
    EXPECT_TRUE(std::isfinite(whiteY));
    EXPECT_TRUE(std::isfinite(whiteZ));
}

// Test black point accessors return valid values
TEST_F(GfxLabColorSpaceTest_458, BlackPointValues_458) {
    double blackX = labCS->getBlackX();
    double blackY = labCS->getBlackY();
    double blackZ = labCS->getBlackZ();

    EXPECT_TRUE(std::isfinite(blackX));
    EXPECT_TRUE(std::isfinite(blackY));
    EXPECT_TRUE(std::isfinite(blackZ));
}

// Test that copy creates a valid object with same bMax
TEST_F(GfxLabColorSpaceTest_458, CopyPreservesBMax_458) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    
    EXPECT_DOUBLE_EQ(labCS->getBMax(), copiedLab->getBMax());
}

// Test that copy preserves all range values
TEST_F(GfxLabColorSpaceTest_458, CopyPreservesAllRanges_458) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    
    EXPECT_DOUBLE_EQ(labCS->getAMin(), copiedLab->getAMin());
    EXPECT_DOUBLE_EQ(labCS->getAMax(), copiedLab->getAMax());
    EXPECT_DOUBLE_EQ(labCS->getBMin(), copiedLab->getBMin());
    EXPECT_DOUBLE_EQ(labCS->getBMax(), copiedLab->getBMax());
}

// Test that copy preserves white and black points
TEST_F(GfxLabColorSpaceTest_458, CopyPreservesWhiteAndBlackPoints_458) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    
    GfxLabColorSpace* copiedLab = dynamic_cast<GfxLabColorSpace*>(copied.get());
    ASSERT_NE(copiedLab, nullptr);
    
    EXPECT_DOUBLE_EQ(labCS->getWhiteX(), copiedLab->getWhiteX());
    EXPECT_DOUBLE_EQ(labCS->getWhiteY(), copiedLab->getWhiteY());
    EXPECT_DOUBLE_EQ(labCS->getWhiteZ(), copiedLab->getWhiteZ());
    EXPECT_DOUBLE_EQ(labCS->getBlackX(), copiedLab->getBlackX());
    EXPECT_DOUBLE_EQ(labCS->getBlackY(), copiedLab->getBlackY());
    EXPECT_DOUBLE_EQ(labCS->getBlackZ(), copiedLab->getBlackZ());
}

// Test getDefaultColor produces a valid color
TEST_F(GfxLabColorSpaceTest_458, GetDefaultColorDoesNotCrash_458) {
    GfxColor color;
    EXPECT_NO_FATAL_FAILURE(labCS->getDefaultColor(&color));
}

// Test getGray with default color
TEST_F(GfxLabColorSpaceTest_458, GetGrayWithDefaultColor_458) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    
    GfxGray gray;
    EXPECT_NO_FATAL_FAILURE(labCS->getGray(&color, &gray));
}

// Test getRGB with default color
TEST_F(GfxLabColorSpaceTest_458, GetRGBWithDefaultColor_458) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    
    GfxRGB rgb;
    EXPECT_NO_FATAL_FAILURE(labCS->getRGB(&color, &rgb));
}

// Test getCMYK with default color
TEST_F(GfxLabColorSpaceTest_458, GetCMYKWithDefaultColor_458) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    
    GfxCMYK cmyk;
    EXPECT_NO_FATAL_FAILURE(labCS->getCMYK(&color, &cmyk));
}

// Test getDeviceN with default color
TEST_F(GfxLabColorSpaceTest_458, GetDeviceNWithDefaultColor_458) {
    GfxColor color;
    labCS->getDefaultColor(&color);
    
    GfxColor deviceN;
    EXPECT_NO_FATAL_FAILURE(labCS->getDeviceN(&color, &deviceN));
}

// Test getDefaultRanges does not crash
TEST_F(GfxLabColorSpaceTest_458, GetDefaultRangesDoesNotCrash_458) {
    double decodeLow[3];
    double decodeRange[3];
    int maxImgPixel = 255;
    EXPECT_NO_FATAL_FAILURE(labCS->getDefaultRanges(decodeLow, decodeRange, maxImgPixel));
}

// Test getDefaultRanges produces finite values
TEST_F(GfxLabColorSpaceTest_458, GetDefaultRangesProducesFiniteValues_458) {
    double decodeLow[3];
    double decodeRange[3];
    int maxImgPixel = 255;
    labCS->getDefaultRanges(decodeLow, decodeRange, maxImgPixel);
    
    for (int i = 0; i < 3; i++) {
        EXPECT_TRUE(std::isfinite(decodeLow[i])) << "decodeLow[" << i << "] is not finite";
        EXPECT_TRUE(std::isfinite(decodeRange[i])) << "decodeRange[" << i << "] is not finite";
    }
}

// Test copy mode is preserved
TEST_F(GfxLabColorSpaceTest_458, CopyPreservesMode_458) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csLab);
}

// Test copy nComps is preserved
TEST_F(GfxLabColorSpaceTest_458, CopyPreservesNComps_458) {
    auto copied = labCS->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNComps(), 3);
}

// Test boundary: getDefaultRanges with maxImgPixel = 0
TEST_F(GfxLabColorSpaceTest_458, GetDefaultRangesWithZeroMaxPixel_458) {
    double decodeLow[3];
    double decodeRange[3];
    EXPECT_NO_FATAL_FAILURE(labCS->getDefaultRanges(decodeLow, decodeRange, 0));
}

// Test boundary: getDefaultRanges with maxImgPixel = 1
TEST_F(GfxLabColorSpaceTest_458, GetDefaultRangesWithOneMaxPixel_458) {
    double decodeLow[3];
    double decodeRange[3];
    EXPECT_NO_FATAL_FAILURE(labCS->getDefaultRanges(decodeLow, decodeRange, 1));
}

// Test boundary: getDefaultRanges with large maxImgPixel
TEST_F(GfxLabColorSpaceTest_458, GetDefaultRangesWithLargeMaxPixel_458) {
    double decodeLow[3];
    double decodeRange[3];
    EXPECT_NO_FATAL_FAILURE(labCS->getDefaultRanges(decodeLow, decodeRange, 65535));
}
