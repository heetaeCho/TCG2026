#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <ceres/ceres.h>

#include "glomap/estimators/cost_function.h"

namespace glomap {
namespace {

class FetzerFocalLengthCostTest_167 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Default principal points at image center
    principal_point0_ = Eigen::Vector2d(320.0, 240.0);
    principal_point1_ = Eigen::Vector2d(320.0, 240.0);
    
    // A simple fundamental matrix (identity-like for testing)
    F_ = Eigen::Matrix3d::Identity();
  }

  Eigen::Matrix3d F_;
  Eigen::Vector2d principal_point0_;
  Eigen::Vector2d principal_point1_;
};

// Test that the constructor does not crash with identity fundamental matrix
TEST_F(FetzerFocalLengthCostTest_167, ConstructWithIdentityF_167) {
  EXPECT_NO_THROW(
    FetzerFocalLengthCost cost(F_, principal_point0_, principal_point1_)
  );
}

// Test that the constructor does not crash with zero fundamental matrix
TEST_F(FetzerFocalLengthCostTest_167, ConstructWithZeroF_167) {
  Eigen::Matrix3d zeroF = Eigen::Matrix3d::Zero();
  EXPECT_NO_THROW(
    FetzerFocalLengthCost cost(zeroF, principal_point0_, principal_point1_)
  );
}

// Test construction with zero principal points
TEST_F(FetzerFocalLengthCostTest_167, ConstructWithZeroPrincipalPoints_167) {
  Eigen::Vector2d zeroPP(0.0, 0.0);
  EXPECT_NO_THROW(
    FetzerFocalLengthCost cost(F_, zeroPP, zeroPP)
  );
}

// Test construction with different principal points
TEST_F(FetzerFocalLengthCostTest_167, ConstructWithDifferentPrincipalPoints_167) {
  Eigen::Vector2d pp0(100.0, 200.0);
  Eigen::Vector2d pp1(300.0, 400.0);
  EXPECT_NO_THROW(
    FetzerFocalLengthCost cost(F_, pp0, pp1)
  );
}

// Test construction with negative principal points
TEST_F(FetzerFocalLengthCostTest_167, ConstructWithNegativePrincipalPoints_167) {
  Eigen::Vector2d pp0(-100.0, -200.0);
  Eigen::Vector2d pp1(-50.0, -75.0);
  EXPECT_NO_THROW(
    FetzerFocalLengthCost cost(F_, pp0, pp1)
  );
}

// Test that Create returns a non-null CostFunction pointer
TEST_F(FetzerFocalLengthCostTest_167, CreateReturnsNonNull_167) {
  ceres::CostFunction* cost_function = 
    FetzerFocalLengthCost::Create(F_, principal_point0_, principal_point1_);
  ASSERT_NE(cost_function, nullptr);
  delete cost_function;
}

// Test that Create works with a zero fundamental matrix
TEST_F(FetzerFocalLengthCostTest_167, CreateWithZeroF_167) {
  Eigen::Matrix3d zeroF = Eigen::Matrix3d::Zero();
  ceres::CostFunction* cost_function = 
    FetzerFocalLengthCost::Create(zeroF, principal_point0_, principal_point1_);
  ASSERT_NE(cost_function, nullptr);
  delete cost_function;
}

// Test that operator() returns true (valid evaluation) with reasonable focal lengths
TEST_F(FetzerFocalLengthCostTest_167, OperatorReturnsTrue_167) {
  FetzerFocalLengthCost cost(F_, principal_point0_, principal_point1_);
  
  double fi = 500.0;
  double fj = 500.0;
  double residuals[3];  // Assuming 3 residuals based on d_01, d_02, d_12
  
  const double* params[] = {&fi, &fj};
  bool result = cost(&fi, &fj, residuals);
  EXPECT_TRUE(result);
}

// Test operator() with equal focal lengths
TEST_F(FetzerFocalLengthCostTest_167, OperatorWithEqualFocalLengths_167) {
  FetzerFocalLengthCost cost(F_, principal_point0_, principal_point1_);
  
  double fi = 1000.0;
  double fj = 1000.0;
  double residuals[3];
  
  bool result = cost(&fi, &fj, residuals);
  EXPECT_TRUE(result);
}

// Test operator() with different focal lengths
TEST_F(FetzerFocalLengthCostTest_167, OperatorWithDifferentFocalLengths_167) {
  FetzerFocalLengthCost cost(F_, principal_point0_, principal_point1_);
  
  double fi = 500.0;
  double fj = 800.0;
  double residuals[3];
  
  bool result = cost(&fi, &fj, residuals);
  EXPECT_TRUE(result);
}

// Test operator() with small focal lengths
TEST_F(FetzerFocalLengthCostTest_167, OperatorWithSmallFocalLengths_167) {
  FetzerFocalLengthCost cost(F_, principal_point0_, principal_point1_);
  
  double fi = 1.0;
  double fj = 1.0;
  double residuals[3];
  
  bool result = cost(&fi, &fj, residuals);
  EXPECT_TRUE(result);
}

// Test operator() with large focal lengths
TEST_F(FetzerFocalLengthCostTest_167, OperatorWithLargeFocalLengths_167) {
  FetzerFocalLengthCost cost(F_, principal_point0_, principal_point1_);
  
  double fi = 10000.0;
  double fj = 10000.0;
  double residuals[3];
  
  bool result = cost(&fi, &fj, residuals);
  EXPECT_TRUE(result);
}

// Test that the cost function works within a Ceres problem
TEST_F(FetzerFocalLengthCostTest_167, WorksInCeresProblem_167) {
  ceres::CostFunction* cost_function = 
    FetzerFocalLengthCost::Create(F_, principal_point0_, principal_point1_);
  ASSERT_NE(cost_function, nullptr);
  
  ceres::Problem problem;
  double fi = 500.0;
  double fj = 500.0;
  
  problem.AddResidualBlock(cost_function, nullptr, &fi, &fj);
  
  // Verify the problem has one residual block
  EXPECT_EQ(problem.NumResidualBlocks(), 1);
  EXPECT_EQ(problem.NumParameterBlocks(), 2);
}

// Test with a more realistic fundamental matrix
TEST_F(FetzerFocalLengthCostTest_167, ConstructWithRealisticF_167) {
  // A rank-2 fundamental matrix (more realistic)
  Eigen::Matrix3d F;
  F << 0.0, -0.001, 0.1,
       0.001, 0.0, -0.2,
       -0.1, 0.2, 0.0;
  
  EXPECT_NO_THROW(
    FetzerFocalLengthCost cost(F, principal_point0_, principal_point1_)
  );
}

// Test operator() with a realistic fundamental matrix
TEST_F(FetzerFocalLengthCostTest_167, OperatorWithRealisticF_167) {
  Eigen::Matrix3d F;
  F << 0.0, -0.001, 0.1,
       0.001, 0.0, -0.2,
       -0.1, 0.2, 0.0;
  
  FetzerFocalLengthCost cost(F, principal_point0_, principal_point1_);
  
  double fi = 500.0;
  double fj = 600.0;
  double residuals[3];
  
  bool result = cost(&fi, &fj, residuals);
  EXPECT_TRUE(result);
}

// Test that residuals change with different focal lengths
TEST_F(FetzerFocalLengthCostTest_167, ResidualsDifferForDifferentFocalLengths_167) {
  Eigen::Matrix3d F;
  F << 0.0, -0.001, 0.1,
       0.001, 0.0, -0.2,
       -0.1, 0.2, 0.0;
  
  FetzerFocalLengthCost cost(F, principal_point0_, principal_point1_);
  
  double fi1 = 500.0, fj1 = 500.0;
  double residuals1[3];
  cost(&fi1, &fj1, residuals1);
  
  double fi2 = 800.0, fj2 = 800.0;
  double residuals2[3];
  cost(&fi2, &fj2, residuals2);
  
  // At least one residual should differ
  bool any_different = false;
  for (int i = 0; i < 3; ++i) {
    if (std::abs(residuals1[i] - residuals2[i]) > 1e-12) {
      any_different = true;
      break;
    }
  }
  EXPECT_TRUE(any_different);
}

// Test that Create cost function has correct parameter block sizes
TEST_F(FetzerFocalLengthCostTest_167, CostFunctionParameterSizes_167) {
  ceres::CostFunction* cost_function = 
    FetzerFocalLengthCost::Create(F_, principal_point0_, principal_point1_);
  ASSERT_NE(cost_function, nullptr);
  
  const std::vector<int32_t>& param_sizes = cost_function->parameter_block_sizes();
  EXPECT_EQ(param_sizes.size(), 2u);
  // Each focal length is a single parameter
  EXPECT_EQ(param_sizes[0], 1);
  EXPECT_EQ(param_sizes[1], 1);
  
  delete cost_function;
}

// Test that the cost function produces finite residuals
TEST_F(FetzerFocalLengthCostTest_167, ResidualsAreFinite_167) {
  Eigen::Matrix3d F;
  F << 0.0, -0.001, 0.1,
       0.001, 0.0, -0.2,
       -0.1, 0.2, 0.0;
  
  FetzerFocalLengthCost cost(F, principal_point0_, principal_point1_);
  
  double fi = 500.0;
  double fj = 600.0;
  double residuals[3];
  
  cost(&fi, &fj, residuals);
  
  for (int i = 0; i < 3; ++i) {
    EXPECT_TRUE(std::isfinite(residuals[i])) << "Residual " << i << " is not finite";
  }
}

// Test construction with very large principal points
TEST_F(FetzerFocalLengthCostTest_167, ConstructWithLargePrincipalPoints_167) {
  Eigen::Vector2d pp0(5000.0, 5000.0);
  Eigen::Vector2d pp1(5000.0, 5000.0);
  EXPECT_NO_THROW(
    FetzerFocalLengthCost cost(F_, pp0, pp1)
  );
}

// Test that Ceres optimization can run (basic smoke test)
TEST_F(FetzerFocalLengthCostTest_167, CeresOptimizationRuns_167) {
  Eigen::Matrix3d F;
  F << 0.0, -0.001, 0.1,
       0.001, 0.0, -0.2,
       -0.1, 0.2, 0.0;
  
  ceres::CostFunction* cost_function = 
    FetzerFocalLengthCost::Create(F, principal_point0_, principal_point1_);
  ASSERT_NE(cost_function, nullptr);
  
  ceres::Problem problem;
  double fi = 500.0;
  double fj = 500.0;
  
  problem.AddResidualBlock(cost_function, nullptr, &fi, &fj);
  
  ceres::Solver::Options options;
  options.max_num_iterations = 50;
  options.linear_solver_type = ceres::DENSE_QR;
  options.minimizer_progress_to_stdout = false;
  
  ceres::Solver::Summary summary;
  ceres::Solve(options, &problem, &summary);
  
  // Just verify it terminates
  EXPECT_TRUE(summary.IsSolutionUsable() || 
              summary.termination_type == ceres::NO_CONVERGENCE);
}

}  // namespace
}  // namespace glomap
