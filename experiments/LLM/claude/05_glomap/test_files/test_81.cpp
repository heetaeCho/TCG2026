#include <gtest/gtest.h>
#include "glomap/processors/relpose_filter.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image_pair.h"

namespace glomap {
namespace {

class RelPoseFilterTest_81 : public ::testing::Test {
 protected:
  void SetUp() override {}

  // Helper to create an ImagePair and insert it into the view graph
  void AddImagePair(ViewGraph& vg, image_t id1, image_t id2,
                    const std::vector<int>& inliers, bool is_valid = true) {
    ImagePair pair(id1, id2);
    pair.inliers = inliers;
    pair.is_valid = is_valid;
    vg.image_pairs[pair.pair_id] = pair;
  }
};

// Test that pairs with fewer inliers than the threshold are invalidated
TEST_F(RelPoseFilterTest_81, FilterInlierNum_InvalidatesBelowThreshold_81) {
  ViewGraph vg;
  // Pair with 3 inliers (below threshold of 5)
  AddImagePair(vg, 0, 1, {1, 2, 3});
  // Pair with 5 inliers (at threshold)
  AddImagePair(vg, 0, 2, {1, 2, 3, 4, 5});
  // Pair with 10 inliers (above threshold)
  AddImagePair(vg, 1, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

  RelPoseFilter::FilterInlierNum(vg, 5);

  for (auto& [pair_id, image_pair] : vg.image_pairs) {
    if (image_pair.image_id1 == 0 && image_pair.image_id2 == 1) {
      EXPECT_FALSE(image_pair.is_valid) << "Pair (0,1) with 3 inliers should be invalid";
    } else if (image_pair.image_id1 == 0 && image_pair.image_id2 == 2) {
      EXPECT_TRUE(image_pair.is_valid) << "Pair (0,2) with 5 inliers should remain valid";
    } else if (image_pair.image_id1 == 1 && image_pair.image_id2 == 2) {
      EXPECT_TRUE(image_pair.is_valid) << "Pair (1,2) with 10 inliers should remain valid";
    }
  }
}

// Test that already invalid pairs are not re-evaluated
TEST_F(RelPoseFilterTest_81, FilterInlierNum_SkipsAlreadyInvalidPairs_81) {
  ViewGraph vg;
  // Pair already invalid with enough inliers - should stay invalid
  AddImagePair(vg, 0, 1, {1, 2, 3, 4, 5, 6}, false);
  // Pair already invalid with too few inliers - should stay invalid
  AddImagePair(vg, 0, 2, {1}, false);

  RelPoseFilter::FilterInlierNum(vg, 5);

  for (auto& [pair_id, image_pair] : vg.image_pairs) {
    EXPECT_FALSE(image_pair.is_valid) << "Already invalid pairs should remain invalid";
  }
}

// Test with an empty view graph
TEST_F(RelPoseFilterTest_81, FilterInlierNum_EmptyViewGraph_81) {
  ViewGraph vg;
  // Should not crash
  RelPoseFilter::FilterInlierNum(vg, 5);
  EXPECT_TRUE(vg.image_pairs.empty());
}

// Test with threshold of 0 - all pairs should remain valid
TEST_F(RelPoseFilterTest_81, FilterInlierNum_ZeroThreshold_81) {
  ViewGraph vg;
  AddImagePair(vg, 0, 1, {});
  AddImagePair(vg, 0, 2, {1, 2, 3});

  RelPoseFilter::FilterInlierNum(vg, 0);

  for (auto& [pair_id, image_pair] : vg.image_pairs) {
    EXPECT_TRUE(image_pair.is_valid);
  }
}

// Test with threshold of 1 - pair with 0 inliers should be invalidated
TEST_F(RelPoseFilterTest_81, FilterInlierNum_ThresholdOne_EmptyInliers_81) {
  ViewGraph vg;
  AddImagePair(vg, 0, 1, {});  // 0 inliers

  RelPoseFilter::FilterInlierNum(vg, 1);

  for (auto& [pair_id, image_pair] : vg.image_pairs) {
    EXPECT_FALSE(image_pair.is_valid) << "Pair with 0 inliers should be invalid when threshold is 1";
  }
}

// Test boundary: exactly at threshold should remain valid
TEST_F(RelPoseFilterTest_81, FilterInlierNum_ExactlyAtThreshold_81) {
  ViewGraph vg;
  AddImagePair(vg, 0, 1, {1, 2, 3, 4, 5});

  RelPoseFilter::FilterInlierNum(vg, 5);

  for (auto& [pair_id, image_pair] : vg.image_pairs) {
    EXPECT_TRUE(image_pair.is_valid) << "Pair with exactly threshold inliers should remain valid";
  }
}

// Test boundary: one below threshold should be invalidated
TEST_F(RelPoseFilterTest_81, FilterInlierNum_OneBelowThreshold_81) {
  ViewGraph vg;
  AddImagePair(vg, 0, 1, {1, 2, 3, 4});

  RelPoseFilter::FilterInlierNum(vg, 5);

  for (auto& [pair_id, image_pair] : vg.image_pairs) {
    EXPECT_FALSE(image_pair.is_valid) << "Pair with one less than threshold should be invalid";
  }
}

// Test that all pairs are invalidated when threshold is very large
TEST_F(RelPoseFilterTest_81, FilterInlierNum_LargeThreshold_81) {
  ViewGraph vg;
  AddImagePair(vg, 0, 1, {1, 2, 3});
  AddImagePair(vg, 0, 2, {1, 2, 3, 4, 5});
  AddImagePair(vg, 1, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

  RelPoseFilter::FilterInlierNum(vg, 1000);

  for (auto& [pair_id, image_pair] : vg.image_pairs) {
    EXPECT_FALSE(image_pair.is_valid) << "All pairs should be invalid with very large threshold";
  }
}

// Test with multiple pairs, some valid and some already invalid, mixed inlier counts
TEST_F(RelPoseFilterTest_81, FilterInlierNum_MixedValidityAndInliers_81) {
  ViewGraph vg;
  AddImagePair(vg, 0, 1, {1, 2}, true);       // valid, 2 inliers -> should be invalidated
  AddImagePair(vg, 0, 2, {1, 2, 3, 4, 5}, true);  // valid, 5 inliers -> should stay valid
  AddImagePair(vg, 1, 2, {1}, false);          // already invalid, 1 inlier -> should stay invalid
  AddImagePair(vg, 2, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, true);  // valid, 10 inliers -> stay valid

  RelPoseFilter::FilterInlierNum(vg, 5);

  int valid_count = 0;
  int invalid_count = 0;
  for (auto& [pair_id, image_pair] : vg.image_pairs) {
    if (image_pair.is_valid) {
      valid_count++;
    } else {
      invalid_count++;
    }
  }
  EXPECT_EQ(valid_count, 2);
  EXPECT_EQ(invalid_count, 2);
}

// Test single pair that should remain valid
TEST_F(RelPoseFilterTest_81, FilterInlierNum_SingleValidPairAboveThreshold_81) {
  ViewGraph vg;
  AddImagePair(vg, 0, 1, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

  RelPoseFilter::FilterInlierNum(vg, 5);

  EXPECT_EQ(vg.image_pairs.size(), 1u);
  for (auto& [pair_id, image_pair] : vg.image_pairs) {
    EXPECT_TRUE(image_pair.is_valid);
  }
}

// Test single pair that should be invalidated
TEST_F(RelPoseFilterTest_81, FilterInlierNum_SingleValidPairBelowThreshold_81) {
  ViewGraph vg;
  AddImagePair(vg, 0, 1, {1, 2});

  RelPoseFilter::FilterInlierNum(vg, 5);

  EXPECT_EQ(vg.image_pairs.size(), 1u);
  for (auto& [pair_id, image_pair] : vg.image_pairs) {
    EXPECT_FALSE(image_pair.is_valid);
  }
}

}  // namespace
}  // namespace glomap
