#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxState> gfxState;



    void SetUp() override {

        PDFRectangle pageBox = {0, 0, 612, 792}; // Example A4 size in points

        gfxState = std::make_unique<GfxState>(300.0, 300.0, &pageBox, 0, false);

    }

};



TEST_F(GfxStateTest_572, GetPageWidth_NormalOperation_572) {

    EXPECT_DOUBLE_EQ(gfxState->getPageWidth(), 612.0);

}



TEST_F(GfxStateTest_572, GetPageHeight_NormalOperation_572) {

    EXPECT_DOUBLE_EQ(gfxState->getPageHeight(), 792.0);

}



TEST_F(GfxStateTest_572, GetRotate_NormalOperation_572) {

    EXPECT_EQ(gfxState->getRotate(), 0);

}



TEST_F(GfxStateTest_572, GetHDPI_NormalOperation_572) {

    EXPECT_DOUBLE_EQ(gfxState->getHDPI(), 300.0);

}



TEST_F(GfxStateTest_572, GetVDPI_NormalOperation_572) {

    EXPECT_DOUBLE_EQ(gfxState->getVDPI(), 300.0);

}



TEST_F(GfxStateTest_572, GetCTM_NormalOperation_572) {

    std::array<double, 6> ctm = gfxState->getCTM();

    for (int i = 1; i < 6; ++i) {

        EXPECT_DOUBLE_EQ(ctm[i], 0.0);

    }

    EXPECT_DOUBLE_EQ(ctm[0], 1.0);

    EXPECT_DOUBLE_EQ(ctm[3], 1.0);

}



TEST_F(GfxStateTest_572, GetX1_NormalOperation_572) {

    EXPECT_DOUBLE_EQ(gfxState->getX1(), 0.0);

}



TEST_F(GfxStateTest_572, GetY1_NormalOperation_572) {

    EXPECT_DOUBLE_EQ(gfxState->getY1(), 0.0);

}



TEST_F(GfxStateTest_572, GetX2_NormalOperation_572) {

    EXPECT_DOUBLE_EQ(gfxState->getX2(), 612.0);

}



TEST_F(GfxStateTest_572, GetY2_NormalOperation_572) {

    EXPECT_DOUBLE_EQ(gfxState->getY2(), 792.0);

}
