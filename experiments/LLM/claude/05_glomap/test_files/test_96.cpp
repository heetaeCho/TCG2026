#include <gtest/gtest.h>
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"

#include <unordered_map>
#include <unordered_set>

namespace glomap {
namespace {

class ViewGraphTest_96 : public ::testing::Test {
 protected:
  void SetUp() override {}

  // Helper to create an Image with a given image_id, camera_id, and frame_id
  void AddImage(std::unordered_map<image_t, Image>& images,
                image_t img_id, camera_t cam_id, frame_t frame_id) {
    Image img(img_id, cam_id, "image_" + std::to_string(img_id));
    img.frame_id = frame_id;
    images.emplace(img_id, std::move(img));
  }

  // Helper to add a valid image pair to the view graph
  void AddImagePair(ViewGraph& vg, image_t id1, image_t id2, bool is_valid = true) {
    ImagePair pair(id1, id2);
    pair.is_valid = is_valid;
    image_pair_t pair_id = pair.pair_id;
    vg.image_pairs.emplace(pair_id, std::move(pair));
  }
};

// Test: Empty view graph produces empty adjacency list
TEST_F(ViewGraphTest_96, CreateFrameAdjacencyList_EmptyGraph_96) {
  ViewGraph vg;
  std::unordered_map<image_t, Image> images;

  auto adjacency = vg.CreateFrameAdjacencyList(images);

  EXPECT_TRUE(adjacency.empty());
}

// Test: Single valid pair creates bidirectional adjacency between frames
TEST_F(ViewGraphTest_96, CreateFrameAdjacencyList_SingleValidPair_96) {
  ViewGraph vg;
  std::unordered_map<image_t, Image> images;

  AddImage(images, 0, 0, 10);
  AddImage(images, 1, 0, 20);
  AddImagePair(vg, 0, 1, true);

  auto adjacency = vg.CreateFrameAdjacencyList(images);

  ASSERT_EQ(adjacency.size(), 2u);
  EXPECT_TRUE(adjacency[10].count(20));
  EXPECT_TRUE(adjacency[20].count(10));
}

// Test: Invalid pairs are excluded from the adjacency list
TEST_F(ViewGraphTest_96, CreateFrameAdjacencyList_InvalidPairExcluded_96) {
  ViewGraph vg;
  std::unordered_map<image_t, Image> images;

  AddImage(images, 0, 0, 10);
  AddImage(images, 1, 0, 20);
  AddImagePair(vg, 0, 1, false);

  auto adjacency = vg.CreateFrameAdjacencyList(images);

  EXPECT_TRUE(adjacency.empty());
}

// Test: Mix of valid and invalid pairs
TEST_F(ViewGraphTest_96, CreateFrameAdjacencyList_MixValidInvalid_96) {
  ViewGraph vg;
  std::unordered_map<image_t, Image> images;

  AddImage(images, 0, 0, 10);
  AddImage(images, 1, 0, 20);
  AddImage(images, 2, 0, 30);
  AddImagePair(vg, 0, 1, true);
  AddImagePair(vg, 1, 2, false);

  auto adjacency = vg.CreateFrameAdjacencyList(images);

  ASSERT_EQ(adjacency.size(), 2u);
  EXPECT_TRUE(adjacency[10].count(20));
  EXPECT_TRUE(adjacency[20].count(10));
  EXPECT_EQ(adjacency.count(30), 0u);
}

// Test: Multiple valid pairs form a connected adjacency
TEST_F(ViewGraphTest_96, CreateFrameAdjacencyList_MultipleValidPairs_96) {
  ViewGraph vg;
  std::unordered_map<image_t, Image> images;

  AddImage(images, 0, 0, 10);
  AddImage(images, 1, 0, 20);
  AddImage(images, 2, 0, 30);
  AddImagePair(vg, 0, 1, true);
  AddImagePair(vg, 1, 2, true);
  AddImagePair(vg, 0, 2, true);

  auto adjacency = vg.CreateFrameAdjacencyList(images);

  ASSERT_EQ(adjacency.size(), 3u);
  EXPECT_TRUE(adjacency[10].count(20));
  EXPECT_TRUE(adjacency[10].count(30));
  EXPECT_TRUE(adjacency[20].count(10));
  EXPECT_TRUE(adjacency[20].count(30));
  EXPECT_TRUE(adjacency[30].count(10));
  EXPECT_TRUE(adjacency[30].count(20));
}

// Test: Two images mapping to the same frame
TEST_F(ViewGraphTest_96, CreateFrameAdjacencyList_SameFrameId_96) {
  ViewGraph vg;
  std::unordered_map<image_t, Image> images;

  // Both images belong to the same frame
  AddImage(images, 0, 0, 10);
  AddImage(images, 1, 0, 10);
  AddImagePair(vg, 0, 1, true);

  auto adjacency = vg.CreateFrameAdjacencyList(images);

  // frame 10 should be adjacent to itself
  ASSERT_EQ(adjacency.size(), 1u);
  EXPECT_TRUE(adjacency[10].count(10));
}

// Test: Multiple images mapping to different frames with chain connectivity
TEST_F(ViewGraphTest_96, CreateFrameAdjacencyList_ChainConnectivity_96) {
  ViewGraph vg;
  std::unordered_map<image_t, Image> images;

  AddImage(images, 0, 0, 100);
  AddImage(images, 1, 0, 200);
  AddImage(images, 2, 0, 300);
  AddImage(images, 3, 0, 400);
  AddImagePair(vg, 0, 1, true);
  AddImagePair(vg, 1, 2, true);
  AddImagePair(vg, 2, 3, true);

  auto adjacency = vg.CreateFrameAdjacencyList(images);

  ASSERT_EQ(adjacency.size(), 4u);

  // Frame 100 only connects to 200
  EXPECT_EQ(adjacency[100].size(), 1u);
  EXPECT_TRUE(adjacency[100].count(200));

  // Frame 200 connects to 100 and 300
  EXPECT_EQ(adjacency[200].size(), 2u);
  EXPECT_TRUE(adjacency[200].count(100));
  EXPECT_TRUE(adjacency[200].count(300));

  // Frame 300 connects to 200 and 400
  EXPECT_EQ(adjacency[300].size(), 2u);
  EXPECT_TRUE(adjacency[300].count(200));
  EXPECT_TRUE(adjacency[300].count(400));

  // Frame 400 only connects to 300
  EXPECT_EQ(adjacency[400].size(), 1u);
  EXPECT_TRUE(adjacency[400].count(300));
}

// Test: Duplicate pairs (same image pair added multiple times) should not duplicate adjacency entries
TEST_F(ViewGraphTest_96, CreateFrameAdjacencyList_DuplicateEdgesNoDuplicateAdjacency_96) {
  ViewGraph vg;
  std::unordered_map<image_t, Image> images;

  AddImage(images, 0, 0, 10);
  AddImage(images, 1, 0, 20);

  // Since image_pairs is a map keyed by pair_id, adding the same pair again
  // just overwrites. But let's verify the adjacency set doesn't have duplicates.
  AddImagePair(vg, 0, 1, true);

  auto adjacency = vg.CreateFrameAdjacencyList(images);

  EXPECT_EQ(adjacency[10].size(), 1u);
  EXPECT_EQ(adjacency[20].size(), 1u);
}

// Test: All pairs invalid results in empty adjacency
TEST_F(ViewGraphTest_96, CreateFrameAdjacencyList_AllInvalidPairs_96) {
  ViewGraph vg;
  std::unordered_map<image_t, Image> images;

  AddImage(images, 0, 0, 10);
  AddImage(images, 1, 0, 20);
  AddImage(images, 2, 0, 30);
  AddImagePair(vg, 0, 1, false);
  AddImagePair(vg, 1, 2, false);
  AddImagePair(vg, 0, 2, false);

  auto adjacency = vg.CreateFrameAdjacencyList(images);

  EXPECT_TRUE(adjacency.empty());
}

// Test: Multiple images sharing the same frame, connected to different frames
TEST_F(ViewGraphTest_96, CreateFrameAdjacencyList_MultipleImagesPerFrame_96) {
  ViewGraph vg;
  std::unordered_map<image_t, Image> images;

  // Images 0 and 1 belong to frame 10, image 2 belongs to frame 20
  AddImage(images, 0, 0, 10);
  AddImage(images, 1, 0, 10);
  AddImage(images, 2, 0, 20);
  AddImagePair(vg, 0, 2, true);
  AddImagePair(vg, 1, 2, true);

  auto adjacency = vg.CreateFrameAdjacencyList(images);

  ASSERT_EQ(adjacency.size(), 2u);
  // Frame 10 adjacent to frame 20
  EXPECT_TRUE(adjacency[10].count(20));
  // Frame 20 adjacent to frame 10
  EXPECT_TRUE(adjacency[20].count(10));
  // No duplicate entries since it's a set
  EXPECT_EQ(adjacency[10].size(), 1u);
  EXPECT_EQ(adjacency[20].size(), 1u);
}

// Test: CreateImageAdjacencyList with empty graph
TEST_F(ViewGraphTest_96, CreateImageAdjacencyList_EmptyGraph_96) {
  ViewGraph vg;
  auto adjacency = vg.CreateImageAdjacencyList();
  EXPECT_TRUE(adjacency.empty());
}

// Test: CreateImageAdjacencyList with valid pairs
TEST_F(ViewGraphTest_96, CreateImageAdjacencyList_ValidPairs_96) {
  ViewGraph vg;
  AddImagePair(vg, 0, 1, true);
  AddImagePair(vg, 1, 2, true);

  auto adjacency = vg.CreateImageAdjacencyList();

  ASSERT_EQ(adjacency.size(), 3u);
  EXPECT_TRUE(adjacency[0].count(1));
  EXPECT_TRUE(adjacency[1].count(0));
  EXPECT_TRUE(adjacency[1].count(2));
  EXPECT_TRUE(adjacency[2].count(1));
}

// Test: CreateImageAdjacencyList with invalid pairs excluded
TEST_F(ViewGraphTest_96, CreateImageAdjacencyList_InvalidPairsExcluded_96) {
  ViewGraph vg;
  AddImagePair(vg, 0, 1, true);
  AddImagePair(vg, 1, 2, false);

  auto adjacency = vg.CreateImageAdjacencyList();

  EXPECT_EQ(adjacency.size(), 2u);
  EXPECT_TRUE(adjacency[0].count(1));
  EXPECT_TRUE(adjacency[1].count(0));
  EXPECT_EQ(adjacency.count(2), 0u);
}

// Test: Large number of frames forming a star topology
TEST_F(ViewGraphTest_96, CreateFrameAdjacencyList_StarTopology_96) {
  ViewGraph vg;
  std::unordered_map<image_t, Image> images;

  // Center image
  AddImage(images, 0, 0, 0);

  // Spoke images
  const int num_spokes = 50;
  for (int i = 1; i <= num_spokes; ++i) {
    AddImage(images, static_cast<image_t>(i), 0, static_cast<frame_t>(i));
    AddImagePair(vg, 0, static_cast<image_t>(i), true);
  }

  auto adjacency = vg.CreateFrameAdjacencyList(images);

  // Center frame should be adjacent to all spoke frames
  EXPECT_EQ(adjacency[0].size(), static_cast<size_t>(num_spokes));

  // Each spoke frame should only be adjacent to the center
  for (int i = 1; i <= num_spokes; ++i) {
    EXPECT_EQ(adjacency[static_cast<frame_t>(i)].size(), 1u);
    EXPECT_TRUE(adjacency[static_cast<frame_t>(i)].count(0));
  }
}

}  // namespace
}  // namespace glomap
