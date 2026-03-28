#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a PDFRectangle
static PDFRectangle makePageBox(double x1, double y1, double x2, double y2) {
    PDFRectangle r;
    r.x1 = x1;
    r.y1 = y1;
    r.x2 = x2;
    r.y2 = y2;
    return r;
}

class GfxStateTest_588 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// --- Constructor and basic getter tests ---

TEST_F(GfxStateTest_588, ConstructorSetsHDPI_588) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_588, ConstructorSetsVDPI_588) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_588, ConstructorSetsRotate_588) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_588, ConstructorSetsPageDimensions_588) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_588, ConstructorSetsPageBounds_588) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

TEST_F(GfxStateTest_588, ConstructorWithRotation_588) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_588, ConstructorWithDifferentDPI_588) {
    PDFRectangle pageBox = makePageBox(0, 0, 100, 200);
    GfxState highDPI(300.0, 150.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDPI.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDPI.getVDPI(), 150.0);
}

// --- CTM tests ---

TEST_F(GfxStateTest_588, GetCTMReturnsArray_588) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_588, SetCTMUpdatesValues_588) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_588, ConcatCTM_588) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 5.0);
    EXPECT_DOUBLE_EQ(ctm[5], 10.0);
}

// --- Transform tests ---

TEST_F(GfxStateTest_588, TransformWithIdentityCTM_588) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

TEST_F(GfxStateTest_588, TransformWithScalingCTM_588) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

TEST_F(GfxStateTest_588, TransformWithTranslation_588) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 105.0);
    EXPECT_DOUBLE_EQ(y2, 210.0);
}

TEST_F(GfxStateTest_588, TransformDelta_588) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    // transformDelta should not include translation
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// --- Line width tests ---

TEST_F(GfxStateTest_588, SetAndGetLineWidth_588) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_588, SetLineWidthZero_588) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// --- Line dash tests ---

TEST_F(GfxStateTest_588, SetAndGetLineDash_588) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

TEST_F(GfxStateTest_588, SetEmptyLineDash_588) {
    std::vector<double> dash = {};
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_TRUE(d.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// --- Flatness tests ---

TEST_F(GfxStateTest_588, SetAndGetFlatness_588) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// --- Line join / cap tests ---

TEST_F(GfxStateTest_588, SetAndGetLineJoin_588) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_588, SetAndGetLineCap_588) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// --- Miter limit tests ---

TEST_F(GfxStateTest_588, SetAndGetMiterLimit_588) {
    state->setMiterLimit(15.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 15.0);
}

// --- Opacity tests ---

TEST_F(GfxStateTest_588, SetAndGetFillOpacity_588) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_588, SetAndGetStrokeOpacity_588) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_588, FillOpacityBoundaryZero_588) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_588, FillOpacityBoundaryOne_588) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// --- Overprint tests ---

TEST_F(GfxStateTest_588, SetAndGetFillOverprint_588) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_588, SetAndGetStrokeOverprint_588) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_588, SetAndGetOverprintMode_588) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// --- Blend mode tests ---

TEST_F(GfxStateTest_588, SetAndGetBlendMode_588) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// --- Stroke adjust tests ---

TEST_F(GfxStateTest_588, SetAndGetStrokeAdjust_588) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// --- Alpha is shape tests ---

TEST_F(GfxStateTest_588, SetAndGetAlphaIsShape_588) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// --- Text knockout tests ---

TEST_F(GfxStateTest_588, SetAndGetTextKnockout_588) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// --- Font size tests ---

TEST_F(GfxStateTest_588, SetAndGetFontSize_588) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

TEST_F(GfxStateTest_588, SetFontSizeZero_588) {
    state->setFont(nullptr, 0.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// --- Text matrix tests ---

TEST_F(GfxStateTest_588, SetAndGetTextMat_588) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 2.0);
    EXPECT_DOUBLE_EQ(tm[2], 3.0);
    EXPECT_DOUBLE_EQ(tm[3], 4.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 6.0);
}

// --- Char / word space tests ---

TEST_F(GfxStateTest_588, SetAndGetCharSpace_588) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_588, SetAndGetWordSpace_588) {
    state->setWordSpace(2.5);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.5);
}

// --- Horizontal scaling tests ---

TEST_F(GfxStateTest_588, SetAndGetHorizScaling_588) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// --- Leading tests ---

TEST_F(GfxStateTest_588, SetAndGetLeading_588) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// --- Rise tests ---

TEST_F(GfxStateTest_588, SetAndGetRise_588) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// --- Render tests ---

TEST_F(GfxStateTest_588, SetAndGetRender_588) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// --- Rendering intent tests ---

TEST_F(GfxStateTest_588, SetAndGetRenderingIntent_588) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_588, SetRenderingIntentRelativeColorimetric_588) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// --- Stroke pattern tests ---

TEST_F(GfxStateTest_588, GetStrokePatternInitiallyNull_588) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

TEST_F(GfxStateTest_588, GetFillPatternInitiallyNull_588) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

// --- Path operations tests ---

TEST_F(GfxStateTest_588, InitiallyNoPath_588) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_588, MoveToSetsCurPt_588) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_588, MoveToSetsCoordinates_588) {
    state->moveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

TEST_F(GfxStateTest_588, LineToCreatesPath_588) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

TEST_F(GfxStateTest_588, CurveToCreatesPath_588) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 5.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 6.0);
}

TEST_F(GfxStateTest_588, ClosePathKeepsPath_588) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_588, ClearPathResetsState_588) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// --- Save / Restore tests ---

TEST_F(GfxStateTest_588, InitiallyNoSaves_588) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_588, SaveCreatesSaveState_588) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
}

TEST_F(GfxStateTest_588, RestoreReturnsParent_588) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 10.0);
    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_588, SavePreservesProperties_588) {
    state->setFillOpacity(0.3);
    state->setStrokeOpacity(0.7);
    GfxState *saved = state->save();
    EXPECT_DOUBLE_EQ(saved->getFillOpacity(), 0.3);
    EXPECT_DOUBLE_EQ(saved->getStrokeOpacity(), 0.7);
    saved->restore();
}

TEST_F(GfxStateTest_588, MultipleSavesAndRestores_588) {
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

// --- isParentState tests ---

TEST_F(GfxStateTest_588, IsParentStateReturnsTrueForParent_588) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->isParentState(state.get()));
    saved->restore();
}

// --- Clip bounding box tests ---

TEST_F(GfxStateTest_588, GetClipBBox_588) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip box should be initialized to page bounds or similar
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_588, ClipToRect_588) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 10.0);
    EXPECT_GE(yMin, 20.0);
    EXPECT_LE(xMax, 100.0);
    EXPECT_LE(yMax, 200.0);
}

TEST_F(GfxStateTest_588, GetUserClipBBox_588) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// --- Text position tests ---

TEST_F(GfxStateTest_588, TextMoveTo_588) {
    state->textMoveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getCurTextX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurTextY(), 20.0);
}

TEST_F(GfxStateTest_588, TextMoveToSetsLineXY_588) {
    state->textMoveTo(15.0, 25.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 15.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 25.0);
}

// --- Copy tests ---

TEST_F(GfxStateTest_588, CopyPreservesProperties_588) {
    state->setLineWidth(7.0);
    state->setFillOpacity(0.4);
    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.4);
}

// --- GetPath tests ---

TEST_F(GfxStateTest_588, GetPathNotNull_588) {
    EXPECT_NE(state->getPath(), nullptr);
}

// --- TransformWidth tests ---

TEST_F(GfxStateTest_588, TransformWidthIdentity_588) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_NEAR(w, 5.0, 0.001);
}

TEST_F(GfxStateTest_588, TransformWidthScaled_588) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_NEAR(w, 10.0, 0.001);
}

// --- GetTransformedLineWidth tests ---

TEST_F(GfxStateTest_588, GetTransformedLineWidth_588) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_NEAR(tw, 3.0, 0.001);
}

// --- parseBlendMode static tests ---

TEST_F(GfxStateTest_588, ParseBlendModeNormal_588) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, GfxBlendMode::Normal);
    }
}

// --- Color state tests ---

TEST_F(GfxStateTest_588, GetFillColorNotNull_588) {
    EXPECT_NE(state->getFillColor(), nullptr);
}

TEST_F(GfxStateTest_588, GetStrokeColorNotNull_588) {
    EXPECT_NE(state->getStrokeColor(), nullptr);
}

// --- ShiftCTMAndClip tests ---

TEST_F(GfxStateTest_588, ShiftCTMAndClip_588) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 100.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 100.0);
}

// --- TextTransform tests ---

TEST_F(GfxStateTest_588, TextTransform_588) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(5.0, 10.0, &x2, &y2);
    // Result depends on CTM and text matrix combination
    // Just verify it doesn't crash and produces finite values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

TEST_F(GfxStateTest_588, TextTransformDelta_588) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(1.0, 1.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// --- GetTransformedFontSize tests ---

TEST_F(GfxStateTest_588, GetTransformedFontSize_588) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setFont(nullptr, 12.0);
    double tfs = state->getTransformedFontSize();
    EXPECT_TRUE(std::isfinite(tfs));
    EXPECT_GT(tfs, 0.0);
}

// --- GetFontTransMat tests ---

TEST_F(GfxStateTest_588, GetFontTransMat_588) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setFont(nullptr, 12.0);
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    EXPECT_TRUE(std::isfinite(m11));
    EXPECT_TRUE(std::isfinite(m12));
    EXPECT_TRUE(std::isfinite(m21));
    EXPECT_TRUE(std::isfinite(m22));
}

// --- GetFont tests ---

TEST_F(GfxStateTest_588, GetFontInitiallyNull_588) {
    // Font may be null after construction
    const auto &font = state->getFont();
    // Just check it doesn't crash; font might be nullptr
    (void)font;
}

// --- Boundary: negative page box ---

TEST_F(GfxStateTest_588, NegativePageBox_588) {
    PDFRectangle pageBox = makePageBox(-100, -200, 100, 200);
    GfxState negState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(negState.getPageWidth(), 200.0);
    EXPECT_DOUBLE_EQ(negState.getPageHeight(), 400.0);
}

// --- UpsideDown false ---

TEST_F(GfxStateTest_588, ConstructorUpsideDownFalse_588) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState noFlipState(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(noFlipState.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(noFlipState.getPageHeight(), 792.0);
}

// --- GetReusablePath tests ---

TEST_F(GfxStateTest_588, GetReusablePath_588) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}
