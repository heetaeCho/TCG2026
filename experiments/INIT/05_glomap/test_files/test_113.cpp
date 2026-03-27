// File: track_engine_establish_full_tracks_test_113.cc

#include <gtest/gtest.h>
#include <unordered_map>

#include "glomap/controllers/track_establishment.h"

using namespace glomap;  // Rely on actual project definitions for types

// Test fixture for TrackEngine-related tests (TEST_ID = 113)
class TrackEngineTest_113 : public ::testing::Test {
 protected:
  TrackEngineTest_113()
      : engine_(view_graph_, images_, options_) {}

  ViewGraph view_graph_;
  std::unordered_map<image_t, Image> images_;
  TrackEstablishmentOptions options_;
  TrackEngine engine_;
};

// 1) Basic behavior: return value must match resulting tracks.size().
TEST_F(TrackEngineTest_113,
       EstablishFullTracks_ReturnsResultingNumberOfTracks_113) {
  std::unordered_map<track_t, Track> tracks;

  const size_t result = engine_.EstablishFullTracks(tracks);

  EXPECT_EQ(result, tracks.size())
      << "EstablishFullTracks should return the final number of tracks.";
}

// 2) Non-empty input: method should still return tracks.size() after it
// performs its internal logic (input content should not break behavior).
TEST_F(TrackEngineTest_113,
       EstablishFullTracks_HandlesNonEmptyInputTracksAndReturnsSize_113) {
  std::unordered_map<track_t, Track> tracks;

  // Pre-populate with a dummy track (actual content is treated as opaque).
  tracks.emplace(static_cast<track_t>(1), Track{});
  const size_t initial_size = tracks.size();
  ASSERT_GT(initial_size, 0u);

  const size_t result = engine_.EstablishFullTracks(tracks);

  // Contract we can observe: return value equals resulting size.
  EXPECT_EQ(result, tracks.size());
}

// 3) Multiple calls: calling EstablishFullTracks repeatedly should be
// stable in the sense that it always returns tracks.size() and does not
// depend on previous contents of 'tracks'.
TEST_F(TrackEngineTest_113,
       EstablishFullTracks_MultipleInvocationsRemainConsistent_113) {
  std::unordered_map<track_t, Track> tracks;

  const size_t first_result = engine_.EstablishFullTracks(tracks);
  const size_t first_size = tracks.size();

  const size_t second_result = engine_.EstablishFullTracks(tracks);
  const size_t second_size = tracks.size();

  // Each call independently must satisfy the observable contract.
  EXPECT_EQ(first_result, first_size);
  EXPECT_EQ(second_result, second_size);
}
