#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState* state;



    void SetUp() override {

        // Assuming a constructor with dummy values for demonstration purposes.

        // Actual constructor parameters should be based on real usage.

        state = new GfxState(72.0, 72.0, nullptr, 0, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_652, SetRenderAndGetRender_NormalOperation_652) {

    int renderValue = 1;

    state->setRender(renderValue);

    EXPECT_EQ(state->getRender(), renderValue);

}



TEST_F(GfxStateTest_652, SetRender_BoundaryCondition_MaxInt_652) {

    int renderValue = INT_MAX;

    state->setRender(renderValue);

    EXPECT_EQ(state->getRender(), renderValue);

}



TEST_F(GfxStateTest_652, SetRender_BoundaryCondition_MinInt_652) {

    int renderValue = INT_MIN;

    state->setRender(renderValue);

    EXPECT_EQ(state->getRender(), renderValue);

}



TEST_F(GfxStateTest_652, SetRenderAndGetRender_MultipleSets_652) {

    int firstRenderValue = 10;

    int secondRenderValue = 20;

    

    state->setRender(firstRenderValue);

    EXPECT_EQ(state->getRender(), firstRenderValue);



    state->setRender(secondRenderValue);

    EXPECT_EQ(state->getRender(), secondRenderValue);

}
