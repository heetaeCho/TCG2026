// File: rot_matrices_equal_test_2633.cpp

#include <array>
#include <limits>

#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/HtmlUtils.h"

namespace {

class RotMatricesEqualTest_2633 : public ::testing::Test {};

TEST_F(RotMatricesEqualTest_2633, ReturnsTrueWhenFirstFourElementsExactlyMatch_2633)
{
    const std::array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};
    const std::array<double, 4> mat1 = {1.0, 2.0, 3.0, 4.0};

    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

TEST_F(RotMatricesEqualTest_2633, ReturnsTrueWhenAllFirstFourElementsAreWithinTolerance_2633)
{
    const std::array<double, 4> mat0 = {10.0, -10.0, 0.0, 0.5};
    const std::array<double, 4> mat1 = {10.05, -10.05, 0.05, 0.55}; // each differs by 0.05

    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

TEST_F(RotMatricesEqualTest_2633, ReturnsTrueWhenDifferenceIsJustBelowTolerance_2633)
{
    const std::array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};
    const std::array<double, 4> mat1 = {1.099, 2.0, 3.0, 4.0}; // difference 0.099

    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

TEST_F(RotMatricesEqualTest_2633, ReturnsFalseWhenAnyFirstFourElementIsBeyondTolerance_2633)
{
    const std::array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};
    const std::array<double, 4> mat1 = {1.101, 2.0, 3.0, 4.0}; // difference 0.101

    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

TEST_F(RotMatricesEqualTest_2633, ReturnsFalseWhenMismatchOccursInLaterComparedElement_2633)
{
    const std::array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};
    const std::array<double, 4> mat1 = {1.0, 2.0, 3.2, 4.0}; // difference 0.2 in index 2

    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

TEST_F(RotMatricesEqualTest_2633, IgnoresElementsBeyondFirstFourWhenArraysAreLarger_2633)
{
    const std::array<double, 6> mat0 = {1.0, 2.0, 3.0, 4.0, 9999.0, -9999.0};
    const std::array<double, 5> mat1 = {1.0, 2.0, 3.0, 4.0, -123456.0};

    // Only the first 4 entries are compared by the interface we see.
    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));
}

TEST_F(RotMatricesEqualTest_2633, ReturnsFalseEvenIfOnlyOneOfFirstFourElementsDiffersBeyondTolerance_2633)
{
    const std::array<double, 5> mat0 = {1.0, 2.0, 3.0, 4.0, 5.0};
    const std::array<double, 6> mat1 = {1.0, 2.0, 3.0, 4.5, 5.0, 6.0}; // difference 0.5 at index 3

    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));
}

} // namespace