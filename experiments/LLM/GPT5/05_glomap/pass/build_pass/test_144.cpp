// File: ./TestProjects/glomap/tests/math/rigid3d_calc_angle_test_144.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

// Adjust this include if the actual header path is different in your project.
#include "glomap/math/rigid3d.h"

namespace {

class CalcAngleTest_144 : public ::testing::Test {
protected:
  static Eigen::Matrix3d Identity() {
    return Eigen::Matrix3d::Identity();
  }

  static Eigen::Matrix3d RotationAroundX(double degrees) {
    double radians = degrees * M_PI / 180.0;
    return Eigen::AngleAxisd(radians, Eigen::Vector3d::UnitX()).toRotationMatrix();
  }

  static Eigen::Matrix3d RotationAroundY(double degrees) {
    double radians = degrees * M_PI / 180.0;
    return Eigen::AngleAxisd(radians, Eigen::Vector3d::UnitY()).toRotationMatrix();
  }

  static Eigen::Matrix3d RotationAroundZ(double degrees) {
    double radians = degrees * M_PI / 180.0;
    return Eigen::AngleAxisd(radians, Eigen::Vector3d::UnitZ()).toRotationMatrix();
  }
};

}  // namespace

// Normal operation: identical rotations should yield 0 degrees.
TEST_F(CalcAngleTest_144, ReturnsZeroForIdenticalRotations_144) {
  Eigen::Matrix3d R = CalcAngleTest_144::RotationAroundZ(45.0);
  double angle = glomap::CalcAngle(R, R);

  EXPECT_NEAR(angle, 0.0, 1e-9);
}

// Normal operation: rotation difference of 90 degrees around a single axis.
TEST_F(CalcAngleTest_144, ReturnsNinetyDegreesForQuarterTurn_144) {
  Eigen::Matrix3d R1 = CalcAngleTest_144::Identity();
  Eigen::Matrix3d R2 = CalcAngleTest_144::RotationAroundZ(90.0);

  double angle = glomap::CalcAngle(R1, R2);

  EXPECT_NEAR(angle, 90.0, 1e-9);
}

// Boundary condition: rotation difference of 180 degrees.
TEST_F(CalcAngleTest_144, ReturnsOneEightyDegreesForHalfTurn_144) {
  Eigen::Matrix3d R1 = CalcAngleTest_144::Identity();
  Eigen::Matrix3d R2 = CalcAngleTest_144::RotationAroundX(180.0);

  double angle = glomap::CalcAngle(R1, R2);

  EXPECT_NEAR(angle, 180.0, 1e-9);
}

// General property: CalcAngle should be symmetric in its arguments.
TEST_F(CalcAngleTest_144, SymmetricWithRespectToArguments_144) {
  Eigen::Matrix3d R1 = CalcAngleTest_144::RotationAroundX(30.0);
  Eigen::Matrix3d R2 = CalcAngleTest_144::RotationAroundY(70.0);

  double angle12 = glomap::CalcAngle(R1, R2);
  double angle21 = glomap::CalcAngle(R2, R1);

  EXPECT_NEAR(angle12, angle21, 1e-9);
}

// Invariance under common left multiplication: applying same rotation to both
// inputs should not change the relative angle.
TEST_F(CalcAngleTest_144, InvariantUnderCommonLeftMultiplication_144) {
  Eigen::Matrix3d R_base = CalcAngleTest_144::RotationAroundZ(45.0);
  Eigen::Matrix3d R1 = CalcAngleTest_144::RotationAroundX(10.0);
  Eigen::Matrix3d R2 = CalcAngleTest_144::RotationAroundX(50.0);

  double angle_original = glomap::CalcAngle(R1, R2);
  double angle_transformed = glomap::CalcAngle(R_base * R1, R_base * R2);

  EXPECT_NEAR(angle_original, angle_transformed, 1e-9);
}

// Robustness / boundary handling: input matrices that are not proper rotations
// but lead to cos_r > 1 should be safely clamped and return 0 degrees.
TEST_F(CalcAngleTest_144, ClampsCosineAboveOneToPreventNaN_144) {
  Eigen::Matrix3d R1 = CalcAngleTest_144::Identity();
  // Deliberately non-rotation matrix with large trace (6.0)
  Eigen::Matrix3d R2 = 2.0 * Eigen::Matrix3d::Identity();

  double angle = glomap::CalcAngle(R1, R2);

  // With clamping, this should behave like cos = 1 -> 0 degrees.
  EXPECT_NEAR(angle, 0.0, 1e-9);
}

// Robustness / boundary handling: input matrices that yield cos_r < -1
// should be clamped and return 180 degrees.
TEST_F(CalcAngleTest_144, ClampsCosineBelowMinusOneToPreventNaN_144) {
  Eigen::Matrix3d R1 = CalcAngleTest_144::Identity();
  // Deliberately non-rotation matrix with very negative trace (-6.0)
  Eigen::Matrix3d R2 = -2.0 * Eigen::Matrix3d::Identity();

  double angle = glomap::CalcAngle(R1, R2);

  // With clamping, this should behave like cos = -1 -> 180 degrees.
  EXPECT_NEAR(angle, 180.0, 1e-9);
}
