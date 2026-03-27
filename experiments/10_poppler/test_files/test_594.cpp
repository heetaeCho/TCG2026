#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState state{72.0, 72.0, nullptr, 0, false};

};



TEST_F(GfxStateTest_594, GetOverprintMode_DefaultValue_594) {

    EXPECT_EQ(state.getOverprintMode(), 0);

}



TEST_F(GfxStateTest_594, SetAndGetOverprintMode_ValidValue_594) {

    state.setOverprintMode(1);

    EXPECT_EQ(state.getOverprintMode(), 1);

}



TEST_F(GfxStateTest_594, GetOverprintMode_AfterReset_594) {

    state.setOverprintMode(2);

    state.setOverprintMode(0);

    EXPECT_EQ(state.getOverprintMode(), 0);

}
