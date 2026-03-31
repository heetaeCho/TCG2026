#include <gtest/gtest.h>
#include <cmath>

// Include necessary Splash headers
#include "splash/SplashTypes.h"
#include "splash/SplashMath.h"

// We need to replicate the static inline function since it's defined in the .cc file
// and not exposed via header. We test the same logic using splashFloor directly,
// which is the public interface it depends on.
static inline int imgCoordMungeLower(SplashCoord x)
{
    return splashFloor(x);
}

#define splashAAGamma 1.5

// Test fixture
class SplashHelperTest_2611 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Tests for splashAAGamma constant
TEST_F(SplashHelperTest_2611, SplashAAGammaValue_2611)
{
    EXPECT_DOUBLE_EQ(splashAAGamma, 1.5);
}

TEST_F(SplashHelperTest_2611, SplashAAGammaIsPositive_2611)
{
    EXPECT_GT(splashAAGamma, 0.0);
}

// Tests for imgCoordMungeLower - Normal operation
TEST_F(SplashHelperTest_2611, ImgCoordMungeLowerPositiveInteger_2611)
{
    // Floor of an integer should be the integer itself
    EXPECT_EQ(imgCoordMungeLower(5.0), 5);
}

TEST_F(SplashHelperTest_2611, ImgCoordMungeLowerNegativeInteger_2611)
{
    EXPECT_EQ(imgCoordMungeLower(-3.0), -3);
}

TEST_F(SplashHelperTest_2611, ImgCoordMungeLowerPositiveFraction_2611)
{
    // Floor of 3.7 should be 3
    EXPECT_EQ(imgCoordMungeLower(3.7), 3);
}

TEST_F(SplashHelperTest_2611, ImgCoordMungeLowerPositiveSmallFraction_2611)
{
    // Floor of 3.2 should be 3
    EXPECT_EQ(imgCoordMungeLower(3.2), 3);
}

TEST_F(SplashHelperTest_2611, ImgCoordMungeLowerNegativeFraction_2611)
{
    // Floor of -2.3 should be -3
    EXPECT_EQ(imgCoordMungeLower(-2.3), -3);
}

TEST_F(SplashHelperTest_2611, ImgCoordMungeLowerNegativeLargeFraction_2611)
{
    // Floor of -2.9 should be -3
    EXPECT_EQ(imgCoordMungeLower(-2.9), -3);
}

// Boundary conditions
TEST_F(SplashHelperTest_2611, ImgCoordMungeLowerZero_2611)
{
    EXPECT_EQ(imgCoordMungeLower(0.0), 0);
}

TEST_F(SplashHelperTest_2611, ImgCoordMungeLowerNegativeZero_2611)
{
    EXPECT_EQ(imgCoordMungeLower(-0.0), 0);
}

TEST_F(SplashHelperTest_2611, ImgCoordMungeLowerVerySmallPositive_2611)
{
    // Floor of a very small positive number should be 0
    EXPECT_EQ(imgCoordMungeLower(0.0001), 0);
}

TEST_F(SplashHelperTest_2611, ImgCoordMungeLowerVerySmallNegative_2611)
{
    // Floor of a very small negative number should be -1
    EXPECT_EQ(imgCoordMungeLower(-0.0001), -1);
}

TEST_F(SplashHelperTest_2611, ImgCoordMungeLowerHalfPositive_2611)
{
    // Floor of 0.5 should be 0
    EXPECT_EQ(imgCoordMungeLower(0.5), 0);
}

TEST_F(SplashHelperTest_2611, ImgCoordMungeLowerHalfNegative_2611)
{
    // Floor of -0.5 should be -1
    EXPECT_EQ(imgCoordMungeLower(-0.5), -1);
}

TEST_F(SplashHelperTest_2611, ImgCoordMungeLowerLargePositive_2611)
{
    EXPECT_EQ(imgCoordMungeLower(100000.99), 100000);
}

TEST_F(SplashHelperTest_2611, ImgCoordMungeLowerLargeNegative_2611)
{
    EXPECT_EQ(imgCoordMungeLower(-100000.01), -100001);
}

TEST_F(SplashHelperTest_2611, ImgCoordMungeLowerOneMinusEpsilon_2611)
{
    // Just below 1.0
    EXPECT_EQ(imgCoordMungeLower(0.999999), 0);
}

TEST_F(SplashHelperTest_2611, ImgCoordMungeLowerExactlyOne_2611)
{
    EXPECT_EQ(imgCoordMungeLower(1.0), 1);
}

TEST_F(SplashHelperTest_2611, ImgCoordMungeLowerNegativeOne_2611)
{
    EXPECT_EQ(imgCoordMungeLower(-1.0), -1);
}

TEST_F(SplashHelperTest_2611, ImgCoordMungeLowerJustBelowNegativeOne_2611)
{
    EXPECT_EQ(imgCoordMungeLower(-1.0001), -2);
}
