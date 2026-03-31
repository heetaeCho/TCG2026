#include <gtest/gtest.h>
#include <memory>
#include <cstring>
#include "GfxState.h"

// Helper to create a GfxState with reasonable defaults
static std::unique_ptr<GfxState> createDefaultState(double hDPI = 72.0, double vDPI = 72.0,
                                                      int rotate = 0, bool upsideDown = false) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612; // Letter width in points
    pageBox.y2 = 792; // Letter height in points
    return std::make_unique<GfxState>(hDPI, vDPI, &pageBox, rotate, upsideDown);
}

class GfxStateTest_610 : public ::testing::Test {
protected:
    std::unique_ptr<GfxState> state;

    void SetUp() override {
        state = createDefaultState();
    }
};

// --- Constructor and basic getters ---

TEST_F(GfxStateTest_610, ConstructorSetsHDPI_610) {
    auto s = createDefaultState(96.0, 72.0);
    EXPECT_DOUBLE_EQ(s->getHDPI(), 96.0);
}

TEST_F(GfxStateTest_610, ConstructorSetsVDPI_610) {
    auto s = createDefaultState(72.0, 150.0);
    EXPECT_DOUBLE_EQ(s->getVDPI(), 150.0);
}

TEST_F(GfxStateTest_610, ConstructorSetsPageDimensions_610) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

TEST_F(GfxStateTest_610, ConstructorSetsPageWidthHeight_610) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_610, ConstructorSetsRotate_610) {
    auto s = createDefaultState(72.0, 72.0, 90);
    EXPECT_EQ(s->getRotate(), 90);
}

// --- HorizScaling ---

TEST_F(GfxStateTest_610, DefaultHorizScaling_610) {
    // Default horizontal scaling should be 1.0 (100%)
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

TEST_F(GfxStateTest_610, SetHorizScaling_610) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

TEST_F(GfxStateTest_610, SetHorizScalingZero_610) {
    state->setHorizScaling(0.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.0);
}

TEST_F(GfxStateTest_610, SetHorizScalingNegative_610) {
    state->setHorizScaling(-2.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), -2.0);
}

// --- CharSpace ---

TEST_F(GfxStateTest_610, DefaultCharSpace_610) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

TEST_F(GfxStateTest_610, SetCharSpace_610) {
    state->setCharSpace(2.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.5);
}

// --- WordSpace ---

TEST_F(GfxStateTest_610, DefaultWordSpace_610) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

TEST_F(GfxStateTest_610, SetWordSpace_610) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

// --- Leading ---

TEST_F(GfxStateTest_610, DefaultLeading_610) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

TEST_F(GfxStateTest_610, SetLeading_610) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// --- Rise ---

TEST_F(GfxStateTest_610, DefaultRise_610) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

TEST_F(GfxStateTest_610, SetRise_610) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

// --- Render ---

TEST_F(GfxStateTest_610, DefaultRender_610) {
    EXPECT_EQ(state->getRender(), 0);
}

TEST_F(GfxStateTest_610, SetRender_610) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// --- LineWidth ---

TEST_F(GfxStateTest_610, DefaultLineWidth_610) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

TEST_F(GfxStateTest_610, SetLineWidth_610) {
    state->setLineWidth(3.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.5);
}

TEST_F(GfxStateTest_610, SetLineWidthZero_610) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// --- MiterLimit ---

TEST_F(GfxStateTest_610, DefaultMiterLimit_610) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_610, SetMiterLimit_610) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// --- Flatness ---

TEST_F(GfxStateTest_610, DefaultFlatness_610) {
    EXPECT_EQ(state->getFlatness(), 1);
}

TEST_F(GfxStateTest_610, SetFlatness_610) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// --- LineJoin ---

TEST_F(GfxStateTest_610, SetLineJoin_610) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// --- LineCap ---

TEST_F(GfxStateTest_610, SetLineCap_610) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// --- Opacity ---

TEST_F(GfxStateTest_610, DefaultFillOpacity_610) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_610, SetFillOpacity_610) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_610, DefaultStrokeOpacity_610) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_610, SetStrokeOpacity_610) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// --- Overprint ---

TEST_F(GfxStateTest_610, DefaultFillOverprint_610) {
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_610, SetFillOverprint_610) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_610, DefaultStrokeOverprint_610) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_610, SetStrokeOverprint_610) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_610, DefaultOverprintMode_610) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

TEST_F(GfxStateTest_610, SetOverprintMode_610) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// --- StrokeAdjust ---

TEST_F(GfxStateTest_610, DefaultStrokeAdjust_610) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_610, SetStrokeAdjust_610) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// --- AlphaIsShape ---

TEST_F(GfxStateTest_610, DefaultAlphaIsShape_610) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_610, SetAlphaIsShape_610) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// --- TextKnockout ---

TEST_F(GfxStateTest_610, DefaultTextKnockout_610) {
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_610, SetTextKnockout_610) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// --- RenderingIntent ---

TEST_F(GfxStateTest_610, SetRenderingIntent_610) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_610, SetRenderingIntentEmpty_610) {
    state->setRenderingIntent("");
    EXPECT_STREQ(state->getRenderingIntent(), "");
}

// --- TextMat ---

TEST_F(GfxStateTest_610, SetTextMat_610) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 2.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 2.0);
    EXPECT_DOUBLE_EQ(tm[4], 10.0);
    EXPECT_DOUBLE_EQ(tm[5], 20.0);
}

// --- CTM ---

TEST_F(GfxStateTest_610, SetCTM_610) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 50.0, 100.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 1.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 1.0);
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 100.0);
}

TEST_F(GfxStateTest_610, ConcatCTM_610) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// --- Transform ---

TEST_F(GfxStateTest_610, TransformIdentity_610) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

TEST_F(GfxStateTest_610, TransformWithTranslation_610) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 105.0);
    EXPECT_DOUBLE_EQ(y2, 210.0);
}

TEST_F(GfxStateTest_610, TransformDelta_610) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    // transformDelta should not include translation
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// --- Save / Restore ---

TEST_F(GfxStateTest_610, SaveRestore_610) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());

    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 10.0);

    GfxState *restored = saved->restore();
    ASSERT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_610, HasSavesInitiallyFalse_610) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_610, HasSavesTrueAfterSave_610) {
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    // Clean up
    saved->restore();
}

// --- Path operations ---

TEST_F(GfxStateTest_610, InitiallyNoCurPtAndNoPath_610) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_610, MoveToSetsCurPt_610) {
    state->clearPath();
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_610, LineToCreatesPath_610) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_610, ClearPathResetsPath_610) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_610, CurveTo_610) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_610, ClosePath_610) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    // After closing, path should still exist
    EXPECT_TRUE(state->isPath());
}

// --- TextMoveTo ---

TEST_F(GfxStateTest_610, TextMoveTo_610) {
    state->textMoveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// --- LineDash ---

TEST_F(GfxStateTest_610, SetLineDash_610) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
}

TEST_F(GfxStateTest_610, SetLineDashEmpty_610) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(d.empty());
}

// --- Font ---

TEST_F(GfxStateTest_610, DefaultFontIsNull_610) {
    EXPECT_EQ(state->getFont(), nullptr);
}

TEST_F(GfxStateTest_610, GetFontSize_610) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// --- Clip ---

TEST_F(GfxStateTest_610, ClipToRect_610) {
    state->clipToRect(10.0, 20.0, 300.0, 400.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, 300.0);
    EXPECT_LE(yMin, 400.0);
    EXPECT_GE(xMax, 10.0);
    EXPECT_GE(yMax, 20.0);
}

TEST_F(GfxStateTest_610, GetUserClipBBox_610) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should return some valid bounding box
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// --- Copy ---

TEST_F(GfxStateTest_610, CopyPreservesProperties_610) {
    state->setLineWidth(7.5);
    state->setHorizScaling(2.0);
    state->setCharSpace(1.5);
    auto copied = std::unique_ptr<GfxState>(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    EXPECT_DOUBLE_EQ(copied->getHorizScaling(), 2.0);
    EXPECT_DOUBLE_EQ(copied->getCharSpace(), 1.5);
}

// --- BlendMode ---

TEST_F(GfxStateTest_610, DefaultBlendMode_610) {
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

TEST_F(GfxStateTest_610, SetBlendMode_610) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// --- TransformWidth ---

TEST_F(GfxStateTest_610, TransformWidthIdentity_610) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 5.0);
}

TEST_F(GfxStateTest_610, TransformWidthScaled_610) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 10.0);
}

// --- Rotated page ---

TEST_F(GfxStateTest_610, ConstructorWithRotation90_610) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    auto s = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 90, false);
    EXPECT_EQ(s->getRotate(), 90);
    // Page width/height should swap with 90 degree rotation
    EXPECT_DOUBLE_EQ(s->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(s->getPageHeight(), 792.0);
}

// --- Boundary: very large and very small values ---

TEST_F(GfxStateTest_610, SetLineWidthVeryLarge_610) {
    state->setLineWidth(1e10);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1e10);
}

TEST_F(GfxStateTest_610, SetLineWidthVerySmall_610) {
    state->setLineWidth(1e-10);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1e-10);
}

TEST_F(GfxStateTest_610, SetFillOpacityBoundaryZero_610) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_610, SetFillOpacityBoundaryOne_610) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// --- Multiple save/restore ---

TEST_F(GfxStateTest_610, MultipleSaveRestore_610) {
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

// --- GetPath ---

TEST_F(GfxStateTest_610, GetPathNotNull_610) {
    EXPECT_NE(state->getPath(), nullptr);
}

// --- ShiftCTMAndClip ---

TEST_F(GfxStateTest_610, ShiftCTMAndClip_610) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 60.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 60.0);
}

// --- GetCTM with Matrix ---

TEST_F(GfxStateTest_610, GetCTMMatrix_610) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Matrix should contain the CTM values
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
    EXPECT_DOUBLE_EQ(m.m[1], 2.0);
    EXPECT_DOUBLE_EQ(m.m[2], 3.0);
    EXPECT_DOUBLE_EQ(m.m[3], 4.0);
    EXPECT_DOUBLE_EQ(m.m[4], 5.0);
    EXPECT_DOUBLE_EQ(m.m[5], 6.0);
}

// --- FillColor / StrokeColor ---

TEST_F(GfxStateTest_610, SetAndGetFillColor_610) {
    GfxColor color;
    color.c[0] = 32768; // midway value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_610, SetAndGetStrokeColor_610) {
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 65535);
}

// --- GetTransformedLineWidth ---

TEST_F(GfxStateTest_610, GetTransformedLineWidth_610) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tw, 6.0);
}

// --- CurX, CurY ---

TEST_F(GfxStateTest_610, GetCurXCurY_610) {
    // These should return some default value, typically 0
    double cx = state->getCurX();
    double cy = state->getCurY();
    EXPECT_DOUBLE_EQ(cx, 0.0);
    EXPECT_DOUBLE_EQ(cy, 0.0);
}
