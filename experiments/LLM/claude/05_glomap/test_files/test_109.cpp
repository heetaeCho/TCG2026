#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/global_positioning.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/types.h"

#include <unordered_map>

namespace glomap {
namespace {

class GlobalPositionerTest_109 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Default options
    options_ = GlobalPositionerOptions();
  }

  GlobalPositionerOptions options_;
};

// Test that GlobalPositioner can be constructed with default options
TEST_F(GlobalPositionerTest_109, ConstructWithDefaultOptions_109) {
  EXPECT_NO_THROW(GlobalPositioner positioner(options_));
}

// Test that GetOptions returns a reference to the internal options
TEST_F(GlobalPositionerTest_109, GetOptionsReturnsOptions_109) {
  GlobalPositioner positioner(options_);
  GlobalPositionerOptions& opts = positioner.GetOptions();
  // The returned options should be accessible
  EXPECT_NO_THROW((void)opts.thres_loss_function);
}

// Test Solve with empty inputs - no view graph edges, no images, no tracks
TEST_F(GlobalPositionerTest_109, SolveWithEmptyInputs_109) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // With empty data, Solve should handle gracefully (may return false or true)
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  // We just verify it doesn't crash; result depends on implementation
  (void)result;
}

// Test Solve with minimal valid setup - two images forming one edge
TEST_F(GlobalPositionerTest_109, SolveWithMinimalViewGraph_109) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Create two cameras
  Camera cam1;
  cam1.camera_id = 0;
  cam1.model_id = 0;  // Simple pinhole
  cam1.width = 640;
  cam1.height = 480;
  cam1.params = {500.0, 320.0, 240.0};
  cameras[0] = cam1;

  Camera cam2;
  cam2.camera_id = 1;
  cam2.model_id = 0;
  cam2.width = 640;
  cam2.height = 480;
  cam2.params = {500.0, 320.0, 240.0};
  cameras[1] = cam2;

  // Create two images
  Image img1;
  img1.image_id = 0;
  img1.camera_id = 0;
  img1.frame_id = 0;
  images[0] = img1;

  Image img2;
  img2.image_id = 1;
  img2.camera_id = 1;
  img2.frame_id = 1;
  images[1] = img2;

  // Create frames
  Frame frame1;
  frame1.frame_id = 0;
  frame1.rig_id = 0;
  frames[0] = frame1;

  Frame frame2;
  frame2.frame_id = 1;
  frame2.rig_id = 0;
  frames[1] = frame2;

  // Create a rig
  Rig rig;
  rig.rig_id = 0;
  rigs[0] = rig;

  // Add an edge to the view graph
  image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
  ImagePair image_pair;
  image_pair.image_id1 = 0;
  image_pair.image_id2 = 1;
  image_pair.is_valid = true;
  Rigid3d rel_pose;
  rel_pose.rotation = Eigen::Quaterniond::Identity();
  rel_pose.translation = Eigen::Vector3d(1.0, 0.0, 0.0);
  image_pair.cam2_from_cam1 = rel_pose;
  view_graph.image_pairs[pair_id] = image_pair;

  // Attempt to solve - should not crash
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  (void)result;
}

// Test Solve with tracks present
TEST_F(GlobalPositionerTest_109, SolveWithTracks_109) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Create cameras
  Camera cam;
  cam.camera_id = 0;
  cam.model_id = 0;
  cam.width = 640;
  cam.height = 480;
  cam.params = {500.0, 320.0, 240.0};
  cameras[0] = cam;
  cameras[1] = cam;
  cameras[1].camera_id = 1;

  // Create images
  Image img1;
  img1.image_id = 0;
  img1.camera_id = 0;
  img1.frame_id = 0;
  images[0] = img1;

  Image img2;
  img2.image_id = 1;
  img2.camera_id = 1;
  img2.frame_id = 1;
  images[1] = img2;

  // Create frames
  Frame frame1;
  frame1.frame_id = 0;
  frame1.rig_id = 0;
  frames[0] = frame1;

  Frame frame2;
  frame2.frame_id = 1;
  frame2.rig_id = 0;
  frames[1] = frame2;

  // Create rig
  Rig rig;
  rig.rig_id = 0;
  rigs[0] = rig;

  // Add edge
  image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
  ImagePair image_pair;
  image_pair.image_id1 = 0;
  image_pair.image_id2 = 1;
  image_pair.is_valid = true;
  Rigid3d rel_pose;
  rel_pose.rotation = Eigen::Quaterniond::Identity();
  rel_pose.translation = Eigen::Vector3d(1.0, 0.0, 0.0);
  image_pair.cam2_from_cam1 = rel_pose;
  view_graph.image_pairs[pair_id] = image_pair;

  // Create a track observed by both images
  Track track;
  track.track_id = 0;
  track.is_initialized = true;
  track.xyz = Eigen::Vector3d(0.5, 0.5, 5.0);
  track.observations.push_back(Observation(0, 0));
  track.observations.push_back(Observation(1, 0));
  tracks[0] = track;

  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  (void)result;
}

// Test that options can be modified through GetOptions
TEST_F(GlobalPositionerTest_109, ModifyOptionsViaGetOptions_109) {
  GlobalPositioner positioner(options_);
  GlobalPositionerOptions& opts = positioner.GetOptions();
  
  double original_thres = opts.thres_loss_function;
  opts.thres_loss_function = 0.5;
  
  // Verify the modification persists
  EXPECT_DOUBLE_EQ(positioner.GetOptions().thres_loss_function, 0.5);
  EXPECT_NE(positioner.GetOptions().thres_loss_function, original_thres);
}

// Test Solve with no edges in view graph but frames exist
TEST_F(GlobalPositionerTest_109, SolveNoEdgesButFramesExist_109) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Add frames but no view graph edges
  Frame frame1;
  frame1.frame_id = 0;
  frame1.rig_id = 0;
  frames[0] = frame1;

  Rig rig;
  rig.rig_id = 0;
  rigs[0] = rig;

  Camera cam;
  cam.camera_id = 0;
  cameras[0] = cam;

  Image img;
  img.image_id = 0;
  img.camera_id = 0;
  img.frame_id = 0;
  images[0] = img;

  // Should handle gracefully with no edges
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  (void)result;
}

// Test construction with different option values
TEST_F(GlobalPositionerTest_109, ConstructWithCustomOptions_109) {
  GlobalPositionerOptions custom_options;
  custom_options.thres_loss_function = 1.0;
  
  EXPECT_NO_THROW(GlobalPositioner positioner(custom_options));
  
  GlobalPositioner positioner(custom_options);
  EXPECT_DOUBLE_EQ(positioner.GetOptions().thres_loss_function, 1.0);
}

// Test Solve with empty tracks map but non-empty view graph
TEST_F(GlobalPositionerTest_109, SolveWithEmptyTracksMap_109) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;  // empty

  // Minimal setup with two images and one edge
  Camera cam;
  cam.camera_id = 0;
  cam.model_id = 0;
  cam.width = 640;
  cam.height = 480;
  cam.params = {500.0, 320.0, 240.0};
  cameras[0] = cam;
  cameras[1] = cam;
  cameras[1].camera_id = 1;

  Image img1;
  img1.image_id = 0;
  img1.camera_id = 0;
  img1.frame_id = 0;
  images[0] = img1;

  Image img2;
  img2.image_id = 1;
  img2.camera_id = 1;
  img2.frame_id = 1;
  images[1] = img2;

  Frame frame1;
  frame1.frame_id = 0;
  frame1.rig_id = 0;
  frames[0] = frame1;

  Frame frame2;
  frame2.frame_id = 1;
  frame2.rig_id = 0;
  frames[1] = frame2;

  Rig rig;
  rig.rig_id = 0;
  rigs[0] = rig;

  image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
  ImagePair image_pair;
  image_pair.image_id1 = 0;
  image_pair.image_id2 = 1;
  image_pair.is_valid = true;
  Rigid3d rel_pose;
  rel_pose.rotation = Eigen::Quaterniond::Identity();
  rel_pose.translation = Eigen::Vector3d(1.0, 0.0, 0.0);
  image_pair.cam2_from_cam1 = rel_pose;
  view_graph.image_pairs[pair_id] = image_pair;

  // Solve with empty tracks - exercises the tracks.size() > 0 branch as false
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  (void)result;
}

}  // namespace
}  // namespace glomap
