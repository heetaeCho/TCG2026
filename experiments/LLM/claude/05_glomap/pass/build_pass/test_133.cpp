#include <gtest/gtest.h>
#include <Eigen/Core>
#include <vector>
#include "glomap/math/gravity.h"

namespace glomap {
namespace {

TEST(AverageGravityTest_133, EmptyInput_ReturnsZeroVector_133) {
  std::vector<Eigen::Vector3d> gravities;
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_DOUBLE_EQ(result(0), 0.0);
  EXPECT_DOUBLE_EQ(result(1), 0.0);
  EXPECT_DOUBLE_EQ(result(2), 0.0);
}

TEST(AverageGravityTest_133, SingleGravityVector_ReturnsSameDirection_133) {
  std::vector<Eigen::Vector3d> gravities;
  Eigen::Vector3d g(0.0, 0.0, -1.0);
  gravities.push_back(g);
  Eigen::Vector3d result = AverageGravity(gravities);
  // Result should be unit vector in same direction as input
  EXPECT_NEAR(result.norm(), 1.0, 1e-6);
  // The dot product with the original should be close to 1 (same direction)
  EXPECT_NEAR(std::abs(result.dot(g.normalized())), 1.0, 1e-6);
  // Since there's only one vector, majority check should keep direction
  EXPECT_NEAR(result.dot(g), 1.0, 1e-6);
}

TEST(AverageGravityTest_133, AllIdenticalVectors_ReturnsSameDirection_133) {
  std::vector<Eigen::Vector3d> gravities;
  Eigen::Vector3d g(0.0, -9.81, 0.0);
  for (int i = 0; i < 10; ++i) {
    gravities.push_back(g);
  }
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_NEAR(result.norm(), 1.0, 1e-6);
  Eigen::Vector3d expected = g.normalized();
  EXPECT_NEAR(result.dot(expected), 1.0, 1e-6);
}

TEST(AverageGravityTest_133, OppositeVectorsMajorityPositive_133) {
  std::vector<Eigen::Vector3d> gravities;
  // 3 vectors pointing in +z, 1 pointing in -z
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, -1.0));
  
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_NEAR(result.norm(), 1.0, 1e-6);
  // Majority is in +z direction
  EXPECT_GT(result(2), 0.0);
}

TEST(AverageGravityTest_133, OppositeVectorsMajorityNegative_133) {
  std::vector<Eigen::Vector3d> gravities;
  // 1 vector pointing in +z, 3 pointing in -z
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, -1.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, -1.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, -1.0));
  
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_NEAR(result.norm(), 1.0, 1e-6);
  // Majority is in -z direction
  EXPECT_LT(result(2), 0.0);
}

TEST(AverageGravityTest_133, SlightlyPerturbedVectors_133) {
  std::vector<Eigen::Vector3d> gravities;
  // All roughly pointing in -y direction with small perturbations
  gravities.push_back(Eigen::Vector3d(0.01, -1.0, 0.02));
  gravities.push_back(Eigen::Vector3d(-0.02, -1.0, 0.01));
  gravities.push_back(Eigen::Vector3d(0.0, -1.0, -0.01));
  gravities.push_back(Eigen::Vector3d(0.015, -1.0, 0.0));
  gravities.push_back(Eigen::Vector3d(-0.01, -1.0, -0.02));
  
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_NEAR(result.norm(), 1.0, 1e-6);
  // The dominant direction should be close to -y
  EXPECT_LT(result(1), -0.9);
}

TEST(AverageGravityTest_133, TwoVectors_133) {
  std::vector<Eigen::Vector3d> gravities;
  gravities.push_back(Eigen::Vector3d(1.0, 0.0, 0.0));
  gravities.push_back(Eigen::Vector3d(1.0, 0.0, 0.0));
  
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_NEAR(result.norm(), 1.0, 1e-6);
  EXPECT_NEAR(std::abs(result(0)), 1.0, 1e-6);
  EXPECT_NEAR(result(1), 0.0, 1e-6);
  EXPECT_NEAR(result(2), 0.0, 1e-6);
}

TEST(AverageGravityTest_133, ResultIsUnitVector_133) {
  std::vector<Eigen::Vector3d> gravities;
  gravities.push_back(Eigen::Vector3d(3.0, 4.0, 0.0));
  gravities.push_back(Eigen::Vector3d(3.0, 4.0, 0.0));
  
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_NEAR(result.norm(), 1.0, 1e-6);
}

TEST(AverageGravityTest_133, NonUnitInputVectors_133) {
  std::vector<Eigen::Vector3d> gravities;
  // Non-unit vectors all pointing roughly in the same direction
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, 5.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, 10.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, 3.0));
  
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_NEAR(result.norm(), 1.0, 1e-6);
  EXPECT_NEAR(result(2), 1.0, 1e-6);
}

TEST(AverageGravityTest_133, LargeNumberOfVectors_133) {
  std::vector<Eigen::Vector3d> gravities;
  // Large number of vectors roughly pointing in +x direction
  for (int i = 0; i < 1000; ++i) {
    double perturbation_y = (i % 2 == 0) ? 0.001 : -0.001;
    double perturbation_z = (i % 3 == 0) ? 0.001 : -0.001;
    gravities.push_back(Eigen::Vector3d(1.0, perturbation_y, perturbation_z));
  }
  
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_NEAR(result.norm(), 1.0, 1e-6);
  EXPECT_GT(result(0), 0.99);
}

TEST(AverageGravityTest_133, VectorsAlongXAxis_133) {
  std::vector<Eigen::Vector3d> gravities;
  gravities.push_back(Eigen::Vector3d(1.0, 0.0, 0.0));
  
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_NEAR(result.norm(), 1.0, 1e-6);
  EXPECT_NEAR(std::abs(result(0)), 1.0, 1e-6);
}

TEST(AverageGravityTest_133, VectorsAlongYAxis_133) {
  std::vector<Eigen::Vector3d> gravities;
  gravities.push_back(Eigen::Vector3d(0.0, 1.0, 0.0));
  
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_NEAR(result.norm(), 1.0, 1e-6);
  EXPECT_NEAR(std::abs(result(1)), 1.0, 1e-6);
}

TEST(AverageGravityTest_133, VectorsAlongZAxis_133) {
  std::vector<Eigen::Vector3d> gravities;
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
  
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_NEAR(result.norm(), 1.0, 1e-6);
  EXPECT_NEAR(std::abs(result(2)), 1.0, 1e-6);
}

TEST(AverageGravityTest_133, MajorityFlipTest_133) {
  // Test the sign flip logic more carefully
  // All 5 vectors point in -x, result should be -x
  std::vector<Eigen::Vector3d> gravities;
  for (int i = 0; i < 5; ++i) {
    gravities.push_back(Eigen::Vector3d(-1.0, 0.0, 0.0));
  }
  
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_NEAR(result.norm(), 1.0, 1e-6);
  EXPECT_NEAR(result(0), -1.0, 1e-6);
}

TEST(AverageGravityTest_133, DiagonalVector_133) {
  std::vector<Eigen::Vector3d> gravities;
  Eigen::Vector3d g(1.0, 1.0, 1.0);
  for (int i = 0; i < 5; ++i) {
    gravities.push_back(g);
  }
  
  Eigen::Vector3d result = AverageGravity(gravities);
  EXPECT_NEAR(result.norm(), 1.0, 1e-6);
  Eigen::Vector3d expected = g.normalized();
  EXPECT_NEAR(result.dot(expected), 1.0, 1e-6);
}

TEST(AverageGravityTest_133, ExactlyHalfOpposite_EvenCount_133) {
  // 2 positive, 2 negative along z - edge case for majority
  std::vector<Eigen::Vector3d> gravities;
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, -1.0));
  gravities.push_back(Eigen::Vector3d(0.0, 0.0, -1.0));
  
  Eigen::Vector3d result = AverageGravity(gravities);
  // Result should still be a unit vector along z axis
  EXPECT_NEAR(result.norm(), 1.0, 1e-6);
  EXPECT_NEAR(std::abs(result(2)), 1.0, 1e-6);
}

}  // namespace
}  // namespace glomap
