#include <gtest/gtest.h>

#include <fstream>
#include <string>
#include <unordered_map>

#include "glomap/io/pose_io.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/view_graph.h"
#include "colmap/geometry/two_view_geometry.h"

namespace {

using glomap::Image;
using glomap::ImagePair;
using glomap::ViewGraph;
using glomap::image_t;
using glomap::image_pair_t;

class ReadRelPoseTest_124 : public ::testing::Test {
 protected:
  std::string WriteTempFile(const std::string& filename,
                            const std::string& content) {
    std::ofstream ofs(filename);
    ofs << content;
    return filename;
  }
};

TEST_F(ReadRelPoseTest_124,
       CreatesNewImagesAndPairWhenMapsAreEmpty_124) {
  std::unordered_map<image_t, Image> images;
  ViewGraph view_graph;

  const std::string path =
      WriteTempFile("relpose_test_create_124.txt",
                    // file1  file2   q0 q1 q2 q3   tx ty tz
                    "imgA.jpg imgB.jpg 0.0 0.1 0.2 0.3  1.0 2.0 3.0\n");

  glomap::ReadRelPose(path, images, view_graph);

  // Two new images should be created.
  EXPECT_EQ(images.size(), 2u);
  // One new view-graph pair should be created.
  ASSERT_EQ(view_graph.image_pairs.size(), 1u);

  const auto pair_it = view_graph.image_pairs.begin();
  const ImagePair& pair = pair_it->second;

  // The pair's image IDs must be present in the images map.
  auto img1_it = images.find(pair.image_id1);
  auto img2_it = images.find(pair.image_id2);
  ASSERT_NE(img1_it, images.end());
  ASSERT_NE(img2_it, images.end());

  EXPECT_EQ(img1_it->second.file_name, "imgA.jpg");
  EXPECT_EQ(img2_it->second.file_name, "imgB.jpg");

  // Translation written from file should be stored in the relative pose.
  EXPECT_DOUBLE_EQ(pair.cam2_from_cam1.translation[0], 1.0);
  EXPECT_DOUBLE_EQ(pair.cam2_from_cam1.translation[1], 2.0);
  EXPECT_DOUBLE_EQ(pair.cam2_from_cam1.translation[2], 3.0);
}

TEST_F(ReadRelPoseTest_124,
       MarksExistingPairsInvalidWhenFileIsEmpty_124) {
  std::unordered_map<image_t, Image> images;

  // Prepare images for a known pair.
  Image img1(1, -1, "img1.jpg");
  Image img2(2, -1, "img2.jpg");
  images.emplace(1, img1);
  images.emplace(2, img2);

  ViewGraph view_graph;
  ImagePair existing_pair(1, 2);
  existing_pair.is_valid = true;
  const image_pair_t existing_pair_id =
      existing_pair.pair_id;
  view_graph.image_pairs.emplace(existing_pair_id, existing_pair);

  // Empty file: no lines of relative poses.
  const std::string path =
      WriteTempFile("relpose_test_empty_124.txt", "");

  glomap::ReadRelPose(path, images, view_graph);

  // No new pairs added.
  ASSERT_EQ(view_graph.image_pairs.size(), 1u);

  const auto it = view_graph.image_pairs.find(existing_pair_id);
  ASSERT_NE(it, view_graph.image_pairs.end());

  // All pairs are set to invalid before reading, and with no lines,
  // they remain invalid.
  EXPECT_FALSE(it->second.is_valid);
}

TEST_F(ReadRelPoseTest_124,
       AddsNewImageForUnknownFileName_124) {
  std::unordered_map<image_t, Image> images;

  // One existing image.
  Image existing_image(1, -1, "known.jpg");
  images.emplace(1, existing_image);

  ViewGraph view_graph;

  // Second file name is not present in images -> should create a new Image.
  const std::string path =
      WriteTempFile("relpose_test_newimage_124.txt",
                    "known.jpg newfile.jpg 0.0 0.0 0.0 1.0  5.0 6.0 7.0\n");

  glomap::ReadRelPose(path, images, view_graph);

  // One new image should be added (total 2).
  EXPECT_EQ(images.size(), 2u);

  // Find the new image by file name.
  bool found_new = false;
  image_t new_image_id = -1;
  for (const auto& kv : images) {
    if (kv.second.file_name == "newfile.jpg") {
      found_new = true;
      new_image_id = kv.first;
      break;
    }
  }
  EXPECT_TRUE(found_new);

  // A corresponding ImagePair using the new image must exist.
  ASSERT_EQ(view_graph.image_pairs.size(), 1u);
  const auto pair_it = view_graph.image_pairs.begin();
  const ImagePair& pair = pair_it->second;

  // One of the image IDs in the pair must be the new image.
  EXPECT_TRUE(pair.image_id1 == new_image_id ||
              pair.image_id2 == new_image_id);

  // Translation should be stored correctly.
  EXPECT_DOUBLE_EQ(pair.cam2_from_cam1.translation[0], 5.0);
  EXPECT_DOUBLE_EQ(pair.cam2_from_cam1.translation[1], 6.0);
  EXPECT_DOUBLE_EQ(pair.cam2_from_cam1.translation[2], 7.0);
}

TEST_F(ReadRelPoseTest_124,
       UpdatesExistingPairAndSetsValidAndConfig_124) {
  std::unordered_map<image_t, Image> images;

  Image img1(10, -1, "a.jpg");
  Image img2(20, -1, "b.jpg");
  images.emplace(10, img1);
  images.emplace(20, img2);

  ViewGraph view_graph;

  // Existing pair between these two images.
  ImagePair existing_pair(10, 20);
  existing_pair.is_valid = false;
  existing_pair.config = colmap::TwoViewGeometry::UNDEFINED;
  const image_pair_t pair_id = existing_pair.pair_id;
  view_graph.image_pairs.emplace(pair_id, existing_pair);

  // File contains a line for the same two images.
  const std::string path =
      WriteTempFile("relpose_test_update_124.txt",
                    "a.jpg b.jpg 0.0 0.0 0.0 1.0  9.0 8.0 7.0\n");

  glomap::ReadRelPose(path, images, view_graph);

  // Still exactly one pair, but it should have been updated.
  ASSERT_EQ(view_graph.image_pairs.size(), 1u);
  const auto it = view_graph.image_pairs.find(pair_id);
  ASSERT_NE(it, view_graph.image_pairs.end());
  const ImagePair& updated_pair = it->second;

  // is_valid must be set to true.
  EXPECT_TRUE(updated_pair.is_valid);
  // Config must be set to CALIBRATED.
  EXPECT_EQ(updated_pair.config,
            colmap::TwoViewGeometry::CALIBRATED);

  // Translation updated from file contents.
  EXPECT_DOUBLE_EQ(updated_pair.cam2_from_cam1.translation[0], 9.0);
  EXPECT_DOUBLE_EQ(updated_pair.cam2_from_cam1.translation[1], 8.0);
  EXPECT_DOUBLE_EQ(updated_pair.cam2_from_cam1.translation[2], 7.0);
}

TEST_F(ReadRelPoseTest_124,
       MultipleLinesCreateAndUpdatePairs_124) {
  std::unordered_map<image_t, Image> images;

  // Pre-existing image for one of the lines.
  Image img1(1, -1, "img1.jpg");
  images.emplace(1, img1);

  ViewGraph view_graph;

  // File:
  // 1) uses existing image and a new one
  // 2) uses two new images
  const std::string path =
      WriteTempFile("relpose_test_multi_124.txt",
                    "img1.jpg img2.jpg 0.0 0.0 0.0 1.0  1.0 2.0 3.0\n"
                    "img3.jpg img4.jpg 0.1 0.2 0.3 0.4  4.0 5.0 6.0\n");

  glomap::ReadRelPose(path, images, view_graph);

  // Total images:
  //   1 existing + 3 new = 4
  EXPECT_EQ(images.size(), 4u);

  // Two relative pose entries (two image pairs).
  EXPECT_EQ(view_graph.image_pairs.size(), 2u);

  // Every stored pair must refer to valid image IDs in the images map.
  for (const auto& kv : view_graph.image_pairs) {
    const ImagePair& p = kv.second;

    auto it1 = images.find(p.image_id1);
    auto it2 = images.find(p.image_id2);
    EXPECT_NE(it1, images.end());
    EXPECT_NE(it2, images.end());

    // All newly created pairs should have some translation set
    // based on the file content.
    // We just check they are finite values.
    EXPECT_TRUE(std::isfinite(p.cam2_from_cam1.translation[0]));
    EXPECT_TRUE(std::isfinite(p.cam2_from_cam1.translation[1]));
    EXPECT_TRUE(std::isfinite(p.cam2_from_cam1.translation[2]));
  }
}

}  // namespace
