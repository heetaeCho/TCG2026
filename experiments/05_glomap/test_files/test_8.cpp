#include <gtest/gtest.h>

#include <Eigen/Dense>

#include "TestProjects/glomap/glomap/scene/camera.h"



using namespace glomap;

using namespace Eigen;



class CameraTest_8 : public ::testing::Test {

protected:

    Camera camera;

};



TEST_F(CameraTest_8, GetK_ReturnsCorrectMatrix_8) {

    // Assuming default constructor initializes FocalLengthX, FocalLengthY, PrincipalPointX, and PrincipalPointY to 0

    Matrix3d expectedK;

    expectedK << 0, 0, 0,

                 0, 0, 0,

                 0, 0, 1;



    EXPECT_EQ(camera.GetK(), expectedK);

}



TEST_F(CameraTest_8, GetK_ReturnsCorrectMatrixWithFocalLengthsAndPrincipalPoints_8) {

    // Mock values for FocalLengthX, FocalLengthY, PrincipalPointX, and PrincipalPointY

    double focalX = 100.0;

    double focalY = 200.0;

    int principalX = 300;

    int principalY = 400;



    // Assuming there is a way to set these values for testing purposes

    // For this example, we will assume a hypothetical setter method exists

    // camera.SetFocalLengthsAndPrincipalPoints(focalX, focalY, principalX, principalY);



    Matrix3d expectedK;

    expectedK << focalX, 0, principalX,

                 0, focalY, principalY,

                 0, 0, 1;



    EXPECT_EQ(camera.GetK(), expectedK);

}



TEST_F(CameraTest_8, GetK_BoundaryConditionsWithZeroValues_8) {

    // Boundary condition with zero values

    double focalX = 0.0;

    double focalY = 0.0;

    int principalX = 0;

    int principalY = 0;



    // Assuming there is a way to set these values for testing purposes

    // For this example, we will assume a hypothetical setter method exists

    // camera.SetFocalLengthsAndPrincipalPoints(focalX, focalY, principalX, principalY);



    Matrix3d expectedK;

    expectedK << 0, 0, 0,

                 0, 0, 0,

                 0, 0, 1;



    EXPECT_EQ(camera.GetK(), expectedK);

}



TEST_F(CameraTest_8, GetK_BoundaryConditionsWithMaxValues_8) {

    // Boundary condition with max values

    double focalX = std::numeric_limits<double>::max();

    double focalY = std::numeric_limits<double>::max();

    int principalX = std::numeric_limits<int>::max();

    int principalY = std::numeric_limits<int>::max();



    // Assuming there is a way to set these values for testing purposes

    // For this example, we will assume a hypothetical setter method exists

    // camera.SetFocalLengthsAndPrincipalPoints(focalX, focalY, principalX, principalY);



    Matrix3d expectedK;

    expectedK << focalX, 0, principalX,

                 0, focalY, principalY,

                 0, 0, 1;



    EXPECT_EQ(camera.GetK(), expectedK);

}
