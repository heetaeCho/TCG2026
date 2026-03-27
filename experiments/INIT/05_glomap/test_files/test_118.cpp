// File: colmap_converter_test_118.cc

#include <gtest/gtest.h>
#include <Eigen/Core>

#include "glomap/io/colmap_converter.h"
#include "glomap/scene/image.h"
#include "colmap/scene/image.h"

class ConvertGlomapToColmapImageTest_118 : public ::testing::Test {
protected:
  glomap::Image MakeGlomapImageWithPoints_118(
      colmap::image_t image_id,
      colmap::camera_t camera_id,
      const std::string& name,
      colmap::frame_t frame_id,
      const std::vector<Eigen::Vector2d>& points) {
    glomap::Image img(image_id, camera_id, name);
    img.frame_id = frame_id;
    img.features = points;
    return img;
  }
};

// Normal operation: all basic fields are copied, keep_points == false
TEST_F(ConvertGlomapToColmapImageTest_118,
       CopiesBasicFieldsWithoutPoints_118) {
  const colmap::image_t image_id = 1;
  const colmap::camera_t camera_id = 2;
  const colmap::frame_t frame_id = 3;

  std::vector<Eigen::Vector2d> points;
  points.emplace_back(10.0, 20.0);
  points.emplace_back(30.0, 40.0);

  glomap::Image glomap_image =
      MakeGlomapImageWithPoints_118(image_id, camera_id, "test_image.jpg",
                                    frame_id, points);

  colmap::Image colmap_image;

  glomap::ConvertGlomapToColmapImage(glomap_image, colmap_image,
                                     /*keep_points=*/false);

  EXPECT_EQ(colmap_image.ImageId(), image_id);
  EXPECT_EQ(colmap_image.CameraId(), camera_id);
  EXPECT_EQ(colmap_image.Name(), "test_image.jpg");
  EXPECT_EQ(colmap_image.FrameId(), frame_id);

  // When keep_points is false, 2D points should remain at their default state
  EXPECT_TRUE(colmap_image.Points2D().empty());
}

// Normal operation: all basic fields and points are copied, keep_points == true
TEST_F(ConvertGlomapToColmapImageTest_118,
       CopiesBasicFieldsAndPointsWhenKeepPointsTrue_118) {
  const colmap::image_t image_id = 10;
  const colmap::camera_t camera_id = 20;
  const colmap::frame_t frame_id = 30;

  std::vector<Eigen::Vector2d> points;
  points.emplace_back(1.0, 2.0);
  points.emplace_back(3.0, 4.0);
  points.emplace_back(5.0, 6.0);

  glomap::Image glomap_image =
      MakeGlomapImageWithPoints_118(image_id, camera_id, "image_with_points.png",
                                    frame_id, points);

  colmap::Image colmap_image;

  glomap::ConvertGlomapToColmapImage(glomap_image, colmap_image,
                                     /*keep_points=*/true);

  EXPECT_EQ(colmap_image.ImageId(), image_id);
  EXPECT_EQ(colmap_image.CameraId(), camera_id);
  EXPECT_EQ(colmap_image.Name(), "image_with_points.png");
  EXPECT_EQ(colmap_image.FrameId(), frame_id);

  const auto& converted_points = colmap_image.Points2D();
  ASSERT_EQ(converted_points.size(), points.size());
  for (size_t i = 0; i < points.size(); ++i) {
    EXPECT_DOUBLE_EQ(converted_points[i].x(), points[i].x());
    EXPECT_DOUBLE_EQ(converted_points[i].y(), points[i].y());
  }
}

// Boundary / interaction: keep_points == false does not override existing points
TEST_F(ConvertGlomapToColmapImageTest_118,
       DoesNotOverrideExistingPointsWhenKeepPointsFalse_118) {
  const colmap::image_t image_id = 5;
  const colmap::camera_t camera_id = 6;
  const colmap::frame_t frame_id = 7;

  // Glomap image with different points
  std::vector<Eigen::Vector2d> glomap_points;
  glomap_points.emplace_back(100.0, 200.0);

  glomap::Image glomap_image =
      MakeGlomapImageWithPoints_118(image_id, camera_id, "source.jpg",
                                    frame_id, glomap_points);

  // Colmap image that already has points
  colmap::Image colmap_image;
  std::vector<Eigen::Vector2d> existing_points;
  existing_points.emplace_back(-1.0, -2.0);
  existing_points.emplace_back(-3.0, -4.0);
  colmap_image.SetPoints2D(existing_points);

  glomap::ConvertGlomapToColmapImage(glomap_image, colmap_image,
                                     /*keep_points=*/false);

  // Basic fields should be updated
  EXPECT_EQ(colmap_image.ImageId(), image_id);
  EXPECT_EQ(colmap_image.CameraId(), camera_id);
  EXPECT_EQ(colmap_image.Name(), "source.jpg");
  EXPECT_EQ(colmap_image.FrameId(), frame_id);

  // Points2D should remain unchanged when keep_points is false
  const auto& converted_points = colmap_image.Points2D();
  ASSERT_EQ(converted_points.size(), existing_points.size());
  for (size_t i = 0; i < existing_points.size(); ++i) {
    EXPECT_DOUBLE_EQ(converted_points[i].x(), existing_points[i].x());
    EXPECT_DOUBLE_EQ(converted_points[i].y(), existing_points[i].y());
  }
}

// Boundary: empty/“default-like” image, keep_points == true
TEST_F(ConvertGlomapToColmapImageTest_118,
       HandlesEmptyFeaturesAndName_118) {
  // Use default-constructed glomap::Image if available
  glomap::Image glomap_image;
  glomap_image.camera_id = 0;
  glomap_image.frame_id = -1;
  glomap_image.features.clear();  // explicitly ensure no points

  colmap::Image colmap_image;

  glomap::ConvertGlomapToColmapImage(glomap_image, colmap_image,
                                     /*keep_points=*/true);

  // Observable behavior: colmap image should reflect glomap basic fields
  EXPECT_EQ(colmap_image.ImageId(), glomap_image.image_id);
  EXPECT_EQ(colmap_image.CameraId(), glomap_image.camera_id);
  EXPECT_EQ(colmap_image.Name(), glomap_image.file_name);
  EXPECT_EQ(colmap_image.FrameId(), glomap_image.frame_id);

  // No features to copy
  EXPECT_TRUE(colmap_image.Points2D().empty());
}
