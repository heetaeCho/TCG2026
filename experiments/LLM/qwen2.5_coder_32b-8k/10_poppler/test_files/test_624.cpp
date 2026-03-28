#include <gtest/gtest.h>

#include "GfxState.h"

#include "GfxPath.h"



class GfxStateTest_624 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any common objects or state here if needed

        PDFRectangle pageBox = {0, 0, 595, 841}; // A4 size in points

        gfxState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);

    }



    void TearDown() override {

        // Clean up any objects or state here if needed

    }



    std::unique_ptr<GfxState> gfxState;

};



TEST_F(GfxStateTest_624, IsPathInitiallyFalse_624) {

    EXPECT_FALSE(gfxState->isPath());

}



TEST_F(GfxStateTest_624, IsPathTrueAfterMoveTo_624) {

    gfxState->moveTo(10.0, 10.0);

    EXPECT_TRUE(gfxState->isPath());

}



TEST_F(GfxStateTest_624, IsPathTrueAfterLineTo_624) {

    gfxState->lineTo(20.0, 20.0);

    EXPECT_TRUE(gfxState->isPath());

}



TEST_F(GfxStateTest_624, IsPathTrueAfterCurveTo_624) {

    gfxState->curveTo(10.0, 10.0, 20.0, 20.0, 30.0, 30.0);

    EXPECT_TRUE(gfxState->isPath());

}



TEST_F(GfxStateTest_624, IsPathTrueAfterClosePath_624) {

    gfxState->closePath();

    EXPECT_TRUE(gfxState->isPath());

}



TEST_F(GfxStateTest_624, IsPathFalseAfterClearPath_624) {

    gfxState->moveTo(10.0, 10.0);

    gfxState->clearPath();

    EXPECT_FALSE(gfxState->isPath());

}
