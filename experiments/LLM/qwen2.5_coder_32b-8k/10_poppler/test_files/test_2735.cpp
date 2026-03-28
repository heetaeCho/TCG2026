#include <gtest/gtest.h>

#include <array>

#include "HtmlUtils.h"



using namespace std;



// Mock function for is_within to simulate its behavior

bool mock_is_within(double val1, double tolerance, double val2) {

    return abs(val1 - val2) <= tolerance;

}



TEST(rot_matrices_equal_2735, EqualMatrices_2735) {

    array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};

    array<double, 4> mat1 = {1.0, 2.0, 3.0, 4.0};



    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));

}



TEST(rot_matrices_equal_2735, NearlyEqualMatrices_2735) {

    array<double, 4> mat0 = {1.05, 2.05, 3.05, 4.05};

    array<double, 4> mat1 = {1.0, 2.0, 3.0, 4.0};



    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));

}



TEST(rot_matrices_equal_2735, NotEqualMatrices_2735) {

    array<double, 4> mat0 = {1.2, 2.2, 3.2, 4.2};

    array<double, 4> mat1 = {1.0, 2.0, 3.0, 4.0};



    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));

}



TEST(rot_matrices_equal_2735, BoundaryConditionTolerance_2735) {

    array<double, 4> mat0 = {1.1, 2.1, 3.1, 4.1};

    array<double, 4> mat1 = {1.0, 2.0, 3.0, 4.0};



    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));

}



TEST(rot_matrices_equal_2735, BoundaryConditionOutsideTolerance_2735) {

    array<double, 4> mat0 = {1.11, 2.11, 3.11, 4.11};

    array<double, 4> mat1 = {1.0, 2.0, 3.0, 4.0};



    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));

}



TEST(rot_matrices_equal_2735, DifferentSizeMatrices_2735) {

    array<double, 6> mat0 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    array<double, 6> mat1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};



    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));

}



TEST(rot_matrices_equal_2735, DifferentSizeMatricesWithTolerance_2735) {

    array<double, 6> mat0 = {1.1, 2.1, 3.1, 4.1, 5.1, 6.1};

    array<double, 6> mat1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};



    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));

}



TEST(rot_matrices_equal_2735, DifferentSizeMatricesOutsideTolerance_2735) {

    array<double, 6> mat0 = {1.2, 2.2, 3.2, 4.2, 5.2, 6.2};

    array<double, 6> mat1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};



    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));

}
