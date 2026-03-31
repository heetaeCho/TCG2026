#include <gtest/gtest.h>
#include <Eigen/Core>
#include <ceres/ceres.h>
#include "glomap/estimators/cost_function.h"

namespace glomap {
namespace {

class GravErrorTest_19 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test that operator() returns true for normal inputs
TEST_F(GravErrorTest_19, OperatorReturnsTrueForNormalInputs_19) {
  Eigen::Vector3d grav_obs(0.0, 0.0, -9.81);
  GravError error(grav_obs);

  double gvec[3] = {0.0, 0.0, -9.81};
  double residuals[3] = {0.0, 0.0, 0.0};

  bool result = error(gvec, residuals);
  EXPECT_TRUE(result);
}

// Test that residuals are zero when gvec matches grav_obs
TEST_F(GravErrorTest_19, ResidualsZeroWhenGvecMatchesObservation_19) {
  Eigen::Vector3d grav_obs(1.0, 2.0, 3.0);
  GravError error(grav_obs);

  double gvec[3] = {1.0, 2.0, 3.0};
  double residuals[3] = {99.0, 99.0, 99.0};

  error(gvec, residuals);

  EXPECT_DOUBLE_EQ(residuals[0], 0.0);
  EXPECT_DOUBLE_EQ(residuals[1], 0.0);
  EXPECT_DOUBLE_EQ(residuals[2], 0.0);
}

// Test that residuals are correctly computed as gvec - grav_obs
TEST_F(GravErrorTest_19, ResidualsComputedAsGvecMinusObservation_19) {
  Eigen::Vector3d grav_obs(1.0, 2.0, 3.0);
  GravError error(grav_obs);

  double gvec[3] = {4.0, 5.0, 6.0};
  double residuals[3] = {0.0, 0.0, 0.0};

  error(gvec, residuals);

  EXPECT_DOUBLE_EQ(residuals[0], 3.0);
  EXPECT_DOUBLE_EQ(residuals[1], 3.0);
  EXPECT_DOUBLE_EQ(residuals[2], 3.0);
}

// Test with negative differences
TEST_F(GravErrorTest_19, ResidualsNegativeWhenGvecLessThanObservation_19) {
  Eigen::Vector3d grav_obs(5.0, 6.0, 7.0);
  GravError error(grav_obs);

  double gvec[3] = {1.0, 2.0, 3.0};
  double residuals[3] = {0.0, 0.0, 0.0};

  error(gvec, residuals);

  EXPECT_DOUBLE_EQ(residuals[0], -4.0);
  EXPECT_DOUBLE_EQ(residuals[1], -4.0);
  EXPECT_DOUBLE_EQ(residuals[2], -4.0);
}

// Test with zero observation vector
TEST_F(GravErrorTest_19, ZeroObservationVector_19) {
  Eigen::Vector3d grav_obs(0.0, 0.0, 0.0);
  GravError error(grav_obs);

  double gvec[3] = {1.5, -2.5, 3.5};
  double residuals[3] = {0.0, 0.0, 0.0};

  error(gvec, residuals);

  EXPECT_DOUBLE_EQ(residuals[0], 1.5);
  EXPECT_DOUBLE_EQ(residuals[1], -2.5);
  EXPECT_DOUBLE_EQ(residuals[2], 3.5);
}

// Test with zero gvec
TEST_F(GravErrorTest_19, ZeroGvec_19) {
  Eigen::Vector3d grav_obs(1.0, 2.0, 3.0);
  GravError error(grav_obs);

  double gvec[3] = {0.0, 0.0, 0.0};
  double residuals[3] = {0.0, 0.0, 0.0};

  error(gvec, residuals);

  EXPECT_DOUBLE_EQ(residuals[0], -1.0);
  EXPECT_DOUBLE_EQ(residuals[1], -2.0);
  EXPECT_DOUBLE_EQ(residuals[2], -3.0);
}

// Test with very large values
TEST_F(GravErrorTest_19, LargeValues_19) {
  Eigen::Vector3d grav_obs(1e10, 1e10, 1e10);
  GravError error(grav_obs);

  double gvec[3] = {2e10, 2e10, 2e10};
  double residuals[3] = {0.0, 0.0, 0.0};

  error(gvec, residuals);

  EXPECT_DOUBLE_EQ(residuals[0], 1e10);
  EXPECT_DOUBLE_EQ(residuals[1], 1e10);
  EXPECT_DOUBLE_EQ(residuals[2], 1e10);
}

// Test with very small values
TEST_F(GravErrorTest_19, SmallValues_19) {
  Eigen::Vector3d grav_obs(1e-15, 2e-15, 3e-15);
  GravError error(grav_obs);

  double gvec[3] = {2e-15, 3e-15, 4e-15};
  double residuals[3] = {0.0, 0.0, 0.0};

  error(gvec, residuals);

  EXPECT_DOUBLE_EQ(residuals[0], 1e-15);
  EXPECT_DOUBLE_EQ(residuals[1], 1e-15);
  EXPECT_DOUBLE_EQ(residuals[2], 1e-15);
}

// Test CreateCost returns a non-null cost function
TEST_F(GravErrorTest_19, CreateCostReturnsNonNull_19) {
  Eigen::Vector3d grav_obs(0.0, 0.0, -9.81);
  ceres::CostFunction* cost = GravError::CreateCost(grav_obs);
  ASSERT_NE(cost, nullptr);
  delete cost;
}

// Test CreateCost creates a cost function with correct parameter and residual sizes
TEST_F(GravErrorTest_19, CreateCostCorrectDimensions_19) {
  Eigen::Vector3d grav_obs(0.0, 0.0, -9.81);
  ceres::CostFunction* cost = GravError::CreateCost(grav_obs);
  ASSERT_NE(cost, nullptr);

  // Residual dimension should be 3
  EXPECT_EQ(cost->num_residuals(), 3);

  // Should have one parameter block of size 3
  const std::vector<int32_t>& param_sizes = cost->parameter_block_sizes();
  ASSERT_EQ(param_sizes.size(), 1);
  EXPECT_EQ(param_sizes[0], 3);

  delete cost;
}

// Test CreateCost cost function evaluates correctly
TEST_F(GravErrorTest_19, CreateCostEvaluatesCorrectly_19) {
  Eigen::Vector3d grav_obs(1.0, 2.0, 3.0);
  ceres::CostFunction* cost = GravError::CreateCost(grav_obs);
  ASSERT_NE(cost, nullptr);

  double gvec[3] = {4.0, 5.0, 6.0};
  double residuals[3] = {0.0, 0.0, 0.0};
  const double* parameters[1] = {gvec};

  // Evaluate without Jacobians
  bool success = cost->Evaluate(parameters, residuals, nullptr);
  EXPECT_TRUE(success);
  EXPECT_DOUBLE_EQ(residuals[0], 3.0);
  EXPECT_DOUBLE_EQ(residuals[1], 3.0);
  EXPECT_DOUBLE_EQ(residuals[2], 3.0);

  delete cost;
}

// Test CreateCost cost function evaluates Jacobians
TEST_F(GravErrorTest_19, CreateCostEvaluatesJacobians_19) {
  Eigen::Vector3d grav_obs(1.0, 2.0, 3.0);
  ceres::CostFunction* cost = GravError::CreateCost(grav_obs);
  ASSERT_NE(cost, nullptr);

  double gvec[3] = {4.0, 5.0, 6.0};
  double residuals[3] = {0.0, 0.0, 0.0};
  double jacobian[9] = {0.0};  // 3 residuals x 3 parameters
  double* jacobians[1] = {jacobian};
  const double* parameters[1] = {gvec};

  bool success = cost->Evaluate(parameters, residuals, jacobians);
  EXPECT_TRUE(success);

  // The Jacobian of (gvec - grav_obs) w.r.t. gvec should be the identity matrix
  // Row-major: [1, 0, 0, 0, 1, 0, 0, 0, 1]
  EXPECT_DOUBLE_EQ(jacobian[0], 1.0);
  EXPECT_DOUBLE_EQ(jacobian[1], 0.0);
  EXPECT_DOUBLE_EQ(jacobian[2], 0.0);
  EXPECT_DOUBLE_EQ(jacobian[3], 0.0);
  EXPECT_DOUBLE_EQ(jacobian[4], 1.0);
  EXPECT_DOUBLE_EQ(jacobian[5], 0.0);
  EXPECT_DOUBLE_EQ(jacobian[6], 0.0);
  EXPECT_DOUBLE_EQ(jacobian[7], 0.0);
  EXPECT_DOUBLE_EQ(jacobian[8], 1.0);

  delete cost;
}

// Test with mixed positive and negative observation values
TEST_F(GravErrorTest_19, MixedSignValues_19) {
  Eigen::Vector3d grav_obs(-1.0, 2.0, -3.0);
  GravError error(grav_obs);

  double gvec[3] = {1.0, -2.0, 3.0};
  double residuals[3] = {0.0, 0.0, 0.0};

  error(gvec, residuals);

  EXPECT_DOUBLE_EQ(residuals[0], 2.0);
  EXPECT_DOUBLE_EQ(residuals[1], -4.0);
  EXPECT_DOUBLE_EQ(residuals[2], 6.0);
}

// Test operator() with Jet type (used by Ceres for automatic differentiation)
TEST_F(GravErrorTest_19, OperatorWorksWithJetType_19) {
  Eigen::Vector3d grav_obs(1.0, 2.0, 3.0);
  GravError error(grav_obs);

  using JetT = ceres::Jet<double, 3>;
  JetT gvec[3];
  gvec[0] = JetT(4.0, 0);
  gvec[1] = JetT(5.0, 1);
  gvec[2] = JetT(6.0, 2);

  JetT residuals[3];

  bool result = error(gvec, residuals);
  EXPECT_TRUE(result);

  EXPECT_DOUBLE_EQ(residuals[0].a, 3.0);
  EXPECT_DOUBLE_EQ(residuals[1].a, 3.0);
  EXPECT_DOUBLE_EQ(residuals[2].a, 3.0);
}

// Test that CreateCost works in a Ceres problem context
TEST_F(GravErrorTest_19, CreateCostWorksInCeresProblem_19) {
  Eigen::Vector3d grav_obs(0.0, 0.0, -9.81);

  double gvec[3] = {0.1, -0.1, -9.5};

  ceres::Problem problem;
  ceres::CostFunction* cost = GravError::CreateCost(grav_obs);
  problem.AddResidualBlock(cost, nullptr, gvec);

  ceres::Solver::Options options;
  options.max_num_iterations = 100;
  options.linear_solver_type = ceres::DENSE_QR;
  ceres::Solver::Summary summary;

  ceres::Solve(options, &problem, &summary);

  // After optimization, gvec should converge to grav_obs
  EXPECT_NEAR(gvec[0], 0.0, 1e-8);
  EXPECT_NEAR(gvec[1], 0.0, 1e-8);
  EXPECT_NEAR(gvec[2], -9.81, 1e-8);
}

}  // namespace
}  // namespace glomap
