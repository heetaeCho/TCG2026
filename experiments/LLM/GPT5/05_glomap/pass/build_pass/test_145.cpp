// File: rigid3d_to_angle_axis_test_145.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "glomap/math/rigid3d.h"

namespace {

class Rigid3dToAngleAxisTest_145 : public ::testing::Test {
 protected:
  const double kTolerance = 1e-10;
};

TEST_F(Rigid3dToAngleAxisTest_145, IdentityRotationReturnsZero_145) {
  glomap::Rigid3d pose;

  // Identity rotation (no rotation).
  pose.rotation = Eigen::Quaterniond::Identity();
  pose.translation = Eigen::Vector3d::Zero();

  const Eigen::Vector3d aa_vec = glomap::Rigid3dToAngleAxis(pose);

  EXPECT_NEAR(aa_vec.x(), 0.0, kTolerance);
  EXPECT_NEAR(aa_vec.y(), 0.0, kTolerance);
  EXPECT_NEAR(aa_vec.z(), 0.0, kTolerance);
  EXPECT_NEAR(aa_vec.norm(), 0.0, kTolerance);
}

TEST_F(Rigid3dToAngleAxisTest_145, RotationAroundZ90Degrees_145) {
  glomap::Rigid3d pose;

  constexpr double kPi = 3.14159265358979323846;
  const double angle = kPi / 2.0;  // 90 degrees
  const Eigen::Vector3d axis(0.0, 0.0, 1.0);

  // Build quaternion for 90° around Z.
  Eigen::AngleAxisd aa(angle, axis);
  pose.rotation = Eigen::Quaterniond(aa);
  pose.translation = Eigen::Vector3d::Zero();

  const Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

  EXPECT_NEAR(result.x(), 0.0, kTolerance);
  EXPECT_NEAR(result.y(), 0.0, kTolerance);
  EXPECT_NEAR(result.z(), angle, kTolerance);

  // Magnitude of angle-axis vector should equal rotation angle.
  EXPECT_NEAR(result.norm(), angle, kTolerance);
}

TEST_F(Rigid3dToAngleAxisTest_145, RotationAroundX180Degrees_145) {
  glomap::Rigid3d pose;

  constexpr double kPi = 3.14159265358979323846;
  const double angle = kPi;  // 180 degrees
  const Eigen::Vector3d axis(1.0, 0.0, 0.0);

  Eigen::AngleAxisd aa(angle, axis);
  pose.rotation = Eigen::Quaterniond(aa);
  pose.translation = Eigen::Vector3d::Zero();

  const Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

  EXPECT_NEAR(result.x(), angle, kTolerance);
  EXPECT_NEAR(result.y(), 0.0, kTolerance);
  EXPECT_NEAR(result.z(), 0.0, kTolerance);
  EXPECT_NEAR(result.norm(), angle, kTolerance);
}

TEST_F(Rigid3dToAngleAxisTest_145, NegativeAxisDirectionProducesNegativeVector_145) {
  glomap::Rigid3d pose;

  constexpr double kPi = 3.14159265358979323846;
  const double angle = kPi / 3.0;  // 60 degrees
  const Eigen::Vector3d axis(0.0, -1.0, 0.0);  // negative Y axis

  Eigen::AngleAxisd aa(angle, axis);
  pose.rotation = Eigen::Quaterniond(aa);
  pose.translation = Eigen::Vector3d::Zero();

  const Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

  EXPECT_NEAR(result.x(), 0.0, kTolerance);
  EXPECT_NEAR(result.y(), -angle, kTolerance);
  EXPECT_NEAR(result.z(), 0.0, kTolerance);
  EXPECT_NEAR(result.norm(), angle, kTolerance);
}

TEST_F(Rigid3dToAngleAxisTest_145, TranslationDoesNotAffectResult_145) {
  glomap::Rigid3d pose1;
  glomap::Rigid3d pose2;

  constexpr double kPi = 3.14159265358979323846;
  const double angle = kPi / 4.0;  // 45 degrees
  const Eigen::Vector3d axis(0.0, 0.0, 1.0);

  Eigen::AngleAxisd aa(angle, axis);
  const Eigen::Quaterniond q(aa);

  // Same rotation, different translations.
  pose1.rotation = q;
  pose1.translation = Eigen::Vector3d(1.0, 2.0, 3.0);

  pose2.rotation = q;
  pose2.translation = Eigen::Vector3d(-5.0, 0.5, 10.0);

  const Eigen::Vector3d result1 = glomap::Rigid3dToAngleAxis(pose1);
  const Eigen::Vector3d result2 = glomap::Rigid3dToAngleAxis(pose2);

  EXPECT_NEAR(result1.x(), result2.x(), kTolerance);
  EXPECT_NEAR(result1.y(), result2.y(), kTolerance);
  EXPECT_NEAR(result1.z(), result2.z(), kTolerance);
  EXPECT_NEAR(result1.norm(), result2.norm(), kTolerance);
}

}  // namespace
