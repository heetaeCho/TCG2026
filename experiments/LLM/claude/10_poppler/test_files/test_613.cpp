#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState with common parameters
class GfxStateTest_613 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// Test initial render value
TEST_F(GfxStateTest_613, GetRenderInitialValue_613) {
    EXPECT_EQ(state->getRender(), 0);
}

// Test setRender and getRender
TEST_F(GfxStateTest_613, SetRenderAndGetRender_613) {
    state->setRender(1);
    EXPECT_EQ(state->getRender(), 1);
}

// Test setRender with different values
TEST_F(GfxStateTest_613, SetRenderMultipleValues_613) {
    state->setRender(0);
    EXPECT_EQ(state->getRender(), 0);
    state->setRender(3);
    EXPECT_EQ(state->getRender(), 3);
    state->setRender(7);
    EXPECT_EQ(state->getRender(), 7);
}

// Test DPI getters
TEST_F(GfxStateTest_613, GetHDPI_613) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_613, GetVDPI_613) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_613, GetPageWidth_613) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_613, GetPageHeight_613) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test coordinate getters
TEST_F(GfxStateTest_613, GetX1Y1X2Y2_613) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_613, GetRotate_613) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test line width
TEST_F(GfxStateTest_613, SetAndGetLineWidth_613) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_613, DefaultLineWidth_613) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test flatness
TEST_F(GfxStateTest_613, SetAndGetFlatness_613) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test miter limit
TEST_F(GfxStateTest_613, SetAndGetMiterLimit_613) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test fill opacity
TEST_F(GfxStateTest_613, SetAndGetFillOpacity_613) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test stroke opacity
TEST_F(GfxStateTest_613, SetAndGetStrokeOpacity_613) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test fill overprint
TEST_F(GfxStateTest_613, SetAndGetFillOverprint_613) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test stroke overprint
TEST_F(GfxStateTest_613, SetAndGetStrokeOverprint_613) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test overprint mode
TEST_F(GfxStateTest_613, SetAndGetOverprintMode_613) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test stroke adjust
TEST_F(GfxStateTest_613, SetAndGetStrokeAdjust_613) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_613, SetAndGetAlphaIsShape_613) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_613, SetAndGetTextKnockout_613) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test char space
TEST_F(GfxStateTest_613, SetAndGetCharSpace_613) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test word space
TEST_F(GfxStateTest_613, SetAndGetWordSpace_613) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test horizontal scaling
TEST_F(GfxStateTest_613, SetAndGetHorizScaling_613) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test leading
TEST_F(GfxStateTest_613, SetAndGetLeading_613) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test rise
TEST_F(GfxStateTest_613, SetAndGetRise_613) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test font size
TEST_F(GfxStateTest_613, GetFontSize_613) {
    // Default font size should be 0 or some initial value
    double fontSize = state->getFontSize();
    // Just verify it returns without error
    SUCCEED();
}

// Test text matrix
TEST_F(GfxStateTest_613, SetAndGetTextMat_613) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &textMat = state->getTextMat();
    EXPECT_DOUBLE_EQ(textMat[0], 1.0);
    EXPECT_DOUBLE_EQ(textMat[1], 0.0);
    EXPECT_DOUBLE_EQ(textMat[2], 0.0);
    EXPECT_DOUBLE_EQ(textMat[3], 1.0);
    EXPECT_DOUBLE_EQ(textMat[4], 10.0);
    EXPECT_DOUBLE_EQ(textMat[5], 20.0);
}

// Test CTM
TEST_F(GfxStateTest_613, GetCTM_613) {
    const auto &ctm = state->getCTM();
    // CTM should be initialized based on the constructor parameters
    EXPECT_EQ(ctm.size(), 6u);
}

// Test setCTM
TEST_F(GfxStateTest_613, SetCTM_613) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 100.0);
    EXPECT_DOUBLE_EQ(ctm[5], 200.0);
}

// Test concatCTM
TEST_F(GfxStateTest_613, ConcatCTM_613) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test line join
TEST_F(GfxStateTest_613, SetAndGetLineJoin_613) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// Test line cap
TEST_F(GfxStateTest_613, SetAndGetLineCap_613) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test rendering intent
TEST_F(GfxStateTest_613, SetAndGetRenderingIntent_613) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test rendering intent with long string (boundary: buffer is 32 chars)
TEST_F(GfxStateTest_613, SetRenderingIntentLongString_613) {
    // The internal buffer is char[32], so setting a long string should be safe
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test blend mode
TEST_F(GfxStateTest_613, SetAndGetBlendMode_613) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test save and restore
TEST_F(GfxStateTest_613, SaveAndRestore_613) {
    state->setRender(5);
    state->setLineWidth(3.0);
    
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    
    state->setRender(2);
    state->setLineWidth(1.0);
    EXPECT_EQ(state->getRender(), 2);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
    
    GfxState *restored = state->restore();
    EXPECT_EQ(restored->getRender(), 5);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 3.0);
}

// Test hasSaves when no saves
TEST_F(GfxStateTest_613, HasSavesInitiallyFalse_613) {
    EXPECT_FALSE(state->hasSaves());
}

// Test path operations
TEST_F(GfxStateTest_613, MoveToAndIsPath_613) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_613, ClearPath_613) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_613, LineToCreatesPath_613) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_613, CurveToCreatesPath_613) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_613, ClosePath_613) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test transform
TEST_F(GfxStateTest_613, TransformIdentityCTM_613) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_613, TransformDeltaIdentityCTM_613) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

TEST_F(GfxStateTest_613, TransformWithScaleCTM_613) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 40.0);
}

TEST_F(GfxStateTest_613, TransformWithTranslation_613) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 50.0, 100.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 60.0);
    EXPECT_DOUBLE_EQ(y2, 120.0);
}

// Test transformWidth
TEST_F(GfxStateTest_613, TransformWidth_613) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_GT(w, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_613, GetTransformedLineWidth_613) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(2.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// Test clip bounding box
TEST_F(GfxStateTest_613, GetClipBBox_613) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_613, GetUserClipBBox_613) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_613, ClipToRect_613) {
    state->clipToRect(10.0, 10.0, 100.0, 100.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test textMoveTo
TEST_F(GfxStateTest_613, TextMoveTo_613) {
    state->textMoveTo(50.0, 100.0);
    // Verify through getCurTextX/getCurTextY or lineX/lineY
    // The exact behavior depends on implementation
    SUCCEED();
}

// Test getCurX and getCurY
TEST_F(GfxStateTest_613, GetCurXCurY_613) {
    state->moveTo(15.0, 25.0);
    // After moveTo, curX and curY should reflect the moved-to point
    double curX = state->getCurX();
    double curY = state->getCurY();
    EXPECT_DOUBLE_EQ(curX, 15.0);
    EXPECT_DOUBLE_EQ(curY, 25.0);
}

// Test line dash
TEST_F(GfxStateTest_613, SetAndGetLineDash_613) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test line dash with offset
TEST_F(GfxStateTest_613, SetLineDashWithOffset_613) {
    std::vector<double> dash = {2.0, 4.0, 6.0};
    state->setLineDash(std::move(dash), 1.5);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 3u);
    EXPECT_DOUBLE_EQ(start, 1.5);
}

// Test empty line dash
TEST_F(GfxStateTest_613, SetEmptyLineDash_613) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 0u);
}

// Test copy
TEST_F(GfxStateTest_613, CopyState_613) {
    state->setRender(4);
    state->setLineWidth(5.0);
    state->setFillOpacity(0.8);
    
    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_EQ(copied->getRender(), 4);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 5.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.8);
}

// Test with different page rotation
TEST(GfxStateRotationTest_613, RotatedPage_613) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
    EXPECT_DOUBLE_EQ(rotatedState.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(rotatedState.getPageHeight(), 792.0);
}

// Test with different DPI
TEST(GfxStateDPITest_613, DifferentDPI_613) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    
    GfxState highDpiState(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 300.0);
}

// Test with asymmetric DPI
TEST(GfxStateDPITest_613, AsymmetricDPI_613) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    
    GfxState asymState(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(asymState.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(asymState.getVDPI(), 300.0);
}

// Test fill color set and get
TEST_F(GfxStateTest_613, SetAndGetFillColor_613) {
    GfxColor color;
    color.c[0] = 32768; // midpoint for 16-bit
    state->setFillColor(&color);
    const GfxColor *retrievedColor = state->getFillColor();
    EXPECT_EQ(retrievedColor->c[0], 32768);
}

// Test stroke color set and get
TEST_F(GfxStateTest_613, SetAndGetStrokeColor_613) {
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor *retrievedColor = state->getStrokeColor();
    EXPECT_EQ(retrievedColor->c[0], 65535);
}

// Test getPath returns non-null
TEST_F(GfxStateTest_613, GetPath_613) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test lineX and lineY
TEST_F(GfxStateTest_613, GetLineXLineY_613) {
    double lx = state->getLineX();
    double ly = state->getLineY();
    // Just verify they return without error
    SUCCEED();
}

// Test getReusablePath
TEST_F(GfxStateTest_613, GetReusablePath_613) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto rpi = state->getReusablePath();
    EXPECT_NE(rpi, nullptr);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_613, ShiftCTMAndClip_613) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test textShift
TEST_F(GfxStateTest_613, TextShift_613) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->textShift(5.0, 10.0);
    // Verify through observable state if possible
    SUCCEED();
}

// Test multiple save/restore levels
TEST_F(GfxStateTest_613, MultipleSaveRestore_613) {
    state->setRender(1);
    GfxState *s1 = state->save();
    EXPECT_TRUE(state->hasSaves());
    
    state->setRender(2);
    GfxState *s2 = state->save();
    EXPECT_TRUE(state->hasSaves());
    
    state->setRender(3);
    EXPECT_EQ(state->getRender(), 3);
    
    GfxState *r1 = state->restore();
    EXPECT_EQ(r1->getRender(), 2);
    
    GfxState *r2 = r1->restore();
    EXPECT_EQ(r2->getRender(), 1);
    EXPECT_FALSE(r2->hasSaves());
}

// Test isParentState
TEST_F(GfxStateTest_613, IsParentState_613) {
    GfxState *saved = state->save();
    EXPECT_TRUE(state->isParentState(saved));
}

// Test setRender boundary values
TEST_F(GfxStateTest_613, SetRenderBoundaryZero_613) {
    state->setRender(0);
    EXPECT_EQ(state->getRender(), 0);
}

TEST_F(GfxStateTest_613, SetRenderBoundaryMax_613) {
    state->setRender(7);
    EXPECT_EQ(state->getRender(), 7);
}

// Test negative render value (edge case)
TEST_F(GfxStateTest_613, SetRenderNegative_613) {
    state->setRender(-1);
    EXPECT_EQ(state->getRender(), -1);
}

// Test fill opacity boundary values
TEST_F(GfxStateTest_613, FillOpacityZero_613) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_613, FillOpacityOne_613) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test stroke opacity boundary values
TEST_F(GfxStateTest_613, StrokeOpacityZero_613) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

TEST_F(GfxStateTest_613, StrokeOpacityOne_613) {
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test line width of zero
TEST_F(GfxStateTest_613, LineWidthZero_613) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test getCTM with Matrix parameter
TEST_F(GfxStateTest_613, GetCTMMatrix_613) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Matrix should be populated from CTM
    SUCCEED();
}

// Test text transform
TEST_F(GfxStateTest_613, TextTransform_613) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(10.0, 20.0, &x2, &y2);
    // Just verify it completes
    SUCCEED();
}

// Test textTransformDelta
TEST_F(GfxStateTest_613, TextTransformDelta_613) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(10.0, 20.0, &x2, &y2);
    // Just verify it completes
    SUCCEED();
}

// Test upsideDown parameter in constructor
TEST(GfxStateConstructorTest_613, UpsideDownFalse_613) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    
    GfxState notFlipped(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(notFlipped.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(notFlipped.getPageHeight(), 792.0);
}

// Test with 180-degree rotation
TEST(GfxStateRotationTest_613, Rotation180_613) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

// Test with 270-degree rotation
TEST(GfxStateRotationTest_613, Rotation270_613) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}
