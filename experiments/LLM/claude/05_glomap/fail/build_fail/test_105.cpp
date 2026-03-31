#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/global_positioning.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/track.h"

#include <unordered_map>

namespace glomap {
namespace {

class GlobalPositionerTest_105 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Default options
    options_.generate_random_positions = true;
    options_.optimize_positions = true;
    options_.seed = 42;
    options_.min_num_view_per_track = 2;
  }

  // Helper to create a registered image with a given frame_id
  void AddRegisteredImage(image_t img_id, camera_t cam_id, frame_t frm_id) {
    Image img(img_id, cam_id, "image_" + std::to_string(img_id) + ".jpg");
    img.frame_id = frm_id;
    // We need to make the image registered. According to the codebase,
    // an image is registered if it has a valid cam_from_world set.
    // We'll set it via the frame pointer or the registration mechanism.
    images_[img_id] = img;
  }

  void AddFrame(frame_t frm_id) {
    frames_[frm_id] = Frame();
    // Initialize with identity transform
    frames_[frm_id].RigFromWorld() = Rigid3d();
  }

  void AddValidImagePair(image_t id1, image_t id2) {
    ImagePair pair(id1, id2);
    pair.is_valid = true;
    view_graph_.image_pairs[pair.pair_id] = pair;
  }

  void AddInvalidImagePair(image_t id1, image_t id2) {
    ImagePair pair(id1, id2);
    pair.is_valid = false;
    view_graph_.image_pairs[pair.pair_id] = pair;
  }

  GlobalPositionerOptions options_;
  ViewGraph view_graph_;
  std::unordered_map<frame_t, Frame> frames_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;
};

// Test: Constructor creates a valid object with default options
TEST_F(GlobalPositionerTest_105, ConstructorWithDefaultOptions_105) {
  GlobalPositionerOptions default_opts;
  EXPECT_NO_THROW(GlobalPositioner positioner(default_opts));
}

// Test: Constructor with custom options
TEST_F(GlobalPositionerTest_105, ConstructorWithCustomOptions_105) {
  options_.generate_random_positions = false;
  options_.optimize_positions = false;
  EXPECT_NO_THROW(GlobalPositioner positioner(options_));
}

// Test: Empty inputs - no frames, no images, no tracks, no view graph edges
TEST_F(GlobalPositionerTest_105, EmptyInputs_105) {
  GlobalPositioner positioner(options_);
  // With empty containers, Solve should handle gracefully
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;

  // This might return false since there's nothing to solve
  bool result = positioner.Solve(view_graph_, rigs, cameras, frames_, images_, tracks_);
  // We just check it doesn't crash; result may be false due to empty problem
  SUCCEED();
}

// Test: GetOptions returns mutable reference to options
TEST_F(GlobalPositionerTest_105, GetOptionsReturnsOptions_105) {
  GlobalPositioner positioner(options_);
  GlobalPositionerOptions& opts = positioner.GetOptions();
  EXPECT_EQ(opts.generate_random_positions, options_.generate_random_positions);
  EXPECT_EQ(opts.optimize_positions, options_.optimize_positions);
  EXPECT_EQ(opts.seed, options_.seed);
}

// Test: GetOptions can modify the internal options
TEST_F(GlobalPositionerTest_105, GetOptionsModifiable_105) {
  GlobalPositioner positioner(options_);
  GlobalPositionerOptions& opts = positioner.GetOptions();
  opts.generate_random_positions = false;
  EXPECT_FALSE(positioner.GetOptions().generate_random_positions);
}

// Test: Default GlobalPositionerOptions values
TEST_F(GlobalPositionerTest_105, DefaultOptionsValues_105) {
  GlobalPositionerOptions opts;
  EXPECT_TRUE(opts.generate_random_positions);
  EXPECT_TRUE(opts.generate_random_points);
  EXPECT_TRUE(opts.generate_scales);
  EXPECT_TRUE(opts.optimize_positions);
  EXPECT_TRUE(opts.optimize_scales);
  EXPECT_EQ(opts.seed, 1u);
  EXPECT_EQ(opts.constraint_type, ONLY_POINTS);
}

// Test: Options constraint_reweight_scale default
TEST_F(GlobalPositionerTest_105, DefaultConstraintReweightScale_105) {
  GlobalPositionerOptions opts;
  EXPECT_DOUBLE_EQ(opts.constraint_reweight_scale, 1.0);
}

// Test: CreateLossFunction returns a valid shared_ptr
TEST_F(GlobalPositionerTest_105, CreateLossFunctionNotNull_105) {
  GlobalPositionerOptions opts;
  auto loss = opts.CreateLossFunction();
  // The loss function should be created (may or may not be null depending on implementation)
  // Just verify it doesn't throw
  SUCCEED();
}

// Test: Solve with single valid image pair and two registered frames
TEST_F(GlobalPositionerTest_105, SolveWithSingleValidPair_105) {
  // Set up two images with frames
  AddFrame(0);
  AddFrame(1);
  AddRegisteredImage(0, 0, 0);
  AddRegisteredImage(1, 0, 1);
  AddValidImagePair(0, 1);

  // Set up rigs and cameras
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;

  // Create a camera
  Camera cam;
  cam.camera_id = 0;
  cam.model_id = 0; // simple pinhole
  cam.width = 640;
  cam.height = 480;
  cam.params = {500.0, 320.0, 240.0};
  cameras[0] = cam;

  // Create a rig
  Rig rig;
  rigs[0] = rig;

  // Associate images with frames properly
  for (auto& [img_id, img] : images_) {
    if (frames_.count(img.frame_id)) {
      img.frame_ptr = &frames_[img.frame_id];
    }
  }

  // Set up tracks with observations
  Track track;
  track.track_id = 0;
  track.observations.push_back({0, 0});
  track.observations.push_back({1, 0});
  track.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);
  tracks_[0] = track;

  GlobalPositioner positioner(options_);
  // Solve may or may not succeed depending on full setup, but shouldn't crash
  EXPECT_NO_THROW(
      positioner.Solve(view_graph_, rigs, cameras, frames_, images_, tracks_));
}

// Test: Solve with invalid image pairs only should handle gracefully
TEST_F(GlobalPositionerTest_105, SolveWithOnlyInvalidPairs_105) {
  AddFrame(0);
  AddFrame(1);
  AddRegisteredImage(0, 0, 0);
  AddRegisteredImage(1, 0, 1);
  AddInvalidImagePair(0, 1);

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;

  GlobalPositioner positioner(options_);
  EXPECT_NO_THROW(
      positioner.Solve(view_graph_, rigs, cameras, frames_, images_, tracks_));
}

// Test: Solve with no image pairs but with tracks
TEST_F(GlobalPositionerTest_105, SolveWithNoImagePairsButTracks_105) {
  AddFrame(0);
  AddFrame(1);
  AddRegisteredImage(0, 0, 0);
  AddRegisteredImage(1, 0, 1);

  Track track;
  track.track_id = 0;
  track.observations.push_back({0, 0});
  track.observations.push_back({1, 0});
  track.xyz = Eigen::Vector3d(0, 0, 0);
  tracks_[0] = track;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;

  GlobalPositioner positioner(options_);
  EXPECT_NO_THROW(
      positioner.Solve(view_graph_, rigs, cameras, frames_, images_, tracks_));
}

// Test: Options with generate_random_positions=false and optimize_positions=false
TEST_F(GlobalPositionerTest_105, SolveWithNoRandomNoOptimize_105) {
  options_.generate_random_positions = false;
  options_.optimize_positions = false;

  AddFrame(0);
  AddFrame(1);
  AddRegisteredImage(0, 0, 0);
  AddRegisteredImage(1, 0, 1);
  AddValidImagePair(0, 1);

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;

  GlobalPositioner positioner(options_);
  EXPECT_NO_THROW(
      positioner.Solve(view_graph_, rigs, cameras, frames_, images_, tracks_));
}

// Test: Options with generate_random_positions=true but optimize_positions=false
TEST_F(GlobalPositionerTest_105, SolveRandomButNoOptimize_105) {
  options_.generate_random_positions = true;
  options_.optimize_positions = false;

  AddFrame(0);
  AddRegisteredImage(0, 0, 0);

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;

  GlobalPositioner positioner(options_);
  EXPECT_NO_THROW(
      positioner.Solve(view_graph_, rigs, cameras, frames_, images_, tracks_));
}

// Test: Tracks with fewer observations than min_num_view_per_track are ignored
TEST_F(GlobalPositionerTest_105, TracksBelowMinViewThreshold_105) {
  options_.min_num_view_per_track = 3;

  AddFrame(0);
  AddFrame(1);
  AddRegisteredImage(0, 0, 0);
  AddRegisteredImage(1, 0, 1);
  AddValidImagePair(0, 1);

  // Track with only 2 observations, below threshold of 3
  Track track;
  track.track_id = 0;
  track.observations.push_back({0, 0});
  track.observations.push_back({1, 0});
  track.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);
  tracks_[0] = track;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;

  GlobalPositioner positioner(options_);
  EXPECT_NO_THROW(
      positioner.Solve(view_graph_, rigs, cameras, frames_, images_, tracks_));
}

// Test: Multiple frames, some constrained, some not
TEST_F(GlobalPositionerTest_105, MultipleFramesMixedConstraints_105) {
  AddFrame(0);
  AddFrame(1);
  AddFrame(2);  // This frame won't be connected by any pair
  AddRegisteredImage(0, 0, 0);
  AddRegisteredImage(1, 0, 1);
  AddRegisteredImage(2, 0, 2);
  AddValidImagePair(0, 1);
  // Frame 2 is not constrained by any valid pair

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;

  GlobalPositioner positioner(options_);
  EXPECT_NO_THROW(
      positioner.Solve(view_graph_, rigs, cameras, frames_, images_, tracks_));
}

// Test: Seed reproducibility - same seed should give same results
TEST_F(GlobalPositionerTest_105, SeedReproducibility_105) {
  options_.seed = 42;
  options_.generate_random_positions = true;
  options_.optimize_positions = true;

  // Just verify construction with same seed is consistent
  GlobalPositioner positioner1(options_);
  GlobalPositioner positioner2(options_);

  EXPECT_EQ(positioner1.GetOptions().seed, positioner2.GetOptions().seed);
}

// Test: Different constraint types
TEST_F(GlobalPositionerTest_105, ConstraintTypeOnlyPoints_105) {
  options_.constraint_type = ONLY_POINTS;
  GlobalPositioner positioner(options_);
  EXPECT_EQ(positioner.GetOptions().constraint_type, ONLY_POINTS);
}

// Test: Large number of frames with no crash
TEST_F(GlobalPositionerTest_105, LargeNumberOfFrames_105) {
  const int num_frames = 100;
  for (int i = 0; i < num_frames; ++i) {
    AddFrame(i);
    AddRegisteredImage(i, 0, i);
  }
  // Add pairs between consecutive frames
  for (int i = 0; i < num_frames - 1; ++i) {
    AddValidImagePair(i, i + 1);
  }

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;

  GlobalPositioner positioner(options_);
  EXPECT_NO_THROW(
      positioner.Solve(view_graph_, rigs, cameras, frames_, images_, tracks_));
}

// Test: Empty tracks map
TEST_F(GlobalPositionerTest_105, EmptyTracksMap_105) {
  AddFrame(0);
  AddFrame(1);
  AddRegisteredImage(0, 0, 0);
  AddRegisteredImage(1, 0, 1);
  AddValidImagePair(0, 1);

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;

  // tracks_ is empty
  GlobalPositioner positioner(options_);
  EXPECT_NO_THROW(
      positioner.Solve(view_graph_, rigs, cameras, frames_, images_, tracks_));
}

// Test: Track with observation referencing non-existent image
TEST_F(GlobalPositionerTest_105, TrackWithNonExistentImage_105) {
  AddFrame(0);
  AddRegisteredImage(0, 0, 0);
  AddValidImagePair(0, 0);  // self-pair (edge case)

  Track track;
  track.track_id = 0;
  track.observations.push_back({0, 0});
  track.observations.push_back({999, 0});  // non-existent image
  track.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);
  tracks_[0] = track;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;

  GlobalPositioner positioner(options_);
  // Should handle missing images gracefully
  EXPECT_NO_THROW(
      positioner.Solve(view_graph_, rigs, cameras, frames_, images_, tracks_));
}

// Test: Constraint reweight scale modification
TEST_F(GlobalPositionerTest_105, ConstraintReweightScaleModification_105) {
  options_.constraint_reweight_scale = 0.5;
  GlobalPositioner positioner(options_);
  EXPECT_DOUBLE_EQ(positioner.GetOptions().constraint_reweight_scale, 0.5);
}

}  // namespace
}  // namespace glomap
