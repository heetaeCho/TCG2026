#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <ceres/ceres.h>
#include "glomap/estimators/cost_function.h"

namespace glomap {
namespace {

class FetzerFocalLengthSameCameraCostTest_168 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Default principal point at image center
    principal_point_ = Eigen::Vector2d(320.0, 240.0);
  }

  Eigen::Vector2d principal_point_;
};

// Test that the constructor does not crash with an identity fundamental matrix
TEST_F(FetzerFocalLengthSameCameraCostTest_168, ConstructWithIdentityMatrix_168) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
  EXPECT_NO_THROW(FetzerFocalLengthSameCameraCost(F, principal_point_));
}

// Test that the constructor does not crash with a zero fundamental matrix
TEST_F(FetzerFocalLengthSameCameraCostTest_168, ConstructWithZeroMatrix_168) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
  EXPECT_NO_THROW(FetzerFocalLengthSameCameraCost(F, principal_point_));
}

// Test construction with a zero principal point
TEST_F(FetzerFocalLengthSameCameraCostTest_168, ConstructWithZeroPrincipalPoint_168) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
  Eigen::Vector2d pp(0.0, 0.0);
  EXPECT_NO_THROW(FetzerFocalLengthSameCameraCost(F, pp));
}

// Test construction with negative principal point values
TEST_F(FetzerFocalLengthSameCameraCostTest_168, ConstructWithNegativePrincipalPoint_168) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
  Eigen::Vector2d pp(-100.0, -200.0);
  EXPECT_NO_THROW(FetzerFocalLengthSameCameraCost(F, pp));
}

// Test construction with a typical fundamental matrix
TEST_F(FetzerFocalLengthSameCameraCostTest_168, ConstructWithTypicalFundamentalMatrix_168) {
  Eigen::Matrix3d F;
  F << 0.0, 0.0, 0.0,
       0.0, 0.0, -1.0,
       0.0, 1.0, 0.0;
  EXPECT_NO_THROW(FetzerFocalLengthSameCameraCost(F, principal_point_));
}

// Test Create returns a non-null cost function
TEST_F(FetzerFocalLengthSameCameraCostTest_168, CreateReturnsNonNull_168) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
  ceres::CostFunction* cost_function =
      FetzerFocalLengthSameCameraCost::Create(F, principal_point_);
  ASSERT_NE(cost_function, nullptr);
  delete cost_function;
}

// Test that the created cost function has the expected number of residuals
TEST_F(FetzerFocalLengthSameCameraCostTest_168, CreateCostFunctionResidualCount_168) {
  Eigen::Matrix3d F;
  F << 0.0, 0.0, 0.0,
       0.0, 0.0, -1.0,
       0.0, 1.0, 0.0;
  ceres::CostFunction* cost_function =
      FetzerFocalLengthSameCameraCost::Create(F, principal_point_);
  ASSERT_NE(cost_function, nullptr);
  // The cost function should have some residuals defined
  EXPECT_GT(cost_function->num_residuals(), 0);
  delete cost_function;
}

// Test that the operator() can be called via Ceres
TEST_F(FetzerFocalLengthSameCameraCostTest_168, EvaluateCostFunction_168) {
  Eigen::Matrix3d F;
  F << 0.0, 0.0, 0.0,
       0.0, 0.0, -1.0,
       0.0, 1.0, 0.0;
  ceres::CostFunction* cost_function =
      FetzerFocalLengthSameCameraCost::Create(F, principal_point_);
  ASSERT_NE(cost_function, nullptr);

  // Use a reasonable focal length
  double focal_length = 500.0;
  const double* parameters[] = {&focal_length};

  int num_residuals = cost_function->num_residuals();
  std::vector<double> residuals(num_residuals);
  std::vector<double> jacobian(num_residuals);
  double* jacobians[] = {jacobian.data()};

  bool success = cost_function->Evaluate(parameters, residuals.data(), jacobians);
  EXPECT_TRUE(success);
  delete cost_function;
}

// Test evaluation with focal length = 1
TEST_F(FetzerFocalLengthSameCameraCostTest_168, EvaluateWithUnitFocalLength_168) {
  Eigen::Matrix3d F;
  F << 0.0, 0.0, 0.0,
       0.0, 0.0, -1.0,
       0.0, 1.0, 0.0;
  ceres::CostFunction* cost_function =
      FetzerFocalLengthSameCameraCost::Create(F, principal_point_);
  ASSERT_NE(cost_function, nullptr);

  double focal_length = 1.0;
  const double* parameters[] = {&focal_length};

  int num_residuals = cost_function->num_residuals();
  std::vector<double> residuals(num_residuals);

  bool success = cost_function->Evaluate(parameters, residuals.data(), nullptr);
  EXPECT_TRUE(success);

  // Residuals should be finite
  for (int i = 0; i < num_residuals; ++i) {
    EXPECT_TRUE(std::isfinite(residuals[i]));
  }
  delete cost_function;
}

// Test evaluation with a very large focal length
TEST_F(FetzerFocalLengthSameCameraCostTest_168, EvaluateWithLargeFocalLength_168) {
  Eigen::Matrix3d F;
  F << 0.0, 0.0, 0.0,
       0.0, 0.0, -1.0,
       0.0, 1.0, 0.0;
  ceres::CostFunction* cost_function =
      FetzerFocalLengthSameCameraCost::Create(F, principal_point_);
  ASSERT_NE(cost_function, nullptr);

  double focal_length = 1e6;
  const double* parameters[] = {&focal_length};

  int num_residuals = cost_function->num_residuals();
  std::vector<double> residuals(num_residuals);

  bool success = cost_function->Evaluate(parameters, residuals.data(), nullptr);
  EXPECT_TRUE(success);
  delete cost_function;
}

// Test evaluation with a very small positive focal length
TEST_F(FetzerFocalLengthSameCameraCostTest_168, EvaluateWithSmallFocalLength_168) {
  Eigen::Matrix3d F;
  F << 0.0, 0.0, 0.0,
       0.0, 0.0, -1.0,
       0.0, 1.0, 0.0;
  ceres::CostFunction* cost_function =
      FetzerFocalLengthSameCameraCost::Create(F, principal_point_);
  ASSERT_NE(cost_function, nullptr);

  double focal_length = 1e-6;
  const double* parameters[] = {&focal_length};

  int num_residuals = cost_function->num_residuals();
  std::vector<double> residuals(num_residuals);

  bool success = cost_function->Evaluate(parameters, residuals.data(), nullptr);
  EXPECT_TRUE(success);
  delete cost_function;
}

// Test that the parameter block sizes are correct (should take 1 parameter for focal length)
TEST_F(FetzerFocalLengthSameCameraCostTest_168, ParameterBlockSizes_168) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
  ceres::CostFunction* cost_function =
      FetzerFocalLengthSameCameraCost::Create(F, principal_point_);
  ASSERT_NE(cost_function, nullptr);

  const std::vector<int32_t>& block_sizes = cost_function->parameter_block_sizes();
  EXPECT_EQ(block_sizes.size(), 1u);
  EXPECT_EQ(block_sizes[0], 1);
  delete cost_function;
}

// Test construction with a random fundamental matrix
TEST_F(FetzerFocalLengthSameCameraCostTest_168, ConstructWithRandomMatrix_168) {
  Eigen::Matrix3d F;
  F << 1.23e-7, -3.45e-6, 2.1e-3,
       4.56e-6, 7.89e-8, -1.5e-2,
       -3.2e-3, 1.8e-2, 1.0;
  EXPECT_NO_THROW(FetzerFocalLengthSameCameraCost(F, principal_point_));
}

// Test that different fundamental matrices produce different residuals
TEST_F(FetzerFocalLengthSameCameraCostTest_168, DifferentFMatricesProduceDifferentResiduals_168) {
  Eigen::Matrix3d F1;
  F1 << 0.0, 0.0, 0.0,
        0.0, 0.0, -1.0,
        0.0, 1.0, 0.0;

  Eigen::Matrix3d F2;
  F2 << 0.0, 0.0, 1.0,
        0.0, 0.0, 0.0,
        -1.0, 0.0, 0.0;

  ceres::CostFunction* cf1 =
      FetzerFocalLengthSameCameraCost::Create(F1, principal_point_);
  ceres::CostFunction* cf2 =
      FetzerFocalLengthSameCameraCost::Create(F2, principal_point_);
  ASSERT_NE(cf1, nullptr);
  ASSERT_NE(cf2, nullptr);

  double focal_length = 500.0;
  const double* parameters[] = {&focal_length};

  int num_res1 = cf1->num_residuals();
  int num_res2 = cf2->num_residuals();
  EXPECT_EQ(num_res1, num_res2);

  std::vector<double> residuals1(num_res1);
  std::vector<double> residuals2(num_res2);

  cf1->Evaluate(parameters, residuals1.data(), nullptr);
  cf2->Evaluate(parameters, residuals2.data(), nullptr);

  // At least one residual should differ
  bool all_same = true;
  for (int i = 0; i < num_res1; ++i) {
    if (std::abs(residuals1[i] - residuals2[i]) > 1e-12) {
      all_same = false;
      break;
    }
  }
  EXPECT_FALSE(all_same);

  delete cf1;
  delete cf2;
}

// Test that different principal points produce different residuals
TEST_F(FetzerFocalLengthSameCameraCostTest_168, DifferentPrincipalPointsProduceDifferentResiduals_168) {
  Eigen::Matrix3d F;
  F << 1e-7, -3e-6, 2e-3,
       4e-6, 7e-8, -1e-2,
       -3e-3, 1e-2, 1.0;

  Eigen::Vector2d pp1(320.0, 240.0);
  Eigen::Vector2d pp2(400.0, 300.0);

  ceres::CostFunction* cf1 =
      FetzerFocalLengthSameCameraCost::Create(F, pp1);
  ceres::CostFunction* cf2 =
      FetzerFocalLengthSameCameraCost::Create(F, pp2);
  ASSERT_NE(cf1, nullptr);
  ASSERT_NE(cf2, nullptr);

  double focal_length = 500.0;
  const double* parameters[] = {&focal_length};

  int num_res = cf1->num_residuals();
  std::vector<double> residuals1(num_res);
  std::vector<double> residuals2(num_res);

  cf1->Evaluate(parameters, residuals1.data(), nullptr);
  cf2->Evaluate(parameters, residuals2.data(), nullptr);

  bool all_same = true;
  for (int i = 0; i < num_res; ++i) {
    if (std::abs(residuals1[i] - residuals2[i]) > 1e-12) {
      all_same = false;
      break;
    }
  }
  EXPECT_FALSE(all_same);

  delete cf1;
  delete cf2;
}

// Test that Create with large principal point values works
TEST_F(FetzerFocalLengthSameCameraCostTest_168, CreateWithLargePrincipalPoint_168) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
  Eigen::Vector2d pp(1e4, 1e4);
  ceres::CostFunction* cost_function =
      FetzerFocalLengthSameCameraCost::Create(F, pp);
  ASSERT_NE(cost_function, nullptr);
  delete cost_function;
}

}  // namespace
}  // namespace glomap
