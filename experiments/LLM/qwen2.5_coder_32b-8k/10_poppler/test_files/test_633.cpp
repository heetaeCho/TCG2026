#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_633 : public ::testing::Test {

protected:

    GfxState* state;



    void SetUp() override {

        // Assuming a default constructor or a mock setup is possible

        // Here we use placeholders for parameters as the actual constructor requires specific arguments.

        double hDPI = 72.0;

        double vDPI = 72.0;

        PDFRectangle pageBox = {0, 0, 612, 792}; // A4 size in points

        int rotate = 0;

        bool upsideDown = false;

        state = new GfxState(hDPI, vDPI, &pageBox, rotate, upsideDown);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_633, SetFillOpacity_ValidValue_633) {

    double opacity = 0.5;

    state->setFillOpacity(opacity);

    EXPECT_DOUBLE_EQ(state->getFillOpacity(), opacity);

}



TEST_F(GfxStateTest_633, SetFillOpacity_BoundaryMin_633) {

    double opacity = 0.0;

    state->setFillOpacity(opacity);

    EXPECT_DOUBLE_EQ(state->getFillOpacity(), opacity);

}



TEST_F(GfxStateTest_633, SetFillOpacity_BoundaryMax_633) {

    double opacity = 1.0;

    state->setFillOpacity(opacity);

    EXPECT_DOUBLE_EQ(state->getFillOpacity(), opacity);

}



TEST_F(GfxStateTest_633, SetFillOpacity_OutOfRangeBelow_633) {

    double opacity = -0.1;

    state->setFillOpacity(opacity);

    // Assuming the implementation clamps values to [0, 1]

    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);

}



TEST_F(GfxStateTest_633, SetFillOpacity_OutOfRangeAbove_633) {

    double opacity = 1.1;

    state->setFillOpacity(opacity);

    // Assuming the implementation clamps values to [0, 1]

    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);

}
