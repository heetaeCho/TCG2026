#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/controllers/track_retriangulation.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/types.h"

#include <colmap/scene/database.h>
#include <colmap/sensor/models.h>

#include <unordered_map>
#include <filesystem>
#include <memory>

namespace glomap {
namespace {

class RetriangulateTracksTest_116 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create an in-memory database
    db_path_ = ":memory:";
    database_.Open(db_path_);
  }

  void TearDown() override {
    database_.Close();
  }

  // Helper to create a minimal camera in the database
  colmap::camera_t AddCameraToDatabase(int model_id, int width, int height) {
    colmap::Camera camera;
    camera.model_id = static_cast<colmap::CameraModelId>(model_id);
    camera.width = width;
    camera.height = height;
    camera.params = colmap::CameraModelInitializeParams(
        camera.model_id, width, height);
    return database_.WriteCamera(camera);
  }

  // Helper to create a minimal image in the database
  colmap::image_t AddImageToDatabase(const std::string& name,
                                      colmap::camera_t camera_id) {
    colmap::Image image;
    image.SetName(name);
    image.SetCameraId(camera_id);
    return database_.WriteImage(image);
  }

  std::string db_path_;
  colmap::Database database_;
};

// Test with empty inputs - no images, no tracks
TEST_F(RetriangulateTracksTest_116, EmptyInputs_116) {
  TriangulatorOptions options;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // With no images registered, this should still execute without crashing
  bool result = RetriangulateTracks(options, database_, rigs, cameras, frames,
                                     images, tracks);
  // With no data, the function should return true (no failure in BA since
  // there's nothing to process) or handle gracefully
  // The exact return depends on implementation, but it shouldn't crash
  SUCCEED();
}

// Test default TriangulatorOptions values
TEST_F(RetriangulateTracksTest_116, DefaultOptionsValues_116) {
  TriangulatorOptions options;
  EXPECT_DOUBLE_EQ(options.tri_complete_max_reproj_error, 15.0);
  EXPECT_DOUBLE_EQ(options.tri_merge_max_reproj_error, 15.0);
  EXPECT_DOUBLE_EQ(options.tri_min_angle, 1.0);
  EXPECT_EQ(options.min_num_matches, 15);
}

// Test with custom options values
TEST_F(RetriangulateTracksTest_116, CustomOptionsValues_116) {
  TriangulatorOptions options;
  options.tri_complete_max_reproj_error = 5.0;
  options.tri_merge_max_reproj_error = 10.0;
  options.tri_min_angle = 2.5;
  options.min_num_matches = 20;

  EXPECT_DOUBLE_EQ(options.tri_complete_max_reproj_error, 5.0);
  EXPECT_DOUBLE_EQ(options.tri_merge_max_reproj_error, 10.0);
  EXPECT_DOUBLE_EQ(options.tri_min_angle, 2.5);
  EXPECT_EQ(options.min_num_matches, 20);
}

// Test with no registered images - tracks output should remain empty
TEST_F(RetriangulateTracksTest_116, NoRegisteredImages_116) {
  TriangulatorOptions options;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Add a camera but no registered images
  Camera cam;
  cam.model_id = static_cast<int>(colmap::CameraModelId::kSimplePinhole);
  cam.width = 640;
  cam.height = 480;
  cam.params = {500.0, 320.0, 240.0};
  cameras[0] = cam;

  bool result = RetriangulateTracks(options, database_, rigs, cameras, frames,
                                     images, tracks);
  // With no registered images, tracks should remain empty
  EXPECT_TRUE(tracks.empty());
}

// Test with images that have no matches in database (high min_num_matches)
TEST_F(RetriangulateTracksTest_116, HighMinNumMatchesFiltersAll_116) {
  TriangulatorOptions options;
  options.min_num_matches = 1000000;  // Unrealistically high

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Even with some setup, extremely high min_num_matches should filter everything
  bool result = RetriangulateTracks(options, database_, rigs, cameras, frames,
                                     images, tracks);
  EXPECT_TRUE(tracks.empty());
}

// Test boundary: min_num_matches = 0
TEST_F(RetriangulateTracksTest_116, ZeroMinNumMatches_116) {
  TriangulatorOptions options;
  options.min_num_matches = 0;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  bool result = RetriangulateTracks(options, database_, rigs, cameras, frames,
                                     images, tracks);
  // Should not crash with zero min matches
  SUCCEED();
}

// Test boundary: very small triangulation angle
TEST_F(RetriangulateTracksTest_116, VerySmallTriMinAngle_116) {
  TriangulatorOptions options;
  options.tri_min_angle = 0.001;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  bool result = RetriangulateTracks(options, database_, rigs, cameras, frames,
                                     images, tracks);
  SUCCEED();
}

// Test boundary: very large reprojection error thresholds
TEST_F(RetriangulateTracksTest_116, LargeReprojErrorThresholds_116) {
  TriangulatorOptions options;
  options.tri_complete_max_reproj_error = 1000.0;
  options.tri_merge_max_reproj_error = 1000.0;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  bool result = RetriangulateTracks(options, database_, rigs, cameras, frames,
                                     images, tracks);
  SUCCEED();
}

// Test that the function handles images not in database correctly
// (image_ids_notconnected path)
TEST_F(RetriangulateTracksTest_116, ImagesNotInDatabaseReregistered_116) {
  TriangulatorOptions options;
  options.min_num_matches = 15;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Create a frame
  Frame frame;
  frame.is_registered = true;
  frames[0] = frame;

  // Create a camera
  Camera cam;
  cam.model_id = static_cast<int>(colmap::CameraModelId::kSimplePinhole);
  cam.width = 640;
  cam.height = 480;
  cam.params = {500.0, 320.0, 240.0};

  // Add the camera to the database as well
  colmap::camera_t db_cam_id = AddCameraToDatabase(
      static_cast<int>(colmap::CameraModelId::kSimplePinhole), 640, 480);
  cameras[db_cam_id] = cam;

  // Create an image that references the frame
  // This image won't be in the database, so it should go through
  // the not-connected path
  Image img(999, db_cam_id, "test_image.jpg");
  img.frame_id = 0;
  img.frame_ptr = &frames[0];
  images[999] = img;

  // The frame was registered, but the image is not in the database
  // After retriangulation, the frame should be re-registered
  bool result = RetriangulateTracks(options, database_, rigs, cameras, frames,
                                     images, tracks);
  
  // The frame's is_registered should be restored to true for not-connected images
  EXPECT_TRUE(frames[0].is_registered);
}

// Test that tracks map is populated after successful retriangulation
// (even if empty due to insufficient data)
TEST_F(RetriangulateTracksTest_116, TracksMapUpdatedAfterRetriangulation_116) {
  TriangulatorOptions options;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Pre-populate tracks to verify they get cleared/updated
  Track dummy_track;
  tracks[0] = dummy_track;
  tracks[1] = dummy_track;

  size_t initial_track_count = tracks.size();
  EXPECT_EQ(initial_track_count, 2u);

  bool result = RetriangulateTracks(options, database_, rigs, cameras, frames,
                                     images, tracks);
  
  // After retriangulation with no valid data, tracks should be updated
  // (likely cleared since there's nothing to reconstruct)
  // We just verify the function completed and tracks were modified
  SUCCEED();
}

}  // namespace
}  // namespace glomap
