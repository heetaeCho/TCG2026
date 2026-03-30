#include <gtest/gtest.h>
#include <Eigen/Core>
#include <vector>

namespace glomap {
// Forward declaration based on the provided implementation.
Eigen::Vector3d AverageGravity(const std::vector<Eigen::Vector3d>& gravities);
}  // namespace glomap

// Test suite for AverageGravity (TEST_ID = 63)
class AverageGravityTest_63 : public ::testing::Test {
 protected:
  // Helper epsilon for floating point comparisons
  static constexpr double kEps;
};

constexpr double AverageGravityTest_63::kEps = 1e-9;

// -----------------------------------------------------------------------------
// Boundary / error-like case: empty input
// -----------------------------------------------------------------------------
TEST_F(AverageGravityTest_63, ReturnsZeroForEmptyInput_63) {
  std::vector<Eigen::Vector3d> gravities;

  Eigen::Vector3d result = glomap::AverageGravity(gravities);

  // For an empty set, the function is expected to return the zero vector.
  EXPECT_TRUE(result.isApprox(Eigen::Vector3d::Zero(), kEps));
}

// -----------------------------------------------------------------------------
// Normal case: all input gravities are identical and aligned.
// We expect a unit vector in the same direction as the inputs.
// -----------------------------------------------------------------------------
TEST_F(AverageGravityTest_63, IdenticalGravityVectorsReturnSameDirection_63) {
  // Use a non-unit "gravity-like" vector to ensure normalization is handled.
  Eigen::Vector3d g(0.0, 0.0, -9.8);
  std::vector<Eigen::Vector3d> gravities(5, g);  // five identical vectors

  Eigen::Vector3d result = glomap::AverageGravity(gravities);

  // Expected direction: along negative z, unit length.
  Eigen::Vector3d expected = g.normalized();

  EXPECT_NEAR(result.norm(), 1.0, kEps);
  EXPECT_TRUE(result.isApprox(expected, 1e-6));  // allow slightly looser epsilon
}

// -----------------------------------------------------------------------------
// Boundary / sign-selection behavior:
// If most vectors point in one direction and a minority in the opposite
// direction, the result should align with the majority.
// -----------------------------------------------------------------------------
TEST_F(AverageGravityTest_63, MajorityDirectionDeterminesSign_63) {
  Eigen::Vector3d down(0.0, 0.0, -1.0);
  Eigen::Vector3d up(0.0, 0.0, 1.0);

  std::vector<Eigen::Vector3d> gravities;
  gravities.push_back(down);
  gravities.push_back(down);
  gravities.push_back(up);  // minority in opposite direction

  Eigen::Vector3d result = glomap::AverageGravity(gravities);

  // Result should align with "down" (negative z).
  EXPECT_NEAR(result.norm(), 1.0, kEps);
  // Dot product > 0 means same general direction.
  EXPECT_GT(result.dot(down), 0.0);
  EXPECT_LT(result.dot(up), 0.0);
}

// -----------------------------------------------------------------------------
// Normal case with small noise around a dominant direction:
// Vectors clustered around a direction should still yield a result close
// to that dominant direction.
// -----------------------------------------------------------------------------
TEST_F(AverageGravityTest_63, NoisyClusterStillAlignsWithDominantDirection_63) {
  Eigen::Vector3d base(0.0, 0.0, -1.0);

  std::vector<Eigen::Vector3d> gravities;
  gravities.push_back(base);
  gravities.push_back((base + Eigen::Vector3d(0.05, 0.0, 0.0)).normalized());
  gravities.push_back((base + Eigen::Vector3d(0.0, 0.05, 0.0)).normalized());
  gravities.push_back((base + Eigen::Vector3d(-0.03, -0.02, 0.0)).normalized());

  Eigen::Vector3d result = glomap::AverageGravity(gravities);

  // Result should be close to the base direction.
  EXPECT_NEAR(result.norm(), 1.0, 1e-6);
  double cos_angle = result.normalized().dot(base);
  // cos(angle) close to 1 => angle small. Here require ≥ cos(10°) ≈ 0.9848.
  EXPECT_GT(cos_angle, 0.97);
}
