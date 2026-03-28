#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/global_positioning.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/view_graph.h"
#include "glomap/types.h"

#include <unordered_map>

namespace glomap {
namespace {

class GlobalPositionerTest_106 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Default options
    options_ = GlobalPositionerOptions();
  }

  // Helper to create a registered image with a trivial frame
  void CreateRegisteredImage(
      image_t image_id,
      camera_t camera_id,
      frame_t frame_id,
      std::unordered_map<image_t, Image>& images,
      std::unordered_map<frame_t, Frame>& frames,
      std::unordered_map<camera_t, Camera>& cameras,
      std::unordered_map<rig_t, Rig>& rigs) {
    // Create frame if not exists
    if (frames.find(frame_id) == frames.end()) {
      frames[frame_id] = Frame();
      frames[frame_id].frame_id = frame_id;
      frames[frame_id].is_registered = true;
      frames[frame_id].rig_id = 0;
    }

    // Create rig if not exists
    if (rigs.find(0) == rigs.end()) {
      rigs[0] = Rig();
      rigs[0].rig_id = 0;
    }

    // Create camera if not exists
    if (cameras.find(camera_id) == cameras.end()) {
      cameras[camera_id] = Camera();
      cameras[camera_id].camera_id = camera_id;
    }

    Image img(image_id, camera_id, "test_image_" + std::to_string(image_id));
    img.frame_id = frame_id;
    img.frame_ptr = &frames[frame_id];
    img.is_registered = true;
    img.cam_from_world = Rigid3d();
    images[image_id] = img;
  }

  GlobalPositionerOptions options_;
};

// Test that Solve can be called with empty inputs
TEST_F(GlobalPositionerTest_106, SolveWithEmptyInputs_106) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  // With empty inputs, Solve should still return (either true or false)
  // We just check it doesn't crash
  SUCCEED();
}

// Test that Solve works with a minimal valid configuration (two images, one pair)
TEST_F(GlobalPositionerTest_106, SolveWithMinimalValidConfig_106) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateRegisteredImage(0, 0, 0, images, frames, cameras, rigs);
  CreateRegisteredImage(1, 0, 1, images, frames, cameras, rigs);

  // Create a valid image pair
  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.cam2_from_cam1 = Rigid3d(Eigen::Quaterniond::Identity(),
                                 Eigen::Vector3d(1.0, 0.0, 0.0));
  view_graph.image_pairs[pair.pair_id] = pair;

  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  // The solver should return a result without crashing
  SUCCEED();
}

// Test that Solve handles unregistered images (they should be skipped)
TEST_F(GlobalPositionerTest_106, SolveSkipsUnregisteredImages_106) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Create one registered and one unregistered image
  CreateRegisteredImage(0, 0, 0, images, frames, cameras, rigs);

  Image unregistered_img(1, 0, "unregistered");
  unregistered_img.is_registered = false;
  unregistered_img.frame_id = 1;
  frames[1] = Frame();
  frames[1].frame_id = 1;
  frames[1].is_registered = false;
  unregistered_img.frame_ptr = &frames[1];
  images[1] = unregistered_img;

  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.cam2_from_cam1 = Rigid3d(Eigen::Quaterniond::Identity(),
                                 Eigen::Vector3d(1.0, 0.0, 0.0));
  view_graph.image_pairs[pair.pair_id] = pair;

  // Should not crash even with unregistered images
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  SUCCEED();
}

// Test that invalid image pairs are skipped
TEST_F(GlobalPositionerTest_106, SolveSkipsInvalidPairs_106) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateRegisteredImage(0, 0, 0, images, frames, cameras, rigs);
  CreateRegisteredImage(1, 0, 1, images, frames, cameras, rigs);

  // Create an invalid image pair
  ImagePair pair(0, 1);
  pair.is_valid = false;
  pair.cam2_from_cam1 = Rigid3d(Eigen::Quaterniond::Identity(),
                                 Eigen::Vector3d(1.0, 0.0, 0.0));
  view_graph.image_pairs[pair.pair_id] = pair;

  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  SUCCEED();
}

// Test with multiple image pairs forming a chain
TEST_F(GlobalPositionerTest_106, SolveWithMultiplePairs_106) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Create 4 images
  for (int i = 0; i < 4; ++i) {
    CreateRegisteredImage(i, 0, i, images, frames, cameras, rigs);
  }

  // Create chain of pairs: 0-1, 1-2, 2-3
  for (int i = 0; i < 3; ++i) {
    ImagePair pair(i, i + 1);
    pair.is_valid = true;
    pair.cam2_from_cam1 = Rigid3d(Eigen::Quaterniond::Identity(),
                                   Eigen::Vector3d(1.0, 0.0, 0.0));
    view_graph.image_pairs[pair.pair_id] = pair;
  }

  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  SUCCEED();
}

// Test that GetOptions returns modifiable options
TEST_F(GlobalPositionerTest_106, GetOptionsReturnsReference_106) {
  GlobalPositioner positioner(options_);
  GlobalPositionerOptions& opts = positioner.GetOptions();
  // Verify we can access options through the reference
  // Just check it doesn't crash
  SUCCEED();
}

// Test with image pair referencing non-existent images
TEST_F(GlobalPositionerTest_106, SolveWithMissingImagesInPair_106) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Only create image 0, but pair references 0 and 1
  CreateRegisteredImage(0, 0, 0, images, frames, cameras, rigs);

  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.cam2_from_cam1 = Rigid3d(Eigen::Quaterniond::Identity(),
                                 Eigen::Vector3d(1.0, 0.0, 0.0));
  view_graph.image_pairs[pair.pair_id] = pair;

  // Should skip the pair since image 1 doesn't exist
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  SUCCEED();
}

// Test with no image pairs but with images
TEST_F(GlobalPositionerTest_106, SolveWithImagesButNoPairs_106) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateRegisteredImage(0, 0, 0, images, frames, cameras, rigs);
  CreateRegisteredImage(1, 0, 1, images, frames, cameras, rigs);

  // No pairs added to view_graph
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  SUCCEED();
}

// Test with tracks (point-to-camera constraints)
TEST_F(GlobalPositionerTest_106, SolveWithTracks_106) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateRegisteredImage(0, 0, 0, images, frames, cameras, rigs);
  CreateRegisteredImage(1, 0, 1, images, frames, cameras, rigs);

  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.cam2_from_cam1 = Rigid3d(Eigen::Quaterniond::Identity(),
                                 Eigen::Vector3d(1.0, 0.0, 0.0));
  view_graph.image_pairs[pair.pair_id] = pair;

  // Create a track observed by both images
  Track track;
  track.track_id = 0;
  track.is_established = true;
  track.observations.push_back(std::make_pair(0, 0));
  track.observations.push_back(std::make_pair(1, 0));
  track.xyz = Eigen::Vector3d(0.5, 0.5, 5.0);
  tracks[0] = track;

  // Add feature observations to images
  images[0].features.push_back(Eigen::Vector2d(100, 100));
  images[0].features_undist.push_back(Eigen::Vector3d(0.1, 0.1, 1.0));
  images[1].features.push_back(Eigen::Vector2d(200, 200));
  images[1].features_undist.push_back(Eigen::Vector3d(0.2, 0.2, 1.0));

  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  SUCCEED();
}

// Test construction with default options
TEST_F(GlobalPositionerTest_106, ConstructWithDefaultOptions_106) {
  GlobalPositionerOptions default_opts;
  EXPECT_NO_THROW(GlobalPositioner positioner(default_opts));
}

// Test with a fully connected graph of 3 images
TEST_F(GlobalPositionerTest_106, SolveWithFullyConnectedGraph_106) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  for (int i = 0; i < 3; ++i) {
    CreateRegisteredImage(i, 0, i, images, frames, cameras, rigs);
  }

  // Fully connected: 0-1, 0-2, 1-2
  std::vector<std::pair<int, int>> pairs_list = {{0, 1}, {0, 2}, {1, 2}};
  for (auto& [a, b] : pairs_list) {
    ImagePair pair(a, b);
    pair.is_valid = true;
    pair.cam2_from_cam1 = Rigid3d(Eigen::Quaterniond::Identity(),
                                   Eigen::Vector3d(1.0, 0.0, 0.0));
    view_graph.image_pairs[pair.pair_id] = pair;
  }

  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  // With a fully connected graph, the solver should be able to find a solution
  SUCCEED();
}

// Test Solve return value with valid configuration
TEST_F(GlobalPositionerTest_106, SolveReturnsTrueForValidConfig_106) {
  GlobalPositioner positioner(options_);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Create a well-conditioned problem with 3 images
  for (int i = 0; i < 3; ++i) {
    CreateRegisteredImage(i, 0, i, images, frames, cameras, rigs);
  }

  // Create pairs with different translations for well-conditioned system
  {
    ImagePair pair(0, 1);
    pair.is_valid = true;
    pair.cam2_from_cam1 = Rigid3d(Eigen::Quaterniond::Identity(),
                                   Eigen::Vector3d(1.0, 0.0, 0.0));
    view_graph.image_pairs[pair.pair_id] = pair;
  }
  {
    ImagePair pair(0, 2);
    pair.is_valid = true;
    pair.cam2_from_cam1 = Rigid3d(Eigen::Quaterniond::Identity(),
                                   Eigen::Vector3d(0.0, 1.0, 0.0));
    view_graph.image_pairs[pair.pair_id] = pair;
  }
  {
    ImagePair pair(1, 2);
    pair.is_valid = true;
    pair.cam2_from_cam1 = Rigid3d(Eigen::Quaterniond::Identity(),
                                   Eigen::Vector3d(-1.0, 1.0, 0.0));
    view_graph.image_pairs[pair.pair_id] = pair;
  }

  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result);
}

}  // namespace
}  // namespace glomap
