#include <gtest/gtest.h>
#include <Eigen/Core>
#include <vector>
#include "glomap/math/gravity.h"

namespace glomap {
namespace {

class AverageGravityTest_63 : public ::testing::Test {
 protected:
  static constexpr double kTolerance = 1e-6;
};

// Test that an empty vector returns zero vector and prints error
TEST_F(AverageGravityTest_63, EmptyInput_ReturnsZeroVector_63) {
  std::vector<Eigen::Vector3d> gravities;
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_DOUBLE_EQ(result(0), 0.0);
  EXPECT_DOUBLE_EQ(result(1), 0.0);
  EXPECT_DOUBLE_EQ(result(2), 0.0);
}

// Test with a single gravity vector
TEST_F(AverageGravityTest_63, SingleVector_ReturnsSameDirection_63) {
  std::vector<Eigen::Vector3d> gravities;
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, -9.81));
  Eigen::Vector3d result = AverageGravity(gravities);
  // The result should be a unit vector in the same direction
  Eigen::Vector3d expected = Eigen::Vector3d(0.0, 0.0, -9.81).normalized();
  // Could be +/- direction but sign correction should match
  EXPECT_NEAR(std::abs(result.dot(expected)), 1.0, kTolerance);
}

// Test with multiple identical vectors
TEST_F(AverageGravityTest_63, IdenticalVectors_ReturnsSameDirection_63) {
  std::vector<Eigen::Vector3d> gravities;
  Eigen::Vector3d g(0.0, -1.0, 0.0);
  for (int i = 0; i < 10; ++i) {
    gravities.push_back(g);
  }
  Eigen::Vector3d result = AverageGravity(gravities);
  Eigen::Vector3d expected = g.normalized();
  EXPECT_NEAR(std::abs(result.dot(expected)), 1.0, kTolerance);
  // Sign should match since majority are in same direction
  EXPECT_NEAR(result.dot(expected), 1.0, kTolerance);
}

// Test with two opposing vectors - majority determines sign
TEST_F(AverageGravityTest_63, TwoOpposingVectors_63) {
  std::vector<Eigen::Vector3d> gravities;
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, -1.0));
  Eigen::Vector3d result = AverageGravity(gravities);
  // Both directions equally represented, result should be unit along z
  EXPECT_NEAR(std::abs(result(2)), 1.0, kTolerance);
  EXPECT_NEAR(std::abs(result(0)), 0.0, kTolerance);
  EXPECT_NEAR(std::abs(result(1)), 0.0, kTolerance);
}

// Test with majority negative direction - sign should flip
TEST_F(AverageGravityTest_63, MajorityNegative_FlipsSign_63) {
  std::vector<Eigen::Vector3d> gravities;
  // 3 vectors pointing in -z, 1 in +z
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, -1.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, -1.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, -1.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
  Eigen::Vector3d result = AverageGravity(gravities);
  // Majority points in -z, so result should point in -z
  EXPECT_NEAR(result(2), -1.0, kTolerance);
  EXPECT_NEAR(result(0), 0.0, kTolerance);
  EXPECT_NEAR(result(1), 0.0, kTolerance);
}

// Test result is a unit vector
TEST_F(AverageGravityTest_63, ResultIsUnitVector_63) {
  std::vector<Eigen::Vector3d> gravities;
  gravities.push_back(Eigen::Vector3d(1.0, 2.0, 3.0));
  gravities.push_back(Eigen::Vector3d(1.1, 2.1, 2.9));
  gravities.push_back(Eigen::Vector3d(0.9, 1.9, 3.1));
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_NEAR(result.norm(), 1.0, kTolerance);
}

// Test with vectors along different axes but dominant direction
TEST_F(AverageGravityTest_63, DominantAxis_63) {
  std::vector<Eigen::Vector3d> gravities;
  // Strong signal along x-axis
  gravities.push_back(Eigen::Vector3d(10.0, 0.1, 0.1));
  gravities.push_back(Eigen::Vector3d(10.0, -0.1, 0.2));
  gravities.push_back(Eigen::Vector3d(10.0, 0.2, -0.1));
  Eigen::Vector3d result = AverageGravity(gravities);
  // Should be predominantly along x-axis
  EXPECT_GT(std::abs(result(0)), 0.9);
  EXPECT_NEAR(result.norm(), 1.0, kTolerance);
}

// Test with vectors slightly perturbed from a common direction
TEST_F(AverageGravityTest_63, SlightlyPerturbedVectors_63) {
  std::vector<Eigen::Vector3d> gravities;
  Eigen::Vector3d base(0.0, -9.81, 0.0);
  for (int i = 0; i < 100; ++i) {
    Eigen::Vector3d noise(0.01 * (i % 10 - 5), 0.0, 0.01 * (i % 7 - 3));
    gravities.push_back(base + noise);
  }
  Eigen::Vector3d result = AverageGravity(gravities);
  Eigen::Vector3d expected = base.normalized();
  EXPECT_NEAR(result.dot(expected), 1.0, 0.01);
}

// Test with a single unit vector along x
TEST_F(AverageGravityTest_63, SingleUnitVectorX_63) {
  std::vector<Eigen::Vector3d> gravities;
  gravities.push_back(Eigen::Vector3d(1.0, 0.0, 0.0));
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_NEAR(std::abs(result(0)), 1.0, kTolerance);
  EXPECT_NEAR(result(1), 0.0, kTolerance);
  EXPECT_NEAR(result(2), 0.0, kTolerance);
}

// Test sign correction: majority positive
TEST_F(AverageGravityTest_63, MajorityPositive_KeepsSign_63) {
  std::vector<Eigen::Vector3d> gravities;
  // 3 vectors pointing in +z, 1 in -z
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, -1.0));
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_NEAR(result(2), 1.0, kTolerance);
}

// Test with large number of vectors
TEST_F(AverageGravityTest_63, LargeNumberOfVectors_63) {
  std::vector<Eigen::Vector3d> gravities;
  for (int i = 0; i < 10000; ++i) {
    gravities.push_back(Eigen::Vector3d(0.0, 0.0, -9.81));
  }
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_NEAR(result(0), 0.0, kTolerance);
  EXPECT_NEAR(result(1), 0.0, kTolerance);
  EXPECT_NEAR(result(2), -1.0, kTolerance);
}

// Test with scaled vectors (different magnitudes, same direction)
TEST_F(AverageGravityTest_63, DifferentMagnitudesSameDirection_63) {
  std::vector<Eigen::Vector3d> gravities;
  gravities.push_back(Eigen::Vector3d(1.0, 0.0, 0.0));
  gravities.push_back(Eigen::Vector3d(100.0, 0.0, 0.0));
  gravities.push_back(Eigen::Vector3d(0.01, 0.0, 0.0));
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_NEAR(std::abs(result(0)), 1.0, kTolerance);
  EXPECT_NEAR(result(1), 0.0, kTolerance);
  EXPECT_NEAR(result(2), 0.0, kTolerance);
}

// Test with three orthogonal vectors, one dominant
TEST_F(AverageGravityTest_63, ThreeOrthogonalOneDominant_63) {
  std::vector<Eigen::Vector3d> gravities;
  gravities.push_back(Eigen::Vector3d(10.0, 0.0, 0.0));
  gravities.push_back(Eigen::Vector3d(0.0, 1.0, 0.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
  Eigen::Vector3d result = AverageGravity(gravities);
  // Dominant eigenvalue should be along x
  EXPECT_GT(std::abs(result(0)), 0.9);
  EXPECT_NEAR(result.norm(), 1.0, kTolerance);
}

}  // namespace
}  // namespace glomap
