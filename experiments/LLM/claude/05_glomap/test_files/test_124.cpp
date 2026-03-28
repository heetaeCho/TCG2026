#include <gtest/gtest.h>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <cstdio>

#include "glomap/io/pose_io.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/view_graph.h"

namespace glomap {
namespace {

class ReadRelPoseTest_124 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create a temporary file path
    tmp_file_ = "test_rel_pose_124.txt";
  }

  void TearDown() override {
    // Remove temporary file
    std::remove(tmp_file_.c_str());
  }

  void WriteFile(const std::string& content) {
    std::ofstream ofs(tmp_file_);
    ofs << content;
    ofs.close();
  }

  std::string tmp_file_;
};

// Test reading from an empty file - no images or pairs should be added
TEST_F(ReadRelPoseTest_124, EmptyFile_124) {
  WriteFile("");

  std::unordered_map<image_t, Image> images;
  ViewGraph view_graph;

  ReadRelPose(tmp_file_, images, view_graph);

  EXPECT_TRUE(images.empty());
  EXPECT_TRUE(view_graph.image_pairs.empty());
}

// Test reading a single relative pose with new images (not in the map)
TEST_F(ReadRelPoseTest_124, SinglePoseNewImages_124) {
  // Format: file1 file2 qx qy qz qw tx ty tz
  // Quaternion in file: qw qx qy qz (but code reads 4 values and assigns with (i+3)%4 mapping)
  WriteFile("img1.jpg img2.jpg 1.0 0.0 0.0 0.0 1.0 2.0 3.0\n");

  std::unordered_map<image_t, Image> images;
  ViewGraph view_graph;

  ReadRelPose(tmp_file_, images, view_graph);

  // Two new images should be created
  EXPECT_EQ(images.size(), 2);
  // One image pair should be created
  EXPECT_EQ(view_graph.image_pairs.size(), 1);
}

// Test reading when images already exist in the map
TEST_F(ReadRelPoseTest_124, ExistingImages_124) {
  WriteFile("img1.jpg img2.jpg 1.0 0.0 0.0 0.0 1.0 2.0 3.0\n");

  std::unordered_map<image_t, Image> images;
  images.insert({1, Image(1, 0, "img1.jpg")});
  images.insert({2, Image(2, 0, "img2.jpg")});

  ViewGraph view_graph;

  ReadRelPose(tmp_file_, images, view_graph);

  // No new images should be added
  EXPECT_EQ(images.size(), 2);
  // One image pair should be created
  EXPECT_EQ(view_graph.image_pairs.size(), 1);
}

// Test that existing image pairs get updated (is_valid set to true, config set to CALIBRATED)
TEST_F(ReadRelPoseTest_124, ExistingPairGetsUpdated_124) {
  std::unordered_map<image_t, Image> images;
  images.insert({1, Image(1, 0, "img1.jpg")});
  images.insert({2, Image(2, 0, "img2.jpg")});

  ViewGraph view_graph;
  image_pair_t pair_id = colmap::ImagePairToPairId(1, 2);
  view_graph.image_pairs.insert({pair_id, ImagePair(1, 2)});

  // Before reading, is_valid will be set to false by the function
  WriteFile("img1.jpg img2.jpg 1.0 0.0 0.0 0.0 1.0 2.0 3.0\n");

  ReadRelPose(tmp_file_, images, view_graph);

  EXPECT_EQ(view_graph.image_pairs.size(), 1);
  auto it = view_graph.image_pairs.find(pair_id);
  ASSERT_NE(it, view_graph.image_pairs.end());
  EXPECT_TRUE(it->second.is_valid);
  EXPECT_EQ(it->second.config, colmap::TwoViewGeometry::CALIBRATED);
}

// Test that existing pairs are invalidated if not in the file
TEST_F(ReadRelPoseTest_124, ExistingPairsInvalidated_124) {
  std::unordered_map<image_t, Image> images;
  images.insert({1, Image(1, 0, "img1.jpg")});
  images.insert({2, Image(2, 0, "img2.jpg")});
  images.insert({3, Image(3, 0, "img3.jpg")});

  ViewGraph view_graph;
  image_pair_t pair_id_12 = colmap::ImagePairToPairId(1, 2);
  image_pair_t pair_id_13 = colmap::ImagePairToPairId(1, 3);
  view_graph.image_pairs.insert({pair_id_12, ImagePair(1, 2)});
  view_graph.image_pairs.insert({pair_id_13, ImagePair(1, 3)});

  // Only provide pose for pair (1,2), so pair (1,3) should remain invalid
  WriteFile("img1.jpg img2.jpg 1.0 0.0 0.0 0.0 1.0 2.0 3.0\n");

  ReadRelPose(tmp_file_, images, view_graph);

  auto it12 = view_graph.image_pairs.find(pair_id_12);
  auto it13 = view_graph.image_pairs.find(pair_id_13);
  ASSERT_NE(it12, view_graph.image_pairs.end());
  ASSERT_NE(it13, view_graph.image_pairs.end());
  EXPECT_TRUE(it12->second.is_valid);
  EXPECT_FALSE(it13->second.is_valid);
}

// Test reading multiple relative poses
TEST_F(ReadRelPoseTest_124, MultiplePoses_124) {
  std::stringstream ss;
  ss << "img1.jpg img2.jpg 1.0 0.0 0.0 0.0 1.0 2.0 3.0\n";
  ss << "img3.jpg img4.jpg 0.0 1.0 0.0 0.0 4.0 5.0 6.0\n";
  ss << "img1.jpg img3.jpg 0.0 0.0 1.0 0.0 7.0 8.0 9.0\n";
  WriteFile(ss.str());

  std::unordered_map<image_t, Image> images;
  ViewGraph view_graph;

  ReadRelPose(tmp_file_, images, view_graph);

  // 4 new images should be created
  EXPECT_EQ(images.size(), 4);
  // 3 image pairs should be created
  EXPECT_EQ(view_graph.image_pairs.size(), 3);
}

// Test that new images get camera_id = -1
TEST_F(ReadRelPoseTest_124, NewImagesGetNegativeCameraId_124) {
  WriteFile("new_img1.jpg new_img2.jpg 1.0 0.0 0.0 0.0 0.0 0.0 0.0\n");

  std::unordered_map<image_t, Image> images;
  ViewGraph view_graph;

  ReadRelPose(tmp_file_, images, view_graph);

  EXPECT_EQ(images.size(), 2);
  for (const auto& [id, img] : images) {
    EXPECT_EQ(img.camera_id, -1);
  }
}

// Test that new images have correct file names
TEST_F(ReadRelPoseTest_124, NewImagesHaveCorrectFileNames_124) {
  WriteFile("alpha.jpg beta.png 1.0 0.0 0.0 0.0 0.0 0.0 0.0\n");

  std::unordered_map<image_t, Image> images;
  ViewGraph view_graph;

  ReadRelPose(tmp_file_, images, view_graph);

  bool found_alpha = false, found_beta = false;
  for (const auto& [id, img] : images) {
    if (img.file_name == "alpha.jpg") found_alpha = true;
    if (img.file_name == "beta.png") found_beta = true;
  }
  EXPECT_TRUE(found_alpha);
  EXPECT_TRUE(found_beta);
}

// Test reading a nonexistent file - should not crash, just do nothing
TEST_F(ReadRelPoseTest_124, NonexistentFile_124) {
  std::unordered_map<image_t, Image> images;
  ViewGraph view_graph;

  // This should not throw or crash
  ReadRelPose("nonexistent_file_124.txt", images, view_graph);

  EXPECT_TRUE(images.empty());
  EXPECT_TRUE(view_graph.image_pairs.empty());
}

// Test that the translation values are correctly parsed
TEST_F(ReadRelPoseTest_124, TranslationValuesParsed_124) {
  std::unordered_map<image_t, Image> images;
  images.insert({1, Image(1, 0, "img1.jpg")});
  images.insert({2, Image(2, 0, "img2.jpg")});

  ViewGraph view_graph;

  WriteFile("img1.jpg img2.jpg 1.0 0.0 0.0 0.0 10.5 20.5 30.5\n");

  ReadRelPose(tmp_file_, images, view_graph);

  EXPECT_EQ(view_graph.image_pairs.size(), 1);
  auto it = view_graph.image_pairs.begin();
  EXPECT_DOUBLE_EQ(it->second.cam2_from_cam1.translation[0], 10.5);
  EXPECT_DOUBLE_EQ(it->second.cam2_from_cam1.translation[1], 20.5);
  EXPECT_DOUBLE_EQ(it->second.cam2_from_cam1.translation[2], 30.5);
}

// Test mixing existing and new images
TEST_F(ReadRelPoseTest_124, MixExistingAndNewImages_124) {
  std::unordered_map<image_t, Image> images;
  images.insert({5, Image(5, 0, "existing.jpg")});

  ViewGraph view_graph;

  WriteFile("existing.jpg new_image.jpg 1.0 0.0 0.0 0.0 0.0 0.0 0.0\n");

  ReadRelPose(tmp_file_, images, view_graph);

  // One existing + one new
  EXPECT_EQ(images.size(), 2);
  EXPECT_EQ(view_graph.image_pairs.size(), 1);

  // Verify existing image is still there
  ASSERT_NE(images.find(5), images.end());
  EXPECT_EQ(images[5].file_name, "existing.jpg");
}

// Test that the same image appearing in multiple pairs is only created once
TEST_F(ReadRelPoseTest_124, SameImageInMultiplePairs_124) {
  std::stringstream ss;
  ss << "common.jpg img_a.jpg 1.0 0.0 0.0 0.0 0.0 0.0 0.0\n";
  ss << "common.jpg img_b.jpg 1.0 0.0 0.0 0.0 0.0 0.0 0.0\n";
  WriteFile(ss.str());

  std::unordered_map<image_t, Image> images;
  ViewGraph view_graph;

  ReadRelPose(tmp_file_, images, view_graph);

  // 3 unique images: common, img_a, img_b
  EXPECT_EQ(images.size(), 3);
  EXPECT_EQ(view_graph.image_pairs.size(), 2);
}

// Test reading a pair where both images are the same file (edge case)
TEST_F(ReadRelPoseTest_124, SameImageBothSides_124) {
  WriteFile("img1.jpg img1.jpg 1.0 0.0 0.0 0.0 0.0 0.0 0.0\n");

  std::unordered_map<image_t, Image> images;
  ViewGraph view_graph;

  ReadRelPose(tmp_file_, images, view_graph);

  // Only one unique image should be created
  EXPECT_EQ(images.size(), 1);
}

// Test that new image pair (not pre-existing in view_graph) is inserted correctly
TEST_F(ReadRelPoseTest_124, NewPairInserted_124) {
  std::unordered_map<image_t, Image> images;
  images.insert({1, Image(1, 0, "a.jpg")});
  images.insert({2, Image(2, 0, "b.jpg")});

  ViewGraph view_graph;
  // No pre-existing pairs

  WriteFile("a.jpg b.jpg 1.0 0.0 0.0 0.0 5.0 6.0 7.0\n");

  ReadRelPose(tmp_file_, images, view_graph);

  image_pair_t pair_id = colmap::ImagePairToPairId(1, 2);
  auto it = view_graph.image_pairs.find(pair_id);
  ASSERT_NE(it, view_graph.image_pairs.end());
  EXPECT_EQ(it->second.image_id1, 1);
  EXPECT_EQ(it->second.image_id2, 2);
}

// Test with max_image_id logic: new images should get IDs beyond existing max
TEST_F(ReadRelPoseTest_124, NewImageIdsIncrementFromMax_124) {
  std::unordered_map<image_t, Image> images;
  images.insert({10, Image(10, 0, "existing.jpg")});

  ViewGraph view_graph;

  WriteFile("new1.jpg new2.jpg 1.0 0.0 0.0 0.0 0.0 0.0 0.0\n");

  ReadRelPose(tmp_file_, images, view_graph);

  // Should have 3 images: 10, 11, 12
  EXPECT_EQ(images.size(), 3);
  EXPECT_NE(images.find(10), images.end());
  EXPECT_NE(images.find(11), images.end());
  EXPECT_NE(images.find(12), images.end());
}

}  // namespace
}  // namespace glomap
