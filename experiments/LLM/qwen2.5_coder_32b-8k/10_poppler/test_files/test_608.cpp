#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_608 : public ::testing::Test {

protected:

    double hDPI = 300.0;

    double vDPI = 300.0;

    PDFRectangle pageBox = {0, 0, 595, 842}; // A4 size in points

    int rotate = 0;



    GfxState* state;



    void SetUp() override {

        state = new GfxState(hDPI, vDPI, &pageBox, rotate, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_608, GetCharSpace_DefaultValue_608) {

    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);

}



TEST_F(GfxStateTest_608, SetAndGetCharSpace_608) {

    double newCharSpace = 2.0;

    state->setCharSpace(newCharSpace);

    EXPECT_DOUBLE_EQ(state->getCharSpace(), newCharSpace);

}



TEST_F(GfxStateTest_608, SetAndGetCharSpace_ZeroValue_608) {

    double newCharSpace = 0.0;

    state->setCharSpace(newCharSpace);

    EXPECT_DOUBLE_EQ(state->getCharSpace(), newCharSpace);

}



TEST_F(GfxStateTest_608, SetAndGetCharSpace_NegativeValue_608) {

    double newCharSpace = -1.5;

    state->setCharSpace(newCharSpace);

    EXPECT_DOUBLE_EQ(state->getCharSpace(), newCharSpace);

}
