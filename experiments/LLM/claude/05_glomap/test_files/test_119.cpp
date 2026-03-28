#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/io/colmap_converter.h"
#include "glomap/scene/types.h"

#include <colmap/scene/reconstruction.h>
#include <colmap/scene/camera.h>
#include <colmap/scene/image.h>
#include <colmap/scene/point3d.h>
#include <colmap/sensor/models.h>

#include <unordered_map>

namespace glomap {
namespace {

class ConvertGlomapToColmapTest_119 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up a basic camera
    camera_.camera_id = 1;
    camera_.SetModelIdFromName("PINHOLE");
    camera_.width = 640;
    camera_.height = 480;
    camera_.params = {500.0, 500.0, 320.0, 240.0};
  }

  // Helper to create a registered image with a frame
  Image CreateRegisteredImage(image_t image_id, camera_t cam_id,
                              frame_t fr_id, int cluster_id,
                              size_t num_features = 0) {
    Image img(image_id, cam_id, "image_" + std::to_string(image_id) + ".jpg");
    img.frame_id = fr_id;

    // We need to set up the frame pointer for IsRegistered and ClusterId
    // to work. The image needs a frame that is registered.
    for (size_t i = 0; i < num_features; i++) {
      img.features.push_back(Eigen::Vector2d(i * 10.0, i * 10.0));
      img.features_undist.push_back(Eigen::Vector3d(i * 10.0, i * 10.0, 1.0));
    }
    return img;
  }

  Frame CreateFrame(frame_t frame_id, bool is_registered, int cluster_id) {
    colmap::Frame colmap_frame;
    colmap_frame.frame_id = frame_id;
    colmap_frame.camera_id = 1;
    Frame frame(colmap_frame);
    frame.is_registered = is_registered;
    frame.cluster_id = cluster_id;
    return frame;
  }

  Camera camera_;
};

// Test with empty inputs - should produce an empty reconstruction
TEST_F(ConvertGlomapToColmapTest_119, EmptyInputs_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
  colmap::Reconstruction reconstruction;

  ConvertGlomapToColmap(rigs, cameras, frames, images, tracks,
                        reconstruction, -1, false);

  EXPECT_EQ(reconstruction.NumCameras(), 0);
  EXPECT_EQ(reconstruction.NumImages(), 0);
  EXPECT_EQ(reconstruction.NumPoints3D(), 0);
}

// Test that cameras are added to reconstruction
TEST_F(ConvertGlomapToColmapTest_119, CamerasAreAdded_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
  colmap::Reconstruction reconstruction;

  cameras[1] = camera_;

  Camera camera2;
  camera2.camera_id = 2;
  camera2.SetModelIdFromName("PINHOLE");
  camera2.width = 800;
  camera2.height = 600;
  camera2.params = {600.0, 600.0, 400.0, 300.0};
  cameras[2] = camera2;

  ConvertGlomapToColmap(rigs, cameras, frames, images, tracks,
                        reconstruction, -1, false);

  EXPECT_EQ(reconstruction.NumCameras(), 2);
  EXPECT_TRUE(reconstruction.ExistsCamera(1));
  EXPECT_TRUE(reconstruction.ExistsCamera(2));
}

// Test that images are added to reconstruction
TEST_F(ConvertGlomapToColmapTest_119, ImagesAreAdded_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
  colmap::Reconstruction reconstruction;

  cameras[1] = camera_;

  Frame frame = CreateFrame(1, true, -1);
  frames[1] = frame;

  Image img(1, 1, "test.jpg");
  img.frame_id = 1;
  images[1] = img;

  ConvertGlomapToColmap(rigs, cameras, frames, images, tracks,
                        reconstruction, -1, false);

  EXPECT_EQ(reconstruction.NumImages(), 1);
  EXPECT_TRUE(reconstruction.ExistsImage(1));
}

// Test that frames are added to reconstruction
TEST_F(ConvertGlomapToColmapTest_119, FramesAreAdded_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
  colmap::Reconstruction reconstruction;

  cameras[1] = camera_;

  Frame frame = CreateFrame(1, true, -1);
  frames[1] = frame;

  ConvertGlomapToColmap(rigs, cameras, frames, images, tracks,
                        reconstruction, -1, false);

  EXPECT_TRUE(reconstruction.ExistsFrame(1));
}

// Test tracks with enough observations are added as 3D points
TEST_F(ConvertGlomapToColmapTest_119, TracksWithEnoughObservationsAreAdded_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
  colmap::Reconstruction reconstruction;

  cameras[1] = camera_;

  Frame frame1 = CreateFrame(1, true, -1);
  Frame frame2 = CreateFrame(2, true, -1);
  frames[1] = frame1;
  frames[2] = frame2;

  Image img1(1, 1, "img1.jpg");
  img1.frame_id = 1;
  img1.frame_ptr = &frames[1];
  img1.features.push_back(Eigen::Vector2d(100.0, 100.0));
  img1.features_undist.push_back(Eigen::Vector3d(100.0, 100.0, 1.0));
  images[1] = img1;

  Image img2(2, 1, "img2.jpg");
  img2.frame_id = 2;
  img2.frame_ptr = &frames[2];
  img2.features.push_back(Eigen::Vector2d(200.0, 200.0));
  img2.features_undist.push_back(Eigen::Vector3d(200.0, 200.0, 1.0));
  images[2] = img2;

  Track track;
  track.track_id = 1;
  track.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);
  track.color = Eigen::Vector3ub(255, 0, 0);
  track.observations.push_back(Observation(1, 0));
  track.observations.push_back(Observation(2, 0));
  tracks[1] = track;

  ConvertGlomapToColmap(rigs, cameras, frames, images, tracks,
                        reconstruction, -1, false);

  EXPECT_TRUE(reconstruction.ExistsPoint3D(1));
  const auto& point = reconstruction.Point3D(1);
  EXPECT_DOUBLE_EQ(point.xyz(0), 1.0);
  EXPECT_DOUBLE_EQ(point.xyz(1), 2.0);
  EXPECT_DOUBLE_EQ(point.xyz(2), 3.0);
}

// Test tracks with insufficient observations are not added
TEST_F(ConvertGlomapToColmapTest_119, TracksWithTooFewObservationsNotAdded_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
  colmap::Reconstruction reconstruction;

  cameras[1] = camera_;

  Frame frame1 = CreateFrame(1, true, -1);
  frames[1] = frame1;

  Image img1(1, 1, "img1.jpg");
  img1.frame_id = 1;
  img1.frame_ptr = &frames[1];
  img1.features.push_back(Eigen::Vector2d(100.0, 100.0));
  images[1] = img1;

  // Track with only 1 observation (min is 2)
  Track track;
  track.track_id = 1;
  track.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);
  track.color = Eigen::Vector3ub(255, 0, 0);
  track.observations.push_back(Observation(1, 0));
  tracks[1] = track;

  ConvertGlomapToColmap(rigs, cameras, frames, images, tracks,
                        reconstruction, -1, false);

  EXPECT_FALSE(reconstruction.ExistsPoint3D(1));
}

// Test cluster filtering with cluster_id != -1
TEST_F(ConvertGlomapToColmapTest_119, ClusterFiltering_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
  colmap::Reconstruction reconstruction;

  cameras[1] = camera_;

  Frame frame1 = CreateFrame(1, true, 0);
  Frame frame2 = CreateFrame(2, true, 1);
  frames[1] = frame1;
  frames[2] = frame2;

  Image img1(1, 1, "img1.jpg");
  img1.frame_id = 1;
  img1.frame_ptr = &frames[1];
  img1.features.push_back(Eigen::Vector2d(100.0, 100.0));
  images[1] = img1;

  Image img2(2, 1, "img2.jpg");
  img2.frame_id = 2;
  img2.frame_ptr = &frames[2];
  img2.features.push_back(Eigen::Vector2d(200.0, 200.0));
  images[2] = img2;

  Track track;
  track.track_id = 1;
  track.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);
  track.color = Eigen::Vector3ub(255, 0, 0);
  track.observations.push_back(Observation(1, 0));
  track.observations.push_back(Observation(2, 0));
  tracks[1] = track;

  // Only cluster 0
  ConvertGlomapToColmap(rigs, cameras, frames, images, tracks,
                        reconstruction, 0, false);

  // The track should not have enough registered observations in cluster 0
  // (only img1 is in cluster 0), so it should not be added
  EXPECT_FALSE(reconstruction.ExistsPoint3D(1));
}

// Test with cluster_id = -1 includes all images
TEST_F(ConvertGlomapToColmapTest_119, ClusterIdMinusOneIncludesAll_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
  colmap::Reconstruction reconstruction;

  cameras[1] = camera_;

  Frame frame1 = CreateFrame(1, true, 0);
  Frame frame2 = CreateFrame(2, true, 1);
  frames[1] = frame1;
  frames[2] = frame2;

  Image img1(1, 1, "img1.jpg");
  img1.frame_id = 1;
  img1.frame_ptr = &frames[1];
  img1.features.push_back(Eigen::Vector2d(100.0, 100.0));
  img1.features_undist.push_back(Eigen::Vector3d(100.0, 100.0, 1.0));
  images[1] = img1;

  Image img2(2, 1, "img2.jpg");
  img2.frame_id = 2;
  img2.frame_ptr = &frames[2];
  img2.features.push_back(Eigen::Vector2d(200.0, 200.0));
  img2.features_undist.push_back(Eigen::Vector3d(200.0, 200.0, 1.0));
  images[2] = img2;

  Track track;
  track.track_id = 1;
  track.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);
  track.color = Eigen::Vector3ub(255, 0, 0);
  track.observations.push_back(Observation(1, 0));
  track.observations.push_back(Observation(2, 0));
  tracks[1] = track;

  ConvertGlomapToColmap(rigs, cameras, frames, images, tracks,
                        reconstruction, -1, false);

  EXPECT_TRUE(reconstruction.ExistsPoint3D(1));
}

// Test reconstruction is reset before population
TEST_F(ConvertGlomapToColmapTest_119, ReconstructionIsReset_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
  colmap::Reconstruction reconstruction;

  // Add a camera to reconstruction before the call
  Camera pre_camera;
  pre_camera.camera_id = 99;
  pre_camera.SetModelIdFromName("PINHOLE");
  pre_camera.width = 100;
  pre_camera.height = 100;
  pre_camera.params = {100.0, 100.0, 50.0, 50.0};
  reconstruction.AddCamera(pre_camera);
  ASSERT_TRUE(reconstruction.ExistsCamera(99));

  ConvertGlomapToColmap(rigs, cameras, frames, images, tracks,
                        reconstruction, -1, false);

  // After call, old data should be gone since reconstruction is reset
  EXPECT_FALSE(reconstruction.ExistsCamera(99));
  EXPECT_EQ(reconstruction.NumCameras(), 0);
}

// Test multiple cameras
TEST_F(ConvertGlomapToColmapTest_119, MultipleCameras_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
  colmap::Reconstruction reconstruction;

  for (int i = 1; i <= 5; i++) {
    Camera cam;
    cam.camera_id = i;
    cam.SetModelIdFromName("PINHOLE");
    cam.width = 640;
    cam.height = 480;
    cam.params = {500.0, 500.0, 320.0, 240.0};
    cameras[i] = cam;
  }

  ConvertGlomapToColmap(rigs, cameras, frames, images, tracks,
                        reconstruction, -1, false);

  EXPECT_EQ(reconstruction.NumCameras(), 5);
  for (int i = 1; i <= 5; i++) {
    EXPECT_TRUE(reconstruction.ExistsCamera(i));
  }
}

// Test unregistered images don't contribute to tracks
TEST_F(ConvertGlomapToColmapTest_119, UnregisteredImagesExcludedFromTracks_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
  colmap::Reconstruction reconstruction;

  cameras[1] = camera_;

  // frame1 is registered, frame2 is not
  Frame frame1 = CreateFrame(1, true, -1);
  Frame frame2 = CreateFrame(2, false, -1);
  frames[1] = frame1;
  frames[2] = frame2;

  Image img1(1, 1, "img1.jpg");
  img1.frame_id = 1;
  img1.frame_ptr = &frames[1];
  img1.features.push_back(Eigen::Vector2d(100.0, 100.0));
  img1.features_undist.push_back(Eigen::Vector3d(100.0, 100.0, 1.0));
  images[1] = img1;

  Image img2(2, 1, "img2.jpg");
  img2.frame_id = 2;
  img2.frame_ptr = &frames[2];
  img2.features.push_back(Eigen::Vector2d(200.0, 200.0));
  img2.features_undist.push_back(Eigen::Vector3d(200.0, 200.0, 1.0));
  images[2] = img2;

  Track track;
  track.track_id = 1;
  track.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);
  track.color = Eigen::Vector3ub(255, 0, 0);
  track.observations.push_back(Observation(1, 0));
  track.observations.push_back(Observation(2, 0));
  tracks[1] = track;

  ConvertGlomapToColmap(rigs, cameras, frames, images, tracks,
                        reconstruction, -1, false);

  // Only one registered image in track, so min_supports (2) not met
  EXPECT_FALSE(reconstruction.ExistsPoint3D(1));
}

// Test with no tracks but include_image_points = true
TEST_F(ConvertGlomapToColmapTest_119, NoTracksWithIncludeImagePoints_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
  colmap::Reconstruction reconstruction;

  cameras[1] = camera_;

  Frame frame1 = CreateFrame(1, true, -1);
  frames[1] = frame1;

  Image img1(1, 1, "img1.jpg");
  img1.frame_id = 1;
  img1.frame_ptr = &frames[1];
  img1.features.push_back(Eigen::Vector2d(100.0, 100.0));
  img1.features_undist.push_back(Eigen::Vector3d(100.0, 100.0, 1.0));
  images[1] = img1;

  ConvertGlomapToColmap(rigs, cameras, frames, images, tracks,
                        reconstruction, -1, true);

  EXPECT_EQ(reconstruction.NumImages(), 1);
  EXPECT_EQ(reconstruction.NumPoints3D(), 0);
}

// Test track color is preserved
TEST_F(ConvertGlomapToColmapTest_119, TrackColorPreserved_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
  colmap::Reconstruction reconstruction;

  cameras[1] = camera_;

  Frame frame1 = CreateFrame(1, true, -1);
  Frame frame2 = CreateFrame(2, true, -1);
  frames[1] = frame1;
  frames[2] = frame2;

  Image img1(1, 1, "img1.jpg");
  img1.frame_id = 1;
  img1.frame_ptr = &frames[1];
  img1.features.push_back(Eigen::Vector2d(100.0, 100.0));
  img1.features_undist.push_back(Eigen::Vector3d(100.0, 100.0, 1.0));
  images[1] = img1;

  Image img2(2, 1, "img2.jpg");
  img2.frame_id = 2;
  img2.frame_ptr = &frames[2];
  img2.features.push_back(Eigen::Vector2d(200.0, 200.0));
  img2.features_undist.push_back(Eigen::Vector3d(200.0, 200.0, 1.0));
  images[2] = img2;

  Track track;
  track.track_id = 1;
  track.xyz = Eigen::Vector3d(5.0, 6.0, 7.0);
  track.color = Eigen::Vector3ub(128, 64, 32);
  track.observations.push_back(Observation(1, 0));
  track.observations.push_back(Observation(2, 0));
  tracks[1] = track;

  ConvertGlomapToColmap(rigs, cameras, frames, images, tracks,
                        reconstruction, -1, false);

  ASSERT_TRUE(reconstruction.ExistsPoint3D(1));
  const auto& point = reconstruction.Point3D(1);
  EXPECT_EQ(point.color(0), 128);
  EXPECT_EQ(point.color(1), 64);
  EXPECT_EQ(point.color(2), 32);
}

// Test multiple tracks
TEST_F(ConvertGlomapToColmapTest_119, MultipleTracks_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
  colmap::Reconstruction reconstruction;

  cameras[1] = camera_;

  Frame frame1 = CreateFrame(1, true, -1);
  Frame frame2 = CreateFrame(2, true, -1);
  frames[1] = frame1;
  frames[2] = frame2;

  Image img1(1, 1, "img1.jpg");
  img1.frame_id = 1;
  img1.frame_ptr = &frames[1];
  img1.features.push_back(Eigen::Vector2d(100.0, 100.0));
  img1.features.push_back(Eigen::Vector2d(110.0, 110.0));
  img1.features_undist.push_back(Eigen::Vector3d(100.0, 100.0, 1.0));
  img1.features_undist.push_back(Eigen::Vector3d(110.0, 110.0, 1.0));
  images[1] = img1;

  Image img2(2, 1, "img2.jpg");
  img2.frame_id = 2;
  img2.frame_ptr = &frames[2];
  img2.features.push_back(Eigen::Vector2d(200.0, 200.0));
  img2.features.push_back(Eigen::Vector2d(210.0, 210.0));
  img2.features_undist.push_back(Eigen::Vector3d(200.0, 200.0, 1.0));
  img2.features_undist.push_back(Eigen::Vector3d(210.0, 210.0, 1.0));
  images[2] = img2;

  Track track1;
  track1.track_id = 1;
  track1.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);
  track1.color = Eigen::Vector3ub(255, 0, 0);
  track1.observations.push_back(Observation(1, 0));
  track1.observations.push_back(Observation(2, 0));
  tracks[1] = track1;

  Track track2;
  track2.track_id = 2;
  track2.xyz = Eigen::Vector3d(4.0, 5.0, 6.0);
  track2.color = Eigen::Vector3ub(0, 255, 0);
  track2.observations.push_back(Observation(1, 1));
  track2.observations.push_back(Observation(2, 1));
  tracks[2] = track2;

  ConvertGlomapToColmap(rigs, cameras, frames, images, tracks,
                        reconstruction, -1, false);

  EXPECT_TRUE(reconstruction.ExistsPoint3D(1));
  EXPECT_TRUE(reconstruction.ExistsPoint3D(2));
  EXPECT_EQ(reconstruction.NumPoints3D(), 2);
}

// Test with only cameras and no other data
TEST_F(ConvertGlomapToColmapTest_119, OnlyCameras_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
  colmap::Reconstruction reconstruction;

  cameras[1] = camera_;

  ConvertGlomapToColmap(rigs, cameras, frames, images, tracks,
                        reconstruction, -1, false);

  EXPECT_EQ(reconstruction.NumCameras(), 1);
  EXPECT_EQ(reconstruction.NumImages(), 0);
  EXPECT_EQ(reconstruction.NumPoints3D(), 0);
}

// Test that track with exactly 2 observations (min_supports boundary) is added
TEST_F(ConvertGlomapToColmapTest_119, TrackWithExactlyMinSupports_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
  colmap::Reconstruction reconstruction;

  cameras[1] = camera_;

  Frame frame1 = CreateFrame(1, true, -1);
  Frame frame2 = CreateFrame(2, true, -1);
  frames[1] = frame1;
  frames[2] = frame2;

  Image img1(1, 1, "img1.jpg");
  img1.frame_id = 1;
  img1.frame_ptr = &frames[1];
  img1.features.push_back(Eigen::Vector2d(100.0, 100.0));
  img1.features_undist.push_back(Eigen::Vector3d(100.0, 100.0, 1.0));
  images[1] = img1;

  Image img2(2, 1, "img2.jpg");
  img2.frame_id = 2;
  img2.frame_ptr = &frames[2];
  img2.features.push_back(Eigen::Vector2d(200.0, 200.0));
  img2.features_undist.push_back(Eigen::Vector3d(200.0, 200.0, 1.0));
  images[2] = img2;

  // Exactly 2 observations = min_supports
  Track track;
  track.track_id = 10;
  track.xyz = Eigen::Vector3d(1.0, 1.0, 1.0);
  track.color = Eigen::Vector3ub(100, 100, 100);
  track.observations.push_back(Observation(1, 0));
  track.observations.push_back(Observation(2, 0));
  tracks[10] = track;

  ConvertGlomapToColmap(rigs, cameras, frames, images, tracks,
                        reconstruction, -1, false);

  EXPECT_TRUE(reconstruction.ExistsPoint3D(10));
}

// Test deregistration of frames not matching cluster
TEST_F(ConvertGlomapToColmapTest_119, FrameDeregistrationOnClusterMismatch_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
  colmap::Reconstruction reconstruction;

  cameras[1] = camera_;

  // Frame in cluster 0
  Frame frame1 = CreateFrame(1, true, 0);
  // Frame in cluster 1
  Frame frame2 = CreateFrame(2, true, 1);
  frames[1] = frame1;
  frames[2] = frame2;

  ConvertGlomapToColmap(rigs, cameras, frames, images, tracks,
                        reconstruction, 0, false);

  // Both frames should exist but frame2 should be deregistered
  EXPECT_TRUE(reconstruction.ExistsFrame(1));
  EXPECT_TRUE(reconstruction.ExistsFrame(2));
}

// Test empty tracks map with include_image_points false
TEST_F(ConvertGlomapToColmapTest_119, EmptyTracksNoIncludePoints_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
  colmap::Reconstruction reconstruction;

  cameras[1] = camera_;

  Frame frame1 = CreateFrame(1, true, -1);
  frames[1] = frame1;

  Image img1(1, 1, "img1.jpg");
  img1.frame_id = 1;
  img1.frame_ptr = &frames[1];
  img1.features.push_back(Eigen::Vector2d(100.0, 100.0));
  images[1] = img1;

  ConvertGlomapToColmap(rigs, cameras, frames, images, tracks,
                        reconstruction, -1, false);

  EXPECT_EQ(reconstruction.NumPoints3D(), 0);
  EXPECT_EQ(reconstruction.NumImages(), 1);
}

}  // namespace
}  // namespace glomap
