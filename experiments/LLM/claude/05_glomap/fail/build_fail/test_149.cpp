#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/processors/image_pair_inliers.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/scene/view_graph.h"
#include "glomap/types.h"

#include <colmap/scene/camera.h>
#include <colmap/scene/two_view_geometry.h>
#include <colmap/util/types.h>

#include <Eigen/Core>
#include <unordered_map>

namespace glomap {
namespace {

class ImagePairsInlierCountTest_149 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Setup default cameras
    Camera cam1;
    cam1.camera_id = 0;
    cam1.model_id = colmap::SimplePinholeCameraModel::model_id;
    cam1.width = 640;
    cam1.height = 480;
    cam1.params = {500.0, 320.0, 240.0};
    cameras_[0] = cam1;

    Camera cam2;
    cam2.camera_id = 1;
    cam2.model_id = colmap::SimplePinholeCameraModel::model_id;
    cam2.width = 640;
    cam2.height = 480;
    cam2.params = {500.0, 320.0, 240.0};
    cameras_[1] = cam2;

    // Setup default images
    Image img1;
    img1.image_id = 0;
    img1.camera_id = 0;
    img1.is_registered = true;
    // Add some 2D features
    Eigen::Vector2d pt(100.0, 100.0);
    img1.features.push_back(pt);
    img1.features.push_back(Eigen::Vector2d(200.0, 200.0));
    img1.features.push_back(Eigen::Vector2d(300.0, 300.0));
    images_[0] = img1;

    Image img2;
    img2.image_id = 1;
    img2.camera_id = 1;
    img2.is_registered = true;
    img2.features.push_back(Eigen::Vector2d(110.0, 110.0));
    img2.features.push_back(Eigen::Vector2d(210.0, 210.0));
    img2.features.push_back(Eigen::Vector2d(310.0, 310.0));
    images_[1] = img2;

    options_.max_angle_error = 1.0;
    options_.max_reprojection_error = 0.01;
    options_.min_triangulation_angle = 1.0;
    options_.max_epipolar_error_E = 1.0;
    options_.max_epipolar_error_F = 4.0;
    options_.max_epipolar_error_H = 4.0;
    options_.min_inlier_num = 30;
    options_.min_inlier_ratio = 0.25;
    options_.max_rotation_error = 10.0;
  }

  ViewGraph view_graph_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<image_t, Image> images_;
  InlierThresholdOptions options_;
};

// Test with empty view graph - no image pairs
TEST_F(ImagePairsInlierCountTest_149, EmptyViewGraph_149) {
  EXPECT_NO_THROW(
      ImagePairsInlierCount(view_graph_, cameras_, images_, options_, false));
  EXPECT_TRUE(view_graph_.image_pairs.empty());
}

// Test that invalid image pairs have their inliers cleared but no scoring
TEST_F(ImagePairsInlierCountTest_149, InvalidImagePairCleared_149) {
  ImagePair pair(0, 1);
  pair.is_valid = false;
  pair.inliers = {0, 1, 2};  // Pre-existing inliers

  image_pair_t pair_id = pair.pair_id;
  view_graph_.image_pairs.emplace(pair_id, pair);

  ImagePairsInlierCount(view_graph_, cameras_, images_, options_, true);

  // Inliers should be cleared because clean_inliers is true
  EXPECT_TRUE(view_graph_.image_pairs.at(pair_id).inliers.empty());
}

// Test with clean_inliers=false and existing inliers - should skip
TEST_F(ImagePairsInlierCountTest_149, SkipExistingInliersWhenNotCleaning_149) {
  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.inliers = {0, 1, 2};  // Pre-existing inliers

  image_pair_t pair_id = pair.pair_id;
  view_graph_.image_pairs.emplace(pair_id, pair);

  ImagePairsInlierCount(view_graph_, cameras_, images_, options_, false);

  // Should not be modified since clean_inliers is false and inliers exist
  EXPECT_EQ(view_graph_.image_pairs.at(pair_id).inliers.size(), 3);
  EXPECT_EQ(view_graph_.image_pairs.at(pair_id).inliers[0], 0);
  EXPECT_EQ(view_graph_.image_pairs.at(pair_id).inliers[1], 1);
  EXPECT_EQ(view_graph_.image_pairs.at(pair_id).inliers[2], 2);
}

// Test with clean_inliers=true and existing inliers on invalid pair
TEST_F(ImagePairsInlierCountTest_149, CleanInliersOnInvalidPair_149) {
  ImagePair pair(0, 1);
  pair.is_valid = false;
  pair.inliers = {0, 1, 2, 3};

  image_pair_t pair_id = pair.pair_id;
  view_graph_.image_pairs.emplace(pair_id, pair);

  ImagePairsInlierCount(view_graph_, cameras_, images_, options_, true);

  // Inliers should be cleared
  EXPECT_TRUE(view_graph_.image_pairs.at(pair_id).inliers.empty());
}

// Test with clean_inliers=false and no existing inliers on invalid pair
TEST_F(ImagePairsInlierCountTest_149, NoInliersInvalidPairNotCleaning_149) {
  ImagePair pair(0, 1);
  pair.is_valid = false;
  pair.inliers.clear();

  image_pair_t pair_id = pair.pair_id;
  view_graph_.image_pairs.emplace(pair_id, pair);

  ImagePairsInlierCount(view_graph_, cameras_, images_, options_, false);

  // Should be empty - was already empty, and is_valid=false means no scoring
  EXPECT_TRUE(view_graph_.image_pairs.at(pair_id).inliers.empty());
}

// Test that valid pair with clean_inliers=true processes scoring
TEST_F(ImagePairsInlierCountTest_149, ValidPairWithCleanInliers_149) {
  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.config = colmap::TwoViewGeometry::CALIBRATED;
  pair.E = Eigen::Matrix3d::Identity();
  pair.F = Eigen::Matrix3d::Identity();
  pair.H = Eigen::Matrix3d::Identity();
  pair.inliers = {0, 1};

  // Set up matches between the features
  Eigen::MatrixXi matches(3, 2);
  matches(0, 0) = 0; matches(0, 1) = 0;
  matches(1, 0) = 1; matches(1, 1) = 1;
  matches(2, 0) = 2; matches(2, 1) = 2;
  pair.matches = matches;

  image_pair_t pair_id = pair.pair_id;
  view_graph_.image_pairs.emplace(pair_id, pair);

  // This should clear and recompute inliers
  EXPECT_NO_THROW(
      ImagePairsInlierCount(view_graph_, cameras_, images_, options_, true));
}

// Test that valid pair with clean_inliers=false and empty inliers processes
TEST_F(ImagePairsInlierCountTest_149, ValidPairEmptyInliersNoClean_149) {
  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.config = colmap::TwoViewGeometry::CALIBRATED;
  pair.E = Eigen::Matrix3d::Identity();
  pair.F = Eigen::Matrix3d::Identity();
  pair.H = Eigen::Matrix3d::Identity();
  pair.inliers.clear();

  Eigen::MatrixXi matches(3, 2);
  matches(0, 0) = 0; matches(0, 1) = 0;
  matches(1, 0) = 1; matches(1, 1) = 1;
  matches(2, 0) = 2; matches(2, 1) = 2;
  pair.matches = matches;

  image_pair_t pair_id = pair.pair_id;
  view_graph_.image_pairs.emplace(pair_id, pair);

  // Should process since inliers is empty even with clean_inliers=false
  EXPECT_NO_THROW(
      ImagePairsInlierCount(view_graph_, cameras_, images_, options_, false));
}

// Test multiple image pairs - mix of valid and invalid
TEST_F(ImagePairsInlierCountTest_149, MultipleImagePairsMixed_149) {
  // Add a third image
  Image img3;
  img3.image_id = 2;
  img3.camera_id = 0;
  img3.is_registered = true;
  img3.features.push_back(Eigen::Vector2d(120.0, 120.0));
  img3.features.push_back(Eigen::Vector2d(220.0, 220.0));
  images_[2] = img3;

  // Pair 1: valid
  ImagePair pair1(0, 1);
  pair1.is_valid = true;
  pair1.config = colmap::TwoViewGeometry::CALIBRATED;
  pair1.E = Eigen::Matrix3d::Identity();
  pair1.inliers.clear();
  Eigen::MatrixXi matches1(2, 2);
  matches1(0, 0) = 0; matches1(0, 1) = 0;
  matches1(1, 0) = 1; matches1(1, 1) = 1;
  pair1.matches = matches1;

  // Pair 2: invalid
  ImagePair pair2(0, 2);
  pair2.is_valid = false;
  pair2.inliers = {0};

  view_graph_.image_pairs.emplace(pair1.pair_id, pair1);
  view_graph_.image_pairs.emplace(pair2.pair_id, pair2);

  ImagePairsInlierCount(view_graph_, cameras_, images_, options_, true);

  // Invalid pair should have cleared inliers
  EXPECT_TRUE(view_graph_.image_pairs.at(pair2.pair_id).inliers.empty());
}

// Test ScoreError directly on an ImagePairInliers object
class ImagePairInliersTest_149 : public ::testing::Test {
 protected:
  void SetUp() override {
    Camera cam;
    cam.camera_id = 0;
    cam.model_id = colmap::SimplePinholeCameraModel::model_id;
    cam.width = 640;
    cam.height = 480;
    cam.params = {500.0, 320.0, 240.0};
    cameras_[0] = cam;

    Camera cam2;
    cam2.camera_id = 1;
    cam2.model_id = colmap::SimplePinholeCameraModel::model_id;
    cam2.width = 640;
    cam2.height = 480;
    cam2.params = {500.0, 320.0, 240.0};
    cameras_[1] = cam2;

    Image img1;
    img1.image_id = 0;
    img1.camera_id = 0;
    img1.is_registered = true;
    for (int i = 0; i < 50; i++) {
      img1.features.push_back(Eigen::Vector2d(100.0 + i * 10, 100.0 + i * 5));
    }
    images_[0] = img1;

    Image img2;
    img2.image_id = 1;
    img2.camera_id = 1;
    img2.is_registered = true;
    for (int i = 0; i < 50; i++) {
      img2.features.push_back(Eigen::Vector2d(105.0 + i * 10, 105.0 + i * 5));
    }
    images_[1] = img2;

    options_.max_epipolar_error_E = 2.0;
    options_.max_epipolar_error_F = 5.0;
    options_.max_epipolar_error_H = 5.0;
    options_.min_inlier_num = 5;
    options_.min_inlier_ratio = 0.1;
  }

  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<image_t, Image> images_;
  InlierThresholdOptions options_;
};

// Test ScoreError returns a value
TEST_F(ImagePairInliersTest_149, ScoreErrorReturnsValue_149) {
  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.config = colmap::TwoViewGeometry::CALIBRATED;
  pair.E = Eigen::Matrix3d::Identity();
  pair.F = Eigen::Matrix3d::Identity();
  pair.H = Eigen::Matrix3d::Identity();

  Eigen::MatrixXi matches(10, 2);
  for (int i = 0; i < 10; i++) {
    matches(i, 0) = i;
    matches(i, 1) = i;
  }
  pair.matches = matches;

  ImagePairInliers inlier_finder(pair, images_, options_, &cameras_);
  double score = inlier_finder.ScoreError();

  // Score should be a finite number
  EXPECT_TRUE(std::isfinite(score));
}

// Test ScoreError with UNDEFINED config
TEST_F(ImagePairInliersTest_149, ScoreErrorUndefinedConfig_149) {
  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.config = colmap::TwoViewGeometry::UNDEFINED;
  pair.E = Eigen::Matrix3d::Identity();
  pair.F = Eigen::Matrix3d::Identity();
  pair.H = Eigen::Matrix3d::Identity();

  Eigen::MatrixXi matches(5, 2);
  for (int i = 0; i < 5; i++) {
    matches(i, 0) = i;
    matches(i, 1) = i;
  }
  pair.matches = matches;

  ImagePairInliers inlier_finder(pair, images_, options_, &cameras_);
  double score = inlier_finder.ScoreError();
  EXPECT_TRUE(std::isfinite(score));
}

// Test ScoreError with no matches
TEST_F(ImagePairInliersTest_149, ScoreErrorNoMatches_149) {
  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.config = colmap::TwoViewGeometry::CALIBRATED;
  pair.E = Eigen::Matrix3d::Identity();

  Eigen::MatrixXi matches(0, 2);
  pair.matches = matches;

  ImagePairInliers inlier_finder(pair, images_, options_, &cameras_);
  double score = inlier_finder.ScoreError();
  EXPECT_TRUE(std::isfinite(score));
  EXPECT_TRUE(pair.inliers.empty());
}

// Test ScoreError with nullptr cameras
TEST_F(ImagePairInliersTest_149, ScoreErrorNullCameras_149) {
  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.config = colmap::TwoViewGeometry::UNCALIBRATED;
  pair.F = Eigen::Matrix3d::Identity();

  Eigen::MatrixXi matches(5, 2);
  for (int i = 0; i < 5; i++) {
    matches(i, 0) = i;
    matches(i, 1) = i;
  }
  pair.matches = matches;

  ImagePairInliers inlier_finder(pair, images_, options_, nullptr);
  double score = inlier_finder.ScoreError();
  EXPECT_TRUE(std::isfinite(score));
}

// Test with PLANAR config (homography)
TEST_F(ImagePairInliersTest_149, ScoreErrorHomographyConfig_149) {
  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.config = colmap::TwoViewGeometry::PLANAR;
  pair.H = Eigen::Matrix3d::Identity();

  Eigen::MatrixXi matches(10, 2);
  for (int i = 0; i < 10; i++) {
    matches(i, 0) = i;
    matches(i, 1) = i;
  }
  pair.matches = matches;

  ImagePairInliers inlier_finder(pair, images_, options_, &cameras_);
  double score = inlier_finder.ScoreError();
  EXPECT_TRUE(std::isfinite(score));
}

}  // namespace
}  // namespace glomap
