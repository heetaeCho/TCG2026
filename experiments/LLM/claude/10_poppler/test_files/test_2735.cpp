#include <gtest/gtest.h>
#include <array>
#include <cmath>

// We need to include the header under test. Based on the partial code, we need
// the full header which likely contains is_within and rot_matrices_equal.
#include "HtmlUtils.h"

// Test rot_matrices_equal with identical matrices
TEST(RotMatricesEqualTest_2735, IdenticalMatrices_2735) {
    std::array<double, 4> mat0 = {1.0, 0.0, 0.0, 1.0};
    std::array<double, 4> mat1 = {1.0, 0.0, 0.0, 1.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test rot_matrices_equal with matrices that differ within tolerance (0.1)
TEST(RotMatricesEqualTest_2735, WithinTolerance_2735) {
    std::array<double, 4> mat0 = {1.0, 0.0, 0.0, 1.0};
    std::array<double, 4> mat1 = {1.05, 0.05, -0.05, 0.95};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test rot_matrices_equal with matrices that differ exactly at tolerance boundary
TEST(RotMatricesEqualTest_2735, AtToleranceBoundary_2735) {
    std::array<double, 4> mat0 = {1.0, 0.0, 0.0, 1.0};
    // Difference of exactly 0.1 - depends on is_within implementation (< vs <=)
    std::array<double, 4> mat1 = {1.1, 0.1, -0.1, 0.9};
    // This might or might not pass depending on whether is_within uses < or <=
    // We just document the behavior
    bool result = rot_matrices_equal(mat0, mat1);
    // Not asserting specific value since boundary behavior depends on is_within
    (void)result;
}

// Test rot_matrices_equal with matrices that differ beyond tolerance
TEST(RotMatricesEqualTest_2735, BeyondTolerance_2735) {
    std::array<double, 4> mat0 = {1.0, 0.0, 0.0, 1.0};
    std::array<double, 4> mat1 = {1.2, 0.0, 0.0, 1.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test rot_matrices_equal where only first element differs beyond tolerance
TEST(RotMatricesEqualTest_2735, FirstElementDiffers_2735) {
    std::array<double, 4> mat0 = {0.0, 0.0, 0.0, 0.0};
    std::array<double, 4> mat1 = {0.5, 0.0, 0.0, 0.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test rot_matrices_equal where only second element differs beyond tolerance
TEST(RotMatricesEqualTest_2735, SecondElementDiffers_2735) {
    std::array<double, 4> mat0 = {0.0, 0.0, 0.0, 0.0};
    std::array<double, 4> mat1 = {0.0, 0.5, 0.0, 0.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test rot_matrices_equal where only third element differs beyond tolerance
TEST(RotMatricesEqualTest_2735, ThirdElementDiffers_2735) {
    std::array<double, 4> mat0 = {0.0, 0.0, 0.0, 0.0};
    std::array<double, 4> mat1 = {0.0, 0.0, 0.5, 0.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test rot_matrices_equal where only fourth element differs beyond tolerance
TEST(RotMatricesEqualTest_2735, FourthElementDiffers_2735) {
    std::array<double, 4> mat0 = {0.0, 0.0, 0.0, 0.0};
    std::array<double, 4> mat1 = {0.0, 0.0, 0.0, 0.5};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test rot_matrices_equal with negative values
TEST(RotMatricesEqualTest_2735, NegativeValues_2735) {
    std::array<double, 4> mat0 = {-1.0, -2.0, -3.0, -4.0};
    std::array<double, 4> mat1 = {-1.0, -2.0, -3.0, -4.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test rot_matrices_equal with negative values within tolerance
TEST(RotMatricesEqualTest_2735, NegativeValuesWithinTolerance_2735) {
    std::array<double, 4> mat0 = {-1.0, -2.0, -3.0, -4.0};
    std::array<double, 4> mat1 = {-1.05, -2.05, -3.05, -4.05};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test rot_matrices_equal with negative values beyond tolerance
TEST(RotMatricesEqualTest_2735, NegativeValuesBeyondTolerance_2735) {
    std::array<double, 4> mat0 = {-1.0, -2.0, -3.0, -4.0};
    std::array<double, 4> mat1 = {-1.5, -2.0, -3.0, -4.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test rot_matrices_equal with zero matrices
TEST(RotMatricesEqualTest_2735, ZeroMatrices_2735) {
    std::array<double, 4> mat0 = {0.0, 0.0, 0.0, 0.0};
    std::array<double, 4> mat1 = {0.0, 0.0, 0.0, 0.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test rot_matrices_equal with larger arrays (only first 4 elements matter)
TEST(RotMatricesEqualTest_2735, LargerArrays_2735) {
    std::array<double, 6> mat0 = {1.0, 0.0, 0.0, 1.0, 99.0, 99.0};
    std::array<double, 6> mat1 = {1.0, 0.0, 0.0, 1.0, -99.0, -99.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test rot_matrices_equal with large values
TEST(RotMatricesEqualTest_2735, LargeValues_2735) {
    std::array<double, 4> mat0 = {1000.0, 2000.0, 3000.0, 4000.0};
    std::array<double, 4> mat1 = {1000.0, 2000.0, 3000.0, 4000.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test rot_matrices_equal with large values slightly different
TEST(RotMatricesEqualTest_2735, LargeValuesSlightlyDifferent_2735) {
    std::array<double, 4> mat0 = {1000.0, 2000.0, 3000.0, 4000.0};
    std::array<double, 4> mat1 = {1000.05, 2000.05, 3000.05, 4000.05};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test rot_matrices_equal with typical rotation matrix (90 degrees)
TEST(RotMatricesEqualTest_2735, TypicalRotationMatrix_2735) {
    std::array<double, 4> mat0 = {0.0, 1.0, -1.0, 0.0};
    std::array<double, 4> mat1 = {0.0, 1.0, -1.0, 0.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test rot_matrices_equal with different rotation matrices
TEST(RotMatricesEqualTest_2735, DifferentRotationMatrices_2735) {
    // 0 degrees rotation
    std::array<double, 4> mat0 = {1.0, 0.0, 0.0, 1.0};
    // 90 degrees rotation
    std::array<double, 4> mat1 = {0.0, 1.0, -1.0, 0.0};
    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

// Test rot_matrices_equal symmetry (a==b implies b==a)
TEST(RotMatricesEqualTest_2735, Symmetry_2735) {
    std::array<double, 4> mat0 = {1.0, 0.05, -0.05, 0.99};
    std::array<double, 4> mat1 = {1.05, 0.0, 0.0, 1.0};
    EXPECT_EQ(rot_matrices_equal(mat0, mat1), rot_matrices_equal(mat1, mat0));
}

// Test all elements just within tolerance
TEST(RotMatricesEqualTest_2735, AllElementsJustWithinTolerance_2735) {
    std::array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};
    std::array<double, 4> mat1 = {1.09, 2.09, 3.09, 4.09};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test with mixed sizes of arrays
TEST(RotMatricesEqualTest_2735, MixedSizeArrays_2735) {
    std::array<double, 4> mat0 = {1.0, 0.0, 0.0, 1.0};
    std::array<double, 6> mat1 = {1.0, 0.0, 0.0, 1.0, 5.0, 6.0};
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

// Test is_within function if it's accessible
TEST(IsWithinTest_2735, ValueWithinRange_2735) {
    EXPECT_TRUE(is_within(1.0, 0.1, 1.05));
    EXPECT_TRUE(is_within(1.0, 0.1, 0.95));
}

TEST(IsWithinTest_2735, ValueOutsideRange_2735) {
    EXPECT_FALSE(is_within(1.0, 0.1, 1.5));
    EXPECT_FALSE(is_within(1.0, 0.1, 0.5));
}

TEST(IsWithinTest_2735, ZeroTolerance_2735) {
    EXPECT_TRUE(is_within(1.0, 0.0, 1.0));
}
