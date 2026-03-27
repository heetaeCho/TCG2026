#include <gtest/gtest.h>

#include <array>



// Assuming the function is_within is defined somewhere in the codebase.

template<typename T> inline bool is_within(T val1, T tolerance, T val2) {

    return std::abs(val1 - val2) <= tolerance;

}



template<size_t Mat0Size, size_t Mat1Size>

inline bool rot_matrices_equal(const std::array<double, Mat0Size> mat0, const std::array<double, Mat1Size> &mat1) {

    static_assert(Mat0Size >= 4);

    static_assert(Mat1Size >= 4);

    return is_within(mat0[0], .1, mat1[0]) && 

           is_within(mat0[1], .1, mat1[1]) && 

           is_within(mat0[2], .1, mat1[2]) && 

           is_within(mat0[3], .1, mat1[3]);

}



// Test fixture for rot_matrices_equal function

class RotMatricesEqualTest : public ::testing::Test {};



TEST_F(RotMatricesEqualTest_2631, NormalOperationWithinTolerance_2631) {

    std::array<double, 4> mat0 = {0.9, -0.4, 0.5, 0.6};

    std::array<double, 4> mat1 = {0.89, -0.41, 0.51, 0.61};

    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));

}



TEST_F(RotMatricesEqualTest_2631, NormalOperationOutsideTolerance_2631) {

    std::array<double, 4> mat0 = {0.9, -0.4, 0.5, 0.6};

    std::array<double, 4> mat1 = {0.8, -0.5, 0.4, 0.7};

    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));

}



TEST_F(RotMatricesEqualTest_2631, BoundaryConditionExactMatch_2631) {

    std::array<double, 4> mat0 = {0.9, -0.4, 0.5, 0.6};

    std::array<double, 4> mat1 = {0.9, -0.4, 0.5, 0.6};

    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));

}



TEST_F(RotMatricesEqualTest_2631, BoundaryConditionToleranceEdgeCase_2631) {

    std::array<double, 4> mat0 = {0.9, -0.4, 0.5, 0.6};

    std::array<double, 4> mat1 = {1.0, -0.5, 0.6, 0.7};

    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));

}



TEST_F(RotMatricesEqualTest_2631, BoundaryConditionToleranceJustOutside_2631) {

    std::array<double, 4> mat0 = {0.9, -0.4, 0.5, 0.6};

    std::array<double, 4> mat1 = {1.1, -0.5, 0.6, 0.7};

    EXPECT_FALSE(rot_matrices_equal(mat0, mat1));

}



TEST_F(RotMatricesEqualTest_2631, DifferentSizeArrays_2631) {

    std::array<double, 4> mat0 = {0.9, -0.4, 0.5, 0.6};

    std::array<double, 8> mat1 = {0.9, -0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};

    EXPECT_TRUE(rot_matrices_equal(mat0, mat1));

}
