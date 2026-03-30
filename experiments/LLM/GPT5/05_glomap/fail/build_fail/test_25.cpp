// File: global_positioner_test.cc

#include <unordered_map>

#include <gtest/gtest.h>

#include "glomap/estimators/global_positioning.h"

namespace glomap {

class GlobalPositionerTest_25 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Assume these aliases/types are provided by the production code.
    rig_t rig_id = static_cast<rig_t>(1);
    camera_t camera_id = static_cast<camera_t>(1);
    frame_t frame_id = static_cast<frame_t>(1);
    image_t image_id = static_cast<image_t>(1);
    track_t track_id = static_cast<track_t>(1);

    // Minimal “valid-looking” data for normal operation.
    rigs_[rig_id] = Rig();
    cameras_[camera_id] = Camera();
    frames_[frame_id] = Frame();
    images_[image_id] = Image();
    tracks_[track_id] = Track();

    // Create at least one image pair in the view graph.
    // The concrete key/value types are defined in the production code;
    // here we assume something default-constructible.
    view_graph_.image_pairs.insert(
        {typename ViewGraph::ImagePair(), typename ViewGraph::ImagePairInfo()});
  }

  // Helper to create a GlobalPositioner with given constraint type.
  GlobalPositioner CreatePositionerWithConstraint(
      GlobalPositionerOptions::ConstraintType constraint_type) {
    GlobalPositionerOptions options;
    options.constraint_type = constraint_type;
    return GlobalPositioner(options);
  }

  ViewGraph view_graph_;
  std::unordered_map<rig_t, Rig> rigs_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<frame_t, Frame> frames_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;
};


// Images empty → Solve should fail early and return false.
TEST_F(GlobalPositionerTest_25, SolveReturnsFalseWhenImagesEmpty_25) {
  GlobalPositioner positioner =
      CreatePositionerWithConstraint(GlobalPositionerOptions::CAMERAS_AND_POINTS);

  images_.clear();  // Trigger: if (images.empty()) ... return false;

  const bool result =
      positioner.Solve(view_graph_, rigs_, cameras_, frames_, images_, tracks_);

  EXPECT_FALSE(result);
}


// image_pairs empty and constraint != ONLY_POINTS → Solve should fail early.
TEST_F(GlobalPositionerTest_25,
       SolveReturnsFalseWhenImagePairsEmptyAndConstraintIsNotOnlyPoints_25) {
  GlobalPositioner positioner =
      CreatePositionerWithConstraint(GlobalPositionerOptions::CAMERAS_AND_POINTS);

  // Keep images and tracks non-empty so only the image_pairs condition matters.
  ASSERT_FALSE(images_.empty());
  ASSERT_FALSE(tracks_.empty());

  view_graph_.image_pairs.clear();  // Trigger the image_pairs guard.

  const bool result =
      positioner.Solve(view_graph_, rigs_, cameras_, frames_, images_, tracks_);

  EXPECT_FALSE(result);
}


// tracks empty and constraint != ONLY_CAMERAS → Solve should fail early.
TEST_F(GlobalPositionerTest_25,
       SolveReturnsFalseWhenTracksEmptyAndConstraintIsNotOnlyCameras_25) {
  GlobalPositioner positioner =
      CreatePositionerWithConstraint(GlobalPositionerOptions::CAMERAS_AND_POINTS);

  // Keep images and image_pairs non-empty so only the tracks condition matters.
  ASSERT_FALSE(images_.empty());
  ASSERT_FALSE(view_graph_.image_pairs.empty());

  tracks_.clear();  // Trigger the tracks guard.

  const bool result =
      positioner.Solve(view_graph_, rigs_, cameras_, frames_, images_, tracks_);

  EXPECT_FALSE(result);
}


// Normal operation: with “valid-looking” data and both constraints enabled,
// Solve should be callable and not throw (we do not assert on the solver result).
TEST_F(GlobalPositionerTest_25, SolveDoesNotThrowOnValidInput_25) {
  GlobalPositioner positioner =
      CreatePositionerWithConstraint(GlobalPositionerOptions::CAMERAS_AND_POINTS);

  ASSERT_FALSE(images_.empty());
  ASSERT_FALSE(view_graph_.image_pairs.empty());
  ASSERT_FALSE(tracks_.empty());

  EXPECT_NO_THROW({
    (void)positioner.Solve(view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  });
}

}  // namespace glomap
