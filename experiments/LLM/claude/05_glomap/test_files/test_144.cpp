#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>

namespace glomap {
double CalcAngle(const Eigen::Matrix3d& rotation1, const Eigen::Matrix3d& rotation2);
}

class CalcAngleTest_144 : public ::testing::Test {
 protected:
  const double kTolerance = 1e-8;
};

// Test that identical rotations yield 0 degrees
TEST_F(CalcAngleTest_144, IdenticalRotationsReturnZero_144) {
  Eigen::Matrix3d identity = Eigen::Matrix3d::Identity();
  double angle = glomap::CalcAngle(identity, identity);
  EXPECT_NEAR(angle, 0.0, kTolerance);
}

// Test that two identical non-identity rotations yield 0 degrees
TEST_F(CalcAngleTest_144, IdenticalNonIdentityRotationsReturnZero_144) {
  Eigen::Matrix3d R = Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d::UnitZ()).toRotationMatrix();
  double angle = glomap::CalcAngle(R, R);
  EXPECT_NEAR(angle, 0.0, kTolerance);
}

// Test 90-degree rotation around Z axis
TEST_F(CalcAngleTest_144, NinetyDegreeRotationAroundZ_144) {
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  Eigen::Matrix3d R2 = Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d::UnitZ()).toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_NEAR(angle, 90.0, kTolerance);
}

// Test 180-degree rotation around X axis
TEST_F(CalcAngleTest_144, OneEightyDegreeRotationAroundX_144) {
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  Eigen::Matrix3d R2 = Eigen::AngleAxisd(M_PI, Eigen::Vector3d::UnitX()).toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_NEAR(angle, 180.0, kTolerance);
}

// Test 180-degree rotation around Y axis
TEST_F(CalcAngleTest_144, OneEightyDegreeRotationAroundY_144) {
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  Eigen::Matrix3d R2 = Eigen::AngleAxisd(M_PI, Eigen::Vector3d::UnitY()).toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_NEAR(angle, 180.0, kTolerance);
}

// Test 45-degree rotation around Z axis
TEST_F(CalcAngleTest_144, FortyFiveDegreeRotation_144) {
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  Eigen::Matrix3d R2 = Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d::UnitZ()).toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_NEAR(angle, 45.0, kTolerance);
}

// Test symmetry: CalcAngle(R1, R2) == CalcAngle(R2, R1)
TEST_F(CalcAngleTest_144, SymmetryProperty_144) {
  Eigen::Matrix3d R1 = Eigen::AngleAxisd(M_PI / 6, Eigen::Vector3d::UnitX()).toRotationMatrix();
  Eigen::Matrix3d R2 = Eigen::AngleAxisd(M_PI / 3, Eigen::Vector3d::UnitY()).toRotationMatrix();
  double angle12 = glomap::CalcAngle(R1, R2);
  double angle21 = glomap::CalcAngle(R2, R1);
  EXPECT_NEAR(angle12, angle21, kTolerance);
}

// Test that the result is always non-negative
TEST_F(CalcAngleTest_144, ResultIsNonNegative_144) {
  Eigen::Matrix3d R1 = Eigen::AngleAxisd(0.5, Eigen::Vector3d::UnitX()).toRotationMatrix();
  Eigen::Matrix3d R2 = Eigen::AngleAxisd(-0.5, Eigen::Vector3d::UnitX()).toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_GE(angle, 0.0);
}

// Test small angle
TEST_F(CalcAngleTest_144, SmallAngle_144) {
  double small_rad = 1e-6;
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  Eigen::Matrix3d R2 = Eigen::AngleAxisd(small_rad, Eigen::Vector3d::UnitZ()).toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  double expected_deg = small_rad * 180.0 / M_PI;
  EXPECT_NEAR(angle, expected_deg, 1e-4);
}

// Test rotation around arbitrary axis
TEST_F(CalcAngleTest_144, ArbitraryAxisRotation_144) {
  Eigen::Vector3d axis = Eigen::Vector3d(1, 1, 1).normalized();
  double theta = M_PI / 3; // 60 degrees
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  Eigen::Matrix3d R2 = Eigen::AngleAxisd(theta, axis).toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_NEAR(angle, 60.0, kTolerance);
}

// Test relative rotation between two non-identity rotations
TEST_F(CalcAngleTest_144, RelativeRotation_144) {
  // R1 = Rz(30°), R2 = Rz(90°), relative angle = 60°
  Eigen::Matrix3d R1 = Eigen::AngleAxisd(M_PI / 6, Eigen::Vector3d::UnitZ()).toRotationMatrix();
  Eigen::Matrix3d R2 = Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d::UnitZ()).toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_NEAR(angle, 60.0, kTolerance);
}

// Test that the angle is bounded by [0, 180]
TEST_F(CalcAngleTest_144, AngleBoundedByZeroAnd180_144) {
  // Even with a "270 degree" rotation, the geodesic distance should be 90°
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  Eigen::Matrix3d R2 = Eigen::AngleAxisd(3 * M_PI / 2, Eigen::Vector3d::UnitZ()).toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_GE(angle, 0.0);
  EXPECT_LE(angle, 180.0 + kTolerance);
  // 270° rotation is equivalent to -90° rotation, so angle should be 90°
  EXPECT_NEAR(angle, 90.0, kTolerance);
}

// Test with composed rotations around different axes
TEST_F(CalcAngleTest_144, ComposedRotations_144) {
  Eigen::Matrix3d Rx = Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d::UnitX()).toRotationMatrix();
  Eigen::Matrix3d Ry = Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d::UnitY()).toRotationMatrix();
  Eigen::Matrix3d R1 = Rx;
  Eigen::Matrix3d R2 = Rx * Ry;
  // The relative rotation is R1^T * R2 = Rx^T * Rx * Ry = Ry, which is 45° around Y
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_NEAR(angle, 45.0, kTolerance);
}

// Test with inverse rotation (R and R^T should give same angle from identity)
TEST_F(CalcAngleTest_144, InverseRotationSameAngle_144) {
  Eigen::Matrix3d R = Eigen::AngleAxisd(M_PI / 5, Eigen::Vector3d(1, 2, 3).normalized()).toRotationMatrix();
  Eigen::Matrix3d I = Eigen::Matrix3d::Identity();
  double angle1 = glomap::CalcAngle(I, R);
  double angle2 = glomap::CalcAngle(I, R.transpose());
  EXPECT_NEAR(angle1, angle2, kTolerance);
}

// Test exact 120 degrees
TEST_F(CalcAngleTest_144, ExactOneHundredTwentyDegrees_144) {
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  Eigen::Matrix3d R2 = Eigen::AngleAxisd(2.0 * M_PI / 3.0, Eigen::Vector3d::UnitX()).toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_NEAR(angle, 120.0, kTolerance);
}
