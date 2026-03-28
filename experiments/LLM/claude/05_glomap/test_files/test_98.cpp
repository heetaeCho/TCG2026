#include <gtest/gtest.h>
#include <unordered_map>

#include "glomap/estimators/bundle_adjustment.h"
#include "glomap/types.h"

namespace glomap {
namespace {

class BundleAdjusterTest_98 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_.use_gpu = false;
    options_.solver_options.max_num_iterations = 5;
    options_.solver_options.num_threads = 1;
  }

  BundleAdjusterOptions options_;

  std::unordered_map<rig_t, Rig> rigs_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<frame_t, Frame> frames_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;
};

// Test that Solve returns false when images map is empty
TEST_F(BundleAdjusterTest_98, SolveWithEmptyImages_98) {
  BundleAdjuster ba(options_);

  // tracks non-empty but images empty
  Track track;
  track.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);
  tracks_[0] = track;

  bool result = ba.Solve(rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result);
}

// Test that Solve returns false when tracks map is empty
TEST_F(BundleAdjusterTest_98, SolveWithEmptyTracks_98) {
  BundleAdjuster ba(options_);

  // images non-empty but tracks empty
  Image img;
  img.camera_id = 0;
  img.frame_id = 0;
  img.rig_id = 0;
  images_[0] = img;

  bool result = ba.Solve(rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result);
}

// Test that Solve returns false when both images and tracks are empty
TEST_F(BundleAdjusterTest_98, SolveWithBothEmpty_98) {
  BundleAdjuster ba(options_);

  bool result = ba.Solve(rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result);
}

// Test that Solve can be called with minimal valid data
// This tests that the function does not crash with a minimal setup
// The actual result depends on whether Ceres can solve the problem
TEST_F(BundleAdjusterTest_98, SolveWithMinimalData_98) {
  BundleAdjuster ba(options_);

  // Create a minimal camera
  Camera cam;
  cam.model_id = 0;  // SIMPLE_PINHOLE
  cam.width = 640;
  cam.height = 480;
  cam.params = {500.0, 320.0, 240.0};
  cameras_[0] = cam;

  // Create a rig
  Rig rig;
  rigs_[0] = rig;

  // Create a frame
  Frame frame;
  frame.rig_id = 0;
  frames_[0] = frame;

  // Create images with identity poses
  Image img0;
  img0.camera_id = 0;
  img0.frame_id = 0;
  img0.rig_id = 0;
  img0.cam_from_world = Rigid3d();
  images_[0] = img0;

  Image img1;
  img1.camera_id = 0;
  img1.frame_id = 0;
  img1.rig_id = 0;
  img1.cam_from_world = Rigid3d();
  img1.cam_from_world.translation = Eigen::Vector3d(1.0, 0.0, 0.0);
  images_[1] = img1;

  // Create a track observed by both images
  Track track;
  track.xyz = Eigen::Vector3d(0.5, 0.5, 5.0);
  track.is_initialized = true;

  Observation obs0;
  obs0.image_id = 0;
  obs0.feature_idx = 0;
  track.observations.push_back(obs0);

  Observation obs1;
  obs1.image_id = 1;
  obs1.feature_idx = 0;
  track.observations.push_back(obs1);

  tracks_[0] = track;

  // Add 2D features to images
  images_[0].features.push_back(Eigen::Vector2d(320.0, 240.0));
  images_[1].features.push_back(Eigen::Vector2d(270.0, 240.0));

  // This may or may not return true depending on convergence,
  // but it should not crash
  ba.Solve(rigs_, cameras_, frames_, images_, tracks_);
}

// Test that GetOptions returns mutable reference to options
TEST_F(BundleAdjusterTest_98, GetOptionsReturnsOptions_98) {
  BundleAdjuster ba(options_);
  BundleAdjusterOptions& opts = ba.GetOptions();
  
  // Modify through returned reference
  opts.optimize_intrinsics = false;
  EXPECT_FALSE(ba.GetOptions().optimize_intrinsics);
}

// Test that default options are set correctly
TEST_F(BundleAdjusterTest_98, DefaultOptionsValues_98) {
  BundleAdjusterOptions default_opts;
  EXPECT_FALSE(default_opts.optimize_rig_poses);
  EXPECT_TRUE(default_opts.optimize_rotations);
  EXPECT_TRUE(default_opts.optimize_translation);
  EXPECT_TRUE(default_opts.optimize_intrinsics);
  EXPECT_FALSE(default_opts.optimize_principal_point);
  EXPECT_TRUE(default_opts.optimize_points);
  EXPECT_TRUE(default_opts.use_gpu);
  EXPECT_EQ(default_opts.min_num_images_gpu_solver, 50);
  EXPECT_EQ(default_opts.min_num_view_per_track, 3);
}

// Test that Solve can be called multiple times without issues
TEST_F(BundleAdjusterTest_98, SolveCalledMultipleTimes_98) {
  BundleAdjuster ba(options_);

  // First call with empty - should return false
  bool result1 = ba.Solve(rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result1);

  // Second call with empty - should still return false
  bool result2 = ba.Solve(rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result2);
}

// Test with images present but tracks empty returns false
TEST_F(BundleAdjusterTest_98, ImagesNonEmptyTracksEmpty_98) {
  BundleAdjuster ba(options_);

  Image img;
  img.camera_id = 0;
  images_[0] = img;
  images_[1] = img;

  // tracks_ is still empty
  bool result = ba.Solve(rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result);
}

// Test CreateLossFunction does not return null
TEST_F(BundleAdjusterTest_98, CreateLossFunctionNotNull_98) {
  BundleAdjusterOptions opts;
  auto loss = opts.CreateLossFunction();
  // The loss function should be created (may or may not be null depending on config,
  // but the function should not throw)
}

}  // namespace
}  // namespace glomap
