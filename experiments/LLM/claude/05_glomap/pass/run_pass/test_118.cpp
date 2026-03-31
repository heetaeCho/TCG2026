#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/io/colmap_converter.h"
#include "glomap/scene/image.h"
#include <colmap/scene/image.h>

#include <string>
#include <vector>
#include <Eigen/Core>

namespace glomap {
namespace {

class ConvertGlomapToColmapImageTest_118 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test that basic image properties are correctly transferred
TEST_F(ConvertGlomapToColmapImageTest_118, BasicPropertiesTransferred_118) {
  Image glomap_image(1, 2, "test_image.jpg");
  glomap_image.frame_id = 5;

  colmap::Image colmap_image;
  ConvertGlomapToColmapImage(glomap_image, colmap_image, false);

  EXPECT_EQ(colmap_image.ImageId(), 1);
  EXPECT_EQ(colmap_image.CameraId(), 2);
  EXPECT_EQ(colmap_image.Name(), "test_image.jpg");
  EXPECT_EQ(colmap_image.FrameId(), 5);
}

// Test that image_id is set correctly
TEST_F(ConvertGlomapToColmapImageTest_118, ImageIdIsSet_118) {
  Image glomap_image(42, 1, "img.png");
  colmap::Image colmap_image;

  ConvertGlomapToColmapImage(glomap_image, colmap_image, false);

  EXPECT_EQ(colmap_image.ImageId(), 42);
}

// Test that camera_id is set correctly
TEST_F(ConvertGlomapToColmapImageTest_118, CameraIdIsSet_118) {
  Image glomap_image(1, 99, "img.png");
  colmap::Image colmap_image;

  ConvertGlomapToColmapImage(glomap_image, colmap_image, false);

  EXPECT_EQ(colmap_image.CameraId(), 99);
}

// Test that file name is set correctly
TEST_F(ConvertGlomapToColmapImageTest_118, FileNameIsSet_118) {
  Image glomap_image(1, 1, "path/to/my_image.jpg");
  colmap::Image colmap_image;

  ConvertGlomapToColmapImage(glomap_image, colmap_image, false);

  EXPECT_EQ(colmap_image.Name(), "path/to/my_image.jpg");
}

// Test that frame_id is set correctly
TEST_F(ConvertGlomapToColmapImageTest_118, FrameIdIsSet_118) {
  Image glomap_image(1, 1, "img.png");
  glomap_image.frame_id = 7;
  colmap::Image colmap_image;

  ConvertGlomapToColmapImage(glomap_image, colmap_image, false);

  EXPECT_EQ(colmap_image.FrameId(), 7);
}

// Test that when keep_points is true, features (Points2D) are transferred
TEST_F(ConvertGlomapToColmapImageTest_118, KeepPointsTrueTransfersFeatures_118) {
  Image glomap_image(1, 1, "img.png");

  std::vector<Eigen::Vector2d> features;
  features.push_back(Eigen::Vector2d(10.0, 20.0));
  features.push_back(Eigen::Vector2d(30.0, 40.0));
  features.push_back(Eigen::Vector2d(50.0, 60.0));
  glomap_image.features = features;

  colmap::Image colmap_image;
  ConvertGlomapToColmapImage(glomap_image, colmap_image, true);

  EXPECT_EQ(colmap_image.NumPoints2D(), 3);
  EXPECT_NEAR(colmap_image.Point2D(0).xy(0), 10.0, 1e-9);
  EXPECT_NEAR(colmap_image.Point2D(0).xy(1), 20.0, 1e-9);
  EXPECT_NEAR(colmap_image.Point2D(1).xy(0), 30.0, 1e-9);
  EXPECT_NEAR(colmap_image.Point2D(1).xy(1), 40.0, 1e-9);
  EXPECT_NEAR(colmap_image.Point2D(2).xy(0), 50.0, 1e-9);
  EXPECT_NEAR(colmap_image.Point2D(2).xy(1), 60.0, 1e-9);
}

// Test that when keep_points is false, features (Points2D) are NOT transferred
TEST_F(ConvertGlomapToColmapImageTest_118, KeepPointsFalseDoesNotTransferFeatures_118) {
  Image glomap_image(1, 1, "img.png");

  std::vector<Eigen::Vector2d> features;
  features.push_back(Eigen::Vector2d(10.0, 20.0));
  features.push_back(Eigen::Vector2d(30.0, 40.0));
  glomap_image.features = features;

  colmap::Image colmap_image;
  ConvertGlomapToColmapImage(glomap_image, colmap_image, false);

  EXPECT_EQ(colmap_image.NumPoints2D(), 0);
}

// Test with empty file name
TEST_F(ConvertGlomapToColmapImageTest_118, EmptyFileName_118) {
  Image glomap_image(1, 1, "");
  colmap::Image colmap_image;

  ConvertGlomapToColmapImage(glomap_image, colmap_image, false);

  EXPECT_EQ(colmap_image.Name(), "");
}

// Test with empty features and keep_points true
TEST_F(ConvertGlomapToColmapImageTest_118, EmptyFeaturesWithKeepPointsTrue_118) {
  Image glomap_image(1, 1, "img.png");
  glomap_image.features.clear();

  colmap::Image colmap_image;
  ConvertGlomapToColmapImage(glomap_image, colmap_image, true);

  EXPECT_EQ(colmap_image.NumPoints2D(), 0);
}

// Test with default frame_id (-1)
TEST_F(ConvertGlomapToColmapImageTest_118, DefaultFrameId_118) {
  Image glomap_image(1, 1, "img.png");
  // frame_id defaults to -1 based on the header

  colmap::Image colmap_image;
  ConvertGlomapToColmapImage(glomap_image, colmap_image, false);

  // The frame_id should be set to whatever the default is
  // Based on the struct definition, default is -1
}

// Test that previously set colmap_image fields are overwritten
TEST_F(ConvertGlomapToColmapImageTest_118, OverwritesExistingColmapImageFields_118) {
  Image glomap_image(10, 20, "new_image.jpg");
  glomap_image.frame_id = 30;

  colmap::Image colmap_image;
  colmap_image.SetImageId(1);
  colmap_image.SetCameraId(2);
  colmap_image.SetName("old_image.jpg");

  ConvertGlomapToColmapImage(glomap_image, colmap_image, false);

  EXPECT_EQ(colmap_image.ImageId(), 10);
  EXPECT_EQ(colmap_image.CameraId(), 20);
  EXPECT_EQ(colmap_image.Name(), "new_image.jpg");
  EXPECT_EQ(colmap_image.FrameId(), 30);
}

// Test with a large number of features
TEST_F(ConvertGlomapToColmapImageTest_118, LargeNumberOfFeatures_118) {
  Image glomap_image(1, 1, "img.png");

  const int num_features = 10000;
  std::vector<Eigen::Vector2d> features;
  features.reserve(num_features);
  for (int i = 0; i < num_features; ++i) {
    features.push_back(Eigen::Vector2d(static_cast<double>(i), static_cast<double>(i * 2)));
  }
  glomap_image.features = features;

  colmap::Image colmap_image;
  ConvertGlomapToColmapImage(glomap_image, colmap_image, true);

  EXPECT_EQ(colmap_image.NumPoints2D(), static_cast<size_t>(num_features));
}

// Test with a single feature point
TEST_F(ConvertGlomapToColmapImageTest_118, SingleFeaturePoint_118) {
  Image glomap_image(1, 1, "img.png");

  std::vector<Eigen::Vector2d> features;
  features.push_back(Eigen::Vector2d(100.5, 200.5));
  glomap_image.features = features;

  colmap::Image colmap_image;
  ConvertGlomapToColmapImage(glomap_image, colmap_image, true);

  EXPECT_EQ(colmap_image.NumPoints2D(), 1);
  EXPECT_NEAR(colmap_image.Point2D(0).xy(0), 100.5, 1e-9);
  EXPECT_NEAR(colmap_image.Point2D(0).xy(1), 200.5, 1e-9);
}

// Test with zero IDs
TEST_F(ConvertGlomapToColmapImageTest_118, ZeroIds_118) {
  Image glomap_image(0, 0, "img.png");
  glomap_image.frame_id = 0;

  colmap::Image colmap_image;
  ConvertGlomapToColmapImage(glomap_image, colmap_image, false);

  EXPECT_EQ(colmap_image.ImageId(), 0);
  EXPECT_EQ(colmap_image.CameraId(), 0);
  EXPECT_EQ(colmap_image.FrameId(), 0);
}

// Test file name with special characters
TEST_F(ConvertGlomapToColmapImageTest_118, SpecialCharacterFileName_118) {
  Image glomap_image(1, 1, "path/with spaces/image (1).jpg");
  colmap::Image colmap_image;

  ConvertGlomapToColmapImage(glomap_image, colmap_image, false);

  EXPECT_EQ(colmap_image.Name(), "path/with spaces/image (1).jpg");
}

}  // namespace
}  // namespace glomap
