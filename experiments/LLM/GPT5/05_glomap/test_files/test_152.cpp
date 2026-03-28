// File: relpose_filter_test_152.cc

#include <gtest/gtest.h>
#include <stdexcept>
#include <unordered_map>

#include "glomap/processors/relpose_filter.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"

namespace glomap {

class RelPoseFilterTest_152 : public ::testing::Test {
 protected:
  using ImageMap = std::unordered_map<image_t, Image>;

  // Helper: create a simple ViewGraph with a single valid ImagePair (1, 2).
  ViewGraph CreateSimpleViewGraphWithSinglePair(image_t id1, image_t id2) {
    ViewGraph view_graph;
    ImagePair pair(id1, id2);
    view_graph.image_pairs.emplace(pair.pair_id, pair);
    return view_graph;
  }

  // Helper: create an image map with two images (ids 1 and 2).
  ImageMap CreateSimpleImageMap(image_t id1, image_t id2) {
    ImageMap images;
    // We only rely on the public constructor; internal pose / registration
    // details are treated as a black box.
    camera_t dummy_cam_id = 1;
    images.emplace(id1, Image(id1, dummy_cam_id, "image1"));
    images.emplace(id2, Image(id2, dummy_cam_id, "image2"));
    return images;
  }
};

//------------------------------------------------------------------------------
// 1) Normal operation on empty ViewGraph: no crash, no modification
//------------------------------------------------------------------------------
TEST_F(RelPoseFilterTest_152, EmptyViewGraph_NoChanges_152) {
  ViewGraph view_graph;
  RelPoseFilter filter;

  std::unordered_map<image_t, Image> empty_images;
  const double max_angle = 10.0;

  // Should not throw and should keep image_pairs empty.
  ASSERT_TRUE(view_graph.image_pairs.empty());

  EXPECT_NO_THROW({
    filter.FilterRotations(view_graph, empty_images, max_angle);
  });

  EXPECT_TRUE(view_graph.image_pairs.empty());
}

//------------------------------------------------------------------------------
// 2) Already-invalid pairs are skipped and do not require images to exist
//    (no exception even if image IDs are not in the images map)
//------------------------------------------------------------------------------
TEST_F(RelPoseFilterTest_152, SkipsAlreadyInvalidPairsWithoutImageLookup_152) {
  ViewGraph view_graph;

  // Create an ImagePair with IDs that won't exist in the images map.
  image_t missing_id1 = 100;
  image_t missing_id2 = 200;
  ImagePair pair(missing_id1, missing_id2);
  pair.is_valid = false;  // Mark as already invalid.

  view_graph.image_pairs.emplace(pair.pair_id, pair);

  // Empty images map: if the implementation tried to look up images.at(...)
  // for this pair, it would throw std::out_of_range. Since is_valid == false,
  // it should be skipped and thus not throw.
  std::unordered_map<image_t, Image> empty_images;
  RelPoseFilter filter;

  EXPECT_NO_THROW({
    filter.FilterRotations(view_graph, empty_images, 5.0);
  });

  // The pair should remain invalid.
  const auto& stored_pair = view_graph.image_pairs.at(pair.pair_id);
  EXPECT_FALSE(stored_pair.is_valid);
}

//------------------------------------------------------------------------------
// 3) Valid pair referencing missing images should cause std::out_of_range
//    from images.at(...)
//------------------------------------------------------------------------------
TEST_F(RelPoseFilterTest_152, ThrowsWhenImagesMissingForValidPair_152) {
  ViewGraph view_graph;

  image_t missing_id1 = 10;
  image_t missing_id2 = 20;
  ImagePair pair(missing_id1, missing_id2);
  pair.is_valid = true;  // Still valid, so the filter will try to access images.

  view_graph.image_pairs.emplace(pair.pair_id, pair);

  std::unordered_map<image_t, Image> empty_images;
  RelPoseFilter filter;

  EXPECT_THROW(
      filter.FilterRotations(view_graph, empty_images, 15.0),
      std::out_of_range);
}

//------------------------------------------------------------------------------
// 4) Monotonicity w.r.t. max_angle:
//    For two fresh, identical graphs, using a smaller max_angle should never
//    produce *fewer* invalid pairs than using a larger max_angle.
//    (invalid_large ⊆ invalid_small)
//------------------------------------------------------------------------------
TEST_F(RelPoseFilterTest_152, MonotonicFilteringWithRespectToMaxAngle_152) {
  const image_t id1 = 1;
  const image_t id2 = 2;

  // Two identical graphs and image maps
  ViewGraph view_graph_small = CreateSimpleViewGraphWithSinglePair(id1, id2);
  ViewGraph view_graph_large = view_graph_small;  // copy
  auto images = CreateSimpleImageMap(id1, id2);

  RelPoseFilter filter;

  const double small_threshold = 5.0;
  const double large_threshold = 30.0;
  ASSERT_LT(small_threshold, large_threshold);

  // Run with small threshold
  filter.FilterRotations(view_graph_small, images, small_threshold);

  // Run with large threshold on the copied graph
  filter.FilterRotations(view_graph_large, images, large_threshold);

  // Compare invalid sets: for each pair, if it is invalid with the larger
  // threshold, it must also be invalid with the smaller threshold.
  for (const auto& kv : view_graph_large.image_pairs) {
    const image_pair_t pair_id = kv.first;
    const ImagePair& pair_large = kv.second;

    const auto it_small = view_graph_small.image_pairs.find(pair_id);
    ASSERT_NE(it_small, view_graph_small.image_pairs.end());
    const ImagePair& pair_small = it_small->second;

    if (!pair_large.is_valid) {
      // If invalid with larger threshold, it must also be invalid with smaller.
      EXPECT_FALSE(pair_small.is_valid)
          << "Pair " << pair_id
          << " is invalid with large threshold but valid with small threshold";
    }
  }
}

//------------------------------------------------------------------------------
// 5) Extremely small max_angle (e.g., negative) should invalidate any
//    registered pair whose relative rotation angle is finite.
//    We require images to be registered; otherwise, we skip the test.
//------------------------------------------------------------------------------
TEST_F(RelPoseFilterTest_152, VerySmallMaxAngle_RegisteredImages_Invalidate_152) {
  const image_t id1 = 1;
  const image_t id2 = 2;

  ViewGraph view_graph = CreateSimpleViewGraphWithSinglePair(id1, id2);
  auto images = CreateSimpleImageMap(id1, id2);

  // Check registration status via the public interface.
  const bool reg1 = images.at(id1).IsRegistered();
  const bool reg2 = images.at(id2).IsRegistered();

  if (!reg1 || !reg2) {
    GTEST_SKIP() << "Images are not registered in this environment; "
                 << "cannot exercise the branch that uses relative rotations.";
  }

  RelPoseFilter filter;

  // A negative threshold should be smaller than any usual rotation angle.
  const double max_angle = -1.0;

  filter.FilterRotations(view_graph, images, max_angle);

  // Since the pair was valid and images are registered, the implementation
  // computes a relative rotation and compares it with max_angle. With a very
  // small threshold, we expect this pair to be invalidated.
  ASSERT_EQ(view_graph.image_pairs.size(), 1u);
  const auto& stored_pair = view_graph.image_pairs.begin()->second;
  EXPECT_FALSE(stored_pair.is_valid);
}

}  // namespace glomap
