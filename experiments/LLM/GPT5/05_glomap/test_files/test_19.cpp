// File: cost_function_test_19.cc

#include <gtest/gtest.h>
#include <ceres/ceres.h>
#include <Eigen/Core>

#include "glomap/estimators/cost_function.h"

namespace {

class GravErrorTest_19 : public ::testing::Test {
 protected:
  GravErrorTest_19() : grav_obs_(0.0, 0.0, 9.81) {}

  Eigen::Vector3d grav_obs_;
};

// Normal operation: operator() should compute residuals = gvec - grav_obs
TEST_F(GravErrorTest_19, OperatorComputesResiduals_19) {
  glomap::GravError error(grav_obs_);

  double gvec[3] = {0.1, -0.2, 9.5};
  double residuals[3] = {0.0, 0.0, 0.0};

  bool ok = error(gvec, residuals);

  EXPECT_TRUE(ok);
  EXPECT_DOUBLE_EQ(residuals[0], gvec[0] - grav_obs_[0]);
  EXPECT_DOUBLE_EQ(residuals[1], gvec[1] - grav_obs_[1]);
  EXPECT_DOUBLE_EQ(residuals[2], gvec[2] - grav_obs_[2]);
}

// Boundary condition: zero residual when estimated gravity equals observed gravity
TEST_F(GravErrorTest_19, OperatorZeroResidualWhenEqual_19) {
  glomap::GravError error(grav_obs_);

  double gvec[3] = {grav_obs_[0], grav_obs_[1], grav_obs_[2]};
  double residuals[3] = {1.0, 1.0, 1.0};  // initialize non-zero to ensure overwrite

  bool ok = error(gvec, residuals);

  EXPECT_TRUE(ok);
  EXPECT_DOUBLE_EQ(residuals[0], 0.0);
  EXPECT_DOUBLE_EQ(residuals[1], 0.0);
  EXPECT_DOUBLE_EQ(residuals[2], 0.0);
}

// Check that CreateCost returns a valid ceres::CostFunction with expected dimensions
TEST_F(GravErrorTest_19, CreateCostReturnsValidCostFunction_19) {
  std::unique_ptr<ceres::CostFunction> cost(
      glomap::GravError::CreateCost(grav_obs_));

  ASSERT_NE(cost, nullptr);

  // The functor takes a 3D gravity vector and produces a 3D residual.
  EXPECT_EQ(cost->num_residuals(), 3);

  const auto& block_sizes = cost->parameter_block_sizes();
  ASSERT_EQ(block_sizes.size(), 1u);
  EXPECT_EQ(block_sizes[0], 3);
}

// Normal operation through Ceres: Evaluate() should produce same residuals
// as direct application of the formula residual = gvec - grav_obs.
TEST_F(GravErrorTest_19, CreateCostEvaluateProducesExpectedResiduals_19) {
  std::unique_ptr<ceres::CostFunction> cost(
      glomap::GravError::CreateCost(grav_obs_));
  ASSERT_NE(cost, nullptr);

  double gvec[3] = {0.3, 0.4, 10.0};
  double* parameters[] = {gvec};
  double residuals[3] = {0.0, 0.0, 0.0};

  bool ok = cost->Evaluate(parameters, residuals, nullptr);

  EXPECT_TRUE(ok);
  EXPECT_NEAR(residuals[0], gvec[0] - grav_obs_[0], 1e-12);
  EXPECT_NEAR(residuals[1], gvec[1] - grav_obs_[1], 1e-12);
  EXPECT_NEAR(residuals[2], gvec[2] - grav_obs_[2], 1e-12);
}

// Template behavior check: ensure operator() also works correctly for float
TEST_F(GravErrorTest_19, OperatorWorksWithFloatType_19) {
  glomap::GravError error(grav_obs_);

  float gvec[3] = {1.0f, -2.0f, 3.5f};
  float residuals[3] = {0.0f, 0.0f, 0.0f};

  bool ok = error(gvec, residuals);

  EXPECT_TRUE(ok);
  EXPECT_FLOAT_EQ(residuals[0], gvec[0] - static_cast<float>(grav_obs_[0]));
  EXPECT_FLOAT_EQ(residuals[1], gvec[1] - static_cast<float>(grav_obs_[1]));
  EXPECT_FLOAT_EQ(residuals[2], gvec[2] - static_cast<float>(grav_obs_[2]));
}

}  // namespace
