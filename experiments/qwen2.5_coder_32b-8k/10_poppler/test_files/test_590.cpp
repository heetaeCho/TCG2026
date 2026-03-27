#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    double hDPI = 300.0;

    double vDPI = 300.0;

    PDFRectangle pageBox{0, 0, 612, 792};

    int rotate = 0;



    GfxState* state;



    void SetUp() override {

        state = new GfxState(hDPI, vDPI, &pageBox, rotate, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_590, GetFillOpacity_DefaultValue_590) {

    EXPECT_EQ(state->getFillOpacity(), 1.0); // Default fill opacity is typically 1.0

}



TEST_F(GfxStateTest_590, SetAndGetFillOpacity_NormalOperation_590) {

    double testOpacity = 0.5;

    state->setFillOpacity(testOpacity);

    EXPECT_EQ(state->getFillOpacity(), testOpacity);

}



TEST_F(GfxStateTest_590, SetAndGetFillOpacity_BoundaryConditions_590) {

    state->setFillOpacity(0.0);

    EXPECT_EQ(state->getFillOpacity(), 0.0);



    state->setFillOpacity(1.0);

    EXPECT_EQ(state->getFillOpacity(), 1.0);

}



TEST_F(GfxStateTest_590, SetAndGetFillOpacity_OutOfBoundsValues_590) {

    state->setFillOpacity(-0.1); // Out of bounds

    EXPECT_GE(state->getFillOpacity(), 0.0);



    state->setFillOpacity(1.1); // Out of bounds

    EXPECT_LE(state->getFillOpacity(), 1.0);

}
