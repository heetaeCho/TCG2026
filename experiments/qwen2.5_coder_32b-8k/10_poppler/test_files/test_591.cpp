#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    double hDPI = 300.0;

    double vDPI = 300.0;

    PDFRectangle pageBox{0, 0, 595, 842}; // A4 size in points

    int rotate = 0;



    GfxState *gfxState;



    void SetUp() override {

        gfxState = new GfxState(hDPI, vDPI, &pageBox, rotate, false);

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_591, GetStrokeOpacity_DefaultValue_591) {

    EXPECT_DOUBLE_EQ(gfxState->getStrokeOpacity(), 1.0);

}



TEST_F(GfxStateTest_591, SetAndGetStrokeOpacity_ValidRange_591) {

    gfxState->setStrokeOpacity(0.5);

    EXPECT_DOUBLE_EQ(gfxState->getStrokeOpacity(), 0.5);



    gfxState->setStrokeOpacity(1.0);

    EXPECT_DOUBLE_EQ(gfxState->getStrokeOpacity(), 1.0);



    gfxState->setStrokeOpacity(0.0);

    EXPECT_DOUBLE_EQ(gfxState->getStrokeOpacity(), 0.0);

}



TEST_F(GfxStateTest_591, SetAndGetStrokeOpacity_OutOfRange_591) {

    gfxState->setStrokeOpacity(-0.1);

    EXPECT_DOUBLE_EQ(gfxState->getStrokeOpacity(), -0.1);



    gfxState->setStrokeOpacity(1.1);

    EXPECT_DOUBLE_EQ(gfxState->getStrokeOpacity(), 1.1);

}



TEST_F(GfxStateTest_591, GetStrokeOpacity_AfterSaveAndRestore_591) {

    gfxState->setStrokeOpacity(0.75);

    auto savedState = gfxState->save();

    EXPECT_DOUBLE_EQ(gfxState->getStrokeOpacity(), 0.75);



    gfxState->restore();

    EXPECT_DOUBLE_EQ(gfxState->getStrokeOpacity(), 0.75);



    delete savedState;

}
