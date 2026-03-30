#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    double hDPI = 72.0;

    double vDPI = 72.0;

    PDFRectangle pageBox = {0, 0, 612, 792};

    int rotate = 0;



    GfxState *gfxState;



    void SetUp() override {

        gfxState = new GfxState(hDPI, vDPI, &pageBox, rotate, false);

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_563, CopyConstructor_DefaultValues_563) {

    GfxState *copyState = gfxState->copy();

    EXPECT_EQ(copyState->getHDPI(), hDPI);

    EXPECT_EQ(copyState->getVDPI(), vDPI);

    EXPECT_EQ(copyState->getPageWidth(), pageBox.x2 - pageBox.x1);

    EXPECT_EQ(copyState->getPageHeight(), pageBox.y2 - pageBox.y1);

    EXPECT_EQ(copyState->getRotate(), rotate);



    delete copyState;

}



TEST_F(GfxStateTest_563, CopyConstructor_CopyPath_DefaultValues_563) {

    GfxState *copyState = gfxState->copy(true);

    EXPECT_EQ(copyState->getHDPI(), hDPI);

    EXPECT_EQ(copyState->getVDPI(), vDPI);

    EXPECT_EQ(copyState->getPageWidth(), pageBox.x2 - pageBox.x1);

    EXPECT_EQ(copyState->getPageHeight(), pageBox.y2 - pageBox.y1);

    EXPECT_EQ(copyState->getRotate(), rotate);



    delete copyState;

}



TEST_F(GfxStateTest_563, Getters_DefaultValues_563) {

    EXPECT_EQ(gfxState->getHDPI(), hDPI);

    EXPECT_EQ(gfxState->getVDPI(), vDPI);

    EXPECT_EQ(gfxState->getPageWidth(), pageBox.x2 - pageBox.x1);

    EXPECT_EQ(gfxState->getPageHeight(), pageBox.y2 - pageBox.y1);

    EXPECT_EQ(gfxState->getRotate(), rotate);

}



TEST_F(GfxStateTest_563, Getters_CTM_DefaultValues_563) {

    std::array<double, 6> ctm = gfxState->getCTM();

    EXPECT_DOUBLE_EQ(ctm[0], 1.0);

    EXPECT_DOUBLE_EQ(ctm[1], 0.0);

    EXPECT_DOUBLE_EQ(ctm[2], 0.0);

    EXPECT_DOUBLE_EQ(ctm[3], 1.0);

    EXPECT_DOUBLE_EQ(ctm[4], 0.0);

    EXPECT_DOUBLE_EQ(ctm[5], 0.0);

}



TEST_F(GfxStateTest_563, SettersAndGetters_CTM_563) {

    gfxState->setCTM(2.0, 0.0, 0.0, 2.0, 1.0, 1.0);

    std::array<double, 6> ctm = gfxState->getCTM();

    EXPECT_DOUBLE_EQ(ctm[0], 2.0);

    EXPECT_DOUBLE_EQ(ctm[1], 0.0);

    EXPECT_DOUBLE_EQ(ctm[2], 0.0);

    EXPECT_DOUBLE_EQ(ctm[3], 2.0);

    EXPECT_DOUBLE_EQ(ctm[4], 1.0);

    EXPECT_DOUBLE_EQ(ctm[5], 1.0);

}



TEST_F(GfxStateTest_563, ConcatCTM_563) {

    gfxState->setCTM(2.0, 0.0, 0.0, 2.0, 1.0, 1.0);

    gfxState->concatCTM(0.5, 0.0, 0.0, 0.5, -1.0, -1.0);



    std::array<double, 6> ctm = gfxState->getCTM();

    EXPECT_DOUBLE_EQ(ctm[0], 1.0);

    EXPECT_DOUBLE_EQ(ctm[1], 0.0);

    EXPECT_DOUBLE_EQ(ctm[2], 0.0);

    EXPECT_DOUBLE_EQ(ctm[3], 1.0);

    EXPECT_DOUBLE_EQ(ctm[4], -1.0);

    EXPECT_DOUBLE_EQ(ctm[5], -1.0);

}



TEST_F(GfxStateTest_563, SaveAndRestore_563) {

    gfxState->setLineWidth(2.0);



    GfxState *savedState = gfxState->save();

    gfxState->setLineWidth(4.0);



    EXPECT_DOUBLE_EQ(gfxState->getLineWidth(), 4.0);

    

    gfxState = gfxState->restore();



    EXPECT_DOUBLE_EQ(gfxState->getLineWidth(), 2.0);



    delete savedState;

}



TEST_F(GfxStateTest_563, SaveAndRestore_NoSavedStates_563) {

    EXPECT_FALSE(gfxState->hasSaves());



    GfxState *savedState = gfxState->save();

    

    EXPECT_TRUE(gfxState->hasSaves());

    

    gfxState = gfxState->restore();



    EXPECT_FALSE(gfxState->hasSaves());



    delete savedState;

}



TEST_F(GfxStateTest_563, SaveAndRestore_MultipleStates_563) {

    gfxState->setLineWidth(2.0);



    GfxState *savedState1 = gfxState->save();

    gfxState->setLineWidth(4.0);

    

    GfxState *savedState2 = gfxState->save();

    gfxState->setLineWidth(6.0);

    

    EXPECT_DOUBLE_EQ(gfxState->getLineWidth(), 6.0);



    gfxState = gfxState->restore();



    EXPECT_DOUBLE_EQ(gfxState->getLineWidth(), 4.0);



    gfxState = gfxState->restore();



    EXPECT_DOUBLE_EQ(gfxState->getLineWidth(), 2.0);



    delete savedState1;

    delete savedState2;

}
