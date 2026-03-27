#include <gtest/gtest.h>

#include "GfxState.h"



// Test fixture for GfxState tests.

class GfxStateTest_606 : public ::testing::Test {

protected:

    GfxState* state;



    void SetUp() override {

        // Assuming a default constructor or mock PDFRectangle and other parameters are available

        state = new GfxState(300.0, 300.0, nullptr, 0, false);

    }



    void TearDown() override {

        delete state;

    }

};



// Test case to verify normal operation of getFontSize

TEST_F(GfxStateTest_606, GetFontSize_NormalOperation_606) {

    // Assuming a default font size is set during construction or can be set using public methods

    double fontSize = 12.0;

    state->setFont(nullptr, fontSize);

    EXPECT_DOUBLE_EQ(state->getFontSize(), fontSize);

}



// Test case to verify boundary condition of getFontSize with zero font size

TEST_F(GfxStateTest_606, GetFontSize_ZeroFontSize_606) {

    double fontSize = 0.0;

    state->setFont(nullptr, fontSize);

    EXPECT_DOUBLE_EQ(state->getFontSize(), fontSize);

}



// Test case to verify boundary condition of getFontSize with a very large font size

TEST_F(GfxStateTest_606, GetFontSize_LargeFontSize_606) {

    double fontSize = 1e9;

    state->setFont(nullptr, fontSize);

    EXPECT_DOUBLE_EQ(state->getFontSize(), fontSize);

}



// Test case to verify boundary condition of getFontSize with a very small font size

TEST_F(GfxStateTest_606, GetFontSize_SmallFontSize_606) {

    double fontSize = 1e-9;

    state->setFont(nullptr, fontSize);

    EXPECT_DOUBLE_EQ(state->getFontSize(), fontSize);

}



// Test case to verify that getFontSize returns the last set font size

TEST_F(GfxStateTest_606, GetFontSize_LastSetFontSize_606) {

    double firstFontSize = 12.0;

    double secondFontSize = 14.5;

    state->setFont(nullptr, firstFontSize);

    state->setFont(nullptr, secondFontSize);

    EXPECT_DOUBLE_EQ(state->getFontSize(), secondFontSize);

}
