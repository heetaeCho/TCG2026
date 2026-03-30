// File: global_positioner_test_103.cc

#include <gtest/gtest.h>

#include "glomap/estimators/global_positioning.h"
#include "glomap/scene/view_graph.h"

namespace glomap {

// Test fixture for GlobalPositioner tests (TEST_ID = 103)
class GlobalPositionerTest_103 : public ::testing::Test {
 protected:
  // Helper to construct a GlobalPositioner with a given constraint type.
  GlobalPositioner CreatePositionerWithConstraint(
      GlobalPositionerOptions::ConstraintType constraint_type) {
    GlobalPositionerOptions options;
    options.constraint_type = constraint_type;
    return GlobalPositioner(options);
  }

  // Helper to make a minimal non-empty images map.
  void MakeNonEmptyImages(std::unordered_map<image_t, Image>& images) {
    images.emplace(static_cast<image_t>(1), Image());
  }

  // Helper to make a minimal non-empty tracks map.
  void MakeNonEmptyTracks(std::unordered_map<track_t, Track>& tracks) {
    tracks.emplace(static_cast<track_t>(1), Track());
  }

  // Helper to make a minimal non-empty image_pairs in ViewGraph.
  void MakeNonEmptyImagePairs(ViewGraph& view_graph) {
    // We assume image_pair_t and ImagePair are valid types from the project.
    const image_pair_t kPairId = static_cast<image_pair_t>(1);
    view_graph.image_pairs.emplace(kPairId, ImagePair());
  }
};

// -----------------------------------------------------------------------------
// Guard check 1: images.empty() → should return false.
// -----------------------------------------------------------------------------
TEST_F(GlobalPositionerTest_103, SolveReturnsFalseWhenImagesEmpty_103) {
  // Arrange
  GlobalPositioner positioner =
      CreatePositionerWithConstraint(GlobalPositionerOptions::ONLY_POINTS);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;  // Intentionally left empty
  std::unordered_map<track_t, Track> tracks;

  // Even if these are non-empty, Solve should fail first on images.empty().
  MakeNonEmptyTracks(tracks);

  // Act
  const bool result =
      positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);

  // Assert
  EXPECT_FALSE(result);
}

// -----------------------------------------------------------------------------
// Guard check 2:
//   view_graph.image_pairs.empty() && constraint_type != ONLY_POINTS → false.
// -----------------------------------------------------------------------------
TEST_F(GlobalPositionerTest_103,
       SolveReturnsFalseWhenImagePairsEmptyAndConstraintNotOnlyPoints_103) {
  // Arrange
  // Use ONLY_CAMERAS so that image_pairs being empty triggers early failure.
  GlobalPositioner positioner =
      CreatePositionerWithConstraint(GlobalPositionerOptions::ONLY_CAMERAS);

  ViewGraph view_graph;
  // Leave view_graph.image_pairs empty on purpose.

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // images must be non-empty to pass the first guard.
  MakeNonEmptyImages(images);
  // tracks can be empty here because constraint_type == ONLY_CAMERAS,
  // so the tracks guard will not trigger.
  // (tracks.empty() && constraint_type != ONLY_CAMERAS) == false

  // Act
  const bool result =
      positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);

  // Assert
  EXPECT_FALSE(result);
}

// -----------------------------------------------------------------------------
// Guard check 3:
//   tracks.empty() && constraint_type != ONLY_CAMERAS → false.
// -----------------------------------------------------------------------------
TEST_F(GlobalPositionerTest_103,
       SolveReturnsFalseWhenTracksEmptyAndConstraintNotOnlyCameras_103) {
  // Arrange
  // Use ONLY_POINTS (anything != ONLY_CAMERAS) so that empty tracks trigger
  // the third guard.
  GlobalPositioner positioner =
      CreatePositionerWithConstraint(GlobalPositionerOptions::ONLY_POINTS);

  ViewGraph view_graph;
  MakeNonEmptyImagePairs(view_graph);  // To pass the image_pairs guard.

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;  // Intentionally empty

  // images must be non-empty to pass the first guard.
  MakeNonEmptyImages(images);

  // Act
  const bool result =
      positioner.Solve(view_graph, rigs, cameras, frames, images, tracks);

  // Assert
  EXPECT_FALSE(result);
}

}  // namespace glomap
