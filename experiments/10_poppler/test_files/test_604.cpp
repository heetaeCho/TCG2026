#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxStateTest_604 : public ::testing::Test {

protected:

    double hDPI = 300.0;

    double vDPI = 300.0;

    PDFRectangle pageBox{0, 0, 595, 842};

    int rotate = 0;



    GfxState state{hDPI, vDPI, &pageBox, rotate, false};



    void SetUp() override {

        // Set up any common preconditions here if needed

    }

};



TEST_F(GfxStateTest_604, GetTextKnockout_DefaultValue_604) {

    EXPECT_FALSE(state.getTextKnockout());

}



TEST_F(GfxStateTest_604, GetTextKnockout_SetTrue_ReturnsTrue_604) {

    state.setTextKnockout(true);

    EXPECT_TRUE(state.getTextKnockout());

}



TEST_F(GfxStateTest_604, GetTextKnockout_SetFalse_ReturnsFalse_604) {

    state.setTextKnockout(false);

    EXPECT_FALSE(state.getTextKnockout());

}
