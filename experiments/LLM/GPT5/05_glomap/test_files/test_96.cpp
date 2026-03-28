// File: view_graph_create_frame_adjacency_list_test_96.cc

#include <gtest/gtest.h>

#include <unordered_map>
#include <unordered_set>

#include "glomap/scene/view_graph.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"

class ViewGraphTest_96 : public ::testing::Test {
protected:
  glomap::ViewGraph view_graph_;
  std::unordered_map<image_t, glomap::Image> images_;

  glomap::Image MakeImageWithFrame(image_t image_id, frame_t frame_id) {
    glomap::Image img;
    img.frame_id = frame_id;   // public member in the partial interface
    return img;
  }
};

// Normal operation: single valid pair creates symmetric adjacency between frames.
TEST_F(ViewGraphTest_96, SingleValidPairCreatesBidirectionalAdjacency_96) {
  // Arrange
  const image_t kImageId1 = static_cast<image_t>(1);
  const image_t kImageId2 = static_cast<image_t>(2);
  const frame_t kFrameId1 = static_cast<frame_t>(10);
  const frame_t kFrameId2 = static_cast<frame_t>(20);

  images_.emplace(kImageId1, MakeImageWithFrame(kImageId1, kFrameId1));
  images_.emplace(kImageId2, MakeImageWithFrame(kImageId2, kFrameId2));

  glomap::ImagePair pair(kImageId1, kImageId2);
  pair.is_valid = true;
  view_graph_.image_pairs.emplace(static_cast<image_pair_t>(0), pair);

  // Act
  const auto adjacency = view_graph_.CreateFrameAdjacencyList(images_);

  // Assert
  ASSERT_EQ(adjacency.size(), 2u);

  auto it1 = adjacency.find(kFrameId1);
  ASSERT_NE(it1, adjacency.end());
  EXPECT_EQ(it1->second.size(), 1u);
  EXPECT_EQ(it1->second.count(kFrameId2), 1u);

  auto it2 = adjacency.find(kFrameId2);
  ASSERT_NE(it2, adjacency.end());
  EXPECT_EQ(it2->second.size(), 1u);
  EXPECT_EQ(it2->second.count(kFrameId1), 1u);
}

// Boundary: no image pairs → empty adjacency list.
TEST_F(ViewGraphTest_96, EmptyImagePairsReturnsEmptyAdjacency_96) {
  // Arrange: view_graph_.image_pairs is empty, images_ can be empty too.

  // Act
  const auto adjacency = view_graph_.CreateFrameAdjacencyList(images_);

  // Assert
  EXPECT_TRUE(adjacency.empty());
}

// Error/edge: pair marked invalid should be ignored.
TEST_F(ViewGraphTest_96, InvalidPairsAreIgnored_96) {
  // Arrange
  const image_t kImageId1 = static_cast<image_t>(1);
  const image_t kImageId2 = static_cast<image_t>(2);
  const frame_t kFrameId1 = static_cast<frame_t>(10);
  const frame_t kFrameId2 = static_cast<frame_t>(20);

  images_.emplace(kImageId1, MakeImageWithFrame(kImageId1, kFrameId1));
  images_.emplace(kImageId2, MakeImageWithFrame(kImageId2, kFrameId2));

  glomap::ImagePair pair(kImageId1, kImageId2);
  pair.is_valid = false;
  view_graph_.image_pairs.emplace(static_cast<image_pair_t>(0), pair);

  // Act
  const auto adjacency = view_graph_.CreateFrameAdjacencyList(images_);

  // Assert: invalid pair should produce no adjacency.
  EXPECT_TRUE(adjacency.empty());
}

// Normal / multi-pair: multiple pairs sharing a frame accumulate neighbors correctly.
TEST_F(ViewGraphTest_96, MultiplePairsAccumulateNeighbors_96) {
  // Arrange
  const image_t kImageId1 = static_cast<image_t>(1);
  const image_t kImageId2 = static_cast<image_t>(2);
  const image_t kImageId3 = static_cast<image_t>(3);

  const frame_t kFrameId1 = static_cast<frame_t>(100);
  const frame_t kFrameId2 = static_cast<frame_t>(200);
  const frame_t kFrameId3 = static_cast<frame_t>(300);

  images_.emplace(kImageId1, MakeImageWithFrame(kImageId1, kFrameId1));
  images_.emplace(kImageId2, MakeImageWithFrame(kImageId2, kFrameId2));
  images_.emplace(kImageId3, MakeImageWithFrame(kImageId3, kFrameId3));

  glomap::ImagePair pair12(kImageId1, kImageId2);
  pair12.is_valid = true;
  glomap::ImagePair pair13(kImageId1, kImageId3);
  pair13.is_valid = true;

  view_graph_.image_pairs.emplace(static_cast<image_pair_t>(0), pair12);
  view_graph_.image_pairs.emplace(static_cast<image_pair_t>(1), pair13);

  // Act
  const auto adjacency = view_graph_.CreateFrameAdjacencyList(images_);

  // Assert
  auto it1 = adjacency.find(kFrameId1);
  ASSERT_NE(it1, adjacency.end());
  EXPECT_EQ(it1->second.size(), 2u);
  EXPECT_EQ(it1->second.count(kFrameId2), 1u);
  EXPECT_EQ(it1->second.count(kFrameId3), 1u);

  auto it2 = adjacency.find(kFrameId2);
  ASSERT_NE(it2, adjacency.end());
  EXPECT_EQ(it2->second.size(), 1u);
  EXPECT_EQ(it2->second.count(kFrameId1), 1u);

  auto it3 = adjacency.find(kFrameId3);
  ASSERT_NE(it3, adjacency.end());
  EXPECT_EQ(it3->second.size(), 1u);
  EXPECT_EQ(it3->second.count(kFrameId1), 1u);
}

// Boundary / degenerate: if both images map to the same frame, we get a self-loop entry.
TEST_F(ViewGraphTest_96, SameFrameIdCreatesSelfLoop_96) {
  // Arrange
  const image_t kImageId1 = static_cast<image_t>(1);
  const image_t kImageId2 = static_cast<image_t>(2);
  const frame_t kSharedFrameId = static_cast<frame_t>(42);

  images_.emplace(kImageId1, MakeImageWithFrame(kImageId1, kSharedFrameId));
  images_.emplace(kImageId2, MakeImageWithFrame(kImageId2, kSharedFrameId));

  glomap::ImagePair pair(kImageId1, kImageId2);
  pair.is_valid = true;
  view_graph_.image_pairs.emplace(static_cast<image_pair_t>(0), pair);

  // Act
  const auto adjacency = view_graph_.CreateFrameAdjacencyList(images_);

  // Assert: We expect an entry for the shared frame, and it should contain itself.
  auto it = adjacency.find(kSharedFrameId);
  ASSERT_NE(it, adjacency.end());
  EXPECT_EQ(it->second.count(kSharedFrameId), 1u);
}

// Exceptional / error case: missing image in the images map triggers an exception via at().
TEST_F(ViewGraphTest_96, MissingImageThrowsOutOfRange_96) {
  // Arrange
  const image_t kImageId1 = static_cast<image_t>(1);
  const image_t kImageId2 = static_cast<image_t>(2);

  // Only insert one of the images; the other will be missing.
  images_.emplace(kImageId1, MakeImageWithFrame(kImageId1, static_cast<frame_t>(10)));

  glomap::ImagePair pair(kImageId1, kImageId2);
  pair.is_valid = true;
  view_graph_.image_pairs.emplace(static_cast<image_pair_t>(0), pair);

  // Act & Assert
  EXPECT_THROW(
      {
        const auto adjacency = view_graph_.CreateFrameAdjacencyList(images_);
        (void)adjacency;
      },
      std::out_of_range);
}
