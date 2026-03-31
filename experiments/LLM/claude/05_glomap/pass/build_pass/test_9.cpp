#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <ceres/ceres.h>
#include "glomap/estimators/bundle_adjustment.h"

namespace glomap {
namespace {

class BundleAdjusterOptionsTest_9 : public ::testing::Test {
 protected:
  BundleAdjusterOptions options_;
};

// Test default construction and default values of boolean flags
TEST_F(BundleAdjusterOptionsTest_9, DefaultConstructionBoolFlags_9) {
  BundleAdjusterOptions opts;
  EXPECT_FALSE(opts.optimize_rig_poses);
  EXPECT_TRUE(opts.optimize_rotations);
  EXPECT_TRUE(opts.optimize_translation);
  EXPECT_TRUE(opts.optimize_intrinsics);
  EXPECT_FALSE(opts.optimize_principal_point);
  EXPECT_TRUE(opts.optimize_points);
}

// Test default value of use_gpu
TEST_F(BundleAdjusterOptionsTest_9, DefaultUseGpu_9) {
  BundleAdjusterOptions opts;
  EXPECT_TRUE(opts.use_gpu);
}

// Test default value of gpu_index
TEST_F(BundleAdjusterOptionsTest_9, DefaultGpuIndex_9) {
  BundleAdjusterOptions opts;
  EXPECT_EQ(opts.gpu_index, "-1");
}

// Test default value of min_num_images_gpu_solver
TEST_F(BundleAdjusterOptionsTest_9, DefaultMinNumImagesGpuSolver_9) {
  BundleAdjusterOptions opts;
  EXPECT_EQ(opts.min_num_images_gpu_solver, 50);
}

// Test default value of min_num_view_per_track
TEST_F(BundleAdjusterOptionsTest_9, DefaultMinNumViewPerTrack_9) {
  BundleAdjusterOptions opts;
  EXPECT_EQ(opts.min_num_view_per_track, 3);
}

// Test default value of thres_loss_function inherited from OptimizationBaseOptions
TEST_F(BundleAdjusterOptionsTest_9, DefaultThresLossFunction_9) {
  BundleAdjusterOptions opts;
  EXPECT_DOUBLE_EQ(opts.thres_loss_function, 0.1);
}

// Test CreateLossFunction returns a non-null shared_ptr
TEST_F(BundleAdjusterOptionsTest_9, CreateLossFunctionReturnsNonNull_9) {
  auto loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);
}

// Test CreateLossFunction returns a valid ceres loss function that can be evaluated
TEST_F(BundleAdjusterOptionsTest_9, CreateLossFunctionIsCallable_9) {
  auto loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);

  // Evaluate the Huber loss at a squared residual of 0
  double rho[3];
  loss->Evaluate(0.0, rho);
  EXPECT_DOUBLE_EQ(rho[0], 0.0);
}

// Test CreateLossFunction with default threshold behaves like HuberLoss(0.1)
TEST_F(BundleAdjusterOptionsTest_9, CreateLossFunctionHuberBehaviorSmallResidual_9) {
  auto loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);

  // For a small squared residual (s < thres^2 = 0.01), Huber loss rho(s) = s
  double rho[3];
  double s = 0.005;  // less than 0.01
  loss->Evaluate(s, rho);
  EXPECT_NEAR(rho[0], s, 1e-12);
}

// Test CreateLossFunction with default threshold for large residual
TEST_F(BundleAdjusterOptionsTest_9, CreateLossFunctionHuberBehaviorLargeResidual_9) {
  auto loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);

  // For a large squared residual (s > thres^2 = 0.01), Huber loss is sublinear
  double rho[3];
  double s = 1.0;  // much larger than 0.01
  loss->Evaluate(s, rho);
  // Huber: rho(s) = 2 * a * sqrt(s) - a^2, where a = thres_loss_function = 0.1
  // rho(1.0) = 2*0.1*1.0 - 0.01 = 0.19
  EXPECT_NEAR(rho[0], 0.19, 1e-10);
}

// Test CreateLossFunction after modifying thres_loss_function
TEST_F(BundleAdjusterOptionsTest_9, CreateLossFunctionWithModifiedThreshold_9) {
  options_.thres_loss_function = 1.0;
  auto loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);

  // With threshold = 1.0, for s = 0.5 (< 1.0^2 = 1.0), Huber rho(s) = s
  double rho[3];
  loss->Evaluate(0.5, rho);
  EXPECT_NEAR(rho[0], 0.5, 1e-12);
}

// Test CreateLossFunction with large threshold for large residual within quadratic region
TEST_F(BundleAdjusterOptionsTest_9, CreateLossFunctionLargeThresholdQuadraticRegion_9) {
  options_.thres_loss_function = 10.0;
  auto loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);

  // s = 50.0 < 100.0 (thres^2), should be in quadratic region: rho(s) = s
  double rho[3];
  loss->Evaluate(50.0, rho);
  EXPECT_NEAR(rho[0], 50.0, 1e-10);
}

// Test that modifying boolean options works
TEST_F(BundleAdjusterOptionsTest_9, ModifyBooleanOptions_9) {
  options_.optimize_rig_poses = true;
  EXPECT_TRUE(options_.optimize_rig_poses);

  options_.optimize_rotations = false;
  EXPECT_FALSE(options_.optimize_rotations);

  options_.optimize_translation = false;
  EXPECT_FALSE(options_.optimize_translation);

  options_.optimize_intrinsics = false;
  EXPECT_FALSE(options_.optimize_intrinsics);

  options_.optimize_principal_point = true;
  EXPECT_TRUE(options_.optimize_principal_point);

  options_.optimize_points = false;
  EXPECT_FALSE(options_.optimize_points);
}

// Test modifying gpu_index
TEST_F(BundleAdjusterOptionsTest_9, ModifyGpuIndex_9) {
  options_.gpu_index = "0";
  EXPECT_EQ(options_.gpu_index, "0");

  options_.gpu_index = "1,2";
  EXPECT_EQ(options_.gpu_index, "1,2");
}

// Test modifying min_num_images_gpu_solver
TEST_F(BundleAdjusterOptionsTest_9, ModifyMinNumImagesGpuSolver_9) {
  options_.min_num_images_gpu_solver = 100;
  EXPECT_EQ(options_.min_num_images_gpu_solver, 100);
}

// Test modifying min_num_view_per_track
TEST_F(BundleAdjusterOptionsTest_9, ModifyMinNumViewPerTrack_9) {
  options_.min_num_view_per_track = 5;
  EXPECT_EQ(options_.min_num_view_per_track, 5);
}

// Test CreateLossFunction at the boundary of quadratic/linear region
TEST_F(BundleAdjusterOptionsTest_9, CreateLossFunctionAtBoundary_9) {
  auto loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);

  // At s = thres^2 = 0.01, should be exactly at the boundary
  double rho[3];
  double s = options_.thres_loss_function * options_.thres_loss_function;
  loss->Evaluate(s, rho);
  // At the boundary, rho(s) = s for Huber loss
  EXPECT_NEAR(rho[0], s, 1e-12);
}

// Test that multiple calls to CreateLossFunction return independent objects
TEST_F(BundleAdjusterOptionsTest_9, CreateLossFunctionReturnsIndependentObjects_9) {
  auto loss1 = options_.CreateLossFunction();
  auto loss2 = options_.CreateLossFunction();
  ASSERT_NE(loss1, nullptr);
  ASSERT_NE(loss2, nullptr);
  EXPECT_NE(loss1.get(), loss2.get());
}

// Test CreateLossFunction with zero threshold
TEST_F(BundleAdjusterOptionsTest_9, CreateLossFunctionZeroThreshold_9) {
  options_.thres_loss_function = 0.0;
  auto loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);

  double rho[3];
  loss->Evaluate(0.0, rho);
  EXPECT_DOUBLE_EQ(rho[0], 0.0);
}

// Test CreateLossFunction with very small threshold
TEST_F(BundleAdjusterOptionsTest_9, CreateLossFunctionVerySmallThreshold_9) {
  options_.thres_loss_function = 1e-10;
  auto loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);

  double rho[3];
  loss->Evaluate(1.0, rho);
  // For large s relative to small threshold, result should be finite
  EXPECT_TRUE(std::isfinite(rho[0]));
}

}  // namespace
}  // namespace glomap
