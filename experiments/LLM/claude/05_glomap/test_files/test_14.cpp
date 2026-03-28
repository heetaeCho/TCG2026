#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <ceres/ceres.h>
#include "glomap/estimators/cost_function.h"

namespace glomap {
namespace {

class RigUnknownBATAPairwiseDirectionErrorTest_14 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Default identity quaternion and zero translation observation
    identity_quat_ = Eigen::Quaterniond::Identity();
    zero_translation_ = Eigen::Vector3d::Zero();
  }

  Eigen::Quaterniond identity_quat_;
  Eigen::Vector3d zero_translation_;
};

// Test that operator() returns true with identity rotation and zero inputs
TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, ReturnsTrue_IdentityRotation_14) {
  RigUnknownBATAPairwiseDirectionError error(zero_translation_, identity_quat_);

  double point3d[3] = {0.0, 0.0, 0.0};
  double rig_from_world_center[3] = {0.0, 0.0, 0.0};
  double cam_from_rig_center[3] = {0.0, 0.0, 0.0};
  double scale[1] = {1.0};
  double residuals[3] = {0.0, 0.0, 0.0};

  bool result = error(point3d, rig_from_world_center, cam_from_rig_center, scale, residuals);
  EXPECT_TRUE(result);
}

// Test residuals are zero when all inputs are zero and translation_obs is zero
TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, ZeroResiduals_AllZeroInputs_14) {
  RigUnknownBATAPairwiseDirectionError error(zero_translation_, identity_quat_);

  double point3d[3] = {0.0, 0.0, 0.0};
  double rig_from_world_center[3] = {0.0, 0.0, 0.0};
  double cam_from_rig_center[3] = {0.0, 0.0, 0.0};
  double scale[1] = {1.0};
  double residuals[3] = {999.0, 999.0, 999.0};

  error(point3d, rig_from_world_center, cam_from_rig_center, scale, residuals);

  EXPECT_NEAR(residuals[0], 0.0, 1e-12);
  EXPECT_NEAR(residuals[1], 0.0, 1e-12);
  EXPECT_NEAR(residuals[2], 0.0, 1e-12);
}

// Test: residuals = translation_obs when scale=0 and cam_from_rig_center=0
TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, ResidualEqualsTranslationObs_ZeroScale_14) {
  Eigen::Vector3d translation_obs(1.0, 2.0, 3.0);
  RigUnknownBATAPairwiseDirectionError error(translation_obs, identity_quat_);

  double point3d[3] = {5.0, 6.0, 7.0};
  double rig_from_world_center[3] = {1.0, 2.0, 3.0};
  double cam_from_rig_center[3] = {0.0, 0.0, 0.0};
  double scale[1] = {0.0};
  double residuals[3];

  error(point3d, rig_from_world_center, cam_from_rig_center, scale, residuals);

  // residuals = translation_obs - 0 * (...) - R^T * cam_from_rig_center
  // With cam_from_rig_center = 0, residuals = translation_obs
  EXPECT_NEAR(residuals[0], 1.0, 1e-12);
  EXPECT_NEAR(residuals[1], 2.0, 1e-12);
  EXPECT_NEAR(residuals[2], 3.0, 1e-12);
}

// Test with identity rotation, specific values
// residuals = translation_obs - scale * (point3d - rig_from_world_center - R^T * cam_from_rig_center)
// With identity R: R^T = I
// residuals = translation_obs - scale * (point3d - rig_from_world_center - cam_from_rig_center)
TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, CorrectResiduals_IdentityRotation_14) {
  Eigen::Vector3d translation_obs(10.0, 20.0, 30.0);
  RigUnknownBATAPairwiseDirectionError error(translation_obs, identity_quat_);

  double point3d[3] = {5.0, 6.0, 7.0};
  double rig_from_world_center[3] = {1.0, 2.0, 3.0};
  double cam_from_rig_center[3] = {0.5, 0.5, 0.5};
  double scale[1] = {2.0};
  double residuals[3];

  error(point3d, rig_from_world_center, cam_from_rig_center, scale, residuals);

  // expected: translation_obs - 2.0 * (point3d - rig_from_world_center - cam_from_rig_center)
  // = (10, 20, 30) - 2.0 * ((5,6,7) - (1,2,3) - (0.5,0.5,0.5))
  // = (10, 20, 30) - 2.0 * (3.5, 3.5, 3.5)
  // = (10, 20, 30) - (7, 7, 7)
  // = (3, 13, 23)
  EXPECT_NEAR(residuals[0], 3.0, 1e-12);
  EXPECT_NEAR(residuals[1], 13.0, 1e-12);
  EXPECT_NEAR(residuals[2], 23.0, 1e-12);
}

// Test with non-identity rotation (90 degree rotation around Z-axis)
TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, CorrectResiduals_NonIdentityRotation_14) {
  Eigen::Vector3d translation_obs(0.0, 0.0, 0.0);
  // 90 degree rotation around Z-axis
  Eigen::Quaterniond rot(Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitZ()));
  RigUnknownBATAPairwiseDirectionError error(translation_obs, rot);

  double point3d[3] = {0.0, 0.0, 0.0};
  double rig_from_world_center[3] = {0.0, 0.0, 0.0};
  double cam_from_rig_center[3] = {1.0, 0.0, 0.0};
  double scale[1] = {0.0};
  double residuals[3];

  error(point3d, rig_from_world_center, cam_from_rig_center, scale, residuals);

  // residuals = (0,0,0) - 0*(...) - R^T * cam_from_rig_center
  // Wait, the formula is:
  // translation_rig = R^T * cam_from_rig_center
  // residuals = translation_obs - scale * (point3d - rig_center - translation_rig)
  // = 0 - 0*(0 - 0 - R^T*(1,0,0))
  // = (0,0,0)
  // With scale=0, residuals should just be translation_obs = (0,0,0)
  EXPECT_NEAR(residuals[0], 0.0, 1e-12);
  EXPECT_NEAR(residuals[1], 0.0, 1e-12);
  EXPECT_NEAR(residuals[2], 0.0, 1e-12);
}

// Test with non-identity rotation and non-zero scale
TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, CorrectResiduals_NonIdentityRotation_NonZeroScale_14) {
  Eigen::Vector3d translation_obs(0.0, 0.0, 0.0);
  // 90 degree rotation around Z-axis: R maps (1,0,0) -> (0,1,0)
  // R^T maps (1,0,0) -> (0,-1,0)
  Eigen::Quaterniond rot(Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitZ()));
  RigUnknownBATAPairwiseDirectionError error(translation_obs, rot);

  double point3d[3] = {2.0, 0.0, 0.0};
  double rig_from_world_center[3] = {0.0, 0.0, 0.0};
  double cam_from_rig_center[3] = {1.0, 0.0, 0.0};
  double scale[1] = {1.0};
  double residuals[3];

  error(point3d, rig_from_world_center, cam_from_rig_center, scale, residuals);

  // translation_rig = R^T * (1,0,0) = (0, -1, 0)
  // residuals = (0,0,0) - 1.0 * ((2,0,0) - (0,0,0) - (0,-1,0))
  // = -(2, 1, 0)
  // = (-2, -1, 0)
  EXPECT_NEAR(residuals[0], -2.0, 1e-10);
  EXPECT_NEAR(residuals[1], -1.0, 1e-10);
  EXPECT_NEAR(residuals[2], 0.0, 1e-10);
}

// Test with negative scale
TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, NegativeScale_14) {
  Eigen::Vector3d translation_obs(0.0, 0.0, 0.0);
  RigUnknownBATAPairwiseDirectionError error(translation_obs, identity_quat_);

  double point3d[3] = {1.0, 0.0, 0.0};
  double rig_from_world_center[3] = {0.0, 0.0, 0.0};
  double cam_from_rig_center[3] = {0.0, 0.0, 0.0};
  double scale[1] = {-1.0};
  double residuals[3];

  error(point3d, rig_from_world_center, cam_from_rig_center, scale, residuals);

  // residuals = (0,0,0) - (-1)*((1,0,0) - (0,0,0) - (0,0,0)) = (1,0,0)
  EXPECT_NEAR(residuals[0], 1.0, 1e-12);
  EXPECT_NEAR(residuals[1], 0.0, 1e-12);
  EXPECT_NEAR(residuals[2], 0.0, 1e-12);
}

// Test with large values
TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, LargeValues_14) {
  Eigen::Vector3d translation_obs(1e6, 1e6, 1e6);
  RigUnknownBATAPairwiseDirectionError error(translation_obs, identity_quat_);

  double point3d[3] = {1e6, 1e6, 1e6};
  double rig_from_world_center[3] = {0.0, 0.0, 0.0};
  double cam_from_rig_center[3] = {0.0, 0.0, 0.0};
  double scale[1] = {1.0};
  double residuals[3];

  error(point3d, rig_from_world_center, cam_from_rig_center, scale, residuals);

  // residuals = (1e6,1e6,1e6) - 1.0*(1e6,1e6,1e6) = (0,0,0)
  EXPECT_NEAR(residuals[0], 0.0, 1e-6);
  EXPECT_NEAR(residuals[1], 0.0, 1e-6);
  EXPECT_NEAR(residuals[2], 0.0, 1e-6);
}

// Test with 180-degree rotation
TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, Rotation180Degrees_14) {
  Eigen::Vector3d translation_obs(0.0, 0.0, 0.0);
  Eigen::Quaterniond rot(Eigen::AngleAxisd(M_PI, Eigen::Vector3d::UnitZ()));
  RigUnknownBATAPairwiseDirectionError error(translation_obs, rot);

  double point3d[3] = {0.0, 0.0, 0.0};
  double rig_from_world_center[3] = {0.0, 0.0, 0.0};
  double cam_from_rig_center[3] = {1.0, 0.0, 0.0};
  double scale[1] = {1.0};
  double residuals[3];

  error(point3d, rig_from_world_center, cam_from_rig_center, scale, residuals);

  // R = 180 around Z: R^T * (1,0,0) = (-1, 0, 0)
  // translation_rig = (-1, 0, 0)
  // residuals = 0 - 1.0*(0 - 0 - (-1,0,0)) = -(1,0,0) = (-1,0,0)
  EXPECT_NEAR(residuals[0], -1.0, 1e-10);
  EXPECT_NEAR(residuals[1], 0.0, 1e-10);
  EXPECT_NEAR(residuals[2], 0.0, 1e-10);
}

// Test Create returns a non-null CostFunction
TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, CreateReturnsNonNull_14) {
  Eigen::Vector3d translation_obs(1.0, 2.0, 3.0);
  Eigen::Quaterniond rot = Eigen::Quaterniond::Identity();

  ceres::CostFunction* cost_function = RigUnknownBATAPairwiseDirectionError::Create(translation_obs, rot);
  ASSERT_NE(cost_function, nullptr);
  delete cost_function;
}

// Test CostFunction from Create evaluates correctly
TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, CreateCostFunctionEvaluates_14) {
  Eigen::Vector3d translation_obs(10.0, 20.0, 30.0);
  Eigen::Quaterniond rot = Eigen::Quaterniond::Identity();

  ceres::CostFunction* cost_function = RigUnknownBATAPairwiseDirectionError::Create(translation_obs, rot);
  ASSERT_NE(cost_function, nullptr);

  double point3d[3] = {5.0, 6.0, 7.0};
  double rig_from_world_center[3] = {1.0, 2.0, 3.0};
  double cam_from_rig_center[3] = {0.5, 0.5, 0.5};
  double scale[1] = {2.0};
  double residuals[3] = {0.0, 0.0, 0.0};

  const double* parameters[4] = {point3d, rig_from_world_center, cam_from_rig_center, scale};
  cost_function->Evaluate(parameters, residuals, nullptr);

  EXPECT_NEAR(residuals[0], 3.0, 1e-10);
  EXPECT_NEAR(residuals[1], 13.0, 1e-10);
  EXPECT_NEAR(residuals[2], 23.0, 1e-10);

  delete cost_function;
}

// Test with arbitrary rotation around arbitrary axis
TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, ArbitraryRotation_14) {
  Eigen::Vector3d translation_obs(1.0, 2.0, 3.0);
  Eigen::Vector3d axis = Eigen::Vector3d(1.0, 1.0, 1.0).normalized();
  double angle = M_PI / 3.0; // 60 degrees
  Eigen::Quaterniond rot(Eigen::AngleAxisd(angle, axis));
  RigUnknownBATAPairwiseDirectionError error(translation_obs, rot);

  double point3d[3] = {1.0, 2.0, 3.0};
  double rig_from_world_center[3] = {0.5, 0.5, 0.5};
  double cam_from_rig_center[3] = {0.1, 0.2, 0.3};
  double scale[1] = {1.5};
  double residuals[3];

  bool result = error(point3d, rig_from_world_center, cam_from_rig_center, scale, residuals);
  EXPECT_TRUE(result);

  // Compute expected values manually
  Eigen::Matrix3d R = rot.toRotationMatrix();
  Eigen::Vector3d cam_from_rig(0.1, 0.2, 0.3);
  Eigen::Vector3d translation_rig = R.transpose() * cam_from_rig;
  Eigen::Vector3d p(1.0, 2.0, 3.0);
  Eigen::Vector3d rig_center(0.5, 0.5, 0.5);
  Eigen::Vector3d expected = translation_obs - 1.5 * (p - rig_center - translation_rig);

  EXPECT_NEAR(residuals[0], expected[0], 1e-10);
  EXPECT_NEAR(residuals[1], expected[1], 1e-10);
  EXPECT_NEAR(residuals[2], expected[2], 1e-10);
}

// Test that point3d == rig_from_world_center + translation_rig gives residuals = translation_obs
TEST_F(RigUnknownBATAPairwiseDirectionErrorTest_14, PointEqualsRigCenterPlusTranslationRig_14) {
  Eigen::Vector3d translation_obs(7.0, 8.0, 9.0);
  Eigen::Quaterniond rot(Eigen::AngleAxisd(M_PI / 4.0, Eigen::Vector3d::UnitY()));
  RigUnknownBATAPairwiseDirectionError error(translation_obs, rot);

  Eigen::Vector3d cam_from_rig_vec(1.0, 2.0, 3.0);
  Eigen::Matrix3d R = rot.toRotationMatrix();
  Eigen::Vector3d translation_rig = R.transpose() * cam_from_rig_vec;

  Eigen::Vector3d rig_center(4.0, 5.0, 6.0);
  Eigen::Vector3d point = rig_center + translation_rig;

  double point3d[3] = {point[0], point[1], point[2]};
  double rig_from_world_center[3] = {rig_center[0], rig_center[1], rig_center[2]};
  double cam_from_rig_center[3] = {cam_from_rig_vec[0], cam_from_rig_vec[1], cam_from_rig_vec[2]};
  double scale[1] = {1.0};
  double residuals[3];

  error(point3d, rig_from_world_center, cam_from_rig_center, scale, residuals);

  // residuals = translation_obs - 1.0 * (point - rig_center - translation_rig) = translation_obs - 0 = translation_obs
  EXPECT_NEAR(residuals[0], 7.0, 1e-10);
  EXPECT_NEAR(residuals[1], 8.0, 1e-10);
  EXPECT_NEAR(residuals[2], 9.0, 1e-10);
}

}  // namespace
}  // namespace glomap
