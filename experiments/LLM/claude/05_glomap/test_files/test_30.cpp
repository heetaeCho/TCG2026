#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/global_rotation_averaging.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/types.h"

#include <unordered_map>
#include <Eigen/Core>

namespace glomap {
namespace {

class RotationEstimatorTest_30 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Default options
    options_.max_num_l1_iterations = 5;
    options_.l1_step_convergence_threshold = 0.001;
    options_.max_num_irls_iterations = 100;
    options_.irls_step_convergence_threshold = 0.001;
    options_.irls_loss_parameter_sigma = 5.0;
    options_.weight_type = RotationEstimatorOptions::GEMAN_MCCLURE;
    options_.skip_initialization = false;
    options_.use_weight = false;
    options_.use_gravity = false;
  }

  RotationEstimatorOptions options_;
};

// Test: Empty inputs should handle gracefully (no crash or return false)
TEST_F(RotationEstimatorTest_30, EmptyInputs_30) {
  RotationEstimator estimator(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  // With empty view graph, frames, and images, the estimator should
  // either return false or handle gracefully without crashing.
  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  // We just check it doesn't crash; result may be true or false depending on implementation.
  (void)result;
}

// Test: Construction with default options
TEST_F(RotationEstimatorTest_30, ConstructionWithDefaultOptions_30) {
  RotationEstimatorOptions default_options;
  EXPECT_NO_THROW(RotationEstimator estimator(default_options));
}

// Test: Construction with custom options
TEST_F(RotationEstimatorTest_30, ConstructionWithCustomOptions_30) {
  options_.max_num_irls_iterations = 50;
  options_.irls_loss_parameter_sigma = 10.0;
  options_.weight_type = RotationEstimatorOptions::HALF_NORM;
  options_.use_gravity = true;

  EXPECT_NO_THROW(RotationEstimator estimator(options_));
}

// Helper to create a simple two-image scenario
void SetupTwoImageScenario(ViewGraph& view_graph,
                           std::unordered_map<rig_t, Rig>& rigs,
                           std::unordered_map<frame_t, Frame>& frames,
                           std::unordered_map<image_t, Image>& images) {
  // Create two images
  Image img0;
  img0.camera_id = 0;
  img0.frame_id = 0;
  img0.is_registered = true;
  images[0] = img0;

  Image img1;
  img1.camera_id = 1;
  img1.frame_id = 1;
  img1.is_registered = true;
  images[1] = img1;

  // Create two frames
  Frame frame0;
  frame0.is_registered = true;
  frames[0] = frame0;

  Frame frame1;
  frame1.is_registered = true;
  frames[1] = frame1;

  // Create two rigs (one per frame)
  Rig rig0;
  rigs[0] = rig0;

  Rig rig1;
  rigs[1] = rig1;

  // Create an image pair
  image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
  ImagePair pair;
  pair.image_id1 = 0;
  pair.image_id2 = 1;
  pair.is_valid = true;
  // Set relative rotation to identity (no rotation between images)
  pair.cam2_from_cam1 = Eigen::Matrix3x4d::Identity().block<3, 4>(0, 0);

  view_graph.image_pairs[pair_id] = pair;
}

// Test: Simple two-image scenario with identity rotation
TEST_F(RotationEstimatorTest_30, TwoImageIdentityRotation_30) {
  RotationEstimator estimator(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  SetupTwoImageScenario(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  // We check it doesn't crash; the result depends on the actual implementation.
  (void)result;
}

// Test: With skip_initialization set to true
TEST_F(RotationEstimatorTest_30, SkipInitialization_30) {
  options_.skip_initialization = true;
  RotationEstimator estimator(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  SetupTwoImageScenario(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  (void)result;
}

// Test: With HALF_NORM weight type
TEST_F(RotationEstimatorTest_30, HalfNormWeightType_30) {
  options_.weight_type = RotationEstimatorOptions::HALF_NORM;
  RotationEstimator estimator(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  SetupTwoImageScenario(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  (void)result;
}

// Test: With use_weight enabled
TEST_F(RotationEstimatorTest_30, UseWeightEnabled_30) {
  options_.use_weight = true;
  RotationEstimator estimator(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  SetupTwoImageScenario(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  (void)result;
}

// Test: With use_gravity enabled
TEST_F(RotationEstimatorTest_30, UseGravityEnabled_30) {
  options_.use_gravity = true;
  RotationEstimator estimator(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  SetupTwoImageScenario(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  (void)result;
}

// Test: Very small sigma value (boundary condition)
TEST_F(RotationEstimatorTest_30, VerySmallSigma_30) {
  options_.irls_loss_parameter_sigma = 1e-10;
  RotationEstimator estimator(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  SetupTwoImageScenario(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  (void)result;
}

// Test: Very large sigma value (boundary condition)
TEST_F(RotationEstimatorTest_30, VeryLargeSigma_30) {
  options_.irls_loss_parameter_sigma = 1e6;
  RotationEstimator estimator(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  SetupTwoImageScenario(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  (void)result;
}

// Test: Zero max iterations for IRLS
TEST_F(RotationEstimatorTest_30, ZeroIRLSIterations_30) {
  options_.max_num_irls_iterations = 0;
  RotationEstimator estimator(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  SetupTwoImageScenario(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  (void)result;
}

// Test: Zero max iterations for L1
TEST_F(RotationEstimatorTest_30, ZeroL1Iterations_30) {
  options_.max_num_l1_iterations = 0;
  RotationEstimator estimator(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  SetupTwoImageScenario(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  (void)result;
}

// Test: Single image (no pairs)
TEST_F(RotationEstimatorTest_30, SingleImageNoPairs_30) {
  RotationEstimator estimator(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  Image img0;
  img0.camera_id = 0;
  img0.frame_id = 0;
  img0.is_registered = true;
  images[0] = img0;

  Frame frame0;
  frame0.is_registered = true;
  frames[0] = frame0;

  Rig rig0;
  rigs[0] = rig0;

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  (void)result;
}

// Test: Large convergence threshold leads to early termination
TEST_F(RotationEstimatorTest_30, LargeConvergenceThreshold_30) {
  options_.irls_step_convergence_threshold = 1e6;
  options_.l1_step_convergence_threshold = 1e6;
  RotationEstimator estimator(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  SetupTwoImageScenario(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  (void)result;
}

// Test: Multiple calls to EstimateRotations on same estimator
TEST_F(RotationEstimatorTest_30, MultipleCallsToEstimate_30) {
  RotationEstimator estimator(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  SetupTwoImageScenario(view_graph, rigs, frames, images);

  bool result1 = estimator.EstimateRotations(view_graph, rigs, frames, images);
  (void)result1;

  // Call again with same data
  bool result2 = estimator.EstimateRotations(view_graph, rigs, frames, images);
  (void)result2;
}

// Test: Options with max_num_irls_iterations = 1
TEST_F(RotationEstimatorTest_30, SingleIRLSIteration_30) {
  options_.max_num_irls_iterations = 1;
  RotationEstimator estimator(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  SetupTwoImageScenario(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  (void)result;
}

}  // namespace
}  // namespace glomap
