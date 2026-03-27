#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    double hDPI = 300;

    double vDPI = 300;

    PDFRectangle pageBox {0, 0, 612, 792};

    int rotate = 0;



    std::unique_ptr<GfxState> gfxState;



    void SetUp() override {

        gfxState = std::make_unique<GfxState>(hDPI, vDPI, &pageBox, rotate, false);

    }

};



TEST_F(GfxStateTest_618, GetCurTextX_DefaultValue_618) {

    EXPECT_EQ(gfxState->getCurTextX(), 0.0);

}



TEST_F(GfxStateTest_618, GetCurTextY_DefaultValue_618) {

    EXPECT_EQ(gfxState->getCurTextY(), 0.0);

}



TEST_F(GfxStateTest_618, TextShift_AffectsCurTextXAndY_618) {

    double tx = 10.0;

    double ty = 20.0;

    gfxState->textShift(tx, ty);

    EXPECT_EQ(gfxState->getCurTextX(), tx);

    EXPECT_EQ(gfxState->getCurTextY(), ty);

}



TEST_F(GfxStateTest_618, TextShiftWithUserCoords_AffectsCurTextXAndY_618) {

    double dx = 5.0;

    double dy = 15.0;

    gfxState->textShiftWithUserCoords(dx, dy);

    EXPECT_EQ(gfxState->getCurTextX(), dx);

    EXPECT_EQ(gfxState->getCurTextY(), dy);

}



TEST_F(GfxStateTest_618, Save_RestorePreservesCurTextXAndY_618) {

    double tx = 30.0;

    double ty = 40.0;

    gfxState->textShift(tx, ty);



    auto savedState = gfxState->save();

    gfxState->textShift(5.0, 5.0);

    EXPECT_NE(gfxState->getCurTextX(), tx);

    EXPECT_NE(gfxState->getCurTextY(), ty);



    gfxState.reset(gfxState->restore());

    EXPECT_EQ(gfxState->getCurTextX(), tx);

    EXPECT_EQ(gfxState->getCurTextY(), ty);

}



TEST_F(GfxStateTest_618, BoundaryCondition_TextShiftLargeValues_618) {

    double largeTx = 1e9;

    double largeTy = -1e9;

    gfxState->textShift(largeTx, largeTy);

    EXPECT_EQ(gfxState->getCurTextX(), largeTx);

    EXPECT_EQ(gfxState->getCurTextY(), largeTy);

}



TEST_F(GfxStateTest_618, BoundaryCondition_TextShiftSmallValues_618) {

    double smallTx = 1e-9;

    double smallTy = -1e-9;

    gfxState->textShift(smallTx, smallTy);

    EXPECT_EQ(gfxState->getCurTextX(), smallTx);

    EXPECT_EQ(gfxState->getCurTextY(), smallTy);

}
