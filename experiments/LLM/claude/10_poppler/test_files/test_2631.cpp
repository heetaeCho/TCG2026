#include <gtest/gtest.h>
#include <array>
#include <cmath>

// We need to provide the is_within function that rot_matrices_equal depends on.
// Based on usage: is_within(val, tolerance, target) checks if |val - target| <= tolerance
// This is a common utility pattern. We include the actual header.

// First, let's check if is_within is defined in the same header or needs to be provided.
// Since the header is HtmlUtils.h, we include it directly.

// If is_within is not available, we define it based on the standard pattern used in poppler:
#ifndef HTML_UTILS_H
inline bool is_within(double val, double tolerance, double target)
{
    return std::fabs(val - target) <= tolerance;
}
#endif

#include "./TestProjects/poppler/utils/HtmlUtils.h"

class RotMatricesEqualTest_2631 : public ::testing::Test {
protected:
};

// Test: Identical 4-element matrices should be equal
TEST_F(RotMatricesEqualTest_2631, IdenticalMatrices_2631)
{
    std::array<double, 4> mat0 = {1.0, 0.0, 0.0, 1.0};
    std::array<double, 4> mat1 = {1.0, 0.0, 0.0, 1.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Matrices with all zeros
TEST_F(RotMatricesEqualTest_2631, AllZeroMatrices_2631)
{
    std::array<double, 4> mat0 = {0.0, 0.0, 0.0, 0.0};
    std::array<double, 4> mat1 = {0.0, 0.0, 0.0, 0.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Matrices within tolerance (just under 0.1 difference)
TEST_F(RotMatricesEqualTest_2631, WithinTolerance_2631)
{
    std::array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};
    std::array<double, 4> mat1 = {1.09, 2.09, 3.09, 4.09};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Matrices at exactly tolerance boundary (difference = 0.1)
TEST_F(RotMatricesEqualTest_2631, AtToleranceBoundary_2631)
{
    std::array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};
    std::array<double, 4> mat1 = {1.1, 2.1, 3.1, 4.1};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: First element exceeds tolerance
TEST_F(RotMatricesEqualTest_2631, FirstElementExceedsTolerance_2631)
{
    std::array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};
    std::array<double, 4> mat1 = {1.2, 2.0, 3.0, 4.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test: Second element exceeds tolerance
TEST_F(RotMatricesEqualTest_2631, SecondElementExceedsTolerance_2631)
{
    std::array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};
    std::array<double, 4> mat1 = {1.0, 2.2, 3.0, 4.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test: Third element exceeds tolerance
TEST_F(RotMatricesEqualTest_2631, ThirdElementExceedsTolerance_2631)
{
    std::array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};
    std::array<double, 4> mat1 = {1.0, 2.0, 3.2, 4.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test: Fourth element exceeds tolerance
TEST_F(RotMatricesEqualTest_2631, FourthElementExceedsTolerance_2631)
{
    std::array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};
    std::array<double, 4> mat1 = {1.0, 2.0, 3.0, 4.2};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test: All elements exceed tolerance
TEST_F(RotMatricesEqualTest_2631, AllElementsExceedTolerance_2631)
{
    std::array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};
    std::array<double, 4> mat1 = {2.0, 3.0, 4.0, 5.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test: Negative values within tolerance
TEST_F(RotMatricesEqualTest_2631, NegativeValuesWithinTolerance_2631)
{
    std::array<double, 4> mat0 = {-1.0, -2.0, -3.0, -4.0};
    std::array<double, 4> mat1 = {-1.05, -2.05, -3.05, -4.05};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Negative values exceeding tolerance
TEST_F(RotMatricesEqualTest_2631, NegativeValuesExceedTolerance_2631)
{
    std::array<double, 4> mat0 = {-1.0, -2.0, -3.0, -4.0};
    std::array<double, 4> mat1 = {-1.2, -2.0, -3.0, -4.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test: Larger arrays (size > 4) - only first 4 elements compared
TEST_F(RotMatricesEqualTest_2631, LargerArraysOnlyFirst4Compared_2631)
{
    std::array<double, 6> mat0 = {1.0, 0.0, 0.0, 1.0, 100.0, 200.0};
    std::array<double, 6> mat1 = {1.0, 0.0, 0.0, 1.0, 999.0, 888.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Different sized arrays (both >= 4)
TEST_F(RotMatricesEqualTest_2631, DifferentSizedArrays_2631)
{
    std::array<double, 4> mat0 = {1.0, 0.0, 0.0, 1.0};
    std::array<double, 6> mat1 = {1.0, 0.0, 0.0, 1.0, 50.0, 60.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Mixed positive and negative within tolerance
TEST_F(RotMatricesEqualTest_2631, MixedSignsWithinTolerance_2631)
{
    std::array<double, 4> mat0 = {0.05, -0.05, 0.05, -0.05};
    std::array<double, 4> mat1 = {-0.05, 0.05, -0.05, 0.05};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Mixed signs exceeding tolerance
TEST_F(RotMatricesEqualTest_2631, MixedSignsExceedTolerance_2631)
{
    std::array<double, 4> mat0 = {0.1, 0.0, 0.0, 0.0};
    std::array<double, 4> mat1 = {-0.1, 0.0, 0.0, 0.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test: Very large values within tolerance
TEST_F(RotMatricesEqualTest_2631, VeryLargeValuesWithinTolerance_2631)
{
    std::array<double, 4> mat0 = {1e10, 1e10, 1e10, 1e10};
    std::array<double, 4> mat1 = {1e10 + 0.05, 1e10 + 0.05, 1e10 + 0.05, 1e10 + 0.05};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Very small values within tolerance
TEST_F(RotMatricesEqualTest_2631, VerySmallValuesWithinTolerance_2631)
{
    std::array<double, 4> mat0 = {1e-15, 1e-15, 1e-15, 1e-15};
    std::array<double, 4> mat1 = {0.0, 0.0, 0.0, 0.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Typical rotation matrix (identity)
TEST_F(RotMatricesEqualTest_2631, IdentityRotationMatrix_2631)
{
    std::array<double, 4> mat0 = {1.0, 0.0, 0.0, 1.0};
    std::array<double, 4> mat1 = {1.0, 0.0, 0.0, 1.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: 90-degree rotation matrix comparison
TEST_F(RotMatricesEqualTest_2631, Rotation90Degrees_2631)
{
    std::array<double, 4> mat0 = {0.0, 1.0, -1.0, 0.0};
    std::array<double, 4> mat1 = {0.0, 1.0, -1.0, 0.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Slightly perturbed rotation vs different rotation
TEST_F(RotMatricesEqualTest_2631, DifferentRotations_2631)
{
    // Identity vs 90-degree rotation
    std::array<double, 4> mat0 = {1.0, 0.0, 0.0, 1.0};
    std::array<double, 4> mat1 = {0.0, 1.0, -1.0, 0.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test: Just barely exceeding tolerance on one element
TEST_F(RotMatricesEqualTest_2631, BarelyExceedingTolerance_2631)
{
    std::array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};
    std::array<double, 4> mat1 = {1.0, 2.0, 3.0, 4.11};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test: Tolerance check is symmetric (negative direction)
TEST_F(RotMatricesEqualTest_2631, ToleranceSymmetricNegative_2631)
{
    std::array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};
    std::array<double, 4> mat1 = {0.9, 1.9, 2.9, 3.9};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Larger array size 8 for mat0 and size 5 for mat1
TEST_F(RotMatricesEqualTest_2631, AsymmetricLargerArrays_2631)
{
    std::array<double, 8> mat0 = {1.0, 0.0, 0.0, 1.0, 10.0, 20.0, 30.0, 40.0};
    std::array<double, 5> mat1 = {1.05, 0.05, -0.05, 0.95, 999.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}
