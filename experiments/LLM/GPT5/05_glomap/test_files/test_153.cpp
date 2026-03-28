// File: reconstruction_pruning_test_153.cc

#include <gtest/gtest.h>

#include <unordered_map>
#include <vector>

#include "glomap/scene/image.h"
#include "glomap/scene/track.h"
#include "glomap/scene/frame.h"
#include "glomap/processors/view_graph_manipulation.h"
#include "glomap/processors/reconstruction_pruning.h"

namespace glomap {

// Forward declaration in case it is only declared in the .cc file.
image_t PruneWeaklyConnectedImages(std::unordered_map<frame_t, Frame>& frames,
                                   std::unordered_map<image_t, Image>& images,
                                   std::unordered_map<track_t, Track>& tracks,
                                   int min_num_images,
                                   int min_num_observations);

// Simple fixture to share a basic consistent reconstruction setting.
class PruneWeaklyConnectedImagesTest_153 : public ::testing::Test {
 protected:
  std::unordered_map<frame_t, Frame> frames_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;

  void SetUp() override {
    // Create two frames. We keep them otherwise default; we do not depend
    // on any internal state of Frame, only that it is default constructible.
    const frame_t kFrame1 = static_cast<frame_t>(1);
    const frame_t kFrame2 = static_cast<frame_t>(2);
    frames_.emplace(kFrame1, Frame());
    frames_.emplace(kFrame2, Frame());

    // Create two images, each associated with a different frame.
    // Only frame_id is needed by PruneWeaklyConnectedImages.
    const image_t kImage1 = static_cast<image_t>(1);
    const image_t kImage2 = static_cast<image_t>(2);

    {
      Image img1;
      img1.frame_id = kFrame1;
      images_.emplace(kImage1, img1);
    }
    {
      Image img2;
      img2.frame_id = kFrame2;
      images_.emplace(kImage2, img2);
    }

    // Build several tracks that observe the same image pair in order to
    // guarantee that covisibility counts reach the ">= 5" threshold used
    // inside PruneWeaklyConnectedImages.
    //
    // Each track has more than two observations to pass the "size() <= 2"
    // check and contributes multiple co-visibility counts for the same
    // pair of frames.
    for (int t = 0; t < 5; ++t) {
      Track track;
      // Observation: typedef std::pair<image_t, feature_t> Observation;
      const feature_t kFeat0 = static_cast<feature_t>(0);
      const feature_t kFeat1 = static_cast<feature_t>(1);

      // Make sure there are at least three observations per track.
      track.observations.emplace_back(kImage1, kFeat0);
      track.observations.emplace_back(kImage2, kFeat0);
      track.observations.emplace_back(kImage1, kFeat1);

      tracks_.emplace(static_cast<track_t>(t), track);
    }
  }
};

// Normal operation: for a stable reconstruction configuration, calling
// PruneWeaklyConnectedImages with the same inputs should be deterministic.
TEST_F(PruneWeaklyConnectedImagesTest_153,
       DeterministicOutputForSameInputs_153) {
  const int kMinNumImages = 1;
  const int kMinNumObservations = 1;

  image_t result1 =
      PruneWeaklyConnectedImages(frames_, images_, tracks_, kMinNumImages,
                                 kMinNumObservations);
  image_t result2 =
      PruneWeaklyConnectedImages(frames_, images_, tracks_, kMinNumImages,
                                 kMinNumObservations);

  // Black-box property: same inputs -> same output.
  EXPECT_EQ(result1, result2);
}

// Boundary-ish condition: use a larger but still valid observation threshold
// that keeps at least one image pair above the internal co-visibility limits.
// The function is expected not to throw and remain deterministic for that
// configuration as well.
TEST_F(PruneWeaklyConnectedImagesTest_153,
       HandlesHigherObservationThresholdDeterministically_153) {
  // In SetUp, each frame is observed multiple times across tracks.
  // Here we pick a threshold that is smaller or equal to the smaller
  // observation count of the two frames to avoid removing all pairs.
  const int kMinNumImages = 1;
  const int kMinNumObservations = 3;

  image_t result1 =
      PruneWeaklyConnectedImages(frames_, images_, tracks_, kMinNumImages,
                                 kMinNumObservations);
  image_t result2 =
      PruneWeaklyConnectedImages(frames_, images_, tracks_, kMinNumImages,
                                 kMinNumObservations);

  EXPECT_EQ(result1, result2);
}

// Boundary / robustness test: add a track that does NOT satisfy the internal
// constraints (e.g., has too few observations) and verify that the function
// still behaves well from the outside (no exception, deterministic output).
TEST_F(PruneWeaklyConnectedImagesTest_153,
       IgnoresTracksWithTooFewObservationsWithoutCrashing_153) {
  // Create local copies so we can tweak without affecting other tests.
  auto frames = frames_;
  auto images = images_;
  auto tracks = tracks_;

  // Add a track with only two observations; according to the implementation,
  // such tracks should be ignored when building co-visibility.
  const image_t kImage1 = static_cast<image_t>(1);
  const image_t kImage2 = static_cast<image_t>(2);
  const feature_t kFeat0 = static_cast<feature_t>(0);

  Track short_track;
  short_track.observations.emplace_back(kImage1, kFeat0);
  short_track.observations.emplace_back(kImage2, kFeat0);
  tracks.emplace(static_cast<track_t>(999), short_track);

  const int kMinNumImages = 1;
  const int kMinNumObservations = 1;

  // Black-box expectations: the function should not throw and should
  // produce deterministic results for the same inputs.
  image_t result1 =
      PruneWeaklyConnectedImages(frames, images, tracks, kMinNumImages,
                                 kMinNumObservations);
  image_t result2 =
      PruneWeaklyConnectedImages(frames, images, tracks, kMinNumImages,
                                 kMinNumObservations);

  EXPECT_EQ(result1, result2);
}

}  // namespace glomap
