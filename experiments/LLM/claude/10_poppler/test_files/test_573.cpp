#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"

// Helper to create a PDFRectangle for test construction
static PDFRectangle makePageBox(double x1, double y1, double x2, double y2) {
    PDFRectangle r;
    r.x1 = x1;
    r.y1 = y1;
    r.x2 = x2;
    r.y2 = y2;
    return r;
}

class GfxStateTest_573 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// ==================== Construction and Basic Getters ====================

TEST_F(GfxStateTest_573, ConstructionSetsHDPI_573) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_573, ConstructionSetsVDPI_573) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_573, ConstructionSetsPageWidth_573) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_573, ConstructionSetsPageHeight_573) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_573, ConstructionSetsRotate_573) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_573, ConstructionWithRotation90_573) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_573, ConstructionWithRotation180_573) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

TEST_F(GfxStateTest_573, ConstructionWithRotation270_573) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

TEST_F(GfxStateTest_573, PageBoundsX1Y1_573) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
}

TEST_F(GfxStateTest_573, PageBoundsX2Y2_573) {
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// ==================== CTM ====================

TEST_F(GfxStateTest_573, GetCTMReturnsArray_573) {
    const auto& ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_573, SetCTMChangesValues_573) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_573, ConcatCTM_573) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 5.0);
    EXPECT_DOUBLE_EQ(ctm[5], 10.0);
}

// ==================== Transform ====================

TEST_F(GfxStateTest_573, TransformWithIdentityCTM_573) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_573, TransformWithScaling_573) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

TEST_F(GfxStateTest_573, TransformWithTranslation_573) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 105.0);
    EXPECT_DOUBLE_EQ(y2, 210.0);
}

TEST_F(GfxStateTest_573, TransformDeltaIgnoresTranslation_573) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// ==================== Line Properties ====================

TEST_F(GfxStateTest_573, SetAndGetLineWidth_573) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_573, SetAndGetLineWidthZero_573) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_573, SetAndGetMiterLimit_573) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

TEST_F(GfxStateTest_573, SetAndGetFlatness_573) {
    state->setFlatness(10);
    EXPECT_EQ(state->getFlatness(), 10);
}

TEST_F(GfxStateTest_573, SetAndGetLineJoin_573) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_573, SetAndGetLineCap_573) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

TEST_F(GfxStateTest_573, SetLineDash_573) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto& d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 2.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

TEST_F(GfxStateTest_573, SetLineDashEmpty_573) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto& d = state->getLineDash(&start);
    EXPECT_TRUE(d.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// ==================== Opacity and Blend ====================

TEST_F(GfxStateTest_573, SetAndGetFillOpacity_573) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_573, SetAndGetStrokeOpacity_573) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_573, SetAndGetFillOpacityBoundary_573) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_573, SetAndGetBlendMode_573) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// ==================== Overprint ====================

TEST_F(GfxStateTest_573, SetAndGetFillOverprint_573) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_573, SetAndGetStrokeOverprint_573) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_573, SetAndGetOverprintMode_573) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
    state->setOverprintMode(0);
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// ==================== Text Properties ====================

TEST_F(GfxStateTest_573, SetAndGetCharSpace_573) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_573, SetAndGetWordSpace_573) {
    state->setWordSpace(2.5);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.5);
}

TEST_F(GfxStateTest_573, SetAndGetHorizScaling_573) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_573, SetAndGetLeading_573) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

TEST_F(GfxStateTest_573, SetAndGetRise_573) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_573, SetAndGetRender_573) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_573, SetAndGetTextMat_573) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto& mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 2.0);
    EXPECT_DOUBLE_EQ(mat[2], 3.0);
    EXPECT_DOUBLE_EQ(mat[3], 4.0);
    EXPECT_DOUBLE_EQ(mat[4], 5.0);
    EXPECT_DOUBLE_EQ(mat[5], 6.0);
}

// ==================== Stroke Adjust and Alpha ====================

TEST_F(GfxStateTest_573, SetAndGetStrokeAdjust_573) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_573, SetAndGetAlphaIsShape_573) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_573, SetAndGetTextKnockout_573) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// ==================== Rendering Intent ====================

TEST_F(GfxStateTest_573, SetAndGetRenderingIntent_573) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_573, SetRenderingIntentRelativeColorimetric_573) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_573, SetRenderingIntentAbsoluteColorimetric_573) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

TEST_F(GfxStateTest_573, SetRenderingIntentSaturation_573) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

// ==================== Path Operations ====================

TEST_F(GfxStateTest_573, InitiallyNoPath_573) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_573, MoveToSetsCurPt_573) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_573, LineToCreatesPath_573) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_573, CurveToCreatesPath_573) {
    state->moveTo(0.0, 0.0);
    state->curveTo(5.0, 5.0, 10.0, 10.0, 15.0, 15.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_573, ClosePathOnSimplePath_573) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_573, ClearPathResetsState_573) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_573, GetPathReturnsNonNull_573) {
    state->moveTo(0.0, 0.0);
    const GfxPath* path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// ==================== Text Position ====================

TEST_F(GfxStateTest_573, TextMoveTo_573) {
    state->textMoveTo(100.0, 200.0);
    // After textMoveTo, lineX/lineY should be updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// ==================== Save / Restore ====================

TEST_F(GfxStateTest_573, InitiallyNoSaves_573) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_573, SaveCreatesSavedState_573) {
    GfxState* saved = state->save();
    EXPECT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());
}

TEST_F(GfxStateTest_573, RestoreReturnsPreviousState_573) {
    state->setLineWidth(5.0);
    GfxState* saved = state->save();
    // saved is the new current state
    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 10.0);
    
    GfxState* restored = saved->restore();
    EXPECT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_573, MultipleSaveRestore_573) {
    state->setFillOpacity(1.0);
    GfxState* s1 = state->save();
    s1->setFillOpacity(0.5);
    GfxState* s2 = s1->save();
    s2->setFillOpacity(0.25);
    
    EXPECT_DOUBLE_EQ(s2->getFillOpacity(), 0.25);
    GfxState* r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getFillOpacity(), 0.5);
    GfxState* r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_573, HasSavesAfterMultipleSaves_573) {
    GfxState* s1 = state->save();
    EXPECT_TRUE(state->hasSaves());
    GfxState* s2 = s1->save();
    EXPECT_TRUE(s1->hasSaves());
    s2->restore();
    s1->restore();
    EXPECT_FALSE(state->hasSaves());
}

// ==================== Copy ====================

TEST_F(GfxStateTest_573, CopyPreservesProperties_573) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.7);
    auto copied = state->copy();
    EXPECT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);
    delete copied;
}

// ==================== Clip ====================

TEST_F(GfxStateTest_573, ClipBBoxInitial_573) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip bbox should be initialized to something covering the page
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_573, ClipToRect_573) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the clip bbox should be no larger than the rect
    EXPECT_GE(xMin, 100.0 - 1e-6);
    EXPECT_GE(yMin, 100.0 - 1e-6);
    EXPECT_LE(xMax, 200.0 + 1e-6);
    EXPECT_LE(yMax, 200.0 + 1e-6);
}

TEST_F(GfxStateTest_573, UserClipBBox_573) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// ==================== Font ====================

TEST_F(GfxStateTest_573, InitialFontIsNull_573) {
    const auto& font = state->getFont();
    // Initially no font is set
    EXPECT_EQ(font, nullptr);
}

TEST_F(GfxStateTest_573, GetFontSizeDefault_573) {
    double fs = state->getFontSize();
    // Default font size
    EXPECT_DOUBLE_EQ(fs, 0.0);
}

// ==================== Color Space / Pattern ====================

TEST_F(GfxStateTest_573, InitialFillColorSpaceNotNull_573) {
    // Default fill color space should be DeviceGray
    GfxColorSpace* cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_573, InitialStrokeColorSpaceNotNull_573) {
    GfxColorSpace* cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_573, InitialFillPatternNull_573) {
    GfxPattern* pat = state->getFillPattern();
    EXPECT_EQ(pat, nullptr);
}

TEST_F(GfxStateTest_573, InitialStrokePatternNull_573) {
    GfxPattern* pat = state->getStrokePattern();
    EXPECT_EQ(pat, nullptr);
}

// ==================== Fill/Stroke Color ====================

TEST_F(GfxStateTest_573, GetFillColorNotNull_573) {
    const GfxColor* color = state->getFillColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_573, GetStrokeColorNotNull_573) {
    const GfxColor* color = state->getStrokeColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_573, SetFillColorAndGet_573) {
    GfxColor color;
    color.c[0] = 32768; // approximately 0.5 in fixed point
    state->setFillColor(&color);
    const GfxColor* retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_573, SetStrokeColorAndGet_573) {
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor* retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], 65535);
}

// ==================== Different Page Box Sizes ====================

TEST_F(GfxStateTest_573, SmallPageBox_573) {
    PDFRectangle pageBox = makePageBox(0, 0, 1, 1);
    GfxState smallState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(smallState.getPageWidth(), 1.0);
    EXPECT_DOUBLE_EQ(smallState.getPageHeight(), 1.0);
}

TEST_F(GfxStateTest_573, LargePageBox_573) {
    PDFRectangle pageBox = makePageBox(0, 0, 10000, 10000);
    GfxState largeState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(largeState.getPageWidth(), 10000.0);
    EXPECT_DOUBLE_EQ(largeState.getPageHeight(), 10000.0);
}

TEST_F(GfxStateTest_573, NonZeroOriginPageBox_573) {
    PDFRectangle pageBox = makePageBox(100, 200, 400, 600);
    GfxState offsetState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(offsetState.getPageWidth(), 300.0);
    EXPECT_DOUBLE_EQ(offsetState.getPageHeight(), 400.0);
}

// ==================== Different DPI ====================

TEST_F(GfxStateTest_573, HighDPI_573) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState hiDpi(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(hiDpi.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(hiDpi.getVDPI(), 300.0);
}

TEST_F(GfxStateTest_573, AsymmetricDPI_573) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState asymDpi(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(asymDpi.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(asymDpi.getVDPI(), 300.0);
}

// ==================== ShiftCTMAndClip ====================

TEST_F(GfxStateTest_573, ShiftCTMAndClip_573) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 100.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 100.0);
}

// ==================== TransformWidth ====================

TEST_F(GfxStateTest_573, TransformWidthWithIdentity_573) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_DOUBLE_EQ(w, 1.0);
}

TEST_F(GfxStateTest_573, TransformWidthWithScaling_573) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_DOUBLE_EQ(w, 2.0);
}

// ==================== GetTransformedLineWidth ====================

TEST_F(GfxStateTest_573, GetTransformedLineWidth_573) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tw, 3.0);
}

// ==================== isParentState ====================

TEST_F(GfxStateTest_573, IsParentStateTrue_573) {
    GfxState* child = state->save();
    EXPECT_TRUE(state->isParentState(child));
    child->restore();
}

TEST_F(GfxStateTest_573, IsParentStateFalse_573) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState other(72.0, 72.0, &pageBox, 0, true);
    EXPECT_FALSE(state->isParentState(&other));
}

// ==================== parseBlendMode (static) ====================

TEST_F(GfxStateTest_573, ParseBlendModeNormal_573) {
    Object obj(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, GfxBlendMode::Normal);
}

TEST_F(GfxStateTest_573, ParseBlendModeMultiply_573) {
    Object obj(new GooString("Multiply"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, GfxBlendMode::Multiply);
}

// ==================== Cursor positions ====================

TEST_F(GfxStateTest_573, InitialCursorPosition_573) {
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// ==================== ReusablePathIterator ====================

TEST_F(GfxStateTest_573, GetReusablePathNotNull_573) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// ==================== UpsideDown false ====================

TEST_F(GfxStateTest_573, ConstructionUpsideDownFalse_573) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState notFlipped(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(notFlipped.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(notFlipped.getPageHeight(), 792.0);
}
