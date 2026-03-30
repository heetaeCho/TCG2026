#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_593 : public ::testing::Test {

protected:

    void SetUp() override {

        gfxState = std::make_unique<GfxState>(72, 72, nullptr, 0, false);

    }



    std::unique_ptr<GfxState> gfxState;

};



TEST_F(GfxStateTest_593, GetStrokeOverprint_DefaultValue_593) {

    EXPECT_FALSE(gfxState->getStrokeOverprint());

}



TEST_F(GfxStateTest_593, SetStrokeOverprint_True_593) {

    gfxState->setStrokeOverprint(true);

    EXPECT_TRUE(gfxState->getStrokeOverprint());

}



TEST_F(GfxStateTest_593, SetStrokeOverprint_False_593) {

    gfxState->setStrokeOverprint(false);

    EXPECT_FALSE(gfxState->getStrokeOverprint());

}
