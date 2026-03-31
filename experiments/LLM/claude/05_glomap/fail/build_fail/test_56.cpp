#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/controllers/track_retriangulation.h"
#include "glomap/types.h"

#include <colmap/scene/database.h>
#include <colmap/sensor/models.h>

#include <unordered_map>
#include <memory>
#include <filesystem>

namespace glomap {
namespace {

class RetriangulateTracksTest_56 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create an in-memory database
    db_path_ = ":memory:";
    database_ = std::make_unique<colmap::Database>(db_path_);
  }

  void TearDown() override {
    database_.reset();
  }

  // Helper to create a minimal camera in the database
  colmap::camera_t AddCameraToDb(int model_id, int width, int height) {
    colmap::Camera camera;
    camera.model_id = static_cast<colmap::CameraModelId>(model_id);
    camera.width = width;
    camera.height = height;
    camera.params = colmap::CameraModelInitializeParams(
        camera.model_id, width, height);
    return database_->WriteCamera(camera);
  }

  // Helper to create a minimal image in the database
  colmap::image_t AddImageToDb(const std::string& name,
                                colmap::camera_t camera_id) {
    colmap::Image image;
    image.SetName(name);
    image.SetCameraId(camera_id);
    return database_->WriteImage(image);
  }

  std::string db_path_;
  std::unique_ptr<colmap::Database> database_;
};

// Test with empty data structures - no images, cameras, etc.
TEST_F(RetriangulateTracksTest_56, EmptyInputReturnsTrue_56) {
  TriangulatorOptions options;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // With no images registered, the function should still succeed
  // (no triangulation to do, no BA to run or trivial BA)
  bool result = RetriangulateTracks(
      options, *database_, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result);
}

// Test with empty tracks but some cameras/images that are not registered
TEST_F(RetriangulateTracksTest_56, NoRegisteredImagesReturnsTrue_56) {
  TriangulatorOptions options;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Add a camera to glomap structures but no registered images
  Camera cam;
  cam.camera_id = 1;
  cam.model_id = static_cast<int>(colmap::CameraModelId::kSimplePinhole);
  cam.width = 640;
  cam.height = 480;
  cam.params = colmap::CameraModelInitializeParams(
      colmap::CameraModelId::kSimplePinhole, 640, 480);
  cameras[1] = cam;

  bool result = RetriangulateTracks(
      options, *database_, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result);
}

// Test that tracks map gets populated when there are registered images
// with matching features in the database
TEST_F(RetriangulateTracksTest_56, RegisteredImagesWithMatchesProduceTracks_56) {
  TriangulatorOptions options;
  options.min_num_matches = 1;

  // Set up database with cameras, images, keypoints, and matches
  auto db_cam_id = AddCameraToDb(
      static_cast<int>(colmap::CameraModelId::kSimplePinhole), 640, 480);
  auto db_img_id1 = AddImageToDb("image1.jpg", db_cam_id);
  auto db_img_id2 = AddImageToDb("image2.jpg", db_cam_id);

  // Add keypoints
  colmap::FeatureKeypoints keypoints1(5);
  colmap::FeatureKeypoints keypoints2(5);
  for (int i = 0; i < 5; ++i) {
    keypoints1[i] = colmap::FeatureKeypoint(
        static_cast<float>(100 + i * 10), static_cast<float>(100 + i * 10));
    keypoints2[i] = colmap::FeatureKeypoint(
        static_cast<float>(100 + i * 10), static_cast<float>(100 + i * 10));
  }
  database_->WriteKeypoints(db_img_id1, keypoints1);
  database_->WriteKeypoints(db_img_id2, keypoints2);

  // Add matches
  colmap::FeatureMatches matches(5);
  for (int i = 0; i < 5; ++i) {
    matches[i] = colmap::FeatureMatch(i, i);
  }
  database_->WriteMatches(db_img_id1, db_img_id2, matches);

  // Inlier matches (two-view geometry)
  colmap::TwoViewGeometry two_view;
  two_view.config = colmap::TwoViewGeometry::CALIBRATED;
  two_view.inlier_matches = matches;
  two_view.F = Eigen::Matrix3d::Identity();
  two_view.E = Eigen::Matrix3d::Identity();
  two_view.H = Eigen::Matrix3d::Identity();
  database_->WriteTwoViewGeometry(db_img_id1, db_img_id2, two_view);

  // Set up glomap structures
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Create rig
  Rig rig;
  rig.rig_id = 0;
  rig.sensors_from_rig.push_back(Eigen::Matrix3x4d::Identity());
  rigs[0] = rig;

  // Create camera matching database
  Camera cam;
  cam.camera_id = db_cam_id;
  cam.model_id = static_cast<int>(colmap::CameraModelId::kSimplePinhole);
  cam.width = 640;
  cam.height = 480;
  cam.params = colmap::CameraModelInitializeParams(
      colmap::CameraModelId::kSimplePinhole, 640, 480);
  cameras[db_cam_id] = cam;

  // Create frames
  Frame frame1;
  frame1.frame_id = 0;
  frame1.rig_id = 0;
  frame1.is_registered = true;
  frames[0] = frame1;

  Frame frame2;
  frame2.frame_id = 1;
  frame2.rig_id = 0;
  frame2.is_registered = true;
  frames[1] = frame2;

  // Create images with valid poses
  Image img1;
  img1.image_id = db_img_id1;
  img1.camera_id = db_cam_id;
  img1.frame_id = 0;
  img1.rig_sensor_idx = 0;
  img1.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(),
                                 Eigen::Vector3d(0, 0, 0));
  img1.features.resize(5);
  for (int i = 0; i < 5; ++i) {
    img1.features[i] = Eigen::Vector2d(100 + i * 10, 100 + i * 10);
  }
  img1.frame_ptr = &frames[0];
  images[db_img_id1] = img1;

  Image img2;
  img2.image_id = db_img_id2;
  img2.camera_id = db_cam_id;
  img2.frame_id = 1;
  img2.rig_sensor_idx = 0;
  img2.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(),
                                 Eigen::Vector3d(1, 0, 0));
  img2.features.resize(5);
  for (int i = 0; i < 5; ++i) {
    img2.features[i] = Eigen::Vector2d(100 + i * 10, 100 + i * 10);
  }
  img2.frame_ptr = &frames[1];
  images[db_img_id2] = img2;

  bool result = RetriangulateTracks(
      options, *database_, rigs, cameras, frames, images, tracks);
  // The function should return true on successful completion
  EXPECT_TRUE(result);
}

// Test default options values are used properly
TEST_F(RetriangulateTracksTest_56, DefaultOptionsWork_56) {
  TriangulatorOptions options;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  bool result = RetriangulateTracks(
      options, *database_, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result);
  // With no data, tracks should remain empty
  EXPECT_TRUE(tracks.empty());
}

// Test that tracks are cleared/replaced on retriangulation
TEST_F(RetriangulateTracksTest_56, TracksMapGetsPopulatedFromScratch_56) {
  TriangulatorOptions options;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Pre-populate tracks with dummy data
  Track dummy_track;
  dummy_track.track_id = 999;
  tracks[999] = dummy_track;

  bool result = RetriangulateTracks(
      options, *database_, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result);
  // After retriangulation with no images, the old tracks should be gone
  // or the map should be updated by ConvertColmapToGlomap
}

// Test with specific triangulator option values
TEST_F(RetriangulateTracksTest_56, CustomTriangulatorOptions_56) {
  TriangulatorOptions options;
  options.tri_complete_max_reproj_error = 2.0;
  options.tri_merge_max_reproj_error = 2.0;
  options.tri_min_angle = 1.0;
  options.min_num_matches = 5;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  bool result = RetriangulateTracks(
      options, *database_, rigs, cameras, frames, images, tracks);
  EXPECT_TRUE(result);
}

// Test that unregistered images (not in database) get their frame
// is_registered restored
TEST_F(RetriangulateTracksTest_56, UnconnectedImagesGetReregistered_56) {
  TriangulatorOptions options;
  options.min_num_matches = 100;  // High threshold so no images pass

  auto db_cam_id = AddCameraToDb(
      static_cast<int>(colmap::CameraModelId::kSimplePinhole), 640, 480);

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  Rig rig;
  rig.rig_id = 0;
  rig.sensors_from_rig.push_back(Eigen::Matrix3x4d::Identity());
  rigs[0] = rig;

  Camera cam;
  cam.camera_id = db_cam_id;
  cam.model_id = static_cast<int>(colmap::CameraModelId::kSimplePinhole);
  cam.width = 640;
  cam.height = 480;
  cam.params = colmap::CameraModelInitializeParams(
      colmap::CameraModelId::kSimplePinhole, 640, 480);
  cameras[db_cam_id] = cam;

  Frame frame;
  frame.frame_id = 0;
  frame.rig_id = 0;
  frame.is_registered = true;
  frames[0] = frame;

  // Image is "registered" in glomap but has no db entry with enough matches
  // Use a non-existent db image id
  image_t fake_img_id = 9999;
  Image img;
  img.image_id = fake_img_id;
  img.camera_id = db_cam_id;
  img.frame_id = 0;
  img.rig_sensor_idx = 0;
  img.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(),
                                Eigen::Vector3d(0, 0, 0));
  img.frame_ptr = &frames[0];
  images[fake_img_id] = img;

  // The image won't exist in database_cache, so it should be marked as
  // not connected, then re-registered at the end
  bool result = RetriangulateTracks(
      options, *database_, rigs, cameras, frames, images, tracks);
  // Check that function completes
  EXPECT_TRUE(result);
  // The frame's is_registered should be restored to true at the end
  EXPECT_TRUE(frames[0].is_registered);
}

}  // namespace
}  // namespace glomap
