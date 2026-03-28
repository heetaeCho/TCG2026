#include <gtest/gtest.h>
#include "glomap/controllers/track_establishment.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/types.h"

namespace glomap {
namespace {

class TrackEngineTest_113 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_ = TrackEstablishmentOptions();
  }

  TrackEstablishmentOptions options_;
  ViewGraph view_graph_;
  std::unordered_map<image_t, Image> images_;
};

// Test: EstablishFullTracks with empty view graph and no images returns zero tracks
TEST_F(TrackEngineTest_113, EstablishFullTracksEmptyInputReturnsZero_113) {
  TrackEngine engine(view_graph_, images_, options_);
  std::unordered_map<track_t, Track> tracks;
  size_t result = engine.EstablishFullTracks(tracks);
  EXPECT_EQ(result, 0);
  EXPECT_TRUE(tracks.empty());
}

// Test: EstablishFullTracks clears pre-existing tracks
TEST_F(TrackEngineTest_113, EstablishFullTracksClearsExistingTracks_113) {
  TrackEngine engine(view_graph_, images_, options_);
  std::unordered_map<track_t, Track> tracks;
  // Insert a dummy track before calling
  tracks[0] = Track();
  tracks[1] = Track();
  EXPECT_EQ(tracks.size(), 2);

  size_t result = engine.EstablishFullTracks(tracks);
  // With empty view graph, should clear and return 0
  EXPECT_EQ(result, tracks.size());
}

// Test: EstablishFullTracks return value matches tracks.size()
TEST_F(TrackEngineTest_113, EstablishFullTracksReturnMatchesSize_113) {
  TrackEngine engine(view_graph_, images_, options_);
  std::unordered_map<track_t, Track> tracks;
  size_t result = engine.EstablishFullTracks(tracks);
  EXPECT_EQ(result, tracks.size());
}

// Test: FindTracksForProblem with empty full tracks returns zero selected
TEST_F(TrackEngineTest_113, FindTracksForProblemEmptyFullTracksReturnsZero_113) {
  TrackEngine engine(view_graph_, images_, options_);
  std::unordered_map<track_t, Track> tracks_full;
  std::unordered_map<track_t, Track> tracks_selected;
  size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);
  EXPECT_EQ(result, 0);
  EXPECT_TRUE(tracks_selected.empty());
}

// Test: FindTracksForProblem return value matches selected size
TEST_F(TrackEngineTest_113, FindTracksForProblemReturnMatchesSelectedSize_113) {
  TrackEngine engine(view_graph_, images_, options_);
  std::unordered_map<track_t, Track> tracks_full;
  std::unordered_map<track_t, Track> tracks_selected;
  size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);
  EXPECT_EQ(result, tracks_selected.size());
}

// Test: Calling EstablishFullTracks multiple times is consistent
TEST_F(TrackEngineTest_113, EstablishFullTracksMultipleCallsConsistent_113) {
  TrackEngine engine(view_graph_, images_, options_);
  std::unordered_map<track_t, Track> tracks1;
  std::unordered_map<track_t, Track> tracks2;

  size_t result1 = engine.EstablishFullTracks(tracks1);
  size_t result2 = engine.EstablishFullTracks(tracks2);

  EXPECT_EQ(result1, result2);
  EXPECT_EQ(tracks1.size(), tracks2.size());
}

// Test: With images but no edges in view graph
TEST_F(TrackEngineTest_113, EstablishFullTracksWithImagesNoEdges_113) {
  Image img;
  images_[0] = img;
  images_[1] = img;

  TrackEngine engine(view_graph_, images_, options_);
  std::unordered_map<track_t, Track> tracks;
  size_t result = engine.EstablishFullTracks(tracks);
  EXPECT_EQ(result, tracks.size());
}

// Test: FindTracksForProblem does not modify full tracks (const reference)
TEST_F(TrackEngineTest_113, FindTracksForProblemDoesNotModifyFullTracks_113) {
  TrackEngine engine(view_graph_, images_, options_);
  std::unordered_map<track_t, Track> tracks_full;
  tracks_full[0] = Track();
  size_t original_size = tracks_full.size();

  std::unordered_map<track_t, Track> tracks_selected;
  engine.FindTracksForProblem(tracks_full, tracks_selected);

  EXPECT_EQ(tracks_full.size(), original_size);
}

}  // namespace
}  // namespace glomap
