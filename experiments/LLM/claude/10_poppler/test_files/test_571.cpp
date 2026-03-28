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

class GfxStateTest_571 : public ::testing::Test {
protected:
    void SetUp() override
    {
        PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// ==================== Basic construction and getters ====================

TEST_F(GfxStateTest_571, ConstructorSetsHDPI_571)
{
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_571, ConstructorSetsVDPI_571)
{
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_571, GetPageDimensions_571)
{
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_571, GetRotate_571)
{
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_571, GetPageBounds_571)
{
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// ==================== Rotation constructor ====================

TEST_F(GfxStateTest_571, ConstructorWithRotation90_571)
{
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_571, ConstructorWithRotation180_571)
{
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

TEST_F(GfxStateTest_571, ConstructorWithRotation270_571)
{
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

// ==================== CTM operations ====================

TEST_F(GfxStateTest_571, GetCTMInitial_571)
{
    const auto &ctm = state->getCTM();
    // With 72 DPI and no rotation, the CTM should be an identity-like transform
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_571, SetCTM_571)
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

TEST_F(GfxStateTest_571, ConcatCTM_571)
{
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

TEST_F(GfxStateTest_571, GetCTMAsMatrix_571)
{
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // The Matrix should reflect the set CTM values
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
    EXPECT_DOUBLE_EQ(m.m[1], 2.0);
    EXPECT_DOUBLE_EQ(m.m[2], 3.0);
    EXPECT_DOUBLE_EQ(m.m[3], 4.0);
    EXPECT_DOUBLE_EQ(m.m[4], 5.0);
    EXPECT_DOUBLE_EQ(m.m[5], 6.0);
}

// ==================== Transform operations ====================

TEST_F(GfxStateTest_571, TransformWithIdentityCTM_571)
{
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_571, TransformWithScaleCTM_571)
{
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

TEST_F(GfxStateTest_571, TransformWithTranslation_571)
{
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 100.0);
    EXPECT_DOUBLE_EQ(y2, 200.0);
}

TEST_F(GfxStateTest_571, TransformDelta_571)
{
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double dx2, dy2;
    state->transformDelta(5.0, 10.0, &dx2, &dy2);
    // Delta should not include translation
    EXPECT_DOUBLE_EQ(dx2, 10.0);
    EXPECT_DOUBLE_EQ(dy2, 30.0);
}

TEST_F(GfxStateTest_571, TransformWidth_571)
{
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_GT(w, 0.0);
}

// ==================== Line properties ====================

TEST_F(GfxStateTest_571, SetAndGetLineWidth_571)
{
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_571, SetAndGetLineWidthZero_571)
{
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_571, SetAndGetMiterLimit_571)
{
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

TEST_F(GfxStateTest_571, SetAndGetLineJoin_571)
{
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_571, SetAndGetLineCap_571)
{
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

TEST_F(GfxStateTest_571, SetAndGetLineDash_571)
{
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

TEST_F(GfxStateTest_571, SetAndGetFlatness_571)
{
    state->setFlatness(2);
    EXPECT_EQ(state->getFlatness(), 2);
}

TEST_F(GfxStateTest_571, SetAndGetStrokeAdjust_571)
{
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// ==================== Opacity and blend ====================

TEST_F(GfxStateTest_571, SetAndGetFillOpacity_571)
{
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_571, SetAndGetStrokeOpacity_571)
{
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_571, SetAndGetFillOverprint_571)
{
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_571, SetAndGetStrokeOverprint_571)
{
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_571, SetAndGetOverprintMode_571)
{
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

TEST_F(GfxStateTest_571, SetAndGetBlendMode_571)
{
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// ==================== Text properties ====================

TEST_F(GfxStateTest_571, SetAndGetCharSpace_571)
{
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_571, SetAndGetWordSpace_571)
{
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_571, SetAndGetHorizScaling_571)
{
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_571, SetAndGetLeading_571)
{
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_571, SetAndGetRise_571)
{
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_571, SetAndGetRender_571)
{
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_571, SetAndGetTextMat_571)
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

TEST_F(GfxStateTest_571, SetAndGetAlphaIsShape_571)
{
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_571, SetAndGetTextKnockout_571)
{
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// ==================== Rendering Intent ====================

TEST_F(GfxStateTest_571, SetAndGetRenderingIntent_571)
{
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_571, SetRenderingIntentRelativeColorimetric_571)
{
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_571, SetRenderingIntentSaturation_571)
{
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

TEST_F(GfxStateTest_571, SetRenderingIntentAbsoluteColorimetric_571)
{
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// ==================== Path operations ====================

TEST_F(GfxStateTest_571, InitialPathIsEmpty_571)
{
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_571, MoveToSetsCurPt_571)
{
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

TEST_F(GfxStateTest_571, LineToCreatesPath_571)
{
    state->moveTo(0.0, 0.0);
    state->lineTo(50.0, 50.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 50.0);
}

TEST_F(GfxStateTest_571, CurveToCreatesPath_571)
{
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
}

TEST_F(GfxStateTest_571, ClosePathSetsCurrentToStart_571)
{
    state->moveTo(10.0, 20.0);
    state->lineTo(50.0, 60.0);
    state->closePath();
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

TEST_F(GfxStateTest_571, ClearPathResetsState_571)
{
    state->moveTo(10.0, 20.0);
    state->lineTo(50.0, 60.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_571, GetPathNotNull_571)
{
    state->moveTo(0.0, 0.0);
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// ==================== Text cursor ====================

TEST_F(GfxStateTest_571, TextMoveTo_571)
{
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// ==================== Clip operations ====================

TEST_F(GfxStateTest_571, GetClipBBox_571)
{
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip box should be defined after construction
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_571, ClipToRect_571)
{
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 10.0);
    EXPECT_GE(yMin, 20.0);
    EXPECT_LE(xMax, 100.0);
    EXPECT_LE(yMax, 200.0);
}

TEST_F(GfxStateTest_571, GetUserClipBBox_571)
{
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// ==================== Save / Restore ====================

TEST_F(GfxStateTest_571, SaveAndRestore_571)
{
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    EXPECT_NE(saved, nullptr);
    EXPECT_TRUE(saved->hasSaves());

    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 10.0);

    GfxState *restored = saved->restore();
    EXPECT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_571, HasSavesInitiallyFalse_571)
{
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_571, HasSavesAfterSave_571)
{
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    saved->restore();
}

// ==================== Copy ====================

TEST_F(GfxStateTest_571, CopyPreservesProperties_571)
{
    state->setLineWidth(3.14);
    state->setFillOpacity(0.42);
    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.14);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.42);
}

// ==================== Color ====================

TEST_F(GfxStateTest_571, GetFillColorNotNull_571)
{
    const GfxColor *color = state->getFillColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_571, GetStrokeColorNotNull_571)
{
    const GfxColor *color = state->getStrokeColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_571, SetAndGetFillColor_571)
{
    GfxColor color;
    color.c[0] = dblToCol(0.5);
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], color.c[0]);
}

TEST_F(GfxStateTest_571, SetAndGetStrokeColor_571)
{
    GfxColor color;
    color.c[0] = dblToCol(0.8);
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], color.c[0]);
}

// ==================== Font ====================

TEST_F(GfxStateTest_571, InitialFontIsNull_571)
{
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

TEST_F(GfxStateTest_571, GetFontSizeInitial_571)
{
    double fs = state->getFontSize();
    EXPECT_DOUBLE_EQ(fs, 0.0);
}

// ==================== parseBlendMode ====================

TEST_F(GfxStateTest_571, ParseBlendModeNormal_571)
{
    Object obj(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, GfxBlendMode::Normal);
}

TEST_F(GfxStateTest_571, ParseBlendModeMultiply_571)
{
    Object obj(new GooString("Multiply"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, GfxBlendMode::Multiply);
}

TEST_F(GfxStateTest_571, ParseBlendModeScreen_571)
{
    Object obj(new GooString("Screen"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, GfxBlendMode::Screen);
}

// ==================== ShiftCTMAndClip ====================

TEST_F(GfxStateTest_571, ShiftCTMAndClip_571)
{
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// ==================== Boundary conditions ====================

TEST_F(GfxStateTest_571, SetLineWidthNegative_571)
{
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

TEST_F(GfxStateTest_571, SetOpacityBoundaryZero_571)
{
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_571, SetOpacityBoundaryOne_571)
{
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_571, SetStrokeOpacityBoundaryZero_571)
{
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

TEST_F(GfxStateTest_571, SetStrokeOpacityBoundaryOne_571)
{
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_571, EmptyLineDash_571)
{
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_TRUE(d.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

TEST_F(GfxStateTest_571, TransformZeroInput_571)
{
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 0.0);
    EXPECT_DOUBLE_EQ(y2, 0.0);
}

TEST_F(GfxStateTest_571, TransformDeltaZeroInput_571)
{
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double dx2, dy2;
    state->transformDelta(0.0, 0.0, &dx2, &dy2);
    EXPECT_DOUBLE_EQ(dx2, 0.0);
    EXPECT_DOUBLE_EQ(dy2, 0.0);
}

// ==================== Multiple save/restore ====================

TEST_F(GfxStateTest_571, MultipleSaveRestore_571)
{
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

// ==================== isParentState ====================

TEST_F(GfxStateTest_571, IsParentState_571)
{
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->isParentState(state.get()));
    saved->restore();
}

// ==================== GetTransformedLineWidth ====================

TEST_F(GfxStateTest_571, GetTransformedLineWidth_571)
{
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// ==================== TextTransform ====================

TEST_F(GfxStateTest_571, TextTransform_571)
{
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(1.0, 1.0, &x2, &y2);
    // Result depends on combined text and CTM transforms
    // Just check it doesn't crash and produces finite values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

TEST_F(GfxStateTest_571, TextTransformDelta_571)
{
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double dx2, dy2;
    state->textTransformDelta(5.0, 10.0, &dx2, &dy2);
    EXPECT_TRUE(std::isfinite(dx2));
    EXPECT_TRUE(std::isfinite(dy2));
}

// ==================== GetReusablePath ====================

TEST_F(GfxStateTest_571, GetReusablePath_571)
{
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// ==================== Different DPI values ====================

TEST_F(GfxStateTest_571, DifferentDPI_571)
{
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState highDpiState(300.0, 600.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 600.0);
}

// ==================== Non-standard page box ====================

TEST_F(GfxStateTest_571, NonStandardPageBox_571)
{
    PDFRectangle pageBox = makePageBox(100, 200, 500, 700);
    GfxState customState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(customState.getPageWidth(), 400.0);
    EXPECT_DOUBLE_EQ(customState.getPageHeight(), 500.0);
}
