// File: read_rel_weight_test_125.cc

#include <gtest/gtest.h>

#include <cstdio>      // std::tmpnam, std::remove
#include <fstream>     // std::ofstream
#include <string>
#include <unordered_map>

#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/view_graph.h"

// Forward declaration of the function under test.
// The implementation is provided by the production code (pose_io.cc).
namespace glomap {
void ReadRelWeight(const std::string& file_path,
                   const std::unordered_map<image_t, Image>& images,
                   ViewGraph& view_graph);
}  // namespace glomap

namespace {

// Simple helper for creating unique temporary file paths.
std::string CreateTempFilePath() {
  char tmp_name[L_tmpnam];
  std::tmpnam(tmp_name);  // NOLINT(cert-msc30-c, cert-msc50-cpp)
  return std::string(tmp_name);
}

class ReadRelWeightTest_125 : public ::testing::Test {
 protected:
  using ImageMap = std::unordered_map<glomap::image_t, glomap::Image>;

  glomap::ViewGraph view_graph_;
  ImageMap images_;

  static glomap::Image MakeImage(glomap::image_t id,
                                 const std::string& file_name) {
    // camera_id is arbitrary for these tests; we just need a valid object.
    return glomap::Image(id, /*camera_id=*/1, file_name);
  }

  void AddImage(glomap::image_t id, const std::string& file_name) {
    images_.emplace(id, MakeImage(id, file_name));
  }
};

}  // namespace

// Normal operation: both images exist and the image pair exists in the view
// graph —> weight should be updated.
TEST_F(ReadRelWeightTest_125, UpdatesWeightWhenPairAndImagesExist_125) {
  // Arrange
  AddImage(1, "img1.jpg");
  AddImage(2, "img2.jpg");

  glomap::ImagePair pair(1, 2);
  pair.weight = -1.0;  // Initial value to verify it actually changes.
  const auto pair_id = pair.pair_id;
  view_graph_.image_pairs.emplace(pair_id, pair);

  const std::string file_path = CreateTempFilePath();
  {
    std::ofstream ofs(file_path);
    ofs << "img1.jpg img2.jpg 0.75\n";
  }

  // Act
  glomap::ReadRelWeight(file_path, images_, view_graph_);
  std::remove(file_path.c_str());

  // Assert
  auto it = view_graph_.image_pairs.find(pair_id);
  ASSERT_NE(it, view_graph_.image_pairs.end());
  EXPECT_DOUBLE_EQ(it->second.weight, 0.75);
}

// Boundary condition: second image name is not present in the images map
// —> the line should be ignored and the weight must remain unchanged.
TEST_F(ReadRelWeightTest_125, SkipsLineWhenImageNameMissingInImages_125) {
  // Arrange
  AddImage(1, "img1.jpg");
  // No image with file name "img2.jpg" in images_.

  glomap::ImagePair pair(1, 2);
  pair.weight = 1.23;  // Initial value.
  const auto pair_id = pair.pair_id;
  view_graph_.image_pairs.emplace(pair_id, pair);

  const std::string file_path = CreateTempFilePath();
  {
    std::ofstream ofs(file_path);
    // file2 name is not in the images_ map
    ofs << "img1.jpg img2.jpg 9.99\n";
  }

  // Act
  glomap::ReadRelWeight(file_path, images_, view_graph_);
  std::remove(file_path.c_str());

  // Assert: weight should remain unchanged because line is skipped.
  auto it = view_graph_.image_pairs.find(pair_id);
  ASSERT_NE(it, view_graph_.image_pairs.end());
  EXPECT_DOUBLE_EQ(it->second.weight, 1.23);
}

// Error/edge case: both images exist but the corresponding image pair
// does not exist in the view graph —> nothing should be inserted or modified.
TEST_F(ReadRelWeightTest_125, SkipsLineWhenImagePairNotInViewGraph_125) {
  // Arrange
  AddImage(1, "img1.jpg");
  AddImage(2, "img2.jpg");

  // No image pair (1, 2) added to view_graph_.
  const std::size_t initial_size = view_graph_.image_pairs.size();

  const std::string file_path = CreateTempFilePath();
  {
    std::ofstream ofs(file_path);
    ofs << "img1.jpg img2.jpg 0.5\n";
  }

  // Act
  glomap::ReadRelWeight(file_path, images_, view_graph_);
  std::remove(file_path.c_str());

  // Assert: still no entries, since pair did not exist.
  EXPECT_EQ(view_graph_.image_pairs.size(), initial_size);
}

// Boundary condition: empty file —> no changes should be made to the view
// graph.
TEST_F(ReadRelWeightTest_125, EmptyFileDoesNotChangeExistingWeights_125) {
  // Arrange
  AddImage(1, "img1.jpg");
  AddImage(2, "img2.jpg");

  glomap::ImagePair pair(1, 2);
  pair.weight = 3.14;
  const auto pair_id = pair.pair_id;
  view_graph_.image_pairs.emplace(pair_id, pair);

  const std::string file_path = CreateTempFilePath();
  {
    // Create an empty file.
    std::ofstream ofs(file_path);
  }

  // Act
  glomap::ReadRelWeight(file_path, images_, view_graph_);
  std::remove(file_path.c_str());

  // Assert: weight remains unchanged.
  auto it = view_graph_.image_pairs.find(pair_id);
  ASSERT_NE(it, view_graph_.image_pairs.end());
  EXPECT_DOUBLE_EQ(it->second.weight, 3.14);
}

// Normal + mixed conditions: multiple lines, some valid and some invalid
// (missing images or missing pairs). Only valid lines for existing pairs
// should update weights.
TEST_F(ReadRelWeightTest_125, MultipleLinesUpdateOnlyExistingPairs_125) {
  // Arrange
  AddImage(1, "img1.jpg");
  AddImage(2, "img2.jpg");
  AddImage(3, "img3.jpg");
  AddImage(4, "img4.jpg");

  glomap::ImagePair pair12(1, 2);
  pair12.weight = 1.0;
  const auto id12 = pair12.pair_id;
  view_graph_.image_pairs.emplace(id12, pair12);

  glomap::ImagePair pair34(3, 4);
  pair34.weight = 2.0;
  const auto id34 = pair34.pair_id;
  view_graph_.image_pairs.emplace(id34, pair34);

  const std::string file_path = CreateTempFilePath();
  {
    std::ofstream ofs(file_path);
    // Valid: both images exist and pair (1,2) exists in view_graph_.
    ofs << "img1.jpg img2.jpg 0.5\n";
    // Invalid: second image name missing in images_ (no imgX.jpg).
    ofs << "img1.jpg imgX.jpg 9.9\n";
    // Valid: both images exist and pair (3,4) exists in view_graph_.
    ofs << "img3.jpg img4.jpg 0.75\n";
  }

  // Act
  glomap::ReadRelWeight(file_path, images_, view_graph_);
  std::remove(file_path.c_str());

  // Assert: only the two valid lines should have updated weights.
  auto it12 = view_graph_.image_pairs.find(id12);
  ASSERT_NE(it12, view_graph_.image_pairs.end());
  EXPECT_DOUBLE_EQ(it12->second.weight, 0.5);

  auto it34 = view_graph_.image_pairs.find(id34);
  ASSERT_NE(it34, view_graph_.image_pairs.end());
  EXPECT_DOUBLE_EQ(it34->second.weight, 0.75);
}
