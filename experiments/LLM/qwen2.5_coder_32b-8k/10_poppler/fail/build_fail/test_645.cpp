#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState* state;



    void SetUp() override {

        // Assuming a constructor with default parameters exists for testing purposes.

        state = new GfxState(300.0, 300.0, nullptr, 0, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_645, SetTextKnockoutNormalOperation_645) {

    state->setTextKnockout(true);

    EXPECT_TRUE(state->getTextKnockout());



    state->setTextKnockout(false);

    EXPECT_FALSE(state->getTextKnockout());

}



TEST_F(GfxStateTest_645, BoundaryConditionSetTextKnockoutTrue_645) {

    state->setTextKnockout(true);

    EXPECT_EQ(state->getTextKnockout(), true);

}



TEST_F(GfxStateTest_645, BoundaryConditionSetTextKnockoutFalse_645) {

    state->setTextKnockout(false);

    EXPECT_EQ(state->getTextKnockout(), false);

}
