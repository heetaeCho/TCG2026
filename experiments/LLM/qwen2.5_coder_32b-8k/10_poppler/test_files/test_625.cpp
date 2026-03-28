#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_625 : public ::testing::Test {

protected:

    void SetUp() override {

        state = std::make_unique<GfxState>(72.0, 72.0, nullptr, 0, false);

    }



    std::unique_ptr<GfxState> state;

};



TEST_F(GfxStateTest_625, TransformIdentityMatrix_625) {

    double x1 = 1.0, y1 = 1.0;

    double x2, y2;



    state->transform(x1, y1, &x2, &y2);



    EXPECT_DOUBLE_EQ(x2, x1);

    EXPECT_DOUBLE_EQ(y2, y1);

}



TEST_F(GfxStateTest_625, TransformNonIdentityMatrix_625) {

    double a = 1.0, b = 2.0, c = 3.0, d = 4.0, e = 5.0, f = 6.0;

    state->setCTM(a, b, c, d, e, f);



    double x1 = 1.0, y1 = 1.0;

    double x2, y2;



    state->transform(x1, y1, &x2, &y2);



    EXPECT_DOUBLE_EQ(x2, a * x1 + c * y1 + e);

    EXPECT_DOUBLE_EQ(y2, b * x1 + d * y1 + f);

}



TEST_F(GfxStateTest_625, TransformBoundaryConditions_625) {

    double x1 = 0.0, y1 = 0.0;

    double x2, y2;



    state->transform(x1, y1, &x2, &y2);



    EXPECT_DOUBLE_EQ(x2, 0.0);

    EXPECT_DOUBLE_EQ(y2, 0.0);



    x1 = std::numeric_limits<double>::max();

    y1 = std::numeric_limits<double>::max();



    state->transform(x1, y1, &x2, &y2);



    // Assuming no overflow in the context of this test

    EXPECT_DOUBLE_EQ(x2, ctm[0] * x1 + ctm[2] * y1 + ctm[4]);

    EXPECT_DOUBLE_EQ(y2, ctm[1] * x1 + ctm[3] * y1 + ctm[5]);



    x1 = std::numeric_limits<double>::lowest();

    y1 = std::numeric_limits<double>::lowest();



    state->transform(x1, y1, &x2, &y2);



    // Assuming no underflow in the context of this test

    EXPECT_DOUBLE_EQ(x2, ctm[0] * x1 + ctm[2] * y1 + ctm[4]);

    EXPECT_DOUBLE_EQ(y2, ctm[1] * x1 + ctm[3] * y1 + ctm[5]);

}



TEST_F(GfxStateTest_625, TransformConcatenatedMatrix_625) {

    double a1 = 1.0, b1 = 2.0, c1 = 3.0, d1 = 4.0, e1 = 5.0, f1 = 6.0;

    double a2 = 7.0, b2 = 8.0, c2 = 9.0, d2 = 10.0, e2 = 11.0, f2 = 12.0;



    state->setCTM(a1, b1, c1, d1, e1, f1);

    state->concatCTM(a2, b2, c2, d2, e2, f2);



    double x1 = 1.0, y1 = 1.0;

    double x2, y2;



    state->transform(x1, y1, &x2, &y2);



    // Expected result after concatenation

    double expectedA = a1 * a2 + b1 * c2;

    double expectedB = a1 * b2 + b1 * d2;

    double expectedC = c1 * a2 + d1 * c2;

    double expectedD = c1 * b2 + d1 * d2;

    double expectedE = e1 * a2 + f1 * c2 + e2;

    double expectedF = e1 * b2 + f1 * d2 + f2;



    EXPECT_DOUBLE_EQ(x2, expectedA * x1 + expectedC * y1 + expectedE);

    EXPECT_DOUBLE_EQ(y2, expectedB * x1 + expectedD * y1 + expectedF);

}
