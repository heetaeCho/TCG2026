#include <gtest/gtest.h>
#include "glomap/processors/relpose_filter.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image_pair.h"

namespace glomap {
namespace {

// Helper to create an ImagePair with specific inlier/match counts
ImagePair CreateImagePairWithInlierRatio(image_t id1, image_t id2,
                                          int num_inliers, int num_matches) {
  ImagePair pair(id1, id2);
  pair.matches.resize(num_matches, 2);
  pair.matches.setZero();
  pair.inliers.clear();
  for (int i = 0; i < num_inliers; i++) {
    pair.inliers.push_back(i);
  }
  pair.is_valid = true;
  return pair;
}

class RelPoseFilterTest_82 : public ::testing::Test {
 protected:
  ViewGraph view_graph_;
};

// Test: All pairs above the threshold remain valid
TEST_F(RelPoseFilterTest_82, FilterInlierRatio_AllAboveThreshold_82) {
  // 80% inlier ratio, threshold 0.5
  ImagePair pair = CreateImagePairWithInlierRatio(0, 1, 8, 10);
  view_graph_.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterInlierRatio(view_graph_, 0.5);

  EXPECT_TRUE(view_graph_.image_pairs[pair.pair_id].is_valid);
}

// Test: All pairs below the threshold become invalid
TEST_F(RelPoseFilterTest_82, FilterInlierRatio_AllBelowThreshold_82) {
  // 20% inlier ratio, threshold 0.5
  ImagePair pair = CreateImagePairWithInlierRatio(0, 1, 2, 10);
  view_graph_.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterInlierRatio(view_graph_, 0.5);

  EXPECT_FALSE(view_graph_.image_pairs[pair.pair_id].is_valid);
}

// Test: Pair exactly at threshold boundary should remain valid
TEST_F(RelPoseFilterTest_82, FilterInlierRatio_ExactlyAtThreshold_82) {
  // 50% inlier ratio, threshold 0.5
  ImagePair pair = CreateImagePairWithInlierRatio(0, 1, 5, 10);
  view_graph_.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterInlierRatio(view_graph_, 0.5);

  EXPECT_TRUE(view_graph_.image_pairs[pair.pair_id].is_valid);
}

// Test: Already invalid pairs should not be affected
TEST_F(RelPoseFilterTest_82, FilterInlierRatio_AlreadyInvalidPairIgnored_82) {
  ImagePair pair = CreateImagePairWithInlierRatio(0, 1, 8, 10);
  pair.is_valid = false;
  view_graph_.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterInlierRatio(view_graph_, 0.5);

  // Should remain invalid (it was already invalid, not processed)
  EXPECT_FALSE(view_graph_.image_pairs[pair.pair_id].is_valid);
}

// Test: Mixed pairs - some above, some below threshold
TEST_F(RelPoseFilterTest_82, FilterInlierRatio_MixedPairs_82) {
  // Pair 1: 80% ratio - should stay valid
  ImagePair pair1 = CreateImagePairWithInlierRatio(0, 1, 8, 10);
  view_graph_.image_pairs[pair1.pair_id] = pair1;

  // Pair 2: 10% ratio - should become invalid
  ImagePair pair2 = CreateImagePairWithInlierRatio(2, 3, 1, 10);
  view_graph_.image_pairs[pair2.pair_id] = pair2;

  // Pair 3: 60% ratio - should stay valid
  ImagePair pair3 = CreateImagePairWithInlierRatio(4, 5, 6, 10);
  view_graph_.image_pairs[pair3.pair_id] = pair3;

  RelPoseFilter::FilterInlierRatio(view_graph_, 0.5);

  EXPECT_TRUE(view_graph_.image_pairs[pair1.pair_id].is_valid);
  EXPECT_FALSE(view_graph_.image_pairs[pair2.pair_id].is_valid);
  EXPECT_TRUE(view_graph_.image_pairs[pair3.pair_id].is_valid);
}

// Test: Empty view graph - no crash
TEST_F(RelPoseFilterTest_82, FilterInlierRatio_EmptyViewGraph_82) {
  EXPECT_NO_THROW(RelPoseFilter::FilterInlierRatio(view_graph_, 0.5));
}

// Test: Threshold of 0 - all pairs should remain valid
TEST_F(RelPoseFilterTest_82, FilterInlierRatio_ZeroThreshold_82) {
  ImagePair pair = CreateImagePairWithInlierRatio(0, 1, 0, 10);
  view_graph_.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterInlierRatio(view_graph_, 0.0);

  EXPECT_TRUE(view_graph_.image_pairs[pair.pair_id].is_valid);
}

// Test: Threshold of 1.0 - only 100% inlier ratio passes
TEST_F(RelPoseFilterTest_82, FilterInlierRatio_MaxThreshold_82) {
  // 100% inlier ratio
  ImagePair pair1 = CreateImagePairWithInlierRatio(0, 1, 10, 10);
  view_graph_.image_pairs[pair1.pair_id] = pair1;

  // 99% inlier ratio (should be filtered)
  ImagePair pair2 = CreateImagePairWithInlierRatio(2, 3, 99, 100);
  view_graph_.image_pairs[pair2.pair_id] = pair2;

  RelPoseFilter::FilterInlierRatio(view_graph_, 1.0);

  EXPECT_TRUE(view_graph_.image_pairs[pair1.pair_id].is_valid);
  EXPECT_FALSE(view_graph_.image_pairs[pair2.pair_id].is_valid);
}

// Test: Pair with zero inliers should be filtered for any positive threshold
TEST_F(RelPoseFilterTest_82, FilterInlierRatio_ZeroInliers_82) {
  ImagePair pair = CreateImagePairWithInlierRatio(0, 1, 0, 10);
  view_graph_.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterInlierRatio(view_graph_, 0.1);

  EXPECT_FALSE(view_graph_.image_pairs[pair.pair_id].is_valid);
}

// Test: Single match with single inlier (100% ratio)
TEST_F(RelPoseFilterTest_82, FilterInlierRatio_SingleMatchSingleInlier_82) {
  ImagePair pair = CreateImagePairWithInlierRatio(0, 1, 1, 1);
  view_graph_.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterInlierRatio(view_graph_, 0.5);

  EXPECT_TRUE(view_graph_.image_pairs[pair.pair_id].is_valid);
}

// Test: Large number of pairs
TEST_F(RelPoseFilterTest_82, FilterInlierRatio_ManyPairs_82) {
  int num_valid_before = 0;
  int expected_filtered = 0;

  for (image_t i = 0; i < 20; i += 2) {
    int num_inliers = (i / 2) * 2;  // 0, 2, 4, 6, 8, 10, 12, 14, 16, 18
    ImagePair pair = CreateImagePairWithInlierRatio(i, i + 1, num_inliers, 20);
    view_graph_.image_pairs[pair.pair_id] = pair;
    num_valid_before++;
    if (num_inliers / 20.0 < 0.5) {
      expected_filtered++;
    }
  }

  RelPoseFilter::FilterInlierRatio(view_graph_, 0.5);

  int num_invalid_after = 0;
  for (auto& [pair_id, image_pair] : view_graph_.image_pairs) {
    if (!image_pair.is_valid) {
      num_invalid_after++;
    }
  }

  EXPECT_EQ(num_invalid_after, expected_filtered);
}

// Test: Ratio just below threshold
TEST_F(RelPoseFilterTest_82, FilterInlierRatio_JustBelowThreshold_82) {
  // 49 inliers out of 100 = 0.49, threshold 0.5
  ImagePair pair = CreateImagePairWithInlierRatio(0, 1, 49, 100);
  view_graph_.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterInlierRatio(view_graph_, 0.5);

  EXPECT_FALSE(view_graph_.image_pairs[pair.pair_id].is_valid);
}

// Test: Ratio just above threshold
TEST_F(RelPoseFilterTest_82, FilterInlierRatio_JustAboveThreshold_82) {
  // 51 inliers out of 100 = 0.51, threshold 0.5
  ImagePair pair = CreateImagePairWithInlierRatio(0, 1, 51, 100);
  view_graph_.image_pairs[pair.pair_id] = pair;

  RelPoseFilter::FilterInlierRatio(view_graph_, 0.5);

  EXPECT_TRUE(view_graph_.image_pairs[pair.pair_id].is_valid);
}

// Test: Multiple invalid pairs already present, only valid ones should be checked
TEST_F(RelPoseFilterTest_82, FilterInlierRatio_MixValidAndInvalidPreExisting_82) {
  // Valid pair with low ratio - should become invalid
  ImagePair pair1 = CreateImagePairWithInlierRatio(0, 1, 1, 10);
  pair1.is_valid = true;
  view_graph_.image_pairs[pair1.pair_id] = pair1;

  // Already invalid pair with high ratio - should remain invalid
  ImagePair pair2 = CreateImagePairWithInlierRatio(2, 3, 9, 10);
  pair2.is_valid = false;
  view_graph_.image_pairs[pair2.pair_id] = pair2;

  // Valid pair with high ratio - should remain valid
  ImagePair pair3 = CreateImagePairWithInlierRatio(4, 5, 9, 10);
  pair3.is_valid = true;
  view_graph_.image_pairs[pair3.pair_id] = pair3;

  RelPoseFilter::FilterInlierRatio(view_graph_, 0.5);

  EXPECT_FALSE(view_graph_.image_pairs[pair1.pair_id].is_valid);
  EXPECT_FALSE(view_graph_.image_pairs[pair2.pair_id].is_valid);
  EXPECT_TRUE(view_graph_.image_pairs[pair3.pair_id].is_valid);
}

}  // namespace
}  // namespace glomap
