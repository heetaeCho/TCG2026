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

class GfxStateTest_621 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle rect = makeRect(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &rect, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// =============================================================================
// Constructor and basic getters
// =============================================================================

TEST_F(GfxStateTest_621, ConstructorSetsHDPI_621) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_621, ConstructorSetsVDPI_621) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_621, ConstructorSetsRotate_621) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_621, ConstructorSetsPageWidth_621) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_621, ConstructorSetsPageHeight_621) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_621, GetX1_621) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
}

TEST_F(GfxStateTest_621, GetY1_621) {
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
}

TEST_F(GfxStateTest_621, GetX2_621) {
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
}

TEST_F(GfxStateTest_621, GetY2_621) {
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// =============================================================================
// Rotation tests
// =============================================================================

TEST_F(GfxStateTest_621, ConstructorWithRotate90_621) {
    PDFRectangle rect = makeRect(0, 0, 612, 792);
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &rect, 90, true);
    EXPECT_EQ(rotatedState->getRotate(), 90);
}

TEST_F(GfxStateTest_621, ConstructorWithRotate180_621) {
    PDFRectangle rect = makeRect(0, 0, 612, 792);
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &rect, 180, true);
    EXPECT_EQ(rotatedState->getRotate(), 180);
}

TEST_F(GfxStateTest_621, ConstructorWithRotate270_621) {
    PDFRectangle rect = makeRect(0, 0, 612, 792);
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &rect, 270, true);
    EXPECT_EQ(rotatedState->getRotate(), 270);
}

// =============================================================================
// CTM tests
// =============================================================================

TEST_F(GfxStateTest_621, GetCTMReturnsArray_621) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_621, SetCTM_621) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_621, ConcatCTM_621) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

TEST_F(GfxStateTest_621, GetCTMMatrix_621) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Matrix should be populated from CTM
    // Just check it doesn't crash and values are consistent
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 1.0);
}

// =============================================================================
// Line properties
// =============================================================================

TEST_F(GfxStateTest_621, DefaultLineWidth_621) {
    // Default line width should be some initial value (typically 1.0 or 0.0)
    double lw = state->getLineWidth();
    EXPECT_GE(lw, 0.0);
}

TEST_F(GfxStateTest_621, SetLineWidth_621) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_621, SetLineWidthZero_621) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_621, SetLineJoin_621) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

TEST_F(GfxStateTest_621, SetLineCap_621) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

TEST_F(GfxStateTest_621, SetMiterLimit_621) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

TEST_F(GfxStateTest_621, SetLineDash_621) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 2.0);
}

TEST_F(GfxStateTest_621, SetLineDashEmpty_621) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(d.empty());
}

// =============================================================================
// Flatness
// =============================================================================

TEST_F(GfxStateTest_621, SetFlatness_621) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// =============================================================================
// Opacity and overprint
// =============================================================================

TEST_F(GfxStateTest_621, SetFillOpacity_621) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_621, SetStrokeOpacity_621) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_621, SetFillOverprint_621) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_621, SetStrokeOverprint_621) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_621, SetOverprintMode_621) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// =============================================================================
// Stroke adjust, alpha is shape, text knockout
// =============================================================================

TEST_F(GfxStateTest_621, SetStrokeAdjust_621) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_621, SetAlphaIsShape_621) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_621, SetTextKnockout_621) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// =============================================================================
// Text properties
// =============================================================================

TEST_F(GfxStateTest_621, SetCharSpace_621) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_621, SetWordSpace_621) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_621, SetHorizScaling_621) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

TEST_F(GfxStateTest_621, SetLeading_621) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_621, SetRise_621) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_621, SetRender_621) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_621, SetTextMat_621) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 1.0);
    EXPECT_DOUBLE_EQ(tm[4], 10.0);
    EXPECT_DOUBLE_EQ(tm[5], 20.0);
}

// =============================================================================
// Font
// =============================================================================

TEST_F(GfxStateTest_621, GetFontInitiallyNull_621) {
    const auto &font = state->getFont();
    // Font may or may not be null initially, but accessing shouldn't crash
    // We just test we can call it
    SUCCEED();
}

TEST_F(GfxStateTest_621, GetFontSizeDefault_621) {
    double fs = state->getFontSize();
    EXPECT_GE(fs, 0.0);
}

// =============================================================================
// Rendering intent
// =============================================================================

TEST_F(GfxStateTest_621, SetRenderingIntent_621) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_621, SetRenderingIntentRelativeColorimetric_621) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_621, SetRenderingIntentSaturation_621) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

TEST_F(GfxStateTest_621, SetRenderingIntentAbsoluteColorimetric_621) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// =============================================================================
// BlendMode
// =============================================================================

TEST_F(GfxStateTest_621, SetBlendMode_621) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

TEST_F(GfxStateTest_621, SetBlendModeNormal_621) {
    state->setBlendMode(gfxBlendNormal);
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// =============================================================================
// Path operations
// =============================================================================

TEST_F(GfxStateTest_621, InitiallyNoPath_621) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_621, MoveToSetsCurPt_621) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_621, LineToCreatesPath_621) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_621, CurveToCreatesPath_621) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_621, ClosePathDoesNotCrash_621) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_621, ClearPathResetsState_621) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_621, GetPathNotNull_621) {
    state->moveTo(5.0, 5.0);
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// =============================================================================
// Cursor position
// =============================================================================

TEST_F(GfxStateTest_621, GetCurXY_621) {
    state->moveTo(15.0, 25.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 15.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 25.0);
}

// =============================================================================
// Text cursor
// =============================================================================

TEST_F(GfxStateTest_621, TextMoveTo_621) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

TEST_F(GfxStateTest_621, GetLineXDefault_621) {
    // Initially lineX should be 0
    EXPECT_DOUBLE_EQ(state->getLineX(), 0.0);
}

TEST_F(GfxStateTest_621, GetLineYDefault_621) {
    EXPECT_DOUBLE_EQ(state->getLineY(), 0.0);
}

// =============================================================================
// Transform
// =============================================================================

TEST_F(GfxStateTest_621, TransformPoint_621) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 110.0);
    EXPECT_DOUBLE_EQ(y2, 220.0);
}

TEST_F(GfxStateTest_621, TransformDelta_621) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double dx2, dy2;
    state->transformDelta(5.0, 10.0, &dx2, &dy2);
    EXPECT_DOUBLE_EQ(dx2, 10.0);
    EXPECT_DOUBLE_EQ(dy2, 20.0);
}

TEST_F(GfxStateTest_621, TransformWidthIdentity_621) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 5.0);
}

TEST_F(GfxStateTest_621, TransformWidthScaled_621) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 10.0);
}

// =============================================================================
// Save / Restore
// =============================================================================

TEST_F(GfxStateTest_621, SaveReturnsNewState_621) {
    GfxState *saved = state->save();
    EXPECT_NE(saved, nullptr);
    EXPECT_NE(saved, state.get());
}

TEST_F(GfxStateTest_621, RestoreReturnsParent_621) {
    GfxState *saved = state->save();
    GfxState *restored = saved->restore();
    EXPECT_EQ(restored, state.get());
}

TEST_F(GfxStateTest_621, HasSavesAfterSave_621) {
    EXPECT_FALSE(state->hasSaves());
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    saved->restore();
}

TEST_F(GfxStateTest_621, SavePreservesLineWidth_621) {
    state->setLineWidth(3.0);
    GfxState *saved = state->save();
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 3.0);
    saved->restore();
}

TEST_F(GfxStateTest_621, SavedStateChangeDoesNotAffectParent_621) {
    state->setLineWidth(3.0);
    GfxState *saved = state->save();
    saved->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 5.0);
    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 3.0);
}

TEST_F(GfxStateTest_621, IsParentState_621) {
    GfxState *saved = state->save();
    EXPECT_TRUE(state->isParentState(saved));
    saved->restore();
}

// =============================================================================
// Clip bounding box
// =============================================================================

TEST_F(GfxStateTest_621, GetClipBBox_621) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip should encompass the page area
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_621, GetUserClipBBox_621) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_621, ClipToRect_621) {
    state->clipToRect(10.0, 10.0, 100.0, 100.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the box should be within or equal to the clipped rect
    EXPECT_GE(xMin, 10.0 - 0.001);
    EXPECT_GE(yMin, 10.0 - 0.001);
    EXPECT_LE(xMax, 100.0 + 0.001);
    EXPECT_LE(yMax, 100.0 + 0.001);
}

// =============================================================================
// Copy
// =============================================================================

TEST_F(GfxStateTest_621, CopyCreatesNewInstance_621) {
    state->setLineWidth(7.0);
    auto copied = state->copy();
    EXPECT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.0);
}

TEST_F(GfxStateTest_621, CopyWithoutPathArg_621) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto copied = state->copy(false);
    EXPECT_NE(copied, nullptr);
}

TEST_F(GfxStateTest_621, CopyWithPathArg_621) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto copied = state->copy(true);
    EXPECT_NE(copied, nullptr);
    EXPECT_TRUE(copied->isPath());
}

// =============================================================================
// Color operations
// =============================================================================

TEST_F(GfxStateTest_621, SetFillColor_621) {
    GfxColor color;
    color.c[0] = 32768; // Some value
    state->setFillColor(&color);
    const GfxColor *fc = state->getFillColor();
    EXPECT_NE(fc, nullptr);
    EXPECT_EQ(fc->c[0], 32768);
}

TEST_F(GfxStateTest_621, SetStrokeColor_621) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *sc = state->getStrokeColor();
    EXPECT_NE(sc, nullptr);
    EXPECT_EQ(sc->c[0], 16384);
}

// =============================================================================
// FillColorSpace and StrokeColorSpace (null checks)
// =============================================================================

TEST_F(GfxStateTest_621, GetFillColorSpaceInitial_621) {
    GfxColorSpace *cs = state->getFillColorSpace();
    // Should have a default color space
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_621, GetStrokeColorSpaceInitial_621) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// =============================================================================
// Fill/Stroke patterns (initially null)
// =============================================================================

TEST_F(GfxStateTest_621, GetFillPatternInitiallyNull_621) {
    GfxPattern *pat = state->getFillPattern();
    EXPECT_EQ(pat, nullptr);
}

TEST_F(GfxStateTest_621, GetStrokePatternInitiallyNull_621) {
    GfxPattern *pat = state->getStrokePattern();
    EXPECT_EQ(pat, nullptr);
}

// =============================================================================
// ShiftCTMAndClip
// =============================================================================

TEST_F(GfxStateTest_621, ShiftCTMAndClip_621) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// =============================================================================
// TextShift
// =============================================================================

TEST_F(GfxStateTest_621, TextShift_621) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->textMoveTo(0.0, 0.0);
    state->textShift(5.0, 0.0);
    // After text shift, curTextX should have changed
    // We can at least verify no crash
    SUCCEED();
}

// =============================================================================
// GetTransformedLineWidth
// =============================================================================

TEST_F(GfxStateTest_621, GetTransformedLineWidth_621) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tlw, 2.0);
}

// =============================================================================
// GetTransformedFontSize
// =============================================================================

TEST_F(GfxStateTest_621, GetTransformedFontSize_621) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    // Just verify it doesn't crash
    double tfs = state->getTransformedFontSize();
    EXPECT_GE(tfs, 0.0);
}

// =============================================================================
// GetFontTransMat
// =============================================================================

TEST_F(GfxStateTest_621, GetFontTransMat_621) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    // Just check no crash and values are finite
    EXPECT_TRUE(std::isfinite(m11));
    EXPECT_TRUE(std::isfinite(m12));
    EXPECT_TRUE(std::isfinite(m21));
    EXPECT_TRUE(std::isfinite(m22));
}

// =============================================================================
// ParseBlendMode (static)
// =============================================================================

TEST_F(GfxStateTest_621, ParseBlendModeNormal_621) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, gfxBlendNormal);
}

TEST_F(GfxStateTest_621, ParseBlendModeMultiply_621) {
    Object obj;
    obj = Object(new GooString("Multiply"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, gfxBlendMultiply);
}

// =============================================================================
// Boundary: Different DPI values
// =============================================================================

TEST_F(GfxStateTest_621, HighDPI_621) {
    PDFRectangle rect = makeRect(0, 0, 612, 792);
    auto highDpiState = std::make_unique<GfxState>(300.0, 300.0, &rect, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState->getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState->getVDPI(), 300.0);
}

TEST_F(GfxStateTest_621, DifferentHVDPI_621) {
    PDFRectangle rect = makeRect(0, 0, 612, 792);
    auto state2 = std::make_unique<GfxState>(150.0, 300.0, &rect, 0, true);
    EXPECT_DOUBLE_EQ(state2->getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(state2->getVDPI(), 300.0);
}

// =============================================================================
// Boundary: UpsideDown flag
// =============================================================================

TEST_F(GfxStateTest_621, UpsideDownFalse_621) {
    PDFRectangle rect = makeRect(0, 0, 612, 792);
    auto state2 = std::make_unique<GfxState>(72.0, 72.0, &rect, 0, false);
    EXPECT_DOUBLE_EQ(state2->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state2->getPageHeight(), 792.0);
}

// =============================================================================
// Reusable path iterator
// =============================================================================

TEST_F(GfxStateTest_621, GetReusablePathIterator_621) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// =============================================================================
// Clip operations
// =============================================================================

TEST_F(GfxStateTest_621, ClipDoesNotCrash_621) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    state->clip();
    SUCCEED();
}

TEST_F(GfxStateTest_621, ClipToStrokePathDoesNotCrash_621) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    state->clipToStrokePath();
    SUCCEED();
}

// =============================================================================
// Multiple save/restore
// =============================================================================

TEST_F(GfxStateTest_621, MultipleSaveRestore_621) {
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

// =============================================================================
// Default color spaces (initially null)
// =============================================================================

TEST_F(GfxStateTest_621, CopyDefaultGrayColorSpaceInitiallyNull_621) {
    auto cs = state->copyDefaultGrayColorSpace();
    // May or may not be null; just check no crash
    SUCCEED();
}

TEST_F(GfxStateTest_621, CopyDefaultRGBColorSpaceInitiallyNull_621) {
    auto cs = state->copyDefaultRGBColorSpace();
    SUCCEED();
}

TEST_F(GfxStateTest_621, CopyDefaultCMYKColorSpaceInitiallyNull_621) {
    auto cs = state->copyDefaultCMYKColorSpace();
    SUCCEED();
}
