#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState *gfxState;



    void SetUp() override {

        gfxState = new GfxState(300, 300, nullptr, 0, false);

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_566, GetCTM_ReturnsDefaultValues_566) {

    const std::array<double, 6>& ctm = gfxState->getCTM();

    EXPECT_DOUBLE_EQ(ctm[0], 1.0);

    EXPECT_DOUBLE_EQ(ctm[1], 0.0);

    EXPECT_DOUBLE_EQ(ctm[2], 0.0);

    EXPECT_DOUBLE_EQ(ctm[3], 1.0);

    EXPECT_DOUBLE_EQ(ctm[4], 0.0);

    EXPECT_DOUBLE_EQ(ctm[5], 0.0);

}



TEST_F(GfxStateTest_566, SetCTM_UpdatesValuesCorrectly_566) {

    gfxState->setCTM(2.0, 3.0, 4.0, 5.0, 6.0, 7.0);

    const std::array<double, 6>& ctm = gfxState->getCTM();

    EXPECT_DOUBLE_EQ(ctm[0], 2.0);

    EXPECT_DOUBLE_EQ(ctm[1], 3.0);

    EXPECT_DOUBLE_EQ(ctm[2], 4.0);

    EXPECT_DOUBLE_EQ(ctm[3], 5.0);

    EXPECT_DOUBLE_EQ(ctm[4], 6.0);

    EXPECT_DOUBLE_EQ(ctm[5], 7.0);

}



TEST_F(GfxStateTest_566, ConcatCTM_MultipliesMatricesCorrectly_566) {

    gfxState->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    gfxState->concatCTM(7.0, 8.0, 9.0, 10.0, 11.0, 12.0);

    const std::array<double, 6>& ctm = gfxState->getCTM();

    EXPECT_DOUBLE_EQ(ctm[0], 34.0);

    EXPECT_DOUBLE_EQ(ctm[1], 50.0);

    EXPECT_DOUBLE_EQ(ctm[2], 40.0);

    EXPECT_DOUBLE_EQ(ctm[3], 64.0);

    EXPECT_DOUBLE_EQ(ctm[4], 79.0);

    EXPECT_DOUBLE_EQ(ctm[5], 118.0);

}



TEST_F(GfxStateTest_566, ShiftCTMAndClip_AddsTranslationToMatrix_566) {

    gfxState->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    gfxState->shiftCTMAndClip(7.0, 8.0);

    const std::array<double, 6>& ctm = gfxState->getCTM();

    EXPECT_DOUBLE_EQ(ctm[0], 1.0);

    EXPECT_DOUBLE_EQ(ctm[1], 2.0);

    EXPECT_DOUBLE_EQ(ctm[2], 3.0);

    EXPECT_DOUBLE_EQ(ctm[3], 4.0);

    EXPECT_DOUBLE_EQ(ctm[4], 59.0);

    EXPECT_DOUBLE_EQ(ctm[5], 86.0);

}



TEST_F(GfxStateTest_566, GetHDPI_ReturnsCorrectValue_566) {

    double hDPI = gfxState->getHDPI();

    EXPECT_DOUBLE_EQ(hDPI, 300.0);

}



TEST_F(GfxStateTest_566, GetVDPI_ReturnsCorrectValue_566) {

    double vDPI = gfxState->getVDPI();

    EXPECT_DOUBLE_EQ(vDPI, 300.0);

}
