#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include "glomap/estimators/cost_function.h"

namespace glomap {
namespace {

class FetzerFocalLengthSameCameraCostTest_164 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test construction with identity fundamental matrix and zero principal point
TEST_F(FetzerFocalLengthSameCameraCostTest_164, ConstructWithIdentityFAndZeroPP_164) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
  Eigen::Vector2d pp(0.0, 0.0);

  EXPECT_NO_THROW({
    FetzerFocalLengthSameCameraCost cost(F, pp);
  });
}

// Test construction with zero fundamental matrix
TEST_F(FetzerFocalLengthSameCameraCostTest_164, ConstructWithZeroF_164) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
  Eigen::Vector2d pp(0.0, 0.0);

  EXPECT_NO_THROW({
    FetzerFocalLengthSameCameraCost cost(F, pp);
  });
}

// Test construction with non-zero principal point
TEST_F(FetzerFocalLengthSameCameraCostTest_164, ConstructWithNonZeroPP_164) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
  Eigen::Vector2d pp(320.0, 240.0);

  EXPECT_NO_THROW({
    FetzerFocalLengthSameCameraCost cost(F, pp);
  });
}

// Test construction with a typical fundamental matrix (rank-2)
TEST_F(FetzerFocalLengthSameCameraCostTest_164, ConstructWithTypicalFundamentalMatrix_164) {
  // Construct a rank-2 fundamental matrix
  Eigen::Matrix3d F;
  F << 0.0, 0.0, 0.0,
       0.0, 0.0, -1.0,
       0.0, 1.0, 0.0;
  Eigen::Vector2d pp(320.0, 240.0);

  EXPECT_NO_THROW({
    FetzerFocalLengthSameCameraCost cost(F, pp);
  });
}

// Test construction with negative principal point values
TEST_F(FetzerFocalLengthSameCameraCostTest_164, ConstructWithNegativePP_164) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
  Eigen::Vector2d pp(-100.0, -200.0);

  EXPECT_NO_THROW({
    FetzerFocalLengthSameCameraCost cost(F, pp);
  });
}

// Test construction with large values in fundamental matrix
TEST_F(FetzerFocalLengthSameCameraCostTest_164, ConstructWithLargeValues_164) {
  Eigen::Matrix3d F;
  F << 1e10, 2e10, 3e10,
       4e10, 5e10, 6e10,
       7e10, 8e10, 9e10;
  Eigen::Vector2d pp(1e5, 1e5);

  EXPECT_NO_THROW({
    FetzerFocalLengthSameCameraCost cost(F, pp);
  });
}

// Test construction with very small values in fundamental matrix
TEST_F(FetzerFocalLengthSameCameraCostTest_164, ConstructWithSmallValues_164) {
  Eigen::Matrix3d F;
  F << 1e-15, 2e-15, 3e-15,
       4e-15, 5e-15, 6e-15,
       7e-15, 8e-15, 9e-15;
  Eigen::Vector2d pp(0.5, 0.5);

  EXPECT_NO_THROW({
    FetzerFocalLengthSameCameraCost cost(F, pp);
  });
}

// Test construction with a realistic fundamental matrix scenario
TEST_F(FetzerFocalLengthSameCameraCostTest_164, ConstructWithRealisticScenario_164) {
  // A more realistic fundamental matrix
  Eigen::Matrix3d F;
  F << 2.34e-7, -1.45e-5, 3.21e-3,
       1.56e-5, 4.78e-7, -8.92e-3,
       -2.67e-3, 7.89e-3, 1.0;
  Eigen::Vector2d pp(640.0, 480.0);

  EXPECT_NO_THROW({
    FetzerFocalLengthSameCameraCost cost(F, pp);
  });
}

// Test construction with symmetric fundamental matrix
TEST_F(FetzerFocalLengthSameCameraCostTest_164, ConstructWithSymmetricF_164) {
  Eigen::Matrix3d F;
  F << 1.0, 2.0, 3.0,
       2.0, 4.0, 5.0,
       3.0, 5.0, 6.0;
  Eigen::Vector2d pp(0.0, 0.0);

  EXPECT_NO_THROW({
    FetzerFocalLengthSameCameraCost cost(F, pp);
  });
}

// Test construction with anti-symmetric fundamental matrix
TEST_F(FetzerFocalLengthSameCameraCostTest_164, ConstructWithAntiSymmetricF_164) {
  Eigen::Matrix3d F;
  F << 0.0, 1.0, -2.0,
       -1.0, 0.0, 3.0,
       2.0, -3.0, 0.0;
  Eigen::Vector2d pp(100.0, 100.0);

  EXPECT_NO_THROW({
    FetzerFocalLengthSameCameraCost cost(F, pp);
  });
}

// Test that multiple instances can be created independently
TEST_F(FetzerFocalLengthSameCameraCostTest_164, MultipleInstancesIndependent_164) {
  Eigen::Matrix3d F1 = Eigen::Matrix3d::Identity();
  Eigen::Matrix3d F2 = Eigen::Matrix3d::Zero();
  Eigen::Vector2d pp1(0.0, 0.0);
  Eigen::Vector2d pp2(320.0, 240.0);

  EXPECT_NO_THROW({
    FetzerFocalLengthSameCameraCost cost1(F1, pp1);
    FetzerFocalLengthSameCameraCost cost2(F2, pp2);
  });
}

// Test construction with diagonal fundamental matrix
TEST_F(FetzerFocalLengthSameCameraCostTest_164, ConstructWithDiagonalF_164) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
  F(0, 0) = 1.0;
  F(1, 1) = 2.0;
  F(2, 2) = 3.0;
  Eigen::Vector2d pp(256.0, 256.0);

  EXPECT_NO_THROW({
    FetzerFocalLengthSameCameraCost cost(F, pp);
  });
}

}  // namespace
}  // namespace glomap
