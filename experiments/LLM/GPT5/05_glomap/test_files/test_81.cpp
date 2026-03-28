// File: relpose_filter_test_81.cc

#include <gtest/gtest.h>

#include "glomap/processors/relpose_filter.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image_pair.h"

namespace glomap {

class RelPoseFilterTest_81 : public ::testing::Test {
 protected:
  ViewGraph view_graph_;

  void SetUp() override {
    view_graph_.image_pairs.clear();
  }

  static ImagePair MakeImagePairWithInliers(size_t num_inliers, bool is_valid = true) {
    ImagePair pair;
    pair.is_valid = is_valid;
    pair.inliers.assign(num_inliers, 0);
    return pair;
  }
};

// Normal case: pairs below the threshold become invalid, others stay valid.
TEST_F(RelPoseFilterTest_81, MarksPairsWithTooFewInliersInvalid_81) {
  const int kMinInlierNum = 4;

  ImagePair pair_low  = MakeImagePairWithInliers(2, true);  // < 4
  ImagePair pair_high = MakeImagePairWithInliers(5, true);  // >= 4

  view_graph_.image_pairs.emplace(1, pair_low);
  view_graph_.image_pairs.emplace(2, pair_high);

  RelPoseFilter filter;
  filter.FilterInlierNum(view_graph_, kMinInlierNum);

  EXPECT_FALSE(view_graph_.image_pairs.at(1).is_valid);
  EXPECT_TRUE(view_graph_.image_pairs.at(2).is_valid);
}

// Boundary: inlier count exactly equal to threshold should remain valid.
TEST_F(RelPoseFilterTest_81, InlierCountEqualToThresholdRemainsValid_81) {
  const int kMinInlierNum = 3;

  ImagePair pair_equal = MakeImagePairWithInliers(3, true);  // == 3
  ImagePair pair_above = MakeImagePairWithInliers(4, true);  // >  3

  view_graph_.image_pairs.emplace(1, pair_equal);
  view_graph_.image_pairs.emplace(2, pair_above);

  RelPoseFilter filter;
  filter.FilterInlierNum(view_graph_, kMinInlierNum);

  EXPECT_TRUE(view_graph_.image_pairs.at(1).is_valid);
  EXPECT_TRUE(view_graph_.image_pairs.at(2).is_valid);
}

// Boundary: zero threshold should not invalidate any pair (no negative inlier counts).
TEST_F(RelPoseFilterTest_81, ZeroThresholdKeepsAllPairsValid_81) {
  const int kMinInlierNum = 0;

  ImagePair pair_zero  = MakeImagePairWithInliers(0, true);
  ImagePair pair_some  = MakeImagePairWithInliers(5, true);

  view_graph_.image_pairs.emplace(1, pair_zero);
  view_graph_.image_pairs.emplace(2, pair_some);

  RelPoseFilter filter;
  filter.FilterInlierNum(view_graph_, kMinInlierNum);

  EXPECT_TRUE(view_graph_.image_pairs.at(1).is_valid);
  EXPECT_TRUE(view_graph_.image_pairs.at(2).is_valid);
}

// Error / edge case: already invalid pairs remain invalid and are not re-validated.
TEST_F(RelPoseFilterTest_81, DoesNotRevalidateAlreadyInvalidPairs_81) {
  const int kMinInlierNum = 2;

  ImagePair pair_invalid_high = MakeImagePairWithInliers(10, false); // already invalid
  ImagePair pair_valid_low    = MakeImagePairWithInliers(1, true);   // should be invalidated

  view_graph_.image_pairs.emplace(1, pair_invalid_high);
  view_graph_.image_pairs.emplace(2, pair_valid_low);

  RelPoseFilter filter;
  filter.FilterInlierNum(view_graph_, kMinInlierNum);

  EXPECT_FALSE(view_graph_.image_pairs.at(1).is_valid);  // stays invalid
  EXPECT_FALSE(view_graph_.image_pairs.at(2).is_valid);  // becomes invalid
}

// Edge case: empty view graph should be handled without modifying anything.
TEST_F(RelPoseFilterTest_81, HandlesEmptyViewGraph_81) {
  ASSERT_TRUE(view_graph_.image_pairs.empty());

  RelPoseFilter filter;
  filter.FilterInlierNum(view_graph_, 5);

  EXPECT_TRUE(view_graph_.image_pairs.empty());
}

// Mixed case: multiple pairs, some already invalid, some below / above threshold.
TEST_F(RelPoseFilterTest_81, FiltersOnlyValidPairsBelowThreshold_81) {
  const int kMinInlierNum = 3;

  ImagePair pair_valid_low    = MakeImagePairWithInliers(1, true);   // should be invalidated
  ImagePair pair_valid_high   = MakeImagePairWithInliers(5, true);   // should stay valid
  ImagePair pair_invalid_low  = MakeImagePairWithInliers(1, false);  // stays invalid
  ImagePair pair_invalid_high = MakeImagePairWithInliers(5, false);  // stays invalid

  view_graph_.image_pairs.emplace(1, pair_valid_low);
  view_graph_.image_pairs.emplace(2, pair_valid_high);
  view_graph_.image_pairs.emplace(3, pair_invalid_low);
  view_graph_.image_pairs.emplace(4, pair_invalid_high);

  RelPoseFilter filter;
  filter.FilterInlierNum(view_graph_, kMinInlierNum);

  EXPECT_FALSE(view_graph_.image_pairs.at(1).is_valid);  // filtered
  EXPECT_TRUE(view_graph_.image_pairs.at(2).is_valid);   // kept
  EXPECT_FALSE(view_graph_.image_pairs.at(3).is_valid);  // unchanged
  EXPECT_FALSE(view_graph_.image_pairs.at(4).is_valid);  // unchanged
}

}  // namespace glomap
