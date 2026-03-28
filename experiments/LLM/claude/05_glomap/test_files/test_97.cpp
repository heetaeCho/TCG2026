#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "glomap/scene/camera.h"
#include <colmap/scene/camera.h>

namespace glomap {
namespace {

class CameraTest_97 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default construction
TEST_F(CameraTest_97, DefaultConstruction_97) {
  Camera camera;
  // Default camera should be constructible
  EXPECT_FALSE(camera.has_refined_focal_length);
}

// Test construction from colmap::Camera
TEST_F(CameraTest_97, ConstructFromColmapCamera_97) {
  colmap::Camera colmap_camera;
  colmap_camera.SetCameraId(1);
  colmap_camera.SetModelIdFromName("PINHOLE");
  colmap_camera.SetWidth(640);
  colmap_camera.SetHeight(480);
  colmap_camera.SetParams({500.0, 500.0, 320.0, 240.0});

  Camera camera(colmap_camera);
  EXPECT_FALSE(camera.has_refined_focal_length);
  EXPECT_EQ(camera.CameraId(), colmap_camera.CameraId());
  EXPECT_EQ(camera.Width(), 640);
  EXPECT_EQ(camera.Height(), 480);
}

// Test assignment operator from colmap::Camera
TEST_F(CameraTest_97, AssignmentFromColmapCamera_97) {
  colmap::Camera colmap_camera;
  colmap_camera.SetCameraId(2);
  colmap_camera.SetModelIdFromName("PINHOLE");
  colmap_camera.SetWidth(1024);
  colmap_camera.SetHeight(768);
  colmap_camera.SetParams({800.0, 800.0, 512.0, 384.0});

  Camera camera;
  camera = colmap_camera;

  EXPECT_EQ(camera.CameraId(), colmap_camera.CameraId());
  EXPECT_EQ(camera.Width(), 1024);
  EXPECT_EQ(camera.Height(), 768);
}

// Test Focal() method with PINHOLE model
TEST_F(CameraTest_97, FocalPinholeModel_97) {
  colmap::Camera colmap_camera;
  colmap_camera.SetModelIdFromName("PINHOLE");
  colmap_camera.SetWidth(640);
  colmap_camera.SetHeight(480);
  colmap_camera.SetParams({500.0, 500.0, 320.0, 240.0});

  Camera camera(colmap_camera);
  double focal = camera.Focal();
  EXPECT_DOUBLE_EQ(focal, 500.0);
}

// Test PrincipalPoint() method
TEST_F(CameraTest_97, PrincipalPointPinholeModel_97) {
  colmap::Camera colmap_camera;
  colmap_camera.SetModelIdFromName("PINHOLE");
  colmap_camera.SetWidth(640);
  colmap_camera.SetHeight(480);
  colmap_camera.SetParams({500.0, 500.0, 320.0, 240.0});

  Camera camera(colmap_camera);
  Eigen::Vector2d pp = camera.PrincipalPoint();
  EXPECT_DOUBLE_EQ(pp(0), 320.0);
  EXPECT_DOUBLE_EQ(pp(1), 240.0);
}

// Test GetK() method - calibration matrix
TEST_F(CameraTest_97, GetKPinholeModel_97) {
  colmap::Camera colmap_camera;
  colmap_camera.SetModelIdFromName("PINHOLE");
  colmap_camera.SetWidth(640);
  colmap_camera.SetHeight(480);
  colmap_camera.SetParams({500.0, 500.0, 320.0, 240.0});

  Camera camera(colmap_camera);
  Eigen::Matrix3d K = camera.GetK();

  // K matrix should be:
  // [fx  0  cx]
  // [0  fy  cy]
  // [0   0   1]
  EXPECT_DOUBLE_EQ(K(0, 0), 500.0);  // fx
  EXPECT_DOUBLE_EQ(K(1, 1), 500.0);  // fy
  EXPECT_DOUBLE_EQ(K(0, 2), 320.0);  // cx
  EXPECT_DOUBLE_EQ(K(1, 2), 240.0);  // cy
  EXPECT_DOUBLE_EQ(K(2, 2), 1.0);
  EXPECT_DOUBLE_EQ(K(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(K(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(K(2, 0), 0.0);
  EXPECT_DOUBLE_EQ(K(2, 1), 0.0);
}

// Test has_refined_focal_length default value
TEST_F(CameraTest_97, HasRefinedFocalLengthDefault_97) {
  Camera camera;
  EXPECT_FALSE(camera.has_refined_focal_length);
}

// Test has_refined_focal_length can be set
TEST_F(CameraTest_97, HasRefinedFocalLengthSetTrue_97) {
  Camera camera;
  camera.has_refined_focal_length = true;
  EXPECT_TRUE(camera.has_refined_focal_length);
}

// Test assignment operator preserves has_refined_focal_length as false (reset)
TEST_F(CameraTest_97, AssignmentResetsHasRefinedFocalLength_97) {
  Camera camera;
  camera.has_refined_focal_length = true;

  colmap::Camera colmap_camera;
  colmap_camera.SetModelIdFromName("PINHOLE");
  colmap_camera.SetWidth(640);
  colmap_camera.SetHeight(480);
  colmap_camera.SetParams({500.0, 500.0, 320.0, 240.0});

  camera = colmap_camera;
  // After assignment from colmap::Camera, has_refined_focal_length should be default (false)
  EXPECT_FALSE(camera.has_refined_focal_length);
}

// Test with SIMPLE_PINHOLE model
TEST_F(CameraTest_97, SimplePinholeModel_97) {
  colmap::Camera colmap_camera;
  colmap_camera.SetModelIdFromName("SIMPLE_PINHOLE");
  colmap_camera.SetWidth(640);
  colmap_camera.SetHeight(480);
  colmap_camera.SetParams({500.0, 320.0, 240.0});

  Camera camera(colmap_camera);
  double focal = camera.Focal();
  EXPECT_DOUBLE_EQ(focal, 500.0);

  Eigen::Vector2d pp = camera.PrincipalPoint();
  EXPECT_DOUBLE_EQ(pp(0), 320.0);
  EXPECT_DOUBLE_EQ(pp(1), 240.0);
}

// Test copy semantics via construction from colmap camera
TEST_F(CameraTest_97, CopyFromColmapPreservesProperties_97) {
  colmap::Camera colmap_camera;
  colmap_camera.SetCameraId(42);
  colmap_camera.SetModelIdFromName("SIMPLE_PINHOLE");
  colmap_camera.SetWidth(1920);
  colmap_camera.SetHeight(1080);
  colmap_camera.SetParams({1000.0, 960.0, 540.0});

  Camera camera(colmap_camera);
  EXPECT_EQ(camera.CameraId(), 42);
  EXPECT_EQ(camera.Width(), 1920);
  EXPECT_EQ(camera.Height(), 1080);
}

// Test GetK with SIMPLE_PINHOLE (single focal length)
TEST_F(CameraTest_97, GetKSimplePinhole_97) {
  colmap::Camera colmap_camera;
  colmap_camera.SetModelIdFromName("SIMPLE_PINHOLE");
  colmap_camera.SetWidth(640);
  colmap_camera.SetHeight(480);
  colmap_camera.SetParams({750.0, 320.0, 240.0});

  Camera camera(colmap_camera);
  Eigen::Matrix3d K = camera.GetK();

  EXPECT_DOUBLE_EQ(K(0, 0), 750.0);
  EXPECT_DOUBLE_EQ(K(1, 1), 750.0);
  EXPECT_DOUBLE_EQ(K(0, 2), 320.0);
  EXPECT_DOUBLE_EQ(K(1, 2), 240.0);
  EXPECT_DOUBLE_EQ(K(2, 2), 1.0);
}

// Test multiple assignments
TEST_F(CameraTest_97, MultipleAssignments_97) {
  colmap::Camera colmap_camera1;
  colmap_camera1.SetCameraId(1);
  colmap_camera1.SetModelIdFromName("SIMPLE_PINHOLE");
  colmap_camera1.SetWidth(640);
  colmap_camera1.SetHeight(480);
  colmap_camera1.SetParams({500.0, 320.0, 240.0});

  colmap::Camera colmap_camera2;
  colmap_camera2.SetCameraId(2);
  colmap_camera2.SetModelIdFromName("PINHOLE");
  colmap_camera2.SetWidth(1920);
  colmap_camera2.SetHeight(1080);
  colmap_camera2.SetParams({1000.0, 1000.0, 960.0, 540.0});

  Camera camera;
  camera = colmap_camera1;
  EXPECT_EQ(camera.CameraId(), 1);
  EXPECT_EQ(camera.Width(), 640);

  camera = colmap_camera2;
  EXPECT_EQ(camera.CameraId(), 2);
  EXPECT_EQ(camera.Width(), 1920);
  EXPECT_EQ(camera.Height(), 1080);
}

// Test with SIMPLE_RADIAL model
TEST_F(CameraTest_97, SimpleRadialModel_97) {
  colmap::Camera colmap_camera;
  colmap_camera.SetModelIdFromName("SIMPLE_RADIAL");
  colmap_camera.SetWidth(640);
  colmap_camera.SetHeight(480);
  colmap_camera.SetParams({500.0, 320.0, 240.0, 0.1});

  Camera camera(colmap_camera);
  double focal = camera.Focal();
  EXPECT_DOUBLE_EQ(focal, 500.0);

  Eigen::Vector2d pp = camera.PrincipalPoint();
  EXPECT_DOUBLE_EQ(pp(0), 320.0);
  EXPECT_DOUBLE_EQ(pp(1), 240.0);
}

}  // namespace
}  // namespace glomap
