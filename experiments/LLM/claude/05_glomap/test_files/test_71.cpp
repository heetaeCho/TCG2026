#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>

namespace glomap {
double CalcAngle(const Eigen::Matrix3d& rotation1, const Eigen::Matrix3d& rotation2);
}

class CalcAngleTest_71 : public ::testing::Test {
 protected:
  const double kTolerance = 1e-8;
};

// Test that identical rotations yield 0 degrees
TEST_F(CalcAngleTest_71, IdenticalRotationsReturnZero_71) {
  Eigen::Matrix3d identity = Eigen::Matrix3d::Identity();
  double angle = glomap::CalcAngle(identity, identity);
  EXPECT_NEAR(angle, 0.0, kTolerance);
}

// Test that two identical non-trivial rotations yield 0 degrees
TEST_F(CalcAngleTest_71, IdenticalNonTrivialRotationsReturnZero_71) {
  Eigen::AngleAxisd aa(M_PI / 4, Eigen::Vector3d::UnitZ());
  Eigen::Matrix3d R = aa.toRotationMatrix();
  double angle = glomap::CalcAngle(R, R);
  EXPECT_NEAR(angle, 0.0, kTolerance);
}

// Test 90 degree rotation around Z axis
TEST_F(CalcAngleTest_71, NinetyDegreeRotationAroundZ_71) {
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  Eigen::AngleAxisd aa(M_PI / 2, Eigen::Vector3d::UnitZ());
  Eigen::Matrix3d R2 = aa.toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_NEAR(angle, 90.0, kTolerance);
}

// Test 180 degree rotation around X axis
TEST_F(CalcAngleTest_71, OneEightyDegreeRotationAroundX_71) {
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  Eigen::AngleAxisd aa(M_PI, Eigen::Vector3d::UnitX());
  Eigen::Matrix3d R2 = aa.toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_NEAR(angle, 180.0, kTolerance);
}

// Test 45 degree rotation around Y axis
TEST_F(CalcAngleTest_71, FortyFiveDegreeRotationAroundY_71) {
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  Eigen::AngleAxisd aa(M_PI / 4, Eigen::Vector3d::UnitY());
  Eigen::Matrix3d R2 = aa.toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_NEAR(angle, 45.0, kTolerance);
}

// Test symmetry: CalcAngle(R1, R2) == CalcAngle(R2, R1)
TEST_F(CalcAngleTest_71, SymmetryProperty_71) {
  Eigen::AngleAxisd aa1(M_PI / 6, Eigen::Vector3d::UnitX());
  Eigen::AngleAxisd aa2(M_PI / 3, Eigen::Vector3d::UnitY());
  Eigen::Matrix3d R1 = aa1.toRotationMatrix();
  Eigen::Matrix3d R2 = aa2.toRotationMatrix();
  double angle12 = glomap::CalcAngle(R1, R2);
  double angle21 = glomap::CalcAngle(R2, R1);
  EXPECT_NEAR(angle12, angle21, kTolerance);
}

// Test small angle rotation
TEST_F(CalcAngleTest_71, SmallAngleRotation_71) {
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  double small_angle = 0.001;  // radians
  Eigen::AngleAxisd aa(small_angle, Eigen::Vector3d::UnitZ());
  Eigen::Matrix3d R2 = aa.toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  double expected_degrees = small_angle * 180.0 / M_PI;
  EXPECT_NEAR(angle, expected_degrees, 1e-6);
}

// Test rotation around an arbitrary axis
TEST_F(CalcAngleTest_71, ArbitraryAxisRotation_71) {
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  Eigen::Vector3d axis = Eigen::Vector3d(1, 1, 1).normalized();
  double angle_rad = M_PI / 5;
  Eigen::AngleAxisd aa(angle_rad, axis);
  Eigen::Matrix3d R2 = aa.toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  double expected_degrees = angle_rad * 180.0 / M_PI;
  EXPECT_NEAR(angle, expected_degrees, kTolerance);
}

// Test that result is always non-negative
TEST_F(CalcAngleTest_71, ResultIsNonNegative_71) {
  Eigen::AngleAxisd aa1(M_PI / 3, Eigen::Vector3d::UnitX());
  Eigen::AngleAxisd aa2(-M_PI / 3, Eigen::Vector3d::UnitX());
  Eigen::Matrix3d R1 = aa1.toRotationMatrix();
  Eigen::Matrix3d R2 = aa2.toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_GE(angle, 0.0);
}

// Test that result is at most 180 degrees
TEST_F(CalcAngleTest_71, ResultAtMost180_71) {
  Eigen::AngleAxisd aa1(0.1, Eigen::Vector3d::UnitX());
  Eigen::AngleAxisd aa2(M_PI - 0.1, Eigen::Vector3d::UnitY());
  Eigen::Matrix3d R1 = aa1.toRotationMatrix();
  Eigen::Matrix3d R2 = aa2.toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_LE(angle, 180.0 + kTolerance);
  EXPECT_GE(angle, 0.0 - kTolerance);
}

// Test composition: rotating by 30 then 60 around same axis gives 90 degree difference from identity to composite
TEST_F(CalcAngleTest_71, CompositionOfRotations_71) {
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  Eigen::AngleAxisd aa_30(M_PI / 6, Eigen::Vector3d::UnitZ());
  Eigen::AngleAxisd aa_60(M_PI / 3, Eigen::Vector3d::UnitZ());
  Eigen::Matrix3d R_30 = aa_30.toRotationMatrix();
  Eigen::Matrix3d R_60 = aa_60.toRotationMatrix();
  
  // Angle between R_30 and R_60 should be 30 degrees
  double angle = glomap::CalcAngle(R_30, R_60);
  EXPECT_NEAR(angle, 30.0, kTolerance);
}

// Test with both rotations being non-identity
TEST_F(CalcAngleTest_71, BothNonIdentityRotations_71) {
  Eigen::AngleAxisd aa1(M_PI / 4, Eigen::Vector3d::UnitX());
  Eigen::AngleAxisd aa2(M_PI / 4, Eigen::Vector3d::UnitX());
  // Same rotation composed differently
  Eigen::AngleAxisd aa3(M_PI / 2, Eigen::Vector3d::UnitX());
  
  Eigen::Matrix3d R1 = aa1.toRotationMatrix();
  Eigen::Matrix3d R2 = aa3.toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_NEAR(angle, 45.0, kTolerance);
}

// Test exact 180 degrees around different axes
TEST_F(CalcAngleTest_71, OneEightyAroundY_71) {
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  Eigen::AngleAxisd aa(M_PI, Eigen::Vector3d::UnitY());
  Eigen::Matrix3d R2 = aa.toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_NEAR(angle, 180.0, kTolerance);
}

// Test exact 180 degrees around Z axis
TEST_F(CalcAngleTest_71, OneEightyAroundZ_71) {
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  Eigen::AngleAxisd aa(M_PI, Eigen::Vector3d::UnitZ());
  Eigen::Matrix3d R2 = aa.toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_NEAR(angle, 180.0, kTolerance);
}

// Test 1 degree rotation
TEST_F(CalcAngleTest_71, OneDegreeRotation_71) {
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  double one_degree_rad = M_PI / 180.0;
  Eigen::AngleAxisd aa(one_degree_rad, Eigen::Vector3d::UnitX());
  Eigen::Matrix3d R2 = aa.toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_NEAR(angle, 1.0, 1e-6);
}

// Test 179 degree rotation (near boundary)
TEST_F(CalcAngleTest_71, NearMaxAngle_71) {
  Eigen::Matrix3d R1 = Eigen::Matrix3d::Identity();
  double angle_rad = 179.0 * M_PI / 180.0;
  Eigen::AngleAxisd aa(angle_rad, Eigen::Vector3d(0, 0, 1));
  Eigen::Matrix3d R2 = aa.toRotationMatrix();
  double angle = glomap::CalcAngle(R1, R2);
  EXPECT_NEAR(angle, 179.0, 1e-5);
}
