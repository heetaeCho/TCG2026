// File: view_graph_manipulation_test_160.cc

#include <gtest/gtest.h>

#include <unordered_map>
#include <vector>

#include "glomap/processors/view_graph_manipulation.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/image.h"
#include "glomap/scene/camera.h"
#include "glomap/types.h"

using namespace glomap;

class ViewGraphManipulaterTest_160 : public ::testing::Test {
 protected:
  ViewGraph view_graph_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<image_t, Image> images_;
};

// 1) Invalid image pairs (is_valid == false) should be ignored
TEST_F(ViewGraphManipulaterTest_160, InvalidImagePairsAreIgnored_160) {
  const image_t kImageId1 = 1;
  const image_t kImageId2 = 2;

  // Create an image pair that is explicitly invalid.
  ImagePair image_pair(kImageId1, kImageId2);
  image_pair.is_valid = false;
  image_pair.config = colmap::TwoViewGeometry::UNDEFINED;

  view_graph_.image_pairs.emplace(image_pair.pair_id, image_pair);

  // Cameras / images are not required for this branch, since invalid pairs are skipped.
  ViewGraphManipulater manipulater;
  manipulater.DecomposeRelPose(view_graph_, cameras_, images_);

  const ImagePair& stored_pair = view_graph_.image_pairs.at(image_pair.pair_id);
  EXPECT_FALSE(stored_pair.is_valid);
  EXPECT_EQ(stored_pair.config, colmap::TwoViewGeometry::UNDEFINED);
}

// 2) PLANAR config + both cameras with prior focal length -> CALIBRATED,
//    and the existing relative pose is not modified by DecomposeRelPose.
TEST_F(ViewGraphManipulaterTest_160, PlanarWithPriorFocalBecomesCalibrated_160) {
  const image_t kImageId1 = 1;
  const image_t kImageId2 = 2;
  const camera_t kCamId1 = 11;
  const camera_t kCamId2 = 22;

  // Cameras with prior focal length
  Camera cam1;
  cam1.has_prior_focal_length = true;
  Camera cam2;
  cam2.has_prior_focal_length = true;
  cameras_[kCamId1] = cam1;
  cameras_[kCamId2] = cam2;

  // Images referencing those cameras
  Image img1(kImageId1, kCamId1, "img1");
  Image img2(kImageId2, kCamId2, "img2");
  // Features are passed through but we do not rely on any particular behavior.
  img1.features.emplace_back(0.0, 0.0);
  img2.features.emplace_back(1.0, 1.0);
  images_[kImageId1] = img1;
  images_[kImageId2] = img2;

  // Image pair with PLANAR config and a non-normalized translation
  ImagePair image_pair(kImageId1, kImageId2);
  image_pair.is_valid = true;
  image_pair.config = colmap::TwoViewGeometry::PLANAR;
  image_pair.cam2_from_cam1.translation = Eigen::Vector3d(10.0, 0.0, 0.0);
  const double original_norm =
      image_pair.cam2_from_cam1.translation.norm();

  view_graph_.image_pairs.emplace(image_pair.pair_id, image_pair);

  ViewGraphManipulater manipulater;
  manipulater.DecomposeRelPose(view_graph_, cameras_, images_);

  const ImagePair& stored_pair = view_graph_.image_pairs.at(image_pair.pair_id);

  // Expect that PLANAR became CALIBRATED
  EXPECT_EQ(stored_pair.config, colmap::TwoViewGeometry::CALIBRATED);

  // In this branch, the existing pose should not be altered by DecomposeRelPose
  EXPECT_DOUBLE_EQ(stored_pair.cam2_from_cam1.translation.norm(),
                   original_norm);
  EXPECT_EQ(stored_pair.cam2_from_cam1.translation.x(), 10.0);
  EXPECT_EQ(stored_pair.cam2_from_cam1.translation.y(), 0.0);
  EXPECT_EQ(stored_pair.cam2_from_cam1.translation.z(), 0.0);
}

// 3) Pairs without prior focal length in at least one camera
//    should be skipped (no decomposition performed).
TEST_F(ViewGraphManipulaterTest_160, MissingPriorFocalSkipsPair_160) {
  const image_t kImageId1 = 1;
  const image_t kImageId2 = 2;
  const camera_t kCamId1 = 11;
  const camera_t kCamId2 = 22;

  // First camera has prior focal, second does not
  Camera cam1;
  cam1.has_prior_focal_length = true;
  Camera cam2;
  cam2.has_prior_focal_length = false;
  cameras_[kCamId1] = cam1;
  cameras_[kCamId2] = cam2;

  Image img1(kImageId1, kCamId1, "img1");
  Image img2(kImageId2, kCamId2, "img2");
  images_[kImageId1] = img1;
  images_[kImageId2] = img2;

  ImagePair image_pair(kImageId1, kImageId2);
  image_pair.is_valid = true;
  image_pair.config = colmap::TwoViewGeometry::PLANAR;
  image_pair.cam2_from_cam1.translation = Eigen::Vector3d(5.0, 0.0, 0.0);
  const Eigen::Vector3d original_translation =
      image_pair.cam2_from_cam1.translation;

  view_graph_.image_pairs.emplace(image_pair.pair_id, image_pair);

  ViewGraphManipulater manipulater;
  manipulater.DecomposeRelPose(view_graph_, cameras_, images_);

  const ImagePair& stored_pair = view_graph_.image_pairs.at(image_pair.pair_id);

  // Since one camera lacked prior focal length, the pair should not be
  // decomposed and its config and pose should remain unchanged.
  EXPECT_EQ(stored_pair.config, colmap::TwoViewGeometry::PLANAR);
  EXPECT_EQ(stored_pair.cam2_from_cam1.translation, original_translation);
}

// 4) Mixed set of image pairs: only valid pairs with prior focal length
//    on both cameras and PLANAR config should be converted to CALIBRATED.
TEST_F(ViewGraphManipulaterTest_160, OnlyEligiblePairsAreProcessed_160) {
  const image_t kImageId1 = 1;
  const image_t kImageId2 = 2;
  const image_t kImageId3 = 3;
  const image_t kImageId4 = 4;

  const camera_t kCamId1 = 11;
  const camera_t kCamId2 = 22;
  const camera_t kCamId3 = 33;
  const camera_t kCamId4 = 44;

  // Cameras
  Camera cam1;
  cam1.has_prior_focal_length = true;
  Camera cam2;
  cam2.has_prior_focal_length = true;
  Camera cam3;
  cam3.has_prior_focal_length = false;  // no prior focal
  Camera cam4;
  cam4.has_prior_focal_length = true;

  cameras_[kCamId1] = cam1;
  cameras_[kCamId2] = cam2;
  cameras_[kCamId3] = cam3;
  cameras_[kCamId4] = cam4;

  // Images
  images_.emplace(kImageId1, Image(kImageId1, kCamId1, "img1"));
  images_.emplace(kImageId2, Image(kImageId2, kCamId2, "img2"));
  images_.emplace(kImageId3, Image(kImageId3, kCamId3, "img3"));
  images_.emplace(kImageId4, Image(kImageId4, kCamId4, "img4"));

  // Pair A: valid, PLANAR, both cameras have prior focal -> should be processed
  ImagePair pair_a(kImageId1, kImageId2);
  pair_a.is_valid = true;
  pair_a.config = colmap::TwoViewGeometry::PLANAR;

  // Pair B: valid, PLANAR, but one camera has no prior focal -> skipped
  ImagePair pair_b(kImageId3, kImageId4);
  pair_b.is_valid = true;
  pair_b.config = colmap::TwoViewGeometry::PLANAR;

  view_graph_.image_pairs.emplace(pair_a.pair_id, pair_a);
  view_graph_.image_pairs.emplace(pair_b.pair_id, pair_b);

  ViewGraphManipulater manipulater;
  manipulater.DecomposeRelPose(view_graph_, cameras_, images_);

  const ImagePair& stored_a = view_graph_.image_pairs.at(pair_a.pair_id);
  const ImagePair& stored_b = view_graph_.image_pairs.at(pair_b.pair_id);

  // Pair A should have been converted to CALIBRATED
  EXPECT_EQ(stored_a.config, colmap::TwoViewGeometry::CALIBRATED);

  // Pair B should remain PLANAR because it was not eligible
  EXPECT_EQ(stored_b.config, colmap::TwoViewGeometry::PLANAR);
}
