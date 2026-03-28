#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState with common parameters
class GfxStateTest_592 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// Test basic construction and page dimensions
TEST_F(GfxStateTest_592, ConstructorSetsPageDimensions_592) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test DPI getters
TEST_F(GfxStateTest_592, GetDPI_592) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test rotation
TEST_F(GfxStateTest_592, GetRotate_592) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page coordinates
TEST_F(GfxStateTest_592, GetPageCoordinates_592) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test fill overprint default
TEST_F(GfxStateTest_592, FillOverprintDefault_592) {
    EXPECT_FALSE(state->getFillOverprint());
}

// Test set/get fill overprint true
TEST_F(GfxStateTest_592, SetFillOverprintTrue_592) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test set/get fill overprint false after true
TEST_F(GfxStateTest_592, SetFillOverprintFalseAfterTrue_592) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test stroke overprint default
TEST_F(GfxStateTest_592, StrokeOverprintDefault_592) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set/get stroke overprint
TEST_F(GfxStateTest_592, SetStrokeOverprint_592) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test overprint mode default
TEST_F(GfxStateTest_592, OverprintModeDefault_592) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test set/get overprint mode
TEST_F(GfxStateTest_592, SetOverprintMode_592) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test fill opacity default
TEST_F(GfxStateTest_592, FillOpacityDefault_592) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test set/get fill opacity
TEST_F(GfxStateTest_592, SetFillOpacity_592) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test stroke opacity default
TEST_F(GfxStateTest_592, StrokeOpacityDefault_592) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test set/get stroke opacity
TEST_F(GfxStateTest_592, SetStrokeOpacity_592) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// Test line width default
TEST_F(GfxStateTest_592, LineWidthDefault_592) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test set/get line width
TEST_F(GfxStateTest_592, SetLineWidth_592) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test set line width to zero
TEST_F(GfxStateTest_592, SetLineWidthZero_592) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test flatness default
TEST_F(GfxStateTest_592, FlatnessDefault_592) {
    EXPECT_EQ(state->getFlatness(), 0);
}

// Test set/get flatness
TEST_F(GfxStateTest_592, SetFlatness_592) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test miter limit default
TEST_F(GfxStateTest_592, MiterLimitDefault_592) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test set/get miter limit
TEST_F(GfxStateTest_592, SetMiterLimit_592) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test stroke adjust default
TEST_F(GfxStateTest_592, StrokeAdjustDefault_592) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test set/get stroke adjust
TEST_F(GfxStateTest_592, SetStrokeAdjust_592) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test alpha is shape default
TEST_F(GfxStateTest_592, AlphaIsShapeDefault_592) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test set/get alpha is shape
TEST_F(GfxStateTest_592, SetAlphaIsShape_592) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test text knockout default
TEST_F(GfxStateTest_592, TextKnockoutDefault_592) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test set/get text knockout
TEST_F(GfxStateTest_592, SetTextKnockout_592) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test font size default
TEST_F(GfxStateTest_592, FontSizeDefault_592) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test char space default
TEST_F(GfxStateTest_592, CharSpaceDefault_592) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test set/get char space
TEST_F(GfxStateTest_592, SetCharSpace_592) {
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
}

// Test word space default
TEST_F(GfxStateTest_592, WordSpaceDefault_592) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test set/get word space
TEST_F(GfxStateTest_592, SetWordSpace_592) {
    state->setWordSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 1.5);
}

// Test horiz scaling default
TEST_F(GfxStateTest_592, HorizScalingDefault_592) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test set/get horiz scaling
TEST_F(GfxStateTest_592, SetHorizScaling_592) {
    state->setHorizScaling(0.8);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.8);
}

// Test leading default
TEST_F(GfxStateTest_592, LeadingDefault_592) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test set/get leading
TEST_F(GfxStateTest_592, SetLeading_592) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test rise default
TEST_F(GfxStateTest_592, RiseDefault_592) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test set/get rise
TEST_F(GfxStateTest_592, SetRise_592) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test render default
TEST_F(GfxStateTest_592, RenderDefault_592) {
    EXPECT_EQ(state->getRender(), 0);
}

// Test set/get render
TEST_F(GfxStateTest_592, SetRender_592) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test blend mode default
TEST_F(GfxStateTest_592, BlendModeDefault_592) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test set/get blend mode
TEST_F(GfxStateTest_592, SetBlendMode_592) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test save and restore
TEST_F(GfxStateTest_592, SaveAndRestore_592) {
    state->setFillOpacity(0.5);
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    
    saved->setFillOpacity(0.3);
    EXPECT_DOUBLE_EQ(saved->getFillOpacity(), 0.3);
    
    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getFillOpacity(), 0.5);
}

// Test hasSaves default
TEST_F(GfxStateTest_592, HasSavesDefault_592) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after save
TEST_F(GfxStateTest_592, HasSavesAfterSave_592) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    GfxState *restored = saved->restore();
    (void)restored;
}

// Test CTM getter
TEST_F(GfxStateTest_592, GetCTM_592) {
    const auto &ctm = state->getCTM();
    // CTM should be set to some identity-like transform based on DPI and page setup
    EXPECT_EQ(ctm.size(), 6u);
}

// Test setCTM
TEST_F(GfxStateTest_592, SetCTM_592) {
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
TEST_F(GfxStateTest_592, Transform_592) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test transformDelta
TEST_F(GfxStateTest_592, TransformDelta_592) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test path operations - moveTo creates current point
TEST_F(GfxStateTest_592, MoveToCreatesCurPt_592) {
    state->moveTo(100.0, 200.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(state->getCurX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 200.0);
}

// Test isPath after lineTo
TEST_F(GfxStateTest_592, LineToCreatesPath_592) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_592, ClearPath_592) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_592, ClosePath_592) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    // After closing, curX/curY should be back at the subpath start
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test curveTo
TEST_F(GfxStateTest_592, CurveTo_592) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
}

// Test text position
TEST_F(GfxStateTest_592, TextMoveTo_592) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test setTextMat
TEST_F(GfxStateTest_592, SetTextMat_592) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto &textMat = state->getTextMat();
    EXPECT_DOUBLE_EQ(textMat[0], 1.0);
    EXPECT_DOUBLE_EQ(textMat[1], 0.0);
    EXPECT_DOUBLE_EQ(textMat[2], 0.0);
    EXPECT_DOUBLE_EQ(textMat[3], 1.0);
    EXPECT_DOUBLE_EQ(textMat[4], 0.0);
    EXPECT_DOUBLE_EQ(textMat[5], 0.0);
}

// Test setRenderingIntent
TEST_F(GfxStateTest_592, SetRenderingIntent_592) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test rendering intent with another value
TEST_F(GfxStateTest_592, SetRenderingIntentRelativeColorimetric_592) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test line dash
TEST_F(GfxStateTest_592, SetLineDash_592) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
}

// Test line join
TEST_F(GfxStateTest_592, SetLineJoin_592) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

// Test line cap
TEST_F(GfxStateTest_592, SetLineCap_592) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test getPath is not null
TEST_F(GfxStateTest_592, GetPathNotNull_592) {
    EXPECT_NE(state->getPath(), nullptr);
}

// Test clip bounding box
TEST_F(GfxStateTest_592, ClipBBox_592) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip should cover at least the page area
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_592, ClipToRect_592) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 100.0);
    EXPECT_GE(yMin, 100.0);
    EXPECT_LE(xMax, 200.0);
    EXPECT_LE(yMax, 200.0);
}

// Test copy
TEST_F(GfxStateTest_592, CopyState_592) {
    state->setFillOpacity(0.7);
    state->setLineWidth(3.0);
    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
}

// Test concatCTM
TEST_F(GfxStateTest_592, ConcatCTM_592) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test construction with rotation
TEST_F(GfxStateTest_592, ConstructWithRotation_592) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test construction with different DPI values
TEST_F(GfxStateTest_592, ConstructWithDifferentDPI_592) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState highDPI(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDPI.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(highDPI.getVDPI(), 300.0);
}

// Test fill color space default
TEST_F(GfxStateTest_592, FillColorSpaceDefault_592) {
    // Default fill color space should exist (DeviceGray by default)
    GfxColorSpace *cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test stroke color space default
TEST_F(GfxStateTest_592, StrokeColorSpaceDefault_592) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test fill pattern default is null
TEST_F(GfxStateTest_592, FillPatternDefault_592) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

// Test stroke pattern default is null
TEST_F(GfxStateTest_592, StrokePatternDefault_592) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test fill color
TEST_F(GfxStateTest_592, GetFillColor_592) {
    const GfxColor *color = state->getFillColor();
    EXPECT_NE(color, nullptr);
}

// Test stroke color
TEST_F(GfxStateTest_592, GetStrokeColor_592) {
    const GfxColor *color = state->getStrokeColor();
    EXPECT_NE(color, nullptr);
}

// Test font default is null
TEST_F(GfxStateTest_592, FontDefault_592) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_592, GetUserClipBBox_592) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test transformWidth with identity CTM
TEST_F(GfxStateTest_592, TransformWidthIdentity_592) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_DOUBLE_EQ(w, 1.0);
}

// Test transformWidth with scaled CTM
TEST_F(GfxStateTest_592, TransformWidthScaled_592) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_DOUBLE_EQ(w, 2.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_592, GetTransformedLineWidth_592) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(2.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tw, 2.0);
}

// Test isCurPt default
TEST_F(GfxStateTest_592, IsCurPtDefault_592) {
    EXPECT_FALSE(state->isCurPt());
}

// Test isPath default
TEST_F(GfxStateTest_592, IsPathDefault_592) {
    EXPECT_FALSE(state->isPath());
}

// Test getCurTextX/Y defaults
TEST_F(GfxStateTest_592, CurTextPositionDefault_592) {
    EXPECT_DOUBLE_EQ(state->getCurTextX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurTextY(), 0.0);
}

// Test save/restore preserves properties correctly
TEST_F(GfxStateTest_592, SaveRestorePreservesLineWidth_592) {
    state->setLineWidth(5.0);
    GfxState *s = state->save();
    s->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(s->getLineWidth(), 10.0);
    GfxState *restored = s->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

// Test getReusablePath
TEST_F(GfxStateTest_592, GetReusablePath_592) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    auto pathIter = state->getReusablePath();
    EXPECT_NE(pathIter, nullptr);
}

// Test rendering intent with long string that would be truncated to 31 chars
TEST_F(GfxStateTest_592, SetRenderingIntentLongString_592) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test set fill color
TEST_F(GfxStateTest_592, SetFillColor_592) {
    GfxColor color;
    color.c[0] = 32768; // 0.5 in fixed point
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], 32768);
}

// Test set stroke color
TEST_F(GfxStateTest_592, SetStrokeColor_592) {
    GfxColor color;
    color.c[0] = 65535; // 1.0 in fixed point
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], 65535);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_592, ShiftCTMAndClip_592) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test getCTM with Matrix version
TEST_F(GfxStateTest_592, GetCTMMatrix_592) {
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

// Test multiple save/restore chain
TEST_F(GfxStateTest_592, MultipleSaveRestore_592) {
    state->setFillOpacity(1.0);
    GfxState *s1 = state->save();
    s1->setFillOpacity(0.8);
    GfxState *s2 = s1->save();
    s2->setFillOpacity(0.5);
    
    EXPECT_DOUBLE_EQ(s2->getFillOpacity(), 0.5);
    
    GfxState *r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getFillOpacity(), 0.8);
    
    GfxState *r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getFillOpacity(), 1.0);
}

// Test isParentState
TEST_F(GfxStateTest_592, IsParentState_592) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->isParentState(state.get()));
    GfxState *restored = saved->restore();
    (void)restored;
}

// Test empty line dash
TEST_F(GfxStateTest_592, EmptyLineDash_592) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 0u);
    EXPECT_DOUBLE_EQ(start, 0.0);
}
