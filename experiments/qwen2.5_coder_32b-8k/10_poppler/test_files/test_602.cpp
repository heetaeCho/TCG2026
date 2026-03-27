#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    double hDPI = 300.0;

    double vDPI = 300.0;

    PDFRectangle pageBox = {0, 0, 612, 792}; // A4 size in points

    int rotate = 0;



    GfxState *gfxState;



    void SetUp() override {

        gfxState = new GfxState(hDPI, vDPI, &pageBox, rotate, false);

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_602, GetStrokeAdjustDefault_602) {

    EXPECT_FALSE(gfxState->getStrokeAdjust());

}



TEST_F(GfxStateTest_602, SetAndGetStrokeAdjustTrue_602) {

    gfxState->setStrokeAdjust(true);

    EXPECT_TRUE(gfxState->getStrokeAdjust());

}



TEST_F(GfxStateTest_602, SetAndGetStrokeAdjustFalse_602) {

    gfxState->setStrokeAdjust(false);

    EXPECT_FALSE(gfxState->getStrokeAdjust());

}



TEST_F(GfxStateTest_602, GetHDPI_602) {

    EXPECT_DOUBLE_EQ(hDPI, gfxState->getHDPI());

}



TEST_F(GfxStateTest_602, GetVDPI_602) {

    EXPECT_DOUBLE_EQ(vDPI, gfxState->getVDPI());

}



TEST_F(GfxStateTest_602, GetPageWidth_602) {

    EXPECT_DOUBLE_EQ(pageBox.xMax - pageBox.xMin, gfxState->getPageWidth());

}



TEST_F(GfxStateTest_602, GetPageHeight_602) {

    EXPECT_DOUBLE_EQ(pageBox.yMax - pageBox.yMin, gfxState->getPageHeight());

}



TEST_F(GfxStateTest_602, GetRotate_602) {

    EXPECT_EQ(rotate, gfxState->getRotate());

}
