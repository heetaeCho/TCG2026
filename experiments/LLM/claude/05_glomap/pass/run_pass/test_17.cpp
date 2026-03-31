#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <ceres/ceres.h>
#include "glomap/estimators/cost_function.h"

namespace glomap {
namespace {

class FetzerFocalLengthCostTest_17 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Identity-like fundamental matrix
    identity_F_ = Eigen::Matrix3d::Identity();
    
    // A more realistic fundamental matrix
    realistic_F_ << 0.0, -0.1, 0.05,
                     0.1, 0.0, -0.02,
                    -0.04, 0.03, 0.0;
    
    zero_pp_ = Eigen::Vector2d::Zero();
    nonzero_pp_ = Eigen::Vector2d(320.0, 240.0);
  }

  Eigen::Matrix3d identity_F_;
  Eigen::Matrix3d realistic_F_;
  Eigen::Vector2d zero_pp_;
  Eigen::Vector2d nonzero_pp_;
};

// Test that operator() returns true with identity fundamental matrix and zero principal points
TEST_F(FetzerFocalLengthCostTest_17, OperatorReturnsTrueIdentityF_17) {
  FetzerFocalLengthCost cost(identity_F_, zero_pp_, zero_pp_);
  
  double fi = 500.0;
  double fj = 500.0;
  double residuals[2];
  
  bool result = cost(&fi, &fj, residuals);
  EXPECT_TRUE(result);
}

// Test that operator() returns true with realistic fundamental matrix
TEST_F(FetzerFocalLengthCostTest_17, OperatorReturnsTrueRealisticF_17) {
  FetzerFocalLengthCost cost(realistic_F_, nonzero_pp_, nonzero_pp_);
  
  double fi = 800.0;
  double fj = 600.0;
  double residuals[2];
  
  bool result = cost(&fi, &fj, residuals);
  EXPECT_TRUE(result);
}

// Test that residuals are finite with normal inputs
TEST_F(FetzerFocalLengthCostTest_17, ResidualsAreFiniteNormalInputs_17) {
  FetzerFocalLengthCost cost(realistic_F_, nonzero_pp_, nonzero_pp_);
  
  double fi = 500.0;
  double fj = 500.0;
  double residuals[2];
  
  cost(&fi, &fj, residuals);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// Test with equal focal lengths
TEST_F(FetzerFocalLengthCostTest_17, EqualFocalLengths_17) {
  FetzerFocalLengthCost cost(realistic_F_, zero_pp_, zero_pp_);
  
  double fi = 1000.0;
  double fj = 1000.0;
  double residuals[2];
  
  bool result = cost(&fi, &fj, residuals);
  EXPECT_TRUE(result);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// Test with different focal lengths
TEST_F(FetzerFocalLengthCostTest_17, DifferentFocalLengths_17) {
  FetzerFocalLengthCost cost(realistic_F_, nonzero_pp_, nonzero_pp_);
  
  double fi = 300.0;
  double fj = 900.0;
  double residuals[2];
  
  bool result = cost(&fi, &fj, residuals);
  EXPECT_TRUE(result);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// Test with very small focal lengths (boundary condition)
TEST_F(FetzerFocalLengthCostTest_17, VerySmallFocalLengths_17) {
  FetzerFocalLengthCost cost(realistic_F_, zero_pp_, zero_pp_);
  
  double fi = 1e-3;
  double fj = 1e-3;
  double residuals[2];
  
  bool result = cost(&fi, &fj, residuals);
  EXPECT_TRUE(result);
  // Residuals should still be finite due to the epsilon guard
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// Test with very large focal lengths
TEST_F(FetzerFocalLengthCostTest_17, VeryLargeFocalLengths_17) {
  FetzerFocalLengthCost cost(realistic_F_, zero_pp_, zero_pp_);
  
  double fi = 1e6;
  double fj = 1e6;
  double residuals[2];
  
  bool result = cost(&fi, &fj, residuals);
  EXPECT_TRUE(result);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// Test with asymmetric principal points
TEST_F(FetzerFocalLengthCostTest_17, AsymmetricPrincipalPoints_17) {
  Eigen::Vector2d pp0(100.0, 200.0);
  Eigen::Vector2d pp1(300.0, 400.0);
  FetzerFocalLengthCost cost(realistic_F_, pp0, pp1);
  
  double fi = 500.0;
  double fj = 600.0;
  double residuals[2];
  
  bool result = cost(&fi, &fj, residuals);
  EXPECT_TRUE(result);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// Test that changing fi affects residuals
TEST_F(FetzerFocalLengthCostTest_17, ChangingFiAffectsResiduals_17) {
  FetzerFocalLengthCost cost(realistic_F_, nonzero_pp_, nonzero_pp_);
  
  double fi1 = 400.0;
  double fi2 = 800.0;
  double fj = 500.0;
  double residuals1[2];
  double residuals2[2];
  
  cost(&fi1, &fj, residuals1);
  cost(&fi2, &fj, residuals2);
  
  // At least one residual should differ when fi changes
  bool differs = (residuals1[0] != residuals2[0]) || (residuals1[1] != residuals2[1]);
  EXPECT_TRUE(differs);
}

// Test that changing fj affects residuals
TEST_F(FetzerFocalLengthCostTest_17, ChangingFjAffectsResiduals_17) {
  FetzerFocalLengthCost cost(realistic_F_, nonzero_pp_, nonzero_pp_);
  
  double fi = 500.0;
  double fj1 = 400.0;
  double fj2 = 800.0;
  double residuals1[2];
  double residuals2[2];
  
  cost(&fi, &fj1, residuals1);
  cost(&fi, &fj2, residuals2);
  
  bool differs = (residuals1[0] != residuals2[0]) || (residuals1[1] != residuals2[1]);
  EXPECT_TRUE(differs);
}

// Test the Create static method returns a valid cost function
TEST_F(FetzerFocalLengthCostTest_17, CreateReturnsValidCostFunction_17) {
  ceres::CostFunction* cost_function = 
      FetzerFocalLengthCost::Create(realistic_F_, nonzero_pp_, nonzero_pp_);
  
  ASSERT_NE(cost_function, nullptr);
  
  // The cost function should have 2 residuals and 2 parameter blocks of size 1
  EXPECT_EQ(cost_function->num_residuals(), 2);
  
  const std::vector<int32_t>& param_sizes = cost_function->parameter_block_sizes();
  ASSERT_EQ(param_sizes.size(), 2);
  EXPECT_EQ(param_sizes[0], 1);
  EXPECT_EQ(param_sizes[1], 1);
  
  delete cost_function;
}

// Test the Create method cost function produces finite residuals
TEST_F(FetzerFocalLengthCostTest_17, CreateCostFunctionProducesFiniteResiduals_17) {
  ceres::CostFunction* cost_function = 
      FetzerFocalLengthCost::Create(realistic_F_, nonzero_pp_, nonzero_pp_);
  
  ASSERT_NE(cost_function, nullptr);
  
  double fi = 500.0;
  double fj = 600.0;
  double residuals[2];
  double* parameters[2] = {&fi, &fj};
  
  bool result = cost_function->Evaluate(parameters, residuals, nullptr);
  EXPECT_TRUE(result);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
  
  delete cost_function;
}

// Test the Create method cost function also provides valid Jacobians
TEST_F(FetzerFocalLengthCostTest_17, CreateCostFunctionProvidesJacobians_17) {
  ceres::CostFunction* cost_function = 
      FetzerFocalLengthCost::Create(realistic_F_, nonzero_pp_, nonzero_pp_);
  
  ASSERT_NE(cost_function, nullptr);
  
  double fi = 500.0;
  double fj = 600.0;
  double residuals[2];
  double jacobian_fi[2];
  double jacobian_fj[2];
  double* parameters[2] = {&fi, &fj};
  double* jacobians[2] = {jacobian_fi, jacobian_fj};
  
  bool result = cost_function->Evaluate(parameters, residuals, jacobians);
  EXPECT_TRUE(result);
  
  // Jacobians should be finite
  for (int i = 0; i < 2; ++i) {
    EXPECT_TRUE(std::isfinite(jacobian_fi[i]));
    EXPECT_TRUE(std::isfinite(jacobian_fj[i]));
  }
  
  delete cost_function;
}

// Test with zero fundamental matrix
TEST_F(FetzerFocalLengthCostTest_17, ZeroFundamentalMatrix_17) {
  Eigen::Matrix3d zero_F = Eigen::Matrix3d::Zero();
  FetzerFocalLengthCost cost(zero_F, zero_pp_, zero_pp_);
  
  double fi = 500.0;
  double fj = 500.0;
  double residuals[2];
  
  bool result = cost(&fi, &fj, residuals);
  EXPECT_TRUE(result);
  // The epsilon guard should prevent division by zero
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// Test consistency: same inputs produce same outputs
TEST_F(FetzerFocalLengthCostTest_17, ConsistentResults_17) {
  FetzerFocalLengthCost cost(realistic_F_, nonzero_pp_, nonzero_pp_);
  
  double fi = 700.0;
  double fj = 800.0;
  double residuals1[2];
  double residuals2[2];
  
  cost(&fi, &fj, residuals1);
  cost(&fi, &fj, residuals2);
  
  EXPECT_DOUBLE_EQ(residuals1[0], residuals2[0]);
  EXPECT_DOUBLE_EQ(residuals1[1], residuals2[1]);
}

// Test with negative focal lengths (mathematically valid in the formula)
TEST_F(FetzerFocalLengthCostTest_17, NegativeFocalLengths_17) {
  FetzerFocalLengthCost cost(realistic_F_, nonzero_pp_, nonzero_pp_);
  
  double fi = -500.0;
  double fj = -600.0;
  double residuals[2];
  
  bool result = cost(&fi, &fj, residuals);
  EXPECT_TRUE(result);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// Test that focal length of 1.0 works (small but nonzero)
TEST_F(FetzerFocalLengthCostTest_17, UnitFocalLength_17) {
  FetzerFocalLengthCost cost(realistic_F_, zero_pp_, zero_pp_);
  
  double fi = 1.0;
  double fj = 1.0;
  double residuals[2];
  
  bool result = cost(&fi, &fj, residuals);
  EXPECT_TRUE(result);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// Test with same principal points for both cameras
TEST_F(FetzerFocalLengthCostTest_17, SamePrincipalPoints_17) {
  Eigen::Vector2d pp(640.0, 480.0);
  FetzerFocalLengthCost cost(realistic_F_, pp, pp);
  
  double fi = 500.0;
  double fj = 500.0;
  double residuals[2];
  
  bool result = cost(&fi, &fj, residuals);
  EXPECT_TRUE(result);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// Test residuals have exactly 2 components (no buffer overflow concerns)
TEST_F(FetzerFocalLengthCostTest_17, ExactlyTwoResiduals_17) {
  FetzerFocalLengthCost cost(realistic_F_, nonzero_pp_, nonzero_pp_);
  
  double fi = 500.0;
  double fj = 600.0;
  // Initialize with sentinel values
  double residuals[3] = {-999.0, -999.0, -999.0};
  
  cost(&fi, &fj, residuals);
  
  // The third element should remain untouched
  EXPECT_DOUBLE_EQ(residuals[2], -999.0);
  // First two should be modified
  EXPECT_NE(residuals[0], -999.0);
  EXPECT_NE(residuals[1], -999.0);
}

}  // namespace
}  // namespace glomap
