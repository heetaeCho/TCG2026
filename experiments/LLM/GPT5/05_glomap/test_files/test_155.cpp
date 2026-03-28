// File: track_filter_angle_test_155.cc

#include <unordered_map>
#include <vector>
#include <cmath>

#include "gtest/gtest.h"

#include "glomap/processors/track_filter.h"
#include "glomap/scene/image.h"
#include "glomap/scene/track.h"
#include "glomap/scene/view_graph.h"
#include "glomap/types.h"
// If Camera is declared in a separate header, include it as well.
// #include "glomap/scene/camera.h"

namespace glomap {

class TrackFilterTest_155 : public ::testing::Test {
 protected:
  ViewGraph view_graph_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;

  void SetUpCalibratedCamera(camera_t cam_id) {
    Camera cam;
    cam.has_prior_focal_length = true;
    cameras_[cam_id] = cam;
  }

  void SetUpUncalibratedCamera(camera_t cam_id) {
    Camera cam;
    cam.has_prior_focal_length = false;
    cameras_[cam_id] = cam;
  }

  void AddImageWithSingleFeature(image_t image_id,
                                 camera_t cam_id,
                                 const Eigen::Vector3d& feature_dir) {
    Image img;
    img.camera_id = cam_id;
    img.features_undist.clear();
    img.features_undist.push_back(feature_dir);
    images_[image_id] = img;
  }

  void AddTrackWithSingleObservation(track_t track_id,
                                     const Eigen::Vector3d& xyz,
                                     image_t image_id,
                                     feature_t feature_id) {
    Track track;
    track.xyz = xyz;
    track.observations.clear();
    track.observations.emplace_back(image_id, feature_id);
    tracks_[track_id] = track;
  }
};

// No tracks: function should return 0 and leave containers unchanged.
TEST_F(TrackFilterTest_155, NoTracksReturnsZero_155) {
  // cameras_ and images_ can be empty as tracks_ is empty.
  double max_angle_error_deg = 10.0;

  int modified =
      TrackFilter::FilterTracksByAngle(view_graph_, cameras_, images_, tracks_,
                                       max_angle_error_deg);

  EXPECT_EQ(modified, 0);
  EXPECT_TRUE(tracks_.empty());
}

// Single track & observation, calibrated camera, perfect alignment:
// nothing should be filtered and return value should be 0.
TEST_F(TrackFilterTest_155, AllObservationsKeptForCalibratedCamera_155) {
  const camera_t cam_id = 1;
  const image_t img_id = 2;
  const track_t track_id = 3;

  SetUpCalibratedCamera(cam_id);

  // Track point in front of the camera along +Z.
  Eigen::Vector3d xyz(0.0, 0.0, 1.0);
  // Feature direction aligned with the point direction.
  Eigen::Vector3d feature_dir(0.0, 0.0, 1.0);

  AddImageWithSingleFeature(img_id, cam_id, feature_dir);
  AddTrackWithSingleObservation(track_id, xyz, img_id, 0);

  double max_angle_error_deg = 1.0;

  int modified =
      TrackFilter::FilterTracksByAngle(view_graph_, cameras_, images_, tracks_,
                                       max_angle_error_deg);

  // No tracks should be reported as modified.
  EXPECT_EQ(modified, 0);
  ASSERT_EQ(tracks_.size(), 1u);
  const auto& track_after = tracks_.at(track_id);
  EXPECT_EQ(track_after.observations.size(), 1u);
  EXPECT_EQ(track_after.observations[0].first, img_id);
  EXPECT_EQ(track_after.observations[0].second, 0);
}

// Single track & observation, calibrated camera, very large angle:
// observation should be removed and function should return 1.
TEST_F(TrackFilterTest_155, ObservationRemovedWhenAngleTooLarge_155) {
  const camera_t cam_id = 1;
  const image_t img_id = 2;
  const track_t track_id = 3;

  SetUpCalibratedCamera(cam_id);

  // Point along +Z.
  Eigen::Vector3d xyz(0.0, 0.0, 1.0);
  // Feature direction roughly opposite to the point (+Z vs -Z).
  Eigen::Vector3d feature_dir(0.0, 0.0, -1.0);

  AddImageWithSingleFeature(img_id, cam_id, feature_dir);
  AddTrackWithSingleObservation(track_id, xyz, img_id, 0);

  double max_angle_error_deg = 1.0;  // very small allowed error

  int modified =
      TrackFilter::FilterTracksByAngle(view_graph_, cameras_, images_, tracks_,
                                       max_angle_error_deg);

  EXPECT_EQ(modified, 1);  // this track should be counted as filtered
  ASSERT_EQ(tracks_.size(), 1u);
  const auto& track_after = tracks_.at(track_id);
  // Observation should be removed.
  EXPECT_TRUE(track_after.observations.empty());
}

// Compare calibrated vs uncalibrated cameras:
// For a 120-degree difference between ray and feature,
// with max_angle_error = 90deg,
// - calibrated camera (threshold based on 90deg) should reject
// - uncalibrated camera (threshold based on 180deg) should keep
TEST_F(TrackFilterTest_155, UncalibratedCameraUsesRelaxedThreshold_155) {
  const camera_t cam_id = 1;
  const image_t img_id = 2;
  const track_t track_id = 3;

  // Common point direction along +Z.
  Eigen::Vector3d xyz(0.0, 0.0, 1.0);

  // Feature direction forming 120 degrees with +Z.
  // dot((0,0,1), (sqrt(3)/2, 0, -1/2)) = -1/2
  Eigen::Vector3d feature_dir(std::sqrt(3.0) / 2.0, 0.0, -0.5);

  double max_angle_error_deg = 90.0;

  // --- Calibrated camera case: should reject (dot = -0.5, threshold = cos 90° = 0) ---
  {
    ViewGraph vg;
    std::unordered_map<camera_t, Camera> cams;
    std::unordered_map<image_t, Image> imgs;
    std::unordered_map<track_t, Track> trks;

    Camera cam_calib;
    cam_calib.has_prior_focal_length = true;
    cams[cam_id] = cam_calib;

    Image img;
    img.camera_id = cam_id;
    img.features_undist.push_back(feature_dir);
    imgs[img_id] = img;

    Track track;
    track.xyz = xyz;
    track.observations.emplace_back(img_id, 0);
    trks[track_id] = track;

    int modified = TrackFilter::FilterTracksByAngle(vg, cams, imgs, trks,
                                                    max_angle_error_deg);
    EXPECT_EQ(modified, 1);  // track modified (observation removed)
    EXPECT_TRUE(trks[track_id].observations.empty());
  }

  // --- Uncalibrated camera case: should keep (dot = -0.5, threshold = cos 180° = -1) ---
  {
    ViewGraph vg;
    std::unordered_map<camera_t, Camera> cams;
    std::unordered_map<image_t, Image> imgs;
    std::unordered_map<track_t, Track> trks;

    Camera cam_uncalib;
    cam_uncalib.has_prior_focal_length = false;
    cams[cam_id] = cam_uncalib;

    Image img;
    img.camera_id = cam_id;
    img.features_undist.push_back(feature_dir);
    imgs[img_id] = img;

    Track track;
    track.xyz = xyz;
    track.observations.emplace_back(img_id, 0);
    trks[track_id] = track;

    int modified = TrackFilter::FilterTracksByAngle(vg, cams, imgs, trks,
                                                    max_angle_error_deg);
    EXPECT_EQ(modified, 0);  // track not modified
    ASSERT_EQ(trks[track_id].observations.size(), 1u);
  }
}

// Point behind the camera (negative depth) should be ignored:
// all observations are skipped, resulting in an empty observation list
// and the track being counted as filtered.
TEST_F(TrackFilterTest_155, NegativeDepthObservationIsDiscarded_155) {
  const camera_t cam_id = 1;
  const image_t img_id = 2;
  const track_t track_id = 3;

  SetUpCalibratedCamera(cam_id);

  // Point behind the camera: negative Z, definitely < EPS.
  Eigen::Vector3d xyz(0.0, 0.0, -1.0);
  Eigen::Vector3d feature_dir(0.0, 0.0, 1.0);

  AddImageWithSingleFeature(img_id, cam_id, feature_dir);
  AddTrackWithSingleObservation(track_id, xyz, img_id, 0);

  double max_angle_error_deg = 10.0;

  int modified =
      TrackFilter::FilterTracksByAngle(view_graph_, cameras_, images_, tracks_,
                                       max_angle_error_deg);

  EXPECT_EQ(modified, 1);  // track modified (observations removed)
  ASSERT_EQ(tracks_.size(), 1u);
  EXPECT_TRUE(tracks_[track_id].observations.empty());
}

}  // namespace glomap
