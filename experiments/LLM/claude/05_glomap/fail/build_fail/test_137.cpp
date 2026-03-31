#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "glomap/math/two_view_geometry.h"
#include "glomap/scene/camera.h"

namespace glomap {
namespace {

// Helper to create a camera with known intrinsics
Camera CreateTestCamera(double focal_length, double cx, double cy, int width, int height) {
    colmap::Camera colmap_cam;
    colmap_cam.SetModelIdFromName("PINHOLE");
    colmap_cam.SetWidth(width);
    colmap_cam.SetHeight(height);
    colmap_cam.SetParams({focal_length, focal_length, cx, cy});
    return Camera(colmap_cam);
}

class FundamentalFromMotionAndCamerasTest_137 : public ::testing::Test {
protected:
    void SetUp() override {
        // Default cameras with identity-like intrinsics
        camera1_ = CreateTestCamera(1.0, 0.0, 0.0, 100, 100);
        camera2_ = CreateTestCamera(1.0, 0.0, 0.0, 100, 100);
    }

    Camera camera1_;
    Camera camera2_;
};

// Test that with identity intrinsics, F should equal E (up to scale)
TEST_F(FundamentalFromMotionAndCamerasTest_137, IdentityIntrinsics_FEqualsE_137) {
    Rigid3d pose;
    // Set a pure translation along x-axis
    pose.rotation = Eigen::Quaterniond::Identity();
    pose.translation = Eigen::Vector3d(1.0, 0.0, 0.0);

    Eigen::Matrix3d F;
    FundamentalFromMotionAndCameras(camera1_, camera2_, pose, &F);

    // Compute E directly for comparison
    Eigen::Matrix3d E;
    EssentialFromMotion(pose, &E);

    // With K = I, F should equal K2^{-T} * E * K1^{-1} = E
    // Since K = I for focal=1, cx=0, cy=0
    Eigen::Matrix3d K1 = camera1_.GetK();
    Eigen::Matrix3d K2 = camera2_.GetK();

    // Verify K is identity
    EXPECT_TRUE(K1.isApprox(Eigen::Matrix3d::Identity(), 1e-10));
    EXPECT_TRUE(K2.isApprox(Eigen::Matrix3d::Identity(), 1e-10));

    // F should equal E
    EXPECT_TRUE(F.isApprox(E, 1e-10));
}

// Test with non-trivial intrinsics
TEST_F(FundamentalFromMotionAndCamerasTest_137, NonTrivialIntrinsics_137) {
    Camera cam1 = CreateTestCamera(500.0, 320.0, 240.0, 640, 480);
    Camera cam2 = CreateTestCamera(600.0, 300.0, 200.0, 640, 480);

    Rigid3d pose;
    pose.rotation = Eigen::Quaterniond(Eigen::AngleAxisd(0.1, Eigen::Vector3d::UnitY()));
    pose.translation = Eigen::Vector3d(1.0, 0.0, 0.0);

    Eigen::Matrix3d F;
    FundamentalFromMotionAndCameras(cam1, cam2, pose, &F);

    // Verify F = K2^{-T} * E * K1^{-1}
    Eigen::Matrix3d E;
    EssentialFromMotion(pose, &E);

    Eigen::Matrix3d K1 = cam1.GetK();
    Eigen::Matrix3d K2 = cam2.GetK();
    Eigen::Matrix3d F_expected = K2.transpose().inverse() * E * K1.inverse();

    EXPECT_TRUE(F.isApprox(F_expected, 1e-10));
}

// Test with pure rotation (no translation)
TEST_F(FundamentalFromMotionAndCamerasTest_137, PureRotation_137) {
    Rigid3d pose;
    pose.rotation = Eigen::Quaterniond(Eigen::AngleAxisd(0.5, Eigen::Vector3d::UnitZ()));
    pose.translation = Eigen::Vector3d(0.0, 0.0, 0.0);

    Eigen::Matrix3d F;
    FundamentalFromMotionAndCameras(camera1_, camera2_, pose, &F);

    // With zero translation, E should be zero, so F should be zero
    EXPECT_TRUE(F.isApprox(Eigen::Matrix3d::Zero(), 1e-10));
}

// Test with pure translation (no rotation)
TEST_F(FundamentalFromMotionAndCamerasTest_137, PureTranslation_137) {
    Rigid3d pose;
    pose.rotation = Eigen::Quaterniond::Identity();
    pose.translation = Eigen::Vector3d(0.0, 0.0, 1.0);

    Eigen::Matrix3d F;
    FundamentalFromMotionAndCameras(camera1_, camera2_, pose, &F);

    // F should be non-zero
    EXPECT_GT(F.norm(), 1e-10);
}

// Test with same cameras (symmetric intrinsics)
TEST_F(FundamentalFromMotionAndCamerasTest_137, SameCameras_137) {
    Camera cam = CreateTestCamera(500.0, 320.0, 240.0, 640, 480);

    Rigid3d pose;
    pose.rotation = Eigen::Quaterniond(Eigen::AngleAxisd(0.2, Eigen::Vector3d::UnitX()));
    pose.translation = Eigen::Vector3d(1.0, 0.5, 0.0);

    Eigen::Matrix3d F;
    FundamentalFromMotionAndCameras(cam, cam, pose, &F);

    Eigen::Matrix3d E;
    EssentialFromMotion(pose, &E);

    Eigen::Matrix3d K = cam.GetK();
    Eigen::Matrix3d F_expected = K.transpose().inverse() * E * K.inverse();

    EXPECT_TRUE(F.isApprox(F_expected, 1e-10));
}

// Test epipolar constraint: x2^T * F * x1 = 0 for corresponding points
TEST_F(FundamentalFromMotionAndCamerasTest_137, EpipolarConstraint_137) {
    Camera cam1 = CreateTestCamera(500.0, 320.0, 240.0, 640, 480);
    Camera cam2 = CreateTestCamera(600.0, 300.0, 200.0, 640, 480);

    Rigid3d pose;
    pose.rotation = Eigen::Quaterniond(Eigen::AngleAxisd(0.1, Eigen::Vector3d::UnitY()));
    pose.translation = Eigen::Vector3d(1.0, 0.0, 0.0);

    Eigen::Matrix3d F;
    FundamentalFromMotionAndCameras(cam1, cam2, pose, &F);

    // Create a 3D point and project it into both cameras
    Eigen::Vector3d X(0.5, 0.3, 5.0);  // 3D point in camera1 frame

    Eigen::Matrix3d K1 = cam1.GetK();
    Eigen::Matrix3d K2 = cam2.GetK();

    // Project into camera 1
    Eigen::Vector3d x1_h = K1 * X;
    Eigen::Vector3d x1 = x1_h / x1_h(2);

    // Transform point to camera 2 frame
    Eigen::Vector3d X2 = pose.rotation * X + pose.translation;
    Eigen::Vector3d x2_h = K2 * X2;
    Eigen::Vector3d x2 = x2_h / x2_h(2);

    // Epipolar constraint: x2^T * F * x1 should be ~0
    double epipolar_error = x2.transpose() * F * x1;
    EXPECT_NEAR(epipolar_error, 0.0, 1e-8);
}

// Test that F has rank 2 (det(F) = 0 for a valid fundamental matrix)
TEST_F(FundamentalFromMotionAndCamerasTest_137, FundamentalMatrixRankTwo_137) {
    Camera cam1 = CreateTestCamera(500.0, 320.0, 240.0, 640, 480);
    Camera cam2 = CreateTestCamera(600.0, 300.0, 200.0, 640, 480);

    Rigid3d pose;
    pose.rotation = Eigen::Quaterniond(Eigen::AngleAxisd(0.15, Eigen::Vector3d::UnitY()));
    pose.translation = Eigen::Vector3d(1.0, 0.2, 0.3);

    Eigen::Matrix3d F;
    FundamentalFromMotionAndCameras(cam1, cam2, pose, &F);

    // det(F) should be approximately 0 for a valid fundamental matrix
    EXPECT_NEAR(F.determinant(), 0.0, 1e-8);
}

// Test with translation along different axes
TEST_F(FundamentalFromMotionAndCamerasTest_137, TranslationAlongY_137) {
    Camera cam = CreateTestCamera(500.0, 320.0, 240.0, 640, 480);

    Rigid3d pose;
    pose.rotation = Eigen::Quaterniond::Identity();
    pose.translation = Eigen::Vector3d(0.0, 1.0, 0.0);

    Eigen::Matrix3d F;
    FundamentalFromMotionAndCameras(cam, cam, pose, &F);

    Eigen::Matrix3d E;
    EssentialFromMotion(pose, &E);

    Eigen::Matrix3d K = cam.GetK();
    Eigen::Matrix3d F_expected = K.transpose().inverse() * E * K.inverse();

    EXPECT_TRUE(F.isApprox(F_expected, 1e-10));
}

// Test with large focal length
TEST_F(FundamentalFromMotionAndCamerasTest_137, LargeFocalLength_137) {
    Camera cam1 = CreateTestCamera(5000.0, 320.0, 240.0, 640, 480);
    Camera cam2 = CreateTestCamera(5000.0, 320.0, 240.0, 640, 480);

    Rigid3d pose;
    pose.rotation = Eigen::Quaterniond(Eigen::AngleAxisd(0.05, Eigen::Vector3d::UnitZ()));
    pose.translation = Eigen::Vector3d(0.5, 0.5, 0.0);

    Eigen::Matrix3d F;
    FundamentalFromMotionAndCameras(cam1, cam2, pose, &F);

    // Should still satisfy det(F) = 0
    EXPECT_NEAR(F.determinant(), 0.0, 1e-4);
}

// Test with small focal length
TEST_F(FundamentalFromMotionAndCamerasTest_137, SmallFocalLength_137) {
    Camera cam1 = CreateTestCamera(1.0, 0.5, 0.5, 10, 10);
    Camera cam2 = CreateTestCamera(2.0, 0.5, 0.5, 10, 10);

    Rigid3d pose;
    pose.rotation = Eigen::Quaterniond(Eigen::AngleAxisd(0.3, Eigen::Vector3d(1, 1, 0).normalized()));
    pose.translation = Eigen::Vector3d(1.0, 0.0, 0.0);

    Eigen::Matrix3d F;
    FundamentalFromMotionAndCameras(cam1, cam2, pose, &F);

    Eigen::Matrix3d E;
    EssentialFromMotion(pose, &E);

    Eigen::Matrix3d K1 = cam1.GetK();
    Eigen::Matrix3d K2 = cam2.GetK();
    Eigen::Matrix3d F_expected = K2.transpose().inverse() * E * K1.inverse();

    EXPECT_TRUE(F.isApprox(F_expected, 1e-10));
}

// Test with combined rotation and translation
TEST_F(FundamentalFromMotionAndCamerasTest_137, CombinedRotationAndTranslation_137) {
    Camera cam1 = CreateTestCamera(800.0, 400.0, 300.0, 800, 600);
    Camera cam2 = CreateTestCamera(1000.0, 500.0, 350.0, 1000, 700);

    Rigid3d pose;
    pose.rotation = Eigen::Quaterniond(
        Eigen::AngleAxisd(0.1, Eigen::Vector3d::UnitX()) *
        Eigen::AngleAxisd(0.2, Eigen::Vector3d::UnitY()) *
        Eigen::AngleAxisd(0.05, Eigen::Vector3d::UnitZ()));
    pose.translation = Eigen::Vector3d(0.5, -0.3, 1.0);

    Eigen::Matrix3d F;
    FundamentalFromMotionAndCameras(cam1, cam2, pose, &F);

    // Verify using the formula
    Eigen::Matrix3d E;
    EssentialFromMotion(pose, &E);

    Eigen::Matrix3d K1 = cam1.GetK();
    Eigen::Matrix3d K2 = cam2.GetK();
    Eigen::Matrix3d F_expected = K2.transpose().inverse() * E * K1.inverse();

    EXPECT_TRUE(F.isApprox(F_expected, 1e-10));

    // Also verify rank-2 property
    EXPECT_NEAR(F.determinant(), 0.0, 1e-6);
}

}  // namespace
}  // namespace glomap
