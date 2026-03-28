#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState state{72.0, 72.0, nullptr, 0, false}; // Example initialization



    void SetUp() override {

        state.setLineWidth(1.0); // Default line width

    }

};



TEST_F(GfxStateTest_596, GetLineWidth_DefaultValue_596) {

    EXPECT_DOUBLE_EQ(state.getLineWidth(), 1.0);

}



TEST_F(GfxStateTest_596, SetLineWidth_ChangesLineWidth_596) {

    state.setLineWidth(2.5);

    EXPECT_DOUBLE_EQ(state.getLineWidth(), 2.5);

}



TEST_F(GfxStateTest_596, GetLineWidth_BoundaryCondition_Zero_596) {

    state.setLineWidth(0.0);

    EXPECT_DOUBLE_EQ(state.getLineWidth(), 0.0);

}



TEST_F(GfxStateTest_596, SetLineWidth_NegativeValue_ShouldNotChange_596) {

    double originalWidth = state.getLineWidth();

    state.setLineWidth(-1.0);

    EXPECT_DOUBLE_EQ(state.getLineWidth(), originalWidth);

}



TEST_F(GfxStateTest_596, SetLineWidth_VeryLargeValue_ShouldSetCorrectly_596) {

    double largeValue = 1e308; // Very large value

    state.setLineWidth(largeValue);

    EXPECT_DOUBLE_EQ(state.getLineWidth(), largeValue);

}
