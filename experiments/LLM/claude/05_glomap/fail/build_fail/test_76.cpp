#include <gtest/gtest.h>
#include <unordered_map>
#include <Eigen/Core>

#include "glomap/processors/image_pair_inliers.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/types.h"
#include "glomap/types.h"

#include <colmap/scene/two_view_geometry.h>
#include <colmap/util/types.h>

namespace glomap {
namespace {

class ImagePairInliersTest_76 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up two images with valid IDs
    image_t id1 = 0;
    image_t id2 = 1;

    Image img1;
    Image img2;
    images_[id1] = img1;
    images_[id2] = img2;

    // Set up cameras
    Camera cam1;
    Camera cam2;
    cameras_[0] = cam1;
    cameras_[1] = cam2;
  }

  std::unordered_map<image_t, Image> images_;
  std::unordered_map<camera_t, Camera> cameras_;
  InlierThresholdOptions options_;
};

// Test that ScoreError returns 0 for UNDEFINED config
TEST_F(ImagePairInliersTest_76, ScoreErrorUndefinedConfig_76) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::UNDEFINED;

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();
  EXPECT_DOUBLE_EQ(score, 0.0);
}

// Test that ScoreError dispatches to homography scoring for PLANAR config
TEST_F(ImagePairInliersTest_76, ScoreErrorPlanarConfig_76) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::PLANAR;

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();
  // We just verify it returns a finite value (dispatched to homography scorer)
  EXPECT_TRUE(std::isfinite(score));
}

// Test that ScoreError dispatches to homography scoring for PANORAMIC config
TEST_F(ImagePairInliersTest_76, ScoreErrorPanoramicConfig_76) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::PANORAMIC;

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();
  EXPECT_TRUE(std::isfinite(score));
}

// Test that ScoreError dispatches to homography scoring for PLANAR_OR_PANORAMIC config
TEST_F(ImagePairInliersTest_76, ScoreErrorPlanarOrPanoramicConfig_76) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::PLANAR_OR_PANORAMIC;

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();
  EXPECT_TRUE(std::isfinite(score));
}

// Test that ScoreError dispatches to fundamental scoring for UNCALIBRATED config
TEST_F(ImagePairInliersTest_76, ScoreErrorUncalibratedConfig_76) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();
  EXPECT_TRUE(std::isfinite(score));
}

// Test that ScoreError dispatches to essential scoring for CALIBRATED config
TEST_F(ImagePairInliersTest_76, ScoreErrorCalibratedConfig_76) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::CALIBRATED;

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();
  EXPECT_TRUE(std::isfinite(score));
}

// Test ScoreError with nullptr cameras (default parameter)
TEST_F(ImagePairInliersTest_76, ScoreErrorNullCameras_76) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::CALIBRATED;

  ImagePairInliers scorer(pair, images_, options_, nullptr);
  double score = scorer.ScoreError();
  EXPECT_TRUE(std::isfinite(score));
}

// Test that ScoreError returns 0 for an unrecognized/degenerate config
TEST_F(ImagePairInliersTest_76, ScoreErrorDegenerateConfig_76) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::DEGENERATE;

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();
  EXPECT_DOUBLE_EQ(score, 0.0);
}

// Test with default constructed ImagePair (invalid IDs)
TEST_F(ImagePairInliersTest_76, ScoreErrorDefaultImagePair_76) {
  ImagePair pair;
  // Default config is UNDEFINED
  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();
  EXPECT_DOUBLE_EQ(score, 0.0);
}

// Test that PLANAR and PANORAMIC configs both go through homography path
// and produce consistent type of results (both finite, non-negative or similar)
TEST_F(ImagePairInliersTest_76, ScoreErrorHomographyPathConsistency_76) {
  ImagePair pair1(0, 1);
  pair1.config = colmap::TwoViewGeometry::PLANAR;
  pair1.H = Eigen::Matrix3d::Identity();

  ImagePair pair2(0, 1);
  pair2.config = colmap::TwoViewGeometry::PANORAMIC;
  pair2.H = Eigen::Matrix3d::Identity();

  ImagePairInliers scorer1(pair1, images_, options_, &cameras_);
  ImagePairInliers scorer2(pair2, images_, options_, &cameras_);

  double score1 = scorer1.ScoreError();
  double score2 = scorer2.ScoreError();

  // Both should use the same homography scoring path with same data
  EXPECT_DOUBLE_EQ(score1, score2);
}

// Test with identity essential matrix for CALIBRATED config
TEST_F(ImagePairInliersTest_76, ScoreErrorCalibratedIdentityE_76) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::CALIBRATED;
  pair.E = Eigen::Matrix3d::Identity();

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();
  EXPECT_TRUE(std::isfinite(score));
}

// Test with identity fundamental matrix for UNCALIBRATED config
TEST_F(ImagePairInliersTest_76, ScoreErrorUncalibratedIdentityF_76) {
  ImagePair pair(0, 1);
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;
  pair.F = Eigen::Matrix3d::Identity();

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();
  EXPECT_TRUE(std::isfinite(score));
}

// Test with a large unrecognized config value returns 0
TEST_F(ImagePairInliersTest_76, ScoreErrorLargeUnknownConfig_76) {
  ImagePair pair(0, 1);
  pair.config = 9999;

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();
  EXPECT_DOUBLE_EQ(score, 0.0);
}

// Test with negative unrecognized config value returns 0
TEST_F(ImagePairInliersTest_76, ScoreErrorNegativeUnknownConfig_76) {
  ImagePair pair(0, 1);
  pair.config = -100;

  ImagePairInliers scorer(pair, images_, options_, &cameras_);
  double score = scorer.ScoreError();
  EXPECT_DOUBLE_EQ(score, 0.0);
}

}  // namespace
}  // namespace glomap
