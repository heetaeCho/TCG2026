// File: reconstruction_normalizer_test_80.cc

#include <gtest/gtest.h>

#include <unordered_map>
#include <cmath>

#include <Eigen/Core>
#include <Eigen/Geometry>

// Assuming the project exposes this header for the function under test.
#include "glomap/processors/reconstruction_normalizer.h"

namespace glomap {

class NormalizeReconstructionTest_80 : public ::testing::Test {
 protected:
  using RigsMap = std::unordered_map<rig_t, Rig>;
  using CamerasMap = std::unordered_map<camera_t, Camera>;
  using FramesMap = std::unordered_map<frame_t, Frame>;
  using ImagesMap = std::unordered_map<image_t, Image>;
  using TracksMap = std::unordered_map<track_t, Track>;

  // Helper: create a registered Image whose projection center is `center`.
  Image CreateRegisteredImageAt(const Eigen::Vector3d& center) {
    Image image;
    image.SetRegistered(true);

    // In COLMAP-style APIs, the camera center C and CamFromWorld=[R|t]
    // are related as: C = -R^T * t. For identity rotation, t = -C.
    Rigid3d cam_from_world(Eigen::Quaterniond::Identity(), -center);
    image.CamFromWorld() = cam_from_world;

    return image;
  }

  // Helper: compute Euclidean distance between two 3D points.
  double Distance(const Eigen::Vector3d& a, const Eigen::Vector3d& b) {
    return (a - b).norm();
  }
};

// TEST 1: Single registered image, non-fixed scale, zero old extent.
// The tracks should be translated so that the mean camera center goes to the origin.
// With a single image at (10, 0, 0), a track at (10, 0, 0) should end up near (0, 0, 0).
TEST_F(NormalizeReconstructionTest_80,
       SingleImage_ShiftsTracksToOriginWhenNotFixedScale_80) {
  RigsMap rigs;
  CamerasMap cameras;
  FramesMap frames;
  ImagesMap images;
  TracksMap tracks;

  const image_t kImageId = static_cast<image_t>(1);
  const track_t kTrackId = static_cast<track_t>(1);

  const Eigen::Vector3d center(10.0, 0.0, 0.0);

  // One registered image at (10, 0, 0).
  images.emplace(kImageId, CreateRegisteredImageAt(center));

  // One track at the same position as the camera center.
  Track track;
  track.xyz = center;
  tracks.emplace(kTrackId, track);

  const bool fixed_scale = false;
  const double extent = 10.0;
  const double p0 = 0.0;
  const double p1 = 1.0;

  const colmap::Sim3d tform =
      NormalizeReconstruction(rigs, cameras, frames, images, tracks,
                              fixed_scale, extent, p0, p1);

  (void)tform;  // We only observe effects via tracks here.

  const Eigen::Vector3d transformed = tracks.at(kTrackId).xyz;

  EXPECT_NEAR(transformed.x(), 0.0, 1e-6);
  EXPECT_NEAR(transformed.y(), 0.0, 1e-6);
  EXPECT_NEAR(transformed.z(), 0.0, 1e-6);
}

// TEST 2: Two registered images with different centers, non-fixed scale.
// With centers at 0 and 2 along X, and percentiles covering full range,
// the old extent is 2, so the distance between transformed points should
// equal the `extent` argument.
TEST_F(NormalizeReconstructionTest_80,
       TwoImages_ScalesTrackDistanceToRequestedExtent_80) {
  RigsMap rigs;
  CamerasMap cameras;
  FramesMap frames;
  ImagesMap images;
  TracksMap tracks;

  const image_t kImageId1 = static_cast<image_t>(1);
  const image_t kImageId2 = static_cast<image_t>(2);
  const track_t kTrackId1 = static_cast<track_t>(1);
  const track_t kTrackId2 = static_cast<track_t>(2);

  const Eigen::Vector3d center1(0.0, 0.0, 0.0);
  const Eigen::Vector3d center2(2.0, 0.0, 0.0);

  images.emplace(kImageId1, CreateRegisteredImageAt(center1));
  images.emplace(kImageId2, CreateRegisteredImageAt(center2));

  // Tracks start at the same locations as the camera centers.
  Track track1;
  track1.xyz = center1;
  tracks.emplace(kTrackId1, track1);

  Track track2;
  track2.xyz = center2;
  tracks.emplace(kTrackId2, track2);

  const double original_distance =
      Distance(tracks.at(kTrackId1).xyz, tracks.at(kTrackId2).xyz);
  ASSERT_NEAR(original_distance, 2.0, 1e-6);  // Sanity check.

  const bool fixed_scale = false;
  const double extent = 10.0;
  const double p0 = 0.0;
  const double p1 = 1.0;

  const colmap::Sim3d tform =
      NormalizeReconstruction(rigs, cameras, frames, images, tracks,
                              fixed_scale, extent, p0, p1);

  (void)tform;

  const Eigen::Vector3d t1 = tracks.at(kTrackId1).xyz;
  const Eigen::Vector3d t2 = tracks.at(kTrackId2).xyz;

  const double new_distance = Distance(t1, t2);

  // After normalization, the distance between the two transformed points
  // should match the requested extent.
  EXPECT_NEAR(new_distance, extent, 1e-5);
}

// TEST 3: Two registered images with different centers, fixed scale.
// With fixed_scale=true, the scene should be re-centered but not scaled,
// i.e., distance between points is preserved, while mean is moved to origin.
TEST_F(NormalizeReconstructionTest_80,
       TwoImages_FixedScale_PreservesDistanceAndRecenters_80) {
  RigsMap rigs;
  CamerasMap cameras;
  FramesMap frames;
  ImagesMap images;
  TracksMap tracks;

  const image_t kImageId1 = static_cast<image_t>(1);
  const image_t kImageId2 = static_cast<image_t>(2);
  const track_t kTrackId1 = static_cast<track_t>(1);
  const track_t kTrackId2 = static_cast<track_t>(2);

  const Eigen::Vector3d center1(0.0, 0.0, 0.0);
  const Eigen::Vector3d center2(2.0, 0.0, 0.0);

  images.emplace(kImageId1, CreateRegisteredImageAt(center1));
  images.emplace(kImageId2, CreateRegisteredImageAt(center2));

  Track track1;
  track1.xyz = center1;
  tracks.emplace(kTrackId1, track1);

  Track track2;
  track2.xyz = center2;
  tracks.emplace(kTrackId2, track2);

  const double original_distance =
      Distance(tracks.at(kTrackId1).xyz, tracks.at(kTrackId2).xyz);
  ASSERT_NEAR(original_distance, 2.0, 1e-6);  // Sanity check.

  const bool fixed_scale = true;
  const double extent = 10.0;  // Should not affect scale when fixed_scale is true.
  const double p0 = 0.0;
  const double p1 = 1.0;

  const colmap::Sim3d tform =
      NormalizeReconstruction(rigs, cameras, frames, images, tracks,
                              fixed_scale, extent, p0, p1);

  (void)tform;

  const Eigen::Vector3d t1 = tracks.at(kTrackId1).xyz;
  const Eigen::Vector3d t2 = tracks.at(kTrackId2).xyz;

  const double new_distance = Distance(t1, t2);
  const Eigen::Vector3d mean_after = 0.5 * (t1 + t2);

  // Distance should be preserved (no scaling).
  EXPECT_NEAR(new_distance, original_distance, 1e-6);

  // But the mean of the two points should be moved close to the origin.
  EXPECT_NEAR(mean_after.x(), 0.0, 1e-6);
  EXPECT_NEAR(mean_after.y(), 0.0, 1e-6);
  EXPECT_NEAR(mean_after.z(), 0.0, 1e-6);
}

}  // namespace glomap
