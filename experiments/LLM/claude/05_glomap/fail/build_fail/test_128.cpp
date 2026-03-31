#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <cstdio>

#include "glomap/io/pose_io.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/view_graph.h"

namespace glomap {
namespace {

class WriteRelPoseTest_128 : public ::testing::Test {
 protected:
  void SetUp() override {
    test_file_path_ = "test_relpose_output_128.txt";
  }

  void TearDown() override {
    // Clean up the test file
    std::remove(test_file_path_.c_str());
  }

  std::string test_file_path_;
};

// Helper to read all lines from a file
std::vector<std::string> ReadLines(const std::string& path) {
  std::vector<std::string> lines;
  std::ifstream file(path);
  std::string line;
  while (std::getline(file, line)) {
    if (!line.empty()) {
      lines.push_back(line);
    }
  }
  return lines;
}

TEST_F(WriteRelPoseTest_128, EmptyViewGraph_128) {
  std::unordered_map<image_t, Image> images;
  ViewGraph view_graph;

  WriteRelPose(test_file_path_, images, view_graph);

  auto lines = ReadLines(test_file_path_);
  EXPECT_TRUE(lines.empty());
}

TEST_F(WriteRelPoseTest_128, SingleValidPair_128) {
  std::unordered_map<image_t, Image> images;
  images.emplace(0, Image(0, 0, "image0.jpg"));
  images.emplace(1, Image(1, 0, "image1.jpg"));

  ViewGraph view_graph;
  ImagePair pair(0, 1);
  pair.is_valid = true;
  // Default Rigid3d: identity rotation, zero translation
  view_graph.image_pairs[pair.pair_id] = pair;

  WriteRelPose(test_file_path_, images, view_graph);

  auto lines = ReadLines(test_file_path_);
  ASSERT_EQ(lines.size(), 1u);

  // Parse the line
  std::istringstream iss(lines[0]);
  std::string name1, name2;
  double qw, qx, qy, qz, tx, ty, tz;
  iss >> name1 >> name2 >> qw >> qx >> qy >> qz >> tx >> ty >> tz;

  EXPECT_EQ(name1, "image0.jpg");
  EXPECT_EQ(name2, "image1.jpg");
  // Identity quaternion: w=1, x=0, y=0, z=0
  EXPECT_DOUBLE_EQ(qw, 1.0);
  EXPECT_DOUBLE_EQ(qx, 0.0);
  EXPECT_DOUBLE_EQ(qy, 0.0);
  EXPECT_DOUBLE_EQ(qz, 0.0);
  // Zero translation
  EXPECT_DOUBLE_EQ(tx, 0.0);
  EXPECT_DOUBLE_EQ(ty, 0.0);
  EXPECT_DOUBLE_EQ(tz, 0.0);
}

TEST_F(WriteRelPoseTest_128, InvalidPairNotWritten_128) {
  std::unordered_map<image_t, Image> images;
  images.emplace(0, Image(0, 0, "image0.jpg"));
  images.emplace(1, Image(1, 0, "image1.jpg"));

  ViewGraph view_graph;
  ImagePair pair(0, 1);
  pair.is_valid = false;
  view_graph.image_pairs[pair.pair_id] = pair;

  WriteRelPose(test_file_path_, images, view_graph);

  auto lines = ReadLines(test_file_path_);
  EXPECT_TRUE(lines.empty());
}

TEST_F(WriteRelPoseTest_128, MultipleValidPairs_128) {
  std::unordered_map<image_t, Image> images;
  images.emplace(0, Image(0, 0, "a.jpg"));
  images.emplace(1, Image(1, 0, "b.jpg"));
  images.emplace(2, Image(2, 0, "c.jpg"));

  ViewGraph view_graph;

  ImagePair pair01(0, 1);
  pair01.is_valid = true;
  view_graph.image_pairs[pair01.pair_id] = pair01;

  ImagePair pair02(0, 2);
  pair02.is_valid = true;
  view_graph.image_pairs[pair02.pair_id] = pair02;

  ImagePair pair12(1, 2);
  pair12.is_valid = true;
  view_graph.image_pairs[pair12.pair_id] = pair12;

  WriteRelPose(test_file_path_, images, view_graph);

  auto lines = ReadLines(test_file_path_);
  EXPECT_EQ(lines.size(), 3u);
}

TEST_F(WriteRelPoseTest_128, MixedValidAndInvalidPairs_128) {
  std::unordered_map<image_t, Image> images;
  images.emplace(0, Image(0, 0, "img0.jpg"));
  images.emplace(1, Image(1, 0, "img1.jpg"));
  images.emplace(2, Image(2, 0, "img2.jpg"));

  ViewGraph view_graph;

  ImagePair pair01(0, 1);
  pair01.is_valid = true;
  view_graph.image_pairs[pair01.pair_id] = pair01;

  ImagePair pair02(0, 2);
  pair02.is_valid = false;
  view_graph.image_pairs[pair02.pair_id] = pair02;

  WriteRelPose(test_file_path_, images, view_graph);

  auto lines = ReadLines(test_file_path_);
  EXPECT_EQ(lines.size(), 1u);

  // Verify it's the valid pair
  std::istringstream iss(lines[0]);
  std::string name1, name2;
  iss >> name1 >> name2;
  EXPECT_EQ(name1, "img0.jpg");
  EXPECT_EQ(name2, "img1.jpg");
}

TEST_F(WriteRelPoseTest_128, NonTrivialPose_128) {
  std::unordered_map<image_t, Image> images;
  images.emplace(0, Image(0, 0, "frame0.png"));
  images.emplace(1, Image(1, 0, "frame1.png"));

  // Create a non-identity pose
  Rigid3d pose;
  // Set a specific rotation quaternion (normalized)
  Eigen::Quaterniond q(0.5, 0.5, 0.5, 0.5); // w, x, y, z
  pose.rotation = q;
  pose.translation = Eigen::Vector3d(1.0, 2.0, 3.0);

  ViewGraph view_graph;
  ImagePair pair(0, 1, pose);
  pair.is_valid = true;
  view_graph.image_pairs[pair.pair_id] = pair;

  WriteRelPose(test_file_path_, images, view_graph);

  auto lines = ReadLines(test_file_path_);
  ASSERT_EQ(lines.size(), 1u);

  std::istringstream iss(lines[0]);
  std::string name1, name2;
  double qw, qx, qy, qz, tx, ty, tz;
  iss >> name1 >> name2 >> qw >> qx >> qy >> qz >> tx >> ty >> tz;

  EXPECT_EQ(name1, "frame0.png");
  EXPECT_EQ(name2, "frame1.png");

  // The code writes coeffs()[(i+3)%4] for i=0..3
  // Eigen coeffs order: x, y, z, w (indices 0,1,2,3)
  // i=0: coeffs[3] = w = 0.5
  // i=1: coeffs[0] = x = 0.5
  // i=2: coeffs[1] = y = 0.5
  // i=3: coeffs[2] = z = 0.5
  EXPECT_NEAR(qw, 0.5, 1e-10);
  EXPECT_NEAR(qx, 0.5, 1e-10);
  EXPECT_NEAR(qy, 0.5, 1e-10);
  EXPECT_NEAR(qz, 0.5, 1e-10);

  EXPECT_NEAR(tx, 1.0, 1e-10);
  EXPECT_NEAR(ty, 2.0, 1e-10);
  EXPECT_NEAR(tz, 3.0, 1e-10);
}

TEST_F(WriteRelPoseTest_128, OutputIsSortedByImageNames_128) {
  std::unordered_map<image_t, Image> images;
  images.emplace(0, Image(0, 0, "z_last.jpg"));
  images.emplace(1, Image(1, 0, "a_first.jpg"));
  images.emplace(2, Image(2, 0, "m_middle.jpg"));

  ViewGraph view_graph;

  // Pair (0,1): "z_last.jpg a_first.jpg"
  ImagePair pair01(0, 1);
  pair01.is_valid = true;
  view_graph.image_pairs[pair01.pair_id] = pair01;

  // Pair (0,2): "z_last.jpg m_middle.jpg"
  ImagePair pair02(0, 2);
  pair02.is_valid = true;
  view_graph.image_pairs[pair02.pair_id] = pair02;

  // Pair (1,2): "a_first.jpg m_middle.jpg"
  ImagePair pair12(1, 2);
  pair12.is_valid = true;
  view_graph.image_pairs[pair12.pair_id] = pair12;

  WriteRelPose(test_file_path_, images, view_graph);

  auto lines = ReadLines(test_file_path_);
  ASSERT_EQ(lines.size(), 3u);

  // The code uses std::map<std::string, ...> sorted by "image1.file_name + ' ' + image2.file_name"
  // Expected sorted order:
  // "a_first.jpg m_middle.jpg" < "z_last.jpg a_first.jpg" < "z_last.jpg m_middle.jpg"
  std::istringstream iss0(lines[0]);
  std::string n1, n2;
  iss0 >> n1 >> n2;
  EXPECT_EQ(n1, "a_first.jpg");
  EXPECT_EQ(n2, "m_middle.jpg");

  std::istringstream iss1(lines[1]);
  iss1 >> n1 >> n2;
  EXPECT_EQ(n1, "z_last.jpg");
  EXPECT_EQ(n2, "a_first.jpg");

  std::istringstream iss2(lines[2]);
  iss2 >> n1 >> n2;
  EXPECT_EQ(n1, "z_last.jpg");
  EXPECT_EQ(n2, "m_middle.jpg");
}

TEST_F(WriteRelPoseTest_128, FileCreatedEvenIfEmpty_128) {
  std::unordered_map<image_t, Image> images;
  ViewGraph view_graph;

  WriteRelPose(test_file_path_, images, view_graph);

  // File should exist
  std::ifstream file(test_file_path_);
  EXPECT_TRUE(file.good());
}

TEST_F(WriteRelPoseTest_128, LineFormatHasCorrectNumberOfFields_128) {
  std::unordered_map<image_t, Image> images;
  images.emplace(0, Image(0, 0, "img_a.jpg"));
  images.emplace(1, Image(1, 0, "img_b.jpg"));

  ViewGraph view_graph;
  ImagePair pair(0, 1);
  pair.is_valid = true;
  view_graph.image_pairs[pair.pair_id] = pair;

  WriteRelPose(test_file_path_, images, view_graph);

  auto lines = ReadLines(test_file_path_);
  ASSERT_EQ(lines.size(), 1u);

  // Each line should have: name1 name2 qw qx qy qz tx ty tz = 9 fields
  std::istringstream iss(lines[0]);
  std::vector<std::string> tokens;
  std::string token;
  while (iss >> token) {
    tokens.push_back(token);
  }
  EXPECT_EQ(tokens.size(), 9u);
}

TEST_F(WriteRelPoseTest_128, AllInvalidPairsProduceEmptyFile_128) {
  std::unordered_map<image_t, Image> images;
  images.emplace(0, Image(0, 0, "img0.jpg"));
  images.emplace(1, Image(1, 0, "img1.jpg"));
  images.emplace(2, Image(2, 0, "img2.jpg"));

  ViewGraph view_graph;

  ImagePair pair01(0, 1);
  pair01.is_valid = false;
  view_graph.image_pairs[pair01.pair_id] = pair01;

  ImagePair pair02(0, 2);
  pair02.is_valid = false;
  view_graph.image_pairs[pair02.pair_id] = pair02;

  WriteRelPose(test_file_path_, images, view_graph);

  auto lines = ReadLines(test_file_path_);
  EXPECT_TRUE(lines.empty());
}

TEST_F(WriteRelPoseTest_128, QuaternionOrderMatchesWXYZ_128) {
  std::unordered_map<image_t, Image> images;
  images.emplace(0, Image(0, 0, "img0.jpg"));
  images.emplace(1, Image(1, 0, "img1.jpg"));

  Rigid3d pose;
  // Quaternion with distinct values: w=0.1, x=0.2, y=0.3, z=0.4 (not normalized, but for test)
  Eigen::Quaterniond q(0.1, 0.2, 0.3, 0.4); // w, x, y, z constructor
  q.normalize();
  pose.rotation = q;
  pose.translation = Eigen::Vector3d(10.0, 20.0, 30.0);

  ViewGraph view_graph;
  ImagePair pair(0, 1, pose);
  pair.is_valid = true;
  view_graph.image_pairs[pair.pair_id] = pair;

  WriteRelPose(test_file_path_, images, view_graph);

  auto lines = ReadLines(test_file_path_);
  ASSERT_EQ(lines.size(), 1u);

  std::istringstream iss(lines[0]);
  std::string n1, n2;
  double vals[7];
  iss >> n1 >> n2;
  for (int i = 0; i < 7; i++) {
    iss >> vals[i];
  }

  // coeffs() returns [x, y, z, w]
  // Code writes coeffs()[(i+3)%4] for i=0..3:
  //   i=0: coeffs[3] = w
  //   i=1: coeffs[0] = x
  //   i=2: coeffs[1] = y
  //   i=3: coeffs[2] = z
  EXPECT_NEAR(vals[0], q.w(), 1e-10);
  EXPECT_NEAR(vals[1], q.x(), 1e-10);
  EXPECT_NEAR(vals[2], q.y(), 1e-10);
  EXPECT_NEAR(vals[3], q.z(), 1e-10);
  EXPECT_NEAR(vals[4], 10.0, 1e-10);
  EXPECT_NEAR(vals[5], 20.0, 1e-10);
  EXPECT_NEAR(vals[6], 30.0, 1e-10);
}

}  // namespace
}  // namespace glomap
