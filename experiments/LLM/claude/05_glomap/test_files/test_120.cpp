#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/io/colmap_converter.h"
#include "glomap/scene/types_sfm.h"

#include <colmap/scene/reconstruction.h>
#include <colmap/scene/camera.h>
#include <colmap/scene/image.h>
#include <colmap/sensor/models.h>

namespace glomap {
namespace {

class ConvertColmapToGlomapTest_120 : public ::testing::Test {
 protected:
  void SetUp() override {
    rigs.clear();
    cameras.clear();
    frames.clear();
    images.clear();
    tracks.clear();
  }

  colmap::Reconstruction reconstruction;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;
};

TEST_F(ConvertColmapToGlomapTest_120, EmptyReconstruction_120) {
  ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);

  EXPECT_TRUE(cameras.empty());
  EXPECT_TRUE(images.empty());
  EXPECT_TRUE(tracks.empty());
  EXPECT_TRUE(rigs.empty());
  EXPECT_TRUE(frames.empty());
}

TEST_F(ConvertColmapToGlomapTest_120, SingleCamera_120) {
  colmap::Camera colmap_camera;
  colmap_camera.camera_id = 1;
  colmap_camera.SetModelIdFromName("PINHOLE");
  colmap_camera.SetWidth(640);
  colmap_camera.SetHeight(480);
  colmap_camera.params = {500.0, 500.0, 320.0, 240.0};
  reconstruction.AddCamera(colmap_camera);

  ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);

  EXPECT_EQ(cameras.size(), 1);
  EXPECT_TRUE(cameras.find(1) != cameras.end());
  EXPECT_EQ(cameras[1].Width(), 640);
  EXPECT_EQ(cameras[1].Height(), 480);
}

TEST_F(ConvertColmapToGlomapTest_120, MultipleCameras_120) {
  for (int i = 1; i <= 5; ++i) {
    colmap::Camera colmap_camera;
    colmap_camera.camera_id = i;
    colmap_camera.SetModelIdFromName("PINHOLE");
    colmap_camera.SetWidth(640);
    colmap_camera.SetHeight(480);
    colmap_camera.params = {500.0, 500.0, 320.0, 240.0};
    reconstruction.AddCamera(colmap_camera);
  }

  ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);

  EXPECT_EQ(cameras.size(), 5);
  for (int i = 1; i <= 5; ++i) {
    EXPECT_TRUE(cameras.find(i) != cameras.end());
  }
}

TEST_F(ConvertColmapToGlomapTest_120, SingleImageWithFeatures_120) {
  // Add camera
  colmap::Camera colmap_camera;
  colmap_camera.camera_id = 1;
  colmap_camera.SetModelIdFromName("PINHOLE");
  colmap_camera.SetWidth(640);
  colmap_camera.SetHeight(480);
  colmap_camera.params = {500.0, 500.0, 320.0, 240.0};
  reconstruction.AddCamera(colmap_camera);

  // Add image
  colmap::Image colmap_image;
  colmap_image.SetImageId(1);
  colmap_image.SetCameraId(1);
  colmap_image.SetName("test_image.jpg");

  std::vector<colmap::Point2D> points2D;
  colmap::Point2D p1;
  p1.xy = Eigen::Vector2d(10.0, 20.0);
  points2D.push_back(p1);
  colmap::Point2D p2;
  p2.xy = Eigen::Vector2d(30.0, 40.0);
  points2D.push_back(p2);
  colmap_image.SetPoints2D(points2D);

  reconstruction.AddImage(colmap_image);

  ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);

  EXPECT_EQ(images.size(), 1);
  EXPECT_TRUE(images.find(1) != images.end());

  const Image& img = images.at(1);
  EXPECT_EQ(img.camera_id, 1);
  EXPECT_EQ(img.file_name, "test_image.jpg");
  EXPECT_EQ(img.features.size(), 2);
  EXPECT_DOUBLE_EQ(img.features[0].x(), 10.0);
  EXPECT_DOUBLE_EQ(img.features[0].y(), 20.0);
  EXPECT_DOUBLE_EQ(img.features[1].x(), 30.0);
  EXPECT_DOUBLE_EQ(img.features[1].y(), 40.0);
}

TEST_F(ConvertColmapToGlomapTest_120, ImageWithNoFeatures_120) {
  colmap::Camera colmap_camera;
  colmap_camera.camera_id = 1;
  colmap_camera.SetModelIdFromName("PINHOLE");
  colmap_camera.SetWidth(640);
  colmap_camera.SetHeight(480);
  colmap_camera.params = {500.0, 500.0, 320.0, 240.0};
  reconstruction.AddCamera(colmap_camera);

  colmap::Image colmap_image;
  colmap_image.SetImageId(1);
  colmap_image.SetCameraId(1);
  colmap_image.SetName("empty_image.jpg");
  reconstruction.AddImage(colmap_image);

  ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);

  EXPECT_EQ(images.size(), 1);
  EXPECT_TRUE(images.at(1).features.empty());
}

TEST_F(ConvertColmapToGlomapTest_120, ClearsPreviousData_120) {
  // Pre-populate cameras and images
  cameras[99] = Camera();
  images.insert(std::make_pair(99, Image(99, 1, "old.jpg")));

  ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);

  // After conversion of empty reconstruction, old data should be cleared
  EXPECT_TRUE(cameras.empty());
  EXPECT_TRUE(images.empty());
}

TEST_F(ConvertColmapToGlomapTest_120, MultipleImagesMultipleCameras_120) {
  // Add cameras
  for (int i = 1; i <= 3; ++i) {
    colmap::Camera colmap_camera;
    colmap_camera.camera_id = i;
    colmap_camera.SetModelIdFromName("PINHOLE");
    colmap_camera.SetWidth(640);
    colmap_camera.SetHeight(480);
    colmap_camera.params = {500.0, 500.0, 320.0, 240.0};
    reconstruction.AddCamera(colmap_camera);
  }

  // Add images
  for (int i = 1; i <= 6; ++i) {
    colmap::Image colmap_image;
    colmap_image.SetImageId(i);
    colmap_image.SetCameraId((i % 3) + 1);
    colmap_image.SetName("image_" + std::to_string(i) + ".jpg");

    std::vector<colmap::Point2D> points2D;
    for (int j = 0; j < i; ++j) {
      colmap::Point2D p;
      p.xy = Eigen::Vector2d(j * 10.0, j * 20.0);
      points2D.push_back(p);
    }
    colmap_image.SetPoints2D(points2D);
    reconstruction.AddImage(colmap_image);
  }

  ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);

  EXPECT_EQ(cameras.size(), 3);
  EXPECT_EQ(images.size(), 6);

  for (int i = 1; i <= 6; ++i) {
    EXPECT_TRUE(images.find(i) != images.end());
    EXPECT_EQ(images.at(i).features.size(), static_cast<size_t>(i));
    EXPECT_EQ(images.at(i).file_name, "image_" + std::to_string(i) + ".jpg");
  }
}

TEST_F(ConvertColmapToGlomapTest_120, TracksFromPoints3D_120) {
  // Add camera
  colmap::Camera colmap_camera;
  colmap_camera.camera_id = 1;
  colmap_camera.SetModelIdFromName("PINHOLE");
  colmap_camera.SetWidth(640);
  colmap_camera.SetHeight(480);
  colmap_camera.params = {500.0, 500.0, 320.0, 240.0};
  reconstruction.AddCamera(colmap_camera);

  // Add two images with features
  for (int i = 1; i <= 2; ++i) {
    colmap::Image colmap_image;
    colmap_image.SetImageId(i);
    colmap_image.SetCameraId(1);
    colmap_image.SetName("image_" + std::to_string(i) + ".jpg");

    std::vector<colmap::Point2D> points2D;
    colmap::Point2D p;
    p.xy = Eigen::Vector2d(100.0 * i, 200.0 * i);
    points2D.push_back(p);
    colmap_image.SetPoints2D(points2D);
    reconstruction.AddImage(colmap_image);
  }

  // Register images (need poses for registration)
  auto& img1 = reconstruction.Image(1);
  auto& img2 = reconstruction.Image(2);
  img1.CamFromWorld() = colmap::Rigid3d();
  img2.CamFromWorld() = colmap::Rigid3d();
  reconstruction.RegisterImage(1);
  reconstruction.RegisterImage(2);

  // Add a 3D point
  colmap::Track track;
  track.AddElement(1, 0);
  track.AddElement(2, 0);
  colmap::Point3D point3D;
  point3D.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);
  point3D.track = track;
  reconstruction.AddPoint3D(point3D.xyz, track);

  ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);

  // There should be at least one track
  EXPECT_GE(tracks.size(), 1);
}

TEST_F(ConvertColmapToGlomapTest_120, CameraIdPreserved_120) {
  colmap::Camera colmap_camera;
  colmap_camera.camera_id = 42;
  colmap_camera.SetModelIdFromName("PINHOLE");
  colmap_camera.SetWidth(1920);
  colmap_camera.SetHeight(1080);
  colmap_camera.params = {1000.0, 1000.0, 960.0, 540.0};
  reconstruction.AddCamera(colmap_camera);

  ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);

  EXPECT_EQ(cameras.size(), 1);
  EXPECT_TRUE(cameras.find(42) != cameras.end());
  EXPECT_EQ(cameras[42].Width(), 1920);
  EXPECT_EQ(cameras[42].Height(), 1080);
}

TEST_F(ConvertColmapToGlomapTest_120, ImageCameraIdMapping_120) {
  colmap::Camera colmap_camera;
  colmap_camera.camera_id = 5;
  colmap_camera.SetModelIdFromName("PINHOLE");
  colmap_camera.SetWidth(640);
  colmap_camera.SetHeight(480);
  colmap_camera.params = {500.0, 500.0, 320.0, 240.0};
  reconstruction.AddCamera(colmap_camera);

  colmap::Image colmap_image;
  colmap_image.SetImageId(10);
  colmap_image.SetCameraId(5);
  colmap_image.SetName("mapped.jpg");
  reconstruction.AddImage(colmap_image);

  ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);

  EXPECT_EQ(images.at(10).camera_id, 5);
}

TEST_F(ConvertColmapToGlomapTest_120, NoTracksWhenNoPoints3D_120) {
  colmap::Camera colmap_camera;
  colmap_camera.camera_id = 1;
  colmap_camera.SetModelIdFromName("PINHOLE");
  colmap_camera.SetWidth(640);
  colmap_camera.SetHeight(480);
  colmap_camera.params = {500.0, 500.0, 320.0, 240.0};
  reconstruction.AddCamera(colmap_camera);

  colmap::Image colmap_image;
  colmap_image.SetImageId(1);
  colmap_image.SetCameraId(1);
  colmap_image.SetName("no_tracks.jpg");
  reconstruction.AddImage(colmap_image);

  ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);

  EXPECT_TRUE(tracks.empty());
}

TEST_F(ConvertColmapToGlomapTest_120, FeatureCoordinatesPreserved_120) {
  colmap::Camera colmap_camera;
  colmap_camera.camera_id = 1;
  colmap_camera.SetModelIdFromName("PINHOLE");
  colmap_camera.SetWidth(640);
  colmap_camera.SetHeight(480);
  colmap_camera.params = {500.0, 500.0, 320.0, 240.0};
  reconstruction.AddCamera(colmap_camera);

  colmap::Image colmap_image;
  colmap_image.SetImageId(1);
  colmap_image.SetCameraId(1);
  colmap_image.SetName("coords.jpg");

  std::vector<colmap::Point2D> points2D;
  colmap::Point2D p;
  p.xy = Eigen::Vector2d(123.456, 789.012);
  points2D.push_back(p);
  colmap_image.SetPoints2D(points2D);
  reconstruction.AddImage(colmap_image);

  ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);

  ASSERT_EQ(images.at(1).features.size(), 1);
  EXPECT_NEAR(images.at(1).features[0].x(), 123.456, 1e-6);
  EXPECT_NEAR(images.at(1).features[0].y(), 789.012, 1e-6);
}

TEST_F(ConvertColmapToGlomapTest_120, LargeNumberOfFeatures_120) {
  colmap::Camera colmap_camera;
  colmap_camera.camera_id = 1;
  colmap_camera.SetModelIdFromName("PINHOLE");
  colmap_camera.SetWidth(640);
  colmap_camera.SetHeight(480);
  colmap_camera.params = {500.0, 500.0, 320.0, 240.0};
  reconstruction.AddCamera(colmap_camera);

  colmap::Image colmap_image;
  colmap_image.SetImageId(1);
  colmap_image.SetCameraId(1);
  colmap_image.SetName("many_features.jpg");

  const int num_features = 10000;
  std::vector<colmap::Point2D> points2D;
  points2D.reserve(num_features);
  for (int i = 0; i < num_features; ++i) {
    colmap::Point2D p;
    p.xy = Eigen::Vector2d(i * 0.1, i * 0.2);
    points2D.push_back(p);
  }
  colmap_image.SetPoints2D(points2D);
  reconstruction.AddImage(colmap_image);

  ConvertColmapToGlomap(reconstruction, rigs, cameras, frames, images, tracks);

  EXPECT_EQ(images.at(1).features.size(), static_cast<size_t>(num_features));
}

}  // namespace
}  // namespace glomap
