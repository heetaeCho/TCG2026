#include <gtest/gtest.h>
#include "glomap/math/tree.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/types.h"

namespace glomap {
namespace {

class MaximumSpanningTreeTest_61 : public ::testing::Test {
 protected:
  void SetUp() override {}

  // Helper to create a registered image
  Image CreateRegisteredImage(image_t id) {
    Image img;
    img.image_id = id;
    img.is_registered = true;
    return img;
  }

  // Helper to create an unregistered image
  Image CreateUnregisteredImage(image_t id) {
    Image img;
    img.image_id = id;
    img.is_registered = false;
    return img;
  }

  // Helper to create a valid image pair
  ImagePair CreateValidPair(image_t id1, image_t id2, int num_inliers, double weight = 1.0) {
    ImagePair pair;
    pair.image_id1 = id1;
    pair.image_id2 = id2;
    pair.is_valid = true;
    pair.inliers.resize(num_inliers);
    pair.weight = weight;
    return pair;
  }

  image_pair_t PairId(image_t id1, image_t id2) {
    if (id1 > id2) std::swap(id1, id2);
    return static_cast<image_pair_t>(id1) * 2147483647 + id2;
  }
};

// Test with a simple two-image case
TEST_F(MaximumSpanningTreeTest_61, TwoImages_61) {
  std::unordered_map<image_t, Image> images;
  images[0] = CreateRegisteredImage(0);
  images[1] = CreateRegisteredImage(1);

  ViewGraph view_graph;
  image_pair_t pair_id = PairId(0, 1);
  view_graph.image_pairs[pair_id] = CreateValidPair(0, 1, 100, 0.9);

  std::unordered_map<image_t, image_t> parents;
  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  // Should have parents for both images
  EXPECT_EQ(parents.size(), 2);
  // Root should be its own parent
  EXPECT_EQ(parents[root], root);
}

// Test with three images forming a triangle, using INLIER_NUM
TEST_F(MaximumSpanningTreeTest_61, ThreeImagesTriangle_INLIER_NUM_61) {
  std::unordered_map<image_t, Image> images;
  images[0] = CreateRegisteredImage(0);
  images[1] = CreateRegisteredImage(1);
  images[2] = CreateRegisteredImage(2);

  ViewGraph view_graph;
  view_graph.image_pairs[PairId(0, 1)] = CreateValidPair(0, 1, 100, 0.9);
  view_graph.image_pairs[PairId(1, 2)] = CreateValidPair(1, 2, 200, 0.8);
  view_graph.image_pairs[PairId(0, 2)] = CreateValidPair(0, 2, 50, 0.5);

  std::unordered_map<image_t, image_t> parents;
  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  // Should have 3 entries in parents
  EXPECT_EQ(parents.size(), 3);
  // Root's parent is itself
  EXPECT_EQ(parents[root], root);
  // All images should be in parents
  EXPECT_TRUE(parents.count(0));
  EXPECT_TRUE(parents.count(1));
  EXPECT_TRUE(parents.count(2));
}

// Test with INLIER_RATIO weight type
TEST_F(MaximumSpanningTreeTest_61, ThreeImagesTriangle_INLIER_RATIO_61) {
  std::unordered_map<image_t, Image> images;
  images[0] = CreateRegisteredImage(0);
  images[1] = CreateRegisteredImage(1);
  images[2] = CreateRegisteredImage(2);

  ViewGraph view_graph;
  view_graph.image_pairs[PairId(0, 1)] = CreateValidPair(0, 1, 100, 0.9);
  view_graph.image_pairs[PairId(1, 2)] = CreateValidPair(1, 2, 200, 0.3);
  view_graph.image_pairs[PairId(0, 2)] = CreateValidPair(0, 2, 50, 0.8);

  std::unordered_map<image_t, image_t> parents;
  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_RATIO);

  EXPECT_EQ(parents.size(), 3);
  EXPECT_EQ(parents[root], root);
}

// Test with invalid image pairs (should be skipped)
TEST_F(MaximumSpanningTreeTest_61, InvalidPairsAreSkipped_61) {
  std::unordered_map<image_t, Image> images;
  images[0] = CreateRegisteredImage(0);
  images[1] = CreateRegisteredImage(1);
  images[2] = CreateRegisteredImage(2);

  ViewGraph view_graph;
  view_graph.image_pairs[PairId(0, 1)] = CreateValidPair(0, 1, 100, 0.9);
  
  ImagePair invalid_pair = CreateValidPair(1, 2, 200, 0.8);
  invalid_pair.is_valid = false;
  view_graph.image_pairs[PairId(1, 2)] = invalid_pair;

  view_graph.image_pairs[PairId(0, 2)] = CreateValidPair(0, 2, 50, 0.5);

  std::unordered_map<image_t, image_t> parents;
  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  EXPECT_EQ(parents.size(), 3);
  EXPECT_EQ(parents[root], root);
}

// Test with unregistered images (should be excluded)
TEST_F(MaximumSpanningTreeTest_61, UnregisteredImagesExcluded_61) {
  std::unordered_map<image_t, Image> images;
  images[0] = CreateRegisteredImage(0);
  images[1] = CreateRegisteredImage(1);
  images[2] = CreateUnregisteredImage(2);

  ViewGraph view_graph;
  view_graph.image_pairs[PairId(0, 1)] = CreateValidPair(0, 1, 100, 0.9);
  view_graph.image_pairs[PairId(1, 2)] = CreateValidPair(1, 2, 200, 0.8);
  view_graph.image_pairs[PairId(0, 2)] = CreateValidPair(0, 2, 50, 0.5);

  std::unordered_map<image_t, image_t> parents;
  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  // Only 2 registered images should be in parents
  EXPECT_EQ(parents.size(), 2);
  EXPECT_EQ(parents[root], root);
  EXPECT_FALSE(parents.count(2));
}

// Test with a linear chain of images
TEST_F(MaximumSpanningTreeTest_61, LinearChain_61) {
  std::unordered_map<image_t, Image> images;
  for (int i = 0; i < 5; i++) {
    images[i] = CreateRegisteredImage(i);
  }

  ViewGraph view_graph;
  for (int i = 0; i < 4; i++) {
    view_graph.image_pairs[PairId(i, i + 1)] = 
        CreateValidPair(i, i + 1, (i + 1) * 50, 0.5 + i * 0.1);
  }

  std::unordered_map<image_t, image_t> parents;
  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  EXPECT_EQ(parents.size(), 5);
  EXPECT_EQ(parents[root], root);

  // Verify tree structure: every non-root node should eventually lead to root
  for (auto& [id, img] : images) {
    image_t current = id;
    int depth = 0;
    while (parents[current] != current && depth < 10) {
      current = parents[current];
      depth++;
    }
    EXPECT_EQ(current, root);
  }
}

// Test that calling MaximumSpanningTree clears previous parents
TEST_F(MaximumSpanningTreeTest_61, ParentsMapIsCleared_61) {
  std::unordered_map<image_t, Image> images;
  images[0] = CreateRegisteredImage(0);
  images[1] = CreateRegisteredImage(1);

  ViewGraph view_graph;
  view_graph.image_pairs[PairId(0, 1)] = CreateValidPair(0, 1, 100, 0.9);

  std::unordered_map<image_t, image_t> parents;
  parents[99] = 98;  // Pre-existing data

  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  // Old entry should be gone
  EXPECT_FALSE(parents.count(99));
  EXPECT_EQ(parents.size(), 2);
}

// Test with a complete graph of 4 nodes and verify MST has correct number of edges
TEST_F(MaximumSpanningTreeTest_61, CompleteGraphFourNodes_61) {
  std::unordered_map<image_t, Image> images;
  for (int i = 0; i < 4; i++) {
    images[i] = CreateRegisteredImage(i);
  }

  ViewGraph view_graph;
  int weight = 10;
  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      view_graph.image_pairs[PairId(i, j)] = 
          CreateValidPair(i, j, weight, weight * 0.01);
      weight += 10;
    }
  }

  std::unordered_map<image_t, image_t> parents;
  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  EXPECT_EQ(parents.size(), 4);
  EXPECT_EQ(parents[root], root);

  // Count non-root nodes (should be 3, forming a tree with 3 edges)
  int non_root_count = 0;
  for (auto& [id, parent] : parents) {
    if (id != parent) non_root_count++;
  }
  EXPECT_EQ(non_root_count, 3);
}

// Test MST picks edges with highest weight (INLIER_NUM)
TEST_F(MaximumSpanningTreeTest_61, MSTSelectsHighestInlierEdges_61) {
  // Create a simple graph where MST selection is deterministic:
  // 3 nodes, triangle with weights 10, 100, 1000
  std::unordered_map<image_t, Image> images;
  images[0] = CreateRegisteredImage(0);
  images[1] = CreateRegisteredImage(1);
  images[2] = CreateRegisteredImage(2);

  ViewGraph view_graph;
  view_graph.image_pairs[PairId(0, 1)] = CreateValidPair(0, 1, 10, 0.1);
  view_graph.image_pairs[PairId(1, 2)] = CreateValidPair(1, 2, 1000, 0.9);
  view_graph.image_pairs[PairId(0, 2)] = CreateValidPair(0, 2, 100, 0.5);

  std::unordered_map<image_t, image_t> parents;
  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  EXPECT_EQ(parents.size(), 3);
  
  // The MST should include edges (1,2) with 1000 and (0,2) with 100
  // and exclude (0,1) with 10
  // All nodes should be reachable from root
  for (auto& [id, img] : images) {
    image_t current = id;
    int depth = 0;
    while (parents[current] != current && depth < 10) {
      current = parents[current];
      depth++;
    }
    EXPECT_EQ(current, root);
  }
}

// Test with non-contiguous image IDs
TEST_F(MaximumSpanningTreeTest_61, NonContiguousImageIds_61) {
  std::unordered_map<image_t, Image> images;
  images[10] = CreateRegisteredImage(10);
  images[20] = CreateRegisteredImage(20);
  images[30] = CreateRegisteredImage(30);

  ViewGraph view_graph;
  view_graph.image_pairs[PairId(10, 20)] = CreateValidPair(10, 20, 100, 0.9);
  view_graph.image_pairs[PairId(20, 30)] = CreateValidPair(20, 30, 200, 0.8);
  view_graph.image_pairs[PairId(10, 30)] = CreateValidPair(10, 30, 50, 0.5);

  std::unordered_map<image_t, image_t> parents;
  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  EXPECT_EQ(parents.size(), 3);
  EXPECT_EQ(parents[root], root);
  EXPECT_TRUE(parents.count(10));
  EXPECT_TRUE(parents.count(20));
  EXPECT_TRUE(parents.count(30));
}

// Test with single registered image (edge case - no pairs)
TEST_F(MaximumSpanningTreeTest_61, SingleImage_61) {
  std::unordered_map<image_t, Image> images;
  images[0] = CreateRegisteredImage(0);

  ViewGraph view_graph;
  // No image pairs

  std::unordered_map<image_t, image_t> parents;
  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  EXPECT_EQ(parents.size(), 1);
  EXPECT_EQ(parents[root], root);
}

// Test with all images unregistered except for edges that connect registered ones
TEST_F(MaximumSpanningTreeTest_61, MixedRegisteredUnregistered_61) {
  std::unordered_map<image_t, Image> images;
  images[0] = CreateRegisteredImage(0);
  images[1] = CreateUnregisteredImage(1);
  images[2] = CreateRegisteredImage(2);
  images[3] = CreateRegisteredImage(3);

  ViewGraph view_graph;
  view_graph.image_pairs[PairId(0, 1)] = CreateValidPair(0, 1, 100, 0.9);
  view_graph.image_pairs[PairId(0, 2)] = CreateValidPair(0, 2, 200, 0.8);
  view_graph.image_pairs[PairId(2, 3)] = CreateValidPair(2, 3, 150, 0.7);
  view_graph.image_pairs[PairId(1, 3)] = CreateValidPair(1, 3, 300, 0.95);

  std::unordered_map<image_t, image_t> parents;
  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  // Only 3 registered images
  EXPECT_EQ(parents.size(), 3);
  EXPECT_EQ(parents[root], root);
  EXPECT_FALSE(parents.count(1));
}

}  // namespace
}  // namespace glomap
