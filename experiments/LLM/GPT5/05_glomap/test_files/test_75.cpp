// File: glomap/math/rigid3d_test_75.cc

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <gtest/gtest.h>

#include "glomap/math/rigid3d.h"

namespace {

class CenterFromPoseTest_75 : public ::testing::Test {
 protected:
  CenterFromPoseTest_75() = default;
};

// TEST_ID: 75
// Verify that an identity pose (no rotation, no translation) has its center at the origin.
TEST_F(CenterFromPoseTest_75, IdentityPoseReturnsZero_75) {
  Eigen::Quaterniond rotation = Eigen::Quaterniond::Identity();
  Eigen::Vector3d translation = Eigen::Vector3d::Zero();

  glomap::Rigid3d pose(rotation, translation);

  const Eigen::Vector3d center = glomap::CenterFromPose(pose);

  EXPECT_NEAR(center.x(), 0.0, 1e-12);
  EXPECT_NEAR(center.y(), 0.0, 1e-12);
  EXPECT_NEAR(center.z(), 0.0, 1e-12);

  // Consistency check: applying the pose to the center should yield the origin.
  Eigen::Vector3d transformed = pose.rotation * center + pose.translation;
  EXPECT_NEAR(transformed.x(), 0.0, 1e-12);
  EXPECT_NEAR(transformed.y(), 0.0, 1e-12);
  EXPECT_NEAR(transformed.z(), 0.0, 1e-12);
}

// TEST_ID: 75
// For a pose with identity rotation and non-zero translation,
// the center should be the negative of the translation.
TEST_F(CenterFromPoseTest_75, PureTranslationReturnsNegativeTranslation_75) {
  Eigen::Quaterniond rotation = Eigen::Quaterniond::Identity();
  Eigen::Vector3d translation(1.0, -2.0, 3.5);

  glomap::Rigid3d pose(rotation, translation);

  const Eigen::Vector3d center = glomap::CenterFromPose(pose);

  EXPECT_NEAR(center.x(), -translation.x(), 1e-12);
  EXPECT_NEAR(center.y(), -translation.y(), 1e-12);
  EXPECT_NEAR(center.z(), -translation.z(), 1e-12);

  // Consistency check: applying the pose to the center should yield the origin.
  Eigen::Vector3d transformed = pose.rotation * center + pose.translation;
  EXPECT_NEAR(transformed.x(), 0.0, 1e-12);
  EXPECT_NEAR(transformed.y(), 0.0, 1e-12);
  EXPECT_NEAR(transformed.z(), 0.0, 1e-12);
}

// TEST_ID: 75
// For a general pose with rotation and translation,
// the returned center should satisfy R * center + t ≈ 0 (camera center in world).
TEST_F(CenterFromPoseTest_75, RotatedPoseMapsCenterToOrigin_75) {
  // 90 degrees around Z axis.
  Eigen::AngleAxisd angle_axis(M_PI / 2.0, Eigen::Vector3d::UnitZ());
  Eigen::Quaterniond rotation(angle_axis);
  Eigen::Vector3d translation(1.0, 2.0, -3.0);

  glomap::Rigid3d pose(rotation, translation);

  const Eigen::Vector3d center = glomap::CenterFromPose(pose);

  // Check that applying the pose to the center brings it to the origin.
  Eigen::Vector3d transformed = pose.rotation * center + pose.translation;
  EXPECT_NEAR(transformed.x(), 0.0, 1e-10);
  EXPECT_NEAR(transformed.y(), 0.0, 1e-10);
  EXPECT_NEAR(transformed.z(), 0.0, 1e-10);
}

// TEST_ID: 75
// With zero translation and any valid rotation, the center should still be at the origin,
// and applying the pose to the center keeps it at the origin.
TEST_F(CenterFromPoseTest_75, ZeroTranslationAnyRotationKeepsCenterAtOrigin_75) {
  // Arbitrary rotation (e.g., 45 degrees around Y axis).
  Eigen::AngleAxisd angle_axis(M_PI / 4.0, Eigen::Vector3d::UnitY());
  Eigen::Quaterniond rotation(angle_axis);
  Eigen::Vector3d translation = Eigen::Vector3d::Zero();

  glomap::Rigid3d pose(rotation, translation);

  const Eigen::Vector3d center = glomap::CenterFromPose(pose);

  EXPECT_NEAR(center.x(), 0.0, 1e-12);
  EXPECT_NEAR(center.y(), 0.0, 1e-12);
  EXPECT_NEAR(center.z(), 0.0, 1e-12);

  Eigen::Vector3d transformed = pose.rotation * center + pose.translation;
  EXPECT_NEAR(transformed.x(), 0.0, 1e-12);
  EXPECT_NEAR(transformed.y(), 0.0, 1e-12);
  EXPECT_NEAR(transformed.z(), 0.0, 1e-12);
}

// TEST_ID: 75
// Boundary-like case: very large translation vector with identity rotation.
// Checks numerical stability for large magnitude values.
TEST_F(CenterFromPoseTest_75, LargeTranslationNumericalStability_75) {
  Eigen::Quaterniond rotation = Eigen::Quaterniond::Identity();
  Eigen::Vector3d translation(1e6, -1e6, 5e6);

  glomap::Rigid3d pose(rotation, translation);

  const Eigen::Vector3d center = glomap::CenterFromPose(pose);

  EXPECT_NEAR(center.x(), -translation.x(), 1e-6);
  EXPECT_NEAR(center.y(), -translation.y(), 1e-6);
  EXPECT_NEAR(center.z(), -translation.z(), 1e-6);

  Eigen::Vector3d transformed = pose.rotation * center + pose.translation;
  EXPECT_NEAR(transformed.x(), 0.0, 1e-6);
  EXPECT_NEAR(transformed.y(), 0.0, 1e-6);
  EXPECT_NEAR(transformed.z(), 0.0, 1e-6);
}

}  // namespace
