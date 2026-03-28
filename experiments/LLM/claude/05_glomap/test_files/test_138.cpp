#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>

namespace glomap {
double SampsonError(const Eigen::Matrix3d& E,
                    const Eigen::Vector2d& x1,
                    const Eigen::Vector2d& x2);
}

class SampsonErrorTest_138 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test that when x2^T * E * x1 = 0 (i.e., the epipolar constraint is perfectly
// satisfied), the Sampson error should be 0.
TEST_F(SampsonErrorTest_138, PerfectEpipolarConstraintReturnsZero_138) {
  // Use an essential matrix from a pure translation along x-axis:
  // E = [0, 0, 0; 0, 0, -1; 0, 1, 0]
  Eigen::Matrix3d E;
  E << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;

  // Points that satisfy x2^T * E * x1 = 0
  // x1 = (0, 0), x2 = (0, 0)
  // x2.homogeneous() = (0, 0, 1), E * x1.homogeneous() = (0, 0, 0)
  // dot product = 0
  Eigen::Vector2d x1(0.0, 0.0);
  Eigen::Vector2d x2(0.0, 0.0);

  double error = glomap::SampsonError(E, x1, x2);
  EXPECT_DOUBLE_EQ(error, 0.0);
}

// Test with identity-like essential matrix and known points to verify
// Sampson error computation.
TEST_F(SampsonErrorTest_138, KnownValueComputation_138) {
  // E = identity matrix (not a valid essential matrix, but we test the formula)
  Eigen::Matrix3d E = Eigen::Matrix3d::Identity();

  Eigen::Vector2d x1(1.0, 0.0);
  Eigen::Vector2d x2(1.0, 0.0);

  // Ex1 = E * [1, 0, 1]^T = [1, 0, 1]
  // Etx2 = E^T * [1, 0, 1]^T = [1, 0, 1]
  // C = [1, 0, 1] . [1, 0, 1] = 1 + 0 + 1 = 2
  // Cx = 1^2 + 0^2 = 1
  // Cy = 1^2 + 0^2 = 1
  // r2 = 4 / 2 = 2
  double error = glomap::SampsonError(E, x1, x2);
  EXPECT_DOUBLE_EQ(error, 2.0);
}

// Test with a non-trivial essential matrix and verify the formula manually.
TEST_F(SampsonErrorTest_138, NonTrivialEssentialMatrix_138) {
  Eigen::Matrix3d E;
  E << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;

  Eigen::Vector2d x1(1.0, 2.0);
  Eigen::Vector2d x2(3.0, 4.0);

  // x1.homogeneous() = [1, 2, 1]
  // x2.homogeneous() = [3, 4, 1]
  // Ex1 = [0, -1, 2]
  // Etx2 = [0, 1, -4] (E^T = [0,0,0; 0,0,1; 0,-1,0], E^T*[3,4,1] = [0, 1, -4])
  // C = [0, -1, 2] . [3, 4, 1] = 0 - 4 + 2 = -2
  // Cx = 0^2 + (-1)^2 = 1
  // Cy = 0^2 + 1^2 = 1
  // r2 = (-2)^2 / (1 + 1) = 4 / 2 = 2
  double error = glomap::SampsonError(E, x1, x2);
  EXPECT_DOUBLE_EQ(error, 2.0);
}

// Test that the Sampson error is non-negative.
TEST_F(SampsonErrorTest_138, ErrorIsNonNegative_138) {
  Eigen::Matrix3d E;
  E << 0.1, 0.2, 0.3,
       0.4, 0.5, 0.6,
       0.7, 0.8, 0.9;

  Eigen::Vector2d x1(1.5, -2.3);
  Eigen::Vector2d x2(-0.7, 3.1);

  double error = glomap::SampsonError(E, x1, x2);
  EXPECT_GE(error, 0.0);
}

// Test with zero essential matrix: numerator is 0, so error should be 0
// (as long as denominator doesn't cause issues — but with E=0, Ex1 = 0,
// Cx = 0, Cy = 0, denominator = 0, this is 0/0).
// This is a boundary condition.
TEST_F(SampsonErrorTest_138, ZeroEssentialMatrix_138) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Zero();

  Eigen::Vector2d x1(1.0, 2.0);
  Eigen::Vector2d x2(3.0, 4.0);

  // Ex1 = [0,0,0], Etx2 = [0,0,0]
  // C = 0, Cx = 0, Cy = 0
  // r2 = 0/0 -> NaN
  double error = glomap::SampsonError(E, x1, x2);
  // When E is zero, we get 0/0 which is NaN
  EXPECT_TRUE(std::isnan(error));
}

// Test with both points at origin.
TEST_F(SampsonErrorTest_138, PointsAtOrigin_138) {
  Eigen::Matrix3d E;
  E << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;

  Eigen::Vector2d x1(0.0, 0.0);
  Eigen::Vector2d x2(0.0, 0.0);

  double error = glomap::SampsonError(E, x1, x2);
  EXPECT_DOUBLE_EQ(error, 0.0);
}

// Test symmetry: swapping x1 and x2 with E replaced by E^T should give same error.
TEST_F(SampsonErrorTest_138, SwapPointsWithTranspose_138) {
  Eigen::Matrix3d E;
  E << 0.3, -0.1, 0.5,
       0.2, 0.7, -0.4,
       -0.6, 0.1, 0.8;

  Eigen::Vector2d x1(1.0, 2.0);
  Eigen::Vector2d x2(3.0, -1.0);

  double error1 = glomap::SampsonError(E, x1, x2);
  double error2 = glomap::SampsonError(E.transpose(), x2, x1);

  EXPECT_NEAR(error1, error2, 1e-12);
}

// Test with large coordinates to check numerical stability.
TEST_F(SampsonErrorTest_138, LargeCoordinates_138) {
  Eigen::Matrix3d E;
  E << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;

  Eigen::Vector2d x1(1000.0, 2000.0);
  Eigen::Vector2d x2(3000.0, 4000.0);

  double error = glomap::SampsonError(E, x1, x2);
  EXPECT_GE(error, 0.0);
  EXPECT_TRUE(std::isfinite(error));
}

// Test with negative coordinates.
TEST_F(SampsonErrorTest_138, NegativeCoordinates_138) {
  Eigen::Matrix3d E;
  E << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;

  Eigen::Vector2d x1(-1.0, -2.0);
  Eigen::Vector2d x2(-3.0, -4.0);

  // Ex1 = E * [-1, -2, 1]^T = [0, -1, -2]
  // Etx2 = E^T * [-3, -4, 1]^T = [0, 1, 4] 
  // Wait: E^T = [0,0,0; 0,0,1; 0,-1,0]
  // E^T * [-3, -4, 1]^T = [0, 1, 4]
  // C = [0, -1, -2] . [-3, -4, 1] = 0 + 4 - 2 = 2
  // Cx = 0 + 1 = 1
  // Cy = 0 + 1 = 1
  // r2 = 4 / 2 = 2
  double error = glomap::SampsonError(E, x1, x2);
  EXPECT_DOUBLE_EQ(error, 2.0);
}

// Detailed manual computation with a general E matrix.
TEST_F(SampsonErrorTest_138, DetailedManualComputation_138) {
  Eigen::Matrix3d E;
  E << 1, 2, 3,
       4, 5, 6,
       7, 8, 9;

  Eigen::Vector2d x1(1.0, 0.0);
  Eigen::Vector2d x2(0.0, 1.0);

  // x1.homogeneous() = [1, 0, 1]
  // x2.homogeneous() = [0, 1, 1]
  // Ex1 = [1+3, 4+6, 7+9] = [4, 10, 16]
  // Etx2 = E^T * [0, 1, 1] = [4+7, 5+8, 6+9] = [11, 13, 15]
  // C = [4, 10, 16] . [0, 1, 1] = 0 + 10 + 16 = 26
  // Cx = 16 + 100 = 116
  // Cy = 121 + 169 = 290
  // r2 = 676 / 406
  double expected = 676.0 / 406.0;
  double error = glomap::SampsonError(E, x1, x2);
  EXPECT_NEAR(error, expected, 1e-12);
}
