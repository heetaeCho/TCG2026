#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "ceres/ceres.h"

#include "Eigen/Dense"

#include "./TestProjects/glomap/glomap/estimators/cost_function.h"



using namespace glomap;

using namespace Eigen;

using ::testing::_;

using ::testing::Return;



class FetzerFocalLengthCostTest_167 : public ::testing::Test {

protected:

    Matrix3d i1_F_i0;

    Vector2d principal_point0;

    Vector2d principal_point1;



    void SetUp() override {

        i1_F_i0 = Matrix3d::Random();

        principal_point0 << 5.0, 5.0;

        principal_point1 << 6.0, 6.0;

    }

};



TEST_F(FetzerFocalLengthCostTest_167, CreateFunctionReturnsNonNullPtr_167) {

    auto cost_function = FetzerFocalLengthCost::Create(i1_F_i0, principal_point0, principal_point1);

    EXPECT_NE(cost_function, nullptr);

}



TEST_F(FetzerFocalLengthCostTest_167, OperatorParenthesisNormalOperation_167) {

    double fi[] = {1.0, 2.0};

    double fj[] = {3.0, 4.0};

    double residuals[1];

    

    FetzerFocalLengthCost cost_function(i1_F_i0, principal_point0, principal_point1);

    bool success = cost_function(fi, fj, residuals);



    EXPECT_TRUE(success);

}



TEST_F(FetzerFocalLengthCostTest_167, OperatorParenthesisBoundaryConditions_167) {

    double fi[] = {std::numeric_limits<double>::max(), std::numeric_limits<double>::lowest()};

    double fj[] = {std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max()};

    double residuals[1];

    

    FetzerFocalLengthCost cost_function(i1_F_i0, principal_point0, principal_point1);

    bool success = cost_function(fi, fj, residuals);



    EXPECT_TRUE(success);

}



TEST_F(FetzerFocalLengthCostTest_167, CreateFunctionWithZeroMatrix_167) {

    Matrix3d zero_matrix = Matrix3d::Zero();

    auto cost_function = FetzerFocalLengthCost::Create(zero_matrix, principal_point0, principal_point1);

    

    EXPECT_NE(cost_function, nullptr);



    double fi[] = {1.0, 2.0};

    double fj[] = {3.0, 4.0};

    double residuals[1];

    bool success = cost_function->Evaluate(&fi, &fj, residuals);



    EXPECT_TRUE(success);

}



TEST_F(FetzerFocalLengthCostTest_167, CreateFunctionWithIdentityMatrix_167) {

    Matrix3d identity_matrix = Matrix3d::Identity();

    auto cost_function = FetzerFocalLengthCost::Create(identity_matrix, principal_point0, principal_point1);



    EXPECT_NE(cost_function, nullptr);



    double fi[] = {1.0, 2.0};

    double fj[] = {3.0, 4.0};

    double residuals[1];

    bool success = cost_function->Evaluate(&fi, &fj, residuals);



    EXPECT_TRUE(success);

}
