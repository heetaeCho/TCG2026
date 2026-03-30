#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState state{72.0, 72.0, nullptr, 0, false};

};



TEST_F(GfxStateTest_638, SetLineWidth_PositiveWidth_638) {

    double width = 5.0;

    state.setLineWidth(width);

    EXPECT_DOUBLE_EQ(state.getLineWidth(), width);

}



TEST_F(GfxStateTest_638, SetLineWidth_ZeroWidth_638) {

    double width = 0.0;

    state.setLineWidth(width);

    EXPECT_DOUBLE_EQ(state.getLineWidth(), width);

}



TEST_F(GfxStateTest_638, SetLineWidth_NegativeWidth_638) {

    double width = -5.0;

    state.setLineWidth(width);

    EXPECT_DOUBLE_EQ(state.getLineWidth(), width);

}
