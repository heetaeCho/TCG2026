#include <gtest/gtest.h>
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image_pair.h"

namespace glomap {
namespace {

using image_t = colmap::image_t;
using image_pair_t = colmap::image_pair_t;

class ViewGraphTest_95 : public ::testing::Test {
 protected:
  ViewGraph view_graph_;
};

// Test that an empty view graph produces an empty adjacency list
TEST_F(ViewGraphTest_95, EmptyViewGraphProducesEmptyAdjacencyList_95) {
  auto adjacency_list = view_graph_.CreateImageAdjacencyList();
  EXPECT_TRUE(adjacency_list.empty());
}

// Test that a single valid image pair creates correct adjacency entries
TEST_F(ViewGraphTest_95, SingleValidPairCreatesAdjacency_95) {
  image_t id1 = 1;
  image_t id2 = 2;
  ImagePair pair(id1, id2);
  pair.is_valid = true;
  view_graph_.image_pairs[pair.pair_id] = pair;

  auto adjacency_list = view_graph_.CreateImageAdjacencyList();

  ASSERT_EQ(adjacency_list.size(), 2);
  EXPECT_EQ(adjacency_list[id1].size(), 1);
  EXPECT_EQ(adjacency_list[id2].size(), 1);
  EXPECT_TRUE(adjacency_list[id1].count(id2));
  EXPECT_TRUE(adjacency_list[id2].count(id1));
}

// Test that an invalid image pair does not appear in adjacency list
TEST_F(ViewGraphTest_95, InvalidPairNotInAdjacencyList_95) {
  image_t id1 = 1;
  image_t id2 = 2;
  ImagePair pair(id1, id2);
  pair.is_valid = false;
  view_graph_.image_pairs[pair.pair_id] = pair;

  auto adjacency_list = view_graph_.CreateImageAdjacencyList();

  EXPECT_TRUE(adjacency_list.empty());
}

// Test multiple valid pairs form correct adjacency
TEST_F(ViewGraphTest_95, MultipleValidPairsFormCorrectAdjacency_95) {
  image_t id1 = 1, id2 = 2, id3 = 3;
  
  ImagePair pair12(id1, id2);
  pair12.is_valid = true;
  view_graph_.image_pairs[pair12.pair_id] = pair12;

  ImagePair pair23(id2, id3);
  pair23.is_valid = true;
  view_graph_.image_pairs[pair23.pair_id] = pair23;

  ImagePair pair13(id1, id3);
  pair13.is_valid = true;
  view_graph_.image_pairs[pair13.pair_id] = pair13;

  auto adjacency_list = view_graph_.CreateImageAdjacencyList();

  ASSERT_EQ(adjacency_list.size(), 3);
  
  // id1 should be connected to id2 and id3
  EXPECT_EQ(adjacency_list[id1].size(), 2);
  EXPECT_TRUE(adjacency_list[id1].count(id2));
  EXPECT_TRUE(adjacency_list[id1].count(id3));

  // id2 should be connected to id1 and id3
  EXPECT_EQ(adjacency_list[id2].size(), 2);
  EXPECT_TRUE(adjacency_list[id2].count(id1));
  EXPECT_TRUE(adjacency_list[id2].count(id3));

  // id3 should be connected to id1 and id2
  EXPECT_EQ(adjacency_list[id3].size(), 2);
  EXPECT_TRUE(adjacency_list[id3].count(id1));
  EXPECT_TRUE(adjacency_list[id3].count(id2));
}

// Test mix of valid and invalid pairs
TEST_F(ViewGraphTest_95, MixedValidAndInvalidPairs_95) {
  image_t id1 = 1, id2 = 2, id3 = 3;

  ImagePair pair12(id1, id2);
  pair12.is_valid = true;
  view_graph_.image_pairs[pair12.pair_id] = pair12;

  ImagePair pair23(id2, id3);
  pair23.is_valid = false;
  view_graph_.image_pairs[pair23.pair_id] = pair23;

  auto adjacency_list = view_graph_.CreateImageAdjacencyList();

  // Only pair (1,2) is valid
  ASSERT_EQ(adjacency_list.size(), 2);
  EXPECT_TRUE(adjacency_list[id1].count(id2));
  EXPECT_TRUE(adjacency_list[id2].count(id1));
  EXPECT_EQ(adjacency_list.count(id3), 0);
}

// Test that adjacency list is symmetric
TEST_F(ViewGraphTest_95, AdjacencyListIsSymmetric_95) {
  image_t id1 = 10, id2 = 20;
  ImagePair pair(id1, id2);
  pair.is_valid = true;
  view_graph_.image_pairs[pair.pair_id] = pair;

  auto adjacency_list = view_graph_.CreateImageAdjacencyList();

  // If id1 has id2 as neighbor, id2 must have id1
  for (const auto& [node, neighbors] : adjacency_list) {
    for (const auto& neighbor : neighbors) {
      EXPECT_TRUE(adjacency_list[neighbor].count(node))
          << "Symmetry violated: " << node << " -> " << neighbor;
    }
  }
}

// Test a chain of valid pairs: 1-2, 2-3, 3-4
TEST_F(ViewGraphTest_95, ChainOfPairs_95) {
  image_t id1 = 1, id2 = 2, id3 = 3, id4 = 4;

  ImagePair pair12(id1, id2);
  pair12.is_valid = true;
  view_graph_.image_pairs[pair12.pair_id] = pair12;

  ImagePair pair23(id2, id3);
  pair23.is_valid = true;
  view_graph_.image_pairs[pair23.pair_id] = pair23;

  ImagePair pair34(id3, id4);
  pair34.is_valid = true;
  view_graph_.image_pairs[pair34.pair_id] = pair34;

  auto adjacency_list = view_graph_.CreateImageAdjacencyList();

  ASSERT_EQ(adjacency_list.size(), 4);
  
  // Endpoints have 1 neighbor
  EXPECT_EQ(adjacency_list[id1].size(), 1);
  EXPECT_EQ(adjacency_list[id4].size(), 1);
  
  // Middle nodes have 2 neighbors
  EXPECT_EQ(adjacency_list[id2].size(), 2);
  EXPECT_EQ(adjacency_list[id3].size(), 2);
}

// Test star topology: one central node connected to many
TEST_F(ViewGraphTest_95, StarTopology_95) {
  image_t center = 0;
  const int num_leaves = 5;

  for (int i = 1; i <= num_leaves; ++i) {
    image_t leaf = static_cast<image_t>(i);
    ImagePair pair(center, leaf);
    pair.is_valid = true;
    view_graph_.image_pairs[pair.pair_id] = pair;
  }

  auto adjacency_list = view_graph_.CreateImageAdjacencyList();

  ASSERT_EQ(adjacency_list.size(), num_leaves + 1);
  EXPECT_EQ(adjacency_list[center].size(), static_cast<size_t>(num_leaves));

  for (int i = 1; i <= num_leaves; ++i) {
    image_t leaf = static_cast<image_t>(i);
    EXPECT_EQ(adjacency_list[leaf].size(), 1);
    EXPECT_TRUE(adjacency_list[leaf].count(center));
  }
}

// Test that all invalid pairs result in empty adjacency list
TEST_F(ViewGraphTest_95, AllInvalidPairsProduceEmptyAdjacency_95) {
  for (int i = 0; i < 5; ++i) {
    for (int j = i + 1; j < 5; ++j) {
      image_t id1 = static_cast<image_t>(i);
      image_t id2 = static_cast<image_t>(j);
      ImagePair pair(id1, id2);
      pair.is_valid = false;
      view_graph_.image_pairs[pair.pair_id] = pair;
    }
  }

  auto adjacency_list = view_graph_.CreateImageAdjacencyList();
  EXPECT_TRUE(adjacency_list.empty());
}

// Test that no self-loops are created (a node should not be adjacent to itself)
TEST_F(ViewGraphTest_95, NoSelfLoopsInAdjacency_95) {
  image_t id1 = 5, id2 = 10;
  ImagePair pair(id1, id2);
  pair.is_valid = true;
  view_graph_.image_pairs[pair.pair_id] = pair;

  auto adjacency_list = view_graph_.CreateImageAdjacencyList();

  for (const auto& [node, neighbors] : adjacency_list) {
    EXPECT_EQ(neighbors.count(node), 0)
        << "Self-loop detected for node " << node;
  }
}

// Test disconnected components
TEST_F(ViewGraphTest_95, DisconnectedComponents_95) {
  // Component 1: 1-2
  ImagePair pair12(1, 2);
  pair12.is_valid = true;
  view_graph_.image_pairs[pair12.pair_id] = pair12;

  // Component 2: 3-4
  ImagePair pair34(3, 4);
  pair34.is_valid = true;
  view_graph_.image_pairs[pair34.pair_id] = pair34;

  auto adjacency_list = view_graph_.CreateImageAdjacencyList();

  ASSERT_EQ(adjacency_list.size(), 4);
  
  // Component 1
  EXPECT_TRUE(adjacency_list[1].count(2));
  EXPECT_TRUE(adjacency_list[2].count(1));
  EXPECT_FALSE(adjacency_list[1].count(3));
  EXPECT_FALSE(adjacency_list[1].count(4));

  // Component 2
  EXPECT_TRUE(adjacency_list[3].count(4));
  EXPECT_TRUE(adjacency_list[4].count(3));
  EXPECT_FALSE(adjacency_list[3].count(1));
  EXPECT_FALSE(adjacency_list[3].count(2));
}

}  // namespace
}  // namespace glomap
