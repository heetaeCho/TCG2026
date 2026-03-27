#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/math/gravity.h"

#include <Eigen/Dense>



using namespace glomap;

using Eigen::Vector3d;

using Eigen::Matrix3d;



class GravityTest_62 : public ::testing::Test {

protected:

    // Setup code here if needed

};



TEST_F(GravityTest_62, NormalOperation_62) {

    Vector3d gravity(0.0, 0.0, 9.81);

    Matrix3d R = GetAlignRot(gravity);

    EXPECT_NEAR(R.determinant(), 1.0, 1e-9);

}



TEST_F(GravityTest_62, BoundaryCondition_ZeroVector_62) {

    Vector3d gravity(0.0, 0.0, 0.0);

    EXPECT_THROW(GetAlignRot(gravity), std::runtime_error);

}



TEST_F(GravityTest_62, BoundaryCondition_UnitX_62) {

    Vector3d gravity(1.0, 0.0, 0.0);

    Matrix3d R = GetAlignRot(gravity);

    EXPECT_NEAR(R.determinant(), 1.0, 1e-9);

}



TEST_F(GravityTest_62, BoundaryCondition_UnitY_62) {

    Vector3d gravity(0.0, 1.0, 0.0);

    Matrix3d R = GetAlignRot(gravity);

    EXPECT_NEAR(R.determinant(), 1.0, 1e-9);

}



TEST_F(GravityTest_62, BoundaryCondition_UnitZ_62) {

    Vector3d gravity(0.0, 0.0, 1.0);

    Matrix3d R = GetAlignRot(gravity);

    EXPECT_NEAR(R.determinant(), 1.0, 1e-9);

}



TEST_F(GravityTest_62, ExceptionalCase_NonNormalizedVector_62) {

    Vector3d gravity(1.0, 1.0, 1.0); // Not normalized

    Matrix3d R = GetAlignRot(gravity);

    EXPECT_NEAR(R.determinant(), 1.0, 1e-9);

}



TEST_F(GravityTest_62, VerificationOfOrthogonality_62) {

    Vector3d gravity(0.0, 0.0, 9.81);

    Matrix3d R = GetAlignRot(gravity);

    Matrix3d identity = R * R.transpose();

    EXPECT_TRUE(identity.isIdentity(1e-9));

}
