#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState state{72.0, 72.0, nullptr, 0, false};



    void SetUp() override {

        state.setHorizScaling(1.0); // Default value

    }

};



TEST_F(GfxStateTest_610, GetHorizScaling_DefaultValue_610) {

    EXPECT_DOUBLE_EQ(state.getHorizScaling(), 1.0);

}



TEST_F(GfxStateTest_610, SetAndGetHorizScaling_NormalOperation_610) {

    state.setHorizScaling(2.5);

    EXPECT_DOUBLE_EQ(state.getHorizScaling(), 2.5);

}



TEST_F(GfxStateTest_610, SetAndGetHorizScaling_BoundaryCondition_Zero_610) {

    state.setHorizScaling(0.0);

    EXPECT_DOUBLE_EQ(state.getHorizScaling(), 0.0);

}



TEST_F(GfxStateTest_610, SetAndGetHorizScaling_BoundaryCondition_MaximumDouble_610) {

    state.setHorizScaling(std::numeric_limits<double>::max());

    EXPECT_DOUBLE_EQ(state.getHorizScaling(), std::numeric_limits<double>::max());

}



TEST_F(GfxStateTest_610, SetAndGetHorizScaling_BoundaryCondition_MinimumDouble_610) {

    state.setHorizScaling(std::numeric_limits<double>::lowest());

    EXPECT_DOUBLE_EQ(state.getHorizScaling(), std::numeric_limits<double>::lowest());

}
