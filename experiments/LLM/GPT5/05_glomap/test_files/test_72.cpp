// File: glomap_math_rigid3d_to_angleaxis_test_72.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>

#include "glomap/math/rigid3d.h"

namespace {

using glomap::Rigid3d;
using glomap::Rigid3dToAngleAxis;

constexpr double kEps72 = 1e-9;

// TEST_ID: 72
// Identity rotation should yield zero angle-axis vector.
TEST(Rigid3dToAngleAxisTest_72, IdentityRotationReturnsZero_72) {
  const Eigen::Quaterniond rotation = Eigen::Quaterniond::Identity();
  const Eigen::Vector3d translation = Eigen::Vector3d::Zero();

  const Rigid3d pose(rotation, translation);

  const Eigen::Vector3d aa_vec = Rigid3dToAngleAxis(pose);

  EXPECT_NEAR(0.0, aa_vec.norm(), kEps72);
  EXPECT_NEAR(0.0, aa_vec.x(), kEps72);
  EXPECT_NEAR(0.0, aa_vec.y(), kEps72);
  EXPECT_NEAR(0.0, aa_vec.z(), kEps72);
}

// TEST_ID: 72
// Rotation of 90 degrees around Z should give angle-axis (0, 0, +pi/2).
TEST(Rigid3dToAngleAxisTest_72, RotationAroundZAxis_QuarterTurn_72) {
  const double angle = M_PI / 2.0;
  const Eigen::Vector3d axis(0.0, 0.0, 1.0);

  const Eigen::AngleAxisd angle_axis(angle, axis);
  const Eigen::Quaterniond rotation(angle_axis);
  const Eigen::Vector3d translation = Eigen::Vector3d::Zero();

  const Rigid3d pose(rotation, translation);

  const Eigen::Vector3d aa_vec = Rigid3dToAngleAxis(pose);

  // Magnitude equals rotation angle.
  EXPECT_NEAR(angle, aa_vec.norm(), 1e-6);

  // Direction matches +Z.
  EXPECT_NEAR(0.0, aa_vec.x(), 1e-6);
  EXPECT_NEAR(0.0, aa_vec.y(), 1e-6);
  EXPECT_NEAR(angle, aa_vec.z(), 1e-6);
}

// TEST_ID: 72
// Rotation of 180 degrees around X should yield vector whose direction is ±X and magnitude pi.
TEST(Rigid3dToAngleAxisTest_72, RotationAroundXAxis_HalfTurn_72) {
  const double angle = M_PI;
  const Eigen::Vector3d axis(1.0, 0.0, 0.0);

  const Eigen::AngleAxisd angle_axis(angle, axis);
  const Eigen::Quaterniond rotation(angle_axis);
  const Eigen::Vector3d translation = Eigen::Vector3d::Zero();

  const Rigid3d pose(rotation, translation);

  const Eigen::Vector3d aa_vec = Rigid3dToAngleAxis(pose);

  // Magnitude equals pi.
  EXPECT_NEAR(angle, aa_vec.norm(), 1e-6);

  // Direction is along ±X, with no Y/Z component.
  Eigen::Vector3d dir = aa_vec.normalized();
  EXPECT_NEAR(1.0, std::abs(dir.x()), 1e-6);
  EXPECT_NEAR(0.0, dir.y(), 1e-6);
  EXPECT_NEAR(0.0, dir.z(), 1e-6);
}

// TEST_ID: 72
// Arbitrary axis and angle: angle-axis vector should have correct magnitude and direction.
TEST(Rigid3dToAngleAxisTest_72, ArbitraryAxisAndAngle_72) {
  const double angle = M_PI / 3.0;  // 60 degrees
  Eigen::Vector3d axis(1.0, 2.0, 3.0);
  axis.normalize();

  const Eigen::AngleAxisd angle_axis(angle, axis);
  const Eigen::Quaterniond rotation(angle_axis);
  const Eigen::Vector3d translation = Eigen::Vector3d::Zero();

  const Rigid3d pose(rotation, translation);

  const Eigen::Vector3d aa_vec = Rigid3dToAngleAxis(pose);

  // Magnitude equals angle.
  EXPECT_NEAR(angle, aa_vec.norm(), 1e-6);

  // Direction matches the chosen axis.
  Eigen::Vector3d dir = aa_vec.normalized();
  EXPECT_NEAR(axis.x(), dir.x(), 1e-6);
  EXPECT_NEAR(axis.y(), dir.y(), 1e-6);
  EXPECT_NEAR(axis.z(), dir.z(), 1e-6);
}

// TEST_ID: 72
// Very small rotation angle should still produce an angle-axis vector with correct small magnitude.
TEST(Rigid3dToAngleAxisTest_72, VerySmallAngleRotation_72) {
  const double angle = 1e-6;
  Eigen::Vector3d axis(0.3, -0.4, 0.5);
  axis.normalize();

  const Eigen::AngleAxisd angle_axis(angle, axis);
  const Eigen::Quaterniond rotation(angle_axis);
  const Eigen::Vector3d translation = Eigen::Vector3d::Zero();

  const Rigid3d pose(rotation, translation);

  const Eigen::Vector3d aa_vec = Rigid3dToAngleAxis(pose);

  // Magnitude should be close to the small angle.
  EXPECT_NEAR(angle, aa_vec.norm(), 1e-9);

  // Direction should be close to the axis (numerical tolerance a bit looser).
  Eigen::Vector3d dir = aa_vec.normalized();
  EXPECT_NEAR(axis.x(), dir.x(), 1e-4);
  EXPECT_NEAR(axis.y(), dir.y(), 1e-4);
  EXPECT_NEAR(axis.z(), dir.z(), 1e-4);
}

// TEST_ID: 72
// Translation part of Rigid3d should not affect the resulting angle-axis vector.
TEST(Rigid3dToAngleAxisTest_72, TranslationDoesNotAffectAngleAxis_72) {
  const double angle = M_PI / 4.0;
  const Eigen::Vector3d axis(0.0, 1.0, 0.0);

  const Eigen::AngleAxisd angle_axis(angle, axis);
  const Eigen::Quaterniond rotation(angle_axis);

  const Rigid3d pose_with_zero_translation(rotation, Eigen::Vector3d::Zero());
  const Rigid3d pose_with_nonzero_translation(
      rotation, Eigen::Vector3d(10.0, -5.0, 3.0));

  const Eigen::Vector3d aa_zero = Rigid3dToAngleAxis(pose_with_zero_translation);
  const Eigen::Vector3d aa_nonzero = Rigid3dToAngleAxis(pose_with_nonzero_translation);

  EXPECT_NEAR(aa_zero.x(), aa_nonzero.x(), 1e-9);
  EXPECT_NEAR(aa_zero.y(), aa_nonzero.y(), 1e-9);
  EXPECT_NEAR(aa_zero.z(), aa_nonzero.z(), 1e-9);
}

}  // namespace
