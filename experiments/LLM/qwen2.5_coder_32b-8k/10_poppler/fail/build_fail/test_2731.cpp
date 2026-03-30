#include <gtest/gtest.h>

#include <array>

#include "TestProjects/poppler/utils/HtmlOutputDev.cc"

#include "TestProjects/poppler/goo/GooString.h"



using namespace std;



TEST(print_matrix_2731, NormalOperation_2731) {

    std::array<double, 6> mat = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    EXPECT_EQ(print_matrix(mat), "[1 2 3 4 5 6]");

}



TEST(print_matrix_2731, BoundaryConditions_ZeroMatrix_2731) {

    std::array<double, 6> mat = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    EXPECT_EQ(print_matrix(mat), "[0 0 0 0 0 0]");

}



TEST(print_matrix_2731, BoundaryConditions_NegativeNumbers_2731) {

    std::array<double, 6> mat = {-1.5, -2.5, -3.5, -4.5, -5.5, -6.5};

    EXPECT_EQ(print_matrix(mat), "[-1.5 -2.5 -3.5 -4.5 -5.5 -6.5]");

}



TEST(print_matrix_2731, BoundaryConditions_MixedNumbers_2731) {

    std::array<double, 6> mat = {-1.0, 2.0, -3.0, 4.0, -5.0, 6.0};

    EXPECT_EQ(print_matrix(mat), "[-1 2 -3 4 -5 6]");

}



TEST(print_matrix_2731, BoundaryConditions_ScientificNotation_2731) {

    std::array<double, 6> mat = {1e-9, 2e-8, 3e-7, 4e-6, 5e-5, 6e-4};

    EXPECT_EQ(print_matrix(mat), "[0.000000001 2e-08 3e-07 4e-06 0.00005 0.0006]");

}
