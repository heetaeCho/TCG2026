#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState with reasonable defaults
static std::unique_ptr<GfxState> createDefaultGfxState() {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    return std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
}

class GfxStateTest_633 : public ::testing::Test {
protected:
    std::unique_ptr<GfxState> state;

    void SetUp() override {
        state = createDefaultGfxState();
    }
};

// ============================================================
// Constructor / Basic Getter Tests
// ============================================================

TEST_F(GfxStateTest_633, ConstructorSetsHDPI_633) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_633, ConstructorSetsVDPI_633) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_633, ConstructorSetsRotate_633) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_633, ConstructorSetsPageDimensions_633) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_633, ConstructorWithRotation90_633) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_633, GetX1Y1X2Y2_633) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// ============================================================
// Fill Opacity Tests
// ============================================================

TEST_F(GfxStateTest_633, DefaultFillOpacity_633) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_633, SetFillOpacityNormal_633) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_633, SetFillOpacityZero_633) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_633, SetFillOpacityOne_633) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_633, SetFillOpacitySmallValue_633) {
    state->setFillOpacity(0.001);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.001);
}

// ============================================================
// Stroke Opacity Tests
// ============================================================

TEST_F(GfxStateTest_633, DefaultStrokeOpacity_633) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_633, SetStrokeOpacity_633) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_633, SetStrokeOpacityZero_633) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

// ============================================================
// Line Width Tests
// ============================================================

TEST_F(GfxStateTest_633, SetLineWidth_633) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_633, SetLineWidthZero_633) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// ============================================================
// Flatness Tests
// ============================================================

TEST_F(GfxStateTest_633, SetFlatness_633) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// ============================================================
// Line Join / Line Cap Tests
// ============================================================

TEST_F(GfxStateTest_633, SetLineJoin_633) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_633, SetLineCap_633) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// ============================================================
// Miter Limit Tests
// ============================================================

TEST_F(GfxStateTest_633, SetMiterLimit_633) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// ============================================================
// Overprint Tests
// ============================================================

TEST_F(GfxStateTest_633, SetFillOverprint_633) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_633, SetStrokeOverprint_633) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_633, SetOverprintMode_633) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// ============================================================
// Stroke Adjust Tests
// ============================================================

TEST_F(GfxStateTest_633, SetStrokeAdjust_633) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// ============================================================
// Alpha Is Shape Tests
// ============================================================

TEST_F(GfxStateTest_633, SetAlphaIsShape_633) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// ============================================================
// Text Knockout Tests
// ============================================================

TEST_F(GfxStateTest_633, SetTextKnockout_633) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// ============================================================
// Text Properties Tests
// ============================================================

TEST_F(GfxStateTest_633, SetCharSpace_633) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_633, SetWordSpace_633) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_633, SetHorizScaling_633) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

TEST_F(GfxStateTest_633, SetLeading_633) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

TEST_F(GfxStateTest_633, SetRise_633) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_633, SetRender_633) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// ============================================================
// Text Matrix Tests
// ============================================================

TEST_F(GfxStateTest_633, SetTextMat_633) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 10.0);
    EXPECT_DOUBLE_EQ(mat[5], 20.0);
}

// ============================================================
// Rendering Intent Tests
// ============================================================

TEST_F(GfxStateTest_633, SetRenderingIntent_633) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_633, SetRenderingIntentRelativeColorimetric_633) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_633, SetRenderingIntentAbsoluteColorimetric_633) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

TEST_F(GfxStateTest_633, SetRenderingIntentSaturation_633) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

// ============================================================
// CTM Tests
// ============================================================

TEST_F(GfxStateTest_633, SetCTM_633) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 100.0);
    EXPECT_DOUBLE_EQ(ctm[5], 200.0);
}

TEST_F(GfxStateTest_633, ConcatCTM_633) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// ============================================================
// Transform Tests
// ============================================================

TEST_F(GfxStateTest_633, TransformIdentity_633) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_633, TransformWithScale_633) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

TEST_F(GfxStateTest_633, TransformWithTranslation_633) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 105.0);
    EXPECT_DOUBLE_EQ(y2, 210.0);
}

TEST_F(GfxStateTest_633, TransformDelta_633) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    // transformDelta should not include translation
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// ============================================================
// Path Tests
// ============================================================

TEST_F(GfxStateTest_633, InitiallyNoPath_633) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_633, MoveToCreatesCurPt_633) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_633, LineToCreatesPath_633) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_633, ClearPathResetsState_633) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_633, CurveToCreatesPath_633) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 10.0, 20.0, 20.0, 30.0, 30.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_633, ClosePathOnValidPath_633) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// ============================================================
// Save / Restore Tests
// ============================================================

TEST_F(GfxStateTest_633, SaveReturnsNewState_633) {
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());
}

TEST_F(GfxStateTest_633, RestoreReturnsPreviousState_633) {
    state->setFillOpacity(0.5);
    GfxState *saved = state->save();
    saved->setFillOpacity(0.25);
    EXPECT_DOUBLE_EQ(saved->getFillOpacity(), 0.25);

    GfxState *restored = saved->restore();
    ASSERT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_633, HasSavesInitiallyFalse_633) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_633, MultipleSaveRestore_633) {
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

// ============================================================
// Copy Tests
// ============================================================

TEST_F(GfxStateTest_633, CopyCreatesIndependentState_633) {
    state->setFillOpacity(0.7);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);

    copied->setFillOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.7);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.3);
}

// ============================================================
// Clip Tests
// ============================================================

TEST_F(GfxStateTest_633, GetClipBBox_633) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip box should be initialized to page dimensions or reasonable values
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_633, ClipToRect_633) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 100.0);
    EXPECT_GE(yMin, 100.0);
    EXPECT_LE(xMax, 200.0);
    EXPECT_LE(yMax, 200.0);
}

TEST_F(GfxStateTest_633, GetUserClipBBox_633) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// ============================================================
// Blend Mode Tests
// ============================================================

TEST_F(GfxStateTest_633, SetBlendMode_633) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

TEST_F(GfxStateTest_633, DefaultBlendModeIsNormal_633) {
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

// ============================================================
// Text Move Tests
// ============================================================

TEST_F(GfxStateTest_633, TextMoveTo_633) {
    state->textMoveTo(10.0, 20.0);
    // lineX and lineY should be updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// ============================================================
// Line Dash Tests
// ============================================================

TEST_F(GfxStateTest_633, SetLineDash_633) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

TEST_F(GfxStateTest_633, SetLineDashWithOffset_633) {
    std::vector<double> dash = {2.0, 4.0, 6.0};
    state->setLineDash(std::move(dash), 1.5);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 3u);
    EXPECT_DOUBLE_EQ(start, 1.5);
}

TEST_F(GfxStateTest_633, SetLineDashEmpty_633) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_TRUE(d.empty());
}

// ============================================================
// Font Size Tests
// ============================================================

TEST_F(GfxStateTest_633, SetFontSetsSize_633) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

// ============================================================
// IsParentState Test
// ============================================================

TEST_F(GfxStateTest_633, IsParentState_633) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->isParentState(state.get()));
}

TEST_F(GfxStateTest_633, IsNotParentState_633) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 100;
    pageBox.y2 = 100;
    GfxState otherState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_FALSE(state->isParentState(&otherState));
}

// ============================================================
// ShiftCTMAndClip Test
// ============================================================

TEST_F(GfxStateTest_633, ShiftCTMAndClip_633) {
    const auto &ctmBefore = state->getCTM();
    double e_before = ctmBefore[4];
    double f_before = ctmBefore[5];

    state->shiftCTMAndClip(10.0, 20.0);

    const auto &ctmAfter = state->getCTM();
    EXPECT_DOUBLE_EQ(ctmAfter[4], e_before + 10.0);
    EXPECT_DOUBLE_EQ(ctmAfter[5], f_before + 20.0);
}

// ============================================================
// TransformWidth Test
// ============================================================

TEST_F(GfxStateTest_633, TransformWidthIdentity_633) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 5.0);
}

TEST_F(GfxStateTest_633, TransformWidthScaled_633) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 10.0);
}

// ============================================================
// Multiple setters interaction test
// ============================================================

TEST_F(GfxStateTest_633, SetMultiplePropertiesIndependently_633) {
    state->setFillOpacity(0.3);
    state->setStrokeOpacity(0.6);
    state->setLineWidth(4.0);
    state->setMiterLimit(8.0);

    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.6);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 4.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 8.0);
}

// ============================================================
// parseBlendMode static test
// ============================================================

TEST_F(GfxStateTest_633, ParseBlendModeNormal_633) {
    Object obj(objName, "Normal");
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, GfxBlendMode::Normal);
}
