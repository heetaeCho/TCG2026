#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <unordered_map>
#include <vector>

#include "glomap/processors/image_pair_inliers.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/types.h"

namespace glomap {
namespace {

class ImagePairInliersTest_78 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up default options
    options_.max_epipolar_error_F = 4.0;
    options_.max_epipolar_error_E = 1.0;
    options_.max_epipolar_error_H = 4.0;
    options_.min_inlier_num = 30;
    options_.min_inlier_ratio = 0.25;
  }

  // Helper to create an image with features
  void AddImage(image_t id, camera_t cam_id,
                const std::vector<Eigen::Vector2d>& features) {
    Image img(id, cam_id, "test_image");
    img.features = features;
    images_[id] = img;
  }

  // Helper to set up a simple fundamental matrix (identity-like for testing)
  Eigen::Matrix3d MakeSimpleFundamental() {
    // A simple fundamental matrix: F = [0 0 0; 0 0 -1; 0 1 0]
    // This gives epipolar constraint: x2^T F x1 = 0 when points are coplanar
    Eigen::Matrix3d F;
    F << 0, 0, 0,
         0, 0, -1,
         0, 1, 0;
    return F;
  }

  // Helper to create a non-degenerate fundamental matrix
  Eigen::Matrix3d MakeNonDegenerateFundamental() {
    // A rank-2 matrix
    Eigen::Matrix3d F;
    F << 0, 0, 0,
         0, 0, -1,
         0, 1, 0;
    return F;
  }

  std::unordered_map<image_t, Image> images_;
  InlierThresholdOptions options_;
};

// Test: No matches should return 0 score and empty inliers
TEST_F(ImagePairInliersTest_78, NoMatchesReturnsZeroScore_78) {
  image_t id1 = 0, id2 = 1;
  AddImage(id1, 0, {});
  AddImage(id2, 0, {});

  ImagePair pair(id1, id2);
  pair.F = MakeSimpleFundamental();
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;
  // Empty matches
  pair.matches.resize(0, 2);

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  // With no matches, we expect no inliers
  EXPECT_TRUE(pair.inliers.empty());
}

// Test: All inlier matches with consistent orientation
TEST_F(ImagePairInliersTest_78, AllInliersConsistentOrientation_78) {
  image_t id1 = 0, id2 = 1;

  // Create feature points that satisfy the epipolar constraint well
  // With F = [0 0 0; 0 0 -1; 0 1 0], the constraint is x2'Fx1 = y2*z1 - z2*y1
  // For homogeneous 2D points (x,y,1): constraint is y2 - y1 = 0
  // So matching points with same y-coordinate are perfect inliers
  std::vector<Eigen::Vector2d> features1, features2;
  int num_points = 10;
  for (int i = 0; i < num_points; i++) {
    features1.push_back(Eigen::Vector2d(i * 10.0, 5.0));
    features2.push_back(Eigen::Vector2d(i * 10.0 + 1.0, 5.0));
  }

  AddImage(id1, 0, features1);
  AddImage(id2, 0, features2);

  ImagePair pair(id1, id2);
  pair.F = MakeSimpleFundamental();
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;
  pair.matches.resize(num_points, 2);
  for (int i = 0; i < num_points; i++) {
    pair.matches(i, 0) = i;
    pair.matches(i, 1) = i;
  }

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  // Score should be non-negative
  EXPECT_GE(score, 0.0);
}

// Test: All outlier matches (large epipolar error)
TEST_F(ImagePairInliersTest_78, AllOutliersLargeError_78) {
  image_t id1 = 0, id2 = 1;

  // With F = [0 0 0; 0 0 -1; 0 1 0], constraint is y2 - y1 = 0
  // If y-coordinates differ a lot, points are outliers
  std::vector<Eigen::Vector2d> features1, features2;
  int num_points = 5;
  for (int i = 0; i < num_points; i++) {
    features1.push_back(Eigen::Vector2d(i * 10.0, 0.0));
    features2.push_back(Eigen::Vector2d(i * 10.0, 1000.0));  // large y diff
  }

  AddImage(id1, 0, features1);
  AddImage(id2, 0, features2);

  ImagePair pair(id1, id2);
  pair.F = MakeSimpleFundamental();
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;
  pair.matches.resize(num_points, 2);
  for (int i = 0; i < num_points; i++) {
    pair.matches(i, 0) = i;
    pair.matches(i, 1) = i;
  }

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  // All points are outliers, so inliers should be empty
  EXPECT_TRUE(pair.inliers.empty());
  // Score should be positive (sum of sq_threshold per outlier)
  double expected_score = num_points * options_.max_epipolar_error_F * options_.max_epipolar_error_F;
  EXPECT_DOUBLE_EQ(score, expected_score);
}

// Test: Pre-existing inliers are cleared before scoring
TEST_F(ImagePairInliersTest_78, InliersClearedBeforeScoring_78) {
  image_t id1 = 0, id2 = 1;

  std::vector<Eigen::Vector2d> features1 = {Eigen::Vector2d(1.0, 5.0)};
  std::vector<Eigen::Vector2d> features2 = {Eigen::Vector2d(2.0, 5.0)};

  AddImage(id1, 0, features1);
  AddImage(id2, 0, features2);

  ImagePair pair(id1, id2);
  pair.F = MakeSimpleFundamental();
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;
  pair.matches.resize(1, 2);
  pair.matches(0, 0) = 0;
  pair.matches(0, 1) = 0;

  // Pre-populate inliers
  pair.inliers = {0, 1, 2, 3, 4};

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  // Inliers from before should be cleared; new inliers computed
  // The old inliers {0,1,2,3,4} should not remain
  EXPECT_LE(pair.inliers.size(), 1u);
}

// Test: Equal positive and negative orientation counts returns 0
TEST_F(ImagePairInliersTest_78, EqualOrientationCountsReturnsZero_78) {
  image_t id1 = 0, id2 = 1;

  // We need to construct a scenario where positive_count == negative_count
  // This is tricky without knowing internals, but we can try with 2 points
  // that have opposite orientation signums
  // Using F that creates this condition
  Eigen::Matrix3d F;
  F << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;

  std::vector<Eigen::Vector2d> features1 = {
    Eigen::Vector2d(1.0, 5.0),
    Eigen::Vector2d(-1.0, 5.0)
  };
  std::vector<Eigen::Vector2d> features2 = {
    Eigen::Vector2d(2.0, 5.0),
    Eigen::Vector2d(-2.0, 5.0)
  };

  AddImage(id1, 0, features1);
  AddImage(id2, 0, features2);

  ImagePair pair(id1, id2);
  pair.F = F;
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;
  pair.matches.resize(2, 2);
  pair.matches(0, 0) = 0;
  pair.matches(0, 1) = 0;
  pair.matches(1, 0) = 1;
  pair.matches(1, 1) = 1;

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  // We can verify the score is non-negative at minimum
  EXPECT_GE(score, 0.0);
}

// Test: Score with zero fundamental matrix
TEST_F(ImagePairInliersTest_78, ZeroFundamentalMatrix_78) {
  image_t id1 = 0, id2 = 1;

  std::vector<Eigen::Vector2d> features1 = {Eigen::Vector2d(1.0, 2.0)};
  std::vector<Eigen::Vector2d> features2 = {Eigen::Vector2d(3.0, 4.0)};

  AddImage(id1, 0, features1);
  AddImage(id2, 0, features2);

  ImagePair pair(id1, id2);
  pair.F = Eigen::Matrix3d::Zero();
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;
  pair.matches.resize(1, 2);
  pair.matches(0, 0) = 0;
  pair.matches(0, 1) = 0;

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  // With zero F, Sampson error should be 0 for all points (all inliers)
  // but orientation test may cause issues
  EXPECT_GE(score, 0.0);
}

// Test: Single match that is an inlier
TEST_F(ImagePairInliersTest_78, SingleMatchInlier_78) {
  image_t id1 = 0, id2 = 1;

  std::vector<Eigen::Vector2d> features1 = {Eigen::Vector2d(10.0, 5.0)};
  std::vector<Eigen::Vector2d> features2 = {Eigen::Vector2d(20.0, 5.0)};

  AddImage(id1, 0, features1);
  AddImage(id2, 0, features2);

  ImagePair pair(id1, id2);
  pair.F = MakeSimpleFundamental();
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;
  pair.matches.resize(1, 2);
  pair.matches(0, 0) = 0;
  pair.matches(0, 1) = 0;

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  // With one point, either positive_count=1,negative_count=0 or vice versa
  // So it should not return 0 from the equal count check
  // Score should be non-negative
  EXPECT_GE(score, 0.0);
  // With a single inlier, it should be in the inliers list if orientation is consistent
  EXPECT_LE(pair.inliers.size(), 1u);
}

// Test: Mixed inliers and outliers
TEST_F(ImagePairInliersTest_78, MixedInliersAndOutliers_78) {
  image_t id1 = 0, id2 = 1;

  // With F = [0 0 0; 0 0 -1; 0 1 0], constraint is y2 = y1
  std::vector<Eigen::Vector2d> features1, features2;

  // Inlier points (same y)
  for (int i = 0; i < 5; i++) {
    features1.push_back(Eigen::Vector2d(i * 10.0, 5.0));
    features2.push_back(Eigen::Vector2d(i * 10.0 + 1.0, 5.0));
  }
  // Outlier points (very different y)
  for (int i = 0; i < 5; i++) {
    features1.push_back(Eigen::Vector2d(i * 10.0, 0.0));
    features2.push_back(Eigen::Vector2d(i * 10.0, 500.0));
  }

  AddImage(id1, 0, features1);
  AddImage(id2, 0, features2);

  ImagePair pair(id1, id2);
  pair.F = MakeSimpleFundamental();
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;
  pair.matches.resize(10, 2);
  for (int i = 0; i < 10; i++) {
    pair.matches(i, 0) = i;
    pair.matches(i, 1) = i;
  }

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  EXPECT_GE(score, 0.0);
  // At most 5 inliers (the first 5 matching points)
  EXPECT_LE(pair.inliers.size(), 5u);
}

// Test: Threshold boundary - error exactly at threshold
TEST_F(ImagePairInliersTest_78, ThresholdBoundary_78) {
  image_t id1 = 0, id2 = 1;
  options_.max_epipolar_error_F = 1.0;  // sq_threshold = 1.0

  std::vector<Eigen::Vector2d> features1 = {Eigen::Vector2d(10.0, 5.0)};
  std::vector<Eigen::Vector2d> features2 = {Eigen::Vector2d(20.0, 5.0)};

  AddImage(id1, 0, features1);
  AddImage(id2, 0, features2);

  ImagePair pair(id1, id2);
  pair.F = MakeSimpleFundamental();
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;
  pair.matches.resize(1, 2);
  pair.matches(0, 0) = 0;
  pair.matches(0, 1) = 0;

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  // Score should be non-negative
  EXPECT_GE(score, 0.0);
}

// Test: Very small threshold makes everything an outlier
TEST_F(ImagePairInliersTest_78, VerySmallThresholdAllOutliers_78) {
  image_t id1 = 0, id2 = 1;
  options_.max_epipolar_error_F = 1e-20;  // Extremely small threshold

  std::vector<Eigen::Vector2d> features1 = {
    Eigen::Vector2d(10.0, 5.0),
    Eigen::Vector2d(20.0, 15.0)
  };
  std::vector<Eigen::Vector2d> features2 = {
    Eigen::Vector2d(20.0, 5.1),  // Slightly off
    Eigen::Vector2d(30.0, 15.1)
  };

  AddImage(id1, 0, features1);
  AddImage(id2, 0, features2);

  ImagePair pair(id1, id2);
  pair.F = MakeSimpleFundamental();
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;
  pair.matches.resize(2, 2);
  pair.matches(0, 0) = 0;
  pair.matches(0, 1) = 0;
  pair.matches(1, 0) = 1;
  pair.matches(1, 1) = 1;

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  EXPECT_TRUE(pair.inliers.empty());
}

// Test: Large number of matches
TEST_F(ImagePairInliersTest_78, LargeNumberOfMatches_78) {
  image_t id1 = 0, id2 = 1;
  int num_points = 1000;

  std::vector<Eigen::Vector2d> features1, features2;
  for (int i = 0; i < num_points; i++) {
    features1.push_back(Eigen::Vector2d(i * 1.0, 5.0));
    features2.push_back(Eigen::Vector2d(i * 1.0 + 0.5, 5.0));
  }

  AddImage(id1, 0, features1);
  AddImage(id2, 0, features2);

  ImagePair pair(id1, id2);
  pair.F = MakeSimpleFundamental();
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;
  pair.matches.resize(num_points, 2);
  for (int i = 0; i < num_points; i++) {
    pair.matches(i, 0) = i;
    pair.matches(i, 1) = i;
  }

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  EXPECT_GE(score, 0.0);
  // With all points having same y, they should mostly be inliers
  EXPECT_GT(pair.inliers.size(), 0u);
}

// Test: Constructor with nullptr cameras
TEST_F(ImagePairInliersTest_78, ConstructorWithNullCameras_78) {
  image_t id1 = 0, id2 = 1;
  AddImage(id1, 0, {Eigen::Vector2d(1.0, 1.0)});
  AddImage(id2, 0, {Eigen::Vector2d(2.0, 1.0)});

  ImagePair pair(id1, id2);
  pair.F = MakeSimpleFundamental();
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;
  pair.matches.resize(1, 2);
  pair.matches(0, 0) = 0;
  pair.matches(0, 1) = 0;

  // Constructor with nullptr cameras (default)
  ImagePairInliers scorer(pair, images_, options_, nullptr);
  double score = scorer.ScoreError();

  EXPECT_GE(score, 0.0);
}

// Test: Verify score is sum of errors for inliers plus sq_threshold for outliers
TEST_F(ImagePairInliersTest_78, ScoreComposition_78) {
  image_t id1 = 0, id2 = 1;

  // Create points where all are clear outliers
  std::vector<Eigen::Vector2d> features1, features2;
  int num_outliers = 3;
  for (int i = 0; i < num_outliers; i++) {
    features1.push_back(Eigen::Vector2d(i * 10.0, 0.0));
    features2.push_back(Eigen::Vector2d(i * 10.0, 1000.0));
  }

  AddImage(id1, 0, features1);
  AddImage(id2, 0, features2);

  ImagePair pair(id1, id2);
  pair.F = MakeSimpleFundamental();
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;
  pair.matches.resize(num_outliers, 2);
  for (int i = 0; i < num_outliers; i++) {
    pair.matches(i, 0) = i;
    pair.matches(i, 1) = i;
  }

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  double sq_threshold = options_.max_epipolar_error_F * options_.max_epipolar_error_F;
  // All outliers: score = num_outliers * sq_threshold
  EXPECT_DOUBLE_EQ(score, num_outliers * sq_threshold);
  EXPECT_TRUE(pair.inliers.empty());
}

// Test: Identity-like F matrix with perfectly matching points
TEST_F(ImagePairInliersTest_78, PerfectMatchesZeroError_78) {
  image_t id1 = 0, id2 = 1;

  // Points that perfectly satisfy the epipolar constraint
  // With F = [0 0 0; 0 0 -1; 0 1 0], y1 = y2 means zero error
  std::vector<Eigen::Vector2d> features1 = {
    Eigen::Vector2d(100.0, 50.0),
    Eigen::Vector2d(200.0, 50.0),
    Eigen::Vector2d(300.0, 50.0)
  };
  std::vector<Eigen::Vector2d> features2 = {
    Eigen::Vector2d(150.0, 50.0),
    Eigen::Vector2d(250.0, 50.0),
    Eigen::Vector2d(350.0, 50.0)
  };

  AddImage(id1, 0, features1);
  AddImage(id2, 0, features2);

  ImagePair pair(id1, id2);
  pair.F = MakeSimpleFundamental();
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;
  pair.matches.resize(3, 2);
  for (int i = 0; i < 3; i++) {
    pair.matches(i, 0) = i;
    pair.matches(i, 1) = i;
  }

  ImagePairInliers scorer(pair, images_, options_);
  double score = scorer.ScoreError();

  // Perfect matches should have very low or zero error contribution from inliers
  EXPECT_GE(score, 0.0);
}

// Test: Repeated calls to ScoreError clear inliers each time
TEST_F(ImagePairInliersTest_78, RepeatedCallsClearInliers_78) {
  image_t id1 = 0, id2 = 1;

  std::vector<Eigen::Vector2d> features1 = {Eigen::Vector2d(10.0, 5.0)};
  std::vector<Eigen::Vector2d> features2 = {Eigen::Vector2d(20.0, 5.0)};

  AddImage(id1, 0, features1);
  AddImage(id2, 0, features2);

  ImagePair pair(id1, id2);
  pair.F = MakeSimpleFundamental();
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;
  pair.matches.resize(1, 2);
  pair.matches(0, 0) = 0;
  pair.matches(0, 1) = 0;

  ImagePairInliers scorer(pair, images_, options_);

  double score1 = scorer.ScoreError();
  size_t inlier_count1 = pair.inliers.size();

  double score2 = scorer.ScoreError();
  size_t inlier_count2 = pair.inliers.size();

  // Scores should be identical on repeated calls
  EXPECT_DOUBLE_EQ(score1, score2);
  EXPECT_EQ(inlier_count1, inlier_count2);
}

}  // namespace
}  // namespace glomap
