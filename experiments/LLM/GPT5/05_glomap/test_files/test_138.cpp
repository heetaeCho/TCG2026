// File: two_view_geometry_test_138.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <cmath>

#include "glomap/math/two_view_geometry.h"  // Assumed header declaring glomap::SampsonError

namespace {

using glomap::SampsonError;

// Normal operation: simple, hand-computable case with identity matrix.
TEST(SampsonErrorTest_138, IdentityMatrixSimplePoints_138) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(1.0, 0.0);
  Eigen::Vector2d x2(1.0, 0.0);

  // For this specific setup:
  // x1h = [1, 0, 1], x2h = [1, 0, 1]
  // Ex1 = [1, 0, 1], E^T x2 = [1, 0, 1]
  // C  = Ex1 · x2h = 1*1 + 0*0 + 1*1 = 2
  // Cx = 1^2 + 0^2 = 1,  Cy = 1^2 + 0^2 = 1
  // r2 = C^2 / (Cx + Cy) = 4 / 2 = 2
  double result = SampsonError(E, x1, x2);

  EXPECT_DOUBLE_EQ(result, 2.0);
}

// Normal operation: when the epipolar constraint is exactly satisfied, error should be zero.
TEST(SampsonErrorTest_138, ZeroErrorWhenEpipolarConstraintSatisfied_138) {
  // Construct E and points so that C = 0 but denominator is non-zero.
  Eigen::Matrix3d E = Eigen::Matrix3d::Zero();
  E(0, 0) = 1.0;  // [1 0 0
  E(1, 1) = 1.0;  //  0 1 0
                  //  0 0 0]
  Eigen::Vector2d x1(1.0, 0.0);  // x1h = [1, 0, 1]
  Eigen::Vector2d x2(0.0, 5.0);  // x2h = [0, 5, 1]

  // With this setup:
  // Ex1  = [1, 0, 0],  E^T x2 = [0, 5, 0]
  // C    = Ex1 · x2h = 1*0 + 0*5 + 0*1 = 0  => numerator = 0
  // Cx   = 1^2 + 0^2 = 1
  // Cy   = 0^2 + 5^2 = 25  => denominator = 26
  // r2   = 0 / 26 = 0
  double result = SampsonError(E, x1, x2);

  EXPECT_DOUBLE_EQ(result, 0.0);
}

// Property test: scaling the matrix E by a non-zero scalar should not change the error.
TEST(SampsonErrorTest_138, ScalingEssentialMatrixKeepsErrorInvariant_138) {
  Eigen::Matrix3d E;
  E << 0.0, -1.0, 2.0,
       1.0,  0.0, -3.0,
       0.5,  2.0,  1.0;

  Eigen::Vector2d x1(0.3, -0.7);
  Eigen::Vector2d x2(1.1, 0.4);

  double base_error   = SampsonError(E,       x1, x2);
  double scaled_error = SampsonError(2.0 * E, x1, x2);

  // Allow for a small numerical tolerance.
  EXPECT_NEAR(base_error, scaled_error, 1e-12);
}

// Boundary case: zero matrix leads to 0/0; the result should be NaN.
TEST(SampsonErrorTest_138, ZeroMatrixProducesNaN_138) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Zero();
  Eigen::Vector2d x1(1.0, 2.0);
  Eigen::Vector2d x2(-3.0, 4.0);

  double result = SampsonError(E, x1, x2);

  // With E = 0, Ex1 = 0, E^T x2 = 0, so C = 0 and Cx + Cy = 0 -> 0 / 0.
  EXPECT_TRUE(std::isnan(result));
}

}  // namespace
