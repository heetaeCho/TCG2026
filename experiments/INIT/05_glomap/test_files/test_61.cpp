#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>

#include "glomap/math/tree.h"

namespace glomap {

class MaximumSpanningTreeTest_61 : public ::testing::Test {
 protected:
  using ImageId = image_t;

  ViewGraph view_graph_;
  std::unordered_map<ImageId, Image> images_;
  std::unordered_map<ImageId, ImageId> parents_;

  // Helper: add an image with given registration state
  void AddImage(ImageId id, bool registered) {
    Image img;
    if (registered) {
      // We only rely on the public interface suggested by the code:
      // Image::IsRegistered(), so we **assume** there is a corresponding
      // setter like SetRegistered(bool).
      img.SetRegistered(true);
    }
    images_.emplace(id, img);
  }

  // Helper: add a single image pair entry into view_graph_.image_pairs
  // without assuming anything about the key type.
  void AddImagePair(ImageId id1,
                    ImageId id2,
                    bool is_valid,
                    double weight,
                    std::size_t num_inliers) {
    using ImagePairsType = decltype(view_graph_.image_pairs);
    typename ImagePairsType::key_type key{};  // default-constructed key
    auto& image_pair = view_graph_.image_pairs[key];

    // Only use fields visible from the implementation snippet.
    image_pair.image_id1 = id1;
    image_pair.image_id2 = id2;
    image_pair.is_valid = is_valid;
    image_pair.weight = weight;
    image_pair.inliers.assign(num_inliers, 0);
  }
};

//------------------------------------------------------------------------------
// 1. Basic connected case with INLIER_RATIO: both registered images participate
//    in the resulting parent map.
//------------------------------------------------------------------------------
TEST_F(MaximumSpanningTreeTest_61,
       BuildsParentsForConnectedRegisteredImages_InlierRatio_61) {
  // Two registered images connected by a valid pair
  AddImage(1, true);
  AddImage(2, true);
  AddImagePair(1, 2, /*is_valid=*/true, /*weight=*/0.8, /*num_inliers=*/10);

  auto root =
      MaximumSpanningTree(view_graph_, images_, parents_, INLIER_RATIO);

  // Both registered images should appear in parents_
  EXPECT_EQ(parents_.size(), 2u);
  EXPECT_TRUE(parents_.count(1) > 0);
  EXPECT_TRUE(parents_.count(2) > 0);

  // The returned root must correspond to one of the registered images
  EXPECT_TRUE(images_.count(root) > 0);
  EXPECT_TRUE(parents_.count(root) > 0);

  // Every parent entry must also reference a registered image
  for (const auto& kv : parents_) {
    EXPECT_TRUE(images_.count(kv.second) > 0);
  }
}

//------------------------------------------------------------------------------
// 2. Same connected case but using INLIER_NUM: ensures the function works
//    correctly for the alternative weight type as well.
//------------------------------------------------------------------------------
TEST_F(MaximumSpanningTreeTest_61,
       BuildsParentsForConnectedRegisteredImages_InlierNum_61) {
  // Two registered images connected by a valid pair
  AddImage(10, true);
  AddImage(20, true);
  AddImagePair(10, 20, /*is_valid=*/true, /*weight=*/0.3, /*num_inliers=*/5);

  auto root =
      MaximumSpanningTree(view_graph_, images_, parents_, INLIER_NUM);

  // Both registered images should appear in parents_
  EXPECT_EQ(parents_.size(), 2u);
  EXPECT_TRUE(parents_.count(10) > 0);
  EXPECT_TRUE(parents_.count(20) > 0);

  // Root is one of the registered images
  EXPECT_TRUE(images_.count(root) > 0);
  EXPECT_TRUE(parents_.count(root) > 0);

  // Parents must reference registered images
  for (const auto& kv : parents_) {
    EXPECT_TRUE(images_.count(kv.second) > 0);
  }
}

//------------------------------------------------------------------------------
// 3. Unregistered images are ignored: only registered images are represented
//    in the MST and parent map, even if an edge connects to an unregistered one.
//------------------------------------------------------------------------------
TEST_F(MaximumSpanningTreeTest_61,
       IgnoresUnregisteredImagesInGraphConstruction_61) {
  // Image 1 is registered, image 2 is not
  AddImage(1, true);
  AddImage(2, false);

  // Edge between 1 and 2 is marked valid, but 2 is unregistered
  AddImagePair(1, 2, /*is_valid=*/true, /*weight=*/1.0, /*num_inliers=*/3);

  auto root =
      MaximumSpanningTree(view_graph_, images_, parents_, INLIER_RATIO);

  // Only the registered image should appear
  EXPECT_EQ(parents_.size(), 1u);
  ASSERT_TRUE(parents_.count(1) > 0);

  // The MST root must be that registered image
  EXPECT_EQ(root, 1);
  EXPECT_EQ(parents_.at(1), 1);  // root is its own parent in the BFS tree
}

//------------------------------------------------------------------------------
// 4. Existing contents of the parents map are cleared before writing new
//    results.
//------------------------------------------------------------------------------
TEST_F(MaximumSpanningTreeTest_61,
       ClearsExistingParentsBeforeAssigningNewTree_61) {
  // Start with some dummy contents in parents_
  parents_.emplace(999, 1000);

  // Single registered image, no edges
  AddImage(42, true);

  auto root =
      MaximumSpanningTree(view_graph_, images_, parents_, INLIER_RATIO);

  // Old entry must be gone
  EXPECT_EQ(parents_.count(999), 0u);

  // New parents map should contain exactly one entry for the single image
  ASSERT_EQ(parents_.size(), 1u);
  EXPECT_TRUE(parents_.count(42) > 0);
  EXPECT_EQ(root, 42);
  EXPECT_EQ(parents_.at(42), 42);  // root as its own parent
}

//------------------------------------------------------------------------------
// 5. No valid edges: invalid pairs are skipped, so even though there are
//    multiple registered images, only the component reachable from the root
//    (based on BFS starting index) will end up in the parents map.
//------------------------------------------------------------------------------
TEST_F(MaximumSpanningTreeTest_61,
       SkipsInvalidImagePairsWhenBuildingGraph_61) {
  // Two registered images
  AddImage(100, true);
  AddImage(200, true);

  // A single pair between them, but marked as invalid
  AddImagePair(100, 200, /*is_valid=*/false, /*weight=*/2.0, /*num_inliers=*/7);

  auto root =
      MaximumSpanningTree(view_graph_, images_, parents_, INLIER_RATIO);

  // Because the only edge is invalid, the MST graph is effectively edgeless.
  // BFS will only visit the starting vertex, so only one image appears in
  // parents_. We don't assume which one; we just check consistency.
  EXPECT_EQ(parents_.size(), 1u);

  // The root must be one of the registered images
  EXPECT_TRUE(images_.count(root) > 0);
  EXPECT_TRUE(parents_.count(root) > 0);

  // Parent of that root is itself in the BFS tree
  EXPECT_EQ(parents_.at(root), root);
}

}  // namespace glomap
