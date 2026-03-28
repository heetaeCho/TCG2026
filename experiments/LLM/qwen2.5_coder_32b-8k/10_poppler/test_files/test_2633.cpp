#include <gtest/gtest.h>

#include <array>



// Assuming HtmlUtils.h is included in the same directory as the test file.

#include "HtmlUtils.h"



using namespace std;



TEST(rot_matrices_equal_2633, MatricesEqualWithinTolerance_2633) {

    array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};

    array<double, 4> mat1 = {1.05, 2.05, 3.05, 4.05};

    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));

}



TEST(rot_matrices_equal_2633, MatricesNotEqualOutsideTolerance_2633) {

    array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};

    array<double, 4> mat1 = {1.2, 2.2, 3.2, 4.2};

    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));

}



TEST(rot_matrices_equal_2633, MatricesEqualExactly_2633) {

    array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};

    array<double, 4> mat1 = {1.0, 2.0, 3.0, 4.0};

    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));

}



TEST(rot_matrices_equal_2633, MatricesEqualBoundaryTolerance_2633) {

    array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};

    array<double, 4> mat1 = {1.1, 2.1, 3.1, 4.1};

    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));

}



TEST(rot_matrices_equal_2633, MatricesNotEqualBoundaryTolerance_2633) {

    array<double, 4> mat0 = {1.0, 2.0, 3.0, 4.0};

    array<double, 4> mat1 = {1.11, 2.11, 3.11, 4.11};

    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));

}
