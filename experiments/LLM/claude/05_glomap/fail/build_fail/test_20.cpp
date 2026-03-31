#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/estimators/view_graph_calibration.h"
#include "glomap/types.h"

#include <unordered_map>

namespace glomap {
namespace {

class ViewGraphCalibratorTest_20 : public ::testing::Test {
 protected:
  void SetUp() override {
    calibrator_ = std::make_unique<ViewGraphCalibrator>();
  }

  // Helper to create a basic camera
  Camera CreateCamera(camera_t camera_id, int width = 640, int height = 480) {
    Camera camera;
    camera.camera_id = camera_id;
    camera.model_id = 0;  // SIMPLE_PINHOLE or similar
    camera.width = width;
    camera.height = height;
    camera.params = {500.0, 320.0, 240.0};  // fx, cx, cy for simple pinhole
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

  // Helper to create an image pair
  ImagePair CreateImagePair(image_t id1, image_t id2) {
    ImagePair pair;
    pair.image_id1 = id1;
    pair.image_id2 = id2;
    pair.is_valid = true;
    // Set a reasonable relative pose
    pair.cam2_from_cam1 = Rigid3d(Eigen::Quaterniond::Identity(),
                                   Eigen::Vector3d(1.0, 0.0, 0.0));
    return pair;
  }

  std::unique_ptr<ViewGraphCalibrator> calibrator_;
};

// Test with empty cameras and images - no cameras to optimize
TEST_F(ViewGraphCalibratorTest_20, EmptyCamerasReturnsTrue_20) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  bool result = calibrator_->Solve(view_graph, cameras, images);
  EXPECT_TRUE(result);
}

// Test with empty view graph but some cameras - no pairs means no cameras parameterized
TEST_F(ViewGraphCalibratorTest_20, NoPairsNoCamerasToOptimize_20) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreateCamera(0);
  images[0] = CreateImage(0, 0);

  bool result = calibrator_->Solve(view_graph, cameras, images);
  EXPECT_TRUE(result);
}

// Test with a single image pair and two cameras (small problem, < 50 cameras -> DENSE solver)
TEST_F(ViewGraphCalibratorTest_20, SinglePairSmallProblem_20) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreateCamera(0);
  cameras[1] = CreateCamera(1);
  images[0] = CreateImage(0, 0);
  images[1] = CreateImage(1, 1);

  image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
  view_graph.image_pairs[pair_id] = CreateImagePair(0, 1);

  bool result = calibrator_->Solve(view_graph, cameras, images);
  // The solver should be able to handle this small problem
  EXPECT_TRUE(result);
}

// Test with multiple pairs forming a small chain
TEST_F(ViewGraphCalibratorTest_20, SmallChainOfPairs_20) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  const int num_images = 5;
  for (int i = 0; i < num_images; ++i) {
    cameras[i] = CreateCamera(i);
    images[i] = CreateImage(i, i);
  }

  // Create a chain: 0-1, 1-2, 2-3, 3-4
  for (int i = 0; i < num_images - 1; ++i) {
    image_pair_t pair_id = ImagePair::ImagePairToPairId(i, i + 1);
    view_graph.image_pairs[pair_id] = CreateImagePair(i, i + 1);
  }

  bool result = calibrator_->Solve(view_graph, cameras, images);
  EXPECT_TRUE(result);
}

// Test that cameras fewer than 50 use dense solver (boundary: exactly 49 cameras)
TEST_F(ViewGraphCalibratorTest_20, BoundaryUnder50Cameras_20) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  // Create 49 cameras and images
  for (int i = 0; i < 49; ++i) {
    cameras[i] = CreateCamera(i);
    images[i] = CreateImage(i, i);
  }

  // Create pairs for consecutive images
  for (int i = 0; i < 48; ++i) {
    image_pair_t pair_id = ImagePair::ImagePairToPairId(i, i + 1);
    view_graph.image_pairs[pair_id] = CreateImagePair(i, i + 1);
  }

  bool result = calibrator_->Solve(view_graph, cameras, images);
  EXPECT_TRUE(result);
}

// Test boundary at exactly 50 cameras (should use SPARSE solver)
TEST_F(ViewGraphCalibratorTest_20, BoundaryExactly50Cameras_20) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  for (int i = 0; i < 50; ++i) {
    cameras[i] = CreateCamera(i);
    images[i] = CreateImage(i, i);
  }

  for (int i = 0; i < 49; ++i) {
    image_pair_t pair_id = ImagePair::ImagePairToPairId(i, i + 1);
    view_graph.image_pairs[pair_id] = CreateImagePair(i, i + 1);
  }

  bool result = calibrator_->Solve(view_graph, cameras, images);
  EXPECT_TRUE(result);
}

// Test calling Solve multiple times (reset should handle re-initialization)
TEST_F(ViewGraphCalibratorTest_20, MultipleSolveCalls_20) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreateCamera(0);
  cameras[1] = CreateCamera(1);
  images[0] = CreateImage(0, 0);
  images[1] = CreateImage(1, 1);

  image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
  view_graph.image_pairs[pair_id] = CreateImagePair(0, 1);

  bool result1 = calibrator_->Solve(view_graph, cameras, images);
  EXPECT_TRUE(result1);

  // Solve again - should reset and work correctly
  bool result2 = calibrator_->Solve(view_graph, cameras, images);
  EXPECT_TRUE(result2);
}

// Test with shared camera (multiple images using same camera)
TEST_F(ViewGraphCalibratorTest_20, SharedCamera_20) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  // Single camera shared by multiple images
  cameras[0] = CreateCamera(0);
  images[0] = CreateImage(0, 0);
  images[1] = CreateImage(1, 0);
  images[2] = CreateImage(2, 0);

  image_pair_t pair_id1 = ImagePair::ImagePairToPairId(0, 1);
  view_graph.image_pairs[pair_id1] = CreateImagePair(0, 1);

  image_pair_t pair_id2 = ImagePair::ImagePairToPairId(1, 2);
  view_graph.image_pairs[pair_id2] = CreateImagePair(1, 2);

  bool result = calibrator_->Solve(view_graph, cameras, images);
  EXPECT_TRUE(result);
}

// Test with invalid pairs in view graph
TEST_F(ViewGraphCalibratorTest_20, InvalidPairsIgnored_20) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[0] = CreateCamera(0);
  cameras[1] = CreateCamera(1);
  images[0] = CreateImage(0, 0);
  images[1] = CreateImage(1, 1);

  image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
  ImagePair pair = CreateImagePair(0, 1);
  pair.is_valid = false;
  view_graph.image_pairs[pair_id] = pair;

  bool result = calibrator_->Solve(view_graph, cameras, images);
  // With no valid pairs, there may be no cameras to optimize
  EXPECT_TRUE(result);
}

// Test with cameras that have prior focal length
TEST_F(ViewGraphCalibratorTest_20, CamerasWithPriorFocalLength_20) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  Camera cam0 = CreateCamera(0);
  cam0.has_prior_focal_length = true;
  cameras[0] = cam0;

  Camera cam1 = CreateCamera(1);
  cam1.has_prior_focal_length = true;
  cameras[1] = cam1;

  images[0] = CreateImage(0, 0);
  images[1] = CreateImage(1, 1);

  image_pair_t pair_id = ImagePair::ImagePairToPairId(0, 1);
  view_graph.image_pairs[pair_id] = CreateImagePair(0, 1);

  bool result = calibrator_->Solve(view_graph, cameras, images);
  EXPECT_TRUE(result);
}

// Test with a fully connected small graph
TEST_F(ViewGraphCalibratorTest_20, FullyConnectedSmallGraph_20) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  const int num_images = 4;
  for (int i = 0; i < num_images; ++i) {
    cameras[i] = CreateCamera(i);
    images[i] = CreateImage(i, i);
  }

  // Fully connected: all pairs
  for (int i = 0; i < num_images; ++i) {
    for (int j = i + 1; j < num_images; ++j) {
      image_pair_t pair_id = ImagePair::ImagePairToPairId(i, j);
      view_graph.image_pairs[pair_id] = CreateImagePair(i, j);
    }
  }

  bool result = calibrator_->Solve(view_graph, cameras, images);
  EXPECT_TRUE(result);
}

}  // namespace
}  // namespace glomap
