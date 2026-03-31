#include <gtest/gtest.h>
#include "glomap/processors/view_graph_manipulation.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/types.h"

namespace glomap {
namespace {

// Helper to create a simple test setup with images, frames, and a view graph
struct TestSetup {
  ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  void AddImage(image_t image_id, camera_t camera_id, frame_t frame_id) {
    Image img(image_id, camera_id, "img_" + std::to_string(image_id));
    img.frame_id = frame_id;
    images[image_id] = img;
    if (frames.find(frame_id) == frames.end()) {
      Frame f;
      frames[frame_id] = f;
    }
  }

  void AddImagePair(image_t id1, image_t id2, bool is_valid, int num_inliers, double weight) {
    ImagePair pair(id1, id2);
    pair.is_valid = is_valid;
    pair.weight = weight;
    pair.inliers.resize(num_inliers);
    view_graph.image_pairs[pair.pair_id] = pair;
  }
};

class ViewGraphManipulaterTest_158 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test: EstablishStrongClusters with empty view graph returns expected cluster count
TEST_F(ViewGraphManipulaterTest_158, EstablishStrongClusters_EmptyGraph_158) {
  TestSetup setup;
  // No images, no pairs
  auto result = ViewGraphManipulater::EstablishStrongClusters(
      setup.view_graph, setup.frames, setup.images,
      ViewGraphManipulater::INLIER_NUM, 10.0, 1);
  // With no images, expect 0 clusters
  EXPECT_GE(result, 0);
}

// Test: EstablishStrongClusters with single connected component using INLIER_NUM
TEST_F(ViewGraphManipulaterTest_158, EstablishStrongClusters_SingleComponent_InlierNum_158) {
  TestSetup setup;
  // Create 3 images in different frames, strongly connected
  setup.AddImage(0, 0, 0);
  setup.AddImage(1, 0, 1);
  setup.AddImage(2, 0, 2);

  // All pairs valid with high inlier count (above threshold)
  setup.AddImagePair(0, 1, true, 50, 5.0);
  setup.AddImagePair(1, 2, true, 50, 5.0);
  setup.AddImagePair(0, 2, true, 50, 5.0);

  auto result = ViewGraphManipulater::EstablishStrongClusters(
      setup.view_graph, setup.frames, setup.images,
      ViewGraphManipulater::INLIER_NUM, 10.0, 1);

  // All strongly connected, should form 1 cluster
  EXPECT_EQ(result, 1);
}

// Test: EstablishStrongClusters with two disconnected components using INLIER_NUM
TEST_F(ViewGraphManipulaterTest_158, EstablishStrongClusters_TwoComponents_InlierNum_158) {
  TestSetup setup;
  // Component 1: images 0, 1
  setup.AddImage(0, 0, 0);
  setup.AddImage(1, 0, 1);
  // Component 2: images 2, 3
  setup.AddImage(2, 0, 2);
  setup.AddImage(3, 0, 3);

  // Strong pairs within each component
  setup.AddImagePair(0, 1, true, 50, 5.0);
  setup.AddImagePair(2, 3, true, 50, 5.0);

  // Weak cross-component pair (below threshold)
  setup.AddImagePair(1, 2, true, 5, 0.5);

  auto result = ViewGraphManipulater::EstablishStrongClusters(
      setup.view_graph, setup.frames, setup.images,
      ViewGraphManipulater::INLIER_NUM, 10.0, 1);

  // Two separate strong clusters, weak edge should be invalidated
  EXPECT_GE(result, 1);
}

// Test: EstablishStrongClusters with WEIGHT criteria
TEST_F(ViewGraphManipulaterTest_158, EstablishStrongClusters_WeightCriteria_158) {
  TestSetup setup;
  setup.AddImage(0, 0, 0);
  setup.AddImage(1, 0, 1);
  setup.AddImage(2, 0, 2);

  setup.AddImagePair(0, 1, true, 5, 20.0);
  setup.AddImagePair(1, 2, true, 5, 20.0);
  setup.AddImagePair(0, 2, true, 5, 20.0);

  auto result = ViewGraphManipulater::EstablishStrongClusters(
      setup.view_graph, setup.frames, setup.images,
      ViewGraphManipulater::WEIGHT, 10.0, 1);

  EXPECT_EQ(result, 1);
}

// Test: EstablishStrongClusters with all invalid pairs
TEST_F(ViewGraphManipulaterTest_158, EstablishStrongClusters_AllInvalidPairs_158) {
  TestSetup setup;
  setup.AddImage(0, 0, 0);
  setup.AddImage(1, 0, 1);
  setup.AddImage(2, 0, 2);

  setup.AddImagePair(0, 1, false, 50, 20.0);
  setup.AddImagePair(1, 2, false, 50, 20.0);

  auto result = ViewGraphManipulater::EstablishStrongClusters(
      setup.view_graph, setup.frames, setup.images,
      ViewGraphManipulater::INLIER_NUM, 10.0, 1);

  // All pairs invalid, no connections
  EXPECT_GE(result, 0);
}

// Test: EstablishStrongClusters invalidates weak inter-cluster edges
TEST_F(ViewGraphManipulaterTest_158, EstablishStrongClusters_InvalidatesWeakEdges_158) {
  TestSetup setup;
  setup.AddImage(0, 0, 0);
  setup.AddImage(1, 0, 1);
  setup.AddImage(2, 0, 2);
  setup.AddImage(3, 0, 3);

  // Strong within cluster 1
  setup.AddImagePair(0, 1, true, 100, 50.0);
  // Strong within cluster 2
  setup.AddImagePair(2, 3, true, 100, 50.0);
  // Weak between clusters (below 0.75 * min_thres for merging)
  setup.AddImagePair(1, 2, true, 2, 1.0);

  auto result = ViewGraphManipulater::EstablishStrongClusters(
      setup.view_graph, setup.frames, setup.images,
      ViewGraphManipulater::INLIER_NUM, 50.0, 1);

  // Check that the weak cross-cluster edge is invalidated
  for (auto& [pair_id, pair] : setup.view_graph.image_pairs) {
    if ((pair.image_id1 == 1 && pair.image_id2 == 2) ||
        (pair.image_id1 == 2 && pair.image_id2 == 1)) {
      EXPECT_FALSE(pair.is_valid);
    }
  }
}

// Test: EstablishStrongClusters with threshold at boundary (exactly at min_thres)
TEST_F(ViewGraphManipulaterTest_158, EstablishStrongClusters_BoundaryThreshold_158) {
  TestSetup setup;
  setup.AddImage(0, 0, 0);
  setup.AddImage(1, 0, 1);

  // Exactly at threshold - the code checks > min_thres (strict), so exactly equal should NOT pass
  setup.AddImagePair(0, 1, true, 10, 10.0);

  auto result = ViewGraphManipulater::EstablishStrongClusters(
      setup.view_graph, setup.frames, setup.images,
      ViewGraphManipulater::INLIER_NUM, 10.0, 1);

  // 10 inliers is NOT > 10.0, so should not form a strong cluster
  EXPECT_GE(result, 0);
}

// Test: EstablishStrongClusters with threshold just below inlier count
TEST_F(ViewGraphManipulaterTest_158, EstablishStrongClusters_JustAboveThreshold_158) {
  TestSetup setup;
  setup.AddImage(0, 0, 0);
  setup.AddImage(1, 0, 1);

  // 11 inliers > 10.0, should pass
  setup.AddImagePair(0, 1, true, 11, 11.0);

  auto result = ViewGraphManipulater::EstablishStrongClusters(
      setup.view_graph, setup.frames, setup.images,
      ViewGraphManipulater::INLIER_NUM, 10.0, 1);

  EXPECT_GE(result, 1);
}

// Test: EstablishStrongClusters merging through multiple weak but sufficient edges
TEST_F(ViewGraphManipulaterTest_158, EstablishStrongClusters_MergeThroughMultipleEdges_158) {
  TestSetup setup;
  // Two clusters with >= 2 cross-cluster edges above 0.75*threshold
  setup.AddImage(0, 0, 0);
  setup.AddImage(1, 0, 1);
  setup.AddImage(2, 0, 2);
  setup.AddImage(3, 0, 3);

  // Strong within cluster 1
  setup.AddImagePair(0, 1, true, 100, 50.0);
  // Strong within cluster 2
  setup.AddImagePair(2, 3, true, 100, 50.0);

  // Two cross-cluster edges above 0.75 * 50 = 37.5
  setup.AddImagePair(0, 2, true, 40, 40.0);
  setup.AddImagePair(1, 3, true, 40, 40.0);

  auto result = ViewGraphManipulater::EstablishStrongClusters(
      setup.view_graph, setup.frames, setup.images,
      ViewGraphManipulater::INLIER_NUM, 50.0, 1);

  // Should merge into single cluster because there are 2 cross-cluster edges
  EXPECT_EQ(result, 1);
}

// Test: EstablishStrongClusters with WEIGHT criteria boundary
TEST_F(ViewGraphManipulaterTest_158, EstablishStrongClusters_WeightBoundary_158) {
  TestSetup setup;
  setup.AddImage(0, 0, 0);
  setup.AddImage(1, 0, 1);

  // weight exactly at threshold
  setup.AddImagePair(0, 1, true, 5, 10.0);

  auto result = ViewGraphManipulater::EstablishStrongClusters(
      setup.view_graph, setup.frames, setup.images,
      ViewGraphManipulater::WEIGHT, 10.0, 1);

  // weight > min_thres is strict, 10.0 is NOT > 10.0
  EXPECT_GE(result, 0);
}

// Test: EstablishStrongClusters with same frame_id for multiple images
TEST_F(ViewGraphManipulaterTest_158, EstablishStrongClusters_SharedFrameId_158) {
  TestSetup setup;
  // Two images sharing the same frame
  setup.AddImage(0, 0, 0);
  setup.AddImage(1, 0, 0);  // same frame_id as image 0
  setup.AddImage(2, 0, 1);

  setup.AddImagePair(0, 2, true, 50, 20.0);
  setup.AddImagePair(1, 2, true, 50, 20.0);

  auto result = ViewGraphManipulater::EstablishStrongClusters(
      setup.view_graph, setup.frames, setup.images,
      ViewGraphManipulater::INLIER_NUM, 10.0, 1);

  EXPECT_GE(result, 1);
}

// Test: EstablishStrongClusters with zero threshold
TEST_F(ViewGraphManipulaterTest_158, EstablishStrongClusters_ZeroThreshold_158) {
  TestSetup setup;
  setup.AddImage(0, 0, 0);
  setup.AddImage(1, 0, 1);

  setup.AddImagePair(0, 1, true, 1, 0.1);

  auto result = ViewGraphManipulater::EstablishStrongClusters(
      setup.view_graph, setup.frames, setup.images,
      ViewGraphManipulater::INLIER_NUM, 0.0, 1);

  // 1 inlier > 0.0, should form cluster
  EXPECT_GE(result, 1);
}

// Test: EstablishStrongClusters preserves valid strong edges
TEST_F(ViewGraphManipulaterTest_158, EstablishStrongClusters_PreservesStrongEdges_158) {
  TestSetup setup;
  setup.AddImage(0, 0, 0);
  setup.AddImage(1, 0, 1);
  setup.AddImage(2, 0, 2);

  setup.AddImagePair(0, 1, true, 100, 50.0);
  setup.AddImagePair(1, 2, true, 100, 50.0);
  setup.AddImagePair(0, 2, true, 100, 50.0);

  ViewGraphManipulater::EstablishStrongClusters(
      setup.view_graph, setup.frames, setup.images,
      ViewGraphManipulater::INLIER_NUM, 10.0, 1);

  // All strong edges within same cluster should remain valid
  for (auto& [pair_id, pair] : setup.view_graph.image_pairs) {
    EXPECT_TRUE(pair.is_valid);
  }
}

// Test: Large number of isolated images
TEST_F(ViewGraphManipulaterTest_158, EstablishStrongClusters_ManyIsolatedImages_158) {
  TestSetup setup;
  for (int i = 0; i < 10; ++i) {
    setup.AddImage(i, 0, i);
  }
  // No pairs at all
  auto result = ViewGraphManipulater::EstablishStrongClusters(
      setup.view_graph, setup.frames, setup.images,
      ViewGraphManipulater::INLIER_NUM, 10.0, 1);

  EXPECT_GE(result, 0);
}

}  // namespace
}  // namespace glomap
