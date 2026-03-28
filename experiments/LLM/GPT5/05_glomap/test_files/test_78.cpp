// TEST_ID: 78

#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>

#include <Eigen/Core>

#include "glomap/processors/image_pair_inliers.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/image.h"
#include "glomap/types.h"

namespace {

// Expose the protected ScoreErrorFundamental for testing.
class TestableImagePairInliers_78 : public glomap::ImagePairInliers {
 public:
  using glomap::ImagePairInliers::ImagePairInliers;

  double CallScoreErrorFundamental() {
    return ScoreErrorFundamental();
  }
};

class ImagePairInliersTest_78 : public ::testing::Test {
 protected:
  glomap::ImagePair image_pair_;
  std::unordered_map<glomap::image_t, glomap::Image> images_;
  glomap::InlierThresholdOptions options_;

  ImagePairInliersTest_78()
      : image_pair_(static_cast<glomap::image_t>(1),
                    static_cast<glomap::image_t>(2)) {}

  void SetUp() override {
    // Simple fundamental matrix and match structure.
    image_pair_.F = Eigen::Matrix3d::Identity();

    // Prepare a few 2D features for both images.
    glomap::Image img1;
    img1.features.resize(3);
    img1.features[0] = Eigen::Vector2d(0.0, 0.0);
    img1.features[1] = Eigen::Vector2d(1.0, 0.0);
    img1.features[2] = Eigen::Vector2d(0.0, 1.0);

    glomap::Image img2;
    img2.features.resize(3);
    img2.features[0] = Eigen::Vector2d(0.0, 0.0);
    img2.features[1] = Eigen::Vector2d(1.0, 0.0);
    img2.features[2] = Eigen::Vector2d(0.0, 1.0);

    images_.emplace(static_cast<glomap::image_t>(1), img1);
    images_.emplace(static_cast<glomap::image_t>(2), img2);

    // Three one-to-one matches between the two images.
    image_pair_.matches.resize(3, 2);
    image_pair_.matches(0, 0) = 0; image_pair_.matches(0, 1) = 0;
    image_pair_.matches(1, 0) = 1; image_pair_.matches(1, 1) = 1;
    image_pair_.matches(2, 0) = 2; image_pair_.matches(2, 1) = 2;

    // Use default options but keep them modifiable per test if needed.
  }

  double CallScoreWithCurrentState() {
    TestableImagePairInliers_78 processor(image_pair_, images_, options_);
    return processor.CallScoreErrorFundamental();
  }
};

// Boundary condition: no matches -> score must be 0 and inliers cleared.
TEST_F(ImagePairInliersTest_78, ReturnsZeroForNoMatches_78) {
  // Pre-populate inliers to verify they are cleared.
  image_pair_.inliers = {0, 1, 2};

  // No matches.
  image_pair_.matches.resize(0, 2);

  double score = CallScoreWithCurrentState();

  EXPECT_DOUBLE_EQ(score, 0.0);
  EXPECT_TRUE(image_pair_.inliers.empty());
}

// Normal operation: existing inliers should not affect the result
// (they are cleared at the beginning of the function).
TEST_F(ImagePairInliersTest_78, ExistingInliersDoNotAffectResult_78) {
  // Ensure matches are present from SetUp.
  ASSERT_EQ(image_pair_.matches.rows(), 3);

  // First run with empty inliers.
  image_pair_.inliers.clear();
  double score1 = CallScoreWithCurrentState();
  std::vector<int> inliers_after_first = image_pair_.inliers;

  // Now add some dummy "stale" inliers and run again.
  image_pair_.inliers = {100, 200};
  double score2 = CallScoreWithCurrentState();
  std::vector<int> inliers_after_second = image_pair_.inliers;

  // Behavior should be identical regardless of initial inliers content.
  EXPECT_DOUBLE_EQ(score1, score2);
  EXPECT_EQ(inliers_after_first, inliers_after_second);

  // And stale indices should have been removed.
  for (int idx : inliers_after_second) {
    EXPECT_NE(idx, 100);
    EXPECT_NE(idx, 200);
  }
}

// Structural property: resulting inliers indices are within range and sorted.
TEST_F(ImagePairInliersTest_78, InliersWithinRangeAndSorted_78) {
  // Use the default configuration with some matches.
  ASSERT_EQ(image_pair_.matches.rows(), 3);

  (void)CallScoreWithCurrentState();

  const auto& inliers = image_pair_.inliers;
  const int num_matches = static_cast<int>(image_pair_.matches.rows());

  // Indices must be within [0, num_matches) and strictly increasing.
  for (size_t i = 0; i < inliers.size(); ++i) {
    EXPECT_GE(inliers[i], 0);
    EXPECT_LT(inliers[i], num_matches);

    if (i > 0) {
      EXPECT_LT(inliers[i - 1], inliers[i]);
    }
  }
}

}  // namespace
