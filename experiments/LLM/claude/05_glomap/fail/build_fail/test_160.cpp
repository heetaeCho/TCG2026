#include <gtest/gtest.h>
#include "glomap/processors/view_graph_manipulation.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/types.h"

#include <colmap/scene/camera.h>
#include <colmap/scene/two_view_geometry.h>
#include <colmap/util/types.h>

#include <unordered_map>
#include <Eigen/Core>

namespace glomap {
namespace {

class ViewGraphManipulaterTest_160 : public ::testing::Test {
 protected:
  void SetUp() override {}

  // Helper to create a simple camera with prior focal length
  colmap::Camera CreateCameraWithPrior(camera_t cam_id) {
    colmap::Camera camera;
    camera.camera_id = cam_id;
    camera.SetModelIdFromName("SIMPLE_PINHOLE");
    camera.SetWidth(640);
    camera.SetHeight(480);
    camera.SetParams({500.0, 320.0, 240.0});
    camera.has_prior_focal_length = true;
    return camera;
  }

  // Helper to create a camera without prior focal length
  colmap::Camera CreateCameraWithoutPrior(camera_t cam_id) {
    colmap::Camera camera;
    camera.camera_id = cam_id;
    camera.SetModelIdFromName("SIMPLE_PINHOLE");
    camera.SetWidth(640);
    camera.SetHeight(480);
    camera.SetParams({500.0, 320.0, 240.0});
    camera.has_prior_focal_length = false;
    return camera;
  }

  // Helper to create a simple image
  Image CreateImage(image_t img_id, camera_t cam_id) {
    Image img(img_id, cam_id, "test_image_" + std::to_string(img_id) + ".jpg");
    // Add some dummy features
    img.features.push_back(Eigen::Vector2d(100.0, 200.0));
    img.features.push_back(Eigen::Vector2d(150.0, 250.0));
    img.features.push_back(Eigen::Vector2d(200.0, 300.0));
    img.features.push_back(Eigen::Vector2d(250.0, 350.0));
    img.features.push_back(Eigen::Vector2d(300.0, 400.0));
    return img;
  }
};

// Test: DecomposeRelPose with empty view graph (no image pairs)
TEST_F(ViewGraphManipulaterTest_160, DecomposeRelPose_EmptyViewGraph_160) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  // Should not crash on empty input
  EXPECT_NO_THROW(
      ViewGraphManipulater::DecomposeRelPose(view_graph, cameras, images));
  EXPECT_TRUE(view_graph.image_pairs.empty());
}

// Test: DecomposeRelPose skips invalid image pairs
TEST_F(ViewGraphManipulaterTest_160, DecomposeRelPose_SkipsInvalidPairs_160) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  // Setup cameras
  cameras[0] = CreateCameraWithPrior(0);
  cameras[1] = CreateCameraWithPrior(1);

  // Setup images
  images.emplace(0, CreateImage(0, 0));
  images.emplace(1, CreateImage(1, 1));

  // Create an invalid image pair
  ImagePair pair(0, 1);
  pair.is_valid = false;
  pair.E = Eigen::Matrix3d::Identity();
  pair.F = Eigen::Matrix3d::Identity();
  pair.H = Eigen::Matrix3d::Identity();
  pair.config = colmap::TwoViewGeometry::CALIBRATED;

  view_graph.image_pairs[pair.pair_id] = pair;

  // Store original config
  int original_config = view_graph.image_pairs[pair.pair_id].config;

  EXPECT_NO_THROW(
      ViewGraphManipulater::DecomposeRelPose(view_graph, cameras, images));

  // Since the pair is invalid, it should not be processed - config should remain unchanged
  EXPECT_EQ(view_graph.image_pairs[pair.pair_id].config, original_config);
}

// Test: DecomposeRelPose skips pairs where cameras don't have prior focal length
TEST_F(ViewGraphManipulaterTest_160,
       DecomposeRelPose_SkipsPairsWithoutPriorFocalLength_160) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  // Camera 0 has prior, camera 1 does not
  cameras[0] = CreateCameraWithPrior(0);
  cameras[1] = CreateCameraWithoutPrior(1);

  images.emplace(0, CreateImage(0, 0));
  images.emplace(1, CreateImage(1, 1));

  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.E = Eigen::Matrix3d::Identity();
  pair.F = Eigen::Matrix3d::Identity();
  pair.H = Eigen::Matrix3d::Identity();
  pair.config = colmap::TwoViewGeometry::CALIBRATED;

  view_graph.image_pairs[pair.pair_id] = pair;

  int original_config = view_graph.image_pairs[pair.pair_id].config;

  EXPECT_NO_THROW(
      ViewGraphManipulater::DecomposeRelPose(view_graph, cameras, images));

  // Pair should not be processed since camera 1 doesn't have prior focal length
  EXPECT_EQ(view_graph.image_pairs[pair.pair_id].config, original_config);
}

// Test: DecomposeRelPose with valid pair and both cameras having prior focal length
TEST_F(ViewGraphManipulaterTest_160,
       DecomposeRelPose_ValidPairWithPriorFocalLength_160) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreateCameraWithPrior(0);
  cameras[1] = CreateCameraWithPrior(1);

  images.emplace(0, CreateImage(0, 0));
  images.emplace(1, CreateImage(1, 1));

  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.E = Eigen::Matrix3d::Identity();
  pair.F = Eigen::Matrix3d::Identity();
  pair.H = Eigen::Matrix3d::Identity();
  pair.config = colmap::TwoViewGeometry::CALIBRATED;

  view_graph.image_pairs[pair.pair_id] = pair;

  EXPECT_NO_THROW(
      ViewGraphManipulater::DecomposeRelPose(view_graph, cameras, images));

  // After decomposition, the pair should still exist in the view graph
  EXPECT_TRUE(view_graph.image_pairs.count(pair.pair_id) > 0);
}

// Test: DecomposeRelPose with PLANAR config and prior focal lengths sets config to CALIBRATED
TEST_F(ViewGraphManipulaterTest_160,
       DecomposeRelPose_PlanarConfigBecomesCalibratedWithPriors_160) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreateCameraWithPrior(0);
  cameras[1] = CreateCameraWithPrior(1);

  images.emplace(0, CreateImage(0, 0));
  images.emplace(1, CreateImage(1, 1));

  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.E = Eigen::Matrix3d::Identity();
  pair.F = Eigen::Matrix3d::Identity();
  pair.H = Eigen::Matrix3d::Identity();
  pair.config = colmap::TwoViewGeometry::PLANAR;

  view_graph.image_pairs[pair.pair_id] = pair;

  EXPECT_NO_THROW(
      ViewGraphManipulater::DecomposeRelPose(view_graph, cameras, images));

  // PLANAR config with both cameras having prior focal length should become CALIBRATED
  EXPECT_EQ(view_graph.image_pairs[pair.pair_id].config,
            colmap::TwoViewGeometry::CALIBRATED);
}

// Test: DecomposeRelPose with multiple pairs, some valid and some invalid
TEST_F(ViewGraphManipulaterTest_160,
       DecomposeRelPose_MultiplePairsMixedValidity_160) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreateCameraWithPrior(0);
  cameras[1] = CreateCameraWithPrior(1);
  cameras[2] = CreateCameraWithPrior(2);

  images.emplace(0, CreateImage(0, 0));
  images.emplace(1, CreateImage(1, 1));
  images.emplace(2, CreateImage(2, 2));

  // Valid pair
  ImagePair pair1(0, 1);
  pair1.is_valid = true;
  pair1.E = Eigen::Matrix3d::Identity();
  pair1.F = Eigen::Matrix3d::Identity();
  pair1.H = Eigen::Matrix3d::Identity();
  pair1.config = colmap::TwoViewGeometry::CALIBRATED;
  view_graph.image_pairs[pair1.pair_id] = pair1;

  // Invalid pair
  ImagePair pair2(0, 2);
  pair2.is_valid = false;
  pair2.E = Eigen::Matrix3d::Identity();
  pair2.F = Eigen::Matrix3d::Identity();
  pair2.H = Eigen::Matrix3d::Identity();
  pair2.config = colmap::TwoViewGeometry::CALIBRATED;
  view_graph.image_pairs[pair2.pair_id] = pair2;

  // Valid pair
  ImagePair pair3(1, 2);
  pair3.is_valid = true;
  pair3.E = Eigen::Matrix3d::Identity();
  pair3.F = Eigen::Matrix3d::Identity();
  pair3.H = Eigen::Matrix3d::Identity();
  pair3.config = colmap::TwoViewGeometry::PLANAR;
  view_graph.image_pairs[pair3.pair_id] = pair3;

  EXPECT_NO_THROW(
      ViewGraphManipulater::DecomposeRelPose(view_graph, cameras, images));

  // pair2 should be unchanged (invalid, not processed)
  // pair3 should become CALIBRATED (PLANAR with prior focal lengths)
  EXPECT_EQ(view_graph.image_pairs[pair2.pair_id].config,
            colmap::TwoViewGeometry::CALIBRATED);  // unchanged
  EXPECT_EQ(view_graph.image_pairs[pair3.pair_id].config,
            colmap::TwoViewGeometry::CALIBRATED);  // PLANAR -> CALIBRATED
}

// Test: DecomposeRelPose normalizes translation when norm > EPS
TEST_F(ViewGraphManipulaterTest_160,
       DecomposeRelPose_TranslationNormalized_160) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreateCameraWithPrior(0);
  cameras[1] = CreateCameraWithPrior(1);

  // Create images with more features for better geometry estimation
  Image img0(0, 0, "img0.jpg");
  Image img1(1, 1, "img1.jpg");
  for (int i = 0; i < 50; i++) {
    img0.features.push_back(
        Eigen::Vector2d(100.0 + i * 10, 200.0 + i * 5));
    img1.features.push_back(
        Eigen::Vector2d(110.0 + i * 10, 210.0 + i * 5));
  }
  images.emplace(0, img0);
  images.emplace(1, img1);

  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.E = Eigen::Matrix3d::Identity();
  pair.F = Eigen::Matrix3d::Identity();
  pair.H = Eigen::Matrix3d::Identity();
  pair.config = colmap::TwoViewGeometry::CALIBRATED;
  view_graph.image_pairs[pair.pair_id] = pair;

  EXPECT_NO_THROW(
      ViewGraphManipulater::DecomposeRelPose(view_graph, cameras, images));

  // Check that the translation is either zero or normalized
  const auto& result_pair = view_graph.image_pairs[pair.pair_id];
  double norm = result_pair.cam2_from_cam1.translation.norm();
  if (norm > EPS) {
    EXPECT_NEAR(norm, 1.0, 1e-6);
  }
}

// Test: DecomposeRelPose with no cameras having prior focal length - no pairs processed
TEST_F(ViewGraphManipulaterTest_160,
       DecomposeRelPose_NoCamerasWithPrior_NoPairsProcessed_160) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreateCameraWithoutPrior(0);
  cameras[1] = CreateCameraWithoutPrior(1);

  images.emplace(0, CreateImage(0, 0));
  images.emplace(1, CreateImage(1, 1));

  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.E = Eigen::Matrix3d::Identity();
  pair.F = Eigen::Matrix3d::Identity();
  pair.H = Eigen::Matrix3d::Identity();
  pair.config = colmap::TwoViewGeometry::UNDEFINED;

  view_graph.image_pairs[pair.pair_id] = pair;

  int original_config = view_graph.image_pairs[pair.pair_id].config;

  EXPECT_NO_THROW(
      ViewGraphManipulater::DecomposeRelPose(view_graph, cameras, images));

  // Config should remain unchanged since no pair was processed
  EXPECT_EQ(view_graph.image_pairs[pair.pair_id].config, original_config);
}

// Test: DecomposeRelPose only one camera has prior focal length
TEST_F(ViewGraphManipulaterTest_160,
       DecomposeRelPose_OnlyOneCameraHasPrior_160) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreateCameraWithPrior(0);
  cameras[1] = CreateCameraWithoutPrior(1);

  images.emplace(0, CreateImage(0, 0));
  images.emplace(1, CreateImage(1, 1));

  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.E = Eigen::Matrix3d::Identity();
  pair.F = Eigen::Matrix3d::Identity();
  pair.H = Eigen::Matrix3d::Identity();
  pair.config = colmap::TwoViewGeometry::UNDEFINED;

  view_graph.image_pairs[pair.pair_id] = pair;

  Rigid3d original_pose = view_graph.image_pairs[pair.pair_id].cam2_from_cam1;

  EXPECT_NO_THROW(
      ViewGraphManipulater::DecomposeRelPose(view_graph, cameras, images));

  // Should not be processed (camera 1 has no prior)
  EXPECT_EQ(view_graph.image_pairs[pair.pair_id].config,
            colmap::TwoViewGeometry::UNDEFINED);
}

// Test: UpdateImagePairsConfig with empty view graph
TEST_F(ViewGraphManipulaterTest_160,
       UpdateImagePairsConfig_EmptyViewGraph_160) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  EXPECT_NO_THROW(
      ViewGraphManipulater::UpdateImagePairsConfig(view_graph, cameras,
                                                   images));
}

// Test: DecomposeRelPose with all pairs being invalid
TEST_F(ViewGraphManipulaterTest_160,
       DecomposeRelPose_AllPairsInvalid_160) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreateCameraWithPrior(0);
  cameras[1] = CreateCameraWithPrior(1);
  cameras[2] = CreateCameraWithPrior(2);

  images.emplace(0, CreateImage(0, 0));
  images.emplace(1, CreateImage(1, 1));
  images.emplace(2, CreateImage(2, 2));

  ImagePair pair1(0, 1);
  pair1.is_valid = false;
  pair1.config = colmap::TwoViewGeometry::CALIBRATED;
  view_graph.image_pairs[pair1.pair_id] = pair1;

  ImagePair pair2(1, 2);
  pair2.is_valid = false;
  pair2.config = colmap::TwoViewGeometry::CALIBRATED;
  view_graph.image_pairs[pair2.pair_id] = pair2;

  EXPECT_NO_THROW(
      ViewGraphManipulater::DecomposeRelPose(view_graph, cameras, images));

  // All pairs invalid, none should be processed
  EXPECT_EQ(view_graph.image_pairs.size(), 2u);
}

}  // namespace
}  // namespace glomap
