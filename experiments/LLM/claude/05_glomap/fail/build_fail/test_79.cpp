#include <gtest/gtest.h>
#include <Eigen/Core>
#include <unordered_map>

#include "glomap/processors/image_pair_inliers.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/types.h"

namespace glomap {
namespace {

class ImagePairInliersTest_79 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create two images with features
    Image img1(0, 0, "img1.jpg");
    Image img2(1, 0, "img2.jpg");

    // Add some features to both images
    img1.features.push_back(Eigen::Vector2d(0.0, 0.0));
    img1.features.push_back(Eigen::Vector2d(1.0, 0.0));
    img1.features.push_back(Eigen::Vector2d(0.0, 1.0));
    img1.features.push_back(Eigen::Vector2d(1.0, 1.0));
    img1.features.push_back(Eigen::Vector2d(2.0, 2.0));

    img2.features.push_back(Eigen::Vector2d(0.0, 0.0));
    img2.features.push_back(Eigen::Vector2d(1.0, 0.0));
    img2.features.push_back(Eigen::Vector2d(0.0, 1.0));
    img2.features.push_back(Eigen::Vector2d(1.0, 1.0));
    img2.features.push_back(Eigen::Vector2d(100.0, 100.0));

    images_[0] = img1;
    images_[1] = img2;

    // Default options
    options_.max_epipolar_error_E = 1.0;
    options_.max_epipolar_error_F = 4.0;
    options_.max_epipolar_error_H = 4.0;
    options_.min_inlier_num = 30;
    options_.min_inlier_ratio = 0.25;
  }

  std::unordered_map<image_t, Image> images_;
  InlierThresholdOptions options_;
};

// Test ScoreError with identity homography - all matching points should be inliers
TEST_F(ImagePairInliersTest_79, HomographyIdentity_AllInliers_79) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::HOMOGRAPHY;
  pair.H = Eigen::Matrix3d::Identity();

  // Set up matches: feature i in img1 matches feature i in img2
  // Points (0,0)->(0,0), (1,0)->(1,0), (0,1)->(0,1), (1,1)->(1,1)
  Eigen::MatrixXi matches(4, 2);
  matches(0, 0) = 0; matches(0, 1) = 0;
  matches(1, 0) = 1; matches(1, 1) = 1;
  matches(2, 0) = 2; matches(2, 1) = 2;
  matches(3, 0) = 3; matches(3, 1) = 3;
  pair.matches = matches;

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  // With identity H and same points, error should be 0 for each match
  // All 4 should be inliers
  EXPECT_EQ(pair.inliers.size(), 4u);
  EXPECT_DOUBLE_EQ(score, 0.0);
}

// Test ScoreError with no matches
TEST_F(ImagePairInliersTest_79, HomographyNoMatches_79) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::HOMOGRAPHY;
  pair.H = Eigen::Matrix3d::Identity();

  Eigen::MatrixXi matches(0, 2);
  pair.matches = matches;

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  EXPECT_EQ(pair.inliers.size(), 0u);
  EXPECT_DOUBLE_EQ(score, 0.0);
}

// Test that inliers are cleared before scoring
TEST_F(ImagePairInliersTest_79, HomographyInliersClearedBeforeScoring_79) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::HOMOGRAPHY;
  pair.H = Eigen::Matrix3d::Identity();

  Eigen::MatrixXi matches(2, 2);
  matches(0, 0) = 0; matches(0, 1) = 0;
  matches(1, 0) = 1; matches(1, 1) = 1;
  pair.matches = matches;

  // Pre-populate inliers
  pair.inliers.push_back(99);
  pair.inliers.push_back(100);

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  // Old inliers should be cleared, only new ones present
  EXPECT_EQ(pair.inliers.size(), 2u);
  for (int idx : pair.inliers) {
    EXPECT_TRUE(idx == 0 || idx == 1);
  }
}

// Test with a large homography error threshold - some outliers
TEST_F(ImagePairInliersTest_79, HomographyWithOutlierMatch_79) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::HOMOGRAPHY;
  pair.H = Eigen::Matrix3d::Identity();

  // Match: feature 4 in img1 (2,2) -> feature 4 in img2 (100,100) -- large error
  Eigen::MatrixXi matches(5, 2);
  matches(0, 0) = 0; matches(0, 1) = 0;  // (0,0) -> (0,0) - inlier
  matches(1, 0) = 1; matches(1, 1) = 1;  // (1,0) -> (1,0) - inlier
  matches(2, 0) = 2; matches(2, 1) = 2;  // (0,1) -> (0,1) - inlier
  matches(3, 0) = 3; matches(3, 1) = 3;  // (1,1) -> (1,1) - inlier
  matches(4, 0) = 4; matches(4, 1) = 4;  // (2,2) -> (100,100) - outlier
  pair.matches = matches;

  options_.max_epipolar_error_H = 4.0;

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  // First 4 matches have 0 error with identity H, last one has huge error
  EXPECT_EQ(pair.inliers.size(), 4u);
  // Score should include sq_threshold for the outlier
  double sq_threshold = options_.max_epipolar_error_H * options_.max_epipolar_error_H;
  EXPECT_GE(score, sq_threshold);
}

// Test with very small threshold - potentially no inliers
TEST_F(ImagePairInliersTest_79, HomographySmallThreshold_79) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::HOMOGRAPHY;

  // Use a non-identity H that shifts points
  pair.H = Eigen::Matrix3d::Identity();
  pair.H(0, 2) = 5.0;  // shift x by 5

  Eigen::MatrixXi matches(2, 2);
  matches(0, 0) = 0; matches(0, 1) = 0;  // (0,0) -> (0,0) but H shifts by 5
  matches(1, 0) = 1; matches(1, 1) = 1;
  pair.matches = matches;

  // Very small threshold
  options_.max_epipolar_error_H = 0.01;

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  double sq_threshold = options_.max_epipolar_error_H * options_.max_epipolar_error_H;
  // With a large shift, all points should be outliers
  EXPECT_EQ(pair.inliers.size(), 0u);
  EXPECT_DOUBLE_EQ(score, 2.0 * sq_threshold);
}

// Test ScoreError returns non-negative
TEST_F(ImagePairInliersTest_79, ScoreIsNonNegative_79) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::HOMOGRAPHY;
  pair.H = Eigen::Matrix3d::Identity();

  Eigen::MatrixXi matches(3, 2);
  matches(0, 0) = 0; matches(0, 1) = 0;
  matches(1, 0) = 1; matches(1, 1) = 1;
  matches(2, 0) = 2; matches(2, 1) = 2;
  pair.matches = matches;

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  EXPECT_GE(score, 0.0);
}

// Test that inlier indices are correct
TEST_F(ImagePairInliersTest_79, HomographyInlierIndicesCorrect_79) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::HOMOGRAPHY;
  pair.H = Eigen::Matrix3d::Identity();

  Eigen::MatrixXi matches(3, 2);
  matches(0, 0) = 0; matches(0, 1) = 0;
  matches(1, 0) = 1; matches(1, 1) = 1;
  matches(2, 0) = 2; matches(2, 1) = 2;
  pair.matches = matches;

  ImagePairInliers scorer(pair, images_, options_);
  scorer.ScoreError();

  ASSERT_EQ(pair.inliers.size(), 3u);
  EXPECT_EQ(pair.inliers[0], 0);
  EXPECT_EQ(pair.inliers[1], 1);
  EXPECT_EQ(pair.inliers[2], 2);
}

// Test calling ScoreError multiple times resets inliers each time
TEST_F(ImagePairInliersTest_79, MultipleCallsResetInliers_79) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::HOMOGRAPHY;
  pair.H = Eigen::Matrix3d::Identity();

  Eigen::MatrixXi matches(2, 2);
  matches(0, 0) = 0; matches(0, 1) = 0;
  matches(1, 0) = 1; matches(1, 1) = 1;
  pair.matches = matches;

  ImagePairInliers scorer(pair, images_, options_);

  double score1 = scorer.ScoreError();
  EXPECT_EQ(pair.inliers.size(), 2u);

  double score2 = scorer.ScoreError();
  EXPECT_EQ(pair.inliers.size(), 2u);

  EXPECT_DOUBLE_EQ(score1, score2);
}

// Test with single match that is an inlier
TEST_F(ImagePairInliersTest_79, SingleMatchInlier_79) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::HOMOGRAPHY;
  pair.H = Eigen::Matrix3d::Identity();

  Eigen::MatrixXi matches(1, 2);
  matches(0, 0) = 0; matches(0, 1) = 0;
  pair.matches = matches;

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  EXPECT_EQ(pair.inliers.size(), 1u);
  EXPECT_EQ(pair.inliers[0], 0);
  EXPECT_DOUBLE_EQ(score, 0.0);
}

// Test with single match that is an outlier
TEST_F(ImagePairInliersTest_79, SingleMatchOutlier_79) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::HOMOGRAPHY;
  pair.H = Eigen::Matrix3d::Identity();

  // Match (2,2) -> (100,100), huge error with identity H
  Eigen::MatrixXi matches(1, 2);
  matches(0, 0) = 4; matches(0, 1) = 4;
  pair.matches = matches;

  options_.max_epipolar_error_H = 4.0;

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  double sq_threshold = options_.max_epipolar_error_H * options_.max_epipolar_error_H;
  EXPECT_EQ(pair.inliers.size(), 0u);
  EXPECT_DOUBLE_EQ(score, sq_threshold);
}

// Test with zero threshold
TEST_F(ImagePairInliersTest_79, ZeroThreshold_79) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::HOMOGRAPHY;
  pair.H = Eigen::Matrix3d::Identity();

  Eigen::MatrixXi matches(2, 2);
  matches(0, 0) = 0; matches(0, 1) = 0;  // perfect match, 0 error
  matches(1, 0) = 1; matches(1, 1) = 1;  // perfect match, 0 error
  pair.matches = matches;

  options_.max_epipolar_error_H = 0.0;

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  // With threshold=0, only exact matches (error < 0) count, which none can
  // since r2 >= 0 and sq_threshold = 0, condition r2 < 0 is never true
  EXPECT_EQ(pair.inliers.size(), 0u);
  EXPECT_DOUBLE_EQ(score, 0.0);
}

// Test construction with nullptr cameras
TEST_F(ImagePairInliersTest_79, ConstructionWithNullCameras_79) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::HOMOGRAPHY;
  pair.H = Eigen::Matrix3d::Identity();

  Eigen::MatrixXi matches(1, 2);
  matches(0, 0) = 0; matches(0, 1) = 0;
  pair.matches = matches;

  ImagePairInliers scorer(pair, images_, options_, nullptr);
  double score = scorer.ScoreError();

  EXPECT_GE(score, 0.0);
}

}  // namespace
}  // namespace glomap
