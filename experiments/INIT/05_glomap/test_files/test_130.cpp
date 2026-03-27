// File: maximum_spanning_tree_test_130.cc

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <gtest/gtest.h>

#include "glomap/scene/view_graph.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/math/tree.h"   // Declares glomap::MaximumSpanningTree and WeightType

// NOTE: These tests treat MaximumSpanningTree as a black box.
// We only assert on observable behavior via its return value and
// the `parents` output parameter.

class MaximumSpanningTreeTest_130 : public ::testing::Test {
protected:
  glomap::ViewGraph view_graph_;
  std::unordered_map<image_t, glomap::Image> images_;
  std::unordered_map<image_t, image_t> parents_;

  // Helper to create a basic Image with the given ID.
  // We assume the public constructor / fields are sufficient to
  // create an image usable by MaximumSpanningTree.
  glomap::Image CreateImage(image_t id) {
    // Use one of the public constructors if available; otherwise
    // default-construct and assign fields as needed.
    glomap::Image image(id, /*camera_id*/ 1, /*file_name*/ "img");
    return image;
  }

  // Helper to add an image into the map (intended to be "registered").
  void AddImage(image_t id) {
    glomap::Image image = CreateImage(id);
    images_.emplace(id, image);
  }

  // Helper to add an image pair into the view graph.
  void AddImagePair(image_t id1,
                    image_t id2,
                    bool is_valid,
                    double weight,
                    const std::vector<int>& inliers) {
    glomap::ImagePair image_pair(id1, id2);
    image_pair.is_valid = is_valid;
    image_pair.weight = weight;
    image_pair.inliers = inliers;

    // The key of the map is irrelevant for MaximumSpanningTree (it only
    // uses the values), so we can use any unique key.
    view_graph_.image_pairs.emplace(image_pair.pair_id, image_pair);
  }
};

// -----------------------------------------------------------------------------
// 1) Single registered image, no pairs
//    - Expect the function to return that image as the root.
//    - Expect parents map to contain exactly that image, pointing to itself.
// -----------------------------------------------------------------------------
TEST_F(MaximumSpanningTreeTest_130,
       SingleRegisteredImage_NoPairs_ReturnsSameRoot_130) {
  const image_t kImageId = 1;
  AddImage(kImageId);

  parents_.clear();

  image_t root =
      glomap::MaximumSpanningTree(view_graph_, images_, parents_,
                                  INLIER_RATIO);  // weight type arbitrary

  EXPECT_EQ(root, kImageId);
  ASSERT_EQ(parents_.size(), 1u);
  EXPECT_EQ(parents_.at(kImageId), kImageId);
}

// -----------------------------------------------------------------------------
// 2) Multiple images with a simple chain of valid pairs (INLIER_NUM)
//    - Expect the root to be one of the input images.
//    - Expect all images to appear in the parents map.
//    - Expect each parent and child to refer to a valid image ID.
// -----------------------------------------------------------------------------
TEST_F(MaximumSpanningTreeTest_130,
       MultipleImages_ChainPairs_InlierNum_AllParentsValid_130) {
  const image_t kId1 = 1;
  const image_t kId2 = 2;
  const image_t kId3 = 3;

  AddImage(kId1);
  AddImage(kId2);
  AddImage(kId3);

  // Chain: 1 -- 2 -- 3
  AddImagePair(kId1, kId2, /*is_valid=*/true, /*weight=*/0.5,
               /*inliers=*/{0, 1});
  AddImagePair(kId2, kId3, /*is_valid=*/true, /*weight=*/0.7,
               /*inliers=*/{0, 1, 2});

  parents_.clear();

  image_t root =
      glomap::MaximumSpanningTree(view_graph_, images_, parents_, INLIER_NUM);

  // Root should correspond to one of the known images.
  EXPECT_TRUE(images_.find(root) != images_.end());

  // All registered images should appear in the parents map.
  ASSERT_EQ(parents_.size(), images_.size());
  for (const auto& [child_id, parent_id] : parents_) {
    // Child must be a valid image.
    EXPECT_TRUE(images_.find(child_id) != images_.end());
    // Parent must also be a valid image.
    EXPECT_TRUE(images_.find(parent_id) != images_.end());
  }
}

// -----------------------------------------------------------------------------
// 3) Multiple images with pairs (INLIER_RATIO)
//    - Similar to the previous test but exercises the INLIER_RATIO branch.
//    - We only verify observable properties (root is a valid image, parents
//      contain valid image IDs, and all images are present).
// -----------------------------------------------------------------------------
TEST_F(MaximumSpanningTreeTest_130,
       MultipleImages_ChainPairs_InlierRatio_AllParentsValid_130) {
  const image_t kId1 = 10;
  const image_t kId2 = 20;
  const image_t kId3 = 30;

  AddImage(kId1);
  AddImage(kId2);
  AddImage(kId3);

  // Use different weights to exercise logic that reads `image_pair.weight`.
  AddImagePair(kId1, kId2, /*is_valid=*/true, /*weight=*/0.1,
               /*inliers=*/{0});
  AddImagePair(kId2, kId3, /*is_valid=*/true, /*weight=*/0.9,
               /*inliers=*/{0, 1});

  parents_.clear();

  image_t root =
      glomap::MaximumSpanningTree(view_graph_, images_, parents_,
                                  INLIER_RATIO);

  EXPECT_TRUE(images_.find(root) != images_.end());
  ASSERT_EQ(parents_.size(), images_.size());

  for (const auto& [child_id, parent_id] : parents_) {
    EXPECT_TRUE(images_.find(child_id) != images_.end());
    EXPECT_TRUE(images_.find(parent_id) != images_.end());
  }
}

// -----------------------------------------------------------------------------
// 4) Invalid pairs are ignored
//    - The ViewGraph contains only invalid pairs.
//    - We still expect the function to produce a parents map for all images,
//      but the invalid edges must not cause failures.
// -----------------------------------------------------------------------------
TEST_F(MaximumSpanningTreeTest_130,
       InvalidPairs_AreIgnored_ParentsStillComputed_130) {
  const image_t kId1 = 100;
  const image_t kId2 = 200;

  AddImage(kId1);
  AddImage(kId2);

  // Add an invalid pair (should be skipped by MaximumSpanningTree).
  AddImagePair(kId1, kId2, /*is_valid=*/false, /*weight=*/1.0,
               /*inliers=*/{0, 1, 2});

  parents_.clear();

  image_t root =
      glomap::MaximumSpanningTree(view_graph_, images_, parents_,
                                  INLIER_NUM);

  EXPECT_TRUE(images_.find(root) != images_.end());
  // Even without valid edges, the function should define parents
  // for all registered images (according to the function contract).
  ASSERT_EQ(parents_.size(), images_.size());

  for (const auto& [child_id, parent_id] : parents_) {
    EXPECT_TRUE(images_.find(child_id) != images_.end());
    EXPECT_TRUE(images_.find(parent_id) != images_.end());
  }
}

// -----------------------------------------------------------------------------
// 5) Parents map is cleared before output is written
//    - Pre-populate `parents` with dummy values.
//    - After calling MaximumSpanningTree, previous keys that don't belong
//      to the input images set should be gone.
// -----------------------------------------------------------------------------
TEST_F(MaximumSpanningTreeTest_130,
       ParentsOutputParameter_IsClearedBeforeUse_130) {
  const image_t kId1 = 5;

  AddImage(kId1);

  // Pre-populate with unrelated entry.
  parents_.clear();
  parents_[999] = 999;

  image_t root =
      glomap::MaximumSpanningTree(view_graph_, images_, parents_,
                                  INLIER_RATIO);

  EXPECT_TRUE(images_.find(root) != images_.end());

  // There should be exactly one entry corresponding to the single image.
  ASSERT_EQ(parents_.size(), 1u);
  EXPECT_EQ(parents_.count(kId1), 1u);
  EXPECT_EQ(parents_.at(kId1), kId1);
  // Old key should not remain.
  EXPECT_EQ(parents_.count(999), 0u);
}
