#include <gtest/gtest.h>
#include <Eigen/Core>
#include <cmath>

namespace glomap {
double CalcAngle(const Eigen::Vector3d& gravity1, const Eigen::Vector3d& gravity2);
}

class CalcAngleTest_134 : public ::testing::Test {
 protected:
};

// Test that two identical vectors have zero angle between them
TEST_F(CalcAngleTest_134, IdenticalVectors_ReturnsZero_134) {
  Eigen::Vector3d v(1.0, 0.0, 0.0);
  double angle = glomap::CalcAngle(v, v);
  EXPECT_NEAR(angle, 0.0, 1e-10);
}

// Test that two opposite vectors have 180 degree angle
TEST_F(CalcAngleTest_134, OppositeVectors_Returns180_134) {
  Eigen::Vector3d v1(1.0, 0.0, 0.0);
  Eigen::Vector3d v2(-1.0, 0.0, 0.0);
  double angle = glomap::CalcAngle(v1, v2);
  EXPECT_NEAR(angle, 180.0, 1e-10);
}

// Test that two perpendicular vectors have 90 degree angle
TEST_F(CalcAngleTest_134, PerpendicularVectors_Returns90_134) {
  Eigen::Vector3d v1(1.0, 0.0, 0.0);
  Eigen::Vector3d v2(0.0, 1.0, 0.0);
  double angle = glomap::CalcAngle(v1, v2);
  EXPECT_NEAR(angle, 90.0, 1e-10);
}

// Test 45 degree angle
TEST_F(CalcAngleTest_134, FortyFiveDegreeAngle_134) {
  Eigen::Vector3d v1(1.0, 0.0, 0.0);
  Eigen::Vector3d v2(1.0, 1.0, 0.0);
  double angle = glomap::CalcAngle(v1, v2);
  EXPECT_NEAR(angle, 45.0, 1e-10);
}

// Test with non-unit vectors (different magnitudes)
TEST_F(CalcAngleTest_134, NonUnitVectors_SameDirection_ReturnsZero_134) {
  Eigen::Vector3d v1(3.0, 0.0, 0.0);
  Eigen::Vector3d v2(5.0, 0.0, 0.0);
  double angle = glomap::CalcAngle(v1, v2);
  EXPECT_NEAR(angle, 0.0, 1e-10);
}

// Test with non-unit vectors at 90 degrees
TEST_F(CalcAngleTest_134, NonUnitVectors_Perpendicular_Returns90_134) {
  Eigen::Vector3d v1(3.0, 0.0, 0.0);
  Eigen::Vector3d v2(0.0, 7.0, 0.0);
  double angle = glomap::CalcAngle(v1, v2);
  EXPECT_NEAR(angle, 90.0, 1e-10);
}

// Test commutativity: CalcAngle(a, b) == CalcAngle(b, a)
TEST_F(CalcAngleTest_134, Commutativity_134) {
  Eigen::Vector3d v1(1.0, 2.0, 3.0);
  Eigen::Vector3d v2(4.0, 5.0, 6.0);
  double angle1 = glomap::CalcAngle(v1, v2);
  double angle2 = glomap::CalcAngle(v2, v1);
  EXPECT_NEAR(angle1, angle2, 1e-10);
}

// Test with 3D vectors at known angle (60 degrees)
TEST_F(CalcAngleTest_134, SixtyDegreeAngle_134) {
  Eigen::Vector3d v1(1.0, 0.0, 0.0);
  // cos(60°) = 0.5, so v2 = (0.5, sqrt(3)/2, 0) has 60° with v1
  Eigen::Vector3d v2(0.5, std::sqrt(3.0) / 2.0, 0.0);
  double angle = glomap::CalcAngle(v1, v2);
  EXPECT_NEAR(angle, 60.0, 1e-10);
}

// Test with negative component vectors
TEST_F(CalcAngleTest_134, NegativeComponents_134) {
  Eigen::Vector3d v1(-1.0, -1.0, 0.0);
  Eigen::Vector3d v2(-1.0, 1.0, 0.0);
  double angle = glomap::CalcAngle(v1, v2);
  EXPECT_NEAR(angle, 90.0, 1e-10);
}

// Test along all three axes perpendicular
TEST_F(CalcAngleTest_134, ZAxisPerpendicular_134) {
  Eigen::Vector3d v1(0.0, 0.0, 1.0);
  Eigen::Vector3d v2(1.0, 0.0, 0.0);
  double angle = glomap::CalcAngle(v1, v2);
  EXPECT_NEAR(angle, 90.0, 1e-10);
}

// Test with very small vectors (should still work due to normalization)
TEST_F(CalcAngleTest_134, VerySmallVectors_134) {
  Eigen::Vector3d v1(1e-15, 0.0, 0.0);
  Eigen::Vector3d v2(0.0, 1e-15, 0.0);
  double angle = glomap::CalcAngle(v1, v2);
  EXPECT_NEAR(angle, 90.0, 1e-6);
}

// Test with very large vectors
TEST_F(CalcAngleTest_134, VeryLargeVectors_134) {
  Eigen::Vector3d v1(1e15, 0.0, 0.0);
  Eigen::Vector3d v2(0.0, 1e15, 0.0);
  double angle = glomap::CalcAngle(v1, v2);
  EXPECT_NEAR(angle, 90.0, 1e-6);
}

// Test 120 degree angle
TEST_F(CalcAngleTest_134, OneTwentyDegreeAngle_134) {
  Eigen::Vector3d v1(1.0, 0.0, 0.0);
  // cos(120°) = -0.5, so v2 = (-0.5, sqrt(3)/2, 0)
  Eigen::Vector3d v2(-0.5, std::sqrt(3.0) / 2.0, 0.0);
  double angle = glomap::CalcAngle(v1, v2);
  EXPECT_NEAR(angle, 120.0, 1e-10);
}

// Test that result is always in [0, 180]
TEST_F(CalcAngleTest_134, ResultInValidRange_134) {
  Eigen::Vector3d v1(1.0, 2.0, -3.0);
  Eigen::Vector3d v2(-4.0, 5.0, 6.0);
  double angle = glomap::CalcAngle(v1, v2);
  EXPECT_GE(angle, 0.0);
  EXPECT_LE(angle, 180.0);
}

// Test with unit vectors along diagonal
TEST_F(CalcAngleTest_134, DiagonalVectors_134) {
  Eigen::Vector3d v1(1.0, 1.0, 1.0);
  Eigen::Vector3d v2(-1.0, -1.0, -1.0);
  double angle = glomap::CalcAngle(v1, v2);
  EXPECT_NEAR(angle, 180.0, 1e-10);
}

// Test same direction different magnitudes
TEST_F(CalcAngleTest_134, SameDirectionDifferentMagnitudes_134) {
  Eigen::Vector3d v1(1.0, 1.0, 1.0);
  Eigen::Vector3d v2(100.0, 100.0, 100.0);
  double angle = glomap::CalcAngle(v1, v2);
  EXPECT_NEAR(angle, 0.0, 1e-10);
}

// Test angle between z-axis and diagonal in 3D
TEST_F(CalcAngleTest_134, ZAxisAndDiagonal3D_134) {
  Eigen::Vector3d v1(0.0, 0.0, 1.0);
  Eigen::Vector3d v2(1.0, 1.0, 1.0);
  // cos(theta) = 1/sqrt(3), theta = acos(1/sqrt(3)) in degrees
  double expected = std::acos(1.0 / std::sqrt(3.0)) * 180.0 / M_PI;
  double angle = glomap::CalcAngle(v1, v2);
  EXPECT_NEAR(angle, expected, 1e-10);
}
