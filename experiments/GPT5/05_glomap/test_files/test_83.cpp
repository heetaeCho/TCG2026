// File: reconstruction_pruning_test_83.cc

#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

// -----------------------------------------------------------------------------
// Test doubles / stubs for external dependencies
// -----------------------------------------------------------------------------

// Simple no-op logger to satisfy LOG(INFO) << ...
struct NullLog {
  template <typename T>
  NullLog& operator<<(const T&) {
    return *this;
  }
};

#define LOG(level) NullLog()

namespace glomap {

// Basic type aliases (can be adjusted to match real project types)
using image_t = int;
using frame_t = int;
using track_t = int;
using image_pair_t = std::uint64_t;

// Minimal data-id wrapper used by Frame::ImageIds()
struct DataId {
  image_t id;
};

// Minimal Frame stub with ImageIds() accessor
struct Frame {
  std::vector<DataId> image_ids;

  const std::vector<DataId>& ImageIds() const {
    return image_ids;
  }
};

// Minimal Image stub with associated frame_id
struct Image {
  frame_t frame_id = 0;
};

// Minimal Track stub with observations
// Only .first (image_t) is used in the production code.
struct Track {
  std::vector<std::pair<image_t, int>> observations;
};

// Minimal ImagePair and ViewGraph used inside PruneWeaklyConnectedImages
struct ImagePair {
  image_t image_id1 = 0;
  image_t image_id2 = 0;
  bool is_valid = false;
  int weight = 0;

  ImagePair() = default;
  ImagePair(image_t i1, image_t i2) : image_id1(i1), image_id2(i2) {}
};

struct ViewGraph {
  std::unordered_map<image_pair_t, ImagePair> image_pairs;
};

// Stubbed ViewGraphManipulater capturing calls to EstablishStrongClusters.
struct ViewGraphManipulater {
  enum WeightType { WEIGHT = 0 };

  static ViewGraph last_graph;
  static double last_threshold;
  static int last_min_num_images;
  static int call_count;
  static image_t last_result;

  static void Reset() {
    last_graph.image_pairs.clear();
    last_threshold = 0.0;
    last_min_num_images = 0;
    call_count = 0;
    last_result = 0;
  }

  static image_t EstablishStrongClusters(
      const ViewGraph& graph,
      std::unordered_map<frame_t, Frame>& /*frames*/,
      std::unordered_map<image_t, Image>& /*images*/,
      WeightType /*weight_type*/, double threshold, int min_num_images) {
    last_graph = graph;
    last_threshold = threshold;
    last_min_num_images = min_num_images;
    ++call_count;
    return last_result;
  }
};

// Static member definitions
ViewGraph ViewGraphManipulater::last_graph;
double ViewGraphManipulater::last_threshold = 0.0;
int ViewGraphManipulater::last_min_num_images = 0;
int ViewGraphManipulater::call_count = 0;
image_t ViewGraphManipulater::last_result = 0;

}  // namespace glomap

namespace colmap {

// Use glomap's basic types
using glomap::image_pair_t;
using glomap::image_t;

// Simple pair-id encoding/decoding helpers for tests
inline image_pair_t ImagePairToPairId(image_t image_id1, image_t image_id2) {
  if (image_id1 > image_id2) {
    std::swap(image_id1, image_id2);
  }
  return (static_cast<image_pair_t>(image_id1) << 32) |
         static_cast<image_pair_t>(image_id2);
}

inline std::pair<image_t, image_t> PairIdToImagePair(image_pair_t pair_id) {
  image_t first = static_cast<image_t>(pair_id >> 32);
  image_t second = static_cast<image_t>(pair_id & 0xffffffffu);
  return {first, second};
}

}  // namespace colmap

// -----------------------------------------------------------------------------
// Include the production implementation under test
// -----------------------------------------------------------------------------

// The path matches the one given in the prompt; adjust if your project uses a
// different relative include path.
#include "glomap/processors/reconstruction_pruning.cc"

// -----------------------------------------------------------------------------
// Test fixture
// -----------------------------------------------------------------------------

class PruneWeaklyConnectedImagesTest_83 : public ::testing::Test {
 protected:
  void SetUp() override { glomap::ViewGraphManipulater::Reset(); }

  // Helper to find whether a ViewGraph contains an edge (u, v) regardless of
  // ordering, and optionally return its weight.
  bool HasEdge(const glomap::ViewGraph& graph,
               glomap::image_t u,
               glomap::image_t v,
               int* weight_out = nullptr) {
    for (const auto& kv : graph.image_pairs) {
      const auto& ip = kv.second;
      if ((ip.image_id1 == u && ip.image_id2 == v) ||
          (ip.image_id1 == v && ip.image_id2 == u)) {
        if (weight_out) {
          *weight_out = ip.weight;
        }
        return true;
      }
    }
    return false;
  }
};

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

// Normal operation: a single strong pair builds a visibility graph and
// EstablishStrongClusters is called with the expected threshold and arguments.
TEST_F(PruneWeaklyConnectedImagesTest_83,
       BuildsVisibilityGraphAndStrongClusterCall_83) {
  using namespace glomap;

  // Frames with multiple images each.
  std::unordered_map<frame_t, Frame> frames;
  Frame frame1;
  frame1.image_ids = {{10}, {11}, {12}};
  Frame frame2;
  frame2.image_ids = {{20}, {21}};
  frames.emplace(1, frame1);
  frames.emplace(2, frame2);

  // Images mapped to frames.
  std::unordered_map<image_t, Image> images;
  Image img10; img10.frame_id = 1;
  Image img11; img11.frame_id = 1;
  Image img12; img12.frame_id = 1;
  Image img20; img20.frame_id = 2;
  Image img21; img21.frame_id = 2;
  images.emplace(10, img10);
  images.emplace(11, img11);
  images.emplace(12, img12);
  images.emplace(20, img20);
  images.emplace(21, img21);

  // One track observing points in both frames -> covisibility >= 5.
  std::unordered_map<track_t, Track> tracks;
  Track track;
  track.observations.emplace_back(10, 0);
  track.observations.emplace_back(20, 0);
  track.observations.emplace_back(11, 0);
  track.observations.emplace_back(21, 0);
  track.observations.emplace_back(12, 0);  // 3 (frame 1) x 2 (frame 2) = 6
  tracks.emplace(1, track);

  const int kMinNumImages = 2;
  const int kMinNumObservations = 1;

  // Configure stubbed clusterer to return a known id.
  ViewGraphManipulater::last_result = 99;

  image_t result = PruneWeaklyConnectedImages(
      frames, images, tracks, kMinNumImages, kMinNumObservations);

  // The return value should be what EstablishStrongClusters returned.
  EXPECT_EQ(result, 99);

  // EstablishStrongClusters should be called exactly once.
  EXPECT_EQ(ViewGraphManipulater::call_count, 1);
  EXPECT_EQ(ViewGraphManipulater::last_min_num_images, kMinNumImages);

  // With a single pair_count entry (value 6), the code should use a threshold
  // of max(median, 20.0) = 20.0.
  EXPECT_DOUBLE_EQ(ViewGraphManipulater::last_threshold, 20.0);

  // Visibility graph should contain:
  //  - one edge between the begin images of frame 1 and 2 (10, 20) with weight 6
  //  - star edges within each frame: (10, 11), (10, 12), (20, 21)
  const auto& graph = ViewGraphManipulater::last_graph;
  EXPECT_EQ(graph.image_pairs.size(), 4u);

  int weight = 0;
  EXPECT_TRUE(HasEdge(graph, 10, 20, &weight));
  EXPECT_EQ(weight, 6);

  EXPECT_TRUE(HasEdge(graph, 10, 11, &weight));
  EXPECT_EQ(weight, 0);

  EXPECT_TRUE(HasEdge(graph, 10, 12, &weight));
  EXPECT_EQ(weight, 0);

  EXPECT_TRUE(HasEdge(graph, 20, 21, &weight));
  EXPECT_EQ(weight, 0);
}

// Boundary / filtering behavior: pairs for which one frame does not reach
// min_num_observations should be skipped, even if their covisibility count is
// high enough.
TEST_F(PruneWeaklyConnectedImagesTest_83,
       SkipsPairsBelowObservationThreshold_83) {
  using namespace glomap;

  std::unordered_map<frame_t, Frame> frames;
  Frame frame1; frame1.image_ids = {{10}, {11}, {12}};
  Frame frame2; frame2.image_ids = {{20}, {21}};
  Frame frame3; frame3.image_ids = {{30}};
  Frame frame4; frame4.image_ids = {{40}};
  frames.emplace(1, frame1);
  frames.emplace(2, frame2);
  frames.emplace(3, frame3);
  frames.emplace(4, frame4);

  std::unordered_map<image_t, Image> images;
  Image img10; img10.frame_id = 1;
  Image img11; img11.frame_id = 1;
  Image img12; img12.frame_id = 1;
  Image img20; img20.frame_id = 2;
  Image img21; img21.frame_id = 2;
  Image img30; img30.frame_id = 3;
  Image img40; img40.frame_id = 4;
  images.emplace(10, img10);
  images.emplace(11, img11);
  images.emplace(12, img12);
  images.emplace(20, img20);
  images.emplace(21, img21);
  images.emplace(30, img30);
  images.emplace(40, img40);

  std::unordered_map<track_t, Track> tracks;

  // Track 1: strong covisibility between frames 1 and 2.
  Track track1;
  // 3 obs in frame 1
  track1.observations.emplace_back(10, 0);
  track1.observations.emplace_back(11, 0);
  track1.observations.emplace_back(12, 0);
  // 3 obs in frame 2
  track1.observations.emplace_back(20, 0);
  track1.observations.emplace_back(21, 0);
  track1.observations.emplace_back(20, 0);  // duplicate allowed
  // => 3 x 3 = 9 covisibility count
  tracks.emplace(1, track1);

  // Track 2: strong covisibility between frames 3 and 4, but frame 3 has
  // too few observations to pass the threshold.
  Track track2;
  track2.observations.emplace_back(30, 0);      // frame 3: 1 obs
  for (int i = 0; i < 5; ++i) {                 // frame 4: 5 obs
    track2.observations.emplace_back(40, 0);
  }
  // product = 1 x 5 = 5 => covisibility >= 5 but frame 3 has only 1 obs
  tracks.emplace(2, track2);

  const int kMinNumImages = 2;
  const int kMinNumObservations = 3;

  ViewGraphManipulater::last_result = 123;

  image_t result = PruneWeaklyConnectedImages(
      frames, images, tracks, kMinNumImages, kMinNumObservations);

  EXPECT_EQ(result, 123);
  EXPECT_EQ(ViewGraphManipulater::call_count, 1);
  EXPECT_DOUBLE_EQ(ViewGraphManipulater::last_threshold, 20.0);

  const auto& graph = ViewGraphManipulater::last_graph;

  // Strong pair between frames 1 and 2 (begin images 10, 20) should be present.
  EXPECT_TRUE(HasEdge(graph, 10, 20));

  // Pair between begin images of frames 3 and 4 (30, 40) should be absent
  // because frame 3 did not reach kMinNumObservations.
  EXPECT_FALSE(HasEdge(graph, 30, 40));
}

// Exceptional / boundary case: tracks with too few observations (<= 2) must be
// ignored when building covisibility pairs.
TEST_F(PruneWeaklyConnectedImagesTest_83,
       IgnoresTracksWithTooFewObservations_83) {
  using namespace glomap;

  std::unordered_map<frame_t, Frame> frames;
  Frame frame1; frame1.image_ids = {{10}, {11}, {12}};
  Frame frame2; frame2.image_ids = {{20}, {21}};
  Frame frame5; frame5.image_ids = {{50}};
  Frame frame6; frame6.image_ids = {{60}};
  frames.emplace(1, frame1);
  frames.emplace(2, frame2);
  frames.emplace(5, frame5);
  frames.emplace(6, frame6);

  std::unordered_map<image_t, Image> images;
  Image img10; img10.frame_id = 1;
  Image img11; img11.frame_id = 1;
  Image img12; img12.frame_id = 1;
  Image img20; img20.frame_id = 2;
  Image img21; img21.frame_id = 2;
  Image img50; img50.frame_id = 5;
  Image img60; img60.frame_id = 6;
  images.emplace(10, img10);
  images.emplace(11, img11);
  images.emplace(12, img12);
  images.emplace(20, img20);
  images.emplace(21, img21);
  images.emplace(50, img50);
  images.emplace(60, img60);

  std::unordered_map<track_t, Track> tracks;

  // Strong covisibility between frames 1 and 2.
  Track strong_track;
  strong_track.observations.emplace_back(10, 0);
  strong_track.observations.emplace_back(20, 0);
  strong_track.observations.emplace_back(11, 0);
  strong_track.observations.emplace_back(21, 0);
  strong_track.observations.emplace_back(12, 0);
  tracks.emplace(1, strong_track);

  // Weak track with exactly two observations (should be ignored completely).
  Track weak_track;
  weak_track.observations.emplace_back(50, 0);  // frame 5
  weak_track.observations.emplace_back(60, 0);  // frame 6
  tracks.emplace(2, weak_track);

  const int kMinNumImages = 2;
  const int kMinNumObservations = 1;

  ViewGraphManipulater::last_result = 7;

  image_t result = PruneWeaklyConnectedImages(
      frames, images, tracks, kMinNumImages, kMinNumObservations);

  EXPECT_EQ(result, 7);
  EXPECT_EQ(ViewGraphManipulater::call_count, 1);

  const auto& graph = ViewGraphManipulater::last_graph;

  // Edge between begin images of frame 1 and 2 (10, 20) should exist.
  EXPECT_TRUE(HasEdge(graph, 10, 20));

  // Edge between begin images of frame 5 and 6 (50, 60) should NOT exist,
  // because the only track that could create it had size <= 2 and must be
  // ignored by the implementation.
  EXPECT_FALSE(HasEdge(graph, 50, 60));
}
