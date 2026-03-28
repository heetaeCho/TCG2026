#include <gtest/gtest.h>
#include <cmath>

// Reproduce the necessary types and functions from Splash headers
typedef double SplashCoord;

static inline int splashCeil(SplashCoord x) {
    return (int)ceil(x);
}

static inline int splashFloor(SplashCoord x) {
    return (int)floor(x);
}

// The function under test, copied from the provided partial code
static inline int imgCoordMungeUpperC(SplashCoord x, bool glyphMode) {
    return glyphMode ? (splashCeil(x + 0.5) - 1) : (splashFloor(x) + 1);
}

// Test fixture
class ImgCoordMungeUpperCTest_2614 : public ::testing::Test {
protected:
};

// ============================================================
// Tests for glyphMode = true
// ============================================================

TEST_F(ImgCoordMungeUpperCTest_2614, GlyphMode_IntegerInput_Zero_2614) {
    // x = 0.0, glyphMode = true
    // ceil(0.0 + 0.5) - 1 = ceil(0.5) - 1 = 1 - 1 = 0
    EXPECT_EQ(0, imgCoordMungeUpperC(0.0, true));
}

TEST_F(ImgCoordMungeUpperCTest_2614, GlyphMode_IntegerInput_Positive_2614) {
    // x = 3.0, glyphMode = true
    // ceil(3.0 + 0.5) - 1 = ceil(3.5) - 1 = 4 - 1 = 3
    EXPECT_EQ(3, imgCoordMungeUpperC(3.0, true));
}

TEST_F(ImgCoordMungeUpperCTest_2614, GlyphMode_IntegerInput_Negative_2614) {
    // x = -3.0, glyphMode = true
    // ceil(-3.0 + 0.5) - 1 = ceil(-2.5) - 1 = -2 - 1 = -3
    EXPECT_EQ(-3, imgCoordMungeUpperC(-3.0, true));
}

TEST_F(ImgCoordMungeUpperCTest_2614, GlyphMode_HalfInput_2614) {
    // x = 2.5, glyphMode = true
    // ceil(2.5 + 0.5) - 1 = ceil(3.0) - 1 = 3 - 1 = 2
    EXPECT_EQ(2, imgCoordMungeUpperC(2.5, true));
}

TEST_F(ImgCoordMungeUpperCTest_2614, GlyphMode_FractionInput_2614) {
    // x = 2.3, glyphMode = true
    // ceil(2.3 + 0.5) - 1 = ceil(2.8) - 1 = 3 - 1 = 2
    EXPECT_EQ(2, imgCoordMungeUpperC(2.3, true));
}

TEST_F(ImgCoordMungeUpperCTest_2614, GlyphMode_FractionInputJustAboveHalf_2614) {
    // x = 2.51, glyphMode = true
    // ceil(2.51 + 0.5) - 1 = ceil(3.01) - 1 = 4 - 1 = 3
    EXPECT_EQ(3, imgCoordMungeUpperC(2.51, true));
}

TEST_F(ImgCoordMungeUpperCTest_2614, GlyphMode_NegativeFraction_2614) {
    // x = -1.7, glyphMode = true
    // ceil(-1.7 + 0.5) - 1 = ceil(-1.2) - 1 = -1 - 1 = -2
    EXPECT_EQ(-2, imgCoordMungeUpperC(-1.7, true));
}

TEST_F(ImgCoordMungeUpperCTest_2614, GlyphMode_NegativeHalf_2614) {
    // x = -0.5, glyphMode = true
    // ceil(-0.5 + 0.5) - 1 = ceil(0.0) - 1 = 0 - 1 = -1
    EXPECT_EQ(-1, imgCoordMungeUpperC(-0.5, true));
}

TEST_F(ImgCoordMungeUpperCTest_2614, GlyphMode_VerySmallPositive_2614) {
    // x = 0.01, glyphMode = true
    // ceil(0.01 + 0.5) - 1 = ceil(0.51) - 1 = 1 - 1 = 0
    EXPECT_EQ(0, imgCoordMungeUpperC(0.01, true));
}

TEST_F(ImgCoordMungeUpperCTest_2614, GlyphMode_VerySmallNegative_2614) {
    // x = -0.01, glyphMode = true
    // ceil(-0.01 + 0.5) - 1 = ceil(0.49) - 1 = 1 - 1 = 0
    EXPECT_EQ(0, imgCoordMungeUpperC(-0.01, true));
}

TEST_F(ImgCoordMungeUpperCTest_2614, GlyphMode_LargePositive_2614) {
    // x = 1000.0, glyphMode = true
    // ceil(1000.0 + 0.5) - 1 = ceil(1000.5) - 1 = 1001 - 1 = 1000
    EXPECT_EQ(1000, imgCoordMungeUpperC(1000.0, true));
}

TEST_F(ImgCoordMungeUpperCTest_2614, GlyphMode_LargeNegative_2614) {
    // x = -1000.0, glyphMode = true
    // ceil(-1000.0 + 0.5) - 1 = ceil(-999.5) - 1 = -999 - 1 = -1000
    EXPECT_EQ(-1000, imgCoordMungeUpperC(-1000.0, true));
}

// ============================================================
// Tests for glyphMode = false
// ============================================================

TEST_F(ImgCoordMungeUpperCTest_2614, NonGlyphMode_IntegerInput_Zero_2614) {
    // x = 0.0, glyphMode = false
    // floor(0.0) + 1 = 0 + 1 = 1
    EXPECT_EQ(1, imgCoordMungeUpperC(0.0, false));
}

TEST_F(ImgCoordMungeUpperCTest_2614, NonGlyphMode_IntegerInput_Positive_2614) {
    // x = 3.0, glyphMode = false
    // floor(3.0) + 1 = 3 + 1 = 4
    EXPECT_EQ(4, imgCoordMungeUpperC(3.0, false));
}

TEST_F(ImgCoordMungeUpperCTest_2614, NonGlyphMode_IntegerInput_Negative_2614) {
    // x = -3.0, glyphMode = false
    // floor(-3.0) + 1 = -3 + 1 = -2
    EXPECT_EQ(-2, imgCoordMungeUpperC(-3.0, false));
}

TEST_F(ImgCoordMungeUpperCTest_2614, NonGlyphMode_FractionInput_2614) {
    // x = 2.3, glyphMode = false
    // floor(2.3) + 1 = 2 + 1 = 3
    EXPECT_EQ(3, imgCoordMungeUpperC(2.3, false));
}

TEST_F(ImgCoordMungeUpperCTest_2614, NonGlyphMode_HalfInput_2614) {
    // x = 2.5, glyphMode = false
    // floor(2.5) + 1 = 2 + 1 = 3
    EXPECT_EQ(3, imgCoordMungeUpperC(2.5, false));
}

TEST_F(ImgCoordMungeUpperCTest_2614, NonGlyphMode_JustBelowInteger_2614) {
    // x = 2.999, glyphMode = false
    // floor(2.999) + 1 = 2 + 1 = 3
    EXPECT_EQ(3, imgCoordMungeUpperC(2.999, false));
}

TEST_F(ImgCoordMungeUpperCTest_2614, NonGlyphMode_JustAboveInteger_2614) {
    // x = 3.001, glyphMode = false
    // floor(3.001) + 1 = 3 + 1 = 4
    EXPECT_EQ(4, imgCoordMungeUpperC(3.001, false));
}

TEST_F(ImgCoordMungeUpperCTest_2614, NonGlyphMode_NegativeFraction_2614) {
    // x = -1.7, glyphMode = false
    // floor(-1.7) + 1 = -2 + 1 = -1
    EXPECT_EQ(-1, imgCoordMungeUpperC(-1.7, false));
}

TEST_F(ImgCoordMungeUpperCTest_2614, NonGlyphMode_NegativeHalf_2614) {
    // x = -0.5, glyphMode = false
    // floor(-0.5) + 1 = -1 + 1 = 0
    EXPECT_EQ(0, imgCoordMungeUpperC(-0.5, false));
}

TEST_F(ImgCoordMungeUpperCTest_2614, NonGlyphMode_VerySmallPositive_2614) {
    // x = 0.01, glyphMode = false
    // floor(0.01) + 1 = 0 + 1 = 1
    EXPECT_EQ(1, imgCoordMungeUpperC(0.01, false));
}

TEST_F(ImgCoordMungeUpperCTest_2614, NonGlyphMode_VerySmallNegative_2614) {
    // x = -0.01, glyphMode = false
    // floor(-0.01) + 1 = -1 + 1 = 0
    EXPECT_EQ(0, imgCoordMungeUpperC(-0.01, false));
}

TEST_F(ImgCoordMungeUpperCTest_2614, NonGlyphMode_LargePositive_2614) {
    // x = 1000.0, glyphMode = false
    // floor(1000.0) + 1 = 1000 + 1 = 1001
    EXPECT_EQ(1001, imgCoordMungeUpperC(1000.0, false));
}

TEST_F(ImgCoordMungeUpperCTest_2614, NonGlyphMode_LargeNegative_2614) {
    // x = -1000.0, glyphMode = false
    // floor(-1000.0) + 1 = -1000 + 1 = -999
    EXPECT_EQ(-999, imgCoordMungeUpperC(-1000.0, false));
}

// ============================================================
// Comparison tests between modes
// ============================================================

TEST_F(ImgCoordMungeUpperCTest_2614, ModeComparison_IntegerInput_2614) {
    // For integer x, glyphMode=true gives x, glyphMode=false gives x+1
    SplashCoord x = 5.0;
    int glyphResult = imgCoordMungeUpperC(x, true);
    int nonGlyphResult = imgCoordMungeUpperC(x, false);
    EXPECT_EQ(5, glyphResult);
    EXPECT_EQ(6, nonGlyphResult);
    EXPECT_EQ(glyphResult + 1, nonGlyphResult);
}

TEST_F(ImgCoordMungeUpperCTest_2614, ModeComparison_FractionInput_2614) {
    // x = 1.2
    // glyphMode=true: ceil(1.7) - 1 = 2 - 1 = 1
    // glyphMode=false: floor(1.2) + 1 = 1 + 1 = 2
    EXPECT_EQ(1, imgCoordMungeUpperC(1.2, true));
    EXPECT_EQ(2, imgCoordMungeUpperC(1.2, false));
}

// ============================================================
// Boundary: x = 1.0 (exact integer)
// ============================================================

TEST_F(ImgCoordMungeUpperCTest_2614, BoundaryExactOne_GlyphMode_2614) {
    // ceil(1.0 + 0.5) - 1 = ceil(1.5) - 1 = 2 - 1 = 1
    EXPECT_EQ(1, imgCoordMungeUpperC(1.0, true));
}

TEST_F(ImgCoordMungeUpperCTest_2614, BoundaryExactOne_NonGlyphMode_2614) {
    // floor(1.0) + 1 = 1 + 1 = 2
    EXPECT_EQ(2, imgCoordMungeUpperC(1.0, false));
}

// ============================================================
// Boundary: x = -1.0 (exact negative integer)
// ============================================================

TEST_F(ImgCoordMungeUpperCTest_2614, BoundaryExactNegOne_GlyphMode_2614) {
    // ceil(-1.0 + 0.5) - 1 = ceil(-0.5) - 1 = 0 - 1 = -1
    EXPECT_EQ(-1, imgCoordMungeUpperC(-1.0, true));
}

TEST_F(ImgCoordMungeUpperCTest_2614, BoundaryExactNegOne_NonGlyphMode_2614) {
    // floor(-1.0) + 1 = -1 + 1 = 0
    EXPECT_EQ(0, imgCoordMungeUpperC(-1.0, false));
}
