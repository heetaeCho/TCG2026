// File: fetzer_focal_length_cost_test_17.cc

#include <cmath>

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <ceres/ceres.h>

#include "glomap/estimators/cost_function.h"

namespace glomap {

class FetzerFocalLengthCostTest_17 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Use a simple, valid fundamental matrix and principal points.
    fundamental_.setIdentity();
    principal_point0_.setZero();
    principal_point1_.setZero();
  }

  Eigen::Matrix3d fundamental_;
  Eigen::Vector2d principal_point0_;
  Eigen::Vector2d principal_point1_;
};

// Basic sanity: construction and operator() produce finite residuals for
// reasonable focal lengths and return true.
TEST_F(FetzerFocalLengthCostTest_17, OperatorProducesFiniteResiduals_17) {
  FetzerFocalLengthCost cost(fundamental_, principal_point0_, principal_point1_);

  const double fi = 800.0;
  const double fj = 850.0;
  double residuals[2] = {0.0, 0.0};

  const bool ok = cost(&fi, &fj, residuals);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));
}

// The cost functor should be deterministic: calling operator() twice with the
// same inputs must yield identical residuals.
TEST_F(FetzerFocalLengthCostTest_17, OperatorIsDeterministicForSameInput_17) {
  FetzerFocalLengthCost cost(fundamental_, principal_point0_, principal_point1_);

  const double fi = 900.0;
  const double fj = 700.0;

  double residuals_first[2]  = {0.0, 0.0};
  double residuals_second[2] = {0.0, 0.0};

  ASSERT_TRUE(cost(&fi, &fj, residuals_first));
  ASSERT_TRUE(cost(&fi, &fj, residuals_second));

  EXPECT_DOUBLE_EQ(residuals_first[0], residuals_second[0]);
  EXPECT_DOUBLE_EQ(residuals_first[1], residuals_second[1]);
}

// Verify that the static Create() correctly configures a ceres::CostFunction
// with the expected number of residuals and parameter blocks, and that
// Evaluate() succeeds and produces finite residuals.
TEST_F(FetzerFocalLengthCostTest_17, CreateReturnsValidCeresCostFunction_17) {
  ceres::CostFunction* cost_function =
      FetzerFocalLengthCost::Create(fundamental_, principal_point0_, principal_point1_);
  ASSERT_NE(cost_function, nullptr);

  // The interface suggests two residuals (residuals[0], residuals[1])
  // and two scalar parameter blocks (fi and fj).
  EXPECT_EQ(cost_function->num_residuals(), 2);

  const std::vector<int32_t>& block_sizes = cost_function->parameter_block_sizes();
  ASSERT_EQ(block_sizes.size(), 2u);
  EXPECT_EQ(block_sizes[0], 1);
  EXPECT_EQ(block_sizes[1], 1);

  // Evaluate the cost function through the ceres::CostFunction interface.
  const double fi = 750.0;
  const double fj = 650.0;
  const double* parameters[2] = {&fi, &fj};

  double residuals[2] = {0.0, 0.0};
  // We don't request Jacobians for this test.
  bool eval_ok = cost_function->Evaluate(parameters, residuals, nullptr);

  EXPECT_TRUE(eval_ok);
  EXPECT_TRUE(std::isfinite(residuals[0]));
  EXPECT_TRUE(std::isfinite(residuals[1]));

  delete cost_function;
}

}  // namespace glomap
