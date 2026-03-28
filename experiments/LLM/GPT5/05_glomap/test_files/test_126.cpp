// File: pose_io_test_126.cc

#include <gtest/gtest.h>
#include <unordered_map>
#include <fstream>
#include <cstdio>

#include <Eigen/Core>
#include <Eigen/Geometry>

// Adjust these include paths to match your project structure.
#include "glomap/io/pose_io.h"
#include "glomap/scene/image.h"
#include "glomap/scene/frame.h"

namespace glomap {

class ReadGravityTest_126 : public ::testing::Test {
protected:
  std::unordered_map<image_t, Image> images_;

  std::string MakeGravityFile(const std::string& content,
                              const std::string& suffix) {
    const std::string path = "gravity_test_126_" + suffix + ".txt";
    std::ofstream ofs(path);
    ofs << content;
    return path;
  }

  void RemoveFileIfExists(const std::string& path) {
    if (!path.empty()) {
      std::remove(path.c_str());
    }
  }

  void TearDown() override {
    // Best-effort cleanup of files we may have created
    RemoveFileIfExists("gravity_test_126_single.txt");
    RemoveFileIfExists("gravity_test_126_nomatch.txt");
    RemoveFileIfExists("gravity_test_126_multi.txt");
    RemoveFileIfExists("gravity_test_126_invalid.txt");
    RemoveFileIfExists("gravity_test_126_empty.txt");
  }
};

// Normal operation: matching image name with trivial frame should update gravity
TEST_F(ReadGravityTest_126, SetsGravityForMatchingImage_126) {
  image_t img_id = 1;
  camera_t cam_id = 10;

  Image image(img_id, cam_id, "img1.jpg");
  Frame frame;
  image.frame_ptr = &frame;
  images_.emplace(img_id, image);

  const std::string path =
      MakeGravityFile("img1.jpg 0.0 1.0 9.81\n", "single");

  ReadGravity(path, images_);

  const auto& updated = images_.at(img_id);
  ASSERT_NE(updated.frame_ptr, nullptr);

  // We only rely on public interface / observable behavior
  EXPECT_TRUE(updated.frame_ptr->gravity_info.has_gravity);

  const Eigen::Vector3d gravity = updated.frame_ptr->gravity_info.GetGravity();
  EXPECT_DOUBLE_EQ(gravity[0], 0.0);
  EXPECT_DOUBLE_EQ(gravity[1], 1.0);
  EXPECT_DOUBLE_EQ(gravity[2], 9.81);
}

// Boundary: line with non-matching image name should not modify existing image
TEST_F(ReadGravityTest_126, NonMatchingNameDoesNotChangeGravity_126) {
  image_t img_id = 2;
  camera_t cam_id = 20;

  Image image(img_id, cam_id, "img2.jpg");
  Frame frame;
  image.frame_ptr = &frame;
  // Ensure initial state is “no gravity”
  image.frame_ptr->gravity_info.has_gravity = false;
  images_.emplace(img_id, image);

  const std::string path =
      MakeGravityFile("other.jpg 1.0 2.0 3.0\n", "nomatch");

  ReadGravity(path, images_);

  const auto& updated = images_.at(img_id);
  ASSERT_NE(updated.frame_ptr, nullptr);
  // Since the name did not match, gravity should still be absent.
  EXPECT_FALSE(updated.frame_ptr->gravity_info.has_gravity);
}

// Normal operation: multiple lines, only matching names should be updated
TEST_F(ReadGravityTest_126, MultipleLinesOnlyMatchingImagesUpdated_126) {
  image_t id1 = 1;
  image_t id2 = 2;
  image_t id3 = 3;
  camera_t cam_id = 30;

  Image img1(id1, cam_id, "a.jpg");
  Image img2(id2, cam_id, "b.jpg");
  Image img3(id3, cam_id, "c.jpg");

  Frame frame1;
  Frame frame2;
  Frame frame3;

  img1.frame_ptr = &frame1;
  img2.frame_ptr = &frame2;
  img3.frame_ptr = &frame3;

  img1.frame_ptr->gravity_info.has_gravity = false;
  img2.frame_ptr->gravity_info.has_gravity = false;
  img3.frame_ptr->gravity_info.has_gravity = false;

  images_.emplace(id1, img1);
  images_.emplace(id2, img2);
  images_.emplace(id3, img3);

  // Second line has non-matching name "x.jpg"
  const std::string content =
      "a.jpg 0.0 0.0 1.0\n"
      "x.jpg 9.0 9.0 9.0\n"
      "c.jpg 1.0 2.0 3.0\n";

  const std::string path = MakeGravityFile(content, "multi");

  ReadGravity(path, images_);

  const auto& updated1 = images_.at(id1);
  const auto& updated2 = images_.at(id2);
  const auto& updated3 = images_.at(id3);

  EXPECT_TRUE(updated1.frame_ptr->gravity_info.has_gravity);
  EXPECT_FALSE(updated2.frame_ptr->gravity_info.has_gravity);
  EXPECT_TRUE(updated3.frame_ptr->gravity_info.has_gravity);

  Eigen::Vector3d g1 = updated1.frame_ptr->gravity_info.GetGravity();
  Eigen::Vector3d g3 = updated3.frame_ptr->gravity_info.GetGravity();

  EXPECT_DOUBLE_EQ(g1[0], 0.0);
  EXPECT_DOUBLE_EQ(g1[1], 0.0);
  EXPECT_DOUBLE_EQ(g1[2], 1.0);

  EXPECT_DOUBLE_EQ(g3[0], 1.0);
  EXPECT_DOUBLE_EQ(g3[1], 2.0);
  EXPECT_DOUBLE_EQ(g3[2], 3.0);
}

// Boundary: non-existing file path → no changes and no crash
TEST_F(ReadGravityTest_126, NonExistingFileDoesNotChangeImages_126) {
  image_t img_id = 5;
  camera_t cam_id = 50;

  Image image(img_id, cam_id, "img5.jpg");
  Frame frame;
  image.frame_ptr = &frame;
  image.frame_ptr->gravity_info.has_gravity = false;
  images_.emplace(img_id, image);

  // Path that we do not create
  const std::string bogus_path = "gravity_test_126_nonexistent.txt";

  ReadGravity(bogus_path, images_);

  const auto& updated = images_.at(img_id);
  ASSERT_NE(updated.frame_ptr, nullptr);
  EXPECT_FALSE(updated.frame_ptr->gravity_info.has_gravity);
}

// Error case: invalid numeric fields should propagate std::invalid_argument
TEST_F(ReadGravityTest_126, InvalidNumericValuesThrowException_126) {
  image_t img_id = 7;
  camera_t cam_id = 70;

  Image image(img_id, cam_id, "img7.jpg");
  Frame frame;
  image.frame_ptr = &frame;
  images_.emplace(img_id, image);

  const std::string path =
      MakeGravityFile("img7.jpg a b c\n", "invalid");

  EXPECT_THROW(ReadGravity(path, images_), std::invalid_argument);
}

// Boundary: empty file → no updates and no crash
TEST_F(ReadGravityTest_126, EmptyGravityFileNoUpdates_126) {
  image_t img_id = 8;
  camera_t cam_id = 80;

  Image image(img_id, cam_id, "img8.jpg");
  Frame frame;
  image.frame_ptr = &frame;
  image.frame_ptr->gravity_info.has_gravity = false;
  images_.emplace(img_id, image);

  const std::string path = MakeGravityFile("", "empty");

  ReadGravity(path, images_);

  const auto& updated = images_.at(img_id);
  ASSERT_NE(updated.frame_ptr, nullptr);
  EXPECT_FALSE(updated.frame_ptr->gravity_info.has_gravity);
}

}  // namespace glomap
