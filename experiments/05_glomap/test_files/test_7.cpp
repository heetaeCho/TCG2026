#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/glomap/glomap/scene/camera.h"



namespace {



class CameraTest_7 : public ::testing::Test {

protected:

    glomap::Camera camera;

};



TEST_F(CameraTest_7, FocalLengthCalculation_7) {

    // Assuming FocalLengthX and FocalLengthY are correctly set in the constructor or elsewhere

    double expectedFocal = (camera.FocalLengthX() + camera.FocalLengthY()) / 2.0;

    EXPECT_DOUBLE_EQ(camera.Focal(), expectedFocal);

}



TEST_F(CameraTest_7, PrincipalPointDefaultValue_7) {

    // Assuming default value for PrincipalPoint is Eigen::Vector2d(0, 0)

    EXPECT_EQ(camera.PrincipalPoint(), Eigen::Vector2d(0, 0));

}



TEST_F(CameraTest_7, GetKDefaultValue_7) {

    // Assuming default value for GetK is Eigen::Matrix3d::Identity()

    EXPECT_EQ(camera.GetK(), Eigen::Matrix3d::Identity());

}



TEST_F(CameraTest_7, FocalLengthBoundaryCondition_7) {

    // Test boundary conditions for FocalLengthX and FocalLengthY

    double maxDouble = std::numeric_limits<double>::max();

    camera.FocalLengthX() = maxDouble;

    camera.FocalLengthY() = maxDouble;

    EXPECT_DOUBLE_EQ(camera.Focal(), maxDouble);



    double minNormalDouble = std::numeric_limits<double>::min();

    camera.FocalLengthX() = minNormalDouble;

    camera.FocalLengthY() = minNormalDouble;

    EXPECT_DOUBLE_EQ(camera.Focal(), minNormalDouble);

}



TEST_F(CameraTest_7, FocalLengthNegativeValues_7) {

    // Test with negative values for FocalLengthX and FocalLengthY

    camera.FocalLengthX() = -10.0;

    camera.FocalLengthY() = -20.0;

    EXPECT_DOUBLE_EQ(camera.Focal(), -15.0);

}



}  // namespace
