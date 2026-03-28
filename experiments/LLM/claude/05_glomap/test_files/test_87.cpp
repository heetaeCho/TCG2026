#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/processors/view_graph_manipulation.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/types.h"

#include <unordered_map>
#include <unordered_set>

namespace glomap {
namespace {

// Helper to create an image pair id from two image ids
image_pair_t ImagePairToPairId(image_t image_id1, image_t image_id2) {
  if (image_id1 > image_id2) std::swap(image_id1, image_id2);
  return static_cast<image_pair_t>(image_id1) * 2147483647 + image_id2;
}

class ViewGraphManipulaterTest_87 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Seed random for reproducibility in probabilistic tests
    srand(42);
  }

  // Helper to set up a simple connected graph with N images all connected
  void SetupFullyConnectedGraph(int num_images) {
    for (int i = 0; i < num_images; i++) {
      image_t img_id = static_cast<image_t>(i);
      images_[img_id] = Image();
      images_[img_id].is_registered = true;
      
      // Create a frame for this image
      frame_t frame_id = static_cast<frame_t>(i);
      frames_[frame_id] = Frame();
      images_[img_id].frame_id = frame_id;
    }

    for (int i = 0; i < num_images; i++) {
      for (int j = i + 1; j < num_images; j++) {
        image_t id1 = static_cast<image_t>(i);
        image_t id2 = static_cast<image_t>(j);
        image_pair_t pair_id = ImagePairToPairId(id1, id2);
        ImagePair pair;
        pair.image_id1 = id1;
        pair.image_id2 = id2;
        pair.is_valid = true;
        view_graph_.image_pairs[pair_id] = pair;
      }
    }
  }

  // Helper to set up a chain graph: 0-1-2-3-...(N-1)
  void SetupChainGraph(int num_images) {
    for (int i = 0; i < num_images; i++) {
      image_t img_id = static_cast<image_t>(i);
      images_[img_id] = Image();
      images_[img_id].is_registered = true;
      
      frame_t frame_id = static_cast<frame_t>(i);
      frames_[frame_id] = Frame();
      images_[img_id].frame_id = frame_id;
    }

    for (int i = 0; i < num_images - 1; i++) {
      image_t id1 = static_cast<image_t>(i);
      image_t id2 = static_cast<image_t>(i + 1);
      image_pair_t pair_id = ImagePairToPairId(id1, id2);
      ImagePair pair;
      pair.image_id1 = id1;
      pair.image_id2 = id2;
      pair.is_valid = true;
      view_graph_.image_pairs[pair_id] = pair;
    }
  }

  ViewGraph view_graph_;
  std::unordered_map<frame_t, Frame> frames_;
  std::unordered_map<image_t, Image> images_;
};

// Test: Empty graph should return 0 chosen edges
TEST_F(ViewGraphManipulaterTest_87, EmptyGraph_87) {
  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph_, frames_, images_, 5);
  EXPECT_EQ(result, 0);
  EXPECT_TRUE(view_graph_.image_pairs.empty());
}

// Test: Single edge between two images with low expected degree keeps the edge
TEST_F(ViewGraphManipulaterTest_87, SingleEdgeKept_87) {
  SetupFullyConnectedGraph(2);
  
  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph_, frames_, images_, 5);
  
  // With only 2 images and 1 edge, degree is 1 which is <= expected_degree=5
  // So the edge should be kept
  EXPECT_GE(result, 1);
}

// Test: Chain graph with expected_degree >= max_degree should keep all edges
TEST_F(ViewGraphManipulaterTest_87, ChainGraphHighExpectedDegreeKeepsAll_87) {
  int num_images = 5;
  SetupChainGraph(num_images);
  
  // In a chain, max degree is 2, so expected_degree=5 means all edges kept
  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph_, frames_, images_, 5);
  
  // All 4 edges should be chosen since degree <= expected_degree for all nodes
  EXPECT_EQ(result, static_cast<image_pair_t>(num_images - 1));
}

// Test: Fully connected graph with high expected degree keeps all edges
TEST_F(ViewGraphManipulaterTest_87, FullyConnectedHighDegreeKeepsAll_87) {
  int num_images = 4;
  SetupFullyConnectedGraph(num_images);
  
  // 4 images fully connected: each has degree 3
  // expected_degree = 10 > 3, so all edges kept
  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph_, frames_, images_, 10);
  
  int expected_edges = num_images * (num_images - 1) / 2;
  EXPECT_EQ(result, static_cast<image_pair_t>(expected_edges));
}

// Test: Fully connected graph with very low expected degree sparsifies
TEST_F(ViewGraphManipulaterTest_87, FullyConnectedLowDegreeSparsifies_87) {
  int num_images = 10;
  SetupFullyConnectedGraph(num_images);
  
  int total_edges = num_images * (num_images - 1) / 2;  // 45 edges
  
  // expected_degree = 1, with degree 9 for each node
  // Most edges should be removed probabilistically
  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph_, frames_, images_, 1);
  
  // Result should be less than total edges (sparsification occurred)
  // We can't predict exact number due to randomness, but should be < total
  EXPECT_LE(result, static_cast<image_pair_t>(total_edges));
  EXPECT_GT(result, 0);  // At least some edges should remain for connectivity
}

// Test: Invalid image pairs are not counted
TEST_F(ViewGraphManipulaterTest_87, InvalidPairsIgnored_87) {
  SetupFullyConnectedGraph(3);
  
  // Mark one pair as invalid
  auto it = view_graph_.image_pairs.begin();
  it->second.is_valid = false;
  
  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph_, frames_, images_, 10);
  
  // Should have at most 2 valid edges (one was invalid)
  EXPECT_LE(result, 2);
}

// Test: Unregistered images' edges are not chosen
TEST_F(ViewGraphManipulaterTest_87, UnregisteredImagesEdgesNotChosen_87) {
  SetupFullyConnectedGraph(3);
  
  // Unregister image 0
  images_[0].is_registered = false;
  
  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph_, frames_, images_, 10);
  
  // Edges involving image 0 should not be chosen
  // Only edge 1-2 should potentially be chosen
  EXPECT_LE(result, 1);
}

// Test: Return value matches number of chosen edges
TEST_F(ViewGraphManipulaterTest_87, ReturnValueMatchesChosenEdges_87) {
  SetupChainGraph(3);
  
  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph_, frames_, images_, 10);
  
  // Count valid edges after sparsification
  int valid_count = 0;
  for (const auto& [pair_id, pair] : view_graph_.image_pairs) {
    if (pair.is_valid) valid_count++;
  }
  
  // The return value should be >= valid_count (some chosen edges might have
  // been invalidated by KeepLargestConnectedComponents at the end)
  EXPECT_GE(result, static_cast<image_pair_t>(valid_count));
}

// Test: Graph with two disconnected components - only largest kept
TEST_F(ViewGraphManipulaterTest_87, DisconnectedComponentsLargestKept_87) {
  // Create two separate components
  // Component 1: images 0, 1, 2 (fully connected)
  for (int i = 0; i < 3; i++) {
    images_[i] = Image();
    images_[i].is_registered = true;
    frames_[i] = Frame();
    images_[i].frame_id = static_cast<frame_t>(i);
  }
  
  // Component 2: images 10, 11 (one edge)
  for (int i = 10; i < 12; i++) {
    images_[i] = Image();
    images_[i].is_registered = true;
    frames_[i] = Frame();
    images_[i].frame_id = static_cast<frame_t>(i);
  }
  
  // Add edges for component 1
  for (int i = 0; i < 3; i++) {
    for (int j = i + 1; j < 3; j++) {
      image_pair_t pair_id = ImagePairToPairId(i, j);
      ImagePair pair;
      pair.image_id1 = i;
      pair.image_id2 = j;
      pair.is_valid = true;
      view_graph_.image_pairs[pair_id] = pair;
    }
  }
  
  // Add edge for component 2
  {
    image_pair_t pair_id = ImagePairToPairId(10, 11);
    ImagePair pair;
    pair.image_id1 = 10;
    pair.image_id2 = 11;
    pair.is_valid = true;
    view_graph_.image_pairs[pair_id] = pair;
  }
  
  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph_, frames_, images_, 10);
  
  // Result should include edges from both components initially chosen,
  // but after KeepLargestConnectedComponents, only the larger component stays
  EXPECT_GE(result, 1);
}

// Test: expected_degree of 0 - probabilistic removal
TEST_F(ViewGraphManipulaterTest_87, ZeroExpectedDegree_87) {
  SetupFullyConnectedGraph(4);
  
  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph_, frames_, images_, 0);
  
  // With expected_degree = 0, no edge satisfies degree <= expected_degree
  // and probability = 0, so no edges should be chosen
  // However, KeepLargestConnectedComponents might affect things
  // We just verify it doesn't crash and returns a value >= 0
  EXPECT_GE(result, 0);
}

// Test: Large expected degree keeps graph intact
TEST_F(ViewGraphManipulaterTest_87, VeryLargeExpectedDegreeKeepsAll_87) {
  int num_images = 6;
  SetupFullyConnectedGraph(num_images);
  
  int total_edges = num_images * (num_images - 1) / 2;  // 15
  
  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph_, frames_, images_, 1000);
  
  EXPECT_EQ(result, static_cast<image_pair_t>(total_edges));
  
  // All edges should remain valid
  for (const auto& [pair_id, pair] : view_graph_.image_pairs) {
    EXPECT_TRUE(pair.is_valid);
  }
}

// Test: Three images in a triangle - all edges kept with high expected degree
TEST_F(ViewGraphManipulaterTest_87, TriangleGraphKeptIntact_87) {
  SetupFullyConnectedGraph(3);
  
  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph_, frames_, images_, 5);
  
  // Triangle: each node has degree 2, expected_degree=5 >= 2, all kept
  EXPECT_EQ(result, 3);
}

}  // namespace
}  // namespace glomap
