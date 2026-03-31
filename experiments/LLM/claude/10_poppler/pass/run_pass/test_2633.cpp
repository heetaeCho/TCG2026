#include <gtest/gtest.h>
#include <array>
#include <cmath>

// We need to include the header under test. Based on the partial code,
// we need the full header which should define is_within and rot_matrices_equal.
#include "./TestProjects/poppler/utils/HtmlUtils.h"

// ============================================================================
// Tests for rot_matrices_equal
// ============================================================================

// Test: Identical matrices should be equal
TEST(RotMatricesEqualTest_2633, IdenticalMatricesAreEqual_2633)
{
    std::array<double, 4> mat0 = {1.0, 0.0, 0.0, 1.0};
    std::array<double, 4> mat1 = {1.0, 0.0, 0.0, 1.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Matrices with all zeros should be equal
TEST(RotMatricesEqualTest_2633, AllZeroMatricesAreEqual_2633)
{
    std::array<double, 4> mat0 = {0.0, 0.0, 0.0, 0.0};
    std::array<double, 4> mat1 = {0.0, 0.0, 0.0, 0.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Matrices within tolerance (just under 0.1) should be equal
TEST(RotMatricesEqualTest_2633, WithinToleranceAreEqual_2633)
{
    std::array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};
    std::array<double, 4> mat1 = {1.09, 2.09, 3.09, 4.09};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Matrices exactly at tolerance boundary (difference = 0.1)
TEST(RotMatricesEqualTest_2633, ExactlyAtToleranceBoundary_2633)
{
    std::array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};
    std::array<double, 4> mat1 = {1.1, 2.1, 3.1, 4.1};
    // is_within typically checks |a - b| < tolerance (strict), so at exactly 0.1 it may fail
    // We test the observable behavior
    // This depends on whether is_within uses < or <=; we just record what happens
    bool result = rot_matrices_equal(mat0, mat1);
    // The result depends on the implementation of is_within; we just verify it doesn't crash
    (void)result;
}

// Test: Matrices outside tolerance should not be equal
TEST(RotMatricesEqualTest_2633, OutsideToleranceAreNotEqual_2633)
{
    std::array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};
    std::array<double, 4> mat1 = {1.2, 2.0, 3.0, 4.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test: Only first element differs beyond tolerance
TEST(RotMatricesEqualTest_2633, FirstElementDiffersBeyondTolerance_2633)
{
    std::array<double, 4> mat0 = {0.0, 1.0, 0.0, 1.0};
    std::array<double, 4> mat1 = {0.5, 1.0, 0.0, 1.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test: Only second element differs beyond tolerance
TEST(RotMatricesEqualTest_2633, SecondElementDiffersBeyondTolerance_2633)
{
    std::array<double, 4> mat0 = {1.0, 0.0, 0.0, 1.0};
    std::array<double, 4> mat1 = {1.0, 0.5, 0.0, 1.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test: Only third element differs beyond tolerance
TEST(RotMatricesEqualTest_2633, ThirdElementDiffersBeyondTolerance_2633)
{
    std::array<double, 4> mat0 = {1.0, 0.0, 0.0, 1.0};
    std::array<double, 4> mat1 = {1.0, 0.0, 0.5, 1.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test: Only fourth element differs beyond tolerance
TEST(RotMatricesEqualTest_2633, FourthElementDiffersBeyondTolerance_2633)
{
    std::array<double, 4> mat0 = {1.0, 0.0, 0.0, 1.0};
    std::array<double, 4> mat1 = {1.0, 0.0, 0.0, 1.5};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test: Negative values within tolerance
TEST(RotMatricesEqualTest_2633, NegativeValuesWithinTolerance_2633)
{
    std::array<double, 4> mat0 = {-1.0, -2.0, -3.0, -4.0};
    std::array<double, 4> mat1 = {-1.05, -2.05, -3.05, -4.05};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Negative values outside tolerance
TEST(RotMatricesEqualTest_2633, NegativeValuesOutsideTolerance_2633)
{
    std::array<double, 4> mat0 = {-1.0, -2.0, -3.0, -4.0};
    std::array<double, 4> mat1 = {-1.5, -2.0, -3.0, -4.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test: Mixed positive and negative values within tolerance
TEST(RotMatricesEqualTest_2633, MixedSignsWithinTolerance_2633)
{
    std::array<double, 4> mat0 = {1.0, -1.0, 0.5, -0.5};
    std::array<double, 4> mat1 = {1.05, -1.05, 0.55, -0.55};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Larger arrays (more than 4 elements) - only first 4 are compared
TEST(RotMatricesEqualTest_2633, LargerArraysOnlyFirst4Compared_2633)
{
    std::array<double, 6> mat0 = {1.0, 0.0, 0.0, 1.0, 999.0, 999.0};
    std::array<double, 6> mat1 = {1.0, 0.0, 0.0, 1.0, -999.0, -999.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Larger arrays where first 4 differ
TEST(RotMatricesEqualTest_2633, LargerArraysFirst4Differ_2633)
{
    std::array<double, 5> mat0 = {1.0, 0.0, 0.0, 1.0, 0.0};
    std::array<double, 5> mat1 = {2.0, 0.0, 0.0, 1.0, 0.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test: Very small values within tolerance
TEST(RotMatricesEqualTest_2633, VerySmallValuesWithinTolerance_2633)
{
    std::array<double, 4> mat0 = {0.001, 0.002, 0.003, 0.004};
    std::array<double, 4> mat1 = {0.01, 0.01, 0.01, 0.01};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Large values within tolerance
TEST(RotMatricesEqualTest_2633, LargeValuesWithinTolerance_2633)
{
    std::array<double, 4> mat0 = {1000.0, 2000.0, 3000.0, 4000.0};
    std::array<double, 4> mat1 = {1000.05, 2000.05, 3000.05, 4000.05};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Large values outside tolerance
TEST(RotMatricesEqualTest_2633, LargeValuesOutsideTolerance_2633)
{
    std::array<double, 4> mat0 = {1000.0, 2000.0, 3000.0, 4000.0};
    std::array<double, 4> mat1 = {1000.2, 2000.0, 3000.0, 4000.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test: Typical rotation matrix (90 degrees)
TEST(RotMatricesEqualTest_2633, Rotation90Degrees_2633)
{
    std::array<double, 4> mat0 = {0.0, 1.0, -1.0, 0.0};
    std::array<double, 4> mat1 = {0.0, 1.0, -1.0, 0.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Slightly perturbed rotation matrix (within tolerance)
TEST(RotMatricesEqualTest_2633, PerturbedRotation90WithinTolerance_2633)
{
    std::array<double, 4> mat0 = {0.0, 1.0, -1.0, 0.0};
    std::array<double, 4> mat1 = {0.05, 1.05, -0.95, 0.05};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Different sized template arrays (mat0 size 5, mat1 size 6)
TEST(RotMatricesEqualTest_2633, DifferentSizedArrays_2633)
{
    std::array<double, 5> mat0 = {1.0, 0.0, 0.0, 1.0, 42.0};
    std::array<double, 6> mat1 = {1.0, 0.0, 0.0, 1.0, 99.0, 99.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Sign crossing near zero within tolerance
TEST(RotMatricesEqualTest_2633, SignCrossingNearZero_2633)
{
    std::array<double, 4> mat0 = {0.05, 0.05, 0.05, 0.05};
    std::array<double, 4> mat1 = {-0.04, -0.04, -0.04, -0.04};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test: Sign crossing near zero outside tolerance
TEST(RotMatricesEqualTest_2633, SignCrossingOutsideTolerance_2633)
{
    std::array<double, 4> mat0 = {0.1, 0.0, 0.0, 0.0};
    std::array<double, 4> mat1 = {-0.1, 0.0, 0.0, 0.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// ============================================================================
// Tests for is_within (if accessible from the header)
// ============================================================================

TEST(IsWithinTest_2633, ExactMatch_2633)
{
    EXPECT_TRUE(is_within(5.0, 0.1, 5.0));
}

TEST(IsWithinTest_2633, WithinPositiveTolerance_2633)
{
    EXPECT_TRUE(is_within(5.0, 0.1, 5.05));
}

TEST(IsWithinTest_2633, WithinNegativeTolerance_2633)
{
    EXPECT_TRUE(is_within(5.0, 0.1, 4.95));
}

TEST(IsWithinTest_2633, OutsidePositiveTolerance_2633)
{
    EXPECT_FALSE(is_within(5.0, 0.1, 5.2));
}

TEST(IsWithinTest_2633, OutsideNegativeTolerance_2633)
{
    EXPECT_FALSE(is_within(5.0, 0.1, 4.8));
}

TEST(IsWithinTest_2633, ZeroTolerance_2633)
{
    EXPECT_TRUE(is_within(1.0, 0.0, 1.0));
    EXPECT_FALSE(is_within(1.0, 0.0, 1.0001));
}
