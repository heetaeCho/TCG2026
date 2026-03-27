#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "Eigen/Dense"

#include "two_view_geometry.h"



namespace glomap {

namespace {



class SampsonErrorTest_138 : public ::testing::Test {

protected:

    Eigen::Matrix3d E;

    Eigen::Vector2d x1;

    Eigen::Vector2d x2;



    void SetUp() override {

        // Initialize E to a generic essential matrix

        E << 0, -1, 4,

             1, 0, 5,

            -4,-5, 0;



        // Initialize x1 and x2 to generic points

        x1 << 1.0, 2.0;

        x2 << 3.0, 4.0;

    }

};



TEST_F(SampsonErrorTest_138, NormalOperation_138) {

    double result = SampsonError(E, x1, x2);

    EXPECT_TRUE(result >= 0); // Sampson Error should be non-negative

}



TEST_F(SampsonErrorTest_138, BoundaryConditionZeroPoints_138) {

    Eigen::Vector2d zero_point(0.0, 0.0);

    double result = SampsonError(E, zero_point, zero_point);

    EXPECT_EQ(result, 0); // Expected to be zero if both points are origin

}



TEST_F(SampsonErrorTest_138, BoundaryConditionCollinearPoints_138) {

    Eigen::Vector2d collinear_x1(1.0, 2.0);

    Eigen::Vector2d collinear_x2(2.0, 4.0); // x2 is a multiple of x1

    double result = SampsonError(E, collinear_x1, collinear_x2);

    EXPECT_TRUE(result >= 0); // Sampson Error should be non-negative

}



TEST_F(SampsonErrorTest_138, BoundaryConditionLargePoints_138) {

    Eigen::Vector2d large_x1(1e6, 2e6);

    Eigen::Vector2d large_x2(3e6, 4e6);

    double result = SampsonError(E, large_x1, large_x2);

    EXPECT_TRUE(result >= 0); // Sampson Error should be non-negative

}



TEST_F(SampsonErrorTest_138, BoundaryConditionSmallPoints_138) {

    Eigen::Vector2d small_x1(1e-6, 2e-6);

    Eigen::Vector2d small_x2(3e-6, 4e-6);

    double result = SampsonError(E, small_x1, small_x2);

    EXPECT_TRUE(result >= 0); // Sampson Error should be non-negative

}



TEST_F(SampsonErrorTest_138, BoundaryConditionIdentityMatrix_138) {

    Eigen::Matrix3d identity_matrix = Eigen::Matrix3d::Identity();

    double result = SampsonError(identity_matrix, x1, x2);

    EXPECT_TRUE(result >= 0); // Sampson Error should be non-negative

}



TEST_F(SampsonErrorTest_138, BoundaryConditionRandomMatrix_138) {

    Eigen::Matrix3d random_matrix;

    random_matrix.setRandom();

    double result = SampsonError(random_matrix, x1, x2);

    EXPECT_TRUE(result >= 0); // Sampson Error should be non-negative

}



} // namespace

} // namespace glomap
