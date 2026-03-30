#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"

#include <memory>



class GfxStateTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize GfxState with default values for testing

        pdfRectangle = std::make_unique<PDFRectangle>(0, 0, 612, 792);

        gfxState = std::make_unique<GfxState>(300.0, 300.0, pdfRectangle.get(), 0, false);

    }



    void TearDown() override {

        // Clean up resources if necessary

    }



    std::unique_ptr<PDFRectangle> pdfRectangle;

    std::unique_ptr<GfxState> gfxState;

};



TEST_F(GfxStateTest_570, getX2_ReturnsCorrectValue_570) {

    EXPECT_EQ(gfxState->getX2(), 612.0);

}



TEST_F(GfxStateTest_570, getY2_ReturnsCorrectValue_570) {

    EXPECT_EQ(gfxState->getY2(), 792.0);

}



TEST_F(GfxStateTest_570, getHDPI_ReturnsCorrectValue_570) {

    EXPECT_EQ(gfxState->getHDPI(), 300.0);

}



TEST_F(GfxStateTest_570, getVDPI_ReturnsCorrectValue_570) {

    EXPECT_EQ(gfxState->getVDPI(), 300.0);

}



TEST_F(GfxStateTest_570, getPageWidth_ReturnsCorrectValue_570) {

    EXPECT_EQ(gfxState->getPageWidth(), 612.0);

}



TEST_F(GfxStateTest_570, getPageHeight_ReturnsCorrectValue_570) {

    EXPECT_EQ(gfxState->getPageHeight(), 792.0);

}



TEST_F(GfxStateTest_570, getRotate_ReturnsCorrectInitialValue_570) {

    EXPECT_EQ(gfxState->getRotate(), 0);

}



TEST_F(GfxStateTest_570, getCTM_ReturnsIdentityMatrix_570) {

    auto ctm = gfxState->getCTM();

    std::array<double, 6> identity{1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    EXPECT_EQ(ctm, identity);

}



TEST_F(GfxStateTest_570, save_RestoreMaintainsState_570) {

    gfxState->setLineWidth(2.0);

    auto savedState = gfxState->save();

    gfxState->setLineWidth(4.0);



    EXPECT_EQ(gfxState->getLineWidth(), 4.0);

    gfxState->restore();



    EXPECT_EQ(gfxState->getLineWidth(), 2.0);

}



TEST_F(GfxStateTest_570, setCTM_ChangesTransformMatrix_570) {

    gfxState->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    auto ctm = gfxState->getCTM();

    std::array<double, 6> expected{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    EXPECT_EQ(ctm, expected);

}



TEST_F(GfxStateTest_570, concatCTM_ModifiesTransformMatrix_570) {

    gfxState->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    gfxState->concatCTM(2.0, 3.0, 4.0, 5.0, 6.0, 7.0);

    auto ctm = gfxState->getCTM();

    std::array<double, 6> expected{10.0, 16.0, 12.0, 21.0, 23.0, 35.0};

    EXPECT_EQ(ctm, expected);

}



TEST_F(GfxStateTest_570, shiftCTMAndClip_AdjustsTransformMatrix_570) {

    gfxState->shiftCTMAndClip(10.0, 20.0);

    auto ctm = gfxState->getCTM();

    std::array<double, 6> expected{1.0, 0.0, 0.0, 1.0, 10.0, 20.0};

    EXPECT_EQ(ctm, expected);

}



TEST_F(GfxStateTest_570, setFont_ChangesFontAndSize_570) {

    auto font = std::make_shared<GfxFont>();

    double fontSize = 12.0;

    gfxState->setFont(font, fontSize);



    EXPECT_EQ(gfxState->getFontSize(), fontSize);

}



TEST_F(GfxStateTest_570, getTransformedFontSize_ReturnsCorrectValue_570) {

    auto font = std::make_shared<GfxFont>();

    double fontSize = 12.0;

    gfxState->setFont(font, fontSize);



    EXPECT_EQ(gfxState->getTransformedFontSize(), fontSize);

}



TEST_F(GfxStateTest_570, getUserClipBBox_ReturnsCorrectValues_570) {

    double xMin, yMin, xMax, yMax;

    gfxState->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);



    EXPECT_EQ(xMin, 0.0);

    EXPECT_EQ(yMin, 0.0);

    EXPECT_EQ(xMax, 612.0);

    EXPECT_EQ(yMax, 792.0);

}



TEST_F(GfxStateTest_570, getClipBBox_ReturnsCorrectValues_570) {

    double xMin, yMin, xMax, yMax;

    gfxState->getClipBBox(&xMin, &yMin, &xMax, &yMax);



    EXPECT_EQ(xMin, 0.0);

    EXPECT_EQ(yMin, 0.0);

    EXPECT_EQ(xMax, 612.0);

    EXPECT_EQ(yMax, 792.0);

}
