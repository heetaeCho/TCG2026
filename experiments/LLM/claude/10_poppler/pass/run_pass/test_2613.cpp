#include <gtest/gtest.h>
#include <cmath>

// Replicate the necessary definitions from the Splash codebase
typedef double SplashCoord;

#define splashCeil(x) ((int)ceil(x))
#define splashFloor(x) ((int)floor(x))

#define splashAAGamma 1.5

static inline int imgCoordMungeLowerC(SplashCoord x, bool glyphMode)
{
    return glyphMode ? (splashCeil(x + 0.5) - 1) : splashFloor(x);
}

// Test fixture
class ImgCoordMungeLowerCTest_2613 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== glyphMode == false (splashFloor path) ====================

TEST_F(ImgCoordMungeLowerCTest_2613, NonGlyphMode_PositiveInteger_2613)
{
    // splashFloor(5.0) = 5
    EXPECT_EQ(5, imgCoordMungeLowerC(5.0, false));
}

TEST_F(ImgCoordMungeLowerCTest_2613, NonGlyphMode_PositiveFraction_2613)
{
    // splashFloor(5.7) = 5
    EXPECT_EQ(5, imgCoordMungeLowerC(5.7, false));
}

TEST_F(ImgCoordMungeLowerCTest_2613, NonGlyphMode_PositiveSmallFraction_2613)
{
    // splashFloor(5.1) = 5
    EXPECT_EQ(5, imgCoordMungeLowerC(5.1, false));
}

TEST_F(ImgCoordMungeLowerCTest_2613, NonGlyphMode_Zero_2613)
{
    // splashFloor(0.0) = 0
    EXPECT_EQ(0, imgCoordMungeLowerC(0.0, false));
}

TEST_F(ImgCoordMungeLowerCTest_2613, NonGlyphMode_NegativeInteger_2613)
{
    // splashFloor(-3.0) = -3
    EXPECT_EQ(-3, imgCoordMungeLowerC(-3.0, false));
}

TEST_F(ImgCoordMungeLowerCTest_2613, NonGlyphMode_NegativeFraction_2613)
{
    // splashFloor(-3.2) = -4
    EXPECT_EQ(-4, imgCoordMungeLowerC(-3.2, false));
}

TEST_F(ImgCoordMungeLowerCTest_2613, NonGlyphMode_NegativeHalf_2613)
{
    // splashFloor(-0.5) = -1
    EXPECT_EQ(-1, imgCoordMungeLowerC(-0.5, false));
}

TEST_F(ImgCoordMungeLowerCTest_2613, NonGlyphMode_PositiveHalf_2613)
{
    // splashFloor(0.5) = 0
    EXPECT_EQ(0, imgCoordMungeLowerC(0.5, false));
}

TEST_F(ImgCoordMungeLowerCTest_2613, NonGlyphMode_LargePositive_2613)
{
    // splashFloor(1000000.9) = 1000000
    EXPECT_EQ(1000000, imgCoordMungeLowerC(1000000.9, false));
}

TEST_F(ImgCoordMungeLowerCTest_2613, NonGlyphMode_LargeNegative_2613)
{
    // splashFloor(-1000000.1) = -1000001
    EXPECT_EQ(-1000001, imgCoordMungeLowerC(-1000000.1, false));
}

TEST_F(ImgCoordMungeLowerCTest_2613, NonGlyphMode_VerySmallPositive_2613)
{
    // splashFloor(0.0001) = 0
    EXPECT_EQ(0, imgCoordMungeLowerC(0.0001, false));
}

TEST_F(ImgCoordMungeLowerCTest_2613, NonGlyphMode_VerySmallNegative_2613)
{
    // splashFloor(-0.0001) = -1
    EXPECT_EQ(-1, imgCoordMungeLowerC(-0.0001, false));
}

// ==================== glyphMode == true (splashCeil(x+0.5) - 1 path) ====================

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_PositiveInteger_2613)
{
    // x=5.0, x+0.5=5.5, ceil(5.5)=6, 6-1=5
    EXPECT_EQ(5, imgCoordMungeLowerC(5.0, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_PositiveFraction_2613)
{
    // x=5.7, x+0.5=6.2, ceil(6.2)=7, 7-1=6
    EXPECT_EQ(6, imgCoordMungeLowerC(5.7, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_PositiveSmallFraction_2613)
{
    // x=5.1, x+0.5=5.6, ceil(5.6)=6, 6-1=5
    EXPECT_EQ(5, imgCoordMungeLowerC(5.1, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_Zero_2613)
{
    // x=0.0, x+0.5=0.5, ceil(0.5)=1, 1-1=0
    EXPECT_EQ(0, imgCoordMungeLowerC(0.0, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_NegativeInteger_2613)
{
    // x=-3.0, x+0.5=-2.5, ceil(-2.5)=-2, -2-1=-3
    EXPECT_EQ(-3, imgCoordMungeLowerC(-3.0, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_NegativeFraction_2613)
{
    // x=-3.2, x+0.5=-2.7, ceil(-2.7)=-2, -2-1=-3
    EXPECT_EQ(-3, imgCoordMungeLowerC(-3.2, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_NegativeHalf_2613)
{
    // x=-0.5, x+0.5=0.0, ceil(0.0)=0, 0-1=-1
    EXPECT_EQ(-1, imgCoordMungeLowerC(-0.5, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_PositiveHalf_2613)
{
    // x=0.5, x+0.5=1.0, ceil(1.0)=1, 1-1=0
    EXPECT_EQ(0, imgCoordMungeLowerC(0.5, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_ExactIntegerAfterAdd_2613)
{
    // x=2.5, x+0.5=3.0, ceil(3.0)=3, 3-1=2
    EXPECT_EQ(2, imgCoordMungeLowerC(2.5, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_NearIntegerBelow_2613)
{
    // x=2.499, x+0.5=2.999, ceil(2.999)=3, 3-1=2
    EXPECT_EQ(2, imgCoordMungeLowerC(2.499, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_NearIntegerAbove_2613)
{
    // x=2.501, x+0.5=3.001, ceil(3.001)=4, 4-1=3
    EXPECT_EQ(3, imgCoordMungeLowerC(2.501, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_LargePositive_2613)
{
    // x=1000000.0, x+0.5=1000000.5, ceil(1000000.5)=1000001, -1=1000000
    EXPECT_EQ(1000000, imgCoordMungeLowerC(1000000.0, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_LargeNegative_2613)
{
    // x=-1000000.0, x+0.5=-999999.5, ceil(-999999.5)=-999999, -1=-1000000
    EXPECT_EQ(-1000000, imgCoordMungeLowerC(-1000000.0, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_VerySmallPositive_2613)
{
    // x=0.0001, x+0.5=0.5001, ceil(0.5001)=1, 1-1=0
    EXPECT_EQ(0, imgCoordMungeLowerC(0.0001, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_VerySmallNegative_2613)
{
    // x=-0.0001, x+0.5=0.4999, ceil(0.4999)=1, 1-1=0
    EXPECT_EQ(0, imgCoordMungeLowerC(-0.0001, true));
}

// ==================== Comparing glyphMode true vs false ====================

TEST_F(ImgCoordMungeLowerCTest_2613, CompareGlyphModes_IntegerInput_2613)
{
    // For integer inputs, both modes should give the same result
    EXPECT_EQ(imgCoordMungeLowerC(3.0, false), imgCoordMungeLowerC(3.0, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, CompareGlyphModes_DifferentResults_2613)
{
    // For x=5.7: non-glyph gives 5, glyph gives 6 — they differ
    int nonGlyph = imgCoordMungeLowerC(5.7, false);
    int glyph = imgCoordMungeLowerC(5.7, true);
    EXPECT_EQ(5, nonGlyph);
    EXPECT_EQ(6, glyph);
    EXPECT_NE(nonGlyph, glyph);
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_NegativeOnePointFive_2613)
{
    // x=-1.5, x+0.5=-1.0, ceil(-1.0)=-1, -1-1=-2
    EXPECT_EQ(-2, imgCoordMungeLowerC(-1.5, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, NonGlyphMode_OnePoint999_2613)
{
    // splashFloor(1.999) = 1
    EXPECT_EQ(1, imgCoordMungeLowerC(1.999, false));
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_OnePoint999_2613)
{
    // x=1.999, x+0.5=2.499, ceil(2.499)=3, 3-1=2
    EXPECT_EQ(2, imgCoordMungeLowerC(1.999, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, NonGlyphMode_NegativeOne_2613)
{
    // splashFloor(-1.0) = -1
    EXPECT_EQ(-1, imgCoordMungeLowerC(-1.0, false));
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_NegativeOne_2613)
{
    // x=-1.0, x+0.5=-0.5, ceil(-0.5)=0, 0-1=-1
    EXPECT_EQ(-1, imgCoordMungeLowerC(-1.0, true));
}

// ==================== Boundary: x + 0.5 is exactly an integer in glyph mode ====================

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_XPlusHalfExactlyZero_2613)
{
    // x=-0.5, x+0.5=0.0, ceil(0.0)=0, 0-1=-1
    EXPECT_EQ(-1, imgCoordMungeLowerC(-0.5, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_XPlusHalfExactlyOne_2613)
{
    // x=0.5, x+0.5=1.0, ceil(1.0)=1, 1-1=0
    EXPECT_EQ(0, imgCoordMungeLowerC(0.5, true));
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphMode_XPlusHalfExactlyNegOne_2613)
{
    // x=-1.5, x+0.5=-1.0, ceil(-1.0)=-1, -1-1=-2
    EXPECT_EQ(-2, imgCoordMungeLowerC(-1.5, true));
}
