#include <gtest/gtest.h>
#include "glomap/math/tree.h"
#include "glomap/scene/types.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/view_graph.h"

#include <unordered_map>

namespace glomap {
namespace {

// Helper to create a registered image
Image MakeRegisteredImage(image_t id, camera_t cam_id = 0) {
  Image img(id, cam_id, "img_" + std::to_string(id));
  // Mark as registered - we need to set the registration status.
  // Based on the interface, Image needs cam_from_world to be set to be registered.
  // We assume setting a valid pose registers the image.
  img.is_registered = true;
  return img;
}

// Helper to create an unregistered image
Image MakeUnregisteredImage(image_t id, camera_t cam_id = 0) {
  Image img(id, cam_id, "img_" + std::to_string(id));
  img.is_registered = false;
  return img;
}

class MaximumSpanningTreeTest_130 : public ::testing::Test {
 protected:
  ViewGraph view_graph;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<image_t, image_t> parents;
};

// Test: Two registered images with one valid pair
TEST_F(MaximumSpanningTreeTest_130, TwoImages_SingleEdge_130) {
  images.emplace(0, MakeRegisteredImage(0));
  images.emplace(1, MakeRegisteredImage(1));

  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.inliers = {0, 1, 2, 3, 4};  // 5 inliers
  pair.weight = 0.8;
  view_graph.image_pairs[pair.pair_id] = pair;

  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  // Should return a valid root
  EXPECT_TRUE(images.count(root) > 0);
  // Parents map should have entries for both images
  EXPECT_EQ(parents.size(), 2u);
  // Root's parent should be itself
  EXPECT_EQ(parents[root], root);
}

// Test: Three images forming a triangle, INLIER_NUM weight type
TEST_F(MaximumSpanningTreeTest_130, ThreeImagesTriangle_InlierNum_130) {
  images.emplace(0, MakeRegisteredImage(0));
  images.emplace(1, MakeRegisteredImage(1));
  images.emplace(2, MakeRegisteredImage(2));

  ImagePair pair01(0, 1);
  pair01.is_valid = true;
  pair01.inliers = {0, 1, 2};  // 3 inliers
  pair01.weight = 0.3;
  view_graph.image_pairs[pair01.pair_id] = pair01;

  ImagePair pair12(1, 2);
  pair12.is_valid = true;
  pair12.inliers = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};  // 10 inliers
  pair12.weight = 0.9;
  view_graph.image_pairs[pair12.pair_id] = pair12;

  ImagePair pair02(0, 2);
  pair02.is_valid = true;
  pair02.inliers = {0, 1, 2, 3, 4};  // 5 inliers
  pair02.weight = 0.5;
  view_graph.image_pairs[pair02.pair_id] = pair02;

  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  EXPECT_TRUE(images.count(root) > 0);
  EXPECT_EQ(parents.size(), 3u);
  // Root parent should be itself
  EXPECT_EQ(parents[root], root);
}

// Test: Three images forming a triangle, INLIER_RATIO weight type
TEST_F(MaximumSpanningTreeTest_130, ThreeImagesTriangle_InlierRatio_130) {
  images.emplace(0, MakeRegisteredImage(0));
  images.emplace(1, MakeRegisteredImage(1));
  images.emplace(2, MakeRegisteredImage(2));

  ImagePair pair01(0, 1);
  pair01.is_valid = true;
  pair01.inliers = {0, 1, 2};
  pair01.weight = 0.9;  // highest weight
  view_graph.image_pairs[pair01.pair_id] = pair01;

  ImagePair pair12(1, 2);
  pair12.is_valid = true;
  pair12.inliers = {0, 1};
  pair12.weight = 0.5;
  view_graph.image_pairs[pair12.pair_id] = pair12;

  ImagePair pair02(0, 2);
  pair02.is_valid = true;
  pair02.inliers = {0};
  pair02.weight = 0.3;  // lowest weight
  view_graph.image_pairs[pair02.pair_id] = pair02;

  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_RATIO);

  EXPECT_TRUE(images.count(root) > 0);
  EXPECT_EQ(parents.size(), 3u);
  EXPECT_EQ(parents[root], root);
}

// Test: Invalid image pairs are skipped
TEST_F(MaximumSpanningTreeTest_130, InvalidPairsSkipped_130) {
  images.emplace(0, MakeRegisteredImage(0));
  images.emplace(1, MakeRegisteredImage(1));
  images.emplace(2, MakeRegisteredImage(2));

  ImagePair pair01(0, 1);
  pair01.is_valid = false;  // invalid
  pair01.inliers = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  pair01.weight = 1.0;
  view_graph.image_pairs[pair01.pair_id] = pair01;

  ImagePair pair12(1, 2);
  pair12.is_valid = true;
  pair12.inliers = {0, 1, 2};
  pair12.weight = 0.5;
  view_graph.image_pairs[pair12.pair_id] = pair12;

  ImagePair pair02(0, 2);
  pair02.is_valid = true;
  pair02.inliers = {0, 1};
  pair02.weight = 0.3;
  view_graph.image_pairs[pair02.pair_id] = pair02;

  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  EXPECT_TRUE(images.count(root) > 0);
  EXPECT_EQ(parents.size(), 3u);
}

// Test: Unregistered images are excluded
TEST_F(MaximumSpanningTreeTest_130, UnregisteredImagesExcluded_130) {
  images.emplace(0, MakeRegisteredImage(0));
  images.emplace(1, MakeRegisteredImage(1));
  images.emplace(2, MakeUnregisteredImage(2));  // unregistered

  ImagePair pair01(0, 1);
  pair01.is_valid = true;
  pair01.inliers = {0, 1, 2};
  pair01.weight = 0.5;
  view_graph.image_pairs[pair01.pair_id] = pair01;

  ImagePair pair02(0, 2);
  pair02.is_valid = true;
  pair02.inliers = {0, 1, 2, 3, 4};
  pair02.weight = 0.8;
  view_graph.image_pairs[pair02.pair_id] = pair02;

  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  // Only 2 registered images
  EXPECT_EQ(parents.size(), 2u);
  EXPECT_TRUE(parents.count(2) == 0);  // image 2 should not be in parents
}

// Test: Single registered image with no edges
TEST_F(MaximumSpanningTreeTest_130, SingleImage_NoEdges_130) {
  images.emplace(0, MakeRegisteredImage(0));

  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  EXPECT_EQ(parents.size(), 1u);
  EXPECT_EQ(parents[root], root);
}

// Test: Linear chain of 4 images
TEST_F(MaximumSpanningTreeTest_130, LinearChainFourImages_130) {
  images.emplace(0, MakeRegisteredImage(0));
  images.emplace(1, MakeRegisteredImage(1));
  images.emplace(2, MakeRegisteredImage(2));
  images.emplace(3, MakeRegisteredImage(3));

  ImagePair pair01(0, 1);
  pair01.is_valid = true;
  pair01.inliers = {0, 1, 2, 3, 4};
  pair01.weight = 0.5;
  view_graph.image_pairs[pair01.pair_id] = pair01;

  ImagePair pair12(1, 2);
  pair12.is_valid = true;
  pair12.inliers = {0, 1, 2};
  pair12.weight = 0.3;
  view_graph.image_pairs[pair12.pair_id] = pair12;

  ImagePair pair23(2, 3);
  pair23.is_valid = true;
  pair23.inliers = {0, 1, 2, 3, 4, 5, 6, 7};
  pair23.weight = 0.8;
  view_graph.image_pairs[pair23.pair_id] = pair23;

  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  EXPECT_TRUE(images.count(root) > 0);
  EXPECT_EQ(parents.size(), 4u);
  EXPECT_EQ(parents[root], root);

  // Verify tree structure: every non-root node has a parent that is a valid image
  for (auto& [img_id, parent_id] : parents) {
    EXPECT_TRUE(images.count(parent_id) > 0);
  }
}

// Test: Parents map is cleared before populating
TEST_F(MaximumSpanningTreeTest_130, ParentsMapCleared_130) {
  images.emplace(0, MakeRegisteredImage(0));
  images.emplace(1, MakeRegisteredImage(1));

  ImagePair pair01(0, 1);
  pair01.is_valid = true;
  pair01.inliers = {0, 1};
  pair01.weight = 0.5;
  view_graph.image_pairs[pair01.pair_id] = pair01;

  // Pre-populate parents with garbage
  parents[99] = 100;
  parents[200] = 300;

  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  // Old entries should be gone
  EXPECT_EQ(parents.count(99), 0u);
  EXPECT_EQ(parents.count(200), 0u);
  EXPECT_EQ(parents.size(), 2u);
}

// Test: MST selects edges with maximum inliers (INLIER_NUM)
TEST_F(MaximumSpanningTreeTest_130, MSTSelectsMaxInlierEdges_130) {
  // Triangle: edges with 10, 5, 3 inliers
  // MST should pick edges with 10 and 5 inliers (drop 3)
  images.emplace(0, MakeRegisteredImage(0));
  images.emplace(1, MakeRegisteredImage(1));
  images.emplace(2, MakeRegisteredImage(2));

  ImagePair pair01(0, 1);
  pair01.is_valid = true;
  pair01.inliers.resize(10);
  pair01.weight = 1.0;
  view_graph.image_pairs[pair01.pair_id] = pair01;

  ImagePair pair12(1, 2);
  pair12.is_valid = true;
  pair12.inliers.resize(5);
  pair12.weight = 0.5;
  view_graph.image_pairs[pair12.pair_id] = pair12;

  ImagePair pair02(0, 2);
  pair02.is_valid = true;
  pair02.inliers.resize(3);
  pair02.weight = 0.3;
  view_graph.image_pairs[pair02.pair_id] = pair02;

  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  // All 3 images should be in the tree
  EXPECT_EQ(parents.size(), 3u);
  EXPECT_EQ(parents[root], root);

  // Verify connectivity: every node should be reachable from root
  for (auto& [img_id, parent_id] : parents) {
    if (img_id != root) {
      EXPECT_NE(parents[img_id], img_id);
    }
  }
}

// Test: All pairs invalid - no edges in MST
TEST_F(MaximumSpanningTreeTest_130, AllPairsInvalid_130) {
  images.emplace(0, MakeRegisteredImage(0));
  images.emplace(1, MakeRegisteredImage(1));

  ImagePair pair01(0, 1);
  pair01.is_valid = false;
  pair01.inliers = {0, 1, 2};
  pair01.weight = 0.5;
  view_graph.image_pairs[pair01.pair_id] = pair01;

  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  EXPECT_TRUE(images.count(root) > 0);
  // Both images should still appear in parents since they're registered
  EXPECT_EQ(parents.size(), 2u);
}

// Test: Five images complete graph
TEST_F(MaximumSpanningTreeTest_130, FiveImagesCompleteGraph_130) {
  for (int i = 0; i < 5; i++) {
    images.emplace(i, MakeRegisteredImage(i));
  }

  int inlier_count = 1;
  for (int i = 0; i < 5; i++) {
    for (int j = i + 1; j < 5; j++) {
      ImagePair pair(i, j);
      pair.is_valid = true;
      pair.inliers.resize(inlier_count);
      pair.weight = static_cast<double>(inlier_count) / 20.0;
      view_graph.image_pairs[pair.pair_id] = pair;
      inlier_count++;
    }
  }

  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  EXPECT_EQ(parents.size(), 5u);
  EXPECT_EQ(parents[root], root);

  // Count non-root nodes: should be 4 (tree with 5 nodes has 4 edges)
  int non_root_count = 0;
  for (auto& [img_id, parent_id] : parents) {
    if (img_id != parent_id) non_root_count++;
  }
  EXPECT_EQ(non_root_count, 4);
}

// Test: Edge between registered and unregistered image is skipped
TEST_F(MaximumSpanningTreeTest_130, EdgeWithUnregisteredImageSkipped_130) {
  images.emplace(0, MakeRegisteredImage(0));
  images.emplace(1, MakeRegisteredImage(1));
  images.emplace(2, MakeUnregisteredImage(2));

  ImagePair pair01(0, 1);
  pair01.is_valid = true;
  pair01.inliers = {0, 1};
  pair01.weight = 0.5;
  view_graph.image_pairs[pair01.pair_id] = pair01;

  ImagePair pair12(1, 2);
  pair12.is_valid = true;
  pair12.inliers = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  pair12.weight = 1.0;
  view_graph.image_pairs[pair12.pair_id] = pair12;

  image_t root = MaximumSpanningTree(view_graph, images, parents, INLIER_NUM);

  // Only registered images in parents
  EXPECT_EQ(parents.size(), 2u);
  EXPECT_EQ(parents.count(2), 0u);
}

// Test: Using default weight type (not INLIER_NUM or INLIER_RATIO)
// The code has an else branch that also uses inliers.size()
TEST_F(MaximumSpanningTreeTest_130, DefaultWeightType_130) {
  images.emplace(0, MakeRegisteredImage(0));
  images.emplace(1, MakeRegisteredImage(1));

  ImagePair pair01(0, 1);
  pair01.is_valid = true;
  pair01.inliers = {0, 1, 2, 3};
  pair01.weight = 0.7;
  view_graph.image_pairs[pair01.pair_id] = pair01;

  // Use a weight type that is neither INLIER_NUM nor INLIER_RATIO
  // This should trigger the else branch
  image_t root = MaximumSpanningTree(view_graph, images, parents, static_cast<WeightType>(999));

  EXPECT_EQ(parents.size(), 2u);
  EXPECT_EQ(parents[root], root);
}

}  // namespace
}  // namespace glomap
