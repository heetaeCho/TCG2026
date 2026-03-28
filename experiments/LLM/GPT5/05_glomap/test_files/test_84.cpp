// File: track_filter_test_84.cc

#include <unordered_map>

#include <gtest/gtest.h>

#include "glomap/processors/track_filter.h"
// The following includes are guesses based on typical glomap layout.
// Adjust them as needed to match the real project structure.
#include "glomap/scene/view_graph.h"
#include "glomap/scene/track.h"
#include "glomap/scene/image.h"
#include "glomap/scene/camera.h"

namespace glomap {

class TrackFilterTest_84 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Default-constructed members are fine; we will populate as needed.
  }

  // Helper to add a simple image with one feature / undistorted feature.
  void AddImage(image_t image_id,
                camera_t camera_id,
                const Eigen::Vector3d& feature_undist,
                const Eigen::Vector2d& feature_dist = Eigen::Vector2d::Zero()) {
    Image image;
    image.camera_id = camera_id;

    // Ensure index 0 exists.
    if (image.features_undist.size() < 1) {
      image.features_undist.resize(1);
    }
    image.features_undist[0] = feature_undist;

    if (image.features.size() < 1) {
      image.features.resize(1);
    }
    image.features[0] = feature_dist;

    images_.emplace(image_id, image);
  }

  // Helper to add a track with a single observation (image_id, feature_id=0).
  void AddTrack(track_t track_id, const Eigen::Vector3d& xyz, image_t image_id) {
    Track track;
    track.xyz = xyz;
    track.observations.clear();
    track.observations.emplace_back(image_id, feature_t(0));
    tracks_.emplace(track_id, track);
  }

  TrackFilter track_filter_;
  ViewGraph view_graph_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;
};

// TEST_ID = 84

// No tracks: should return 0 and leave containers unchanged.
TEST_F(TrackFilterTest_84, NoTracksReturnsZero_84) {
  const double kMaxReprojError = 1.0;
  const bool kInNormalizedImage = true;

  ASSERT_TRUE(tracks_.empty());

  int num_filtered = track_filter_.FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, kMaxReprojError,
      kInNormalizedImage);

  EXPECT_EQ(num_filtered, 0);
  EXPECT_TRUE(tracks_.empty());
}

// All observations within threshold in normalized-image mode: nothing filtered.
TEST_F(TrackFilterTest_84,
       NormalizedImage_AllObservationsKeptWithinThreshold_84) {
  const camera_t kCameraId = camera_t(1);
  const image_t kImageId = image_t(1);
  const track_t kTrackId = track_t(1);

  // One camera (not actually used in normalized-image branch).
  cameras_.emplace(kCameraId, Camera());

  // Choose a 3D point in front of the camera.
  Eigen::Vector3d xyz(0.0, 0.0, 1.0);

  // For normalized-image branch, reprojection error is based on:
  //   pt_reproj = (x/z, y/z)
  //   normalized_feature = feature_undist.head(2) / (feature_undist(2) + EPS)
  // If we set feature_undist = (0,0,1) and xyz = (0,0,1), both become (0,0).
  Eigen::Vector3d feature_undist(0.0, 0.0, 1.0);

  AddImage(kImageId, kCameraId, feature_undist);
  AddTrack(kTrackId, xyz, kImageId);

  const double kMaxReprojError = 1.0;
  const bool kInNormalizedImage = true;

  int num_filtered = track_filter_.FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, kMaxReprojError,
      kInNormalizedImage);

  // No tracks should be reported as filtered.
  EXPECT_EQ(num_filtered, 0);
  ASSERT_EQ(tracks_.count(kTrackId), 1u);
  EXPECT_EQ(tracks_.at(kTrackId).observations.size(), 1u);
}

// Some observations exceed threshold in normalized-image mode: track shrinks.
TEST_F(TrackFilterTest_84,
       NormalizedImage_ObservationsRemovedWhenErrorTooLarge_84) {
  const camera_t kCameraId = camera_t(1);
  const image_t kImageId = image_t(1);
  const track_t kTrackId = track_t(1);

  cameras_.emplace(kCameraId, Camera());

  // Point in front of camera.
  Eigen::Vector3d xyz(0.0, 0.0, 1.0);

  // Make the undistorted feature far enough from the projected point so that
  // the reprojection error is large.
  Eigen::Vector3d feature_undist(10.0, 0.0, 1.0);

  AddImage(kImageId, kCameraId, feature_undist);
  AddTrack(kTrackId, xyz, kImageId);

  const double kMaxReprojError = 1.0;
  const bool kInNormalizedImage = true;

  int num_filtered = track_filter_.FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, kMaxReprojError,
      kInNormalizedImage);

  // The single track should have had its observations changed, so counter == 1.
  EXPECT_EQ(num_filtered, 1);
  ASSERT_EQ(tracks_.count(kTrackId), 1u);
  EXPECT_EQ(tracks_.at(kTrackId).observations.size(), 0u);
}

// Points with z < EPS (behind or on the camera plane) are skipped, so
// observations get removed and the track is counted as filtered.
TEST_F(TrackFilterTest_84, NormalizedImage_PointBehindCameraIsRemoved_84) {
  const camera_t kCameraId = camera_t(1);
  const image_t kImageId = image_t(1);
  const track_t kTrackId = track_t(1);

  cameras_.emplace(kCameraId, Camera());

  // Choose a point whose projected z will be very small (e.g., zero).
  Eigen::Vector3d xyz(0.0, 0.0, 0.0);

  // Feature values don't really matter here, since the point is discarded
  // before reprojection is computed.
  Eigen::Vector3d feature_undist(0.0, 0.0, 1.0);

  AddImage(kImageId, kCameraId, feature_undist);
  AddTrack(kTrackId, xyz, kImageId);

  const double kMaxReprojError = 1.0;
  const bool kInNormalizedImage = true;

  int num_filtered = track_filter_.FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, kMaxReprojError,
      kInNormalizedImage);

  // The track's observation should be dropped because pt_calc(2) < EPS.
  EXPECT_EQ(num_filtered, 1);
  ASSERT_EQ(tracks_.count(kTrackId), 1u);
  EXPECT_TRUE(tracks_.at(kTrackId).observations.empty());
}

// Distorted-image branch: uses cameras + image.features; verify behavior for
// small vs large reprojection error.
TEST_F(TrackFilterTest_84,
       DistortedImage_UsesCameraAndFeaturesToFilter_84) {
  const camera_t kCameraId = camera_t(1);
  const image_t kImageId = image_t(1);
  const track_t kTrackId = track_t(1);

  // Default camera; ImgFromCam may return std::nullopt, in which case
  // TrackFilter uses Eigen::Vector2d::Zero().
  cameras_.emplace(kCameraId, Camera());

  // Point in front of camera.
  Eigen::Vector3d xyz(0.0, 0.0, 1.0);

  // First, set the measured feature to be at (0,0) so that, if ImgFromCam
  // produces (0,0) (or nullopt -> Zero), reprojection error is small.
  Eigen::Vector3d feature_undist(0.0, 0.0, 1.0);  // not used in this branch
  Eigen::Vector2d feature_dist_small(0.0, 0.0);

  AddImage(kImageId, kCameraId, feature_undist, feature_dist_small);
  AddTrack(kTrackId, xyz, kImageId);

  const double kMaxReprojError = 1.0;
  const bool kInNormalizedImage = false;

  // First call: reprojection error expected to be small -> keep observation.
  int num_filtered_small = track_filter_.FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, kMaxReprojError,
      kInNormalizedImage);

  EXPECT_EQ(num_filtered_small, 0);
  ASSERT_EQ(tracks_.count(kTrackId), 1u);
  ASSERT_EQ(tracks_.at(kTrackId).observations.size(), 1u);

  // Now make the measured feature far from the projected point so that the
  // reprojection error is large, triggering removal.
  images_.at(kImageId).features[0] = Eigen::Vector2d(10.0, 0.0);

  int num_filtered_large = track_filter_.FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, kMaxReprojError,
      kInNormalizedImage);

  EXPECT_EQ(num_filtered_large, 1);
  ASSERT_EQ(tracks_.count(kTrackId), 1u);
  EXPECT_TRUE(tracks_.at(kTrackId).observations.empty());
}

}  // namespace glomap
