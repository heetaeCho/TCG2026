#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Dense>

// Include the header that declares HomographyError
// Based on the file structure, we need the declaration
namespace glomap {
extern const double EPS;
double HomographyError(const Eigen::Matrix3d& H,
                       const Eigen::Vector2d& x1,
                       const Eigen::Vector2d& x2);
}

class HomographyErrorTest_140 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test that identity homography with same points gives zero error
TEST_F(HomographyErrorTest_140, IdentityHomographySamePoints_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(1.0, 2.0);
  Eigen::Vector2d x2(1.0, 2.0);

  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

// Test that identity homography with different points gives non-zero error
TEST_F(HomographyErrorTest_140, IdentityHomographyDifferentPoints_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(1.0, 0.0);
  Eigen::Vector2d x2(2.0, 0.0);

  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 1.0, 1e-10);
}

// Test with zero points
TEST_F(HomographyErrorTest_140, ZeroPoints_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(0.0, 0.0);
  Eigen::Vector2d x2(0.0, 0.0);

  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

// Test with a known translation homography
TEST_F(HomographyErrorTest_140, TranslationHomography_140) {
  // H translates by (3, 4) in homogeneous coordinates
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  H(0, 2) = 3.0;
  H(1, 2) = 4.0;

  Eigen::Vector2d x1(0.0, 0.0);
  Eigen::Vector2d x2(3.0, 4.0);

  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

// Test with a known translation homography where x2 doesn't match
TEST_F(HomographyErrorTest_140, TranslationHomographyMismatch_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  H(0, 2) = 3.0;
  H(1, 2) = 4.0;

  Eigen::Vector2d x1(0.0, 0.0);
  Eigen::Vector2d x2(0.0, 0.0);

  double error = glomap::HomographyError(H, x1, x2);
  // H * [0,0,1]^T = [3,4,1]^T -> projected = (3,4)
  // Error = (3-0)^2 + (4-0)^2 = 25
  EXPECT_NEAR(error, 25.0, 1e-10);
}

// Test with scaling homography
TEST_F(HomographyErrorTest_140, ScalingHomography_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  H(0, 0) = 2.0;
  H(1, 1) = 2.0;

  Eigen::Vector2d x1(1.0, 1.0);
  Eigen::Vector2d x2(2.0, 2.0);

  double error = glomap::HomographyError(H, x1, x2);
  // H * [1,1,1]^T = [2,2,1]^T -> projected = (2,2)
  EXPECT_NEAR(error, 0.0, 1e-10);
}

// Test with a homography that scales the third coordinate
TEST_F(HomographyErrorTest_140, HomographyWithPerspectiveDivision_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  H(2, 2) = 2.0;  // Scale the homogeneous coordinate

  Eigen::Vector2d x1(4.0, 6.0);
  // H * [4,6,1]^T = [4,6,2]^T -> projected = (2,3)
  Eigen::Vector2d x2(2.0, 3.0);

  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

// Test with negative coordinates
TEST_F(HomographyErrorTest_140, NegativeCoordinates_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(-3.0, -4.0);
  Eigen::Vector2d x2(-3.0, -4.0);

  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

// Test that error is always non-negative
TEST_F(HomographyErrorTest_140, ErrorIsNonNegative_140) {
  Eigen::Matrix3d H;
  H << 1.5, 0.3, -0.2,
       0.1, 2.0, 0.5,
       0.01, -0.02, 1.0;

  Eigen::Vector2d x1(5.0, -3.0);
  Eigen::Vector2d x2(10.0, 20.0);

  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_GE(error, 0.0);
}

// Test with a rotation homography (90 degrees)
TEST_F(HomographyErrorTest_140, RotationHomography_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  H(0, 0) = 0.0;
  H(0, 1) = -1.0;
  H(1, 0) = 1.0;
  H(1, 1) = 0.0;

  Eigen::Vector2d x1(1.0, 0.0);
  // H * [1,0,1]^T = [0,1,1]^T -> projected = (0,1)
  Eigen::Vector2d x2(0.0, 1.0);

  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

// Test with large coordinates
TEST_F(HomographyErrorTest_140, LargeCoordinates_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(1e6, 1e6);
  Eigen::Vector2d x2(1e6, 1e6);

  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-4);
}

// Test with very small coordinates
TEST_F(HomographyErrorTest_140, VerySmallCoordinates_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(1e-10, 1e-10);
  Eigen::Vector2d x2(1e-10, 1e-10);

  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-15);
}

// Test with a general homography and known result
TEST_F(HomographyErrorTest_140, GeneralHomographyKnownResult_140) {
  Eigen::Matrix3d H;
  H << 2.0, 0.0, 1.0,
       0.0, 3.0, 2.0,
       0.0, 0.0, 1.0;

  Eigen::Vector2d x1(1.0, 1.0);
  // H * [1,1,1]^T = [3,5,1]^T -> projected = (3,5)
  Eigen::Vector2d x2(3.0, 5.0);

  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

// Test with perspective homography element affecting normalization
TEST_F(HomographyErrorTest_140, PerspectiveHomographyElement_140) {
  Eigen::Matrix3d H;
  H << 1.0, 0.0, 0.0,
       0.0, 1.0, 0.0,
       0.5, 0.0, 1.0;

  Eigen::Vector2d x1(2.0, 3.0);
  // H * [2,3,1]^T = [2,3,2]^T -> projected = (1, 1.5)
  Eigen::Vector2d x2(1.0, 1.5);

  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

// Test that error is the squared distance
TEST_F(HomographyErrorTest_140, ErrorIsSquaredDistance_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(0.0, 0.0);
  Eigen::Vector2d x2(3.0, 4.0);

  double error = glomap::HomographyError(H, x1, x2);
  // Expected: (0-3)^2 + (0-4)^2 = 9 + 16 = 25
  EXPECT_NEAR(error, 25.0, 1e-10);
}

// Test with homography where third coordinate of result is near zero (boundary case with EPS)
TEST_F(HomographyErrorTest_140, NearZeroThirdCoordinate_140) {
  Eigen::Matrix3d H;
  H << 1.0, 0.0, 0.0,
       0.0, 1.0, 0.0,
       0.0, 0.0, 0.0;  // Third row zeroed except it will use EPS

  Eigen::Vector2d x1(1.0, 1.0);
  // H * [1,1,1]^T = [1,1,0]^T -> divided by (EPS + 0) = EPS
  // projected = (1/EPS, 1/EPS) which will be very large

  double error = glomap::HomographyError(H, x1, x2);
  // Just verify it doesn't crash and returns something finite (well, it could be very large)
  // Actually this test needs x2 defined
  Eigen::Vector2d x2_local(0.0, 0.0);
  double error2 = glomap::HomographyError(H, x1, x2_local);
  EXPECT_GT(error2, 0.0);
}

// Test symmetry: error(H, x1, x2) is not necessarily equal to error(H, x2, x1)
TEST_F(HomographyErrorTest_140, AsymmetryCheck_140) {
  Eigen::Matrix3d H;
  H << 2.0, 0.0, 1.0,
       0.0, 1.0, 0.0,
       0.0, 0.0, 1.0;

  Eigen::Vector2d x1(1.0, 0.0);
  Eigen::Vector2d x2(0.0, 0.0);

  double error_forward = glomap::HomographyError(H, x1, x2);
  double error_backward = glomap::HomographyError(H, x2, x1);

  // These should generally not be equal for a non-identity H
  // H*[1,0,1]^T = [3,0,1]^T -> (3,0), error = 9
  EXPECT_NEAR(error_forward, 9.0, 1e-10);
  // H*[0,0,1]^T = [1,0,1]^T -> (1,0), error to (-1,0)... wait x2 is (1,0)
  // Actually error_backward: H*[0,0,1]^T = [1,0,1] -> (1,0), x2=(1,0) -> error=(1-1)^2+(0-0)^2=0
  // No, x2 in backward call is x1 from forward = (1,0)
  EXPECT_NEAR(error_backward, 0.0, 1e-10);
}

// Fix the near-zero test (previous one had a compilation issue)
TEST_F(HomographyErrorTest_140, NearZeroThirdCoordinateCorrected_140) {
  Eigen::Matrix3d H;
  H << 1.0, 0.0, 0.0,
       0.0, 1.0, 0.0,
       0.0, 0.0, 0.0;

  Eigen::Vector2d x1(1.0, 1.0);
  Eigen::Vector2d x2(0.0, 0.0);

  // H * [1,1,1]^T = [1,1,0]^T -> divided by (EPS + 0) which is very small
  // This should produce a very large error
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_GT(error, 1e10);  // Should be enormous due to division by EPS
}
#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Dense>

namespace glomap {
extern const double EPS;
double HomographyError(const Eigen::Matrix3d& H,
                       const Eigen::Vector2d& x1,
                       const Eigen::Vector2d& x2);
}

class HomographyErrorTest_140 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

TEST_F(HomographyErrorTest_140, IdentityHomographySamePoints_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(1.0, 2.0);
  Eigen::Vector2d x2(1.0, 2.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

TEST_F(HomographyErrorTest_140, IdentityHomographyDifferentPoints_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(1.0, 0.0);
  Eigen::Vector2d x2(2.0, 0.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 1.0, 1e-10);
}

TEST_F(HomographyErrorTest_140, ZeroPoints_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(0.0, 0.0);
  Eigen::Vector2d x2(0.0, 0.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

TEST_F(HomographyErrorTest_140, TranslationHomographyMatch_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  H(0, 2) = 3.0;
  H(1, 2) = 4.0;
  Eigen::Vector2d x1(0.0, 0.0);
  Eigen::Vector2d x2(3.0, 4.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

TEST_F(HomographyErrorTest_140, TranslationHomographyMismatch_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  H(0, 2) = 3.0;
  H(1, 2) = 4.0;
  Eigen::Vector2d x1(0.0, 0.0);
  Eigen::Vector2d x2(0.0, 0.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 25.0, 1e-10);
}

TEST_F(HomographyErrorTest_140, ScalingHomography_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  H(0, 0) = 2.0;
  H(1, 1) = 2.0;
  Eigen::Vector2d x1(1.0, 1.0);
  Eigen::Vector2d x2(2.0, 2.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

TEST_F(HomographyErrorTest_140, PerspectiveDivision_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  H(2, 2) = 2.0;
  Eigen::Vector2d x1(4.0, 6.0);
  Eigen::Vector2d x2(2.0, 3.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

TEST_F(HomographyErrorTest_140, NegativeCoordinates_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(-3.0, -4.0);
  Eigen::Vector2d x2(-3.0, -4.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

TEST_F(HomographyErrorTest_140, ErrorIsNonNegative_140) {
  Eigen::Matrix3d H;
  H << 1.5, 0.3, -0.2,
       0.1, 2.0, 0.5,
       0.01, -0.02, 1.0;
  Eigen::Vector2d x1(5.0, -3.0);
  Eigen::Vector2d x2(10.0, 20.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_GE(error, 0.0);
}

TEST_F(HomographyErrorTest_140, RotationHomography90Degrees_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  H(0, 0) = 0.0;
  H(0, 1) = -1.0;
  H(1, 0) = 1.0;
  H(1, 1) = 0.0;
  Eigen::Vector2d x1(1.0, 0.0);
  Eigen::Vector2d x2(0.0, 1.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

TEST_F(HomographyErrorTest_140, LargeCoordinates_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(1e6, 1e6);
  Eigen::Vector2d x2(1e6, 1e6);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-4);
}

TEST_F(HomographyErrorTest_140, VerySmallCoordinates_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(1e-10, 1e-10);
  Eigen::Vector2d x2(1e-10, 1e-10);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-15);
}

TEST_F(HomographyErrorTest_140, GeneralHomographyKnownResult_140) {
  Eigen::Matrix3d H;
  H << 2.0, 0.0, 1.0,
       0.0, 3.0, 2.0,
       0.0, 0.0, 1.0;
  Eigen::Vector2d x1(1.0, 1.0);
  Eigen::Vector2d x2(3.0, 5.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

TEST_F(HomographyErrorTest_140, PerspectiveHomographyRow_140) {
  Eigen::Matrix3d H;
  H << 1.0, 0.0, 0.0,
       0.0, 1.0, 0.0,
       0.5, 0.0, 1.0;
  Eigen::Vector2d x1(2.0, 3.0);
  Eigen::Vector2d x2(1.0, 1.5);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 0.0, 1e-10);
}

TEST_F(HomographyErrorTest_140, ErrorIsSquaredDistance_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(0.0, 0.0);
  Eigen::Vector2d x2(3.0, 4.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_NEAR(error, 25.0, 1e-10);
}

TEST_F(HomographyErrorTest_140, NearZeroThirdCoordinate_140) {
  Eigen::Matrix3d H;
  H << 1.0, 0.0, 0.0,
       0.0, 1.0, 0.0,
       0.0, 0.0, 0.0;
  Eigen::Vector2d x1(1.0, 1.0);
  Eigen::Vector2d x2(0.0, 0.0);
  double error = glomap::HomographyError(H, x1, x2);
  EXPECT_GT(error, 1e10);
}

TEST_F(HomographyErrorTest_140, AsymmetryCheck_140) {
  Eigen::Matrix3d H;
  H << 2.0, 0.0, 1.0,
       0.0, 1.0, 0.0,
       0.0, 0.0, 1.0;
  Eigen::Vector2d x1(1.0, 0.0);
  Eigen::Vector2d x2(0.0, 0.0);
  double error_forward = glomap::HomographyError(H, x1, x2);
  double error_backward = glomap::HomographyError(H, x2, x1);
  // H*[1,0,1]^T = [3,0,1]^T -> (3,0), error to (0,0) = 9
  EXPECT_NEAR(error_forward, 9.0, 1e-10);
  // H*[0,0,1]^T = [1,0,1]^T -> (1,0), error to (1,0) = 0
  EXPECT_NEAR(error_backward, 0.0, 1e-10);
}

TEST_F(HomographyErrorTest_140, ScaledHomographyEquivalence_140) {
  // A homography scaled by a constant should give the same result
  // because of the perspective division
  Eigen::Matrix3d H;
  H << 1.0, 0.5, 0.2,
       0.3, 1.0, 0.1,
       0.0, 0.0, 1.0;
  Eigen::Matrix3d H_scaled = 5.0 * H;

  Eigen::Vector2d x1(2.0, 3.0);
  Eigen::Vector2d x2(1.0, 1.0);

  double error1 = glomap::HomographyError(H, x1, x2);
  double error2 = glomap::HomographyError(H_scaled, x1, x2);
  EXPECT_NEAR(error1, error2, 1e-10);
}

TEST_F(HomographyErrorTest_140, ZeroHomographyMatrix_140) {
  // All zeros: Hx1 = [0,0,0], division by EPS
  Eigen::Matrix3d H = Eigen::Matrix3d::Zero();
  Eigen::Vector2d x1(1.0, 1.0);
  Eigen::Vector2d x2(0.0, 0.0);
  double error = glomap::HomographyError(H, x1, x2);
  // [0,0,0] -> (0/EPS, 0/EPS) = (0,0), error to (0,0) = 0
  EXPECT_NEAR(error, 0.0, 1e-10);
}

TEST_F(HomographyErrorTest_140, OnlyXComponentDifference_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(5.0, 3.0);
  Eigen::Vector2d x2(7.0, 3.0);
  double error = glomap::HomographyError(H, x1, x2);
  // (5-7)^2 + (3-3)^2 = 4
  EXPECT_NEAR(error, 4.0, 1e-10);
}

TEST_F(HomographyErrorTest_140, OnlyYComponentDifference_140) {
  Eigen::Matrix3d H = Eigen::Matrix3d::Identity();
  Eigen::Vector2d x1(3.0, 1.0);
  Eigen::Vector2d x2(3.0, 4.0);
  double error = glomap::HomographyError(H, x1, x2);
  // (3-3)^2 + (1-4)^2 = 9
  EXPECT_NEAR(error, 9.0, 1e-10);
}
