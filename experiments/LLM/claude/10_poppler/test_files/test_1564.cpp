#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Include the header under test
#include "splash/SplashMath.h"

class SplashCheckDetTest_1564 : public ::testing::Test {
protected:
    // Common epsilon values used across tests
    static constexpr SplashCoord defaultEpsilon = 1e-6;
};

// Test: Identity-like matrix has determinant 1, which is >= any small epsilon
TEST_F(SplashCheckDetTest_1564, IdentityMatrixReturnsTrue_1564) {
    // det = 1*1 - 0*0 = 1
    EXPECT_TRUE(splashCheckDet(1.0, 0.0, 0.0, 1.0, defaultEpsilon));
}

// Test: Zero matrix has determinant 0, which is < any positive epsilon
TEST_F(SplashCheckDetTest_1564, ZeroMatrixReturnsFalse_1564) {
    // det = 0*0 - 0*0 = 0
    EXPECT_FALSE(splashCheckDet(0.0, 0.0, 0.0, 0.0, defaultEpsilon));
}

// Test: Singular matrix (linearly dependent rows) has determinant 0
TEST_F(SplashCheckDetTest_1564, SingularMatrixReturnsFalse_1564) {
    // det = 2*4 - 4*2 = 0
    EXPECT_FALSE(splashCheckDet(2.0, 4.0, 2.0, 4.0, defaultEpsilon));
}

// Test: Non-singular matrix with positive determinant
TEST_F(SplashCheckDetTest_1564, PositiveDeterminantReturnsTrue_1564) {
    // det = 3*5 - 2*4 = 15 - 8 = 7
    EXPECT_TRUE(splashCheckDet(3.0, 2.0, 4.0, 5.0, defaultEpsilon));
}

// Test: Non-singular matrix with negative determinant (absolute value used)
TEST_F(SplashCheckDetTest_1564, NegativeDeterminantReturnsTrue_1564) {
    // det = 1*3 - 4*2 = 3 - 8 = -5, |det| = 5
    EXPECT_TRUE(splashCheckDet(1.0, 4.0, 2.0, 3.0, defaultEpsilon));
}

// Test: Determinant exactly equal to epsilon should return true (>= comparison)
TEST_F(SplashCheckDetTest_1564, DeterminantExactlyEqualToEpsilonReturnsTrue_1564) {
    // det = 1*epsilon - 0*0 = epsilon
    SplashCoord epsilon = 0.5;
    EXPECT_TRUE(splashCheckDet(1.0, 0.0, 0.0, epsilon, epsilon));
}

// Test: Determinant slightly less than epsilon should return false
TEST_F(SplashCheckDetTest_1564, DeterminantSlightlyLessThanEpsilonReturnsFalse_1564) {
    SplashCoord epsilon = 1.0;
    // det = 0.5 * 1.0 - 0.0 * 0.0 = 0.5, which is < 1.0
    EXPECT_FALSE(splashCheckDet(0.5, 0.0, 0.0, 1.0, epsilon));
}

// Test: Determinant slightly greater than epsilon should return true
TEST_F(SplashCheckDetTest_1564, DeterminantSlightlyGreaterThanEpsilonReturnsTrue_1564) {
    SplashCoord epsilon = 1.0;
    // det = 1.5 * 1.0 - 0.0 * 0.0 = 1.5, which is >= 1.0
    EXPECT_TRUE(splashCheckDet(1.5, 0.0, 0.0, 1.0, epsilon));
}

// Test: Epsilon of zero — any non-zero determinant should return true
TEST_F(SplashCheckDetTest_1564, ZeroEpsilonNonZeroDeterminantReturnsTrue_1564) {
    // det = 1*1 - 0*0 = 1
    EXPECT_TRUE(splashCheckDet(1.0, 0.0, 0.0, 1.0, 0.0));
}

// Test: Epsilon of zero and zero determinant should return true (0 >= 0)
TEST_F(SplashCheckDetTest_1564, ZeroEpsilonZeroDeterminantReturnsTrue_1564) {
    EXPECT_TRUE(splashCheckDet(0.0, 0.0, 0.0, 0.0, 0.0));
}

// Test: Large values in matrix
TEST_F(SplashCheckDetTest_1564, LargeValuesReturnsTrue_1564) {
    SplashCoord large = 1e6;
    // det = 1e6 * 1e6 - 0*0 = 1e12
    EXPECT_TRUE(splashCheckDet(large, 0.0, 0.0, large, defaultEpsilon));
}

// Test: Very small non-zero determinant with small epsilon
TEST_F(SplashCheckDetTest_1564, VerySmallDeterminantWithSmallerEpsilonReturnsTrue_1564) {
    // det = 1e-10 * 1.0 - 0*0 = 1e-10
    EXPECT_TRUE(splashCheckDet(1e-10, 0.0, 0.0, 1.0, 1e-11));
}

// Test: Very small non-zero determinant with larger epsilon
TEST_F(SplashCheckDetTest_1564, VerySmallDeterminantWithLargerEpsilonReturnsFalse_1564) {
    // det = 1e-10 * 1.0 - 0*0 = 1e-10
    EXPECT_FALSE(splashCheckDet(1e-10, 0.0, 0.0, 1.0, 1e-9));
}

// Test: Negative values in matrix elements
TEST_F(SplashCheckDetTest_1564, NegativeMatrixElementsReturnsTrue_1564) {
    // det = (-3)*(-5) - (-2)*(-4) = 15 - 8 = 7
    EXPECT_TRUE(splashCheckDet(-3.0, -2.0, -4.0, -5.0, defaultEpsilon));
}

// Test: Mixed positive and negative elements producing zero determinant
TEST_F(SplashCheckDetTest_1564, MixedElementsZeroDeterminantReturnsFalse_1564) {
    // det = 2*6 - 3*4 = 12 - 12 = 0
    EXPECT_FALSE(splashCheckDet(2.0, 3.0, 4.0, 6.0, defaultEpsilon));
}

// Test: Diagonal matrix with different values
TEST_F(SplashCheckDetTest_1564, DiagonalMatrixReturnsTrue_1564) {
    // det = 5*3 - 0*0 = 15
    EXPECT_TRUE(splashCheckDet(5.0, 0.0, 0.0, 3.0, defaultEpsilon));
}

// Test: Anti-diagonal matrix
TEST_F(SplashCheckDetTest_1564, AntiDiagonalMatrixReturnsTrue_1564) {
    // det = 0*0 - 3*2 = -6, |det| = 6
    EXPECT_TRUE(splashCheckDet(0.0, 3.0, 2.0, 0.0, defaultEpsilon));
}

// Test: Matrix where m11*m22 and m12*m21 nearly cancel but not exactly
TEST_F(SplashCheckDetTest_1564, NearCancellationAboveEpsilonReturnsTrue_1564) {
    // det = 1.0 * 1.0 - 1.0 * (1.0 - 1e-4) = 1e-4
    EXPECT_TRUE(splashCheckDet(1.0, 1.0, 1.0 - 1e-4, 1.0, 1e-5));
}

// Test: Scaling matrix (uniform scale of 2)
TEST_F(SplashCheckDetTest_1564, ScalingMatrixReturnsTrue_1564) {
    // det = 2*2 - 0*0 = 4
    EXPECT_TRUE(splashCheckDet(2.0, 0.0, 0.0, 2.0, defaultEpsilon));
}

// Test: Rotation-like matrix (det should be 1 for rotation)
TEST_F(SplashCheckDetTest_1564, RotationMatrixReturnsTrue_1564) {
    SplashCoord angle = M_PI / 4.0; // 45 degrees
    SplashCoord c = cos(angle);
    SplashCoord s = sin(angle);
    // det = cos^2 + sin^2 = 1
    EXPECT_TRUE(splashCheckDet(c, -s, s, c, defaultEpsilon));
}
