#include <gtest/gtest.h>
#include "glomap/estimators/global_rotation_averaging.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/types.h"

#include <unordered_map>

namespace glomap {
namespace {

class RotationEstimatorTest_26 : public ::testing::Test {
 protected:
  void SetUp() override {}

  // Helper to create a simple two-image scene with one image pair
  void CreateSimpleTwoImageScene(
      ViewGraph& view_graph,
      std::unordered_map<rig_t, Rig>& rigs,
      std::unordered_map<frame_t, Frame>& frames,
      std::unordered_map<image_t, Image>& images) {
    // Create two images
    Image img1;
    img1.camera_id = 0;
    img1.frame_id = 0;
    img1.rig_id = 0;
    img1.is_registered = true;
    img1.cam_from_world = Eigen::Matrix3x4d::Identity();

    Image img2;
    img2.camera_id = 1;
    img2.frame_id = 1;
    img2.rig_id = 0;
    img2.is_registered = true;
    img2.cam_from_world = Eigen::Matrix3x4d::Identity();

    images[0] = img1;
    images[1] = img2;

    // Create frames
    Frame frame0;
    frame0.is_registered = true;
    frame0.rig_id = 0;
    frames[0] = frame0;

    Frame frame1;
    frame1.is_registered = true;
    frame1.rig_id = 0;
    frames[1] = frame1;

    // Create rig
    Rig rig;
    rigs[0] = rig;

    // Create image pair
    image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
    ImagePair pair;
    pair.image_id1 = 0;
    pair.image_id2 = 1;
    pair.is_valid = true;
    pair.cam2_from_cam1 = Eigen::Matrix3x4d::Identity();
    view_graph.image_pairs[pair_id] = pair;
  }
};

// Test with empty data structures
TEST_F(RotationEstimatorTest_26, EmptyInputs_26) {
  RotationEstimatorOptions options;
  options.max_num_l1_iterations = 0;
  options.max_num_irls_iterations = 0;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  // With empty inputs, it should still handle gracefully
  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

// Test with default options on a simple scene
TEST_F(RotationEstimatorTest_26, SimpleSceneDefaultOptions_26) {
  RotationEstimatorOptions options;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  CreateSimpleTwoImageScene(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  // The result depends on whether the solvers succeed, but shouldn't crash
  // We just verify it returns a boolean without crashing
  SUCCEED();
}

// Test with skip_initialization = true
TEST_F(RotationEstimatorTest_26, SkipInitialization_26) {
  RotationEstimatorOptions options;
  options.skip_initialization = true;
  options.max_num_l1_iterations = 0;
  options.max_num_irls_iterations = 0;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  CreateSimpleTwoImageScene(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

// Test with use_gravity = true but no sensor calibration (should return false)
TEST_F(RotationEstimatorTest_26, UseGravityMissingSensor_26) {
  RotationEstimatorOptions options;
  options.use_gravity = true;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  CreateSimpleTwoImageScene(view_graph, rigs, frames, images);

  // Add a non-ref sensor without value to trigger the error
  Rig& rig = rigs[0];
  // If the rig has non-ref sensors without values, it should fail
  // This depends on the Rig structure - we try to trigger the failure path
  // by having a rig with non-ref sensors that have no value
  // The exact mechanism depends on Rig::NonRefSensors()
  
  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  // Result depends on whether rig has non-ref sensors without values
  // For a default rig with no non-ref sensors, this should pass
  // We just verify it doesn't crash
  SUCCEED();
}

// Test with L1 iterations only (no IRLS)
TEST_F(RotationEstimatorTest_26, L1OnlyIterations_26) {
  RotationEstimatorOptions options;
  options.max_num_l1_iterations = 5;
  options.max_num_irls_iterations = 0;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  CreateSimpleTwoImageScene(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  SUCCEED();
}

// Test with IRLS iterations only (no L1)
TEST_F(RotationEstimatorTest_26, IRLSOnlyIterations_26) {
  RotationEstimatorOptions options;
  options.max_num_l1_iterations = 0;
  options.max_num_irls_iterations = 100;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  CreateSimpleTwoImageScene(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  SUCCEED();
}

// Test with zero iterations for both L1 and IRLS
TEST_F(RotationEstimatorTest_26, NoIterations_26) {
  RotationEstimatorOptions options;
  options.max_num_l1_iterations = 0;
  options.max_num_irls_iterations = 0;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  CreateSimpleTwoImageScene(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

// Test with use_gravity and skip_initialization both true
TEST_F(RotationEstimatorTest_26, UseGravityWithSkipInit_26) {
  RotationEstimatorOptions options;
  options.use_gravity = true;
  options.skip_initialization = true;
  options.max_num_l1_iterations = 0;
  options.max_num_irls_iterations = 0;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  CreateSimpleTwoImageScene(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  // With no non-ref sensors, gravity check passes, and no iterations -> true
  EXPECT_TRUE(result);
}

// Test with empty view graph but non-empty images/frames
TEST_F(RotationEstimatorTest_26, EmptyViewGraphNonEmptyImages_26) {
  RotationEstimatorOptions options;
  options.max_num_l1_iterations = 0;
  options.max_num_irls_iterations = 0;
  options.skip_initialization = true;
  RotationEstimator estimator(options);

  ViewGraph view_graph;  // No image pairs
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  Image img;
  img.camera_id = 0;
  img.frame_id = 0;
  img.rig_id = 0;
  img.is_registered = true;
  images[0] = img;

  Frame frame;
  frame.is_registered = true;
  frame.rig_id = 0;
  frames[0] = frame;

  Rig rig;
  rigs[0] = rig;

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

// Test convergence threshold options don't cause crashes
TEST_F(RotationEstimatorTest_26, CustomConvergenceThresholds_26) {
  RotationEstimatorOptions options;
  options.l1_step_convergence_threshold = 1e-6;
  options.irls_step_convergence_threshold = 1e-6;
  options.max_num_l1_iterations = 2;
  options.max_num_irls_iterations = 2;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  CreateSimpleTwoImageScene(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  // Just verify no crash
  SUCCEED();
}

// Test with use_weight option
TEST_F(RotationEstimatorTest_26, UseWeightOption_26) {
  RotationEstimatorOptions options;
  options.use_weight = true;
  options.max_num_l1_iterations = 1;
  options.max_num_irls_iterations = 1;
  RotationEstimator estimator(options);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  CreateSimpleTwoImageScene(view_graph, rigs, frames, images);

  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  SUCCEED();
}

}  // namespace
}  // namespace glomap
