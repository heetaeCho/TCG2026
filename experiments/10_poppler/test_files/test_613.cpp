#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    double hDPI = 72.0;

    double vDPI = 72.0;

    PDFRectangle pageBox{0, 0, 595, 842};

    int rotate = 0;



    GfxState *gfxState;



    void SetUp() override {

        gfxState = new GfxState(hDPI, vDPI, &pageBox, rotate, false);

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_613, InitialRenderValue_613) {

    EXPECT_EQ(gfxState->getRender(), 0);

}



TEST_F(GfxStateTest_613, SetAndGetRenderValue_613) {

    int newRenderValue = 1;

    gfxState->setRender(newRenderValue);

    EXPECT_EQ(gfxState->getRender(), newRenderValue);

}



TEST_F(GfxStateTest_613, BoundaryRenderValuePositive_613) {

    int boundaryValue = std::numeric_limits<int>::max();

    gfxState->setRender(boundaryValue);

    EXPECT_EQ(gfxState->getRender(), boundaryValue);

}



TEST_F(GfxStateTest_613, BoundaryRenderValueNegative_613) {

    int boundaryValue = std::numeric_limits<int>::min();

    gfxState->setRender(boundaryValue);

    EXPECT_EQ(gfxState->getRender(), boundaryValue);

}
