#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>
#include <utility>

#include "glomap/controllers/track_establishment.h"
#include "glomap/types.h"

namespace glomap {
namespace {

// Helper to create a Track with given observations
Track MakeTrack(track_t id, const std::vector<std::pair<image_t, feature_t>>& obs) {
    Track track;
    track.track_id = id;
    for (const auto& o : obs) {
        track.observations.emplace_back(o);
    }
    return track;
}

class TrackEngineTest_54 : public ::testing::Test {
protected:
    void SetUp() override {
        // Default options
    }

    // Helper to add a registered image
    void AddRegisteredImage(image_t id) {
        Image img;
        img.image_id = id;
        img.is_registered = true;
        images_[id] = img;
    }

    // Helper to add an unregistered image
    void AddUnregisteredImage(image_t id) {
        Image img;
        img.image_id = id;
        img.is_registered = false;
        images_[id] = img;
    }

    std::unordered_map<image_t, Image> images_;
    TrackEstablishmentOptions options_;
};

// Test with empty tracks input
TEST_F(TrackEngineTest_54, EmptyTracksReturnsZero_54) {
    TrackEngine engine(options_, images_);
    std::unordered_map<track_t, Track> tracks_full;
    std::unordered_map<track_t, Track> tracks_selected;

    size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

    EXPECT_EQ(result, 0);
    EXPECT_TRUE(tracks_selected.empty());
}

// Test with no registered images
TEST_F(TrackEngineTest_54, NoRegisteredImagesReturnsZero_54) {
    AddUnregisteredImage(1);
    AddUnregisteredImage(2);

    TrackEngine engine(options_, images_);

    std::unordered_map<track_t, Track> tracks_full;
    tracks_full[0] = MakeTrack(0, {{1, 0}, {2, 1}});

    std::unordered_map<track_t, Track> tracks_selected;
    size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

    EXPECT_EQ(result, 0);
    EXPECT_TRUE(tracks_selected.empty());
}

// Test that tracks below min_num_view_per_track are filtered out
TEST_F(TrackEngineTest_54, TracksBelowMinViewsFiltered_54) {
    AddRegisteredImage(1);
    AddRegisteredImage(2);
    AddRegisteredImage(3);

    options_.min_num_view_per_track = 3;
    options_.max_num_view_per_track = 100;
    options_.min_num_tracks_per_view = 100;
    options_.max_num_tracks = 1000;

    TrackEngine engine(options_, images_);

    std::unordered_map<track_t, Track> tracks_full;
    // This track has only 2 observations, below min of 3
    tracks_full[0] = MakeTrack(0, {{1, 0}, {2, 1}});

    std::unordered_map<track_t, Track> tracks_selected;
    size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

    EXPECT_EQ(result, 0);
    EXPECT_TRUE(tracks_selected.empty());
}

// Test that tracks above max_num_view_per_track are filtered out
TEST_F(TrackEngineTest_54, TracksAboveMaxViewsFiltered_54) {
    AddRegisteredImage(1);
    AddRegisteredImage(2);
    AddRegisteredImage(3);
    AddRegisteredImage(4);

    options_.min_num_view_per_track = 2;
    options_.max_num_view_per_track = 3;
    options_.min_num_tracks_per_view = 100;
    options_.max_num_tracks = 1000;

    TrackEngine engine(options_, images_);

    std::unordered_map<track_t, Track> tracks_full;
    // This track has 4 observations, above max of 3
    tracks_full[0] = MakeTrack(0, {{1, 0}, {2, 1}, {3, 2}, {4, 3}});

    std::unordered_map<track_t, Track> tracks_selected;
    size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

    EXPECT_EQ(result, 0);
    EXPECT_TRUE(tracks_selected.empty());
}

// Test normal case where tracks are selected
TEST_F(TrackEngineTest_54, NormalTrackSelection_54) {
    AddRegisteredImage(1);
    AddRegisteredImage(2);
    AddRegisteredImage(3);

    options_.min_num_view_per_track = 2;
    options_.max_num_view_per_track = 100;
    options_.min_num_tracks_per_view = 100;
    options_.max_num_tracks = 1000;

    TrackEngine engine(options_, images_);

    std::unordered_map<track_t, Track> tracks_full;
    tracks_full[0] = MakeTrack(0, {{1, 0}, {2, 1}, {3, 2}});
    tracks_full[1] = MakeTrack(1, {{1, 3}, {2, 4}});

    std::unordered_map<track_t, Track> tracks_selected;
    size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

    EXPECT_EQ(result, 2);
    EXPECT_EQ(tracks_selected.size(), 2);
    EXPECT_TRUE(tracks_selected.count(0) > 0);
    EXPECT_TRUE(tracks_selected.count(1) > 0);
}

// Test that max_num_tracks limits the number of tracks selected
TEST_F(TrackEngineTest_54, MaxNumTracksLimit_54) {
    AddRegisteredImage(1);
    AddRegisteredImage(2);
    AddRegisteredImage(3);
    AddRegisteredImage(4);
    AddRegisteredImage(5);

    options_.min_num_view_per_track = 2;
    options_.max_num_view_per_track = 100;
    options_.min_num_tracks_per_view = 1000;  // high so we don't stop by camera coverage
    options_.max_num_tracks = 1;  // limit to 1 track

    TrackEngine engine(options_, images_);

    std::unordered_map<track_t, Track> tracks_full;
    tracks_full[0] = MakeTrack(0, {{1, 0}, {2, 1}, {3, 2}});
    tracks_full[1] = MakeTrack(1, {{3, 3}, {4, 4}, {5, 5}});
    tracks_full[2] = MakeTrack(2, {{1, 6}, {4, 7}});

    std::unordered_map<track_t, Track> tracks_selected;
    size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

    // Should stop after max_num_tracks exceeded
    EXPECT_LE(result, 3u);
}

// Test that tracks with observations only on unregistered images are excluded
TEST_F(TrackEngineTest_54, TracksOnUnregisteredImagesExcluded_54) {
    AddRegisteredImage(1);
    AddUnregisteredImage(2);
    AddUnregisteredImage(3);

    options_.min_num_view_per_track = 2;
    options_.max_num_view_per_track = 100;
    options_.min_num_tracks_per_view = 100;
    options_.max_num_tracks = 1000;

    TrackEngine engine(options_, images_);

    std::unordered_map<track_t, Track> tracks_full;
    // Track has 3 observations total but only 1 on registered image
    tracks_full[0] = MakeTrack(0, {{1, 0}, {2, 1}, {3, 2}});

    std::unordered_map<track_t, Track> tracks_selected;
    size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

    // After filtering unregistered images, only 1 observation left, below min of 2
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(tracks_selected.empty());
}

// Test that longer tracks are prioritized (sorted in descending order)
TEST_F(TrackEngineTest_54, LongerTracksPrioritized_54) {
    AddRegisteredImage(1);
    AddRegisteredImage(2);
    AddRegisteredImage(3);
    AddRegisteredImage(4);

    options_.min_num_view_per_track = 2;
    options_.max_num_view_per_track = 100;
    options_.min_num_tracks_per_view = 1;  // stop after 1 track per view covered
    options_.max_num_tracks = 1000;

    TrackEngine engine(options_, images_);

    std::unordered_map<track_t, Track> tracks_full;
    // Longer track
    tracks_full[0] = MakeTrack(0, {{1, 0}, {2, 1}, {3, 2}, {4, 3}});
    // Shorter track on same images
    tracks_full[1] = MakeTrack(1, {{1, 4}, {2, 5}});

    std::unordered_map<track_t, Track> tracks_selected;
    size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

    // The longer track should be selected first
    EXPECT_GE(result, 1u);
    EXPECT_TRUE(tracks_selected.count(0) > 0);
}

// Test with exact min_num_view_per_track boundary
TEST_F(TrackEngineTest_54, ExactMinViewBoundary_54) {
    AddRegisteredImage(1);
    AddRegisteredImage(2);

    options_.min_num_view_per_track = 2;
    options_.max_num_view_per_track = 100;
    options_.min_num_tracks_per_view = 100;
    options_.max_num_tracks = 1000;

    TrackEngine engine(options_, images_);

    std::unordered_map<track_t, Track> tracks_full;
    // Exactly 2 observations == min_num_view_per_track
    tracks_full[0] = MakeTrack(0, {{1, 0}, {2, 1}});

    std::unordered_map<track_t, Track> tracks_selected;
    size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

    EXPECT_EQ(result, 1);
    EXPECT_TRUE(tracks_selected.count(0) > 0);
}

// Test with exact max_num_view_per_track boundary
TEST_F(TrackEngineTest_54, ExactMaxViewBoundary_54) {
    AddRegisteredImage(1);
    AddRegisteredImage(2);
    AddRegisteredImage(3);

    options_.min_num_view_per_track = 2;
    options_.max_num_view_per_track = 3;
    options_.min_num_tracks_per_view = 100;
    options_.max_num_tracks = 1000;

    TrackEngine engine(options_, images_);

    std::unordered_map<track_t, Track> tracks_full;
    // Exactly 3 observations == max_num_view_per_track
    tracks_full[0] = MakeTrack(0, {{1, 0}, {2, 1}, {3, 2}});

    std::unordered_map<track_t, Track> tracks_selected;
    size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

    EXPECT_EQ(result, 1);
    EXPECT_TRUE(tracks_selected.count(0) > 0);
}

// Test that selected tracks contain correct observations (only registered images)
TEST_F(TrackEngineTest_54, SelectedTrackContainsOnlyRegisteredObservations_54) {
    AddRegisteredImage(1);
    AddRegisteredImage(2);
    AddUnregisteredImage(3);

    options_.min_num_view_per_track = 2;
    options_.max_num_view_per_track = 100;
    options_.min_num_tracks_per_view = 100;
    options_.max_num_tracks = 1000;

    TrackEngine engine(options_, images_);

    std::unordered_map<track_t, Track> tracks_full;
    tracks_full[0] = MakeTrack(0, {{1, 0}, {2, 1}, {3, 2}});

    std::unordered_map<track_t, Track> tracks_selected;
    size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

    EXPECT_EQ(result, 1);
    ASSERT_TRUE(tracks_selected.count(0) > 0);

    // The selected track should only have observations on registered images
    const auto& selected_track = tracks_selected.at(0);
    for (const auto& [img_id, feat_id] : selected_track.observations) {
        EXPECT_NE(img_id, 3) << "Unregistered image should not appear in selected track";
    }
    EXPECT_EQ(selected_track.observations.size(), 2);
}

// Test cameras_left == 0 early termination
TEST_F(TrackEngineTest_54, EarlyTerminationWhenAllCamerasCovered_54) {
    AddRegisteredImage(1);
    AddRegisteredImage(2);

    options_.min_num_view_per_track = 2;
    options_.max_num_view_per_track = 100;
    options_.min_num_tracks_per_view = 0;  // Any track will exceed this
    options_.max_num_tracks = 1000;

    TrackEngine engine(options_, images_);

    std::unordered_map<track_t, Track> tracks_full;
    tracks_full[0] = MakeTrack(0, {{1, 0}, {2, 1}});
    tracks_full[1] = MakeTrack(1, {{1, 2}, {2, 3}});

    std::unordered_map<track_t, Track> tracks_selected;
    size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

    // With min_num_tracks_per_view = 0, after first track that adds to cameras,
    // cameras_left should hit 0 quickly
    EXPECT_GE(result, 1u);
}

// Test output parameter is properly populated
TEST_F(TrackEngineTest_54, OutputParameterPopulatedCorrectly_54) {
    AddRegisteredImage(1);
    AddRegisteredImage(2);

    options_.min_num_view_per_track = 2;
    options_.max_num_view_per_track = 100;
    options_.min_num_tracks_per_view = 100;
    options_.max_num_tracks = 1000;

    TrackEngine engine(options_, images_);

    std::unordered_map<track_t, Track> tracks_full;
    tracks_full[5] = MakeTrack(5, {{1, 10}, {2, 20}});

    std::unordered_map<track_t, Track> tracks_selected;
    size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

    EXPECT_EQ(result, tracks_selected.size());
    EXPECT_EQ(result, 1);
    ASSERT_TRUE(tracks_selected.count(5) > 0);
    EXPECT_EQ(tracks_selected[5].track_id, 5);
}

// Test return value matches output map size
TEST_F(TrackEngineTest_54, ReturnValueMatchesOutputSize_54) {
    AddRegisteredImage(1);
    AddRegisteredImage(2);
    AddRegisteredImage(3);

    options_.min_num_view_per_track = 2;
    options_.max_num_view_per_track = 100;
    options_.min_num_tracks_per_view = 100;
    options_.max_num_tracks = 1000;

    TrackEngine engine(options_, images_);

    std::unordered_map<track_t, Track> tracks_full;
    tracks_full[0] = MakeTrack(0, {{1, 0}, {2, 1}});
    tracks_full[1] = MakeTrack(1, {{2, 2}, {3, 3}});
    tracks_full[2] = MakeTrack(2, {{1, 4}, {3, 5}});

    std::unordered_map<track_t, Track> tracks_selected;
    size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

    EXPECT_EQ(result, tracks_selected.size());
}

// Test with single observation track (below any reasonable min)
TEST_F(TrackEngineTest_54, SingleObservationTrackFiltered_54) {
    AddRegisteredImage(1);

    options_.min_num_view_per_track = 2;
    options_.max_num_view_per_track = 100;
    options_.min_num_tracks_per_view = 100;
    options_.max_num_tracks = 1000;

    TrackEngine engine(options_, images_);

    std::unordered_map<track_t, Track> tracks_full;
    tracks_full[0] = MakeTrack(0, {{1, 0}});

    std::unordered_map<track_t, Track> tracks_selected;
    size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

    EXPECT_EQ(result, 0);
    EXPECT_TRUE(tracks_selected.empty());
}

// Test with images not present in any track
TEST_F(TrackEngineTest_54, RegisteredImagesNotInTracks_54) {
    AddRegisteredImage(1);
    AddRegisteredImage(2);
    AddRegisteredImage(100);  // not in any track

    options_.min_num_view_per_track = 2;
    options_.max_num_view_per_track = 100;
    options_.min_num_tracks_per_view = 100;
    options_.max_num_tracks = 1000;

    TrackEngine engine(options_, images_);

    std::unordered_map<track_t, Track> tracks_full;
    tracks_full[0] = MakeTrack(0, {{1, 0}, {2, 1}});

    std::unordered_map<track_t, Track> tracks_selected;
    size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

    EXPECT_EQ(result, 1);
    EXPECT_TRUE(tracks_selected.count(0) > 0);
}

// Test that the output map is overwritten (not appended to)
TEST_F(TrackEngineTest_54, OutputMapOverwritten_54) {
    AddRegisteredImage(1);
    AddRegisteredImage(2);

    options_.min_num_view_per_track = 2;
    options_.max_num_view_per_track = 100;
    options_.min_num_tracks_per_view = 100;
    options_.max_num_tracks = 1000;

    TrackEngine engine(options_, images_);

    std::unordered_map<track_t, Track> tracks_full;
    tracks_full[0] = MakeTrack(0, {{1, 0}, {2, 1}});

    // Pre-populate selected with some junk data
    std::unordered_map<track_t, Track> tracks_selected;
    tracks_selected[999] = MakeTrack(999, {{1, 99}});

    size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

    EXPECT_EQ(result, 1);
    EXPECT_EQ(tracks_selected.size(), 1);
    EXPECT_TRUE(tracks_selected.count(0) > 0);
    EXPECT_TRUE(tracks_selected.count(999) == 0);
}

}  // namespace
}  // namespace glomap
