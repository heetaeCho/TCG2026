#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxStateTest_642 : public ::testing::Test {

protected:

    void SetUp() override {

        state = std::make_unique<GfxState>(300.0, 300.0, nullptr, 0, false);

    }



    void TearDown() override {

        state.reset();

    }



    std::unique_ptr<GfxState> state;

};



TEST_F(GfxStateTest_642, SetMiterLimit_NormalOperation_642) {

    double limit = 5.0;

    state->setMiterLimit(limit);

    EXPECT_DOUBLE_EQ(state->getMiterLimit(), limit);

}



TEST_F(GfxStateTest_642, SetMiterLimit_BoundaryCondition_Zero_642) {

    double limit = 0.0;

    state->setMiterLimit(limit);

    EXPECT_DOUBLE_EQ(state->getMiterLimit(), limit);

}



TEST_F(GfxStateTest_642, SetMiterLimit_BoundaryCondition_Negative_642) {

    double limit = -1.0;

    state->setMiterLimit(limit);

    EXPECT_DOUBLE_EQ(state->getMiterLimit(), limit); // Assuming the implementation allows negative values

}



TEST_F(GfxStateTest_642, SetMiterLimit_BoundaryCondition_LargeValue_642) {

    double limit = 1e10;

    state->setMiterLimit(limit);

    EXPECT_DOUBLE_EQ(state->getMiterLimit(), limit);

}
