#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>

namespace glomap {
Eigen::Vector3d RotationToAngleAxis(const Eigen::Matrix3d& rot);
}

class RotationToAngleAxisTest_146 : public ::testing::Test {
 protected:
  static constexpr double kTolerance = 1e-10;
};

// Test identity rotation returns zero angle-axis vector
TEST_F(RotationToAngleAxisTest_146, IdentityRotationReturnsZeroVector_146) {
  Eigen::Matrix3d identity = Eigen::Matrix3d::Identity();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(identity);
  EXPECT_NEAR(result.norm(), 0.0, kTolerance);
}

// Test rotation around X axis by 90 degrees
TEST_F(RotationToAngleAxisTest_146, RotationAroundXAxis90Degrees_146) {
  double angle = M_PI / 2.0;
  Eigen::Matrix3d rot = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitX()).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);
  
  EXPECT_NEAR(result.norm(), angle, kTolerance);
  // The axis should be aligned with X
  Eigen::Vector3d expected = angle * Eigen::Vector3d::UnitX();
  EXPECT_NEAR(result(0), expected(0), kTolerance);
  EXPECT_NEAR(result(1), expected(1), kTolerance);
  EXPECT_NEAR(result(2), expected(2), kTolerance);
}

// Test rotation around Y axis by 90 degrees
TEST_F(RotationToAngleAxisTest_146, RotationAroundYAxis90Degrees_146) {
  double angle = M_PI / 2.0;
  Eigen::Matrix3d rot = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitY()).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);
  
  EXPECT_NEAR(result.norm(), angle, kTolerance);
  Eigen::Vector3d expected = angle * Eigen::Vector3d::UnitY();
  EXPECT_NEAR(result(0), expected(0), kTolerance);
  EXPECT_NEAR(result(1), expected(1), kTolerance);
  EXPECT_NEAR(result(2), expected(2), kTolerance);
}

// Test rotation around Z axis by 90 degrees
TEST_F(RotationToAngleAxisTest_146, RotationAroundZAxis90Degrees_146) {
  double angle = M_PI / 2.0;
  Eigen::Matrix3d rot = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ()).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);
  
  EXPECT_NEAR(result.norm(), angle, kTolerance);
  Eigen::Vector3d expected = angle * Eigen::Vector3d::UnitZ();
  EXPECT_NEAR(result(0), expected(0), kTolerance);
  EXPECT_NEAR(result(1), expected(1), kTolerance);
  EXPECT_NEAR(result(2), expected(2), kTolerance);
}

// Test rotation by 180 degrees around X axis
TEST_F(RotationToAngleAxisTest_146, RotationAroundXAxis180Degrees_146) {
  double angle = M_PI;
  Eigen::Matrix3d rot = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitX()).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);
  
  EXPECT_NEAR(result.norm(), angle, kTolerance);
}

// Test small rotation angle
TEST_F(RotationToAngleAxisTest_146, SmallRotationAngle_146) {
  double angle = 1e-8;
  Eigen::Vector3d axis = Eigen::Vector3d::UnitZ();
  Eigen::Matrix3d rot = Eigen::AngleAxisd(angle, axis).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);
  
  EXPECT_NEAR(result.norm(), angle, 1e-6);
}

// Test rotation around an arbitrary axis
TEST_F(RotationToAngleAxisTest_146, ArbitraryAxisRotation_146) {
  double angle = 1.2;
  Eigen::Vector3d axis(1.0, 2.0, 3.0);
  axis.normalize();
  Eigen::Matrix3d rot = Eigen::AngleAxisd(angle, axis).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);
  
  EXPECT_NEAR(result.norm(), angle, kTolerance);
  Eigen::Vector3d expected = angle * axis;
  EXPECT_NEAR(result(0), expected(0), kTolerance);
  EXPECT_NEAR(result(1), expected(1), kTolerance);
  EXPECT_NEAR(result(2), expected(2), kTolerance);
}

// Test that converting to angle-axis and back gives the same rotation matrix
TEST_F(RotationToAngleAxisTest_146, RoundTripConsistency_146) {
  double angle = 0.75;
  Eigen::Vector3d axis(0.5, -0.3, 0.8);
  axis.normalize();
  Eigen::Matrix3d rot = Eigen::AngleAxisd(angle, axis).toRotationMatrix();
  Eigen::Vector3d aa = glomap::RotationToAngleAxis(rot);
  
  double recovered_angle = aa.norm();
  Eigen::Vector3d recovered_axis = aa.normalized();
  Eigen::Matrix3d recovered_rot = Eigen::AngleAxisd(recovered_angle, recovered_axis).toRotationMatrix();
  
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_NEAR(rot(i, j), recovered_rot(i, j), kTolerance);
    }
  }
}

// Test negative angle (rotation in opposite direction)
TEST_F(RotationToAngleAxisTest_146, NegativeAngleRotation_146) {
  double angle = -M_PI / 3.0;
  Eigen::Vector3d axis = Eigen::Vector3d::UnitY();
  Eigen::Matrix3d rot = Eigen::AngleAxisd(angle, axis).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);
  
  // AngleAxis normalizes to positive angle, so the result norm should be |angle|
  // but the direction may flip
  EXPECT_NEAR(result.norm(), std::abs(angle), kTolerance);
  
  // Verify that the angle-axis representation is equivalent
  // Either (angle, axis) or (-angle, -axis) represents the same rotation
  Eigen::Vector3d expected_option1 = std::abs(angle) * (-axis);  // positive angle, negated axis
  Eigen::Vector3d expected_option2 = angle * axis;  // negative angle, same axis (but Eigen normalizes)
  
  // Both should give the same vector
  bool matches = (result - expected_option1).norm() < kTolerance ||
                 (result - expected_option2).norm() < kTolerance;
  EXPECT_TRUE(matches);
}

// Test rotation by 45 degrees around Z
TEST_F(RotationToAngleAxisTest_146, RotationAroundZAxis45Degrees_146) {
  double angle = M_PI / 4.0;
  Eigen::Matrix3d rot = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ()).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);
  
  Eigen::Vector3d expected(0.0, 0.0, angle);
  EXPECT_NEAR(result(0), expected(0), kTolerance);
  EXPECT_NEAR(result(1), expected(1), kTolerance);
  EXPECT_NEAR(result(2), expected(2), kTolerance);
}

// Test near-180-degree rotation around arbitrary axis
TEST_F(RotationToAngleAxisTest_146, NearPiRotation_146) {
  double angle = M_PI - 1e-6;
  Eigen::Vector3d axis(0.6, 0.8, 0.0);
  axis.normalize();
  Eigen::Matrix3d rot = Eigen::AngleAxisd(angle, axis).toRotationMatrix();
  Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);
  
  EXPECT_NEAR(result.norm(), angle, 1e-4);
}

// Test multiple different angles produce correct magnitudes
TEST_F(RotationToAngleAxisTest_146, MultipleAnglesCorrectMagnitude_146) {
  std::vector<double> angles = {0.1, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0};
  Eigen::Vector3d axis = Eigen::Vector3d(1, 1, 1).normalized();
  
  for (double angle : angles) {
    Eigen::Matrix3d rot = Eigen::AngleAxisd(angle, axis).toRotationMatrix();
    Eigen::Vector3d result = glomap::RotationToAngleAxis(rot);
    EXPECT_NEAR(result.norm(), angle, kTolerance) << "Failed for angle: " << angle;
  }
}
