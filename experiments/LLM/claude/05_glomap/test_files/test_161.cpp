#include <gtest/gtest.h>
#include "glomap/estimators/bundle_adjustment.h"

namespace glomap {
namespace {

// Test fixture for BundleAdjusterOptions
class BundleAdjusterOptionsTest_161 : public ::testing::Test {
 protected:
  BundleAdjusterOptions options_;
};

// Test default constructor sets thres_loss_function to 1.0
TEST_F(BundleAdjusterOptionsTest_161, DefaultThresLossFunction_161) {
  EXPECT_DOUBLE_EQ(options_.thres_loss_function, 1.0);
}

// Test default constructor sets max_num_iterations to 200
TEST_F(BundleAdjusterOptionsTest_161, DefaultMaxNumIterations_161) {
  EXPECT_EQ(options_.solver_options.max_num_iterations, 200);
}

// Test default value of optimize_rig_poses
TEST_F(BundleAdjusterOptionsTest_161, DefaultOptimizeRigPoses_161) {
  EXPECT_FALSE(options_.optimize_rig_poses);
}

// Test default value of optimize_rotations
TEST_F(BundleAdjusterOptionsTest_161, DefaultOptimizeRotations_161) {
  EXPECT_TRUE(options_.optimize_rotations);
}

// Test default value of optimize_translation
TEST_F(BundleAdjusterOptionsTest_161, DefaultOptimizeTranslation_161) {
  EXPECT_TRUE(options_.optimize_translation);
}

// Test default value of optimize_intrinsics
TEST_F(BundleAdjusterOptionsTest_161, DefaultOptimizeIntrinsics_161) {
  EXPECT_TRUE(options_.optimize_intrinsics);
}

// Test default value of optimize_principal_point
TEST_F(BundleAdjusterOptionsTest_161, DefaultOptimizePrincipalPoint_161) {
  EXPECT_FALSE(options_.optimize_principal_point);
}

// Test default value of optimize_points
TEST_F(BundleAdjusterOptionsTest_161, DefaultOptimizePoints_161) {
  EXPECT_TRUE(options_.optimize_points);
}

// Test default value of use_gpu
TEST_F(BundleAdjusterOptionsTest_161, DefaultUseGpu_161) {
  EXPECT_TRUE(options_.use_gpu);
}

// Test default value of gpu_index
TEST_F(BundleAdjusterOptionsTest_161, DefaultGpuIndex_161) {
  EXPECT_EQ(options_.gpu_index, "-1");
}

// Test default value of min_num_images_gpu_solver
TEST_F(BundleAdjusterOptionsTest_161, DefaultMinNumImagesGpuSolver_161) {
  EXPECT_EQ(options_.min_num_images_gpu_solver, 50);
}

// Test default value of min_num_view_per_track
TEST_F(BundleAdjusterOptionsTest_161, DefaultMinNumViewPerTrack_161) {
  EXPECT_EQ(options_.min_num_view_per_track, 3);
}

// Test modifying optimize_rotations
TEST_F(BundleAdjusterOptionsTest_161, ModifyOptimizeRotations_161) {
  options_.optimize_rotations = false;
  EXPECT_FALSE(options_.optimize_rotations);
}

// Test modifying optimize_translation
TEST_F(BundleAdjusterOptionsTest_161, ModifyOptimizeTranslation_161) {
  options_.optimize_translation = false;
  EXPECT_FALSE(options_.optimize_translation);
}

// Test modifying optimize_intrinsics
TEST_F(BundleAdjusterOptionsTest_161, ModifyOptimizeIntrinsics_161) {
  options_.optimize_intrinsics = false;
  EXPECT_FALSE(options_.optimize_intrinsics);
}

// Test modifying optimize_points
TEST_F(BundleAdjusterOptionsTest_161, ModifyOptimizePoints_161) {
  options_.optimize_points = false;
  EXPECT_FALSE(options_.optimize_points);
}

// Test modifying thres_loss_function
TEST_F(BundleAdjusterOptionsTest_161, ModifyThresLossFunction_161) {
  options_.thres_loss_function = 2.5;
  EXPECT_DOUBLE_EQ(options_.thres_loss_function, 2.5);
}

// Test modifying solver_options max_num_iterations
TEST_F(BundleAdjusterOptionsTest_161, ModifySolverMaxIterations_161) {
  options_.solver_options.max_num_iterations = 500;
  EXPECT_EQ(options_.solver_options.max_num_iterations, 500);
}

// Test modifying gpu_index
TEST_F(BundleAdjusterOptionsTest_161, ModifyGpuIndex_161) {
  options_.gpu_index = "0";
  EXPECT_EQ(options_.gpu_index, "0");
}

// Test modifying min_num_images_gpu_solver
TEST_F(BundleAdjusterOptionsTest_161, ModifyMinNumImagesGpuSolver_161) {
  options_.min_num_images_gpu_solver = 100;
  EXPECT_EQ(options_.min_num_images_gpu_solver, 100);
}

// Test modifying min_num_view_per_track
TEST_F(BundleAdjusterOptionsTest_161, ModifyMinNumViewPerTrack_161) {
  options_.min_num_view_per_track = 5;
  EXPECT_EQ(options_.min_num_view_per_track, 5);
}

// Test CreateLossFunction returns a non-null pointer
TEST_F(BundleAdjusterOptionsTest_161, CreateLossFunctionNotNull_161) {
  auto loss_function = options_.CreateLossFunction();
  EXPECT_NE(loss_function, nullptr);
}

// Test CreateLossFunction with different thresholds
TEST_F(BundleAdjusterOptionsTest_161, CreateLossFunctionWithDifferentThreshold_161) {
  options_.thres_loss_function = 5.0;
  auto loss_function = options_.CreateLossFunction();
  EXPECT_NE(loss_function, nullptr);
}

// Test copy construction preserves values
TEST_F(BundleAdjusterOptionsTest_161, CopyConstruction_161) {
  options_.optimize_rotations = false;
  options_.thres_loss_function = 3.0;
  options_.min_num_view_per_track = 10;

  BundleAdjusterOptions copy = options_;
  EXPECT_FALSE(copy.optimize_rotations);
  EXPECT_DOUBLE_EQ(copy.thres_loss_function, 3.0);
  EXPECT_EQ(copy.min_num_view_per_track, 10);
}

// Test that BundleAdjusterOptions inherits from OptimizationBaseOptions
TEST_F(BundleAdjusterOptionsTest_161, InheritsFromOptimizationBaseOptions_161) {
  OptimizationBaseOptions* base_ptr = &options_;
  EXPECT_NE(base_ptr, nullptr);
}

// Test boundary: min_num_view_per_track set to 0
TEST_F(BundleAdjusterOptionsTest_161, BoundaryMinNumViewPerTrackZero_161) {
  options_.min_num_view_per_track = 0;
  EXPECT_EQ(options_.min_num_view_per_track, 0);
}

// Test boundary: min_num_images_gpu_solver set to 0
TEST_F(BundleAdjusterOptionsTest_161, BoundaryMinNumImagesGpuSolverZero_161) {
  options_.min_num_images_gpu_solver = 0;
  EXPECT_EQ(options_.min_num_images_gpu_solver, 0);
}

// Test boundary: thres_loss_function set to 0
TEST_F(BundleAdjusterOptionsTest_161, BoundaryThresLossFunctionZero_161) {
  options_.thres_loss_function = 0.0;
  EXPECT_DOUBLE_EQ(options_.thres_loss_function, 0.0);
}

// Test multiple instances are independent
TEST_F(BundleAdjusterOptionsTest_161, MultipleInstancesIndependent_161) {
  BundleAdjusterOptions options2;
  options_.optimize_rotations = false;
  EXPECT_FALSE(options_.optimize_rotations);
  EXPECT_TRUE(options2.optimize_rotations);
}

}  // namespace
}  // namespace glomap
