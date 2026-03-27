// File: view_graph_manipulater_sparsify_graph_test_157.cc

#include <gtest/gtest.h>

#include <string>
#include <unordered_map>

#include "glomap/processors/view_graph_manipulation.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/view_graph.h"

namespace glomap {

class ViewGraphManipulaterTest_157 : public ::testing::Test {
 protected:
  ViewGraph view_graph_;
  std::unordered_map<frame_t, Frame> frames_;
  std::unordered_map<image_t, Image> images_;

  // Helper to insert an Image into the images_ map.
  // We only rely on the public constructor and fields.
  void AddImage(image_t id, bool mark_registered = false) {
    // camera_t is assumed to be an integer-like type.
    camera_t cam_id = static_cast<camera_t>(0);
    Image img(id, cam_id, "image_" + std::to_string(id));

    // The header shows frame_id has default -1, which often denotes "invalid".
    // We use a non-negative value as a reasonable way to mark it as "registered"
    // without assuming the exact implementation of IsRegistered().
    if (mark_registered) {
      img.frame_id = 0;
    }
    images_.emplace(id, img);
  }

  // Helper to insert an ImagePair into view_graph_.image_pairs.
  image_pair_t AddImagePair(image_t id1, image_t id2, bool valid = true) {
    ImagePair pair(id1, id2);
    pair.is_valid = valid;
    const image_pair_t key = pair.pair_id;
    view_graph_.image_pairs.emplace(key, pair);
    return key;
  }
};

// -----------------------------------------------------------------------------
// TEST 1: No valid image pairs -> return 0 and keep container empty
// -----------------------------------------------------------------------------
TEST_F(ViewGraphManipulaterTest_157, ReturnsZeroWhenNoImagePairs_157) {
  // Ensure there is at least one image so that KeepLargestConnectedComponents
  // has some content to work with and num_img is unlikely to be zero.
  AddImage(static_cast<image_t>(1), /*mark_registered=*/true);

  const int expected_degree = 1;

  const image_pair_t num_kept =
      ViewGraphManipulater::SparsifyGraph(view_graph_, frames_, images_,
                                          expected_degree);

  EXPECT_EQ(num_kept, 0);
  EXPECT_TRUE(view_graph_.image_pairs.empty());
}

// -----------------------------------------------------------------------------
// TEST 2: All image pairs are initially invalid -> still invalid, return 0
// -----------------------------------------------------------------------------
TEST_F(ViewGraphManipulaterTest_157,
       AllInvalidPairsRemainInvalidAndReturnZero_157) {
  // Add images referenced by the pairs.
  AddImage(static_cast<image_t>(1), /*mark_registered=*/true);
  AddImage(static_cast<image_t>(2), /*mark_registered=*/true);
  AddImage(static_cast<image_t>(3), /*mark_registered=*/true);

  // Insert two image pairs, both marked invalid.
  const image_pair_t pair_12 =
      AddImagePair(static_cast<image_t>(1), static_cast<image_t>(2),
                   /*valid=*/false);
  const image_pair_t pair_23 =
      AddImagePair(static_cast<image_t>(2), static_cast<image_t>(3),
                   /*valid=*/false);

  const int expected_degree = 2;

  const image_pair_t num_kept =
      ViewGraphManipulater::SparsifyGraph(view_graph_, frames_, images_,
                                          expected_degree);

  // No valid edges were eligible to be chosen.
  EXPECT_EQ(num_kept, 0);

  // Both pairs should remain invalid.
  auto it12 = view_graph_.image_pairs.find(pair_12);
  ASSERT_NE(it12, view_graph_.image_pairs.end());
  EXPECT_FALSE(it12->second.is_valid);

  auto it23 = view_graph_.image_pairs.find(pair_23);
  ASSERT_NE(it23, view_graph_.image_pairs.end());
  EXPECT_FALSE(it23->second.is_valid);
}

// -----------------------------------------------------------------------------
// TEST 3: A single valid pair between two (likely) registered images
//         with small degree should always be kept, and the function
//         should report exactly one kept edge.
// -----------------------------------------------------------------------------
TEST_F(ViewGraphManipulaterTest_157,
       KeepsPairsWithDegreeBelowOrEqualExpected_157) {
  // Create two images and mark them as "registered" via public fields.
  const image_t img1 = static_cast<image_t>(1);
  const image_t img2 = static_cast<image_t>(2);

  AddImage(img1, /*mark_registered=*/true);
  AddImage(img2, /*mark_registered=*/true);

  // Single valid pair between img1 and img2.
  const image_pair_t pair_id = AddImagePair(img1, img2, /*valid=*/true);

  // With just one edge between two images, their degrees in the adjacency
  // list are expected to be 1, so using expected_degree = 1 exercises the
  // deterministic branch (degree <= expected_degree).
  const int expected_degree = 1;

  const image_pair_t num_kept =
      ViewGraphManipulater::SparsifyGraph(view_graph_, frames_, images_,
                                          expected_degree);

  // We expect exactly one kept edge.
  EXPECT_EQ(num_kept, 1);

  // The only pair we inserted should remain valid after sparsification.
  auto it = view_graph_.image_pairs.find(pair_id);
  ASSERT_NE(it, view_graph_.image_pairs.end());
  EXPECT_TRUE(it->second.is_valid);
}

}  // namespace glomap
