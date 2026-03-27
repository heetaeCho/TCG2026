#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    double hDPI = 300.0;

    double vDPI = 300.0;

    PDFRectangle pageBox{0, 0, 612, 792};

    int rotate = 0;

    bool upsideDown = false;



    GfxState *gfxState;



    void SetUp() override {

        gfxState = new GfxState(hDPI, vDPI, &pageBox, rotate, upsideDown);

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_630, SetFillColor_NormalOperation_630) {

    GfxColor color = {1.0, 0.0, 0.0};

    gfxState->setFillColor(&color);

    const GfxColor *fillColor = gfxState->getFillColor();

    EXPECT_EQ(fillColor->c[0], 1.0);

    EXPECT_EQ(fillColor->c[1], 0.0);

    EXPECT_EQ(fillColor->c[2], 0.0);

}



TEST_F(GfxStateTest_630, SetFillColor_BoundaryConditions_630) {

    GfxColor color = {0.0, 0.0, 0.0};

    gfxState->setFillColor(&color);

    const GfxColor *fillColor = gfxState->getFillColor();

    EXPECT_EQ(fillColor->c[0], 0.0);

    EXPECT_EQ(fillColor->c[1], 0.0);

    EXPECT_EQ(fillColor->c[2], 0.0);



    color = {1.0, 1.0, 1.0};

    gfxState->setFillColor(&color);

    fillColor = gfxState->getFillColor();

    EXPECT_EQ(fillColor->c[0], 1.0);

    EXPECT_EQ(fillColor->c[1], 1.0);

    EXPECT_EQ(fillColor->c[2], 1.0);

}



TEST_F(GfxStateTest_630, SetFillColor_ExceptionalCases_630) {

    GfxColor *nullColor = nullptr;

    EXPECT_NO_THROW(gfxState->setFillColor(nullColor));

    const GfxColor *fillColor = gfxState->getFillColor();

    EXPECT_EQ(fillColor, nullptr);

}
