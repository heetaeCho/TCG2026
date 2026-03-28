#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>

namespace glomap {
Eigen::Vector3d RotationToAngleAxis(const Eigen::Matrix3d& rot);
}

class RotationToAngleAxisTest_73 : public ::testing::Test {
 protected:
  static constexpr double kTolerance = 1e-10;
};

// Test identity rotation yields zero angle-axis vector
TEST_F(RotationToAngleAxisTest_73, IdentityRotationReturnsZeroVector_73) {
  Eigen::Matrix3d identity = Eigen::Matrix3d::Identity();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(identity);
  EXPECT_NEAR(result.norm(), 0.0, kTolerance);
}

// Test 90-degree rotation around the X-axis
TEST_F(RotationToAngleAxisTest_73, Rotation90DegreesAroundXAxis_73) {
  double angle = M_PI / 2.0;
  Eigen::Matrix3d rot =
      Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitX()).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);

  Eigen::Vector3d expected = angle * Eigen::Vector3d::UnitX();
  EXPECT_NEAR(result(0), expected(0), kTolerance);
  EXPECT_NEAR(result(1), expected(1), kTolerance);
  EXPECT_NEAR(result(2), expected(2), kTolerance);
}

// Test 90-degree rotation around the Y-axis
TEST_F(RotationToAngleAxisTest_73, Rotation90DegreesAroundYAxis_73) {
  double angle = M_PI / 2.0;
  Eigen::Matrix3d rot =
      Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitY()).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);

  Eigen::Vector3d expected = angle * Eigen::Vector3d::UnitY();
  EXPECT_NEAR(result(0), expected(0), kTolerance);
  EXPECT_NEAR(result(1), expected(1), kTolerance);
  EXPECT_NEAR(result(2), expected(2), kTolerance);
}

// Test 90-degree rotation around the Z-axis
TEST_F(RotationToAngleAxisTest_73, Rotation90DegreesAroundZAxis_73) {
  double angle = M_PI / 2.0;
  Eigen::Matrix3d rot =
      Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ()).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);

  Eigen::Vector3d expected = angle * Eigen::Vector3d::UnitZ();
  EXPECT_NEAR(result(0), expected(0), kTolerance);
  EXPECT_NEAR(result(1), expected(1), kTolerance);
  EXPECT_NEAR(result(2), expected(2), kTolerance);
}

// Test 180-degree rotation around an axis (boundary case)
TEST_F(RotationToAngleAxisTest_73, Rotation180DegreesAroundZAxis_73) {
  double angle = M_PI;
  Eigen::Matrix3d rot =
      Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ()).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);

  // The norm should be pi
  EXPECT_NEAR(result.norm(), M_PI, kTolerance);
}

// Test small angle rotation
TEST_F(RotationToAngleAxisTest_73, SmallAngleRotation_73) {
  double angle = 1e-8;
  Eigen::Vector3d axis = Eigen::Vector3d::UnitX();
  Eigen::Matrix3d rot =
      Eigen::AngleAxisd(angle, axis).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);

  EXPECT_NEAR(result.norm(), angle, 1e-6);
}

// Test arbitrary axis rotation
TEST_F(RotationToAngleAxisTest_73, ArbitraryAxisRotation_73) {
  double angle = 1.2;
  Eigen::Vector3d axis(1.0, 2.0, 3.0);
  axis.normalize();
  Eigen::Matrix3d rot =
      Eigen::AngleAxisd(angle, axis).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);

  Eigen::Vector3d expected = angle * axis;
  EXPECT_NEAR(result(0), expected(0), kTolerance);
  EXPECT_NEAR(result(1), expected(1), kTolerance);
  EXPECT_NEAR(result(2), expected(2), kTolerance);
}

// Test that the norm of the result equals the rotation angle
TEST_F(RotationToAngleAxisTest_73, NormEqualsAngle_73) {
  double angle = 0.75;
  Eigen::Vector3d axis(0.5, 0.5, std::sqrt(0.5));
  axis.normalize();
  Eigen::Matrix3d rot =
      Eigen::AngleAxisd(angle, axis).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);

  EXPECT_NEAR(result.norm(), angle, kTolerance);
}

// Test negative angle (rotation in opposite direction)
TEST_F(RotationToAngleAxisTest_73, NegativeAngleRotation_73) {
  double angle = -0.5;
  Eigen::Vector3d axis = Eigen::Vector3d::UnitY();
  // Eigen::AngleAxisd normalizes: negative angle becomes positive angle with flipped axis
  Eigen::Matrix3d rot =
      Eigen::AngleAxisd(angle, axis).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);

  // The result should represent the same rotation
  // Reconstructing the rotation from result should give the same matrix
  double result_angle = result.norm();
  Eigen::Vector3d result_axis = result.normalized();
  Eigen::Matrix3d reconstructed =
      Eigen::AngleAxisd(result_angle, result_axis).toRotationMatrix();
  
  EXPECT_TRUE(rot.isApprox(reconstructed, 1e-9));
}

// Test round-trip: rotation matrix -> angle-axis -> rotation matrix
TEST_F(RotationToAngleAxisTest_73, RoundTripConsistency_73) {
  double angle = 2.1;
  Eigen::Vector3d axis(0.3, 0.6, 0.7);
  axis.normalize();
  Eigen::Matrix3d rot =
      Eigen::AngleAxisd(angle, axis).toRotationMatrix();
  
  Eigen::Vector3d aa_vec = glomap::RotationToAngleAxis(rot);
  
  double recovered_angle = aa_vec.norm();
  Eigen::Vector3d recovered_axis = aa_vec.normalized();
  Eigen::Matrix3d recovered_rot =
      Eigen::AngleAxisd(recovered_angle, recovered_axis).toRotationMatrix();
  
  EXPECT_TRUE(rot.isApprox(recovered_rot, 1e-9));
}

// Test 180-degree rotation around arbitrary axis
TEST_F(RotationToAngleAxisTest_73, Rotation180DegreesArbitraryAxis_73) {
  double angle = M_PI;
  Eigen::Vector3d axis(1.0, 1.0, 0.0);
  axis.normalize();
  Eigen::Matrix3d rot =
      Eigen::AngleAxisd(angle, axis).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);

  EXPECT_NEAR(result.norm(), M_PI, 1e-9);

  // Reconstruct and verify
  double result_angle = result.norm();
  Eigen::Vector3d result_axis = result.normalized();
  Eigen::Matrix3d reconstructed =
      Eigen::AngleAxisd(result_angle, result_axis).toRotationMatrix();
  EXPECT_TRUE(rot.isApprox(reconstructed, 1e-9));
}

// Test very small rotation close to zero
TEST_F(RotationToAngleAxisTest_73, VerySmallRotation_73) {
  double angle = 1e-15;
  Eigen::Vector3d axis = Eigen::Vector3d::UnitZ();
  Eigen::Matrix3d rot =
      Eigen::AngleAxisd(angle, axis).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);

  // Should be close to zero
  EXPECT_NEAR(result.norm(), 0.0, 1e-10);
}

// Test 45-degree rotation
TEST_F(RotationToAngleAxisTest_73, Rotation45Degrees_73) {
  double angle = M_PI / 4.0;
  Eigen::Vector3d axis = Eigen::Vector3d::UnitZ();
  Eigen::Matrix3d rot =
      Eigen::AngleAxisd(angle, axis).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);

  Eigen::Vector3d expected = angle * axis;
  EXPECT_NEAR(result(0), expected(0), kTolerance);
  EXPECT_NEAR(result(1), expected(1), kTolerance);
  EXPECT_NEAR(result(2), expected(2), kTolerance);
}
