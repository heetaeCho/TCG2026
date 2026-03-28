#include <gtest/gtest.h>
#include "glomap/estimators/global_positioning.h"
#include "glomap/scene/view_graph.h"
#include "glomap/types.h"

namespace glomap {
namespace {

class GlobalPositionerTest_103 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up default options
    options_.constraint_type = GlobalPositionerOptions::ONLY_POINTS;
    options_.generate_random_positions = true;
    options_.generate_random_points = true;
    options_.seed = 1;
  }

  // Helper to create a minimal valid setup with images, frames, cameras, rigs, and tracks
  void CreateMinimalSetup() {
    // Create one rig
    rigs_[0] = Rig();

    // Create one camera
    cameras_[0] = Camera();
    cameras_[0].model_id = 0;  // Simple pinhole
    cameras_[0].width = 640;
    cameras_[0].height = 480;
    cameras_[0].params = {500.0, 320.0, 240.0};

    // Create two images
    images_[0] = Image();
    images_[0].camera_id = 0;
    images_[0].frame_id = 0;
    images_[0].rig_id = 0;
    images_[0].is_registered = true;

    images_[1] = Image();
    images_[1].camera_id = 0;
    images_[1].frame_id = 1;
    images_[1].rig_id = 0;
    images_[1].is_registered = true;

    // Create two frames
    frames_[0] = Frame();
    frames_[0].rig_id = 0;
    frames_[0].is_registered = true;

    frames_[1] = Frame();
    frames_[1].rig_id = 0;
    frames_[1].is_registered = true;

    // Create a track observed by both images
    tracks_[0] = Track();
    tracks_[0].is_established = true;
    tracks_[0].observations.push_back(Observation(0, 0));
    tracks_[0].observations.push_back(Observation(1, 0));
  }

  void AddImagePair() {
    image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
    view_graph_.image_pairs[pair_id] = ImagePair();
    view_graph_.image_pairs[pair_id].image_id1 = 0;
    view_graph_.image_pairs[pair_id].image_id2 = 1;
    view_graph_.image_pairs[pair_id].is_valid = true;
    // Set a relative pose
    view_graph_.image_pairs[pair_id].cam2_from_cam1 = Rigid3d();
  }

  GlobalPositionerOptions options_;
  ViewGraph view_graph_;
  std::unordered_map<rig_t, Rig> rigs_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<frame_t, Frame> frames_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;
};

// Test that Solve returns false when images map is empty
TEST_F(GlobalPositionerTest_103, SolveFailsWithEmptyImages_103) {
  GlobalPositioner positioner(options_);

  // images_ is empty, should return false
  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_,
                                  images_, tracks_);
  EXPECT_FALSE(result);
}

// Test that Solve returns false when image_pairs is empty and constraint_type is not ONLY_POINTS
TEST_F(GlobalPositionerTest_103, SolveFailsWithEmptyImagePairsAndCameraConstraint_103) {
  options_.constraint_type = GlobalPositionerOptions::ONLY_CAMERAS;
  GlobalPositioner positioner(options_);

  // Add an image so we pass the first check
  images_[0] = Image();
  images_[0].camera_id = 0;
  images_[0].is_registered = true;

  // view_graph_ has no image_pairs, constraint_type is ONLY_CAMERAS
  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_,
                                  images_, tracks_);
  EXPECT_FALSE(result);
}

// Test that Solve returns false when tracks is empty and constraint_type is not ONLY_CAMERAS
TEST_F(GlobalPositionerTest_103, SolveFailsWithEmptyTracksAndPointConstraint_103) {
  options_.constraint_type = GlobalPositionerOptions::ONLY_POINTS;
  GlobalPositioner positioner(options_);

  // Add an image so we pass the first check
  images_[0] = Image();
  images_[0].camera_id = 0;
  images_[0].is_registered = true;

  // tracks_ is empty, constraint_type is ONLY_POINTS (not ONLY_CAMERAS)
  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_,
                                  images_, tracks_);
  EXPECT_FALSE(result);
}

// Test that Solve returns false when tracks is empty and constraint_type is POINTS_AND_CAMERAS
TEST_F(GlobalPositionerTest_103, SolveFailsWithEmptyTracksAndPointsAndCamerasConstraint_103) {
  options_.constraint_type = GlobalPositionerOptions::POINTS_AND_CAMERAS;
  GlobalPositioner positioner(options_);

  images_[0] = Image();
  images_[0].camera_id = 0;
  images_[0].is_registered = true;

  AddImagePair();

  // tracks_ is empty
  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_,
                                  images_, tracks_);
  EXPECT_FALSE(result);
}

// Test that Solve does not fail due to empty image_pairs when constraint_type is ONLY_POINTS
TEST_F(GlobalPositionerTest_103, SolveDoesNotRequireImagePairsForOnlyPoints_103) {
  options_.constraint_type = GlobalPositionerOptions::ONLY_POINTS;
  GlobalPositioner positioner(options_);

  CreateMinimalSetup();

  // No image pairs needed for ONLY_POINTS
  // This should not fail due to empty image_pairs check
  // It may or may not succeed depending on the solver, but should not return false
  // due to the image_pairs check
  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_,
                                  images_, tracks_);
  // We just verify it doesn't crash; the result depends on solver convergence
  // The key is that it passed the precondition checks
  (void)result;
}

// Test that Solve does not fail due to empty tracks when constraint_type is ONLY_CAMERAS
TEST_F(GlobalPositionerTest_103, SolveDoesNotRequireTracksForOnlyCameras_103) {
  options_.constraint_type = GlobalPositionerOptions::ONLY_CAMERAS;
  GlobalPositioner positioner(options_);

  CreateMinimalSetup();
  AddImagePair();
  tracks_.clear();  // No tracks needed for ONLY_CAMERAS

  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_,
                                  images_, tracks_);
  // Just verify no crash from precondition checks
  (void)result;
}

// Test with a minimal valid configuration using ONLY_POINTS
TEST_F(GlobalPositionerTest_103, SolveMinimalValidOnlyPoints_103) {
  options_.constraint_type = GlobalPositionerOptions::ONLY_POINTS;
  GlobalPositioner positioner(options_);

  CreateMinimalSetup();

  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_,
                                  images_, tracks_);
  // The solver should at least run without crashing
  // Result depends on problem structure being solvable
  (void)result;
}

// Test with POINTS_AND_CAMERAS constraint type
TEST_F(GlobalPositionerTest_103, SolveMinimalValidPointsAndCameras_103) {
  options_.constraint_type = GlobalPositionerOptions::POINTS_AND_CAMERAS;
  GlobalPositioner positioner(options_);

  CreateMinimalSetup();
  AddImagePair();

  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_,
                                  images_, tracks_);
  (void)result;
}

// Test with POINTS_AND_CAMERAS_BALANCED constraint type
TEST_F(GlobalPositionerTest_103, SolveMinimalValidPointsAndCamerasBalanced_103) {
  options_.constraint_type = GlobalPositionerOptions::POINTS_AND_CAMERAS_BALANCED;
  GlobalPositioner positioner(options_);

  CreateMinimalSetup();
  AddImagePair();

  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_,
                                  images_, tracks_);
  (void)result;
}

// Test that empty images returns false regardless of constraint type
TEST_F(GlobalPositionerTest_103, SolveFailsWithEmptyImagesOnlyCameras_103) {
  options_.constraint_type = GlobalPositionerOptions::ONLY_CAMERAS;
  GlobalPositioner positioner(options_);

  // images_ is empty
  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_,
                                  images_, tracks_);
  EXPECT_FALSE(result);
}

TEST_F(GlobalPositionerTest_103, SolveFailsWithEmptyImagesPointsAndCameras_103) {
  options_.constraint_type = GlobalPositionerOptions::POINTS_AND_CAMERAS;
  GlobalPositioner positioner(options_);

  // images_ is empty
  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_,
                                  images_, tracks_);
  EXPECT_FALSE(result);
}

TEST_F(GlobalPositionerTest_103, SolveFailsWithEmptyImagesBalanced_103) {
  options_.constraint_type = GlobalPositionerOptions::POINTS_AND_CAMERAS_BALANCED;
  GlobalPositioner positioner(options_);

  // images_ is empty
  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_,
                                  images_, tracks_);
  EXPECT_FALSE(result);
}

// Test construction with default options
TEST_F(GlobalPositionerTest_103, ConstructionWithDefaultOptions_103) {
  GlobalPositionerOptions default_options;
  GlobalPositioner positioner(default_options);
  // Should construct without issues
  SUCCEED();
}

// Test that empty image pairs fail for ONLY_CAMERAS constraint
TEST_F(GlobalPositionerTest_103, EmptyImagePairsFailForOnlyCamerasConstraint_103) {
  options_.constraint_type = GlobalPositionerOptions::ONLY_CAMERAS;
  GlobalPositioner positioner(options_);

  CreateMinimalSetup();
  // view_graph_ has no image_pairs

  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_,
                                  images_, tracks_);
  EXPECT_FALSE(result);
}

// Test that empty image pairs fail for POINTS_AND_CAMERAS constraint
TEST_F(GlobalPositionerTest_103, EmptyImagePairsFailForPointsAndCamerasConstraint_103) {
  options_.constraint_type = GlobalPositionerOptions::POINTS_AND_CAMERAS;
  GlobalPositioner positioner(options_);

  CreateMinimalSetup();
  // view_graph_ has no image_pairs

  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_,
                                  images_, tracks_);
  EXPECT_FALSE(result);
}

// Test that empty image pairs fail for POINTS_AND_CAMERAS_BALANCED constraint
TEST_F(GlobalPositionerTest_103, EmptyImagePairsFailForBalancedConstraint_103) {
  options_.constraint_type = GlobalPositionerOptions::POINTS_AND_CAMERAS_BALANCED;
  GlobalPositioner positioner(options_);

  CreateMinimalSetup();
  // view_graph_ has no image_pairs

  bool result = positioner.Solve(view_graph_, rigs_, cameras_, frames_,
                                  images_, tracks_);
  EXPECT_FALSE(result);
}

}  // namespace
}  // namespace glomap
