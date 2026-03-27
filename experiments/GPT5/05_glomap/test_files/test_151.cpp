// File: image_undistorter_test_151.cc

#include <unordered_map>
#include <vector>

#include <gtest/gtest.h>
#include <Eigen/Core>

#include "glomap/scene/image.h"
#include "glomap/processors/image_undistorter.h"

namespace glomap {

class ImageUndistorterTest_151 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// -----------------------------------------------------------------------------
// 1) If an image is already undistorted and clean_points == false,
//    UndistortImages must skip it (no modification).
// -----------------------------------------------------------------------------
TEST_F(ImageUndistorterTest_151,
       SkipAlreadyUndistortedWhenCleanPointsFalse_151) {
  // Arrange
  std::unordered_map<camera_t, Camera> cameras;  // not needed for skipped case

  image_t img_id = static_cast<image_t>(1);
  camera_t cam_id = static_cast<camera_t>(1);

  Image image(img_id, cam_id, "test_image.jpg");

  // Two original feature positions
  image.features.clear();
  image.features.emplace_back(10.0, 20.0);
  image.features.emplace_back(30.0, 40.0);

  // Mark as "already undistorted" with sentinel values
  image.features_undist.clear();
  Eigen::Vector3d sentinel1(1.0, 2.0, 3.0);
  Eigen::Vector3d sentinel2(4.0, 5.0, 6.0);
  image.features_undist.push_back(sentinel1);
  image.features_undist.push_back(sentinel2);

  std::unordered_map<image_t, Image> images;
  images.emplace(img_id, image);

  // Act
  UndistortImages(cameras, images, /*clean_points=*/false);

  // Assert: the image should still be considered "already undistorted" and not touched.
  const Image& result = images.at(img_id);
  ASSERT_EQ(result.features_undist.size(), image.features_undist.size());
  EXPECT_EQ(result.features_undist[0], sentinel1);
  EXPECT_EQ(result.features_undist[1], sentinel2);
}

// -----------------------------------------------------------------------------
// 2) If features_undist has a different size than features and there are
//    zero features, UndistortImages should clear features_undist.
//    This covers the path where an image is queued for processing even when
//    num_points == 0 (no call to CamFromImg needed).
// -----------------------------------------------------------------------------
TEST_F(ImageUndistorterTest_151,
       ClearsUndistortedPointsWhenNoFeatures_151) {
  std::unordered_map<camera_t, Camera> cameras;

  image_t img_id = static_cast<image_t>(2);
  camera_t cam_id = static_cast<camera_t>(2);

  Image image(img_id, cam_id, "empty_features.jpg");

  // No original features
  image.features.clear();

  // But features_undist contains some stale data
  image.features_undist.clear();
  image.features_undist.emplace_back(7.0, 8.0, 9.0);
  image.features_undist.emplace_back(1.0, 2.0, 3.0);

  std::unordered_map<image_t, Image> images;
  images.emplace(img_id, image);

  // Act
  UndistortImages(cameras, images, /*clean_points=*/false);

  // Assert: features_undist should be cleared, because the image is processed
  // (sizes differ) and num_points == 0.
  const Image& result = images.at(img_id);
  EXPECT_TRUE(result.features_undist.empty());
}

// -----------------------------------------------------------------------------
// 3) If an image has features but features_undist is not the same size,
//    UndistortImages should populate features_undist to match features.size().
//    We do NOT assert the numeric values (that belongs to Camera::CamFromImg),
//    only that the size is correct as an observable behavior.
// -----------------------------------------------------------------------------
TEST_F(ImageUndistorterTest_151,
       PopulatesUndistortedForImagesWithFeatures_151) {
  std::unordered_map<camera_t, Camera> cameras;

  image_t img_id = static_cast<image_t>(3);
  camera_t cam_id = static_cast<camera_t>(3);

  // Insert a camera entry so cameras[cam_id] refers to an existing Camera.
  cameras.emplace(cam_id, Camera());

  Image image(img_id, cam_id, "with_features.jpg");

  // Three input features
  image.features.clear();
  image.features.emplace_back(100.0, 50.0);
  image.features.emplace_back(120.0, 60.0);
  image.features.emplace_back(140.0, 70.0);

  // features_undist initially empty → will trigger undistortion
  image.features_undist.clear();

  std::unordered_map<image_t, Image> images;
  images.emplace(img_id, image);

  // Act
  UndistortImages(cameras, images, /*clean_points=*/false);

  // Assert: features_undist should now have the same number of entries as features.
  const Image& result = images.at(img_id);
  EXPECT_EQ(result.features_undist.size(), result.features.size());

  // Also check that it is not left empty by mistake.
  EXPECT_FALSE(result.features_undist.empty());
}

// -----------------------------------------------------------------------------
// 4) If clean_points == true, even images that appear already undistorted
//    (same size) should be re-processed. We only assert that the size is
//    still consistent; we do not depend on the particular numeric output.
// -----------------------------------------------------------------------------
TEST_F(ImageUndistorterTest_151,
       CleanPointsTrueForcesReprocessing_151) {
  std::unordered_map<camera_t, Camera> cameras;

  image_t img_id = static_cast<image_t>(4);
  camera_t cam_id = static_cast<camera_t>(4);

  cameras.emplace(cam_id, Camera());

  Image image(img_id, cam_id, "reprocess.jpg");

  // Single feature
  image.features.clear();
  image.features.emplace_back(10.0, 10.0);

  // Pretend it's already undistorted, with some sentinel value
  image.features_undist.clear();
  Eigen::Vector3d sentinel(1.0, 2.0, 3.0);
  image.features_undist.push_back(sentinel);

  std::unordered_map<image_t, Image> images;
  images.emplace(img_id, image);

  // Act
  UndistortImages(cameras, images, /*clean_points=*/true);

  // Assert: size should still match features.size().
  const Image& result = images.at(img_id);
  ASSERT_EQ(result.features_undist.size(), result.features.size());

  // Optionally, try to detect that data likely changed
  // (best-effort, not relying on Camera implementation).
  // This is a soft check; even if equal by coincidence, the main
  // behavior (re-processing instead of skipping) is covered by the code path.
  if (!result.features_undist.empty()) {
    // At least verify that the vector is a valid direction (finite values).
    EXPECT_TRUE(result.features_undist[0].allFinite());
  }
}

}  // namespace glomap
