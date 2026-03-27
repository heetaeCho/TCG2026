#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "cost_function.h"

#include <Eigen/Dense>



using namespace glomap;

using namespace Eigen;



TEST_F(FetzerDTest_91, NormalOperation_91) {

    Vector3d ai(1.0, 2.0, 3.0);

    Vector3d bi(4.0, 5.0, 6.0);

    Vector3d aj(7.0, 8.0, 9.0);

    Vector3d bj(10.0, 11.0, 12.0);

    int u = 0;

    int v = 1;



    Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);



    EXPECT_DOUBLE_EQ(result(0), -3.0);  // ai(u) * aj(v) - ai(v) * aj(u)

    EXPECT_DOUBLE_EQ(result(1), -3.0);  // ai(u) * bj(v) - ai(v) * bj(u)

    EXPECT_DOUBLE_EQ(result(2), -6.0);  // bi(u) * aj(v) - bi(v) * aj(u)

    EXPECT_DOUBLE_EQ(result(3), -6.0);  // bi(u) * bj(v) - bi(v) * bj(u)

}



TEST_F(FetzerDTest_91, BoundaryConditions_UZeroVTwo_91) {

    Vector3d ai(1.0, 2.0, 3.0);

    Vector3d bi(4.0, 5.0, 6.0);

    Vector3d aj(7.0, 8.0, 9.0);

    Vector3d bj(10.0, 11.0, 12.0);

    int u = 0;

    int v = 2;



    Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);



    EXPECT_DOUBLE_EQ(result(0), -6.0);  // ai(u) * aj(v) - ai(v) * aj(u)

    EXPECT_DOUBLE_EQ(result(1), -6.0);  // ai(u) * bj(v) - ai(v) * bj(u)

    EXPECT_DOUBLE_EQ(result(2), -12.0); // bi(u) * aj(v) - bi(v) * aj(u)

    EXPECT_DOUBLE_EQ(result(3), -12.0); // bi(u) * bj(v) - bi(v) * bj(u)

}



TEST_F(FetzerDTest_91, BoundaryConditions_UOneVTwo_91) {

    Vector3d ai(1.0, 2.0, 3.0);

    Vector3d bi(4.0, 5.0, 6.0);

    Vector3d aj(7.0, 8.0, 9.0);

    Vector3d bj(10.0, 11.0, 12.0);

    int u = 1;

    int v = 2;



    Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);



    EXPECT_DOUBLE_EQ(result(0), -6.0);  // ai(u) * aj(v) - ai(v) * aj(u)

    EXPECT_DOUBLE_EQ(result(1), -9.0);  // ai(u) * bj(v) - ai(v) * bj(u)

    EXPECT_DOUBLE_EQ(result(2), -12.0); // bi(u) * aj(v) - bi(v) * aj(u)

    EXPECT_DOUBLE_EQ(result(3), -15.0); // bi(u) * bj(v) - bi(v) * bj(u)

}



TEST_F(FetzerDTest_91, ZeroVectors_91) {

    Vector3d ai(0.0, 0.0, 0.0);

    Vector3d bi(0.0, 0.0, 0.0);

    Vector3d aj(0.0, 0.0, 0.0);

    Vector3d bj(0.0, 0.0, 0.0);

    int u = 1;

    int v = 2;



    Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);



    EXPECT_DOUBLE_EQ(result(0), 0.0);

    EXPECT_DOUBLE_EQ(result(1), 0.0);

    EXPECT_DOUBLE_EQ(result(2), 0.0);

    EXPECT_DOUBLE_EQ(result(3), 0.0);

}



TEST_F(FetzerDTest_91, EqualVectors_91) {

    Vector3d ai(1.0, 2.0, 3.0);

    Vector3d bi(4.0, 5.0, 6.0);

    int u = 0;

    int v = 1;



    Vector4d result = fetzer_d(ai, bi, ai, bi, u, v);



    EXPECT_DOUBLE_EQ(result(0), 0.0); // ai(u) * ai(v) - ai(v) * ai(u)

    EXPECT_DOUBLE_EQ(result(1), 0.0); // ai(u) * bi(v) - ai(v) * bi(u)

    EXPECT_DOUBLE_EQ(result(2), 0.0); // bi(u) * ai(v) - bi(v) * ai(u)

    EXPECT_DOUBLE_EQ(result(3), 0.0); // bi(u) * bi(v) - bi(v) * bi(u)

}



TEST_F(FetzerDTest_91, NegativeValues_91) {

    Vector3d ai(-1.0, -2.0, -3.0);

    Vector3d bi(-4.0, -5.0, -6.0);

    Vector3d aj(-7.0, -8.0, -9.0);

    Vector3d bj(-10.0, -11.0, -12.0);

    int u = 0;

    int v = 1;



    Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);



    EXPECT_DOUBLE_EQ(result(0), 3.0);   // ai(u) * aj(v) - ai(v) * aj(u)

    EXPECT_DOUBLE_EQ(result(1), 3.0);   // ai(u) * bj(v) - ai(v) * bj(u)

    EXPECT_DOUBLE_EQ(result(2), 6.0);   // bi(u) * aj(v) - bi(v) * aj(u)

    EXPECT_DOUBLE_EQ(result(3), 6.0);   // bi(u) * bj(v) - bi(v) * bj(u)

}



TEST_F(FetzerDTest_91, MixedSigns_91) {

    Vector3d ai(-1.0, 2.0, -3.0);

    Vector3d bi(4.0, -5.0, 6.0);

    Vector3d aj(-7.0, 8.0, -9.0);

    Vector3d bj(10.0, -11.0, 12.0);

    int u = 0;

    int v = 1;



    Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);



    EXPECT_DOUBLE_EQ(result(0), 3.0);   // ai(u) * aj(v) - ai(v) * aj(u)

    EXPECT_DOUBLE_EQ(result(1), -27.0); // ai(u) * bj(v) - ai(v) * bj(u)

    EXPECT_DOUBLE_EQ(result(2), 6.0);   // bi(u) * aj(v) - bi(v) * aj(u)

    EXPECT_DOUBLE_EQ(result(3), -45.0); // bi(u) * bj(v) - bi(v) * bj(u)

}
