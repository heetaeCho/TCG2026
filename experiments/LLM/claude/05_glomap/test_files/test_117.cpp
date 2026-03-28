#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>

#include "glomap/io/colmap_io.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/types.h"

namespace glomap {
namespace {

class WriteGlomapReconstructionTest_117 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create a temporary directory for output
    test_dir_ = std::filesystem::temp_directory_path() / "glomap_test_117";
    std::filesystem::create_directories(test_dir_);
  }

  void TearDown() override {
    // Clean up
    std::filesystem::remove_all(test_dir_);
  }

  std::filesystem::path test_dir_;

  // Helper to create minimal valid test data
  void CreateMinimalTestData(
      std::unordered_map<camera_t, Camera>& cameras,
      std::unordered_map<image_t, Image>& images,
      std::unordered_map<frame_t, Frame>& frames) {
    // Create a camera
    Camera cam;
    cam.camera_id = 0;
    cam.model_id = 0;  // SIMPLE_PINHOLE
    cam.width = 640;
    cam.height = 480;
    cam.params = {500.0, 320.0, 240.0};
    cameras[0] = cam;

    // Create an image
    Image img;
    img.image_id = 0;
    img.file_name = "test.jpg";
    img.camera_id = 0;
    img.cam_from_world = Rigid3d();
    img.is_registered = true;
    images[0] = img;

    // Create a frame
    Frame frame;
    frame.is_registered = true;
    frame.cluster_id = -1;
    frames[0] = frame;
  }
};

// Test with empty data - no frames means largest_component_num stays -1
TEST_F(WriteGlomapReconstructionTest_117, EmptyDataWritesTxt_117) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  std::string output_path = test_dir_.string();

  // Should not crash with empty data
  EXPECT_NO_THROW(WriteGlomapReconstruction(
      output_path, rigs, cameras, frames, images, tracks, "txt", ""));

  // Check that directory /0 was created
  EXPECT_TRUE(std::filesystem::exists(output_path + "/0"));
}

// Test with empty data writing binary format
TEST_F(WriteGlomapReconstructionTest_117, EmptyDataWritesBin_117) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  std::string output_path = test_dir_.string();

  EXPECT_NO_THROW(WriteGlomapReconstruction(
      output_path, rigs, cameras, frames, images, tracks, "bin", ""));

  EXPECT_TRUE(std::filesystem::exists(output_path + "/0"));
}

// Test with unsupported output format - should not crash (just logs error)
TEST_F(WriteGlomapReconstructionTest_117, UnsupportedFormatDoesNotCrash_117) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  std::string output_path = test_dir_.string();

  EXPECT_NO_THROW(WriteGlomapReconstruction(
      output_path, rigs, cameras, frames, images, tracks, "xyz", ""));
}

// Test with all frames having cluster_id = -1 (single component path)
TEST_F(WriteGlomapReconstructionTest_117, AllFramesClusterNegativeOne_117) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  Frame f1;
  f1.cluster_id = -1;
  f1.is_registered = true;
  frames[0] = f1;

  Frame f2;
  f2.cluster_id = -1;
  f2.is_registered = true;
  frames[1] = f2;

  std::string output_path = test_dir_.string();

  EXPECT_NO_THROW(WriteGlomapReconstruction(
      output_path, rigs, cameras, frames, images, tracks, "txt", ""));

  // Single component, directory /0 should exist
  EXPECT_TRUE(std::filesystem::exists(output_path + "/0"));
}

// Test with frames having cluster_id = 0 (single cluster, multi-component path)
TEST_F(WriteGlomapReconstructionTest_117, SingleClusterWritesTxt_117) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  Frame f1;
  f1.cluster_id = 0;
  f1.is_registered = true;
  frames[0] = f1;

  std::string output_path = test_dir_.string();

  EXPECT_NO_THROW(WriteGlomapReconstruction(
      output_path, rigs, cameras, frames, images, tracks, "txt", ""));

  EXPECT_TRUE(std::filesystem::exists(output_path + "/0"));
}

// Test with multiple clusters
TEST_F(WriteGlomapReconstructionTest_117, MultipleClustersCreateDirectories_117) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  Frame f1;
  f1.cluster_id = 0;
  f1.is_registered = true;
  frames[0] = f1;

  Frame f2;
  f2.cluster_id = 1;
  f2.is_registered = true;
  frames[1] = f2;

  Frame f3;
  f3.cluster_id = 2;
  f3.is_registered = true;
  frames[2] = f3;

  std::string output_path = test_dir_.string();

  EXPECT_NO_THROW(WriteGlomapReconstruction(
      output_path, rigs, cameras, frames, images, tracks, "txt", ""));

  // Directories 0, 1, 2 should be created
  EXPECT_TRUE(std::filesystem::exists(output_path + "/0"));
  EXPECT_TRUE(std::filesystem::exists(output_path + "/1"));
  EXPECT_TRUE(std::filesystem::exists(output_path + "/2"));
}

// Test with multiple clusters writing binary format
TEST_F(WriteGlomapReconstructionTest_117, MultipleClustersWritesBin_117) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  Frame f1;
  f1.cluster_id = 0;
  f1.is_registered = true;
  frames[0] = f1;

  Frame f2;
  f2.cluster_id = 1;
  f2.is_registered = true;
  frames[1] = f2;

  std::string output_path = test_dir_.string();

  EXPECT_NO_THROW(WriteGlomapReconstruction(
      output_path, rigs, cameras, frames, images, tracks, "bin", ""));

  EXPECT_TRUE(std::filesystem::exists(output_path + "/0"));
  EXPECT_TRUE(std::filesystem::exists(output_path + "/1"));
}

// Test with multiple clusters and unsupported format
TEST_F(WriteGlomapReconstructionTest_117, MultipleClustersUnsupportedFormat_117) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  Frame f1;
  f1.cluster_id = 0;
  f1.is_registered = true;
  frames[0] = f1;

  std::string output_path = test_dir_.string();

  EXPECT_NO_THROW(WriteGlomapReconstruction(
      output_path, rigs, cameras, frames, images, tracks, "invalid", ""));
}

// Test that largest_component_num is correctly identified
TEST_F(WriteGlomapReconstructionTest_117, LargestComponentCorrectlyIdentified_117) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Frames with cluster_ids 0 and 3 (gap in between)
  Frame f1;
  f1.cluster_id = 0;
  f1.is_registered = true;
  frames[0] = f1;

  Frame f2;
  f2.cluster_id = 3;
  f2.is_registered = true;
  frames[1] = f2;

  std::string output_path = test_dir_.string();

  EXPECT_NO_THROW(WriteGlomapReconstruction(
      output_path, rigs, cameras, frames, images, tracks, "txt", ""));

  // Should create directories 0, 1, 2, 3 (iterates from 0 to largest_component_num)
  EXPECT_TRUE(std::filesystem::exists(output_path + "/0"));
  EXPECT_TRUE(std::filesystem::exists(output_path + "/1"));
  EXPECT_TRUE(std::filesystem::exists(output_path + "/2"));
  EXPECT_TRUE(std::filesystem::exists(output_path + "/3"));
}

// Test boundary: single frame with cluster_id = 0
TEST_F(WriteGlomapReconstructionTest_117, BoundarySingleFrameClusterZero_117) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  Frame f;
  f.cluster_id = 0;
  f.is_registered = false;
  frames[0] = f;

  std::string output_path = test_dir_.string();

  EXPECT_NO_THROW(WriteGlomapReconstruction(
      output_path, rigs, cameras, frames, images, tracks, "bin", ""));

  EXPECT_TRUE(std::filesystem::exists(output_path + "/0"));
  // Only cluster 0, so /1 should not exist
  EXPECT_FALSE(std::filesystem::exists(output_path + "/1"));
}

// Test with empty image_path (no color extraction)
TEST_F(WriteGlomapReconstructionTest_117, EmptyImagePathNoColorExtraction_117) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  std::string output_path = test_dir_.string();

  // Empty image path should skip color extraction
  EXPECT_NO_THROW(WriteGlomapReconstruction(
      output_path, rigs, cameras, frames, images, tracks, "txt", ""));
}

// Test with mixed cluster ids including -1 and positive values
TEST_F(WriteGlomapReconstructionTest_117, MixedClusterIds_117) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  Frame f1;
  f1.cluster_id = -1;
  f1.is_registered = true;
  frames[0] = f1;

  Frame f2;
  f2.cluster_id = 1;
  f2.is_registered = true;
  frames[1] = f2;

  std::string output_path = test_dir_.string();

  // largest_component_num = 1, so multi-component path
  EXPECT_NO_THROW(WriteGlomapReconstruction(
      output_path, rigs, cameras, frames, images, tracks, "txt", ""));

  EXPECT_TRUE(std::filesystem::exists(output_path + "/0"));
  EXPECT_TRUE(std::filesystem::exists(output_path + "/1"));
}

}  // namespace
}  // namespace glomap
