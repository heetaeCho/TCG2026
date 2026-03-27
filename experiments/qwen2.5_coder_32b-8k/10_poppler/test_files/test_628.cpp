#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState state{72.0, 72.0, nullptr, 0, false}; // Assuming a default constructor for simplicity



    void SetUp() override {

        // Reset text matrix to identity matrix before each test

        state.setTextMat(1, 0, 0, 1, 0, 0);

    }

};



TEST_F(GfxStateTest_628, TextTransformDelta_IdentityMatrix_628) {

    double x1 = 1.0;

    double y1 = 1.0;

    double x2 = 0.0;

    double y2 = 0.0;



    state.textTransformDelta(x1, y1, &x2, &y2);



    EXPECT_EQ(x2, 1.0);

    EXPECT_EQ(y2, 1.0);

}



TEST_F(GfxStateTest_628, TextTransformDelta_ScaledMatrix_628) {

    state.setTextMat(2, 0, 0, 2, 0, 0);



    double x1 = 1.0;

    double y1 = 1.0;

    double x2 = 0.0;

    double y2 = 0.0;



    state.textTransformDelta(x1, y1, &x2, &y2);



    EXPECT_EQ(x2, 2.0);

    EXPECT_EQ(y2, 2.0);

}



TEST_F(GfxStateTest_628, TextTransformDelta_TranslatedMatrix_628) {

    state.setTextMat(1, 0, 0, 1, 5, 3);



    double x1 = 1.0;

    double y1 = 1.0;

    double x2 = 0.0;

    double y2 = 0.0;



    state.textTransformDelta(x1, y1, &x2, &y2);



    EXPECT_EQ(x2, 1.0);

    EXPECT_EQ(y2, 1.0);

}



TEST_F(GfxStateTest_628, TextTransformDelta_RotatedMatrix_628) {

    state.setTextMat(0, -1, 1, 0, 0, 0);



    double x1 = 1.0;

    double y1 = 1.0;

    double x2 = 0.0;

    double y2 = 0.0;



    state.textTransformDelta(x1, y1, &x2, &y2);



    EXPECT_EQ(x2, -1.0);

    EXPECT_EQ(y2, 1.0);

}



TEST_F(GfxStateTest_628, TextTransformDelta_ZeroInput_628) {

    double x1 = 0.0;

    double y1 = 0.0;

    double x2 = 0.0;

    double y2 = 0.0;



    state.textTransformDelta(x1, y1, &x2, &y2);



    EXPECT_EQ(x2, 0.0);

    EXPECT_EQ(y2, 0.0);

}



TEST_F(GfxStateTest_628, TextTransformDelta_NegativeInput_628) {

    state.setTextMat(1, 0, 0, 1, 0, 0);



    double x1 = -1.0;

    double y1 = -1.0;

    double x2 = 0.0;

    double y2 = 0.0;



    state.textTransformDelta(x1, y1, &x2, &y2);



    EXPECT_EQ(x2, -1.0);

    EXPECT_EQ(y2, -1.0);

}



TEST_F(GfxStateTest_628, TextTransformDelta_LargeValues_628) {

    state.setTextMat(1e6, 0, 0, 1e6, 0, 0);



    double x1 = 1.0;

    double y1 = 1.0;

    double x2 = 0.0;

    double y2 = 0.0;



    state.textTransformDelta(x1, y1, &x2, &y2);



    EXPECT_EQ(x2, 1e6);

    EXPECT_EQ(y2, 1e6);

}



TEST_F(GfxStateTest_628, TextTransformDelta_ShearedMatrix_628) {

    state.setTextMat(1, 0.5, 0.5, 1, 0, 0);



    double x1 = 1.0;

    double y1 = 1.0;

    double x2 = 0.0;

    double y2 = 0.0;



    state.textTransformDelta(x1, y1, &x2, &y2);



    EXPECT_EQ(x2, 1.5);

    EXPECT_EQ(y2, 1.5);

}



TEST_F(GfxStateTest_628, TextTransformDelta_UnchangedMatrixAfterCall_628) {

    std::array<double, 6> initialTextMat = state.getTextMat();

    double x1 = 1.0;

    double y1 = 1.0;

    double x2 = 0.0;

    double y2 = 0.0;



    state.textTransformDelta(x1, y1, &x2, &y2);



    EXPECT_EQ(state.getTextMat(), initialTextMat);

}
