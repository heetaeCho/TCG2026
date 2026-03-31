#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/bundle_adjustment.h"
#include "glomap/types.h"

#include <unordered_map>

namespace glomap {
namespace {

class BundleAdjusterTest_10 : public ::testing::Test {
 protected:
  void SetUp() override {
    adjuster_ = std::make_unique<BundleAdjuster>();
  }

  // Helper to create a minimal valid camera
  Camera CreateCamera(camera_t cam_id) {
    Camera camera;
    camera.camera_id = cam_id;
    // Set a simple pinhole model with reasonable defaults
    camera.model_id = 0;  // SIMPLE_PINHOLE or similar
    camera.width = 640;
    camera.height = 480;
    camera.params = {500.0, 320.0, 240.0};  // fx, cx, cy
    return camera;
  }

  // Helper to create a minimal valid image
  Image CreateImage(image_t img_id, camera_t cam_id) {
    Image image;
    image.image_id = img_id;
    image.camera_id = cam_id;
    image.is_registered = true;
    // Set a valid pose (identity rotation, zero translation)
    image.cam_from_world = Rigid3d();
    return image;
  }

  // Helper to create a minimal valid track with observations
  Track CreateTrack(track_t track_id,
                    const std::vector<std::pair<image_t, int>>& observations) {
    Track track;
    track.track_id = track_id;
    track.is_established = true;
    track.xyz = Eigen::Vector3d(1.0, 2.0, 10.0);
    for (const auto& [img_id, feat_idx] : observations) {
      track.observations.emplace_back(img_id, feat_idx);
    }
    return track;
  }

  std::unique_ptr<BundleAdjuster> adjuster_;
  std::unordered_map<rig_t, Rig> rigs_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<frame_t, Frame> frames_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;
};

// Test that Solve returns false when images map is empty
TEST_F(BundleAdjusterTest_10, SolveWithEmptyImages_10) {
  // images_ is empty, tracks_ has one entry
  tracks_[0] = CreateTrack(0, {{0, 0}});

  bool result = adjuster_->Solve(rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result);
}

// Test that Solve returns false when tracks map is empty
TEST_F(BundleAdjusterTest_10, SolveWithEmptyTracks_10) {
  // images_ has one entry, tracks_ is empty
  cameras_[0] = CreateCamera(0);
  images_[0] = CreateImage(0, 0);

  bool result = adjuster_->Solve(rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result);
}

// Test that Solve returns false when both images and tracks are empty
TEST_F(BundleAdjusterTest_10, SolveWithEmptyImagesAndTracks_10) {
  bool result = adjuster_->Solve(rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result);
}

// Test that Solve can be called with minimal valid data
// (This test verifies the function doesn't crash; the result depends on
//  whether ceres can solve the problem with the given data)
TEST_F(BundleAdjusterTest_10, SolveWithMinimalValidData_10) {
  camera_t cam_id = 0;
  image_t img_id_1 = 0;
  image_t img_id_2 = 1;
  track_t track_id = 0;

  Camera cam = CreateCamera(cam_id);
  cameras_[cam_id] = cam;

  Image img1 = CreateImage(img_id_1, cam_id);
  // Add a feature point for the track observation
  img1.features.push_back(Eigen::Vector2d(100.0, 200.0));
  images_[img_id_1] = img1;

  Image img2 = CreateImage(img_id_2, cam_id);
  // Slightly different pose
  img2.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(),
                                 Eigen::Vector3d(1.0, 0.0, 0.0));
  img2.features.push_back(Eigen::Vector2d(150.0, 210.0));
  images_[img_id_2] = img2;

  // Create frames
  Frame frame1;
  frame1.frame_id = 0;
  frame1.image_id = img_id_1;
  frame1.camera_id = cam_id;
  frame1.rig_id = -1;
  frames_[0] = frame1;

  Frame frame2;
  frame2.frame_id = 1;
  frame2.image_id = img_id_2;
  frame2.camera_id = cam_id;
  frame2.rig_id = -1;
  frames_[1] = frame2;

  tracks_[track_id] = CreateTrack(track_id, {{img_id_1, 0}, {img_id_2, 0}});

  // We just verify it doesn't crash. The actual solvability depends on
  // internal constraint setup.
  bool result = adjuster_->Solve(rigs_, cameras_, frames_, images_, tracks_);
  // Result could be true or false depending on internal problem setup;
  // we just ensure no crash.
  (void)result;
}

// Test that Solve can be called multiple times (tests Reset behavior)
TEST_F(BundleAdjusterTest_10, SolveCalledMultipleTimes_10) {
  // First call with empty images should return false
  tracks_[0] = CreateTrack(0, {{0, 0}});
  bool result1 = adjuster_->Solve(rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result1);

  // Second call should also handle gracefully
  bool result2 = adjuster_->Solve(rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result2);
}

// Test with single image (edge case - should still fail or handle gracefully
// since BA typically needs multiple views)
TEST_F(BundleAdjusterTest_10, SolveWithSingleImage_10) {
  camera_t cam_id = 0;
  image_t img_id = 0;
  track_t track_id = 0;

  cameras_[cam_id] = CreateCamera(cam_id);

  Image img = CreateImage(img_id, cam_id);
  img.features.push_back(Eigen::Vector2d(100.0, 200.0));
  images_[img_id] = img;

  Frame frame;
  frame.frame_id = 0;
  frame.image_id = img_id;
  frame.camera_id = cam_id;
  frame.rig_id = -1;
  frames_[0] = frame;

  tracks_[track_id] = CreateTrack(track_id, {{img_id, 0}});

  // Should not crash; result depends on implementation
  bool result = adjuster_->Solve(rigs_, cameras_, frames_, images_, tracks_);
  (void)result;
}

// Test with images present but no tracks - should return false
TEST_F(BundleAdjusterTest_10, SolveImagesButNoTracks_10) {
  cameras_[0] = CreateCamera(0);
  images_[0] = CreateImage(0, 0);
  images_[1] = CreateImage(1, 0);

  bool result = adjuster_->Solve(rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result);
}

}  // namespace
}  // namespace glomap
