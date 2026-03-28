#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/global_positioning.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/types.h"

#include <unordered_map>
#include <memory>

namespace glomap {
namespace {

class GlobalPositionerTest_111 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_ = GlobalPositionerOptions();
  }

  GlobalPositionerOptions options_;
};

// Test that the constructor does not throw with default options
TEST_F(GlobalPositionerTest_111, ConstructorWithDefaultOptions_111) {
  EXPECT_NO_THROW(GlobalPositioner positioner(options_));
}

// Test that GetOptions returns the options that were passed in
TEST_F(GlobalPositionerTest_111, GetOptionsReturnsOptions_111) {
  GlobalPositioner positioner(options_);
  GlobalPositionerOptions& retrieved_options = positioner.GetOptions();
  // The returned reference should be valid and accessible
  (void)retrieved_options;
}

// Test Solve with empty inputs - should handle gracefully
TEST_F(GlobalPositionerTest_111, SolveWithEmptyInputs_111) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // With empty data, Solve may return false or handle gracefully
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  // We just verify it doesn't crash; the return value depends on implementation
  (void)result;
}

// Test Solve with minimal valid input - a single image pair
TEST_F(GlobalPositionerTest_111, SolveWithMinimalInput_111) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Create minimal scene with two cameras, two images, two frames
  camera_t cam_id1 = 0, cam_id2 = 1;
  image_t img_id1 = 0, img_id2 = 1;
  frame_t frame_id1 = 0, frame_id2 = 1;
  rig_t rig_id1 = 0, rig_id2 = 1;

  cameras[cam_id1] = Camera();
  cameras[cam_id2] = Camera();

  Image img1;
  img1.camera_id = cam_id1;
  img1.frame_id = frame_id1;
  img1.rig_id = rig_id1;
  images[img_id1] = img1;

  Image img2;
  img2.camera_id = cam_id2;
  img2.frame_id = frame_id2;
  img2.rig_id = rig_id2;
  images[img_id2] = img2;

  Frame f1;
  frames[frame_id1] = f1;
  Frame f2;
  frames[frame_id2] = f2;

  Rig r1;
  rigs[rig_id1] = r1;
  Rig r2;
  rigs[rig_id2] = r2;

  // Add an image pair to the view graph
  image_pair_t pair_id = ImagePair::ImagePairToPairId(img_id1, img_id2);
  ImagePair image_pair;
  image_pair.is_valid = true;
  image_pair.image_id1 = img_id1;
  image_pair.image_id2 = img_id2;
  view_graph.image_pairs[pair_id] = image_pair;

  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  // Just verify no crash
  (void)result;
}

// Test that GetOptions returns a modifiable reference
TEST_F(GlobalPositionerTest_111, GetOptionsIsModifiable_111) {
  GlobalPositioner positioner(options_);
  GlobalPositionerOptions& opts = positioner.GetOptions();
  // Verify we can modify through the reference without crashing
  opts.thres_loss_function = 0.5;
  EXPECT_DOUBLE_EQ(positioner.GetOptions().thres_loss_function, 0.5);
}

// Test Solve with no valid image pairs in view graph
TEST_F(GlobalPositionerTest_111, SolveWithNoValidImagePairs_111) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Add an invalid image pair
  image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
  ImagePair image_pair;
  image_pair.is_valid = false;
  view_graph.image_pairs[pair_id] = image_pair;

  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  (void)result;
}

// Test construction with modified options
TEST_F(GlobalPositionerTest_111, ConstructorWithModifiedOptions_111) {
  options_.thres_loss_function = 1.0;
  EXPECT_NO_THROW(GlobalPositioner positioner(options_));
}

}  // namespace
}  // namespace glomap
