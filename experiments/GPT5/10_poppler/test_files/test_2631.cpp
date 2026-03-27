// File: rot_matrices_equal_test_2631.cpp
#include <gtest/gtest.h>

#include <array>

#include "./TestProjects/poppler/utils/HtmlUtils.h"

namespace {

class RotMatricesEqualTest_2631 : public ::testing::Test {};

TEST_F(RotMatricesEqualTest_2631, ReturnsTrueWhenAllFirstFourElementsWithinTolerance_2631) {
  const std::array<double, 4> mat1 = {1.0, 0.0, 0.0, 1.0};

  // Each of the first 4 entries is within 0.1 of mat1.
  const std::array<double, 4> mat0 = {1.05, -0.05, 0.09, 0.91};

  EXPECT_TRUE((rot_matrices_equal<4, 4>(mat0, mat1)));
}

TEST_F(RotMatricesEqualTest_2631, ReturnsFalseWhenAnyOfFirstFourElementsOutOfTolerance_2631) {
  const std::array<double, 4> mat1 = {1.0, 2.0, 3.0, 4.0};

  // Only mat0[2] is out of tolerance (> 0.1 away).
  const std::array<double, 4> mat0 = {1.0, 2.0, 3.2001, 4.0};

  EXPECT_FALSE((rot_matrices_equal<4, 4>(mat0, mat1)));
}

TEST_F(RotMatricesEqualTest_2631, ReturnsTrueWithMismatchedSizesWhenFirstFourElementsWithinTolerance_2631) {
  const std::array<double, 8> mat1 = {10.0, -2.0, 0.5, 7.0, 111.0, 222.0, 333.0, 444.0};

  // mat0 has only 4 entries; compare to mat1's first 4 entries.
  const std::array<double, 4> mat0 = {9.95, -2.05, 0.55, 6.91};

  EXPECT_TRUE((rot_matrices_equal<4, 8>(mat0, mat1)));
}

TEST_F(RotMatricesEqualTest_2631, IgnoresElementsBeyondFirstFourInMat0AndMat1_2631) {
  // First 4 entries match within tolerance; later entries differ wildly.
  const std::array<double, 6> mat1 = {1.0, 2.0, 3.0, 4.0, 9999.0, -9999.0};
  const std::array<double, 6> mat0 = {1.01, 2.02, 2.99, 4.09, -123456.0, 123456.0};

  EXPECT_TRUE((rot_matrices_equal<6, 6>(mat0, mat1)));
}

TEST_F(RotMatricesEqualTest_2631, ReturnsFalseWhenSecondElementOutOfToleranceEvenIfOthersWithinTolerance_2631) {
  const std::array<double, 5> mat1 = {0.0, 5.0, 0.0, 5.0, 42.0};

  // Only the 2nd element differs by > 0.1.
  const std::array<double, 7> mat0 = {0.05, 5.101, -0.05, 4.95, 0.0, 0.0, 0.0};

  EXPECT_FALSE((rot_matrices_equal<7, 5>(mat0, mat1)));
}

TEST_F(RotMatricesEqualTest_2631, HandlesNegativeValuesWithinTolerance_2631) {
  const std::array<double, 4> mat1 = {-1.0, -2.0, -3.0, -4.0};
  const std::array<double, 4> mat0 = {-1.09, -2.01, -2.92, -3.95};

  EXPECT_TRUE((rot_matrices_equal<4, 4>(mat0, mat1)));
}

TEST_F(RotMatricesEqualTest_2631, ReturnsFalseWhenJustOverTolerance_2631) {
  const std::array<double, 4> mat1 = {1.0, 1.0, 1.0, 1.0};

  // mat0[0] differs by slightly more than 0.1.
  const std::array<double, 4> mat0 = {1.100001, 1.0, 1.0, 1.0};

  EXPECT_FALSE((rot_matrices_equal<4, 4>(mat0, mat1)));
}

TEST_F(RotMatricesEqualTest_2631, ReturnsTrueWhenJustUnderTolerance_2631) {
  const std::array<double, 4> mat1 = {1.0, 1.0, 1.0, 1.0};

  // mat0[3] differs by slightly less than 0.1.
  const std::array<double, 4> mat0 = {1.0, 1.0, 1.0, 0.900001};

  EXPECT_TRUE((rot_matrices_equal<4, 4>(mat0, mat1)));
}

}  // namespace