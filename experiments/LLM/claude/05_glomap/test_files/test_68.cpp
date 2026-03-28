#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Dense>

namespace glomap {
double HomographyError(const Eigen::Matrix3d& H,
                       const Eigen::Vector2d& x1,
                       const Eigen::Vector2d& x2);
}

class HomographyErrorTest_68 : public ::testing::Test {
 protected:
  Eigen::Matrix3d identity_;
  void SetUp() override {
    identity_ = Eigen::Matrix3d::Identity();
  }
};

// Test that identity homography with the same points gives zero error
TEST_F(HomographyErrorTest_68, IdentityHomographySamePoints_68) {
  Eigen::Vector2d x1(1.0, 2.0);
  Eigen::Vector2d x2(1.0, 2.0);
  double error = glomap::HomographyError(identity_, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

// Test that identity homography with different points gives nonzero error
TEST_F(HomographyErrorTest_68, IdentityHomographyDifferentPoints_68) {
  Eigen::Vector2d x1(1.0, 2.0);
  Eigen::Vector2d x2(3.0, 4.0);
  double error = glomap::HomographyError(identity_, x1, x2);
  // Expected: (1-3)^2 + (2-4)^2 = 4 + 4 = 8
  EXPECT_NEAR(error, 8.0, 1e-10);
}

// Test with zero points
TEST_F(HomographyErrorTest_68, ZeroPoints_68) {
  Eigen::Vector2d x1(0.0, 0.0);
  Eigen::Vector2d x2(0.0, 0.0);
  double error = glomap::HomographyError(identity_, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

// Test with a scaling homography
TEST_F(HomographyErrorTest_68, ScalingHomography_68) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  H(0, 0) = 2.0;
  H(1, 1) = 3.0;
  Eigen::Vector2d x1(1.0, 1.0);
  // H * [1, 1, 1]^T = [2, 3, 1]^T -> normalized = (2, 3)
  Eigen::Vector2d x2(2.0, 3.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

// Test with a translation homography
TEST_F(HomographyErrorTest_68, TranslationHomography_68) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  H(0, 2) = 5.0;  // translate x by 5
  H(1, 2) = -3.0; // translate y by -3
  Eigen::Vector2d x1(1.0, 2.0);
  // H * [1, 2, 1]^T = [6, -1, 1]^T -> normalized = (6, -1)
  Eigen::Vector2d x2(6.0, -1.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

// Test with a homography that has a non-trivial third row (projective)
TEST_F(HomographyErrorTest_68, ProjectiveHomography_68) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  H(2, 0) = 0.5;  // Makes third component depend on x1
  Eigen::Vector2d x1(2.0, 0.0);
  // H * [2, 0, 1]^T = [2, 0, 2]^T -> normalized = (1, 0)
  Eigen::Vector2d x2(1.0, 0.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

// Test with wrong x2 for projective homography
TEST_F(HomographyErrorTest_68, ProjectiveHomographyWithError_68) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  H(2, 0) = 0.5;
  Eigen::Vector2d x1(2.0, 0.0);
  // H * [2, 0, 1]^T = [2, 0, 2]^T -> normalized = (1, 0)
  Eigen::Vector2d x2(2.0, 0.0);  // wrong point
  double error = glomap::HomographyError(H, x1, x2);
  // Expected: (1-2)^2 + (0-0)^2 = 1
  EXPECT_NEAR(error, 1.0, 1e-10);
}

// Test that error is always non-negative
TEST_F(HomographyErrorTest_68, ErrorIsNonNegative_68) {
  Eigen::Matrix3d H;
  H << 1.5, -0.3, 0.7,
       0.2,  1.1, -0.5,
       0.01, 0.02, 1.0;
  Eigen::Vector2d x1(3.0, -2.0);
  Eigen::Vector2d x2(-1.0, 5.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_GE(error, 0.0);
}

// Test with negative coordinates
TEST_F(HomographyErrorTest_68, NegativeCoordinates_68) {
  Eigen::Vector2d x1(-1.0, -2.0);
  Eigen::Vector2d x2(-1.0, -2.0);
  double error = glomap::HomographyError(identity_, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

// Test with large coordinates
TEST_F(HomographyErrorTest_68, LargeCoordinates_68) {
  Eigen::Vector2d x1(1e6, 1e6);
  Eigen::Vector2d x2(1e6, 1e6);
  double error = glomap::HomographyError(identity_, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-4);
}

// Test with very small coordinates
TEST_F(HomographyErrorTest_68, SmallCoordinates_68) {
  Eigen::Vector2d x1(1e-10, 1e-10);
  Eigen::Vector2d x2(1e-10, 1e-10);
  double error = glomap::HomographyError(identity_, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-15);
}

// Test with a general homography and verify numerical correctness
TEST_F(HomographyErrorTest_68, GeneralHomographyCorrectness_68) {
  Eigen::Matrix3d H;
  H << 2.0, 0.0, 1.0,
       0.0, 2.0, 1.0,
       0.0, 0.0, 1.0;
  Eigen::Vector2d x1(1.0, 1.0);
  // H * [1, 1, 1]^T = [3, 3, 1]^T -> normalized = (3, 3)
  Eigen::Vector2d x2(3.0, 3.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

// Test that the homography properly handles the third component normalization
TEST_F(HomographyErrorTest_68, ThirdComponentNormalization_68) {
  Eigen::Matrix3d H;
  H << 1.0, 0.0, 0.0,
       0.0, 1.0, 0.0,
       0.0, 0.0, 2.0;  // scale the homogeneous coordinate
  Eigen::Vector2d x1(4.0, 6.0);
  // H * [4, 6, 1]^T = [4, 6, 2]^T -> normalized = (2, 3)
  Eigen::Vector2d x2(2.0, 3.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

// Test near-zero third component (boundary: H makes z ~ 0, EPS should prevent division by zero)
TEST_F(HomographyErrorTest_68, NearZeroThirdComponent_68) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Zero();
  H(0, 0) = 1.0;
  H(1, 1) = 1.0;
  // H(2, 2) = 0.0, so H * [x, y, 1]^T = [x, y, 0]^T
  // The EPS should prevent division by zero
  Eigen::Vector2d x1(1.0, 1.0);
  Eigen::Vector2d x2(0.0, 0.0);
  double error = glomap::HomographyError(H, x1, x2);
  // Should not crash or return NaN/Inf
  EXPECT_FALSE(std::isnan(error));
  EXPECT_FALSE(std::isinf(error));
  EXPECT_GE(error, 0.0);
}

// Test with a rotation homography (90 degree rotation)
TEST_F(HomographyErrorTest_68, RotationHomography_68) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  H(0, 0) = 0.0;  H(0, 1) = -1.0;
  H(1, 0) = 1.0;  H(1, 1) = 0.0;
  Eigen::Vector2d x1(1.0, 0.0);
  // H * [1, 0, 1]^T = [0, 1, 1]^T -> normalized = (0, 1)
  Eigen::Vector2d x2(0.0, 1.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

// Test symmetry: error(H, x1, x2) != error(H, x2, x1) in general
TEST_F(HomographyErrorTest_68, AsymmetryCheck_68) {
  Eigen::Matrix3d H;
  H << 2.0, 0.0, 1.0,
       0.0, 3.0, -1.0,
       0.1, 0.0, 1.0;
  Eigen::Vector2d x1(1.0, 2.0);
  Eigen::Vector2d x2(3.0, 4.0);
  double error1 = glomap::HomographyError(H, x1, x2);
  double error2 = glomap::HomographyError(H, x2, x1);
  // In general, these should be different
  // Just check both are non-negative
  EXPECT_GE(error1, 0.0);
  EXPECT_GE(error2, 0.0);
}

// Test that the returned value is squared norm (not norm)
TEST_F(HomographyErrorTest_68, ReturnsSquaredError_68) {
  Eigen::Vector2d x1(0.0, 0.0);
  Eigen::Vector2d x2(3.0, 4.0);
  double error = glomap::HomographyError(identity_, x1, x2);
  // Expected squared norm: 3^2 + 4^2 = 25 (not 5)
  EXPECT_NEAR(error, 25.0, 1e-10);
}
