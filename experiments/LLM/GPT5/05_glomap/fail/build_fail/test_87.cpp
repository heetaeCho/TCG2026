// File: view_graph_manipulation_test_87.cc

#include <gtest/gtest.h>
#include <unordered_map>
#include <unordered_set>

// NOTE: Adjust this include path to match the real project structure.
#include "glomap/processors/view_graph_manipulation.h"

namespace glomap {

class ViewGraphManipulaterTest_87 : public ::testing::Test {
 protected:
  using ImagePairMap      = decltype(std::declval<ViewGraph>().image_pairs);
  using ImagePairType     = typename ImagePairMap::mapped_type;

  using FrameMap          = std::unordered_map<frame_t, Frame>;
  using ImageMap          = std::unordered_map<image_t, Image>;

  ViewGraphManipulater manipulater_;
  ViewGraph            view_graph_;
  FrameMap             frames_;
  ImageMap             images_;

  // Helper to add an image into the images_ map.
  // We only rely on the fact that Image is default constructible.
  void AddImage(image_t image_id) {
    images_.emplace(image_id, Image{});
  }

  // Helper to add an image pair into the view_graph_.image_pairs container.
  // We only use members that are visible in the given code:
  //   - image_id1
  //   - image_id2
  //   - is_valid
  void AddImagePair(image_pair_t pair_id,
                    image_t image_id1,
                    image_t image_id2,
                    bool is_valid = true) {
    ImagePairType image_pair{};
    image_pair.image_id1 = image_id1;
    image_pair.image_id2 = image_id2;
    image_pair.is_valid  = is_valid;
    view_graph_.image_pairs.emplace(pair_id, image_pair);
  }
};

// ---------------------------------------------------------------------------
// Normal operation: when expected_degree is sufficiently large, all valid
// edges whose incident images are registered should be kept.
// This uses the branch where (degree1 <= expected_degree || degree2 <= expected_degree)
// is true, so the random part is not involved.
// ---------------------------------------------------------------------------
TEST_F(ViewGraphManipulaterTest_87,
       HighExpectedDegreeKeepsAllValidEdges_87) {
  // Arrange: create a simple chain 1-2-3.
  image_t img1 = static_cast<image_t>(1);
  image_t img2 = static_cast<image_t>(2);
  image_t img3 = static_cast<image_t>(3);

  AddImage(img1);
  AddImage(img2);
  AddImage(img3);

  AddImagePair(static_cast<image_pair_t>(1), img1, img2, true);
  AddImagePair(static_cast<image_pair_t>(2), img2, img3, true);

  const int expected_degree = 10;  // Larger than any actual node degree.

  // Act
  image_pair_t kept_count =
      manipulater_.SparsifyGraph(view_graph_, frames_, images_, expected_degree);

  // Assert:
  // All valid edges should be chosen (and thus remain valid).
  EXPECT_EQ(kept_count, static_cast<image_pair_t>(2));

  for (const auto& kv : view_graph_.image_pairs) {
    const auto& pair = kv.second;
    EXPECT_TRUE(pair.is_valid);
  }
}

// ---------------------------------------------------------------------------
// Boundary condition: expected_degree == 0.
// In this case, no node degree is <= expected_degree (since any real node
// participating in an edge has degree >= 1), so the random branch is used.
// The probability term becomes 0, so no additional edges are chosen,
// and all edges should end up invalid.
// ---------------------------------------------------------------------------
TEST_F(ViewGraphManipulaterTest_87,
       ExpectedDegreeZeroRemovesAllEdges_87) {
  // Arrange: a simple single edge between two images.
  image_t img1 = static_cast<image_t>(1);
  image_t img2 = static_cast<image_t>(2);

  AddImage(img1);
  AddImage(img2);

  AddImagePair(static_cast<image_pair_t>(1), img1, img2, true);

  const int expected_degree = 0;

  // Act
  image_pair_t kept_count =
      manipulater_.SparsifyGraph(view_graph_, frames_, images_, expected_degree);

  // Assert: no edges should remain valid.
  EXPECT_EQ(kept_count, static_cast<image_pair_t>(0));

  for (const auto& kv : view_graph_.image_pairs) {
    const auto& pair = kv.second;
    EXPECT_FALSE(pair.is_valid);
  }
}

// ---------------------------------------------------------------------------
// Exceptional / edge case: initially invalid edges are ignored when selecting
// edges, and therefore they must not contribute to the returned count.
// They should remain invalid after sparsification.
// ---------------------------------------------------------------------------
TEST_F(ViewGraphManipulaterTest_87,
       InitiallyInvalidEdgesAreNotCounted_87) {
  // Arrange: two edges share an image; one is valid, one is already invalid.
  image_t img1 = static_cast<image_t>(1);
  image_t img2 = static_cast<image_t>(2);
  image_t img3 = static_cast<image_t>(3);

  AddImage(img1);
  AddImage(img2);
  AddImage(img3);

  // pair_id 1: valid
  AddImagePair(static_cast<image_pair_t>(1), img1, img2, true);
  // pair_id 2: invalid from the start
  AddImagePair(static_cast<image_pair_t>(2), img2, img3, false);

  const int expected_degree = 10;  // Large enough to keep valid edges.

  // Act
  image_pair_t kept_count =
      manipulater_.SparsifyGraph(view_graph_, frames_, images_, expected_degree);

  // Assert:
  // Only the initially valid edge should be counted.
  EXPECT_EQ(kept_count, static_cast<image_pair_t>(1));

  // The initially invalid edge must remain invalid.
  const auto& pair1 =
      view_graph_.image_pairs.at(static_cast<image_pair_t>(1));
  const auto& pair2 =
      view_graph_.image_pairs.at(static_cast<image_pair_t>(2));

  EXPECT_TRUE(pair1.is_valid);
  EXPECT_FALSE(pair2.is_valid);
}

}  // namespace glomap
