#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"

// Helper to create a GfxState with reasonable defaults
class GfxStateTest_634 : public ::testing::Test {
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

// --- Normal Operation Tests ---

TEST_F(GfxStateTest_634, ConstructorSetsHDPI_634) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_634, ConstructorSetsVDPI_634) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_634, ConstructorSetsRotate_634) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_634, ConstructorSetsPageDimensions_634) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_634, GetX1Y1X2Y2_634) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

TEST_F(GfxStateTest_634, SetAndGetStrokeOpacity_634) {
    state->setStrokeOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.5);
}

TEST_F(GfxStateTest_634, SetAndGetFillOpacity_634) {
    state->setFillOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.75);
}

TEST_F(GfxStateTest_634, SetAndGetLineWidth_634) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_634, SetAndGetFlatness_634) {
    state->setFlatness(10);
    EXPECT_EQ(state->getFlatness(), 10);
}

TEST_F(GfxStateTest_634, SetAndGetLineJoin_634) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_634, SetAndGetLineCap_634) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

TEST_F(GfxStateTest_634, SetAndGetMiterLimit_634) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

TEST_F(GfxStateTest_634, SetAndGetCharSpace_634) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_634, SetAndGetWordSpace_634) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_634, SetAndGetHorizScaling_634) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_634, SetAndGetLeading_634) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_634, SetAndGetRise_634) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_634, SetAndGetRender_634) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_634, SetAndGetFillOverprint_634) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_634, SetAndGetStrokeOverprint_634) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_634, SetAndGetOverprintMode_634) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

TEST_F(GfxStateTest_634, SetAndGetStrokeAdjust_634) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_634, SetAndGetAlphaIsShape_634) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_634, SetAndGetTextKnockout_634) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_634, SetAndGetBlendMode_634) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

TEST_F(GfxStateTest_634, SetAndGetRenderingIntent_634) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_634, SetCTM_634) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_634, SetTextMat_634) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 5.0, 10.0);
    const auto &textMat = state->getTextMat();
    EXPECT_DOUBLE_EQ(textMat[0], 1.0);
    EXPECT_DOUBLE_EQ(textMat[1], 0.0);
    EXPECT_DOUBLE_EQ(textMat[2], 0.0);
    EXPECT_DOUBLE_EQ(textMat[3], 1.0);
    EXPECT_DOUBLE_EQ(textMat[4], 5.0);
    EXPECT_DOUBLE_EQ(textMat[5], 10.0);
}

// --- Path Operations ---

TEST_F(GfxStateTest_634, InitiallyNoPath_634) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_634, MoveToSetsCurPt_634) {
    state->moveTo(100.0, 200.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_634, LineToCreatesPath_634) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_634, CurveToCreatesPath_634) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_634, ClearPathResetsState_634) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_634, ClosePathDoesNotCrash_634) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// --- Save/Restore ---

TEST_F(GfxStateTest_634, SaveReturnsNewState_634) {
    GfxState *saved = state->save();
    EXPECT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());
}

TEST_F(GfxStateTest_634, RestoreReturnsPreviousState_634) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 10.0);
    GfxState *restored = saved->restore();
    EXPECT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_634, HasSavesInitiallyFalse_634) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_634, IsParentState_634) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->isParentState(state.get()));
}

// --- Transform ---

TEST_F(GfxStateTest_634, TransformIdentityCTM_634) {
    // After construction with identity-like CTM, transform should produce predictable results
    double x2, y2;
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_634, TransformDeltaIdentityCTM_634) {
    double x2, y2;
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->transformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

TEST_F(GfxStateTest_634, TransformWithScaling_634) {
    double x2, y2;
    state->setCTM(2.0, 0.0, 0.0, 3.0, 10.0, 20.0);
    state->transform(1.0, 1.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 12.0);
    EXPECT_DOUBLE_EQ(y2, 23.0);
}

TEST_F(GfxStateTest_634, TransformWidth_634) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_GT(w, 0.0);
}

// --- ConcatCTM ---

TEST_F(GfxStateTest_634, ConcatCTMUpdatesTransform_634) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 5.0);
    double x2, y2;
    state->transform(1.0, 1.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 7.0);
    EXPECT_DOUBLE_EQ(y2, 7.0);
}

// --- Clip ---

TEST_F(GfxStateTest_634, ClipToRectUpdatesClipBBox_634) {
    state->clipToRect(10.0, 20.0, 300.0, 400.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, 300.0);
    EXPECT_LE(yMin, 400.0);
    EXPECT_GE(xMax, 10.0);
    EXPECT_GE(yMax, 20.0);
}

TEST_F(GfxStateTest_634, GetUserClipBBox_634) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should return valid values without crashing
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// --- Boundary Conditions ---

TEST_F(GfxStateTest_634, SetStrokeOpacityZero_634) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

TEST_F(GfxStateTest_634, SetStrokeOpacityOne_634) {
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_634, SetFillOpacityZero_634) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_634, SetFillOpacityOne_634) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_634, SetLineWidthZero_634) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_634, SetLineWidthLarge_634) {
    state->setLineWidth(1000.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1000.0);
}

TEST_F(GfxStateTest_634, SetFlatnessBoundary_634) {
    state->setFlatness(0);
    EXPECT_EQ(state->getFlatness(), 0);
    state->setFlatness(100);
    EXPECT_EQ(state->getFlatness(), 100);
}

TEST_F(GfxStateTest_634, SetRenderingIntentLongString_634) {
    // Rendering intent is stored in a 32-char buffer
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_634, SetRenderingIntentAbsoluteColorimetric_634) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

TEST_F(GfxStateTest_634, SetRenderingIntentSaturation_634) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

// --- LineDash ---

TEST_F(GfxStateTest_634, SetLineDashEmpty_634) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_TRUE(d.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

TEST_F(GfxStateTest_634, SetLineDashWithValues_634) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 2.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

// --- Text operations ---

TEST_F(GfxStateTest_634, TextMoveTo_634) {
    state->textMoveTo(100.0, 200.0);
    // After textMoveTo, lineX and lineY should be updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// --- Copy ---

TEST_F(GfxStateTest_634, CopyCreatesIndependentState_634) {
    state->setLineWidth(3.0);
    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_NE(copied.get(), state.get());
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    copied->setLineWidth(7.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.0);
}

// --- Font ---

TEST_F(GfxStateTest_634, InitialFontIsNull_634) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

TEST_F(GfxStateTest_634, SetFontWithNullptr_634) {
    state->setFont(nullptr, 12.0);
    EXPECT_EQ(state->getFont(), nullptr);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

// --- Color patterns ---

TEST_F(GfxStateTest_634, InitialFillPatternIsNull_634) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

TEST_F(GfxStateTest_634, InitialStrokePatternIsNull_634) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// --- Multiple save/restore ---

TEST_F(GfxStateTest_634, MultipleSaveRestore_634) {
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

// --- Rotated page ---

TEST_F(GfxStateTest_634, ConstructorWithRotation_634) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// --- Different DPI ---

TEST_F(GfxStateTest_634, ConstructorWithDifferentDPI_634) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState highDpiState(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 300.0);
}

// --- ShiftCTMAndClip ---

TEST_F(GfxStateTest_634, ShiftCTMAndClipDoesNotCrash_634) {
    state->shiftCTMAndClip(10.0, 20.0);
    // Verify CTM was modified
    const auto &ctm = state->getCTM();
    // Just verify no crash and values are valid
    EXPECT_TRUE(std::isfinite(ctm[4]));
    EXPECT_TRUE(std::isfinite(ctm[5]));
}

// --- GetCTM with Matrix ---

TEST_F(GfxStateTest_634, GetCTMAsMatrix_634) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Verify the matrix was populated (at minimum, no crash)
    EXPECT_TRUE(std::isfinite(m.m[0]));
}

// --- GetTransformedLineWidth ---

TEST_F(GfxStateTest_634, GetTransformedLineWidth_634) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_GT(tw, 0.0);
}

// --- GetTransformedFontSize ---

TEST_F(GfxStateTest_634, GetTransformedFontSize_634) {
    state->setFont(nullptr, 12.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double fs = state->getTransformedFontSize();
    EXPECT_GE(fs, 0.0);
}

// --- GetFontTransMat ---

TEST_F(GfxStateTest_634, GetFontTransMat_634) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setFont(nullptr, 12.0);
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    EXPECT_TRUE(std::isfinite(m11));
    EXPECT_TRUE(std::isfinite(m12));
    EXPECT_TRUE(std::isfinite(m21));
    EXPECT_TRUE(std::isfinite(m22));
}

// --- TextTransform ---

TEST_F(GfxStateTest_634, TextTransformIdentity_634) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(10.0, 20.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

TEST_F(GfxStateTest_634, TextTransformDelta_634) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// --- Clip with path ---

TEST_F(GfxStateTest_634, ClipAfterPath_634) {
    state->moveTo(10.0, 10.0);
    state->lineTo(200.0, 10.0);
    state->lineTo(200.0, 200.0);
    state->closePath();
    state->clip();
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// --- ClipToStrokePath ---

TEST_F(GfxStateTest_634, ClipToStrokePathAfterPath_634) {
    state->moveTo(10.0, 10.0);
    state->lineTo(200.0, 10.0);
    state->lineTo(200.0, 200.0);
    state->closePath();
    state->clipToStrokePath();
    // Should not crash
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
}

// --- Reusable path iterator ---

TEST_F(GfxStateTest_634, GetReusablePathNoPath_634) {
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

TEST_F(GfxStateTest_634, GetReusablePathWithPath_634) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// --- BlendMode default ---

TEST_F(GfxStateTest_634, DefaultBlendModeIsNormal_634) {
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

// --- FillColor / StrokeColor ---

TEST_F(GfxStateTest_634, SetAndGetFillColor_634) {
    GfxColor color;
    color.c[0] = 32768;
    state->setFillColor(&color);
    const GfxColor *fc = state->getFillColor();
    EXPECT_NE(fc, nullptr);
    EXPECT_EQ(fc->c[0], 32768);
}

TEST_F(GfxStateTest_634, SetAndGetStrokeColor_634) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *sc = state->getStrokeColor();
    EXPECT_NE(sc, nullptr);
    EXPECT_EQ(sc->c[0], 16384);
}

// --- Negative values ---

TEST_F(GfxStateTest_634, SetNegativeCharSpace_634) {
    state->setCharSpace(-1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), -1.5);
}

TEST_F(GfxStateTest_634, SetNegativeWordSpace_634) {
    state->setWordSpace(-0.5);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), -0.5);
}

TEST_F(GfxStateTest_634, SetNegativeRise_634) {
    state->setRise(-5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), -5.0);
}

// --- TextShift ---

TEST_F(GfxStateTest_634, TextShiftDoesNotCrash_634) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->textShift(5.0, 10.0);
    // No crash expected; verify curTextX/curTextY updated
    EXPECT_TRUE(std::isfinite(state->getCurTextX()));
    EXPECT_TRUE(std::isfinite(state->getCurTextY()));
}

// --- GetPath ---

TEST_F(GfxStateTest_634, GetPathNotNull_634) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}
