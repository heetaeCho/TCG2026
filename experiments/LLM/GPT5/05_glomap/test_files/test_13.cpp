// File: rig_ba_pairwise_direction_error_test_13.cc

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <ceres/cost_function.h>

#include "glomap/estimators/cost_function.h"

namespace glomap {

class RigBATAPairwiseDirectionErrorTest_13 : public ::testing::Test {
 protected:
  RigBATAPairwiseDirectionErrorTest_13()
      : translation_obs_(1.0, 2.0, 3.0),
        translation_rig_(0.5, -1.0, 2.0),
        error_(translation_obs_, translation_rig_) {}

  Eigen::Vector3d translation_obs_;
  Eigen::Vector3d translation_rig_;
  RigBATAPairwiseDirectionError error_;
};

// Basic check that operator() computes expected residuals for typical values.
TEST_F(RigBATAPairwiseDirectionErrorTest_13, ComputesResidualsForDoubleInputs_13) {
  double position1[3] = {0.1, -0.2, 0.3};
  double position2[3] = {1.0, 0.5, -0.4};
  double scale[1]     = {2.0};
  double scale_rig[1] = {0.3};
  double residuals[3];

  bool ok = error_(position1, position2, scale, scale_rig, residuals);
  EXPECT_TRUE(ok);

  Eigen::Vector3d pos1(position1[0], position1[1], position1[2]);
  Eigen::Vector3d pos2(position2[0], position2[1], position2[2]);
  Eigen::Vector3d expected =
      translation_obs_ - scale[0] * (pos2 - pos1 + scale_rig[0] * translation_rig_);

  EXPECT_NEAR(expected[0], residuals[0], 1e-12);
  EXPECT_NEAR(expected[1], residuals[1], 1e-12);
  EXPECT_NEAR(expected[2], residuals[2], 1e-12);
}

// When scale is zero, residuals should equal the observed translation.
TEST_F(RigBATAPairwiseDirectionErrorTest_13, ZeroScaleLeavesObservedTranslation_13) {
  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {10.0, -5.0, 2.0};
  double scale[1]     = {0.0};
  double scale_rig[1] = {1.0};  // arbitrary, should not matter when scale == 0
  double residuals[3];

  bool ok = error_(position1, position2, scale, scale_rig, residuals);
  EXPECT_TRUE(ok);

  EXPECT_NEAR(translation_obs_[0], residuals[0], 1e-12);
  EXPECT_NEAR(translation_obs_[1], residuals[1], 1e-12);
  EXPECT_NEAR(translation_obs_[2], residuals[2], 1e-12);
}

// When rig translation is zero, the effect of scale_rig should disappear.
TEST_F(RigBATAPairwiseDirectionErrorTest_13, ZeroRigTranslationIgnoresScaleRig_13) {
  Eigen::Vector3d zero_rig(0.0, 0.0, 0.0);
  RigBATAPairwiseDirectionError error_zero_rig(translation_obs_, zero_rig);

  double position1[3] = {0.2, -0.1, 0.4};
  double position2[3] = {0.5, 0.7, -0.3};
  double scale[1]     = {1.5};
  double scale_rig1[1] = {0.0};
  double scale_rig2[1] = {100.0};
  double residuals1[3];
  double residuals2[3];

  bool ok1 = error_zero_rig(position1, position2, scale, scale_rig1, residuals1);
  bool ok2 = error_zero_rig(position1, position2, scale, scale_rig2, residuals2);
  EXPECT_TRUE(ok1);
  EXPECT_TRUE(ok2);

  // With zero rig translation, scale_rig should have no effect.
  EXPECT_NEAR(residuals1[0], residuals2[0], 1e-12);
  EXPECT_NEAR(residuals1[1], residuals2[1], 1e-12);
  EXPECT_NEAR(residuals1[2], residuals2[2], 1e-12);
}

// Static Create should return a valid CostFunction pointer.
TEST_F(RigBATAPairwiseDirectionErrorTest_13, CreateReturnsNonNullCostFunction_13) {
  ceres::CostFunction* cost_function =
      RigBATAPairwiseDirectionError::Create(translation_obs_, translation_rig_);
  EXPECT_NE(cost_function, nullptr);
  delete cost_function;
}

// The created CostFunction should expose the expected residual and parameter sizes.
TEST_F(RigBATAPairwiseDirectionErrorTest_13, CostFunctionHasExpectedDimensions_13) {
  ceres::CostFunction* cost_function =
      RigBATAPairwiseDirectionError::Create(translation_obs_, translation_rig_);
  ASSERT_NE(cost_function, nullptr);

  // From the operator() signature, we expect:
  // - 3 residuals (3D translation)
  // - 4 parameter blocks: position1(3), position2(3), scale(1), scale_rig(1)
  EXPECT_EQ(cost_function->num_residuals(), 3);

  const std::vector<int32_t>& param_sizes = cost_function->parameter_block_sizes();
  ASSERT_EQ(param_sizes.size(), 4u);
  EXPECT_EQ(param_sizes[0], 3);
  EXPECT_EQ(param_sizes[1], 3);
  EXPECT_EQ(param_sizes[2], 1);
  EXPECT_EQ(param_sizes[3], 1);

  delete cost_function;
}

// Evaluating the CostFunction should match directly calling the functor operator().
TEST_F(RigBATAPairwiseDirectionErrorTest_13, CostFunctionEvaluateMatchesFunctor_13) {
  ceres::CostFunction* cost_function =
      RigBATAPairwiseDirectionError::Create(translation_obs_, translation_rig_);
  ASSERT_NE(cost_function, nullptr);

  double position1[3] = {0.3, -0.6, 0.9};
  double position2[3] = {-0.1, 0.4, 0.2};
  double scale[1]     = {0.8};
  double scale_rig[1] = {-0.5};

  double residuals_functor[3];
  bool ok_functor = error_(position1, position2, scale, scale_rig, residuals_functor);
  ASSERT_TRUE(ok_functor);

  const double* parameters[4] = {position1, position2, scale, scale_rig};
  double residuals_cost[3];
  bool ok_cost = cost_function->Evaluate(parameters, residuals_cost, nullptr);
  ASSERT_TRUE(ok_cost);

  EXPECT_NEAR(residuals_functor[0], residuals_cost[0], 1e-12);
  EXPECT_NEAR(residuals_functor[1], residuals_cost[1], 1e-12);
  EXPECT_NEAR(residuals_functor[2], residuals_cost[2], 1e-12);

  delete cost_function;
}

}  // namespace glomap
