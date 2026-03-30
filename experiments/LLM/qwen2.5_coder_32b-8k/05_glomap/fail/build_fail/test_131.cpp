#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/math/gravity.h"

#include <Eigen/Dense>



using namespace glomap;

using namespace Eigen;



class GravityTest_131 : public ::testing::Test {

protected:

    Vector3d gravity;

};



TEST_F(GravityTest_131, NormalOperation_131) {

    // Arrange

    gravity << 0, 0, 1;



    // Act

    Matrix3d result = GetAlignRot(gravity);



    // Assert

    EXPECT_TRUE(result.isOrthogonal());

    EXPECT_NEAR(result.determinant(), 1.0, 1e-9);

}



TEST_F(GravityTest_131, BoundaryCondition_ZeroVector_131) {

    // Arrange

    gravity << 0, 0, 0;



    // Act & Assert

    EXPECT_THROW(GetAlignRot(gravity), std::invalid_argument);

}



TEST_F(GravityTest_131, BoundaryCondition_UnitX_131) {

    // Arrange

    gravity << 1, 0, 0;



    // Act

    Matrix3d result = GetAlignRot(gravity);



    // Assert

    EXPECT_TRUE(result.isOrthogonal());

    EXPECT_NEAR(result.determinant(), 1.0, 1e-9);

}



TEST_F(GravityTest_131, BoundaryCondition_UnitY_131) {

    // Arrange

    gravity << 0, 1, 0;



    // Act

    Matrix3d result = GetAlignRot(gravity);



    // Assert

    EXPECT_TRUE(result.isOrthogonal());

    EXPECT_NEAR(result.determinant(), 1.0, 1e-9);

}



TEST_F(GravityTest_131, BoundaryCondition_UnitZ_131) {

    // Arrange

    gravity << 0, 0, 1;



    // Act

    Matrix3d result = GetAlignRot(gravity);



    // Assert

    EXPECT_TRUE(result.isOrthogonal());

    EXPECT_NEAR(result.determinant(), 1.0, 1e-9);

}



TEST_F(GravityTest_131, Exceptional_NegativeZ_131) {

    // Arrange

    gravity << 0, 0, -1;



    // Act

    Matrix3d result = GetAlignRot(gravity);



    // Assert

    EXPECT_TRUE(result.isOrthogonal());

    EXPECT_NEAR(result.determinant(), 1.0, 1e-9);

}



TEST_F(GravityTest_131, Exceptional_NonUnitVector_131) {

    // Arrange

    gravity << 2, 0, 0;



    // Act

    Matrix3d result = GetAlignRot(gravity);



    // Assert

    EXPECT_TRUE(result.isOrthogonal());

    EXPECT_NEAR(result.determinant(), 1.0, 1e-9);

}
