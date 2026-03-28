// File: image_pair_inliers_score_error_homography_test_79.cc

#include <gtest/gtest.h>
#include <unordered_map>

#include <Eigen/Core>

#include "glomap/processors/image_pair_inliers.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/image.h"
#include "glomap/types.h"

namespace {

// Helper subclass to access the protected ScoreErrorHomography method.
class TestableImagePairInliers_79 : public glomap::ImagePairInliers {
public:
  using glomap::ImagePairInliers::ImagePairInliers;

  double CallScoreErrorHomography_79() {
    return ScoreErrorHomography();
  }
};

// Common fixture for ImagePairInliers tests.
class ImagePairInliersTest_79 : public ::testing::Test {
protected:
  ImagePairInliersTest_79()
      : image_pair(static_cast<glomap::image_t>(1),
                   static_cast<glomap::image_t>(2)) {}

  void SetUp() override {
    // Default option values; tests may override specific fields.
    options = glomap::InlierThresholdOptions();

    // Initialize homography to identity.
    image_pair.H = Eigen::Matrix3d::Identity();

    // Prepare minimal image map with two images.
    glomap::Image img1(static_cast<glomap::image_t>(1),
                       static_cast<glomap::camera_t>(1),
                       "img1");
    glomap::Image img2(static_cast<glomap::image_t>(2),
                       static_cast<glomap::camera_t>(1),
                       "img2");

    images.clear();
    images.emplace(img1.image_id, img1);
    images.emplace(img2.image_id, img2);
  }

  glomap::InlierThresholdOptions options;
  glomap::ImagePair image_pair;
  std::unordered_map<glomap::image_t, glomap::Image> images;
};

// -----------------------------------------------------------------------------
// Test: Existing inliers are cleared when there are no matches.
// Also verifies that the score is zero when no matches are processed.
// -----------------------------------------------------------------------------
TEST_F(ImagePairInliersTest_79, ClearsExistingInliersWhenNoMatches_79) {
  // Arrange
  image_pair.inliers = {1, 2, 3};  // Pre-existing inliers

  // Zero-row matches matrix => loop body is never executed.
  image_pair.matches = Eigen::MatrixXi(0, 2);

  TestableImagePairInliers_79 inliers_processor(
      image_pair, images, options, nullptr);

  // Act
  const double score = inliers_processor.CallScoreErrorHomography_79();

  // Assert
  EXPECT_TRUE(image_pair.inliers.empty())
      << "Existing inliers should be cleared before processing matches.";
  EXPECT_DOUBLE_EQ(score, 0.0)
      << "Score should remain zero when there are no matches.";
}

// -----------------------------------------------------------------------------
// Test: Match with very small homography error (expected below threshold)
// becomes an inlier and contributes its error to the score.
// Also verifies that previous inliers are cleared.
// -----------------------------------------------------------------------------
TEST_F(ImagePairInliersTest_79, AddsInlierWhenErrorBelowThreshold_79) {
  // Arrange
  // Use a positive threshold; with identity H and identical points,
  // the homography error is expected to be zero and thus below threshold.
  options.max_epipolar_error_H = 1.0;

  // Features: same 2D point in both images.
  images.at(static_cast<glomap::image_t>(1)).features.push_back(
      Eigen::Vector2d(0.0, 0.0));
  images.at(static_cast<glomap::image_t>(2)).features.push_back(
      Eigen::Vector2d(0.0, 0.0));

  // Single match referencing feature index 0 in both images.
  Eigen::MatrixXi matches(1, 2);
  matches(0, 0) = 0;
  matches(0, 1) = 0;
  image_pair.matches = matches;

  // Pre-fill inliers to ensure they are cleared.
  image_pair.inliers = {42, 99};

  TestableImagePairInliers_79 inliers_processor(
      image_pair, images, options, nullptr);

  // Act
  const double score = inliers_processor.CallScoreErrorHomography_79();

  // Assert
  ASSERT_EQ(image_pair.inliers.size(), 1u)
      << "Exactly one inlier should be recorded for a single good match.";
  EXPECT_EQ(image_pair.inliers[0], 0)
      << "The inlier index should correspond to the row index of the match.";
  EXPECT_NEAR(score, 0.0, 1e-12)
      << "With identical points under identity homography, the error score "
         "is expected to be (close to) zero.";
}

// -----------------------------------------------------------------------------
// Test: Match with large homography error (expected above threshold)
// should NOT be added to inliers, and the score should be equal to
// the squared threshold for that match.
// -----------------------------------------------------------------------------
TEST_F(ImagePairInliersTest_79, NoInlierAndSqThresholdScoreWhenErrorAboveThreshold_79) {
  // Arrange
  // Use a very small threshold, and choose points that are far apart so
  // the error should be larger than the threshold.
  options.max_epipolar_error_H = 0.001;
  const double sq_threshold = options.max_epipolar_error_H *
                              options.max_epipolar_error_H;

  // Features: points far apart in the second image.
  images.at(static_cast<glomap::image_t>(1)).features.push_back(
      Eigen::Vector2d(0.0, 0.0));
  images.at(static_cast<glomap::image_t>(2)).features.push_back(
      Eigen::Vector2d(1000.0, 0.0));  // Large displacement

  // Single match referencing feature index 0 in both images.
  Eigen::MatrixXi matches(1, 2);
  matches(0, 0) = 0;
  matches(0, 1) = 0;
  image_pair.matches = matches;

  TestableImagePairInliers_79 inliers_processor(
      image_pair, images, options, nullptr);

  // Act
  const double score = inliers_processor.CallScoreErrorHomography_79();

  // Assert
  EXPECT_TRUE(image_pair.inliers.empty())
      << "No inliers should be added when the error exceeds the threshold.";
  EXPECT_NEAR(score, sq_threshold, 1e-9)
      << "For a single outlier match, the score should equal the squared "
         "threshold.";
}

// -----------------------------------------------------------------------------
// Test: Mixed inlier/outlier scenario with two matches.
// Verifies that only the low-error match is recorded as an inlier while the
// other contributes squared threshold to the score.
// -----------------------------------------------------------------------------
TEST_F(ImagePairInliersTest_79, MixedInliersAndOutliers_79) {
  // Arrange
  options.max_epipolar_error_H = 1.0;
  const double sq_threshold = options.max_epipolar_error_H *
                              options.max_epipolar_error_H;

  // Prepare two features per image:
  //  - index 0: identical points -> expected low error (inlier)
  //  - index 1: far apart         -> expected large error (outlier)
  auto& img1 = images.at(static_cast<glomap::image_t>(1));
  auto& img2 = images.at(static_cast<glomap::image_t>(2));

  img1.features.push_back(Eigen::Vector2d(0.0, 0.0));     // index 0
  img2.features.push_back(Eigen::Vector2d(0.0, 0.0));     // index 0

  img1.features.push_back(Eigen::Vector2d(0.0, 0.0));     // index 1
  img2.features.push_back(Eigen::Vector2d(1000.0, 0.0));  // index 1

  Eigen::MatrixXi matches(2, 2);
  matches(0, 0) = 0;  matches(0, 1) = 0;  // expected inlier
  matches(1, 0) = 1;  matches(1, 1) = 1;  // expected outlier
  image_pair.matches = matches;

  TestableImagePairInliers_79 inliers_processor(
      image_pair, images, options, nullptr);

  // Act
  const double score = inliers_processor.CallScoreErrorHomography_79();

  // Assert
  ASSERT_EQ(image_pair.inliers.size(), 1u)
      << "Exactly one inlier should be recorded when only one match "
         "has error below threshold.";
  EXPECT_EQ(image_pair.inliers[0], 0)
      << "Only the first match (row 0) should be considered an inlier.";

  // The score is the sum of r2 for inliers and sq_threshold for outliers.
  // For the first match we expect very small error (near zero), so
  // the total score should be close to sq_threshold from the outlier.
  EXPECT_GT(score, 0.0);
  EXPECT_NEAR(score, sq_threshold, 1e-3)
      << "The total score should be dominated by the squared threshold "
         "contribution of the outlier match.";
}

}  // namespace
