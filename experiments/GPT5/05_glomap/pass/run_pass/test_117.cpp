// File: glomap/test/colmap_io_test_117.cc

#include <gtest/gtest.h>

#include <cstdlib>
#include <string>
#include <unordered_map>

#include <sys/stat.h>
#include <sys/types.h>

#include "glomap/io/colmap_io.cc"  // Uses the existing implementation

namespace {

// Simple helper to remove directories recursively (best-effort).
void RemoveDirectory(const std::string& path) {
  // Best-effort cleanup; ignore return value.
  std::string cmd = "rm -rf \"" + path + "\"";
  std::system(cmd.c_str());
}

// Helper to check whether a directory exists.
bool DirectoryExists(const std::string& path) {
  struct stat info;
  if (stat(path.c_str(), &info) != 0) {
    return false;
  }
  return (info.st_mode & S_IFDIR) != 0;
}

class WriteGlomapReconstructionTest_117 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Clean up any test directories we created.
    RemoveDirectory("test_output_single_117");
    RemoveDirectory("test_output_multi_117");
    RemoveDirectory("test_output_unsupported_117");
    RemoveDirectory("test_output_with_colors_117");
  }
};

}  // namespace

namespace glomap {

// -----------------------------------------------------------------------------
// Test 1: No frames at all -> single component (directory "<path>/0") created.
// -----------------------------------------------------------------------------
TEST_F(WriteGlomapReconstructionTest_117,
       CreatesSingleComponentDirectoryWhenNoFrames_117) {
  const std::string reconstruction_path = "test_output_single_117";
  RemoveDirectory(reconstruction_path);

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;   // empty
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  WriteGlomapReconstruction(reconstruction_path, rigs, cameras, frames, images,
                            tracks, "txt", /*image_path=*/"");

  EXPECT_TRUE(DirectoryExists(reconstruction_path + "/0"));
  EXPECT_FALSE(DirectoryExists(reconstruction_path + "/1"));
}

// -----------------------------------------------------------------------------
// Test 2: Frames with cluster IDs 0..2 -> multiple components, directories
// "<path>/0", "<path>/1", "<path>/2" should exist, but not "<path>/3".
// -----------------------------------------------------------------------------
TEST_F(WriteGlomapReconstructionTest_117,
       CreatesMultipleComponentDirectoriesBasedOnMaxClusterId_117) {
  const std::string reconstruction_path = "test_output_multi_117";
  RemoveDirectory(reconstruction_path);

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  Frame frame0;
  frame0.cluster_id = 0;
  Frame frame1;
  frame1.cluster_id = 1;
  Frame frame2;
  frame2.cluster_id = 2;

  frames.emplace(static_cast<frame_t>(1), frame0);
  frames.emplace(static_cast<frame_t>(2), frame1);
  frames.emplace(static_cast<frame_t>(3), frame2);

  WriteGlomapReconstruction(reconstruction_path, rigs, cameras, frames, images,
                            tracks, "txt", /*image_path=*/"");

  EXPECT_TRUE(DirectoryExists(reconstruction_path + "/0"));
  EXPECT_TRUE(DirectoryExists(reconstruction_path + "/1"));
  EXPECT_TRUE(DirectoryExists(reconstruction_path + "/2"));
  EXPECT_FALSE(DirectoryExists(reconstruction_path + "/3"));
}

// -----------------------------------------------------------------------------
// Test 3: Non-empty image_path should still allow reconstruction and directory
// creation (color extraction is internal, we only check for no failure and
// directory existence).
// -----------------------------------------------------------------------------
TEST_F(WriteGlomapReconstructionTest_117,
       HandlesNonEmptyImagePathAndCreatesDirectory_117) {
  const std::string reconstruction_path = "test_output_with_colors_117";
  RemoveDirectory(reconstruction_path);

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Use a single frame with default cluster_id (-1) to take the single-component
  // branch.
  Frame frame;
  // cluster_id default is assumed -1.
  frames.emplace(static_cast<frame_t>(1), frame);

  WriteGlomapReconstruction(reconstruction_path, rigs, cameras, frames, images,
                            tracks, "txt", /*image_path=*/"dummy_image_path");

  EXPECT_TRUE(DirectoryExists(reconstruction_path + "/0"));
}

// -----------------------------------------------------------------------------
// Test 4: Unsupported output format should still create the directory, while
// logging an error internally (we just verify directory existence).
// -----------------------------------------------------------------------------
TEST_F(WriteGlomapReconstructionTest_117,
       UnsupportedOutputFormatStillCreatesDirectory_117) {
  const std::string reconstruction_path = "test_output_unsupported_117";
  RemoveDirectory(reconstruction_path);

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // No frames so that the single-component branch is used.
  WriteGlomapReconstruction(reconstruction_path, rigs, cameras, frames, images,
                            tracks, "unsupported_format", /*image_path=*/"");

  EXPECT_TRUE(DirectoryExists(reconstruction_path + "/0"));
}

}  // namespace glomap
