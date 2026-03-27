#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    double hDPI = 300.0;

    double vDPI = 300.0;

    PDFRectangle pageBox{0, 0, 612, 792};

    int rotate = 0;



    std::unique_ptr<GfxState> gfxState;



    void SetUp() override {

        gfxState = std::make_unique<GfxState>(hDPI, vDPI, &pageBox, rotate, false);

    }

};



TEST_F(GfxStateTest_621, GetLineX_DefaultValue_621) {

    EXPECT_DOUBLE_EQ(gfxState->getLineX(), 0.0);

}



TEST_F(GfxStateTest_621, SetLineWidth_GetLineWidth_NormalOperation_621) {

    double lineWidth = 2.5;

    gfxState->setLineWidth(lineWidth);

    EXPECT_DOUBLE_EQ(gfxState->getLineWidth(), lineWidth);

}



TEST_F(GfxStateTest_621, SetLineWidth_ZeroBoundaryCondition_621) {

    double lineWidth = 0.0;

    gfxState->setLineWidth(lineWidth);

    EXPECT_DOUBLE_EQ(gfxState->getLineWidth(), lineWidth);

}



TEST_F(GfxStateTest_621, SetLineWidth_NegativeBoundaryCondition_621) {

    double lineWidth = -1.0;

    gfxState->setLineWidth(lineWidth);

    EXPECT_DOUBLE_EQ(gfxState->getLineWidth(), lineWidth);

}



TEST_F(GfxStateTest_621, SetLineDash_GetLineDash_NormalOperation_621) {

    std::vector<double> lineDash{5.0, 3.0};

    double start = 0.0;

    gfxState->setLineDash(std::move(lineDash), start);

    std::vector<double> retrievedDash;

    double retrievedStart;

    retrievedDash = gfxState->getLineDash(&retrievedStart);

    EXPECT_EQ(retrievedDash, lineDash);

    EXPECT_DOUBLE_EQ(retrievedStart, start);

}



TEST_F(GfxStateTest_621, SetFont_GetFont_NormalOperation_621) {

    auto font = std::make_shared<GfxFont>();

    double fontSize = 12.0;

    gfxState->setFont(font, fontSize);

    EXPECT_EQ(gfxState->getFont(), font);

    EXPECT_DOUBLE_EQ(gfxState->getFontSize(), fontSize);

}



TEST_F(GfxStateTest_621, GetClipBBox_DefaultValues_621) {

    double xMin, yMin, xMax, yMax;

    gfxState->getClipBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, 0.0);

    EXPECT_DOUBLE_EQ(yMin, 0.0);

    EXPECT_DOUBLE_EQ(xMax, 612.0);

    EXPECT_DOUBLE_EQ(yMax, 792.0);

}



TEST_F(GfxStateTest_621, ClipToRect_GetClipBBox_NormalOperation_621) {

    double clipXMin = 50.0;

    double clipYMin = 50.0;

    double clipXMax = 562.0;

    double clipYMax = 742.0;

    gfxState->clipToRect(clipXMin, clipYMin, clipXMax, clipYMax);

    double xMin, yMin, xMax, yMax;

    gfxState->getClipBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, clipXMin);

    EXPECT_DOUBLE_EQ(yMin, clipYMin);

    EXPECT_DOUBLE_EQ(xMax, clipXMax);

    EXPECT_DOUBLE_EQ(yMax, clipYMax);

}



TEST_F(GfxStateTest_621, MoveTo_GetCurXAndCurY_NormalOperation_621) {

    double x = 100.0;

    double y = 200.0;

    gfxState->moveTo(x, y);

    EXPECT_DOUBLE_EQ(gfxState->getCurX(), x);

    EXPECT_DOUBLE_EQ(gfxState->getCurY(), y);

}



TEST_F(GfxStateTest_621, LineTo_GetCurXAndCurY_NormalOperation_621) {

    double startX = 100.0;

    double startY = 200.0;

    gfxState->moveTo(startX, startY);

    double endX = 300.0;

    double endY = 400.0;

    gfxState->lineTo(endX, endY);

    EXPECT_DOUBLE_EQ(gfxState->getCurX(), endX);

    EXPECT_DOUBLE_EQ(gfxState->getCurY(), endY);

}



TEST_F(GfxStateTest_621, CurveTo_GetCurXAndCurY_NormalOperation_621) {

    double startX = 100.0;

    double startY = 200.0;

    gfxState->moveTo(startX, startY);

    double x1 = 150.0, y1 = 250.0;

    double x2 = 250.0, y2 = 350.0;

    double endX = 300.0, endY = 400.0;

    gfxState->curveTo(x1, y1, x2, y2, endX, endY);

    EXPECT_DOUBLE_EQ(gfxState->getCurX(), endX);

    EXPECT_DOUBLE_EQ(gfxState->getCurY(), endY);

}



TEST_F(GfxStateTest_621, ClosePath_HasNoEffectOnCoordinates_621) {

    double startX = 100.0;

    double startY = 200.0;

    gfxState->moveTo(startX, startY);

    gfxState->closePath();

    EXPECT_DOUBLE_EQ(gfxState->getCurX(), startX);

    EXPECT_DOUBLE_EQ(gfxState->getCurY(), startY);

}
