#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cstdio>

#include "glomap/io/pose_io.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/view_graph.h"

namespace glomap {
namespace {

// Helper to create a temporary file with given content
class TempFile {
 public:
  TempFile(const std::string& content) {
    // Create a unique temporary file name
    file_path_ = std::tmpnam(nullptr);
    std::ofstream ofs(file_path_);
    ofs << content;
    ofs.close();
  }
  ~TempFile() { std::remove(file_path_.c_str()); }
  const std::string& path() const { return file_path_; }

 private:
  std::string file_path_;
};

class ReadRelWeightTest_125 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create images with known file names and IDs
    // Using small IDs to ensure valid pair IDs
    images_[1] = Image(1, 0, "image1.jpg");
    images_[2] = Image(2, 0, "image2.jpg");
    images_[3] = Image(3, 0, "image3.jpg");
  }

  std::unordered_map<image_t, Image> images_;
  ViewGraph view_graph_;
};

// Test normal operation: a single valid line updates the weight
TEST_F(ReadRelWeightTest_125, SingleValidLine_125) {
  // Create image pair in view graph
  image_pair_t pair_id = colmap::ImagePairToPairId(1, 2);
  view_graph_.image_pairs[pair_id] = ImagePair(1, 2);

  ASSERT_EQ(view_graph_.image_pairs[pair_id].weight, -1);

  TempFile temp("image1.jpg image2.jpg 0.75\n");
  ReadRelWeight(temp.path(), images_, view_graph_);

  EXPECT_DOUBLE_EQ(view_graph_.image_pairs[pair_id].weight, 0.75);
}

// Test multiple valid lines update weights correctly
TEST_F(ReadRelWeightTest_125, MultipleValidLines_125) {
  image_pair_t pair_id_12 = colmap::ImagePairToPairId(1, 2);
  image_pair_t pair_id_13 = colmap::ImagePairToPairId(1, 3);
  view_graph_.image_pairs[pair_id_12] = ImagePair(1, 2);
  view_graph_.image_pairs[pair_id_13] = ImagePair(1, 3);

  TempFile temp("image1.jpg image2.jpg 0.5\nimage1.jpg image3.jpg 0.9\n");
  ReadRelWeight(temp.path(), images_, view_graph_);

  EXPECT_DOUBLE_EQ(view_graph_.image_pairs[pair_id_12].weight, 0.5);
  EXPECT_DOUBLE_EQ(view_graph_.image_pairs[pair_id_13].weight, 0.9);
}

// Test that lines with unknown image names are skipped
TEST_F(ReadRelWeightTest_125, UnknownImageNameSkipped_125) {
  image_pair_t pair_id = colmap::ImagePairToPairId(1, 2);
  view_graph_.image_pairs[pair_id] = ImagePair(1, 2);

  TempFile temp("unknown1.jpg image2.jpg 0.5\n");
  ReadRelWeight(temp.path(), images_, view_graph_);

  // Weight should remain unchanged (default -1)
  EXPECT_DOUBLE_EQ(view_graph_.image_pairs[pair_id].weight, -1);
}

// Test that lines referencing pairs not in view graph are skipped
TEST_F(ReadRelWeightTest_125, PairNotInViewGraphSkipped_125) {
  // Don't add any pair to view_graph_
  TempFile temp("image1.jpg image2.jpg 0.5\n");
  ReadRelWeight(temp.path(), images_, view_graph_);

  // No pairs should have been added
  image_pair_t pair_id = colmap::ImagePairToPairId(1, 2);
  EXPECT_EQ(view_graph_.image_pairs.find(pair_id),
            view_graph_.image_pairs.end());
}

// Test empty file - no weights should be updated
TEST_F(ReadRelWeightTest_125, EmptyFile_125) {
  image_pair_t pair_id = colmap::ImagePairToPairId(1, 2);
  view_graph_.image_pairs[pair_id] = ImagePair(1, 2);

  TempFile temp("");
  ReadRelWeight(temp.path(), images_, view_graph_);

  EXPECT_DOUBLE_EQ(view_graph_.image_pairs[pair_id].weight, -1);
}

// Test nonexistent file - should not crash, no weights updated
TEST_F(ReadRelWeightTest_125, NonexistentFile_125) {
  image_pair_t pair_id = colmap::ImagePairToPairId(1, 2);
  view_graph_.image_pairs[pair_id] = ImagePair(1, 2);

  ReadRelWeight("/nonexistent/path/file.txt", images_, view_graph_);

  EXPECT_DOUBLE_EQ(view_graph_.image_pairs[pair_id].weight, -1);
}

// Test that only matching lines update; non-matching lines are skipped
TEST_F(ReadRelWeightTest_125, MixedValidAndInvalidLines_125) {
  image_pair_t pair_id_12 = colmap::ImagePairToPairId(1, 2);
  view_graph_.image_pairs[pair_id_12] = ImagePair(1, 2);

  // First line: unknown image, second line: valid, third line: pair not in graph
  TempFile temp(
      "unknown.jpg image2.jpg 0.1\n"
      "image1.jpg image2.jpg 0.42\n"
      "image2.jpg image3.jpg 0.8\n");
  ReadRelWeight(temp.path(), images_, view_graph_);

  EXPECT_DOUBLE_EQ(view_graph_.image_pairs[pair_id_12].weight, 0.42);
}

// Test with weight of zero
TEST_F(ReadRelWeightTest_125, ZeroWeight_125) {
  image_pair_t pair_id = colmap::ImagePairToPairId(1, 2);
  view_graph_.image_pairs[pair_id] = ImagePair(1, 2);

  TempFile temp("image1.jpg image2.jpg 0.0\n");
  ReadRelWeight(temp.path(), images_, view_graph_);

  EXPECT_DOUBLE_EQ(view_graph_.image_pairs[pair_id].weight, 0.0);
}

// Test with negative weight value
TEST_F(ReadRelWeightTest_125, NegativeWeight_125) {
  image_pair_t pair_id = colmap::ImagePairToPairId(1, 2);
  view_graph_.image_pairs[pair_id] = ImagePair(1, 2);

  TempFile temp("image1.jpg image2.jpg -3.5\n");
  ReadRelWeight(temp.path(), images_, view_graph_);

  EXPECT_DOUBLE_EQ(view_graph_.image_pairs[pair_id].weight, -3.5);
}

// Test with large weight value
TEST_F(ReadRelWeightTest_125, LargeWeight_125) {
  image_pair_t pair_id = colmap::ImagePairToPairId(1, 2);
  view_graph_.image_pairs[pair_id] = ImagePair(1, 2);

  TempFile temp("image1.jpg image2.jpg 1e10\n");
  ReadRelWeight(temp.path(), images_, view_graph_);

  EXPECT_DOUBLE_EQ(view_graph_.image_pairs[pair_id].weight, 1e10);
}

// Test with empty images map - all lines should be skipped
TEST_F(ReadRelWeightTest_125, EmptyImagesMap_125) {
  std::unordered_map<image_t, Image> empty_images;
  image_pair_t pair_id = colmap::ImagePairToPairId(1, 2);
  view_graph_.image_pairs[pair_id] = ImagePair(1, 2);

  TempFile temp("image1.jpg image2.jpg 0.5\n");
  ReadRelWeight(temp.path(), empty_images, view_graph_);

  EXPECT_DOUBLE_EQ(view_graph_.image_pairs[pair_id].weight, -1);
}

// Test that only the last weight is kept if same pair appears multiple times
TEST_F(ReadRelWeightTest_125, DuplicatePairLastWeightWins_125) {
  image_pair_t pair_id = colmap::ImagePairToPairId(1, 2);
  view_graph_.image_pairs[pair_id] = ImagePair(1, 2);

  TempFile temp("image1.jpg image2.jpg 0.3\nimage1.jpg image2.jpg 0.7\n");
  ReadRelWeight(temp.path(), images_, view_graph_);

  EXPECT_DOUBLE_EQ(view_graph_.image_pairs[pair_id].weight, 0.7);
}

// Test with second image name unknown
TEST_F(ReadRelWeightTest_125, SecondImageUnknown_125) {
  image_pair_t pair_id = colmap::ImagePairToPairId(1, 2);
  view_graph_.image_pairs[pair_id] = ImagePair(1, 2);

  TempFile temp("image1.jpg nonexistent.jpg 0.5\n");
  ReadRelWeight(temp.path(), images_, view_graph_);

  EXPECT_DOUBLE_EQ(view_graph_.image_pairs[pair_id].weight, -1);
}

// Test fractional weight with high precision
TEST_F(ReadRelWeightTest_125, HighPrecisionWeight_125) {
  image_pair_t pair_id = colmap::ImagePairToPairId(1, 2);
  view_graph_.image_pairs[pair_id] = ImagePair(1, 2);

  TempFile temp("image1.jpg image2.jpg 0.123456789012345\n");
  ReadRelWeight(temp.path(), images_, view_graph_);

  EXPECT_NEAR(view_graph_.image_pairs[pair_id].weight, 0.123456789012345,
              1e-12);
}

}  // namespace
}  // namespace glomap
