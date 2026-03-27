#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_641 : public ::testing::Test {

protected:

    GfxState* state;



    void SetUp() override {

        // Assuming a default constructor or mock setup is available

        state = new GfxState(72.0, 72.0, nullptr, 0, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_641, SetLineCap_NormalOperation_641) {

    LineCapStyle expectedCap = LineCapStyle::ButtCap;

    state->setLineCap(expectedCap);

    EXPECT_EQ(state->getLineCap(), expectedCap);

}



TEST_F(GfxStateTest_641, SetLineCap_BoundaryCondition_RoundCap_641) {

    LineCapStyle expectedCap = LineCapStyle::RoundCap;

    state->setLineCap(expectedCap);

    EXPECT_EQ(state->getLineCap(), expectedCap);

}



TEST_F(GfxStateTest_641, SetLineCap_BoundaryCondition_SquareCap_641) {

    LineCapStyle expectedCap = LineCapStyle::SquareCap;

    state->setLineCap(expectedCap);

    EXPECT_EQ(state->getLineCap(), expectedCap);

}
