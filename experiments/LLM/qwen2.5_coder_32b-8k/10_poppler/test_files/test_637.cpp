#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState* state;



    void SetUp() override {

        // Assuming a default constructor or mockable setup for GfxState is available.

        // Since the actual constructor requires specific parameters, we'll use a placeholder.

        double hDPI = 300.0;

        double vDPI = 300.0;

        PDFRectangle pageBox(0, 0, 612, 792);

        int rotateA = 0;

        bool upsideDown = false;

        state = new GfxState(hDPI, vDPI, &pageBox, rotateA, upsideDown);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_637, SetOverprintMode_SetsCorrectValue_637) {

    int op = 1;

    state->setOverprintMode(op);

    EXPECT_EQ(state->getOverprintMode(), op);

}



TEST_F(GfxStateTest_637, SetOverprintMode_BoundaryCondition_Zero_637) {

    int op = 0;

    state->setOverprintMode(op);

    EXPECT_EQ(state->getOverprintMode(), op);

}



TEST_F(GfxStateTest_637, SetOverprintMode_NegativeValue_Allowed_637) {

    int op = -1;

    state->setOverprintMode(op);

    EXPECT_EQ(state->getOverprintMode(), op);

}
