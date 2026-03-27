// File: batapairwisedirectionerror_test_12.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <ceres/ceres.h>

#include "glomap/estimators/cost_function.h"

namespace {

using glomap::BATAPairwiseDirectionError;

class BATAPairwiseDirectionErrorTest_12 : public ::testing::Test {
 protected:
  static constexpr double kTolerance = 1e-9;
};

TEST_F(BATAPairwiseDirectionErrorTest_12,
       OperatorReturnsTrueAndComputesResidualsForDouble_12) {
  // Arrange
  Eigen::Vector3d translation_obs(1.0, -2.0, 3.0);
  BATAPairwiseDirectionError functor(translation_obs);

  double position1[3] = {0.5, -1.0, 2.0};
  double position2[3] = {1.5, 0.0, 4.0};
  double scale[1]     = {2.0};
  double residuals[3] = {0.0, 0.0, 0.0};

  // Act
  const bool success = functor(position1, position2, scale, residuals);

  // Assert
  EXPECT_TRUE(success);

  Eigen::Vector3d p1(position1[0], position1[1], position1[2]);
  Eigen::Vector3d p2(position2[0], position2[1], position2[2]);
  Eigen::Vector3d expected =
      translation_obs - scale[0] * (p2 - p1);

  EXPECT_NEAR(residuals[0], expected[0], kTolerance);
  EXPECT_NEAR(residuals[1], expected[1], kTolerance);
  EXPECT_NEAR(residuals[2], expected[2], kTolerance);
}

TEST_F(BATAPairwiseDirectionErrorTest_12,
       OperatorWorksWithFloatAndZeroScale_12) {
  // Arrange
  Eigen::Vector3d translation_obs(0.1, 0.2, 0.3);
  BATAPairwiseDirectionError functor(translation_obs);

  float position1[3] = {1.0f, 2.0f, 3.0f};
  float position2[3] = {4.0f, 5.0f, 6.0f};
  float scale[1]     = {0.0f};  // boundary: zero scale
  float residuals[3] = {0.0f, 0.0f, 0.0f};

  // Act
  const bool success = functor(position1, position2, scale, residuals);

  // Assert
  EXPECT_TRUE(success);

  // With zero scale, residuals should match translation_obs (cast to float).
  EXPECT_NEAR(residuals[0], static_cast<float>(translation_obs[0]), 1e-6f);
  EXPECT_NEAR(residuals[1], static_cast<float>(translation_obs[1]), 1e-6f);
  EXPECT_NEAR(residuals[2], static_cast<float>(translation_obs[2]), 1e-6f);
}

TEST_F(BATAPairwiseDirectionErrorTest_12,
       OperatorHandlesIdenticalPositions_12) {
  // Arrange
  Eigen::Vector3d translation_obs(5.0, -1.0, 0.0);
  BATAPairwiseDirectionError functor(translation_obs);

  double position1[3] = {2.0, 3.0, 4.0};
  double position2[3] = {2.0, 3.0, 4.0};  // identical to position1
  double scale[1]     = {10.0};
  double residuals[3] = {0.0, 0.0, 0.0};

  // Act
  const bool success = functor(position1, position2, scale, residuals);

  // Assert
  EXPECT_TRUE(success);

  // If position1 == position2, residuals should equal translation_obs.
  EXPECT_NEAR(residuals[0], translation_obs[0], kTolerance);
  EXPECT_NEAR(residuals[1], translation_obs[1], kTolerance);
  EXPECT_NEAR(residuals[2], translation_obs[2], kTolerance);
}

TEST_F(BATAPairwiseDirectionErrorTest_12,
       CreateBuildsCostFunctionWithExpectedShape_12) {
  // Arrange
  Eigen::Vector3d translation_obs(1.0, 2.0, 3.0);

  // Act
  ceres::CostFunction* cost_function =
      BATAPairwiseDirectionError::Create(translation_obs);

  // Assert basic properties of the created cost function.
  ASSERT_NE(cost_function, nullptr);

  EXPECT_EQ(cost_function->num_residuals(), 3);

  const std::vector<int32_t>& block_sizes =
      cost_function->parameter_block_sizes();
  ASSERT_EQ(block_sizes.size(), 3u);
  EXPECT_EQ(block_sizes[0], 3);  // position1
  EXPECT_EQ(block_sizes[1], 3);  // position2
  EXPECT_EQ(block_sizes[2], 1);  // scale

  // Clean up to avoid leaks.
  delete cost_function;
}

}  // namespace
