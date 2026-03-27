// File: rig_unknown_ba_pairwise_direction_error_test_14.cc

#include "glomap/estimators/cost_function.h"

#include <ceres/ceres.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <gtest/gtest.h>

namespace {

class RigUnknownBATAPairwiseDirectionErrorTest_14 : public ::testing::Test {};

TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14,
       ZeroScaleYieldsTranslationObs_14) {
  // Arrange
  const Eigen::Vector3d translation_obs(0.1, -0.2, 0.3);
  const Eigen::Quaterniond rig_rot = Eigen::Quaterniond::Identity();

  glomap::RigUnknownBATAPairwiseDirectionError error(translation_obs, rig_rot);

  double point3d[3] = {1.0, 2.0, 3.0};
  double rig_from_world_center[3] = {4.0, 5.0, 6.0};
  double cam_from_rig_center[3] = {7.0, 8.0, 9.0};
  double scale[1] = {0.0};
  double residuals[3] = {0.0, 0.0, 0.0};

  // Act
  const bool ok = error(point3d,
                        rig_from_world_center,
                        cam_from_rig_center,
                        scale,
                        residuals);

  // Assert
  EXPECT_TRUE(ok);
  EXPECT_NEAR(residuals[0], translation_obs[0], 1e-12);
  EXPECT_NEAR(residuals[1], translation_obs[1], 1e-12);
  EXPECT_NEAR(residuals[2], translation_obs[2], 1e-12);
}

TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14,
       IdentityRotationProducesNegativePointWhenNoOffsets_14) {
  // Arrange: identity rotation, zero observed translation, zero offsets
  const Eigen::Vector3d translation_obs = Eigen::Vector3d::Zero();
  const Eigen::Quaterniond rig_rot = Eigen::Quaterniond::Identity();

  glomap::RigUnknownBATAPairwiseDirectionError error(translation_obs, rig_rot);

  double point3d[3] = {1.0, -2.0, 0.5};
  double rig_from_world_center[3] = {0.0, 0.0, 0.0};
  double cam_from_rig_center[3] = {0.0, 0.0, 0.0};
  double scale[1] = {1.0};
  double residuals[3] = {0.0, 0.0, 0.0};

  // Act
  const bool ok = error(point3d,
                        rig_from_world_center,
                        cam_from_rig_center,
                        scale,
                        residuals);

  // Assert: with this setup, residuals should be the negative of point3d
  EXPECT_TRUE(ok);
  EXPECT_NEAR(residuals[0], -point3d[0], 1e-12);
  EXPECT_NEAR(residuals[1], -point3d[1], 1e-12);
  EXPECT_NEAR(residuals[2], -point3d[2], 1e-12);
}

TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14,
       PointAtRigPlusCamCenterYieldsTranslationObs_14) {
  // Arrange: choose point such that point3d - rig_center - translation_rig = 0
  const Eigen::Vector3d translation_obs(0.3, 0.4, -0.5);
  const Eigen::Quaterniond rig_rot = Eigen::Quaterniond::Identity();

  glomap::RigUnknownBATAPairwiseDirectionError error(translation_obs, rig_rot);

  Eigen::Vector3d rig_center_vec(1.0, 2.0, 3.0);
  Eigen::Vector3d cam_center_vec(-0.5, 0.0, 2.0);
  Eigen::Vector3d point3d_vec = rig_center_vec + cam_center_vec;

  double point3d[3] = {point3d_vec[0], point3d_vec[1], point3d_vec[2]};
  double rig_from_world_center[3] = {
      rig_center_vec[0], rig_center_vec[1], rig_center_vec[2]};
  double cam_from_rig_center[3] = {
      cam_center_vec[0], cam_center_vec[1], cam_center_vec[2]};
  double scale[1] = {1.0};
  double residuals[3] = {0.0, 0.0, 0.0};

  // Act
  const bool ok = error(point3d,
                        rig_from_world_center,
                        cam_from_rig_center,
                        scale,
                        residuals);

  // Assert: for this configuration and scale=1, residuals reduce to translation_obs
  EXPECT_TRUE(ok);
  EXPECT_NEAR(residuals[0], translation_obs[0], 1e-12);
  EXPECT_NEAR(residuals[1], translation_obs[1], 1e-12);
  EXPECT_NEAR(residuals[2], translation_obs[2], 1e-12);
}

TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14,
       TemplateProducesConsistentResultsForFloatAndDouble_14) {
  // Arrange
  const Eigen::Vector3d translation_obs(0.2, -0.1, 0.7);
  const Eigen::Quaterniond rig_rot = Eigen::Quaterniond::Identity();

  glomap::RigUnknownBATAPairwiseDirectionError error(translation_obs, rig_rot);

  double point3d_d[3] = {1.0, 2.0, 3.0};
  double rig_from_world_center_d[3] = {0.5, -1.0, 0.0};
  double cam_from_rig_center_d[3] = {0.1, 0.2, 0.3};
  double scale_d[1] = {1.5};
  double residuals_d[3] = {0.0, 0.0, 0.0};

  float point3d_f[3] = {1.0f, 2.0f, 3.0f};
  float rig_from_world_center_f[3] = {0.5f, -1.0f, 0.0f};
  float cam_from_rig_center_f[3] = {0.1f, 0.2f, 0.3f};
  float scale_f[1] = {1.5f};
  float residuals_f[3] = {0.0f, 0.0f, 0.0f};

  // Act
  const bool ok_double = error(point3d_d,
                               rig_from_world_center_d,
                               cam_from_rig_center_d,
                               scale_d,
                               residuals_d);

  const bool ok_float = error(point3d_f,
                              rig_from_world_center_f,
                              cam_from_rig_center_f,
                              scale_f,
                              residuals_f);

  // Assert: both instantiations should succeed and yield numerically close results
  EXPECT_TRUE(ok_double);
  EXPECT_TRUE(ok_float);

  EXPECT_NEAR(static_cast<double>(residuals_f[0]), residuals_d[0], 1e-5);
  EXPECT_NEAR(static_cast<double>(residuals_f[1]), residuals_d[1], 1e-5);
  EXPECT_NEAR(static_cast<double>(residuals_f[2]), residuals_d[2], 1e-5);
}

TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14,
       CreateBuildsCostFunctionWithCorrectBlocksAndBehavior_14) {
  // Arrange
  const Eigen::Vector3d translation_obs(0.4, -0.3, 0.6);
  const Eigen::Quaterniond rig_rot = Eigen::Quaterniond::Identity();

  glomap::RigUnknownBATAPairwiseDirectionError error_functor(translation_obs,
                                                             rig_rot);

  // Act: create ceres::CostFunction
  ceres::CostFunction* cost_function =
      glomap::RigUnknownBATAPairwiseDirectionError::Create(translation_obs,
                                                           rig_rot);

  // Assert basic properties
  ASSERT_NE(cost_function, nullptr);
  EXPECT_EQ(cost_function->num_residuals(), 3);

  const std::vector<int32_t>& block_sizes =
      cost_function->parameter_block_sizes();
  ASSERT_EQ(block_sizes.size(), 4u);
  EXPECT_EQ(block_sizes[0], 3);  // point3d
  EXPECT_EQ(block_sizes[1], 3);  // rig_from_world_center
  EXPECT_EQ(block_sizes[2], 3);  // cam_from_rig_center
  EXPECT_EQ(block_sizes[3], 1);  // scale

  // Also verify that evaluating the CostFunction is consistent with directly
  // invoking the functor.
  double point3d[3] = {0.2, -1.0, 3.5};
  double rig_from_world_center[3] = {0.1, 0.0, -0.3};
  double cam_from_rig_center[3] = {-0.5, 0.2, 0.8};
  double scale[1] = {0.9};

  double* parameters[] = {
      point3d,
      rig_from_world_center,
      cam_from_rig_center,
      scale,
  };

  double residuals_from_cost[3] = {0.0, 0.0, 0.0};
  bool eval_ok =
      cost_function->Evaluate(parameters, residuals_from_cost, nullptr);
  EXPECT_TRUE(eval_ok);

  double residuals_from_functor[3] = {0.0, 0.0, 0.0};
  bool functor_ok = error_functor(point3d,
                                  rig_from_world_center,
                                  cam_from_rig_center,
                                  scale,
                                  residuals_from_functor);
  EXPECT_TRUE(functor_ok);

  EXPECT_NEAR(residuals_from_cost[0], residuals_from_functor[0], 1e-12);
  EXPECT_NEAR(residuals_from_cost[1], residuals_from_functor[1], 1e-12);
  EXPECT_NEAR(residuals_from_cost[2], residuals_from_functor[2], 1e-12);

  delete cost_function;
}

}  // namespace
