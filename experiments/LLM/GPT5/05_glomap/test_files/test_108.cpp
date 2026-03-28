// File: global_positioner_add_track_to_problem_test_108.cc

#include <unordered_map>
#include <vector>

#include <gtest/gtest.h>

#include "glomap/estimators/global_positioning.h"
#include "glomap/scene/track.h"
#include "glomap/scene/image.h"
#include "glomap/scene/rig.h"
#include "glomap/scene/camera.h"
#include "glomap/scene/frame.h"

namespace glomap {

class GlobalPositionerAddTrackToProblemTest_108 : public ::testing::Test {
protected:
  GlobalPositionerOptions options_;
  GlobalPositioner positioner_;

  GlobalPositionerAddTrackToProblemTest_108()
      : options_(), positioner_(options_) {}

  // Helper aliases for brevity
  using RigMap    = std::unordered_map<rig_t, Rig>;
  using CameraMap = std::unordered_map<camera_t, Camera>;
  using FrameMap  = std::unordered_map<frame_t, Frame>;
  using ImageMap  = std::unordered_map<image_t, Image>;
  using TrackMap  = std::unordered_map<track_t, Track>;
};

// -----------------------------------------------------------------------------
// 1) Normal / boundary-ish case:
//    - track_id is not yet present in the tracks map
//    - The function uses tracks[track_id], which (by interface) inserts
//      a default-constructed Track into the map when missing.
//    We verify that a new entry is created and that no crash occurs.
// -----------------------------------------------------------------------------
TEST_F(GlobalPositionerAddTrackToProblemTest_108,
       MissingTrackIdInsertsDefaultTrack_108) {
  RigMap rigs;
  CameraMap cameras;
  FrameMap frames;
  ImageMap images;
  TrackMap tracks;

  const track_t new_track_id = static_cast<track_t>(1);

  // Pre-condition: no such track yet.
  EXPECT_EQ(tracks.count(new_track_id), 0u);

  // Call the method under test (should not throw/crash).
  positioner_.AddTrackToProblem(new_track_id, rigs, cameras, frames, images,
                                tracks);

  // Post-condition: track with new_track_id should now exist in the map.
  EXPECT_EQ(tracks.count(new_track_id), 1u);

  // The newly created track is default-constructed; we at least verify that
  // observations is a valid vector and currently empty (observable state
  // via public field).
  const Track& created_track = tracks.at(new_track_id);
  EXPECT_TRUE(created_track.observations.empty());
}

// -----------------------------------------------------------------------------
// 2) Existing track with observations whose images are *not* present in
//    the images map:
//    - For each observation, the implementation checks if the image exists
//      in the images map and continues if it doesn't.
//    - This ensures no attempt is made to access missing images,
//      and the call should complete without modifying the images map.
// -----------------------------------------------------------------------------
TEST_F(GlobalPositionerAddTrackToProblemTest_108,
       ObservationsWithMissingImagesAreIgnored_108) {
  RigMap rigs;
  CameraMap cameras;
  FrameMap frames;
  ImageMap images;  // intentionally left empty
  TrackMap tracks;

  const track_t track_id = static_cast<track_t>(2);
  const image_t missing_image_id = static_cast<image_t>(10);
  const feature_t feature_id = static_cast<feature_t>(5);

  Track track;
  track.track_id = track_id;
  // Add an observation that references an image not in the images map.
  track.observations.emplace_back(missing_image_id, feature_id);

  tracks.emplace(track_id, track);

  // Pre-condition: images map is empty and track is present.
  EXPECT_TRUE(images.empty());
  EXPECT_EQ(tracks.count(track_id), 1u);

  // Call the method under test; all observations should be ignored because
  // their image IDs are not present in the images map.
  positioner_.AddTrackToProblem(track_id, rigs, cameras, frames, images,
                                tracks);

  // Post-condition: images map remains unchanged (still empty),
  // and the track with track_id is still present.
  EXPECT_TRUE(images.empty());
  EXPECT_EQ(tracks.count(track_id), 1u);
  // We also expect that the number of observations on the track is unchanged.
  EXPECT_EQ(tracks.at(track_id).observations.size(), 1u);
}

// -----------------------------------------------------------------------------
// 3) Boundary case: track exists but has no observations.
//    - The loop inside AddTrackToProblem should not execute at all.
//    - We verify that no crash occurs and that the container sizes remain
//      unchanged from the caller's perspective.
// -----------------------------------------------------------------------------
TEST_F(GlobalPositionerAddTrackToProblemTest_108,
       TrackWithNoObservationsIsNoOp_108) {
  RigMap rigs;
  CameraMap cameras;
  FrameMap frames;
  ImageMap images;
  TrackMap tracks;

  const track_t track_id = static_cast<track_t>(3);

  Track track;
  track.track_id = track_id;
  // No observations added.
  tracks.emplace(track_id, track);

  const std::size_t initial_track_count  = tracks.size();
  const std::size_t initial_image_count  = images.size();
  const std::size_t initial_rig_count    = rigs.size();
  const std::size_t initial_camera_count = cameras.size();
  const std::size_t initial_frame_count  = frames.size();

  // Call the method; with no observations, it should effectively be a no-op.
  positioner_.AddTrackToProblem(track_id, rigs, cameras, frames, images,
                                tracks);

  // All container sizes should remain the same (observable external state).
  EXPECT_EQ(tracks.size(), initial_track_count);
  EXPECT_EQ(images.size(), initial_image_count);
  EXPECT_EQ(rigs.size(), initial_rig_count);
  EXPECT_EQ(cameras.size(), initial_camera_count);
  EXPECT_EQ(frames.size(), initial_frame_count);

  // Track is still present and has no observations.
  EXPECT_EQ(tracks.count(track_id), 1u);
  EXPECT_TRUE(tracks.at(track_id).observations.empty());
}

}  // namespace glomap
