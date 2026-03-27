#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState state{72.0, 72.0, nullptr, 0, false};



    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(GfxStateTest_644, SetAlphaIsShape_DefaultValue_644) {

    EXPECT_EQ(state.getAlphaIsShape(), false);

}



TEST_F(GfxStateTest_644, SetAlphaIsShape_True_644) {

    state.setAlphaIsShape(true);

    EXPECT_EQ(state.getAlphaIsShape(), true);

}



TEST_F(GfxStateTest_644, SetAlphaIsShape_False_644) {

    state.setAlphaIsShape(false);

    EXPECT_EQ(state.getAlphaIsShape(), false);

}



TEST_F(GfxStateTest_644, SetAlphaIsShape_MultipleCalls_644) {

    state.setAlphaIsShape(true);

    EXPECT_EQ(state.getAlphaIsShape(), true);



    state.setAlphaIsShape(false);

    EXPECT_EQ(state.getAlphaIsShape(), false);

}
