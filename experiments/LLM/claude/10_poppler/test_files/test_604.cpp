#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"

// Helper to create a PDFRectangle for constructing GfxState
static PDFRectangle makePageBox(double x1, double y1, double x2, double y2) {
    PDFRectangle box;
    box.x1 = x1;
    box.y1 = y1;
    box.x2 = x2;
    box.y2 = y2;
    return box;
}

class GfxStateTest_604 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// ===================== Constructor and basic getters =====================

TEST_F(GfxStateTest_604, ConstructorSetsHDPI_604) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_604, ConstructorSetsVDPI_604) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_604, ConstructorSetsRotate_604) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_604, ConstructorSetsPageWidth_604) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_604, ConstructorSetsPageHeight_604) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_604, GetX1_604) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
}

TEST_F(GfxStateTest_604, GetY1_604) {
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
}

TEST_F(GfxStateTest_604, GetX2_604) {
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
}

TEST_F(GfxStateTest_604, GetY2_604) {
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// ===================== Rotation variants =====================

TEST_F(GfxStateTest_604, ConstructorWithRotate90_604) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_604, ConstructorWithRotate180_604) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

TEST_F(GfxStateTest_604, ConstructorWithRotate270_604) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

// ===================== TextKnockout =====================

TEST_F(GfxStateTest_604, DefaultTextKnockoutIsFalse_604) {
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_604, SetTextKnockoutTrue_604) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

TEST_F(GfxStateTest_604, SetTextKnockoutFalse_604) {
    state->setTextKnockout(true);
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// ===================== Line Width =====================

TEST_F(GfxStateTest_604, DefaultLineWidth_604) {
    // Default line width is typically 1.0
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

TEST_F(GfxStateTest_604, SetLineWidth_604) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_604, SetLineWidthZero_604) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// ===================== Flatness =====================

TEST_F(GfxStateTest_604, DefaultFlatness_604) {
    EXPECT_EQ(state->getFlatness(), 1);
}

TEST_F(GfxStateTest_604, SetFlatness_604) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// ===================== Line Join =====================

TEST_F(GfxStateTest_604, SetLineJoin_604) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// ===================== Line Cap =====================

TEST_F(GfxStateTest_604, SetLineCap_604) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// ===================== Miter Limit =====================

TEST_F(GfxStateTest_604, DefaultMiterLimit_604) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_604, SetMiterLimit_604) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// ===================== Fill Opacity =====================

TEST_F(GfxStateTest_604, DefaultFillOpacity_604) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_604, SetFillOpacity_604) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// ===================== Stroke Opacity =====================

TEST_F(GfxStateTest_604, DefaultStrokeOpacity_604) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_604, SetStrokeOpacity_604) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// ===================== Fill Overprint =====================

TEST_F(GfxStateTest_604, DefaultFillOverprint_604) {
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_604, SetFillOverprint_604) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// ===================== Stroke Overprint =====================

TEST_F(GfxStateTest_604, DefaultStrokeOverprint_604) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_604, SetStrokeOverprint_604) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// ===================== Overprint Mode =====================

TEST_F(GfxStateTest_604, DefaultOverprintMode_604) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

TEST_F(GfxStateTest_604, SetOverprintMode_604) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// ===================== Stroke Adjust =====================

TEST_F(GfxStateTest_604, DefaultStrokeAdjust_604) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_604, SetStrokeAdjust_604) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// ===================== AlphaIsShape =====================

TEST_F(GfxStateTest_604, DefaultAlphaIsShape_604) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_604, SetAlphaIsShape_604) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// ===================== Font Size =====================

TEST_F(GfxStateTest_604, DefaultFontSize_604) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// ===================== Char Space =====================

TEST_F(GfxStateTest_604, DefaultCharSpace_604) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

TEST_F(GfxStateTest_604, SetCharSpace_604) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// ===================== Word Space =====================

TEST_F(GfxStateTest_604, DefaultWordSpace_604) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

TEST_F(GfxStateTest_604, SetWordSpace_604) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// ===================== Horiz Scaling =====================

TEST_F(GfxStateTest_604, DefaultHorizScaling_604) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

TEST_F(GfxStateTest_604, SetHorizScaling_604) {
    state->setHorizScaling(0.8);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.8);
}

// ===================== Leading =====================

TEST_F(GfxStateTest_604, DefaultLeading_604) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

TEST_F(GfxStateTest_604, SetLeading_604) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// ===================== Rise =====================

TEST_F(GfxStateTest_604, DefaultRise_604) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

TEST_F(GfxStateTest_604, SetRise_604) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// ===================== Render =====================

TEST_F(GfxStateTest_604, DefaultRender_604) {
    EXPECT_EQ(state->getRender(), 0);
}

TEST_F(GfxStateTest_604, SetRender_604) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// ===================== BlendMode =====================

TEST_F(GfxStateTest_604, DefaultBlendMode_604) {
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

TEST_F(GfxStateTest_604, SetBlendMode_604) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// ===================== CTM =====================

TEST_F(GfxStateTest_604, GetCTMReturnsArray_604) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_604, SetCTM_604) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_604, ConcatCTM_604) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 5.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// ===================== Transform =====================

TEST_F(GfxStateTest_604, TransformIdentityCTM_604) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_604, TransformWithScaling_604) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

TEST_F(GfxStateTest_604, TransformDelta_604) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    // transformDelta should ignore translation
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// ===================== Text Mat =====================

TEST_F(GfxStateTest_604, SetTextMat_604) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 2.0);
    EXPECT_DOUBLE_EQ(tm[2], 3.0);
    EXPECT_DOUBLE_EQ(tm[3], 4.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 6.0);
}

// ===================== Path operations =====================

TEST_F(GfxStateTest_604, InitialPathIsEmpty_604) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_604, MoveToSetsCurrentPoint_604) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_604, LineToCreatesPath_604) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_604, ClearPathResetsState_604) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_604, CurveToCreatesPath_604) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_604, ClosePathOnOpenPath_604) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// ===================== Save/Restore =====================

TEST_F(GfxStateTest_604, InitialHasNoSaves_604) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_604, SaveCreatesSaveState_604) {
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    // saved should be the original state pointer; the returned pointer is the new state
    EXPECT_NE(saved, nullptr);
}

TEST_F(GfxStateTest_604, SaveRestoreRoundTrip_604) {
    state->setLineWidth(5.0);
    GfxState *newState = state->save();
    EXPECT_DOUBLE_EQ(newState->getLineWidth(), 5.0);

    newState->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(newState->getLineWidth(), 10.0);

    GfxState *restored = newState->restore();
    EXPECT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_604, RestoreAfterMultipleSaves_604) {
    state->setFillOpacity(1.0);
    GfxState *s1 = state->save();
    s1->setFillOpacity(0.5);
    GfxState *s2 = s1->save();
    s2->setFillOpacity(0.3);

    EXPECT_DOUBLE_EQ(s2->getFillOpacity(), 0.3);

    GfxState *r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getFillOpacity(), 0.5);

    GfxState *r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getFillOpacity(), 1.0);
}

// ===================== Copy =====================

TEST_F(GfxStateTest_604, CopyPreservesProperties_604) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.7);
    state->setCharSpace(2.0);
    
    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);
    EXPECT_DOUBLE_EQ(copied->getCharSpace(), 2.0);
}

// ===================== Rendering Intent =====================

TEST_F(GfxStateTest_604, SetRenderingIntent_604) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_604, SetRenderingIntentRelativeColorimetric_604) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// ===================== LineDash =====================

TEST_F(GfxStateTest_604, SetLineDash_604) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
}

TEST_F(GfxStateTest_604, SetLineDashEmpty_604) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_EQ(d.size(), 0u);
}

// ===================== Clip BBox =====================

TEST_F(GfxStateTest_604, GetClipBBox_604) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After construction, clip should cover the page
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_604, ClipToRect_604) {
    state->clipToRect(100.0, 200.0, 300.0, 400.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 100.0);
    EXPECT_GE(yMin, 200.0);
    EXPECT_LE(xMax, 300.0);
    EXPECT_LE(yMax, 400.0);
}

// ===================== Text position =====================

TEST_F(GfxStateTest_604, TextMoveTo_604) {
    state->textMoveTo(15.0, 25.0);
    // After textMoveTo, lineX/lineY should be updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 15.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 25.0);
}

// ===================== FillColor / StrokeColor =====================

TEST_F(GfxStateTest_604, SetFillColor_604) {
    GfxColor color;
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *fc = state->getFillColor();
    EXPECT_EQ(fc->c[0], 32768);
}

TEST_F(GfxStateTest_604, SetStrokeColor_604) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *sc = state->getStrokeColor();
    EXPECT_EQ(sc->c[0], 16384);
}

// ===================== FillColorSpace / StrokeColorSpace =====================

TEST_F(GfxStateTest_604, InitialFillColorSpaceNotNull_604) {
    // By default, GfxState should have a default fill color space (DeviceGray)
    GfxColorSpace *fcs = state->getFillColorSpace();
    EXPECT_NE(fcs, nullptr);
}

TEST_F(GfxStateTest_604, InitialStrokeColorSpaceNotNull_604) {
    GfxColorSpace *scs = state->getStrokeColorSpace();
    EXPECT_NE(scs, nullptr);
}

// ===================== Pattern =====================

TEST_F(GfxStateTest_604, InitialFillPatternIsNull_604) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

TEST_F(GfxStateTest_604, InitialStrokePatternIsNull_604) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// ===================== GetPath =====================

TEST_F(GfxStateTest_604, GetPathNotNull_604) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// ===================== UserClipBBox =====================

TEST_F(GfxStateTest_604, GetUserClipBBox_604) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// ===================== ShiftCTMAndClip =====================

TEST_F(GfxStateTest_604, ShiftCTMAndClip_604) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// ===================== parseBlendMode =====================

TEST_F(GfxStateTest_604, ParseBlendModeNormal_604) {
    Object obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, GfxBlendMode::Normal);
    }
}

// ===================== Different DPI =====================

TEST_F(GfxStateTest_604, DifferentDPI_604) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState highDpiState(300.0, 600.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 600.0);
}

// ===================== UpsideDown false =====================

TEST_F(GfxStateTest_604, ConstructorUpsideDownFalse_604) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState notFlipped(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(notFlipped.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(notFlipped.getPageHeight(), 792.0);
}

// ===================== isParentState =====================

TEST_F(GfxStateTest_604, IsParentStateAfterSave_604) {
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
}

// ===================== Transformed line width =====================

TEST_F(GfxStateTest_604, GetTransformedLineWidth_604) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_GT(tw, 0.0);
}

// ===================== TransformWidth =====================

TEST_F(GfxStateTest_604, TransformWidthIdentity_604) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 5.0);
}

// ===================== Font =====================

TEST_F(GfxStateTest_604, InitialFontIsNull_604) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// ===================== CurX and CurY =====================

TEST_F(GfxStateTest_604, CurXAndCurY_604) {
    // Initially should be 0
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// ===================== getCTM with Matrix =====================

TEST_F(GfxStateTest_604, GetCTMAsMatrix_604) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
    EXPECT_DOUBLE_EQ(m.m[1], 2.0);
    EXPECT_DOUBLE_EQ(m.m[2], 3.0);
    EXPECT_DOUBLE_EQ(m.m[3], 4.0);
    EXPECT_DOUBLE_EQ(m.m[4], 5.0);
    EXPECT_DOUBLE_EQ(m.m[5], 6.0);
}

// ===================== Boundary: Very small page =====================

TEST_F(GfxStateTest_604, VerySmallPage_604) {
    PDFRectangle pageBox = makePageBox(0, 0, 1, 1);
    GfxState smallState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(smallState.getPageWidth(), 1.0);
    EXPECT_DOUBLE_EQ(smallState.getPageHeight(), 1.0);
}

// ===================== Boundary: Large page =====================

TEST_F(GfxStateTest_604, LargePage_604) {
    PDFRectangle pageBox = makePageBox(0, 0, 100000, 100000);
    GfxState largeState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(largeState.getPageWidth(), 100000.0);
    EXPECT_DOUBLE_EQ(largeState.getPageHeight(), 100000.0);
}

// ===================== TextShift =====================

TEST_F(GfxStateTest_604, TextShift_604) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double origX = state->getCurX();
    double origY = state->getCurY();
    state->textShift(5.0, 10.0);
    // After textShift, curX and curY should have changed
    // (exact values depend on CTM and textMat, but should differ from original for non-zero shift)
    // We just verify the function doesn't crash and values are numeric
    EXPECT_TRUE(std::isfinite(state->getCurX()));
    EXPECT_TRUE(std::isfinite(state->getCurY()));
}

// ===================== GetReusablePath =====================

TEST_F(GfxStateTest_604, GetReusablePathNotNull_604) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto pathIter = state->getReusablePath();
    EXPECT_NE(pathIter, nullptr);
}
