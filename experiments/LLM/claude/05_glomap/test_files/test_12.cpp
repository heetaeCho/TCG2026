#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Eigen/Core>
#include <ceres/ceres.h>
#include "glomap/estimators/cost_function.h"

namespace glomap {
namespace {

class BATAPairwiseDirectionErrorTest_12 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test that operator() returns true for basic inputs
TEST_F(BATAPairwiseDirectionErrorTest_12, OperatorReturnsTrueBasic_12) {
  Eigen::Vector3d translation_obs(1.0, 0.0, 0.0);
  BATAPairwiseDirectionError error(translation_obs);

  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {1.0, 0.0, 0.0};
  double scale[1] = {1.0};
  double residuals[3] = {0.0, 0.0, 0.0};

  bool result = error(position1, position2, scale, residuals);
  EXPECT_TRUE(result);
}

// Test that residuals = translation_obs - scale * (position2 - position1)
// When positions match the observation with scale=1, residuals should be zero
TEST_F(BATAPairwiseDirectionErrorTest_12, ZeroResidualWhenPerfectMatch_12) {
  Eigen::Vector3d translation_obs(3.0, 4.0, 5.0);
  BATAPairwiseDirectionError error(translation_obs);

  double position1[3] = {1.0, 2.0, 3.0};
  double position2[3] = {4.0, 6.0, 8.0};
  double scale[1] = {1.0};
  double residuals[3];

  error(position1, position2, scale, residuals);

  EXPECT_NEAR(residuals[0], 0.0, 1e-12);
  EXPECT_NEAR(residuals[1], 0.0, 1e-12);
  EXPECT_NEAR(residuals[2], 0.0, 1e-12);
}

// Test with non-unit scale
TEST_F(BATAPairwiseDirectionErrorTest_12, NonUnitScale_12) {
  Eigen::Vector3d translation_obs(6.0, 8.0, 10.0);
  BATAPairwiseDirectionError error(translation_obs);

  double position1[3] = {1.0, 2.0, 3.0};
  double position2[3] = {4.0, 6.0, 8.0};
  double scale[1] = {2.0};
  double residuals[3];

  // residuals = [6,8,10] - 2*([4,6,8]-[1,2,3]) = [6,8,10] - 2*[3,4,5] = [6,8,10]-[6,8,10] = [0,0,0]
  error(position1, position2, scale, residuals);

  EXPECT_NEAR(residuals[0], 0.0, 1e-12);
  EXPECT_NEAR(residuals[1], 0.0, 1e-12);
  EXPECT_NEAR(residuals[2], 0.0, 1e-12);
}

// Test with non-zero residuals
TEST_F(BATAPairwiseDirectionErrorTest_12, NonZeroResiduals_12) {
  Eigen::Vector3d translation_obs(1.0, 2.0, 3.0);
  BATAPairwiseDirectionError error(translation_obs);

  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {1.0, 1.0, 1.0};
  double scale[1] = {1.0};
  double residuals[3];

  // residuals = [1,2,3] - 1*([1,1,1]-[0,0,0]) = [1,2,3]-[1,1,1] = [0,1,2]
  error(position1, position2, scale, residuals);

  EXPECT_NEAR(residuals[0], 0.0, 1e-12);
  EXPECT_NEAR(residuals[1], 1.0, 1e-12);
  EXPECT_NEAR(residuals[2], 2.0, 1e-12);
}

// Test with zero scale
TEST_F(BATAPairwiseDirectionErrorTest_12, ZeroScale_12) {
  Eigen::Vector3d translation_obs(1.0, 2.0, 3.0);
  BATAPairwiseDirectionError error(translation_obs);

  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {5.0, 6.0, 7.0};
  double scale[1] = {0.0};
  double residuals[3];

  // residuals = [1,2,3] - 0*[5,6,7] = [1,2,3]
  error(position1, position2, scale, residuals);

  EXPECT_NEAR(residuals[0], 1.0, 1e-12);
  EXPECT_NEAR(residuals[1], 2.0, 1e-12);
  EXPECT_NEAR(residuals[2], 3.0, 1e-12);
}

// Test with negative scale
TEST_F(BATAPairwiseDirectionErrorTest_12, NegativeScale_12) {
  Eigen::Vector3d translation_obs(1.0, 2.0, 3.0);
  BATAPairwiseDirectionError error(translation_obs);

  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {1.0, 1.0, 1.0};
  double scale[1] = {-1.0};
  double residuals[3];

  // residuals = [1,2,3] - (-1)*[1,1,1] = [1,2,3]+[1,1,1] = [2,3,4]
  error(position1, position2, scale, residuals);

  EXPECT_NEAR(residuals[0], 2.0, 1e-12);
  EXPECT_NEAR(residuals[1], 3.0, 1e-12);
  EXPECT_NEAR(residuals[2], 4.0, 1e-12);
}

// Test with identical positions
TEST_F(BATAPairwiseDirectionErrorTest_12, IdenticalPositions_12) {
  Eigen::Vector3d translation_obs(1.0, 2.0, 3.0);
  BATAPairwiseDirectionError error(translation_obs);

  double position1[3] = {5.0, 5.0, 5.0};
  double position2[3] = {5.0, 5.0, 5.0};
  double scale[1] = {1.0};
  double residuals[3];

  // residuals = [1,2,3] - 1*[0,0,0] = [1,2,3]
  error(position1, position2, scale, residuals);

  EXPECT_NEAR(residuals[0], 1.0, 1e-12);
  EXPECT_NEAR(residuals[1], 2.0, 1e-12);
  EXPECT_NEAR(residuals[2], 3.0, 1e-12);
}

// Test with zero translation observation
TEST_F(BATAPairwiseDirectionErrorTest_12, ZeroTranslationObs_12) {
  Eigen::Vector3d translation_obs(0.0, 0.0, 0.0);
  BATAPairwiseDirectionError error(translation_obs);

  double position1[3] = {1.0, 2.0, 3.0};
  double position2[3] = {4.0, 5.0, 6.0};
  double scale[1] = {1.0};
  double residuals[3];

  // residuals = [0,0,0] - 1*[3,3,3] = [-3,-3,-3]
  error(position1, position2, scale, residuals);

  EXPECT_NEAR(residuals[0], -3.0, 1e-12);
  EXPECT_NEAR(residuals[1], -3.0, 1e-12);
  EXPECT_NEAR(residuals[2], -3.0, 1e-12);
}

// Test with large values
TEST_F(BATAPairwiseDirectionErrorTest_12, LargeValues_12) {
  Eigen::Vector3d translation_obs(1e6, 2e6, 3e6);
  BATAPairwiseDirectionError error(translation_obs);

  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {1e6, 2e6, 3e6};
  double scale[1] = {1.0};
  double residuals[3];

  error(position1, position2, scale, residuals);

  EXPECT_NEAR(residuals[0], 0.0, 1e-6);
  EXPECT_NEAR(residuals[1], 0.0, 1e-6);
  EXPECT_NEAR(residuals[2], 0.0, 1e-6);
}

// Test with very small values
TEST_F(BATAPairwiseDirectionErrorTest_12, SmallValues_12) {
  Eigen::Vector3d translation_obs(1e-10, 2e-10, 3e-10);
  BATAPairwiseDirectionError error(translation_obs);

  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {1e-10, 2e-10, 3e-10};
  double scale[1] = {1.0};
  double residuals[3];

  error(position1, position2, scale, residuals);

  EXPECT_NEAR(residuals[0], 0.0, 1e-20);
  EXPECT_NEAR(residuals[1], 0.0, 1e-20);
  EXPECT_NEAR(residuals[2], 0.0, 1e-20);
}

// Test Create() returns a valid cost function
TEST_F(BATAPairwiseDirectionErrorTest_12, CreateReturnsValidCostFunction_12) {
  Eigen::Vector3d translation_obs(1.0, 2.0, 3.0);
  ceres::CostFunction* cost_function = BATAPairwiseDirectionError::Create(translation_obs);

  ASSERT_NE(cost_function, nullptr);

  // Check that the cost function has the right number of residuals
  EXPECT_EQ(cost_function->num_residuals(), 3);

  // Check parameter block sizes: position1(3), position2(3), scale(1)
  const std::vector<int32_t>& param_sizes = cost_function->parameter_block_sizes();
  ASSERT_EQ(param_sizes.size(), 3u);
  EXPECT_EQ(param_sizes[0], 3);
  EXPECT_EQ(param_sizes[1], 3);
  EXPECT_EQ(param_sizes[2], 1);

  delete cost_function;
}

// Test Create() cost function produces correct residuals
TEST_F(BATAPairwiseDirectionErrorTest_12, CreateCostFunctionProducesCorrectResiduals_12) {
  Eigen::Vector3d translation_obs(3.0, 4.0, 5.0);
  ceres::CostFunction* cost_function = BATAPairwiseDirectionError::Create(translation_obs);

  ASSERT_NE(cost_function, nullptr);

  double position1[3] = {1.0, 2.0, 3.0};
  double position2[3] = {4.0, 6.0, 8.0};
  double scale[1] = {1.0};
  double residuals[3];

  const double* parameters[3] = {position1, position2, scale};
  cost_function->Evaluate(parameters, residuals, nullptr);

  EXPECT_NEAR(residuals[0], 0.0, 1e-12);
  EXPECT_NEAR(residuals[1], 0.0, 1e-12);
  EXPECT_NEAR(residuals[2], 0.0, 1e-12);

  delete cost_function;
}

// Test Create() cost function with Jacobians
TEST_F(BATAPairwiseDirectionErrorTest_12, CreateCostFunctionJacobiansNotNull_12) {
  Eigen::Vector3d translation_obs(1.0, 2.0, 3.0);
  ceres::CostFunction* cost_function = BATAPairwiseDirectionError::Create(translation_obs);

  ASSERT_NE(cost_function, nullptr);

  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {1.0, 1.0, 1.0};
  double scale[1] = {1.0};
  double residuals[3];

  double jacobian1[9];  // 3 residuals x 3 params
  double jacobian2[9];
  double jacobian3[3];  // 3 residuals x 1 param
  double* jacobians[3] = {jacobian1, jacobian2, jacobian3};

  const double* parameters[3] = {position1, position2, scale};
  bool success = cost_function->Evaluate(parameters, residuals, jacobians);

  EXPECT_TRUE(success);

  delete cost_function;
}

// Test with negative positions
TEST_F(BATAPairwiseDirectionErrorTest_12, NegativePositions_12) {
  Eigen::Vector3d translation_obs(-2.0, -3.0, -4.0);
  BATAPairwiseDirectionError error(translation_obs);

  double position1[3] = {3.0, 4.0, 5.0};
  double position2[3] = {1.0, 1.0, 1.0};
  double scale[1] = {1.0};
  double residuals[3];

  // residuals = [-2,-3,-4] - 1*([1,1,1]-[3,4,5]) = [-2,-3,-4] - [-2,-3,-4] = [0,0,0]
  error(position1, position2, scale, residuals);

  EXPECT_NEAR(residuals[0], 0.0, 1e-12);
  EXPECT_NEAR(residuals[1], 0.0, 1e-12);
  EXPECT_NEAR(residuals[2], 0.0, 1e-12);
}

// Test with fractional scale
TEST_F(BATAPairwiseDirectionErrorTest_12, FractionalScale_12) {
  Eigen::Vector3d translation_obs(1.5, 2.0, 2.5);
  BATAPairwiseDirectionError error(translation_obs);

  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {3.0, 4.0, 5.0};
  double scale[1] = {0.5};
  double residuals[3];

  // residuals = [1.5,2.0,2.5] - 0.5*[3,4,5] = [1.5,2.0,2.5]-[1.5,2.0,2.5] = [0,0,0]
  error(position1, position2, scale, residuals);

  EXPECT_NEAR(residuals[0], 0.0, 1e-12);
  EXPECT_NEAR(residuals[1], 0.0, 1e-12);
  EXPECT_NEAR(residuals[2], 0.0, 1e-12);
}

}  // namespace
}  // namespace glomap
