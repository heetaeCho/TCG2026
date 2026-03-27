#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_636 : public ::testing::Test {

protected:

    GfxState *gfxState;



    void SetUp() override {

        gfxState = new GfxState(72.0, 72.0, nullptr, 0, false);

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_636, SetStrokeOverprint_NormalOperation_636) {

    gfxState->setStrokeOverprint(true);

    EXPECT_TRUE(gfxState->getStrokeOverprint());



    gfxState->setStrokeOverprint(false);

    EXPECT_FALSE(gfxState->getStrokeOverprint());

}



TEST_F(GfxStateTest_636, SetStrokeOverprint_BoundaryConditions_636) {

    // Boundary condition: setting true and false multiple times

    gfxState->setStrokeOverprint(true);

    gfxState->setStrokeOverprint(true);

    EXPECT_TRUE(gfxState->getStrokeOverprint());



    gfxState->setStrokeOverprint(false);

    gfxState->setStrokeOverprint(false);

    EXPECT_FALSE(gfxState->getStrokeOverprint());

}



TEST_F(GfxStateTest_636, SetStrokeOverprint_ExceptionalCases_636) {

    // No exceptional cases expected as the method only sets a boolean value

    // This is more of a placeholder in case there are future changes to the method

}
