#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState* state;



    void SetUp() override {

        // Assuming a default constructor or mock-up for setup purposes

        state = new GfxState(72.0, 72.0, nullptr, 0, false);

        // Set a known CTM for testing transformDelta

        state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0); // Identity matrix

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_626, TransformDeltaIdentityMatrix_626) {

    double x1 = 5.0, y1 = 3.0;

    double x2 = 0.0, y2 = 0.0;

    state->transformDelta(x1, y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x2, 5.0);

    EXPECT_DOUBLE_EQ(y2, 3.0);

}



TEST_F(GfxStateTest_626, TransformDeltaNonIdentityMatrix_626) {

    state->setCTM(2.0, 1.0, 1.0, 2.0, 0.0, 0.0); // Non-identity matrix

    double x1 = 5.0, y1 = 3.0;

    double x2 = 0.0, y2 = 0.0;

    state->transformDelta(x1, y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x2, 13.0); // 2*5 + 1*3

    EXPECT_DOUBLE_EQ(y2, 11.0); // 1*5 + 2*3

}



TEST_F(GfxStateTest_626, TransformDeltaBoundaryConditions_626) {

    state->setCTM(0.0, 0.0, 0.0, 0.0, 0.0, 0.0); // Zero matrix

    double x1 = std::numeric_limits<double>::max(), y1 = std::numeric_limits<double>::max();

    double x2 = 0.0, y2 = 0.0;

    state->transformDelta(x1, y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x2, 0.0); // Any number * 0 should be 0

    EXPECT_DOUBLE_EQ(y2, 0.0);



    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0); // Identity matrix again

    x1 = std::numeric_limits<double>::lowest(), y1 = std::numeric_limits<double>::lowest();

    state->transformDelta(x1, y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x2, std::numeric_limits<double>::lowest());

    EXPECT_DOUBLE_EQ(y2, std::numeric_limits<double>::lowest());

}



TEST_F(GfxStateTest_626, TransformDeltaNegativeValues_626) {

    state->setCTM(-1.0, 0.0, 0.0, -1.0, 0.0, 0.0); // Reflection matrix

    double x1 = -5.0, y1 = -3.0;

    double x2 = 0.0, y2 = 0.0;

    state->transformDelta(x1, y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x2, 5.0); // -1 * -5 + 0 * -3

    EXPECT_DOUBLE_EQ(y2, 3.0); // 0 * -5 + -1 * -3

}
