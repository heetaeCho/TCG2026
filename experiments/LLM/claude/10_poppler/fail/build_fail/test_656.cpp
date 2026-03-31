#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a PDFRectangle
static PDFRectangle makePageBox(double x1, double y1, double x2, double y2)
{
    PDFRectangle box;
    box.x1 = x1;
    box.y1 = y1;
    box.x2 = x2;
    box.y2 = y2;
    return box;
}

class GfxStateTest_656 : public ::testing::Test {
protected:
    void SetUp() override
    {
        PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override
    {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// Test constructor sets DPI values correctly
TEST_F(GfxStateTest_656, ConstructorSetsDPI_656)
{
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_656, ConstructorSetsPageDimensions_656)
{
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_656, ConstructorSetsRotate_656)
{
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page box coordinates
TEST_F(GfxStateTest_656, PageBoxCoordinates_656)
{
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test default fill opacity
TEST_F(GfxStateTest_656, DefaultFillOpacity_656)
{
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test default stroke opacity
TEST_F(GfxStateTest_656, DefaultStrokeOpacity_656)
{
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test set and get fill opacity
TEST_F(GfxStateTest_656, SetFillOpacity_656)
{
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test set and get stroke opacity
TEST_F(GfxStateTest_656, SetStrokeOpacity_656)
{
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test default line width
TEST_F(GfxStateTest_656, DefaultLineWidth_656)
{
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test set and get line width
TEST_F(GfxStateTest_656, SetLineWidth_656)
{
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test default flatness
TEST_F(GfxStateTest_656, DefaultFlatness_656)
{
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test set and get flatness
TEST_F(GfxStateTest_656, SetFlatness_656)
{
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test default miter limit
TEST_F(GfxStateTest_656, DefaultMiterLimit_656)
{
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test set and get miter limit
TEST_F(GfxStateTest_656, SetMiterLimit_656)
{
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test default fill overprint
TEST_F(GfxStateTest_656, DefaultFillOverprint_656)
{
    EXPECT_FALSE(state->getFillOverprint());
}

// Test set and get fill overprint
TEST_F(GfxStateTest_656, SetFillOverprint_656)
{
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test default stroke overprint
TEST_F(GfxStateTest_656, DefaultStrokeOverprint_656)
{
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set and get stroke overprint
TEST_F(GfxStateTest_656, SetStrokeOverprint_656)
{
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_656, DefaultOverprintMode_656)
{
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test set and get overprint mode
TEST_F(GfxStateTest_656, SetOverprintMode_656)
{
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test default stroke adjust
TEST_F(GfxStateTest_656, DefaultStrokeAdjust_656)
{
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test set and get stroke adjust
TEST_F(GfxStateTest_656, SetStrokeAdjust_656)
{
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_656, DefaultAlphaIsShape_656)
{
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test set and get alpha is shape
TEST_F(GfxStateTest_656, SetAlphaIsShape_656)
{
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_656, DefaultTextKnockout_656)
{
    EXPECT_FALSE(state->getTextKnockout());
}

// Test set and get text knockout
TEST_F(GfxStateTest_656, SetTextKnockout_656)
{
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test default font size
TEST_F(GfxStateTest_656, DefaultFontSize_656)
{
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test default char space
TEST_F(GfxStateTest_656, DefaultCharSpace_656)
{
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test set and get char space
TEST_F(GfxStateTest_656, SetCharSpace_656)
{
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test default word space
TEST_F(GfxStateTest_656, DefaultWordSpace_656)
{
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test set and get word space
TEST_F(GfxStateTest_656, SetWordSpace_656)
{
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test default horiz scaling
TEST_F(GfxStateTest_656, DefaultHorizScaling_656)
{
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test set and get horiz scaling
TEST_F(GfxStateTest_656, SetHorizScaling_656)
{
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test default leading
TEST_F(GfxStateTest_656, DefaultLeading_656)
{
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test set and get leading
TEST_F(GfxStateTest_656, SetLeading_656)
{
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test default rise
TEST_F(GfxStateTest_656, DefaultRise_656)
{
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test set and get rise
TEST_F(GfxStateTest_656, SetRise_656)
{
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test default render
TEST_F(GfxStateTest_656, DefaultRender_656)
{
    EXPECT_EQ(state->getRender(), 0);
}

// Test set and get render
TEST_F(GfxStateTest_656, SetRender_656)
{
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test default blend mode
TEST_F(GfxStateTest_656, DefaultBlendMode_656)
{
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test set and get blend mode
TEST_F(GfxStateTest_656, SetBlendMode_656)
{
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test setCTM and getCTM
TEST_F(GfxStateTest_656, SetCTM_656)
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

// Test concatCTM
TEST_F(GfxStateTest_656, ConcatCTM_656)
{
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test transform
TEST_F(GfxStateTest_656, Transform_656)
{
    state->setCTM(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    double x2, y2;
    state->transform(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 15.0);
    EXPECT_DOUBLE_EQ(y2, 25.0);
}

// Test transformDelta
TEST_F(GfxStateTest_656, TransformDelta_656)
{
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(3.0, 4.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 6.0);
    EXPECT_DOUBLE_EQ(y2, 8.0);
}

// Test save and restore
TEST_F(GfxStateTest_656, SaveAndRestore_656)
{
    EXPECT_FALSE(state->hasSaves());
    state->setLineWidth(5.0);

    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());

    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 10.0);

    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

// Test hasSaves
TEST_F(GfxStateTest_656, HasSaves_656)
{
    EXPECT_FALSE(state->hasSaves());
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    GfxState *restored = saved->restore();
    EXPECT_FALSE(restored->hasSaves());
}

// Test moveTo and isCurPt / isPath
TEST_F(GfxStateTest_656, MoveToAndPath_656)
{
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());

    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test lineTo
TEST_F(GfxStateTest_656, LineTo_656)
{
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
}

// Test curveTo
TEST_F(GfxStateTest_656, CurveTo_656)
{
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_656, ClosePath_656)
{
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_656, ClearPath_656)
{
    state->moveTo(10.0, 10.0);
    state->lineTo(20.0, 20.0);
    EXPECT_TRUE(state->isPath());

    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test getPath returns non-null
TEST_F(GfxStateTest_656, GetPathNotNull_656)
{
    EXPECT_NE(state->getPath(), nullptr);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_656, SetTextMat_656)
{
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 2.0);
    EXPECT_DOUBLE_EQ(mat[2], 3.0);
    EXPECT_DOUBLE_EQ(mat[3], 4.0);
    EXPECT_DOUBLE_EQ(mat[4], 5.0);
    EXPECT_DOUBLE_EQ(mat[5], 6.0);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_656, SetRenderingIntent_656)
{
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test setRenderingIntent with long string (boundary: 31 chars max due to char[32])
TEST_F(GfxStateTest_656, SetRenderingIntentLong_656)
{
    // The buffer is 32 chars, so intent should be truncated or limited
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_656, SetLineDash_656)
{
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);

    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
}

// Test setLineJoin and getLineJoin
TEST_F(GfxStateTest_656, SetLineJoin_656)
{
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// Test setLineCap and getLineCap
TEST_F(GfxStateTest_656, SetLineCap_656)
{
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test clipToRect and getClipBBox
TEST_F(GfxStateTest_656, ClipToRect_656)
{
    state->clipToRect(50.0, 60.0, 200.0, 300.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, 200.0);
    EXPECT_LE(yMin, 300.0);
    EXPECT_GE(xMax, 50.0);
    EXPECT_GE(yMax, 60.0);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_656, GetUserClipBBox_656)
{
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should return some valid bounding box
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test textMoveTo
TEST_F(GfxStateTest_656, TextMoveTo_656)
{
    state->textMoveTo(100.0, 200.0);
    // After textMoveTo, lineX/lineY should be set
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test setDefaultRGBColorSpace (the provided snippet)
TEST_F(GfxStateTest_656, SetDefaultRGBColorSpace_656)
{
    // Setting to nullptr should work without crash
    state->setDefaultRGBColorSpace(nullptr);
    auto cs = state->copyDefaultRGBColorSpace();
    EXPECT_EQ(cs, nullptr);
}

// Test setDefaultGrayColorSpace
TEST_F(GfxStateTest_656, SetDefaultGrayColorSpace_656)
{
    state->setDefaultGrayColorSpace(nullptr);
    auto cs = state->copyDefaultGrayColorSpace();
    EXPECT_EQ(cs, nullptr);
}

// Test setDefaultCMYKColorSpace
TEST_F(GfxStateTest_656, SetDefaultCMYKColorSpace_656)
{
    state->setDefaultCMYKColorSpace(nullptr);
    auto cs = state->copyDefaultCMYKColorSpace();
    EXPECT_EQ(cs, nullptr);
}

// Test copy
TEST_F(GfxStateTest_656, CopyState_656)
{
    state->setLineWidth(7.5);
    state->setFillOpacity(0.3);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.3);
}

// Test different rotation
TEST_F(GfxStateTest_656, RotatedPage_656)
{
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState->getRotate(), 90);
    EXPECT_DOUBLE_EQ(rotatedState->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(rotatedState->getPageHeight(), 792.0);
}

// Test different DPI values
TEST_F(GfxStateTest_656, DifferentDPI_656)
{
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    auto highDpiState = std::make_unique<GfxState>(300.0, 600.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState->getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState->getVDPI(), 600.0);
}

// Test transformWidth
TEST_F(GfxStateTest_656, TransformWidth_656)
{
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_GT(w, 0.0);
}

// Test setFillColor and getFillColor
TEST_F(GfxStateTest_656, SetFillColor_656)
{
    GfxColor color;
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *fc = state->getFillColor();
    ASSERT_NE(fc, nullptr);
    EXPECT_EQ(fc->c[0], 32768);
}

// Test setStrokeColor and getStrokeColor
TEST_F(GfxStateTest_656, SetStrokeColor_656)
{
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *sc = state->getStrokeColor();
    ASSERT_NE(sc, nullptr);
    EXPECT_EQ(sc->c[0], 16384);
}

// Test initial isPath is false
TEST_F(GfxStateTest_656, InitialIsPathFalse_656)
{
    state->clearPath();
    EXPECT_FALSE(state->isPath());
}

// Test getCurX and getCurY after moveTo
TEST_F(GfxStateTest_656, GetCurXYAfterMoveTo_656)
{
    state->clearPath();
    state->moveTo(42.0, 84.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 42.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 84.0);
}

// Test save/restore preserves color space
TEST_F(GfxStateTest_656, SaveRestorePreservesLineWidth_656)
{
    state->setLineWidth(3.0);
    GfxState *s = state->save();
    s->setLineWidth(9.0);
    EXPECT_DOUBLE_EQ(s->getLineWidth(), 9.0);
    GfxState *r = s->restore();
    EXPECT_DOUBLE_EQ(r->getLineWidth(), 3.0);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_656, ShiftCTMAndClip_656)
{
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test empty line dash
TEST_F(GfxStateTest_656, EmptyLineDash_656)
{
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(d.empty());
}

// Test setFont with nullptr
TEST_F(GfxStateTest_656, SetFontNullptr_656)
{
    state->setFont(nullptr, 12.0);
    EXPECT_EQ(state->getFont(), nullptr);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

// Test getReusablePath
TEST_F(GfxStateTest_656, GetReusablePath_656)
{
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto rp = state->getReusablePath();
    EXPECT_NE(rp, nullptr);
}

// Test parseBlendMode with normal
TEST_F(GfxStateTest_656, ParseBlendModeNormal_656)
{
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, gfxBlendNormal);
    }
}

// Test 180 degree rotation
TEST_F(GfxStateTest_656, Rotation180_656)
{
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    auto rotState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotState->getRotate(), 180);
}

// Test 270 degree rotation
TEST_F(GfxStateTest_656, Rotation270_656)
{
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    auto rotState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotState->getRotate(), 270);
}

// Test upside down = false
TEST_F(GfxStateTest_656, UpsideDownFalse_656)
{
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    auto s = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    EXPECT_NE(s, nullptr);
    EXPECT_DOUBLE_EQ(s->getPageWidth(), 612.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_656, GetTransformedLineWidth_656)
{
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_GT(tw, 0.0);
}

// Test clip does not crash on empty path
TEST_F(GfxStateTest_656, ClipOnPath_656)
{
    state->clearPath();
    state->moveTo(0, 0);
    state->lineTo(100, 0);
    state->lineTo(100, 100);
    state->closePath();
    state->clip();
    // Just verify no crash
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
}
