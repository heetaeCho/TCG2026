// File: gravity_test_132.cc

#include <gtest/gtest.h>
#include <Eigen/Dense>

#include "glomap/math/gravity.h"  // Assumed header declaring glomap::RotUpToAngle

namespace {

// Simple helper to construct a rotation around the Y (up) axis.
Eigen::Matrix3d MakeYRotation(double angle) {
  const double c = std::cos(angle);
  const double s = std::sin(angle);

  Eigen::Matrix3d R;
  R <<  c, 0.0,  s,
        0.0, 1.0, 0.0,
       -s, 0.0,  c;
  return R;
}

class RotUpToAngleTest_132 : public ::testing::Test {};

}  // namespace

// -----------------------------------------------------------------------------
// Normal operation: identity rotation
// -----------------------------------------------------------------------------
TEST_F(RotUpToAngleTest_132, IdentityRotationReturnsZero_132) {
  Eigen::Matrix3d R = Eigen::Matrix3d::Identity();

  const double angle_up = glomap::RotUpToAngle(R);

  EXPECT_NEAR(angle_up, 0.0, 1e-12);
}

// -----------------------------------------------------------------------------
// Normal operation: positive rotation around the up (Y) axis
// -----------------------------------------------------------------------------
TEST_F(RotUpToAngleTest_132, PositiveYRotationReturnsPositiveAngle_132) {
  const double kAngle = M_PI / 4.0;  // 45 degrees
  Eigen::Matrix3d R = MakeYRotation(kAngle);

  const double angle_up = glomap::RotUpToAngle(R);

  EXPECT_NEAR(angle_up, kAngle, 1e-9);
}

// -----------------------------------------------------------------------------
// Normal operation: negative rotation around the up (Y) axis
// -----------------------------------------------------------------------------
TEST_F(RotUpToAngleTest_132, NegativeYRotationReturnsNegativeAngle_132) {
  const double kAngle = -M_PI / 6.0;  // -30 degrees
  Eigen::Matrix3d R = MakeYRotation(kAngle);

  const double angle_up = glomap::RotUpToAngle(R);

  EXPECT_NEAR(angle_up, kAngle, 1e-9);
}

// -----------------------------------------------------------------------------
// Boundary condition: rotation close to zero
// -----------------------------------------------------------------------------
TEST_F(RotUpToAngleTest_132, VerySmallRotationIsAccurate_132) {
  const double kAngle = 1e-8;  // very small angle
  Eigen::Matrix3d R = MakeYRotation(kAngle);

  const double angle_up = glomap::RotUpToAngle(R);

  EXPECT_NEAR(angle_up, kAngle, 1e-10);
}

// -----------------------------------------------------------------------------
// Boundary condition: rotation near pi (180 degrees)
// Only the magnitude is asserted, as axis sign may flip in angle-axis.
// -----------------------------------------------------------------------------
TEST_F(RotUpToAngleTest_132, PiRotationHasPiMagnitude_132) {
  const double kAngle = M_PI;
  Eigen::Matrix3d R = MakeYRotation(kAngle);

  const double angle_up = glomap::RotUpToAngle(R);

  EXPECT_NEAR(std::abs(angle_up), M_PI, 1e-9);
}
