// track_filter_test_85.cc
//
// Unit tests for glomap::TrackFilter::FilterTracksByAngle.
// TEST_ID = 85

#include <unordered_map>

#include <gtest/gtest.h>

#include "glomap/processors/track_filter.h"

namespace {

using glomap::TrackFilter;
using glomap::ViewGraph;
using glomap::Camera;
using glomap::Image;
using glomap::Track;
using glomap::camera_t;
using glomap::image_t;
using glomap::track_t;

// Common fixture for TrackFilter tests (ID: 85)
class TrackFilterTest_85 : public ::testing::Test {
 protected:
  TrackFilter track_filter_;
  ViewGraph view_graph_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;
};

//------------------------------------------------------------------------------
// 1. Empty input
//------------------------------------------------------------------------------

TEST_F(TrackFilterTest_85, EmptyTracksReturnsZero_85) {
  const double kMaxAngleErrorDeg = 10.0;

  const int filtered = track_filter_.FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, kMaxAngleErrorDeg);

  EXPECT_EQ(filtered, 0);
  EXPECT_TRUE(tracks_.empty());
}

//------------------------------------------------------------------------------
// 2. Track present but with no observations
//    (loop body is never entered, so nothing should be modified)
//------------------------------------------------------------------------------

TEST_F(TrackFilterTest_85, TrackWithNoObservationsNotModified_85) {
  const double kMaxAngleErrorDeg = 10.0;

  const track_t track_id = static_cast<track_t>(1);
  Track empty_track;  // Default-constructed; observations should be empty.
  tracks_.emplace(track_id, empty_track);

  const int filtered = track_filter_.FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, kMaxAngleErrorDeg);

  EXPECT_EQ(filtered, 0);
  ASSERT_EQ(tracks_.size(), 1u);

  // We only rely on the public interface suggested by the implementation:
  EXPECT_EQ(tracks_.at(track_id).observations.size(), 0u);
}

//------------------------------------------------------------------------------
// 3. Error case: observation refers to an image that is not in the images map.
//    The implementation uses images.at(image_id), which should throw.
//------------------------------------------------------------------------------

TEST_F(TrackFilterTest_85, ThrowsIfImageMissing_85) {
  const double kMaxAngleErrorDeg = 10.0;

  const track_t track_id = static_cast<track_t>(1);
  const image_t image_id = static_cast<image_t>(10);
  const std::size_t feature_id = 0;

  Track track;
  // observations is a std::vector<Observation>-like container;
  // Observation is constructible from (image_t, feature_id).
  track.observations.emplace_back(image_id, feature_id);

  tracks_.emplace(track_id, track);

  EXPECT_THROW(
      {
        (void)track_filter_.FilterTracksByAngle(
            view_graph_, cameras_, images_, tracks_, kMaxAngleErrorDeg);
      },
      std::out_of_range);
}

//------------------------------------------------------------------------------
// 4. Error case: image exists but feature index/key is missing in features_undist.
//    The implementation uses image.features_undist.at(feature_id), which
//    should throw std::out_of_range when the feature is not present.
//------------------------------------------------------------------------------

TEST_F(TrackFilterTest_85, ThrowsIfFeatureMissing_85) {
  const double kMaxAngleErrorDeg = 10.0;

  const track_t track_id = static_cast<track_t>(1);
  const image_t image_id = static_cast<image_t>(5);
  const std::size_t feature_id = 42;

  // Insert an image but do NOT populate its features_undist for feature_id.
  images_.emplace(image_id, Image());

  Track track;
  track.observations.emplace_back(image_id, feature_id);
  tracks_.emplace(track_id, track);

  EXPECT_THROW(
      {
        (void)track_filter_.FilterTracksByAngle(
            view_graph_, cameras_, images_, tracks_, kMaxAngleErrorDeg);
      },
      std::out_of_range);
}

}  // namespace
