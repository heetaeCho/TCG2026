#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/utils/HtmlOutputDev.cc"

#include "./TestProjects/poppler/goo/GooString.h"



using namespace std;

using ::testing::Eq;



TEST(PrintMatrixTest_2730, NormalOperation_2730) {

    std::array<double, 4> mat = {1.1, 2.2, 3.3, 4.4};

    EXPECT_EQ(print_matrix(mat), "[1.1 2.2 3.3 4.4]");

}



TEST(PrintMatrixTest_2730, BoundaryConditions_Zeros_2730) {

    std::array<double, 4> mat = {0.0, 0.0, 0.0, 0.0};

    EXPECT_EQ(print_matrix(mat), "[0 0 0 0]");

}



TEST(PrintMatrixTest_2730, BoundaryConditions_Negatives_2730) {

    std::array<double, 4> mat = {-1.1, -2.2, -3.3, -4.4};

    EXPECT_EQ(print_matrix(mat), "[-1.1 -2.2 -3.3 -4.4]");

}



TEST(PrintMatrixTest_2730, BoundaryConditions_MaxValues_2730) {

    std::array<double, 4> mat = {DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX};

    EXPECT_EQ(print_matrix(mat), "[1.79769e+308 1.79769e+308 1.79769e+308 1.79769e+308]");

}



TEST(PrintMatrixTest_2730, BoundaryConditions_MinValues_2730) {

    std::array<double, 4> mat = {-DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX};

    EXPECT_EQ(print_matrix(mat), "[-1.79769e+308 -1.79769e+308 -1.79769e+308 -1.79769e+308]");

}
