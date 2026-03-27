// File: relpose_filter_test_82.cc

#include <gtest/gtest.h>
#include <unordered_map>

#include "glomap/processors/relpose_filter.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image_pair.h"

#include <Eigen/Core>

namespace glomap {

class RelPoseFilterTest_82 : public ::testing::Test {
protected:
  // Helper to construct an ImagePair with given numbers of matches and inliers.
  ImagePair MakeImagePairWithCounts(int num_match_rows,
                                    int num_inliers,
                                    bool is_valid = true) {
    ImagePair image_pair;  // Use default constructor; ids are irrelevant here.

    image_pair.is_valid = is_valid;

    // We only care about rows(), so a single column is enough.
    image_pair.matches = Eigen::MatrixXi::Zero(num_match_rows, 1);

    image_pair.inliers.clear();
    image_pair.inliers.resize(static_cast<size_t>(num_inliers), 0);

    return image_pair;
  }

  // Helper to insert an image pair into a ViewGraph with a simple key.
  void AddImagePair(ViewGraph& view_graph,
                    image_pair_t key,
                    const ImagePair& image_pair) {
    view_graph.image_pairs.emplace(key, image_pair);
  }
};

// Normal operation: pairs below threshold become invalid, above stay valid.
TEST_F(RelPoseFilterTest_82,
       MarksPairsWithLowInlierRatioAsInvalid_82) {
  ViewGraph view_graph;

  // pair 1: ratio = 8 / 10 = 0.8  (above threshold 0.5) -> should stay valid
  AddImagePair(view_graph, image_pair_t(1),
               MakeImagePairWithCounts(/*num_match_rows=*/10,
                                       /*num_inliers=*/8,
                                       /*is_valid=*/true));

  // pair 2: ratio = 2 / 10 = 0.2  (below threshold 0.5) -> should become invalid
  AddImagePair(view_graph, image_pair_t(2),
               MakeImagePairWithCounts(/*num_match_rows=*/10,
                                       /*num_inliers=*/2,
                                       /*is_valid=*/true));

  // pair 3: already invalid; should remain invalid regardless of ratio
  AddImagePair(view_graph, image_pair_t(3),
               MakeImagePairWithCounts(/*num_match_rows=*/10,
                                       /*num_inliers=*/1,
                                       /*is_valid=*/false));

  RelPoseFilter filter;
  const double threshold = 0.5;
  filter.FilterInlierRatio(view_graph, threshold);

  // Check results
  EXPECT_TRUE(view_graph.image_pairs.at(image_pair_t(1)).is_valid);
  EXPECT_FALSE(view_graph.image_pairs.at(image_pair_t(2)).is_valid);
  EXPECT_FALSE(view_graph.image_pairs.at(image_pair_t(3)).is_valid);
}

// Boundary condition: ratio exactly equal to threshold should remain valid
// because the implementation uses "< min_inlier_ratio" for filtering.
TEST_F(RelPoseFilterTest_82,
       KeepsPairsWithInlierRatioEqualToThresholdValid_82) {
  ViewGraph view_graph;

  // ratio = 5 / 10 = 0.5, threshold = 0.5 -> should stay valid
  AddImagePair(view_graph, image_pair_t(10),
               MakeImagePairWithCounts(/*num_match_rows=*/10,
                                       /*num_inliers=*/5,
                                       /*is_valid=*/true));

  RelPoseFilter filter;
  const double threshold = 0.5;
  filter.FilterInlierRatio(view_graph, threshold);

  EXPECT_TRUE(view_graph.image_pairs.at(image_pair_t(10)).is_valid);
}

// Edge case: all pairs have high inlier ratio, so none should be filtered.
TEST_F(RelPoseFilterTest_82,
       DoesNotFilterPairsWhenAllRatiosAboveThreshold_82) {
  ViewGraph view_graph;

  // All ratios above threshold 0.3
  AddImagePair(view_graph, image_pair_t(21),
               MakeImagePairWithCounts(/*num_match_rows=*/10,
                                       /*num_inliers=*/7,
                                       /*is_valid=*/true));  // 0.7

  AddImagePair(view_graph, image_pair_t(22),
               MakeImagePairWithCounts(/*num_match_rows=*/20,
                                       /*num_inliers=*/10,
                                       /*is_valid=*/true));  // 0.5

  AddImagePair(view_graph, image_pair_t(23),
               MakeImagePairWithCounts(/*num_match_rows=*/5,
                                       /*num_inliers=*/4,
                                       /*is_valid=*/true));  // 0.8

  RelPoseFilter filter;
  const double threshold = 0.3;
  filter.FilterInlierRatio(view_graph, threshold);

  EXPECT_TRUE(view_graph.image_pairs.at(image_pair_t(21)).is_valid);
  EXPECT_TRUE(view_graph.image_pairs.at(image_pair_t(22)).is_valid);
  EXPECT_TRUE(view_graph.image_pairs.at(image_pair_t(23)).is_valid);
}

// Edge case: empty ViewGraph should be handled gracefully (no crash, no change).
TEST_F(RelPoseFilterTest_82,
       HandlesEmptyViewGraphWithoutCrashing_82) {
  ViewGraph view_graph;

  RelPoseFilter filter;
  filter.FilterInlierRatio(view_graph, /*min_inlier_ratio=*/0.5);

  // Nothing to check except that the function returns without error.
  EXPECT_TRUE(view_graph.image_pairs.empty());
}

}  // namespace glomap
