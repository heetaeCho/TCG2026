#include <gtest/gtest.h>

#include <Eigen/Dense>

#include "cost_function.h"



using namespace glomap;

using Eigen::Vector3d;

using Eigen::Vector4d;



class CostFunctionTest_15 : public ::testing::Test {

protected:

    Vector3d ai, bi, aj, bj;

    

    void SetUp() override {

        ai << 1.0, 2.0, 3.0;

        bi << 4.0, 5.0, 6.0;

        aj << 7.0, 8.0, 9.0;

        bj << 10.0, 11.0, 12.0;

    }

};



TEST_F(CostFunctionTest_15, NormalOperation_15) {

    int u = 0, v = 1;

    Vector4d expected;

    expected(0) = ai(u) * aj(v) - ai(v) * aj(u);

    expected(1) = ai(u) * bj(v) - ai(v) * bj(u);

    expected(2) = bi(u) * aj(v) - bi(v) * aj(u);

    expected(3) = bi(u) * bj(v) - bi(v) * bj(u);



    Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);

    EXPECT_EQ(result, expected);

}



TEST_F(CostFunctionTest_15, BoundaryConditions_U0V2_15) {

    int u = 0, v = 2;

    Vector4d expected;

    expected(0) = ai(u) * aj(v) - ai(v) * aj(u);

    expected(1) = ai(u) * bj(v) - ai(v) * bj(u);

    expected(2) = bi(u) * aj(v) - bi(v) * aj(u);

    expected(3) = bi(u) * bj(v) - bi(v) * bj(u);



    Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);

    EXPECT_EQ(result, expected);

}



TEST_F(CostFunctionTest_15, BoundaryConditions_U2V0_15) {

    int u = 2, v = 0;

    Vector4d expected;

    expected(0) = ai(u) * aj(v) - ai(v) * aj(u);

    expected(1) = ai(u) * bj(v) - ai(v) * bj(u);

    expected(2) = bi(u) * aj(v) - bi(v) * aj(u);

    expected(3) = bi(u) * bj(v) - bi(v) * bj(u);



    Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);

    EXPECT_EQ(result, expected);

}



TEST_F(CostFunctionTest_15, BoundaryConditions_U2V2_15) {

    int u = 2, v = 2;

    Vector4d expected;

    expected(0) = ai(u) * aj(v) - ai(v) * aj(u);

    expected(1) = ai(u) * bj(v) - ai(v) * bj(u);

    expected(2) = bi(u) * aj(v) - bi(v) * aj(u);

    expected(3) = bi(u) * bj(v) - bi(v) * bj(u);



    Vector4d result = fetzer_d(ai, bi, aj, bj, u, v);

    EXPECT_EQ(result, expected);

}



TEST_F(CostFunctionTest_15, ExceptionalCase_OutOfBounds_15) {

    int u = 3, v = 0; // Out of bounds for ai and bi

    EXPECT_THROW(fetzer_d(ai, bi, aj, bj, u, v), std::exception);

}



TEST_F(CostFunctionTest_15, ExceptionalCase_OutOfBounds2_15) {

    int u = 0, v = 3; // Out of bounds for aj and bj

    EXPECT_THROW(fetzer_d(ai, bi, aj, bj, u, v), std::exception);

}

```


