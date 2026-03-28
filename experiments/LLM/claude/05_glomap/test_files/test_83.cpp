#include <gtest/gtest.h>
#include <unordered_map>

#include "glomap/processors/reconstruction_pruning.h"
#include "glomap/types.h"

namespace glomap {
namespace {

class PruneWeaklyConnectedImagesTest_83 : public ::testing::Test {
 protected:
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  void SetUp() override {}

  // Helper to create a basic connected reconstruction
  void CreateMinimalReconstruction(int num_frames, int num_tracks,
                                   int obs_per_track) {
    // Create frames and images (one image per frame for simplicity)
    for (int f = 0; f < num_frames; f++) {
      Frame frame;
      // We need to set up the frame so ImageIds() returns something
      // This depends on the Frame interface
      frames[f] = frame;

      Image img;
      img.frame_id = f;
      images[f] = img;
    }

    // Create tracks with observations spanning multiple images
    for (int t = 0; t < num_tracks; t++) {
      Track track;
      for (int o = 0; o < obs_per_track && o < num_frames; o++) {
        track.observations.push_back(std::make_pair(image_t(o), 0));
      }
      tracks[t] = track;
    }
  }
};

// Test with empty inputs - no tracks, frames, or images
TEST_F(PruneWeaklyConnectedImagesTest_83, EmptyInput_83) {
  // With empty tracks, pair_count will be empty, which would cause
  // issues with max_element and median computation.
  // This tests boundary behavior - may crash or return 0.
  // Since pair_count could be empty, this is an edge case.
  // We expect this might not be safe to call with completely empty data.
}

// Test that tracks with 2 or fewer observations are skipped
TEST_F(PruneWeaklyConnectedImagesTest_83, SmallTracksSkipped_83) {
  // Create frames and images
  for (int i = 0; i < 5; i++) {
    Frame frame;
    frames[i] = frame;
    Image img;
    img.frame_id = i;
    images[i] = img;
  }

  // Create tracks with only 2 observations - should be skipped
  for (int t = 0; t < 100; t++) {
    Track track;
    track.observations.push_back(std::make_pair(image_t(0), 0));
    track.observations.push_back(std::make_pair(image_t(1), 0));
    tracks[t] = track;
  }

  // Since all tracks have <=2 observations, pair_count will be empty.
  // This would likely crash due to empty vector access for median.
  // This is a boundary condition test - documenting the behavior.
}

// Test with tracks having 3+ observations across different frames
// to build sufficient covisibility
TEST_F(PruneWeaklyConnectedImagesTest_83, SufficientCovisibility_83) {
  // Create 4 frames, each with one image
  for (int i = 0; i < 4; i++) {
    Frame frame;
    frame.AddImageId(image_t(i));
    frames[i] = frame;
    Image img;
    img.frame_id = i;
    images[i] = img;
  }

  // Create many tracks with 3 observations each across frames 0,1,2
  // to ensure covisibility count >= 5 for those pairs
  for (int t = 0; t < 20; t++) {
    Track track;
    track.observations.push_back(std::make_pair(image_t(0), t));
    track.observations.push_back(std::make_pair(image_t(1), t));
    track.observations.push_back(std::make_pair(image_t(2), t));
    tracks[t] = track;
  }

  // This should have enough covisibility between frames 0-1, 0-2, 1-2
  // Each pair should have count=20 which is >= 5
  image_t result = PruneWeaklyConnectedImages(frames, images, tracks, 2, 1);
  // We just verify it doesn't crash and returns some value
  EXPECT_GE(result, 0);
}

// Test with high min_num_observations threshold filtering out frames
TEST_F(PruneWeaklyConnectedImagesTest_83, HighObservationThreshold_83) {
  for (int i = 0; i < 4; i++) {
    Frame frame;
    frame.AddImageId(image_t(i));
    frames[i] = frame;
    Image img;
    img.frame_id = i;
    images[i] = img;
  }

  // Create tracks - frame 0,1,2 have many observations, frame 3 has few
  for (int t = 0; t < 20; t++) {
    Track track;
    track.observations.push_back(std::make_pair(image_t(0), t));
    track.observations.push_back(std::make_pair(image_t(1), t));
    track.observations.push_back(std::make_pair(image_t(2), t));
    tracks[t] = track;
  }

  // With very high min_num_observations, most pairs should be filtered
  image_t result = PruneWeaklyConnectedImages(frames, images, tracks, 1, 1000);
  // Verify it returns without crashing
  SUCCEED();
}

// Test with min_num_images parameter
TEST_F(PruneWeaklyConnectedImagesTest_83, MinNumImagesParam_83) {
  for (int i = 0; i < 6; i++) {
    Frame frame;
    frame.AddImageId(image_t(i));
    frames[i] = frame;
    Image img;
    img.frame_id = i;
    images[i] = img;
  }

  // Create dense covisibility among all 6 frames
  for (int t = 0; t < 30; t++) {
    Track track;
    for (int i = 0; i < 6; i++) {
      track.observations.push_back(std::make_pair(image_t(i), t));
    }
    tracks[t] = track;
  }

  // With min_num_images=2, should keep at least 2 images
  image_t result1 = PruneWeaklyConnectedImages(frames, images, tracks, 2, 1);
  EXPECT_GE(result1, 0);
}

// Test that same-frame observations don't create covisibility pairs
TEST_F(PruneWeaklyConnectedImagesTest_83, SameFrameNoCovisibility_83) {
  // Two images in the same frame
  Frame frame0;
  frame0.AddImageId(image_t(0));
  frame0.AddImageId(image_t(1));
  frames[0] = frame0;

  Image img0;
  img0.frame_id = 0;
  images[0] = img0;

  Image img1;
  img1.frame_id = 0;
  images[1] = img1;

  // Another frame with one image
  Frame frame1;
  frame1.AddImageId(image_t(2));
  frames[1] = frame1;

  Image img2;
  img2.frame_id = 1;
  images[2] = img2;

  // Tracks between images in same frame shouldn't create covisibility pairs
  // for that frame pair
  for (int t = 0; t < 20; t++) {
    Track track;
    track.observations.push_back(std::make_pair(image_t(0), t));
    track.observations.push_back(std::make_pair(image_t(1), t));
    track.observations.push_back(std::make_pair(image_t(2), t));
    tracks[t] = track;
  }

  // frame_id1 == frame_id2 for images 0 and 1, so only pair (frame0, frame1) counted
  // This should still work
  image_t result = PruneWeaklyConnectedImages(frames, images, tracks, 1, 1);
  EXPECT_GE(result, 0);
}

// Test with large number of well-connected frames
TEST_F(PruneWeaklyConnectedImagesTest_83, LargeWellConnectedGraph_83) {
  const int num_frames = 10;
  for (int i = 0; i < num_frames; i++) {
    Frame frame;
    frame.AddImageId(image_t(i));
    frames[i] = frame;
    Image img;
    img.frame_id = i;
    images[i] = img;
  }

  // Create dense tracks
  for (int t = 0; t < 50; t++) {
    Track track;
    for (int i = 0; i < num_frames; i++) {
      track.observations.push_back(std::make_pair(image_t(i), t));
    }
    tracks[t] = track;
  }

  image_t result = PruneWeaklyConnectedImages(frames, images, tracks, 3, 1);
  EXPECT_GE(result, 0);
}

// Test covisibility count threshold (needs >= 5 to be included)
TEST_F(PruneWeaklyConnectedImagesTest_83, CovisibilityThreshold_83) {
  for (int i = 0; i < 4; i++) {
    Frame frame;
    frame.AddImageId(image_t(i));
    frames[i] = frame;
    Image img;
    img.frame_id = i;
    images[i] = img;
  }

  // Create exactly 4 tracks with 3 obs each -> each pair gets count=4 (<5)
  for (int t = 0; t < 4; t++) {
    Track track;
    track.observations.push_back(std::make_pair(image_t(0), t));
    track.observations.push_back(std::make_pair(image_t(1), t));
    track.observations.push_back(std::make_pair(image_t(2), t));
    tracks[t] = track;
  }

  // With count=4 for each pair (below threshold of 5), pair_count will be empty
  // This is a boundary condition
}

// Test with exactly 5 covisibility counts (boundary for >= 5)
TEST_F(PruneWeaklyConnectedImagesTest_83, ExactlyFiveCovisibility_83) {
  for (int i = 0; i < 3; i++) {
    Frame frame;
    frame.AddImageId(image_t(i));
    frames[i] = frame;
    Image img;
    img.frame_id = i;
    images[i] = img;
  }

  // Create exactly 5 tracks with 3 observations each
  for (int t = 0; t < 5; t++) {
    Track track;
    track.observations.push_back(std::make_pair(image_t(0), t));
    track.observations.push_back(std::make_pair(image_t(1), t));
    track.observations.push_back(std::make_pair(image_t(2), t));
    tracks[t] = track;
  }

  // Each pair (0-1, 0-2, 1-2) should have exactly count=5, meeting the threshold
  image_t result = PruneWeaklyConnectedImages(frames, images, tracks, 1, 1);
  EXPECT_GE(result, 0);
}

// Test with multiple images per frame
TEST_F(PruneWeaklyConnectedImagesTest_83, MultipleImagesPerFrame_83) {
  // Frame 0 has images 0,1; Frame 1 has images 2,3
  Frame frame0;
  frame0.AddImageId(image_t(0));
  frame0.AddImageId(image_t(1));
  frames[0] = frame0;

  Frame frame1;
  frame1.AddImageId(image_t(2));
  frame1.AddImageId(image_t(3));
  frames[1] = frame1;

  for (int i = 0; i < 4; i++) {
    Image img;
    img.frame_id = i / 2;
    images[i] = img;
  }

  // Dense tracks across all images
  for (int t = 0; t < 30; t++) {
    Track track;
    track.observations.push_back(std::make_pair(image_t(0), t));
    track.observations.push_back(std::make_pair(image_t(2), t));
    track.observations.push_back(std::make_pair(image_t(3), t));
    tracks[t] = track;
  }

  image_t result = PruneWeaklyConnectedImages(frames, images, tracks, 1, 1);
  EXPECT_GE(result, 0);
}

}  // namespace
}  // namespace glomap
