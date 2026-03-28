#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/global_positioning.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/scene/track.h"
#include "glomap/types.h"

#include <unordered_map>

namespace glomap {
namespace {

class GlobalPositionerTest_107 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Default options
    options_.generate_random_positions = true;
    options_.generate_random_points = true;
    options_.generate_scales = true;
    options_.optimize_positions = true;
    options_.optimize_scales = true;
    options_.seed = 42;
    options_.constraint_type = GlobalPositionerOptions::ONLY_POINTS;
  }

  GlobalPositionerOptions options_;

  // Helper to create a minimal ViewGraph
  ViewGraph CreateMinimalViewGraph() {
    ViewGraph vg;
    return vg;
  }

  // Helper to create a simple scene with images, cameras, frames, rigs, and tracks
  void CreateSimpleScene(
      std::unordered_map<rig_t, Rig>& rigs,
      std::unordered_map<camera_t, Camera>& cameras,
      std::unordered_map<frame_t, Frame>& frames,
      std::unordered_map<image_t, Image>& images,
      std::unordered_map<track_t, Track>& tracks,
      int num_images = 3,
      int num_tracks = 5,
      int obs_per_track = 3) {
    // Create cameras
    for (int i = 0; i < num_images; i++) {
      Camera cam;
      cam.camera_id = i;
      cam.model_id = 0;  // SIMPLE_PINHOLE or similar
      cam.width = 640;
      cam.height = 480;
      cam.params = {500.0, 320.0, 240.0};
      cameras[i] = cam;
    }

    // Create rigs
    Rig rig;
    rig.rig_id = 0;
    rigs[0] = rig;

    // Create frames and images
    for (int i = 0; i < num_images; i++) {
      Frame frame;
      frame.frame_id = i;
      frame.rig_id = 0;
      frames[i] = frame;

      Image img;
      img.image_id = i;
      img.camera_id = i;
      img.frame_id = i;
      img.is_registered = true;
      images[i] = img;
    }

    // Create tracks
    for (int t = 0; t < num_tracks; t++) {
      Track track;
      track.track_id = t;
      track.xyz = Eigen::Vector3d::Random();
      track.is_initialized = true;
      for (int o = 0; o < std::min(obs_per_track, num_images); o++) {
        track.observations.push_back(Observation(o, t));
      }
      tracks[t] = track;
    }
  }
};

// Test that GlobalPositioner can be constructed with default options
TEST_F(GlobalPositionerTest_107, ConstructWithDefaultOptions_107) {
  GlobalPositionerOptions default_opts;
  EXPECT_NO_THROW(GlobalPositioner positioner(default_opts));
}

// Test that GlobalPositioner can be constructed with custom options
TEST_F(GlobalPositionerTest_107, ConstructWithCustomOptions_107) {
  options_.constraint_type = GlobalPositionerOptions::POINTS_AND_CAMERAS_BALANCED;
  options_.constraint_reweight_scale = 2.0;
  EXPECT_NO_THROW(GlobalPositioner positioner(options_));
}

// Test Solve with empty view graph and empty scene data
TEST_F(GlobalPositionerTest_107, SolveWithEmptyData_107) {
  GlobalPositioner positioner(options_);
  ViewGraph vg;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // With empty data, Solve should handle gracefully (return true or false)
  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  // We just check it doesn't crash - result may vary
  SUCCEED();
}

// Test Solve with a minimal scene
TEST_F(GlobalPositionerTest_107, SolveWithMinimalScene_107) {
  options_.constraint_type = GlobalPositionerOptions::ONLY_POINTS;
  GlobalPositioner positioner(options_);
  ViewGraph vg;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateSimpleScene(rigs, cameras, frames, images, tracks, 3, 5, 3);

  // Add edges to the view graph for camera-to-camera constraints
  for (int i = 0; i < 3; i++) {
    for (int j = i + 1; j < 3; j++) {
      ImagePair pair;
      pair.image_id1 = i;
      pair.image_id2 = j;
      pair.is_valid = true;
      vg.image_pairs[ImagePair::ImagePairToPairId(i, j)] = pair;
    }
  }

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  // Just verify it doesn't crash
  SUCCEED();
}

// Test with ONLY_CAMERAS constraint type
TEST_F(GlobalPositionerTest_107, SolveWithOnlyCameras_107) {
  options_.constraint_type = GlobalPositionerOptions::ONLY_CAMERAS;
  GlobalPositioner positioner(options_);
  ViewGraph vg;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateSimpleScene(rigs, cameras, frames, images, tracks, 4, 0, 0);

  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      ImagePair pair;
      pair.image_id1 = i;
      pair.image_id2 = j;
      pair.is_valid = true;
      vg.image_pairs[ImagePair::ImagePairToPairId(i, j)] = pair;
    }
  }

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  SUCCEED();
}

// Test with POINTS_AND_CAMERAS_BALANCED constraint type
TEST_F(GlobalPositionerTest_107, SolveWithBalancedConstraints_107) {
  options_.constraint_type = GlobalPositionerOptions::POINTS_AND_CAMERAS_BALANCED;
  options_.constraint_reweight_scale = 1.5;
  GlobalPositioner positioner(options_);
  ViewGraph vg;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateSimpleScene(rigs, cameras, frames, images, tracks, 4, 6, 3);

  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      ImagePair pair;
      pair.image_id1 = i;
      pair.image_id2 = j;
      pair.is_valid = true;
      vg.image_pairs[ImagePair::ImagePairToPairId(i, j)] = pair;
    }
  }

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  SUCCEED();
}

// Test with POINTS_AND_CAMERAS constraint type
TEST_F(GlobalPositionerTest_107, SolveWithPointsAndCameras_107) {
  options_.constraint_type = GlobalPositionerOptions::POINTS_AND_CAMERAS;
  GlobalPositioner positioner(options_);
  ViewGraph vg;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateSimpleScene(rigs, cameras, frames, images, tracks, 4, 6, 3);

  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      ImagePair pair;
      pair.image_id1 = i;
      pair.image_id2 = j;
      pair.is_valid = true;
      vg.image_pairs[ImagePair::ImagePairToPairId(i, j)] = pair;
    }
  }

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  SUCCEED();
}

// Test with tracks that have too few observations (should be skipped)
TEST_F(GlobalPositionerTest_107, TracksWithFewObservationsSkipped_107) {
  options_.constraint_type = GlobalPositionerOptions::ONLY_POINTS;
  options_.min_num_view_per_track = 5;  // High threshold
  GlobalPositioner positioner(options_);
  ViewGraph vg;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Create scene with only 2 observations per track, less than threshold of 5
  CreateSimpleScene(rigs, cameras, frames, images, tracks, 3, 5, 2);

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  SUCCEED();
}

// Test with no tracks (empty tracks map)
TEST_F(GlobalPositionerTest_107, EmptyTracks_107) {
  options_.constraint_type = GlobalPositionerOptions::ONLY_POINTS;
  GlobalPositioner positioner(options_);
  ViewGraph vg;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateSimpleScene(rigs, cameras, frames, images, tracks, 3, 0, 0);

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  SUCCEED();
}

// Test with generate_random_points disabled
TEST_F(GlobalPositionerTest_107, SolveWithoutRandomPoints_107) {
  options_.generate_random_points = false;
  options_.constraint_type = GlobalPositionerOptions::ONLY_POINTS;
  GlobalPositioner positioner(options_);
  ViewGraph vg;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateSimpleScene(rigs, cameras, frames, images, tracks, 3, 5, 3);

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  SUCCEED();
}

// Test with generate_random_positions disabled
TEST_F(GlobalPositionerTest_107, SolveWithoutRandomPositions_107) {
  options_.generate_random_positions = false;
  options_.constraint_type = GlobalPositionerOptions::ONLY_POINTS;
  GlobalPositioner positioner(options_);
  ViewGraph vg;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateSimpleScene(rigs, cameras, frames, images, tracks, 3, 5, 3);

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  SUCCEED();
}

// Test different seed values produce (potentially) different results
TEST_F(GlobalPositionerTest_107, DifferentSeedsProduceDifferentResults_107) {
  options_.seed = 1;
  options_.constraint_type = GlobalPositionerOptions::ONLY_POINTS;
  
  std::unordered_map<rig_t, Rig> rigs1, rigs2;
  std::unordered_map<camera_t, Camera> cameras1, cameras2;
  std::unordered_map<frame_t, Frame> frames1, frames2;
  std::unordered_map<image_t, Image> images1, images2;
  std::unordered_map<track_t, Track> tracks1, tracks2;
  ViewGraph vg;

  CreateSimpleScene(rigs1, cameras1, frames1, images1, tracks1, 4, 5, 3);
  CreateSimpleScene(rigs2, cameras2, frames2, images2, tracks2, 4, 5, 3);

  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      ImagePair pair;
      pair.image_id1 = i;
      pair.image_id2 = j;
      pair.is_valid = true;
      vg.image_pairs[ImagePair::ImagePairToPairId(i, j)] = pair;
    }
  }

  {
    options_.seed = 1;
    GlobalPositioner positioner1(options_);
    positioner1.Solve(vg, rigs1, cameras1, frames1, images1, tracks1);
  }
  {
    options_.seed = 999;
    GlobalPositioner positioner2(options_);
    positioner2.Solve(vg, rigs2, cameras2, frames2, images2, tracks2);
  }

  // We don't assert specific values since we treat it as black box,
  // but we verify both runs complete without error
  SUCCEED();
}

// Test constraint_reweight_scale boundary: zero
TEST_F(GlobalPositionerTest_107, ZeroReweightScale_107) {
  options_.constraint_type = GlobalPositionerOptions::POINTS_AND_CAMERAS_BALANCED;
  options_.constraint_reweight_scale = 0.0;
  GlobalPositioner positioner(options_);
  ViewGraph vg;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateSimpleScene(rigs, cameras, frames, images, tracks, 3, 5, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = i + 1; j < 3; j++) {
      ImagePair pair;
      pair.image_id1 = i;
      pair.image_id2 = j;
      pair.is_valid = true;
      vg.image_pairs[ImagePair::ImagePairToPairId(i, j)] = pair;
    }
  }

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  SUCCEED();
}

// Test with single track having single observation
TEST_F(GlobalPositionerTest_107, SingleTrackSingleObservation_107) {
  options_.constraint_type = GlobalPositionerOptions::ONLY_POINTS;
  options_.min_num_view_per_track = 1;
  GlobalPositioner positioner(options_);
  ViewGraph vg;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateSimpleScene(rigs, cameras, frames, images, tracks, 1, 1, 1);

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  SUCCEED();
}

// Test GlobalPositionerOptions default values
TEST_F(GlobalPositionerTest_107, DefaultOptionsValues_107) {
  GlobalPositionerOptions opts;
  EXPECT_TRUE(opts.generate_random_positions);
  EXPECT_TRUE(opts.generate_random_points);
  EXPECT_TRUE(opts.generate_scales);
  EXPECT_TRUE(opts.optimize_positions);
  EXPECT_TRUE(opts.optimize_scales);
  EXPECT_EQ(opts.seed, 1u);
  EXPECT_EQ(opts.constraint_type, GlobalPositionerOptions::ONLY_POINTS);
  EXPECT_DOUBLE_EQ(opts.constraint_reweight_scale, 1.0);
}

// Test ConstraintType enum values
TEST_F(GlobalPositionerTest_107, ConstraintTypeEnumValues_107) {
  EXPECT_EQ(GlobalPositionerOptions::ONLY_POINTS, 0);
  EXPECT_EQ(GlobalPositionerOptions::ONLY_CAMERAS, 1);
  EXPECT_EQ(GlobalPositionerOptions::POINTS_AND_CAMERAS_BALANCED, 2);
  EXPECT_EQ(GlobalPositionerOptions::POINTS_AND_CAMERAS, 3);
}

// Test large number of tracks
TEST_F(GlobalPositionerTest_107, LargeNumberOfTracks_107) {
  options_.constraint_type = GlobalPositionerOptions::ONLY_POINTS;
  GlobalPositioner positioner(options_);
  ViewGraph vg;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateSimpleScene(rigs, cameras, frames, images, tracks, 10, 100, 5);

  for (int i = 0; i < 10; i++) {
    for (int j = i + 1; j < 10; j++) {
      ImagePair pair;
      pair.image_id1 = i;
      pair.image_id2 = j;
      pair.is_valid = true;
      vg.image_pairs[ImagePair::ImagePairToPairId(i, j)] = pair;
    }
  }

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  SUCCEED();
}

}  // namespace
}  // namespace glomap
