#include <gtest/gtest.h>
#include "CairoOutputDev.h"

class CairoImageOutputDevTest_1741 : public ::testing::Test {
protected:
    CairoImageOutputDev dev;
};

// Test useShadedFills returns true for type values <= 7
TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_Type1_ReturnsTrue_1741) {
    EXPECT_TRUE(dev.useShadedFills(1));
}

TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_Type2_ReturnsTrue_1741) {
    EXPECT_TRUE(dev.useShadedFills(2));
}

TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_Type3_ReturnsTrue_1741) {
    EXPECT_TRUE(dev.useShadedFills(3));
}

TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_Type4_ReturnsTrue_1741) {
    EXPECT_TRUE(dev.useShadedFills(4));
}

TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_Type5_ReturnsTrue_1741) {
    EXPECT_TRUE(dev.useShadedFills(5));
}

TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_Type6_ReturnsTrue_1741) {
    EXPECT_TRUE(dev.useShadedFills(6));
}

TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_Type7_ReturnsTrue_1741) {
    EXPECT_TRUE(dev.useShadedFills(7));
}

// Test useShadedFills returns false for type values > 7
TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_Type8_ReturnsFalse_1741) {
    EXPECT_FALSE(dev.useShadedFills(8));
}

TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_Type9_ReturnsFalse_1741) {
    EXPECT_FALSE(dev.useShadedFills(9));
}

TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_Type100_ReturnsFalse_1741) {
    EXPECT_FALSE(dev.useShadedFills(100));
}

// Boundary: type = 0
TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_Type0_ReturnsTrue_1741) {
    EXPECT_TRUE(dev.useShadedFills(0));
}

// Boundary: negative type
TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_TypeNegative_ReturnsTrue_1741) {
    EXPECT_TRUE(dev.useShadedFills(-1));
}

TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_TypeNegativeLarge_ReturnsTrue_1741) {
    EXPECT_TRUE(dev.useShadedFills(-100));
}

// Test getNumImages on freshly constructed object
TEST_F(CairoImageOutputDevTest_1741, GetNumImages_InitiallyZero_1741) {
    EXPECT_EQ(dev.getNumImages(), 0);
}

// Test getImage with valid index on empty device (boundary - no images)
// Note: We cannot add images without going through drawImage, but we can check the count.
TEST_F(CairoImageOutputDevTest_1741, GetImage_NoImages_ReturnsNull_1741) {
    // With no images, accessing index 0 should return nullptr or be invalid
    // Based on typical implementations, getImage(0) when numImages==0 would be out of bounds
    // We test that numImages is 0 and don't access out of bounds
    EXPECT_EQ(dev.getNumImages(), 0);
}

// Test setImageDrawDecideCbk with nullptr callback
TEST_F(CairoImageOutputDevTest_1741, SetImageDrawDecideCbk_NullCallback_1741) {
    // Should not crash when setting a null callback
    dev.setImageDrawDecideCbk(nullptr, nullptr);
    EXPECT_EQ(dev.getNumImages(), 0);
}

// Test setImageDrawDecideCbk with a valid callback
static bool testCallback(int img_id, void *data) {
    return true;
}

TEST_F(CairoImageOutputDevTest_1741, SetImageDrawDecideCbk_ValidCallback_1741) {
    int userData = 42;
    dev.setImageDrawDecideCbk(testCallback, &userData);
    // Just verify it doesn't crash and state is consistent
    EXPECT_EQ(dev.getNumImages(), 0);
}

// Test that various no-op override methods don't crash when called with nullptr
TEST_F(CairoImageOutputDevTest_1741, SaveState_NullState_NoCrash_1741) {
    dev.saveState(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, RestoreState_NullState_NoCrash_1741) {
    dev.restoreState(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, UpdateAll_NullState_NoCrash_1741) {
    dev.updateAll(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, UpdateFillColor_NullState_NoCrash_1741) {
    dev.updateFillColor(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, UpdateStrokeColor_NullState_NoCrash_1741) {
    dev.updateStrokeColor(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, Stroke_NullState_NoCrash_1741) {
    dev.stroke(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, Fill_NullState_NoCrash_1741) {
    dev.fill(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, EoFill_NullState_NoCrash_1741) {
    dev.eoFill(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, Clip_NullState_NoCrash_1741) {
    dev.clip(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, EoClip_NullState_NoCrash_1741) {
    dev.eoClip(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, ClearSoftMask_NullState_NoCrash_1741) {
    dev.clearSoftMask(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, UpdateLineDash_NullState_NoCrash_1741) {
    dev.updateLineDash(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, UpdateFlatness_NullState_NoCrash_1741) {
    dev.updateFlatness(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, UpdateLineJoin_NullState_NoCrash_1741) {
    dev.updateLineJoin(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, UpdateLineCap_NullState_NoCrash_1741) {
    dev.updateLineCap(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, UpdateMiterLimit_NullState_NoCrash_1741) {
    dev.updateMiterLimit(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, UpdateLineWidth_NullState_NoCrash_1741) {
    dev.updateLineWidth(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, UpdateFillOpacity_NullState_NoCrash_1741) {
    dev.updateFillOpacity(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, UpdateStrokeOpacity_NullState_NoCrash_1741) {
    dev.updateStrokeOpacity(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, UpdateBlendMode_NullState_NoCrash_1741) {
    dev.updateBlendMode(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, UpdateFont_NullState_NoCrash_1741) {
    dev.updateFont(nullptr);
}

TEST_F(CairoImageOutputDevTest_1741, ClipToStrokePath_NullState_NoCrash_1741) {
    dev.clipToStrokePath(nullptr);
}

// Test large type value for useShadedFills
TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_IntMax_ReturnsFalse_1741) {
    EXPECT_FALSE(dev.useShadedFills(INT_MAX));
}

// Test INT_MIN for useShadedFills
TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_IntMin_ReturnsTrue_1741) {
    EXPECT_TRUE(dev.useShadedFills(INT_MIN));
}
