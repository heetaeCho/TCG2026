// File: write_rel_pose_test_128.cc

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "glomap/io/pose_io.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/view_graph.h"

using namespace glomap;

class WriteRelPoseTest_128 : public ::testing::Test {
protected:
  std::string temp_file_;

  void SetUp() override {
    temp_file_ = "write_rel_pose_output_128.txt";
    std::remove(temp_file_.c_str());
  }

  void TearDown() override {
    std::remove(temp_file_.c_str());
  }

  // Helper to read the entire file into vector of token vectors
  std::vector<std::vector<std::string>> ReadFileTokens() const {
    std::ifstream ifs(temp_file_);
    std::vector<std::vector<std::string>> lines_tokens;
    std::string line;

    while (std::getline(ifs, line)) {
      std::stringstream ss(line);
      std::vector<std::string> tokens;
      std::string token;
      while (ss >> token) {
        tokens.push_back(token);
      }
      if (!tokens.empty()) {
        lines_tokens.push_back(tokens);
      }
    }
    return lines_tokens;
  }
};

// Normal operation: single valid pair -> one line with expected content.
TEST_F(WriteRelPoseTest_128, SingleValidPair_WritesExpectedLine_128) {
  // Arrange
  std::unordered_map<image_t, Image> images;
  Image image1(1, 1, "img1.jpg");
  Image image2(2, 1, "img2.jpg");
  images.emplace(1, image1);
  images.emplace(2, image2);

  // Set up a known relative pose
  Eigen::Quaterniond q(1.0, 2.0, 3.0, 4.0);        // (w, x, y, z)
  Eigen::Vector3d t(10.0, 20.0, 30.0);

  Rigid3d T(q, t);
  ImagePair pair(1, 2, T);

  ViewGraph view_graph;
  view_graph.image_pairs.emplace(pair.pair_id, pair);

  // Act
  WriteRelPose(temp_file_, images, view_graph);

  // Assert
  auto lines_tokens = ReadFileTokens();
  ASSERT_EQ(lines_tokens.size(), 1u) << "Expected exactly one output line";

  const auto& tokens = lines_tokens[0];
  ASSERT_EQ(tokens.size(), 9u) << "Each line should have 9 tokens";

  // First two tokens: file names
  EXPECT_EQ(tokens[0], "img1.jpg");
  EXPECT_EQ(tokens[1], "img2.jpg");

  // Next four tokens: rotation components (w, x, y, z)
  double rot0 = std::stod(tokens[2]);
  double rot1 = std::stod(tokens[3]);
  double rot2 = std::stod(tokens[4]);
  double rot3 = std::stod(tokens[5]);

  EXPECT_DOUBLE_EQ(rot0, 1.0);
  EXPECT_DOUBLE_EQ(rot1, 2.0);
  EXPECT_DOUBLE_EQ(rot2, 3.0);
  EXPECT_DOUBLE_EQ(rot3, 4.0);

  // Last three tokens: translation (x, y, z)
  double tx = std::stod(tokens[6]);
  double ty = std::stod(tokens[7]);
  double tz = std::stod(tokens[8]);

  EXPECT_DOUBLE_EQ(tx, 10.0);
  EXPECT_DOUBLE_EQ(ty, 20.0);
  EXPECT_DOUBLE_EQ(tz, 30.0);
}

// Boundary/exceptional behavior: invalid pairs should be skipped entirely.
TEST_F(WriteRelPoseTest_128, InvalidPairIsSkipped_128) {
  // Arrange
  std::unordered_map<image_t, Image> images;
  Image image1(1, 1, "img1.jpg");
  Image image2(2, 1, "img2.jpg");
  images.emplace(1, image1);
  images.emplace(2, image2);

  Eigen::Quaterniond q_valid(1.0, 0.0, 0.0, 0.0);
  Eigen::Vector3d t_valid(1.0, 2.0, 3.0);
  Rigid3d T_valid(q_valid, t_valid);
  ImagePair valid_pair(1, 2, T_valid);

  Eigen::Quaterniond q_invalid(0.0, 1.0, 0.0, 0.0);
  Eigen::Vector3d t_invalid(4.0, 5.0, 6.0);
  Rigid3d T_invalid(q_invalid, t_invalid);
  ImagePair invalid_pair(1, 2, T_invalid);
  invalid_pair.is_valid = false;

  ViewGraph view_graph;
  view_graph.image_pairs.emplace(valid_pair.pair_id, valid_pair);
  view_graph.image_pairs.emplace(invalid_pair.pair_id + 1, invalid_pair);

  // Act
  WriteRelPose(temp_file_, images, view_graph);

  // Assert
  auto lines_tokens = ReadFileTokens();
  // Only the valid pair should produce a line
  ASSERT_EQ(lines_tokens.size(), 1u);

  const auto& tokens = lines_tokens[0];
  ASSERT_EQ(tokens.size(), 9u);
  EXPECT_EQ(tokens[0], "img1.jpg");
  EXPECT_EQ(tokens[1], "img2.jpg");

  // Check translation matches the valid pose, not the invalid one
  double tx = std::stod(tokens[6]);
  double ty = std::stod(tokens[7]);
  double tz = std::stod(tokens[8]);

  EXPECT_DOUBLE_EQ(tx, 1.0);
  EXPECT_DOUBLE_EQ(ty, 2.0);
  EXPECT_DOUBLE_EQ(tz, 3.0);
}

// Normal operation + ordering: multiple valid pairs should be written in
// lexicographic order of "file_name1 file_name2".
TEST_F(WriteRelPoseTest_128, MultiplePairsWrittenInLexicographicOrder_128) {
  // Arrange
  std::unordered_map<image_t, Image> images;
  Image img_a(1, 1, "a.jpg");
  Image img_b(2, 1, "b.jpg");
  Image img_c(3, 1, "c.jpg");
  images.emplace(1, img_a);
  images.emplace(2, img_b);
  images.emplace(3, img_c);

  Eigen::Quaterniond q(1.0, 0.0, 0.0, 0.0);
  Eigen::Vector3d t(0.0, 0.0, 0.0);
  Rigid3d T(q, t);

  // Pairs inserted in arbitrary order
  ImagePair pair_ab(1, 2, T);  // "a.jpg b.jpg"
  ImagePair pair_bc(2, 3, T);  // "b.jpg c.jpg"
  ImagePair pair_ac(1, 3, T);  // "a.jpg c.jpg"

  ViewGraph view_graph;
  view_graph.image_pairs.emplace(pair_bc.pair_id, pair_bc);
  view_graph.image_pairs.emplace(pair_ab.pair_id, pair_ab);
  view_graph.image_pairs.emplace(pair_ac.pair_id, pair_ac);

  // Act
  WriteRelPose(temp_file_, images, view_graph);

  // Assert
  auto lines_tokens = ReadFileTokens();
  ASSERT_EQ(lines_tokens.size(), 3u);

  // Build combined "name1 name2" strings to check lexicographic order
  std::vector<std::string> combined;
  for (const auto& tokens : lines_tokens) {
    ASSERT_GE(tokens.size(), 2u);
    combined.push_back(tokens[0] + " " + tokens[1]);
  }

  // They should be in ascending lexicographic order
  EXPECT_LE(combined[0], combined[1]);
  EXPECT_LE(combined[1], combined[2]);

  // And the set of pairs should match what we expect
  std::multiset<std::string> expected = {
      "a.jpg b.jpg", "a.jpg c.jpg", "b.jpg c.jpg"};
  std::multiset<std::string> actual(combined.begin(), combined.end());
  EXPECT_EQ(expected, actual);
}

// Boundary condition: empty view graph -> empty file.
TEST_F(WriteRelPoseTest_128, EmptyViewGraphProducesEmptyFile_128) {
  // Arrange
  std::unordered_map<image_t, Image> images;
  ViewGraph view_graph;  // view_graph.image_pairs is empty

  // Act
  WriteRelPose(temp_file_, images, view_graph);

  // Assert
  auto lines_tokens = ReadFileTokens();
  EXPECT_TRUE(lines_tokens.empty()) << "No lines should be written for empty view graph";
}
