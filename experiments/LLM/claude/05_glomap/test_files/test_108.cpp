#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/global_positioning.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/scene/image.h"
#include "glomap/scene/track.h"
#include "glomap/scene/camera.h"
#include "glomap/scene/rigid3d.h"
#include "glomap/types.h"

#include <unordered_map>
#include <Eigen/Core>

namespace glomap {
namespace {

class GlobalPositionerTest_108 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up default options
    options_.generate_random_positions = true;
    options_.generate_random_points = true;
    options_.generate_scales = true;
    options_.optimize_positions = true;
    options_.optimize_scales = true;
    options_.seed = 42;
    options_.constraint_type = ONLY_POINTS;
  }

  GlobalPositionerOptions options_;

  // Helper to create a minimal scene with a view graph, images, cameras, etc.
  void CreateMinimalScene(
      ViewGraph& view_graph,
      std::unordered_map<rig_t, Rig>& rigs,
      std::unordered_map<camera_t, Camera>& cameras,
      std::unordered_map<frame_t, Frame>& frames,
      std::unordered_map<image_t, Image>& images,
      std::unordered_map<track_t, Track>& tracks,
      int num_images = 3,
      int num_tracks = 2) {
    // Create cameras
    camera_t cam_id = 0;
    Camera cam;
    cam.camera_id = cam_id;
    cam.model_id = 0;  // SIMPLE_PINHOLE or similar
    cam.width = 640;
    cam.height = 480;
    cam.params = {500.0, 320.0, 240.0};  // fx, cx, cy
    cam.has_prior_focal_length = true;
    cameras[cam_id] = cam;

    // Create a rig
    rig_t rig_id = 0;
    rigs[rig_id] = Rig();

    // Create frames and images
    for (int i = 0; i < num_images; i++) {
      image_t img_id = static_cast<image_t>(i);
      frame_t frm_id = static_cast<frame_t>(i);

      Frame frame;
      frame.frame_id = frm_id;
      frame.rig_id = rig_id;
      frame.is_registered = true;
      // Set identity rotation and some translation
      frame.RigFromWorld().rotation = Eigen::Quaterniond::Identity();
      frame.RigFromWorld().translation = Eigen::Vector3d(i * 1.0, 0, 0);
      frames[frm_id] = frame;

      Image img(img_id, cam_id, "image_" + std::to_string(i) + ".jpg");
      img.frame_id = frm_id;
      img.frame_ptr = &frames[frm_id];
      img.is_registered = true;

      // Add some features
      for (int t = 0; t < num_tracks; t++) {
        img.features.push_back(Eigen::Vector2d(100.0 + t * 50.0, 200.0));
        img.features_undist.push_back(
            Eigen::Vector3d(0.1 + t * 0.05, 0.2, 1.0).normalized());
      }
      images[img_id] = img;
    }

    // Fix frame pointers after map insertion
    for (auto& [img_id, img] : images) {
      img.frame_ptr = &frames[img.frame_id];
    }

    // Create tracks with observations
    for (int t = 0; t < num_tracks; t++) {
      track_t trk_id = static_cast<track_t>(t);
      Track track;
      track.track_id = trk_id;
      track.xyz = Eigen::Vector3d(t * 2.0, 1.0, 5.0);
      track.is_initialized = true;

      for (int i = 0; i < num_images; i++) {
        track.observations.push_back(
            std::make_pair(static_cast<image_t>(i), static_cast<feature_t>(t)));
      }
      tracks[trk_id] = track;
    }

    // Create view graph edges
    for (int i = 0; i < num_images; i++) {
      for (int j = i + 1; j < num_images; j++) {
        image_t id1 = static_cast<image_t>(i);
        image_t id2 = static_cast<image_t>(j);
        ImagePair pair;
        pair.image_id1 = id1;
        pair.image_id2 = id2;
        pair.is_valid = true;
        pair.is_initialized = true;
        pair.cam2_from_cam1.rotation = Eigen::Quaterniond::Identity();
        pair.cam2_from_cam1.translation =
            Eigen::Vector3d(1.0, 0.0, 0.0).normalized();
        view_graph.image_pairs[std::make_pair(id1, id2)] = pair;
      }
    }
  }
};

// Test: Constructor with default options
TEST_F(GlobalPositionerTest_108, ConstructorDefault_108) {
  GlobalPositionerOptions default_options;
  EXPECT_NO_THROW(GlobalPositioner positioner(default_options));
}

// Test: Constructor with custom options
TEST_F(GlobalPositionerTest_108, ConstructorCustomOptions_108) {
  options_.generate_random_positions = false;
  options_.generate_random_points = false;
  options_.seed = 123;
  EXPECT_NO_THROW(GlobalPositioner positioner(options_));
}

// Test: GetOptions returns the options passed to constructor
TEST_F(GlobalPositionerTest_108, GetOptionsReturnsCorrectOptions_108) {
  options_.seed = 999;
  options_.generate_scales = false;
  GlobalPositioner positioner(options_);
  auto& returned_options = positioner.GetOptions();
  EXPECT_EQ(returned_options.seed, 999u);
  EXPECT_FALSE(returned_options.generate_scales);
}

// Test: Solve with a minimal valid scene should return true
TEST_F(GlobalPositionerTest_108, SolveMinimalScene_108) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateMinimalScene(view_graph, rigs, cameras, frames, images, tracks, 3, 2);

  GlobalPositioner positioner(options_);
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  // With a proper minimal scene, Solve should succeed
  EXPECT_TRUE(result);
}

// Test: Solve with empty inputs
TEST_F(GlobalPositionerTest_108, SolveEmptyInputs_108) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  GlobalPositioner positioner(options_);
  // Empty scene - solver behavior depends on implementation
  // It should not crash at minimum
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  // With no data, the solver may return true or false, but should not crash
  (void)result;
}

// Test: Solve with ONLY_CAMERAS constraint type
TEST_F(GlobalPositionerTest_108, SolveOnlyCamerasConstraint_108) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateMinimalScene(view_graph, rigs, cameras, frames, images, tracks, 4, 3);

  options_.constraint_type = ONLY_CAMERAS;
  GlobalPositioner positioner(options_);
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result);
}

// Test: Solve with generate_scales = false
TEST_F(GlobalPositionerTest_108, SolveWithoutGeneratingScales_108) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateMinimalScene(view_graph, rigs, cameras, frames, images, tracks, 3, 2);

  options_.generate_scales = false;
  GlobalPositioner positioner(options_);
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result);
}

// Test: Solve with generate_random_positions = false
TEST_F(GlobalPositionerTest_108, SolveWithoutRandomPositions_108) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateMinimalScene(view_graph, rigs, cameras, frames, images, tracks, 3, 2);

  options_.generate_random_positions = false;
  GlobalPositioner positioner(options_);
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result);
}

// Test: Solve with no tracks (only camera-to-camera constraints)
TEST_F(GlobalPositionerTest_108, SolveNoTracks_108) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateMinimalScene(view_graph, rigs, cameras, frames, images, tracks, 3, 0);

  options_.constraint_type = ONLY_CAMERAS;
  GlobalPositioner positioner(options_);
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  // Should still work with only camera constraints
  (void)result;
}

// Test: Solve modifies frame translations (positions should change from random init)
TEST_F(GlobalPositionerTest_108, SolveModifiesFrameTranslations_108) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateMinimalScene(view_graph, rigs, cameras, frames, images, tracks, 4, 5);

  // Record initial translations
  std::unordered_map<frame_t, Eigen::Vector3d> initial_translations;
  for (const auto& [fid, frame] : frames) {
    initial_translations[fid] = frame.RigFromWorld().translation;
  }

  GlobalPositioner positioner(options_);
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);

  if (result) {
    // After solving, at least some frame translations should have changed
    // (due to random initialization and optimization)
    bool any_changed = false;
    for (const auto& [fid, frame] : frames) {
      if ((frame.RigFromWorld().translation - initial_translations[fid]).norm() > 1e-10) {
        any_changed = true;
        break;
      }
    }
    // With random init, positions should change
    EXPECT_TRUE(any_changed);
  }
}

// Test: Solve with unregistered images - they should be skipped
TEST_F(GlobalPositionerTest_108, SolveWithUnregisteredImages_108) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateMinimalScene(view_graph, rigs, cameras, frames, images, tracks, 3, 2);

  // Mark one image as unregistered
  images[1].is_registered = false;

  GlobalPositioner positioner(options_);
  // Should not crash; unregistered images are skipped
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  (void)result;
}

// Test: Solve with uncalibrated camera (has_prior_focal_length = false)
TEST_F(GlobalPositionerTest_108, SolveWithUncalibratedCamera_108) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateMinimalScene(view_graph, rigs, cameras, frames, images, tracks, 3, 2);

  // Set camera as uncalibrated
  cameras[0].has_prior_focal_length = false;

  GlobalPositioner positioner(options_);
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result);
}

// Test: Solve with larger scene
TEST_F(GlobalPositionerTest_108, SolveLargerScene_108) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateMinimalScene(view_graph, rigs, cameras, frames, images, tracks, 10, 20);

  GlobalPositioner positioner(options_);
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result);
}

// Test: Solve determinism with same seed
TEST_F(GlobalPositionerTest_108, SolveDeterministicWithSameSeed_108) {
  auto run_solve = [this](unsigned int seed) {
    ViewGraph view_graph;
    std::unordered_map<rig_t, Rig> rigs;
    std::unordered_map<camera_t, Camera> cameras;
    std::unordered_map<frame_t, Frame> frames;
    std::unordered_map<image_t, Image> images;
    std::unordered_map<track_t, Track> tracks;

    CreateMinimalScene(view_graph, rigs, cameras, frames, images, tracks, 4, 3);

    GlobalPositionerOptions opts = options_;
    opts.seed = seed;
    GlobalPositioner positioner(opts);
    positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);

    std::unordered_map<frame_t, Eigen::Vector3d> results;
    for (const auto& [fid, frame] : frames) {
      results[fid] = frame.RigFromWorld().translation;
    }
    return results;
  };

  auto results1 = run_solve(42);
  auto results2 = run_solve(42);

  for (const auto& [fid, trans] : results1) {
    EXPECT_TRUE(results2.count(fid) > 0);
    if (results2.count(fid) > 0) {
      EXPECT_NEAR((trans - results2[fid]).norm(), 0.0, 1e-10)
          << "Frame " << fid << " differs between two runs with same seed";
    }
  }
}

// Test: Solve with tracks that have no observations
TEST_F(GlobalPositionerTest_108, SolveTracksWithNoObservations_108) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateMinimalScene(view_graph, rigs, cameras, frames, images, tracks, 3, 2);

  // Add a track with no observations
  Track empty_track;
  empty_track.track_id = 100;
  empty_track.xyz = Eigen::Vector3d(0, 0, 0);
  empty_track.is_initialized = true;
  tracks[100] = empty_track;

  GlobalPositioner positioner(options_);
  // Should handle empty observation tracks gracefully
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  (void)result;
}

// Test: Options modification through GetOptions
TEST_F(GlobalPositionerTest_108, ModifyOptionsViaGetOptions_108) {
  GlobalPositioner positioner(options_);
  auto& opts = positioner.GetOptions();
  opts.seed = 12345;
  opts.generate_random_positions = false;

  EXPECT_EQ(positioner.GetOptions().seed, 12345u);
  EXPECT_FALSE(positioner.GetOptions().generate_random_positions);
}

// Test: Constraint type CAMERAS_AND_POINTS
TEST_F(GlobalPositionerTest_108, SolveCamerasAndPointsConstraint_108) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateMinimalScene(view_graph, rigs, cameras, frames, images, tracks, 4, 3);

  options_.constraint_type = CAMERAS_AND_POINTS;
  GlobalPositioner positioner(options_);
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result);
}

// Test: Solve with single image (boundary - minimum case)
TEST_F(GlobalPositionerTest_108, SolveSingleImage_108) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateMinimalScene(view_graph, rigs, cameras, frames, images, tracks, 1, 1);

  GlobalPositioner positioner(options_);
  // Single image may or may not succeed, but should not crash
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  (void)result;
}

// Test: Default options values
TEST_F(GlobalPositionerTest_108, DefaultOptionsValues_108) {
  GlobalPositionerOptions default_opts;
  EXPECT_TRUE(default_opts.generate_random_positions);
  EXPECT_TRUE(default_opts.generate_random_points);
  EXPECT_TRUE(default_opts.generate_scales);
  EXPECT_TRUE(default_opts.optimize_positions);
  EXPECT_TRUE(default_opts.optimize_scales);
  EXPECT_EQ(default_opts.seed, 1u);
  EXPECT_EQ(default_opts.constraint_type, ONLY_POINTS);
  EXPECT_DOUBLE_EQ(default_opts.constraint_reweight_scale, 1.0);
}

// Test: Solve with uninitialized tracks
TEST_F(GlobalPositionerTest_108, SolveWithUninitializedTracks_108) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateMinimalScene(view_graph, rigs, cameras, frames, images, tracks, 3, 2);

  // Mark tracks as uninitialized
  for (auto& [tid, track] : tracks) {
    track.is_initialized = false;
  }

  GlobalPositioner positioner(options_);
  bool result = positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);
  (void)result;
}

}  // namespace
}  // namespace glomap
