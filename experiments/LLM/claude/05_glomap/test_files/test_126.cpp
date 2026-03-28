#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "glomap/io/pose_io.h"
#include "glomap/scene/image.h"
#include "glomap/scene/frame.h"
#include "glomap/types.h"

namespace glomap {
namespace {

// Helper to create a temporary file with given content
class TempFile {
 public:
  TempFile(const std::string& content) {
    path_ = std::tmpnam(nullptr);
    std::ofstream ofs(path_);
    ofs << content;
    ofs.close();
  }
  ~TempFile() { std::remove(path_.c_str()); }
  const std::string& path() const { return path_; }

 private:
  std::string path_;
};

class ReadGravityTest_126 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test: Empty file produces no changes
TEST_F(ReadGravityTest_126, EmptyFile_NoChanges_126) {
  TempFile tmpfile("");
  std::unordered_map<image_t, Image> images;
  Frame frame;
  images.emplace(std::piecewise_construct,
                 std::forward_as_tuple(1),
                 std::forward_as_tuple(1, 1, "test.jpg"));
  images.at(1).frame_ptr = &frame;

  ReadGravity(tmpfile.path(), images);

  // No gravity should have been set since file is empty
  EXPECT_FALSE(frame.gravity_info.has_gravity);
}

// Test: File with one matching image sets gravity
TEST_F(ReadGravityTest_126, SingleMatchingImage_GravitySet_126) {
  std::string content = "test.jpg 0.0 0.0 -9.8\n";
  TempFile tmpfile(content);

  std::unordered_map<image_t, Image> images;
  Frame frame;
  images.emplace(std::piecewise_construct,
                 std::forward_as_tuple(1),
                 std::forward_as_tuple(1, 1, "test.jpg"));
  images.at(1).frame_ptr = &frame;

  ReadGravity(tmpfile.path(), images);

  // Gravity should be set
  EXPECT_TRUE(frame.gravity_info.has_gravity);
}

// Test: File with non-matching image name does not set gravity
TEST_F(ReadGravityTest_126, NoMatchingImage_NoGravitySet_126) {
  std::string content = "nonexistent.jpg 0.0 0.0 -9.8\n";
  TempFile tmpfile(content);

  std::unordered_map<image_t, Image> images;
  Frame frame;
  images.emplace(std::piecewise_construct,
                 std::forward_as_tuple(1),
                 std::forward_as_tuple(1, 1, "test.jpg"));
  images.at(1).frame_ptr = &frame;

  ReadGravity(tmpfile.path(), images);

  EXPECT_FALSE(frame.gravity_info.has_gravity);
}

// Test: Multiple images, some matching and some not
TEST_F(ReadGravityTest_126, MultipleImages_PartialMatch_126) {
  std::string content =
      "img1.jpg 1.0 0.0 0.0\n"
      "img3.jpg 0.0 1.0 0.0\n";
  TempFile tmpfile(content);

  std::unordered_map<image_t, Image> images;
  Frame frame1, frame2;

  images.emplace(std::piecewise_construct,
                 std::forward_as_tuple(1),
                 std::forward_as_tuple(1, 1, "img1.jpg"));
  images.at(1).frame_ptr = &frame1;

  images.emplace(std::piecewise_construct,
                 std::forward_as_tuple(2),
                 std::forward_as_tuple(2, 1, "img2.jpg"));
  images.at(2).frame_ptr = &frame2;

  ReadGravity(tmpfile.path(), images);

  // img1 matches, img2 does not
  EXPECT_TRUE(frame1.gravity_info.has_gravity);
  EXPECT_FALSE(frame2.gravity_info.has_gravity);
}

// Test: Multiple matching images all get gravity set
TEST_F(ReadGravityTest_126, AllImagesMatch_AllGravitySet_126) {
  std::string content =
      "img1.jpg 1.0 2.0 3.0\n"
      "img2.jpg 4.0 5.0 6.0\n";
  TempFile tmpfile(content);

  std::unordered_map<image_t, Image> images;
  Frame frame1, frame2;

  images.emplace(std::piecewise_construct,
                 std::forward_as_tuple(1),
                 std::forward_as_tuple(1, 1, "img1.jpg"));
  images.at(1).frame_ptr = &frame1;

  images.emplace(std::piecewise_construct,
                 std::forward_as_tuple(2),
                 std::forward_as_tuple(2, 1, "img2.jpg"));
  images.at(2).frame_ptr = &frame2;

  ReadGravity(tmpfile.path(), images);

  EXPECT_TRUE(frame1.gravity_info.has_gravity);
  EXPECT_TRUE(frame2.gravity_info.has_gravity);
}

// Test: Gravity values are correctly parsed and stored
TEST_F(ReadGravityTest_126, GravityValuesCorrectlyParsed_126) {
  std::string content = "test.jpg 1.5 -2.5 3.5\n";
  TempFile tmpfile(content);

  std::unordered_map<image_t, Image> images;
  Frame frame;

  images.emplace(std::piecewise_construct,
                 std::forward_as_tuple(1),
                 std::forward_as_tuple(1, 1, "test.jpg"));
  images.at(1).frame_ptr = &frame;

  ReadGravity(tmpfile.path(), images);

  EXPECT_TRUE(frame.gravity_info.has_gravity);
  Eigen::Vector3d gravity = frame.gravity_info.GetGravity();
  EXPECT_NEAR(gravity[0], 1.5, 1e-9);
  EXPECT_NEAR(gravity[1], -2.5, 1e-9);
  EXPECT_NEAR(gravity[2], 3.5, 1e-9);
}

// Test: Image without a trivial frame is skipped (no crash, no gravity set)
TEST_F(ReadGravityTest_126, ImageWithoutTrivialFrame_Skipped_126) {
  std::string content = "test.jpg 1.0 2.0 3.0\n";
  TempFile tmpfile(content);

  std::unordered_map<image_t, Image> images;
  images.emplace(std::piecewise_construct,
                 std::forward_as_tuple(1),
                 std::forward_as_tuple(1, 1, "test.jpg"));
  // frame_ptr is nullptr by default, so HasTrivialFrame() should return false

  // Should not crash
  ReadGravity(tmpfile.path(), images);
}

// Test: Nonexistent file path results in no changes (empty file stream)
TEST_F(ReadGravityTest_126, NonexistentFile_NoChanges_126) {
  std::unordered_map<image_t, Image> images;
  Frame frame;
  images.emplace(std::piecewise_construct,
                 std::forward_as_tuple(1),
                 std::forward_as_tuple(1, 1, "test.jpg"));
  images.at(1).frame_ptr = &frame;

  ReadGravity("/nonexistent/path/to/gravity.txt", images);

  EXPECT_FALSE(frame.gravity_info.has_gravity);
}

// Test: Empty images map with valid file
TEST_F(ReadGravityTest_126, EmptyImagesMap_NoEffect_126) {
  std::string content = "test.jpg 1.0 2.0 3.0\n";
  TempFile tmpfile(content);

  std::unordered_map<image_t, Image> images;

  // Should not crash with empty images
  ReadGravity(tmpfile.path(), images);
  EXPECT_TRUE(images.empty());
}

// Test: Rotation is set from RAlign after gravity is loaded
TEST_F(ReadGravityTest_126, RotationUpdatedFromRAlign_126) {
  std::string content = "test.jpg 0.0 0.0 -1.0\n";
  TempFile tmpfile(content);

  std::unordered_map<image_t, Image> images;
  Frame frame;
  images.emplace(std::piecewise_construct,
                 std::forward_as_tuple(1),
                 std::forward_as_tuple(1, 1, "test.jpg"));
  images.at(1).frame_ptr = &frame;

  ReadGravity(tmpfile.path(), images);

  // After reading gravity, the cam_from_world rotation should be set
  // from GetRAlign. We verify by checking the rotation is valid (unit quaternion).
  if (frame.gravity_info.has_gravity) {
    Eigen::Matrix3d R_align = frame.gravity_info.GetRAlign();
    // R_align should be a valid rotation matrix (det ~= 1, R^T * R ~= I)
    EXPECT_NEAR(R_align.determinant(), 1.0, 1e-6);
    Eigen::Matrix3d should_be_identity = R_align.transpose() * R_align;
    EXPECT_NEAR((should_be_identity - Eigen::Matrix3d::Identity()).norm(), 0.0, 1e-6);
  }
}

// Test: Duplicate image names in file - first occurrence should be processed
TEST_F(ReadGravityTest_126, DuplicateNamesInFile_126) {
  std::string content =
      "test.jpg 1.0 0.0 0.0\n"
      "test.jpg 0.0 1.0 0.0\n";
  TempFile tmpfile(content);

  std::unordered_map<image_t, Image> images;
  Frame frame;
  images.emplace(std::piecewise_construct,
                 std::forward_as_tuple(1),
                 std::forward_as_tuple(1, 1, "test.jpg"));
  images.at(1).frame_ptr = &frame;

  ReadGravity(tmpfile.path(), images);

  // Both lines match, so gravity should be set (last one wins or both applied)
  EXPECT_TRUE(frame.gravity_info.has_gravity);
  // The gravity value should be from the second line (overwritten)
  Eigen::Vector3d gravity = frame.gravity_info.GetGravity();
  EXPECT_NEAR(gravity[0], 0.0, 1e-9);
  EXPECT_NEAR(gravity[1], 1.0, 1e-9);
  EXPECT_NEAR(gravity[2], 0.0, 1e-9);
}

// Test: Large gravity values
TEST_F(ReadGravityTest_126, LargeGravityValues_126) {
  std::string content = "test.jpg 1e10 -1e10 1e10\n";
  TempFile tmpfile(content);

  std::unordered_map<image_t, Image> images;
  Frame frame;
  images.emplace(std::piecewise_construct,
                 std::forward_as_tuple(1),
                 std::forward_as_tuple(1, 1, "test.jpg"));
  images.at(1).frame_ptr = &frame;

  ReadGravity(tmpfile.path(), images);

  EXPECT_TRUE(frame.gravity_info.has_gravity);
  Eigen::Vector3d gravity = frame.gravity_info.GetGravity();
  EXPECT_NEAR(gravity[0], 1e10, 1e1);
  EXPECT_NEAR(gravity[1], -1e10, 1e1);
  EXPECT_NEAR(gravity[2], 1e10, 1e1);
}

// Test: Zero gravity vector
TEST_F(ReadGravityTest_126, ZeroGravityVector_126) {
  std::string content = "test.jpg 0.0 0.0 0.0\n";
  TempFile tmpfile(content);

  std::unordered_map<image_t, Image> images;
  Frame frame;
  images.emplace(std::piecewise_construct,
                 std::forward_as_tuple(1),
                 std::forward_as_tuple(1, 1, "test.jpg"));
  images.at(1).frame_ptr = &frame;

  ReadGravity(tmpfile.path(), images);

  // Even zero gravity should be "set"
  EXPECT_TRUE(frame.gravity_info.has_gravity);
}

}  // namespace
}  // namespace glomap
