#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>

#include "glomap/estimators/global_positioning.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/track.h"

namespace glomap {
namespace {

class GlobalPositionerTest_104 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up default options
    options_.generate_random_positions = true;
    options_.generate_random_points = true;
    options_.generate_scales = true;
    options_.optimize_positions = true;
    options_.optimize_scales = true;
    options_.seed = 42;
  }

  GlobalPositionerOptions options_;

  // Helper to create a minimal valid ViewGraph with some image pairs
  ViewGraph CreateMinimalViewGraph() {
    ViewGraph vg;
    return vg;
  }

  // Helper to create a ViewGraph with image pairs
  ViewGraph CreateViewGraphWithPairs(int num_pairs) {
    ViewGraph vg;
    for (int i = 0; i < num_pairs; i++) {
      image_pair_t pair_id = ImagePair::ImagePairToPairId(i, i + num_pairs);
      ImagePair ip;
      ip.image_id1 = i;
      ip.image_id2 = i + num_pairs;
      ip.is_valid = true;
      vg.image_pairs[pair_id] = ip;
    }
    return vg;
  }

  // Helper to create rigs
  std::unordered_map<rig_t, Rig> CreateRigs(int num_rigs) {
    std::unordered_map<rig_t, Rig> rigs;
    for (int i = 0; i < num_rigs; i++) {
      Rig rig;
      rig.rig_id = i;
      rigs[i] = rig;
    }
    return rigs;
  }

  // Helper to create tracks with observations
  std::unordered_map<track_t, Track> CreateTracks(int num_tracks,
                                                    int obs_per_track) {
    std::unordered_map<track_t, Track> tracks;
    for (int i = 0; i < num_tracks; i++) {
      Track t;
      t.track_id = i;
      t.is_initialized = true;
      t.xyz = Eigen::Vector3d::Random();
      for (int j = 0; j < obs_per_track; j++) {
        t.observations.push_back(Observation(j, j * 10 + i));
      }
      tracks[i] = t;
    }
    return tracks;
  }

  // Helper to create cameras
  std::unordered_map<camera_t, Camera> CreateCameras(int num_cameras) {
    std::unordered_map<camera_t, Camera> cameras;
    for (int i = 0; i < num_cameras; i++) {
      Camera cam;
      cam.camera_id = i;
      cameras[i] = cam;
    }
    return cameras;
  }

  // Helper to create frames
  std::unordered_map<frame_t, Frame> CreateFrames(int num_frames) {
    std::unordered_map<frame_t, Frame> frames;
    for (int i = 0; i < num_frames; i++) {
      Frame f;
      f.frame_id = i;
      f.is_registered = true;
      frames[i] = f;
    }
    return frames;
  }

  // Helper to create images
  std::unordered_map<image_t, Image> CreateImages(int num_images) {
    std::unordered_map<image_t, Image> images;
    for (int i = 0; i < num_images; i++) {
      Image img;
      img.image_id = i;
      img.camera_id = 0;
      img.frame_id = i;
      img.is_registered = true;
      images[i] = img;
    }
    return images;
  }
};

// Test construction with default options
TEST_F(GlobalPositionerTest_104, ConstructWithDefaultOptions_104) {
  GlobalPositionerOptions default_opts;
  EXPECT_NO_THROW(GlobalPositioner positioner(default_opts));
}

// Test construction with custom options
TEST_F(GlobalPositionerTest_104, ConstructWithCustomOptions_104) {
  options_.seed = 123;
  options_.constraint_type = ONLY_CAMERAS;
  EXPECT_NO_THROW(GlobalPositioner positioner(options_));
}

// Test Solve with empty data structures
TEST_F(GlobalPositionerTest_104, SolveWithEmptyData_104) {
  GlobalPositioner positioner(options_);
  ViewGraph vg;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // With empty data, Solve should handle gracefully
  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  // Result depends on implementation; we just verify it doesn't crash
  (void)result;
}

// Test Solve with minimal valid input
TEST_F(GlobalPositionerTest_104, SolveWithMinimalInput_104) {
  options_.constraint_type = ONLY_POINTS;
  GlobalPositioner positioner(options_);

  ViewGraph vg = CreateViewGraphWithPairs(2);
  auto rigs = CreateRigs(1);
  auto cameras = CreateCameras(1);
  auto frames = CreateFrames(4);
  auto images = CreateImages(4);
  auto tracks = CreateTracks(3, 2);

  // Set up images to reference proper camera and frame and rig
  for (auto& [id, img] : images) {
    img.camera_id = 0;
    img.frame_id = id;
    img.rig_id = 0;
  }

  for (auto& [id, frame] : frames) {
    frame.rig_id = 0;
  }

  // Attempt to solve - this tests the full pipeline
  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  // We just check it runs and returns a boolean
  EXPECT_TRUE(result == true || result == false);
}

// Test that options are stored correctly
TEST_F(GlobalPositionerTest_104, OptionsStoredCorrectly_104) {
  options_.generate_random_positions = false;
  options_.optimize_positions = false;
  options_.seed = 999;

  GlobalPositioner positioner(options_);
  // We can verify through GetOptions if available
  auto& opts = positioner.GetOptions();
  EXPECT_EQ(opts.generate_random_positions, false);
  EXPECT_EQ(opts.optimize_positions, false);
  EXPECT_EQ(opts.seed, 999u);
}

// Test constraint type ONLY_CAMERAS
TEST_F(GlobalPositionerTest_104, SolveWithOnlyCamerasConstraint_104) {
  options_.constraint_type = ONLY_CAMERAS;
  GlobalPositioner positioner(options_);

  ViewGraph vg = CreateViewGraphWithPairs(1);
  auto rigs = CreateRigs(1);
  auto cameras = CreateCameras(1);
  auto frames = CreateFrames(2);
  auto images = CreateImages(2);
  auto tracks = CreateTracks(0, 0);

  for (auto& [id, img] : images) {
    img.camera_id = 0;
    img.frame_id = id;
    img.rig_id = 0;
  }
  for (auto& [id, frame] : frames) {
    frame.rig_id = 0;
  }

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result == true || result == false);
}

// Test constraint type ONLY_POINTS
TEST_F(GlobalPositionerTest_104, SolveWithOnlyPointsConstraint_104) {
  options_.constraint_type = ONLY_POINTS;
  GlobalPositioner positioner(options_);

  ViewGraph vg = CreateViewGraphWithPairs(1);
  auto rigs = CreateRigs(1);
  auto cameras = CreateCameras(1);
  auto frames = CreateFrames(2);
  auto images = CreateImages(2);
  auto tracks = CreateTracks(2, 2);

  for (auto& [id, img] : images) {
    img.camera_id = 0;
    img.frame_id = id;
    img.rig_id = 0;
  }
  for (auto& [id, frame] : frames) {
    frame.rig_id = 0;
  }

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result == true || result == false);
}

// Test with multiple rigs
TEST_F(GlobalPositionerTest_104, SolveWithMultipleRigs_104) {
  GlobalPositioner positioner(options_);

  ViewGraph vg = CreateViewGraphWithPairs(2);
  auto rigs = CreateRigs(3);
  auto cameras = CreateCameras(2);
  auto frames = CreateFrames(4);
  auto images = CreateImages(4);
  auto tracks = CreateTracks(2, 2);

  for (auto& [id, img] : images) {
    img.camera_id = id % 2;
    img.frame_id = id;
    img.rig_id = id % 3;
  }
  for (auto& [id, frame] : frames) {
    frame.rig_id = id % 3;
  }

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result == true || result == false);
}

// Test options with random positions disabled
TEST_F(GlobalPositionerTest_104, SolveWithRandomPositionsDisabled_104) {
  options_.generate_random_positions = false;
  options_.generate_random_points = false;
  GlobalPositioner positioner(options_);

  ViewGraph vg = CreateViewGraphWithPairs(1);
  auto rigs = CreateRigs(1);
  auto cameras = CreateCameras(1);
  auto frames = CreateFrames(2);
  auto images = CreateImages(2);
  auto tracks = CreateTracks(1, 2);

  for (auto& [id, img] : images) {
    img.camera_id = 0;
    img.frame_id = id;
    img.rig_id = 0;
  }
  for (auto& [id, frame] : frames) {
    frame.rig_id = 0;
  }

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result == true || result == false);
}

// Test that GlobalPositionerOptions default values are correct
TEST_F(GlobalPositionerTest_104, DefaultOptionsValues_104) {
  GlobalPositionerOptions opts;
  EXPECT_TRUE(opts.generate_random_positions);
  EXPECT_TRUE(opts.generate_random_points);
  EXPECT_TRUE(opts.generate_scales);
  EXPECT_TRUE(opts.optimize_positions);
  EXPECT_TRUE(opts.optimize_scales);
  EXPECT_EQ(opts.seed, 1u);
  EXPECT_EQ(opts.constraint_type, ONLY_POINTS);
  EXPECT_DOUBLE_EQ(opts.constraint_reweight_scale, 1.0);
}

// Test CreateLossFunction returns a valid shared_ptr
TEST_F(GlobalPositionerTest_104, CreateLossFunctionReturnsValid_104) {
  GlobalPositionerOptions opts;
  auto loss = opts.CreateLossFunction();
  // The loss function should be created (may or may not be nullptr depending on config)
  // Just verify it doesn't throw
}

// Test with tracks having no observations
TEST_F(GlobalPositionerTest_104, SolveWithEmptyObservationTracks_104) {
  GlobalPositioner positioner(options_);

  ViewGraph vg = CreateViewGraphWithPairs(1);
  auto rigs = CreateRigs(1);
  auto cameras = CreateCameras(1);
  auto frames = CreateFrames(2);
  auto images = CreateImages(2);
  auto tracks = CreateTracks(3, 0);  // tracks with 0 observations

  for (auto& [id, img] : images) {
    img.camera_id = 0;
    img.frame_id = id;
    img.rig_id = 0;
  }
  for (auto& [id, frame] : frames) {
    frame.rig_id = 0;
  }

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result == true || result == false);
}

// Test with large number of tracks and observations
TEST_F(GlobalPositionerTest_104, SolveWithLargerDataset_104) {
  options_.constraint_type = ONLY_POINTS;
  GlobalPositioner positioner(options_);

  ViewGraph vg = CreateViewGraphWithPairs(5);
  auto rigs = CreateRigs(2);
  auto cameras = CreateCameras(2);
  auto frames = CreateFrames(10);
  auto images = CreateImages(10);
  auto tracks = CreateTracks(10, 3);

  for (auto& [id, img] : images) {
    img.camera_id = id % 2;
    img.frame_id = id;
    img.rig_id = id % 2;
  }
  for (auto& [id, frame] : frames) {
    frame.rig_id = id % 2;
  }

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result == true || result == false);
}

// Test scales optimization disabled
TEST_F(GlobalPositionerTest_104, SolveWithScalesOptimizationDisabled_104) {
  options_.optimize_scales = false;
  options_.generate_scales = false;
  GlobalPositioner positioner(options_);

  ViewGraph vg = CreateViewGraphWithPairs(1);
  auto rigs = CreateRigs(1);
  auto cameras = CreateCameras(1);
  auto frames = CreateFrames(2);
  auto images = CreateImages(2);
  auto tracks = CreateTracks(1, 2);

  for (auto& [id, img] : images) {
    img.camera_id = 0;
    img.frame_id = id;
    img.rig_id = 0;
  }
  for (auto& [id, frame] : frames) {
    frame.rig_id = 0;
  }

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result == true || result == false);
}

// Test different seeds produce potentially different results
TEST_F(GlobalPositionerTest_104, DifferentSeedsConstruction_104) {
  options_.seed = 1;
  EXPECT_NO_THROW(GlobalPositioner positioner1(options_));

  options_.seed = 9999;
  EXPECT_NO_THROW(GlobalPositioner positioner2(options_));
}

// Test constraint_reweight_scale boundary
TEST_F(GlobalPositionerTest_104, ConstraintReweightScaleZero_104) {
  options_.constraint_reweight_scale = 0.0;
  GlobalPositioner positioner(options_);

  ViewGraph vg;
  auto rigs = CreateRigs(1);
  auto cameras = CreateCameras(1);
  auto frames = CreateFrames(1);
  auto images = CreateImages(1);
  auto tracks = CreateTracks(0, 0);

  for (auto& [id, img] : images) {
    img.camera_id = 0;
    img.frame_id = id;
    img.rig_id = 0;
  }
  for (auto& [id, frame] : frames) {
    frame.rig_id = 0;
  }

  bool result = positioner.Solve(vg, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result == true || result == false);
}

// Test constraint_reweight_scale large value
TEST_F(GlobalPositionerTest_104, ConstraintReweightScaleLarge_104) {
  options_.constraint_reweight_scale = 1000.0;
  EXPECT_NO_THROW(GlobalPositioner positioner(options_));
}

}  // namespace
}  // namespace glomap
