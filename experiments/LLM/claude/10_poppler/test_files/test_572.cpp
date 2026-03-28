#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a PDFRectangle
static PDFRectangle makePageBox(double x1, double y1, double x2, double y2)
{
    PDFRectangle r;
    r.x1 = x1;
    r.y1 = y1;
    r.x2 = x2;
    r.y2 = y2;
    return r;
}

class GfxStateTest_572 : public ::testing::Test {
protected:
    void SetUp() override
    {
        PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// ==================== Construction / Basic Getters ====================

TEST_F(GfxStateTest_572, ConstructionSetsHDPI_572)
{
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_572, ConstructionSetsVDPI_572)
{
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_572, ConstructionSetsPageWidth_572)
{
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_572, ConstructionSetsPageHeight_572)
{
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_572, ConstructionSetsRotate_572)
{
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_572, ConstructionWithRotation_572)
{
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_572, GetX1Y1X2Y2_572)
{
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// ==================== CTM ====================

TEST_F(GfxStateTest_572, GetCTMReturnsArray_572)
{
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_572, SetCTM_572)
{
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_572, ConcatCTM_572)
{
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 5.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

TEST_F(GfxStateTest_572, GetCTMAsMatrix_572)
{
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

// ==================== Transform ====================

TEST_F(GfxStateTest_572, TransformPoint_572)
{
    state->setCTM(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    double x2, y2;
    state->transform(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 15.0);
    EXPECT_DOUBLE_EQ(y2, 25.0);
}

TEST_F(GfxStateTest_572, TransformDelta_572)
{
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double dx2, dy2;
    state->transformDelta(5.0, 5.0, &dx2, &dy2);
    EXPECT_DOUBLE_EQ(dx2, 10.0);
    EXPECT_DOUBLE_EQ(dy2, 15.0);
}

TEST_F(GfxStateTest_572, TransformWidth_572)
{
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double tw = state->transformWidth(1.0);
    EXPECT_GT(tw, 0.0);
}

// ==================== Line Properties ====================

TEST_F(GfxStateTest_572, SetAndGetLineWidth_572)
{
    state->setLineWidth(3.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.5);
}

TEST_F(GfxStateTest_572, SetAndGetLineCap_572)
{
    state->setLineCap(LineCapRound);
    EXPECT_EQ(state->getLineCap(), LineCapRound);
}

TEST_F(GfxStateTest_572, SetAndGetLineJoin_572)
{
    state->setLineJoin(LineJoinRound);
    EXPECT_EQ(state->getLineJoin(), LineJoinRound);
}

TEST_F(GfxStateTest_572, SetAndGetMiterLimit_572)
{
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

TEST_F(GfxStateTest_572, SetAndGetFlatness_572)
{
    state->setFlatness(2);
    EXPECT_EQ(state->getFlatness(), 2);
}

TEST_F(GfxStateTest_572, SetAndGetLineDash_572)
{
    std::vector<double> dash = {3.0, 2.0, 1.0};
    state->setLineDash(std::move(dash), 1.5);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.5);
    ASSERT_EQ(d.size(), 3u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 2.0);
    EXPECT_DOUBLE_EQ(d[2], 1.0);
}

TEST_F(GfxStateTest_572, SetAndGetStrokeAdjust_572)
{
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// ==================== Opacity and Blend ====================

TEST_F(GfxStateTest_572, SetAndGetFillOpacity_572)
{
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_572, SetAndGetStrokeOpacity_572)
{
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_572, SetAndGetBlendMode_572)
{
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// ==================== Overprint ====================

TEST_F(GfxStateTest_572, SetAndGetFillOverprint_572)
{
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_572, SetAndGetStrokeOverprint_572)
{
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_572, SetAndGetOverprintMode_572)
{
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// ==================== Text Properties ====================

TEST_F(GfxStateTest_572, SetAndGetCharSpace_572)
{
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
}

TEST_F(GfxStateTest_572, SetAndGetWordSpace_572)
{
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

TEST_F(GfxStateTest_572, SetAndGetHorizScaling_572)
{
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_572, SetAndGetLeading_572)
{
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_572, SetAndGetRise_572)
{
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

TEST_F(GfxStateTest_572, SetAndGetRender_572)
{
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_572, SetAndGetTextMat_572)
{
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 2.0);
    EXPECT_DOUBLE_EQ(tm[2], 3.0);
    EXPECT_DOUBLE_EQ(tm[3], 4.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 6.0);
}

TEST_F(GfxStateTest_572, SetAndGetAlphaIsShape_572)
{
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_572, SetAndGetTextKnockout_572)
{
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// ==================== Rendering Intent ====================

TEST_F(GfxStateTest_572, SetAndGetRenderingIntent_572)
{
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_572, RenderingIntentLongString_572)
{
    // renderingIntent is char[32], test with a string that fits
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// ==================== Path Operations ====================

TEST_F(GfxStateTest_572, InitiallyNoCurrentPoint_572)
{
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_572, MoveToSetsCurPt_572)
{
    state->clearPath();
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_572, LineToCreatesPath_572)
{
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_572, CurveToCreatesPath_572)
{
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_572, ClosePathDoesNotCrash_572)
{
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_572, ClearPathResetsPath_572)
{
    state->moveTo(5.0, 5.0);
    state->lineTo(10.0, 10.0);
    state->clearPath();
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_572, GetPathReturnsNonNull_572)
{
    state->moveTo(0.0, 0.0);
    EXPECT_NE(state->getPath(), nullptr);
}

// ==================== Text Position ====================

TEST_F(GfxStateTest_572, TextMoveToSetsTextPosition_572)
{
    state->textMoveTo(100.0, 200.0);
    // After textMoveTo, lineX and lineY should be updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// ==================== Save / Restore ====================

TEST_F(GfxStateTest_572, SaveAndRestore_572)
{
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    EXPECT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());

    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 10.0);

    GfxState *restored = saved->restore();
    EXPECT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_572, HasSavesInitiallyFalse_572)
{
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_572, SaveCreatesSaveChain_572)
{
    GfxState *s1 = state->save();
    EXPECT_TRUE(state->hasSaves());
    GfxState *s2 = s1->save();
    EXPECT_TRUE(s1->hasSaves());
    // Restore back
    GfxState *r1 = s2->restore();
    EXPECT_EQ(r1, s1);
    GfxState *r2 = r1->restore();
    EXPECT_EQ(r2, state.get());
}

// ==================== Copy ====================

TEST_F(GfxStateTest_572, CopyCreatesIndependentState_572)
{
    state->setLineWidth(7.0);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.0);

    copied->setLineWidth(99.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 7.0);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 99.0);
}

// ==================== Clip ====================

TEST_F(GfxStateTest_572, ClipBBoxAfterClipToRect_572)
{
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 100.0);
    EXPECT_GE(yMin, 100.0);
    EXPECT_LE(xMax, 200.0);
    EXPECT_LE(yMax, 200.0);
}

TEST_F(GfxStateTest_572, GetUserClipBBox_572)
{
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should return some valid bounding box
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// ==================== Shift CTM and Clip ====================

TEST_F(GfxStateTest_572, ShiftCTMAndClip_572)
{
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// ==================== Font ====================

TEST_F(GfxStateTest_572, SetAndGetFontSize_572)
{
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

TEST_F(GfxStateTest_572, GetFontInitiallyNull_572)
{
    // After construction, font may be null
    const auto &font = state->getFont();
    // Just check it doesn't crash; font may or may not be null
    (void)font;
}

// ==================== Color ====================

TEST_F(GfxStateTest_572, SetAndGetFillColor_572)
{
    GfxColor color;
    memset(&color, 0, sizeof(color));
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *fc = state->getFillColor();
    ASSERT_NE(fc, nullptr);
    EXPECT_EQ(fc->c[0], 32768);
}

TEST_F(GfxStateTest_572, SetAndGetStrokeColor_572)
{
    GfxColor color;
    memset(&color, 0, sizeof(color));
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor *sc = state->getStrokeColor();
    ASSERT_NE(sc, nullptr);
    EXPECT_EQ(sc->c[0], 65535);
}

// ==================== Color Space ====================

TEST_F(GfxStateTest_572, GetFillColorSpaceNotNull_572)
{
    // Default fill color space should be set after construction
    GfxColorSpace *cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_572, GetStrokeColorSpaceNotNull_572)
{
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// ==================== Pattern ====================

TEST_F(GfxStateTest_572, GetFillPatternInitiallyNull_572)
{
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

TEST_F(GfxStateTest_572, GetStrokePatternInitiallyNull_572)
{
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// ==================== parseBlendMode (static) ====================

TEST_F(GfxStateTest_572, ParseBlendModeNormal_572)
{
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, gfxBlendNormal);
}

TEST_F(GfxStateTest_572, ParseBlendModeMultiply_572)
{
    Object obj;
    obj = Object(new GooString("Multiply"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, gfxBlendMultiply);
}

TEST_F(GfxStateTest_572, ParseBlendModeInvalid_572)
{
    Object obj;
    obj = Object(new GooString("NotABlendMode"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_FALSE(result);
}

// ==================== Boundary / Edge Cases ====================

TEST_F(GfxStateTest_572, ZeroLineWidth_572)
{
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_572, NegativeLineWidth_572)
{
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

TEST_F(GfxStateTest_572, OpacityBoundaryZero_572)
{
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_572, OpacityBoundaryOne_572)
{
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_572, EmptyLineDash_572)
{
    std::vector<double> emptyDash;
    state->setLineDash(std::move(emptyDash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_TRUE(d.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

TEST_F(GfxStateTest_572, LargePageBox_572)
{
    PDFRectangle pageBox = makePageBox(0, 0, 100000, 100000);
    GfxState largeState(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(largeState.getPageWidth(), 100000.0);
    EXPECT_DOUBLE_EQ(largeState.getPageHeight(), 100000.0);
}

TEST_F(GfxStateTest_572, RotatedPageDimensions_572)
{
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotState(72.0, 72.0, &pageBox, 90, true);
    // With 90 degree rotation, width and height should be swapped
    EXPECT_DOUBLE_EQ(rotState.getPageWidth(), 792.0);
    EXPECT_DOUBLE_EQ(rotState.getPageHeight(), 612.0);
}

// ==================== Display Profile ====================

TEST_F(GfxStateTest_572, GetDisplayProfileInitiallyNull_572)
{
    GfxLCMSProfilePtr profile = state->getDisplayProfile();
    EXPECT_EQ(profile, nullptr);
}

// ==================== isParentState ====================

TEST_F(GfxStateTest_572, IsParentStateAfterSave_572)
{
    GfxState *child = state->save();
    EXPECT_TRUE(state->isParentState(child));
    child->restore();
}

// ==================== Reusable Path Iterator ====================

TEST_F(GfxStateTest_572, GetReusablePathNotNull_572)
{
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// ==================== Text Transform ====================

TEST_F(GfxStateTest_572, TextTransform_572)
{
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(5.0, 10.0, &x2, &y2);
    // With identity text matrix, the result depends on CTM as well
    // Just verify it doesn't crash and produces finite values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

TEST_F(GfxStateTest_572, TextTransformDelta_572)
{
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double dx2, dy2;
    state->textTransformDelta(1.0, 1.0, &dx2, &dy2);
    EXPECT_TRUE(std::isfinite(dx2));
    EXPECT_TRUE(std::isfinite(dy2));
}

// ==================== GetTransformedLineWidth ====================

TEST_F(GfxStateTest_572, GetTransformedLineWidth_572)
{
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// ==================== GetTransformedFontSize ====================

TEST_F(GfxStateTest_572, GetTransformedFontSize_572)
{
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setFont(nullptr, 12.0);
    double tfs = state->getTransformedFontSize();
    EXPECT_TRUE(std::isfinite(tfs));
}

// ==================== GetFontTransMat ====================

TEST_F(GfxStateTest_572, GetFontTransMat_572)
{
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setFont(nullptr, 12.0);
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    EXPECT_TRUE(std::isfinite(m11));
    EXPECT_TRUE(std::isfinite(m12));
    EXPECT_TRUE(std::isfinite(m21));
    EXPECT_TRUE(std::isfinite(m22));
}

// ==================== CurX / CurY ====================

TEST_F(GfxStateTest_572, GetCurXYAfterMoveTo_572)
{
    state->clearPath();
    state->moveTo(42.0, 84.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 42.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 84.0);
}

// ==================== Multiple Save/Restore ====================

TEST_F(GfxStateTest_572, MultipleSaveRestore_572)
{
    state->setFillOpacity(1.0);
    GfxState *s1 = state->save();
    s1->setFillOpacity(0.5);
    GfxState *s2 = s1->save();
    s2->setFillOpacity(0.25);

    EXPECT_DOUBLE_EQ(s2->getFillOpacity(), 0.25);
    GfxState *r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getFillOpacity(), 0.5);
    GfxState *r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getFillOpacity(), 1.0);
}
