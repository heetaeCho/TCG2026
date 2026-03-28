#include <gtest/gtest.h>
#include <Eigen/Core>

#include "glomap/math/two_view_geometry.h"  // Adjust include path if needed.

namespace {

class SampsonErrorTest_67 : public ::testing::Test {};

// Normal operation: simple numeric case where we can compute the expected value
// E = I, x1 = (1, 0), x2 = (0, 1)
// Ex1 = (1, 0, 1), E^T x2 = (0, 1, 1)
// C  = Ex1 · x2_h = 1
// Cx = 1^2 + 0^2 = 1
// Cy = 0^2 + 1^2 = 1
// r2 = 1^2 / (1 + 1) = 0.5
TEST_F(SampsonErrorTest_67, IdentityMatrixSimplePoints_ReturnsExpectedValue_67) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(1.0, 0.0);
  Eigen::Vector2d x2(0.0, 1.0);

  const double error = glomap::SampsonError(E, x1, x2);

  EXPECT_NEAR(error, 0.5, 1e-12);
}

// Property-based behavior: scaling the essential matrix should not change
// the Sampson error for the same points, since both numerator and denominator
// scale quadratically with E.
TEST_F(SampsonErrorTest_67, ScalingEssentialMatrix_DoesNotChangeError_67) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Identity();
  Eigen::Matrix3d E_scaled = 2.5 * E;  // Any nonzero scalar

  Eigen::Vector2d x1(1.0, 0.0);
  Eigen::Vector2d x2(0.0, 1.0);

  const double error_original = glomap::SampsonError(E, x1, x2);
  const double error_scaled   = glomap::SampsonError(E_scaled, x1, x2);

  EXPECT_NEAR(error_original, error_scaled, 1e-12);
}

// Boundary / special condition: perfect epipolar constraint.
// Choose E and points so that x2^T * E * x1 == 0 but the denominator is nonzero.
//
// Let
//   E = [1 0 0;
//        0 0 0;
//        0 0 0]
//   x1 = (1, 0)  -> x1_h = (1, 0, 1)
//   x2 = (0, 2)  -> x2_h = (0, 2, 1)
//
// Ex1 = (1, 0, 0)
// E^T x2 = (0, 0, 0)
// C  = Ex1 · x2_h = (1, 0, 0) · (0, 2, 1) = 0
// Cx = 1^2 + 0^2 = 1
// Cy = 0
// r2 = 0^2 / (1 + 0) = 0
TEST_F(SampsonErrorTest_67, PerfectEpipolarConstraint_GivesZeroError_67) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Zero();
  E(0, 0) = 1.0;

  Eigen::Vector2d x1(1.0, 0.0);
  Eigen::Vector2d x2(0.0, 2.0);

  const double error = glomap::SampsonError(E, x1, x2);

  EXPECT_NEAR(error, 0.0, 1e-12);
}

// General sanity check: for arbitrary non-degenerate inputs, the error should
// be finite and non-negative (since it is a squared residual).
TEST_F(SampsonErrorTest_67, ArbitraryInputs_ReturnsNonNegativeError_67) {
  Eigen::Matrix3d E;
  E << 0.5, -1.0, 2.0,
       1.5,  0.3, -0.7,
       -0.2, 0.9,  1.1;

  Eigen::Vector2d x1(1.5, -0.5);
  Eigen::Vector2d x2(-0.7, 2.0);

  const double error = glomap::SampsonError(E, x1, x2);

  EXPECT_GE(error, 0.0);
  EXPECT_TRUE(std::isfinite(error));
}

}  // namespace
