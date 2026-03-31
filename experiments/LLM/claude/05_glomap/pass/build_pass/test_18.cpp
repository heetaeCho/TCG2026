#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <ceres/ceres.h>
#include "glomap/estimators/cost_function.h"

namespace glomap {
namespace {

class FetzerFocalLengthSameCameraCostTest_18 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test that operator() returns true for a simple identity-like fundamental matrix
TEST_F(FetzerFocalLengthSameCameraCostTest_18, OperatorReturnsTrueWithIdentityF_18) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
  Eigen::Vector2d pp(0.0, 0.0);
  
  FetzerFocalLengthSameCameraCost cost(F, pp);
  
  double fi = 500.0;
  double residuals[2];
  
  bool result = cost(&fi, residuals);
  EXPECT_TRUE(result);
}

// Test with a known fundamental matrix and principal point at origin
TEST_F(FetzerFocalLengthSameCameraCostTest_18, ResidualComputationWithZeroPrincipalPoint_18) {
  Eigen::Matrix3d F;
  F << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;
  Eigen::Vector2d pp(0.0, 0.0);
  
  FetzerFocalLengthSameCameraCost cost(F, pp);
  
  double fi = 1.0;
  double residuals[2];
  
  bool result = cost(&fi, residuals);
  EXPECT_TRUE(result);
  // Residuals should be finite
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// Test with a non-zero principal point
TEST_F(FetzerFocalLengthSameCameraCostTest_18, ResidualComputationWithNonZeroPrincipalPoint_18) {
  Eigen::Matrix3d F;
  F << 0.001, 0.002, 0.003,
       0.004, 0.005, 0.006,
       0.007, 0.008, 0.009;
  Eigen::Vector2d pp(320.0, 240.0);
  
  FetzerFocalLengthSameCameraCost cost(F, pp);
  
  double fi = 800.0;
  double residuals[2];
  
  bool result = cost(&fi, residuals);
  EXPECT_TRUE(result);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// Test with a very large focal length
TEST_F(FetzerFocalLengthSameCameraCostTest_18, LargeFocalLength_18) {
  Eigen::Matrix3d F;
  F << 1e-8, 2e-8, 3e-8,
       4e-8, 5e-8, 6e-8,
       7e-8, 8e-8, 9e-8;
  Eigen::Vector2d pp(500.0, 500.0);
  
  FetzerFocalLengthSameCameraCost cost(F, pp);
  
  double fi = 1e6;
  double residuals[2];
  
  bool result = cost(&fi, residuals);
  EXPECT_TRUE(result);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// Test with a very small focal length
TEST_F(FetzerFocalLengthSameCameraCostTest_18, SmallFocalLength_18) {
  Eigen::Matrix3d F;
  F << 0.1, 0.2, 0.3,
       0.4, 0.5, 0.6,
       0.7, 0.8, 0.9;
  Eigen::Vector2d pp(100.0, 100.0);
  
  FetzerFocalLengthSameCameraCost cost(F, pp);
  
  double fi = 1e-3;
  double residuals[2];
  
  bool result = cost(&fi, residuals);
  EXPECT_TRUE(result);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// Test that Create returns a valid CostFunction pointer
TEST_F(FetzerFocalLengthSameCameraCostTest_18, CreateReturnsCostFunction_18) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
  Eigen::Vector2d pp(320.0, 240.0);
  
  ceres::CostFunction* cost_function = FetzerFocalLengthSameCameraCost::Create(F, pp);
  EXPECT_NE(cost_function, nullptr);
  
  // Verify the cost function has the right number of residuals and parameter blocks
  EXPECT_EQ(cost_function->num_residuals(), 2);
  
  std::vector<int32_t> param_sizes = cost_function->parameter_block_sizes();
  EXPECT_EQ(param_sizes.size(), 1);
  EXPECT_EQ(param_sizes[0], 1);
  
  delete cost_function;
}

// Test that the created cost function can be evaluated
TEST_F(FetzerFocalLengthSameCameraCostTest_18, CreateAndEvaluate_18) {
  Eigen::Matrix3d F;
  F << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;
  Eigen::Vector2d pp(0.0, 0.0);
  
  ceres::CostFunction* cost_function = FetzerFocalLengthSameCameraCost::Create(F, pp);
  ASSERT_NE(cost_function, nullptr);
  
  double fi = 500.0;
  double residuals[2];
  double jacobian[2];  // 2 residuals x 1 parameter
  
  const double* parameters[] = {&fi};
  double* jacobians[] = {jacobian};
  
  bool success = cost_function->Evaluate(parameters, residuals, jacobians);
  EXPECT_TRUE(success);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
  EXPECT_TRUE(std::isfinite(jacobian[0]));
  EXPECT_TRUE(std::isfinite(jacobian[1]));
  
  delete cost_function;
}

// Test with zero fundamental matrix
TEST_F(FetzerFocalLengthSameCameraCostTest_18, ZeroFundamentalMatrix_18) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
  Eigen::Vector2d pp(0.0, 0.0);
  
  FetzerFocalLengthSameCameraCost cost(F, pp);
  
  double fi = 500.0;
  double residuals[2];
  
  bool result = cost(&fi, residuals);
  EXPECT_TRUE(result);
  // With zero F, the denominators would be zero, triggering the 1e-6 fallback
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// Test that the same focal length applied twice gives consistent results
TEST_F(FetzerFocalLengthSameCameraCostTest_18, ConsistentResults_18) {
  Eigen::Matrix3d F;
  F << 0.001, 0.002, 0.003,
       0.004, 0.005, 0.006,
       0.007, 0.008, 0.010;
  Eigen::Vector2d pp(320.0, 240.0);
  
  FetzerFocalLengthSameCameraCost cost(F, pp);
  
  double fi = 600.0;
  double residuals1[2];
  double residuals2[2];
  
  cost(&fi, residuals1);
  cost(&fi, residuals2);
  
  EXPECT_DOUBLE_EQ(residuals1[0], residuals2[0]);
  EXPECT_DOUBLE_EQ(residuals1[1], residuals2[1]);
}

// Test that different focal lengths produce different residuals
TEST_F(FetzerFocalLengthSameCameraCostTest_18, DifferentFocalLengthsDifferentResiduals_18) {
  Eigen::Matrix3d F;
  F << 0.001, 0.002, 0.003,
       0.004, 0.005, 0.006,
       0.007, 0.008, 0.010;
  Eigen::Vector2d pp(320.0, 240.0);
  
  FetzerFocalLengthSameCameraCost cost(F, pp);
  
  double fi1 = 500.0;
  double fi2 = 1000.0;
  double residuals1[2];
  double residuals2[2];
  
  cost(&fi1, residuals1);
  cost(&fi2, residuals2);
  
  // At least one residual should differ
  bool differs = (residuals1[0] != residuals2[0]) || (residuals1[1] != residuals2[1]);
  EXPECT_TRUE(differs);
}

// Test using the cost function in a simple Ceres problem
TEST_F(FetzerFocalLengthSameCameraCostTest_18, CeresOptimization_18) {
  Eigen::Matrix3d F;
  F << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;
  Eigen::Vector2d pp(0.0, 0.0);
  
  double focal_length = 100.0;
  
  ceres::Problem problem;
  problem.AddResidualBlock(
      FetzerFocalLengthSameCameraCost::Create(F, pp),
      nullptr,
      &focal_length);
  
  ceres::Solver::Options options;
  options.max_num_iterations = 100;
  options.linear_solver_type = ceres::DENSE_QR;
  
  ceres::Solver::Summary summary;
  ceres::Solve(options, &problem, &summary);
  
  // Simply check that the optimization ran without issues
  EXPECT_TRUE(summary.IsSolutionUsable());
  EXPECT_TRUE(std::isfinite(focal_length));
}

// Test with negative focal length (edge case)
TEST_F(FetzerFocalLengthSameCameraCostTest_18, NegativeFocalLength_18) {
  Eigen::Matrix3d F;
  F << 0.001, 0.002, 0.003,
       0.004, 0.005, 0.006,
       0.007, 0.008, 0.009;
  Eigen::Vector2d pp(320.0, 240.0);
  
  FetzerFocalLengthSameCameraCost cost(F, pp);
  
  double fi = -500.0;
  double residuals[2];
  
  bool result = cost(&fi, residuals);
  EXPECT_TRUE(result);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// Test with focal length of 1.0 (unit focal length)
TEST_F(FetzerFocalLengthSameCameraCostTest_18, UnitFocalLength_18) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
  Eigen::Vector2d pp(0.0, 0.0);
  
  FetzerFocalLengthSameCameraCost cost(F, pp);
  
  double fi = 1.0;
  double residuals[2];
  
  bool result = cost(&fi, residuals);
  EXPECT_TRUE(result);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

}  // namespace
}  // namespace glomap
