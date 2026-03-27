#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/scene/camera.h"

#include <Eigen/Dense>



using namespace glomap;

using ::testing::Return;



class CameraTest_97 : public ::testing::Test {

protected:

    colmap::Camera colmap_camera;

    Camera camera;



    void SetUp() override {

        // Initialize a sample colmap::Camera if necessary

    }

};



TEST_F(CameraTest_97, DefaultConstructorInitializesCorrectly_97) {

    Camera default_camera;

    EXPECT_EQ(default_camera.Focal(), 0.0); // Assuming default focal length is 0.0

    EXPECT_EQ(default_camera.PrincipalPoint().x(), 0.0);

    EXPECT_EQ(default_camera.PrincipalPoint().y(), 0.0);

}



TEST_F(CameraTest_97, CopyConstructorCopiesValues_97) {

    Camera source_camera(colmap_camera);

    Camera copied_camera(source_camera);



    EXPECT_EQ(copied_camera.Focal(), source_camera.Focal());

    EXPECT_EQ(copied_camera.PrincipalPoint().x(), source_camera.PrincipalPoint().x());

    EXPECT_EQ(copied_camera.PrincipalPoint().y(), source_camera.PrincipalPoint().y());

}



TEST_F(CameraTest_97, AssignmentOperatorCopiesValues_97) {

    Camera source_camera(colmap_camera);

    Camera assigned_camera;

    assigned_camera = source_camera;



    EXPECT_EQ(assigned_camera.Focal(), source_camera.Focal());

    EXPECT_EQ(assigned_camera.PrincipalPoint().x(), source_camera.PrincipalPoint().x());

    EXPECT_EQ(assigned_camera.PrincipalPoint().y(), source_camera.PrincipalPoint().y());

}



TEST_F(CameraTest_97, FocalReturnsCorrectValue_97) {

    double expected_focal = 42.0; // Example value

    colmap_camera = colmap::Camera(expected_focal);

    Camera test_camera(colmap_camera);



    EXPECT_EQ(test_camera.Focal(), expected_focal);

}



TEST_F(CameraTest_97, PrincipalPointReturnsCorrectValue_97) {

    Eigen::Vector2d expected_principal_point(10.0, 20.0); // Example values

    colmap_camera = colmap::Camera(expected_principal_point.x(), expected_principal_point.y());

    Camera test_camera(colmap_camera);



    EXPECT_EQ(test_camera.PrincipalPoint().x(), expected_principal_point.x());

    EXPECT_EQ(test_camera.PrincipalPoint().y(), expected_principal_point.y());

}



TEST_F(CameraTest_97, GetKReturnsCorrectMatrix_97) {

    Eigen::Matrix3d expected_K = Eigen::Matrix3d::Identity();

    colmap_camera = colmap::Camera(expected_K);

    Camera test_camera(colmap_camera);



    EXPECT_TRUE(test_camera.GetK().isApprox(expected_K));

}
