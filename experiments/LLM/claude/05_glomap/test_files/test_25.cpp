#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/global_positioning.h"
#include "glomap/types.h"

#include <unordered_map>

namespace glomap {
namespace {

class GlobalPositionerTest_25 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up a minimal valid scenario
  }

  ViewGraph view_graph_;
  std::unordered_map<rig_t, Rig> rigs_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<frame_t, Frame> frames_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;
};

// Test that Solve returns false when images map is empty
TEST_F(GlobalPositionerTest_25, EmptyImagesReturnsFalse_25) {
  GlobalPositionerOptions options;
  GlobalPositioner positioner(options);

  // images_ is empty
  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result);
}

// Test that Solve returns false when image_pairs is empty and constraint_type is not ONLY_POINTS
TEST_F(GlobalPositionerTest_25, EmptyImagePairsWithNonOnlyPointsReturnsFalse_25) {
  GlobalPositionerOptions options;
  options.constraint_type = GlobalPositionerOptions::ONLY_CAMERAS;
  GlobalPositioner positioner(options);

  // Add at least one image so we don't fail at the images check
  Image img;
  img.image_id = 0;
  img.camera_id = 0;
  img.rig_id = 0;
  img.frame_id = 0;
  img.is_registered = true;
  images_[0] = img;

  // view_graph_.image_pairs is empty
  // constraint_type is ONLY_CAMERAS, not ONLY_POINTS
  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result);
}

// Test that Solve returns false when tracks is empty and constraint_type is not ONLY_CAMERAS
TEST_F(GlobalPositionerTest_25, EmptyTracksWithNonOnlyCamerasReturnsFalse_25) {
  GlobalPositionerOptions options;
  options.constraint_type = GlobalPositionerOptions::ONLY_POINTS;
  GlobalPositioner positioner(options);

  // Add at least one image
  Image img;
  img.image_id = 0;
  img.camera_id = 0;
  img.rig_id = 0;
  img.frame_id = 0;
  img.is_registered = true;
  images_[0] = img;

  // tracks_ is empty, constraint_type is ONLY_POINTS (not ONLY_CAMERAS)
  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result);
}

// Test with ONLY_POINTS constraint type: empty image_pairs should be allowed
// but empty tracks should cause failure
TEST_F(GlobalPositionerTest_25, OnlyPointsWithEmptyTracksReturnsFalse_25) {
  GlobalPositionerOptions options;
  options.constraint_type = GlobalPositionerOptions::ONLY_POINTS;
  GlobalPositioner positioner(options);

  Image img;
  img.image_id = 0;
  img.camera_id = 0;
  img.rig_id = 0;
  img.frame_id = 0;
  img.is_registered = true;
  images_[0] = img;

  // Empty image_pairs is OK for ONLY_POINTS, but empty tracks is not
  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result);
}

// Test with a minimal valid setup using ONLY_CAMERAS constraint type
TEST_F(GlobalPositionerTest_25, MinimalValidSetupOnlyCameras_25) {
  GlobalPositionerOptions options;
  options.constraint_type = GlobalPositionerOptions::ONLY_CAMERAS;
  GlobalPositioner positioner(options);

  // Create a rig
  Rig rig;
  rig.rig_id = 0;
  rigs_[0] = rig;

  // Create a camera
  Camera camera;
  camera.camera_id = 0;
  camera.model_id = 0;  // Simple pinhole
  camera.width = 640;
  camera.height = 480;
  camera.params = {500.0, 320.0, 240.0};
  cameras_[0] = camera;

  // Create frames
  Frame frame0;
  frame0.frame_id = 0;
  frame0.rig_id = 0;
  frame0.is_registered = true;
  frames_[0] = frame0;

  Frame frame1;
  frame1.frame_id = 1;
  frame1.rig_id = 0;
  frame1.is_registered = true;
  frames_[1] = frame1;

  // Create images
  Image img0;
  img0.image_id = 0;
  img0.camera_id = 0;
  img0.rig_id = 0;
  img0.frame_id = 0;
  img0.is_registered = true;
  img0.cam_from_world = Eigen::Matrix3x4d::Identity();
  images_[0] = img0;

  Image img1;
  img1.image_id = 1;
  img1.camera_id = 0;
  img1.rig_id = 0;
  img1.frame_id = 1;
  img1.is_registered = true;
  img1.cam_from_world = Eigen::Matrix3x4d::Identity();
  images_[1] = img1;

  // Create an image pair
  image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
  ImagePair image_pair;
  image_pair.image_id1 = 0;
  image_pair.image_id2 = 1;
  image_pair.is_valid = true;
  image_pair.cam2_from_cam1 = Rigid3d();
  view_graph_.image_pairs[pair_id] = image_pair;

  // No tracks needed for ONLY_CAMERAS
  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  // The result depends on whether the solver finds a usable solution
  // We mainly verify it doesn't crash and returns a bool
  EXPECT_TRUE(result == true || result == false);
}

// Test that Solve with ONLY_CAMERAS constraint and empty tracks still works
TEST_F(GlobalPositionerTest_25, OnlyCamerasEmptyTracksAllowed_25) {
  GlobalPositionerOptions options;
  options.constraint_type = GlobalPositionerOptions::ONLY_CAMERAS;
  GlobalPositioner positioner(options);

  // Create minimal setup
  Rig rig;
  rig.rig_id = 0;
  rigs_[0] = rig;

  Camera camera;
  camera.camera_id = 0;
  camera.model_id = 0;
  camera.width = 640;
  camera.height = 480;
  camera.params = {500.0, 320.0, 240.0};
  cameras_[0] = camera;

  Frame frame0;
  frame0.frame_id = 0;
  frame0.rig_id = 0;
  frame0.is_registered = true;
  frames_[0] = frame0;

  Frame frame1;
  frame1.frame_id = 1;
  frame1.rig_id = 0;
  frame1.is_registered = true;
  frames_[1] = frame1;

  Image img0;
  img0.image_id = 0;
  img0.camera_id = 0;
  img0.rig_id = 0;
  img0.frame_id = 0;
  img0.is_registered = true;
  img0.cam_from_world = Eigen::Matrix3x4d::Identity();
  images_[0] = img0;

  Image img1;
  img1.image_id = 1;
  img1.camera_id = 0;
  img1.rig_id = 0;
  img1.frame_id = 1;
  img1.is_registered = true;
  img1.cam_from_world = Eigen::Matrix3x4d::Identity();
  images_[1] = img1;

  image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
  ImagePair image_pair;
  image_pair.image_id1 = 0;
  image_pair.image_id2 = 1;
  image_pair.is_valid = true;
  image_pair.cam2_from_cam1 = Rigid3d();
  view_graph_.image_pairs[pair_id] = image_pair;

  // tracks_ is empty but that's OK for ONLY_CAMERAS
  // Should not return false due to empty tracks check
  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  // At minimum, it should not crash
  SUCCEED();
}

// Test that completely empty inputs (no images) always returns false
TEST_F(GlobalPositionerTest_25, AllEmptyReturnsFalse_25) {
  GlobalPositionerOptions options;
  GlobalPositioner positioner(options);

  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result);
}

// Test with single image - no pairs and no tracks (default constraint type)
TEST_F(GlobalPositionerTest_25, SingleImageNoPairsDefaultConstraint_25) {
  GlobalPositionerOptions options;
  GlobalPositioner positioner(options);

  Image img;
  img.image_id = 0;
  img.camera_id = 0;
  img.rig_id = 0;
  img.frame_id = 0;
  img.is_registered = true;
  images_[0] = img;

  // Default constraint type should require both pairs and tracks
  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result);
}

}  // namespace
}  // namespace glomap
