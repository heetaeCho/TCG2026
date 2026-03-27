#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_617 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Initialize with arbitrary values for hDPI and vDPI, and a mock pageBox.

        PDFRectangle pageBox(0.0, 0.0, 100.0, 200.0);

        gfxState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);

    }



    virtual void TearDown() {

        // Clean up resources if necessary.

        gfxState.reset();

    }



    std::unique_ptr<GfxState> gfxState;

};



TEST_F(GfxStateTest_617, GetCurY_NormalOperation_617) {

    double y = gfxState->getCurY();

    EXPECT_DOUBLE_EQ(y, 0.0); // Default value should be 0.0 unless modified.

}



TEST_F(GfxStateTest_617, GetCurY_BoundaryConditions_617) {

    // No specific boundary conditions for getCurY as it is a simple accessor.

    double y = gfxState->getCurY();

    EXPECT_DOUBLE_EQ(y, 0.0);

}



// Since there are no setters or other functions to modify curY in the provided interface,

// we cannot directly test exceptional cases or verify interactions.



TEST_F(GfxStateTest_617, GetHDPI_NormalOperation_617) {

    double hDPI = gfxState->getHDPI();

    EXPECT_DOUBLE_EQ(hDPI, 72.0);

}



TEST_F(GfxStateTest_617, GetVDPI_NormalOperation_617) {

    double vDPI = gfxState->getVDPI();

    EXPECT_DOUBLE_EQ(vDPI, 72.0);

}



TEST_F(GfxStateTest_617, GetPageWidth_NormalOperation_617) {

    double pageWidth = gfxState->getPageWidth();

    EXPECT_DOUBLE_EQ(pageWidth, 100.0); // As per the mock pageBox initialization.

}



TEST_F(GfxStateTest_617, GetPageHeight_NormalOperation_617) {

    double pageHeight = gfxState->getPageHeight();

    EXPECT_DOUBLE_EQ(pageHeight, 200.0); // As per the mock pageBox initialization.

}



TEST_F(GfxStateTest_617, GetRotate_NormalOperation_617) {

    int rotate = gfxState->getRotate();

    EXPECT_EQ(rotate, 0);

}
