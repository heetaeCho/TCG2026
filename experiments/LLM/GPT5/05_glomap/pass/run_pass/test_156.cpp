// File: track_filter_triangulation_angle_test_156.cc

#include <gtest/gtest.h>

#include "glomap/processors/track_filter.h"
#include "glomap/scene/image.h"
#include "glomap/scene/track.h"
#include "glomap/scene/view_graph.h"

#include <Eigen/Core>
#include <unordered_map>

namespace glomap {

class TrackFilterTest_156 : public ::testing::Test {
protected:
  ViewGraph view_graph_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;

  void SetUp() override {
    // Common setup if needed.
  }

  // Helper to add an image with a given id to images_.
  // We don't assume anything about Center() implementation; we just ensure
  // that images referenced by observations exist.
  void AddImage(image_t image_id) {
    // Use any available constructor; file name and camera_id are not relevant
    // for this test, we only need the object to exist.
    images_.emplace(image_id, Image(image_id, /*cam_id=*/0, "dummy"));
  }

  // Helper to create a track with a given id and non-zero xyz to avoid
  // degenerate normalized() calls in the implementation.
  Track& AddTrack(track_t track_id) {
    Track track;
    track.track_id = track_id;
    track.xyz = Eigen::Vector3d(1.0, 0.0, 0.0);  // any non-zero direction
    auto [it, inserted] = tracks_.emplace(track_id, track);
    return it->second;
  }
};

// 1) Empty tracks map: should not filter anything and return 0.
TEST_F(TrackFilterTest_156, EmptyTracksReturnZero_156) {
  double min_angle_deg = 10.0;

  int filtered =
      TrackFilter::FilterTrackTriangulationAngle(view_graph_, images_, tracks_,
                                                 min_angle_deg);

  EXPECT_EQ(filtered, 0);
  EXPECT_TRUE(tracks_.empty());
}

// 2) Single track with no observations: cannot triangulate, should be filtered.
//    We expect the counter to increase and observations to remain (trivially) empty.
TEST_F(TrackFilterTest_156, TrackWithNoObservationsIsFiltered_156) {
  AddTrack(/*track_id=*/1);

  double min_angle_deg = 10.0;
  int filtered =
      TrackFilter::FilterTrackTriangulationAngle(view_graph_, images_, tracks_,
                                                 min_angle_deg);

  EXPECT_EQ(filtered, 1);
  ASSERT_EQ(tracks_.size(), 1u);
  EXPECT_TRUE(tracks_.at(1).observations.empty());
}

// 3) Single track with exactly one observation: still cannot form a
//    triangulation angle, so it should be treated as invalid and filtered.
TEST_F(TrackFilterTest_156, SingleObservationTrackIsFiltered_156) {
  auto& track = AddTrack(/*track_id=*/1);

  image_t img_id = 10;
  AddImage(img_id);
  track.observations.emplace_back(img_id, /*feature_id=*/0);

  double min_angle_deg = 10.0;
  int filtered =
      TrackFilter::FilterTrackTriangulationAngle(view_graph_, images_, tracks_,
                                                 min_angle_deg);

  EXPECT_EQ(filtered, 1);
  ASSERT_EQ(tracks_.size(), 1u);
  EXPECT_TRUE(tracks_.at(1).observations.empty());
}

// 4) Track with multiple observations all from the same image:
//    all viewing rays are identical, so the effective triangulation angle
//    between any pair is zero. For any positive min_angle, such a track
//    should be filtered as “too small triangulation angle”.
TEST_F(TrackFilterTest_156, MultipleObservationsSameImageAreFiltered_156) {
  auto& track = AddTrack(/*track_id=*/1);

  image_t img_id = 10;
  AddImage(img_id);

  // Two observations from the same image.
  track.observations.emplace_back(img_id, /*feature_id=*/0);
  track.observations.emplace_back(img_id, /*feature_id=*/1);

  double min_angle_deg = 5.0;  // positive threshold
  int filtered =
      TrackFilter::FilterTrackTriangulationAngle(view_graph_, images_, tracks_,
                                                 min_angle_deg);

  EXPECT_EQ(filtered, 1);
  ASSERT_EQ(tracks_.size(), 1u);
  EXPECT_TRUE(tracks_.at(1).observations.empty());
}

// 5) Multiple tracks: verify that the function counts tracks that are
//    invalid for triangulation (0 or 1 observation, or multiple observations
//    from the same image) and does not erase the track entries themselves.
TEST_F(TrackFilterTest_156, MultipleInvalidTracksAllFiltered_156) {
  // Track 1: no observations
  AddTrack(/*track_id=*/1);

  // Track 2: single observation
  auto& track2 = AddTrack(/*track_id=*/2);
  image_t img2_id = 20;
  AddImage(img2_id);
  track2.observations.emplace_back(img2_id, /*feature_id=*/0);

  // Track 3: two observations from same image
  auto& track3 = AddTrack(/*track_id=*/3);
  image_t img3_id = 30;
  AddImage(img3_id);
  track3.observations.emplace_back(img3_id, /*feature_id=*/0);
  track3.observations.emplace_back(img3_id, /*feature_id=*/1);

  double min_angle_deg = 10.0;
  int filtered =
      TrackFilter::FilterTrackTriangulationAngle(view_graph_, images_, tracks_,
                                                 min_angle_deg);

  EXPECT_EQ(filtered, 3);
  ASSERT_EQ(tracks_.size(), 3u);

  EXPECT_TRUE(tracks_.at(1).observations.empty());
  EXPECT_TRUE(tracks_.at(2).observations.empty());
  EXPECT_TRUE(tracks_.at(3).observations.empty());
}

// 6) Boundary case: min_angle = 0.0. The function should behave
//    deterministically and the return value must be within [0, num_tracks].
//    We do not assume a specific geometric threshold logic here; we only
//    check for a valid count and stable behavior.
TEST_F(TrackFilterTest_156, ZeroMinAngleProducesValidCount_156) {
  auto& track = AddTrack(/*track_id=*/1);

  image_t img_id = 10;
  AddImage(img_id);
  track.observations.emplace_back(img_id, /*feature_id=*/0);

  double min_angle_deg = 0.0;
  int filtered =
      TrackFilter::FilterTrackTriangulationAngle(view_graph_, images_, tracks_,
                                                 min_angle_deg);

  EXPECT_GE(filtered, 0);
  EXPECT_LE(filtered, static_cast<int>(tracks_.size()));
}

}  // namespace glomap
