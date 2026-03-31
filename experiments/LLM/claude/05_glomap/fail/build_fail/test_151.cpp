#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>
#include <Eigen/Core>

#include "glomap/processors/image_undistorter.h"
#include "glomap/scene/image.h"
#include "glomap/scene/camera.h"
#include "glomap/types.h"

namespace glomap {
namespace {

class ImageUndistorterTest_151 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up a simple pinhole camera (no distortion) for testing
    // Camera ID 0
    Camera cam;
    cam.camera_id = 0;
    // Set up as a simple pinhole camera using colmap's camera model
    // We use PINHOLE model which has no distortion
    cam.model_id = colmap::CameraModelId::kPinhole;
    cam.width = 640;
    cam.height = 480;
    cam.params = {500.0, 500.0, 320.0, 240.0};  // fx, fy, cx, cy
    cameras_[0] = cam;
  }

  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<image_t, Image> images_;
};

// Test that UndistortImages works with empty images map
TEST_F(ImageUndistorterTest_151, EmptyImages_151) {
  UndistortImages(cameras_, images_, false);
  EXPECT_TRUE(images_.empty());
}

// Test that UndistortImages undistorts features for a single image
TEST_F(ImageUndistorterTest_151, SingleImageWithFeatures_151) {
  Image img(0, 0, "test.jpg");
  img.features.push_back(Eigen::Vector2d(320.0, 240.0));  // principal point
  img.features.push_back(Eigen::Vector2d(0.0, 0.0));
  img.features.push_back(Eigen::Vector2d(640.0, 480.0));
  images_[0] = img;

  UndistortImages(cameras_, images_, false);

  EXPECT_EQ(images_[0].features_undist.size(), 3);
  // Each undistorted feature should be a normalized 3D point (homogeneous, normalized)
  for (const auto& pt : images_[0].features_undist) {
    EXPECT_NEAR(pt.norm(), 1.0, 1e-10);
  }
}

// Test that UndistortImages does not re-undistort already undistorted images
TEST_F(ImageUndistorterTest_151, SkipAlreadyUndistorted_151) {
  Image img(0, 0, "test.jpg");
  img.features.push_back(Eigen::Vector2d(100.0, 200.0));
  // Pre-populate features_undist with same size
  img.features_undist.push_back(Eigen::Vector3d(1.0, 2.0, 3.0));
  images_[0] = img;

  UndistortImages(cameras_, images_, false);

  // Should not have changed since it was already "undistorted"
  ASSERT_EQ(images_[0].features_undist.size(), 1);
  EXPECT_NEAR(images_[0].features_undist[0].x(), 1.0, 1e-10);
  EXPECT_NEAR(images_[0].features_undist[0].y(), 2.0, 1e-10);
  EXPECT_NEAR(images_[0].features_undist[0].z(), 3.0, 1e-10);
}

// Test that clean_points forces re-undistortion even if already done
TEST_F(ImageUndistorterTest_151, CleanPointsForcesReUndistortion_151) {
  Image img(0, 0, "test.jpg");
  img.features.push_back(Eigen::Vector2d(320.0, 240.0));
  // Pre-populate features_undist with same size but different values
  img.features_undist.push_back(Eigen::Vector3d(99.0, 99.0, 99.0));
  images_[0] = img;

  UndistortImages(cameras_, images_, true);

  // Should have been re-undistorted
  ASSERT_EQ(images_[0].features_undist.size(), 1);
  // The values should have changed from (99, 99, 99)
  // For pinhole at principal point, undistorted should be (0, 0, 1) normalized
  EXPECT_NEAR(images_[0].features_undist[0].norm(), 1.0, 1e-10);
}

// Test with image that has no features
TEST_F(ImageUndistorterTest_151, ImageWithNoFeatures_151) {
  Image img(0, 0, "test.jpg");
  // No features added
  images_[0] = img;

  UndistortImages(cameras_, images_, false);

  EXPECT_EQ(images_[0].features_undist.size(), 0);
}

// Test with multiple images
TEST_F(ImageUndistorterTest_151, MultipleImages_151) {
  Image img1(0, 0, "test1.jpg");
  img1.features.push_back(Eigen::Vector2d(100.0, 100.0));
  img1.features.push_back(Eigen::Vector2d(200.0, 200.0));
  images_[0] = img1;

  Image img2(1, 0, "test2.jpg");
  img2.features.push_back(Eigen::Vector2d(300.0, 300.0));
  images_[1] = img2;

  Image img3(2, 0, "test3.jpg");
  img3.features.push_back(Eigen::Vector2d(50.0, 50.0));
  img3.features.push_back(Eigen::Vector2d(150.0, 150.0));
  img3.features.push_back(Eigen::Vector2d(250.0, 250.0));
  images_[2] = img3;

  UndistortImages(cameras_, images_, false);

  EXPECT_EQ(images_[0].features_undist.size(), 2);
  EXPECT_EQ(images_[1].features_undist.size(), 1);
  EXPECT_EQ(images_[2].features_undist.size(), 3);

  // All should be normalized
  for (auto& [id, image] : images_) {
    for (const auto& pt : image.features_undist) {
      EXPECT_NEAR(pt.norm(), 1.0, 1e-10);
    }
  }
}

// Test that features_undist has correct size matching features
TEST_F(ImageUndistorterTest_151, UndistortedSizeMatchesFeatures_151) {
  Image img(0, 0, "test.jpg");
  for (int i = 0; i < 100; ++i) {
    img.features.push_back(Eigen::Vector2d(i * 5.0, i * 3.0));
  }
  images_[0] = img;

  UndistortImages(cameras_, images_, false);

  EXPECT_EQ(images_[0].features_undist.size(), images_[0].features.size());
}

// Test mixed scenario: some images already undistorted, some not
TEST_F(ImageUndistorterTest_151, MixedUndistortedAndNot_151) {
  // Image 0: already undistorted
  Image img0(0, 0, "test0.jpg");
  img0.features.push_back(Eigen::Vector2d(100.0, 100.0));
  img0.features_undist.push_back(Eigen::Vector3d(0.5, 0.5, 0.7071));
  images_[0] = img0;

  // Image 1: not undistorted
  Image img1(1, 0, "test1.jpg");
  img1.features.push_back(Eigen::Vector2d(200.0, 200.0));
  images_[1] = img1;

  UndistortImages(cameras_, images_, false);

  // Image 0 should remain unchanged
  ASSERT_EQ(images_[0].features_undist.size(), 1);
  EXPECT_NEAR(images_[0].features_undist[0].x(), 0.5, 1e-10);

  // Image 1 should be undistorted
  ASSERT_EQ(images_[1].features_undist.size(), 1);
  EXPECT_NEAR(images_[1].features_undist[0].norm(), 1.0, 1e-10);
}

// Test that features_undist size mismatch triggers re-undistortion
TEST_F(ImageUndistorterTest_151, SizeMismatchTriggersReUndistortion_151) {
  Image img(0, 0, "test.jpg");
  img.features.push_back(Eigen::Vector2d(100.0, 100.0));
  img.features.push_back(Eigen::Vector2d(200.0, 200.0));
  // Only one undistorted point but two features -> mismatch
  img.features_undist.push_back(Eigen::Vector3d(1.0, 0.0, 0.0));
  images_[0] = img;

  UndistortImages(cameras_, images_, false);

  // Should have been re-undistorted to match feature count
  EXPECT_EQ(images_[0].features_undist.size(), 2);
  for (const auto& pt : images_[0].features_undist) {
    EXPECT_NEAR(pt.norm(), 1.0, 1e-10);
  }
}

// Test undistortion at principal point produces (0,0,1) direction
TEST_F(ImageUndistorterTest_151, PrincipalPointUndistortion_151) {
  Image img(0, 0, "test.jpg");
  // Feature at principal point (320, 240) for our camera
  img.features.push_back(Eigen::Vector2d(320.0, 240.0));
  images_[0] = img;

  UndistortImages(cameras_, images_, false);

  ASSERT_EQ(images_[0].features_undist.size(), 1);
  // At the principal point, the undistorted normalized point should be (0, 0, 1)
  EXPECT_NEAR(images_[0].features_undist[0].x(), 0.0, 1e-8);
  EXPECT_NEAR(images_[0].features_undist[0].y(), 0.0, 1e-8);
  EXPECT_NEAR(images_[0].features_undist[0].z(), 1.0, 1e-8);
}

// Test with multiple cameras
TEST_F(ImageUndistorterTest_151, MultipleCameras_151) {
  // Add a second camera with different parameters
  Camera cam2;
  cam2.camera_id = 1;
  cam2.model_id = colmap::CameraModelId::kPinhole;
  cam2.width = 800;
  cam2.height = 600;
  cam2.params = {600.0, 600.0, 400.0, 300.0};
  cameras_[1] = cam2;

  Image img0(0, 0, "test0.jpg");
  img0.features.push_back(Eigen::Vector2d(320.0, 240.0));
  images_[0] = img0;

  Image img1(1, 1, "test1.jpg");
  img1.features.push_back(Eigen::Vector2d(400.0, 300.0));
  images_[1] = img1;

  UndistortImages(cameras_, images_, false);

  ASSERT_EQ(images_[0].features_undist.size(), 1);
  ASSERT_EQ(images_[1].features_undist.size(), 1);

  // Both at principal points, should be (0, 0, 1)
  EXPECT_NEAR(images_[0].features_undist[0].x(), 0.0, 1e-8);
  EXPECT_NEAR(images_[0].features_undist[0].y(), 0.0, 1e-8);
  EXPECT_NEAR(images_[0].features_undist[0].z(), 1.0, 1e-8);

  EXPECT_NEAR(images_[1].features_undist[0].x(), 0.0, 1e-8);
  EXPECT_NEAR(images_[1].features_undist[0].y(), 0.0, 1e-8);
  EXPECT_NEAR(images_[1].features_undist[0].z(), 1.0, 1e-8);
}

}  // namespace
}  // namespace glomap
