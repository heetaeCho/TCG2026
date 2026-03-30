#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "cost_function.h"



using namespace glomap;

using namespace Eigen;



class FetzerFocalLengthSameCameraCostTest_168 : public ::testing::Test {

protected:

    Matrix3d i1_F_i0;

    Vector2d principal_point;



    void SetUp() override {

        i1_F_i0 << 1, 0, 0,

                   0, 1, 0,

                   0, 0, 1;

        principal_point << 150, 100;

    }

};



TEST_F(FetzerFocalLengthSameCameraCostTest_168, ConstructorWithIdentityMatrixAndPrincipalPoint_168) {

    FetzerFocalLengthSameCameraCost cost(i1_F_i0, principal_point);

    // Since the constructor does not have observable side effects other than internal state,

    // we can only assume it initializes correctly based on the provided parameters.

}



TEST_F(FetzerFocalLengthSameCameraCostTest_168, CreateFunctionWithIdentityMatrixAndPrincipalPoint_168) {

    ceres::CostFunction* cost_function = FetzerFocalLengthSameCameraCost::Create(i1_F_i0, principal_point);

    ASSERT_NE(cost_function, nullptr);

    delete cost_function;

}



TEST_F(FetzerFocalLengthSameCameraCostTest_168, CreateFunctionWithNonIdentityMatrixAndPrincipalPoint_168) {

    i1_F_i0 << 2, 0, 0,

               0, 3, 0,

               0, 0, 1;

    principal_point << 200, 150;



    ceres::CostFunction* cost_function = FetzerFocalLengthSameCameraCost::Create(i1_F_i0, principal_point);

    ASSERT_NE(cost_function, nullptr);

    delete cost_function;

}



TEST_F(FetzerFocalLengthSameCameraCostTest_168, CreateFunctionWithZeroMatrixAndPrincipalPoint_168) {

    i1_F_i0.setZero();



    ceres::CostFunction* cost_function = FetzerFocalLengthSameCameraCost::Create(i1_F_i0, principal_point);

    ASSERT_NE(cost_function, nullptr);

    delete cost_function;

}



TEST_F(FetzerFocalLengthSameCameraCostTest_168, CreateFunctionWithPrincipalPointAtOrigin_168) {

    principal_point.setZero();



    ceres::CostFunction* cost_function = FetzerFocalLengthSameCameraCost::Create(i1_F_i0, principal_point);

    ASSERT_NE(cost_function, nullptr);

    delete cost_function;

}
