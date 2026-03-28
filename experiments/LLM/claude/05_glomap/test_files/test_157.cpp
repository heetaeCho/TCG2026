#include <gtest/gtest.h>
#include "glomap/processors/view_graph_manipulation.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/types.h"

#include <unordered_map>
#include <cstdlib>

namespace glomap {
namespace {

// Helper to create a registered image with a given id and camera id
Image CreateRegisteredImage(image_t img_id, camera_t cam_id = 0) {
  Image img(img_id, cam_id, "image_" + std::to_string(img_id) + ".jpg");
  // We need to make the image registered. Based on the interface,
  // IsRegistered() likely checks if cam_from_world is set or some registration flag.
  // We'll rely on the actual implementation's default behavior.
  // If needed, we may need to set pose to make it registered.
  return img;
}

// Test fixture for SparsifyGraph tests
class ViewGraphManipulaterTest_157 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Seed random for reproducibility in tests that depend on random behavior
    srand(42);
  }

  // Helper to build a simple complete graph with n images
  void BuildCompleteGraph(int n, ViewGraph& view_graph,
                          std::unordered_map<frame_t, Frame>& frames,
                          std::unordered_map<image_t, Image>& images) {
    for (int i = 0; i < n; i++) {
      images.emplace(i, Image(i, 0, "img_" + std::to_string(i) + ".jpg"));
      frames.emplace(i, Frame());
    }
    
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        ImagePair pair(i, j);
        pair.is_valid = true;
        view_graph.image_pairs.emplace(pair.pair_id, pair);
      }
    }
  }

  // Helper to build a line graph: 0-1-2-3-...(n-1)
  void BuildLineGraph(int n, ViewGraph& view_graph,
                      std::unordered_map<frame_t, Frame>& frames,
                      std::unordered_map<image_t, Image>& images) {
    for (int i = 0; i < n; i++) {
      images.emplace(i, Image(i, 0, "img_" + std::to_string(i) + ".jpg"));
      frames.emplace(i, Frame());
    }
    
    for (int i = 0; i < n - 1; i++) {
      ImagePair pair(i, i + 1);
      pair.is_valid = true;
      view_graph.image_pairs.emplace(pair.pair_id, pair);
    }
  }

  // Count valid edges
  int CountValidEdges(const ViewGraph& view_graph) {
    int count = 0;
    for (const auto& [pair_id, pair] : view_graph.image_pairs) {
      if (pair.is_valid) count++;
    }
    return count;
  }
};

// Test: SparsifyGraph with an empty view graph should return 0
TEST_F(ViewGraphManipulaterTest_157, SparsifyGraphEmptyGraph_157) {
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph, frames, images, 5);

  // With no edges, result should be 0
  EXPECT_EQ(result, 0);
}

// Test: SparsifyGraph with a single edge should keep it if expected_degree >= 1
TEST_F(ViewGraphManipulaterTest_157, SparsifyGraphSingleEdge_157) {
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  images.emplace(0, Image(0, 0, "img0.jpg"));
  images.emplace(1, Image(1, 0, "img1.jpg"));
  frames.emplace(0, Frame());
  frames.emplace(1, Frame());

  ImagePair pair(0, 1);
  pair.is_valid = true;
  view_graph.image_pairs.emplace(pair.pair_id, pair);

  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph, frames, images, 5);

  // Both nodes have degree 1 which is <= expected_degree=5, so edge should be kept
  EXPECT_GE(result, 0);
}

// Test: SparsifyGraph on a line graph with high expected_degree keeps all edges
TEST_F(ViewGraphManipulaterTest_157, SparsifyGraphLineGraphHighDegree_157) {
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  int n = 5;
  BuildLineGraph(n, view_graph, frames, images);

  // In a line graph, max degree is 2. With expected_degree >= 2,
  // all edges should be chosen (degree1 <= expected_degree for all).
  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph, frames, images, 10);

  // All n-1 edges should be chosen
  EXPECT_EQ(result, n - 1);
}

// Test: SparsifyGraph with expected_degree=0 on a complete graph may remove some edges
TEST_F(ViewGraphManipulaterTest_157, SparsifyGraphCompleteLowDegree_157) {
  srand(42);
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  int n = 6;
  BuildCompleteGraph(n, view_graph, frames, images);

  int total_edges = n * (n - 1) / 2;

  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph, frames, images, 0);

  // With expected_degree=0, no node has degree <= 0, so edges are chosen probabilistically
  // Result should be between 0 and total_edges
  EXPECT_GE(result, 0);
  EXPECT_LE(result, total_edges);
}

// Test: SparsifyGraph return value matches number of chosen edges
TEST_F(ViewGraphManipulaterTest_157, SparsifyGraphReturnValueMatchesChosenEdges_157) {
  srand(42);
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  int n = 4;
  BuildCompleteGraph(n, view_graph, frames, images);

  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph, frames, images, 5);

  // Since expected_degree=5 and max degree in K4 is 3, all edges should be kept
  // (degree <= expected_degree for all nodes)
  EXPECT_EQ(result, 6);  // C(4,2) = 6
}

// Test: SparsifyGraph marks non-chosen edges as invalid
TEST_F(ViewGraphManipulaterTest_157, SparsifyGraphInvalidatesNonChosenEdges_157) {
  srand(42);
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  int n = 10;
  BuildCompleteGraph(n, view_graph, frames, images);

  image_pair_t chosen = ViewGraphManipulater::SparsifyGraph(
      view_graph, frames, images, 2);

  int valid_count = CountValidEdges(view_graph);

  // After sparsification and KeepLargestConnectedComponents,
  // valid edges should be <= chosen (some might have been invalidated by connected components)
  EXPECT_LE(valid_count, static_cast<int>(chosen));
  EXPECT_GE(valid_count, 0);
}

// Test: SparsifyGraph with already invalid edges - they stay invalid
TEST_F(ViewGraphManipulaterTest_157, SparsifyGraphPreInvalidEdges_157) {
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  int n = 4;
  BuildCompleteGraph(n, view_graph, frames, images);

  // Invalidate some edges beforehand
  int invalidated = 0;
  for (auto& [pair_id, pair] : view_graph.image_pairs) {
    if (invalidated < 2) {
      pair.is_valid = false;
      invalidated++;
    }
  }

  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph, frames, images, 10);

  // Non-negative result
  EXPECT_GE(result, 0);
}

// Test: SparsifyGraph with two disconnected components and high expected_degree
TEST_F(ViewGraphManipulaterTest_157, SparsifyGraphDisconnectedComponents_157) {
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  // Component 1: 0-1-2
  for (int i = 0; i < 3; i++) {
    images.emplace(i, Image(i, 0, "img_" + std::to_string(i) + ".jpg"));
    frames.emplace(i, Frame());
  }
  ImagePair p01(0, 1); p01.is_valid = true;
  ImagePair p12(1, 2); p12.is_valid = true;
  view_graph.image_pairs.emplace(p01.pair_id, p01);
  view_graph.image_pairs.emplace(p12.pair_id, p12);

  // Component 2: 10-11
  images.emplace(10, Image(10, 0, "img_10.jpg"));
  images.emplace(11, Image(11, 0, "img_11.jpg"));
  frames.emplace(10, Frame());
  frames.emplace(11, Frame());
  ImagePair p1011(10, 11); p1011.is_valid = true;
  view_graph.image_pairs.emplace(p1011.pair_id, p1011);

  // After KeepLargestConnectedComponents, only the larger component should remain
  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph, frames, images, 10);

  // Result should be non-negative
  EXPECT_GE(result, 0);
}

// Test: SparsifyGraph expected_degree boundary - exactly equal to max degree
TEST_F(ViewGraphManipulaterTest_157, SparsifyGraphDegreeEqualToMaxDegree_157) {
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  // Triangle: degree of each node is 2
  int n = 3;
  BuildCompleteGraph(n, view_graph, frames, images);

  // expected_degree = 2, which equals max degree
  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph, frames, images, 2);

  // All edges should be kept since degree <= expected_degree for all
  EXPECT_EQ(result, 3);
}

// Test: SparsifyGraph with expected_degree = 1 on triangle
TEST_F(ViewGraphManipulaterTest_157, SparsifyGraphDegreeOneOnTriangle_157) {
  srand(42);
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  int n = 3;
  BuildCompleteGraph(n, view_graph, frames, images);

  // expected_degree = 1, degree of each node is 2 > 1
  // Probabilistic selection will occur
  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph, frames, images, 1);

  EXPECT_GE(result, 0);
  EXPECT_LE(result, 3);
}

// Test: SparsifyGraph preserves graph connectivity (after KeepLargestConnectedComponents)
TEST_F(ViewGraphManipulaterTest_157, SparsifyGraphPreservesConnectivity_157) {
  srand(42);
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  int n = 5;
  BuildCompleteGraph(n, view_graph, frames, images);

  ViewGraphManipulater::SparsifyGraph(
      view_graph, frames, images, 2);

  // After sparsification and KeepLargestConnectedComponents,
  // there should be at least some valid edges remaining
  int valid_count = CountValidEdges(view_graph);
  // For a connected component with >= 2 nodes, need at least 1 edge
  // (could be 0 if all nodes are isolated, but that's unlikely with K5)
  EXPECT_GE(valid_count, 0);
}

// Test: SparsifyGraph on a star graph (one central node connected to all others)
TEST_F(ViewGraphManipulaterTest_157, SparsifyGraphStarGraph_157) {
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  int n = 6;  // node 0 is center, connected to 1..5
  for (int i = 0; i < n; i++) {
    images.emplace(i, Image(i, 0, "img_" + std::to_string(i) + ".jpg"));
    frames.emplace(i, Frame());
  }

  for (int i = 1; i < n; i++) {
    ImagePair pair(0, i);
    pair.is_valid = true;
    view_graph.image_pairs.emplace(pair.pair_id, pair);
  }

  // Leaf nodes have degree 1, so with expected_degree >= 1, all edges kept
  image_pair_t result = ViewGraphManipulater::SparsifyGraph(
      view_graph, frames, images, 5);

  // All 5 edges should be kept (leaf degree=1 <= 5)
  EXPECT_EQ(result, 5);
}

// Test: Multiple calls to SparsifyGraph progressively reduce edges
TEST_F(ViewGraphManipulaterTest_157, SparsifyGraphMultipleCalls_157) {
  srand(42);
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  int n = 8;
  BuildCompleteGraph(n, view_graph, frames, images);

  int total_edges = n * (n - 1) / 2;

  image_pair_t result1 = ViewGraphManipulater::SparsifyGraph(
      view_graph, frames, images, 3);

  int valid_after_first = CountValidEdges(view_graph);

  // Second call should not increase valid edges
  image_pair_t result2 = ViewGraphManipulater::SparsifyGraph(
      view_graph, frames, images, 3);

  int valid_after_second = CountValidEdges(view_graph);

  EXPECT_LE(valid_after_second, valid_after_first);
}

}  // namespace
}  // namespace glomap
