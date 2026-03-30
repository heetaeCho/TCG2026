#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_629 : public ::testing::Test {

protected:

    GfxState state{72.0, 72.0, nullptr, 0, false};

};



TEST_F(GfxStateTest_629, GetTransformedLineWidth_DefaultLineWidth_629) {

    double lineWidth = state.getTransformedLineWidth();

    EXPECT_DOUBLE_EQ(lineWidth, state.transformWidth(state.getLineWidth()));

}



TEST_F(GfxStateTest_629, SetLineWidth_ChangeLineWidth_629) {

    state.setLineWidth(5.0);

    double lineWidth = state.getTransformedLineWidth();

    EXPECT_DOUBLE_EQ(lineWidth, state.transformWidth(5.0));

}



TEST_F(GfxStateTest_629, GetTransformedLineWidth_ZeroLineWidth_629) {

    state.setLineWidth(0.0);

    double lineWidth = state.getTransformedLineWidth();

    EXPECT_DOUBLE_EQ(lineWidth, 0.0);

}



TEST_F(GfxStateTest_629, SetLineWidth_NegativeLineWidth_629) {

    state.setLineWidth(-3.5);

    double lineWidth = state.getTransformedLineWidth();

    EXPECT_DOUBLE_EQ(lineWidth, state.transformWidth(-3.5));

}



TEST_F(GfxStateTest_629, TransformWidth_BoundaryConditionPositiveLargeValue_629) {

    double largeValue = 1e10;

    double transformed = state.transformWidth(largeValue);

    EXPECT_DOUBLE_EQ(transformed, state.transformWidth(largeValue));

}



TEST_F(GfxStateTest_629, TransformWidth_BoundaryConditionNegativeLargeValue_629) {

    double largeValue = -1e10;

    double transformed = state.transformWidth(largeValue);

    EXPECT_DOUBLE_EQ(transformed, state.transformWidth(largeValue));

}
