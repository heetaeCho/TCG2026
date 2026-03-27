#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/glomap/math/two_view_geometry.h"

#include "glomap/glomap/types.h"



namespace glomap {



class TwoViewGeometryTest_139 : public ::testing::Test {

protected:

    Eigen::Matrix3d E;

    Eigen::Vector3d x1;

    Eigen::Vector3d x2;



    void SetUp() override {

        // Initialize with some default values

        E << 1, 0, 0,

             0, 1, 0,

             0, 0, 1;



        x1 << 1, 2, 3;

        x2 << 4, 5, 6;

    }

};



TEST_F(TwoViewGeometryTest_139, NormalOperation_139) {

    double result = SampsonError(E, x1, x2);

    EXPECT_DOUBLE_EQ(result, 0.0); // Expected result based on the default values

}



TEST_F(TwoViewGeometryTest_139, BoundaryConditionZeroZ1_139) {

    x1[2] = 0;

    double result = SampsonError(E, x1, x2);

    EXPECT_DOUBLE_EQ(result, 0.0); // EPS should handle division by zero

}



TEST_F(TwoViewGeometryTest_139, BoundaryConditionZeroZ2_139) {

    x2[2] = 0;

    double result = SampsonError(E, x1, x2);

    EXPECT_DOUBLE_EQ(result, 0.0); // EPS should handle division by zero

}



TEST_F(TwoViewGeometryTest_139, BoundaryConditionZeroX1AndX2_139) {

    x1 << 0, 0, 1;

    x2 << 0, 0, 1;

    double result = SampsonError(E, x1, x2);

    EXPECT_DOUBLE_EQ(result, 0.0); // Expected result based on the default values

}



TEST_F(TwoViewGeometryTest_139, ExceptionalCaseLargeValues_139) {

    x1 << 1e10, 2e10, 3e10;

    x2 << 4e10, 5e10, 6e10;

    double result = SampsonError(E, x1, x2);

    EXPECT_DOUBLE_EQ(result, 0.0); // Expected result based on the default values

}



TEST_F(TwoViewGeometryTest_139, ExceptionalCaseSmallValues_139) {

    x1 << 1e-10, 2e-10, 3e-10;

    x2 << 4e-10, 5e-10, 6e-10;

    double result = SampsonError(E, x1, x2);

    EXPECT_DOUBLE_EQ(result, 0.0); // Expected result based on the default values

}



} // namespace glomap
