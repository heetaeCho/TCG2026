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

class GfxStateTest_617 : public ::testing::Test {
protected:
    void SetUp() override
    {
        PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// --- Constructor and basic getters ---

TEST_F(GfxStateTest_617, ConstructorSetsHDPI_617)
{
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_617, ConstructorSetsVDPI_617)
{
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_617, ConstructorSetsRotate_617)
{
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_617, ConstructorSetsPageDimensions_617)
{
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_617, ConstructorSetsBBox_617)
{
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// --- Rotation ---

TEST_F(GfxStateTest_617, ConstructorWithRotation90_617)
{
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_617, ConstructorWithRotation180_617)
{
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

TEST_F(GfxStateTest_617, ConstructorWithRotation270_617)
{
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

// --- getCurX / getCurY ---

TEST_F(GfxStateTest_617, InitialCurXAndCurY_617)
{
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// --- Line properties ---

TEST_F(GfxStateTest_617, SetAndGetLineWidth_617)
{
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_617, SetAndGetLineWidthZero_617)
{
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_617, SetAndGetMiterLimit_617)
{
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_617, SetAndGetFlatness_617)
{
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

TEST_F(GfxStateTest_617, SetAndGetLineJoin_617)
{
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_617, SetAndGetLineCap_617)
{
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// --- Opacity ---

TEST_F(GfxStateTest_617, SetAndGetFillOpacity_617)
{
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_617, SetAndGetStrokeOpacity_617)
{
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_617, FillOpacityBoundaryZero_617)
{
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_617, FillOpacityBoundaryOne_617)
{
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// --- Overprint ---

TEST_F(GfxStateTest_617, SetAndGetFillOverprint_617)
{
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_617, SetAndGetStrokeOverprint_617)
{
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_617, SetAndGetOverprintMode_617)
{
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// --- StrokeAdjust ---

TEST_F(GfxStateTest_617, SetAndGetStrokeAdjust_617)
{
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// --- AlphaIsShape ---

TEST_F(GfxStateTest_617, SetAndGetAlphaIsShape_617)
{
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// --- TextKnockout ---

TEST_F(GfxStateTest_617, SetAndGetTextKnockout_617)
{
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// --- Text properties ---

TEST_F(GfxStateTest_617, SetAndGetCharSpace_617)
{
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_617, SetAndGetWordSpace_617)
{
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_617, SetAndGetHorizScaling_617)
{
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_617, SetAndGetLeading_617)
{
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_617, SetAndGetRise_617)
{
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_617, SetAndGetRender_617)
{
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// --- TextMat ---

TEST_F(GfxStateTest_617, SetAndGetTextMat_617)
{
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 1.0);
    EXPECT_DOUBLE_EQ(tm[4], 10.0);
    EXPECT_DOUBLE_EQ(tm[5], 20.0);
}

// --- RenderingIntent ---

TEST_F(GfxStateTest_617, SetAndGetRenderingIntent_617)
{
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_617, SetRenderingIntentAbsoluteColorimetric_617)
{
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// --- BlendMode ---

TEST_F(GfxStateTest_617, SetAndGetBlendMode_617)
{
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// --- CTM ---

TEST_F(GfxStateTest_617, SetCTM_617)
{
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 100.0);
    EXPECT_DOUBLE_EQ(ctm[5], 200.0);
}

TEST_F(GfxStateTest_617, ConcatCTM_617)
{
    // Set identity first
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    // Concat with a scaling matrix
    state->concatCTM(2.0, 0.0, 0.0, 3.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 3.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// --- Transform ---

TEST_F(GfxStateTest_617, TransformPoint_617)
{
    state->setCTM(1.0, 0.0, 0.0, 1.0, 50.0, 100.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 60.0);
    EXPECT_DOUBLE_EQ(y2, 120.0);
}

TEST_F(GfxStateTest_617, TransformDelta_617)
{
    state->setCTM(2.0, 0.0, 0.0, 2.0, 50.0, 100.0);
    double dx2, dy2;
    state->transformDelta(5.0, 10.0, &dx2, &dy2);
    EXPECT_DOUBLE_EQ(dx2, 10.0);
    EXPECT_DOUBLE_EQ(dy2, 20.0);
}

// --- Path operations ---

TEST_F(GfxStateTest_617, InitiallyNoPath_617)
{
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_617, MoveToSetsCurPoint_617)
{
    state->moveTo(100.0, 200.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(state->getCurX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 200.0);
}

TEST_F(GfxStateTest_617, LineToCreatesPath_617)
{
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 100.0);
}

TEST_F(GfxStateTest_617, CurveToUpdatesCurPoint_617)
{
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
}

TEST_F(GfxStateTest_617, ClearPathResetsState_617)
{
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_617, ClosePathWorks_617)
{
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    // After closePath, curPt should be at the start of the subpath
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// --- GetPath ---

TEST_F(GfxStateTest_617, GetPathNotNull_617)
{
    EXPECT_NE(state->getPath(), nullptr);
}

// --- Save / Restore ---

TEST_F(GfxStateTest_617, SaveAndRestore_617)
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

TEST_F(GfxStateTest_617, HasSavesInitiallyFalse_617)
{
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_617, HasSavesTrueAfterSave_617)
{
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    // Clean up by restoring
    saved->restore();
}

// --- Copy ---

TEST_F(GfxStateTest_617, CopyCreatesIndependentState_617)
{
    state->setLineWidth(3.0);
    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_NE(copied.get(), nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);

    // Modifying copy doesn't affect original
    copied->setLineWidth(7.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.0);
}

// --- LineDash ---

TEST_F(GfxStateTest_617, SetAndGetLineDash_617)
{
    std::vector<double> dash = {3.0, 2.0, 1.0};
    state->setLineDash(std::move(dash), 5.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 5.0);
    ASSERT_EQ(d.size(), 3u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 2.0);
    EXPECT_DOUBLE_EQ(d[2], 1.0);
}

TEST_F(GfxStateTest_617, SetEmptyLineDash_617)
{
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(d.empty());
}

// --- TextMoveTo ---

TEST_F(GfxStateTest_617, TextMoveToUpdatesCurText_617)
{
    state->textMoveTo(100.0, 200.0);
    // After textMoveTo, lineX/lineY should be updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// --- ClipBBox ---

TEST_F(GfxStateTest_617, GetClipBBox_617)
{
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip bbox should be at least covering the page
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_617, ClipToRect_617)
{
    state->clipToRect(100.0, 200.0, 300.0, 400.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip box should be constrained
    EXPECT_GE(xMin, 100.0);
    EXPECT_GE(yMin, 200.0);
    EXPECT_LE(xMax, 300.0);
    EXPECT_LE(yMax, 400.0);
}

// --- getUserClipBBox ---

TEST_F(GfxStateTest_617, GetUserClipBBox_617)
{
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// --- Font ---

TEST_F(GfxStateTest_617, InitialFontIsNull_617)
{
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

TEST_F(GfxStateTest_617, GetFontSizeDefault_617)
{
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// --- FillColor / StrokeColor ---

TEST_F(GfxStateTest_617, GetFillColorNotNull_617)
{
    const GfxColor *color = state->getFillColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_617, GetStrokeColorNotNull_617)
{
    const GfxColor *color = state->getStrokeColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_617, SetAndGetFillColor_617)
{
    GfxColor color;
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_617, SetAndGetStrokeColor_617)
{
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], 65535);
}

// --- FillColorSpace / StrokeColorSpace ---

TEST_F(GfxStateTest_617, FillColorSpaceNotNullByDefault_617)
{
    // Default color space should be set (typically DeviceGray)
    GfxColorSpace *cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_617, StrokeColorSpaceNotNullByDefault_617)
{
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// --- Patterns ---

TEST_F(GfxStateTest_617, FillPatternInitiallyNull_617)
{
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

TEST_F(GfxStateTest_617, StrokePatternInitiallyNull_617)
{
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// --- transformWidth ---

TEST_F(GfxStateTest_617, TransformWidth_617)
{
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double tw = state->transformWidth(1.0);
    EXPECT_GT(tw, 0.0);
}

TEST_F(GfxStateTest_617, TransformWidthZero_617)
{
    double tw = state->transformWidth(0.0);
    EXPECT_GE(tw, 0.0);
}

// --- shiftCTMAndClip ---

TEST_F(GfxStateTest_617, ShiftCTMAndClip_617)
{
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// --- isParentState ---

TEST_F(GfxStateTest_617, IsParentState_617)
{
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
    child->restore();
}

// --- parseBlendMode ---

TEST_F(GfxStateTest_617, ParseBlendModeNormal_617)
{
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, GfxBlendMode::Normal);
}

TEST_F(GfxStateTest_617, ParseBlendModeMultiply_617)
{
    Object obj;
    obj = Object(new GooString("Multiply"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, GfxBlendMode::Multiply);
}

// --- getTransformedLineWidth ---

TEST_F(GfxStateTest_617, GetTransformedLineWidth_617)
{
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// --- getReusablePath ---

TEST_F(GfxStateTest_617, GetReusablePath_617)
{
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// --- Different DPI values ---

TEST_F(GfxStateTest_617, DifferentDPIValues_617)
{
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState highDpiState(300.0, 600.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 600.0);
}

// --- Non-standard page box ---

TEST_F(GfxStateTest_617, NonStandardPageBox_617)
{
    PDFRectangle pageBox = makePageBox(50, 100, 400, 600);
    GfxState customState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(customState.getPageWidth(), 350.0);
    EXPECT_DOUBLE_EQ(customState.getPageHeight(), 500.0);
}

// --- textShift ---

TEST_F(GfxStateTest_617, TextShift_617)
{
    state->textMoveTo(10.0, 20.0);
    double initTextX = state->getCurTextX();
    double initTextY = state->getCurTextY();
    state->textShift(5.0, 3.0);
    // After shift, text position should have changed
    // The exact values depend on the text matrix, but they should differ
    // from initial in the general case
    // Just verify no crash and values are finite
    double newX = state->getCurX();
    double newY = state->getCurY();
    EXPECT_TRUE(std::isfinite(newX));
    EXPECT_TRUE(std::isfinite(newY));
}

// --- Multiple save/restore ---

TEST_F(GfxStateTest_617, MultipleSaveRestore_617)
{
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

// --- getCTM with Matrix ---

TEST_F(GfxStateTest_617, GetCTMAsMatrix_617)
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

// --- Clip operation ---

TEST_F(GfxStateTest_617, ClipOperation_617)
{
    state->moveTo(100.0, 100.0);
    state->lineTo(200.0, 100.0);
    state->lineTo(200.0, 200.0);
    state->closePath();
    state->clip();
    // After clip, the clip bbox should be constrained
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}
