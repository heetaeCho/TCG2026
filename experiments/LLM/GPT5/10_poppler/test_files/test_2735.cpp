// File: rot_matrices_equal_test_2735.cpp

#include <array>
#include <gtest/gtest.h>

// Adjust include path as needed for your build setup.
#include "utils/HtmlUtils.h"

namespace {

class RotMatricesEqualTest_2735 : public ::testing::Test {};

TEST_F(RotMatricesEqualTest_2735, ReturnsTrueWhenFirstFourElementsAreWithinTolerance_2735)
{
    const std::array<double, 4> mat0 = {1.00, 0.00, 0.00, 1.00};
    const std::array<double, 4> mat1 = {1.05, -0.05, 0.05, 0.95}; // all diffs <= 0.05

    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

TEST_F(RotMatricesEqualTest_2735, ReturnsTrueWhenDifferencesAreJustUnderTolerance_2735)
{
    const std::array<double, 4> mat0 = {10.0, 20.0, 30.0, 40.0};
    const std::array<double, 4> mat1 = {10.0999, 19.9001, 30.0999, 39.9001}; // all diffs < 0.1

    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

TEST_F(RotMatricesEqualTest_2735, ReturnsFalseWhenAnyDifferenceIsJustOverTolerance_2735)
{
    const std::array<double, 4> mat0 = {10.0, 20.0, 30.0, 40.0};
    const std::array<double, 4> mat1 = {10.0, 20.0, 30.1001, 40.0}; // one diff > 0.1

    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

TEST_F(RotMatricesEqualTest_2735, ReturnsFalseWhenFirstElementIsFarOutsideTolerance_2735)
{
    const std::array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};
    const std::array<double, 4> mat1 = {2.0, 2.0, 3.0, 4.0}; // diff = 1.0 on index 0

    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

TEST_F(RotMatricesEqualTest_2735, IgnoresElementsBeyondFirstFour_2735)
{
    const std::array<double, 6> mat0 = {1.00, 0.00, 0.00, 1.00, 12345.0, -99999.0};
    const std::array<double, 6> mat1 = {1.02, -0.02, 0.02, 0.98, -1.0, 1.0};

    // Only first 4 elements should affect equality.
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

TEST_F(RotMatricesEqualTest_2735, WorksWithDifferentArraySizesAsLongAsTheyHaveAtLeastFour_2735)
{
    const std::array<double, 4> mat0 = {5.0, 6.0, 7.0, 8.0};
    const std::array<double, 8> mat1 = {5.05, 5.95, 7.05, 7.95, 100.0, 200.0, 300.0, 400.0};

    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

} // namespace