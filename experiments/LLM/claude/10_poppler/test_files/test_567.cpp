#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <cstring>
#include <cmath>

#include "poppler/GfxState.h"

// Helper to create a PDFRectangle
static PDFRectangle makePageBox(double x1, double y1, double x2, double y2) {
    PDFRectangle r;
    r.x1 = x1;
    r.y1 = y1;
    r.x2 = x2;
    r.y2 = y2;
    return r;
}

class GfxStateTest_567 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// ==================== Constructor and Basic Getters ====================

TEST_F(GfxStateTest_567, ConstructorSetsHDPI_567) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_567, ConstructorSetsVDPI_567) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_567, ConstructorSetsPageWidth_567) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_567, ConstructorSetsPageHeight_567) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_567, ConstructorSetsRotate_567) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_567, ConstructorWithRotation90_567) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_567, ConstructorWithRotation180_567) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

TEST_F(GfxStateTest_567, ConstructorWithRotation270_567) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

TEST_F(GfxStateTest_567, GetX1Y1X2Y2_567) {
    // The page box corners should be reflected
    double x1 = state->getX1();
    double y1 = state->getY1();
    double x2 = state->getX2();
    double y2 = state->getY2();
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// ==================== CTM ====================

TEST_F(GfxStateTest_567, GetCTMReturnsArray_567) {
    const auto &ctm = state->getCTM();
    // CTM should be an array of 6 doubles; for identity-like default it should have meaningful values
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_567, GetCTMViaMatrix_567) {
    Matrix m;
    state->getCTM(&m);
    // Should match the array version
    const auto &ctm = state->getCTM();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(m.m[i], ctm[i]);
    }
}

TEST_F(GfxStateTest_567, SetCTM_567) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_567, ConcatCTM_567) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// ==================== Transform ====================

TEST_F(GfxStateTest_567, TransformPoint_567) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double tx, ty;
    state->transform(0.0, 0.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 100.0);
    EXPECT_DOUBLE_EQ(ty, 200.0);
}

TEST_F(GfxStateTest_567, TransformDelta_567) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double tx, ty;
    state->transformDelta(1.0, 1.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 2.0);
    EXPECT_DOUBLE_EQ(ty, 3.0);
}

TEST_F(GfxStateTest_567, TransformWidth_567) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_GT(w, 0.0);
}

TEST_F(GfxStateTest_567, TransformWidthZero_567) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(0.0);
    EXPECT_GE(w, 0.0);
}

// ==================== Line Properties ====================

TEST_F(GfxStateTest_567, SetAndGetLineWidth_567) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_567, SetLineWidthZero_567) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_567, SetAndGetLineJoin_567) {
    state->setLineJoin(LineJoinStyle::Miter);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Miter);
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
    state->setLineJoin(LineJoinStyle::Bevel);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Bevel);
}

TEST_F(GfxStateTest_567, SetAndGetLineCap_567) {
    state->setLineCap(LineCapStyle::Butt);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Butt);
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
    state->setLineCap(LineCapStyle::Projecting);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Projecting);
}

TEST_F(GfxStateTest_567, SetAndGetMiterLimit_567) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_567, SetAndGetLineDash_567) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
}

TEST_F(GfxStateTest_567, SetLineDashEmpty_567) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 0u);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

TEST_F(GfxStateTest_567, SetAndGetFlatness_567) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// ==================== Opacity and Blend ====================

TEST_F(GfxStateTest_567, SetAndGetFillOpacity_567) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_567, SetAndGetStrokeOpacity_567) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_567, SetFillOpacityBoundary_567) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_567, SetStrokeOpacityBoundary_567) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_567, SetAndGetBlendMode_567) {
    state->setBlendMode(GfxBlendMode::Normal);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// ==================== Overprint ====================

TEST_F(GfxStateTest_567, SetAndGetFillOverprint_567) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_567, SetAndGetStrokeOverprint_567) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_567, SetAndGetOverprintMode_567) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
    state->setOverprintMode(0);
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// ==================== Stroke Adjust, AlphaIsShape, TextKnockout ====================

TEST_F(GfxStateTest_567, SetAndGetStrokeAdjust_567) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_567, SetAndGetAlphaIsShape_567) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_567, SetAndGetTextKnockout_567) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// ==================== Text Properties ====================

TEST_F(GfxStateTest_567, SetAndGetCharSpace_567) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_567, SetAndGetWordSpace_567) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_567, SetAndGetHorizScaling_567) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

TEST_F(GfxStateTest_567, SetAndGetLeading_567) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_567, SetAndGetRise_567) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_567, SetAndGetRender_567) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_567, SetAndGetTextMat_567) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 2.0);
    EXPECT_DOUBLE_EQ(tm[2], 3.0);
    EXPECT_DOUBLE_EQ(tm[3], 4.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 6.0);
}

// ==================== Rendering Intent ====================

TEST_F(GfxStateTest_567, SetAndGetRenderingIntent_567) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

TEST_F(GfxStateTest_567, SetRenderingIntentRelativeColorimetric_567) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_567, SetRenderingIntentPerceptual_567) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_567, SetRenderingIntentSaturation_567) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

// ==================== Font ====================

TEST_F(GfxStateTest_567, GetFontSizeDefault_567) {
    // After construction, fontSize might be 0 or some default
    double fs = state->getFontSize();
    EXPECT_GE(fs, 0.0);
}

TEST_F(GfxStateTest_567, GetFontDefaultNull_567) {
    // After construction, font might be null
    const auto &f = state->getFont();
    // It may or may not be null; just test that it doesn't crash
    (void)f;
}

// ==================== Path Operations ====================

TEST_F(GfxStateTest_567, InitialPathIsEmpty_567) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_567, MoveToSetsCurrentPoint_567) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

TEST_F(GfxStateTest_567, LineToCreatesPath_567) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

TEST_F(GfxStateTest_567, CurveToCreatesPath_567) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 5.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 6.0);
}

TEST_F(GfxStateTest_567, ClosePathOperation_567) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_567, ClearPathResetsPath_567) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_567, GetPathNotNull_567) {
    state->moveTo(0.0, 0.0);
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// ==================== Text Move ====================

TEST_F(GfxStateTest_567, TextMoveTo_567) {
    state->textMoveTo(100.0, 200.0);
    // lineX, lineY should be set
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// ==================== Clipping ====================

TEST_F(GfxStateTest_567, GetClipBBox_567) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_567, GetUserClipBBox_567) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_567, ClipToRect_567) {
    state->clipToRect(10.0, 10.0, 100.0, 100.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_567, ClipToRectNarrows_567) {
    double xMinBefore, yMinBefore, xMaxBefore, yMaxBefore;
    state->getClipBBox(&xMinBefore, &yMinBefore, &xMaxBefore, &yMaxBefore);
    
    state->clipToRect(50.0, 50.0, 100.0, 100.0);
    
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, xMinBefore);
    EXPECT_GE(yMin, yMinBefore);
    EXPECT_LE(xMax, xMaxBefore);
    EXPECT_LE(yMax, yMaxBefore);
}

// ==================== Save / Restore ====================

TEST_F(GfxStateTest_567, InitiallyNoSaves_567) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_567, SaveCreatesSavedState_567) {
    GfxState *saved = state->save();
    EXPECT_NE(saved, nullptr);
    EXPECT_TRUE(saved->hasSaves());
}

TEST_F(GfxStateTest_567, RestoreReturnsParent_567) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    GfxState *restored = saved->restore();
    EXPECT_NE(restored, nullptr);
}

TEST_F(GfxStateTest_567, SaveRestorePreservesLineWidth_567) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 10.0);
    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_567, SaveRestorePreservesOpacity_567) {
    state->setFillOpacity(0.3);
    GfxState *saved = state->save();
    saved->setFillOpacity(0.9);
    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getFillOpacity(), 0.3);
}

TEST_F(GfxStateTest_567, IsParentState_567) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->isParentState(state.get()));
}

// ==================== Copy ====================

TEST_F(GfxStateTest_567, CopyState_567) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.5);
    GfxState *copied = state->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.5);
    delete copied;
}

// ==================== Text Transform ====================

TEST_F(GfxStateTest_567, TextTransform_567) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(10.0, 20.0, &x2, &y2);
    // The result should be valid (at minimum, no crash)
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

TEST_F(GfxStateTest_567, TextTransformDelta_567) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(1.0, 1.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// ==================== ShiftCTMAndClip ====================

TEST_F(GfxStateTest_567, ShiftCTMAndClip_567) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// ==================== Color ====================

TEST_F(GfxStateTest_567, SetAndGetFillColor_567) {
    GfxColor color;
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *fc = state->getFillColor();
    ASSERT_NE(fc, nullptr);
    EXPECT_EQ(fc->c[0], 32768);
}

TEST_F(GfxStateTest_567, SetAndGetStrokeColor_567) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *sc = state->getStrokeColor();
    ASSERT_NE(sc, nullptr);
    EXPECT_EQ(sc->c[0], 16384);
}

// ==================== Color Space (nullptr checks) ====================

TEST_F(GfxStateTest_567, GetFillColorSpaceInitial_567) {
    // Might be default or null
    GfxColorSpace *cs = state->getFillColorSpace();
    // Just check no crash
    (void)cs;
}

TEST_F(GfxStateTest_567, GetStrokeColorSpaceInitial_567) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    (void)cs;
}

TEST_F(GfxStateTest_567, GetFillPatternInitial_567) {
    GfxPattern *p = state->getFillPattern();
    EXPECT_EQ(p, nullptr);
}

TEST_F(GfxStateTest_567, GetStrokePatternInitial_567) {
    GfxPattern *p = state->getStrokePattern();
    EXPECT_EQ(p, nullptr);
}

// ==================== Transformed Line Width ====================

TEST_F(GfxStateTest_567, GetTransformedLineWidth_567) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// ==================== Transformed Font Size ====================

TEST_F(GfxStateTest_567, GetTransformedFontSize_567) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double tfs = state->getTransformedFontSize();
    EXPECT_GE(tfs, 0.0);
}

// ==================== GetFontTransMat ====================

TEST_F(GfxStateTest_567, GetFontTransMat_567) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    EXPECT_TRUE(std::isfinite(m11));
    EXPECT_TRUE(std::isfinite(m12));
    EXPECT_TRUE(std::isfinite(m21));
    EXPECT_TRUE(std::isfinite(m22));
}

// ==================== TextShift ====================

TEST_F(GfxStateTest_567, TextShift_567) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->textMoveTo(0.0, 0.0);
    state->textShift(10.0, 5.0);
    // curX, curY should have shifted
    // Just verify no crash and values are finite
    EXPECT_TRUE(std::isfinite(state->getCurX()));
    EXPECT_TRUE(std::isfinite(state->getCurY()));
}

// ==================== Different DPI Values ====================

TEST_F(GfxStateTest_567, DifferentDPIValues_567) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState highDpiState(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 300.0);
}

TEST_F(GfxStateTest_567, AsymmetricDPI_567) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState asymState(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(asymState.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(asymState.getVDPI(), 300.0);
}

// ==================== Upside Down ====================

TEST_F(GfxStateTest_567, UpsideDownFalse_567) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState notFlipped(72.0, 72.0, &pageBox, 0, false);
    // Should construct without error
    EXPECT_DOUBLE_EQ(notFlipped.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(notFlipped.getPageHeight(), 792.0);
}

// ==================== Reusable Path Iterator ====================

TEST_F(GfxStateTest_567, GetReusablePathIterator_567) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// ==================== Multiple save/restore ====================

TEST_F(GfxStateTest_567, MultipleSaveRestore_567) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    s1->setLineWidth(2.0);
    GfxState *s2 = s1->save();
    s2->setLineWidth(3.0);
    
    EXPECT_DOUBLE_EQ(s2->getLineWidth(), 3.0);
    GfxState *r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);
    GfxState *r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getLineWidth(), 1.0);
}

// ==================== Clip operations ====================

TEST_F(GfxStateTest_567, ClipAfterPath_567) {
    state->moveTo(10.0, 10.0);
    state->lineTo(100.0, 10.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    state->clip();
    // After clip, the clip bbox should potentially change
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// ==================== Default Color Spaces ====================

TEST_F(GfxStateTest_567, CopyDefaultGrayColorSpaceNull_567) {
    auto cs = state->copyDefaultGrayColorSpace();
    // Initially might be null
    (void)cs;
}

TEST_F(GfxStateTest_567, CopyDefaultRGBColorSpaceNull_567) {
    auto cs = state->copyDefaultRGBColorSpace();
    (void)cs;
}

TEST_F(GfxStateTest_567, CopyDefaultCMYKColorSpaceNull_567) {
    auto cs = state->copyDefaultCMYKColorSpace();
    (void)cs;
}

// ==================== Edge case: Zero-size page ====================

TEST_F(GfxStateTest_567, ZeroSizePage_567) {
    PDFRectangle pageBox = makePageBox(0, 0, 0, 0);
    GfxState zeroState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(zeroState.getPageWidth(), 0.0);
    EXPECT_DOUBLE_EQ(zeroState.getPageHeight(), 0.0);
}

// ==================== Negative coordinates page ====================

TEST_F(GfxStateTest_567, NegativeCoordinatesPage_567) {
    PDFRectangle pageBox = makePageBox(-100, -100, 100, 100);
    GfxState negState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(negState.getPageWidth(), 200.0);
    EXPECT_DOUBLE_EQ(negState.getPageHeight(), 200.0);
}
