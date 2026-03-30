// File: two_view_geometry_test_66.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <cmath>

namespace glomap {
// Forward declaration of the function under test.
double GetOrientationSignum(const Eigen::Matrix3d& F,
                            const Eigen::Vector3d& epipole,
                            const Eigen::Vector2d& pt1,
                            const Eigen::Vector2d& pt2);
}  // namespace glomap

// ----------------------
// Normal operation tests
// ----------------------

TEST(GetOrientationSignumTest_66, ReturnsPositiveValueForSimpleInputs_66) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
  // Only needed entries for this test.
  F(0, 0) = 2.0;
  F(1, 0) = 3.0;
  F(2, 0) = 4.0;

  Eigen::Vector3d epipole(0.0, 5.0, 1.0);
  Eigen::Vector2d pt1(0.0, 1.0);
  Eigen::Vector2d pt2(1.0, 2.0);

  // Expected result is a simple scalar value based on these constants.
  const double expected = 48.0;  //  (2*1 + 3*2 + 4) * (5 - 1*1)

  const double result =
      glomap::GetOrientationSignum(F, epipole, pt1, pt2);

  EXPECT_DOUBLE_EQ(result, expected);
}

TEST(GetOrientationSignumTest_66, ReturnsNegativeValueWhenSignFlips_66) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
  F(0, 0) = 2.0;
  F(1, 0) = 3.0;
  F(2, 0) = 4.0;

  // Make the second factor negative by choosing different epipole.
  Eigen::Vector3d epipole(0.0, 1.0, 10.0);
  Eigen::Vector2d pt1(0.0, 1.0);
  Eigen::Vector2d pt2(1.0, 2.0);

  const double expected = -108.0;  // (2*1 + 3*2 + 4) * (1 - 10*1)

  const double result =
      glomap::GetOrientationSignum(F, epipole, pt1, pt2);

  EXPECT_DOUBLE_EQ(result, expected);
}

// -------------------------
// Boundary / edge-case tests
// -------------------------

TEST(GetOrientationSignumTest_66, ReturnsZeroWhenFundamentalColumnZero_66) {
  // When the relevant column of F is zero, the first factor becomes zero.
  Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
  Eigen::Vector3d epipole(0.0, 1.0, 1.0);
  Eigen::Vector2d pt1(0.0, 0.0);
  Eigen::Vector2d pt2(1.0, 2.0);

  const double result =
      glomap::GetOrientationSignum(F, epipole, pt1, pt2);

  EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(GetOrientationSignumTest_66, ReturnsZeroWhenEpipoleCancelsOut_66) {
  // Choose epipole and pt1 so that the second factor becomes zero.
  Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
  F(0, 0) = 10.0;  // Non-zero so that the first factor is non-zero.
  Eigen::Vector3d epipole(0.0, 2.0, 2.0);
  Eigen::Vector2d pt1(0.0, 1.0);  // epipole(1) - epipole(2) * pt1[1] = 2 - 2*1 = 0
  Eigen::Vector2d pt2(1.0, 0.0);

  const double result =
      glomap::GetOrientationSignum(F, epipole, pt1, pt2);

  EXPECT_DOUBLE_EQ(result, 0.0);
}

// --------------------------------------
// Robustness / independence-type checks
// --------------------------------------

TEST(GetOrientationSignumTest_66, IgnoresIrrelevantEntriesOfFundamentalMatrix_66) {
  // Build two matrices that differ only in entries that should not affect the
  // result, and verify the outputs are identical.
  Eigen::Matrix3d F1 = Eigen::Matrix3d::Zero();
  Eigen::Matrix3d F2 = Eigen::Matrix3d::Zero();

  // Column used in the computation is identical.
  F1(0, 0) = 1.0;  F1(1, 0) = 2.0;  F1(2, 0) = 3.0;
  F2(0, 0) = 1.0;  F2(1, 0) = 2.0;  F2(2, 0) = 3.0;

  // Other entries differ.
  F1(0, 1) = 100.0; F1(1, 2) = -50.0;
  F2(0, 1) = -200.0; F2(1, 2) = 75.0;

  Eigen::Vector3d epipole(0.0, 4.0, 1.0);
  Eigen::Vector2d pt1(0.0, 1.0);
  Eigen::Vector2d pt2(1.0, 1.0);

  const double result1 =
      glomap::GetOrientationSignum(F1, epipole, pt1, pt2);
  const double result2 =
      glomap::GetOrientationSignum(F2, epipole, pt1, pt2);

  EXPECT_DOUBLE_EQ(result1, result2);
}

TEST(GetOrientationSignumTest_66, HandlesLargeValuesWithoutNaNOrInfinity_66) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
  F(0, 0) = 1e150;
  F(1, 0) = 2e150;
  F(2, 0) = -1e150;

  Eigen::Vector3d epipole(0.0, 1e150, -1e150);
  Eigen::Vector2d pt1(0.0, 1.0);
  Eigen::Vector2d pt2(1.0, -1.0);

  const double result =
      glomap::GetOrientationSignum(F, epipole, pt1, pt2);

  // We don't assert a specific numeric value here, only that it's finite.
  EXPECT_TRUE(std::isfinite(result));
}
