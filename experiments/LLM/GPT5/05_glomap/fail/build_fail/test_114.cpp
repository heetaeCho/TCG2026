// TEST_ID: 114

#include <gtest/gtest.h>

#include <unordered_map>
#include <vector>
#include <memory>

#include "glomap/controllers/track_establishment.h"
#include "glomap/scene/image.h"
#include "glomap/scene/track.h"

namespace {

using glomap::TrackEngine;
using glomap::TrackEstablishmentOptions;
using glomap::Track;
using glomap::Image;
using glomap::image_t;
using glomap::track_t;
using glomap::feature_t;
using glomap::ViewGraph;

class TrackEngineTest_114 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Reasonable defaults; individual tests may override specific fields.
    options_.min_num_view_per_track = 1;
    options_.min_num_tracks_per_view = 1;
    options_.max_num_view_per_track = 100;
    options_.max_num_tracks = 1000;

    engine_ = std::make_unique<TrackEngine>(view_graph_, images_, options_);
  }

  // Helper: add a registered image to the images_ map.
  void AddRegisteredImage(const image_t image_id) {
    Image image;
    // Image follows the COLMAP API: SetRegistered controls IsRegistered().
    image.SetRegistered(true);
    images_.emplace(image_id, image);
  }

  // Helper: construct a Track with given observations.
  Track MakeTrack(
      const track_t track_id,
      const std::vector<std::pair<image_t, feature_t>>& observations) {
    Track track;
    track.track_id = track_id;
    for (const auto& obs : observations) {
      track.observations.emplace_back(obs.first, obs.second);
    }
    return track;
  }

  ViewGraph view_graph_;
  std::unordered_map<image_t, Image> images_;
  TrackEstablishmentOptions options_;
  std::unique_ptr<TrackEngine> engine_;
};

// Empty input: no full tracks and no selected tracks.
TEST_F(TrackEngineTest_114, EmptyTracksReturnsZero_114) {
  std::unordered_map<track_t, Track> tracks_full;
  std::unordered_map<track_t, Track> tracks_selected;

  const size_t result =
      engine_->FindTracksForProblem(tracks_full, tracks_selected);

  EXPECT_EQ(result, 0u);
  EXPECT_TRUE(tracks_selected.empty());
}

// Tracks whose number of observations is below min_num_view_per_track
// should be ignored.
TEST_F(TrackEngineTest_114, IgnoresTracksBelowMinNumViews_114) {
  options_.min_num_view_per_track = 2;
  options_.max_num_view_per_track = 10;

  AddRegisteredImage(static_cast<image_t>(1));

  std::unordered_map<track_t, Track> tracks_full;
  std::unordered_map<track_t, Track> tracks_selected;

  Track short_track =
      MakeTrack(static_cast<track_t>(1),
                {{static_cast<image_t>(1), static_cast<feature_t>(0)}});  // 1 obs
  tracks_full.emplace(static_cast<track_t>(1), short_track);

  const size_t result =
      engine_->FindTracksForProblem(tracks_full, tracks_selected);

  EXPECT_EQ(result, 0u);
  EXPECT_TRUE(tracks_selected.empty());
}

// Tracks whose number of observations is above max_num_view_per_track
// should be ignored.
TEST_F(TrackEngineTest_114, IgnoresTracksAboveMaxNumViews_114) {
  options_.min_num_view_per_track = 1;
  options_.max_num_view_per_track = 1;  // Only allow tracks with 1 observation.

  AddRegisteredImage(static_cast<image_t>(1));

  std::unordered_map<track_t, Track> tracks_full;
  std::unordered_map<track_t, Track> tracks_selected;

  // 2 observations -> exceeds max_num_view_per_track.
  Track long_track = MakeTrack(
      static_cast<track_t>(1),
      {
          {static_cast<image_t>(1), static_cast<feature_t>(0)},
          {static_cast<image_t>(1), static_cast<feature_t>(1)},
      });
  tracks_full.emplace(static_cast<track_t>(1), long_track);

  const size_t result =
      engine_->FindTracksForProblem(tracks_full, tracks_selected);

  EXPECT_EQ(result, 0u);
  EXPECT_TRUE(tracks_selected.empty());
}

// If min_num_tracks_per_view is negative, the per-view constraint effectively
// prevents any track from being added (since track_per_camera > min always).
TEST_F(TrackEngineTest_114, NegativeMinTracksPerViewPreventsSelection_114) {
  options_.min_num_view_per_track = 1;
  options_.min_num_tracks_per_view = -1;
  options_.max_num_view_per_track = 10;

  AddRegisteredImage(static_cast<image_t>(1));

  std::unordered_map<track_t, Track> tracks_full;
  std::unordered_map<track_t, Track> tracks_selected;

  Track track =
      MakeTrack(static_cast<track_t>(1),
                {{static_cast<image_t>(1), static_cast<feature_t>(0)}});

  tracks_full.emplace(static_cast<track_t>(1), track);

  const size_t result =
      engine_->FindTracksForProblem(tracks_full, tracks_selected);

  EXPECT_EQ(result, 0u);
  EXPECT_TRUE(tracks_selected.empty());
}

// When a single camera accumulates more than min_num_tracks_per_view tracks,
// that camera is considered "satisfied" and no further tracks are needed for it.
// This can cause early termination once all cameras are satisfied.
TEST_F(TrackEngineTest_114,
       StopsWhenAllCamerasSatisfiedByPerViewLimit_114) {
  options_.min_num_view_per_track = 1;
  options_.min_num_tracks_per_view = 1;  // After >1, the camera is "satisfied".
  options_.max_num_view_per_track = 10;
  options_.max_num_tracks = 10;

  const image_t kImageId = static_cast<image_t>(1);
  AddRegisteredImage(kImageId);

  std::unordered_map<track_t, Track> tracks_full;
  std::unordered_map<track_t, Track> tracks_selected;

  // First track has two observations in the same registered image, which is
  // enough to satisfy the camera according to the implementation.
  Track track1 =
      MakeTrack(static_cast<track_t>(1),
                {
                    {kImageId, static_cast<feature_t>(0)},
                    {kImageId, static_cast<feature_t>(1)},
                });

  // Second track is also valid but should not be selected due to early stop.
  Track track2 =
      MakeTrack(static_cast<track_t>(2),
                {
                    {kImageId, static_cast<feature_t>(2)},
                });

  tracks_full.emplace(static_cast<track_t>(1), track1);
  tracks_full.emplace(static_cast<track_t>(2), track2);

  const size_t result =
      engine_->FindTracksForProblem(tracks_full, tracks_selected);

  EXPECT_EQ(result, 1u);
  ASSERT_EQ(tracks_selected.size(), 1u);

  auto it = tracks_selected.find(static_cast<track_t>(1));
  ASSERT_NE(it, tracks_selected.end());
  EXPECT_EQ(it->second.track_id, static_cast<track_t>(1));
  EXPECT_EQ(it->second.observations.size(), track1.observations.size());
}

// The implementation uses `>` comparison for max_num_tracks, so it may accept
// up to max_num_tracks + 1 tracks before stopping.
TEST_F(TrackEngineTest_114, MaxNumTracksHasOffByOneBehavior_114) {
  options_.min_num_view_per_track = 1;
  options_.min_num_tracks_per_view = 10;  // Large enough not to constrain.
  options_.max_num_view_per_track = 10;
  options_.max_num_tracks = 1;  // Intuitively allow 1, but implementation allows 2.

  const image_t kImageId1 = static_cast<image_t>(1);
  const image_t kImageId2 = static_cast<image_t>(2);
  AddRegisteredImage(kImageId1);
  AddRegisteredImage(kImageId2);

  std::unordered_map<track_t, Track> tracks_full;
  std::unordered_map<track_t, Track> tracks_selected;

  Track track1 =
      MakeTrack(static_cast<track_t>(1),
                {
                    {kImageId1, static_cast<feature_t>(0)},
                });

  Track track2 =
      MakeTrack(static_cast<track_t>(2),
                {
                    {kImageId2, static_cast<feature_t>(0)},
                });

  tracks_full.emplace(static_cast<track_t>(1), track1);
  tracks_full.emplace(static_cast<track_t>(2), track2);

  const size_t result =
      engine_->FindTracksForProblem(tracks_full, tracks_selected);

  // Due to `if (tracks.size() > max_num_tracks) break;`
  // both tracks can be accepted before stopping.
  EXPECT_EQ(result, 2u);
  EXPECT_EQ(tracks_selected.size(), 2u);
  EXPECT_NE(tracks_selected.find(static_cast<track_t>(1)),
            tracks_selected.end());
  EXPECT_NE(tracks_selected.find(static_cast<track_t>(2)),
            tracks_selected.end());
}

// Sanity check: returned size matches the size of the selected tracks map and
// selected tracks preserve their observations.
TEST_F(TrackEngineTest_114, ReturnedCountMatchesSelectedTracks_114) {
  options_.min_num_view_per_track = 1;
  options_.min_num_tracks_per_view = 2;
  options_.max_num_view_per_track = 10;
  options_.max_num_tracks = 10;

  const image_t kImageId1 = static_cast<image_t>(1);
  const image_t kImageId2 = static_cast<image_t>(2);
  AddRegisteredImage(kImageId1);
  AddRegisteredImage(kImageId2);

  std::unordered_map<track_t, Track> tracks_full;
  std::unordered_map<track_t, Track> tracks_selected;

  Track track1 =
      MakeTrack(static_cast<track_t>(1),
                {
                    {kImageId1, static_cast<feature_t>(0)},
                    {kImageId2, static_cast<feature_t>(1)},
                });

  Track track2 =
      MakeTrack(static_cast<track_t>(2),
                {
                    {kImageId1, static_cast<feature_t>(2)},
                });

  tracks_full.emplace(static_cast<track_t>(1), track1);
  tracks_full.emplace(static_cast<track_t>(2), track2);

  const size_t result =
      engine_->FindTracksForProblem(tracks_full, tracks_selected);

  EXPECT_EQ(result, tracks_selected.size());

  // At least one of the original tracks must be present, with consistent data.
  auto it = tracks_selected.find(static_cast<track_t>(1));
  if (it != tracks_selected.end()) {
    EXPECT_EQ(it->second.track_id, static_cast<track_t>(1));
    EXPECT_EQ(it->second.observations.size(), track1.observations.size());
  } else {
    it = tracks_selected.find(static_cast<track_t>(2));
    ASSERT_NE(it, tracks_selected.end());
    EXPECT_EQ(it->second.track_id, static_cast<track_t>(2));
    EXPECT_EQ(it->second.observations.size(), track2.observations.size());
  }
}

}  // namespace
