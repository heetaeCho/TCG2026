#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    double hDPI = 72.0;

    double vDPI = 72.0;

    PDFRectangle pageBox{0, 0, 595.28, 841.89};

    int rotate = 0;



    std::shared_ptr<GfxFont> testFont = std::make_shared<GfxFont>();



    GfxState *gfxState;



    void SetUp() override {

        gfxState = new GfxState(hDPI, vDPI, &pageBox, rotate, false);

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_605, GetFontInitiallyNull_605) {

    EXPECT_EQ(gfxState->getFont(), nullptr);

}



TEST_F(GfxStateTest_605, SetAndGetFontNormalOperation_605) {

    gfxState->setFont(testFont, 12.0);

    EXPECT_EQ(gfxState->getFont(), testFont);

}



TEST_F(GfxStateTest_605, SetAndGetFontSizeNormalOperation_605) {

    double fontSize = 14.0;

    gfxState->setFont(testFont, fontSize);

    EXPECT_DOUBLE_EQ(gfxState->getFontSize(), fontSize);

}



TEST_F(GfxStateTest_605, GetTransformedFontSizeInitiallyZero_605) {

    EXPECT_DOUBLE_EQ(gfxState->getTransformedFontSize(), 0.0);

}



TEST_F(GfxStateTest_605, SetAndGetLineWidthNormalOperation_605) {

    double lineWidth = 2.0;

    gfxState->setLineWidth(lineWidth);

    EXPECT_DOUBLE_EQ(gfxState->getLineWidth(), lineWidth);

}



TEST_F(GfxStateTest_605, GetFlatnessInitiallyDefault_605) {

    EXPECT_EQ(gfxState->getFlatness(), 1);

}



TEST_F(GfxStateTest_605, SetAndGetFlatnessNormalOperation_605) {

    int flatness = 2;

    gfxState->setFlatness(flatness);

    EXPECT_EQ(gfxState->getFlatness(), flatness);

}



TEST_F(GfxStateTest_605, GetLineJoinInitiallyMiter_605) {

    EXPECT_EQ(gfxState->getLineJoin(), miterJoin);

}



TEST_F(GfxStateTest_605, SetAndGetLineJoinNormalOperation_605) {

    LineJoinStyle lineJoin = roundJoin;

    gfxState->setLineJoin(lineJoin);

    EXPECT_EQ(gfxState->getLineJoin(), lineJoin);

}



TEST_F(GfxStateTest_605, GetLineCapInitiallyButt_605) {

    EXPECT_EQ(gfxState->getLineCap(), buttCap);

}



TEST_F(GfxStateTest_605, SetAndGetLineCapNormalOperation_605) {

    LineCapStyle lineCap = roundCap;

    gfxState->setLineCap(lineCap);

    EXPECT_EQ(gfxState->getLineCap(), lineCap);

}



TEST_F(GfxStateTest_605, GetMiterLimitInitiallyTen_605) {

    EXPECT_DOUBLE_EQ(gfxState->getMiterLimit(), 10.0);

}



TEST_F(GfxStateTest_605, SetAndGetMiterLimitNormalOperation_605) {

    double miterLimit = 20.0;

    gfxState->setMiterLimit(miterLimit);

    EXPECT_DOUBLE_EQ(gfxState->getMiterLimit(), miterLimit);

}



TEST_F(GfxStateTest_605, GetStrokeAdjustInitiallyFalse_605) {

    EXPECT_FALSE(gfxState->getStrokeAdjust());

}



TEST_F(GfxStateTest_605, SetAndGetStrokeAdjustNormalOperation_605) {

    bool strokeAdjust = true;

    gfxState->setStrokeAdjust(strokeAdjust);

    EXPECT_EQ(gfxState->getStrokeAdjust(), strokeAdjust);

}



TEST_F(GfxStateTest_605, GetAlphaIsShapeInitiallyFalse_605) {

    EXPECT_FALSE(gfxState->getAlphaIsShape());

}



TEST_F(GfxStateTest_605, SetAndGetAlphaIsShapeNormalOperation_605) {

    bool alphaIsShape = true;

    gfxState->setAlphaIsShape(alphaIsShape);

    EXPECT_EQ(gfxState->getAlphaIsShape(), alphaIsShape);

}



TEST_F(GfxStateTest_605, GetTextKnockoutInitiallyFalse_605) {

    EXPECT_FALSE(gfxState->getTextKnockout());

}



TEST_F(GfxStateTest_605, SetAndGetTextKnockoutNormalOperation_605) {

    bool textKnockout = true;

    gfxState->setTextKnockout(textKnockout);

    EXPECT_EQ(gfxState->getTextKnockout(), textKnockout);

}



TEST_F(GfxStateTest_605, SetAndGetBlendModeNormalOperation_605) {

    GfxBlendMode blendMode = multiply;

    gfxState->setBlendMode(blendMode);

    EXPECT_EQ(gfxState->getBlendMode(), blendMode);

}



TEST_F(GfxStateTest_605, SetAndGetFillOpacityNormalOperation_605) {

    double fillOpacity = 0.8;

    gfxState->setFillOpacity(fillOpacity);

    EXPECT_DOUBLE_EQ(gfxState->getFillOpacity(), fillOpacity);

}



TEST_F(GfxStateTest_605, SetAndGetStrokeOpacityNormalOperation_605) {

    double strokeOpacity = 0.6;

    gfxState->setStrokeOpacity(strokeOpacity);

    EXPECT_DOUBLE_EQ(gfxState->getStrokeOpacity(), strokeOpacity);

}



TEST_F(GfxStateTest_605, SetAndGetFillOverprintNormalOperation_605) {

    bool fillOverprint = true;

    gfxState->setFillOverprint(fillOverprint);

    EXPECT_EQ(gfxState->getFillOverprint(), fillOverprint);

}



TEST_F(GfxStateTest_605, SetAndGetStrokeOverprintNormalOperation_605) {

    bool strokeOverprint = false;

    gfxState->setStrokeOverprint(strokeOverprint);

    EXPECT_EQ(gfxState->getStrokeOverprint(), strokeOverprint);

}



TEST_F(GfxStateTest_605, SetAndGetOverprintModeNormalOperation_605) {

    int overprintMode = 2;

    gfxState->setOverprintMode(overprintMode);

    EXPECT_EQ(gfxState->getOverprintMode(), overprintMode);

}
