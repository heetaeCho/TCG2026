// two_view_geometry_test_139.cc
//
// Unit tests for glomap::SampsonError (TEST_ID = 139)

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <cmath>

// Assuming the function is declared in this header.
#include "glomap/math/two_view_geometry.h"

namespace {

using glomap::SampsonError;

// Helper to build homogeneous 3D point (x, y, z)
Eigen::Vector3d MakePoint(double x, double y, double z) {
  return Eigen::Vector3d(x, y, z);
}

// Normal operation: perfect epipolar constraint should give (approximately) zero error.
TEST(SampsonErrorTest_139, PerfectEpipolarConstraintReturnsZero_139) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Identity();

  // Choose x1, x2 such that x1 ⋅ x2 == 0 (in 3D), to make C = 0.
  Eigen::Vector3d x1 = MakePoint(1.0, 0.0, 1.0);
  Eigen::Vector3d x2 = MakePoint(0.0, 1.0, 0.0);

  const double error = SampsonError(E, x1, x2);

  EXPECT_NEAR(error, 0.0, 1e-15);
}

// Normal operation: check against a manually derived expected value for a simple case.
TEST(SampsonErrorTest_139, IdentityMatrixKnownValue_139) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Identity();

  // Homogeneous points with z = 1.
  Eigen::Vector3d x1 = MakePoint(1.0, 2.0, 1.0);
  Eigen::Vector3d x2 = MakePoint(3.0, 4.0, 1.0);

  const double error = SampsonError(E, x1, x2);

  // For E = I and z1 = z2 = 1, algebra on the given implementation yields:
  // r^2 = ( (x1 · x2)^2 ) / (x1_x^2 + x1_y^2 + x2_x^2 + x2_y^2)
  const double dot = x1.dot(x2);  // 1*3 + 2*4 + 1*1 = 12
  const double denom_xy =
      x1.x() * x1.x() + x1.y() * x1.y() +
      x2.x() * x2.x() + x2.y() * x2.y();  // 1 + 4 + 9 + 16 = 30
  const double expected = (dot * dot) / denom_xy;  // 144 / 30 = 4.8

  EXPECT_NEAR(error, expected, 1e-12);
}

// Property test: SampsonError should be invariant under E -> -E.
TEST(SampsonErrorTest_139, InvariantUnderNegatingEssentialMatrix_139) {
  Eigen::Matrix3d E;
  E << 0.0, -1.0, 2.0,
       1.0,  0.5, 3.0,
      -2.0,  4.0, 0.0;

  Eigen::Vector3d x1 = MakePoint(0.5, -1.0, 2.0);
  Eigen::Vector3d x2 = MakePoint(1.5,  0.5, 3.0);

  const double error_pos = SampsonError(E,  x1, x2);
  const double error_neg = SampsonError(-E, x1, x2);

  EXPECT_NEAR(error_pos, error_neg, 1e-15);
}

// Property test: SampsonError should always be non-negative.
TEST(SampsonErrorTest_139, ErrorIsNonNegative_139) {
  Eigen::Matrix3d E;
  E << 0.1, -0.2, 0.3,
       0.4,  0.5, -0.6,
      -0.7, 0.8,  0.9;

  Eigen::Vector3d x1 = MakePoint(-1.0, 2.0, 0.5);
  Eigen::Vector3d x2 = MakePoint( 3.0,-4.0, 1.5);

  const double error = SampsonError(E, x1, x2);

  EXPECT_GE(error, 0.0);
}

// Boundary-like case: zero depth coordinates rely entirely on EPS; result should be finite.
TEST(SampsonErrorTest_139, HandlesZeroDepthWithEpsilonSafely_139) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Identity();

  // z-components are zero, so divisions use EPS internally.
  Eigen::Vector3d x1 = MakePoint(1.0, -2.0, 0.0);
  Eigen::Vector3d x2 = MakePoint(0.5,  3.0, 0.0);

  const double error = SampsonError(E, x1, x2);

  EXPECT_TRUE(std::isfinite(error));
}

}  // namespace
