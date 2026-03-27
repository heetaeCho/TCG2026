#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/estimators/cost_function.h"

#include <Eigen/Dense>



using namespace glomap;

using namespace Eigen;



TEST_F(FetzerFocalLengthCostTest_17, NormalOperation_17) {

    Matrix3d i1_F_i0 = Matrix3d::Identity();

    Vector2d principal_point0(0.0, 0.0);

    Vector2d principal_point1(0.0, 0.0);



    FetzerFocalLengthCost cost_function(i1_F_i0, principal_point0, principal_point1);



    double fi = 1.0;

    double fj = 2.0;

    double residuals[2];



    bool result = cost_function(&fi, &fj, residuals);

    

    EXPECT_TRUE(result);

    // Assuming normal operation results in non-zero residuals

    EXPECT_NE(residuals[0], 0.0);

    EXPECT_NE(residuals[1], 0.0);

}



TEST_F(FetzerFocalLengthCostTest_17, BoundaryCondition_ZeroFi_17) {

    Matrix3d i1_F_i0 = Matrix3d::Identity();

    Vector2d principal_point0(0.0, 0.0);

    Vector2d principal_point1(0.0, 0.0);



    FetzerFocalLengthCost cost_function(i1_F_i0, principal_point0, principal_point1);



    double fi = 0.0;

    double fj = 2.0;

    double residuals[2];



    bool result = cost_function(&fi, &fj, residuals);

    

    EXPECT_TRUE(result);

    // Assuming boundary condition results in a specific value for residuals

    EXPECT_NEAR(residuals[0], 1.0, 1e-5); // due to T(1e-6) replacement

}



TEST_F(FetzerFocalLengthCostTest_17, BoundaryCondition_ZeroFj_17) {

    Matrix3d i1_F_i0 = Matrix3d::Identity();

    Vector2d principal_point0(0.0, 0.0);

    Vector2d principal_point1(0.0, 0.0);



    FetzerFocalLengthCost cost_function(i1_F_i0, principal_point0, principal_point1);



    double fi = 1.0;

    double fj = 0.0;

    double residuals[2];



    bool result = cost_function(&fi, &fj, residuals);

    

    EXPECT_TRUE(result);

    // Assuming boundary condition results in a specific value for residuals

    EXPECT_NEAR(residuals[1], 1.0, 1e-5); // due to T(1e-6) replacement

}



TEST_F(FetzerFocalLengthCostTest_17, ExceptionalCase_NegativeFi_17) {

    Matrix3d i1_F_i0 = Matrix3d::Identity();

    Vector2d principal_point0(0.0, 0.0);

    Vector2d principal_point1(0.0, 0.0);



    FetzerFocalLengthCost cost_function(i1_F_i0, principal_point0, principal_point1);



    double fi = -1.0;

    double fj = 2.0;

    double residuals[2];



    bool result = cost_function(&fi, &fj, residuals);

    

    EXPECT_TRUE(result);

    // Assuming exceptional case results in specific behavior

}



TEST_F(FetzerFocalLengthCostTest_17, ExceptionalCase_NegativeFj_17) {

    Matrix3d i1_F_i0 = Matrix3d::Identity();

    Vector2d principal_point0(0.0, 0.0);

    Vector2d principal_point1(0.0, 0.0);



    FetzerFocalLengthCost cost_function(i1_F_i0, principal_point0, principal_point1);



    double fi = 1.0;

    double fj = -2.0;

    double residuals[2];



    bool result = cost_function(&fi, &fj, residuals);

    

    EXPECT_TRUE(result);

    // Assuming exceptional case results in specific behavior

}
