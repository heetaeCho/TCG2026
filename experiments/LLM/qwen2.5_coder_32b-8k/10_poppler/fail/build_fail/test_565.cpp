#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState state;



    void SetUp() override {

        // Initialize with arbitrary values since we are treating the implementation as a black box.

        double hDPIA = 300.0;

        double vDPIA = 300.0;

        PDFRectangle pageBox = {0, 0, 612, 792}; // A4 size in points

        int rotateA = 0; // No rotation

        bool upsideDown = false;



        state = GfxState(hDPIA, vDPIA, &pageBox, rotateA, upsideDown);

    }

};



TEST_F(GfxStateTest_565, GetVDPI_ReturnsExpectedValue_565) {

    double expectedVDPI = 300.0; // As initialized in SetUp

    EXPECT_EQ(state.getVDPI(), expectedVDPI);

}



TEST_F(GfxStateTest_565, GetHDPI_ReturnsExpectedValue_565) {

    double expectedHDPI = 300.0; // As initialized in SetUp

    EXPECT_EQ(state.getHDPI(), expectedHDPI);

}



TEST_F(GfxStateTest_565, GetPageWidth_ReturnsCorrectValue_565) {

    double expectedWidth = 612.0; // A4 size width in points

    EXPECT_EQ(state.getPageWidth(), expectedWidth);

}



TEST_F(GfxStateTest_565, GetPageHeight_ReturnsCorrectValue_565) {

    double expectedHeight = 792.0; // A4 size height in points

    EXPECT_EQ(state.getPageHeight(), expectedHeight);

}



TEST_F(GfxStateTest_565, GetRotate_ReturnsExpectedValue_565) {

    int expectedRotate = 0; // No rotation

    EXPECT_EQ(state.getRotate(), expectedRotate);

}
