#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>

namespace glomap {
double SampsonError(const Eigen::Matrix3d& E,
                    const Eigen::Vector2d& x1,
                    const Eigen::Vector2d& x2);
}

class SampsonErrorTest_67 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test with identity essential matrix and matching points at origin
TEST_F(SampsonErrorTest_67, IdentityMatrixOriginPoints_67) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(0.0, 0.0);
  Eigen::Vector2d x2(0.0, 0.0);

  // E * [0,0,1]^T = [0,0,1]^T
  // E^T * [0,0,1]^T = [0,0,1]^T
  // C = [0,0,1] . [0,0,1] = 1
  // Cx = 0^2 + 0^2 = 0
  // Cy = 0^2 + 0^2 = 0
  // Division by zero => result is inf or nan
  double result = glomap::SampsonError(E, x1, x2);
  EXPECT_TRUE(std::isinf(result) || std::isnan(result));
}

// Test with identity matrix and points that produce a well-defined result
TEST_F(SampsonErrorTest_67, IdentityMatrixNonZeroPoints_67) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(1.0, 0.0);
  Eigen::Vector2d x2(1.0, 0.0);

  // E * [1,0,1]^T = [1,0,1]^T
  // E^T * [1,0,1]^T = [1,0,1]^T
  // C = [1,0,1] . [1,0,1] = 1 + 0 + 1 = 2
  // Cx = 1^2 + 0^2 = 1
  // Cy = 1^2 + 0^2 = 1
  // r2 = 4 / 2 = 2
  double result = glomap::SampsonError(E, x1, x2);
  EXPECT_NEAR(result, 2.0, 1e-10);
}

// Test with zero essential matrix - all terms should be zero, causing 0/0
TEST_F(SampsonErrorTest_67, ZeroMatrix_67) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Zero();
  Eigen::Vector2d x1(1.0, 2.0);
  Eigen::Vector2d x2(3.0, 4.0);

  // E * x1h = [0,0,0], E^T * x2h = [0,0,0]
  // C = 0, Cx = 0, Cy = 0 => 0/0 = nan
  double result = glomap::SampsonError(E, x1, x2);
  EXPECT_TRUE(std::isnan(result));
}

// Test that Sampson error is zero when the epipolar constraint is perfectly satisfied
TEST_F(SampsonErrorTest_67, PerfectEpipolarConstraint_67) {
  // Create a known essential matrix from a rotation and translation
  // For simplicity, use a skew-symmetric matrix [t]_x * R
  // Use t = [1,0,0], R = I => E = [t]_x
  Eigen::Matrix3d E;
  E << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;

  // Points satisfying x2^T E x1 = 0
  // x1 = (0, 0), x2 = (0, 0)
  // E * [0,0,1]^T = [0,-1,0]^T
  // [0,0,1] . [0,-1,0] = 0 => C = 0 => r2 = 0
  Eigen::Vector2d x1(0.0, 0.0);
  Eigen::Vector2d x2(0.0, 0.0);

  double result = glomap::SampsonError(E, x1, x2);
  EXPECT_NEAR(result, 0.0, 1e-10);
}

// Test with a known essential matrix and points where error is nonzero
TEST_F(SampsonErrorTest_67, NonZeroSampsonError_67) {
  Eigen::Matrix3d E;
  E << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;

  Eigen::Vector2d x1(1.0, 1.0);
  Eigen::Vector2d x2(1.0, 1.0);

  // E * [1,1,1]^T = [0, -1, 1]^T
  // E^T * [1,1,1]^T = [0, 1, -1]^T
  // C = [0,-1,1] . [1,1,1] = 0 - 1 + 1 = 0
  // Cx = 0 + 1 = 1, Cy = 0 + 1 = 1
  // r2 = 0 / 2 = 0
  double result = glomap::SampsonError(E, x1, x2);
  EXPECT_NEAR(result, 0.0, 1e-10);
}

// Test with non-trivial E and points that give nonzero error
TEST_F(SampsonErrorTest_67, NonTrivialNonZeroError_67) {
  Eigen::Matrix3d E;
  E << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;

  // Choose x1 and x2 such that epipolar constraint is not satisfied
  Eigen::Vector2d x1(0.0, 1.0);
  Eigen::Vector2d x2(0.0, 0.0);

  // E * [0,1,1]^T = [0, -1, 1]^T
  // E^T * [0,0,1]^T = [0, 1, 0]^T
  // C = [0,-1,1] . [0,0,1] = 0 + 0 + 1 = 1
  // Cx = 0^2 + (-1)^2 = 1
  // Cy = 0^2 + 1^2 = 1
  // r2 = 1 / 2 = 0.5
  double result = glomap::SampsonError(E, x1, x2);
  EXPECT_NEAR(result, 0.5, 1e-10);
}

// Test that the result is non-negative (Sampson error is a squared quantity)
TEST_F(SampsonErrorTest_67, ResultIsNonNegative_67) {
  Eigen::Matrix3d E;
  E << 0.1, 0.2, 0.3,
       0.4, 0.5, 0.6,
       0.7, 0.8, 0.9;

  Eigen::Vector2d x1(3.5, -2.7);
  Eigen::Vector2d x2(-1.2, 4.8);

  double result = glomap::SampsonError(E, x1, x2);
  EXPECT_GE(result, 0.0);
}

// Test symmetry-like property: swapping x1 and x2 with E transposed
TEST_F(SampsonErrorTest_67, SwapPointsWithTranspose_67) {
  Eigen::Matrix3d E;
  E << 0.1, -0.3, 0.5,
       0.2, 0.4, -0.6,
       -0.1, 0.7, 0.3;

  Eigen::Vector2d x1(1.0, 2.0);
  Eigen::Vector2d x2(3.0, 4.0);

  double result1 = glomap::SampsonError(E, x1, x2);
  double result2 = glomap::SampsonError(E.transpose(), x2, x1);

  EXPECT_NEAR(result1, result2, 1e-10);
}

// Test with large coordinate values
TEST_F(SampsonErrorTest_67, LargeCoordinates_67) {
  Eigen::Matrix3d E;
  E << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;

  Eigen::Vector2d x1(1000.0, 2000.0);
  Eigen::Vector2d x2(3000.0, 4000.0);

  // E * [1000, 2000, 1]^T = [0, -1, 2000]^T
  // E^T * [3000, 4000, 1]^T = [0, 1, -4000]^T
  // C = [0, -1, 2000] . [3000, 4000, 1] = 0 - 4000 + 2000 = -2000
  // Cx = 0 + 1 = 1
  // Cy = 0 + 1 = 1
  // r2 = 4000000 / 2 = 2000000
  double result = glomap::SampsonError(E, x1, x2);
  EXPECT_NEAR(result, 2000000.0, 1e-4);
}

// Test with negative coordinates
TEST_F(SampsonErrorTest_67, NegativeCoordinates_67) {
  Eigen::Matrix3d E = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(-1.0, -1.0);
  Eigen::Vector2d x2(-1.0, -1.0);

  // E * [-1,-1,1]^T = [-1,-1,1]^T
  // E^T * [-1,-1,1]^T = [-1,-1,1]^T
  // C = [-1,-1,1] . [-1,-1,1] = 1 + 1 + 1 = 3
  // Cx = 1 + 1 = 2
  // Cy = 1 + 1 = 2
  // r2 = 9 / 4 = 2.25
  double result = glomap::SampsonError(E, x1, x2);
  EXPECT_NEAR(result, 2.25, 1e-10);
}

// Test with a scaled essential matrix (scaling E by a factor)
TEST_F(SampsonErrorTest_67, ScaledEssentialMatrix_67) {
  Eigen::Matrix3d E;
  E << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;

  Eigen::Vector2d x1(0.0, 1.0);
  Eigen::Vector2d x2(0.0, 0.0);

  double result1 = glomap::SampsonError(E, x1, x2);
  double result2 = glomap::SampsonError(2.0 * E, x1, x2);

  // Sampson error should be the same when E is scaled,
  // because C scales by k, Cx and Cy scale by k^2,
  // so r2 = k^2 C^2 / (k^2 Cx + k^2 Cy) = C^2 / (Cx + Cy) = same
  EXPECT_NEAR(result1, result2, 1e-10);
}

// Verify actual manual computation for a general case
TEST_F(SampsonErrorTest_67, ManualComputation_67) {
  Eigen::Matrix3d E;
  E << 1, 2, 3,
       4, 5, 6,
       7, 8, 9;

  Eigen::Vector2d x1(1.0, 0.0);
  Eigen::Vector2d x2(0.0, 1.0);

  // x1h = [1,0,1], x2h = [0,1,1]
  // Ex1 = E * [1,0,1]^T = [1+3, 4+6, 7+9] = [4, 10, 16]
  // Etx2 = E^T * [0,1,1]^T = [2+3, 5+6, 8+9] = [4+7 hmm, let me redo]
  // E^T:
  // 1 4 7
  // 2 5 8
  // 3 6 9
  // E^T * [0,1,1]^T = [4+7, 5+8, 6+9] = [11, 13, 15]
  // C = [4, 10, 16] . [0, 1, 1] = 0 + 10 + 16 = 26
  // Cx = 4^2 + 10^2 = 16 + 100 = 116
  // Cy = 11^2 + 13^2 = 121 + 169 = 290
  // r2 = 26^2 / (116 + 290) = 676 / 406
  double expected = 676.0 / 406.0;
  double result = glomap::SampsonError(E, x1, x2);
  EXPECT_NEAR(result, expected, 1e-10);
}
