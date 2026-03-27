#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxStateTest_598 : public ::testing::Test {

protected:

    double hDPI = 300.0;

    double vDPI = 300.0;

    PDFRectangle pageBox {0, 0, 612, 792};

    int rotate = 0;



    GfxState *gfxState;



    void SetUp() override {

        gfxState = new GfxState(hDPI, vDPI, &pageBox, rotate, false);

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_598, GetFlatnessDefault_598) {

    EXPECT_EQ(gfxState->getFlatness(), 0);

}



TEST_F(GfxStateTest_598, SetAndGetFlatnessNormal_598) {

    gfxState->setFlatness(1);

    EXPECT_EQ(gfxState->getFlatness(), 1);



    gfxState->setFlatness(10);

    EXPECT_EQ(gfxState->getFlatness(), 10);

}



TEST_F(GfxStateTest_598, SetAndGetFlatnessBoundary_598) {

    gfxState->setFlatness(-1);

    EXPECT_EQ(gfxState->getFlatness(), -1);



    gfxState->setFlatness(256); // Assuming some reasonable upper limit

    EXPECT_EQ(gfxState->getFlatness(), 256);

}



TEST_F(GfxStateTest_598, SetAndGetFlatnessSameValueTwice_598) {

    gfxState->setFlatness(5);

    gfxState->setFlatness(5);

    EXPECT_EQ(gfxState->getFlatness(), 5);

}
