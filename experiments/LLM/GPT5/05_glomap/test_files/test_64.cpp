// File: gravity_calc_angle_test_64.cc

#include <gtest/gtest.h>
#include <Eigen/Core>

#include "glomap/math/gravity.h"  // Assumed header declaring glomap::CalcAngle

namespace {

using glomap::CalcAngle;

class GravityCalcAngleTest_64 : public ::testing::Test {};

// Identical non-zero vectors should have 0 degree angle.
TEST_F(GravityCalcAngleTest_64, IdenticalVectors_ReturnsZeroDegrees_64) {
  Eigen::Vector3d v1(1.0, 2.0, 3.0);
  Eigen::Vector3d v2 = v1;

  double angle_deg = CalcAngle(v1, v2);

  EXPECT_NEAR(angle_deg, 0.0, 1e-9);
}

// Opposite vectors should have 180 degree angle.
TEST_F(GravityCalcAngleTest_64, OppositeVectors_Returns180Degrees_64) {
  Eigen::Vector3d v1(1.0, 0.0, 0.0);
  Eigen::Vector3d v2(-1.0, 0.0, 0.0);

  double angle_deg = CalcAngle(v1, v2);

  EXPECT_NEAR(angle_deg, 180.0, 1e-9);
}

// Perpendicular vectors should have 90 degree angle.
TEST_F(GravityCalcAngleTest_64, PerpendicularVectors_Returns90Degrees_64) {
  Eigen::Vector3d v1(1.0, 0.0, 0.0);
  Eigen::Vector3d v2(0.0, 1.0, 0.0);

  double angle_deg = CalcAngle(v1, v2);

  EXPECT_NEAR(angle_deg, 90.0, 1e-9);
}

// Non-unit vectors with a known angle (45 degrees) should be handled correctly.
TEST_F(GravityCalcAngleTest_64, NonUnitVectors_ReturnsCorrectAngle_64) {
  // v1 and v2 have a 45-degree angle:
  // v1 = (1, 0, 0)
  // v2 = (1, 1, 0)  -> cos(theta) = 1 / sqrt(2) -> theta = 45 deg
  Eigen::Vector3d v1(1.0, 0.0, 0.0);
  Eigen::Vector3d v2(1.0, 1.0, 0.0);

  double angle_deg = CalcAngle(v1, v2);

  EXPECT_NEAR(angle_deg, 45.0, 1e-9);
}

// The angle should be symmetric: CalcAngle(a, b) == CalcAngle(b, a).
TEST_F(GravityCalcAngleTest_64, Symmetry_Property_64) {
  Eigen::Vector3d a(1.0, 2.0, 3.0);
  Eigen::Vector3d b(-4.0, 5.0, -6.0);

  double angle_ab = CalcAngle(a, b);
  double angle_ba = CalcAngle(b, a);

  EXPECT_NEAR(angle_ab, angle_ba, 1e-9);
}

// Scaling both vectors by a positive factor should not change the angle.
TEST_F(GravityCalcAngleTest_64, PositiveScaling_DoesNotChangeAngle_64) {
  Eigen::Vector3d v1(1.0, 2.0, 3.0);
  Eigen::Vector3d v2(4.0, 5.0, 6.0);

  Eigen::Vector3d v1_scaled = 2.0 * v1;
  Eigen::Vector3d v2_scaled = 3.0 * v2;

  double angle_original = CalcAngle(v1, v2);
  double angle_scaled = CalcAngle(v1_scaled, v2_scaled);

  EXPECT_NEAR(angle_original, angle_scaled, 1e-9);
}

}  // namespace
