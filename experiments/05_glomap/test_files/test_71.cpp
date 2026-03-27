#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/glomap/glomap/math/rigid3d.cc"

#include <Eigen/Dense>



namespace glomap {



class Rigid3DTest_71 : public ::testing::Test {

protected:

    Eigen::Matrix3d identity_matrix;

    Eigen::Matrix3d rotation_90_x;



    void SetUp() override {

        identity_matrix = Eigen::Matrix3d::Identity();

        rotation_90_x << 1, 0, 0,

                         0, 0,-1,

                         0, 1, 0;

    }

};



TEST_F(Rigid3DTest_71, IdentityMatricesAngleIsZero_71) {

    EXPECT_DOUBLE_EQ(CalcAngle(identity_matrix, identity_matrix), 0.0);

}



TEST_F(Rigid3DTest_71, IdentityAnd90XMatrixAngleIs90_71) {

    EXPECT_DOUBLE_EQ(CalcAngle(identity_matrix, rotation_90_x), 90.0);

}



TEST_F(Rigid3DTest_71, SameRotationMatricesAnyAngleIsZero_71) {

    Eigen::Matrix3d rotation = Eigen::AngleAxisd(EIGEN_PI / 4, Eigen::Vector3d(1, 0, 0)).toRotationMatrix();

    EXPECT_DOUBLE_EQ(CalcAngle(rotation, rotation), 0.0);

}



TEST_F(Rigid3DTest_71, OppositeMatricesAngleIs180_71) {

    Eigen::Matrix3d opposite_rotation = -identity_matrix;

    EXPECT_DOUBLE_EQ(CalcAngle(identity_matrix, opposite_rotation), 180.0);

}



TEST_F(Rigid3DTest_71, BoundaryConditionCosValueTooHigh_71) {

    Eigen::Matrix3d invalid_matrix;

    invalid_matrix << 2, 0, 0,

                      0, 1, 0,

                      0, 0, 1;

    EXPECT_DOUBLE_EQ(CalcAngle(identity_matrix, invalid_matrix), 0.0);

}



TEST_F(Rigid3DTest_71, BoundaryConditionCosValueTooLow_71) {

    Eigen::Matrix3d invalid_matrix;

    invalid_matrix << -2, 0, 0,

                      0, 1, 0,

                      0, 0, 1;

    EXPECT_DOUBLE_EQ(CalcAngle(identity_matrix, invalid_matrix), 180.0);

}



} // namespace glomap
