#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a PDFRectangle
static PDFRectangle makePageBox(double x1, double y1, double x2, double y2) {
    PDFRectangle box;
    box.x1 = x1;
    box.y1 = y1;
    box.x2 = x2;
    box.y2 = y2;
    return box;
}

class GfxStateTest_654 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// ===================== Constructor / Basic Getters =====================

TEST_F(GfxStateTest_654, ConstructorSetsHDPI_654) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_654, ConstructorSetsVDPI_654) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_654, ConstructorSetsRotate_654) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_654, ConstructorSetsPageDimensions_654) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_654, GetX1Y1X2Y2_654) {
    // The coordinates depend on the page box and rotation
    // Just verify they return reasonable values
    double x1 = state->getX1();
    double y1 = state->getY1();
    double x2 = state->getX2();
    double y2 = state->getY2();
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

TEST_F(GfxStateTest_654, ConstructorWithRotation_654) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_654, ConstructorWithUpsideDownFalse_654) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState st(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(st.getHDPI(), 72.0);
}

// ===================== CTM =====================

TEST_F(GfxStateTest_654, GetCTMReturnsArray_654) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_654, SetCTM_654) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_654, ConcatCTM_654) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

TEST_F(GfxStateTest_654, GetCTMAsMatrix_654) {
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

// ===================== Transform =====================

TEST_F(GfxStateTest_654, TransformIdentity_654) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

TEST_F(GfxStateTest_654, TransformWithTranslation_654) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 105.0);
    EXPECT_DOUBLE_EQ(y2, 210.0);
}

TEST_F(GfxStateTest_654, TransformWithScaling_654) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

TEST_F(GfxStateTest_654, TransformDelta_654) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double dx2, dy2;
    state->transformDelta(5.0, 10.0, &dx2, &dy2);
    // transformDelta should not include translation
    EXPECT_DOUBLE_EQ(dx2, 10.0);
    EXPECT_DOUBLE_EQ(dy2, 20.0);
}

// ===================== Line Properties =====================

TEST_F(GfxStateTest_654, SetAndGetLineWidth_654) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_654, SetAndGetLineJoin_654) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_654, SetAndGetLineCap_654) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

TEST_F(GfxStateTest_654, SetAndGetMiterLimit_654) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

TEST_F(GfxStateTest_654, SetAndGetFlatness_654) {
    state->setFlatness(2);
    EXPECT_EQ(state->getFlatness(), 2);
}

TEST_F(GfxStateTest_654, SetAndGetLineDash_654) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
}

TEST_F(GfxStateTest_654, SetEmptyLineDash_654) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_EQ(d.size(), 0u);
}

// ===================== Opacity and Blend =====================

TEST_F(GfxStateTest_654, SetAndGetFillOpacity_654) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_654, SetAndGetStrokeOpacity_654) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_654, SetAndGetBlendMode_654) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// ===================== Overprint =====================

TEST_F(GfxStateTest_654, SetAndGetFillOverprint_654) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_654, SetAndGetStrokeOverprint_654) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_654, SetAndGetOverprintMode_654) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// ===================== Text Properties =====================

TEST_F(GfxStateTest_654, SetAndGetCharSpace_654) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_654, SetAndGetWordSpace_654) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_654, SetAndGetHorizScaling_654) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_654, SetAndGetLeading_654) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_654, SetAndGetRise_654) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_654, SetAndGetRender_654) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_654, SetAndGetTextMat_654) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 2.0);
    EXPECT_DOUBLE_EQ(tm[2], 3.0);
    EXPECT_DOUBLE_EQ(tm[3], 4.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 6.0);
}

// ===================== Stroke Adjust / AlphaIsShape / TextKnockout =====================

TEST_F(GfxStateTest_654, SetAndGetStrokeAdjust_654) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_654, SetAndGetAlphaIsShape_654) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_654, SetAndGetTextKnockout_654) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// ===================== Rendering Intent =====================

TEST_F(GfxStateTest_654, SetAndGetRenderingIntent_654) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_654, SetRenderingIntentLongString_654) {
    // The internal buffer is char[32], so test boundary
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// ===================== Path Operations =====================

TEST_F(GfxStateTest_654, InitiallyNoPath_654) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_654, MoveToSetsCurPt_654) {
    state->clearPath();
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_654, LineToCreatesPath_654) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_654, CurveToCreatesPath_654) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_654, ClosePathOnPath_654) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_654, ClearPathRemovesPath_654) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_654, GetPathReturnsNonNull_654) {
    state->moveTo(0.0, 0.0);
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// ===================== Save / Restore =====================

TEST_F(GfxStateTest_654, SaveReturnsNewState_654) {
    GfxState *saved = state->save();
    EXPECT_NE(saved, nullptr);
    // saved should be the new state on top of the stack
    // The returned pointer is the new current state
}

TEST_F(GfxStateTest_654, HasSavesAfterSave_654) {
    GfxState *newState = state->save();
    EXPECT_TRUE(newState->hasSaves());
}

TEST_F(GfxStateTest_654, RestoreReturnsParentState_654) {
    GfxState *newState = state->save();
    GfxState *restored = newState->restore();
    EXPECT_NE(restored, nullptr);
}

TEST_F(GfxStateTest_654, SavePreservesLineWidth_654) {
    state->setLineWidth(5.0);
    GfxState *newState = state->save();
    EXPECT_DOUBLE_EQ(newState->getLineWidth(), 5.0);
    // Modify newState
    newState->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(newState->getLineWidth(), 10.0);
    // Restore
    GfxState *restored = newState->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_654, InitialStateHasNoSaves_654) {
    EXPECT_FALSE(state->hasSaves());
}

// ===================== Clip =====================

TEST_F(GfxStateTest_654, ClipBBox_654) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should return some valid clip bbox
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_654, UserClipBBox_654) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_654, ClipToRect_654) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the clip bbox should be constrained
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// ===================== Text Position =====================

TEST_F(GfxStateTest_654, TextMoveTo_654) {
    state->textMoveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// ===================== Copy =====================

TEST_F(GfxStateTest_654, CopyCreatesNewState_654) {
    state->setLineWidth(7.0);
    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_NE(copied.get(), state.get());
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.0);
}

TEST_F(GfxStateTest_654, CopyWithPath_654) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    std::unique_ptr<GfxState> copied(state->copy(true));
    EXPECT_TRUE(copied->isPath());
}

// ===================== Display Profile =====================

TEST_F(GfxStateTest_654, GetDisplayProfileInitiallyNull_654) {
    GfxLCMSProfilePtr profile = state->getDisplayProfile();
    // Initially should be null/empty
    EXPECT_FALSE(profile);
}

// ===================== Font =====================

TEST_F(GfxStateTest_654, GetFontInitiallyNull_654) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

TEST_F(GfxStateTest_654, GetFontSizeDefault_654) {
    double fontSize = state->getFontSize();
    EXPECT_DOUBLE_EQ(fontSize, 0.0);
}

// ===================== Color =====================

TEST_F(GfxStateTest_654, GetFillColorNonNull_654) {
    const GfxColor *color = state->getFillColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_654, GetStrokeColorNonNull_654) {
    const GfxColor *color = state->getStrokeColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_654, SetFillColor_654) {
    GfxColor color;
    color.c[0] = 32768;
    state->setFillColor(&color);
    const GfxColor *result = state->getFillColor();
    EXPECT_EQ(result->c[0], 32768);
}

TEST_F(GfxStateTest_654, SetStrokeColor_654) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *result = state->getStrokeColor();
    EXPECT_EQ(result->c[0], 16384);
}

// ===================== parseBlendMode (static) =====================

TEST_F(GfxStateTest_654, ParseBlendModeNormal_654) {
    Object obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, GfxBlendMode::Normal);
}

TEST_F(GfxStateTest_654, ParseBlendModeMultiply_654) {
    Object obj = Object(new GooString("Multiply"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, GfxBlendMode::Multiply);
}

// ===================== TransformWidth =====================

TEST_F(GfxStateTest_654, TransformWidthWithIdentityCTM_654) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 5.0);
}

TEST_F(GfxStateTest_654, TransformWidthWithScaling_654) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 10.0);
}

// ===================== Boundary: Zero and Negative Values =====================

TEST_F(GfxStateTest_654, SetLineWidthZero_654) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_654, SetFillOpacityBoundaryZero_654) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_654, SetFillOpacityBoundaryOne_654) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_654, SetStrokeOpacityBoundaryZero_654) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

TEST_F(GfxStateTest_654, SetStrokeOpacityBoundaryOne_654) {
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// ===================== Multiple Save/Restore =====================

TEST_F(GfxStateTest_654, MultipleSaveRestore_654) {
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

// ===================== isParentState =====================

TEST_F(GfxStateTest_654, IsParentState_654) {
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
}

TEST_F(GfxStateTest_654, IsNotParentStateForUnrelated_654) {
    PDFRectangle pageBox = makePageBox(0, 0, 100, 100);
    GfxState other(72.0, 72.0, &pageBox, 0, true);
    EXPECT_FALSE(state->isParentState(&other));
}

// ===================== ShiftCTMAndClip =====================

TEST_F(GfxStateTest_654, ShiftCTMAndClip_654) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 60.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 60.0);
}

// ===================== GetTransformedLineWidth =====================

TEST_F(GfxStateTest_654, GetTransformedLineWidth_654) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tlw, 6.0);
}

// ===================== GetReusablePath =====================

TEST_F(GfxStateTest_654, GetReusablePathNotNull_654) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// ===================== Different Page Boxes =====================

TEST_F(GfxStateTest_654, LargePageBox_654) {
    PDFRectangle pageBox = makePageBox(0, 0, 5000, 5000);
    GfxState largeState(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(largeState.getPageWidth(), 5000.0);
    EXPECT_DOUBLE_EQ(largeState.getPageHeight(), 5000.0);
    EXPECT_DOUBLE_EQ(largeState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(largeState.getVDPI(), 300.0);
}

TEST_F(GfxStateTest_654, NonOriginPageBox_654) {
    PDFRectangle pageBox = makePageBox(100, 200, 400, 600);
    GfxState offsetState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(offsetState.getPageWidth(), 300.0);
    EXPECT_DOUBLE_EQ(offsetState.getPageHeight(), 400.0);
}

// ===================== TextTransform =====================

TEST_F(GfxStateTest_654, TextTransformIdentity_654) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(5.0, 10.0, &x2, &y2);
    // The result depends on the combination of text matrix and CTM
    // With both as identity, it should pass through
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// ===================== Cur coordinates =====================

TEST_F(GfxStateTest_654, GetCurXY_654) {
    // Initially cur position should be finite
    double cx = state->getCurX();
    double cy = state->getCurY();
    EXPECT_TRUE(std::isfinite(cx));
    EXPECT_TRUE(std::isfinite(cy));
}

TEST_F(GfxStateTest_654, GetCurTextXY_654) {
    double tx = state->getCurTextX();
    double ty = state->getCurTextY();
    EXPECT_TRUE(std::isfinite(tx));
    EXPECT_TRUE(std::isfinite(ty));
}
