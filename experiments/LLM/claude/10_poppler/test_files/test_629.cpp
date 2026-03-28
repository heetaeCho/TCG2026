#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"
#include "Object.h"
#include <memory>
#include <cmath>

// Helper to create a PDFRectangle
static PDFRectangle makePageBox(double x1, double y1, double x2, double y2) {
    PDFRectangle r;
    r.x1 = x1;
    r.y1 = y1;
    r.x2 = x2;
    r.y2 = y2;
    return r;
}

class GfxStateTest_629 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// --- Basic Construction and Getters ---

TEST_F(GfxStateTest_629, ConstructorSetsHDPI_629) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_629, ConstructorSetsVDPI_629) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_629, ConstructorSetsRotate_629) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_629, ConstructorSetsPageDimensions_629) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_629, ConstructorSetsPageBounds_629) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// --- Line Width ---

TEST_F(GfxStateTest_629, DefaultLineWidth_629) {
    // Default line width should be some initial value (typically 1 or 0)
    double lw = state->getLineWidth();
    EXPECT_GE(lw, 0.0);
}

TEST_F(GfxStateTest_629, SetLineWidth_629) {
    state->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_629, SetLineWidthZero_629) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_629, GetTransformedLineWidth_629) {
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    // With identity-like CTM at 72 DPI, the transformed line width should be a positive value
    EXPECT_GT(tlw, 0.0);
}

TEST_F(GfxStateTest_629, GetTransformedLineWidthZero_629) {
    state->setLineWidth(0.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tlw, 0.0);
}

// --- Font Size ---

TEST_F(GfxStateTest_629, SetFontAndGetFontSize_629) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

TEST_F(GfxStateTest_629, GetTransformedFontSize_629) {
    state->setFont(nullptr, 12.0);
    double tfs = state->getTransformedFontSize();
    EXPECT_GT(tfs, 0.0);
}

// --- Opacity ---

TEST_F(GfxStateTest_629, SetFillOpacity_629) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_629, SetStrokeOpacity_629) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_629, DefaultFillOpacity_629) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_629, DefaultStrokeOpacity_629) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// --- Overprint ---

TEST_F(GfxStateTest_629, SetFillOverprint_629) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_629, SetStrokeOverprint_629) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_629, DefaultFillOverprint_629) {
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_629, DefaultStrokeOverprint_629) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_629, SetOverprintMode_629) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// --- Blend Mode ---

TEST_F(GfxStateTest_629, DefaultBlendMode_629) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

TEST_F(GfxStateTest_629, SetBlendMode_629) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// --- Flatness ---

TEST_F(GfxStateTest_629, SetFlatness_629) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// --- Line Join and Cap ---

TEST_F(GfxStateTest_629, SetLineJoin_629) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

TEST_F(GfxStateTest_629, SetLineCap_629) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// --- Miter Limit ---

TEST_F(GfxStateTest_629, SetMiterLimit_629) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// --- Stroke Adjust ---

TEST_F(GfxStateTest_629, SetStrokeAdjust_629) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_629, DefaultStrokeAdjust_629) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// --- Alpha Is Shape ---

TEST_F(GfxStateTest_629, SetAlphaIsShape_629) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_629, DefaultAlphaIsShape_629) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// --- Text Knockout ---

TEST_F(GfxStateTest_629, SetTextKnockout_629) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

TEST_F(GfxStateTest_629, DefaultTextKnockout_629) {
    EXPECT_FALSE(state->getTextKnockout());
}

// --- Text Properties ---

TEST_F(GfxStateTest_629, SetCharSpace_629) {
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
}

TEST_F(GfxStateTest_629, SetWordSpace_629) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

TEST_F(GfxStateTest_629, SetHorizScaling_629) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_629, SetLeading_629) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_629, SetRise_629) {
    state->setRise(2.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 2.0);
}

TEST_F(GfxStateTest_629, SetRender_629) {
    state->setRender(1);
    EXPECT_EQ(state->getRender(), 1);
}

// --- Text Matrix ---

TEST_F(GfxStateTest_629, SetTextMat_629) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 1.0);
    EXPECT_DOUBLE_EQ(tm[4], 10.0);
    EXPECT_DOUBLE_EQ(tm[5], 20.0);
}

// --- Rendering Intent ---

TEST_F(GfxStateTest_629, SetRenderingIntent_629) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_629, SetRenderingIntentRelativeColorimetric_629) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// --- CTM ---

TEST_F(GfxStateTest_629, SetCTM_629) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 100.0);
    EXPECT_DOUBLE_EQ(ctm[5], 200.0);
}

TEST_F(GfxStateTest_629, ConcatCTM_629) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// --- Transform ---

TEST_F(GfxStateTest_629, TransformPoint_629) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 110.0);
    EXPECT_DOUBLE_EQ(y2, 220.0);
}

TEST_F(GfxStateTest_629, TransformDelta_629) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double dx2, dy2;
    state->transformDelta(5.0, 10.0, &dx2, &dy2);
    EXPECT_DOUBLE_EQ(dx2, 10.0);
    EXPECT_DOUBLE_EQ(dy2, 30.0);
}

// --- TransformedLineWidth with scaled CTM ---

TEST_F(GfxStateTest_629, GetTransformedLineWidthScaled_629) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tlw, 2.0);
}

TEST_F(GfxStateTest_629, GetTransformedLineWidthNonUniformScale_629) {
    state->setCTM(3.0, 0.0, 0.0, 4.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    // transformWidth should give some averaged or specific scaled value
    EXPECT_GT(tlw, 0.0);
}

// --- Save and Restore ---

TEST_F(GfxStateTest_629, SaveAndRestore_629) {
    state->setLineWidth(3.0);
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    saved->setLineWidth(7.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 7.0);

    GfxState *restored = saved->restore();
    ASSERT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 3.0);
}

TEST_F(GfxStateTest_629, HasSaves_629) {
    EXPECT_FALSE(state->hasSaves());
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    GfxState *restored = saved->restore();
    EXPECT_FALSE(restored->hasSaves());
}

// --- Path Operations ---

TEST_F(GfxStateTest_629, InitiallyNoPath_629) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_629, MoveToCreatesCurrentPoint_629) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_629, LineToCreatesPath_629) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_629, ClearPathRemovesPath_629) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_629, CurveToCreatesPath_629) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_629, ClosePathOnPath_629) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// --- Clip ---

TEST_F(GfxStateTest_629, ClipBBox_629) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Initially the clip should cover the page
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_629, ClipToRect_629) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 100.0);
    EXPECT_GE(yMin, 100.0);
    EXPECT_LE(xMax, 200.0);
    EXPECT_LE(yMax, 200.0);
}

// --- UserClipBBox ---

TEST_F(GfxStateTest_629, GetUserClipBBox_629) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// --- Line Dash ---

TEST_F(GfxStateTest_629, SetLineDash_629) {
    std::vector<double> dash = {5.0, 3.0};
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 5.0);
    EXPECT_DOUBLE_EQ(d[1], 3.0);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

TEST_F(GfxStateTest_629, SetLineDashWithOffset_629) {
    std::vector<double> dash = {10.0, 5.0, 2.0};
    state->setLineDash(std::move(dash), 3.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 3u);
    EXPECT_DOUBLE_EQ(start, 3.0);
}

TEST_F(GfxStateTest_629, SetLineDashEmpty_629) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_TRUE(d.empty());
}

// --- Text Move ---

TEST_F(GfxStateTest_629, TextMoveTo_629) {
    state->textMoveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getCurTextX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurTextY(), 20.0);
}

// --- Copy ---

TEST_F(GfxStateTest_629, CopyPreservesState_629) {
    state->setLineWidth(42.0);
    state->setFillOpacity(0.3);
    auto copied = std::unique_ptr<GfxState>(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 42.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.3);
}

// --- Rotation constructor ---

TEST_F(GfxStateTest_629, ConstructWithRotation90_629) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_629, ConstructWithRotation180_629) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

TEST_F(GfxStateTest_629, ConstructWithRotation270_629) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

// --- Different DPI ---

TEST_F(GfxStateTest_629, HighDPIConstruction_629) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState highDpi(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpi.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpi.getVDPI(), 300.0);
}

TEST_F(GfxStateTest_629, AsymmetricDPI_629) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState asymDpi(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(asymDpi.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(asymDpi.getVDPI(), 300.0);
}

// --- isParentState ---

TEST_F(GfxStateTest_629, IsParentState_629) {
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
}

// --- Parse Blend Mode ---

TEST_F(GfxStateTest_629, ParseBlendModeNormal_629) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, gfxBlendNormal);
    }
}

// --- Boundary: very large line width ---

TEST_F(GfxStateTest_629, VeryLargeLineWidth_629) {
    state->setLineWidth(1e10);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1e10);
}

// --- Boundary: negative line width ---

TEST_F(GfxStateTest_629, NegativeLineWidth_629) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

// --- Multiple save/restore ---

TEST_F(GfxStateTest_629, MultipleSaveRestore_629) {
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

// --- GetPath ---

TEST_F(GfxStateTest_629, GetPathNotNull_629) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// --- ShiftCTMAndClip ---

TEST_F(GfxStateTest_629, ShiftCTMAndClip_629) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 60.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 60.0);
}

// --- GetCTM with Matrix ---

TEST_F(GfxStateTest_629, GetCTMMatrix_629) {
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

// --- Line position ---

TEST_F(GfxStateTest_629, LinePosition_629) {
    state->textMoveTo(15.0, 25.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 15.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 25.0);
}
