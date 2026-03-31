#include <gtest/gtest.h>
#include "CairoOutputDev.h"

class CairoOutputDevTest_1725 : public ::testing::Test {
protected:
    CairoOutputDev dev;
};

// ============================================================
// Tests for useShadedFills
// ============================================================

TEST_F(CairoOutputDevTest_1725, UseShadedFills_Type1_ReturnsTrue_1725) {
    EXPECT_TRUE(dev.useShadedFills(1));
}

TEST_F(CairoOutputDevTest_1725, UseShadedFills_Type2_ReturnsTrue_1725) {
    EXPECT_TRUE(dev.useShadedFills(2));
}

TEST_F(CairoOutputDevTest_1725, UseShadedFills_Type3_ReturnsTrue_1725) {
    EXPECT_TRUE(dev.useShadedFills(3));
}

TEST_F(CairoOutputDevTest_1725, UseShadedFills_Type4_ReturnsTrue_1725) {
    EXPECT_TRUE(dev.useShadedFills(4));
}

TEST_F(CairoOutputDevTest_1725, UseShadedFills_Type5_ReturnsTrue_1725) {
    EXPECT_TRUE(dev.useShadedFills(5));
}

TEST_F(CairoOutputDevTest_1725, UseShadedFills_Type6_ReturnsTrue_1725) {
    EXPECT_TRUE(dev.useShadedFills(6));
}

TEST_F(CairoOutputDevTest_1725, UseShadedFills_Type7_ReturnsTrue_1725) {
    EXPECT_TRUE(dev.useShadedFills(7));
}

TEST_F(CairoOutputDevTest_1725, UseShadedFills_Type8_ReturnsFalse_1725) {
    EXPECT_FALSE(dev.useShadedFills(8));
}

TEST_F(CairoOutputDevTest_1725, UseShadedFills_Type0_ReturnsTrue_1725) {
    EXPECT_TRUE(dev.useShadedFills(0));
}

TEST_F(CairoOutputDevTest_1725, UseShadedFills_NegativeType_ReturnsTrue_1725) {
    EXPECT_TRUE(dev.useShadedFills(-1));
}

TEST_F(CairoOutputDevTest_1725, UseShadedFills_LargeType_ReturnsFalse_1725) {
    EXPECT_FALSE(dev.useShadedFills(100));
}

TEST_F(CairoOutputDevTest_1725, UseShadedFills_VeryNegativeType_ReturnsTrue_1725) {
    EXPECT_TRUE(dev.useShadedFills(-100));
}

// ============================================================
// Tests for upsideDown
// ============================================================

TEST_F(CairoOutputDevTest_1725, UpsideDown_ReturnsFalse_1725) {
    // CairoOutputDev typically returns false for upsideDown
    // (device coordinate system has origin at top-left)
    bool result = dev.upsideDown();
    // Just verify it returns a consistent boolean value
    EXPECT_FALSE(result) << "upsideDown() should return false for Cairo output";
}

// ============================================================
// Tests for useDrawChar
// ============================================================

TEST_F(CairoOutputDevTest_1725, UseDrawChar_ReturnsTrue_1725) {
    EXPECT_TRUE(dev.useDrawChar());
}

// ============================================================
// Tests for useTilingPatternFill
// ============================================================

TEST_F(CairoOutputDevTest_1725, UseTilingPatternFill_ReturnsTrue_1725) {
    EXPECT_TRUE(dev.useTilingPatternFill());
}

// ============================================================
// Tests for useFillColorStop
// ============================================================

TEST_F(CairoOutputDevTest_1725, UseFillColorStop_ReturnsTrue_1725) {
    EXPECT_TRUE(dev.useFillColorStop());
}

// ============================================================
// Tests for interpretType3Chars
// ============================================================

TEST_F(CairoOutputDevTest_1725, InterpretType3Chars_ReturnsExpected_1725) {
    // CairoOutputDev should interpret Type3 chars
    bool result = dev.interpretType3Chars();
    EXPECT_TRUE(result);
}

// ============================================================
// Tests for hasType3GlyphBBox
// ============================================================

TEST_F(CairoOutputDevTest_1725, HasType3GlyphBBox_InitiallyFalse_1725) {
    // Before any type3D1 call, there should be no bbox
    EXPECT_FALSE(dev.hasType3GlyphBBox());
}

// ============================================================
// Tests for type3GlyphHasColor
// ============================================================

TEST_F(CairoOutputDevTest_1725, Type3GlyphHasColor_InitiallyFalse_1725) {
    EXPECT_FALSE(dev.type3GlyphHasColor());
}

// ============================================================
// Tests for getType3GlyphWidth
// ============================================================

TEST_F(CairoOutputDevTest_1725, GetType3GlyphWidth_InitialValues_1725) {
    double wx = -1.0, wy = -1.0;
    dev.getType3GlyphWidth(&wx, &wy);
    // Initially should be 0 or some default
    EXPECT_DOUBLE_EQ(wx, 0.0);
    EXPECT_DOUBLE_EQ(wy, 0.0);
}

// ============================================================
// Boundary test for useShadedFills at boundary value 7
// ============================================================

TEST_F(CairoOutputDevTest_1725, UseShadedFills_BoundaryAt7_1725) {
    EXPECT_TRUE(dev.useShadedFills(7));
    EXPECT_FALSE(dev.useShadedFills(8));
}

// ============================================================
// Tests for useShadedFills with INT_MAX
// ============================================================

TEST_F(CairoOutputDevTest_1725, UseShadedFills_IntMax_ReturnsFalse_1725) {
    EXPECT_FALSE(dev.useShadedFills(INT_MAX));
}

// ============================================================
// Tests for useShadedFills with INT_MIN
// ============================================================

TEST_F(CairoOutputDevTest_1725, UseShadedFills_IntMin_ReturnsTrue_1725) {
    EXPECT_TRUE(dev.useShadedFills(INT_MIN));
}
