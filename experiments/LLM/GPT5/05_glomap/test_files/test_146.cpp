// File: rigid3d_test_146.cc

#include <cmath>
#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "glomap/math/rigid3d.h"  // Adjust include path to your project layout

namespace {

using glomap::RotationToAngleAxis;

// Normal operation: identity rotation → zero angle-axis vector
TEST(RotationToAngleAxisTest_146, IdentityRotationReturnsZeroVector_146) {
  Eigen::Matrix3d rot = Eigen::Matrix3d::Identity();

  Eigen::Vector3d aa_vec = RotationToAngleAxis(rot);

  const double kTolerance = 1e-12;
  EXPECT_NEAR(aa_vec.x(), 0.0, kTolerance);
  EXPECT_NEAR(aa_vec.y(), 0.0, kTolerance);
  EXPECT_NEAR(aa_vec.z(), 0.0, kTolerance);
}

// Normal operation: 90-degree rotation around X-axis
TEST(RotationToAngleAxisTest_146, RotationAroundXAxis_ReturnsExpectedAngleAxis_146) {
  const double angle = M_PI / 2.0;
  Eigen::Vector3d axis(1.0, 0.0, 0.0);
  Eigen::AngleAxisd aa(angle, axis);
  Eigen::Matrix3d rot = aa.toRotationMatrix();

  Eigen::Vector3d aa_vec = RotationToAngleAxis(rot);

  const double kTolerance = 1e-9;
  EXPECT_NEAR(aa_vec.x(), angle, kTolerance);
  EXPECT_NEAR(aa_vec.y(), 0.0,   kTolerance);
  EXPECT_NEAR(aa_vec.z(), 0.0,   kTolerance);
}

// Normal operation: 90-degree rotation around Z-axis
TEST(RotationToAngleAxisTest_146, RotationAroundZAxis_ReturnsExpectedAngleAxis_146) {
  const double angle = M_PI / 2.0;
  Eigen::Vector3d axis(0.0, 0.0, 1.0);
  Eigen::AngleAxisd aa(angle, axis);
  Eigen::Matrix3d rot = aa.toRotationMatrix();

  Eigen::Vector3d aa_vec = RotationToAngleAxis(rot);

  const double kTolerance = 1e-9;
  EXPECT_NEAR(aa_vec.x(), 0.0,   kTolerance);
  EXPECT_NEAR(aa_vec.y(), 0.0,   kTolerance);
  EXPECT_NEAR(aa_vec.z(), angle, kTolerance);
}

// General case: arbitrary axis and angle should match magnitude & direction
TEST(RotationToAngleAxisTest_146, ArbitraryAxisRotation_MatchesAngleAndAxis_146) {
  const double angle = M_PI / 3.0;  // 60 degrees
  Eigen::Vector3d axis(1.0, 2.0, 3.0);
  axis.normalize();

  Eigen::AngleAxisd aa(angle, axis);
  Eigen::Matrix3d rot = aa.toRotationMatrix();

  Eigen::Vector3d aa_vec = RotationToAngleAxis(rot);

  const double result_angle = aa_vec.norm();
  Eigen::Vector3d result_axis = aa_vec.normalized();

  const double kTolerance = 1e-9;
  // Check angle magnitude
  EXPECT_NEAR(result_angle, angle, kTolerance);
  // Check axis direction
  EXPECT_NEAR(result_axis.x(), axis.x(), kTolerance);
  EXPECT_NEAR(result_axis.y(), axis.y(), kTolerance);
  EXPECT_NEAR(result_axis.z(), axis.z(), kTolerance);
}

// Boundary condition: 180-degree rotation (pi radians)
TEST(RotationToAngleAxisTest_146, PiRotation_ReconstructsOriginalMatrix_146) {
  const double angle = M_PI;  // 180 degrees
  Eigen::Vector3d axis(0.0, 1.0, 0.0);
  Eigen::AngleAxisd aa(angle, axis);
  Eigen::Matrix3d rot = aa.toRotationMatrix();

  Eigen::Vector3d aa_vec = RotationToAngleAxis(rot);

  double result_angle = aa_vec.norm();
  Eigen::Vector3d result_axis = aa_vec.normalized();

  // Reconstruct rotation from returned angle-axis and compare with original.
  Eigen::AngleAxisd reconstructed(result_angle, result_axis);
  Eigen::Matrix3d rot_reconstructed = reconstructed.toRotationMatrix();

  const double kTolerance = 1e-9;
  EXPECT_TRUE(rot_reconstructed.isApprox(rot, kTolerance));

  // Angle should still be pi in magnitude for a 180-degree rotation
  EXPECT_NEAR(result_angle, angle, kTolerance);
}

}  // namespace
