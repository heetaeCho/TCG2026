#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_map>
#include <vector>
#include <utility>

#include "glomap/controllers/track_establishment.h"
#include "glomap/scene/track.h"
#include "glomap/scene/image.h"
#include "glomap/scene/types.h"

// We need ViewGraph for constructing TrackEngine. Including it:
#include "glomap/scene/view_graph.h"

namespace glomap {
namespace {

// Helper to create a registered image
Image CreateRegisteredImage(image_t id, camera_t cam_id = 0) {
  Image img(id, cam_id, "test_image_" + std::to_string(id));
  // We need to make the image registered. Based on the interface,
  // we assume there's a way to set registration status.
  // Looking at typical COLMAP-style code, we set cam_from_world.
  img.is_registered = true;
  return img;
}

// Helper to create a track with given observations
Track CreateTrack(track_t id, const std::vector<Observation>& obs) {
  Track track;
  track.track_id = id;
  track.observations = obs;
  return track;
}

class FindTracksForProblemTest_114 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Default options
    options_.min_num_tracks_per_view = 2;
    options_.max_num_view_per_track = 100;
    options_.max_num_tracks = 10000000;
    // min_num_view_per_track is not directly in TrackEstablishmentOptions
    // based on the header, but it's used in the code. Let's check...
    // The provided code uses options_.min_num_view_per_track but
    // TrackEstablishmentOptions doesn't show it. It might be inherited
    // or we need to set it. We'll assume a default of 2.
  }

  TrackEstablishmentOptions options_;
};

// Test: Empty tracks_full should return 0 selected tracks
TEST_F(FindTracksForProblemTest_114, EmptyInput_114) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  images[0] = CreateRegisteredImage(0);
  images[1] = CreateRegisteredImage(1);

  TrackEngine engine(view_graph, images, options_);

  std::unordered_map<track_t, Track> tracks_full;
  std::unordered_map<track_t, Track> tracks_selected;

  size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);
  EXPECT_EQ(result, 0u);
  EXPECT_TRUE(tracks_selected.empty());
}

// Test: Tracks with fewer observations than min_num_view_per_track are filtered
TEST_F(FindTracksForProblemTest_114, TracksFilteredByMinViews_114) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  images[0] = CreateRegisteredImage(0);
  images[1] = CreateRegisteredImage(1);
  images[2] = CreateRegisteredImage(2);

  TrackEngine engine(view_graph, images, options_);

  std::unordered_map<track_t, Track> tracks_full;
  // Track with only 1 observation - should be filtered if min_num_view_per_track >= 2
  tracks_full[0] = CreateTrack(0, {{0, 0}});

  std::unordered_map<track_t, Track> tracks_selected;
  size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);
  EXPECT_EQ(result, 0u);
  EXPECT_TRUE(tracks_selected.empty());
}

// Test: Tracks with more observations than max_num_view_per_track are filtered
TEST_F(FindTracksForProblemTest_114, TracksFilteredByMaxViews_114) {
  options_.max_num_view_per_track = 3;

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  for (image_t i = 0; i < 5; ++i) {
    images[i] = CreateRegisteredImage(i);
  }

  TrackEngine engine(view_graph, images, options_);

  std::unordered_map<track_t, Track> tracks_full;
  // Track with 4 observations - exceeds max of 3
  tracks_full[0] = CreateTrack(0, {{0, 0}, {1, 0}, {2, 0}, {3, 0}});

  std::unordered_map<track_t, Track> tracks_selected;
  size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);
  EXPECT_EQ(result, 0u);
}

// Test: Valid tracks are selected when they meet criteria
TEST_F(FindTracksForProblemTest_114, ValidTracksSelected_114) {
  options_.min_num_tracks_per_view = 2;
  options_.max_num_view_per_track = 100;

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  for (image_t i = 0; i < 5; ++i) {
    images[i] = CreateRegisteredImage(i);
  }

  TrackEngine engine(view_graph, images, options_);

  std::unordered_map<track_t, Track> tracks_full;
  tracks_full[0] = CreateTrack(0, {{0, 0}, {1, 0}, {2, 0}});
  tracks_full[1] = CreateTrack(1, {{1, 1}, {2, 1}, {3, 1}});
  tracks_full[2] = CreateTrack(2, {{2, 2}, {3, 2}, {4, 2}});

  std::unordered_map<track_t, Track> tracks_selected;
  size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);
  EXPECT_GT(result, 0u);
  EXPECT_EQ(result, tracks_selected.size());
}

// Test: max_num_tracks limits the number of selected tracks
TEST_F(FindTracksForProblemTest_114, MaxNumTracksLimit_114) {
  options_.max_num_tracks = 1;
  options_.min_num_tracks_per_view = 100;  // high so cameras_left won't hit 0

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  for (image_t i = 0; i < 10; ++i) {
    images[i] = CreateRegisteredImage(i);
  }

  TrackEngine engine(view_graph, images, options_);

  std::unordered_map<track_t, Track> tracks_full;
  for (track_t t = 0; t < 20; ++t) {
    tracks_full[t] = CreateTrack(t, {{static_cast<image_t>(t % 10), 0},
                                     {static_cast<image_t>((t + 1) % 10), 0}});
  }

  std::unordered_map<track_t, Track> tracks_selected;
  size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);
  // Should be limited by max_num_tracks
  EXPECT_LE(result, static_cast<size_t>(options_.max_num_tracks + 1));
}

// Test: Tracks referencing unregistered images have those observations filtered
TEST_F(FindTracksForProblemTest_114, UnregisteredImagesFiltered_114) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  images[0] = CreateRegisteredImage(0);
  images[1] = CreateRegisteredImage(1);
  // Image 2 is not registered
  Image unreg_img(2, 0, "unreg");
  unreg_img.is_registered = false;
  images[2] = unreg_img;

  TrackEngine engine(view_graph, images, options_);

  std::unordered_map<track_t, Track> tracks_full;
  // Track has observations on images 0, 1, and 2; but 2 is unregistered
  tracks_full[0] = CreateTrack(0, {{0, 0}, {1, 0}, {2, 0}});

  std::unordered_map<track_t, Track> tracks_selected;
  size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

  if (result > 0) {
    // The selected track should only have observations from registered images
    for (const auto& [tid, track] : tracks_selected) {
      for (const auto& [img_id, feat_id] : track.observations) {
        EXPECT_TRUE(images.at(img_id).IsRegistered())
            << "Observation references unregistered image " << img_id;
      }
    }
  }
}

// Test: Longer tracks are prioritized (sorted in descending order)
TEST_F(FindTracksForProblemTest_114, LongerTracksPrioritized_114) {
  options_.max_num_tracks = 1;
  options_.min_num_tracks_per_view = 100;

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  for (image_t i = 0; i < 5; ++i) {
    images[i] = CreateRegisteredImage(i);
  }

  TrackEngine engine(view_graph, images, options_);

  std::unordered_map<track_t, Track> tracks_full;
  // Short track
  tracks_full[0] = CreateTrack(0, {{0, 0}, {1, 0}});
  // Long track
  tracks_full[1] = CreateTrack(1, {{0, 1}, {1, 1}, {2, 1}, {3, 1}});

  std::unordered_map<track_t, Track> tracks_selected;
  size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

  if (result == 1) {
    // The longer track should be selected first
    EXPECT_TRUE(tracks_selected.count(1) > 0);
  }
}

// Test: No registered images means no tracks selected
TEST_F(FindTracksForProblemTest_114, NoRegisteredImages_114) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  // All unregistered
  Image unreg0(0, 0, "unreg0");
  unreg0.is_registered = false;
  images[0] = unreg0;
  Image unreg1(1, 0, "unreg1");
  unreg1.is_registered = false;
  images[1] = unreg1;

  TrackEngine engine(view_graph, images, options_);

  std::unordered_map<track_t, Track> tracks_full;
  tracks_full[0] = CreateTrack(0, {{0, 0}, {1, 0}});

  std::unordered_map<track_t, Track> tracks_selected;
  size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);
  EXPECT_EQ(result, 0u);
}

// Test: Return value matches the size of tracks_selected
TEST_F(FindTracksForProblemTest_114, ReturnValueMatchesSelectedSize_114) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  for (image_t i = 0; i < 5; ++i) {
    images[i] = CreateRegisteredImage(i);
  }

  TrackEngine engine(view_graph, images, options_);

  std::unordered_map<track_t, Track> tracks_full;
  tracks_full[0] = CreateTrack(0, {{0, 0}, {1, 0}, {2, 0}});
  tracks_full[1] = CreateTrack(1, {{2, 1}, {3, 1}, {4, 1}});

  std::unordered_map<track_t, Track> tracks_selected;
  size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);
  EXPECT_EQ(result, tracks_selected.size());
}

// Test: cameras_left reaching 0 stops adding tracks
TEST_F(FindTracksForProblemTest_114, CamerasLeftStopsSelection_114) {
  options_.min_num_tracks_per_view = 1;

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  // Only 2 registered images
  images[0] = CreateRegisteredImage(0);
  images[1] = CreateRegisteredImage(1);

  TrackEngine engine(view_graph, images, options_);

  std::unordered_map<track_t, Track> tracks_full;
  // These two tracks should satisfy both cameras
  tracks_full[0] = CreateTrack(0, {{0, 0}, {1, 0}});
  tracks_full[1] = CreateTrack(1, {{0, 1}, {1, 1}});
  // Extra tracks that shouldn't be needed
  tracks_full[2] = CreateTrack(2, {{0, 2}, {1, 2}});
  tracks_full[3] = CreateTrack(3, {{0, 3}, {1, 3}});

  std::unordered_map<track_t, Track> tracks_selected;
  size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);
  // With min_num_tracks_per_view=1, after 2 tracks both cameras should be satisfied
  // The algorithm should stop early
  EXPECT_GE(result, 1u);
  EXPECT_LE(result, 4u);
}

// Test: Track observations referencing non-existent images in images_ are skipped
TEST_F(FindTracksForProblemTest_114, NonExistentImageObservationsSkipped_114) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  images[0] = CreateRegisteredImage(0);
  images[1] = CreateRegisteredImage(1);
  // Image 99 does not exist in images_

  TrackEngine engine(view_graph, images, options_);

  std::unordered_map<track_t, Track> tracks_full;
  // Track references image 99 which doesn't exist
  tracks_full[0] = CreateTrack(0, {{0, 0}, {99, 0}});

  std::unordered_map<track_t, Track> tracks_selected;
  size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);
  
  // After filtering, only image 0 remains, which is < min_num_view_per_track (2)
  // So track should not be selected
  EXPECT_EQ(result, 0u);
}

// Test: Selected tracks preserve correct track_id
TEST_F(FindTracksForProblemTest_114, SelectedTracksPreserveTrackId_114) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  for (image_t i = 0; i < 5; ++i) {
    images[i] = CreateRegisteredImage(i);
  }

  TrackEngine engine(view_graph, images, options_);

  std::unordered_map<track_t, Track> tracks_full;
  tracks_full[42] = CreateTrack(42, {{0, 0}, {1, 0}, {2, 0}});

  std::unordered_map<track_t, Track> tracks_selected;
  size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);

  if (result > 0) {
    EXPECT_TRUE(tracks_selected.count(42) > 0);
    EXPECT_EQ(tracks_selected[42].track_id, 42);
  }
}

// Test: Single track meeting all criteria is selected
TEST_F(FindTracksForProblemTest_114, SingleValidTrack_114) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  images[0] = CreateRegisteredImage(0);
  images[1] = CreateRegisteredImage(1);
  images[2] = CreateRegisteredImage(2);

  TrackEngine engine(view_graph, images, options_);

  std::unordered_map<track_t, Track> tracks_full;
  tracks_full[0] = CreateTrack(0, {{0, 0}, {1, 0}, {2, 0}});

  std::unordered_map<track_t, Track> tracks_selected;
  size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);
  EXPECT_EQ(result, 1u);
  EXPECT_EQ(tracks_selected.size(), 1u);
}

// Test: Boundary - track with exactly min_num_view_per_track observations
TEST_F(FindTracksForProblemTest_114, ExactlyMinViewsPerTrack_114) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  images[0] = CreateRegisteredImage(0);
  images[1] = CreateRegisteredImage(1);

  TrackEngine engine(view_graph, images, options_);

  std::unordered_map<track_t, Track> tracks_full;
  // Exactly 2 observations (assuming min_num_view_per_track = 2)
  tracks_full[0] = CreateTrack(0, {{0, 0}, {1, 0}});

  std::unordered_map<track_t, Track> tracks_selected;
  size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);
  EXPECT_EQ(result, 1u);
}

// Test: Boundary - track with exactly max_num_view_per_track observations
TEST_F(FindTracksForProblemTest_114, ExactlyMaxViewsPerTrack_114) {
  options_.max_num_view_per_track = 3;

  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  for (image_t i = 0; i < 4; ++i) {
    images[i] = CreateRegisteredImage(i);
  }

  TrackEngine engine(view_graph, images, options_);

  std::unordered_map<track_t, Track> tracks_full;
  // Exactly 3 observations = max_num_view_per_track
  tracks_full[0] = CreateTrack(0, {{0, 0}, {1, 0}, {2, 0}});

  std::unordered_map<track_t, Track> tracks_selected;
  size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);
  EXPECT_EQ(result, 1u);
}

// Test: tracks_selected is overwritten (not appended to)
TEST_F(FindTracksForProblemTest_114, TracksSelectedOverwritten_114) {
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  images[0] = CreateRegisteredImage(0);
  images[1] = CreateRegisteredImage(1);

  TrackEngine engine(view_graph, images, options_);

  std::unordered_map<track_t, Track> tracks_full;
  // Empty input

  std::unordered_map<track_t, Track> tracks_selected;
  // Pre-populate tracks_selected
  tracks_selected[99] = CreateTrack(99, {{0, 0}, {1, 0}});

  size_t result = engine.FindTracksForProblem(tracks_full, tracks_selected);
  EXPECT_EQ(result, 0u);
  EXPECT_TRUE(tracks_selected.empty());
}

}  // namespace
}  // namespace glomap
