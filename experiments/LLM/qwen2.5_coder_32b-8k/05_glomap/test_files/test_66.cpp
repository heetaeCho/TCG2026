#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Eigen/Dense"

#include "glomap/math/two_view_geometry.h"



using namespace glomap;

using namespace Eigen;



class TwoViewGeometryTest_66 : public ::testing::Test {

protected:

    Matrix3d F;

    Vector3d epipole;

    Vector2d pt1, pt2;

};



TEST_F(TwoViewGeometryTest_66, NormalOperationPositiveSignum_66) {

    // Arrange

    F << 1, 0, 0,

         0, 1, 0,

         0, 0, 1;

    epipole << 1, 2, 3;

    pt1 << 4, 5;

    pt2 << 6, 7;



    // Act

    double result = GetOrientationSignum(F, epipole, pt1, pt2);



    // Assert

    EXPECT_GT(result, 0);

}



TEST_F(TwoViewGeometryTest_66, NormalOperationNegativeSignum_66) {

    // Arrange

    F << -1, 0, 0,

         0, -1, 0,

         0, 0, -1;

    epipole << 1, 2, 3;

    pt1 << 4, 5;

    pt2 << 6, 7;



    // Act

    double result = GetOrientationSignum(F, epipole, pt1, pt2);



    // Assert

    EXPECT_LT(result, 0);

}



TEST_F(TwoViewGeometryTest_66, ZeroSignum_66) {

    // Arrange

    F << 1, 0, 0,

         0, 1, 0,

         0, 0, 0;

    epipole << 1, 2, 3;

    pt1 << 4, 5;

    pt2 << 6, 7;



    // Act

    double result = GetOrientationSignum(F, epipole, pt1, pt2);



    // Assert

    EXPECT_EQ(result, 0);

}



TEST_F(TwoViewGeometryTest_66, BoundaryConditionEpipoleZero_66) {

    // Arrange

    F << 1, 0, 0,

         0, 1, 0,

         0, 0, 1;

    epipole << 0, 0, 0;

    pt1 << 4, 5;

    pt2 << 6, 7;



    // Act

    double result = GetOrientationSignum(F, epipole, pt1, pt2);



    // Assert

    EXPECT_EQ(result, 0);

}



TEST_F(TwoViewGeometryTest_66, BoundaryConditionPointsZero_66) {

    // Arrange

    F << 1, 0, 0,

         0, 1, 0,

         0, 0, 1;

    epipole << 1, 2, 3;

    pt1 << 0, 0;

    pt2 << 0, 0;



    // Act

    double result = GetOrientationSignum(F, epipole, pt1, pt2);



    // Assert

    EXPECT_EQ(result, 0);

}



TEST_F(TwoViewGeometryTest_66, BoundaryConditionFZeroMatrix_66) {

    // Arrange

    F << 0, 0, 0,

         0, 0, 0,

         0, 0, 0;

    epipole << 1, 2, 3;

    pt1 << 4, 5;

    pt2 << 6, 7;



    // Act

    double result = GetOrientationSignum(F, epipole, pt1, pt2);



    // Assert

    EXPECT_EQ(result, 0);

}
