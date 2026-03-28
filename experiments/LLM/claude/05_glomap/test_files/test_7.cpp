#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "glomap/scene/camera.h"

namespace glomap {
namespace {

class CameraTest_7 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction
TEST_F(CameraTest_7, DefaultConstruction_7) {
    Camera camera;
    // Default constructed camera should be valid
    EXPECT_NO_THROW(camera.Focal());
}

// Test that has_refined_focal_length defaults to false
TEST_F(CameraTest_7, DefaultHasRefinedFocalLengthIsFalse_7) {
    Camera camera;
    EXPECT_FALSE(camera.has_refined_focal_length);
}

// Test setting has_refined_focal_length
TEST_F(CameraTest_7, SetHasRefinedFocalLength_7) {
    Camera camera;
    camera.has_refined_focal_length = true;
    EXPECT_TRUE(camera.has_refined_focal_length);
}

// Test construction from colmap::Camera
TEST_F(CameraTest_7, ConstructFromColmapCamera_7) {
    colmap::Camera colmap_camera;
    colmap_camera.SetModelIdFromName("PINHOLE");
    colmap_camera.SetWidth(640);
    colmap_camera.SetHeight(480);
    colmap_camera.SetParams({500.0, 500.0, 320.0, 240.0});

    Camera camera(colmap_camera);
    // Focal should be average of FocalLengthX and FocalLengthY
    double expected_focal = (500.0 + 500.0) / 2.0;
    EXPECT_DOUBLE_EQ(camera.Focal(), expected_focal);
}

// Test Focal() returns average of FocalLengthX and FocalLengthY
TEST_F(CameraTest_7, FocalReturnsAverageOfFocalLengths_7) {
    colmap::Camera colmap_camera;
    colmap_camera.SetModelIdFromName("PINHOLE");
    colmap_camera.SetWidth(640);
    colmap_camera.SetHeight(480);
    colmap_camera.SetParams({600.0, 400.0, 320.0, 240.0});

    Camera camera(colmap_camera);
    double expected_focal = (600.0 + 400.0) / 2.0;
    EXPECT_DOUBLE_EQ(camera.Focal(), expected_focal);
}

// Test Focal() with equal focal lengths
TEST_F(CameraTest_7, FocalWithEqualFocalLengths_7) {
    colmap::Camera colmap_camera;
    colmap_camera.SetModelIdFromName("PINHOLE");
    colmap_camera.SetWidth(640);
    colmap_camera.SetHeight(480);
    colmap_camera.SetParams({750.0, 750.0, 320.0, 240.0});

    Camera camera(colmap_camera);
    EXPECT_DOUBLE_EQ(camera.Focal(), 750.0);
}

// Test PrincipalPoint()
TEST_F(CameraTest_7, PrincipalPointReturnsCorrectValues_7) {
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

// Test GetK() returns proper calibration matrix
TEST_F(CameraTest_7, GetKReturnsCalibrationMatrix_7) {
    colmap::Camera colmap_camera;
    colmap_camera.SetModelIdFromName("PINHOLE");
    colmap_camera.SetWidth(640);
    colmap_camera.SetHeight(480);
    colmap_camera.SetParams({500.0, 500.0, 320.0, 240.0});

    Camera camera(colmap_camera);
    Eigen::Matrix3d K = camera.GetK();

    // K should be: [fx, 0, cx; 0, fy, cy; 0, 0, 1]
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

// Test assignment operator from colmap::Camera
TEST_F(CameraTest_7, AssignmentFromColmapCamera_7) {
    colmap::Camera colmap_camera;
    colmap_camera.SetModelIdFromName("PINHOLE");
    colmap_camera.SetWidth(800);
    colmap_camera.SetHeight(600);
    colmap_camera.SetParams({1000.0, 1000.0, 400.0, 300.0});

    Camera camera;
    camera = colmap_camera;

    EXPECT_DOUBLE_EQ(camera.Focal(), 1000.0);
    Eigen::Vector2d pp = camera.PrincipalPoint();
    EXPECT_DOUBLE_EQ(pp(0), 400.0);
    EXPECT_DOUBLE_EQ(pp(1), 300.0);
}

// Test that assignment preserves has_refined_focal_length
TEST_F(CameraTest_7, AssignmentPreservesRefinedFlag_7) {
    colmap::Camera colmap_camera;
    colmap_camera.SetModelIdFromName("PINHOLE");
    colmap_camera.SetWidth(640);
    colmap_camera.SetHeight(480);
    colmap_camera.SetParams({500.0, 500.0, 320.0, 240.0});

    Camera camera;
    camera.has_refined_focal_length = true;
    camera = colmap_camera;

    // After assignment from colmap::Camera, the focal parameters should update
    EXPECT_DOUBLE_EQ(camera.Focal(), 500.0);
}

// Test with asymmetric focal lengths
TEST_F(CameraTest_7, AsymmetricFocalLengths_7) {
    colmap::Camera colmap_camera;
    colmap_camera.SetModelIdFromName("PINHOLE");
    colmap_camera.SetWidth(1920);
    colmap_camera.SetHeight(1080);
    colmap_camera.SetParams({1200.0, 800.0, 960.0, 540.0});

    Camera camera(colmap_camera);
    double expected_focal = (1200.0 + 800.0) / 2.0;
    EXPECT_DOUBLE_EQ(camera.Focal(), expected_focal);
}

// Test GetK with asymmetric focal lengths
TEST_F(CameraTest_7, GetKAsymmetricFocal_7) {
    colmap::Camera colmap_camera;
    colmap_camera.SetModelIdFromName("PINHOLE");
    colmap_camera.SetWidth(1920);
    colmap_camera.SetHeight(1080);
    colmap_camera.SetParams({1200.0, 800.0, 960.0, 540.0});

    Camera camera(colmap_camera);
    Eigen::Matrix3d K = camera.GetK();

    EXPECT_DOUBLE_EQ(K(0, 0), 1200.0);
    EXPECT_DOUBLE_EQ(K(1, 1), 800.0);
    EXPECT_DOUBLE_EQ(K(0, 2), 960.0);
    EXPECT_DOUBLE_EQ(K(1, 2), 540.0);
}

// Test with very small focal length values
TEST_F(CameraTest_7, SmallFocalLengthValues_7) {
    colmap::Camera colmap_camera;
    colmap_camera.SetModelIdFromName("PINHOLE");
    colmap_camera.SetWidth(100);
    colmap_camera.SetHeight(100);
    colmap_camera.SetParams({0.001, 0.001, 50.0, 50.0});

    Camera camera(colmap_camera);
    EXPECT_DOUBLE_EQ(camera.Focal(), 0.001);
}

// Test with very large focal length values
TEST_F(CameraTest_7, LargeFocalLengthValues_7) {
    colmap::Camera colmap_camera;
    colmap_camera.SetModelIdFromName("PINHOLE");
    colmap_camera.SetWidth(10000);
    colmap_camera.SetHeight(10000);
    colmap_camera.SetParams({1e6, 1e6, 5000.0, 5000.0});

    Camera camera(colmap_camera);
    EXPECT_DOUBLE_EQ(camera.Focal(), 1e6);
}

// Test copy of Camera preserves properties
TEST_F(CameraTest_7, CopyConstructorPreservesProperties_7) {
    colmap::Camera colmap_camera;
    colmap_camera.SetModelIdFromName("PINHOLE");
    colmap_camera.SetWidth(640);
    colmap_camera.SetHeight(480);
    colmap_camera.SetParams({500.0, 600.0, 320.0, 240.0});

    Camera camera1(colmap_camera);
    camera1.has_refined_focal_length = true;

    Camera camera2 = camera1;
    EXPECT_DOUBLE_EQ(camera2.Focal(), camera1.Focal());
    EXPECT_EQ(camera2.has_refined_focal_length, camera1.has_refined_focal_length);
}

}  // namespace
}  // namespace glomap
