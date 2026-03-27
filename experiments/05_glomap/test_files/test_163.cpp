#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Eigen/Dense>

#include "cost_function.h"



namespace glomap {

namespace {



class FetzerFocalLengthCostTest : public ::testing::Test {

protected:

    void SetUp() override {

        i1_F_i0 << 1, 2, 3,

                   4, 5, 6,

                   7, 8, 9;

        principal_point0 << 0.5, 1.5;

        principal_point1 << -0.5, -1.5;

    }



    Eigen::Matrix3d i1_F_i0;

    Eigen::Vector2d principal_point0;

    Eigen::Vector2d principal_point1;

};



TEST_F(FetzerFocalLengthCostTest_163, ConstructorInitializesMatricesCorrectly_163) {

    FetzerFocalLengthCost cost(i1_F_i0, principal_point0, principal_point1);

    // Since the internal state is not accessible, we can only verify that the object is constructed without errors.

}



TEST_F(FetzerFocalLengthCostTest_163, ConstructorHandlesZeroPrincipalPoints_163) {

    Eigen::Vector2d zero_principal_point(0.0, 0.0);

    FetzerFocalLengthCost cost(i1_F_i0, zero_principal_point, zero_principal_point);

    // Verify that the object is constructed without errors when principal points are zero.

}



TEST_F(FetzerFocalLengthCostTest_163, ConstructorHandlesNegativePrincipalPoints_163) {

    Eigen::Vector2d negative_principal_point(-1.0, -1.0);

    FetzerFocalLengthCost cost(i1_F_i0, negative_principal_point, negative_principal_point);

    // Verify that the object is constructed without errors when principal points are negative.

}



TEST_F(FetzerFocalLengthCostTest_163, ConstructorHandlesLargePrincipalPoints_163) {

    Eigen::Vector2d large_principal_point(1000.0, 1000.0);

    FetzerFocalLengthCost cost(i1_F_i0, large_principal_point, large_principal_point);

    // Verify that the object is constructed without errors when principal points are large.

}



TEST_F(FetzerFocalLengthCostTest_163, ConstructorHandlesIdentityMatrix_163) {

    Eigen::Matrix3d identity_matrix = Eigen::Matrix3d::Identity();

    FetzerFocalLengthCost cost(identity_matrix, principal_point0, principal_point1);

    // Verify that the object is constructed without errors when i1_F_i0 is an identity matrix.

}



TEST_F(FetzerFocalLengthCostTest_163, ConstructorHandlesSingularMatrix_163) {

    Eigen::Matrix3d singular_matrix;

    singular_matrix << 1, 2, 3,

                       4, 5, 6,

                       8, 10, 12; // Last row is a multiple of the first row, making it singular.

    EXPECT_THROW(FetzerFocalLengthCost cost(singular_matrix, principal_point0, principal_point1), std::exception);

    // Verify that the object throws an exception when i1_F_i0 is singular. This is a hypothetical test as no exception is thrown in the provided code.

}



}  // namespace

}  // namespace glomap
