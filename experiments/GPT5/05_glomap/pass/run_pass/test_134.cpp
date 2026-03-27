// File: calc_angle_test_134.cc
//
// TEST_ID: 134
//
// Unit tests for glomap::CalcAngle using Google Test.
// The implementation is treated as a black box; tests rely only on
// geometric expectations for specific vector configurations.

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <cmath>

namespace glomap {
// Forward declaration; the real implementation is in gravity.cc.
double CalcAngle(const Eigen::Vector3d& gravity1, const Eigen::Vector3d& gravity2);
}  // namespace glomap

class CalcAngleTest_134 : public ::testing::Test {};

// Same direction (including positive scalar multiples) should give ~0 degrees.
TEST_F(CalcAngleTest_134, SameDirectionReturnsZero_134) {
  Eigen::Vector3d g1(1.0, 0.0, 0.0);
  Eigen::Vector3d g2(2.0, 0.0, 0.0);  // Same direction, different magnitude

  double angle = glomap::CalcAngle(g1, g2);

  EXPECT_NEAR(angle, 0.0, 1e-9);
}

// Opposite direction vectors should yield ~180 degrees.
TEST_F(CalcAngleTest_134, OppositeDirectionReturns180_134) {
  Eigen::Vector3d g1(1.0, 0.0, 0.0);
  Eigen::Vector3d g2(-1.0, 0.0, 0.0);  // Exactly opposite

  double angle = glomap::CalcAngle(g1, g2);

  EXPECT_NEAR(angle, 180.0, 1e-9);
}

// Orthogonal vectors should yield ~90 degrees.
TEST_F(CalcAngleTest_134, OrthogonalVectorsReturn90_134) {
  Eigen::Vector3d g1(1.0, 0.0, 0.0);
  Eigen::Vector3d g2(0.0, 1.0, 0.0);  // Orthogonal

  double angle = glomap::CalcAngle(g1, g2);

  EXPECT_NEAR(angle, 90.0, 1e-9);
}

// A non-trivial angle (e.g., 60 degrees) with non-axis-aligned vector.
TEST_F(CalcAngleTest_134, NonTrivialAngleReturnsExpectedValue_134) {
  // Vector along x-axis.
  Eigen::Vector3d g1(1.0, 0.0, 0.0);

  // Vector rotated 60 degrees from x-axis in the xy-plane:
  // (cos 60°, sin 60°, 0) = (0.5, sqrt(3)/2, 0).
  Eigen::Vector3d g2(0.5, std::sqrt(3.0) / 2.0, 0.0);

  double angle = glomap::CalcAngle(g1, g2);

  EXPECT_NEAR(angle, 60.0, 1e-9);
}

// The function should be symmetric: angle(a, b) == angle(b, a).
TEST_F(CalcAngleTest_134, SymmetryBetweenArguments_134) {
  Eigen::Vector3d g1(1.0, 2.0, 3.0);
  Eigen::Vector3d g2(-4.0, 5.0, -6.0);

  double angle1 = glomap::CalcAngle(g1, g2);
  double angle2 = glomap::CalcAngle(g2, g1);

  EXPECT_NEAR(angle1, angle2, 1e-9);
}

// Very close vectors should result in a very small angle (near 0).
TEST_F(CalcAngleTest_134, NearlyParallelVectorsReturnSmallAngle_134) {
  Eigen::Vector3d g1(1.0, 1.0, 1.0);
  Eigen::Vector3d g2(1.0 + 1e-9, 1.0, 1.0);  // Slightly perturbed

  double angle = glomap::CalcAngle(g1, g2);

  // We don't know the exact value, but it should be very small and non-negative.
  EXPECT_GE(angle, 0.0);
  EXPECT_LT(angle, 1e-3);  // < 0.001 degrees
}

// Exceptional case: if one vector is zero, the angle is mathematically undefined.
// We at least verify that the function does not produce a finite angle.
TEST_F(CalcAngleTest_134, ZeroVectorProducesNonFiniteResult_134) {
  Eigen::Vector3d zero(0.0, 0.0, 0.0);
  Eigen::Vector3d nonzero(1.0, 0.0, 0.0);

  double angle1 = glomap::CalcAngle(zero, nonzero);
  double angle2 = glomap::CalcAngle(nonzero, zero);

  // Behavior for this invalid input should not look like a valid finite angle.
  EXPECT_TRUE(std::isnan(angle1) || std::isinf(angle1));
  EXPECT_TRUE(std::isnan(angle2) || std::isinf(angle2));
}
