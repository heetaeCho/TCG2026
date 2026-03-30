#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_634 : public ::testing::Test {

protected:

    GfxState state{72.0, 72.0, nullptr, 0, false};

};



TEST_F(GfxStateTest_634, SetStrokeOpacity_NormalOperation_634) {

    double opacity = 0.5;

    state.setStrokeOpacity(opacity);

    EXPECT_DOUBLE_EQ(state.getStrokeOpacity(), opacity);

}



TEST_F(GfxStateTest_634, SetStrokeOpacity_BoundaryCondition_LowerLimit_634) {

    double opacity = 0.0;

    state.setStrokeOpacity(opacity);

    EXPECT_DOUBLE_EQ(state.getStrokeOpacity(), opacity);

}



TEST_F(GfxStateTest_634, SetStrokeOpacity_BoundaryCondition_UpperLimit_634) {

    double opacity = 1.0;

    state.setStrokeOpacity(opacity);

    EXPECT_DOUBLE_EQ(state.getStrokeOpacity(), opacity);

}



TEST_F(GfxStateTest_634, SetStrokeOpacity_OutOfBounds_Lower_634) {

    double opacity = -0.1;

    state.setStrokeOpacity(opacity);

    // Assuming the implementation clamps values between 0 and 1

    EXPECT_DOUBLE_EQ(state.getStrokeOpacity(), 0.0);

}



TEST_F(GfxStateTest_634, SetStrokeOpacity_OutOfBounds_Upper_634) {

    double opacity = 1.1;

    state.setStrokeOpacity(opacity);

    // Assuming the implementation clamps values between 0 and 1

    EXPECT_DOUBLE_EQ(state.getStrokeOpacity(), 1.0);

}
