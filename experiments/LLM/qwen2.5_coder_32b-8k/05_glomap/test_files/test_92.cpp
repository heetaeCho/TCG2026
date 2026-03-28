#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Eigen/Dense>

#include "glomap/estimators/cost_function.h"



using namespace glomap;

using namespace Eigen;



TEST(fetzer_ds_92, NormalOperation_92) {

    Matrix3d i1_G_i0;

    i1_G_i0 << 1.0, 0.0, 0.0,

               0.0, 1.0, 0.0,

               0.0, 0.0, 1.0;



    std::array<Vector4d, 3> result = fetzer_ds(i1_G_i0);



    EXPECT_TRUE(result[0].allFinite());

    EXPECT_TRUE(result[1].allFinite());

    EXPECT_TRUE(result[2].allFinite());

}



TEST(fetzer_ds_92, BoundaryConditionZeroMatrix_92) {

    Matrix3d i1_G_i0 = Matrix3d::Zero();



    std::array<Vector4d, 3> result = fetzer_ds(i1_G_i0);



    EXPECT_TRUE(result[0].allFinite());

    EXPECT_TRUE(result[1].allFinite());

    EXPECT_TRUE(result[2].allFinite());

}



TEST(fetzer_ds_92, BoundaryConditionIdentityMatrix_92) {

    Matrix3d i1_G_i0 = Matrix3d::Identity();



    std::array<Vector4d, 3> result = fetzer_ds(i1_G_i0);



    EXPECT_TRUE(result[0].allFinite());

    EXPECT_TRUE(result[1].allFinite());

    EXPECT_TRUE(result[2].allFinite());

}



TEST(fetzer_ds_92, BoundaryConditionRandomMatrix_92) {

    Matrix3d i1_G_i0 = Matrix3d::Random();



    std::array<Vector4d, 3> result = fetzer_ds(i1_G_i0);



    EXPECT_TRUE(result[0].allFinite());

    EXPECT_TRUE(result[1].allFinite());

    EXPECT_TRUE(result[2].allFinite());

}



TEST(fetzer_ds_92, BoundaryConditionLargeValuesMatrix_92) {

    Matrix3d i1_G_i0;

    i1_G_i0 << 1e6, 0.0, 0.0,

               0.0, 1e6, 0.0,

               0.0, 0.0, 1e6;



    std::array<Vector4d, 3> result = fetzer_ds(i1_G_i0);



    EXPECT_TRUE(result[0].allFinite());

    EXPECT_TRUE(result[1].allFinite());

    EXPECT_TRUE(result[2].allFinite());

}



TEST(fetzer_ds_92, BoundaryConditionSmallValuesMatrix_92) {

    Matrix3d i1_G_i0;

    i1_G_i0 << 1e-6, 0.0, 0.0,

               0.0, 1e-6, 0.0,

               0.0, 0.0, 1e-6;



    std::array<Vector4d, 3> result = fetzer_ds(i1_G_i0);



    EXPECT_TRUE(result[0].allFinite());

    EXPECT_TRUE(result[1].allFinite());

    EXPECT_TRUE(result[2].allFinite());

}
