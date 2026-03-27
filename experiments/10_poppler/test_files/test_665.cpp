#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_665 : public ::testing::Test {

protected:

    GfxState *gfxState;



    void SetUp() override {

        gfxState = new GfxState(300.0, 300.0, nullptr, 0, false);

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_665, TextMoveToSetsLineCoordinates_665) {

    double tx = 10.0, ty = 20.0;

    gfxState->textMoveTo(tx, ty);

    EXPECT_EQ(gfxState->getLineX(), tx);

    EXPECT_EQ(gfxState->getLineY(), ty);

}



TEST_F(GfxStateTest_665, TextMoveToUpdatesCurTextCoordinates_665) {

    double tx = 10.0, ty = 20.0;

    gfxState->textMoveTo(tx, ty);

    EXPECT_EQ(gfxState->getCurTextX(), tx);

    EXPECT_EQ(gfxState->getCurTextY(), ty);

}



TEST_F(GfxStateTest_665, TextMoveToBoundaryConditions_665) {

    double maxDouble = std::numeric_limits<double>::max();

    gfxState->textMoveTo(maxDouble, maxDouble);

    EXPECT_EQ(gfxState->getLineX(), maxDouble);

    EXPECT_EQ(gfxState->getLineY(), maxDouble);



    double minDouble = std::numeric_limits<double>::lowest();

    gfxState->textMoveTo(minDouble, minDouble);

    EXPECT_EQ(gfxState->getLineX(), minDouble);

    EXPECT_EQ(gfxState->getLineY(), minDouble);

}



TEST_F(GfxStateTest_665, TextMoveToZeroCoordinates_665) {

    double tx = 0.0, ty = 0.0;

    gfxState->textMoveTo(tx, ty);

    EXPECT_EQ(gfxState->getLineX(), tx);

    EXPECT_EQ(gfxState->getLineY(), ty);

}



TEST_F(GfxStateTest_665, TextMoveToNegativeCoordinates_665) {

    double tx = -10.0, ty = -20.0;

    gfxState->textMoveTo(tx, ty);

    EXPECT_EQ(gfxState->getLineX(), tx);

    EXPECT_EQ(gfxState->getLineY(), ty);

}
