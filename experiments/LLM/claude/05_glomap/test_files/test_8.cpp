#include <gtest/gtest.h>
#include <Eigen/Core>
#include "glomap/scene/camera.h"

namespace glomap {
namespace {

class CameraTest_8 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test default construction
TEST_F(CameraTest_8, DefaultConstruction_8) {
  Camera camera;
  // Default camera should be constructible without errors
  EXPECT_FALSE(camera.has_refined_focal_length);
}

// Test GetK returns a 3x3 matrix with correct structure
TEST_F(CameraTest_8, GetKReturnsCorrectStructure_8) {
  Camera camera;
  // Set up camera with known parameters - use SIMPLE_PINHOLE model
  camera.SetModelIdFromName("SIMPLE_PINHOLE");
  camera.SetWidth(640);
  camera.SetHeight(480);
  std::vector<double> params = {500.0, 320.0, 240.0};
  camera.SetParams(params);

  Eigen::Matrix3d K = camera.GetK();

  // Check structure: K should be upper triangular with 1 at (2,2)
  EXPECT_DOUBLE_EQ(K(2, 2), 1.0);
  EXPECT_DOUBLE_EQ(K(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(K(2, 0), 0.0);
  EXPECT_DOUBLE_EQ(K(2, 1), 0.0);
}

// Test GetK with SIMPLE_PINHOLE model returns expected values
TEST_F(CameraTest_8, GetKSimplePinhole_8) {
  Camera camera;
  camera.SetModelIdFromName("SIMPLE_PINHOLE");
  camera.SetWidth(640);
  camera.SetHeight(480);
  std::vector<double> params = {500.0, 320.0, 240.0};
  camera.SetParams(params);

  Eigen::Matrix3d K = camera.GetK();

  // For SIMPLE_PINHOLE: fx=fy=f, cx, cy
  EXPECT_DOUBLE_EQ(K(0, 0), 500.0);  // FocalLengthX
  EXPECT_DOUBLE_EQ(K(1, 1), 500.0);  // FocalLengthY
  EXPECT_DOUBLE_EQ(K(0, 2), 320.0);  // PrincipalPointX
  EXPECT_DOUBLE_EQ(K(1, 2), 240.0);  // PrincipalPointY
  EXPECT_DOUBLE_EQ(K(0, 1), 0.0);
}

// Test GetK with PINHOLE model (separate fx, fy)
TEST_F(CameraTest_8, GetKPinhole_8) {
  Camera camera;
  camera.SetModelIdFromName("PINHOLE");
  camera.SetWidth(640);
  camera.SetHeight(480);
  std::vector<double> params = {500.0, 600.0, 320.0, 240.0};
  camera.SetParams(params);

  Eigen::Matrix3d K = camera.GetK();

  EXPECT_DOUBLE_EQ(K(0, 0), 500.0);  // FocalLengthX
  EXPECT_DOUBLE_EQ(K(1, 1), 600.0);  // FocalLengthY
  EXPECT_DOUBLE_EQ(K(0, 2), 320.0);  // PrincipalPointX
  EXPECT_DOUBLE_EQ(K(1, 2), 240.0);  // PrincipalPointY
}

// Test copy construction from colmap::Camera
TEST_F(CameraTest_8, CopyFromColmapCamera_8) {
  colmap::Camera colmap_cam;
  colmap_cam.SetModelIdFromName("SIMPLE_PINHOLE");
  colmap_cam.SetWidth(800);
  colmap_cam.SetHeight(600);
  std::vector<double> params = {700.0, 400.0, 300.0};
  colmap_cam.SetParams(params);

  Camera camera(colmap_cam);

  Eigen::Matrix3d K = camera.GetK();
  EXPECT_DOUBLE_EQ(K(0, 0), 700.0);
  EXPECT_DOUBLE_EQ(K(1, 1), 700.0);
  EXPECT_DOUBLE_EQ(K(0, 2), 400.0);
  EXPECT_DOUBLE_EQ(K(1, 2), 300.0);
}

// Test assignment operator from colmap::Camera
TEST_F(CameraTest_8, AssignmentFromColmapCamera_8) {
  colmap::Camera colmap_cam;
  colmap_cam.SetModelIdFromName("SIMPLE_PINHOLE");
  colmap_cam.SetWidth(1024);
  colmap_cam.SetHeight(768);
  std::vector<double> params = {800.0, 512.0, 384.0};
  colmap_cam.SetParams(params);

  Camera camera;
  camera = colmap_cam;

  Eigen::Matrix3d K = camera.GetK();
  EXPECT_DOUBLE_EQ(K(0, 0), 800.0);
  EXPECT_DOUBLE_EQ(K(0, 2), 512.0);
  EXPECT_DOUBLE_EQ(K(1, 2), 384.0);
}

// Test has_refined_focal_length defaults to false
TEST_F(CameraTest_8, HasRefinedFocalLengthDefault_8) {
  Camera camera;
  EXPECT_FALSE(camera.has_refined_focal_length);
}

// Test has_refined_focal_length can be set
TEST_F(CameraTest_8, HasRefinedFocalLengthCanBeSet_8) {
  Camera camera;
  camera.has_refined_focal_length = true;
  EXPECT_TRUE(camera.has_refined_focal_length);
}

// Test Focal() method
TEST_F(CameraTest_8, FocalMethod_8) {
  Camera camera;
  camera.SetModelIdFromName("SIMPLE_PINHOLE");
  camera.SetWidth(640);
  camera.SetHeight(480);
  std::vector<double> params = {500.0, 320.0, 240.0};
  camera.SetParams(params);

  double focal = camera.Focal();
  EXPECT_DOUBLE_EQ(focal, 500.0);
}

// Test PrincipalPoint() method
TEST_F(CameraTest_8, PrincipalPointMethod_8) {
  Camera camera;
  camera.SetModelIdFromName("SIMPLE_PINHOLE");
  camera.SetWidth(640);
  camera.SetHeight(480);
  std::vector<double> params = {500.0, 320.0, 240.0};
  camera.SetParams(params);

  Eigen::Vector2d pp = camera.PrincipalPoint();
  EXPECT_DOUBLE_EQ(pp(0), 320.0);
  EXPECT_DOUBLE_EQ(pp(1), 240.0);
}

// Test GetK with very small focal length (boundary)
TEST_F(CameraTest_8, GetKSmallFocalLength_8) {
  Camera camera;
  camera.SetModelIdFromName("SIMPLE_PINHOLE");
  camera.SetWidth(640);
  camera.SetHeight(480);
  std::vector<double> params = {1.0, 320.0, 240.0};
  camera.SetParams(params);

  Eigen::Matrix3d K = camera.GetK();
  EXPECT_DOUBLE_EQ(K(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(K(1, 1), 1.0);
}

// Test GetK with very large focal length (boundary)
TEST_F(CameraTest_8, GetKLargeFocalLength_8) {
  Camera camera;
  camera.SetModelIdFromName("SIMPLE_PINHOLE");
  camera.SetWidth(640);
  camera.SetHeight(480);
  std::vector<double> params = {1e6, 320.0, 240.0};
  camera.SetParams(params);

  Eigen::Matrix3d K = camera.GetK();
  EXPECT_DOUBLE_EQ(K(0, 0), 1e6);
  EXPECT_DOUBLE_EQ(K(1, 1), 1e6);
}

// Test GetK with zero principal point
TEST_F(CameraTest_8, GetKZeroPrincipalPoint_8) {
  Camera camera;
  camera.SetModelIdFromName("SIMPLE_PINHOLE");
  camera.SetWidth(640);
  camera.SetHeight(480);
  std::vector<double> params = {500.0, 0.0, 0.0};
  camera.SetParams(params);

  Eigen::Matrix3d K = camera.GetK();
  EXPECT_DOUBLE_EQ(K(0, 2), 0.0);
  EXPECT_DOUBLE_EQ(K(1, 2), 0.0);
}

// Test K matrix diagonal symmetry property for SIMPLE_PINHOLE
TEST_F(CameraTest_8, GetKDiagonalSymmetrySimplePinhole_8) {
  Camera camera;
  camera.SetModelIdFromName("SIMPLE_PINHOLE");
  camera.SetWidth(640);
  camera.SetHeight(480);
  std::vector<double> params = {500.0, 320.0, 240.0};
  camera.SetParams(params);

  Eigen::Matrix3d K = camera.GetK();
  // For SIMPLE_PINHOLE, fx == fy
  EXPECT_DOUBLE_EQ(K(0, 0), K(1, 1));
}

// Test K matrix zeros are in correct positions
TEST_F(CameraTest_8, GetKZerosInCorrectPositions_8) {
  Camera camera;
  camera.SetModelIdFromName("PINHOLE");
  camera.SetWidth(640);
  camera.SetHeight(480);
  std::vector<double> params = {500.0, 600.0, 320.0, 240.0};
  camera.SetParams(params);

  Eigen::Matrix3d K = camera.GetK();
  EXPECT_DOUBLE_EQ(K(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(K(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(K(2, 0), 0.0);
  EXPECT_DOUBLE_EQ(K(2, 1), 0.0);
}

}  // namespace
}  // namespace glomap
