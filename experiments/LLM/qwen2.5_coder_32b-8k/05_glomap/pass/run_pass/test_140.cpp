#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/math/two_view_geometry.cc"



namespace glomap {



TEST(HomographyErrorTest_140, NormalOperation_140) {

    Eigen::Matrix3d H;

    H << 1, 0, 0,

         0, 1, 0,

         0, 0, 1;

    Eigen::Vector2d x1(1.0, 1.0);

    Eigen::Vector2d x2(1.0, 1.0);



    double error = HomographyError(H, x1, x2);

    EXPECT_DOUBLE_EQ(error, 0.0);

}



TEST(HomographyErrorTest_140, BoundaryCondition_ZeroMatrix_140) {

    Eigen::Matrix3d H;

    H.setZero();

    Eigen::Vector2d x1(1.0, 1.0);

    Eigen::Vector2d x2(1.0, 1.0);



    double error = HomographyError(H, x1, x2);

    EXPECT_DOUBLE_EQ(error, (x1 - x2).squaredNorm() / EPS);

}



TEST(HomographyErrorTest_140, BoundaryCondition_SmallEpsilon_140) {

    Eigen::Matrix3d H;

    H << 1, 0, 0,

         0, 1, 0,

         0, 0, EPS;

    Eigen::Vector2d x1(1.0, 1.0);

    Eigen::Vector2d x2(1.0, 1.0);



    double error = HomographyError(H, x1, x2);

    EXPECT_DOUBLE_EQ(error, 0.0);

}



TEST(HomographyErrorTest_140, ExceptionalCase_DifferentPoints_140) {

    Eigen::Matrix3d H;

    H << 1, 0, 0,

         0, 1, 0,

         0, 0, 1;

    Eigen::Vector2d x1(1.0, 1.0);

    Eigen::Vector2d x2(2.0, 2.0);



    double error = HomographyError(H, x1, x2);

    EXPECT_DOUBLE_EQ(error, 2.0);

}



} // namespace glomap
