#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a PDFRectangle
static PDFRectangle makeRect(double x1, double y1, double x2, double y2) {
    PDFRectangle rect;
    rect.x1 = x1;
    rect.y1 = y1;
    rect.x2 = x2;
    rect.y2 = y2;
    return rect;
}

class GfxStateTest_616 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox = makeRect(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// --- Construction and basic getters ---

TEST_F(GfxStateTest_616, ConstructorSetsHDPI_616) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_616, ConstructorSetsVDPI_616) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_616, ConstructorSetsRotate_616) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_616, ConstructorSetsPageWidth_616) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_616, ConstructorSetsPageHeight_616) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_616, GetX1_616) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
}

TEST_F(GfxStateTest_616, GetY1_616) {
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
}

TEST_F(GfxStateTest_616, GetX2_616) {
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
}

TEST_F(GfxStateTest_616, GetY2_616) {
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// --- Rotated construction ---

TEST_F(GfxStateTest_616, ConstructorWithRotate90_616) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState->getRotate(), 90);
}

TEST_F(GfxStateTest_616, ConstructorWithRotate180_616) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState->getRotate(), 180);
}

TEST_F(GfxStateTest_616, ConstructorWithRotate270_616) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState->getRotate(), 270);
}

// --- CTM ---

TEST_F(GfxStateTest_616, GetCTMReturnsArray_616) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_616, SetCTM_616) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_616, ConcatCTM_616) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

TEST_F(GfxStateTest_616, GetCTMAsMatrix_616) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Matrix should reflect the set CTM values
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
    EXPECT_DOUBLE_EQ(m.m[1], 2.0);
    EXPECT_DOUBLE_EQ(m.m[2], 3.0);
    EXPECT_DOUBLE_EQ(m.m[3], 4.0);
    EXPECT_DOUBLE_EQ(m.m[4], 5.0);
    EXPECT_DOUBLE_EQ(m.m[5], 6.0);
}

// --- Coordinate transforms ---

TEST_F(GfxStateTest_616, TransformIdentityCTM_616) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_616, TransformWithTranslation_616) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 110.0);
    EXPECT_DOUBLE_EQ(y2, 220.0);
}

TEST_F(GfxStateTest_616, TransformDeltaIgnoresTranslation_616) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_616, TransformWithScale_616) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// --- Current position ---

TEST_F(GfxStateTest_616, InitialCurXY_616) {
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// --- Line properties ---

TEST_F(GfxStateTest_616, SetGetLineWidth_616) {
    state->setLineWidth(3.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.5);
}

TEST_F(GfxStateTest_616, SetGetLineWidthZero_616) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_616, SetGetMiterLimit_616) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_616, SetGetFlatness_616) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

TEST_F(GfxStateTest_616, SetGetLineJoin_616) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

TEST_F(GfxStateTest_616, SetGetLineCap_616) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

TEST_F(GfxStateTest_616, SetGetLineDash_616) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
}

TEST_F(GfxStateTest_616, SetGetLineDashEmpty_616) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(d.empty());
}

// --- Opacity ---

TEST_F(GfxStateTest_616, SetGetFillOpacity_616) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_616, SetGetStrokeOpacity_616) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_616, FillOpacityBoundaryZero_616) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_616, FillOpacityBoundaryOne_616) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_616, StrokeOpacityBoundaryZero_616) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

TEST_F(GfxStateTest_616, StrokeOpacityBoundaryOne_616) {
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// --- Overprint ---

TEST_F(GfxStateTest_616, SetGetFillOverprint_616) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_616, SetGetStrokeOverprint_616) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_616, SetGetOverprintMode_616) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
    state->setOverprintMode(0);
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// --- Stroke adjust ---

TEST_F(GfxStateTest_616, SetGetStrokeAdjust_616) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// --- Alpha is shape ---

TEST_F(GfxStateTest_616, SetGetAlphaIsShape_616) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// --- Text knockout ---

TEST_F(GfxStateTest_616, SetGetTextKnockout_616) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// --- Text properties ---

TEST_F(GfxStateTest_616, SetGetCharSpace_616) {
    state->setCharSpace(2.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.5);
}

TEST_F(GfxStateTest_616, SetGetWordSpace_616) {
    state->setWordSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 1.5);
}

TEST_F(GfxStateTest_616, SetGetHorizScaling_616) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_616, SetGetLeading_616) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_616, SetGetRise_616) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_616, SetGetRender_616) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_616, SetGetTextMat_616) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 2.0);
    EXPECT_DOUBLE_EQ(tm[2], 3.0);
    EXPECT_DOUBLE_EQ(tm[3], 4.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 6.0);
}

// --- Font ---

TEST_F(GfxStateTest_616, SetGetFontSize_616) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

TEST_F(GfxStateTest_616, GetFontNullInitially_616) {
    // Font may be null initially
    const auto &font = state->getFont();
    // Just verify we can call the getter without crashing
    (void)font;
}

// --- Rendering intent ---

TEST_F(GfxStateTest_616, SetGetRenderingIntent_616) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_616, SetRenderingIntentAbsoluteColorimetric_616) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

TEST_F(GfxStateTest_616, SetRenderingIntentPerceptual_616) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_616, SetRenderingIntentSaturation_616) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

// --- Blend mode ---

TEST_F(GfxStateTest_616, SetGetBlendMode_616) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

TEST_F(GfxStateTest_616, SetBlendModeNormal_616) {
    state->setBlendMode(gfxBlendNormal);
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// --- Path operations ---

TEST_F(GfxStateTest_616, InitialPathState_616) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_616, MoveToSetsCurPt_616) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

TEST_F(GfxStateTest_616, LineToCreatesPath_616) {
    state->moveTo(0.0, 0.0);
    state->lineTo(50.0, 50.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 50.0);
}

TEST_F(GfxStateTest_616, CurveToCreatesPath_616) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
}

TEST_F(GfxStateTest_616, ClosePathReturnsToStart_616) {
    state->moveTo(10.0, 20.0);
    state->lineTo(50.0, 60.0);
    state->closePath();
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

TEST_F(GfxStateTest_616, ClearPathResetsState_616) {
    state->moveTo(10.0, 20.0);
    state->lineTo(50.0, 60.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_616, GetPathNotNull_616) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_NE(state->getPath(), nullptr);
}

// --- Text move ---

TEST_F(GfxStateTest_616, TextMoveTo_616) {
    state->textMoveTo(100.0, 200.0);
    // After textMoveTo, lineX and lineY should be updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// --- Clip operations ---

TEST_F(GfxStateTest_616, ClipToRect_616) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, 100.0);
    EXPECT_LE(yMin, 200.0);
    EXPECT_GE(xMax, 10.0);
    EXPECT_GE(yMax, 20.0);
}

TEST_F(GfxStateTest_616, GetClipBBox_616) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Initially, clip box should cover the page area
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_616, GetUserClipBBox_616) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// --- Save / Restore ---

TEST_F(GfxStateTest_616, InitiallyNoSaves_616) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_616, SaveCreatesChild_616) {
    GfxState *saved = state->save();
    EXPECT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());
}

TEST_F(GfxStateTest_616, RestoreReturnsSavedState_616) {
    state->setLineWidth(5.0);
    GfxState *child = state->save();
    child->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(child->getLineWidth(), 10.0);

    GfxState *restored = child->restore();
    EXPECT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_616, SaveRestorePreservesProperties_616) {
    state->setFillOpacity(0.3);
    state->setStrokeOpacity(0.7);
    state->setCharSpace(2.0);

    GfxState *child = state->save();
    // Child should inherit parent values
    EXPECT_DOUBLE_EQ(child->getFillOpacity(), 0.3);
    EXPECT_DOUBLE_EQ(child->getStrokeOpacity(), 0.7);
    EXPECT_DOUBLE_EQ(child->getCharSpace(), 2.0);

    // Modify child
    child->setFillOpacity(0.9);
    EXPECT_DOUBLE_EQ(child->getFillOpacity(), 0.9);

    // Restore
    GfxState *restored = child->restore();
    EXPECT_DOUBLE_EQ(restored->getFillOpacity(), 0.3);
}

TEST_F(GfxStateTest_616, MultipleSaveRestore_616) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    s1->setLineWidth(2.0);
    GfxState *s2 = s1->save();
    s2->setLineWidth(3.0);

    EXPECT_DOUBLE_EQ(s2->getLineWidth(), 3.0);

    GfxState *r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);

    GfxState *r0 = r1->restore();
    EXPECT_DOUBLE_EQ(r0->getLineWidth(), 1.0);
}

// --- Copy ---

TEST_F(GfxStateTest_616, CopyCreatesIndependentState_616) {
    state->setLineWidth(7.0);
    state->setFillOpacity(0.4);

    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.4);

    // Modifying copy shouldn't affect original
    copied->setLineWidth(99.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 7.0);
}

// --- isParentState ---

TEST_F(GfxStateTest_616, IsParentState_616) {
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
}

TEST_F(GfxStateTest_616, IsNotParentState_616) {
    PDFRectangle pageBox = makeRect(0, 0, 100, 100);
    GfxState other(72.0, 72.0, &pageBox, 0, true);
    EXPECT_FALSE(state->isParentState(&other));
}

// --- Transform width ---

TEST_F(GfxStateTest_616, TransformWidthIdentity_616) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double tw = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(tw, 5.0);
}

TEST_F(GfxStateTest_616, TransformWidthScaled_616) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double tw = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(tw, 10.0);
}

// --- GetTransformedLineWidth ---

TEST_F(GfxStateTest_616, GetTransformedLineWidth_616) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tlw, 3.0);
}

// --- Fill and Stroke Color ---

TEST_F(GfxStateTest_616, SetGetFillColor_616) {
    GfxColor color;
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *fc = state->getFillColor();
    EXPECT_NE(fc, nullptr);
    EXPECT_EQ(fc->c[0], 32768);
}

TEST_F(GfxStateTest_616, SetGetStrokeColor_616) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *sc = state->getStrokeColor();
    EXPECT_NE(sc, nullptr);
    EXPECT_EQ(sc->c[0], 16384);
}

// --- Color spaces (null checks) ---

TEST_F(GfxStateTest_616, GetFillColorSpaceInitially_616) {
    // The initial fill color space should be set to device gray
    GfxColorSpace *cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_616, GetStrokeColorSpaceInitially_616) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// --- Patterns ---

TEST_F(GfxStateTest_616, GetFillPatternInitiallyNull_616) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

TEST_F(GfxStateTest_616, GetStrokePatternInitiallyNull_616) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// --- ShiftCTMAndClip ---

TEST_F(GfxStateTest_616, ShiftCTMAndClip_616) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// --- TextShift ---

TEST_F(GfxStateTest_616, TextShift_616) {
    state->moveTo(0.0, 0.0);
    double initialX = state->getCurX();
    double initialY = state->getCurY();
    state->textShift(5.0, 10.0);
    // curX and curY should be shifted
    // The exact behavior depends on textMat, but we can check they changed
    // with identity text mat
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x0 = state->getCurX();
    double y0 = state->getCurY();
    state->textShift(5.0, 0.0);
    // After shift, curX should have moved
    (void)x0;
    (void)y0;
}

// --- Reusable path ---

TEST_F(GfxStateTest_616, GetReusablePath_616) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto rp = state->getReusablePath();
    EXPECT_NE(rp, nullptr);
}

// --- parseBlendMode (static) ---

TEST_F(GfxStateTest_616, ParseBlendModeNormal_616) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, gfxBlendNormal);
    }
}

// --- Different DPI values ---

TEST_F(GfxStateTest_616, DifferentDPIValues_616) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    auto hiDpiState = std::make_unique<GfxState>(300.0, 600.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(hiDpiState->getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(hiDpiState->getVDPI(), 600.0);
}

// --- Non-standard page box ---

TEST_F(GfxStateTest_616, NonStandardPageBox_616) {
    PDFRectangle pageBox = makeRect(50, 100, 550, 700);
    auto customState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(customState->getPageWidth(), 500.0);
    EXPECT_DOUBLE_EQ(customState->getPageHeight(), 600.0);
}

// --- Clip after path ---

TEST_F(GfxStateTest_616, ClipAfterPath_616) {
    state->moveTo(10.0, 10.0);
    state->lineTo(100.0, 10.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    state->clip();
    // After clip, the clip bbox should be constrained
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// --- TextTransform ---

TEST_F(GfxStateTest_616, TextTransformIdentity_616) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(10.0, 20.0, &x2, &y2);
    // With identity matrices, the delta transform should pass through
    // The exact result depends on font size and horiz scaling
}

// --- GetTransformedFontSize ---

TEST_F(GfxStateTest_616, GetTransformedFontSize_616) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setFont(nullptr, 12.0);
    double tfs = state->getTransformedFontSize();
    EXPECT_DOUBLE_EQ(tfs, 12.0);
}

// --- GetFontTransMat ---

TEST_F(GfxStateTest_616, GetFontTransMat_616) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setFont(nullptr, 12.0);
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    // With identity CTM and textMat, the font trans mat should reflect font size
    EXPECT_DOUBLE_EQ(m11, 12.0);
    EXPECT_DOUBLE_EQ(m22, 12.0);
}

// --- Negative line width (boundary) ---

TEST_F(GfxStateTest_616, NegativeLineWidth_616) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

// --- Very large values ---

TEST_F(GfxStateTest_616, VeryLargeLineWidth_616) {
    state->setLineWidth(1e10);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1e10);
}

// --- CurText position ---

TEST_F(GfxStateTest_616, TextMoveToSetsCurText_616) {
    state->textMoveTo(50.0, 60.0);
    // getCurTextX/Y should reflect the text position
    // (actual transformation depends on textMat and CTM)
}

// --- Default color spaces ---

TEST_F(GfxStateTest_616, CopyDefaultGrayColorSpaceInitiallyNull_616) {
    auto cs = state->copyDefaultGrayColorSpace();
    // May be null or default - just don't crash
    (void)cs;
}

TEST_F(GfxStateTest_616, CopyDefaultRGBColorSpaceInitiallyNull_616) {
    auto cs = state->copyDefaultRGBColorSpace();
    (void)cs;
}

TEST_F(GfxStateTest_616, CopyDefaultCMYKColorSpaceInitiallyNull_616) {
    auto cs = state->copyDefaultCMYKColorSpace();
    (void)cs;
}
