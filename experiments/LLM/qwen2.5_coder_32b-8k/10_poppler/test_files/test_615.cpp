#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_615 : public ::testing::Test {

protected:

    GfxState *gfxState;



    virtual void SetUp() {

        gfxState = new GfxState(300.0, 300.0, nullptr, 0, false);

    }



    virtual void TearDown() {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_615, GetPath_ReturnsNullPointer_615) {

    EXPECT_EQ(gfxState->getPath(), nullptr);

}



TEST_F(GfxStateTest_615, GetHDPI_ReturnsCorrectValue_615) {

    EXPECT_DOUBLE_EQ(gfxState->getHDPI(), 300.0);

}



TEST_F(GfxStateTest_615, GetVDPI_ReturnsCorrectValue_615) {

    EXPECT_DOUBLE_EQ(gfxState->getVDPI(), 300.0);

}



TEST_F(GfxStateTest_615, GetCTM_ReturnsDefaultMatrix_615) {

    std::array<double, 6> expectedCTM = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    EXPECT_EQ(gfxState->getCTM(), expectedCTM);

}



TEST_F(GfxStateTest_615, GetRotate_ReturnsCorrectValue_615) {

    EXPECT_EQ(gfxState->getRotate(), 0);

}



TEST_F(GfxStateTest_615, GetClipBBox_DefaultValues_615) {

    double xMin = 0.0, yMin = 0.0, xMax = 0.0, yMax = 0.0;

    gfxState->getClipBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, 0.0);

    EXPECT_DOUBLE_EQ(yMin, 0.0);

    EXPECT_DOUBLE_EQ(xMax, 0.0);

    EXPECT_DOUBLE_EQ(yMax, 0.0);

}



TEST_F(GfxStateTest_615, GetTransformedFontSize_DefaultValue_615) {

    EXPECT_DOUBLE_EQ(gfxState->getTransformedFontSize(), 0.0);

}



TEST_F(GfxStateTest_615, SetCTM_And_GetCTM_615) {

    gfxState->setCTM(2.0, 3.0, 4.0, 5.0, 6.0, 7.0);

    std::array<double, 6> expectedCTM = {2.0, 3.0, 4.0, 5.0, 6.0, 7.0};

    EXPECT_EQ(gfxState->getCTM(), expectedCTM);

}



TEST_F(GfxStateTest_615, ConcatCTM_And_GetCTM_615) {

    gfxState->setCTM(2.0, 3.0, 4.0, 5.0, 6.0, 7.0);

    gfxState->concatCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    std::array<double, 6> expectedCTM = {14.0, 19.0, 23.0, 34.0, 37.0, 58.0};

    EXPECT_EQ(gfxState->getCTM(), expectedCTM);

}



TEST_F(GfxStateTest_615, ShiftCTMAndClip_DefaultValues_NoChangeInClipBBox_615) {

    double xMin = 0.0, yMin = 0.0, xMax = 0.0, yMax = 0.0;

    gfxState->shiftCTMAndClip(10.0, 20.0);

    gfxState->getClipBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, 0.0);

    EXPECT_DOUBLE_EQ(yMin, 0.0);

    EXPECT_DOUBLE_EQ(xMax, 0.0);

    EXPECT_DOUBLE_EQ(yMax, 0.0);

}



TEST_F(GfxStateTest_615, SaveAndRestore_ReturnsSameState_615) {

    GfxState *savedState = gfxState->save();

    EXPECT_NE(savedState, nullptr);



    gfxState->setLineWidth(2.5);

    EXPECT_DOUBLE_EQ(gfxState->getLineWidth(), 2.5);



    gfxState->restore();

    EXPECT_DOUBLE_EQ(gfxState->getLineWidth(), 1.0); // default line width



    delete savedState;

}
