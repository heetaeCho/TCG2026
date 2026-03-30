// File: view_graph_manipulation_test_159.cc

#include <gtest/gtest.h>

#include "glomap/processors/view_graph_manipulation.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/image.h"

using glomap::ViewGraph;
using glomap::Image;
using glomap::ImagePair;
using glomap::ViewGraphManipulater;
using glomap::image_t;
using glomap::camera_t;

class ViewGraphManipulaterTest_159 : public ::testing::Test {
 protected:
  ViewGraph view_graph_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<image_t, Image> images_;

  void AddCamera(camera_t id, bool has_prior_focal_length) {
    Camera cam;
    cam.has_prior_focal_length = has_prior_focal_length;
    cameras_[id] = cam;
  }

  void AddImage(image_t img_id, camera_t cam_id, const std::string& name) {
    images_.emplace(img_id, Image(img_id, cam_id, name));
  }

  ImagePair MakePair(image_t id1, image_t id2, int config) {
    ImagePair pair(id1, id2);
    pair.config = config;
    pair.is_valid = true;
    return pair;
  }
};

// Normal operation: cameras are mostly involved in CALIBRATED pairs,
// so UNCALIBRATED pairs between those cameras are upgraded.
TEST_F(ViewGraphManipulaterTest_159,
       UpgradeUncalibratedPairsWhenCamerasMostlyCalibrated_159) {
  // Cameras
  camera_t cam1_id = static_cast<camera_t>(1);
  camera_t cam2_id = static_cast<camera_t>(2);
  AddCamera(cam1_id, true);
  AddCamera(cam2_id, true);

  // Images using the two cameras
  image_t img1_id = static_cast<image_t>(1);
  image_t img2_id = static_cast<image_t>(2);
  image_t img3_id = static_cast<image_t>(3);
  AddImage(img1_id, cam1_id, "img1");
  AddImage(img2_id, cam2_id, "img2");
  AddImage(img3_id, cam2_id, "img3");

  // Two calibrated pairs and one uncalibrated between the same cameras.
  ImagePair pair12_calib = MakePair(
      img1_id, img2_id, colmap::TwoViewGeometry::CALIBRATED);
  ImagePair pair13_calib = MakePair(
      img1_id, img3_id, colmap::TwoViewGeometry::CALIBRATED);
  ImagePair pair23_uncal = MakePair(
      img2_id, img3_id, colmap::TwoViewGeometry::UNCALIBRATED);

  view_graph_.image_pairs.emplace(pair12_calib.pair_id, pair12_calib);
  view_graph_.image_pairs.emplace(pair13_calib.pair_id, pair13_calib);
  view_graph_.image_pairs.emplace(pair23_uncal.pair_id, pair23_uncal);

  // Act
  ViewGraphManipulater::UpdateImagePairsConfig(view_graph_, cameras_, images_);

  // The uncalibrated pair should be promoted to CALIBRATED.
  const auto& updated_pair23 =
      view_graph_.image_pairs.at(pair23_uncal.pair_id);
  EXPECT_EQ(updated_pair23.config, colmap::TwoViewGeometry::CALIBRATED);
}

// Boundary condition: cameras are not "mostly calibrated"
// (ratio of calibrated to total pairs is <= 0.5), so UNCALIBRATED pairs
// must NOT be upgraded.
TEST_F(ViewGraphManipulaterTest_159,
       DoesNotUpgradeWhenCamerasNotMostlyCalibrated_159) {
  camera_t cam1_id = static_cast<camera_t>(10);
  camera_t cam2_id = static_cast<camera_t>(20);
  AddCamera(cam1_id, true);
  AddCamera(cam2_id, true);

  image_t img1_id = static_cast<image_t>(11);
  image_t img2_id = static_cast<image_t>(22);
  AddImage(img1_id, cam1_id, "img1");
  AddImage(img2_id, cam2_id, "img2");

  // One calibrated and one uncalibrated pair between the same cameras.
  // For each camera: first = 2, second = 1 -> ratio = 0.5, not > 0.5.
  ImagePair pair_calib =
      MakePair(img1_id, img2_id, colmap::TwoViewGeometry::CALIBRATED);
  ImagePair pair_uncal =
      MakePair(img1_id, img2_id, colmap::TwoViewGeometry::UNCALIBRATED);

  view_graph_.image_pairs.emplace(pair_calib.pair_id, pair_calib);
  view_graph_.image_pairs.emplace(pair_uncal.pair_id, pair_uncal);

  // Act
  ViewGraphManipulater::UpdateImagePairsConfig(view_graph_, cameras_, images_);

  // Uncalibrated pair should remain UNCALIBRATED because ratio == 0.5.
  const auto& updated_pair_uncal =
      view_graph_.image_pairs.at(pair_uncal.pair_id);
  EXPECT_EQ(updated_pair_uncal.config,
            colmap::TwoViewGeometry::UNCALIBRATED);
}

// Error/edge behavior: if cameras do NOT have prior focal length,
// pairs involving them are ignored when computing camera validity,
// so UNCALIBRATED pairs stay UNCALIBRATED.
TEST_F(ViewGraphManipulaterTest_159,
       SkipsPairsWithoutPriorFocalLength_159) {
  camera_t cam1_id = static_cast<camera_t>(100);
  camera_t cam2_id = static_cast<camera_t>(200);
  // No prior focal length for either camera.
  AddCamera(cam1_id, false);
  AddCamera(cam2_id, false);

  image_t img1_id = static_cast<image_t>(101);
  image_t img2_id = static_cast<image_t>(202);
  AddImage(img1_id, cam1_id, "img1");
  AddImage(img2_id, cam2_id, "img2");

  ImagePair pair_uncal =
      MakePair(img1_id, img2_id, colmap::TwoViewGeometry::UNCALIBRATED);
  view_graph_.image_pairs.emplace(pair_uncal.pair_id, pair_uncal);

  // Act
  ViewGraphManipulater::UpdateImagePairsConfig(view_graph_, cameras_, images_);

  // Since cameras lack prior focal length, they never enter camera_counter,
  // thus are never considered valid, so config should not be changed.
  const auto& updated_pair =
      view_graph_.image_pairs.at(pair_uncal.pair_id);
  EXPECT_EQ(updated_pair.config, colmap::TwoViewGeometry::UNCALIBRATED);
}

// Error/edge behavior: invalid image pairs (is_valid == false)
// are skipped both in counting and in updating, so their config
// must remain unchanged even if their cameras are valid.
TEST_F(ViewGraphManipulaterTest_159,
       SkipsInvalidImagePairs_159) {
  camera_t cam1_id = static_cast<camera_t>(300);
  camera_t cam2_id = static_cast<camera_t>(400);
  AddCamera(cam1_id, true);
  AddCamera(cam2_id, true);

  image_t img1_id = static_cast<image_t>(301);
  image_t img2_id = static_cast<image_t>(302);
  image_t img3_id = static_cast<image_t>(303);

  AddImage(img1_id, cam1_id, "img1");
  AddImage(img2_id, cam2_id, "img2");
  AddImage(img3_id, cam2_id, "img3");

  // Two calibrated pairs to make both cameras "valid".
  ImagePair pair12_calib =
      MakePair(img1_id, img2_id, colmap::TwoViewGeometry::CALIBRATED);
  ImagePair pair13_calib =
      MakePair(img1_id, img3_id, colmap::TwoViewGeometry::CALIBRATED);

  // One uncalibrated but INVALID pair.
  ImagePair pair23_invalid =
      MakePair(img2_id, img3_id, colmap::TwoViewGeometry::UNCALIBRATED);
  pair23_invalid.is_valid = false;

  view_graph_.image_pairs.emplace(pair12_calib.pair_id, pair12_calib);
  view_graph_.image_pairs.emplace(pair13_calib.pair_id, pair13_calib);
  view_graph_.image_pairs.emplace(pair23_invalid.pair_id, pair23_invalid);

  // Act
  ViewGraphManipulater::UpdateImagePairsConfig(view_graph_, cameras_, images_);

  // The invalid pair must not be updated.
  const auto& updated_invalid_pair =
      view_graph_.image_pairs.at(pair23_invalid.pair_id);
  EXPECT_EQ(updated_invalid_pair.config,
            colmap::TwoViewGeometry::UNCALIBRATED);
  EXPECT_FALSE(updated_invalid_pair.is_valid);
}
