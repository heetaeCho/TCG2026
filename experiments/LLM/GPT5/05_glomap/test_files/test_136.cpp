// File: two_view_geometry_test_136.cc

#include <gtest/gtest.h>
#include <Eigen/Dense>

// Forward declaration of the function under test.
// The actual implementation is in glomap/math/two_view_geometry.cc.
namespace glomap {
double GetOrientationSignum(const Eigen::Matrix3d& F,
                            const Eigen::Vector3d& epipole,
                            const Eigen::Vector2d& pt1,
                            const Eigen::Vector2d& pt2);
}

class GetOrientationSignumTest_136 : public ::testing::Test {};

// Normal case: both terms positive → positive result.
TEST_F(GetOrientationSignumTest_136, ReturnsPositiveWhenBothTermsPositive_136) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
  F(0, 0) = 1.0;   // signum1 = 1 * pt2.x
  Eigen::Vector3d epipole(0.0, 2.0, 1.0);  // signum2 = 2 - 1 * pt1.y
  Eigen::Vector2d pt1(0.5, 1.0);           // signum2 = 1.0
  Eigen::Vector2d pt2(1.0, 0.0);           // signum1 = 1.0

  double result = glomap::GetOrientationSignum(F, epipole, pt1, pt2);

  // Expected = 1.0 * 1.0 = 1.0
  EXPECT_DOUBLE_EQ(result, 1.0);
}

// Normal case: one term positive, one negative → negative result.
TEST_F(GetOrientationSignumTest_136, ReturnsNegativeWhenSignsDiffer_136) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
  F(0, 0) = -2.0;       // signum1 = -2 * pt2.x
  Eigen::Vector3d epipole(0.0, 3.0, 1.0); // signum2 = 3 - 1 * pt1.y
  Eigen::Vector2d pt1(0.0, 1.0);          // signum2 = 2.0
  Eigen::Vector2d pt2(1.0, 0.0);          // signum1 = -2.0

  double result = glomap::GetOrientationSignum(F, epipole, pt1, pt2);

  // Expected = -2.0 * 2.0 = -4.0
  EXPECT_DOUBLE_EQ(result, -4.0);
}

// Boundary case: signum1 term becomes zero → overall result zero.
TEST_F(GetOrientationSignumTest_136, ReturnsZeroWhenFirstTermIsZero_136) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
  // With all relevant entries 0, signum1 = 0 regardless of pt2.
  Eigen::Vector3d epipole(0.0, 5.0, 2.0);
  Eigen::Vector2d pt1(0.0, 1.0);
  Eigen::Vector2d pt2(3.0, 4.0);

  double result = glomap::GetOrientationSignum(F, epipole, pt1, pt2);

  EXPECT_DOUBLE_EQ(result, 0.0);
}

// Boundary case: signum2 term becomes zero → overall result zero.
TEST_F(GetOrientationSignumTest_136, ReturnsZeroWhenSecondTermIsZero_136) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
  F(0, 0) = 3.0;  // non-zero first factor
  Eigen::Vector3d epipole(0.0, 4.0, 2.0);
  Eigen::Vector2d pt1(0.0, 2.0);  // signum2 = 4 - 2 * 2 = 0
  Eigen::Vector2d pt2(1.0, 0.0);  // signum1 = 3.0

  double result = glomap::GetOrientationSignum(F, epipole, pt1, pt2);

  EXPECT_DOUBLE_EQ(result, 0.0);
}

// Stress / large-value case: handles large magnitudes without overflow issues.
TEST_F(GetOrientationSignumTest_136, HandlesLargeValues_136) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
  F(0, 0) = 1e6;  // signum1 = 1e6 * pt2.x
  Eigen::Vector3d epipole(0.0, 1e6, 0.0);  // signum2 = 1e6 - 0 * pt1.y = 1e6
  Eigen::Vector2d pt1(0.0, 0.0);
  Eigen::Vector2d pt2(1.0, 0.0);           // signum1 = 1e6

  double result = glomap::GetOrientationSignum(F, epipole, pt1, pt2);

  // Expected = 1e6 * 1e6 = 1e12
  EXPECT_DOUBLE_EQ(result, 1e12);
}
