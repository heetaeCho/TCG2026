// File: image_pairs_inlier_count_test_149.cc

#include <gtest/gtest.h>

#include <unordered_map>
#include <vector>

#include "glomap/types.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/view_graph.h"
#include "glomap/processors/image_pair_inliers.h"

namespace glomap {

// Forward declaration of the function under test (implemented in image_pair_inliers.cc).
void ImagePairsInlierCount(ViewGraph& view_graph,
                           const std::unordered_map<camera_t, Camera>& cameras,
                           const std::unordered_map<image_t, Image>& images,
                           const InlierThresholdOptions& options,
                           bool clean_inliers);

}  // namespace glomap

class ImagePairsInlierCountTest_149 : public ::testing::Test {
 protected:
  glomap::ViewGraph view_graph_;
  std::unordered_map<glomap::camera_t, glomap::Camera> cameras_;
  std::unordered_map<glomap::image_t, glomap::Image> images_;
  glomap::InlierThresholdOptions options_;
};

// -----------------------------------------------------------------------------
// Behavior: If clean_inliers == false and the ImagePair already has inliers,
//           the function must skip that pair without clearing its inliers.
// -----------------------------------------------------------------------------
TEST_F(ImagePairsInlierCountTest_149,
       SkipsPairsWithExistingInliersWhenNotCleaning_149) {
  glomap::ImagePair image_pair;
  image_pair.is_valid = true;
  image_pair.inliers = {1, 2, 3};

  const glomap::image_pair_t pair_id = 1;
  view_graph_.image_pairs.emplace(pair_id, image_pair);

  glomap::ImagePairsInlierCount(view_graph_, cameras_, images_, options_,
                                /*clean_inliers=*/false);

  const auto& stored_pair = view_graph_.image_pairs.at(pair_id);
  ASSERT_EQ(stored_pair.inliers.size(), 3u);
  EXPECT_EQ(stored_pair.inliers[0], 1);
  EXPECT_EQ(stored_pair.inliers[1], 2);
  EXPECT_EQ(stored_pair.inliers[2], 3);
}

// -----------------------------------------------------------------------------
// Behavior: If the ImagePair is invalid (is_valid == false), but already has
//           inliers and clean_inliers == false, the early continue based on
//           existing inliers should still apply, so inliers remain unchanged.
// -----------------------------------------------------------------------------
TEST_F(ImagePairsInlierCountTest_149,
       InvalidPairWithExistingInliersNotCleanedWhenNotCleaning_149) {
  glomap::ImagePair image_pair;
  image_pair.is_valid = false;
  image_pair.inliers = {10, 20};

  const glomap::image_pair_t pair_id = 2;
  view_graph_.image_pairs.emplace(pair_id, image_pair);

  glomap::ImagePairsInlierCount(view_graph_, cameras_, images_, options_,
                                /*clean_inliers=*/false);

  const auto& stored_pair = view_graph_.image_pairs.at(pair_id);
  ASSERT_EQ(stored_pair.inliers.size(), 2u);
  EXPECT_EQ(stored_pair.inliers[0], 10);
  EXPECT_EQ(stored_pair.inliers[1], 20);
}

// -----------------------------------------------------------------------------
// Behavior: If clean_inliers == true and the ImagePair is invalid
//           (is_valid == false), the function clears inliers and then skips
//           further processing (ScoreError is not called from this function).
//           The observable effect is that inliers become empty.
// -----------------------------------------------------------------------------
TEST_F(ImagePairsInlierCountTest_149,
       ClearsInliersForInvalidPairsWhenCleaning_149) {
  glomap::ImagePair image_pair;
  image_pair.is_valid = false;
  image_pair.inliers = {5, 6, 7};

  const glomap::image_pair_t pair_id = 3;
  view_graph_.image_pairs.emplace(pair_id, image_pair);

  glomap::ImagePairsInlierCount(view_graph_, cameras_, images_, options_,
                                /*clean_inliers=*/true);

  const auto& stored_pair = view_graph_.image_pairs.at(pair_id);
  EXPECT_TRUE(stored_pair.inliers.empty());
}

// -----------------------------------------------------------------------------
// Behavior: Function should handle an empty ViewGraph gracefully without
//           modifying it or throwing exceptions.
// -----------------------------------------------------------------------------
TEST_F(ImagePairsInlierCountTest_149, HandlesEmptyViewGraph_149) {
  ASSERT_TRUE(view_graph_.image_pairs.empty());

  glomap::ImagePairsInlierCount(view_graph_, cameras_, images_, options_,
                                /*clean_inliers=*/false);

  EXPECT_TRUE(view_graph_.image_pairs.empty());
}
