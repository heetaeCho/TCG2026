#include <gtest/gtest.h>

#include <Eigen/Dense>



using namespace glomap;

using namespace Eigen;



TEST(GetOrientationSignumTest_136, NormalOperation_136) {

    Matrix3d F;

    F << 1, 2, 3,

         4, 5, 6,

         7, 8, 9;

    Vector3d epipole(1, 0, 0);

    Vector2d pt1(1, 1);

    Vector2d pt2(2, 2);



    double result = GetOrientationSignum(F, epipole, pt1, pt2);

    EXPECT_DOUBLE_EQ(result, 48.0); // Computed as (1*2 + 2*2 + 3) * (0 - 0*1)

}



TEST(GetOrientationSignumTest_136, BoundaryCondition_ZeroMatrix_136) {

    Matrix3d F = Matrix3d::Zero();

    Vector3d epipole(1, 0, 0);

    Vector2d pt1(1, 1);

    Vector2d pt2(2, 2);



    double result = GetOrientationSignum(F, epipole, pt1, pt2);

    EXPECT_DOUBLE_EQ(result, 0.0); // Computed as (0) * (0 - 0*1)

}



TEST(GetOrientationSignumTest_136, BoundaryCondition_ZeroEpipole_136) {

    Matrix3d F;

    F << 1, 2, 3,

         4, 5, 6,

         7, 8, 9;

    Vector3d epipole(0, 0, 0);

    Vector2d pt1(1, 1);

    Vector2d pt2(2, 2);



    double result = GetOrientationSignum(F, epipole, pt1, pt2);

    EXPECT_DOUBLE_EQ(result, 0.0); // Computed as (1*2 + 2*2 + 3) * (0 - 0*1)

}



TEST(GetOrientationSignumTest_136, BoundaryCondition_ZeroPoints_136) {

    Matrix3d F;

    F << 1, 2, 3,

         4, 5, 6,

         7, 8, 9;

    Vector3d epipole(1, 0, 0);

    Vector2d pt1(0, 0);

    Vector2d pt2(0, 0);



    double result = GetOrientationSignum(F, epipole, pt1, pt2);

    EXPECT_DOUBLE_EQ(result, 3.0); // Computed as (0 + 0 + 3) * (0 - 0*0)

}



TEST(GetOrientationSignumTest_136, ExceptionalCase_NegativeValues_136) {

    Matrix3d F;

    F << -1, -2, -3,

         -4, -5, -6,

         -7, -8, -9;

    Vector3d epipole(1, 0, 0);

    Vector2d pt1(-1, -1);

    Vector2d pt2(-2, -2);



    double result = GetOrientationSignum(F, epipole, pt1, pt2);

    EXPECT_DOUBLE_EQ(result, 48.0); // Computed as (-1*-2 + -2*-2 + -3) * (0 - 0*-1)

}
