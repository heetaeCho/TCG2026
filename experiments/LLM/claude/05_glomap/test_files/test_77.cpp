#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/processors/image_pair_inliers.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/image.h"
#include "glomap/scene/camera.h"
#include "glomap/types.h"

#include <colmap/scene/two_view_geometry.h>
#include <colmap/geometry/rigid3.h>
#include <unordered_map>
#include <Eigen/Core>

namespace glomap {
namespace {

class ImagePairInliersTest_77 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up default cameras
    colmap::Camera colmap_cam;
    colmap_cam.SetCameraId(1);
    colmap_cam.SetModelIdFromName("SIMPLE_PINHOLE");
    colmap_cam.SetWidth(640);
    colmap_cam.SetHeight(480);
    colmap_cam.SetParams({500.0, 320.0, 240.0});  // focal, cx, cy

    Camera cam(colmap_cam);
    cameras_[1] = cam;

    colmap::Camera colmap_cam2;
    colmap_cam2.SetCameraId(2);
    colmap_cam2.SetModelIdFromName("SIMPLE_PINHOLE");
    colmap_cam2.SetWidth(640);
    colmap_cam2.SetHeight(480);
    colmap_cam2.SetParams({500.0, 320.0, 240.0});

    Camera cam2(colmap_cam2);
    cameras_[2] = cam2;

    // Set up images
    Image img1(0, 1, "img1.jpg");
    Image img2(1, 2, "img2.jpg");

    images_[0] = img1;
    images_[1] = img2;

    // Default options
    options_.max_epipolar_error_E = 1.0;
    options_.max_epipolar_error_F = 4.0;
    options_.max_epipolar_error_H = 4.0;
    options_.max_reprojection_error = 0.01;
    options_.min_triangulation_angle = 1.0;
    options_.max_angle_error = 1.0;
    options_.min_inlier_num = 30;
    options_.min_inlier_ratio = 0.25;
    options_.max_rotation_error = 10.0;
  }

  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<image_t, Image> images_;
  InlierThresholdOptions options_;
};

// Test with no matches - score should be 0
TEST_F(ImagePairInliersTest_77, NoMatchesReturnsZeroScore_77) {
  Rigid3d identity;
  ImagePair pair(0, 1, identity);
  pair.matches.resize(0, 2);
  pair.config = colmap::TwoViewGeometry::CALIBRATED;

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();

  EXPECT_GE(score, 0.0);
  EXPECT_TRUE(pair.inliers.empty());
}

// Test that inliers are cleared before scoring
TEST_F(ImagePairInliersTest_77, InliersClearedBeforeScoring_77) {
  Rigid3d identity;
  ImagePair pair(0, 1, identity);
  pair.matches.resize(0, 2);
  pair.config = colmap::TwoViewGeometry::CALIBRATED;

  // Pre-populate inliers
  pair.inliers.push_back(0);
  pair.inliers.push_back(1);
  ASSERT_EQ(pair.inliers.size(), 2);

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  scorer.ScoreError();

  // Inliers should be cleared (or repopulated) after scoring
  // With no matches, should be empty
  EXPECT_TRUE(pair.inliers.empty());
}

// Test with identity motion and matching features on the epipolar line
TEST_F(ImagePairInliersTest_77, IdentityMotionNoInliers_77) {
  // Identity motion has zero translation which makes essential matrix degenerate
  Rigid3d identity;
  ImagePair pair(0, 1, identity);

  // Add some dummy features
  images_[0].features_undist.push_back(Eigen::Vector3d(0.1, 0.2, 1.0).normalized());
  images_[1].features_undist.push_back(Eigen::Vector3d(0.1, 0.2, 1.0).normalized());

  pair.matches.resize(1, 2);
  pair.matches(0, 0) = 0;
  pair.matches(0, 1) = 0;
  pair.config = colmap::TwoViewGeometry::CALIBRATED;

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();

  // Score should be non-negative
  EXPECT_GE(score, 0.0);
}

// Test with a valid essential matrix configuration
TEST_F(ImagePairInliersTest_77, ValidEssentialMatrixConfig_77) {
  // Create a non-trivial motion
  Eigen::Quaterniond q(Eigen::AngleAxisd(0.1, Eigen::Vector3d::UnitY()));
  Eigen::Vector3d t(0.5, 0.0, 0.0);
  Rigid3d motion;
  motion.rotation = q;
  motion.translation = t;

  ImagePair pair(0, 1, motion);
  pair.config = colmap::TwoViewGeometry::CALIBRATED;

  // Add features that should be inliers (point at sufficient depth)
  Eigen::Vector3d pt1 = Eigen::Vector3d(0.0, 0.0, 1.0).normalized();
  Eigen::Vector3d pt2 = Eigen::Vector3d(-0.05, 0.0, 1.0).normalized();

  images_[0].features_undist.push_back(pt1);
  images_[1].features_undist.push_back(pt2);

  pair.matches.resize(1, 2);
  pair.matches(0, 0) = 0;
  pair.matches(0, 1) = 0;

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();

  EXPECT_GE(score, 0.0);
}

// Test with multiple matches
TEST_F(ImagePairInliersTest_77, MultipleMatches_77) {
  Eigen::Quaterniond q(Eigen::AngleAxisd(0.05, Eigen::Vector3d::UnitY()));
  Eigen::Vector3d t(1.0, 0.0, 0.0);
  Rigid3d motion;
  motion.rotation = q;
  motion.translation = t;

  ImagePair pair(0, 1, motion);
  pair.config = colmap::TwoViewGeometry::CALIBRATED;

  // Add multiple features
  for (int i = 0; i < 5; ++i) {
    double x = 0.1 * (i - 2);
    Eigen::Vector3d pt1 = Eigen::Vector3d(x, 0.0, 1.0).normalized();
    Eigen::Vector3d pt2 = Eigen::Vector3d(x - 0.1, 0.0, 1.0).normalized();
    images_[0].features_undist.push_back(pt1);
    images_[1].features_undist.push_back(pt2);
  }

  pair.matches.resize(5, 2);
  for (int i = 0; i < 5; ++i) {
    pair.matches(i, 0) = i;
    pair.matches(i, 1) = i;
  }

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();

  EXPECT_GE(score, 0.0);
  // Inliers count should be <= total matches
  EXPECT_LE(static_cast<int>(pair.inliers.size()), 5);
}

// Test with UNCALIBRATED config (should use fundamental matrix scoring)
TEST_F(ImagePairInliersTest_77, FundamentalMatrixConfig_77) {
  Rigid3d identity;
  ImagePair pair(0, 1, identity);
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;
  pair.F = Eigen::Matrix3d::Identity();

  images_[0].features_undist.push_back(Eigen::Vector3d(0.1, 0.1, 1.0));
  images_[1].features_undist.push_back(Eigen::Vector3d(0.1, 0.1, 1.0));

  pair.matches.resize(1, 2);
  pair.matches(0, 0) = 0;
  pair.matches(0, 1) = 0;

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();

  EXPECT_GE(score, 0.0);
}

// Test with PLANAR config (should use homography scoring)
TEST_F(ImagePairInliersTest_77, HomographyConfig_77) {
  Rigid3d identity;
  ImagePair pair(0, 1, identity);
  pair.config = colmap::TwoViewGeometry::PLANAR;
  pair.H = Eigen::Matrix3d::Identity();

  images_[0].features_undist.push_back(Eigen::Vector3d(0.1, 0.1, 1.0));
  images_[1].features_undist.push_back(Eigen::Vector3d(0.1, 0.1, 1.0));

  pair.matches.resize(1, 2);
  pair.matches(0, 0) = 0;
  pair.matches(0, 1) = 0;

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();

  EXPECT_GE(score, 0.0);
}

// Test score increases with more outlier matches
TEST_F(ImagePairInliersTest_77, ScoreIncreasesWithOutliers_77) {
  Eigen::Quaterniond q(Eigen::AngleAxisd(0.1, Eigen::Vector3d::UnitY()));
  Eigen::Vector3d t(1.0, 0.0, 0.0);
  Rigid3d motion;
  motion.rotation = q;
  motion.translation = t;

  // First pair with 1 match
  ImagePair pair1(0, 1, motion);
  pair1.config = colmap::TwoViewGeometry::CALIBRATED;

  // Add a feature that is likely an outlier (very different directions)
  images_[0].features_undist.push_back(Eigen::Vector3d(1.0, 0.0, 0.1).normalized());
  images_[1].features_undist.push_back(Eigen::Vector3d(-1.0, 0.0, 0.1).normalized());

  pair1.matches.resize(1, 2);
  pair1.matches(0, 0) = 0;
  pair1.matches(0, 1) = 0;

  ImagePairInliers scorer1(pair1, images_, options_, &cameras_);
  double score1 = scorer1.ScoreError();

  // Add more outlier features
  images_[0].features_undist.push_back(Eigen::Vector3d(0.0, 1.0, 0.1).normalized());
  images_[1].features_undist.push_back(Eigen::Vector3d(0.0, -1.0, 0.1).normalized());

  ImagePair pair2(0, 1, motion);
  pair2.config = colmap::TwoViewGeometry::CALIBRATED;
  pair2.matches.resize(2, 2);
  pair2.matches(0, 0) = 0;
  pair2.matches(0, 1) = 0;
  pair2.matches(1, 0) = 1;
  pair2.matches(1, 1) = 1;

  ImagePairInliers scorer2(pair2, images_, options_, &cameras_);
  double score2 = scorer2.ScoreError();

  // More matches should mean score >= previous score
  EXPECT_GE(score2, score1);
}

// Test that inlier indices are valid
TEST_F(ImagePairInliersTest_77, InlierIndicesAreValid_77) {
  Eigen::Quaterniond q(Eigen::AngleAxisd(0.05, Eigen::Vector3d::UnitY()));
  Eigen::Vector3d t(1.0, 0.0, 0.0);
  Rigid3d motion;
  motion.rotation = q;
  motion.translation = t;

  ImagePair pair(0, 1, motion);
  pair.config = colmap::TwoViewGeometry::CALIBRATED;

  int num_matches = 10;
  for (int i = 0; i < num_matches; ++i) {
    double x = 0.05 * (i - 5);
    images_[0].features_undist.push_back(Eigen::Vector3d(x, 0.0, 1.0).normalized());
    images_[1].features_undist.push_back(Eigen::Vector3d(x - 0.05, 0.0, 1.0).normalized());
  }

  pair.matches.resize(num_matches, 2);
  for (int i = 0; i < num_matches; ++i) {
    pair.matches(i, 0) = i;
    pair.matches(i, 1) = i;
  }

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  scorer.ScoreError();

  // All inlier indices should be in [0, num_matches)
  for (int idx : pair.inliers) {
    EXPECT_GE(idx, 0);
    EXPECT_LT(idx, num_matches);
  }
}

// Test with nullptr cameras (essential matrix path might not need cameras)
TEST_F(ImagePairInliersTest_77, NullCamerasPointer_77) {
  Rigid3d identity;
  ImagePair pair(0, 1, identity);
  pair.matches.resize(0, 2);
  pair.config = colmap::TwoViewGeometry::CALIBRATED;

  // Passing nullptr for cameras - may or may not crash depending on config
  // With no matches, should be safe
  ImagePairInliers scorer(pair, images_, options_, nullptr);
  // This test is about construction succeeding
  // ScoreError with no matches should be safe even without cameras
  double score = scorer.ScoreError();
  EXPECT_GE(score, 0.0);
}

// Test with very large epipolar error threshold (all should be inliers if cheirality passes)
TEST_F(ImagePairInliersTest_77, LargeThresholdMoreInliers_77) {
  Eigen::Quaterniond q(Eigen::AngleAxisd(0.05, Eigen::Vector3d::UnitY()));
  Eigen::Vector3d t(1.0, 0.0, 0.0);
  Rigid3d motion;
  motion.rotation = q;
  motion.translation = t;

  // Setup features
  images_[0].features_undist.clear();
  images_[1].features_undist.clear();
  for (int i = 0; i < 5; ++i) {
    double x = 0.02 * (i - 2);
    images_[0].features_undist.push_back(Eigen::Vector3d(x, 0.0, 1.0).normalized());
    images_[1].features_undist.push_back(Eigen::Vector3d(x - 0.02, 0.0, 1.0).normalized());
  }

  // Small threshold
  InlierThresholdOptions strict_options = options_;
  strict_options.max_epipolar_error_E = 0.001;

  ImagePair pair_strict(0, 1, motion);
  pair_strict.config = colmap::TwoViewGeometry::CALIBRATED;
  pair_strict.matches.resize(5, 2);
  for (int i = 0; i < 5; ++i) {
    pair_strict.matches(i, 0) = i;
    pair_strict.matches(i, 1) = i;
  }

  ImagePairInliers scorer_strict(pair_strict, images_, strict_options, &cameras_);
  scorer_strict.ScoreError();
  size_t strict_inliers = pair_strict.inliers.size();

  // Large threshold
  InlierThresholdOptions loose_options = options_;
  loose_options.max_epipolar_error_E = 100.0;

  ImagePair pair_loose(0, 1, motion);
  pair_loose.config = colmap::TwoViewGeometry::CALIBRATED;
  pair_loose.matches.resize(5, 2);
  for (int i = 0; i < 5; ++i) {
    pair_loose.matches(i, 0) = i;
    pair_loose.matches(i, 1) = i;
  }

  ImagePairInliers scorer_loose(pair_loose, images_, loose_options, &cameras_);
  scorer_loose.ScoreError();
  size_t loose_inliers = pair_loose.inliers.size();

  // Looser threshold should have >= inliers than strict
  EXPECT_GE(loose_inliers, strict_inliers);
}

// Test that score is non-negative regardless of configuration
TEST_F(ImagePairInliersTest_77, ScoreIsNonNegative_77) {
  Eigen::Quaterniond q(Eigen::AngleAxisd(0.3, Eigen::Vector3d::UnitZ()));
  Eigen::Vector3d t(0.0, 1.0, 0.5);
  Rigid3d motion;
  motion.rotation = q;
  motion.translation = t;

  ImagePair pair(0, 1, motion);
  pair.config = colmap::TwoViewGeometry::CALIBRATED;

  images_[0].features_undist.push_back(Eigen::Vector3d(0.5, 0.3, 1.0).normalized());
  images_[0].features_undist.push_back(Eigen::Vector3d(-0.2, 0.1, 1.0).normalized());
  images_[1].features_undist.push_back(Eigen::Vector3d(0.4, 0.2, 1.0).normalized());
  images_[1].features_undist.push_back(Eigen::Vector3d(-0.3, 0.15, 1.0).normalized());

  pair.matches.resize(2, 2);
  pair.matches(0, 0) = 0;
  pair.matches(0, 1) = 0;
  pair.matches(1, 0) = 1;
  pair.matches(1, 1) = 1;

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();

  EXPECT_GE(score, 0.0);
}

// Test with same camera for both images
TEST_F(ImagePairInliersTest_77, SameCameraForBothImages_77) {
  // Both images use camera 1
  images_[1] = Image(1, 1, "img2.jpg");

  Eigen::Quaterniond q(Eigen::AngleAxisd(0.1, Eigen::Vector3d::UnitY()));
  Eigen::Vector3d t(1.0, 0.0, 0.0);
  Rigid3d motion;
  motion.rotation = q;
  motion.translation = t;

  ImagePair pair(0, 1, motion);
  pair.config = colmap::TwoViewGeometry::CALIBRATED;

  images_[0].features_undist.push_back(Eigen::Vector3d(0.0, 0.0, 1.0).normalized());
  images_[1].features_undist.push_back(Eigen::Vector3d(-0.1, 0.0, 1.0).normalized());

  pair.matches.resize(1, 2);
  pair.matches(0, 0) = 0;
  pair.matches(0, 1) = 0;

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();

  EXPECT_GE(score, 0.0);
}

}  // namespace
}  // namespace glomap
