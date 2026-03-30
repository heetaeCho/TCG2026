#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_632 : public ::testing::Test {

protected:

    GfxState *gfxState;



    void SetUp() override {

        gfxState = new GfxState(72.0, 72.0, nullptr, 0, false);

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_632, SetBlendMode_NormalOperation_632) {

    gfxState->setBlendMode(gfxBlendNormal);

    EXPECT_EQ(gfxState->getBlendMode(), gfxBlendNormal);

}



TEST_F(GfxStateTest_632, SetBlendMode_BoundaryConditions_632) {

    gfxState->setBlendMode(static_cast<GfxBlendMode>(-1));

    EXPECT_EQ(gfxState->getBlendMode(), static_cast<GfxBlendMode>(-1));



    gfxState->setBlendMode(static_cast<GfxBlendMode>(50)); // Assuming 50 is out of the valid range

    EXPECT_EQ(gfxState->getBlendMode(), static_cast<GfxBlendMode>(50));

}



TEST_F(GfxStateTest_632, SetBlendMode_ExceptionalCases_632) {

    // No exceptional cases are observable through the interface for setBlendMode

}



// Assuming there are no external interactions to verify for setBlendMode


