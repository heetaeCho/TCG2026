#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"

// Helper to create a PDFRectangle for constructing GfxState
static PDFRectangle makePageBox(double x1, double y1, double x2, double y2) {
    PDFRectangle r;
    r.x1 = x1;
    r.y1 = y1;
    r.x2 = x2;
    r.y2 = y2;
    return r;
}

class GfxStateTest_600 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// --- Construction and basic getters ---

TEST_F(GfxStateTest_600, ConstructionBasicProperties_600) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_600, PageDimensions_600) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_600, PageBounds_600) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// --- Line Cap ---

TEST_F(GfxStateTest_600, DefaultLineCap_600) {
    // Default line cap should be 0 (butt cap)
    EXPECT_EQ(state->getLineCap(), 0);
}

TEST_F(GfxStateTest_600, SetAndGetLineCap_600) {
    state->setLineCap((LineCapStyle)1);
    EXPECT_EQ(state->getLineCap(), 1);
    state->setLineCap((LineCapStyle)2);
    EXPECT_EQ(state->getLineCap(), 2);
    state->setLineCap((LineCapStyle)0);
    EXPECT_EQ(state->getLineCap(), 0);
}

// --- Line Join ---

TEST_F(GfxStateTest_600, DefaultLineJoin_600) {
    EXPECT_EQ(state->getLineJoin(), 0);
}

TEST_F(GfxStateTest_600, SetAndGetLineJoin_600) {
    state->setLineJoin((LineJoinStyle)1);
    EXPECT_EQ(state->getLineJoin(), 1);
    state->setLineJoin((LineJoinStyle)2);
    EXPECT_EQ(state->getLineJoin(), 2);
}

// --- Line Width ---

TEST_F(GfxStateTest_600, DefaultLineWidth_600) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

TEST_F(GfxStateTest_600, SetLineWidth_600) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// --- Miter Limit ---

TEST_F(GfxStateTest_600, DefaultMiterLimit_600) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_600, SetMiterLimit_600) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// --- Flatness ---

TEST_F(GfxStateTest_600, DefaultFlatness_600) {
    EXPECT_EQ(state->getFlatness(), 1);
}

TEST_F(GfxStateTest_600, SetFlatness_600) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// --- Fill and Stroke Opacity ---

TEST_F(GfxStateTest_600, DefaultFillOpacity_600) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_600, SetFillOpacity_600) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_600, DefaultStrokeOpacity_600) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_600, SetStrokeOpacity_600) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// --- Overprint ---

TEST_F(GfxStateTest_600, DefaultFillOverprint_600) {
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_600, SetFillOverprint_600) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_600, DefaultStrokeOverprint_600) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_600, SetStrokeOverprint_600) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_600, DefaultOverprintMode_600) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

TEST_F(GfxStateTest_600, SetOverprintMode_600) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// --- Stroke Adjust ---

TEST_F(GfxStateTest_600, DefaultStrokeAdjust_600) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_600, SetStrokeAdjust_600) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// --- Alpha Is Shape ---

TEST_F(GfxStateTest_600, DefaultAlphaIsShape_600) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_600, SetAlphaIsShape_600) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// --- Text Knockout ---

TEST_F(GfxStateTest_600, DefaultTextKnockout_600) {
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_600, SetTextKnockout_600) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// --- Font ---

TEST_F(GfxStateTest_600, DefaultFontIsNull_600) {
    EXPECT_EQ(state->getFont(), nullptr);
}

TEST_F(GfxStateTest_600, DefaultFontSize_600) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// --- Text properties ---

TEST_F(GfxStateTest_600, DefaultCharSpace_600) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

TEST_F(GfxStateTest_600, SetCharSpace_600) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_600, DefaultWordSpace_600) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

TEST_F(GfxStateTest_600, SetWordSpace_600) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_600, DefaultHorizScaling_600) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

TEST_F(GfxStateTest_600, SetHorizScaling_600) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

TEST_F(GfxStateTest_600, DefaultLeading_600) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

TEST_F(GfxStateTest_600, SetLeading_600) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

TEST_F(GfxStateTest_600, DefaultRise_600) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

TEST_F(GfxStateTest_600, SetRise_600) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_600, DefaultRender_600) {
    EXPECT_EQ(state->getRender(), 0);
}

TEST_F(GfxStateTest_600, SetRender_600) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// --- Rendering Intent ---

TEST_F(GfxStateTest_600, DefaultRenderingIntent_600) {
    const char *intent = state->getRenderingIntent();
    EXPECT_NE(intent, nullptr);
}

TEST_F(GfxStateTest_600, SetRenderingIntent_600) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_600, SetRenderingIntentRelativeColorimetric_600) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// --- CTM ---

TEST_F(GfxStateTest_600, GetCTM_600) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_600, SetCTM_600) {
    state->setCTM(2.0, 0, 0, 2.0, 10, 20);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_600, ConcatCTM_600) {
    state->setCTM(1.0, 0, 0, 1.0, 0, 0); // identity
    state->concatCTM(2.0, 0, 0, 2.0, 5, 10);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 5.0);
    EXPECT_DOUBLE_EQ(ctm[5], 10.0);
}

// --- Transform ---

TEST_F(GfxStateTest_600, TransformIdentity_600) {
    state->setCTM(1.0, 0, 0, 1.0, 0, 0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_600, TransformWithTranslation_600) {
    state->setCTM(1.0, 0, 0, 1.0, 100, 200);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 110.0);
    EXPECT_DOUBLE_EQ(y2, 220.0);
}

TEST_F(GfxStateTest_600, TransformWithScaling_600) {
    state->setCTM(2.0, 0, 0, 3.0, 0, 0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 60.0);
}

TEST_F(GfxStateTest_600, TransformDelta_600) {
    state->setCTM(2.0, 0, 0, 3.0, 100, 200);
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    // transformDelta should not add translation
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 60.0);
}

// --- Text Matrix ---

TEST_F(GfxStateTest_600, SetTextMat_600) {
    state->setTextMat(2.0, 0, 0, 2.0, 10, 20);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 2.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 2.0);
    EXPECT_DOUBLE_EQ(tm[4], 10.0);
    EXPECT_DOUBLE_EQ(tm[5], 20.0);
}

// --- Path Operations ---

TEST_F(GfxStateTest_600, InitialPathState_600) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_600, MoveToSetsCurrentPoint_600) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

TEST_F(GfxStateTest_600, LineToCreatesPath_600) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 100.0);
}

TEST_F(GfxStateTest_600, CurveToCreatesPath_600) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
}

TEST_F(GfxStateTest_600, ClearPathResetsState_600) {
    state->moveTo(10.0, 20.0);
    state->lineTo(100.0, 200.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_600, ClosePathOperation_600) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    // After closing, current point should be back to the start of the subpath
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// --- Save / Restore ---

TEST_F(GfxStateTest_600, InitiallyNoSaves_600) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_600, SaveCreatesSavedState_600) {
    GfxState *saved = state->save();
    EXPECT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());
}

TEST_F(GfxStateTest_600, RestoreReturnsPreviousState_600) {
    state->setLineWidth(5.0);
    GfxState *current = state->save();
    current->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(current->getLineWidth(), 10.0);
    
    GfxState *restored = current->restore();
    EXPECT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_600, SaveRestorePreservesProperties_600) {
    state->setFillOpacity(0.7);
    state->setStrokeOpacity(0.3);
    state->setLineCap((LineCapStyle)2);
    state->setLineJoin((LineJoinStyle)1);
    
    GfxState *current = state->save();
    current->setFillOpacity(0.1);
    current->setLineCap((LineCapStyle)0);
    
    GfxState *restored = current->restore();
    EXPECT_DOUBLE_EQ(restored->getFillOpacity(), 0.7);
    EXPECT_DOUBLE_EQ(restored->getStrokeOpacity(), 0.3);
    EXPECT_EQ(restored->getLineCap(), 2);
    EXPECT_EQ(restored->getLineJoin(), 1);
}

// --- isParentState ---

TEST_F(GfxStateTest_600, IsParentState_600) {
    GfxState *current = state->save();
    EXPECT_TRUE(current->isParentState(state.get()));
}

// --- Blend Mode ---

TEST_F(GfxStateTest_600, DefaultBlendMode_600) {
    EXPECT_EQ(state->getBlendMode(), (GfxBlendMode)0); // Normal
}

TEST_F(GfxStateTest_600, SetBlendMode_600) {
    state->setBlendMode((GfxBlendMode)1);
    EXPECT_EQ(state->getBlendMode(), (GfxBlendMode)1);
}

// --- Line Dash ---

TEST_F(GfxStateTest_600, DefaultLineDash_600) {
    double start = -1;
    const auto &dash = state->getLineDash(&start);
    EXPECT_TRUE(dash.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

TEST_F(GfxStateTest_600, SetLineDash_600) {
    std::vector<double> dashPattern = {3.0, 5.0};
    state->setLineDash(std::move(dashPattern), 1.0);
    double start;
    const auto &dash = state->getLineDash(&start);
    ASSERT_EQ(dash.size(), 2u);
    EXPECT_DOUBLE_EQ(dash[0], 3.0);
    EXPECT_DOUBLE_EQ(dash[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

// --- Clip ---

TEST_F(GfxStateTest_600, GetClipBBox_600) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip should encompass the page
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_600, ClipToRect_600) {
    state->clipToRect(100, 100, 200, 200);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 100.0);
    EXPECT_GE(yMin, 100.0);
    EXPECT_LE(xMax, 200.0);
    EXPECT_LE(yMax, 200.0);
}

// --- Text positioning ---

TEST_F(GfxStateTest_600, TextMoveTo_600) {
    state->textMoveTo(15.0, 25.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 15.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 25.0);
}

// --- Construction with rotation ---

TEST_F(GfxStateTest_600, ConstructionWithRotation90_600) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_600, ConstructionWithRotation180_600) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

TEST_F(GfxStateTest_600, ConstructionWithRotation270_600) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

// --- Copy ---

TEST_F(GfxStateTest_600, CopyPreservesProperties_600) {
    state->setLineWidth(7.5);
    state->setFillOpacity(0.4);
    state->setLineCap((LineCapStyle)1);
    
    auto copied = std::unique_ptr<GfxState>(state->copy());
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.4);
    EXPECT_EQ(copied->getLineCap(), 1);
}

// --- TransformWidth ---

TEST_F(GfxStateTest_600, TransformWidthWithIdentity_600) {
    state->setCTM(1.0, 0, 0, 1.0, 0, 0);
    double w = state->transformWidth(5.0);
    EXPECT_NEAR(w, 5.0, 0.001);
}

TEST_F(GfxStateTest_600, TransformWidthWithScaling_600) {
    state->setCTM(2.0, 0, 0, 2.0, 0, 0);
    double w = state->transformWidth(5.0);
    EXPECT_NEAR(w, 10.0, 0.001);
}

// --- GetTransformedLineWidth ---

TEST_F(GfxStateTest_600, GetTransformedLineWidth_600) {
    state->setCTM(1.0, 0, 0, 1.0, 0, 0);
    state->setLineWidth(3.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_NEAR(tlw, 3.0, 0.001);
}

// --- Fill / Stroke Color ---

TEST_F(GfxStateTest_600, SetAndGetFillColor_600) {
    GfxColor color;
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_600, SetAndGetStrokeColor_600) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], 16384);
}

// --- GetPath ---

TEST_F(GfxStateTest_600, GetPathNotNull_600) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// --- UserClipBBox ---

TEST_F(GfxStateTest_600, GetUserClipBBox_600) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// --- Different DPI ---

TEST_F(GfxStateTest_600, HighDPIConstruction_600) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState highDpi(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpi.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpi.getVDPI(), 300.0);
}

TEST_F(GfxStateTest_600, DifferentHVDPI_600) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState diffDpi(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(diffDpi.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(diffDpi.getVDPI(), 300.0);
}

// --- ShiftCTMAndClip ---

TEST_F(GfxStateTest_600, ShiftCTMAndClip_600) {
    state->setCTM(1.0, 0, 0, 1.0, 0, 0);
    state->shiftCTMAndClip(50.0, 60.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 60.0);
}

// --- Multiple save/restore ---

TEST_F(GfxStateTest_600, MultipleSaveRestore_600) {
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
    EXPECT_FALSE(r0->hasSaves());
}

// --- Boundary: zero-size page ---

TEST_F(GfxStateTest_600, ZeroSizePage_600) {
    PDFRectangle pageBox = makePageBox(0, 0, 0, 0);
    GfxState zeroState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(zeroState.getPageWidth(), 0.0);
    EXPECT_DOUBLE_EQ(zeroState.getPageHeight(), 0.0);
}

// --- Boundary: negative coordinates in page box ---

TEST_F(GfxStateTest_600, NegativePageBox_600) {
    PDFRectangle pageBox = makePageBox(-100, -100, 100, 100);
    GfxState negState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(negState.getX1(), -100.0);
    EXPECT_DOUBLE_EQ(negState.getY1(), -100.0);
    EXPECT_DOUBLE_EQ(negState.getX2(), 100.0);
    EXPECT_DOUBLE_EQ(negState.getY2(), 100.0);
}

// --- GetReusablePath ---

TEST_F(GfxStateTest_600, GetReusablePath_600) {
    state->moveTo(0, 0);
    state->lineTo(100, 100);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// --- FillColorSpace and StrokeColorSpace initially ---

TEST_F(GfxStateTest_600, InitialFillColorSpace_600) {
    GfxColorSpace *cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_600, InitialStrokeColorSpace_600) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// --- Fill/Stroke Pattern initially null ---

TEST_F(GfxStateTest_600, InitialFillPattern_600) {
    GfxPattern *p = state->getFillPattern();
    EXPECT_EQ(p, nullptr);
}

TEST_F(GfxStateTest_600, InitialStrokePattern_600) {
    GfxPattern *p = state->getStrokePattern();
    EXPECT_EQ(p, nullptr);
}

// --- TextShift ---

TEST_F(GfxStateTest_600, TextShift_600) {
    state->setCTM(1.0, 0, 0, 1.0, 0, 0);
    state->setTextMat(1.0, 0, 0, 1.0, 0, 0);
    double oldX = state->getCurX();
    double oldY = state->getCurY();
    state->textShift(5.0, 0.0);
    // CurX should have changed
    EXPECT_NE(state->getCurX(), oldX);
}

// --- GetCTM as Matrix ---

TEST_F(GfxStateTest_600, GetCTMAsMatrix_600) {
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
