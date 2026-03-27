#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_623 : public ::testing::Test {

protected:

    std::unique_ptr<GfxPath> path;

    std::unique_ptr<GfxState> gfxState;



    void SetUp() override {

        path = std::make_unique<GfxPath>();

        gfxState = std::make_unique<GfxState>(150.0, 150.0, nullptr, 0, false);

        gfxState->clearPath(); // Ensure the path is initially empty

    }

};



TEST_F(GfxStateTest_623, IsCurPt_ReturnsFalse_WhenNoPointsAdded_623) {

    EXPECT_FALSE(gfxState->isCurPt());

}



TEST_F(GfxStateTest_623, IsCurPt_ReturnsTrue_AfterMoveTo_623) {

    gfxState->moveTo(10.0, 20.0);

    EXPECT_TRUE(gfxState->isCurPt());

}



TEST_F(GfxStateTest_623, IsCurPt_ReturnsTrue_AfterLineTo_623) {

    gfxState->moveTo(10.0, 20.0);

    gfxState->lineTo(30.0, 40.0);

    EXPECT_TRUE(gfxState->isCurPt());

}



TEST_F(GfxStateTest_623, IsCurPt_ReturnsTrue_AfterCurveTo_623) {

    gfxState->moveTo(10.0, 20.0);

    gfxState->curveTo(15.0, 25.0, 25.0, 35.0, 30.0, 40.0);

    EXPECT_TRUE(gfxState->isCurPt());

}



TEST_F(GfxStateTest_623, IsCurPt_ReturnsFalse_AfterClosePath_NoPointsAdded_623) {

    gfxState->closePath();

    EXPECT_FALSE(gfxState->isCurPt());

}



TEST_F(GfxStateTest_623, IsCurPt_ReturnsTrue_AfterClosePath_SomePointsAdded_623) {

    gfxState->moveTo(10.0, 20.0);

    gfxState->lineTo(30.0, 40.0);

    gfxState->closePath();

    EXPECT_TRUE(gfxState->isCurPt());

}



TEST_F(GfxStateTest_623, IsCurPt_ReturnsFalse_AfterClearPath_623) {

    gfxState->moveTo(10.0, 20.0);

    gfxState->clearPath();

    EXPECT_FALSE(gfxState->isCurPt());

}
