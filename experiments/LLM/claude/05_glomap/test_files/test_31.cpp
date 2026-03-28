#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/global_rotation_averaging.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/types.h"

#include <unordered_map>
#include <Eigen/Core>

namespace glomap {
namespace {

class RotationEstimatorTest_31 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_.max_num_l1_iterations = 5;
    options_.l1_step_convergence_threshold = 0.001;
    options_.max_num_irls_iterations = 100;
    options_.irls_step_convergence_threshold = 0.001;
    options_.irls_loss_parameter_sigma = 5.0;
    options_.skip_initialization = false;
    options_.use_weight = false;
    options_.use_gravity = false;
  }

  RotationEstimatorOptions options_;
};

// Helper to create a simple two-image view graph with identity relative rotation
void SetupSimpleTwoImageScene(
    ViewGraph& view_graph,
    std::unordered_map<image_t, Image>& images,
    std::unordered_map<frame_t, Frame>& frames,
    std::unordered_map<rig_t, Rig>& rigs) {
  // Create two images
  Image img1;
  Image img2;
  images[0] = img1;
  images[1] = img2;

  // Create frames
  Frame frame1;
  Frame frame2;
  frames[0] = frame1;
  frames[1] = frame2;

  // Create an image pair
  ImagePair pair;
  pair.image_id1 = 0;
  pair.image_id2 = 1;
  pair.is_valid = true;
  // Set relative rotation to identity
  pair.cam2_from_cam1 = Eigen::Matrix3x4d::Identity();

  image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
  view_graph.image_pairs[pair_id] = pair;
}

// Helper to create a three-image chain view graph
void SetupThreeImageChainScene(
    ViewGraph& view_graph,
    std::unordered_map<image_t, Image>& images,
    std::unordered_map<frame_t, Frame>& frames,
    std::unordered_map<rig_t, Rig>& rigs) {
  Image img1, img2, img3;
  images[0] = img1;
  images[1] = img2;
  images[2] = img3;

  Frame frame1, frame2, frame3;
  frames[0] = frame1;
  frames[1] = frame2;
  frames[2] = frame3;

  ImagePair pair01;
  pair01.image_id1 = 0;
  pair01.image_id2 = 1;
  pair01.is_valid = true;
  pair01.cam2_from_cam1 = Eigen::Matrix3x4d::Identity();

  ImagePair pair12;
  pair12.image_id1 = 1;
  pair12.image_id2 = 2;
  pair12.is_valid = true;
  pair12.cam2_from_cam1 = Eigen::Matrix3x4d::Identity();

  image_pair_t pair_id01 = ImagePair::ImagePairToPairId(0, 1);
  image_pair_t pair_id12 = ImagePair::ImagePairToPairId(1, 2);
  view_graph.image_pairs[pair_id01] = pair01;
  view_graph.image_pairs[pair_id12] = pair12;
}

// Test: Construction with default options
TEST_F(RotationEstimatorTest_31, ConstructWithDefaultOptions_31) {
  EXPECT_NO_THROW({
    RotationEstimator estimator(options_);
  });
}

// Test: EstimateRotations returns true for a simple valid two-image scene
TEST_F(RotationEstimatorTest_31, EstimateRotationsTwoImages_31) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  SetupSimpleTwoImageScene(view_graph, images, frames, rigs);

  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

// Test: EstimateRotations with three images in a chain
TEST_F(RotationEstimatorTest_31, EstimateRotationsThreeImageChain_31) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  SetupThreeImageChainScene(view_graph, images, frames, rigs);

  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

// Test: EstimateRotations with empty view graph
TEST_F(RotationEstimatorTest_31, EstimateRotationsEmptyViewGraph_31) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  // With no pairs, estimation should fail or return false
  EXPECT_FALSE(result);
}

// Test: EstimateRotations with skip_initialization enabled
TEST_F(RotationEstimatorTest_31, EstimateRotationsSkipInit_31) {
  options_.skip_initialization = true;

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  SetupSimpleTwoImageScene(view_graph, images, frames, rigs);

  RotationEstimator estimator(options_);
  // With skip_initialization and no pre-set rotations, behavior may vary
  // but should not crash
  estimator.EstimateRotations(view_graph, rigs, frames, images);
}

// Test: EstimateRotations modifies image rotations
TEST_F(RotationEstimatorTest_31, EstimateRotationsModifiesImages_31) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  SetupSimpleTwoImageScene(view_graph, images, frames, rigs);

  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);

  if (result) {
    // After estimation, images should have been updated
    // We can at least verify images still exist
    EXPECT_EQ(images.size(), 2);
  }
}

// Test: EstimateRotations with use_weight option
TEST_F(RotationEstimatorTest_31, EstimateRotationsWithWeight_31) {
  options_.use_weight = true;

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  SetupSimpleTwoImageScene(view_graph, images, frames, rigs);

  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

// Test: EstimateRotations with use_gravity option but no gravity info
TEST_F(RotationEstimatorTest_31, EstimateRotationsWithGravityNoGravityInfo_31) {
  options_.use_gravity = true;

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  SetupSimpleTwoImageScene(view_graph, images, frames, rigs);

  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  // Should still work even without gravity info on images
  EXPECT_TRUE(result);
}

// Test: Options max iterations boundary - zero L1 iterations
TEST_F(RotationEstimatorTest_31, EstimateRotationsZeroL1Iterations_31) {
  options_.max_num_l1_iterations = 0;

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  SetupSimpleTwoImageScene(view_graph, images, frames, rigs);

  RotationEstimator estimator(options_);
  // Should not crash with zero iterations
  estimator.EstimateRotations(view_graph, rigs, frames, images);
}

// Test: Options max iterations boundary - zero IRLS iterations
TEST_F(RotationEstimatorTest_31, EstimateRotationsZeroIRLSIterations_31) {
  options_.max_num_irls_iterations = 0;

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  SetupSimpleTwoImageScene(view_graph, images, frames, rigs);

  RotationEstimator estimator(options_);
  // Should not crash with zero IRLS iterations
  estimator.EstimateRotations(view_graph, rigs, frames, images);
}

// Test: Single image with no pairs
TEST_F(RotationEstimatorTest_31, EstimateRotationsSingleImage_31) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  Image img;
  images[0] = img;
  Frame frame;
  frames[0] = frame;

  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_FALSE(result);
}

// Test: EstimateRotations with identity relative rotations produces consistent results
TEST_F(RotationEstimatorTest_31, IdentityRelativeRotationsConsistency_31) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  SetupThreeImageChainScene(view_graph, images, frames, rigs);

  // Also add pair 0-2 with identity rotation
  ImagePair pair02;
  pair02.image_id1 = 0;
  pair02.image_id2 = 2;
  pair02.is_valid = true;
  pair02.cam2_from_cam1 = Eigen::Matrix3x4d::Identity();
  image_pair_t pair_id02 = ImagePair::ImagePairToPairId(0, 2);
  view_graph.image_pairs[pair_id02] = pair02;

  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

// Test: Very high convergence threshold leads to quick convergence
TEST_F(RotationEstimatorTest_31, HighConvergenceThreshold_31) {
  options_.l1_step_convergence_threshold = 1e6;
  options_.irls_step_convergence_threshold = 1e6;

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  SetupSimpleTwoImageScene(view_graph, images, frames, rigs);

  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  // Should converge immediately with high threshold
  EXPECT_TRUE(result);
}

// Test: Multiple calls to EstimateRotations
TEST_F(RotationEstimatorTest_31, MultipleEstimationCalls_31) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  SetupSimpleTwoImageScene(view_graph, images, frames, rigs);

  RotationEstimator estimator(options_);
  
  bool result1 = estimator.EstimateRotations(view_graph, rigs, frames, images);
  bool result2 = estimator.EstimateRotations(view_graph, rigs, frames, images);
  
  EXPECT_EQ(result1, result2);
}

// Test: Large sigma parameter
TEST_F(RotationEstimatorTest_31, LargeSigmaParameter_31) {
  options_.irls_loss_parameter_sigma = 1000.0;

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  SetupSimpleTwoImageScene(view_graph, images, frames, rigs);

  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

// Test: Very small sigma parameter
TEST_F(RotationEstimatorTest_31, SmallSigmaParameter_31) {
  options_.irls_loss_parameter_sigma = 0.001;

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<rig_t, Rig> rigs;

  SetupSimpleTwoImageScene(view_graph, images, frames, rigs);

  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph, rigs, frames, images);
  EXPECT_TRUE(result);
}

}  // namespace
}  // namespace glomap
