#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <cstdio>

#include "glomap/io/pose_io.h"
#include "glomap/scene/image.h"
#include "glomap/types.h"

namespace glomap {
namespace {

class WriteGlobalRotationTest_127 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create a temporary file path for testing
    test_file_path_ = "test_global_rotation_127.txt";
  }

  void TearDown() override {
    // Clean up the temporary file
    std::remove(test_file_path_.c_str());
  }

  std::string test_file_path_;

  // Helper to read file contents
  std::string ReadFileContents(const std::string& path) {
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
  }

  // Helper to count lines in file
  int CountLines(const std::string& path) {
    std::ifstream file(path);
    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
      if (!line.empty()) count++;
    }
    return count;
  }
};

// Test with empty image map - should produce an empty file
TEST_F(WriteGlobalRotationTest_127, EmptyImageMap_127) {
  std::unordered_map<image_t, Image> images;
  WriteGlobalRotation(test_file_path_, images);

  std::string contents = ReadFileContents(test_file_path_);
  EXPECT_TRUE(contents.empty());
}

// Test with a single registered image
TEST_F(WriteGlobalRotationTest_127, SingleRegisteredImage_127) {
  std::unordered_map<image_t, Image> images;

  Image img(1, 1, "image001.jpg");
  // Set the image as registered with an identity rotation
  img.cam_from_world = Rigid3d();  // Identity
  img.is_registered = true;

  images[1] = img;
  WriteGlobalRotation(test_file_path_, images);

  std::string contents = ReadFileContents(test_file_path_);
  EXPECT_FALSE(contents.empty());

  // Should contain the file name
  EXPECT_NE(contents.find("image001.jpg"), std::string::npos);

  // Count lines - should be exactly 1
  EXPECT_EQ(CountLines(test_file_path_), 1);
}

// Test with only unregistered images - should produce empty output
TEST_F(WriteGlobalRotationTest_127, OnlyUnregisteredImages_127) {
  std::unordered_map<image_t, Image> images;

  Image img(1, 1, "image001.jpg");
  // Image is not registered by default (or set explicitly)
  images[1] = img;

  WriteGlobalRotation(test_file_path_, images);

  std::string contents = ReadFileContents(test_file_path_);
  EXPECT_TRUE(contents.empty());
}

// Test with multiple registered images - output should be sorted by image_id
TEST_F(WriteGlobalRotationTest_127, MultipleRegisteredImagesSorted_127) {
  std::unordered_map<image_t, Image> images;

  Image img1(3, 1, "image003.jpg");
  img1.cam_from_world = Rigid3d();
  img1.is_registered = true;
  images[3] = img1;

  Image img2(1, 1, "image001.jpg");
  img2.cam_from_world = Rigid3d();
  img2.is_registered = true;
  images[1] = img2;

  Image img3(2, 1, "image002.jpg");
  img3.cam_from_world = Rigid3d();
  img3.is_registered = true;
  images[2] = img3;

  WriteGlobalRotation(test_file_path_, images);

  // Read lines and check they are in sorted order by image_id
  std::ifstream file(test_file_path_);
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    if (!line.empty()) lines.push_back(line);
  }

  EXPECT_EQ(lines.size(), 3);
  // Since std::set sorts by image_id, image001 (id=1) should come first
  EXPECT_NE(lines[0].find("image001.jpg"), std::string::npos);
  EXPECT_NE(lines[1].find("image002.jpg"), std::string::npos);
  EXPECT_NE(lines[2].find("image003.jpg"), std::string::npos);
}

// Test with mix of registered and unregistered images
TEST_F(WriteGlobalRotationTest_127, MixedRegisteredAndUnregistered_127) {
  std::unordered_map<image_t, Image> images;

  Image img1(1, 1, "registered.jpg");
  img1.cam_from_world = Rigid3d();
  img1.is_registered = true;
  images[1] = img1;

  Image img2(2, 1, "unregistered.jpg");
  // Not registered
  images[2] = img2;

  Image img3(3, 1, "also_registered.jpg");
  img3.cam_from_world = Rigid3d();
  img3.is_registered = true;
  images[3] = img3;

  WriteGlobalRotation(test_file_path_, images);

  EXPECT_EQ(CountLines(test_file_path_), 2);

  std::string contents = ReadFileContents(test_file_path_);
  EXPECT_NE(contents.find("registered.jpg"), std::string::npos);
  EXPECT_NE(contents.find("also_registered.jpg"), std::string::npos);
  EXPECT_EQ(contents.find("unregistered.jpg"), std::string::npos);
}

// Test that rotation values are written (identity quaternion case)
TEST_F(WriteGlobalRotationTest_127, IdentityRotationValues_127) {
  std::unordered_map<image_t, Image> images;

  Image img(1, 1, "test.jpg");
  img.cam_from_world = Rigid3d();  // Identity rotation: w=1, x=0, y=0, z=0
  img.is_registered = true;
  images[1] = img;

  WriteGlobalRotation(test_file_path_, images);

  std::ifstream file(test_file_path_);
  std::string line;
  std::getline(file, line);

  // The line should contain the filename followed by 4 quaternion values
  std::istringstream iss(line);
  std::string filename;
  double q0, q1, q2, q3;
  iss >> filename >> q0 >> q1 >> q2 >> q3;

  EXPECT_EQ(filename, "test.jpg");

  // For identity rotation, Eigen stores coeffs as (x, y, z, w) = (0, 0, 0, 1)
  // The code writes coeffs[(i+3)%4] for i=0..3:
  // i=0: coeffs[3] = w = 1
  // i=1: coeffs[0] = x = 0
  // i=2: coeffs[1] = y = 0
  // i=3: coeffs[2] = z = 0
  EXPECT_DOUBLE_EQ(q0, 1.0);
  EXPECT_DOUBLE_EQ(q1, 0.0);
  EXPECT_DOUBLE_EQ(q2, 0.0);
  EXPECT_DOUBLE_EQ(q3, 0.0);
}

// Test that the output format has exactly 5 tokens per line (filename + 4 quaternion components)
TEST_F(WriteGlobalRotationTest_127, OutputFormatTokenCount_127) {
  std::unordered_map<image_t, Image> images;

  Image img(1, 1, "format_test.jpg");
  img.cam_from_world = Rigid3d();
  img.is_registered = true;
  images[1] = img;

  WriteGlobalRotation(test_file_path_, images);

  std::ifstream file(test_file_path_);
  std::string line;
  std::getline(file, line);

  std::istringstream iss(line);
  std::vector<std::string> tokens;
  std::string token;
  while (iss >> token) {
    tokens.push_back(token);
  }

  // filename + 4 quaternion values = 5 tokens
  EXPECT_EQ(tokens.size(), 5);
}

// Test with non-identity rotation
TEST_F(WriteGlobalRotationTest_127, NonIdentityRotation_127) {
  std::unordered_map<image_t, Image> images;

  Image img(1, 1, "rotated.jpg");
  // Create a rotation (90 degrees around z-axis)
  Eigen::Quaterniond q(Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitZ()));
  Rigid3d pose;
  pose.rotation = q;
  img.cam_from_world = pose;
  img.is_registered = true;
  images[1] = img;

  WriteGlobalRotation(test_file_path_, images);

  std::ifstream file(test_file_path_);
  std::string line;
  std::getline(file, line);
  EXPECT_FALSE(line.empty());

  std::istringstream iss(line);
  std::string filename;
  double q0, q1, q2, q3;
  iss >> filename >> q0 >> q1 >> q2 >> q3;

  EXPECT_EQ(filename, "rotated.jpg");

  // coeffs order in Eigen is (x, y, z, w)
  // Output order: coeffs[3], coeffs[0], coeffs[1], coeffs[2] = w, x, y, z
  EXPECT_NEAR(q0, q.w(), 1e-10);
  EXPECT_NEAR(q1, q.x(), 1e-10);
  EXPECT_NEAR(q2, q.y(), 1e-10);
  EXPECT_NEAR(q3, q.z(), 1e-10);
}

// Test file creation - file should be created even if directory exists
TEST_F(WriteGlobalRotationTest_127, FileIsCreated_127) {
  std::unordered_map<image_t, Image> images;
  WriteGlobalRotation(test_file_path_, images);

  EXPECT_TRUE(std::filesystem::exists(test_file_path_));
}

// Test with large number of images
TEST_F(WriteGlobalRotationTest_127, LargeNumberOfImages_127) {
  std::unordered_map<image_t, Image> images;

  const int num_images = 100;
  for (int i = 0; i < num_images; i++) {
    Image img(i, 1, "image_" + std::to_string(i) + ".jpg");
    img.cam_from_world = Rigid3d();
    img.is_registered = true;
    images[i] = img;
  }

  WriteGlobalRotation(test_file_path_, images);

  EXPECT_EQ(CountLines(test_file_path_), num_images);
}

}  // namespace
}  // namespace glomap
