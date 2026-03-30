#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_564 : public ::testing::Test {

protected:

    double hDPI = 300.0;

    double vDPI = 200.0;

    PDFRectangle pageBox{0, 0, 816, 1056}; // A4 size in points

    int rotate = 0;



    GfxState state{hDPI, vDPI, &pageBox, rotate, false};

};



TEST_F(GfxStateTest_564, GetHDPI_ReturnsCorrectValue_564) {

    EXPECT_EQ(state.getHDPI(), hDPI);

}



TEST_F(GfxStateTest_564, GetVDPI_ReturnsCorrectValue_564) {

    EXPECT_EQ(state.getVDPI(), vDPI);

}



TEST_F(GfxStateTest_564, GetPageWidth_ReturnsCorrectValue_564) {

    EXPECT_EQ(state.getPageWidth(), 816.0);

}



TEST_F(GfxStateTest_564, GetPageHeight_ReturnsCorrectValue_564) {

    EXPECT_EQ(state.getPageHeight(), 1056.0);

}



TEST_F(GfxStateTest_564, GetRotate_ReturnsCorrectValue_564) {

    EXPECT_EQ(state.getRotate(), rotate);

}
