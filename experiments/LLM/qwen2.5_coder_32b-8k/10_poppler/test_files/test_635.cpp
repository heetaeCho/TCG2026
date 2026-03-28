#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState state{72.0, 72.0, nullptr, 0, false}; // Initialize with some dummy values



    void SetUp() override {

        // Reset the state before each test

        state.setFillOverprint(false);

    }

};



TEST_F(GfxStateTest_635, SetFillOverprintTrue_635) {

    state.setFillOverprint(true);

    EXPECT_TRUE(state.getFillOverprint());

}



TEST_F(GfxStateTest_635, SetFillOverprintFalse_635) {

    state.setFillOverprint(false);

    EXPECT_FALSE(state.getFillOverprint());

}



TEST_F(GfxStateTest_635, BoundaryConditionSetFillOverprintTrueTwice_635) {

    state.setFillOverprint(true);

    state.setFillOverprint(true);

    EXPECT_TRUE(state.getFillOverprint());

}



TEST_F(GfxStateTest_635, BoundaryConditionSetFillOverprintFalseTwice_635) {

    state.setFillOverprint(false);

    state.setFillOverprint(false);

    EXPECT_FALSE(state.getFillOverprint());

}



TEST_F(GfxStateTest_635, ToggleFillOverprint_635) {

    state.setFillOverprint(true);

    EXPECT_TRUE(state.getFillOverprint());



    state.setFillOverprint(false);

    EXPECT_FALSE(state.getFillOverprint());

}
