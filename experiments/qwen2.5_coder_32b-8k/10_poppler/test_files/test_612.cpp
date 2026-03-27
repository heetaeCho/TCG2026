#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState *state;



    void SetUp() override {

        state = new GfxState(300, 300, nullptr, 0, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_612, GetRiseDefault_612) {

    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);

}



TEST_F(GfxStateTest_612, SetAndGetRisePositive_612) {

    state->setRise(5.0);

    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);

}



TEST_F(GfxStateTest_612, SetAndGetRiseNegative_612) {

    state->setRise(-3.5);

    EXPECT_DOUBLE_EQ(state->getRise(), -3.5);

}



TEST_F(GfxStateTest_612, SetAndGetRiseZero_612) {

    state->setRise(0.0);

    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);

}
