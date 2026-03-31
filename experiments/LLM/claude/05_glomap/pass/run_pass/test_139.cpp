#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>

// Forward declaration based on the provided code
namespace glomap {
extern const double EPS;
double SampsonError(const Eigen::Matrix3d& E, const Eigen::Vector3d& x1, const Eigen::Vector3d& x2);
}

class SampsonErrorTest_139 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test with identity essential matrix and identical points
TEST_F(SampsonErrorTest_139, IdentityMatrixIdenticalPoints_139) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Identity();
  Eigen::Vector3d x1(1.0, 0.0, 1.0);
  Eigen::Vector3d x2(1.0, 0.0, 1.0);
  
  double result = glomap::SampsonError(E, x1, x2);
  // With E = I, Ex1 = x1/x1[2] = (1,0,1), x2^T Ex1 = x2 dot (1,0,1) = 1+0+1=2
  // The result should be a finite non-negative number
  EXPECT_GE(result, 0.0);
  EXPECT_TRUE(std::isfinite(result));
}

// Test with zero essential matrix - should return 0
TEST_F(SampsonErrorTest_139, ZeroEssentialMatrix_139) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Zero();
  Eigen::Vector3d x1(1.0, 2.0, 1.0);
  Eigen::Vector3d x2(3.0, 4.0, 1.0);
  
  double result = glomap::SampsonError(E, x1, x2);
  // E=0 => Ex1=0, Etx2=0, C=0 => r2=0/(0+0) which could be NaN or 0
  // Actually C=0, Cx=0, Cy=0, so 0/(0+0) = 0/0 = NaN
  // Let's just check the behavior
  // With E=0: Ex1 = (0,0,0), C = 0, Cx = 0, Cy = 0 => 0/0
  // This is a degenerate case; we just document the behavior
  // The function may return NaN here
  // We just verify it doesn't crash
  (void)result;
}

// Test with a valid essential matrix and perfectly corresponding points
TEST_F(SampsonErrorTest_139, PerfectEpipolarConstraint_139) {
  // Construct E from known R and t
  // For a pure translation along x-axis: t = (1,0,0), t_cross = [[0,0,0],[0,0,-1],[0,1,0]]
  // E = t_cross * R, with R = I => E = t_cross
  Eigen::Matrix3d E;
  E << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;
  
  // Point on epipolar line: x2^T E x1 = 0 when the points satisfy the constraint
  // For x1 = (0, 0, 1) and x2 = (0, 0, 1): x2^T E x1 = 0
  Eigen::Vector3d x1(0.0, 0.0, 1.0);
  Eigen::Vector3d x2(0.0, 0.0, 1.0);
  
  double result = glomap::SampsonError(E, x1, x2);
  EXPECT_NEAR(result, 0.0, 1e-10);
}

// Test with known non-zero Sampson error
TEST_F(SampsonErrorTest_139, NonZeroSampsonError_139) {
  Eigen::Matrix3d E;
  E << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;
  
  // x1 = (1, 1, 1), x2 = (1, 1, 1)
  // Ex1 = E * (1,1,1) / (EPS + 1) ≈ E * (1,1,1) = (0, -1, 1)
  // Etx2 = E^T * (1,1,1) / (EPS + 1) ≈ E^T * (1,1,1) = (0, 1, -1)
  // C = (0,-1,1) dot (1,1,1) = 0 - 1 + 1 = 0
  // So the error is still 0 here. Let's pick different points.
  
  Eigen::Vector3d x1(1.0, 0.0, 1.0);
  Eigen::Vector3d x2(0.0, 1.0, 1.0);
  
  // Ex1 = E * (1,0,1) / (1+EPS) ≈ (0, -1, 0)
  // Etx2 = E^T * (0,1,1) / (1+EPS) ≈ (0, 1, -1)
  // C = (0,-1,0) dot (0,1,1) = 0 - 1 + 0 = -1
  // Cx = 0^2 + (-1)^2 = 1
  // Cy = 0^2 + 1^2 = 1
  // r2 = 1 / 2 = 0.5
  
  double result = glomap::SampsonError(E, x1, x2);
  EXPECT_GT(result, 0.0);
  EXPECT_NEAR(result, 0.5, 1e-6);
}

// Test symmetry: SampsonError(E, x1, x2) vs SampsonError(E^T, x2, x1)
TEST_F(SampsonErrorTest_139, SymmetryProperty_139) {
  Eigen::Matrix3d E;
  E << 0.1, 0.2, 0.3,
       0.4, 0.5, 0.6,
       0.7, 0.8, 0.9;
  
  Eigen::Vector3d x1(1.0, 2.0, 1.0);
  Eigen::Vector3d x2(3.0, 4.0, 1.0);
  
  double error1 = glomap::SampsonError(E, x1, x2);
  double error2 = glomap::SampsonError(E.transpose(), x2, x1);
  
  EXPECT_NEAR(error1, error2, 1e-10);
}

// Test that Sampson error is always non-negative
TEST_F(SampsonErrorTest_139, NonNegativeResult_139) {
  Eigen::Matrix3d E;
  E << 1, 2, 3,
       4, 5, 6,
       7, 8, 9;
  
  Eigen::Vector3d x1(0.5, -0.3, 1.0);
  Eigen::Vector3d x2(-0.7, 0.9, 1.0);
  
  double result = glomap::SampsonError(E, x1, x2);
  EXPECT_GE(result, 0.0);
}

// Test with homogeneous coordinates where third component is not 1
TEST_F(SampsonErrorTest_139, NonUnitHomogeneousCoordinate_139) {
  Eigen::Matrix3d E;
  E << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;
  
  Eigen::Vector3d x1(2.0, 0.0, 2.0);  // equivalent to (1, 0, 1) when normalized
  Eigen::Vector3d x2(0.0, 3.0, 3.0);  // equivalent to (0, 1, 1) when normalized
  
  double result = glomap::SampsonError(E, x1, x2);
  
  // The function divides by (EPS + x[2]), so this should give a result
  // related to the normalized version
  EXPECT_GE(result, 0.0);
  EXPECT_TRUE(std::isfinite(result));
}

// Test with very small z-coordinate (near-zero, but protected by EPS)
TEST_F(SampsonErrorTest_139, SmallZCoordinate_139) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Identity();
  Eigen::Vector3d x1(1.0, 1.0, 1e-15);
  Eigen::Vector3d x2(1.0, 1.0, 1.0);
  
  double result = glomap::SampsonError(E, x1, x2);
  // Should not crash due to division by zero (EPS protects)
  EXPECT_TRUE(std::isfinite(result));
}

// Test with zero z-coordinate (EPS prevents division by zero)
TEST_F(SampsonErrorTest_139, ZeroZCoordinate_139) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Identity();
  Eigen::Vector3d x1(1.0, 1.0, 0.0);
  Eigen::Vector3d x2(1.0, 1.0, 1.0);
  
  double result = glomap::SampsonError(E, x1, x2);
  // EPS prevents actual division by zero
  EXPECT_TRUE(std::isfinite(result));
}

// Test with negative z-coordinate
TEST_F(SampsonErrorTest_139, NegativeZCoordinate_139) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Identity();
  Eigen::Vector3d x1(1.0, 1.0, -1.0);
  Eigen::Vector3d x2(1.0, 1.0, 1.0);
  
  double result = glomap::SampsonError(E, x1, x2);
  EXPECT_GE(result, 0.0);
  EXPECT_TRUE(std::isfinite(result));
}

// Test with large values
TEST_F(SampsonErrorTest_139, LargeValues_139) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Identity();
  Eigen::Vector3d x1(1e6, 1e6, 1.0);
  Eigen::Vector3d x2(1e6, 1e6, 1.0);
  
  double result = glomap::SampsonError(E, x1, x2);
  EXPECT_GE(result, 0.0);
  EXPECT_TRUE(std::isfinite(result));
}

// Test: when epipolar constraint is exactly satisfied, error should be zero
TEST_F(SampsonErrorTest_139, ExactEpipolarConstraintSatisfied_139) {
  // Fundamental matrix for pure translation t=(1,0,0)
  Eigen::Matrix3d E;
  E << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;
  
  // Any point (a, b, 1) and (c, 0, 1) should satisfy x2^T E x1 = 0
  // x2^T E = (0, c, 0) * ... let's verify
  // E * x1 = (0, -1, b) for x1 = (a, b, 1)
  // x2^T * E * x1 = c*0 + 0*(-1) + 1*b = b for x2 = (c, 0, 1)
  // So we need b = 0
  
  Eigen::Vector3d x1(5.0, 0.0, 1.0);
  Eigen::Vector3d x2(3.0, 0.0, 1.0);
  
  double result = glomap::SampsonError(E, x1, x2);
  EXPECT_NEAR(result, 0.0, 1e-10);
}

// Verify manual computation with specific values
TEST_F(SampsonErrorTest_139, ManualComputation_139) {
  Eigen::Matrix3d E;
  E << 1, 0, 0,
       0, 1, 0,
       0, 0, 1;
  
  Eigen::Vector3d x1(1.0, 0.0, 1.0);
  Eigen::Vector3d x2(0.0, 1.0, 1.0);
  
  // Ex1 = E * (1,0,1) / (EPS + 1) ≈ (1, 0, 1)
  // Etx2 = E^T * (0,1,1) / (EPS + 1) ≈ (0, 1, 1)
  // C = (1,0,1) dot (0,1,1) = 0 + 0 + 1 = 1
  // Cx = 1^2 + 0^2 = 1
  // Cy = 0^2 + 1^2 = 1
  // r2 = 1 / (1 + 1) = 0.5
  
  double result = glomap::SampsonError(E, x1, x2);
  EXPECT_NEAR(result, 0.5, 1e-6);
}

// Test with diagonal essential matrix
TEST_F(SampsonErrorTest_139, DiagonalEssentialMatrix_139) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Zero();
  E(0, 0) = 2.0;
  E(1, 1) = 3.0;
  E(2, 2) = 0.0;
  
  Eigen::Vector3d x1(1.0, 1.0, 1.0);
  Eigen::Vector3d x2(1.0, 1.0, 1.0);
  
  // Ex1 = (2, 3, 0) / (1+EPS) ≈ (2, 3, 0)
  // Etx2 = (2, 3, 0) / (1+EPS) ≈ (2, 3, 0)
  // C = (2,3,0) dot (1,1,1) = 2+3+0 = 5
  // Cx = 4 + 9 = 13
  // Cy = 4 + 9 = 13
  // r2 = 25 / 26 ≈ 0.961538
  
  double result = glomap::SampsonError(E, x1, x2);
  EXPECT_NEAR(result, 25.0 / 26.0, 1e-6);
}
