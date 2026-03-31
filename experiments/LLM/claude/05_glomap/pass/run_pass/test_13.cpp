#include <gtest/gtest.h>
#include <Eigen/Core>
#include <ceres/ceres.h>
#include "glomap/estimators/cost_function.h"

namespace glomap {
namespace {

class RigBATAPairwiseDirectionErrorTest_13 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test that operator() returns true for basic inputs
TEST_F(RigBATAPairwiseDirectionErrorTest_13, OperatorReturnsTrue_13) {
  Eigen::Vector3d translation_obs(1.0, 2.0, 3.0);
  Eigen::Vector3d translation_rig(0.1, 0.2, 0.3);
  RigBATAPairwiseDirectionError error(translation_obs, translation_rig);

  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {1.0, 1.0, 1.0};
  double scale[1] = {1.0};
  double scale_rig[1] = {1.0};
  double residuals[3] = {0.0, 0.0, 0.0};

  bool result = error(position1, position2, scale, scale_rig, residuals);
  EXPECT_TRUE(result);
}

// Test residual computation with zero positions
TEST_F(RigBATAPairwiseDirectionErrorTest_13, ZeroPositions_13) {
  Eigen::Vector3d translation_obs(1.0, 2.0, 3.0);
  Eigen::Vector3d translation_rig(0.5, 0.5, 0.5);
  RigBATAPairwiseDirectionError error(translation_obs, translation_rig);

  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {0.0, 0.0, 0.0};
  double scale[1] = {1.0};
  double scale_rig[1] = {1.0};
  double residuals[3];

  error(position1, position2, scale, scale_rig, residuals);

  // residuals = translation_obs - scale * (position2 - position1 + scale_rig * translation_rig)
  // = (1,2,3) - 1.0 * ((0,0,0) - (0,0,0) + 1.0 * (0.5,0.5,0.5))
  // = (1,2,3) - (0.5,0.5,0.5) = (0.5, 1.5, 2.5)
  EXPECT_DOUBLE_EQ(residuals[0], 0.5);
  EXPECT_DOUBLE_EQ(residuals[1], 1.5);
  EXPECT_DOUBLE_EQ(residuals[2], 2.5);
}

// Test residual computation with non-zero positions
TEST_F(RigBATAPairwiseDirectionErrorTest_13, NonZeroPositions_13) {
  Eigen::Vector3d translation_obs(5.0, 5.0, 5.0);
  Eigen::Vector3d translation_rig(1.0, 1.0, 1.0);
  RigBATAPairwiseDirectionError error(translation_obs, translation_rig);

  double position1[3] = {1.0, 2.0, 3.0};
  double position2[3] = {4.0, 5.0, 6.0};
  double scale[1] = {1.0};
  double scale_rig[1] = {0.0};
  double residuals[3];

  error(position1, position2, scale, scale_rig, residuals);

  // residuals = (5,5,5) - 1.0 * ((4,5,6) - (1,2,3) + 0.0 * (1,1,1))
  // = (5,5,5) - (3,3,3) = (2,2,2)
  EXPECT_DOUBLE_EQ(residuals[0], 2.0);
  EXPECT_DOUBLE_EQ(residuals[1], 2.0);
  EXPECT_DOUBLE_EQ(residuals[2], 2.0);
}

// Test with scale factor applied
TEST_F(RigBATAPairwiseDirectionErrorTest_13, ScaleFactorEffect_13) {
  Eigen::Vector3d translation_obs(10.0, 10.0, 10.0);
  Eigen::Vector3d translation_rig(0.0, 0.0, 0.0);
  RigBATAPairwiseDirectionError error(translation_obs, translation_rig);

  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {2.0, 2.0, 2.0};
  double scale[1] = {3.0};
  double scale_rig[1] = {1.0};
  double residuals[3];

  error(position1, position2, scale, scale_rig, residuals);

  // residuals = (10,10,10) - 3.0 * ((2,2,2) - (0,0,0) + 1.0 * (0,0,0))
  // = (10,10,10) - (6,6,6) = (4,4,4)
  EXPECT_DOUBLE_EQ(residuals[0], 4.0);
  EXPECT_DOUBLE_EQ(residuals[1], 4.0);
  EXPECT_DOUBLE_EQ(residuals[2], 4.0);
}

// Test with rig scale factor applied
TEST_F(RigBATAPairwiseDirectionErrorTest_13, RigScaleFactorEffect_13) {
  Eigen::Vector3d translation_obs(10.0, 10.0, 10.0);
  Eigen::Vector3d translation_rig(1.0, 2.0, 3.0);
  RigBATAPairwiseDirectionError error(translation_obs, translation_rig);

  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {1.0, 1.0, 1.0};
  double scale[1] = {1.0};
  double scale_rig[1] = {2.0};
  double residuals[3];

  error(position1, position2, scale, scale_rig, residuals);

  // residuals = (10,10,10) - 1.0 * ((1,1,1) - (0,0,0) + 2.0 * (1,2,3))
  // = (10,10,10) - (1+2, 1+4, 1+6) = (10,10,10) - (3,5,7) = (7,5,3)
  EXPECT_DOUBLE_EQ(residuals[0], 7.0);
  EXPECT_DOUBLE_EQ(residuals[1], 5.0);
  EXPECT_DOUBLE_EQ(residuals[2], 3.0);
}

// Test zero residual case (perfect match)
TEST_F(RigBATAPairwiseDirectionErrorTest_13, ZeroResidual_13) {
  Eigen::Vector3d translation_obs(3.0, 3.0, 3.0);
  Eigen::Vector3d translation_rig(0.0, 0.0, 0.0);
  RigBATAPairwiseDirectionError error(translation_obs, translation_rig);

  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {3.0, 3.0, 3.0};
  double scale[1] = {1.0};
  double scale_rig[1] = {1.0};
  double residuals[3];

  error(position1, position2, scale, scale_rig, residuals);

  EXPECT_DOUBLE_EQ(residuals[0], 0.0);
  EXPECT_DOUBLE_EQ(residuals[1], 0.0);
  EXPECT_DOUBLE_EQ(residuals[2], 0.0);
}

// Test with negative values
TEST_F(RigBATAPairwiseDirectionErrorTest_13, NegativeValues_13) {
  Eigen::Vector3d translation_obs(-1.0, -2.0, -3.0);
  Eigen::Vector3d translation_rig(-0.5, -0.5, -0.5);
  RigBATAPairwiseDirectionError error(translation_obs, translation_rig);

  double position1[3] = {1.0, 1.0, 1.0};
  double position2[3] = {-1.0, -1.0, -1.0};
  double scale[1] = {1.0};
  double scale_rig[1] = {1.0};
  double residuals[3];

  error(position1, position2, scale, scale_rig, residuals);

  // residuals = (-1,-2,-3) - 1.0 * ((-1,-1,-1) - (1,1,1) + 1.0*(-0.5,-0.5,-0.5))
  // = (-1,-2,-3) - (-2-0.5, -2-0.5, -2-0.5) = (-1,-2,-3) - (-2.5,-2.5,-2.5) = (1.5, 0.5, -0.5)
  EXPECT_DOUBLE_EQ(residuals[0], 1.5);
  EXPECT_DOUBLE_EQ(residuals[1], 0.5);
  EXPECT_DOUBLE_EQ(residuals[2], -0.5);
}

// Test with zero scale
TEST_F(RigBATAPairwiseDirectionErrorTest_13, ZeroScale_13) {
  Eigen::Vector3d translation_obs(5.0, 6.0, 7.0);
  Eigen::Vector3d translation_rig(1.0, 1.0, 1.0);
  RigBATAPairwiseDirectionError error(translation_obs, translation_rig);

  double position1[3] = {1.0, 2.0, 3.0};
  double position2[3] = {4.0, 5.0, 6.0};
  double scale[1] = {0.0};
  double scale_rig[1] = {1.0};
  double residuals[3];

  error(position1, position2, scale, scale_rig, residuals);

  // residuals = (5,6,7) - 0.0 * (...) = (5,6,7)
  EXPECT_DOUBLE_EQ(residuals[0], 5.0);
  EXPECT_DOUBLE_EQ(residuals[1], 6.0);
  EXPECT_DOUBLE_EQ(residuals[2], 7.0);
}

// Test with zero rig scale
TEST_F(RigBATAPairwiseDirectionErrorTest_13, ZeroRigScale_13) {
  Eigen::Vector3d translation_obs(5.0, 6.0, 7.0);
  Eigen::Vector3d translation_rig(100.0, 200.0, 300.0);
  RigBATAPairwiseDirectionError error(translation_obs, translation_rig);

  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {1.0, 1.0, 1.0};
  double scale[1] = {1.0};
  double scale_rig[1] = {0.0};
  double residuals[3];

  error(position1, position2, scale, scale_rig, residuals);

  // residuals = (5,6,7) - 1.0 * ((1,1,1) - (0,0,0) + 0.0*(100,200,300))
  // = (5,6,7) - (1,1,1) = (4,5,6)
  EXPECT_DOUBLE_EQ(residuals[0], 4.0);
  EXPECT_DOUBLE_EQ(residuals[1], 5.0);
  EXPECT_DOUBLE_EQ(residuals[2], 6.0);
}

// Test Create returns a valid cost function
TEST_F(RigBATAPairwiseDirectionErrorTest_13, CreateReturnsCostFunction_13) {
  Eigen::Vector3d translation_obs(1.0, 2.0, 3.0);
  Eigen::Vector3d translation_rig(0.1, 0.2, 0.3);

  ceres::CostFunction* cost_function =
      RigBATAPairwiseDirectionError::Create(translation_obs, translation_rig);

  ASSERT_NE(cost_function, nullptr);
  
  // Verify parameter block sizes and residual size
  EXPECT_EQ(cost_function->num_residuals(), 3);
  
  const std::vector<int32_t>& param_sizes = cost_function->parameter_block_sizes();
  ASSERT_EQ(param_sizes.size(), 4);
  EXPECT_EQ(param_sizes[0], 3);  // position1
  EXPECT_EQ(param_sizes[1], 3);  // position2
  EXPECT_EQ(param_sizes[2], 1);  // scale
  EXPECT_EQ(param_sizes[3], 1);  // scale_rig

  delete cost_function;
}

// Test Create cost function evaluation matches direct operator() call
TEST_F(RigBATAPairwiseDirectionErrorTest_13, CreateCostFunctionEvaluation_13) {
  Eigen::Vector3d translation_obs(3.0, 4.0, 5.0);
  Eigen::Vector3d translation_rig(0.5, 0.5, 0.5);

  ceres::CostFunction* cost_function =
      RigBATAPairwiseDirectionError::Create(translation_obs, translation_rig);

  double position1[3] = {1.0, 0.0, 0.0};
  double position2[3] = {2.0, 1.0, 1.0};
  double scale[1] = {2.0};
  double scale_rig[1] = {0.5};
  double residuals[3];

  const double* parameters[4] = {position1, position2, scale, scale_rig};
  cost_function->Evaluate(parameters, residuals, nullptr);

  // residuals = (3,4,5) - 2.0 * ((2,1,1) - (1,0,0) + 0.5*(0.5,0.5,0.5))
  // = (3,4,5) - 2.0 * (1+0.25, 1+0.25, 1+0.25) = (3,4,5) - 2.0*(1.25,1.25,1.25)
  // = (3,4,5) - (2.5,2.5,2.5) = (0.5, 1.5, 2.5)
  EXPECT_NEAR(residuals[0], 0.5, 1e-10);
  EXPECT_NEAR(residuals[1], 1.5, 1e-10);
  EXPECT_NEAR(residuals[2], 2.5, 1e-10);

  delete cost_function;
}

// Test with large values
TEST_F(RigBATAPairwiseDirectionErrorTest_13, LargeValues_13) {
  Eigen::Vector3d translation_obs(1e6, 1e6, 1e6);
  Eigen::Vector3d translation_rig(1e3, 1e3, 1e3);
  RigBATAPairwiseDirectionError error(translation_obs, translation_rig);

  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {1e5, 1e5, 1e5};
  double scale[1] = {1.0};
  double scale_rig[1] = {1.0};
  double residuals[3];

  error(position1, position2, scale, scale_rig, residuals);

  // residuals = (1e6,1e6,1e6) - 1.0 * ((1e5,1e5,1e5) + (1e3,1e3,1e3))
  // = (1e6,1e6,1e6) - (101000,101000,101000) = (899000,899000,899000)
  EXPECT_DOUBLE_EQ(residuals[0], 899000.0);
  EXPECT_DOUBLE_EQ(residuals[1], 899000.0);
  EXPECT_DOUBLE_EQ(residuals[2], 899000.0);
}

// Test with very small values
TEST_F(RigBATAPairwiseDirectionErrorTest_13, SmallValues_13) {
  Eigen::Vector3d translation_obs(1e-10, 2e-10, 3e-10);
  Eigen::Vector3d translation_rig(1e-12, 1e-12, 1e-12);
  RigBATAPairwiseDirectionError error(translation_obs, translation_rig);

  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {0.0, 0.0, 0.0};
  double scale[1] = {1.0};
  double scale_rig[1] = {1.0};
  double residuals[3];

  error(position1, position2, scale, scale_rig, residuals);

  // residuals = (1e-10,2e-10,3e-10) - 1.0*(0+1e-12, 0+1e-12, 0+1e-12)
  EXPECT_NEAR(residuals[0], 1e-10 - 1e-12, 1e-20);
  EXPECT_NEAR(residuals[1], 2e-10 - 1e-12, 1e-20);
  EXPECT_NEAR(residuals[2], 3e-10 - 1e-12, 1e-20);
}

// Test combined scale and rig_scale interaction
TEST_F(RigBATAPairwiseDirectionErrorTest_13, CombinedScaleInteraction_13) {
  Eigen::Vector3d translation_obs(0.0, 0.0, 0.0);
  Eigen::Vector3d translation_rig(1.0, 0.0, 0.0);
  RigBATAPairwiseDirectionError error(translation_obs, translation_rig);

  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {0.0, 0.0, 0.0};
  double scale[1] = {3.0};
  double scale_rig[1] = {2.0};
  double residuals[3];

  error(position1, position2, scale, scale_rig, residuals);

  // residuals = (0,0,0) - 3.0 * ((0,0,0) - (0,0,0) + 2.0*(1,0,0))
  // = (0,0,0) - 3.0*(2,0,0) = (-6, 0, 0)
  EXPECT_DOUBLE_EQ(residuals[0], -6.0);
  EXPECT_DOUBLE_EQ(residuals[1], 0.0);
  EXPECT_DOUBLE_EQ(residuals[2], 0.0);
}

// Test that position1 subtracts correctly from position2
TEST_F(RigBATAPairwiseDirectionErrorTest_13, PositionDifferenceSign_13) {
  Eigen::Vector3d translation_obs(0.0, 0.0, 0.0);
  Eigen::Vector3d translation_rig(0.0, 0.0, 0.0);
  RigBATAPairwiseDirectionError error(translation_obs, translation_rig);

  double position1[3] = {5.0, 5.0, 5.0};
  double position2[3] = {2.0, 2.0, 2.0};
  double scale[1] = {1.0};
  double scale_rig[1] = {0.0};
  double residuals[3];

  error(position1, position2, scale, scale_rig, residuals);

  // residuals = (0,0,0) - 1.0 * ((2,2,2)-(5,5,5)) = -(-3,-3,-3) = (3,3,3)
  EXPECT_DOUBLE_EQ(residuals[0], 3.0);
  EXPECT_DOUBLE_EQ(residuals[1], 3.0);
  EXPECT_DOUBLE_EQ(residuals[2], 3.0);
}

// Test negative scale
TEST_F(RigBATAPairwiseDirectionErrorTest_13, NegativeScale_13) {
  Eigen::Vector3d translation_obs(0.0, 0.0, 0.0);
  Eigen::Vector3d translation_rig(0.0, 0.0, 0.0);
  RigBATAPairwiseDirectionError error(translation_obs, translation_rig);

  double position1[3] = {0.0, 0.0, 0.0};
  double position2[3] = {1.0, 2.0, 3.0};
  double scale[1] = {-1.0};
  double scale_rig[1] = {1.0};
  double residuals[3];

  error(position1, position2, scale, scale_rig, residuals);

  // residuals = (0,0,0) - (-1.0) * ((1,2,3) - (0,0,0) + 0) = (1,2,3)
  EXPECT_DOUBLE_EQ(residuals[0], 1.0);
  EXPECT_DOUBLE_EQ(residuals[1], 2.0);
  EXPECT_DOUBLE_EQ(residuals[2], 3.0);
}

}  // namespace
}  // namespace glomap
