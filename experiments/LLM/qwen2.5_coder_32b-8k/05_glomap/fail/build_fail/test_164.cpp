#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Eigen/Dense>

#include "./cost_function.h"



using namespace glomap;

using namespace Eigen;



namespace {



class FetzerFocalLengthSameCameraCostTest_164 : public ::testing::Test {

protected:

    void SetUp() override {

        i1_F_i0 = Matrix3d::Random();

        principal_point = Vector2d(320, 240);

    }



    Matrix3d i1_F_i0;

    Vector2d principal_point;

};



TEST_F(FetzerFocalLengthSameCameraCostTest_164, ConstructorInitializesKMatrices_164) {

    FetzerFocalLengthSameCameraCost cost(i1_F_i0, principal_point);

    // We can't access K0 and K1 directly, but we can infer their structure

    Matrix3d expected_K0 = Matrix3d::Identity();

    Matrix3d expected_K1 = Matrix3d::Identity();

    expected_K0(0, 2) = principal_point(0);

    expected_K0(1, 2) = principal_point(1);

    expected_K1(0, 2) = principal_point(0);

    expected_K1(1, 2) = principal_point(1);



    // Verify that the internal transformation i1_G_i0 is computed correctly

    Matrix3d i1_G_i0 = expected_K1.transpose() * i1_F_i0 * expected_K0;

    EXPECT_TRUE(cost.d_01.isApprox(i1_G_i0.col(0)));

    EXPECT_TRUE(cost.d_02.isApprox(i1_G_i0.col(1)));

    EXPECT_TRUE(cost.d_12.isApprox(i1_G_i0.col(2)));

}



TEST_F(FetzerFocalLengthSameCameraCostTest_164, ConstructorHandlesZeroPrincipalPoint_164) {

    principal_point.setZero();

    FetzerFocalLengthSameCameraCost cost(i1_F_i0, principal_point);

    

    // Expected K matrices with zero principal point

    Matrix3d expected_K0 = Matrix3d::Identity();

    Matrix3d expected_K1 = Matrix3d::Identity();



    // Verify that the internal transformation i1_G_i0 is computed correctly

    Matrix3d i1_G_i0 = expected_K1.transpose() * i1_F_i0 * expected_K0;

    EXPECT_TRUE(cost.d_01.isApprox(i1_G_i0.col(0)));

    EXPECT_TRUE(cost.d_02.isApprox(i1_G_i0.col(1)));

    EXPECT_TRUE(cost.d_12.isApprox(i1_G_i0.col(2)));

}



TEST_F(FetzerFocalLengthSameCameraCostTest_164, ConstructorHandlesLargePrincipalPoint_164) {

    principal_point << 1e6, 1e6;

    FetzerFocalLengthSameCameraCost cost(i1_F_i0, principal_point);

    

    // Expected K matrices with large principal point

    Matrix3d expected_K0 = Matrix3d::Identity();

    Matrix3d expected_K1 = Matrix3d::Identity();

    expected_K0(0, 2) = principal_point(0);

    expected_K0(1, 2) = principal_point(1);

    expected_K1(0, 2) = principal_point(0);

    expected_K1(1, 2) = principal_point(1);



    // Verify that the internal transformation i1_G_i0 is computed correctly

    Matrix3d i1_G_i0 = expected_K1.transpose() * i1_F_i0 * expected_K0;

    EXPECT_TRUE(cost.d_01.isApprox(i1_G_i0.col(0)));

    EXPECT_TRUE(cost.d_02.isApprox(i1_G_i0.col(1)));

    EXPECT_TRUE(cost.d_12.isApprox(i1_G_i0.col(2)));

}



TEST_F(FetzerFocalLengthSameCameraCostTest_164, ConstructorHandlesRandomPrincipalPoint_164) {

    principal_point = Vector2d::Random();

    FetzerFocalLengthSameCameraCost cost(i1_F_i0, principal_point);

    

    // Expected K matrices with random principal point

    Matrix3d expected_K0 = Matrix3d::Identity();

    Matrix3d expected_K1 = Matrix3d::Identity();

    expected_K0(0, 2) = principal_point(0);

    expected_K0(1, 2) = principal_point(1);

    expected_K1(0, 2) = principal_point(0);

    expected_K1(1, 2) = principal_point(1);



    // Verify that the internal transformation i1_G_i0 is computed correctly

    Matrix3d i1_G_i0 = expected_K1.transpose() * i1_F_i0 * expected_K0;

    EXPECT_TRUE(cost.d_01.isApprox(i1_G_i0.col(0)));

    EXPECT_TRUE(cost.d_02.isApprox(i1_G_i0.col(1)));

    EXPECT_TRUE(cost.d_12.isApprox(i1_G_i0.col(2)));

}



}  // namespace
