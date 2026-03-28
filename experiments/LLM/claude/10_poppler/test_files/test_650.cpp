#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState with reasonable defaults
class GfxStateTest_650 : public ::testing::Test {
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

// Test setLeading and getLeading - normal value
TEST_F(GfxStateTest_650, SetLeadingNormalValue_650) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test setLeading and getLeading - zero value
TEST_F(GfxStateTest_650, SetLeadingZero_650) {
    state->setLeading(0.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test setLeading and getLeading - negative value
TEST_F(GfxStateTest_650, SetLeadingNegative_650) {
    state->setLeading(-12.5);
    EXPECT_DOUBLE_EQ(state->getLeading(), -12.5);
}

// Test setLeading and getLeading - large value
TEST_F(GfxStateTest_650, SetLeadingLargeValue_650) {
    state->setLeading(1e10);
    EXPECT_DOUBLE_EQ(state->getLeading(), 1e10);
}

// Test setLeading and getLeading - very small value
TEST_F(GfxStateTest_650, SetLeadingVerySmall_650) {
    state->setLeading(1e-15);
    EXPECT_DOUBLE_EQ(state->getLeading(), 1e-15);
}

// Test setLeading overwrites previous value
TEST_F(GfxStateTest_650, SetLeadingOverwrite_650) {
    state->setLeading(10.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 10.0);
    state->setLeading(20.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 20.0);
}

// Test initial DPI values
TEST_F(GfxStateTest_650, InitialDPIValues_650) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_650, PageDimensions_650) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test getRotate
TEST_F(GfxStateTest_650, GetRotate_650) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test setCharSpace and getCharSpace
TEST_F(GfxStateTest_650, SetCharSpace_650) {
    state->setCharSpace(2.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.5);
}

// Test setWordSpace and getWordSpace
TEST_F(GfxStateTest_650, SetWordSpace_650) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

// Test setHorizScaling and getHorizScaling
TEST_F(GfxStateTest_650, SetHorizScaling_650) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test setRise and getRise
TEST_F(GfxStateTest_650, SetRise_650) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

// Test setRender and getRender
TEST_F(GfxStateTest_650, SetRender_650) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test setLineWidth and getLineWidth
TEST_F(GfxStateTest_650, SetLineWidth_650) {
    state->setLineWidth(2.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.0);
}

// Test setLineWidth zero
TEST_F(GfxStateTest_650, SetLineWidthZero_650) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test setFlatness and getFlatness
TEST_F(GfxStateTest_650, SetFlatness_650) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test setMiterLimit and getMiterLimit
TEST_F(GfxStateTest_650, SetMiterLimit_650) {
    state->setMiterLimit(8.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 8.0);
}

// Test setLineJoin and getLineJoin
TEST_F(GfxStateTest_650, SetLineJoin_650) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// Test setLineCap and getLineCap
TEST_F(GfxStateTest_650, SetLineCap_650) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test setFillOpacity and getFillOpacity
TEST_F(GfxStateTest_650, SetFillOpacity_650) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test setStrokeOpacity and getStrokeOpacity
TEST_F(GfxStateTest_650, SetStrokeOpacity_650) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test setFillOverprint and getFillOverprint
TEST_F(GfxStateTest_650, SetFillOverprint_650) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setStrokeOverprint and getStrokeOverprint
TEST_F(GfxStateTest_650, SetStrokeOverprint_650) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test setOverprintMode and getOverprintMode
TEST_F(GfxStateTest_650, SetOverprintMode_650) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test setStrokeAdjust and getStrokeAdjust
TEST_F(GfxStateTest_650, SetStrokeAdjust_650) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test setAlphaIsShape and getAlphaIsShape
TEST_F(GfxStateTest_650, SetAlphaIsShape_650) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test setTextKnockout and getTextKnockout
TEST_F(GfxStateTest_650, SetTextKnockout_650) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test save and restore
TEST_F(GfxStateTest_650, SaveAndRestore_650) {
    state->setLeading(14.0);
    state->setLineWidth(3.0);

    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    EXPECT_DOUBLE_EQ(saved->getLeading(), 14.0);

    saved->setLeading(20.0);
    EXPECT_DOUBLE_EQ(saved->getLeading(), 20.0);

    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getLeading(), 14.0);
}

// Test hasSaves initially false
TEST_F(GfxStateTest_650, HasSavesInitiallyFalse_650) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after save
TEST_F(GfxStateTest_650, HasSavesAfterSave_650) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    // Restore to clean up
    saved->restore();
}

// Test moveTo and path operations
TEST_F(GfxStateTest_650, MoveToCreatesPath_650) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test isCurPt initially false
TEST_F(GfxStateTest_650, IsCurPtInitiallyFalse_650) {
    EXPECT_FALSE(state->isCurPt());
}

// Test isPath initially false
TEST_F(GfxStateTest_650, IsPathInitiallyFalse_650) {
    EXPECT_FALSE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_650, ClearPath_650) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test lineTo after moveTo
TEST_F(GfxStateTest_650, LineTo_650) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test curveTo after moveTo
TEST_F(GfxStateTest_650, CurveTo_650) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 10.0, 20.0, 20.0, 30.0, 30.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test closePath
TEST_F(GfxStateTest_650, ClosePath_650) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test setCTM and getCTM
TEST_F(GfxStateTest_650, SetCTM_650) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test transform
TEST_F(GfxStateTest_650, Transform_650) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test transform with translation
TEST_F(GfxStateTest_650, TransformWithTranslation_650) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 110.0);
    EXPECT_DOUBLE_EQ(y2, 220.0);
}

// Test transformDelta (no translation component)
TEST_F(GfxStateTest_650, TransformDelta_650) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 60.0);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_650, SetTextMat_650) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 5.0, 10.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 1.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 10.0);
}

// Test textMoveTo
TEST_F(GfxStateTest_650, TextMoveTo_650) {
    state->textMoveTo(50.0, 100.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 100.0);
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_650, SetLineDash_650) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

// Test setLineDash empty
TEST_F(GfxStateTest_650, SetLineDashEmpty_650) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_TRUE(d.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_650, SetRenderingIntent_650) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test setRenderingIntent with different values
TEST_F(GfxStateTest_650, SetRenderingIntentRelativeColorimetric_650) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test getClipBBox
TEST_F(GfxStateTest_650, GetClipBBox_650) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should return some valid bounding box
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect changes clip bounds
TEST_F(GfxStateTest_650, ClipToRect_650) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 100.0);
    EXPECT_GE(yMin, 100.0);
    EXPECT_LE(xMax, 200.0);
    EXPECT_LE(yMax, 200.0);
}

// Test copy
TEST_F(GfxStateTest_650, CopyState_650) {
    state->setLeading(12.0);
    state->setLineWidth(2.5);
    state->setCharSpace(1.0);

    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_DOUBLE_EQ(copied->getLeading(), 12.0);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 2.5);
    EXPECT_DOUBLE_EQ(copied->getCharSpace(), 1.0);
}

// Test page box coordinates
TEST_F(GfxStateTest_650, PageBoxCoordinates_650) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test with rotated page
TEST(GfxStateRotatedTest_650, RotatedPage_650) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test setBlendMode and getBlendMode
TEST_F(GfxStateTest_650, SetBlendMode_650) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test setFont and getFont/getFontSize
TEST_F(GfxStateTest_650, SetFontSize_650) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
    EXPECT_EQ(state->getFont(), nullptr);
}

// Test multiple setLeading calls
TEST_F(GfxStateTest_650, SetLeadingMultiple_650) {
    for (double v = -100.0; v <= 100.0; v += 25.0) {
        state->setLeading(v);
        EXPECT_DOUBLE_EQ(state->getLeading(), v);
    }
}

// Test getUserClipBBox
TEST_F(GfxStateTest_650, GetUserClipBBox_650) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test concatCTM
TEST_F(GfxStateTest_650, ConcatCTM_650) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test transformWidth
TEST_F(GfxStateTest_650, TransformWidth_650) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double tw = state->transformWidth(1.0);
    EXPECT_GT(tw, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_650, GetTransformedLineWidth_650) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(2.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tlw, 2.0);
}

// Test save/restore preserves state properly
TEST_F(GfxStateTest_650, SaveRestorePreservesMultipleProperties_650) {
    state->setLeading(15.0);
    state->setCharSpace(2.0);
    state->setWordSpace(3.0);
    state->setLineWidth(1.5);

    GfxState *s = state->save();
    s->setLeading(25.0);
    s->setCharSpace(4.0);
    s->setWordSpace(5.0);
    s->setLineWidth(3.0);

    EXPECT_DOUBLE_EQ(s->getLeading(), 25.0);

    GfxState *r = s->restore();
    EXPECT_DOUBLE_EQ(r->getLeading(), 15.0);
    EXPECT_DOUBLE_EQ(r->getCharSpace(), 2.0);
    EXPECT_DOUBLE_EQ(r->getWordSpace(), 3.0);
    EXPECT_DOUBLE_EQ(r->getLineWidth(), 1.5);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_650, ShiftCTMAndClip_650) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 50.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 50.0);
}
