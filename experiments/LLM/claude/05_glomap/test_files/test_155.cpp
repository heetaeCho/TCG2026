#include <gtest/gtest.h>
#include "glomap/processors/track_filter.h"
#include "glomap/scene/types.h"
#include "glomap/types.h"

#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace glomap {
namespace {

// Helper to create an Image with identity pose (camera at origin looking along +Z)
Image CreateImageAtOrigin(image_t img_id, camera_t cam_id) {
  Image img(img_id, cam_id, "test.jpg");
  // We need to set the pose to identity so CamFromWorld() returns identity
  // The Image likely stores a Rigid3d internally; we need to figure out how to set it.
  // Based on the interface, Image has CamFromWorld() returning Rigid3d.
  // We'll assume default construction gives identity transform.
  return img;
}

class TrackFilterByAngleTest_155 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up a default camera with prior focal length
    Camera cam;
    cam.camera_id = 0;
    cam.has_prior_focal_length = true;
    cameras_[0] = cam;

    // Set up a camera without prior focal length
    Camera cam_no_prior;
    cam_no_prior.camera_id = 1;
    cam_no_prior.has_prior_focal_length = false;
    cameras_[1] = cam_no_prior;
  }

  ViewGraph view_graph_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;
};

// Test with empty tracks map - should return 0 and not crash
TEST_F(TrackFilterByAngleTest_155, EmptyTracks_155) {
  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 2.0);
  EXPECT_EQ(result, 0);
  EXPECT_TRUE(tracks_.empty());
}

// Test with a track that has no observations - should count as filtered if size changes (0 == 0 means no change)
TEST_F(TrackFilterByAngleTest_155, TrackWithNoObservations_155) {
  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(0, 0, 5);
  // No observations
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 2.0);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(tracks_[0].observations.size(), 0);
}

// Test where track point is directly along the viewing direction - observation should be kept
TEST_F(TrackFilterByAngleTest_155, TrackAlignedWithViewingDirection_155) {
  // Create image at origin with identity pose
  Image img(0, 0, "test.jpg");
  // The point is at (0, 0, 5) in world coords.
  // With identity CamFromWorld, the point in camera frame is (0, 0, 5).
  // Normalized: (0, 0, 1).
  // The undistorted feature should also be (0, 0, 1) for a perfect match.
  img.features_undist.push_back(Eigen::Vector3d(0, 0, 1).normalized());
  images_[0] = img;

  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(0, 0, 5);
  track.observations.push_back(std::make_pair(image_t(0), feature_t(0)));
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 2.0);
  // Perfect alignment, should keep the observation
  EXPECT_EQ(tracks_[0].observations.size(), 1);
  EXPECT_EQ(result, 0);
}

// Test where the track point is behind the camera (negative Z) - observation should be removed
TEST_F(TrackFilterByAngleTest_155, TrackBehindCamera_155) {
  Image img(0, 0, "test.jpg");
  img.features_undist.push_back(Eigen::Vector3d(0, 0, 1).normalized());
  images_[0] = img;

  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(0, 0, -5);  // Behind camera
  track.observations.push_back(std::make_pair(image_t(0), feature_t(0)));
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 2.0);
  // Point is behind camera, should be filtered
  EXPECT_EQ(tracks_[0].observations.size(), 0);
  EXPECT_EQ(result, 1);
}

// Test with a large angle error that keeps everything
TEST_F(TrackFilterByAngleTest_155, LargeAngleThresholdKeepsAll_155) {
  Image img(0, 0, "test.jpg");
  // Feature direction is slightly off from the track point projection
  img.features_undist.push_back(Eigen::Vector3d(0.1, 0.1, 1).normalized());
  images_[0] = img;

  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(0, 0, 5);
  track.observations.push_back(std::make_pair(image_t(0), feature_t(0)));
  tracks_[0] = track;

  // Very large angle tolerance - should keep everything
  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 90.0);
  EXPECT_EQ(tracks_[0].observations.size(), 1);
  EXPECT_EQ(result, 0);
}

// Test with a very small angle error that filters everything with slight misalignment
TEST_F(TrackFilterByAngleTest_155, SmallAngleThresholdFiltersOff_155) {
  Image img(0, 0, "test.jpg");
  // Feature direction is significantly off
  img.features_undist.push_back(Eigen::Vector3d(1, 1, 1).normalized());
  images_[0] = img;

  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(0, 0, 5);
  track.observations.push_back(std::make_pair(image_t(0), feature_t(0)));
  tracks_[0] = track;

  // Very small angle tolerance
  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 0.001);
  EXPECT_EQ(tracks_[0].observations.size(), 0);
  EXPECT_EQ(result, 1);
}

// Test with uncalibrated camera (no prior focal length) - uses 2x angle threshold
TEST_F(TrackFilterByAngleTest_155, UncalibratedCameraUsesDoubleThreshold_155) {
  Image img(0, 1, "test.jpg");  // camera_id = 1, which has no prior
  // Slightly off feature direction
  img.features_undist.push_back(Eigen::Vector3d(0.05, 0.0, 1.0).normalized());
  images_[0] = img;

  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(0, 0, 5);
  track.observations.push_back(std::make_pair(image_t(0), feature_t(0)));
  tracks_[0] = track;

  // Use a threshold where:
  // - calibrated threshold (max_angle_error) might filter it
  // - uncalibrated threshold (2 * max_angle_error) keeps it
  // The angle between (0, 0, 1) and (0.05, 0, 1).normalized() is about 2.86 degrees
  // Set threshold to 2.0 degrees -> calibrated cos(2) = 0.9994, uncalib cos(4) = 0.9976
  // dot product of (0,0,1) and normalized(0.05,0,1) ≈ 0.99875
  // 0.99875 < cos(2deg) = 0.9994? No, 0.99875 < 0.9994 => filtered for calibrated
  // 0.99875 > cos(4deg) = 0.9976? Yes => kept for uncalibrated
  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 2.0);
  EXPECT_EQ(tracks_[0].observations.size(), 1);
  EXPECT_EQ(result, 0);
}

// Test with calibrated camera that would filter the same observation
TEST_F(TrackFilterByAngleTest_155, CalibratedCameraUsesStrictThreshold_155) {
  Image img(0, 0, "test.jpg");  // camera_id = 0, which has prior
  img.features_undist.push_back(Eigen::Vector3d(0.05, 0.0, 1.0).normalized());
  images_[0] = img;

  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(0, 0, 5);
  track.observations.push_back(std::make_pair(image_t(0), feature_t(0)));
  tracks_[0] = track;

  // Same setup as above but with calibrated camera - should be filtered
  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 2.0);
  EXPECT_EQ(tracks_[0].observations.size(), 0);
  EXPECT_EQ(result, 1);
}

// Test multiple tracks, some filtered, some not
TEST_F(TrackFilterByAngleTest_155, MultipleTracks_155) {
  Image img(0, 0, "test.jpg");
  img.features_undist.push_back(Eigen::Vector3d(0, 0, 1).normalized());  // feature 0: perfect alignment
  img.features_undist.push_back(Eigen::Vector3d(1, 1, 1).normalized());  // feature 1: large angle
  images_[0] = img;

  // Track 0: good alignment
  Track track0;
  track0.track_id = 0;
  track0.xyz = Eigen::Vector3d(0, 0, 5);
  track0.observations.push_back(std::make_pair(image_t(0), feature_t(0)));
  tracks_[0] = track0;

  // Track 1: bad alignment
  Track track1;
  track1.track_id = 1;
  track1.xyz = Eigen::Vector3d(0, 0, 5);
  track1.observations.push_back(std::make_pair(image_t(0), feature_t(1)));
  tracks_[1] = track1;

  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 2.0);
  
  // Track 0 should keep its observation, Track 1 should lose it
  EXPECT_EQ(tracks_[0].observations.size(), 1);
  EXPECT_EQ(tracks_[1].observations.size(), 0);
  EXPECT_EQ(result, 1);
}

// Test track with multiple observations - some kept, some removed
TEST_F(TrackFilterByAngleTest_155, TrackWithMixedObservations_155) {
  Image img0(0, 0, "test0.jpg");
  img0.features_undist.push_back(Eigen::Vector3d(0, 0, 1).normalized());  // Good alignment
  images_[0] = img0;

  Image img1(1, 0, "test1.jpg");
  img1.features_undist.push_back(Eigen::Vector3d(1, 1, 0.1).normalized());  // Very bad alignment
  images_[1] = img1;

  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(0, 0, 5);
  track.observations.push_back(std::make_pair(image_t(0), feature_t(0)));
  track.observations.push_back(std::make_pair(image_t(1), feature_t(0)));
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 5.0);
  
  // First observation should be kept (perfect alignment)
  // Second observation should be removed (huge angle error)
  EXPECT_EQ(tracks_[0].observations.size(), 1);
  EXPECT_EQ(tracks_[0].observations[0].first, image_t(0));
  EXPECT_EQ(result, 1);
}

// Test that return value correctly counts only tracks that were modified
TEST_F(TrackFilterByAngleTest_155, ReturnValueCountsModifiedTracks_155) {
  Image img(0, 0, "test.jpg");
  img.features_undist.push_back(Eigen::Vector3d(0, 0, 1).normalized());
  img.features_undist.push_back(Eigen::Vector3d(0, 0, 1).normalized());
  img.features_undist.push_back(Eigen::Vector3d(1, 0, 0).normalized());  // perpendicular
  images_[0] = img;

  // Track 0: good
  Track t0;
  t0.track_id = 0;
  t0.xyz = Eigen::Vector3d(0, 0, 5);
  t0.observations.push_back(std::make_pair(image_t(0), feature_t(0)));
  tracks_[0] = t0;

  // Track 1: good
  Track t1;
  t1.track_id = 1;
  t1.xyz = Eigen::Vector3d(0, 0, 5);
  t1.observations.push_back(std::make_pair(image_t(0), feature_t(1)));
  tracks_[1] = t1;

  // Track 2: bad (perpendicular direction)
  Track t2;
  t2.track_id = 2;
  t2.xyz = Eigen::Vector3d(0, 0, 5);
  t2.observations.push_back(std::make_pair(image_t(0), feature_t(2)));
  tracks_[2] = t2;

  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 5.0);
  EXPECT_EQ(result, 1);  // Only track 2 should be modified
}

// Test with point at z very close to 0 (EPS boundary)
TEST_F(TrackFilterByAngleTest_155, TrackPointAtZeroDepth_155) {
  Image img(0, 0, "test.jpg");
  img.features_undist.push_back(Eigen::Vector3d(0, 0, 1).normalized());
  images_[0] = img;

  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(0, 0, 1e-13);  // Very close to zero, at or below EPS
  track.observations.push_back(std::make_pair(image_t(0), feature_t(0)));
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 5.0);
  // Point at ~zero depth should be filtered out (pt_calc(2) < EPS)
  EXPECT_EQ(tracks_[0].observations.size(), 0);
  EXPECT_EQ(result, 1);
}

// Test with zero angle threshold (very strict)
TEST_F(TrackFilterByAngleTest_155, ZeroAngleThreshold_155) {
  Image img(0, 0, "test.jpg");
  img.features_undist.push_back(Eigen::Vector3d(0, 0, 1).normalized());
  images_[0] = img;

  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(0, 0, 5);
  track.observations.push_back(std::make_pair(image_t(0), feature_t(0)));
  tracks_[0] = track;

  // Zero threshold means cos(0) = 1.0, so only perfectly aligned observations kept
  // (0,0,1) dot (0,0,1) = 1.0 which should be > cos(0) = 1.0? Actually 1.0 > 1.0 is false
  // So even perfect alignment might be filtered with threshold = 0
  int result = TrackFilter::FilterTracksByAngle(
      view_graph_, cameras_, images_, tracks_, 0.0);
  // dot = 1.0, thres = cos(0) = 1.0, condition is dot > thres, i.e., 1.0 > 1.0 = false
  EXPECT_EQ(tracks_[0].observations.size(), 0);
  EXPECT_EQ(result, 1);
}

}  // namespace
}  // namespace glomap
