#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    double hDPI = 72.0;

    double vDPI = 72.0;

    PDFRectangle pageBox = {0, 0, 612, 792};

    int rotate = 0;



    GfxState* state;



    void SetUp() override {

        state = new GfxState(hDPI, vDPI, &pageBox, rotate, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_601, GetMiterLimit_DefaultValue_601) {

    EXPECT_EQ(state->getMiterLimit(), 10.0); // Assuming default miter limit is 10.0

}



TEST_F(GfxStateTest_601, SetMiterLimit_PositiveValue_601) {

    double newMiterLimit = 5.0;

    state->setMiterLimit(newMiterLimit);

    EXPECT_EQ(state->getMiterLimit(), newMiterLimit);

}



TEST_F(GfxStateTest_601, SetMiterLimit_ZeroValue_601) {

    double newMiterLimit = 0.0;

    state->setMiterLimit(newMiterLimit);

    EXPECT_EQ(state->getMiterLimit(), newMiterLimit);

}



TEST_F(GfxStateTest_601, GetHDPI_DefaultValue_601) {

    EXPECT_EQ(state->getHDPI(), hDPI);

}



TEST_F(GfxStateTest_601, GetVDPI_DefaultValue_601) {

    EXPECT_EQ(state->getVDPI(), vDPI);

}



TEST_F(GfxStateTest_601, SetLineWidth_PositiveValue_601) {

    double newLineWidth = 2.5;

    state->setLineWidth(newLineWidth);

    EXPECT_EQ(state->getLineWidth(), newLineWidth);

}



TEST_F(GfxStateTest_601, SetLineWidth_ZeroValue_601) {

    double newLineWidth = 0.0;

    state->setLineWidth(newLineWidth);

    EXPECT_EQ(state->getLineWidth(), newLineWidth);

}



TEST_F(GfxStateTest_601, SaveAndRestore_DefaultState_601) {

    GfxState* savedState = state->save();

    delete state; // Original state is deleted

    state = savedState->restore(); // Restoring the state



    EXPECT_EQ(state->getHDPI(), hDPI);

    EXPECT_EQ(state->getVDPI(), vDPI);

}



TEST_F(GfxStateTest_601, SetAndGetBlendMode_601) {

    GfxBlendMode newBlendMode = gfxBlendMultiply;

    state->setBlendMode(newBlendMode);

    EXPECT_EQ(state->getBlendMode(), newBlendMode);

}
