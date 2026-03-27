#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState state{150.0, 150.0, nullptr, 0, false};



    void SetUp() override {

        // Initialization if needed

    }



    void TearDown() override {

        // Cleanup if needed

    }

};



TEST_F(GfxStateTest_616, GetCurX_ReturnsInitialValue_616) {

    EXPECT_EQ(state.getCurX(), 0.0);

}



TEST_F(GfxStateTest_616, SetCTM_AffectsGetCurX_616) {

    state.setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    EXPECT_EQ(state.getCurX(), 5.0);

}



TEST_F(GfxStateTest_616, ConcatCTM_AffectsGetCurX_616) {

    state.setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    state.concatCTM(0.5, 1.0, 1.5, 2.0, 2.5, 3.0);

    EXPECT_EQ(state.getCurX(), 15.0);

}



TEST_F(GfxStateTest_616, ShiftCTMAndClip_AffectsGetCurX_616) {

    state.setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);

    state.shiftCTMAndClip(10.0, 20.0);

    EXPECT_EQ(state.getCurX(), 10.0);

}



TEST_F(GfxStateTest_616, MoveTo_AffectsGetCurX_616) {

    state.moveTo(10.0, 20.0);

    EXPECT_EQ(state.getCurX(), 10.0);

}



TEST_F(GfxStateTest_616, LineTo_AffectsGetCurX_616) {

    state.moveTo(10.0, 20.0);

    state.lineTo(30.0, 40.0);

    EXPECT_EQ(state.getCurX(), 30.0);

}



TEST_F(GfxStateTest_616, CurveTo_AffectsGetCurX_616) {

    state.moveTo(10.0, 20.0);

    state.curveTo(15.0, 25.0, 20.0, 30.0, 25.0, 35.0);

    EXPECT_EQ(state.getCurX(), 25.0);

}



TEST_F(GfxStateTest_616, ClosePath_DoesNotAffectGetCurX_616) {

    state.moveTo(10.0, 20.0);

    state.lineTo(30.0, 40.0);

    double initialX = state.getCurX();

    state.closePath();

    EXPECT_EQ(state.getCurX(), initialX);

}
