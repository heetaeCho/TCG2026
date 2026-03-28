// File: image_pair_inliers_test_77.cc

#include <gtest/gtest.h>
#include <unordered_map>

#include "glomap/processors/image_pair_inliers.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/camera.h"
#include "glomap/types.h"

namespace glomap {

// Helper subclass to expose the protected ScoreErrorEssential for testing.
class TestableImagePairInliers_77 : public ImagePairInliers {
 public:
  using ImagePairInliers::ImagePairInliers;
  using ImagePairInliers::ScoreErrorEssential;  // Make protected method public
};

class ImagePairInliersTest_77 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Basic option setup (we rely only on them being valid numbers)
    options_.max_epipolar_error_E = 1.0;

    // Create two cameras and insert them into the map.
    // We do not assume any particular focal length; we only need them to exist.
    Camera cam1;
    Camera cam2;
    cameras_.emplace(static_cast<camera_t>(1), cam1);
    cameras_.emplace(static_cast<camera_t>(2), cam2);

    // Create two images with IDs 1 and 2 and assign camera IDs.
    Image img1(static_cast<image_t>(1), static_cast<camera_t>(1), "img1");
    Image img2(static_cast<image_t>(2), static_cast<camera_t>(2), "img2");

    // Provide a couple of 3D undistorted feature points for each image.
    // Exact values are not important; we just need valid entries.
    img1.features_undist.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
    img1.features_undist.push_back(Eigen::Vector3d(0.1, 0.0, 1.0));

    img2.features_undist.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));
    img2.features_undist.push_back(Eigen::Vector3d(0.0, 0.1, 1.0));

    images_.emplace(static_cast<image_t>(1), img1);
    images_.emplace(static_cast<image_t>(2), img2);

    // Initialize an image pair with IDs 1 and 2 and default relative pose.
    image_pair_ = ImagePair(static_cast<image_t>(1),
                            static_cast<image_t>(2),
                            Rigid3d());

    // Provide a simple 1-row match matrix that maps feature 0 ↔ 0.
    image_pair_.matches.resize(1, 2);
    image_pair_.matches(0, 0) = 0;  // feature index in image 1
    image_pair_.matches(0, 1) = 0;  // feature index in image 2

    // Construct the processor under test.
    processor_ = std::make_unique<TestableImagePairInliers_77>(
        image_pair_, images_, options_, &cameras_);
  }

  ImagePair image_pair_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<camera_t, Camera> cameras_;
  InlierThresholdOptions options_;
  std::unique_ptr<TestableImagePairInliers_77> processor_;
};

// -----------------------------------------------------------------------------
// 1) Boundary condition: no matches → score should be 0 and inliers cleared.
// -----------------------------------------------------------------------------
TEST_F(ImagePairInliersTest_77, ReturnsZeroScoreWhenNoMatches_77) {
  // Arrange: fill inliers and then remove all matches
  image_pair_.inliers = {0, 1, 2};
  image_pair_.matches.resize(0, 2);  // zero rows

  // Act
  const double score = processor_->ScoreErrorEssential();

  // Assert
  EXPECT_DOUBLE_EQ(score, 0.0) << "With no matches, score should remain 0.";
  EXPECT_TRUE(image_pair_.inliers.empty())
      << "Existing inliers should be cleared even when there are no matches.";
}

// -----------------------------------------------------------------------------
// 2) Pre-existing inliers should be cleared before processing new matches.
// -----------------------------------------------------------------------------
TEST_F(ImagePairInliersTest_77, ClearsExistingInliersBeforeProcessing_77) {
  // Arrange: add some fake inliers before calling the method
  image_pair_.inliers = {5, 6, 7};

  // Act
  (void)processor_->ScoreErrorEssential();

  // Assert: even if new inliers are added, original ones must be gone.
  // We only check that the size is not simply the original size.
  EXPECT_NE(image_pair_.inliers.size(), static_cast<size_t>(3))
      << "Inliers from previous runs must be cleared before processing.";
  EXPECT_LE(image_pair_.inliers.size(),
            static_cast<size_t>(image_pair_.matches.rows()))
      << "Number of inliers cannot exceed number of match rows.";
}

// -----------------------------------------------------------------------------
// 3) General sanity: score should be non-negative and inlier indices, if any,
//    must be within [0, matches.rows()).
// -----------------------------------------------------------------------------
TEST_F(ImagePairInliersTest_77, ScoreAndInlierIndicesAreConsistent_77) {
  // Arrange: keep default setup from SetUp()

  // Act
  const double score = processor_->ScoreErrorEssential();

  // Assert: score should not be negative (both r2 and thresholds are squared)
  EXPECT_GE(score, 0.0) << "ScoreErrorEssential should not return negative score.";

  // All inliers indices must be valid match row indices
  const int num_rows = image_pair_.matches.rows();
  for (const int idx : image_pair_.inliers) {
    EXPECT_GE(idx, 0);
    EXPECT_LT(idx, num_rows)
        << "Inlier indices must refer to valid rows of the matches matrix.";
  }
}

}  // namespace glomap
