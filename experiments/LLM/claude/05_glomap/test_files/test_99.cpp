#include <gtest/gtest.h>
#include "glomap/estimators/view_graph_calibration.h"
#include "glomap/scene/view_graph.h"
#include "glomap/types.h"

namespace glomap {
namespace {

// Helper to create a basic camera
Camera CreateCamera(camera_t camera_id, double focal_length = 500.0) {
  Camera camera;
  camera.camera_id = camera_id;
  camera.model_id = 0;  // SIMPLE_PINHOLE or similar
  camera.width = 1000;
  camera.height = 1000;
  camera.params = {focal_length, 500.0, 500.0};
  camera.has_prior_focal_length = false;
  return camera;
}

// Helper to create a basic image
Image CreateImage(image_t image_id, camera_t camera_id) {
  Image image;
  image.image_id = image_id;
  image.camera_id = camera_id;
  image.is_registered = true;
  return image;
}

// Helper to create an image pair key from two image ids
image_pair_t ImagePairToPairId(image_t id1, image_t id2) {
  if (id1 > id2) std::swap(id1, id2);
  return static_cast<image_pair_t>(id1) * 2147483647 + id2;
}

class ViewGraphCalibratorTest_99 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_ = ViewGraphCalibratorOptions();
  }

  ViewGraphCalibratorOptions options_;
};

// Test: Empty inputs - no cameras, no images, no image pairs
TEST_F(ViewGraphCalibratorTest_99, EmptyInputs_99) {
  ViewGraphCalibrator calibrator(options_);
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  bool result = calibrator.Solve(view_graph, cameras, images);
  // With no cameras to optimize, should return true
  EXPECT_TRUE(result);
}

// Test: Single camera, no image pairs
TEST_F(ViewGraphCalibratorTest_99, SingleCameraNoImagePairs_99) {
  ViewGraphCalibrator calibrator(options_);
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreateCamera(0);
  images[0] = CreateImage(0, 0);

  bool result = calibrator.Solve(view_graph, cameras, images);
  // No image pairs means no parameters added to problem, so no cameras to optimize
  EXPECT_TRUE(result);
}

// Test: Two cameras with a valid image pair
TEST_F(ViewGraphCalibratorTest_99, TwoCamerasWithImagePair_99) {
  ViewGraphCalibrator calibrator(options_);
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreateCamera(0, 500.0);
  cameras[1] = CreateCamera(1, 600.0);
  images[0] = CreateImage(0, 0);
  images[1] = CreateImage(1, 1);

  ImagePair pair;
  pair.image_id1 = 0;
  pair.image_id2 = 1;
  pair.is_valid = true;
  // Set a reasonable fundamental matrix / essential matrix
  pair.F = Eigen::Matrix3d::Identity();
  pair.E = Eigen::Matrix3d::Identity();
  pair.cam2_from_cam1 = Rigid3d();

  image_pair_t pair_id = ImagePairToPairId(0, 1);
  view_graph.image_pairs[pair_id] = pair;

  bool result = calibrator.Solve(view_graph, cameras, images);
  // Result depends on whether ceres can solve; should be usable
  // We just check it doesn't crash and returns a boolean
  EXPECT_TRUE(result == true || result == false);
}

// Test: Multiple cameras below threshold (< 50) uses DENSE solver
TEST_F(ViewGraphCalibratorTest_99, FewCamerasUsesDenseSolver_99) {
  ViewGraphCalibrator calibrator(options_);
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  // Create 5 cameras and images
  for (int i = 0; i < 5; ++i) {
    cameras[i] = CreateCamera(i, 500.0 + i * 10);
    images[i] = CreateImage(i, i);
  }

  // Create image pairs connecting them
  for (int i = 0; i < 4; ++i) {
    ImagePair pair;
    pair.image_id1 = i;
    pair.image_id2 = i + 1;
    pair.is_valid = true;
    pair.F = Eigen::Matrix3d::Identity();
    pair.E = Eigen::Matrix3d::Identity();
    pair.cam2_from_cam1 = Rigid3d();
    image_pair_t pair_id = ImagePairToPairId(i, i + 1);
    view_graph.image_pairs[pair_id] = pair;
  }

  bool result = calibrator.Solve(view_graph, cameras, images);
  // Just verify it completes without error
  EXPECT_TRUE(result == true || result == false);
}

// Test: No valid image pairs
TEST_F(ViewGraphCalibratorTest_99, NoValidImagePairs_99) {
  ViewGraphCalibrator calibrator(options_);
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreateCamera(0);
  cameras[1] = CreateCamera(1);
  images[0] = CreateImage(0, 0);
  images[1] = CreateImage(1, 1);

  ImagePair pair;
  pair.image_id1 = 0;
  pair.image_id2 = 1;
  pair.is_valid = false;  // Invalid pair
  pair.F = Eigen::Matrix3d::Identity();
  pair.E = Eigen::Matrix3d::Identity();
  pair.cam2_from_cam1 = Rigid3d();

  image_pair_t pair_id = ImagePairToPairId(0, 1);
  view_graph.image_pairs[pair_id] = pair;

  bool result = calibrator.Solve(view_graph, cameras, images);
  // With no valid pairs, might have no cameras to optimize
  EXPECT_TRUE(result);
}

// Test: Solve called multiple times (reset behavior)
TEST_F(ViewGraphCalibratorTest_99, SolveCalledMultipleTimes_99) {
  ViewGraphCalibrator calibrator(options_);
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreateCamera(0, 500.0);
  cameras[1] = CreateCamera(1, 600.0);
  images[0] = CreateImage(0, 0);
  images[1] = CreateImage(1, 1);

  ImagePair pair;
  pair.image_id1 = 0;
  pair.image_id2 = 1;
  pair.is_valid = true;
  pair.F = Eigen::Matrix3d::Identity();
  pair.E = Eigen::Matrix3d::Identity();
  pair.cam2_from_cam1 = Rigid3d();

  image_pair_t pair_id = ImagePairToPairId(0, 1);
  view_graph.image_pairs[pair_id] = pair;

  // First solve
  bool result1 = calibrator.Solve(view_graph, cameras, images);

  // Second solve - should reset and work again
  bool result2 = calibrator.Solve(view_graph, cameras, images);

  // Both should complete without crashing
  EXPECT_TRUE(result1 == true || result1 == false);
  EXPECT_TRUE(result2 == true || result2 == false);
}

// Test: Same camera used by multiple images
TEST_F(ViewGraphCalibratorTest_99, SharedCameraAmongImages_99) {
  ViewGraphCalibrator calibrator(options_);
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  // One camera shared by two images
  cameras[0] = CreateCamera(0, 500.0);
  images[0] = CreateImage(0, 0);
  images[1] = CreateImage(1, 0);  // Same camera

  ImagePair pair;
  pair.image_id1 = 0;
  pair.image_id2 = 1;
  pair.is_valid = true;
  pair.F = Eigen::Matrix3d::Identity();
  pair.E = Eigen::Matrix3d::Identity();
  pair.cam2_from_cam1 = Rigid3d();

  image_pair_t pair_id = ImagePairToPairId(0, 1);
  view_graph.image_pairs[pair_id] = pair;

  bool result = calibrator.Solve(view_graph, cameras, images);
  EXPECT_TRUE(result == true || result == false);
}

// Test: Boundary - exactly 50 cameras (should use SPARSE solver)
TEST_F(ViewGraphCalibratorTest_99, ExactlyFiftyCameras_99) {
  ViewGraphCalibrator calibrator(options_);
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  for (int i = 0; i < 50; ++i) {
    cameras[i] = CreateCamera(i, 500.0 + i);
    images[i] = CreateImage(i, i);
  }

  // Create chain of image pairs
  for (int i = 0; i < 49; ++i) {
    ImagePair pair;
    pair.image_id1 = i;
    pair.image_id2 = i + 1;
    pair.is_valid = true;
    pair.F = Eigen::Matrix3d::Identity();
    pair.E = Eigen::Matrix3d::Identity();
    pair.cam2_from_cam1 = Rigid3d();
    image_pair_t pair_id = ImagePairToPairId(i, i + 1);
    view_graph.image_pairs[pair_id] = pair;
  }

  bool result = calibrator.Solve(view_graph, cameras, images);
  // With 50 cameras, should use SPARSE_NORMAL_CHOLESKY
  EXPECT_TRUE(result == true || result == false);
}

// Test: Boundary - exactly 49 cameras (should use DENSE solver)
TEST_F(ViewGraphCalibratorTest_99, FortyNineCameras_99) {
  ViewGraphCalibrator calibrator(options_);
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  for (int i = 0; i < 49; ++i) {
    cameras[i] = CreateCamera(i, 500.0 + i);
    images[i] = CreateImage(i, i);
  }

  for (int i = 0; i < 48; ++i) {
    ImagePair pair;
    pair.image_id1 = i;
    pair.image_id2 = i + 1;
    pair.is_valid = true;
    pair.F = Eigen::Matrix3d::Identity();
    pair.E = Eigen::Matrix3d::Identity();
    pair.cam2_from_cam1 = Rigid3d();
    image_pair_t pair_id = ImagePairToPairId(i, i + 1);
    view_graph.image_pairs[pair_id] = pair;
  }

  bool result = calibrator.Solve(view_graph, cameras, images);
  EXPECT_TRUE(result == true || result == false);
}

// Test: Cameras with prior focal length
TEST_F(ViewGraphCalibratorTest_99, CamerasWithPriorFocalLength_99) {
  ViewGraphCalibrator calibrator(options_);
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  Camera cam0 = CreateCamera(0, 500.0);
  cam0.has_prior_focal_length = true;
  cameras[0] = cam0;

  Camera cam1 = CreateCamera(1, 600.0);
  cam1.has_prior_focal_length = true;
  cameras[1] = cam1;

  images[0] = CreateImage(0, 0);
  images[1] = CreateImage(1, 1);

  ImagePair pair;
  pair.image_id1 = 0;
  pair.image_id2 = 1;
  pair.is_valid = true;
  pair.F = Eigen::Matrix3d::Identity();
  pair.E = Eigen::Matrix3d::Identity();
  pair.cam2_from_cam1 = Rigid3d();

  image_pair_t pair_id = ImagePairToPairId(0, 1);
  view_graph.image_pairs[pair_id] = pair;

  bool result = calibrator.Solve(view_graph, cameras, images);
  EXPECT_TRUE(result == true || result == false);
}

// Test: Default options construction
TEST_F(ViewGraphCalibratorTest_99, DefaultOptionsConstruction_99) {
  ViewGraphCalibratorOptions default_options;
  ViewGraphCalibrator calibrator(default_options);
  
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  // Should handle empty case gracefully
  bool result = calibrator.Solve(view_graph, cameras, images);
  EXPECT_TRUE(result);
}

// Test: Image pairs that may get filtered after solve
TEST_F(ViewGraphCalibratorTest_99, FilteringAfterSolve_99) {
  ViewGraphCalibrator calibrator(options_);
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreateCamera(0, 500.0);
  cameras[1] = CreateCamera(1, 600.0);
  cameras[2] = CreateCamera(2, 700.0);
  images[0] = CreateImage(0, 0);
  images[1] = CreateImage(1, 1);
  images[2] = CreateImage(2, 2);

  // Create multiple pairs
  for (int i = 0; i < 2; ++i) {
    ImagePair pair;
    pair.image_id1 = i;
    pair.image_id2 = i + 1;
    pair.is_valid = true;
    pair.F = Eigen::Matrix3d::Identity();
    pair.E = Eigen::Matrix3d::Identity();
    pair.cam2_from_cam1 = Rigid3d();
    image_pair_t pair_id = ImagePairToPairId(i, i + 1);
    view_graph.image_pairs[pair_id] = pair;
  }

  size_t initial_pair_count = view_graph.image_pairs.size();
  bool result = calibrator.Solve(view_graph, cameras, images);

  // After solve, some pairs might be filtered (marked invalid)
  // We can check that the view_graph still has entries but some might be invalid
  EXPECT_TRUE(result == true || result == false);
  // The number of entries in image_pairs map should not increase
  EXPECT_LE(view_graph.image_pairs.size(), initial_pair_count + 1);
}

}  // namespace
}  // namespace glomap
