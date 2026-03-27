#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_603 : public ::testing::Test {

protected:

    GfxState state{150.0, 150.0, nullptr, 0, false};



    void SetUp() override {

        // Initialization code if needed

    }



    void TearDown() override {

        // Cleanup code if needed

    }

};



TEST_F(GfxStateTest_603, DefaultAlphaIsShapeFalse_603) {

    EXPECT_FALSE(state.getAlphaIsShape());

}



TEST_F(GfxStateTest_603, SetAlphaIsShapeTrueAndGetTrue_603) {

    state.setAlphaIsShape(true);

    EXPECT_TRUE(state.getAlphaIsShape());

}



TEST_F(GfxStateTest_603, SetAlphaIsShapeFalseAndGetFalse_603) {

    state.setAlphaIsShape(false);

    EXPECT_FALSE(state.getAlphaIsShape());

}
