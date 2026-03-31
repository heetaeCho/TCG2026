#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>

namespace glomap {
Eigen::Matrix3d GetAlignRot(const Eigen::Vector3d& gravity);
}

class GravityTest_131 : public ::testing::Test {
 protected:
  static constexpr double kTolerance = 1e-10;
};

// Test that the result is a valid rotation matrix (orthogonal with determinant +1)
// for a simple downward gravity vector
TEST_F(GravityTest_131, DownwardGravityProducesRotationMatrix_131) {
  Eigen::Vector3d gravity(0.0, -9.81, 0.0);
  Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

  // Check orthogonality: R^T * R should be identity
  Eigen::Matrix3d identity = R.transpose() * R;
  EXPECT_NEAR((identity - Eigen::Matrix3d::Identity()).norm(), 0.0, kTolerance);

  // Check determinant is +1
  EXPECT_NEAR(R.determinant(), 1.0, kTolerance);
}

// Test that column 1 of R equals the normalized gravity vector
TEST_F(GravityTest_131, Column1IsNormalizedGravity_131) {
  Eigen::Vector3d gravity(1.0, 2.0, 3.0);
  Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

  Eigen::Vector3d expected_col1 = gravity.normalized();
  EXPECT_NEAR((R.col(1) - expected_col1).norm(), 0.0, kTolerance);
}

// Test with unit vector along x-axis
TEST_F(GravityTest_131, UnitXGravity_131) {
  Eigen::Vector3d gravity(1.0, 0.0, 0.0);
  Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

  // col(1) should be (1, 0, 0)
  EXPECT_NEAR(R.col(1)(0), 1.0, kTolerance);
  EXPECT_NEAR(R.col(1)(1), 0.0, kTolerance);
  EXPECT_NEAR(R.col(1)(2), 0.0, kTolerance);

  // Determinant should be +1
  EXPECT_NEAR(R.determinant(), 1.0, kTolerance);

  // Orthogonality
  Eigen::Matrix3d identity = R.transpose() * R;
  EXPECT_NEAR((identity - Eigen::Matrix3d::Identity()).norm(), 0.0, kTolerance);
}

// Test with unit vector along y-axis
TEST_F(GravityTest_131, UnitYGravity_131) {
  Eigen::Vector3d gravity(0.0, 1.0, 0.0);
  Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

  EXPECT_NEAR(R.col(1)(0), 0.0, kTolerance);
  EXPECT_NEAR(R.col(1)(1), 1.0, kTolerance);
  EXPECT_NEAR(R.col(1)(2), 0.0, kTolerance);

  EXPECT_NEAR(R.determinant(), 1.0, kTolerance);

  Eigen::Matrix3d identity = R.transpose() * R;
  EXPECT_NEAR((identity - Eigen::Matrix3d::Identity()).norm(), 0.0, kTolerance);
}

// Test with unit vector along z-axis
TEST_F(GravityTest_131, UnitZGravity_131) {
  Eigen::Vector3d gravity(0.0, 0.0, 1.0);
  Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

  EXPECT_NEAR(R.col(1)(0), 0.0, kTolerance);
  EXPECT_NEAR(R.col(1)(1), 0.0, kTolerance);
  EXPECT_NEAR(R.col(1)(2), 1.0, kTolerance);

  EXPECT_NEAR(R.determinant(), 1.0, kTolerance);

  Eigen::Matrix3d identity = R.transpose() * R;
  EXPECT_NEAR((identity - Eigen::Matrix3d::Identity()).norm(), 0.0, kTolerance);
}

// Test with negative gravity vector
TEST_F(GravityTest_131, NegativeGravityVector_131) {
  Eigen::Vector3d gravity(-1.0, -2.0, -3.0);
  Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

  Eigen::Vector3d expected_col1 = gravity.normalized();
  EXPECT_NEAR((R.col(1) - expected_col1).norm(), 0.0, kTolerance);

  EXPECT_NEAR(R.determinant(), 1.0, kTolerance);

  Eigen::Matrix3d identity = R.transpose() * R;
  EXPECT_NEAR((identity - Eigen::Matrix3d::Identity()).norm(), 0.0, kTolerance);
}

// Test with a large magnitude gravity vector (should still normalize)
TEST_F(GravityTest_131, LargeMagnitudeGravity_131) {
  Eigen::Vector3d gravity(1000.0, 2000.0, 3000.0);
  Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

  Eigen::Vector3d expected_col1 = gravity.normalized();
  EXPECT_NEAR((R.col(1) - expected_col1).norm(), 0.0, kTolerance);

  EXPECT_NEAR(R.determinant(), 1.0, kTolerance);

  Eigen::Matrix3d identity = R.transpose() * R;
  EXPECT_NEAR((identity - Eigen::Matrix3d::Identity()).norm(), 0.0, kTolerance);
}

// Test with a small magnitude gravity vector
TEST_F(GravityTest_131, SmallMagnitudeGravity_131) {
  Eigen::Vector3d gravity(1e-8, 1e-8, 1e-8);
  Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

  Eigen::Vector3d expected_col1 = gravity.normalized();
  EXPECT_NEAR((R.col(1) - expected_col1).norm(), 0.0, kTolerance);

  EXPECT_NEAR(R.determinant(), 1.0, kTolerance);
}

// Test columns are mutually orthogonal
TEST_F(GravityTest_131, ColumnsAreMutuallyOrthogonal_131) {
  Eigen::Vector3d gravity(3.0, 4.0, 5.0);
  Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

  EXPECT_NEAR(R.col(0).dot(R.col(1)), 0.0, kTolerance);
  EXPECT_NEAR(R.col(0).dot(R.col(2)), 0.0, kTolerance);
  EXPECT_NEAR(R.col(1).dot(R.col(2)), 0.0, kTolerance);
}

// Test that each column has unit norm
TEST_F(GravityTest_131, ColumnsHaveUnitNorm_131) {
  Eigen::Vector3d gravity(7.0, -3.0, 11.0);
  Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

  EXPECT_NEAR(R.col(0).norm(), 1.0, kTolerance);
  EXPECT_NEAR(R.col(1).norm(), 1.0, kTolerance);
  EXPECT_NEAR(R.col(2).norm(), 1.0, kTolerance);
}

// Test with a negative unit vector along x-axis
TEST_F(GravityTest_131, NegativeUnitXGravity_131) {
  Eigen::Vector3d gravity(-1.0, 0.0, 0.0);
  Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

  EXPECT_NEAR(R.col(1)(0), -1.0, kTolerance);
  EXPECT_NEAR(R.col(1)(1), 0.0, kTolerance);
  EXPECT_NEAR(R.col(1)(2), 0.0, kTolerance);

  EXPECT_NEAR(R.determinant(), 1.0, kTolerance);

  Eigen::Matrix3d identity = R.transpose() * R;
  EXPECT_NEAR((identity - Eigen::Matrix3d::Identity()).norm(), 0.0, kTolerance);
}

// Test with a diagonal gravity vector
TEST_F(GravityTest_131, DiagonalGravityVector_131) {
  Eigen::Vector3d gravity(1.0, 1.0, 1.0);
  Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

  Eigen::Vector3d expected_col1 = gravity.normalized();
  EXPECT_NEAR((R.col(1) - expected_col1).norm(), 0.0, kTolerance);

  EXPECT_NEAR(R.determinant(), 1.0, kTolerance);

  Eigen::Matrix3d identity = R.transpose() * R;
  EXPECT_NEAR((identity - Eigen::Matrix3d::Identity()).norm(), 0.0, kTolerance);
}

// Test determinant is always positive regardless of input direction
TEST_F(GravityTest_131, DeterminantAlwaysPositive_131) {
  std::vector<Eigen::Vector3d> test_vectors = {
    {1, 0, 0}, {0, 1, 0}, {0, 0, 1},
    {-1, 0, 0}, {0, -1, 0}, {0, 0, -1},
    {1, 1, 0}, {0, 1, 1}, {1, 0, 1},
    {-1, -1, -1}, {2, -3, 5}, {-7, 11, -13}
  };

  for (const auto& g : test_vectors) {
    Eigen::Matrix3d R = glomap::GetAlignRot(g);
    EXPECT_NEAR(R.determinant(), 1.0, kTolerance)
      << "Failed for gravity = (" << g.transpose() << ")";
  }
}

// Test that the result forms a proper right-handed coordinate system
TEST_F(GravityTest_131, RightHandedCoordinateSystem_131) {
  Eigen::Vector3d gravity(2.0, -5.0, 3.0);
  Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

  // For a right-handed system: col(0) x col(1) = col(2)
  Eigen::Vector3d cross = R.col(0).cross(R.col(1));
  EXPECT_NEAR((cross - R.col(2)).norm(), 0.0, kTolerance);
}

// Test with gravity vector having only two non-zero components
TEST_F(GravityTest_131, TwoComponentGravity_131) {
  Eigen::Vector3d gravity(3.0, 4.0, 0.0);
  Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

  Eigen::Vector3d expected_col1 = gravity.normalized();
  EXPECT_NEAR((R.col(1) - expected_col1).norm(), 0.0, kTolerance);

  EXPECT_NEAR(R.determinant(), 1.0, kTolerance);

  Eigen::Matrix3d identity = R.transpose() * R;
  EXPECT_NEAR((identity - Eigen::Matrix3d::Identity()).norm(), 0.0, kTolerance);
}
