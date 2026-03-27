// File: track_establishment_test_54.cc

#include <gtest/gtest.h>
#include <unordered_map>

#include "glomap/controllers/track_establishment.h"

namespace {

using glomap::TrackEngine;
using glomap::Track;
using glomap::track_t;

// Helper to build a simple map of tracks with default-constructed Track objects.
std::unordered_map<track_t, Track> CreateTracksMap_54(
    const std::vector<track_t>& ids) {
  std::unordered_map<track_t, Track> tracks;
  for (const auto id : ids) {
    Track t;              // Rely only on default construction; no internal logic.
    tracks.emplace(id, t);
  }
  return tracks;
}

// TEST_ID = 54

// 1) Empty input: should return 0 and clear any pre-existing contents
//    in the output map, regardless of internal options/images.
TEST(TrackEngineTest_54, EmptyInputClearsOutputAndReturnsZero_54) {
  TrackEngine engine;

  // tracks_full is empty
  std::unordered_map<track_t, Track> tracks_full;

  // Pre-populate tracks_selected to verify it gets overwritten/cleared
  std::unordered_map<track_t, Track> tracks_selected =
      CreateTracksMap_54({static_cast<track_t>(1), static_cast<track_t>(2)});

  const size_t num_selected =
      engine.FindTracksForProblem(tracks_full, tracks_selected);

  EXPECT_EQ(num_selected, 0u);
  EXPECT_TRUE(tracks_selected.empty());
}

// 2) Input map is not modified: tracks_full is passed as const&, so it
//    must remain unchanged after the call.
TEST(TrackEngineTest_54, DoesNotModifyInputTracksFull_54) {
  TrackEngine engine;

  // Create some dummy input tracks
  std::unordered_map<track_t, Track> tracks_full =
      CreateTracksMap_54({static_cast<track_t>(1),
                          static_cast<track_t>(2),
                          static_cast<track_t>(3)});

  // Make a copy to compare after the call
  const auto tracks_full_before = tracks_full;

  std::unordered_map<track_t, Track> tracks_selected;
  (void)engine.FindTracksForProblem(tracks_full, tracks_selected);

  // Size and keys should remain identical
  EXPECT_EQ(tracks_full.size(), tracks_full_before.size());
  for (const auto& kv : tracks_full_before) {
    auto it = tracks_full.find(kv.first);
    ASSERT_NE(it, tracks_full.end());
    // We purposefully do not rely on any internal Track fields here,
    // only that the entry for the key still exists.
  }
}

// 3) All selected tracks (if any) must come from the input map.
//    I.e., the keys in tracks_selected must be a subset of keys from tracks_full.
TEST(TrackEngineTest_54, SelectedTracksAreSubsetOfInput_54) {
  TrackEngine engine;

  // Create some dummy tracks in the input
  std::unordered_map<track_t, Track> tracks_full =
      CreateTracksMap_54({static_cast<track_t>(10),
                          static_cast<track_t>(20),
                          static_cast<track_t>(30)});

  std::unordered_map<track_t, Track> tracks_selected;
  (void)engine.FindTracksForProblem(tracks_full, tracks_selected);

  // Every selected key must exist in the input
  for (const auto& kv : tracks_selected) {
    const track_t selected_id = kv.first;
    EXPECT_NE(tracks_full.find(selected_id), tracks_full.end());
  }
}

// 4) Idempotence: calling FindTracksForProblem with the same input twice
//    should yield the same set of selected track IDs, assuming there is
//    no hidden state modification from this call.
TEST(TrackEngineTest_54, IdempotentForSameInput_54) {
  TrackEngine engine;

  // Some dummy tracks
  std::unordered_map<track_t, Track> tracks_full =
      CreateTracksMap_54({static_cast<track_t>(5),
                          static_cast<track_t>(6),
                          static_cast<track_t>(7)});

  // First call
  std::unordered_map<track_t, Track> tracks_selected_first;
  (void)engine.FindTracksForProblem(tracks_full, tracks_selected_first);

  // Collect keys from the first call
  std::vector<track_t> keys_first;
  keys_first.reserve(tracks_selected_first.size());
  for (const auto& kv : tracks_selected_first) {
    keys_first.push_back(kv.first);
  }
  std::sort(keys_first.begin(), keys_first.end());

  // Second call with the same input
  std::unordered_map<track_t, Track> tracks_selected_second;
  (void)engine.FindTracksForProblem(tracks_full, tracks_selected_second);

  // Collect keys from the second call
  std::vector<track_t> keys_second;
  keys_second.reserve(tracks_selected_second.size());
  for (const auto& kv : tracks_selected_second) {
    keys_second.push_back(kv.first);
  }
  std::sort(keys_second.begin(), keys_second.end());

  // The sets of selected IDs should be identical
  EXPECT_EQ(keys_first, keys_second);
}

}  // namespace
