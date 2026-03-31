#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_map>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "glomap/processors/track_filter.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/types.h"

namespace glomap {
namespace {

class TrackFilterTest_85 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up a simple camera with prior focal length
    Camera cam;
    cam.camera_id = 0;
    cam.has_prior_focal_length = true;
    cameras_[0] = cam;

    // Set up a camera without prior focal length
    Camera cam_uncalib;
    cam_uncalib.camera_id = 1;
    cam_uncalib.has_prior_focal_length = false;
    cameras_[1] = cam_uncalib;
  }

  // Helper to create an image at identity pose looking along +Z
  Image CreateIdentityImage(image_t id, camera_t cam_id) {
    Image img;
    img.image_id = id;
    img.camera_id = cam_id;
    // Set identity rotation and zero translation (looking along +Z)
    img.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(),
                                  Eigen::Vector3d::Zero());
    return img;
  }

  // Helper to create an image with a specific pose
  Image CreateImage(image_t id, camera_t cam_id,
                    const Eigen::Quaterniond& q,
                    const Eigen::Vector3d& t) {
    Image img;
    img.image_id = id;
    img.camera_id = cam_id;
    img.cam_from_world = Rigid3d(q, t);
    return img;
  }

  ViewGraph view_graph_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;
};

// Test with empty tracks map - should return 0
TEST_F(TrackFilterTest_85, EmptyTracks_85) {
  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 2.0);
  EXPECT_EQ(result, 0);
}

// Test with a track that has no observations - should count as filtered if empty != original
TEST_F(TrackFilterTest_85, TrackWithNoObservations_85) {
  Track track;
  track.xyz = Eigen::Vector3d(0, 0, 5);
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 2.0);
  EXPECT_EQ(result, 0);
  EXPECT_TRUE(tracks_[0].observations.empty());
}

// Test with a track whose observation projects well within the angle threshold
TEST_F(TrackFilterTest_85, SingleObservationWithinThreshold_85) {
  // Image at identity looking along +Z
  Image img = CreateIdentityImage(0, 0);

  // 3D point at (0, 0, 5) - directly in front
  Eigen::Vector3d pt(0, 0, 5);
  Eigen::Vector3d projected = pt.normalized();  // (0, 0, 1)

  // Feature undistorted matches the projected direction
  img.features_undist[0] = projected;
  images_[0] = img;

  Track track;
  track.xyz = pt;
  track.observations.emplace_back(0, 0);
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 2.0);
  // Observation should be kept, so no filtering
  EXPECT_EQ(result, 0);
  EXPECT_EQ(tracks_[0].observations.size(), 1u);
}

// Test with a track whose observation is beyond the angle threshold
TEST_F(TrackFilterTest_85, SingleObservationBeyondThreshold_85) {
  Image img = CreateIdentityImage(0, 0);

  // 3D point at (0, 0, 5)
  Eigen::Vector3d pt(0, 0, 5);

  // Feature undistorted is very different from projection direction
  // projected direction would be (0, 0, 1), but feature points sideways
  img.features_undist[0] = Eigen::Vector3d(1, 0, 0).normalized();
  images_[0] = img;

  Track track;
  track.xyz = pt;
  track.observations.emplace_back(0, 0);
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 2.0);
  // Observation should be removed
  EXPECT_EQ(result, 1);
  EXPECT_EQ(tracks_[0].observations.size(), 0u);
}

// Test with a point behind the camera (negative z after projection)
TEST_F(TrackFilterTest_85, PointBehindCamera_85) {
  Image img = CreateIdentityImage(0, 0);

  // 3D point behind the camera at (0, 0, -5)
  Eigen::Vector3d pt(0, 0, -5);

  img.features_undist[0] = Eigen::Vector3d(0, 0, -1).normalized();
  images_[0] = img;

  Track track;
  track.xyz = pt;
  track.observations.emplace_back(0, 0);
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 90.0);
  // Should be filtered because pt_calc(2) < EPS
  EXPECT_EQ(result, 1);
  EXPECT_EQ(tracks_[0].observations.size(), 0u);
}

// Test with uncalibrated camera uses doubled angle threshold
TEST_F(TrackFilterTest_85, UncalibratedCameraUsesDoubleThreshold_85) {
  Image img = CreateIdentityImage(0, 1);  // camera_id = 1 (uncalibrated)

  // 3D point at (0, 0, 5)
  Eigen::Vector3d pt(0, 0, 5);
  Eigen::Vector3d projected = pt.normalized();

  // Create a feature that is slightly off - within 2*max_angle but not within max_angle
  double angle_deg = 3.0;  // Use 3 degrees offset
  double angle_rad = angle_deg * M_PI / 180.0;
  Eigen::Vector3d feature(std::sin(angle_rad), 0, std::cos(angle_rad));
  feature.normalize();

  img.features_undist[0] = feature;
  images_[0] = img;

  Track track;
  track.xyz = pt;
  track.observations.emplace_back(0, 0);
  tracks_[0] = track;

  // With max_angle_error = 2.0, calibrated threshold = cos(2 deg), uncalibrated = cos(4 deg)
  // 3 deg offset: cos(3 deg) > cos(4 deg) => should pass for uncalibrated
  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 2.0);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(tracks_[0].observations.size(), 1u);
}

// Same angle but with calibrated camera should be filtered
TEST_F(TrackFilterTest_85, CalibratedCameraStricterThreshold_85) {
  Image img = CreateIdentityImage(0, 0);  // camera_id = 0 (calibrated)

  Eigen::Vector3d pt(0, 0, 5);

  // 3 degree offset - beyond 2 degree threshold for calibrated
  double angle_deg = 3.0;
  double angle_rad = angle_deg * M_PI / 180.0;
  Eigen::Vector3d feature(std::sin(angle_rad), 0, std::cos(angle_rad));
  feature.normalize();

  img.features_undist[0] = feature;
  images_[0] = img;

  Track track;
  track.xyz = pt;
  track.observations.emplace_back(0, 0);
  tracks_[0] = track;

  // With max_angle_error = 2.0, calibrated threshold = cos(2 deg)
  // 3 deg offset: cos(3 deg) < cos(2 deg) => should fail for calibrated
  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 2.0);
  EXPECT_EQ(result, 1);
  EXPECT_EQ(tracks_[0].observations.size(), 0u);
}

// Test multiple observations, some kept and some filtered
TEST_F(TrackFilterTest_85, MultipleObservationsPartialFilter_85) {
  // Image 0 - good observation
  Image img0 = CreateIdentityImage(0, 0);
  Eigen::Vector3d pt(0, 0, 5);
  img0.features_undist[0] = pt.normalized();
  images_[0] = img0;

  // Image 1 - bad observation (big angle error)
  Image img1 = CreateIdentityImage(1, 0);
  img1.features_undist[0] = Eigen::Vector3d(1, 0, 0).normalized();
  images_[1] = img1;

  Track track;
  track.xyz = pt;
  track.observations.emplace_back(0, 0);
  track.observations.emplace_back(1, 0);
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 2.0);
  EXPECT_EQ(result, 1);
  EXPECT_EQ(tracks_[0].observations.size(), 1u);
  EXPECT_EQ(tracks_[0].observations[0].first, 0);
}

// Test multiple tracks
TEST_F(TrackFilterTest_85, MultipleTracks_85) {
  Image img0 = CreateIdentityImage(0, 0);
  Eigen::Vector3d pt0(0, 0, 5);
  Eigen::Vector3d pt1(0, 0, -5);  // behind camera

  img0.features_undist[0] = pt0.normalized();
  img0.features_undist[1] = Eigen::Vector3d(0, 0, -1);
  images_[0] = img0;

  // Track 0: good observation
  Track track0;
  track0.xyz = pt0;
  track0.observations.emplace_back(0, 0);
  tracks_[0] = track0;

  // Track 1: point behind camera
  Track track1;
  track1.xyz = pt1;
  track1.observations.emplace_back(0, 1);
  tracks_[1] = track1;

  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 2.0);
  EXPECT_EQ(result, 1);
  EXPECT_EQ(tracks_[0].observations.size(), 1u);
  EXPECT_EQ(tracks_[1].observations.size(), 0u);
}

// Test with very large max_angle_error - all observations should pass
TEST_F(TrackFilterTest_85, LargeAngleThresholdKeepsAll_85) {
  Image img = CreateIdentityImage(0, 0);
  Eigen::Vector3d pt(0, 0, 5);

  // Even a large angle offset should pass with 90 degree threshold
  double angle_rad = 80.0 * M_PI / 180.0;
  Eigen::Vector3d feature(std::sin(angle_rad), 0, std::cos(angle_rad));
  feature.normalize();

  img.features_undist[0] = feature;
  images_[0] = img;

  Track track;
  track.xyz = pt;
  track.observations.emplace_back(0, 0);
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 90.0);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(tracks_[0].observations.size(), 1u);
}

// Test with zero angle threshold - only exact matches pass
TEST_F(TrackFilterTest_85, ZeroAngleThreshold_85) {
  Image img = CreateIdentityImage(0, 0);
  Eigen::Vector3d pt(0, 0, 5);

  // Perfect match
  img.features_undist[0] = pt.normalized();
  images_[0] = img;

  Track track;
  track.xyz = pt;
  track.observations.emplace_back(0, 0);
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 0.0);
  // cos(0) = 1.0, and pt_calc.dot(feature) should be exactly 1.0
  // This should pass
  EXPECT_EQ(result, 0);
  EXPECT_EQ(tracks_[0].observations.size(), 1u);
}

// Test that all observations are kept when none change
TEST_F(TrackFilterTest_85, NoFilteringReturnsZero_85) {
  Image img0 = CreateIdentityImage(0, 0);
  Image img1 = CreateIdentityImage(1, 0);

  Eigen::Vector3d pt(0, 0, 10);
  img0.features_undist[0] = pt.normalized();
  img1.features_undist[0] = pt.normalized();
  images_[0] = img0;
  images_[1] = img1;

  Track track;
  track.xyz = pt;
  track.observations.emplace_back(0, 0);
  track.observations.emplace_back(1, 0);
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 5.0);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(tracks_[0].observations.size(), 2u);
}

// Test with a non-identity camera pose
TEST_F(TrackFilterTest_85, NonIdentityCameraPose_85) {
  // Camera rotated 180 degrees around Y axis, looking along -Z
  Eigen::Quaterniond q(Eigen::AngleAxisd(M_PI, Eigen::Vector3d::UnitY()));
  Image img = CreateImage(0, 0, q, Eigen::Vector3d::Zero());

  // Point at (0, 0, -5) in world coords -> (0, 0, 5) in camera coords
  Eigen::Vector3d pt(0, 0, -5);
  Eigen::Vector3d projected = (q.toRotationMatrix() * pt).normalized();

  img.features_undist[0] = projected;
  images_[0] = img;

  Track track;
  track.xyz = pt;
  track.observations.emplace_back(0, 0);
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 2.0);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(tracks_[0].observations.size(), 1u);
}

// Test boundary: observation exactly at threshold angle
TEST_F(TrackFilterTest_85, ObservationExactlyAtThreshold_85) {
  Image img = CreateIdentityImage(0, 0);
  Eigen::Vector3d pt(0, 0, 5);

  // Feature at exactly 2 degrees from projected direction
  double angle_rad = 2.0 * M_PI / 180.0;
  Eigen::Vector3d feature(std::sin(angle_rad), 0, std::cos(angle_rad));
  feature.normalize();

  img.features_undist[0] = feature;
  images_[0] = img;

  Track track;
  track.xyz = pt;
  track.observations.emplace_back(0, 0);
  tracks_[0] = track;

  // At exactly threshold: dot product = cos(2 deg), threshold = cos(2 deg)
  // The condition is strictly >, so exactly at threshold should be filtered
  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 2.0);
  // Since it's strict inequality (>), exact threshold should NOT pass
  EXPECT_EQ(result, 1);
  EXPECT_EQ(tracks_[0].observations.size(), 0u);
}

// Test return value counts only tracks that changed
TEST_F(TrackFilterTest_85, ReturnValueCountsOnlyChangedTracks_85) {
  Image img0 = CreateIdentityImage(0, 0);
  Eigen::Vector3d pt(0, 0, 5);

  img0.features_undist[0] = pt.normalized();
  img0.features_undist[1] = Eigen::Vector3d(1, 0, 0).normalized();  // bad
  images_[0] = img0;

  // Track 0: all good
  Track track0;
  track0.xyz = pt;
  track0.observations.emplace_back(0, 0);
  tracks_[0] = track0;

  // Track 1: all bad
  Track track1;
  track1.xyz = pt;
  track1.observations.emplace_back(0, 1);
  tracks_[1] = track1;

  // Track 2: all good
  Track track2;
  track2.xyz = pt;
  track2.observations.emplace_back(0, 0);
  tracks_[2] = track2;

  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 2.0);
  EXPECT_EQ(result, 1);  // Only track 1 changed
}

}  // namespace
}  // namespace glomap
