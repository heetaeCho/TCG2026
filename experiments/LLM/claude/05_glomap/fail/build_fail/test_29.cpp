#include <gtest/gtest.h>
#include "glomap/estimators/global_rotation_averaging.h"
#include "glomap/scene/view_graph.h"
#include "glomap/types.h"

#include <unordered_map>
#include <Eigen/Core>

namespace glomap {
namespace {

// Helper to create a simple view graph with image pairs
// We build a minimal scenario: a few images connected by pairs
class RotationEstimatorTest_29 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Default options
    options_.max_num_l1_iterations = 5;
    options_.l1_step_convergence_threshold = 0.001;
    options_.max_num_irls_iterations = 100;
    options_.irls_step_convergence_threshold = 0.001;
    options_.irls_loss_parameter_sigma = 5.0;
    options_.skip_initialization = false;
    options_.use_weight = false;
    options_.use_gravity = false;
  }

  void CreateSimpleScene(int num_images) {
    // Create images, frames, and rigs
    for (int i = 0; i < num_images; i++) {
      Image img;
      img.camera_id = 0;
      img.frame_id = i;
      img.is_registered = true;
      // Set identity rotation as initial
      img.cam_from_world = Eigen::Matrix3x4d::Identity();
      images_[i] = img;

      Frame frame;
      frame.is_registered = true;
      frames_[i] = frame;
    }

    Rig rig;
    rigs_[0] = rig;

    // Create image pairs forming a chain: 0-1, 1-2, 2-3, ...
    for (int i = 0; i < num_images - 1; i++) {
      image_pair_t pair_id =
          static_cast<image_pair_t>(i) * 2147483647 + (i + 1);
      ImagePair pair;
      pair.image_id1 = i;
      pair.image_id2 = i + 1;
      pair.is_valid = true;
      // Set relative rotation to identity (no rotation between views)
      pair.cam2_from_cam1 = Eigen::Matrix3x4d::Identity();
      view_graph_.image_pairs[pair_id] = pair;
    }
  }

  RotationEstimatorOptions options_;
  ViewGraph view_graph_;
  std::unordered_map<rig_t, Rig> rigs_;
  std::unordered_map<frame_t, Frame> frames_;
  std::unordered_map<image_t, Image> images_;
};

// Test: Default options construction
TEST_F(RotationEstimatorTest_29, DefaultOptionsConstruction_29) {
  RotationEstimatorOptions opts;
  EXPECT_EQ(opts.max_num_l1_iterations, 5);
  EXPECT_DOUBLE_EQ(opts.l1_step_convergence_threshold, 0.001);
  EXPECT_EQ(opts.max_num_irls_iterations, 100);
  EXPECT_DOUBLE_EQ(opts.irls_step_convergence_threshold, 0.001);
  EXPECT_DOUBLE_EQ(opts.irls_loss_parameter_sigma, 5.0);
  EXPECT_FALSE(opts.skip_initialization);
  EXPECT_FALSE(opts.use_weight);
  EXPECT_FALSE(opts.use_gravity);
}

// Test: RotationEstimator can be constructed with options
TEST_F(RotationEstimatorTest_29, Construction_29) {
  EXPECT_NO_THROW(RotationEstimator estimator(options_));
}

// Test: Empty view graph (no image pairs)
TEST_F(RotationEstimatorTest_29, EmptyViewGraph_29) {
  RotationEstimator estimator(options_);
  // With empty view graph and empty data, the function may return true or false
  // but should not crash
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  // We simply verify it doesn't crash; the result depends on implementation
  (void)result;
}

// Test: Single image - no pairs
TEST_F(RotationEstimatorTest_29, SingleImage_29) {
  Image img;
  img.camera_id = 0;
  img.frame_id = 0;
  img.is_registered = true;
  img.cam_from_world = Eigen::Matrix3x4d::Identity();
  images_[0] = img;

  Frame frame;
  frame.is_registered = true;
  frames_[0] = frame;

  Rig rig;
  rigs_[0] = rig;

  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  (void)result;  // Should not crash
}

// Test: Two images with identity relative rotation
TEST_F(RotationEstimatorTest_29, TwoImagesIdentityRotation_29) {
  CreateSimpleScene(2);
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  // For a valid simple scene, we expect success
  EXPECT_TRUE(result);
}

// Test: Three images in a chain
TEST_F(RotationEstimatorTest_29, ThreeImagesChain_29) {
  CreateSimpleScene(3);
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  EXPECT_TRUE(result);
}

// Test: Multiple images forming a larger chain
TEST_F(RotationEstimatorTest_29, LargerChain_29) {
  CreateSimpleScene(10);
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  EXPECT_TRUE(result);
}

// Test: Custom options - single L1 iteration
TEST_F(RotationEstimatorTest_29, SingleL1Iteration_29) {
  options_.max_num_l1_iterations = 1;
  CreateSimpleScene(3);
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  EXPECT_TRUE(result);
}

// Test: Custom options - zero L1 iterations
TEST_F(RotationEstimatorTest_29, ZeroL1Iterations_29) {
  options_.max_num_l1_iterations = 0;
  CreateSimpleScene(3);
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  // With zero L1 iterations, L1 regression loop won't execute
  EXPECT_TRUE(result);
}

// Test: Custom options - zero IRLS iterations
TEST_F(RotationEstimatorTest_29, ZeroIRLSIterations_29) {
  options_.max_num_irls_iterations = 0;
  CreateSimpleScene(3);
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  EXPECT_TRUE(result);
}

// Test: With use_weight enabled
TEST_F(RotationEstimatorTest_29, UseWeightEnabled_29) {
  options_.use_weight = true;
  CreateSimpleScene(3);
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  EXPECT_TRUE(result);
}

// Test: With skip_initialization enabled
TEST_F(RotationEstimatorTest_29, SkipInitialization_29) {
  options_.skip_initialization = true;
  CreateSimpleScene(3);
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  EXPECT_TRUE(result);
}

// Test: Very high convergence threshold (should converge quickly)
TEST_F(RotationEstimatorTest_29, HighConvergenceThreshold_29) {
  options_.l1_step_convergence_threshold = 1e6;
  options_.irls_step_convergence_threshold = 1e6;
  CreateSimpleScene(3);
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  EXPECT_TRUE(result);
}

// Test: Very low convergence threshold
TEST_F(RotationEstimatorTest_29, LowConvergenceThreshold_29) {
  options_.l1_step_convergence_threshold = 1e-15;
  options_.irls_step_convergence_threshold = 1e-15;
  options_.max_num_l1_iterations = 2;
  options_.max_num_irls_iterations = 2;
  CreateSimpleScene(3);
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  EXPECT_TRUE(result);
}

// Test: EPS constant value
TEST_F(RotationEstimatorTest_29, EPSConstantValue_29) {
  EXPECT_DOUBLE_EQ(EPS, 9.9999999999999998E-13);
}

// Test: With invalid image pairs (is_valid = false)
TEST_F(RotationEstimatorTest_29, InvalidImagePairs_29) {
  CreateSimpleScene(3);
  // Mark all pairs as invalid
  for (auto& [id, pair] : view_graph_.image_pairs) {
    pair.is_valid = false;
  }
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  (void)result;  // Should not crash
}

// Test: Multiple calls to EstimateRotations
TEST_F(RotationEstimatorTest_29, MultipleCalls_29) {
  CreateSimpleScene(3);
  RotationEstimator estimator(options_);
  bool result1 = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  bool result2 = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  EXPECT_EQ(result1, result2);
}

// Test: Different weight types
TEST_F(RotationEstimatorTest_29, GemanMcClureWeightType_29) {
  options_.weight_type = RotationEstimatorOptions::GEMAN_MCCLURE;
  CreateSimpleScene(3);
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  EXPECT_TRUE(result);
}

// Test: Large number of iterations allowed
TEST_F(RotationEstimatorTest_29, LargeIterationCount_29) {
  options_.max_num_l1_iterations = 100;
  options_.max_num_irls_iterations = 200;
  CreateSimpleScene(4);
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  EXPECT_TRUE(result);
}

// Test: Gravity option enabled
TEST_F(RotationEstimatorTest_29, UseGravityEnabled_29) {
  options_.use_gravity = true;
  options_.axis = Eigen::Vector3d(0, 1, 0);
  CreateSimpleScene(3);
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  // Just verifying it doesn't crash with gravity enabled
  (void)result;
}

}  // namespace
}  // namespace glomap
