// File: glomap/math/rigid3d_test.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "glomap/math/rigid3d.h"

namespace {

class CalcAngleTest_141 : public ::testing::Test {
 protected:
  // Helper to build a pose with given rotation and zero translation.
  glomap::Rigid3d MakePose(const Eigen::Quaterniond& rotation) {
    return glomap::Rigid3d(rotation, Eigen::Vector3d::Zero());
  }
};

// Normal operation: identical poses -> angle 0 degrees (within tolerance).
TEST_F(CalcAngleTest_141, ZeroAngleForIdenticalRotations_141) {
  const Eigen::Quaterniond q_identity = Eigen::Quaterniond::Identity();
  const glomap::Rigid3d pose1 = MakePose(q_identity);
  const glomap::Rigid3d pose2 = MakePose(q_identity);

  const double angle_deg = glomap::CalcAngle(pose1, pose2);

  EXPECT_NEAR(angle_deg, 0.0, 1e-10);
}

// Boundary condition: 90-degree rotation difference around Z axis.
TEST_F(CalcAngleTest_141, NinetyDegreeRotationDifference_141) {
  const Eigen::Quaterniond q_identity = Eigen::Quaterniond::Identity();
  const Eigen::Quaterniond q_90z =
      Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitZ());

  const glomap::Rigid3d pose_identity = MakePose(q_identity);
  const glomap::Rigid3d pose_90z = MakePose(q_90z);

  const double angle_deg = glomap::CalcAngle(pose_identity, pose_90z);

  EXPECT_NEAR(angle_deg, 90.0, 1e-6);
}

// Boundary condition: 180-degree rotation difference around X axis.
TEST_F(CalcAngleTest_141, OneEightyDegreeRotationDifference_141) {
  const Eigen::Quaterniond q_identity = Eigen::Quaterniond::Identity();
  const Eigen::Quaterniond q_180x =
      Eigen::AngleAxisd(M_PI, Eigen::Vector3d::UnitX());

  const glomap::Rigid3d pose_identity = MakePose(q_identity);
  const glomap::Rigid3d pose_180x = MakePose(q_180x);

  const double angle_deg = glomap::CalcAngle(pose_identity, pose_180x);

  EXPECT_NEAR(angle_deg, 180.0, 1e-6);
}

// Observable behavior: translation should not affect the computed angle.
TEST_F(CalcAngleTest_141, TranslationDoesNotAffectAngle_141) {
  const Eigen::Quaterniond q_rot =
      Eigen::AngleAxisd(M_PI / 3.0, Eigen::Vector3d::UnitY());  // 60 degrees

  const glomap::Rigid3d pose_zero_translation(q_rot, Eigen::Vector3d::Zero());
  const glomap::Rigid3d pose_nonzero_translation(
      q_rot, Eigen::Vector3d(1.0, -2.0, 3.0));

  const double angle_deg =
      glomap::CalcAngle(pose_zero_translation, pose_nonzero_translation);

  // Same rotation => angle should be ~0 regardless of translation.
  EXPECT_NEAR(angle_deg, 0.0, 1e-10);
}

// General property: angle should be symmetric and within [0, 180] degrees.
TEST_F(CalcAngleTest_141, SymmetryAndRange_141) {
  const Eigen::Quaterniond q1 =
      Eigen::AngleAxisd(M_PI / 4.0, Eigen::Vector3d::UnitX());  // 45 deg
  const Eigen::Quaterniond q2 =
      Eigen::AngleAxisd(M_PI / 3.0, Eigen::Vector3d::UnitY());  // 60 deg

  const glomap::Rigid3d pose1 = MakePose(q1);
  const glomap::Rigid3d pose2 = MakePose(q2);

  const double angle12 = glomap::CalcAngle(pose1, pose2);
  const double angle21 = glomap::CalcAngle(pose2, pose1);

  // Symmetry: CalcAngle(p1, p2) == CalcAngle(p2, p1) (within tolerance).
  EXPECT_NEAR(angle12, angle21, 1e-10);

  // Range check: returned angle should be between 0 and 180 degrees.
  EXPECT_GE(angle12, 0.0);
  EXPECT_LE(angle12, 180.0 + 1e-9);
}

}  // namespace
