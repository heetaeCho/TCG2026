#include <gtest/gtest.h>

#include <Eigen/Dense>

#include "./TestProjects/glomap/glomap/estimators/cost_function.h"



namespace glomap {



// Mocking helper function to control its behavior in tests

class CostFunctionMock {

public:

    static std::array<Eigen::Vector4d, 3> fetzer_d_mock(

        const Eigen::Vector3d& ai, const Eigen::Vector3d& bi,

        const Eigen::Vector3d& aj, const Eigen::Vector3d& bj,

        int i, int j) {

        // Mock implementation for testing purposes

        std::array<Eigen::Vector4d, 3> ds;

        ds[0] = Eigen::Vector4d(1.0, 2.0, 3.0, 4.0);

        ds[1] = Eigen::Vector4d(5.0, 6.0, 7.0, 8.0);

        ds[2] = Eigen::Vector4d(9.0, 10.0, 11.0, 12.0);

        return ds;

    }

};



// Overriding the real fetzer_d function with our mock version for testing

Eigen::Vector4d fetzer_d(

    const Eigen::Vector3d& ai, const Eigen::Vector3d& bi,

    const Eigen::Vector3d& aj, const Eigen::Vector3d& bj,

    int i, int j) {

    return CostFunctionMock::fetzer_d_mock(ai, bi, aj, bj, i, j)[i];

}



class CostFunctionTest_16 : public ::testing::Test {};



TEST_F(CostFunctionTest_16, NormalOperation_16) {

    Eigen::Matrix3d i1_G_i0;

    i1_G_i0 << 1.0, 2.0, 3.0,

               4.0, 5.0, 6.0,

               7.0, 8.0, 9.0;



    std::array<Eigen::Vector4d, 3> result = fetzer_ds(i1_G_i0);



    EXPECT_EQ(result[0], Eigen::Vector4d(1.0, 2.0, 3.0, 4.0));

    EXPECT_EQ(result[1], Eigen::Vector4d(5.0, 6.0, 7.0, 8.0));

    EXPECT_EQ(result[2], Eigen::Vector4d(9.0, 10.0, 11.0, 12.0));

}



TEST_F(CostFunctionTest_16, BoundaryConditions_16) {

    // Test with zero matrix

    Eigen::Matrix3d i1_G_i0_zero = Eigen::Matrix3d::Zero();

    std::array<Eigen::Vector4d, 3> result_zero = fetzer_ds(i1_G_i0_zero);



    EXPECT_TRUE(result_zero[0].isZero());

    EXPECT_TRUE(result_zero[1].isZero());

    EXPECT_TRUE(result_zero[2].isZero());



    // Test with identity matrix

    Eigen::Matrix3d i1_G_i0_identity = Eigen::Matrix3d::Identity();

    std::array<Eigen::Vector4d, 3> result_identity = fetzer_ds(i1_G_i0_identity);



    EXPECT_TRUE(result_identity[0].isZero());

    EXPECT_TRUE(result_identity[1].isZero());

    EXPECT_TRUE(result_identity[2].isZero());

}



} // namespace glomap
