#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cmath>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a basic GfxState for testing
// Using a simple page box and common parameters
class GfxStateTest_563 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612; // Letter width in points
        pageBox.y2 = 792; // Letter height in points
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// Test basic construction and DPI getters
TEST_F(GfxStateTest_563, Construction_GetDPI_563) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_563, GetPageDimensions_563) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_563, GetRotate_563) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page box coordinates
TEST_F(GfxStateTest_563, GetPageBoxCoordinates_563) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test with rotation
TEST_F(GfxStateTest_563, ConstructionWithRotation_563) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test CTM getter
TEST_F(GfxStateTest_563, GetCTM_563) {
    const auto &ctm = state->getCTM();
    // CTM should be set based on construction parameters
    EXPECT_EQ(ctm.size(), 6u);
}

// Test CTM Matrix getter
TEST_F(GfxStateTest_563, GetCTMMatrix_563) {
    Matrix m;
    state->getCTM(&m);
    // Just verify it doesn't crash; the matrix values depend on internal logic
}

// Test setCTM and getCTM
TEST_F(GfxStateTest_563, SetCTM_563) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test concatCTM
TEST_F(GfxStateTest_563, ConcatCTM_563) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0); // Identity
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 5.0);
    EXPECT_DOUBLE_EQ(ctm[5], 10.0);
}

// Test transform
TEST_F(GfxStateTest_563, Transform_563) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 110.0);
    EXPECT_DOUBLE_EQ(y2, 220.0);
}

// Test transformDelta
TEST_F(GfxStateTest_563, TransformDelta_563) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 40.0);
}

// Test fill opacity
TEST_F(GfxStateTest_563, FillOpacity_563) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test stroke opacity
TEST_F(GfxStateTest_563, StrokeOpacity_563) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test line width
TEST_F(GfxStateTest_563, LineWidth_563) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test line width zero (hairline)
TEST_F(GfxStateTest_563, LineWidthZero_563) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test miter limit
TEST_F(GfxStateTest_563, MiterLimit_563) {
    state->setMiterLimit(15.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 15.0);
}

// Test flatness
TEST_F(GfxStateTest_563, Flatness_563) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test line join
TEST_F(GfxStateTest_563, LineJoin_563) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);

    state->setLineJoin(LineJoinStyle::Bevel);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Bevel);

    state->setLineJoin(LineJoinStyle::Miter);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Miter);
}

// Test line cap
TEST_F(GfxStateTest_563, LineCap_563) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);

    state->setLineCap(LineCapStyle::Projecting);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Projecting);

    state->setLineCap(LineCapStyle::Butt);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Butt);
}

// Test fill overprint
TEST_F(GfxStateTest_563, FillOverprint_563) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());

    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test stroke overprint
TEST_F(GfxStateTest_563, StrokeOverprint_563) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());

    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test overprint mode
TEST_F(GfxStateTest_563, OverprintMode_563) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);

    state->setOverprintMode(0);
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test stroke adjust
TEST_F(GfxStateTest_563, StrokeAdjust_563) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());

    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_563, AlphaIsShape_563) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());

    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_563, TextKnockout_563) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());

    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test char space
TEST_F(GfxStateTest_563, CharSpace_563) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test word space
TEST_F(GfxStateTest_563, WordSpace_563) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test horizontal scaling
TEST_F(GfxStateTest_563, HorizScaling_563) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test leading
TEST_F(GfxStateTest_563, Leading_563) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test rise
TEST_F(GfxStateTest_563, Rise_563) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

// Test render
TEST_F(GfxStateTest_563, Render_563) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test rendering intent
TEST_F(GfxStateTest_563, RenderingIntent_563) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test rendering intent with longer string (boundary: max 31 chars + null)
TEST_F(GfxStateTest_563, RenderingIntentMaxLength_563) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test text matrix
TEST_F(GfxStateTest_563, TextMat_563) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 2.0);
    EXPECT_DOUBLE_EQ(tm[2], 3.0);
    EXPECT_DOUBLE_EQ(tm[3], 4.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 6.0);
}

// Test font size
TEST_F(GfxStateTest_563, FontSize_563) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0); // Default before setting
}

// Test blend mode
TEST_F(GfxStateTest_563, BlendMode_563) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);

    state->setBlendMode(GfxBlendMode::Normal);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

// Test save and restore
TEST_F(GfxStateTest_563, SaveRestore_563) {
    state->setLineWidth(3.0);
    EXPECT_FALSE(state->hasSaves());

    GfxState *savedState = state->save();
    EXPECT_TRUE(savedState->hasSaves());

    savedState->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(savedState->getLineWidth(), 5.0);

    GfxState *restoredState = savedState->restore();
    EXPECT_DOUBLE_EQ(restoredState->getLineWidth(), 3.0);
}

// Test hasSaves
TEST_F(GfxStateTest_563, HasSaves_563) {
    EXPECT_FALSE(state->hasSaves());
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    GfxState *restored = saved->restore();
    EXPECT_FALSE(restored->hasSaves());
}

// Test copy
TEST_F(GfxStateTest_563, Copy_563) {
    state->setLineWidth(7.5);
    state->setFillOpacity(0.3);

    GfxState *copied = state->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.3);
    delete copied;
}

// Test copy with copyPath=true
TEST_F(GfxStateTest_563, CopyWithPath_563) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);

    GfxState *copied = state->copy(true);
    ASSERT_NE(copied, nullptr);

    const GfxPath *path = copied->getPath();
    EXPECT_NE(path, nullptr);
    delete copied;
}

// Test copy without path
TEST_F(GfxStateTest_563, CopyWithoutPath_563) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);

    GfxState *copied = state->copy(false);
    ASSERT_NE(copied, nullptr);
    delete copied;
}

// Test path operations - moveTo and isPath/isCurPt
TEST_F(GfxStateTest_563, MoveToAndPathState_563) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());

    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test lineTo
TEST_F(GfxStateTest_563, LineTo_563) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
}

// Test curveTo
TEST_F(GfxStateTest_563, CurveTo_563) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_563, ClosePath_563) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_563, ClearPath_563) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());

    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test clip bounding box
TEST_F(GfxStateTest_563, ClipBBox_563) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip box should be set to some valid values after construction
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_563, GetUserClipBBox_563) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_563, ClipToRect_563) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the bounds should be constrained
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test textMoveTo
TEST_F(GfxStateTest_563, TextMoveTo_563) {
    state->textMoveTo(50.0, 100.0);
    // Verify line positions are updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 100.0);
}

// Test text transform
TEST_F(GfxStateTest_563, TextTransform_563) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(10.0, 20.0, &x2, &y2);
    // Should transform based on text matrix and CTM
}

// Test textTransformDelta
TEST_F(GfxStateTest_563, TextTransformDelta_563) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(5.0, 10.0, &x2, &y2);
    // Result depends on text matrix and CTM combination
}

// Test fill and stroke color
TEST_F(GfxStateTest_563, FillColor_563) {
    GfxColor color;
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_563, StrokeColor_563) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 16384);
}

// Test line dash
TEST_F(GfxStateTest_563, LineDash_563) {
    std::vector<double> dash = {3.0, 2.0, 1.0};
    state->setLineDash(std::move(dash), 0.5);

    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.5);
    ASSERT_EQ(retrievedDash.size(), 3u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 2.0);
    EXPECT_DOUBLE_EQ(retrievedDash[2], 1.0);
}

// Test empty line dash
TEST_F(GfxStateTest_563, EmptyLineDash_563) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);

    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_EQ(retrievedDash.size(), 0u);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_563, ShiftCTMAndClip_563) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 100.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 100.0);
}

// Test transformWidth
TEST_F(GfxStateTest_563, TransformWidth_563) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double result = state->transformWidth(1.0);
    EXPECT_GT(result, 0.0);
}

// Test transformWidth with zero width
TEST_F(GfxStateTest_563, TransformWidthZero_563) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double result = state->transformWidth(0.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_563, GetTransformedLineWidth_563) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double result = state->getTransformedLineWidth();
    EXPECT_GT(result, 0.0);
}

// Test multiple save/restore chain
TEST_F(GfxStateTest_563, MultipleSaveRestore_563) {
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

// Test isParentState
TEST_F(GfxStateTest_563, IsParentState_563) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->isParentState(state.get()));

    GfxState *restored = saved->restore();
    // After restore, the relationship changes
}

// Test getPath
TEST_F(GfxStateTest_563, GetPath_563) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test getReusablePath
TEST_F(GfxStateTest_563, GetReusablePath_563) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// Test parseBlendMode with normal mode
TEST_F(GfxStateTest_563, ParseBlendModeNormal_563) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, GfxBlendMode::Normal);
    }
}

// Test fill opacity boundary values
TEST_F(GfxStateTest_563, FillOpacityBoundary_563) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);

    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test stroke opacity boundary values
TEST_F(GfxStateTest_563, StrokeOpacityBoundary_563) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);

    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test negative line width (edge case)
TEST_F(GfxStateTest_563, NegativeLineWidth_563) {
    state->setLineWidth(-1.0);
    // Just verify it doesn't crash; behavior is implementation-defined
    double lw = state->getLineWidth();
    (void)lw;
}

// Test different DPI values
TEST_F(GfxStateTest_563, DifferentDPI_563) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState highDpiState(300.0, 600.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 600.0);
}

// Test construction with upsideDown = false
TEST_F(GfxStateTest_563, ConstructionNotUpsideDown_563) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState notUpsideDown(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(notUpsideDown.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(notUpsideDown.getPageHeight(), 792.0);
}

// Test curX and curY after moveTo
TEST_F(GfxStateTest_563, CurXYAfterMoveTo_563) {
    state->moveTo(42.0, 84.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 42.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 84.0);
}

// Test curX and curY after lineTo
TEST_F(GfxStateTest_563, CurXYAfterLineTo_563) {
    state->moveTo(0.0, 0.0);
    state->lineTo(55.0, 66.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 55.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 66.0);
}

// Test curX and curY after curveTo
TEST_F(GfxStateTest_563, CurXYAfterCurveTo_563) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
}

// Test fill color space is initially set
TEST_F(GfxStateTest_563, FillColorSpaceInitial_563) {
    GfxColorSpace *cs = state->getFillColorSpace();
    // Should have a default color space after construction
    EXPECT_NE(cs, nullptr);
}

// Test stroke color space is initially set
TEST_F(GfxStateTest_563, StrokeColorSpaceInitial_563) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test fill pattern initially null
TEST_F(GfxStateTest_563, FillPatternInitiallyNull_563) {
    GfxPattern *pat = state->getFillPattern();
    EXPECT_EQ(pat, nullptr);
}

// Test stroke pattern initially null
TEST_F(GfxStateTest_563, StrokePatternInitiallyNull_563) {
    GfxPattern *pat = state->getStrokePattern();
    EXPECT_EQ(pat, nullptr);
}

// Test rotation values
TEST_F(GfxStateTest_563, RotationValues_563) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    GfxState rot0(72.0, 72.0, &pageBox, 0, true);
    EXPECT_EQ(rot0.getRotate(), 0);

    GfxState rot90(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rot90.getRotate(), 90);

    GfxState rot180(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rot180.getRotate(), 180);

    GfxState rot270(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rot270.getRotate(), 270);
}

// Test getFont returns nullptr when no font set
TEST_F(GfxStateTest_563, GetFontInitiallyNull_563) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// Test text shift updates curX, curY
TEST_F(GfxStateTest_563, TextShift_563) {
    // Just verify it doesn't crash
    state->textShift(10.0, 20.0);
}

// Test textShiftWithUserCoords
TEST_F(GfxStateTest_563, TextShiftWithUserCoords_563) {
    state->textShiftWithUserCoords(5.0, 10.0);
    // Just verify it doesn't crash
}

// Test clip operation
TEST_F(GfxStateTest_563, Clip_563) {
    state->moveTo(100.0, 100.0);
    state->lineTo(200.0, 100.0);
    state->lineTo(200.0, 200.0);
    state->closePath();
    state->clip();
    // Verify clip box is updated
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToStrokePath
TEST_F(GfxStateTest_563, ClipToStrokePath_563) {
    state->setLineWidth(2.0);
    state->moveTo(100.0, 100.0);
    state->lineTo(200.0, 200.0);
    state->clipToStrokePath();
    // Should not crash
}

// Test save preserves state properties
TEST_F(GfxStateTest_563, SavePreservesProperties_563) {
    state->setFillOpacity(0.4);
    state->setStrokeOpacity(0.6);
    state->setLineWidth(5.0);
    state->setMiterLimit(12.0);
    state->setCharSpace(2.0);
    state->setWordSpace(3.0);

    GfxState *saved = state->save();
    EXPECT_DOUBLE_EQ(saved->getFillOpacity(), 0.4);
    EXPECT_DOUBLE_EQ(saved->getStrokeOpacity(), 0.6);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 5.0);
    EXPECT_DOUBLE_EQ(saved->getMiterLimit(), 12.0);
    EXPECT_DOUBLE_EQ(saved->getCharSpace(), 2.0);
    EXPECT_DOUBLE_EQ(saved->getWordSpace(), 3.0);

    saved->restore();
}

// Test identity CTM transform
TEST_F(GfxStateTest_563, IdentityCTMTransform_563) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(42.0, 84.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 42.0);
    EXPECT_DOUBLE_EQ(y2, 84.0);
}

// Test scaling CTM
TEST_F(GfxStateTest_563, ScalingCTMTransform_563) {
    state->setCTM(3.0, 0.0, 0.0, 4.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 30.0);
    EXPECT_DOUBLE_EQ(y2, 40.0);
}

// Test non-square page box
TEST_F(GfxStateTest_563, NonSquarePageBox_563) {
    PDFRectangle pageBox;
    pageBox.x1 = 10;
    pageBox.y1 = 20;
    pageBox.x2 = 100;
    pageBox.y2 = 300;
    GfxState customState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(customState.getPageWidth(), 90.0);
    EXPECT_DOUBLE_EQ(customState.getPageHeight(), 280.0);
}
