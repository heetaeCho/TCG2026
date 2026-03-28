#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/relpose_estimation.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"

#include <colmap/scene/camera.h>
#include <colmap/util/types.h>

#include <Eigen/Core>
#include <unordered_map>

namespace glomap {
namespace {

class RelativePoseEstimationTest_102 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up default options
    options_ = RelativePoseEstimationOptions();
  }

  // Helper to create a simple camera with PINHOLE model
  colmap::Camera CreatePinholeCamera(camera_t camera_id, double focal_length,
                                     int width, int height) {
    colmap::Camera camera;
    camera.camera_id = camera_id;
    camera.SetModelIdFromName("PINHOLE");
    camera.SetWidth(width);
    camera.SetHeight(height);
    camera.SetParams({focal_length, focal_length,
                      static_cast<double>(width) / 2.0,
                      static_cast<double>(height) / 2.0});
    return camera;
  }

  // Helper to create a simple camera with SIMPLE_PINHOLE model
  colmap::Camera CreateSimplePinholeCamera(camera_t camera_id,
                                           double focal_length, int width,
                                           int height) {
    colmap::Camera camera;
    camera.camera_id = camera_id;
    camera.SetModelIdFromName("SIMPLE_PINHOLE");
    camera.SetWidth(width);
    camera.SetHeight(height);
    camera.SetParams({focal_length, static_cast<double>(width) / 2.0,
                      static_cast<double>(height) / 2.0});
    return camera;
  }

  // Generate synthetic feature matches for a pair of images
  // with a known relative pose (pure translation along x-axis)
  void GenerateSyntheticData(Image& image1, Image& image2,
                             ImagePair& image_pair,
                             const colmap::Camera& camera1,
                             const colmap::Camera& camera2, int num_points) {
    image1.features.clear();
    image2.features.clear();

    Eigen::MatrixXi matches(num_points, 2);

    // Generate 3D points and project them
    double cx1 = camera1.PrincipalPointX();
    double cy1 = camera1.PrincipalPointY();
    double fx1 = camera1.FocalLengthX();
    double fy1 = camera1.FocalLengthY();

    double cx2 = camera2.PrincipalPointX();
    double cy2 = camera2.PrincipalPointY();
    double fx2 = camera2.FocalLengthX();
    double fy2 = camera2.FocalLengthY();

    for (int i = 0; i < num_points; i++) {
      // Random 3D point in front of both cameras
      double X = (i % 10 - 5) * 0.5;
      double Y = ((i / 10) % 10 - 5) * 0.5;
      double Z = 5.0 + (i % 7) * 0.3;

      // Project to camera 1 (identity pose)
      double u1 = fx1 * X / Z + cx1;
      double v1 = fy1 * Y / Z + cy1;

      // Camera 2 has a translation of (1, 0, 0) relative to camera 1
      double X2 = X - 1.0;
      double u2 = fx2 * X2 / Z + cx2;
      double v2 = fy2 * Y / Z + cy2;

      image1.features.push_back(Eigen::Vector2d(u1, v1));
      image2.features.push_back(Eigen::Vector2d(u2, v2));

      matches(i, 0) = i;
      matches(i, 1) = i;
    }

    image_pair.matches = matches;
  }

  RelativePoseEstimationOptions options_;
};

// Test: Empty view graph with no image pairs
TEST_F(RelativePoseEstimationTest_102, EmptyViewGraph_102) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  // Should not crash with empty inputs
  EXPECT_NO_THROW(
      EstimateRelativePoses(view_graph, cameras, images, options_));
  EXPECT_TRUE(view_graph.image_pairs.empty());
}

// Test: All pairs invalid - none should be processed
TEST_F(RelativePoseEstimationTest_102, AllPairsInvalid_102) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  // Create cameras
  cameras[0] = CreatePinholeCamera(0, 500.0, 640, 480);
  cameras[1] = CreatePinholeCamera(1, 500.0, 640, 480);

  // Create images
  images[0] = Image(0, 0, "img0.jpg");
  images[1] = Image(1, 1, "img1.jpg");

  // Create an invalid pair
  image_pair_t pair_id = colmap::ImagePairToPairId(0, 1);
  ImagePair pair(0, 1);
  pair.is_valid = false;
  pair.matches = Eigen::MatrixXi(0, 2);
  view_graph.image_pairs[pair_id] = pair;

  EXPECT_NO_THROW(
      EstimateRelativePoses(view_graph, cameras, images, options_));

  // The pair should remain invalid
  EXPECT_FALSE(view_graph.image_pairs[pair_id].is_valid);
}

// Test: Single valid pair with sufficient synthetic correspondences
TEST_F(RelativePoseEstimationTest_102, SingleValidPairWithSufficientMatches_102) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreatePinholeCamera(0, 500.0, 640, 480);
  cameras[1] = CreatePinholeCamera(1, 500.0, 640, 480);

  images[0] = Image(0, 0, "img0.jpg");
  images[1] = Image(1, 1, "img1.jpg");

  image_pair_t pair_id = colmap::ImagePairToPairId(0, 1);
  ImagePair pair(0, 1);
  pair.is_valid = true;

  int num_points = 100;
  GenerateSyntheticData(images[0], images[1], pair, cameras[0], cameras[1],
                        num_points);

  view_graph.image_pairs[pair_id] = pair;

  EXPECT_NO_THROW(
      EstimateRelativePoses(view_graph, cameras, images, options_));

  // After estimation, the pair should still be valid (assuming enough inliers)
  // and cam2_from_cam1 should have been updated
  auto& result_pair = view_graph.image_pairs[pair_id];
  // We can check that the translation is non-zero (since there's a real translation)
  if (result_pair.is_valid) {
    double translation_norm = result_pair.cam2_from_cam1.translation.norm();
    // The translation should be normalized or at least non-zero
    EXPECT_GT(translation_norm, 0.0);
  }
}

// Test: Multiple valid pairs
TEST_F(RelativePoseEstimationTest_102, MultipleValidPairs_102) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  const int num_images = 5;
  for (int i = 0; i < num_images; i++) {
    cameras[i] = CreatePinholeCamera(i, 500.0, 640, 480);
    images[i] = Image(i, i, "img" + std::to_string(i) + ".jpg");
  }

  // Create pairs between consecutive images
  std::vector<image_pair_t> pair_ids;
  for (int i = 0; i < num_images - 1; i++) {
    image_pair_t pair_id = colmap::ImagePairToPairId(i, i + 1);
    ImagePair pair(i, i + 1);
    pair.is_valid = true;

    int num_points = 80;
    GenerateSyntheticData(images[i], images[i + 1], pair, cameras[i],
                          cameras[i + 1], num_points);

    view_graph.image_pairs[pair_id] = pair;
    pair_ids.push_back(pair_id);
  }

  EXPECT_NO_THROW(
      EstimateRelativePoses(view_graph, cameras, images, options_));

  // All pairs should have been processed
  for (const auto& pid : pair_ids) {
    auto it = view_graph.image_pairs.find(pid);
    ASSERT_NE(it, view_graph.image_pairs.end());
    // They should either be valid with a computed pose or marked invalid
  }
}

// Test: Mix of valid and invalid pairs
TEST_F(RelativePoseEstimationTest_102, MixedValidInvalidPairs_102) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreatePinholeCamera(0, 500.0, 640, 480);
  cameras[1] = CreatePinholeCamera(1, 500.0, 640, 480);
  cameras[2] = CreatePinholeCamera(2, 500.0, 640, 480);

  images[0] = Image(0, 0, "img0.jpg");
  images[1] = Image(1, 1, "img1.jpg");
  images[2] = Image(2, 2, "img2.jpg");

  // Valid pair
  image_pair_t pair_id_01 = colmap::ImagePairToPairId(0, 1);
  ImagePair pair01(0, 1);
  pair01.is_valid = true;
  GenerateSyntheticData(images[0], images[1], pair01, cameras[0], cameras[1],
                        100);
  view_graph.image_pairs[pair_id_01] = pair01;

  // Invalid pair
  image_pair_t pair_id_12 = colmap::ImagePairToPairId(1, 2);
  ImagePair pair12(1, 2);
  pair12.is_valid = false;
  pair12.matches = Eigen::MatrixXi(0, 2);
  view_graph.image_pairs[pair_id_12] = pair12;

  EXPECT_NO_THROW(
      EstimateRelativePoses(view_graph, cameras, images, options_));

  // Invalid pair should remain invalid
  EXPECT_FALSE(view_graph.image_pairs[pair_id_12].is_valid);
}

// Test: Pair with very few matches (boundary case - may fail estimation)
TEST_F(RelativePoseEstimationTest_102, VeryFewMatches_102) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreatePinholeCamera(0, 500.0, 640, 480);
  cameras[1] = CreatePinholeCamera(1, 500.0, 640, 480);

  images[0] = Image(0, 0, "img0.jpg");
  images[1] = Image(1, 1, "img1.jpg");

  image_pair_t pair_id = colmap::ImagePairToPairId(0, 1);
  ImagePair pair(0, 1);
  pair.is_valid = true;

  // Only 3 matches - likely not enough for 5-point algorithm
  int num_points = 3;
  GenerateSyntheticData(images[0], images[1], pair, cameras[0], cameras[1],
                        num_points);

  view_graph.image_pairs[pair_id] = pair;

  // Should not crash even with very few matches
  EXPECT_NO_THROW(
      EstimateRelativePoses(view_graph, cameras, images, options_));
}

// Test: SIMPLE_PINHOLE camera model
TEST_F(RelativePoseEstimationTest_102, SimplePinholeCameraModel_102) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreateSimplePinholeCamera(0, 500.0, 640, 480);
  cameras[1] = CreateSimplePinholeCamera(1, 500.0, 640, 480);

  images[0] = Image(0, 0, "img0.jpg");
  images[1] = Image(1, 1, "img1.jpg");

  image_pair_t pair_id = colmap::ImagePairToPairId(0, 1);
  ImagePair pair(0, 1);
  pair.is_valid = true;

  int num_points = 100;
  GenerateSyntheticData(images[0], images[1], pair, cameras[0], cameras[1],
                        num_points);

  view_graph.image_pairs[pair_id] = pair;

  EXPECT_NO_THROW(
      EstimateRelativePoses(view_graph, cameras, images, options_));
}

// Test: Different cameras for each image
TEST_F(RelativePoseEstimationTest_102, DifferentCameras_102) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreatePinholeCamera(0, 400.0, 800, 600);
  cameras[1] = CreatePinholeCamera(1, 600.0, 1024, 768);

  images[0] = Image(0, 0, "img0.jpg");
  images[1] = Image(1, 1, "img1.jpg");

  image_pair_t pair_id = colmap::ImagePairToPairId(0, 1);
  ImagePair pair(0, 1);
  pair.is_valid = true;

  int num_points = 100;
  GenerateSyntheticData(images[0], images[1], pair, cameras[0], cameras[1],
                        num_points);

  view_graph.image_pairs[pair_id] = pair;

  EXPECT_NO_THROW(
      EstimateRelativePoses(view_graph, cameras, images, options_));
}

// Test: Large number of pairs to test chunking logic
TEST_F(RelativePoseEstimationTest_102, LargeNumberOfPairs_102) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  const int num_images = 25;
  for (int i = 0; i < num_images; i++) {
    cameras[i] = CreatePinholeCamera(i, 500.0, 640, 480);
    images[i] = Image(i, i, "img" + std::to_string(i) + ".jpg");
  }

  // Create pairs for all consecutive images
  for (int i = 0; i < num_images - 1; i++) {
    image_pair_t pair_id = colmap::ImagePairToPairId(i, i + 1);
    ImagePair pair(i, i + 1);
    pair.is_valid = true;

    int num_points = 50;
    GenerateSyntheticData(images[i], images[i + 1], pair, cameras[i],
                          cameras[i + 1], num_points);
    view_graph.image_pairs[pair_id] = pair;
  }

  EXPECT_NO_THROW(
      EstimateRelativePoses(view_graph, cameras, images, options_));
}

// Test: Default options construction
TEST_F(RelativePoseEstimationTest_102, DefaultOptionsConstruction_102) {
  RelativePoseEstimationOptions opts;
  // Just verify it can be constructed without issues
  SUCCEED();
}

// Test: Pair with zero matches (boundary)
TEST_F(RelativePoseEstimationTest_102, ZeroMatches_102) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreatePinholeCamera(0, 500.0, 640, 480);
  cameras[1] = CreatePinholeCamera(1, 500.0, 640, 480);

  images[0] = Image(0, 0, "img0.jpg");
  images[1] = Image(1, 1, "img1.jpg");

  image_pair_t pair_id = colmap::ImagePairToPairId(0, 1);
  ImagePair pair(0, 1);
  pair.is_valid = true;
  pair.matches = Eigen::MatrixXi(0, 2);

  view_graph.image_pairs[pair_id] = pair;

  // Should handle zero matches gracefully (may throw internally and mark invalid)
  EXPECT_NO_THROW(
      EstimateRelativePoses(view_graph, cameras, images, options_));
}

// Test: Same camera for both images sharing camera_id
TEST_F(RelativePoseEstimationTest_102, SharedCamera_102) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreatePinholeCamera(0, 500.0, 640, 480);

  // Both images share the same camera
  images[0] = Image(0, 0, "img0.jpg");
  images[1] = Image(1, 0, "img1.jpg");

  image_pair_t pair_id = colmap::ImagePairToPairId(0, 1);
  ImagePair pair(0, 1);
  pair.is_valid = true;

  int num_points = 100;
  GenerateSyntheticData(images[0], images[1], pair, cameras[0], cameras[0],
                        num_points);

  view_graph.image_pairs[pair_id] = pair;

  EXPECT_NO_THROW(
      EstimateRelativePoses(view_graph, cameras, images, options_));
}

}  // namespace
}  // namespace glomap
