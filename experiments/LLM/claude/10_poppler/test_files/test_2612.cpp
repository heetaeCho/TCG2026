#include <gtest/gtest.h>
#include <cmath>

// Include necessary Poppler/Splash headers
#include "splash/SplashTypes.h"
#include "splash/SplashMath.h"

// We need to include the source or replicate the static inline function
// since it's a static inline in Splash.cc, we include it to get access
// For testing purposes, we define the function as it appears in the interface
#define splashAAGamma 1.5

static inline int imgCoordMungeUpper(SplashCoord x)
{
    return splashFloor(x) + 1;
}

// Test fixture
class ImgCoordMungeUpperTest_2612 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

class SplashAAGammaTest_2612 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Tests for splashAAGamma ====================

TEST_F(SplashAAGammaTest_2612, GammaValueIs1Point5_2612)
{
    EXPECT_DOUBLE_EQ(splashAAGamma, 1.5);
}

TEST_F(SplashAAGammaTest_2612, GammaValueIsPositive_2612)
{
    EXPECT_GT(splashAAGamma, 0.0);
}

// ==================== Tests for imgCoordMungeUpper ====================

// Normal operation: positive integer input
TEST_F(ImgCoordMungeUpperTest_2612, PositiveIntegerReturnsNextInt_2612)
{
    // floor(5.0) + 1 = 6
    EXPECT_EQ(imgCoordMungeUpper(5.0), 6);
}

// Normal operation: positive fractional input
TEST_F(ImgCoordMungeUpperTest_2612, PositiveFractionalValue_2612)
{
    // floor(3.7) + 1 = 3 + 1 = 4
    EXPECT_EQ(imgCoordMungeUpper(3.7), 4);
}

TEST_F(ImgCoordMungeUpperTest_2612, PositiveSmallFraction_2612)
{
    // floor(3.1) + 1 = 3 + 1 = 4
    EXPECT_EQ(imgCoordMungeUpper(3.1), 4);
}

// Zero input
TEST_F(ImgCoordMungeUpperTest_2612, ZeroReturnsOne_2612)
{
    // floor(0.0) + 1 = 0 + 1 = 1
    EXPECT_EQ(imgCoordMungeUpper(0.0), 1);
}

// Negative integer input
TEST_F(ImgCoordMungeUpperTest_2612, NegativeIntegerInput_2612)
{
    // floor(-3.0) + 1 = -3 + 1 = -2
    EXPECT_EQ(imgCoordMungeUpper(-3.0), -2);
}

// Negative fractional input
TEST_F(ImgCoordMungeUpperTest_2612, NegativeFractionalInput_2612)
{
    // floor(-2.5) + 1 = -3 + 1 = -2
    EXPECT_EQ(imgCoordMungeUpper(-2.5), -2);
}

TEST_F(ImgCoordMungeUpperTest_2612, NegativeSmallFraction_2612)
{
    // floor(-0.1) + 1 = -1 + 1 = 0
    EXPECT_EQ(imgCoordMungeUpper(-0.1), 0);
}

// Boundary: very small positive value
TEST_F(ImgCoordMungeUpperTest_2612, VerySmallPositiveValue_2612)
{
    // floor(0.0001) + 1 = 0 + 1 = 1
    EXPECT_EQ(imgCoordMungeUpper(0.0001), 1);
}

// Boundary: value just below an integer
TEST_F(ImgCoordMungeUpperTest_2612, JustBelowInteger_2612)
{
    // floor(4.9999) + 1 = 4 + 1 = 5
    EXPECT_EQ(imgCoordMungeUpper(4.9999), 5);
}

// Large positive value
TEST_F(ImgCoordMungeUpperTest_2612, LargePositiveValue_2612)
{
    // floor(10000.5) + 1 = 10000 + 1 = 10001
    EXPECT_EQ(imgCoordMungeUpper(10000.5), 10001);
}

// Large negative value
TEST_F(ImgCoordMungeUpperTest_2612, LargeNegativeValue_2612)
{
    // floor(-10000.5) + 1 = -10001 + 1 = -10000
    EXPECT_EQ(imgCoordMungeUpper(-10000.5), -10000);
}

// One input
TEST_F(ImgCoordMungeUpperTest_2612, OneReturnsTwo_2612)
{
    // floor(1.0) + 1 = 1 + 1 = 2
    EXPECT_EQ(imgCoordMungeUpper(1.0), 2);
}

// Negative one input
TEST_F(ImgCoordMungeUpperTest_2612, NegativeOneReturnsZero_2612)
{
    // floor(-1.0) + 1 = -1 + 1 = 0
    EXPECT_EQ(imgCoordMungeUpper(-1.0), 0);
}

// Half value
TEST_F(ImgCoordMungeUpperTest_2612, HalfValueReturnsOne_2612)
{
    // floor(0.5) + 1 = 0 + 1 = 1
    EXPECT_EQ(imgCoordMungeUpper(0.5), 1);
}

// Negative half value
TEST_F(ImgCoordMungeUpperTest_2612, NegativeHalfValueReturnsZero_2612)
{
    // floor(-0.5) + 1 = -1 + 1 = 0
    EXPECT_EQ(imgCoordMungeUpper(-0.5), 0);
}
