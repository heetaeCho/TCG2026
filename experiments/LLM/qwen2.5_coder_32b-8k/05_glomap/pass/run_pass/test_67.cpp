#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/math/two_view_geometry.h"



using namespace glomap;

using namespace Eigen;



namespace {



TEST(SampsonErrorTest_67, NormalOperation_67) {

    Matrix3d E = Matrix3d::Random();

    Vector2d x1(1.0, 2.0);

    Vector2d x2(3.0, 4.0);



    double error = SampsonError(E, x1, x2);



    EXPECT_TRUE(error >= 0); // Sampson error should be non-negative

}



TEST(SampsonErrorTest_67, BoundaryCondition_ZeroE_67) {

    Matrix3d E = Matrix3d::Zero();

    Vector2d x1(1.0, 2.0);

    Vector2d x2(3.0, 4.0);



    double error = SampsonError(E, x1, x2);



    EXPECT_EQ(error, 0); // When E is zero, the Sampson error should be zero

}



TEST(SampsonErrorTest_67, BoundaryCondition_ZeroX1_67) {

    Matrix3d E = Matrix3d::Random();

    Vector2d x1(0.0, 0.0);

    Vector2d x2(3.0, 4.0);



    double error = SampsonError(E, x1, x2);



    EXPECT_EQ(error, 0); // When x1 is zero, the Sampson error should be zero

}



TEST(SampsonErrorTest_67, BoundaryCondition_ZeroX2_67) {

    Matrix3d E = Matrix3d::Random();

    Vector2d x1(1.0, 2.0);

    Vector2d x2(0.0, 0.0);



    double error = SampsonError(E, x1, x2);



    EXPECT_EQ(error, 0); // When x2 is zero, the Sampson error should be zero

}



TEST(SampsonErrorTest_67, BoundaryCondition_IdentityE_67) {

    Matrix3d E = Matrix3d::Identity();

    Vector2d x1(1.0, 2.0);

    Vector2d x2(3.0, 4.0);



    double error = SampsonError(E, x1, x2);



    EXPECT_TRUE(error >= 0); // When E is identity, the Sampson error should be non-negative

}



TEST(SampsonErrorTest_67, ExceptionalCase_ParallelVectors_67) {

    Matrix3d E = Matrix3d::Random();

    Vector2d x1(1.0, 2.0);

    Vector2d x2 = 2 * x1; // x2 is a multiple of x1



    double error = SampsonError(E, x1, x2);



    EXPECT_TRUE(error >= 0); // Even if vectors are parallel, Sampson error should be non-negative

}



} // namespace
