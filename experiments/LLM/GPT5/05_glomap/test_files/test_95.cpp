// File: view_graph_create_image_adjacency_list_test_95.cc

#include <gtest/gtest.h>

#include "glomap/scene/view_graph.h"
#include "glomap/scene/image_pair.h"

namespace glomap {

class ViewGraphTest_95 : public ::testing::Test {
 protected:
  ViewGraph view_graph_;
};

// TEST 1: Empty ViewGraph should produce an empty adjacency list.
TEST_F(ViewGraphTest_95, EmptyGraph_ReturnsEmptyAdjacencyList_95) {
  // image_pairs is empty by default.
  const auto adjacency_list = view_graph_.CreateImageAdjacencyList();

  EXPECT_TRUE(adjacency_list.empty());
}

// TEST 2: Single valid pair should create symmetric adjacency between two images.
TEST_F(ViewGraphTest_95, SingleValidPair_CreatesSymmetricAdjacency_95) {
  // Arrange
  ImagePair pair_12(1, 2);
  view_graph_.image_pairs.emplace(pair_12.pair_id, pair_12);

  // Act
  const auto adjacency_list = view_graph_.CreateImageAdjacencyList();

  // Assert
  ASSERT_EQ(adjacency_list.size(), 2u);

  auto it1 = adjacency_list.find(1);
  ASSERT_NE(it1, adjacency_list.end());
  EXPECT_EQ(it1->second.size(), 1u);
  EXPECT_NE(it1->second.find(2), it1->second.end());

  auto it2 = adjacency_list.find(2);
  ASSERT_NE(it2, adjacency_list.end());
  EXPECT_EQ(it2->second.size(), 1u);
  EXPECT_NE(it2->second.find(1), it2->second.end());
}

// TEST 3: Invalid pairs should be ignored in the adjacency list.
TEST_F(ViewGraphTest_95, InvalidPairsAreIgnored_95) {
  // Arrange
  ImagePair valid_pair(1, 2);
  ImagePair invalid_pair(2, 3);
  invalid_pair.is_valid = false;

  view_graph_.image_pairs.emplace(valid_pair.pair_id, valid_pair);
  view_graph_.image_pairs.emplace(invalid_pair.pair_id, invalid_pair);

  // Act
  const auto adjacency_list = view_graph_.CreateImageAdjacencyList();

  // Assert: only images from the valid pair (1,2) should appear.
  ASSERT_EQ(adjacency_list.size(), 2u);

  // Image 1 should be connected only to 2
  auto it1 = adjacency_list.find(1);
  ASSERT_NE(it1, adjacency_list.end());
  EXPECT_EQ(it1->second.size(), 1u);
  EXPECT_NE(it1->second.find(2), it1->second.end());

  // Image 2 should be connected only to 1
  auto it2 = adjacency_list.find(2);
  ASSERT_NE(it2, adjacency_list.end());
  EXPECT_EQ(it2->second.size(), 1u);
  EXPECT_NE(it2->second.find(1), it2->second.end());

  // Image 3 should not be present at all
  EXPECT_EQ(adjacency_list.find(3), adjacency_list.end());
}

// TEST 4: Multiple valid pairs sharing a node should aggregate neighbors.
TEST_F(ViewGraphTest_95, MultiplePairs_AggregatesNeighborsPerImage_95) {
  // Arrange
  ImagePair pair_12(1, 2);
  ImagePair pair_13(1, 3);
  ImagePair pair_24(2, 4);

  view_graph_.image_pairs.emplace(pair_12.pair_id, pair_12);
  view_graph_.image_pairs.emplace(pair_13.pair_id, pair_13);
  view_graph_.image_pairs.emplace(pair_24.pair_id, pair_24);

  // Act
  const auto adjacency_list = view_graph_.CreateImageAdjacencyList();

  // Assert: image 1 should be adjacent to 2 and 3
  auto it1 = adjacency_list.find(1);
  ASSERT_NE(it1, adjacency_list.end());
  EXPECT_EQ(it1->second.size(), 2u);
  EXPECT_NE(it1->second.find(2), it1->second.end());
  EXPECT_NE(it1->second.find(3), it1->second.end());

  // Image 2 should be adjacent to 1 and 4
  auto it2 = adjacency_list.find(2);
  ASSERT_NE(it2, adjacency_list.end());
  EXPECT_EQ(it2->second.size(), 2u);
  EXPECT_NE(it2->second.find(1), it2->second.end());
  EXPECT_NE(it2->second.find(4), it2->second.end());

  // Image 3 should be adjacent only to 1
  auto it3 = adjacency_list.find(3);
  ASSERT_NE(it3, adjacency_list.end());
  EXPECT_EQ(it3->second.size(), 1u);
  EXPECT_NE(it3->second.find(1), it3->second.end());

  // Image 4 should be adjacent only to 2
  auto it4 = adjacency_list.find(4);
  ASSERT_NE(it4, adjacency_list.end());
  EXPECT_EQ(it4->second.size(), 1u);
  EXPECT_NE(it4->second.find(2), it4->second.end());
}

}  // namespace glomap
