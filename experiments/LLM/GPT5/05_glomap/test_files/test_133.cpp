// File: gravity_test_133.cc

#include <gtest/gtest.h>
#include <Eigen/Dense>
#include <vector>
#include <cmath>

// Forward declaration of the function under test.
// We treat the implementation as a black box.
namespace glomap {
Eigen::Vector3d AverageGravity(const std::vector<Eigen::Vector3d>& gravities);
}

// Test fixture (empty for now, but ready for future extensions)
class AverageGravityTest_133 : public ::testing::Test {};

// Helper to compute cosine of angle between two vectors.
static double CosineBetween(const Eigen::Vector3d& a, const Eigen::Vector3d& b) {
  const double norm_a = a.norm();
  const double norm_b = b.norm();
  if (norm_a == 0.0 || norm_b == 0.0) {
    return 0.0;
  }
  return a.dot(b) / (norm_a * norm_b);
}

//------------------------------------------------------------------------------
// Empty input behavior
//------------------------------------------------------------------------------
TEST_F(AverageGravityTest_133, EmptyInputReturnsZeroVector_133) {
  std::vector<Eigen::Vector3d> gravities;  // empty

  Eigen::Vector3d result = glomap::AverageGravity(gravities);

  EXPECT_DOUBLE_EQ(result.x(), 0.0);
  EXPECT_DOUBLE_EQ(result.y(), 0.0);
  EXPECT_DOUBLE_EQ(result.z(), 0.0);
}

//------------------------------------------------------------------------------
// Single vector: direction should match the input gravity direction
//------------------------------------------------------------------------------
TEST_F(AverageGravityTest_133, SingleGravityDirectionMatchesInput_133) {
  // A typical gravity vector pointing roughly along -Z
  Eigen::Vector3d g(0.0, 0.0, -9.81);
  std::vector<Eigen::Vector3d> gravities = {g};

  Eigen::Vector3d result = glomap::AverageGravity(gravities);

  Eigen::Vector3d expected_dir(0.0, 0.0, -1.0);
  double cos_theta = CosineBetween(result, expected_dir);

  // Result should be almost perfectly aligned with -Z.
  EXPECT_NEAR(cos_theta, 1.0, 1e-6);
}

//------------------------------------------------------------------------------
// Multiple similar gravity vectors: direction should be close to their mean
//------------------------------------------------------------------------------
TEST_F(AverageGravityTest_133, ConsistentGravitiesProduceStableDirection_133) {
  std::vector<Eigen::Vector3d> gravities;
  gravities.emplace_back(0.0, 0.0, -9.80);
  gravities.emplace_back(0.1, 0.0, -9.75);   // slight tilt
  gravities.emplace_back(-0.1, 0.0, -9.85);  // slight tilt the other way

  Eigen::Vector3d result = glomap::AverageGravity(gravities);

  Eigen::Vector3d expected_dir(0.0, 0.0, -1.0);
  double cos_theta = CosineBetween(result, expected_dir);

  // Result should still point very close to -Z.
  EXPECT_NEAR(cos_theta, 1.0, 1e-2);  // allow small deviation due to tilts
}

//------------------------------------------------------------------------------
// Mixture of opposite vectors: result should align with majority direction
//------------------------------------------------------------------------------
TEST_F(AverageGravityTest_133, MajorityDirectionIsPreservedWithOppositeSamples_133) {
  // Two vectors pointing down, one up: majority is along -Z.
  Eigen::Vector3d down1(0.0, 0.0, -9.81);
  Eigen::Vector3d down2(0.0, 0.0, -9.70);
  Eigen::Vector3d up(0.0, 0.0, 9.81);

  std::vector<Eigen::Vector3d> gravities = {down1, down2, up};

  Eigen::Vector3d result = glomap::AverageGravity(gravities);

  Eigen::Vector3d expected_dir(0.0, 0.0, -1.0);
  double cos_theta = CosineBetween(result, expected_dir);

  // The returned direction should agree with the majority (-Z).
  EXPECT_NEAR(cos_theta, 1.0, 1e-2);
}
