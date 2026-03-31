#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/io/colmap_converter.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/camera.h"
#include "glomap/scene/frame.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"

#include <colmap/scene/database.h>
#include <colmap/scene/camera.h>
#include <colmap/scene/image.h>
#include <colmap/feature/types.h>
#include <colmap/geometry/rigid3.h>

#include <filesystem>
#include <unordered_map>

namespace glomap {
namespace {

class ConvertDatabaseToGlomapTest_122 : public ::testing::Test {
 protected:
  void SetUp() override {
    db_path_ = std::filesystem::temp_directory_path() / "test_db_122.db";
    // Remove if exists from previous run
    std::filesystem::remove(db_path_);
    database_.Open(db_path_.string());
  }

  void TearDown() override {
    database_.Close();
    std::filesystem::remove(db_path_);
  }

  colmap::Camera CreateColmapCamera(int model_id = colmap::CameraModelId::kSimplePinhole,
                                     int width = 640,
                                     int height = 480) {
    colmap::Camera camera;
    camera.camera_id = colmap::kInvalidCameraId;
    camera.SetModelId(model_id);
    camera.SetWidth(width);
    camera.SetHeight(height);
    camera.SetParams({500.0, 320.0, 240.0});
    return camera;
  }

  std::filesystem::path db_path_;
  colmap::Database database_;
};

// Test with empty database - no images, cameras, etc.
TEST_F(ConvertDatabaseToGlomapTest_122, EmptyDatabase_122) {
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  ConvertDatabaseToGlomap(database_, view_graph, rigs, cameras, frames, images);

  EXPECT_TRUE(images.empty());
  EXPECT_TRUE(cameras.empty());
  EXPECT_TRUE(frames.empty());
  EXPECT_TRUE(view_graph.image_pairs.empty());
}

// Test with a single camera and single image
TEST_F(ConvertDatabaseToGlomapTest_122, SingleCameraAndImage_122) {
  colmap::Camera cam = CreateColmapCamera();
  cam.camera_id = database_.WriteCamera(cam);

  colmap::Image img;
  img.SetName("test_image.jpg");
  img.SetCameraId(cam.camera_id);
  img.SetImageId(database_.WriteImage(img));

  // Write some keypoints for this image
  colmap::FeatureKeypoints keypoints(3);
  keypoints[0] = colmap::FeatureKeypoint(10.0f, 20.0f);
  keypoints[1] = colmap::FeatureKeypoint(30.0f, 40.0f);
  keypoints[2] = colmap::FeatureKeypoint(50.0f, 60.0f);
  database_.WriteKeypoints(img.ImageId(), keypoints);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  ConvertDatabaseToGlomap(database_, view_graph, rigs, cameras, frames, images);

  EXPECT_EQ(images.size(), 1u);
  EXPECT_EQ(cameras.size(), 1u);
  EXPECT_TRUE(view_graph.image_pairs.empty());

  // Check image properties
  auto it = images.find(img.ImageId());
  ASSERT_NE(it, images.end());
  EXPECT_EQ(it->second.camera_id, cam.camera_id);
  EXPECT_EQ(it->second.features.size(), 3u);

  // Check keypoints were loaded correctly
  EXPECT_DOUBLE_EQ(it->second.features[0].x(), 10.0);
  EXPECT_DOUBLE_EQ(it->second.features[0].y(), 20.0);
  EXPECT_DOUBLE_EQ(it->second.features[1].x(), 30.0);
  EXPECT_DOUBLE_EQ(it->second.features[1].y(), 40.0);
  EXPECT_DOUBLE_EQ(it->second.features[2].x(), 50.0);
  EXPECT_DOUBLE_EQ(it->second.features[2].y(), 60.0);
}

// Test with multiple cameras and images
TEST_F(ConvertDatabaseToGlomapTest_122, MultipleCamerasAndImages_122) {
  colmap::Camera cam1 = CreateColmapCamera();
  cam1.camera_id = database_.WriteCamera(cam1);

  colmap::Camera cam2 = CreateColmapCamera();
  cam2.camera_id = database_.WriteCamera(cam2);

  colmap::Image img1;
  img1.SetName("image1.jpg");
  img1.SetCameraId(cam1.camera_id);
  img1.SetImageId(database_.WriteImage(img1));

  colmap::Image img2;
  img2.SetName("image2.jpg");
  img2.SetCameraId(cam2.camera_id);
  img2.SetImageId(database_.WriteImage(img2));

  // Write keypoints
  colmap::FeatureKeypoints kp1(2);
  kp1[0] = colmap::FeatureKeypoint(1.0f, 2.0f);
  kp1[1] = colmap::FeatureKeypoint(3.0f, 4.0f);
  database_.WriteKeypoints(img1.ImageId(), kp1);

  colmap::FeatureKeypoints kp2(2);
  kp2[0] = colmap::FeatureKeypoint(5.0f, 6.0f);
  kp2[1] = colmap::FeatureKeypoint(7.0f, 8.0f);
  database_.WriteKeypoints(img2.ImageId(), kp2);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  ConvertDatabaseToGlomap(database_, view_graph, rigs, cameras, frames, images);

  EXPECT_EQ(images.size(), 2u);
  EXPECT_EQ(cameras.size(), 2u);
  EXPECT_NE(images.find(img1.ImageId()), images.end());
  EXPECT_NE(images.find(img2.ImageId()), images.end());
}

// Test that cameras are correctly read
TEST_F(ConvertDatabaseToGlomapTest_122, CamerasCorrectlyRead_122) {
  colmap::Camera cam = CreateColmapCamera(colmap::CameraModelId::kSimplePinhole, 800, 600);
  cam.camera_id = database_.WriteCamera(cam);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  ConvertDatabaseToGlomap(database_, view_graph, rigs, cameras, frames, images);

  EXPECT_EQ(cameras.size(), 1u);
  auto it = cameras.find(cam.camera_id);
  ASSERT_NE(it, cameras.end());
  EXPECT_EQ(it->second.Width(), 800);
  EXPECT_EQ(it->second.Height(), 600);
}

// Test image pair with matches (uncalibrated two view geometry)
TEST_F(ConvertDatabaseToGlomapTest_122, ImagePairWithUncalibratedGeometry_122) {
  colmap::Camera cam = CreateColmapCamera();
  cam.camera_id = database_.WriteCamera(cam);

  colmap::Image img1;
  img1.SetName("img1.jpg");
  img1.SetCameraId(cam.camera_id);
  img1.SetImageId(database_.WriteImage(img1));

  colmap::Image img2;
  img2.SetName("img2.jpg");
  img2.SetCameraId(cam.camera_id);
  img2.SetImageId(database_.WriteImage(img2));

  colmap::FeatureKeypoints kp1(3);
  kp1[0] = colmap::FeatureKeypoint(10.0f, 20.0f);
  kp1[1] = colmap::FeatureKeypoint(30.0f, 40.0f);
  kp1[2] = colmap::FeatureKeypoint(50.0f, 60.0f);
  database_.WriteKeypoints(img1.ImageId(), kp1);

  colmap::FeatureKeypoints kp2(3);
  kp2[0] = colmap::FeatureKeypoint(15.0f, 25.0f);
  kp2[1] = colmap::FeatureKeypoint(35.0f, 45.0f);
  kp2[2] = colmap::FeatureKeypoint(55.0f, 65.0f);
  database_.WriteKeypoints(img2.ImageId(), kp2);

  // Write matches
  colmap::FeatureMatches matches;
  matches.push_back(colmap::FeatureMatch(0, 0));
  matches.push_back(colmap::FeatureMatch(1, 1));
  matches.push_back(colmap::FeatureMatch(2, 2));
  database_.WriteMatches(img1.ImageId(), img2.ImageId(), matches);

  // Write two view geometry as UNCALIBRATED
  colmap::TwoViewGeometry two_view;
  two_view.config = colmap::TwoViewGeometry::UNCALIBRATED;
  two_view.F = Eigen::Matrix3d::Identity();
  two_view.inlier_matches = matches;
  database_.WriteTwoViewGeometry(img1.ImageId(), img2.ImageId(), two_view);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  ConvertDatabaseToGlomap(database_, view_graph, rigs, cameras, frames, images);

  EXPECT_EQ(images.size(), 2u);
  EXPECT_EQ(cameras.size(), 1u);
  EXPECT_EQ(view_graph.image_pairs.size(), 1u);

  auto pair_it = view_graph.image_pairs.begin();
  ASSERT_NE(pair_it, view_graph.image_pairs.end());
  EXPECT_TRUE(pair_it->second.is_valid);
  EXPECT_EQ(pair_it->second.config, colmap::TwoViewGeometry::UNCALIBRATED);
  EXPECT_EQ(pair_it->second.matches.rows(), 3);
  EXPECT_EQ(pair_it->second.matches.cols(), 2);
}

// Test image pair with DEGENERATE geometry marks pair as invalid
TEST_F(ConvertDatabaseToGlomapTest_122, DegenerateGeometryMarksInvalid_122) {
  colmap::Camera cam = CreateColmapCamera();
  cam.camera_id = database_.WriteCamera(cam);

  colmap::Image img1;
  img1.SetName("img1.jpg");
  img1.SetCameraId(cam.camera_id);
  img1.SetImageId(database_.WriteImage(img1));

  colmap::Image img2;
  img2.SetName("img2.jpg");
  img2.SetCameraId(cam.camera_id);
  img2.SetImageId(database_.WriteImage(img2));

  colmap::FeatureKeypoints kp1(2);
  kp1[0] = colmap::FeatureKeypoint(10.0f, 20.0f);
  kp1[1] = colmap::FeatureKeypoint(30.0f, 40.0f);
  database_.WriteKeypoints(img1.ImageId(), kp1);

  colmap::FeatureKeypoints kp2(2);
  kp2[0] = colmap::FeatureKeypoint(15.0f, 25.0f);
  kp2[1] = colmap::FeatureKeypoint(35.0f, 45.0f);
  database_.WriteKeypoints(img2.ImageId(), kp2);

  colmap::FeatureMatches matches;
  matches.push_back(colmap::FeatureMatch(0, 0));
  matches.push_back(colmap::FeatureMatch(1, 1));
  database_.WriteMatches(img1.ImageId(), img2.ImageId(), matches);

  colmap::TwoViewGeometry two_view;
  two_view.config = colmap::TwoViewGeometry::DEGENERATE;
  two_view.inlier_matches = matches;
  database_.WriteTwoViewGeometry(img1.ImageId(), img2.ImageId(), two_view);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  ConvertDatabaseToGlomap(database_, view_graph, rigs, cameras, frames, images);

  EXPECT_EQ(view_graph.image_pairs.size(), 1u);
  auto pair_it = view_graph.image_pairs.begin();
  ASSERT_NE(pair_it, view_graph.image_pairs.end());
  EXPECT_FALSE(pair_it->second.is_valid);
}

// Test image pair with UNDEFINED geometry marks pair as invalid
TEST_F(ConvertDatabaseToGlomapTest_122, UndefinedGeometryMarksInvalid_122) {
  colmap::Camera cam = CreateColmapCamera();
  cam.camera_id = database_.WriteCamera(cam);

  colmap::Image img1;
  img1.SetName("a.jpg");
  img1.SetCameraId(cam.camera_id);
  img1.SetImageId(database_.WriteImage(img1));

  colmap::Image img2;
  img2.SetName("b.jpg");
  img2.SetCameraId(cam.camera_id);
  img2.SetImageId(database_.WriteImage(img2));

  colmap::FeatureKeypoints kp1(1);
  kp1[0] = colmap::FeatureKeypoint(1.0f, 2.0f);
  database_.WriteKeypoints(img1.ImageId(), kp1);

  colmap::FeatureKeypoints kp2(1);
  kp2[0] = colmap::FeatureKeypoint(3.0f, 4.0f);
  database_.WriteKeypoints(img2.ImageId(), kp2);

  colmap::FeatureMatches matches;
  matches.push_back(colmap::FeatureMatch(0, 0));
  database_.WriteMatches(img1.ImageId(), img2.ImageId(), matches);

  colmap::TwoViewGeometry two_view;
  two_view.config = colmap::TwoViewGeometry::UNDEFINED;
  database_.WriteTwoViewGeometry(img1.ImageId(), img2.ImageId(), two_view);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  ConvertDatabaseToGlomap(database_, view_graph, rigs, cameras, frames, images);

  EXPECT_EQ(view_graph.image_pairs.size(), 1u);
  auto pair_it = view_graph.image_pairs.begin();
  EXPECT_FALSE(pair_it->second.is_valid);
}

// Test that frames are created for images without explicit frames
TEST_F(ConvertDatabaseToGlomapTest_122, FramesCreatedForImagesWithoutExplicitFrames_122) {
  colmap::Camera cam = CreateColmapCamera();
  cam.camera_id = database_.WriteCamera(cam);

  colmap::Image img;
  img.SetName("test.jpg");
  img.SetCameraId(cam.camera_id);
  img.SetImageId(database_.WriteImage(img));

  colmap::FeatureKeypoints kp(1);
  kp[0] = colmap::FeatureKeypoint(1.0f, 2.0f);
  database_.WriteKeypoints(img.ImageId(), kp);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  ConvertDatabaseToGlomap(database_, view_graph, rigs, cameras, frames, images);

  // Each image should have a frame assigned
  EXPECT_FALSE(frames.empty());
  auto img_it = images.find(img.ImageId());
  ASSERT_NE(img_it, images.end());
  EXPECT_NE(img_it->second.frame_id, colmap::kInvalidFrameId);
}

// Test that rigs are created for cameras without explicit rigs
TEST_F(ConvertDatabaseToGlomapTest_122, RigsCreatedForCamerasWithoutExplicitRigs_122) {
  colmap::Camera cam = CreateColmapCamera();
  cam.camera_id = database_.WriteCamera(cam);

  colmap::Image img;
  img.SetName("test.jpg");
  img.SetCameraId(cam.camera_id);
  img.SetImageId(database_.WriteImage(img));

  colmap::FeatureKeypoints kp(1);
  kp[0] = colmap::FeatureKeypoint(1.0f, 2.0f);
  database_.WriteKeypoints(img.ImageId(), kp);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  ConvertDatabaseToGlomap(database_, view_graph, rigs, cameras, frames, images);

  // At least one rig should be created for the camera
  EXPECT_FALSE(rigs.empty());
}

// Test with no keypoints for an image
TEST_F(ConvertDatabaseToGlomapTest_122, ImageWithNoKeypoints_122) {
  colmap::Camera cam = CreateColmapCamera();
  cam.camera_id = database_.WriteCamera(cam);

  colmap::Image img;
  img.SetName("no_keypoints.jpg");
  img.SetCameraId(cam.camera_id);
  img.SetImageId(database_.WriteImage(img));

  // Don't write any keypoints
  database_.WriteKeypoints(img.ImageId(), colmap::FeatureKeypoints());

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  ConvertDatabaseToGlomap(database_, view_graph, rigs, cameras, frames, images);

  EXPECT_EQ(images.size(), 1u);
  auto it = images.find(img.ImageId());
  ASSERT_NE(it, images.end());
  EXPECT_EQ(it->second.features.size(), 0u);
}

// Test with no matches between images
TEST_F(ConvertDatabaseToGlomapTest_122, NoMatchesBetweenImages_122) {
  colmap::Camera cam = CreateColmapCamera();
  cam.camera_id = database_.WriteCamera(cam);

  colmap::Image img1;
  img1.SetName("img1.jpg");
  img1.SetCameraId(cam.camera_id);
  img1.SetImageId(database_.WriteImage(img1));

  colmap::Image img2;
  img2.SetName("img2.jpg");
  img2.SetCameraId(cam.camera_id);
  img2.SetImageId(database_.WriteImage(img2));

  colmap::FeatureKeypoints kp1(2);
  kp1[0] = colmap::FeatureKeypoint(1.0f, 2.0f);
  kp1[1] = colmap::FeatureKeypoint(3.0f, 4.0f);
  database_.WriteKeypoints(img1.ImageId(), kp1);

  colmap::FeatureKeypoints kp2(2);
  kp2[0] = colmap::FeatureKeypoint(5.0f, 6.0f);
  kp2[1] = colmap::FeatureKeypoint(7.0f, 8.0f);
  database_.WriteKeypoints(img2.ImageId(), kp2);

  // No matches written

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  ConvertDatabaseToGlomap(database_, view_graph, rigs, cameras, frames, images);

  EXPECT_EQ(images.size(), 2u);
  EXPECT_TRUE(view_graph.image_pairs.empty());
}

// Test multiple cameras, each with its own rig
TEST_F(ConvertDatabaseToGlomapTest_122, MultipleCamerasGetSeparateRigs_122) {
  colmap::Camera cam1 = CreateColmapCamera();
  cam1.camera_id = database_.WriteCamera(cam1);

  colmap::Camera cam2 = CreateColmapCamera();
  cam2.camera_id = database_.WriteCamera(cam2);

  colmap::Image img1;
  img1.SetName("img1.jpg");
  img1.SetCameraId(cam1.camera_id);
  img1.SetImageId(database_.WriteImage(img1));

  colmap::Image img2;
  img2.SetName("img2.jpg");
  img2.SetCameraId(cam2.camera_id);
  img2.SetImageId(database_.WriteImage(img2));

  database_.WriteKeypoints(img1.ImageId(), colmap::FeatureKeypoints());
  database_.WriteKeypoints(img2.ImageId(), colmap::FeatureKeypoints());

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  ConvertDatabaseToGlomap(database_, view_graph, rigs, cameras, frames, images);

  EXPECT_EQ(cameras.size(), 2u);
  // Each camera without a pre-existing rig should get its own rig
  EXPECT_GE(rigs.size(), 2u);
}

// Test WATERMARK geometry marks pair as invalid
TEST_F(ConvertDatabaseToGlomapTest_122, WatermarkGeometryMarksInvalid_122) {
  colmap::Camera cam = CreateColmapCamera();
  cam.camera_id = database_.WriteCamera(cam);

  colmap::Image img1;
  img1.SetName("w1.jpg");
  img1.SetCameraId(cam.camera_id);
  img1.SetImageId(database_.WriteImage(img1));

  colmap::Image img2;
  img2.SetName("w2.jpg");
  img2.SetCameraId(cam.camera_id);
  img2.SetImageId(database_.WriteImage(img2));

  colmap::FeatureKeypoints kp1(1);
  kp1[0] = colmap::FeatureKeypoint(1.0f, 2.0f);
  database_.WriteKeypoints(img1.ImageId(), kp1);

  colmap::FeatureKeypoints kp2(1);
  kp2[0] = colmap::FeatureKeypoint(3.0f, 4.0f);
  database_.WriteKeypoints(img2.ImageId(), kp2);

  colmap::FeatureMatches matches;
  matches.push_back(colmap::FeatureMatch(0, 0));
  database_.WriteMatches(img1.ImageId(), img2.ImageId(), matches);

  colmap::TwoViewGeometry two_view;
  two_view.config = colmap::TwoViewGeometry::WATERMARK;
  database_.WriteTwoViewGeometry(img1.ImageId(), img2.ImageId(), two_view);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  ConvertDatabaseToGlomap(database_, view_graph, rigs, cameras, frames, images);

  EXPECT_EQ(view_graph.image_pairs.size(), 1u);
  auto pair_it = view_graph.image_pairs.begin();
  EXPECT_FALSE(pair_it->second.is_valid);
}

// Test PLANAR geometry sets both H and F
TEST_F(ConvertDatabaseToGlomapTest_122, PlanarGeometrySetsHandF_122) {
  colmap::Camera cam = CreateColmapCamera();
  cam.camera_id = database_.WriteCamera(cam);

  colmap::Image img1;
  img1.SetName("p1.jpg");
  img1.SetCameraId(cam.camera_id);
  img1.SetImageId(database_.WriteImage(img1));

  colmap::Image img2;
  img2.SetName("p2.jpg");
  img2.SetCameraId(cam.camera_id);
  img2.SetImageId(database_.WriteImage(img2));

  colmap::FeatureKeypoints kp1(2);
  kp1[0] = colmap::FeatureKeypoint(10.0f, 20.0f);
  kp1[1] = colmap::FeatureKeypoint(30.0f, 40.0f);
  database_.WriteKeypoints(img1.ImageId(), kp1);

  colmap::FeatureKeypoints kp2(2);
  kp2[0] = colmap::FeatureKeypoint(15.0f, 25.0f);
  kp2[1] = colmap::FeatureKeypoint(35.0f, 45.0f);
  database_.WriteKeypoints(img2.ImageId(), kp2);

  colmap::FeatureMatches matches;
  matches.push_back(colmap::FeatureMatch(0, 0));
  matches.push_back(colmap::FeatureMatch(1, 1));
  database_.WriteMatches(img1.ImageId(), img2.ImageId(), matches);

  colmap::TwoViewGeometry two_view;
  two_view.config = colmap::TwoViewGeometry::PLANAR;
  two_view.F = Eigen::Matrix3d::Identity() * 2.0;
  two_view.H = Eigen::Matrix3d::Identity() * 3.0;
  two_view.inlier_matches = matches;
  database_.WriteTwoViewGeometry(img1.ImageId(), img2.ImageId(), two_view);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  ConvertDatabaseToGlomap(database_, view_graph, rigs, cameras, frames, images);

  EXPECT_EQ(view_graph.image_pairs.size(), 1u);
  auto pair_it = view_graph.image_pairs.begin();
  ASSERT_NE(pair_it, view_graph.image_pairs.end());
  EXPECT_TRUE(pair_it->second.is_valid);
  EXPECT_EQ(pair_it->second.config, colmap::TwoViewGeometry::PLANAR);

  // H and F should be set
  EXPECT_FALSE(pair_it->second.H.isZero());
  EXPECT_FALSE(pair_it->second.F.isZero());
}

// Test match indices validation - invalid indices should be skipped
TEST_F(ConvertDatabaseToGlomapTest_122, MatchWithOutOfBoundsIndicesSkipped_122) {
  colmap::Camera cam = CreateColmapCamera();
  cam.camera_id = database_.WriteCamera(cam);

  colmap::Image img1;
  img1.SetName("idx1.jpg");
  img1.SetCameraId(cam.camera_id);
  img1.SetImageId(database_.WriteImage(img1));

  colmap::Image img2;
  img2.SetName("idx2.jpg");
  img2.SetCameraId(cam.camera_id);
  img2.SetImageId(database_.WriteImage(img2));

  // Only 1 keypoint each
  colmap::FeatureKeypoints kp1(1);
  kp1[0] = colmap::FeatureKeypoint(10.0f, 20.0f);
  database_.WriteKeypoints(img1.ImageId(), kp1);

  colmap::FeatureKeypoints kp2(1);
  kp2[0] = colmap::FeatureKeypoint(15.0f, 25.0f);
  database_.WriteKeypoints(img2.ImageId(), kp2);

  colmap::FeatureMatches matches;
  matches.push_back(colmap::FeatureMatch(0, 0));  // valid
  matches.push_back(colmap::FeatureMatch(5, 0));  // out of bounds for img1
  matches.push_back(colmap::FeatureMatch(0, 5));  // out of bounds for img2
  database_.WriteMatches(img1.ImageId(), img2.ImageId(), matches);

  colmap::TwoViewGeometry two_view;
  two_view.config = colmap::TwoViewGeometry::UNCALIBRATED;
  two_view.F = Eigen::Matrix3d::Identity();
  two_view.inlier_matches = matches;
  database_.WriteTwoViewGeometry(img1.ImageId(), img2.ImageId(), two_view);

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  ConvertDatabaseToGlomap(database_, view_graph, rigs, cameras, frames, images);

  EXPECT_EQ(view_graph.image_pairs.size(), 1u);
  auto pair_it = view_graph.image_pairs.begin();
  // Only the valid match should remain
  EXPECT_EQ(pair_it->second.matches.rows(), 1);
}

// Test that image file name is preserved
TEST_F(ConvertDatabaseToGlomapTest_122, ImageFileNamePreserved_122) {
  colmap::Camera cam = CreateColmapCamera();
  cam.camera_id = database_.WriteCamera(cam);

  colmap::Image img;
  img.SetName("my_special_photo.png");
  img.SetCameraId(cam.camera_id);
  img.SetImageId(database_.WriteImage(img));

  database_.WriteKeypoints(img.ImageId(), colmap::FeatureKeypoints());

  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  ConvertDatabaseToGlomap(database_, view_graph, rigs, cameras, frames, images);

  auto it = images.find(img.ImageId());
  ASSERT_NE(it, images.end());
  EXPECT_EQ(it->second.file_name, "my_special_photo.png");
}

}  // namespace
}  // namespace glomap
