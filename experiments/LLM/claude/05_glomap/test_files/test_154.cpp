#include <gtest/gtest.h>
#include "glomap/processors/track_filter.h"
#include "glomap/scene/types.h"
#include "glomap/types.h"

#include <unordered_map>
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace glomap {
namespace {

class TrackFilterTest_154 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up a simple pinhole camera (identity-like)
    // We'll create a camera with id 0
    Camera cam;
    cam.camera_id = 0;
    // Set up as a simple pinhole camera with focal length 1, principal point at (0,0)
    // Using COLMAP camera model: SIMPLE_PINHOLE with params [f, cx, cy]
    cam.model_id = 0;  // SIMPLE_PINHOLE
    cam.width = 100;
    cam.height = 100;
    cam.params = {100.0, 50.0, 50.0};  // focal_length, cx, cy
    cameras_[0] = cam;
  }

  // Helper to create an image at identity pose (looking along +Z)
  Image CreateImageAtIdentity(image_t img_id, camera_t cam_id) {
    Image img(img_id, cam_id, "test.jpg");
    // Set identity pose: cam_from_world is identity
    img.cam_from_world = Rigid3d();  // identity
    img.is_registered = true;
    return img;
  }

  // Helper to create an image with a specific pose
  Image CreateImageWithPose(image_t img_id, camera_t cam_id,
                            const Eigen::Quaterniond& q,
                            const Eigen::Vector3d& t) {
    Image img(img_id, cam_id, "test.jpg");
    img.cam_from_world = Rigid3d(q, t);
    img.is_registered = true;
    return img;
  }

  ViewGraph view_graph_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;
};

// Test with empty tracks map
TEST_F(TrackFilterTest_154, EmptyTracks_154) {
  int result = TrackFilter::FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, 4.0, false);
  EXPECT_EQ(result, 0);
}

// Test where all observations have good reprojection (none filtered)
TEST_F(TrackFilterTest_154, AllObservationsGood_NoneFiltered_154) {
  // Create an image at identity pose
  Image img = CreateImageAtIdentity(0, 0);
  
  // 3D point at (0, 0, 10) - in front of camera
  Eigen::Vector3d xyz(0.0, 0.0, 10.0);
  
  // Project: cam coords = (0, 0, 10), pixel = (f*0/10 + cx, f*0/10 + cy) = (50, 50)
  img.features.push_back(Eigen::Vector2d(50.0, 50.0));
  images_[0] = img;

  Track track;
  track.track_id = 0;
  track.xyz = xyz;
  track.observations.emplace_back(0, 0);
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, 4.0, false);
  
  EXPECT_EQ(result, 0);
  EXPECT_EQ(tracks_[0].observations.size(), 1);
}

// Test where an observation has bad reprojection (gets filtered)
TEST_F(TrackFilterTest_154, BadReprojection_ObservationFiltered_154) {
  Image img = CreateImageAtIdentity(0, 0);
  
  // 3D point at (0, 0, 10)
  Eigen::Vector3d xyz(0.0, 0.0, 10.0);
  
  // Feature at a very wrong location (far from projected point (50, 50))
  img.features.push_back(Eigen::Vector2d(200.0, 200.0));
  images_[0] = img;

  Track track;
  track.track_id = 0;
  track.xyz = xyz;
  track.observations.emplace_back(0, 0);
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, 4.0, false);
  
  EXPECT_EQ(result, 1);
  EXPECT_EQ(tracks_[0].observations.size(), 0);
}

// Test with point behind camera (negative z) - observation should be removed
TEST_F(TrackFilterTest_154, PointBehindCamera_ObservationRemoved_154) {
  Image img = CreateImageAtIdentity(0, 0);
  
  // 3D point behind camera
  Eigen::Vector3d xyz(0.0, 0.0, -10.0);
  
  img.features.push_back(Eigen::Vector2d(50.0, 50.0));
  images_[0] = img;

  Track track;
  track.track_id = 0;
  track.xyz = xyz;
  track.observations.emplace_back(0, 0);
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, 4.0, false);
  
  EXPECT_EQ(result, 1);
  EXPECT_EQ(tracks_[0].observations.size(), 0);
}

// Test with multiple observations, some good and some bad
TEST_F(TrackFilterTest_154, MixedObservations_PartialFiltering_154) {
  // Image 0: identity pose
  Image img0 = CreateImageAtIdentity(0, 0);
  // Image 1: identity pose
  Image img1 = CreateImageAtIdentity(1, 0);

  Eigen::Vector3d xyz(0.0, 0.0, 10.0);
  
  // Good observation for img0: projected to (50, 50)
  img0.features.push_back(Eigen::Vector2d(50.0, 50.0));
  // Bad observation for img1: far off
  img1.features.push_back(Eigen::Vector2d(200.0, 200.0));
  
  images_[0] = img0;
  images_[1] = img1;

  Track track;
  track.track_id = 0;
  track.xyz = xyz;
  track.observations.emplace_back(0, 0);
  track.observations.emplace_back(1, 0);
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, 4.0, false);
  
  EXPECT_EQ(result, 1);
  EXPECT_EQ(tracks_[0].observations.size(), 1);
  // The good observation should remain
  EXPECT_EQ(tracks_[0].observations[0].first, 0);
}

// Test with multiple tracks, some modified and some not
TEST_F(TrackFilterTest_154, MultipleTracks_CountCorrect_154) {
  Image img0 = CreateImageAtIdentity(0, 0);
  Image img1 = CreateImageAtIdentity(1, 0);

  Eigen::Vector3d xyz_good(0.0, 0.0, 10.0);
  Eigen::Vector3d xyz_bad(0.0, 0.0, 10.0);

  // Good feature for track 0
  img0.features.push_back(Eigen::Vector2d(50.0, 50.0));
  // Bad feature for track 1
  img0.features.push_back(Eigen::Vector2d(200.0, 200.0));
  // Good feature for track 0 in img1
  img1.features.push_back(Eigen::Vector2d(50.0, 50.0));

  images_[0] = img0;
  images_[1] = img1;

  // Track 0: good observations in both images
  Track track0;
  track0.track_id = 0;
  track0.xyz = xyz_good;
  track0.observations.emplace_back(0, 0);
  track0.observations.emplace_back(1, 0);
  tracks_[0] = track0;

  // Track 1: bad observation
  Track track1;
  track1.track_id = 1;
  track1.xyz = xyz_bad;
  track1.observations.emplace_back(0, 1);  // feature_id 1 in img0
  tracks_[1] = track1;

  int result = TrackFilter::FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, 4.0, false);
  
  // Track 1 should be modified (observation removed), Track 0 should stay
  EXPECT_EQ(result, 1);
  EXPECT_EQ(tracks_[0].observations.size(), 2);
  EXPECT_EQ(tracks_[1].observations.size(), 0);
}

// Test normalized image mode
TEST_F(TrackFilterTest_154, NormalizedImageMode_GoodObservation_154) {
  Image img = CreateImageAtIdentity(0, 0);

  Eigen::Vector3d xyz(0.0, 0.0, 10.0);

  // In normalized image mode, we compare undistorted features
  // The projected normalized coords: (0/10, 0/10) = (0, 0)
  // Feature undistorted should match
  img.features_undist.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
  images_[0] = img;

  Track track;
  track.track_id = 0;
  track.xyz = xyz;
  track.observations.emplace_back(0, 0);
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, 0.01, true);

  EXPECT_EQ(result, 0);
  EXPECT_EQ(tracks_[0].observations.size(), 1);
}

// Test normalized image mode with bad observation
TEST_F(TrackFilterTest_154, NormalizedImageMode_BadObservation_154) {
  Image img = CreateImageAtIdentity(0, 0);

  Eigen::Vector3d xyz(0.0, 0.0, 10.0);

  // Feature undistorted far from projected point
  img.features_undist.push_back(Eigen::Vector3d(5.0, 5.0, 1.0));
  images_[0] = img;

  Track track;
  track.track_id = 0;
  track.xyz = xyz;
  track.observations.emplace_back(0, 0);
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, 0.01, true);

  EXPECT_EQ(result, 1);
  EXPECT_EQ(tracks_[0].observations.size(), 0);
}

// Test with very large max_reprojection_error (nothing should be filtered except behind-camera)
TEST_F(TrackFilterTest_154, LargeThreshold_NothingFiltered_154) {
  Image img = CreateImageAtIdentity(0, 0);

  Eigen::Vector3d xyz(1.0, 1.0, 10.0);

  // Even a wrong feature location should pass with very large threshold
  img.features.push_back(Eigen::Vector2d(999.0, 999.0));
  images_[0] = img;

  Track track;
  track.track_id = 0;
  track.xyz = xyz;
  track.observations.emplace_back(0, 0);
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, 1e10, false);

  EXPECT_EQ(result, 0);
  EXPECT_EQ(tracks_[0].observations.size(), 1);
}

// Test with zero max_reprojection_error (everything should be filtered unless exact match)
TEST_F(TrackFilterTest_154, ZeroThreshold_EverythingFiltered_154) {
  Image img = CreateImageAtIdentity(0, 0);

  Eigen::Vector3d xyz(0.1, 0.1, 10.0);

  // Even a close feature will likely not be exactly zero error
  img.features.push_back(Eigen::Vector2d(51.0, 51.0));
  images_[0] = img;

  Track track;
  track.track_id = 0;
  track.xyz = xyz;
  track.observations.emplace_back(0, 0);
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, 0.0, false);

  // With threshold 0, reprojection_error must be < 0 which is impossible for non-zero error
  EXPECT_EQ(result, 1);
  EXPECT_EQ(tracks_[0].observations.size(), 0);
}

// Test track with no observations
TEST_F(TrackFilterTest_154, TrackWithNoObservations_154) {
  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(0.0, 0.0, 10.0);
  // Empty observations
  tracks_[0] = track;

  int result = TrackFilter::FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, 4.0, false);

  EXPECT_EQ(result, 0);
  EXPECT_EQ(tracks_[0].observations.size(), 0);
}

// Test return value equals number of modified tracks
TEST_F(TrackFilterTest_154, ReturnValueMatchesModifiedTrackCount_154) {
  Image img = CreateImageAtIdentity(0, 0);
  
  // Feature 0: good match for track at (0,0,10)
  img.features.push_back(Eigen::Vector2d(50.0, 50.0));
  // Feature 1: bad match
  img.features.push_back(Eigen::Vector2d(200.0, 200.0));
  // Feature 2: bad match
  img.features.push_back(Eigen::Vector2d(300.0, 300.0));
  
  images_[0] = img;

  // Track 0: good
  Track t0;
  t0.track_id = 0;
  t0.xyz = Eigen::Vector3d(0.0, 0.0, 10.0);
  t0.observations.emplace_back(0, 0);
  tracks_[0] = t0;

  // Track 1: bad
  Track t1;
  t1.track_id = 1;
  t1.xyz = Eigen::Vector3d(0.0, 0.0, 10.0);
  t1.observations.emplace_back(0, 1);
  tracks_[1] = t1;

  // Track 2: bad
  Track t2;
  t2.track_id = 2;
  t2.xyz = Eigen::Vector3d(0.0, 0.0, 10.0);
  t2.observations.emplace_back(0, 2);
  tracks_[2] = t2;

  int result = TrackFilter::FilterTracksByReprojection(
      view_graph_, cameras_, images_, tracks_, 4.0, false);

  EXPECT_EQ(result, 2);
}

}  // namespace
}  // namespace glomap
