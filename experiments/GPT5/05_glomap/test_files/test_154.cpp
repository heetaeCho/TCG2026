// File: track_filter_test_154.cc

#include <gtest/gtest.h>

#include "glomap/processors/track_filter.h"
#include "glomap/scene/image.h"
#include "glomap/scene/track.h"
#include "glomap/scene/view_graph.h"
#include "glomap/types.h"

#include <Eigen/Core>
#include <unordered_map>
#include <vector>

namespace glomap {

class TrackFilterTest_154 : public ::testing::Test {
 protected:
  ViewGraph view_graph_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;
};

//------------------------------------------------------------------------------
// 1) Empty input
//------------------------------------------------------------------------------

TEST_F(TrackFilterTest_154, ReturnsZeroWhenNoTracks_154) {
  const double kMaxReprojError = 1.0;
  const bool kInNormalizedImage = true;

  const int num_filtered = TrackFilter::FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, kMaxReprojError,
      kInNormalizedImage);

  EXPECT_EQ(num_filtered, 0);
  EXPECT_TRUE(tracks_.empty());
}

//------------------------------------------------------------------------------
// 2) Track with no observations: should not be counted or modified
//------------------------------------------------------------------------------

TEST_F(TrackFilterTest_154, TrackWithoutObservationsIsNotCounted_154) {
  const track_t track_id = 1;
  Track track;
  track.track_id = track_id;
  // No observations added.
  tracks_[track_id] = track;

  const double kMaxReprojError = 1.0;
  const bool kInNormalizedImage = true;

  const int num_filtered = TrackFilter::FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, kMaxReprojError,
      kInNormalizedImage);

  EXPECT_EQ(num_filtered, 0);
  ASSERT_EQ(tracks_.size(), 1u);
  EXPECT_TRUE(tracks_.at(track_id).observations.empty());
}

//------------------------------------------------------------------------------
// 3) Normal operation (in_normalized_image = true):
//    One track, two observations; one within threshold, one outside.
//    Track should be updated and counted once.
//------------------------------------------------------------------------------

TEST_F(TrackFilterTest_154,
       NormalizedImage_RemovesObservationAboveThreshold_154) {
  const image_t image_id = 1;
  const camera_t camera_id = 1;

  // Create image with undistorted features.
  Image image(image_id, camera_id, "image_1");
  // Two undistorted feature points:
  //  - feature 0: near the expected projection
  //  - feature 1: far from the expected projection
  image.features_undist.clear();
  image.features_undist.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));   // id 0
  image.features_undist.push_back(Eigen::Vector3d(10.0, 0.0, 1.0));  // id 1
  images_[image_id] = image;

  // Single 3D point; Image::CamFromWorld() is treated as a black box.
  Track track;
  const track_t track_id = 10;
  track.track_id = track_id;
  track.xyz = Eigen::Vector3d(0.0, 0.0, 1.0);
  // Two observations in the same image with different feature ids.
  track.observations.emplace_back(image_id, feature_t(0));
  track.observations.emplace_back(image_id, feature_t(1));
  tracks_[track_id] = track;

  const double kMaxReprojError = 1.0;
  const bool kInNormalizedImage = true;

  const int num_filtered = TrackFilter::FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, kMaxReprojError,
      kInNormalizedImage);

  // Exactly one track should be counted as filtered (its observations changed).
  EXPECT_EQ(num_filtered, 1);

  ASSERT_EQ(tracks_.count(track_id), 1u);
  const Track& filtered_track = tracks_.at(track_id);

  // One observation should remain.
  ASSERT_EQ(filtered_track.observations.size(), 1u);
  // We expect the low-error observation (feature_id = 0) to be kept.
  EXPECT_EQ(filtered_track.observations[0].first, image_id);
  EXPECT_EQ(filtered_track.observations[0].second, feature_t(0));
}

//------------------------------------------------------------------------------
// 4) Normal operation (in_normalized_image = true):
//    All observations within threshold -> track should NOT be counted.
//------------------------------------------------------------------------------

TEST_F(TrackFilterTest_154,
       NormalizedImage_TrackUnchangedWhenAllWithinThreshold_154) {
  const image_t image_id = 2;
  const camera_t camera_id = 2;

  Image image(image_id, camera_id, "image_2");
  image.features_undist.clear();
  // Both features relatively close in normalized space.
  image.features_undist.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));   // id 0
  image.features_undist.push_back(Eigen::Vector3d(0.1, 0.0, 1.0));   // id 1
  images_[image_id] = image;

  Track track;
  const track_t track_id = 20;
  track.track_id = track_id;
  track.xyz = Eigen::Vector3d(0.0, 0.0, 1.0);
  track.observations.emplace_back(image_id, feature_t(0));
  track.observations.emplace_back(image_id, feature_t(1));
  const auto original_observations = track.observations;

  tracks_[track_id] = track;

  const double kMaxReprojError = 5.0;  // Large enough to keep both.
  const bool kInNormalizedImage = true;

  const int num_filtered = TrackFilter::FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, kMaxReprojError,
      kInNormalizedImage);

  // Track should not be counted as filtered since its observation set is
  // unchanged.
  EXPECT_EQ(num_filtered, 0);

  ASSERT_EQ(tracks_.count(track_id), 1u);
  const Track& filtered_track = tracks_.at(track_id);

  ASSERT_EQ(filtered_track.observations.size(), original_observations.size());
  for (size_t i = 0; i < original_observations.size(); ++i) {
    EXPECT_EQ(filtered_track.observations[i].first,
              original_observations[i].first);
    EXPECT_EQ(filtered_track.observations[i].second,
              original_observations[i].second);
  }
}

}  // namespace glomap
