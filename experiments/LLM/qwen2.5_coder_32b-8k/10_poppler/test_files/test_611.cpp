#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_611 : public ::testing::Test {

protected:

    GfxState* state;



    void SetUp() override {

        // Assuming a default constructor or mock setup for GfxState is available

        // Here we use a dummy pageBox and other parameters as they are required by the constructor.

        PDFRectangle pageBox = {0, 0, 612, 792};

        state = new GfxState(300, 300, &pageBox, 0, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_611, GetLeading_DefaultValue_611) {

    // Assuming the default value of leading is 0.0 if not set otherwise

    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);

}



TEST_F(GfxStateTest_611, SetAndGetLeading_PositiveValue_611) {

    state->setLeading(24.0);

    EXPECT_DOUBLE_EQ(state->getLeading(), 24.0);

}



TEST_F(GfxStateTest_611, SetAndGetLeading_NegativeValue_611) {

    state->setLeading(-12.0);

    EXPECT_DOUBLE_EQ(state->getLeading(), -12.0);

}



TEST_F(GfxStateTest_611, SetAndGetLeading_ZeroValue_611) {

    state->setLeading(0.0);

    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);

}
