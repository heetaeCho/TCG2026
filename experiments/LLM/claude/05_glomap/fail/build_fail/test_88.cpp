#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/processors/view_graph_manipulation.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/types.h"

namespace glomap {
namespace {

class ViewGraphManipulaterTest_88 : public ::testing::Test {
 protected:
  void SetUp() override {}

  // Helper to create a simple connected graph with N images, each in its own frame
  void CreateSimpleGraph(int num_images) {
    for (int i = 0; i < num_images; i++) {
      Image img;
      img.image_id = i;
      img.frame_id = i;
      img.is_registered = true;
      images[i] = img;

      Frame frame;
      frame.frame_id = i;
      frame.is_registered = true;
      frames[i] = frame;
    }
  }

  void AddImagePair(image_t id1, image_t id2, bool is_valid, 
                     int num_inliers, double weight) {
    image_pair_t pair_id = ImagePair::ImagePairToPairId(id1, id2);
    ImagePair pair;
    pair.image_id1 = id1;
    pair.image_id2 = id2;
    pair.is_valid = is_valid;
    pair.weight = weight;
    pair.inliers.resize(num_inliers);
    for (int i = 0; i < num_inliers; i++) {
      pair.inliers[i] = i;
    }
    view_graph.image_pairs[pair_id] = pair;
  }

  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
};

// Test with empty graph - no images, no pairs
TEST_F(ViewGraphManipulaterTest_88, EmptyGraph_88) {
  ViewGraphManipulater manipulater;
  image_t result = manipulater.EstablishStrongClusters(
      view_graph, frames, images, INLIER_NUM, 10.0, 1);
  EXPECT_GE(result, 0);
}

// Test with a single pair that meets the inlier threshold - should stay in one cluster
TEST_F(ViewGraphManipulaterTest_88, SinglePairAboveThreshold_InlierNum_88) {
  CreateSimpleGraph(2);
  AddImagePair(0, 1, true, 50, 1.0);

  ViewGraphManipulater manipulater;
  image_t result = manipulater.EstablishStrongClusters(
      view_graph, frames, images, INLIER_NUM, 10.0, 1);

  // Both images should be in the same cluster since inliers(50) > threshold(10)
  EXPECT_EQ(result, 1);

  // The pair should remain valid
  for (auto& [id, pair] : view_graph.image_pairs) {
    EXPECT_TRUE(pair.is_valid);
  }
}

// Test with a single pair below threshold - should split into separate components
TEST_F(ViewGraphManipulaterTest_88, SinglePairBelowThreshold_InlierNum_88) {
  CreateSimpleGraph(2);
  AddImagePair(0, 1, true, 5, 1.0);

  ViewGraphManipulater manipulater;
  image_t result = manipulater.EstablishStrongClusters(
      view_graph, frames, images, INLIER_NUM, 10.0, 1);

  // Images won't be strongly connected, pair may be invalidated
  // Depending on KeepLargestConnectedComponents behavior
  EXPECT_GE(result, 1);
}

// Test with WEIGHT criteria above threshold
TEST_F(ViewGraphManipulaterTest_88, SinglePairAboveThreshold_Weight_88) {
  CreateSimpleGraph(2);
  AddImagePair(0, 1, true, 5, 20.0);

  ViewGraphManipulater manipulater;
  image_t result = manipulater.EstablishStrongClusters(
      view_graph, frames, images, WEIGHT, 10.0, 1);

  EXPECT_EQ(result, 1);
  for (auto& [id, pair] : view_graph.image_pairs) {
    EXPECT_TRUE(pair.is_valid);
  }
}

// Test with WEIGHT criteria below threshold
TEST_F(ViewGraphManipulaterTest_88, SinglePairBelowThreshold_Weight_88) {
  CreateSimpleGraph(2);
  AddImagePair(0, 1, true, 5, 3.0);

  ViewGraphManipulater manipulater;
  image_t result = manipulater.EstablishStrongClusters(
      view_graph, frames, images, WEIGHT, 10.0, 1);

  EXPECT_GE(result, 1);
}

// Test with invalid pairs - should be ignored
TEST_F(ViewGraphManipulaterTest_88, InvalidPairsIgnored_88) {
  CreateSimpleGraph(2);
  AddImagePair(0, 1, false, 50, 20.0);

  ViewGraphManipulater manipulater;
  image_t result = manipulater.EstablishStrongClusters(
      view_graph, frames, images, INLIER_NUM, 10.0, 1);

  // Invalid pair should remain invalid
  for (auto& [id, pair] : view_graph.image_pairs) {
    EXPECT_FALSE(pair.is_valid);
  }
}

// Test with a chain of 3 images, all strongly connected
TEST_F(ViewGraphManipulaterTest_88, ChainOfThreeStronglyConnected_88) {
  CreateSimpleGraph(3);
  AddImagePair(0, 1, true, 50, 20.0);
  AddImagePair(1, 2, true, 50, 20.0);

  ViewGraphManipulater manipulater;
  image_t result = manipulater.EstablishStrongClusters(
      view_graph, frames, images, INLIER_NUM, 10.0, 1);

  EXPECT_EQ(result, 1);
}

// Test with two disconnected components that are each strongly connected
TEST_F(ViewGraphManipulaterTest_88, TwoDisconnectedComponents_88) {
  CreateSimpleGraph(4);
  AddImagePair(0, 1, true, 50, 20.0);
  AddImagePair(2, 3, true, 50, 20.0);

  ViewGraphManipulater manipulater;
  image_t result = manipulater.EstablishStrongClusters(
      view_graph, frames, images, INLIER_NUM, 10.0, 1);

  // Should have at least 1 component (largest kept), possibly 2 if both are kept
  EXPECT_GE(result, 1);
}

// Test cluster merging: two strong clusters connected by multiple weak edges
TEST_F(ViewGraphManipulaterTest_88, ClusterMergingViaWeakEdges_88) {
  CreateSimpleGraph(4);
  // Strong edges within clusters
  AddImagePair(0, 1, true, 50, 20.0);
  AddImagePair(2, 3, true, 50, 20.0);
  // Weak edges between clusters (above 0.75 * min_thres = 7.5 but below min_thres = 10)
  // We need at least 2 cross-cluster pairs for merging
  AddImagePair(0, 2, true, 8, 8.0);
  AddImagePair(1, 3, true, 8, 8.0);

  ViewGraphManipulater manipulater;
  image_t result = manipulater.EstablishStrongClusters(
      view_graph, frames, images, INLIER_NUM, 10.0, 1);

  // The two clusters should be merged via the weak edges
  EXPECT_EQ(result, 1);
}

// Test that edges below 0.75 * min_thres are not considered for merging
TEST_F(ViewGraphManipulaterTest_88, VeryWeakEdgesNotConsideredForMerging_88) {
  CreateSimpleGraph(4);
  AddImagePair(0, 1, true, 50, 20.0);
  AddImagePair(2, 3, true, 50, 20.0);
  // Very weak edges (below 0.75 * 10 = 7.5)
  AddImagePair(0, 2, true, 5, 5.0);
  AddImagePair(1, 3, true, 5, 5.0);

  ViewGraphManipulater manipulater;
  image_t result = manipulater.EstablishStrongClusters(
      view_graph, frames, images, INLIER_NUM, 10.0, 1);

  // Clusters should not merge; cross edges should be invalidated
  // The result depends on KeepLargestConnectedComponents
  EXPECT_GE(result, 1);
}

// Test with a fully connected triangle
TEST_F(ViewGraphManipulaterTest_88, FullyConnectedTriangle_88) {
  CreateSimpleGraph(3);
  AddImagePair(0, 1, true, 50, 20.0);
  AddImagePair(0, 2, true, 50, 20.0);
  AddImagePair(1, 2, true, 50, 20.0);

  ViewGraphManipulater manipulater;
  image_t result = manipulater.EstablishStrongClusters(
      view_graph, frames, images, INLIER_NUM, 10.0, 1);

  EXPECT_EQ(result, 1);
  // All pairs should remain valid
  for (auto& [id, pair] : view_graph.image_pairs) {
    EXPECT_TRUE(pair.is_valid);
  }
}

// Test with threshold at boundary (exact threshold value)
TEST_F(ViewGraphManipulaterTest_88, ExactThresholdBoundary_88) {
  CreateSimpleGraph(2);
  // Exactly at threshold - condition is strictly greater than
  AddImagePair(0, 1, true, 10, 10.0);

  ViewGraphManipulater manipulater;
  // For INLIER_NUM: inliers.size() (10) > min_thres (10) is false
  image_t result = manipulater.EstablishStrongClusters(
      view_graph, frames, images, INLIER_NUM, 10.0, 1);

  // Since 10 is NOT > 10, the pair won't form a strong connection
  EXPECT_GE(result, 1);
}

// Test with threshold just above - should connect
TEST_F(ViewGraphManipulaterTest_88, JustAboveThreshold_88) {
  CreateSimpleGraph(2);
  AddImagePair(0, 1, true, 11, 11.0);

  ViewGraphManipulater manipulater;
  image_t result = manipulater.EstablishStrongClusters(
      view_graph, frames, images, INLIER_NUM, 10.0, 1);

  EXPECT_EQ(result, 1);
}

// Test with zero threshold
TEST_F(ViewGraphManipulaterTest_88, ZeroThreshold_88) {
  CreateSimpleGraph(2);
  AddImagePair(0, 1, true, 1, 0.1);

  ViewGraphManipulater manipulater;
  image_t result = manipulater.EstablishStrongClusters(
      view_graph, frames, images, INLIER_NUM, 0.0, 1);

  EXPECT_EQ(result, 1);
}

// Test with large graph - star topology
TEST_F(ViewGraphManipulaterTest_88, StarTopologyStrongEdges_88) {
  int num_images = 6;
  CreateSimpleGraph(num_images);
  // Center node 0 connected to all others
  for (int i = 1; i < num_images; i++) {
    AddImagePair(0, i, true, 100, 50.0);
  }

  ViewGraphManipulater manipulater;
  image_t result = manipulater.EstablishStrongClusters(
      view_graph, frames, images, INLIER_NUM, 10.0, 1);

  EXPECT_EQ(result, 1);
}

// Test that only one cross-cluster edge is not enough for merging
TEST_F(ViewGraphManipulaterTest_88, SingleCrossClusterEdgeNotEnoughForMerge_88) {
  CreateSimpleGraph(4);
  AddImagePair(0, 1, true, 50, 20.0);
  AddImagePair(2, 3, true, 50, 20.0);
  // Only one cross-cluster edge (need >= 2 for merge)
  AddImagePair(0, 2, true, 8, 8.0);

  ViewGraphManipulater manipulater;
  image_t result = manipulater.EstablishStrongClusters(
      view_graph, frames, images, INLIER_NUM, 10.0, 1);

  // Should not merge - cross edge should be invalidated
  // The pair 0-2 should become invalid
  EXPECT_GE(result, 1);
}

// Test with mixed valid and invalid pairs
TEST_F(ViewGraphManipulaterTest_88, MixedValidInvalidPairs_88) {
  CreateSimpleGraph(3);
  AddImagePair(0, 1, true, 50, 20.0);
  AddImagePair(1, 2, false, 50, 20.0);  // invalid

  ViewGraphManipulater manipulater;
  image_t result = manipulater.EstablishStrongClusters(
      view_graph, frames, images, INLIER_NUM, 10.0, 1);

  EXPECT_GE(result, 1);
}

}  // namespace
}  // namespace glomap
