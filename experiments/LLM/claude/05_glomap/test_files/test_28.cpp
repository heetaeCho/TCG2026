#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/global_rotation_averaging.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/types.h"

#include <unordered_map>
#include <Eigen/Core>

namespace glomap {
namespace {

// Helper to create a simple image pair key
image_pair_t ImagePairToPairId(image_t image_id1, image_t image_id2) {
  if (image_id1 > image_id2) std::swap(image_id1, image_id2);
  return static_cast<image_pair_t>(image_id1) * 2147483647 + image_id2;
}

class RotationEstimatorTest_28 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_.max_num_l1_iterations = 5;
    options_.max_num_irls_iterations = 100;
    options_.use_gravity = false;
    options_.use_weight = false;
    options_.skip_initialization = false;
  }

  // Helper to set up a minimal two-image scenario with trivial frames
  void SetupTwoImageScene() {
    // Create two images
    Image image1;
    image1.camera_id = 0;
    image1.frame_id = 0;
    image1.is_registered = true;

    Image image2;
    image2.camera_id = 1;
    image2.frame_id = 1;
    image2.is_registered = true;

    images_[0] = image1;
    images_[1] = image2;

    // Create two frames
    Frame frame0;
    frame0.is_registered = true;
    frame0.AddImageId(DataId(0));
    frame0.SetRigFromWorld(Rigid3d());

    Frame frame1;
    frame1.is_registered = true;
    frame1.AddImageId(DataId(1));
    frame1.SetRigFromWorld(Rigid3d());

    frames_[0] = frame0;
    frames_[1] = frame1;

    // Link images to frames
    images_[0].frame_id = 0;
    images_[0].frame_ptr = &frames_[0];
    images_[1].frame_id = 1;
    images_[1].frame_ptr = &frames_[1];

    // Create an image pair
    image_pair_t pair_id = ImagePairToPairId(0, 1);
    ImagePair ip;
    ip.image_id1 = 0;
    ip.image_id2 = 1;
    ip.is_valid = true;
    ip.weight = 1.0;
    ip.cam2_from_cam1 = Rigid3d();

    view_graph_.image_pairs[pair_id] = ip;

    // Create a default rig
    Rig rig;
    rigs_[0] = rig;
  }

  // Helper to set up a three-image chain scenario
  void SetupThreeImageChain() {
    for (int i = 0; i < 3; i++) {
      Image img;
      img.camera_id = i;
      img.frame_id = i;
      img.is_registered = true;
      images_[i] = img;

      Frame frame;
      frame.is_registered = true;
      frame.AddImageId(DataId(i));
      frame.SetRigFromWorld(Rigid3d());
      frames_[i] = frame;

      images_[i].frame_ptr = &frames_[i];
    }

    // Pairs: (0,1) and (1,2)
    for (int k = 0; k < 2; k++) {
      image_t id1 = k;
      image_t id2 = k + 1;
      image_pair_t pair_id = ImagePairToPairId(id1, id2);
      ImagePair ip;
      ip.image_id1 = id1;
      ip.image_id2 = id2;
      ip.is_valid = true;
      ip.weight = 1.0;
      ip.cam2_from_cam1 = Rigid3d();
      view_graph_.image_pairs[pair_id] = ip;
    }

    Rig rig;
    rigs_[0] = rig;
  }

  RotationEstimatorOptions options_;
  ViewGraph view_graph_;
  std::unordered_map<rig_t, Rig> rigs_;
  std::unordered_map<frame_t, Frame> frames_;
  std::unordered_map<image_t, Image> images_;
};

// Test that EstimateRotations returns true with a valid two-image scene
TEST_F(RotationEstimatorTest_28, EstimateRotationsTwoImages_28) {
  SetupTwoImageScene();
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  EXPECT_TRUE(result);
}

// Test with empty inputs - no images, no frames
TEST_F(RotationEstimatorTest_28, EmptyScene_28) {
  RotationEstimator estimator(options_);
  // With empty scene, EstimateRotations should handle gracefully
  // It may return false or true depending on implementation
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  // We just check it doesn't crash
  SUCCEED();
}

// Test with no valid image pairs
TEST_F(RotationEstimatorTest_28, NoValidImagePairs_28) {
  SetupTwoImageScene();
  // Mark all pairs as invalid
  for (auto& [id, pair] : view_graph_.image_pairs) {
    pair.is_valid = false;
  }
  RotationEstimator estimator(options_);
  // Should handle gracefully without crashing
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  SUCCEED();
}

// Test with three images in a chain
TEST_F(RotationEstimatorTest_28, ThreeImageChain_28) {
  SetupThreeImageChain();
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  EXPECT_TRUE(result);
}

// Test that unregistered images are handled
TEST_F(RotationEstimatorTest_28, UnregisteredImages_28) {
  SetupTwoImageScene();
  images_[0].is_registered = false;
  images_[1].is_registered = false;
  frames_[0].is_registered = false;
  frames_[1].is_registered = false;

  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  // Should handle gracefully
  SUCCEED();
}

// Test with skip_initialization option
TEST_F(RotationEstimatorTest_28, SkipInitialization_28) {
  SetupTwoImageScene();
  options_.skip_initialization = true;
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  EXPECT_TRUE(result);
}

// Test with use_weight option enabled
TEST_F(RotationEstimatorTest_28, UseWeightEnabled_28) {
  SetupTwoImageScene();
  options_.use_weight = true;
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  EXPECT_TRUE(result);
}

// Test with negative weight on image pair (should default to 1)
TEST_F(RotationEstimatorTest_28, NegativeWeight_28) {
  SetupTwoImageScene();
  options_.use_weight = true;
  for (auto& [id, pair] : view_graph_.image_pairs) {
    pair.weight = -1.0;
  }
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  EXPECT_TRUE(result);
}

// Test with identical rotations (zero relative rotation)
TEST_F(RotationEstimatorTest_28, IdenticalRotations_28) {
  SetupTwoImageScene();
  // cam2_from_cam1 is identity, so rotations should remain identity-ish
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  EXPECT_TRUE(result);
  
  // After estimation, frames should have some rotation assigned
  EXPECT_TRUE(frames_[0].MaybeRigFromWorld().has_value());
  EXPECT_TRUE(frames_[1].MaybeRigFromWorld().has_value());
}

// Test convergence parameters boundary
TEST_F(RotationEstimatorTest_28, ZeroIterations_28) {
  SetupTwoImageScene();
  options_.max_num_l1_iterations = 0;
  options_.max_num_irls_iterations = 0;
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  // Should still complete without crash
  SUCCEED();
}

// Test with a single image (no pairs possible)
TEST_F(RotationEstimatorTest_28, SingleImage_28) {
  Image image1;
  image1.camera_id = 0;
  image1.frame_id = 0;
  image1.is_registered = true;
  images_[0] = image1;

  Frame frame0;
  frame0.is_registered = true;
  frame0.AddImageId(DataId(0));
  frame0.SetRigFromWorld(Rigid3d());
  frames_[0] = frame0;

  images_[0].frame_ptr = &frames_[0];

  Rig rig;
  rigs_[0] = rig;

  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  SUCCEED();
}

// Test with large convergence thresholds (should converge immediately)
TEST_F(RotationEstimatorTest_28, LargeConvergenceThreshold_28) {
  SetupTwoImageScene();
  options_.l1_step_convergence_threshold = 1e6;
  options_.irls_step_convergence_threshold = 1e6;
  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  EXPECT_TRUE(result);
}

// Test construction with default options
TEST_F(RotationEstimatorTest_28, ConstructorDefaultOptions_28) {
  RotationEstimatorOptions default_opts;
  RotationEstimator estimator(default_opts);
  // Just verify construction doesn't crash
  SUCCEED();
}

// Test with multiple disconnected pairs
TEST_F(RotationEstimatorTest_28, DisconnectedPairs_28) {
  // Create 4 images in 2 disconnected pairs
  for (int i = 0; i < 4; i++) {
    Image img;
    img.camera_id = i;
    img.frame_id = i;
    img.is_registered = true;
    images_[i] = img;

    Frame frame;
    frame.is_registered = true;
    frame.AddImageId(DataId(i));
    frame.SetRigFromWorld(Rigid3d());
    frames_[i] = frame;

    images_[i].frame_ptr = &frames_[i];
  }

  // Pair (0,1)
  {
    image_pair_t pair_id = ImagePairToPairId(0, 1);
    ImagePair ip;
    ip.image_id1 = 0;
    ip.image_id2 = 1;
    ip.is_valid = true;
    ip.weight = 1.0;
    ip.cam2_from_cam1 = Rigid3d();
    view_graph_.image_pairs[pair_id] = ip;
  }

  // Pair (2,3)
  {
    image_pair_t pair_id = ImagePairToPairId(2, 3);
    ImagePair ip;
    ip.image_id1 = 2;
    ip.image_id2 = 3;
    ip.is_valid = true;
    ip.weight = 1.0;
    ip.cam2_from_cam1 = Rigid3d();
    view_graph_.image_pairs[pair_id] = ip;
  }

  Rig rig;
  rigs_[0] = rig;

  RotationEstimator estimator(options_);
  bool result = estimator.EstimateRotations(view_graph_, rigs_, frames_, images_);
  SUCCEED();
}

}  // namespace
}  // namespace glomap
